/*
 * Copyright 2017 Stefan Dösinger
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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "thunk/qemu_winternl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */
typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA
{
    ULONG Flags;
    const UNICODE_STRING *FullDllName;
    const UNICODE_STRING *BaseDllName;
    void *DllBase;
    ULONG SizeOfImage;
} LDR_DLL_LOADED_NOTIFICATION_DATA, *PLDR_DLL_LOADED_NOTIFICATION_DATA;

typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA
{
    ULONG Flags;
    const UNICODE_STRING *FullDllName;
    const UNICODE_STRING *BaseDllName;
    void *DllBase;
    ULONG SizeOfImage;
} LDR_DLL_UNLOADED_NOTIFICATION_DATA, *PLDR_DLL_UNLOADED_NOTIFICATION_DATA;

typedef union _LDR_DLL_NOTIFICATION_DATA
{
    LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
    LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
} LDR_DLL_NOTIFICATION_DATA, *PLDR_DLL_NOTIFICATION_DATA;

typedef void (CALLBACK *PLDR_DLL_NOTIFICATION_FUNCTION)(ULONG, LDR_DLL_NOTIFICATION_DATA*, void*);

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>
#include <delayloadhandler.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_LdrFindEntryForAddress
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t mod;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_LdrFindEntryForAddress(const void *addr, LDR_DATA_TABLE_ENTRY **mod)
{
    /* FIXME: With proper data in the PEB we should be able to do this on the
     * client side.
     *
     * FIXME 2: HMODULE != LDR_DATA_TABLE_ENTRY, but for now it is good enough for our little
     * PE loader. */
    struct qemu_LdrFindEntryForAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRFINDENTRYFORADDRESS);
    call.addr = (ULONG_PTR)addr;
    call.mod = (ULONG_PTR)mod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrFindEntryForAddress(struct qemu_syscall *call)
{
    struct qemu_LdrFindEntryForAddress *c = (struct qemu_LdrFindEntryForAddress *)call;
    HMODULE mod;
    WINE_TRACE("\n");

    if (qemu_ops->qemu_FindEntryForAddress(QEMU_G2H(c->addr), &mod))
        c->super.iret = STATUS_SUCCESS;
    else
        c->super.iret = STATUS_NO_MORE_ENTRIES;

    *(uint64_t *)QEMU_G2H(c->mod) = (ULONG_PTR)mod;
}

#endif

#ifdef QEMU_DLL_GUEST

/* Copypasted from Wine with exception handling removed for now. */
PIMAGE_NT_HEADERS WINAPI ntdll_RtlImageNtHeader(HMODULE hModule)
{
    IMAGE_NT_HEADERS *ret;

    IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)hModule;

    ret = NULL;
    if (dos->e_magic == IMAGE_DOS_SIGNATURE)
    {
        ret = (IMAGE_NT_HEADERS *)((char *)dos + dos->e_lfanew);
        if (ret->Signature != IMAGE_NT_SIGNATURE) ret = NULL;
    }
    return ret;
}

/* Copypasted from Wine. */
PIMAGE_SECTION_HEADER WINAPI ntdll_RtlImageRvaToSection( const IMAGE_NT_HEADERS *nt,
                                                   HMODULE module, DWORD rva )
{
    int i;
    const IMAGE_SECTION_HEADER *sec;

    sec = (const IMAGE_SECTION_HEADER*)((const char*)&nt->OptionalHeader +
                                        nt->FileHeader.SizeOfOptionalHeader);
    for (i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++)
    {
        if ((sec->VirtualAddress <= rva) && (sec->VirtualAddress + sec->SizeOfRawData > rva))
            return (PIMAGE_SECTION_HEADER)sec;
    }
    return NULL;
}

/* Copypasted from Wine. */
PVOID WINAPI ntdll_RtlImageRvaToVa( const IMAGE_NT_HEADERS *nt, HMODULE module,
                              DWORD rva, IMAGE_SECTION_HEADER **section )
{
    IMAGE_SECTION_HEADER *sec;

    if (section && *section)  /* try this section first */
    {
        sec = *section;
        if ((sec->VirtualAddress <= rva) && (sec->VirtualAddress + sec->SizeOfRawData > rva))
            goto found;
    }
    if (!(sec = ntdll_RtlImageRvaToSection( nt, module, rva ))) return NULL;
 found:
    if (section) *section = sec;
    return (char *)module + sec->PointerToRawData + (rva - sec->VirtualAddress);
}

