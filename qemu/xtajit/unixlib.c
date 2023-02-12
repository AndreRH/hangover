/*
 * Copyright 2022-2023 André Zwing
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#if 0
#pragma makedep unix
#endif

#include "config.h"

#include <stdarg.h>
#include <dlfcn.h>

#include "ntstatus.h"
#define WIN32_NO_STATUS
#include "unixlib.h"
#include "wine/debug.h"
#include "qemu.h"

WINE_DEFAULT_DEBUG_CHANNEL(wow);

__thread CPUState *thread_cpu;

#define ExitProcess(x) exit(x)
#define h2g(x) (x)
#define g2h(x) (x)

typedef DWORD qemu_ptr, qemu_handle;

static void (*pcpu_reset)(CPUState*);
static void (*pcpu_dump_state)(CPUState *cpu, FILE *f, int flags);
static void (*pcpu_exec_start)(CPUState *);
static int (*pcpu_exec)(CPUState *);
static void (*pcpu_exec_end)(CPUState *);
static void (*pprocess_queued_cpu_work)(CPUState *);
static void (*prcu_register_thread)(void);
static void (*ptcg_register_thread)(void);
static void (*pmodule_call_init)(module_init_type);
static void (*pqemu_init_cpu_list)(void);
static void (*ptcg_exec_init)(unsigned long);
static void (*ptcg_prologue_init)(void*/*TCGContext*/);
static void (*ptcg_region_init)(void);
static CPUState* (*pcpu_create)(const char *typename);
static int (*pqemu_str_to_log_mask)(const char *);
static void (*pqemu_log_needs_buffers)(void);
static void (*pqemu_set_log)(int);
static void (*perror_init)(const char *);
static void (*ppage_set_flags)(target_ulong start, target_ulong end, int flags);
static void (*pcpu_sync_bndcs_hflags)(CPUX86State *env);

static void* *ptcg_ctx;

static void *emuapi_handle;

static NTSTATUS attach( void *args )
{
    int log_mask;

    if (!(emuapi_handle = dlopen( "/opt/libqemu-i386.so", RTLD_NOW ))) return STATUS_DLL_NOT_FOUND;

#define LOAD_FUNCPTR(f) if((p##f = dlsym(emuapi_handle, #f)) == NULL) {ERR(#f " %p\n", p##f);return STATUS_ENTRYPOINT_NOT_FOUND;}
#define LOAD_FUNCPTR_OPT(f) if((p##f = dlsym(emuapi_handle, #f)) == NULL) {ERR(#f " %p\n", p##f);}
    LOAD_FUNCPTR(cpu_reset);
    LOAD_FUNCPTR(cpu_dump_state);
    LOAD_FUNCPTR(cpu_exec_start);
    LOAD_FUNCPTR(cpu_exec);
    LOAD_FUNCPTR(cpu_exec_end);
    LOAD_FUNCPTR(process_queued_cpu_work);
    LOAD_FUNCPTR(rcu_register_thread);
    LOAD_FUNCPTR(tcg_register_thread);
    LOAD_FUNCPTR(module_call_init);
    LOAD_FUNCPTR(qemu_init_cpu_list);
    LOAD_FUNCPTR_OPT(tcg_exec_init);
    LOAD_FUNCPTR(tcg_prologue_init);
    LOAD_FUNCPTR(tcg_region_init);
    LOAD_FUNCPTR(cpu_create);
    LOAD_FUNCPTR(qemu_str_to_log_mask);
    LOAD_FUNCPTR_OPT(qemu_log_needs_buffers);
    LOAD_FUNCPTR(qemu_set_log);
    LOAD_FUNCPTR(error_init);
    LOAD_FUNCPTR(page_set_flags);
    LOAD_FUNCPTR(cpu_sync_bndcs_hflags);
    LOAD_FUNCPTR(tcg_ctx);
#undef LOAD_FUNCPTR_OPT
#undef LOAD_FUNCPTR

    perror_init("MYemu");
    pmodule_call_init(MODULE_INIT_TRACE);
    pqemu_init_cpu_list();
    pmodule_call_init(MODULE_INIT_QOM);

    log_mask = pqemu_str_to_log_mask("");
    if (log_mask) {
        if (pqemu_log_needs_buffers)
            pqemu_log_needs_buffers();
        pqemu_set_log(log_mask);
    }

    if (ptcg_exec_init)
        ptcg_exec_init(0);
    thread_cpu = pcpu_create(X86_CPU_TYPE_NAME("core2duo"));
    pcpu_reset(thread_cpu);

    ptcg_prologue_init(*ptcg_ctx);
    ptcg_region_init();
    ppage_set_flags(4096, 0x80000000, 8|4|2|1);

    return STATUS_SUCCESS;
}

