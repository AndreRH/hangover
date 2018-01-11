/*
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
#include <tlhelp32.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CreateToolhelp32Snapshot
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t process;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateToolhelp32Snapshot(DWORD flags, DWORD process)
{
    struct qemu_CreateToolhelp32Snapshot call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETOOLHELP32SNAPSHOT);
    call.flags = (ULONG_PTR)flags;
    call.process = (ULONG_PTR)process;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateToolhelp32Snapshot(struct qemu_syscall *call)
{
    struct qemu_CreateToolhelp32Snapshot *c = (struct qemu_CreateToolhelp32Snapshot *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateToolhelp32Snapshot(c->flags, c->process);
}

#endif

struct qemu_Thread32First
{
    struct qemu_syscall super;
    uint64_t hSnapShot;
    uint64_t lpte;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Thread32First(HANDLE hSnapShot, LPTHREADENTRY32 lpte)
{
    struct qemu_Thread32First call;
    call.super.id = QEMU_SYSCALL_ID(CALL_THREAD32FIRST);
    call.hSnapShot = (ULONG_PTR)hSnapShot;
    call.lpte = (ULONG_PTR)lpte;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Thread32First(struct qemu_syscall *call)
{
    struct qemu_Thread32First *c = (struct qemu_Thread32First *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Thread32First(QEMU_G2H(c->hSnapShot), QEMU_G2H(c->lpte));
}

#endif

struct qemu_Thread32Next
{
    struct qemu_syscall super;
    uint64_t hSnapShot;
    uint64_t lpte;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Thread32Next(HANDLE hSnapShot, LPTHREADENTRY32 lpte)
{
    struct qemu_Thread32Next call;
    call.super.id = QEMU_SYSCALL_ID(CALL_THREAD32NEXT);
    call.hSnapShot = (ULONG_PTR)hSnapShot;
    call.lpte = (ULONG_PTR)lpte;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Thread32Next(struct qemu_syscall *call)
{
    struct qemu_Thread32Next *c = (struct qemu_Thread32Next *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Thread32Next(QEMU_G2H(c->hSnapShot), QEMU_G2H(c->lpte));
}

#endif

struct qemu_Process32First
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lppe;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
    struct qemu_Process32First call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESS32FIRST);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lppe = (ULONG_PTR)lppe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Process32First(struct qemu_syscall *call)
{
    struct qemu_Process32First *c = (struct qemu_Process32First *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Process32First(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lppe));
}

#endif

struct qemu_Process32Next
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lppe;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
    struct qemu_Process32Next call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESS32NEXT);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lppe = (ULONG_PTR)lppe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Process32Next(struct qemu_syscall *call)
{
    struct qemu_Process32Next *c = (struct qemu_Process32Next *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Process32Next(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lppe));
}

#endif

struct qemu_Process32FirstW
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lppe;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Process32FirstW(HANDLE hSnapshot, LPPROCESSENTRY32W lppe)
{
    struct qemu_Process32FirstW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESS32FIRSTW);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lppe = (ULONG_PTR)lppe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Process32FirstW(struct qemu_syscall *call)
{
    struct qemu_Process32FirstW *c = (struct qemu_Process32FirstW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Process32FirstW(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lppe));
}

#endif

struct qemu_Process32NextW
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lppe;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Process32NextW(HANDLE hSnapshot, LPPROCESSENTRY32W lppe)
{
    struct qemu_Process32NextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESS32NEXTW);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lppe = (ULONG_PTR)lppe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Process32NextW(struct qemu_syscall *call)
{
    struct qemu_Process32NextW *c = (struct qemu_Process32NextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Process32NextW(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lppe));
}

#endif

struct qemu_Module32FirstW
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lpme;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Module32FirstW(HANDLE hSnapshot, LPMODULEENTRY32W lpme)
{
    struct qemu_Module32FirstW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODULE32FIRSTW);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lpme = (ULONG_PTR)lpme;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Module32FirstW(struct qemu_syscall *call)
{
    struct qemu_Module32FirstW *c = (struct qemu_Module32FirstW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Module32FirstW(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lpme));
}

#endif

struct qemu_Module32NextW
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lpme;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Module32NextW(HANDLE hSnapshot, LPMODULEENTRY32W lpme)
{
    struct qemu_Module32NextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODULE32NEXTW);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lpme = (ULONG_PTR)lpme;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Module32NextW(struct qemu_syscall *call)
{
    struct qemu_Module32NextW *c = (struct qemu_Module32NextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Module32NextW(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lpme));
}

#endif

struct qemu_Module32First
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lpme;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
{
    struct qemu_Module32First call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODULE32FIRST);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lpme = (ULONG_PTR)lpme;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Module32First(struct qemu_syscall *call)
{
    struct qemu_Module32First *c = (struct qemu_Module32First *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Module32First(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lpme));
}

#endif

struct qemu_Module32Next
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lpme;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
{
    struct qemu_Module32Next call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODULE32NEXT);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lpme = (ULONG_PTR)lpme;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Module32Next(struct qemu_syscall *call)
{
    struct qemu_Module32Next *c = (struct qemu_Module32Next *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Module32Next(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lpme));
}

#endif

struct qemu_Heap32ListFirst
{
    struct qemu_syscall super;
    uint64_t hSnapshot;
    uint64_t lphl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Heap32ListFirst(HANDLE hSnapshot, LPHEAPLIST32 lphl)
{
    struct qemu_Heap32ListFirst call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAP32LISTFIRST);
    call.hSnapshot = (ULONG_PTR)hSnapshot;
    call.lphl = (ULONG_PTR)lphl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Heap32ListFirst(struct qemu_syscall *call)
{
    struct qemu_Heap32ListFirst *c = (struct qemu_Heap32ListFirst *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Heap32ListFirst(QEMU_G2H(c->hSnapshot), QEMU_G2H(c->lphl));
}

#endif

struct qemu_Toolhelp32ReadProcessMemory
{
    struct qemu_syscall super;
    uint64_t pid;
    uint64_t base;
    uint64_t buf;
    uint64_t len;
    uint64_t r;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Toolhelp32ReadProcessMemory(DWORD pid, const void* base, void* buf, SIZE_T len, SIZE_T* r)
{
    struct qemu_Toolhelp32ReadProcessMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOOLHELP32READPROCESSMEMORY);
    call.pid = (ULONG_PTR)pid;
    call.base = (ULONG_PTR)base;
    call.buf = (ULONG_PTR)buf;
    call.len = (ULONG_PTR)len;
    call.r = (ULONG_PTR)r;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Toolhelp32ReadProcessMemory(struct qemu_syscall *call)
{
    struct qemu_Toolhelp32ReadProcessMemory *c = (struct qemu_Toolhelp32ReadProcessMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Toolhelp32ReadProcessMemory(c->pid, QEMU_G2H(c->base), QEMU_G2H(c->buf), c->len, QEMU_G2H(c->r));
}

#endif

