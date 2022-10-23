/*
 * Copyright 2022 André Zwing
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

WINE_DEFAULT_DEBUG_CHANNEL(qemu);

__thread CPUState *thread_cpu;

#define ExitProcess(x) exit(x)

static void (*pcpu_reset)(CPUState*);
static void (*pcpu_dump_state)(CPUState *cpu, FILE *f, int flags);
//static void* (*pcpu_set_fpuc)(void);
static void (*pcpu_exec_start)(CPUState *);
static int (*pcpu_exec)(CPUState *);
static void (*pcpu_exec_end)(CPUState *);
static void (*pprocess_queued_cpu_work)(CPUState *);
static void (*pcpu_exec_step_atomic)(CPUState *);
static void (*prcu_register_thread)(void);
static void (*ptcg_register_thread)(void);
static void (*pmodule_call_init)(module_init_type);
static void (*pqemu_init_cpu_list)(void);
static void (*ptcg_exec_init)(unsigned long);
static void (*ptcg_prologue_init)(void*/*TCGContext*/);
static void (*ptcg_region_init)(void);
static CPUState* (*pcpu_create)(const char *typename);
//static void (*pdo_qemu_init_cpu_register_types)(void);
//static void (*pdo_qemu_init_arm_cpu_register_types)(void);
static int (*pqemu_str_to_log_mask)(const char *);
static void (*pqemu_log_needs_buffers)(void);
static void (*pqemu_set_log)(int);
static void (*perror_init)(const char *);
/*
static TranslationBlock* (*ptb_htable_lookup)(CPUState *cpu, target_ulong pc,
                                   target_ulong cs_base, uint32_t flags,
                                   uint32_t cf_mask);
static int (*pcpu_memory_rw_debug)(CPUState *cpu, target_ulong addr, void *ptr, target_ulong len, bool is_write);*/
static int (*ppage_get_flags)(target_ulong address);
static void (*ppage_set_flags)(target_ulong start, target_ulong end, int flags); /* did the trick */

//static CPUState* *pthread_cpu;
static void* *ptcg_ctx;
static unsigned long *pguest_base;
static bool *phave_guest_base;

static void *emuapi_handle;

static NTSTATUS attach( void *args )
{
    int log_mask;

    if (!(emuapi_handle = dlopen( "/opt/libqemu-i386.so", RTLD_NOW ))) return STATUS_DLL_NOT_FOUND;

    ERR("HERE\n");

#define LOAD_FUNCPTR(f) if((p##f = dlsym(emuapi_handle, #f)) == NULL) {ERR(#f " %p\n", p##f);return STATUS_ENTRYPOINT_NOT_FOUND;}
#define LOAD_FUNCPTR_OPT(f) if((p##f = dlsym(emuapi_handle, #f)) == NULL) {ERR(#f " %p\n", p##f);}
    LOAD_FUNCPTR(cpu_reset);
    LOAD_FUNCPTR(cpu_dump_state);
    //LOAD_FUNCPTR(cpu_set_fpuc);
    LOAD_FUNCPTR(cpu_exec_start);
    LOAD_FUNCPTR(cpu_exec);
    LOAD_FUNCPTR(cpu_exec_end);
    LOAD_FUNCPTR(process_queued_cpu_work);
    LOAD_FUNCPTR(cpu_exec_step_atomic);
    LOAD_FUNCPTR(rcu_register_thread);
    LOAD_FUNCPTR(tcg_register_thread);
    LOAD_FUNCPTR(module_call_init);
    LOAD_FUNCPTR(qemu_init_cpu_list);
    LOAD_FUNCPTR_OPT(tcg_exec_init);
    LOAD_FUNCPTR(tcg_prologue_init);
    LOAD_FUNCPTR(tcg_region_init);
    LOAD_FUNCPTR(cpu_create);
    //LOAD_FUNCPTR_OPT(do_qemu_init_arm_cpu_register_types);
    //LOAD_FUNCPTR(do_qemu_init_cpu_register_types);
    LOAD_FUNCPTR(qemu_str_to_log_mask);
    LOAD_FUNCPTR_OPT(qemu_log_needs_buffers);
    LOAD_FUNCPTR(qemu_set_log);
    LOAD_FUNCPTR(error_init);
    /*LOAD_FUNCPTR(tb_htable_lookup);
    LOAD_FUNCPTR(cpu_memory_rw_debug);*/
    LOAD_FUNCPTR(page_get_flags);
    LOAD_FUNCPTR(page_set_flags);

    //LOAD_FUNCPTR(thread_cpu);
    LOAD_FUNCPTR(tcg_ctx);
    LOAD_FUNCPTR(guest_base);
    LOAD_FUNCPTR(have_guest_base);
#undef LOAD_FUNCPTR_OPT
#undef LOAD_FUNCPTR

    perror_init("MYemu");
    pmodule_call_init(MODULE_INIT_TRACE);
    pqemu_init_cpu_list();
    pmodule_call_init(MODULE_INIT_QOM);

    log_mask = pqemu_str_to_log_mask("page");
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
        ERR("Unable to find CPU definition\n");
        ExitProcess(EXIT_FAILURE);
    }
    pcpu_reset(thread_cpu);
}