static NTSTATUS detach( void *args )
{
    dlclose( emuapi_handle );
    return STATUS_SUCCESS;
}

static void init_thread_cpu(void)
{
    if (!thread_cpu)
        thread_cpu = pcpu_create(X86_CPU_TYPE_NAME("core2duo"));
    if (!thread_cpu)
    {
        fprintf(stderr, "Unable to find CPU definition\n");
    }
    pcpu_reset(thread_cpu);
}

static inline void *get_wow_teb( TEB *teb )
{
    return teb->WowTebOffset ? (void *)((char *)teb + teb->WowTebOffset) : NULL;
}

static void ctx_to_qemu(I386_CONTEXT *c, CPUX86State *env, int first_time)
{
    TEB *teb = NtCurrentTeb();
    void *wowteb = get_wow_teb(teb);
    int i;

    env->regs[R_EAX] = c->Eax;
    env->regs[R_EBX] = c->Ebx;
    env->regs[R_ECX] = c->Ecx;
    env->regs[R_EDX] = c->Edx;
    env->regs[R_ESI] = c->Esi;
    env->regs[R_EDI] = c->Edi;
    env->regs[R_EBP] = c->Ebp;
    env->regs[R_ESP] = c->Esp;

    env->eip = c->Eip;
    env->eflags = c->EFlags;

    env->segs[R_ES].selector = c->SegEs;
    env->segs[R_CS].selector = c->SegCs;
    env->segs[R_SS].selector = c->SegSs;
    env->segs[R_DS].selector = c->SegDs;
    env->segs[R_FS].selector = c->SegFs;
    env->segs[R_GS].selector = c->SegGs;

    if (first_time)
    {
        first_time = 0;
        env->segs[R_ES].base = 0;
        env->segs[R_CS].base = 0;
        env->segs[R_SS].base = 0;
        env->segs[R_DS].base = 0;
        env->segs[R_FS].base = PtrToUlong(wowteb);
        env->segs[R_GS].base = 0;
        env->segs[R_ES].limit = 0xffffffff;
        env->segs[R_CS].limit = 0xffffffff;
        env->segs[R_SS].limit = 0xffffffff;
        env->segs[R_DS].limit = 0xffffffff;
        env->segs[R_FS].limit = 0xffffffff;
        env->segs[R_GS].limit = 0xffffffff;
        env->segs[R_ES].flags = 0x00cff300;
        env->segs[R_CS].flags = 0x00cffb00;
        env->segs[R_SS].flags = 0x00cff300;
        env->segs[R_DS].flags = 0x00cff300;
        env->segs[R_FS].flags = 0x00cff300;
        env->segs[R_GS].flags = 0x00cff300;

    /* update hflags */
    {
        unsigned int new_hflags;

        /* update the hidden flags */
        {
            if (1) { //cs
                    /* legacy / compatibility case */
                    new_hflags = (env->segs[R_CS].flags & DESC_B_MASK)
                        >> (DESC_B_SHIFT - HF_CS32_SHIFT);
                    env->hflags = (env->hflags & ~(HF_CS32_MASK | HF_CS64_MASK)) |
                        new_hflags;
            }
            if (1) { //ss
                uint32_t flags=0x00cff300;
                int cpl = (flags >> DESC_DPL_SHIFT) & 3;
    #if HF_CPL_MASK != 3
    #error HF_CPL_MASK is hardcoded
    #endif
                env->hflags = (env->hflags & ~HF_CPL_MASK) | cpl;
                /* Possibly switch between BNDCFGS and BNDCFGU */
                pcpu_sync_bndcs_hflags(env);
            }
            new_hflags = (env->segs[R_SS].flags & DESC_B_MASK)
                >> (DESC_B_SHIFT - HF_SS32_SHIFT);
            if (env->hflags & HF_CS64_MASK) {
                /* zero base assumed for DS, ES and SS in long mode */
            } else if (!(env->cr[0] & CR0_PE_MASK) ||
                       (env->eflags & VM_MASK) ||
                       !(env->hflags & HF_CS32_MASK)) {
                /* XXX: try to avoid this test. The problem comes from the
                   fact that is real mode or vm86 mode we only modify the
                   'base' and 'selector' fields of the segment cache to go
                   faster. A solution may be to force addseg to one in
                   translate-i386.c. */
                new_hflags |= HF_ADDSEG_MASK;
            } else {
                new_hflags |= ((env->segs[R_DS].base |
                                env->segs[R_ES].base |
                                env->segs[R_SS].base) != 0) <<
                    HF_ADDSEG_SHIFT;
            }
            env->hflags = (env->hflags &
                           ~(HF_SS32_MASK | HF_ADDSEG_MASK)) | new_hflags;
        }
    }
    }


    /* FloatSave */
    env->fpus = c->FloatSave.StatusWord;
    env->fpuc = c->FloatSave.ControlWord;
    for (i = 0; i < 8; i++)
    {
        if ((c->FloatSave.TagWord >> (2 * i)) & 3) env->fptags[i] = 1;  /* empty */
        else env->fptags[i] = 0;
    }
    memcpy(env->fpregs, c->FloatSave.RegisterArea, sizeof(c->FloatSave.RegisterArea));

    /* debug registers */
    env->dr[0] = c->Dr0;
    env->dr[1] = c->Dr1;
    env->dr[2] = c->Dr2;
    env->dr[3] = c->Dr3;
    env->dr[6] = c->Dr6;
    env->dr[7] = c->Dr7;

    /* TODO: ExtendedRegisters -> X86XSaveArea */
}