/* Copypasted from Wine. */
PVOID WINAPI ntdll_RtlImageDirectoryEntryToData( HMODULE module, BOOL image, WORD dir, ULONG *size )
{
    const IMAGE_NT_HEADERS *nt;
    DWORD addr;

    if ((ULONG_PTR)module & 1)  /* mapped as data file */
    {
        module = (HMODULE)((ULONG_PTR)module & ~1);
        image = FALSE;
    }
    if (!(nt = ntdll_RtlImageNtHeader( module ))) return NULL;
    if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        const IMAGE_NT_HEADERS64 *nt64 = (const IMAGE_NT_HEADERS64 *)nt;

        if (dir >= nt64->OptionalHeader.NumberOfRvaAndSizes) return NULL;
        if (!(addr = nt64->OptionalHeader.DataDirectory[dir].VirtualAddress)) return NULL;
        *size = nt64->OptionalHeader.DataDirectory[dir].Size;
        if (image || addr < nt64->OptionalHeader.SizeOfHeaders) return (char *)module + addr;
    }
    else if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
    {
        const IMAGE_NT_HEADERS32 *nt32 = (const IMAGE_NT_HEADERS32 *)nt;

        if (dir >= nt32->OptionalHeader.NumberOfRvaAndSizes) return NULL;
        if (!(addr = nt32->OptionalHeader.DataDirectory[dir].VirtualAddress)) return NULL;
        *size = nt32->OptionalHeader.DataDirectory[dir].Size;
        if (image || addr < nt32->OptionalHeader.SizeOfHeaders) return (char *)module + addr;
    }
    else return NULL;

    /* not mapped as image, need to find the section containing the virtual address */
    return ntdll_RtlImageRvaToVa( nt, module, addr, NULL );
}

#endif

