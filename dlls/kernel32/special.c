/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <winternl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_GetEnvironmentStringsA
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

/* The headers have a #define that maps GetEnvironmentStringsA to GetEnvironmentStrings. */
LPSTR WINAPI qemu_GetEnvironmentStringsA(void)
{
    struct qemu_GetEnvironmentStringsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENVIRONMENTSTRINGSA);

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_GetEnvironmentStringsA(struct qemu_syscall *call)
{
    struct qemu_GetEnvironmentStringsA *c = (struct qemu_GetEnvironmentStringsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetEnvironmentStringsA();
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI CHAR WINAPI *GetCommandLineA(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCOMMANDLINEA);

    qemu_syscall(&call);

    return (CHAR *)call.iret;
}

#else

void qemu_GetCommandLineA(struct qemu_syscall *c)
{
    const TEB *teb;
    static char *cmdlineA;
    WINE_TRACE("\n");

    if (!cmdlineA) /* make an ansi version if we don't have it. Take from Wine. */
    {
        ANSI_STRING     ansi;

        teb = qemu_ops->qemu_getTEB();
        cmdlineA = !RtlUnicodeStringToAnsiString(&ansi, &teb->Peb->ProcessParameters->CommandLine, TRUE) ?
            ansi.Buffer : NULL;
    }

    c->iret = QEMU_H2G(cmdlineA);
}

#endif

#ifdef QEMU_DLL_GUEST

/* This just reads the PEB, so we should be able to do it without calling
 * the host, but Mingw's headers don't properly declare the PEB. So for now
 * call out of the VM to have access to Wine's winternl.h. */
WINBASEAPI WCHAR WINAPI *GetCommandLineW(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCOMMANDLINEW);

    qemu_syscall(&call);

    return (WCHAR *)call.iret;
}

#else

void qemu_GetCommandLineW(struct qemu_syscall *c)
{
    const TEB *teb = qemu_ops->qemu_getTEB();
    WINE_TRACE("\n");
    c->iret = QEMU_H2G(teb->Peb->ProcessParameters->CommandLine.Buffer);
}

#endif

struct qemu_ModuleFileName
{
    struct qemu_syscall super;
    uint64_t module;
    uint64_t name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetModuleFileNameA(HMODULE module, CHAR *name, DWORD size)
{
    struct qemu_ModuleFileName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEFILENAMEA);
    call.module = (uint64_t)module;
    call.name = (uint64_t)name;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI DWORD WINAPI GetModuleFileNameW(HMODULE module, WCHAR *name, DWORD size)
{
    struct qemu_ModuleFileName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEFILENAMEW);
    call.module = (uint64_t)module;
    call.name = (uint64_t)name;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetModuleFileNameA(struct qemu_syscall *call)
{
    struct qemu_ModuleFileName *c = (struct qemu_ModuleFileName *)call;
    WCHAR *wbuf;
    WINE_TRACE("\n");

    wbuf = HeapAlloc(GetProcessHeap(), 0, (c->size + 1) * sizeof(*wbuf));

    /* Allocate one more to make sure WideCharToMultiByte triggers an error, if there is an error. */
    qemu_ops->qemu_GetModuleFileName((HANDLE)c->module, wbuf, c->size ? c->size + 1 : 0);

    c->super.iret = WideCharToMultiByte(CP_ACP, 0, wbuf, -1, QEMU_G2H(c->name), c->size, NULL, NULL);
    if (!c->super.iret)
        c->super.iret = WideCharToMultiByte(CP_ACP, 0, wbuf, c->size, QEMU_G2H(c->name), c->size, NULL, NULL);

    HeapFree(GetProcessHeap(), 0, wbuf);
}

void qemu_GetModuleFileNameW(struct qemu_syscall *call)
{
    struct qemu_ModuleFileName *c = (struct qemu_ModuleFileName *)call;
    WINE_TRACE("\n");
    c->super.iret = qemu_ops->qemu_GetModuleFileName((HANDLE)c->module, QEMU_G2H(c->name), c->size);
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetProcessHeap()
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETPROCESSHEAP);

    qemu_syscall(&call);

    return (HANDLE)call.iret;
}

#else

void qemu_GetProcessHeap(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    c->iret = (uint64_t)GetProcessHeap();
}

#endif

struct qemu_ModuleOpA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI GetModuleHandleA(const char *name)
{
    struct qemu_ModuleOpA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEHANDLEA);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HMODULE)call.super.iret;
}

#else

void qemu_GetModuleHandleA(struct qemu_syscall *call)
{
    struct qemu_ModuleOpA *c = (struct qemu_ModuleOpA *)call;
    WCHAR *nameW = NULL;
    int size;

    WINE_TRACE("(\"%s\")\n", (char *)QEMU_G2H(c->name));

    if (c->name)
    {
        size = MultiByteToWideChar(CP_ACP, 0, QEMU_G2H(c->name), -1, NULL, 0);
        nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(*nameW));
        MultiByteToWideChar(CP_ACP, 0, QEMU_G2H(c->name), -1, nameW, size);
    }

    c->super.iret = (uint64_t)qemu_ops->qemu_GetModuleHandleEx(
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, nameW);

    HeapFree(GetProcessHeap(), 0, nameW);
    WINE_TRACE("Returning %p\n", (void *)c->super.iret);
}