static void qemu_to_ctx(CPUX86State *env, I386_CONTEXT *c)
{
    int i;

    c->Eax = env->regs[R_EAX];
    c->Ebx = env->regs[R_EBX];
    c->Ecx = env->regs[R_ECX];
    c->Edx = env->regs[R_EDX];
    c->Esi = env->regs[R_ESI];
    c->Edi = env->regs[R_EDI];
    c->Ebp = env->regs[R_EBP];
    c->Esp = env->regs[R_ESP];

    c->Eip = env->eip;
    c->EFlags = env->eflags;

    c->SegEs = env->segs[R_ES].selector;
    c->SegCs = env->segs[R_CS].selector;
    c->SegSs = env->segs[R_SS].selector;
    c->SegDs = env->segs[R_DS].selector;
    c->SegFs = env->segs[R_FS].selector;
    c->SegGs = env->segs[R_GS].selector;

    /* FloatSave */
    c->FloatSave.StatusWord = env->fpus;
    c->FloatSave.ControlWord = env->fpuc;
    c->FloatSave.TagWord = 0;
    for (i = 0; i < 8; i++)
    {
        int tag;
        if (env->fptags[i] == 0) /* empty */
            tag = 3;
        else
            tag = 0;
        c->FloatSave.TagWord |= tag >> (2 * i);
    }
    memcpy(c->FloatSave.RegisterArea, env->fpregs, sizeof(c->FloatSave.RegisterArea));

    /* debug registers */
    c->Dr0 = env->dr[0];
    c->Dr1 = env->dr[1];
    c->Dr2 = env->dr[2];
    c->Dr3 = env->dr[3];
    c->Dr6 = env->dr[6];
    c->Dr7 = env->dr[7];

    /* TODO: ExtendedRegisters */
}

static inline uint32_t bswap32(uint32_t x)
{
    return (((x & 0x000000ffU) << 24) |
            ((x & 0x0000ff00U) <<  8) |
            ((x & 0x00ff0000U) >>  8) |
            ((x & 0xff000000U) >> 24));
}
static inline uint32_t tswap32(uint32_t s)
{
    return bswap32(s);
}

static void write_dt(void *ptr, unsigned long addr, unsigned long limit,
                     int flags)
{
    unsigned int e1, e2;
    uint32_t *p;
    e1 = (addr << 16) | (limit & 0xffff);
    e2 = ((addr >> 16) & 0xff) | (addr & 0xff000000) | (limit & 0x000f0000);
    e2 |= flags;
    p = ptr;
    p[0] = tswap32(e1);
    p[1] = tswap32(e2);
}
static void set_gate(void *ptr, unsigned int type, unsigned int dpl,
                     uint32_t addr, unsigned int sel)
{
    uint32_t *p, e1, e2;
    e1 = (addr & 0xffff) | (sel << 16);
    e2 = (addr & 0xffff0000) | 0x8000 | (dpl << 13) | (type << 8);
    p = ptr;
    p[0] = tswap32(e1);
    p[1] = tswap32(e2);
}

