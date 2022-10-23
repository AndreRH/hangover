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

#include <string.h>
#include <stdarg.h>

#include "ntstatus.h"
#define WIN32_NO_STATUS
#include "windef.h"
#include "winbase.h"
#include "winreg.h"
#include "winnls.h"
#include "unixlib.h"
#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(wow);

static unixlib_handle_t emuapi_handle;

#define EMUAPI_CALL( func, params ) __wine_unix_call( emuapi_handle, unix_ ## func, params )

void WINAPI emu_run(ARM_CONTEXT *c)
{
    struct emu_run_params params = { c };
    EMUAPI_CALL( emu_run, &params );
}

void *get_cpu_area( USHORT machine )
{
    WOW64_CPURESERVED *cpu;
    ULONG align;

    if (!NtCurrentTeb()->WowTebOffset) return NULL;
#ifdef _WIN64
    cpu = NtCurrentTeb()->TlsSlots[WOW64_TLS_CPURESERVED];
#else
    cpu = ULongToPtr( NtCurrentTeb64()->TlsSlots[WOW64_TLS_CPURESERVED] );
#endif
    if (cpu->Machine != machine) return NULL;
    switch (cpu->Machine)
    {
    case IMAGE_FILE_MACHINE_I386: align = TYPE_ALIGNMENT(I386_CONTEXT); break;
    case IMAGE_FILE_MACHINE_AMD64: align = TYPE_ALIGNMENT(AMD64_CONTEXT); break;
    case IMAGE_FILE_MACHINE_ARMNT: align = TYPE_ALIGNMENT(ARM_CONTEXT); break;
    case IMAGE_FILE_MACHINE_ARM64: align = TYPE_ALIGNMENT(ARM64_NT_CONTEXT); break;
    default: return NULL;
    }
    return (void *)(((ULONG_PTR)(cpu + 1) + align - 1) & ~((ULONG_PTR)align - 1));
}

NTSTATUS WINAPI Wow64SystemServiceEx( UINT num, UINT *args );

/**********************************************************************
 *           BTCpuProcessInit  (wow64cpu.@)
 */
void WINAPI BTCpuSimulate(void)
{
    ARM_CONTEXT *wow_context_arm = get_cpu_area(IMAGE_FILE_MACHINE_ARMNT);
    NTSTATUS ret;
    ULONG bu_r3;

    ERR( "START %p %08lx\n", wow_context_arm, wow_context_arm->Pc );
    emu_run(wow_context_arm);
    ERR("wow_context_arm->R3 = %08lx\n", wow_context_arm->R3);
    bu_r3 = wow_context_arm->R3;
    ret = Wow64SystemServiceEx(wow_context_arm->R12, (void*)wow_context_arm->Sp);
    ERR("RET IS %lX    %ld %lx    wow_context_arm->R3 = %08lx %08lx\n", ret, wow_context_arm->R12, wow_context_arm->Sp, wow_context_arm->R3, bu_r3);
    if (wow_context_arm->R3 != bu_r3)
        ERR("WADDEMA!\n");
    if (wow_context_arm->R3 && wow_context_arm->R3 == bu_r3)
    {
        wow_context_arm->R0 = ret;
        wow_context_arm->Pc = wow_context_arm->R3;
        wow_context_arm->Sp += 4*4; /* pop r0-r3 */
    }
}

/**********************************************************************
 *           BTCpuProcessInit  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuProcessInit(void)
{
    if ((ULONG_PTR)BTCpuProcessInit >> 32)
    {
        ERR( "wowarmhw loaded above 4G, disabling\n" );
        return STATUS_INVALID_ADDRESS;
    }
    FIXME("SUCCESS! %p\n", BTCpuProcessInit);
    return STATUS_SUCCESS;
}


/**********************************************************************
 *           BTCpuGetBopCode  (wow64cpu.@)
 */
void * WINAPI BTCpuGetBopCode(void)
{
    static const UINT32 bopcode = 0xef000000;
    return (UINT32*)&bopcode;
}


/**********************************************************************
 *           BTCpuGetContext  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuGetContext( HANDLE thread, HANDLE process, void *unknown, ARM_CONTEXT *ctx )
{
    return NtQueryInformationThread( thread, ThreadWow64Context, ctx, sizeof(*ctx), NULL );
}


/**********************************************************************
 *           BTCpuSetContext  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuSetContext( HANDLE thread, HANDLE process, void *unknown, ARM_CONTEXT *ctx )
{
    return NtSetInformationThread( thread, ThreadWow64Context, ctx, sizeof(*ctx) );
}


/**********************************************************************
 *           BTCpuResetToConsistentState  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuResetToConsistentState( EXCEPTION_POINTERS *ptrs )
{
    ERR( "NYI\n" );
    return STATUS_SUCCESS;
}


/**********************************************************************
 *           BTCpuTurboThunkControl  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuTurboThunkControl( ULONG enable )
{
    ERR( "NYI\n" );
    if (enable) return STATUS_NOT_SUPPORTED;
    /* we don't have turbo thunks yet */
    return STATUS_SUCCESS;
}

BOOL WINAPI DllMain (HINSTANCE inst, DWORD reason, void *reserved )
{
    TRACE("%p,%lx,%p\n", inst, reason, reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            LdrDisableThreadCalloutsForDll(inst);
            if (NtQueryVirtualMemory( GetCurrentProcess(), inst, MemoryWineUnixFuncs,
                                      &emuapi_handle, sizeof(emuapi_handle), NULL ))
                return FALSE;
            if (EMUAPI_CALL( attach, NULL ))
                return FALSE;
            break;
        case DLL_PROCESS_DETACH:
            if (reserved) break;
            EMUAPI_CALL( detach, NULL );
            break;
    }

    return TRUE;
}