struct qemu_RtlPcToFileHeader
{
    struct qemu_syscall super;
    uint64_t pc;
    uint64_t address;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI RtlPcToFileHeader(void *pc, void **address)
{
    struct qemu_RtlPcToFileHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLPCTOFILEHEADER);
    call.pc = (ULONG_PTR)pc;
    call.address = (ULONG_PTR)address;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlPcToFileHeader(struct qemu_syscall *call)
{
    struct qemu_RtlPcToFileHeader *c = (struct qemu_RtlPcToFileHeader *)call;
    void *ret = NULL;

    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(qemu_ops->qemu_RtlPcToFileHeader(QEMU_G2H(c->pc), c->address ? &ret : NULL));
    if (c->address)
        *(uint64_t *)QEMU_G2H(c->address) = QEMU_H2G(ret);
}

#endif

struct qemu_LdrResolveDelayLoadedAPI
{
    struct qemu_syscall super;
    uint64_t base;
    uint64_t desc;
    uint64_t dllhook;
    uint64_t syshook;
    uint64_t addr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* WINAPI LdrResolveDelayLoadedAPI(void *base, const IMAGE_DELAYLOAD_DESCRIPTOR *desc,
        void *dllhook, void *syshook, IMAGE_THUNK_DATA *addr, ULONG flags)
{
    struct qemu_LdrResolveDelayLoadedAPI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRRESOLVEDELAYLOADEDAPI);
    call.base = (ULONG_PTR)base;
    call.desc = (ULONG_PTR)desc;
    call.dllhook = (ULONG_PTR)dllhook;
    call.syshook = (ULONG_PTR)syshook;
    call.addr = (ULONG_PTR)addr;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

static void WINAPI *DelayLoaderFailure(ULONG u, DELAYLOAD_INFO *info)
{
    WINE_FIXME("Stub\n");
    return NULL;
}

void qemu_LdrResolveDelayLoadedAPI(struct qemu_syscall *call)
{
    struct qemu_LdrResolveDelayLoadedAPI *c = (struct qemu_LdrResolveDelayLoadedAPI *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(qemu_ops->qemu_LdrResolveDelayLoadedAPI(QEMU_G2H(c->base), QEMU_G2H(c->desc),
            DelayLoaderFailure, QEMU_G2H(c->syshook), QEMU_G2H(c->addr), c->flags));
}

#endif

struct qemu_RtlGetUnloadEventTrace
{
    struct qemu_syscall super;
};

typedef struct _RTL_UNLOAD_EVENT_TRACE RTL_UNLOAD_EVENT_TRACE;

#ifdef QEMU_DLL_GUEST

WINBASEAPI RTL_UNLOAD_EVENT_TRACE * WINAPI RtlGetUnloadEventTrace(void)
{
    struct qemu_RtlGetUnloadEventTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETUNLOADEVENTTRACE);

    qemu_syscall(&call.super);

    return (RTL_UNLOAD_EVENT_TRACE *)(ULONG_PTR)call.super.iret;
}

#else

extern WINBASEAPI RTL_UNLOAD_EVENT_TRACE * WINAPI RtlGetUnloadEventTrace(void);
void qemu_RtlGetUnloadEventTrace(struct qemu_syscall *call)
{
    struct qemu_RtlGetUnloadEventTrace *c = (struct qemu_RtlGetUnloadEventTrace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(RtlGetUnloadEventTrace());
}

#endif

struct qemu_RtlGetUnloadEventTraceEx
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t count;
    uint64_t trace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlGetUnloadEventTraceEx(ULONG **size, ULONG **count, void **trace)
{
    struct qemu_RtlGetUnloadEventTraceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETUNLOADEVENTTRACEEX);
    call.size = (ULONG_PTR)size;
    call.count = (ULONG_PTR)count;
    call.trace = (ULONG_PTR)trace;

    qemu_syscall(&call.super);
}

#else

extern WINBASEAPI void WINAPI RtlGetUnloadEventTraceEx(ULONG **size, ULONG **count, void **trace);
void qemu_RtlGetUnloadEventTraceEx(struct qemu_syscall *call)
{
    struct qemu_RtlGetUnloadEventTraceEx *c = (struct qemu_RtlGetUnloadEventTraceEx *)call;
    WINE_FIXME("Unverified!\n");
    RtlGetUnloadEventTraceEx(QEMU_G2H(c->size), QEMU_G2H(c->count), QEMU_G2H(c->trace));
}

#endif

struct qemu_LdrDisableThreadCalloutsForDll
{
    struct qemu_syscall super;
    uint64_t hModule;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrDisableThreadCalloutsForDll(HMODULE hModule)
{
    struct qemu_LdrDisableThreadCalloutsForDll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRDISABLETHREADCALLOUTSFORDLL);
    call.hModule = (ULONG_PTR)hModule;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrDisableThreadCalloutsForDll(struct qemu_syscall *call)
{
    struct qemu_LdrDisableThreadCalloutsForDll *c = (struct qemu_LdrDisableThreadCalloutsForDll *)call;
    WINE_TRACE("\n");
    c->super.iret = qemu_ops->qemu_LdrDisableThreadCalloutsForDll(QEMU_G2H(c->hModule));
}

#endif

struct qemu_LdrEnumerateLoadedModules
{
    struct qemu_syscall super;
    uint64_t unknown;
    uint64_t callback;
    uint64_t context;
};

typedef void  (CALLBACK *LDRENUMPROC)(LDR_DATA_TABLE_ENTRY *, void *, BOOLEAN *);

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrEnumerateLoadedModules(void *unknown, LDRENUMPROC callback, void *context)
{
    struct qemu_LdrEnumerateLoadedModules call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRENUMERATELOADEDMODULES);
    call.unknown = (ULONG_PTR)unknown;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI NTSTATUS WINAPI LdrEnumerateLoadedModules(void *unknown, LDRENUMPROC callback, void *context);

void qemu_LdrEnumerateLoadedModules(struct qemu_syscall *call)
{
    struct qemu_LdrEnumerateLoadedModules *c = (struct qemu_LdrEnumerateLoadedModules *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrEnumerateLoadedModules(QEMU_G2H(c->unknown), QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_LdrRegisterDllNotification
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t callback;
    uint64_t context;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrRegisterDllNotification(ULONG flags, PLDR_DLL_NOTIFICATION_FUNCTION callback, void *context, void **cookie)
{
    struct qemu_LdrRegisterDllNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRREGISTERDLLNOTIFICATION);
    call.flags = flags;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI NTSTATUS WINAPI LdrRegisterDllNotification(ULONG flags, PLDR_DLL_NOTIFICATION_FUNCTION callback, void *context, void **cookie);

void qemu_LdrRegisterDllNotification(struct qemu_syscall *call)
{
    struct qemu_LdrRegisterDllNotification *c = (struct qemu_LdrRegisterDllNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrRegisterDllNotification(c->flags, QEMU_G2H(c->callback), QEMU_G2H(c->context), QEMU_G2H(c->cookie));
}

#endif

struct qemu_LdrUnregisterDllNotification
{
    struct qemu_syscall super;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrUnregisterDllNotification(void *cookie)
{
    struct qemu_LdrUnregisterDllNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRUNREGISTERDLLNOTIFICATION);
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI NTSTATUS WINAPI LdrUnregisterDllNotification(void *cookie);

void qemu_LdrUnregisterDllNotification(struct qemu_syscall *call)
{
    struct qemu_LdrUnregisterDllNotification *c = (struct qemu_LdrUnregisterDllNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrUnregisterDllNotification(QEMU_G2H(c->cookie));
}

#endif

struct qemu_LdrLockLoaderLock
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t result;
    uint64_t magic;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrLockLoaderLock(ULONG flags, ULONG *result, ULONG_PTR *magic)
{
    struct qemu_LdrLockLoaderLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRLOCKLOADERLOCK);
    call.flags = flags;
    call.result = (ULONG_PTR)result;
    call.magic = (ULONG_PTR)magic;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrLockLoaderLock(struct qemu_syscall *call)
{
    struct qemu_LdrLockLoaderLock *c = (struct qemu_LdrLockLoaderLock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrLockLoaderLock(c->flags, QEMU_G2H(c->result), QEMU_G2H(c->magic));
}

#endif

struct qemu_LdrUnlockLoaderLock
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t magic;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrUnlockLoaderLock(ULONG flags, ULONG_PTR magic)
{
    struct qemu_LdrUnlockLoaderLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRUNLOCKLOADERLOCK);
    call.flags = flags;
    call.magic = magic;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrUnlockLoaderLock(struct qemu_syscall *call)
{
    struct qemu_LdrUnlockLoaderLock *c = (struct qemu_LdrUnlockLoaderLock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrUnlockLoaderLock(c->flags, c->magic);
}

#endif

struct qemu_LdrGetProcedureAddress
{
    struct qemu_syscall super;
    uint64_t module;
    uint64_t name;
    uint64_t ord;
    uint64_t address;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrGetProcedureAddress(HMODULE module, const ANSI_STRING *name, ULONG ord, PVOID *address)
{
    struct qemu_LdrGetProcedureAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRGETPROCEDUREADDRESS);
    call.module = (ULONG_PTR)module;
    call.name = (ULONG_PTR)name;
    call.ord = ord;
    call.address = (ULONG_PTR)address;

    qemu_syscall(&call.super);
    if (call.super.iret == STATUS_SUCCESS)
        *address = (void *)(ULONG_PTR)call.address;

    return call.super.iret;
}

#else

void qemu_LdrGetProcedureAddress(struct qemu_syscall *call)
{
    struct qemu_LdrGetProcedureAddress *c = (struct qemu_LdrGetProcedureAddress *)call;
    void *address;
    ANSI_STRING stack, *name = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    name = QEMU_G2H(c->name);
#else
    if (QEMU_G2H(c->name))
        STRING_g2h(name, QEMU_G2H(c->name));
    else
        name = NULL;
#endif

    c->super.iret = qemu_ops->qemu_LdrGetProcedureAddress(QEMU_G2H(c->module), name, c->ord, &address);
    WINE_TRACE("ret %lx got addr %p\n", c->super.iret, address);

    c->address = QEMU_H2G(address);
}

#endif

struct qemu_LdrLoadDll
{
    struct qemu_syscall super;
    uint64_t path_name;
    uint64_t flags;
    uint64_t libname;
    uint64_t hModule;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrLoadDll(LPCWSTR path_name, DWORD flags, const UNICODE_STRING *libname, HMODULE* hModule)
{
    struct qemu_LdrLoadDll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRLOADDLL);
    call.path_name = (ULONG_PTR)path_name;
    call.flags = flags;
    call.libname = (ULONG_PTR)libname;
    call.hModule = (ULONG_PTR)hModule;

    qemu_syscall(&call.super);
    *hModule = (HMODULE)(ULONG_PTR)call.hModule;

    return call.super.iret;
}

#else

void qemu_LdrLoadDll(struct qemu_syscall *call)
{
    struct qemu_LdrLoadDll *c = (struct qemu_LdrLoadDll *)call;
    UNICODE_STRING stack, *libname = &stack;
    HMODULE mod;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    libname = QEMU_G2H(c->libname);
#else
    if (QEMU_G2H(c->libname))
        UNICODE_STRING_g2h(libname, QEMU_G2H(c->libname));
    else
        libname = NULL;
#endif
    
    c->super.iret = qemu_ops->qemu_LdrLoadDll(QEMU_G2H(c->path_name), c->flags, libname, &mod);
    
    c->hModule = QEMU_H2G(mod);
}

#endif

struct qemu_LdrGetDllHandle
{
    struct qemu_syscall super;
    uint64_t load_path;
    uint64_t flags;
    uint64_t name;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrGetDllHandle(LPCWSTR load_path, ULONG flags, const UNICODE_STRING *name, HMODULE *base)
{
    struct qemu_LdrGetDllHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRGETDLLHANDLE);
    call.load_path = (ULONG_PTR)load_path;
    call.flags = flags;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);
    *base = (HMODULE)(ULONG_PTR)call.base;

    return call.super.iret;
}

#else

void qemu_LdrGetDllHandle(struct qemu_syscall *call)
{
    struct qemu_LdrGetDllHandle *c = (struct qemu_LdrGetDllHandle *)call;
    HMODULE base;
    UNICODE_STRING stack, *name = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    name = QEMU_G2H(c->name);
#else
    if (QEMU_G2H(c->name))
        UNICODE_STRING_g2h(name, QEMU_G2H(c->name));
    else
        name = NULL;
#endif

    c->super.iret = qemu_ops->qemu_LdrGetDllHandle(QEMU_G2H(c->load_path), c->flags, name, &base);
    
    c->base = QEMU_H2G(base);
}

#endif

struct qemu_LdrAddRefDll
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t module;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrAddRefDll(ULONG flags, HMODULE module)
{
    struct qemu_LdrAddRefDll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRADDREFDLL);
    call.flags = flags;
    call.module = (ULONG_PTR)module;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrAddRefDll(struct qemu_syscall *call)
{
    struct qemu_LdrAddRefDll *c = (struct qemu_LdrAddRefDll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrAddRefDll(c->flags, QEMU_G2H(c->module));
}

#endif

struct qemu_LdrProcessRelocationBlock
{
    struct qemu_syscall super;
    uint64_t page;
    uint64_t count;
    uint64_t relocs;
    uint64_t delta;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI IMAGE_BASE_RELOCATION * WINAPI LdrProcessRelocationBlock(void *page, UINT count, USHORT *relocs, INT_PTR delta)
{
    struct qemu_LdrProcessRelocationBlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRPROCESSRELOCATIONBLOCK);
    call.page = (ULONG_PTR)page;
    call.count = count;
    call.relocs = (ULONG_PTR)relocs;
    call.delta = delta;

    qemu_syscall(&call.super);

    return (IMAGE_BASE_RELOCATION *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LdrProcessRelocationBlock(struct qemu_syscall *call)
{
    struct qemu_LdrProcessRelocationBlock *c = (struct qemu_LdrProcessRelocationBlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(LdrProcessRelocationBlock(QEMU_G2H(c->page), c->count, QEMU_G2H(c->relocs), c->delta));
}

#endif

struct qemu_LdrQueryProcessModuleInformation
{
    struct qemu_syscall super;
    uint64_t smi;
    uint64_t buf_size;
    uint64_t req_size;
};

#ifdef QEMU_DLL_GUEST

typedef struct _SYSTEM_MODULE_INFORMATION SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

WINBASEAPI NTSTATUS WINAPI LdrQueryProcessModuleInformation(PSYSTEM_MODULE_INFORMATION smi, ULONG buf_size, ULONG* req_size)
{
    struct qemu_LdrQueryProcessModuleInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRQUERYPROCESSMODULEINFORMATION);
    call.smi = (ULONG_PTR)smi;
    call.buf_size = buf_size;
    call.req_size = (ULONG_PTR)req_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrQueryProcessModuleInformation(struct qemu_syscall *call)
{
    struct qemu_LdrQueryProcessModuleInformation *c = (struct qemu_LdrQueryProcessModuleInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrQueryProcessModuleInformation(QEMU_G2H(c->smi), c->buf_size, QEMU_G2H(c->req_size));
}

#endif

struct qemu_LdrQueryImageFileExecutionOptions
{
    struct qemu_syscall super;
    uint64_t key;
    uint64_t value;
    uint64_t type;
    uint64_t data;
    uint64_t in_size;
    uint64_t out_size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrQueryImageFileExecutionOptions(const UNICODE_STRING *key, LPCWSTR value, ULONG type, void *data, ULONG in_size, ULONG *out_size)
{
    struct qemu_LdrQueryImageFileExecutionOptions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRQUERYIMAGEFILEEXECUTIONOPTIONS);
    call.key = (ULONG_PTR)key;
    call.value = (ULONG_PTR)value;
    call.type = type;
    call.data = (ULONG_PTR)data;
    call.in_size = in_size;
    call.out_size = (ULONG_PTR)out_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrQueryImageFileExecutionOptions(struct qemu_syscall *call)
{
    struct qemu_LdrQueryImageFileExecutionOptions *c = (struct qemu_LdrQueryImageFileExecutionOptions *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrQueryImageFileExecutionOptions(QEMU_G2H(c->key), QEMU_G2H(c->value), c->type, QEMU_G2H(c->data), c->in_size, QEMU_G2H(c->out_size));
}

#endif

struct qemu_RtlDllShutdownInProgress
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlDllShutdownInProgress(void)
{
    struct qemu_RtlDllShutdownInProgress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDLLSHUTDOWNINPROGRESS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDllShutdownInProgress(struct qemu_syscall *call)
{
    struct qemu_RtlDllShutdownInProgress *c = (struct qemu_RtlDllShutdownInProgress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDllShutdownInProgress();
}

#endif

struct qemu_LdrShutdownProcess
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI LdrShutdownProcess(void)
{
    struct qemu_LdrShutdownProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRSHUTDOWNPROCESS);

    qemu_syscall(&call.super);
}

#else

void qemu_LdrShutdownProcess(struct qemu_syscall *call)
{
    struct qemu_LdrShutdownProcess *c = (struct qemu_LdrShutdownProcess *)call;
    WINE_FIXME("Unverified!\n");
    LdrShutdownProcess();
}

#endif

struct qemu_RtlExitUserProcess
{
    struct qemu_syscall super;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlExitUserProcess(DWORD status)
{
    struct qemu_RtlExitUserProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEXITUSERPROCESS);
    call.status = status;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlExitUserProcess(struct qemu_syscall *call)
{
    struct qemu_RtlExitUserProcess *c = (struct qemu_RtlExitUserProcess *)call;
    WINE_FIXME("Unverified!\n");
    RtlExitUserProcess(c->status);
}

#endif

struct qemu_LdrShutdownThread
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI LdrShutdownThread(void)
{
    struct qemu_LdrShutdownThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRSHUTDOWNTHREAD);

    qemu_syscall(&call.super);
}

#else

void qemu_LdrShutdownThread(struct qemu_syscall *call)
{
    struct qemu_LdrShutdownThread *c = (struct qemu_LdrShutdownThread *)call;
    WINE_FIXME("Unverified!\n");
    LdrShutdownThread();
}

#endif

struct qemu_LdrUnloadDll
{
    struct qemu_syscall super;
    uint64_t hModule;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrUnloadDll(HMODULE hModule)
{
    struct qemu_LdrUnloadDll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRUNLOADDLL);
    call.hModule = (ULONG_PTR)hModule;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrUnloadDll(struct qemu_syscall *call)
{
    struct qemu_LdrUnloadDll *c = (struct qemu_LdrUnloadDll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrUnloadDll(QEMU_G2H(c->hModule));
}

#endif

struct qemu_LdrInitializeThunk
{
    struct qemu_syscall super;
    uint64_t context;
    uint64_t entry;
    uint64_t unknown3;
    uint64_t unknown4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI LdrInitializeThunk(CONTEXT *context, void **entry, ULONG_PTR unknown3, ULONG_PTR unknown4)
{
    struct qemu_LdrInitializeThunk call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRINITIALIZETHUNK);
    call.context = (ULONG_PTR)context;
    call.entry = (ULONG_PTR)entry;
    call.unknown3 = unknown3;
    call.unknown4 = unknown4;

    qemu_syscall(&call.super);
}

#else

extern WINBASEAPI void WINAPI LdrInitializeThunk(CONTEXT *context, void **entry, ULONG_PTR unknown3, ULONG_PTR unknown4);

void qemu_LdrInitializeThunk(struct qemu_syscall *call)
{
    struct qemu_LdrInitializeThunk *c = (struct qemu_LdrInitializeThunk *)call;
    WINE_FIXME("Unverified!\n");
    LdrInitializeThunk(QEMU_G2H(c->context), QEMU_G2H(c->entry), c->unknown3, c->unknown4);
}

#endif

struct qemu_NtLoadDriver
{
    struct qemu_syscall super;
    uint64_t DriverServiceName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtLoadDriver(const UNICODE_STRING *DriverServiceName)
{
    struct qemu_NtLoadDriver call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTLOADDRIVER);
    call.DriverServiceName = (ULONG_PTR)DriverServiceName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtLoadDriver(struct qemu_syscall *call)
{
    struct qemu_NtLoadDriver *c = (struct qemu_NtLoadDriver *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtLoadDriver(QEMU_G2H(c->DriverServiceName));
}

#endif

struct qemu_NtUnloadDriver
{
    struct qemu_syscall super;
    uint64_t DriverServiceName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtUnloadDriver(const UNICODE_STRING *DriverServiceName)
{
    struct qemu_NtUnloadDriver call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTUNLOADDRIVER);
    call.DriverServiceName = (ULONG_PTR)DriverServiceName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtUnloadDriver(struct qemu_syscall *call)
{
    struct qemu_NtUnloadDriver *c = (struct qemu_NtUnloadDriver *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtUnloadDriver(QEMU_G2H(c->DriverServiceName));
}

#endif

struct qemu_LdrGetDllDirectory
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrGetDllDirectory(UNICODE_STRING *dir)
{
    struct qemu_LdrGetDllDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRGETDLLDIRECTORY);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrGetDllDirectory(struct qemu_syscall *call)
{
    struct qemu_LdrGetDllDirectory *c = (struct qemu_LdrGetDllDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrGetDllDirectory(QEMU_G2H(c->dir));
}

#endif

struct qemu_LdrSetDllDirectory
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrSetDllDirectory(const UNICODE_STRING *dir)
{
    struct qemu_LdrSetDllDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRSETDLLDIRECTORY);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrSetDllDirectory(struct qemu_syscall *call)
{
    struct qemu_LdrSetDllDirectory *c = (struct qemu_LdrSetDllDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrSetDllDirectory(QEMU_G2H(c->dir));
}

#endif

struct qemu_LdrAddDllDirectory
{
    struct qemu_syscall super;
    uint64_t dir;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrAddDllDirectory(const UNICODE_STRING *dir, void **cookie)
{
    struct qemu_LdrAddDllDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRADDDLLDIRECTORY);
    call.dir = (ULONG_PTR)dir;
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrAddDllDirectory(struct qemu_syscall *call)
{
    struct qemu_LdrAddDllDirectory *c = (struct qemu_LdrAddDllDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrAddDllDirectory(QEMU_G2H(c->dir), QEMU_G2H(c->cookie));
}

#endif

struct qemu_LdrGetDllPath
{
    struct qemu_syscall super;
    uint64_t module;
    uint64_t flags;
    uint64_t path;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrGetDllPath(PCWSTR module, ULONG flags, PWSTR *path, PWSTR *unknown)
{
    struct qemu_LdrGetDllPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRGETDLLPATH);
    call.module = (ULONG_PTR)module;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (call.super.iret == STATUS_INVALID_PARAMETER)
        return STATUS_INVALID_PARAMETER;

    *path = (WCHAR *)(ULONG_PTR)call.path;
    *unknown = (WCHAR *)(ULONG_PTR)call.unknown;

    return call.super.iret;
}

#else

void qemu_LdrGetDllPath(struct qemu_syscall *call)
{
    struct qemu_LdrGetDllPath *c = (struct qemu_LdrGetDllPath *)call;
    WCHAR *path;
    WCHAR *unknown;

    /* Note that we fix up host vs guest load paths at a later point. */
    WINE_TRACE("\n");
    c->super.iret = LdrGetDllPath(QEMU_G2H(c->module), c->flags, &path, &unknown);
    c->path = QEMU_H2G(path);
    c->unknown = QEMU_H2G(unknown);
}

#endif

struct qemu_LdrRemoveDllDirectory
{
    struct qemu_syscall super;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrRemoveDllDirectory(void *cookie)
{
    struct qemu_LdrRemoveDllDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRREMOVEDLLDIRECTORY);
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrRemoveDllDirectory(struct qemu_syscall *call)
{
    struct qemu_LdrRemoveDllDirectory *c = (struct qemu_LdrRemoveDllDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrRemoveDllDirectory(QEMU_G2H(c->cookie));
}

#endif

struct qemu_LdrSetDefaultDllDirectories
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrSetDefaultDllDirectories(ULONG flags)
{
    struct qemu_LdrSetDefaultDllDirectories call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRSETDEFAULTDLLDIRECTORIES);
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrSetDefaultDllDirectories(struct qemu_syscall *call)
{
    struct qemu_LdrSetDefaultDllDirectories *c = (struct qemu_LdrSetDefaultDllDirectories *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrSetDefaultDllDirectories(c->flags);
}

#endif

struct qemu_RtlSetSearchPathMode
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetSearchPathMode(ULONG flags)
{
    struct qemu_RtlSetSearchPathMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETSEARCHPATHMODE);
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetSearchPathMode(struct qemu_syscall *call)
{
    struct qemu_RtlSetSearchPathMode *c = (struct qemu_RtlSetSearchPathMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetSearchPathMode(c->flags);
}

#endif

struct qemu_RtlGetExePath
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetExePath(PCWSTR name, PWSTR *path)
{
    struct qemu_RtlGetExePath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETEXEPATH);
    call.name = (ULONG_PTR)name;
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetExePath(struct qemu_syscall *call)
{
    struct qemu_RtlGetExePath *c = (struct qemu_RtlGetExePath *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetExePath(QEMU_G2H(c->name), QEMU_G2H(c->path));
}

#endif

struct qemu_RtlGetSearchPath
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetSearchPath(PWSTR *path)
{
    struct qemu_RtlGetSearchPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETSEARCHPATH);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetSearchPath(struct qemu_syscall *call)
{
    struct qemu_RtlGetSearchPath *c = (struct qemu_RtlGetSearchPath *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetSearchPath(QEMU_G2H(c->path));
}

#endif

struct qemu_RtlReleasePath
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlReleasePath(PWSTR path)
{
    struct qemu_RtlReleasePath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRELEASEPATH);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlReleasePath(struct qemu_syscall *call)
{
    struct qemu_RtlReleasePath *c = (struct qemu_RtlReleasePath *)call;
    WINE_TRACE("\n");
    RtlReleasePath(QEMU_G2H(c->path));
}

#endif