/* only dpl matters as we do only user space emulation */
static void set_idt(int n, unsigned int dpl, uint64_t *idt_table)
{
    set_gate(idt_table + n, 0, dpl, 0, 0);
}

static NTSTATUS emu_run( void *args )
{
    static int first_time = 1;
    const struct emu_run_params *params = args;
    CPUState *cs;
    CPUX86State *env;
    int trapnr;
    uint64_t *gdt_table;

    uint64_t *ldt_table = params->ldt;
    TEB *teb = NtCurrentTeb();
    void *wowteb = get_wow_teb(teb);

    if (!params->c->Eip)
    {
        ERR("Attempting to execute NULL.\n");
        ExitProcess(1);
    }

    if (!thread_cpu)
    {
        FIXME("Initializing new CPU for thread %x.\n", GetCurrentThreadId());
        prcu_register_thread();
        ptcg_register_thread();
        init_thread_cpu();
        ppage_set_flags(4096, 0x80000000, 8|4|2|1);
        first_time = 1;
    }
    cs = thread_cpu;
    env = cs->env_ptr;

    ctx_to_qemu(params->c, env, first_time);

    if (first_time)
    {
        first_time = 0;
        env->cr[0] = CR0_PG_MASK | CR0_WP_MASK | CR0_PE_MASK;
        env->hflags |= HF_PE_MASK | HF_CPL_MASK;
        //if (env->features[FEAT_1_EDX] & CPUID_SSE) {
            env->cr[4] |= CR4_OSFXSR_MASK;
            env->hflags |= HF_OSFXSR_MASK;
        //}
        env->eflags |= IF_MASK;


        env->idt.limit = 255;
        env->idt.base = PtrToUlong(params->idt);
        set_idt(0, 0, params->idt);
        set_idt(1, 0, params->idt);
        set_idt(2, 0, params->idt);
        set_idt(3, 3, params->idt);
        set_idt(4, 3, params->idt);
        set_idt(5, 0, params->idt);
        set_idt(6, 0, params->idt);
        set_idt(7, 0, params->idt);
        set_idt(8, 0, params->idt);
        set_idt(9, 0, params->idt);
        set_idt(10, 0, params->idt);
        set_idt(11, 0, params->idt);
        set_idt(12, 0, params->idt);
        set_idt(13, 0, params->idt);
        set_idt(14, 0, params->idt);
        set_idt(15, 0, params->idt);
        set_idt(16, 0, params->idt);
        set_idt(17, 0, params->idt);
        set_idt(18, 0, params->idt);
        set_idt(19, 0, params->idt);
        set_idt(0x80, 3, params->idt);

        env->gdt.base = PtrToUlong(params->gdt);
        gdt_table = params->gdt;
        env->gdt.limit = sizeof(uint64_t) * 9 - 1;
            write_dt(&gdt_table[__USER_CS >> 3], 0, 0xfffff,
                    DESC_G_MASK | DESC_B_MASK | DESC_P_MASK | DESC_S_MASK |
                    (3 << DESC_DPL_SHIFT) | (0xa << DESC_TYPE_SHIFT));
            write_dt(&gdt_table[__USER_DS >> 3], 0, 0xfffff,
                    DESC_G_MASK | DESC_B_MASK | DESC_P_MASK | DESC_S_MASK |
                    (3 << DESC_DPL_SHIFT) | (0x2 << DESC_TYPE_SHIFT));

        env->ldt.base = PtrToUlong(ldt_table);
        env->ldt.limit = sizeof(uint64_t) * 256;
        write_dt(&ldt_table[0x63 >> 3], PtrToUlong(wowteb), 0xfff,
                DESC_G_MASK | DESC_B_MASK | DESC_P_MASK | DESC_S_MASK |
                (3 << DESC_DPL_SHIFT) | (0xa << DESC_TYPE_SHIFT));

        pcpu_sync_bndcs_hflags(env);
    }

    pcpu_exec_start(cs);
    trapnr = pcpu_exec(cs);
    pcpu_exec_end(cs);
    pprocess_queued_cpu_work(cs);

    switch (trapnr)
    {
        case EXCP06_ILLOP:
        case EXCP_SWI:
            break;

        default:
            ERR("Unhandled trap %x, exiting.\n", trapnr);
            pcpu_dump_state(cs, stderr, 0);
            ExitProcess(255);
    }

    qemu_to_ctx(env, params->c);

    return 0;
}

const unixlib_entry_t __wine_unix_call_funcs[] =
{
    attach,
    detach,
    emu_run,
};
