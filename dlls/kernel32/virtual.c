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
#include <psapi.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_VirtualAlloc
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t size;
    uint64_t type;
    uint64_t protect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI VirtualAlloc(void *addr, SIZE_T size, DWORD type, DWORD protect)
{
    struct qemu_VirtualAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALALLOC);
    call.addr = (ULONG_PTR)addr;
    call.size = size;
    call.type = type;
    call.protect = protect;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_VirtualAlloc(struct qemu_syscall *call)
{
    struct qemu_VirtualAlloc *c = (struct qemu_VirtualAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)VirtualAlloc(QEMU_G2H(c->addr), c->size, c->type, c->protect);
}

#endif

struct qemu_VirtualAllocEx
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t addr;
    uint64_t size;
    uint64_t type;
    uint64_t protect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI VirtualAllocEx(HANDLE hProcess, LPVOID addr, SIZE_T size, DWORD type, DWORD protect)
{
    struct qemu_VirtualAllocEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALALLOCEX);
    call.hProcess = guest_HANDLE_g2h(hProcess);
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;
    call.type = (ULONG_PTR)type;
    call.protect = (ULONG_PTR)protect;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_VirtualAllocEx(struct qemu_syscall *call)
{
    struct qemu_VirtualAllocEx *c = (struct qemu_VirtualAllocEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)VirtualAllocEx(QEMU_G2H(c->hProcess), QEMU_G2H(c->addr), c->size, c->type, c->protect);
}

#endif

struct qemu_VirtualFree
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t size;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualFree(LPVOID addr, SIZE_T size, DWORD type)
{
    struct qemu_VirtualFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALFREE);
    call.addr = (ULONG_PTR)addr;
    call.size = size;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualFree(struct qemu_syscall *call)
{
    struct qemu_VirtualFree *c = (struct qemu_VirtualFree *)call;
    WINE_TRACE("\n");
    c->super.iret = VirtualFree(QEMU_G2H(c->addr), c->size, c->type);
}

#endif