static inline void *get_wow_teb( TEB *teb )
{
    return teb->WowTebOffset ? (void *)((char *)teb + teb->WowTebOffset) : NULL;
}

static void ctx_to_qemu(I386_CONTEXT *c, CPUX86State *env)
{
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

    env->regs[R_ES] = c->SegEs;
    env->regs[R_CS] = c->SegCs;
    env->regs[R_SS] = c->SegSs;
    env->regs[R_DS] = c->SegDs;
    env->regs[R_FS] = c->SegFs;
    env->regs[R_GS] = c->SegGs;

    /* TODO: debug registers */
    /* TODO: FloatSave */
    /* TODO: ExtendedRegisters */
}

static void qemu_to_ctx(CPUX86State *env, I386_CONTEXT *c)
{
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

    c->SegEs = env->regs[R_ES];
    c->SegCs = env->regs[R_CS];
    c->SegSs = env->regs[R_SS];
    c->SegDs = env->regs[R_DS];
    c->SegFs = env->regs[R_FS];
    c->SegGs = env->regs[R_GS];

    /* TODO: debug registers */
    /* TODO: FloatSave */
    /* TODO: ExtendedRegisters */
}

static NTSTATUS emu_run( void *args )
{
    const struct emu_run_params *params = args;
    CPUState *cs;
    CPUX86State *env;
    int trapnr;

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
    }
    cs = thread_cpu;
    env = cs->env_ptr;

    ctx_to_qemu(params->c, env);

    pcpu_exec_start(cs);
    ERR("exec_started\n");
    pcpu_dump_state(cs, stderr, 0);
    trapnr = pcpu_exec(cs);
    ERR("cpu_exec returned\n");
    pcpu_exec_end(cs);
    pprocess_queued_cpu_work(cs);

    switch (trapnr)
    {
        case EXCP_SWI:
            FIXME("MY SYSCALL\n");
            pcpu_dump_state(cs, stderr, 0);
            #if 0
            if (1)
            {
                uint32_t *ptr = (void*)env->regs[13];
                int i;
                for (i=0; i<6; i++)
                {
                    FIXME("%i %08x\n", i, *ptr);
                    ptr++;
                }
            }
            #endif
            break;

        case EXCP_INTERRUPT:
            FIXME("MY async INTERRUPT?\n");
            /* just indicate that signals should be handled asap */
            //break;
            pcpu_dump_state(cs, stderr, 0);
            ExitProcess(255);

        default:
            ERR("Unhandled trap %x, exiting.\n", trapnr);
            pcpu_dump_state(cs, stderr, 0);
            ExitProcess(255);
    }

    //ERR("SYSCALL ID %04x\n", env->regs[12]);
    qemu_to_ctx(env, params->c);

    return 0;
}

const unixlib_entry_t __wine_unix_call_funcs[] =
{
    attach,
    detach,
    emu_run,
};