#endif

struct qemu_GetModuleHandleExA
{
    struct qemu_syscall super;
    DWORD flags;
    uint64_t name, module;
};
#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI GetModuleHandleExA(DWORD flags, const char *name, HMODULE *module)
{
    struct qemu_GetModuleHandleExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEHANDLEEXA);
    call.flags = flags;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    *module = (HMODULE)call.module;
    return call.super.iret;
}

#else

void qemu_GetModuleHandleExA(struct qemu_syscall *call)
{
    struct qemu_GetModuleHandleExA *c = (struct qemu_GetModuleHandleExA *)call;
    HANDLE m;
    WINE_TRACE("\n");

    m = qemu_ops->qemu_GetModuleHandleEx(c->flags, QEMU_G2H(c->name));

    c->super.iret = !!m;
    c->module = (uint64_t)m;
}

#endif

struct qemu_ModuleOpW
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI GetModuleHandleW(const WCHAR *name)
{
    struct qemu_ModuleOpW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMODULEHANDLEW);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HMODULE)call.super.iret;
}

#else

void qemu_GetModuleHandleW(struct qemu_syscall *call)
{
    struct qemu_ModuleOpW *c = (struct qemu_ModuleOpW *)call;
    int size;

    WINE_TRACE("(\"%s\")\n", (char *)QEMU_G2H(c->name));

    c->super.iret = (uint64_t)qemu_ops->qemu_GetModuleHandleEx(
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, QEMU_G2H(c->name));

    WINE_TRACE("Returning %p\n", (void *)c->super.iret);
}

#endif

struct qemu_GetProcAddress
{
    struct qemu_syscall super;
    uint64_t module, name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FARPROC WINAPI GetProcAddress(HMODULE module, const char *name)
{
    struct qemu_GetProcAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCADDRESS);
    call.module = (uint64_t)module;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (FARPROC)call.super.iret;
}

#else

void qemu_GetProcAddress(struct qemu_syscall *call)
{
    struct qemu_GetProcAddress *c = (struct qemu_GetProcAddress *)call;
    WINE_TRACE("\n");

    c->super.iret = QEMU_H2G(qemu_ops->qemu_GetProcAddress((HMODULE)c->module,
            QEMU_G2H(c->name)));
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI LoadLibraryA(const char *name)
{
    struct qemu_ModuleOpA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADLIBRARYA);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HMODULE)call.super.iret;
}

WINBASEAPI HMODULE WINAPI LoadLibraryW(const WCHAR *name)
{
    struct qemu_ModuleOpW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADLIBRARYW);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HMODULE)call.super.iret;
}

#else

void qemu_LoadLibraryA(struct qemu_syscall *call)
{
    struct qemu_ModuleOpA *c = (struct qemu_ModuleOpA *)call;
    WCHAR *nameW = NULL;
    int size;
    WINE_TRACE("(\"%s\")\n", (char *)QEMU_G2H(c->name));

    if (c->name)
    {
        size = MultiByteToWideChar(CP_ACP, 0, QEMU_G2H(c->name), -1, NULL, 0);
        nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(*nameW));
        MultiByteToWideChar(CP_ACP, 0, QEMU_G2H(c->name), -1, nameW, size);
    }

    c->super.iret = (uint64_t)qemu_ops->qemu_LoadLibrary(nameW);

    HeapFree(GetProcessHeap(), 0, nameW);

    WINE_TRACE("Returning %p\n", (void *)c->super.iret);
}

void qemu_LoadLibraryW(struct qemu_syscall *call)
{
    struct qemu_ModuleOpW *c = (struct qemu_ModuleOpW *)call;
    int size;
    WINE_TRACE("\n");

    c->super.iret = (uint64_t)qemu_ops->qemu_LoadLibrary(QEMU_G2H(c->name));

    WINE_TRACE("Returning %p\n", (void *)c->super.iret);
}

#endif

struct qemu_FreeLibrary
{
    struct qemu_syscall super;
    uint64_t module;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI FreeLibrary(HMODULE module)
{
    struct qemu_FreeLibrary call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREELIBRARY);
    call.module = (uint64_t)module;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeLibrary(struct qemu_syscall *call)
{
    struct qemu_FreeLibrary *c = (struct qemu_FreeLibrary *)call;
    WINE_TRACE("\n");
    c->super.iret = qemu_ops->qemu_FreeLibrary((HMODULE)c->module);
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCurrentProcessId(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPROCESSID);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetCurrentProcessId(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetCurrentProcessId();
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCurrentThreadId(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCURRENTTHREADID);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetCurrentThreadId(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetCurrentThreadId();
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTickCount(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETTICKCOUNT);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetTickCount(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetTickCount();
}

#endif