struct qemu_VirtualFreeEx
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t size;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualFreeEx(HANDLE process, LPVOID addr, SIZE_T size, DWORD type)
{
    struct qemu_VirtualFreeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALFREEEX);
    call.process = guest_HANDLE_g2h(process);
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualFreeEx(struct qemu_syscall *call)
{
    struct qemu_VirtualFreeEx *c = (struct qemu_VirtualFreeEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VirtualFreeEx(QEMU_G2H(c->process), QEMU_G2H(c->addr), c->size, c->type);
}

#endif

struct qemu_VirtualLock
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualLock(LPVOID addr, SIZE_T size)
{
    struct qemu_VirtualLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALLOCK);
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualLock(struct qemu_syscall *call)
{
    struct qemu_VirtualLock *c = (struct qemu_VirtualLock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VirtualLock(QEMU_G2H(c->addr), c->size);
}

#endif

struct qemu_VirtualUnlock
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualUnlock(LPVOID addr, SIZE_T size)
{
    struct qemu_VirtualUnlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALUNLOCK);
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualUnlock(struct qemu_syscall *call)
{
    struct qemu_VirtualUnlock *c = (struct qemu_VirtualUnlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VirtualUnlock(QEMU_G2H(c->addr), c->size);
}

#endif

struct qemu_VirtualProtect
{
    struct qemu_syscall super;
    uint64_t address;
    uint64_t size;
    uint64_t new_protect;
    uint64_t old_protect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualProtect(void *address, SIZE_T size, DWORD new_protect, DWORD *old_protect)
{
    struct qemu_VirtualProtect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALPROTECT);
    call.address = (ULONG_PTR)address;
    call.size = size;
    call.new_protect = new_protect;
    call.old_protect = (ULONG_PTR)old_protect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualProtect(struct qemu_syscall *call)
{
    struct qemu_VirtualProtect *c = (struct qemu_VirtualProtect *)call;
    WINE_TRACE("\n");
    c->super.iret = VirtualProtect(QEMU_G2H(c->address), c->size, c->new_protect,
            QEMU_G2H(c->old_protect));
}

#endif

struct qemu_VirtualProtectEx
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t size;
    uint64_t new_prot;
    uint64_t old_prot;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VirtualProtectEx(HANDLE process, LPVOID addr, SIZE_T size, DWORD new_prot, LPDWORD old_prot)
{
    struct qemu_VirtualProtectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALPROTECTEX);
    call.process = guest_HANDLE_g2h(process);
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;
    call.new_prot = (ULONG_PTR)new_prot;
    call.old_prot = (ULONG_PTR)old_prot;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualProtectEx(struct qemu_syscall *call)
{
    struct qemu_VirtualProtectEx *c = (struct qemu_VirtualProtectEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VirtualProtectEx(QEMU_G2H(c->process), QEMU_G2H(c->addr), c->size, c->new_prot, QEMU_G2H(c->old_prot));
}

#endif

struct qemu_VirtualQuery
{
    struct qemu_syscall super;
    uint64_t address;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI VirtualQuery(const void *address,
        MEMORY_BASIC_INFORMATION *info, SIZE_T size)
{
    struct qemu_VirtualQuery call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALQUERY);
    call.address = (ULONG_PTR)address;
    call.info = (ULONG_PTR)info;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualQuery(struct qemu_syscall *call)
{
    struct qemu_VirtualQuery *c = (struct qemu_VirtualQuery *)call;
    MEMORY_BASIC_INFORMATION stack, *info = &stack;
    HMODULE mod;
    void *address;
    WINE_TRACE("\n");

    address = QEMU_G2H(c->address);
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->info);
#endif

    c->super.iret = VirtualQuery(address, info, c->size);

    if (qemu_ops->qemu_FindEntryForAddress(address, &mod))
        info->Type = MEM_IMAGE;

#if GUEST_BIT != HOST_BIT
    MEMORY_BASIC_INFORMATION_h2g(info, QEMU_G2H(c->info));
    if (c->super.iret == sizeof(info))
        c->super.iret = sizeof(struct qemu_MEMORY_BASIC_INFORMATION);
#endif
}

#endif

struct qemu_VirtualQueryEx
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t info;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI VirtualQueryEx(HANDLE process, LPCVOID addr, PMEMORY_BASIC_INFORMATION info, SIZE_T len)
{
    struct qemu_VirtualQueryEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VIRTUALQUERYEX);
    call.process = guest_HANDLE_g2h(process);
    call.addr = (ULONG_PTR)addr;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VirtualQueryEx(struct qemu_syscall *call)
{
    struct qemu_VirtualQueryEx *c = (struct qemu_VirtualQueryEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VirtualQueryEx(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->info), c->len);
}

#endif

struct qemu_CreateFileMappingA
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t sa;
    uint64_t protect;
    uint64_t size_high;
    uint64_t size_low;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFileMappingA(HANDLE hFile, SECURITY_ATTRIBUTES *sa, DWORD protect, DWORD size_high, DWORD size_low, LPCSTR name)
{
    struct qemu_CreateFileMappingA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILEMAPPINGA);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.sa = (ULONG_PTR)sa;
    call.protect = (ULONG_PTR)protect;
    call.size_high = (ULONG_PTR)size_high;
    call.size_low = (ULONG_PTR)size_low;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFileMappingA(struct qemu_syscall *call)
{
    struct qemu_CreateFileMappingA *c = (struct qemu_CreateFileMappingA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

    if (c->protect & SEC_IMAGE)
        WINE_FIXME("SEC_IMAGE mappings will be rejected by Wine.\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateFileMappingA(QEMU_G2H(c->hFile), sa, c->protect, c->size_high, c->size_low, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateFileMappingW
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t sa;
    uint64_t protect;
    uint64_t size_high;
    uint64_t size_low;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFileMappingW(HANDLE hFile, LPSECURITY_ATTRIBUTES sa, DWORD protect, DWORD size_high, DWORD size_low, LPCWSTR name)
{
    struct qemu_CreateFileMappingW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILEMAPPINGW);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.sa = (ULONG_PTR)sa;
    call.protect = (ULONG_PTR)protect;
    call.size_high = (ULONG_PTR)size_high;
    call.size_low = (ULONG_PTR)size_low;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFileMappingW(struct qemu_syscall *call)
{
    struct qemu_CreateFileMappingW *c = (struct qemu_CreateFileMappingW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

    if (c->protect & SEC_IMAGE)
        WINE_FIXME("SEC_IMAGE mappings will be rejected by Wine.\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateFileMappingW(QEMU_G2H(c->hFile), sa, c->protect, c->size_high, c->size_low, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenFileMappingA
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenFileMappingA(DWORD access, BOOL inherit, LPCSTR name)
{
    struct qemu_OpenFileMappingA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENFILEMAPPINGA);
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenFileMappingA(struct qemu_syscall *call)
{
    struct qemu_OpenFileMappingA *c = (struct qemu_OpenFileMappingA *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenFileMappingA(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenFileMappingW
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenFileMappingW(DWORD access, BOOL inherit, LPCWSTR name)
{
    struct qemu_OpenFileMappingW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENFILEMAPPINGW);
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenFileMappingW(struct qemu_syscall *call)
{
    struct qemu_OpenFileMappingW *c = (struct qemu_OpenFileMappingW *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenFileMappingW(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_MapViewOfFile
{
    struct qemu_syscall super;
    uint64_t mapping;
    uint64_t access;
    uint64_t offset_high;
    uint64_t offset_low;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI MapViewOfFile(HANDLE mapping, DWORD access, DWORD offset_high, DWORD offset_low, SIZE_T count)
{
    struct qemu_MapViewOfFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPVIEWOFFILE);
    call.mapping = guest_HANDLE_g2h(mapping);
    call.access = (ULONG_PTR)access;
    call.offset_high = (ULONG_PTR)offset_high;
    call.offset_low = (ULONG_PTR)offset_low;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_MapViewOfFile(struct qemu_syscall *call)
{
    struct qemu_MapViewOfFile *c = (struct qemu_MapViewOfFile *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)MapViewOfFile(QEMU_G2H(c->mapping), c->access, c->offset_high, c->offset_low, c->count);
}

#endif

struct qemu_MapViewOfFileEx
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t offset_high;
    uint64_t offset_low;
    uint64_t count;
    uint64_t addr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI MapViewOfFileEx(HANDLE handle, DWORD access, DWORD offset_high, DWORD offset_low, SIZE_T count, LPVOID addr)
{
    struct qemu_MapViewOfFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPVIEWOFFILEEX);
    call.handle = guest_HANDLE_g2h(handle);
    call.access = access;
    call.offset_high = offset_high;
    call.offset_low = offset_low;
    call.count = count;
    call.addr = (ULONG_PTR)addr;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_MapViewOfFileEx(struct qemu_syscall *call)
{
    struct qemu_MapViewOfFileEx *c = (struct qemu_MapViewOfFileEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)MapViewOfFileEx((HANDLE)c->handle, c->access, c->offset_high, c->offset_low, c->count, QEMU_G2H(c->addr));
}

#endif

struct qemu_UnmapViewOfFile
{
    struct qemu_syscall super;
    uint64_t addr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnmapViewOfFile(LPCVOID addr)
{
    struct qemu_UnmapViewOfFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNMAPVIEWOFFILE);
    call.addr = (ULONG_PTR)addr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnmapViewOfFile(struct qemu_syscall *call)
{
    struct qemu_UnmapViewOfFile *c = (struct qemu_UnmapViewOfFile *)call;
    WINE_TRACE("\n");
    c->super.iret = UnmapViewOfFile(QEMU_G2H(c->addr));
}

#endif

struct qemu_FlushViewOfFile
{
    struct qemu_syscall super;
    uint64_t base;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlushViewOfFile(LPCVOID base, SIZE_T size)
{
    struct qemu_FlushViewOfFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHVIEWOFFILE);
    call.base = (ULONG_PTR)base;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushViewOfFile(struct qemu_syscall *call)
{
    struct qemu_FlushViewOfFile *c = (struct qemu_FlushViewOfFile *)call;
    WINE_TRACE("\n");
    c->super.iret = FlushViewOfFile(QEMU_G2H(c->base), c->size);
}

#endif

struct qemu_GetWriteWatch
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t base;
    uint64_t size;
    uint64_t addresses;
    uint64_t count;
    uint64_t granularity;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetWriteWatch(DWORD flags, LPVOID base, SIZE_T size, LPVOID *addresses, ULONG_PTR *count, ULONG *granularity)
{
    struct qemu_GetWriteWatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWRITEWATCH);
    call.flags = (ULONG_PTR)flags;
    call.base = (ULONG_PTR)base;
    call.size = (ULONG_PTR)size;
    call.addresses = (ULONG_PTR)addresses;
    call.count = (ULONG_PTR)count;
    call.granularity = (ULONG_PTR)granularity;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWriteWatch(struct qemu_syscall *call)
{
    struct qemu_GetWriteWatch *c = (struct qemu_GetWriteWatch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWriteWatch(c->flags, QEMU_G2H(c->base), c->size, QEMU_G2H(c->addresses), QEMU_G2H(c->count), QEMU_G2H(c->granularity));
}

#endif

struct qemu_ResetWriteWatch
{
    struct qemu_syscall super;
    uint64_t base;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ResetWriteWatch(LPVOID base, SIZE_T size)
{
    struct qemu_ResetWriteWatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESETWRITEWATCH);
    call.base = (ULONG_PTR)base;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResetWriteWatch(struct qemu_syscall *call)
{
    struct qemu_ResetWriteWatch *c = (struct qemu_ResetWriteWatch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ResetWriteWatch(QEMU_G2H(c->base), c->size);
}

#endif

struct qemu_IsBadReadPtr
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadReadPtr(LPCVOID ptr, UINT_PTR size)
{
    struct qemu_IsBadReadPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADREADPTR);
    call.ptr = (ULONG_PTR)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadReadPtr(struct qemu_syscall *call)
{
    struct qemu_IsBadReadPtr *c = (struct qemu_IsBadReadPtr *)call;
    WINE_TRACE("\n");
    c->super.iret = IsBadReadPtr(QEMU_G2H(c->ptr), c->size);
}

#endif

struct qemu_IsBadWritePtr
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadWritePtr(LPVOID ptr, UINT_PTR size)
{
    struct qemu_IsBadWritePtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADWRITEPTR);
    call.ptr = (ULONG_PTR)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadWritePtr(struct qemu_syscall *call)
{
    struct qemu_IsBadWritePtr *c = (struct qemu_IsBadWritePtr *)call;
    WINE_TRACE("\n");
    c->super.iret = IsBadWritePtr(QEMU_G2H(c->ptr), c->size);
}

#endif

struct qemu_IsBadHugeReadPtr
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadHugeReadPtr(LPCVOID ptr, UINT_PTR size)
{
    struct qemu_IsBadHugeReadPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADHUGEREADPTR);
    call.ptr = (ULONG_PTR)ptr;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadHugeReadPtr(struct qemu_syscall *call)
{
    struct qemu_IsBadHugeReadPtr *c = (struct qemu_IsBadHugeReadPtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsBadHugeReadPtr(QEMU_G2H(c->ptr), c->size);
}

#endif

struct qemu_IsBadHugeWritePtr
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadHugeWritePtr(LPVOID ptr, UINT_PTR size)
{
    struct qemu_IsBadHugeWritePtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADHUGEWRITEPTR);
    call.ptr = (ULONG_PTR)ptr;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadHugeWritePtr(struct qemu_syscall *call)
{
    struct qemu_IsBadHugeWritePtr *c = (struct qemu_IsBadHugeWritePtr *)call;
    WINE_TRACE("\n");
    c->super.iret = IsBadHugeWritePtr(QEMU_G2H(c->ptr), c->size);
}

#endif

struct qemu_IsBadCodePtr
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadCodePtr(FARPROC ptr)
{
    struct qemu_IsBadCodePtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADCODEPTR);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadCodePtr(struct qemu_syscall *call)
{
    struct qemu_IsBadCodePtr *c = (struct qemu_IsBadCodePtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsBadCodePtr(QEMU_G2H(c->ptr));
}

#endif

struct qemu_IsBadStringPtrA
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadStringPtrA(LPCSTR str, UINT_PTR max)
{
    struct qemu_IsBadStringPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADSTRINGPTRA);
    call.str = (ULONG_PTR)str;
    call.max = (ULONG_PTR)max;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadStringPtrA(struct qemu_syscall *call)
{
    struct qemu_IsBadStringPtrA *c = (struct qemu_IsBadStringPtrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsBadStringPtrA(QEMU_G2H(c->str), c->max);
}

#endif

struct qemu_IsBadStringPtrW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsBadStringPtrW(LPCWSTR str, UINT_PTR max)
{
    struct qemu_IsBadStringPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBADSTRINGPTRW);
    call.str = (ULONG_PTR)str;
    call.max = (ULONG_PTR)max;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsBadStringPtrW(struct qemu_syscall *call)
{
    struct qemu_IsBadStringPtrW *c = (struct qemu_IsBadStringPtrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsBadStringPtrW(QEMU_G2H(c->str), c->max);
}

#endif

struct qemu_K32GetMappedFileNameA
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t lpv;
    uint64_t file_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetMappedFileNameA(HANDLE process, LPVOID lpv, LPSTR file_name, DWORD size)
{
    struct qemu_K32GetMappedFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMAPPEDFILENAMEA);
    call.process = guest_HANDLE_g2h(process);
    call.lpv = (ULONG_PTR)lpv;
    call.file_name = (ULONG_PTR)file_name;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetMappedFileNameA(struct qemu_syscall *call)
{
    struct qemu_K32GetMappedFileNameA *c = (struct qemu_K32GetMappedFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetMappedFileNameA(QEMU_G2H(c->process), QEMU_G2H(c->lpv), QEMU_G2H(c->file_name), c->size);
}

#endif

struct qemu_K32GetMappedFileNameW
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t lpv;
    uint64_t file_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetMappedFileNameW(HANDLE process, LPVOID lpv, LPWSTR file_name, DWORD size)
{
    struct qemu_K32GetMappedFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMAPPEDFILENAMEW);
    call.process = guest_HANDLE_g2h(process);
    call.lpv = (ULONG_PTR)lpv;
    call.file_name = (ULONG_PTR)file_name;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetMappedFileNameW(struct qemu_syscall *call)
{
    struct qemu_K32GetMappedFileNameW *c = (struct qemu_K32GetMappedFileNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetMappedFileNameW(QEMU_G2H(c->process), QEMU_G2H(c->lpv), QEMU_G2H(c->file_name), c->size);
}

#endif

struct qemu_K32EnumPageFilesA
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EnumPageFilesA(PENUM_PAGE_FILE_CALLBACKA callback, LPVOID context)
{
    struct qemu_K32EnumPageFilesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32ENUMPAGEFILESA);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32EnumPageFilesA(struct qemu_syscall *call)
{
    struct qemu_K32EnumPageFilesA *c = (struct qemu_K32EnumPageFilesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EnumPageFilesA(QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_K32EnumPageFilesW
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EnumPageFilesW(PENUM_PAGE_FILE_CALLBACKW callback, LPVOID context)
{
    struct qemu_K32EnumPageFilesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32ENUMPAGEFILESW);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32EnumPageFilesW(struct qemu_syscall *call)
{
    struct qemu_K32EnumPageFilesW *c = (struct qemu_K32EnumPageFilesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EnumPageFilesW(QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_K32GetWsChanges
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t watchinfo;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32GetWsChanges(HANDLE process, PPSAPI_WS_WATCH_INFORMATION watchinfo, DWORD size)
{
    struct qemu_K32GetWsChanges call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETWSCHANGES);
    call.process = guest_HANDLE_g2h(process);
    call.watchinfo = (ULONG_PTR)watchinfo;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetWsChanges(struct qemu_syscall *call)
{
    struct qemu_K32GetWsChanges *c = (struct qemu_K32GetWsChanges *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetWsChanges(QEMU_G2H(c->process), QEMU_G2H(c->watchinfo), c->size);
}

#endif

struct qemu_K32InitializeProcessForWsWatch
{
    struct qemu_syscall super;
    uint64_t process;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32InitializeProcessForWsWatch(HANDLE process)
{
    struct qemu_K32InitializeProcessForWsWatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32INITIALIZEPROCESSFORWSWATCH);
    call.process = guest_HANDLE_g2h(process);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32InitializeProcessForWsWatch(struct qemu_syscall *call)
{
    struct qemu_K32InitializeProcessForWsWatch *c = (struct qemu_K32InitializeProcessForWsWatch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32InitializeProcessForWsWatch(QEMU_G2H(c->process));
}

#endif

