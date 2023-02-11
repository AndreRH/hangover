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

void WINAPI emu_run(I386_CONTEXT *c)
{
    static char gdt[1024*9], idt[255*8];
    struct emu_run_params params = { c, gdt, idt };
    EMUAPI_CALL( emu_run, &params );
}

USHORT get_flags( USHORT machine )
{
    WOW64_CPURESERVED *cpu;
    USHORT ret;

    if (!NtCurrentTeb()->WowTebOffset) return 0;
    cpu = NtCurrentTeb()->TlsSlots[WOW64_TLS_CPURESERVED];
    if (cpu->Machine != machine) return 0;
    ret = cpu->Flags;
    cpu->Flags = 0;
    return ret;
}

NTSTATUS WINAPI Wow64SystemServiceEx( UINT num, UINT *args );

static const UINT16 bopcode = 0x040f;
static const UINT16 unxcode = 0x070f;

static NTSTATUS (WINAPI *p__wine_unix_call)( unixlib_handle_t, unsigned int, void * );

void WINAPI handle_unix_call(I386_CONTEXT *c)
{
    HMODULE module;
    UNICODE_STRING str;
    UINT32 *p;
    NTSTATUS ret;
    UINT32 p0;
    unixlib_handle_t *handle;

    p = ULongToPtr(c->Esp);
    handle = (void*)&p[1];

    if (!p__wine_unix_call)
    {
        RtlInitUnicodeString( &str, L"ntdll.dll" );
        LdrGetDllHandle( NULL, 0, &str, &module );
        p__wine_unix_call = RtlFindExportedRoutineByName( module, "__wine_unix_call" );
    }

    p0 = p[0];
    ret = p__wine_unix_call(*handle, p[3], ULongToPtr(p[4]));
    c->Eip=p0;
    c->Esp+=4+8+4+4;
    c->Eax=ret;
}

void WINAPI handle_syscall(I386_CONTEXT *c)
{
    I386_CONTEXT *wow_context;
    NTSTATUS ret;

    RtlWow64GetCurrentCpuArea(NULL, (void **)&wow_context, NULL);

    ret = Wow64SystemServiceEx(wow_context->Eax, ULongToPtr(wow_context->Esp+8));

    if (!(get_flags(IMAGE_FILE_MACHINE_I386) & WOW64_CPURESERVED_FLAG_RESET_STATE))
    {
        TRACE("ADAPTING %x\n", get_flags(IMAGE_FILE_MACHINE_I386));
        wow_context->Eip=*(DWORD*)ULongToPtr(wow_context->Esp);
        wow_context->Esp+=4;
        wow_context->Eax=ret;
    }
    else
    {
        TRACE("NOT ADAPTING !!! %x\n", get_flags(IMAGE_FILE_MACHINE_I386));
    }
}


/**********************************************************************
 *           BTCpuProcessInit  (wow64cpu.@)
 */
void WINAPI BTCpuSimulate(void)
{
    while (1)
    {
        I386_CONTEXT *wow_context;

        RtlWow64GetCurrentCpuArea(NULL, (void **)&wow_context, NULL);

        TRACE( "START %p %08lx\n", wow_context, wow_context->Eip );

        emu_run(wow_context);

        if (ULongToPtr(wow_context->Eip) == &unxcode)
        {
            // unix call!
            handle_unix_call(wow_context);
        }
        else if (ULongToPtr(wow_context->Eip) == &bopcode)
        {
            // sys call!
            handle_syscall(wow_context);
        }
        else
        {
            DWORD arg[] = {0, 0};

            ERR("Client crashed\n");

            //NtDelayExecution
            Wow64SystemServiceEx(50, (UINT*)&arg);
        }
    }
}


/**********************************************************************
 *           BTCpuProcessInit  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuProcessInit(void)
{
    if ((ULONG_PTR)BTCpuProcessInit >> 32)
    {
        ERR( "wow64cpu loaded above 4G, disabling\n" );
        return STATUS_INVALID_ADDRESS;
    }
    return STATUS_SUCCESS;
}


/**********************************************************************
 *           BTCpuGetBopCode  (wow64cpu.@)
 */
void * WINAPI BTCpuGetBopCode(void)
{
    return (UINT32*)&bopcode;
}

void * WINAPI __wine_get_unix_opcode(void)
{
    return (UINT32*)&unxcode;
}

/**********************************************************************
 *           BTCpuGetContext  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuGetContext( HANDLE thread, HANDLE process, void *unknown, I386_CONTEXT *ctx )
{
    return NtQueryInformationThread( thread, ThreadWow64Context, ctx, sizeof(*ctx), NULL );
}


/**********************************************************************
 *           BTCpuSetContext  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuSetContext( HANDLE thread, HANDLE process, void *unknown, I386_CONTEXT *ctx )
{
    return NtSetInformationThread( thread, ThreadWow64Context, ctx, sizeof(*ctx) );
}


/**********************************************************************
 *           BTCpuResetToConsistentState  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuResetToConsistentState( EXCEPTION_POINTERS *ptrs )
{
    FIXME( "NYI\n" );
    return STATUS_SUCCESS;
}


/**********************************************************************
 *           BTCpuTurboThunkControl  (wow64cpu.@)
 */
NTSTATUS WINAPI BTCpuTurboThunkControl( ULONG enable )
{
    FIXME( "NYI\n" );
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
