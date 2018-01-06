/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
 * Copyright 2017 André Hentschel
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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_GetEnvironmentStringsW
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI GetEnvironmentStringsW(void)
{
    struct qemu_GetEnvironmentStringsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENVIRONMENTSTRINGSW);

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetEnvironmentStringsW(struct qemu_syscall *call)
{
    struct qemu_GetEnvironmentStringsW *c = (struct qemu_GetEnvironmentStringsW *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(GetEnvironmentStringsW());
}

#endif

struct qemu_FreeEnvironmentStringsA
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeEnvironmentStringsA(LPSTR ptr)
{
    struct qemu_FreeEnvironmentStringsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEENVIRONMENTSTRINGSA);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeEnvironmentStringsA(struct qemu_syscall *call)
{
    struct qemu_FreeEnvironmentStringsA *c = (struct qemu_FreeEnvironmentStringsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeEnvironmentStringsA(QEMU_G2H(c->ptr));
}

#endif

struct qemu_FreeEnvironmentStringsW
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeEnvironmentStringsW(LPWSTR ptr)
{
    struct qemu_FreeEnvironmentStringsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEENVIRONMENTSTRINGSW);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeEnvironmentStringsW(struct qemu_syscall *call)
{
    struct qemu_FreeEnvironmentStringsW *c = (struct qemu_FreeEnvironmentStringsW *)call;
    WINE_TRACE("\n");
    c->super.iret = FreeEnvironmentStringsW(QEMU_G2H(c->ptr));
}

#endif

struct qemu_GetEnvironmentVariableA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t value;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetEnvironmentVariableA(LPCSTR name, LPSTR value, DWORD size)
{
    struct qemu_GetEnvironmentVariableA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENVIRONMENTVARIABLEA);
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnvironmentVariableA(struct qemu_syscall *call)
{
    struct qemu_GetEnvironmentVariableA *c = (struct qemu_GetEnvironmentVariableA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetEnvironmentVariableA(QEMU_G2H(c->name), QEMU_G2H(c->value), c->size);
}

#endif

struct qemu_GetEnvironmentVariableW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t val;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetEnvironmentVariableW(LPCWSTR name, LPWSTR val, DWORD size)
{
    struct qemu_GetEnvironmentVariableW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENVIRONMENTVARIABLEW);
    call.name = (ULONG_PTR)name;
    call.val = (ULONG_PTR)val;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEnvironmentVariableW(struct qemu_syscall *call)
{
    struct qemu_GetEnvironmentVariableW *c = (struct qemu_GetEnvironmentVariableW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetEnvironmentVariableW(QEMU_G2H(c->name), QEMU_G2H(c->val), c->size);
}

#endif

struct qemu_SetEnvironmentVariableA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetEnvironmentVariableA(LPCSTR name, LPCSTR value)
{
    struct qemu_SetEnvironmentVariableA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENVIRONMENTVARIABLEA);
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEnvironmentVariableA(struct qemu_syscall *call)
{
    struct qemu_SetEnvironmentVariableA *c = (struct qemu_SetEnvironmentVariableA *)call;
    WINE_TRACE("\n");
    c->super.iret = SetEnvironmentVariableA(QEMU_G2H(c->name), QEMU_G2H(c->value));
}

#endif

struct qemu_SetEnvironmentVariableW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetEnvironmentVariableW(LPCWSTR name, LPCWSTR value)
{
    struct qemu_SetEnvironmentVariableW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENVIRONMENTVARIABLEW);
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEnvironmentVariableW(struct qemu_syscall *call)
{
    struct qemu_SetEnvironmentVariableW *c = (struct qemu_SetEnvironmentVariableW *)call;
    WINE_TRACE("\n");
    c->super.iret = SetEnvironmentVariableW(QEMU_G2H(c->name), QEMU_G2H(c->value));
}

#endif

struct qemu_ExpandEnvironmentStringsA
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dst;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ExpandEnvironmentStringsA(LPCSTR src, LPSTR dst, DWORD count)
{
    struct qemu_ExpandEnvironmentStringsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPANDENVIRONMENTSTRINGSA);
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExpandEnvironmentStringsA(struct qemu_syscall *call)
{
    struct qemu_ExpandEnvironmentStringsA *c = (struct qemu_ExpandEnvironmentStringsA *)call;
    WINE_TRACE("\n");
    c->super.iret = ExpandEnvironmentStringsA(QEMU_G2H(c->src), QEMU_G2H(c->dst), c->count);
}

#endif

struct qemu_ExpandEnvironmentStringsW
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dst;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ExpandEnvironmentStringsW(LPCWSTR src, LPWSTR dst, DWORD len)
{
    struct qemu_ExpandEnvironmentStringsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPANDENVIRONMENTSTRINGSW);
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExpandEnvironmentStringsW(struct qemu_syscall *call)
{
    struct qemu_ExpandEnvironmentStringsW *c = (struct qemu_ExpandEnvironmentStringsW *)call;
    WINE_TRACE("\n");
    c->super.iret = ExpandEnvironmentStringsW(QEMU_G2H(c->src), QEMU_G2H(c->dst), c->len);
}

#endif

struct qemu_GetStdHandle
{
    struct qemu_syscall super;
    uint64_t std_handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetStdHandle(DWORD std_handle)
{
    struct qemu_GetStdHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTDHANDLE);
    call.std_handle = std_handle;
    qemu_syscall(&call.super);
    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetStdHandle(struct qemu_syscall *call)
{
    struct qemu_GetStdHandle *c = (struct qemu_GetStdHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(GetStdHandle(c->std_handle));
}

#endif

struct qemu_SetStdHandle
{
    struct qemu_syscall super;
    uint64_t std_handle;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetStdHandle(DWORD std_handle, HANDLE handle)
{
    struct qemu_SetStdHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSTDHANDLE);
    call.std_handle = std_handle;
    call.handle = (LONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetStdHandle(struct qemu_syscall *call)
{
    struct qemu_SetStdHandle *c = (struct qemu_SetStdHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetStdHandle(c->std_handle, QEMU_G2H(c->handle));
}

#endif

struct qemu_GetStartupInfo
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI GetStartupInfoA(STARTUPINFOA *info)
{
    struct qemu_GetStartupInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTARTUPINFOA);
    call.info = (ULONG_PTR)info;
    qemu_syscall(&call.super);
}

#else

static WCHAR *titleW;
static char *titleA;

static void init_titleW()
{
    RTL_USER_PROCESS_PARAMETERS *rupp;
    rupp = ((struct _TEB *)qemu_ops->qemu_getTEB())->Peb->ProcessParameters;
    titleW = rupp->WindowTitle.Buffer;
}

static void init_titleA()
{
    unsigned int len;
    if (!titleW)
        init_titleW();

    /* FIXME: This is not thread safe, may allocate twice. */
    len = WideCharToMultiByte(CP_ACP, 0, titleW, -1, NULL, 0, NULL, NULL);
    titleA = HeapAlloc(GetProcessHeap(), 0, len);
    WideCharToMultiByte(CP_ACP, 0, titleW, -1, titleA, len, NULL, NULL);
}

void qemu_GetStartupInfoA(struct qemu_syscall *call)
{
    struct qemu_GetStartupInfo *c = (struct qemu_GetStartupInfo *)call;
    STARTUPINFOA a;

    WINE_TRACE("\n");
    GetStartupInfoA(&a);
    a.cb = sizeof(a);

    if (!titleA)
        init_titleA();

    a.lpTitle = titleA;
#if HOST_BIT==GUEST_BIT
    *((STARTUPINFOA *)QEMU_G2H(c->info)) = a;
#else
    STARTUPINFO_h2g(QEMU_G2H(c->info), (STARTUPINFOW *)&a);
#endif
}

#endif

struct qemu_GetStartupInfoW
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI GetStartupInfoW(STARTUPINFOW *info)
{
    struct qemu_GetStartupInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTARTUPINFOW);
    call.info = (ULONG_PTR)info;
    qemu_syscall(&call.super);
}

#else

void qemu_GetStartupInfoW(struct qemu_syscall *call)
{
    struct qemu_GetStartupInfoW *c = (struct qemu_GetStartupInfoW *)call;
    STARTUPINFOW w;
    w.cb = sizeof(w);

    WINE_TRACE("\n");
    GetStartupInfoW(&w);

    if (!titleW)
        init_titleW();

    w.lpTitle = titleW;

#if HOST_BIT==GUEST_BIT
    *((STARTUPINFOW *)QEMU_G2H(c->info)) = w;
#else
    STARTUPINFO_h2g(QEMU_G2H(c->info), &w);
#endif
}

#endif

struct qemu_GetFirmwareEnvironmentVariableA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t guid;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFirmwareEnvironmentVariableA(LPCSTR name, LPCSTR guid, PVOID buffer, DWORD size)
{
    struct qemu_GetFirmwareEnvironmentVariableA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFIRMWAREENVIRONMENTVARIABLEA);
    call.name = (ULONG_PTR)name;
    call.guid = (ULONG_PTR)guid;
    call.buffer = (ULONG_PTR)buffer;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFirmwareEnvironmentVariableA to Wine headers? */
extern DWORD WINAPI GetFirmwareEnvironmentVariableA(LPCSTR name, LPCSTR guid, PVOID buffer, DWORD size);
void qemu_GetFirmwareEnvironmentVariableA(struct qemu_syscall *call)
{
    struct qemu_GetFirmwareEnvironmentVariableA *c = (struct qemu_GetFirmwareEnvironmentVariableA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFirmwareEnvironmentVariableA(QEMU_G2H(c->name), QEMU_G2H(c->guid), QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_GetFirmwareEnvironmentVariableW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t guid;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFirmwareEnvironmentVariableW(LPCWSTR name, LPCWSTR guid, PVOID buffer, DWORD size)
{
    struct qemu_GetFirmwareEnvironmentVariableW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFIRMWAREENVIRONMENTVARIABLEW);
    call.name = (ULONG_PTR)name;
    call.guid = (ULONG_PTR)guid;
    call.buffer = (ULONG_PTR)buffer;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFirmwareEnvironmentVariableW to Wine headers? */
extern DWORD WINAPI GetFirmwareEnvironmentVariableW(LPCWSTR name, LPCWSTR guid, PVOID buffer, DWORD size);
void qemu_GetFirmwareEnvironmentVariableW(struct qemu_syscall *call)
{
    struct qemu_GetFirmwareEnvironmentVariableW *c = (struct qemu_GetFirmwareEnvironmentVariableW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFirmwareEnvironmentVariableW(QEMU_G2H(c->name), QEMU_G2H(c->guid), QEMU_G2H(c->buffer), c->size);
}

#endif

