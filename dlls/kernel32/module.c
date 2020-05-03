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
#include <psapi.h>
#include <winternl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetDllDirectoryA
{
    struct qemu_syscall super;
    uint64_t buf_len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetDllDirectoryA(DWORD buf_len, LPSTR buffer)
{
    struct qemu_GetDllDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLLDIRECTORYA);
    call.buf_len = buf_len;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDllDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetDllDirectoryA *c = (struct qemu_GetDllDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDllDirectoryA(c->buf_len, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetDllDirectoryW
{
    struct qemu_syscall super;
    uint64_t buf_len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetDllDirectoryW(DWORD buf_len, LPWSTR buffer)
{
    struct qemu_GetDllDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDLLDIRECTORYW);
    call.buf_len = buf_len;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDllDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetDllDirectoryW *c = (struct qemu_GetDllDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDllDirectoryW(c->buf_len, QEMU_G2H(c->buffer));
}

#endif

struct qemu_SetDllDirectoryA
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDllDirectoryA(LPCSTR dir)
{
    struct qemu_SetDllDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDLLDIRECTORYA);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDllDirectoryA(struct qemu_syscall *call)
{
    struct qemu_SetDllDirectoryA *c = (struct qemu_SetDllDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDllDirectoryA(QEMU_G2H(c->dir));
}

#endif

struct qemu_SetDllDirectoryW
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDllDirectoryW(LPCWSTR dir)
{
    struct qemu_SetDllDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDLLDIRECTORYW);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDllDirectoryW(struct qemu_syscall *call)
{
    struct qemu_SetDllDirectoryW *c = (struct qemu_SetDllDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDllDirectoryW(QEMU_G2H(c->dir));
}

#endif

struct qemu_DisableThreadLibraryCalls
{
    struct qemu_syscall super;
    uint64_t hModule;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DisableThreadLibraryCalls(HMODULE hModule)
{
    struct qemu_DisableThreadLibraryCalls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DISABLETHREADLIBRARYCALLS);
    call.hModule = (ULONG_PTR)hModule;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DisableThreadLibraryCalls(struct qemu_syscall *call)
{
    struct qemu_DisableThreadLibraryCalls *c = (struct qemu_DisableThreadLibraryCalls *)call;
    WINE_TRACE("\n");
    c->super.iret = qemu_ops->qemu_DisableThreadLibraryCalls((HMODULE)c->hModule);
}

#endif

struct qemu_GetBinaryTypeW
{
    struct qemu_syscall super;
    uint64_t lpApplicationName;
    uint64_t lpBinaryType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetBinaryTypeW(LPCWSTR lpApplicationName, LPDWORD lpBinaryType)
{
    struct qemu_GetBinaryTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBINARYTYPEW);
    call.lpApplicationName = (ULONG_PTR)lpApplicationName;
    call.lpBinaryType = (ULONG_PTR)lpBinaryType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBinaryTypeW(struct qemu_syscall *call)
{
    struct qemu_GetBinaryTypeW *c = (struct qemu_GetBinaryTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBinaryTypeW(QEMU_G2H(c->lpApplicationName), QEMU_G2H(c->lpBinaryType));
}

#endif

struct qemu_GetBinaryTypeA
{
    struct qemu_syscall super;
    uint64_t lpApplicationName;
    uint64_t lpBinaryType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetBinaryTypeA(LPCSTR lpApplicationName, LPDWORD lpBinaryType)
{
    struct qemu_GetBinaryTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBINARYTYPEA);
    call.lpApplicationName = (ULONG_PTR)lpApplicationName;
    call.lpBinaryType = (ULONG_PTR)lpBinaryType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBinaryTypeA(struct qemu_syscall *call)
{
    struct qemu_GetBinaryTypeA *c = (struct qemu_GetBinaryTypeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBinaryTypeA(QEMU_G2H(c->lpApplicationName), QEMU_G2H(c->lpBinaryType));
}

#endif

struct qemu_LoadLibraryExA
{
    struct qemu_syscall super;
    uint64_t libname;
    uint64_t hfile;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI LoadLibraryExA(LPCSTR libname, HANDLE hfile, DWORD flags)
{
    struct qemu_LoadLibraryExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADLIBRARYEXA);
    call.libname = (ULONG_PTR)libname;
    call.hfile = (ULONG_PTR)hfile;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (HMODULE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LoadLibraryExA(struct qemu_syscall *call)
{
    struct qemu_LoadLibraryExA *c = (struct qemu_LoadLibraryExA *)call;
    WCHAR *nameW = NULL;
    int size;

    WINE_TRACE("\n");
    if (c->hfile)
        WINE_FIXME("Loading from file handle not implemented\n");

    if (c->libname)
    {
        size = MultiByteToWideChar(CP_ACP, 0, QEMU_G2H(c->libname), -1, NULL, 0);
        nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(*nameW));
        MultiByteToWideChar(CP_ACP, 0, QEMU_G2H(c->libname), -1, nameW, size);
    }

    c->super.iret = QEMU_H2G(qemu_ops->qemu_LoadLibrary(nameW, c->flags));
    HeapFree(GetProcessHeap(), 0, nameW);
}

#endif

struct qemu_LoadLibraryExW
{
    struct qemu_syscall super;
    uint64_t libnameW;
    uint64_t hfile;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI LoadLibraryExW(LPCWSTR libnameW, HANDLE hfile, DWORD flags)
{
    struct qemu_LoadLibraryExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADLIBRARYEXW);
    call.libnameW = (ULONG_PTR)libnameW;
    call.hfile = (ULONG_PTR)hfile;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (HMODULE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LoadLibraryExW(struct qemu_syscall *call)
{
    struct qemu_LoadLibraryExW *c = (struct qemu_LoadLibraryExW *)call;

    WINE_TRACE("\n");
    if (c->hfile)
        WINE_FIXME("Loading from file handle not implemented\n");

    c->super.iret = QEMU_H2G(qemu_ops->qemu_LoadLibrary(QEMU_G2H(c->libnameW), c->flags));
}

#endif

struct qemu_DelayLoadFailureHook
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t function;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FARPROC WINAPI DelayLoadFailureHook(LPCSTR name, LPCSTR function)
{
    struct qemu_DelayLoadFailureHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELAYLOADFAILUREHOOK);
    call.name = (ULONG_PTR)name;
    call.function = (ULONG_PTR)function;

    qemu_syscall(&call.super);

    return (FARPROC)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add DelayLoadFailureHook to Wine headers? */
extern FARPROC WINAPI DelayLoadFailureHook(LPCSTR name, LPCSTR function);
void qemu_DelayLoadFailureHook(struct qemu_syscall *call)
{
    struct qemu_DelayLoadFailureHook *c = (struct qemu_DelayLoadFailureHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(DelayLoadFailureHook(QEMU_G2H(c->name), QEMU_G2H(c->function)));
}

#endif

struct qemu_K32EnumProcessModules
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t lphModule;
    uint64_t cb;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EnumProcessModules(HANDLE process, HMODULE *lphModule, DWORD cb, DWORD *needed)
{
    struct qemu_K32EnumProcessModules call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32ENUMPROCESSMODULES);
    call.process = (ULONG_PTR)process;
    call.lphModule = (ULONG_PTR)lphModule;
    call.cb = cb;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32EnumProcessModules to Wine headers? */
extern BOOL WINAPI K32EnumProcessModules(HANDLE process, HMODULE *lphModule, DWORD cb, DWORD *needed);
void qemu_K32EnumProcessModules(struct qemu_syscall *call)
{
    struct qemu_K32EnumProcessModules *c = (struct qemu_K32EnumProcessModules *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EnumProcessModules(QEMU_G2H(c->process), QEMU_G2H(c->lphModule), c->cb, QEMU_G2H(c->needed));
}

#endif

struct qemu_K32EnumProcessModulesEx
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t lphModule;
    uint64_t cb;
    uint64_t needed;
    uint64_t filter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EnumProcessModulesEx(HANDLE process, HMODULE *lphModule, DWORD cb, DWORD *needed, DWORD filter)
{
    struct qemu_K32EnumProcessModulesEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32ENUMPROCESSMODULESEX);
    call.process = (ULONG_PTR)process;
    call.lphModule = (ULONG_PTR)lphModule;
    call.cb = cb;
    call.needed = (ULONG_PTR)needed;
    call.filter = filter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32EnumProcessModulesEx to Wine headers? */
extern BOOL WINAPI K32EnumProcessModulesEx(HANDLE process, HMODULE *lphModule, DWORD cb, DWORD *needed, DWORD filter);
void qemu_K32EnumProcessModulesEx(struct qemu_syscall *call)
{
    struct qemu_K32EnumProcessModulesEx *c = (struct qemu_K32EnumProcessModulesEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EnumProcessModulesEx(QEMU_G2H(c->process), QEMU_G2H(c->lphModule), c->cb, QEMU_G2H(c->needed), c->filter);
}

#endif

struct qemu_K32GetModuleBaseNameW
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t module;
    uint64_t base_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetModuleBaseNameW(HANDLE process, HMODULE module, LPWSTR base_name, DWORD size)
{
    struct qemu_K32GetModuleBaseNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMODULEBASENAMEW);
    call.process = (ULONG_PTR)process;
    call.module = (ULONG_PTR)module;
    call.base_name = (ULONG_PTR)base_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetModuleBaseNameW to Wine headers? */
extern DWORD WINAPI K32GetModuleBaseNameW(HANDLE process, HMODULE module, LPWSTR base_name, DWORD size);
void qemu_K32GetModuleBaseNameW(struct qemu_syscall *call)
{
    struct qemu_K32GetModuleBaseNameW *c = (struct qemu_K32GetModuleBaseNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetModuleBaseNameW(QEMU_G2H(c->process), QEMU_G2H(c->module), QEMU_G2H(c->base_name), c->size);
}

#endif

struct qemu_K32GetModuleBaseNameA
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t module;
    uint64_t base_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetModuleBaseNameA(HANDLE process, HMODULE module, LPSTR base_name, DWORD size)
{
    struct qemu_K32GetModuleBaseNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMODULEBASENAMEA);
    call.process = (ULONG_PTR)process;
    call.module = (ULONG_PTR)module;
    call.base_name = (ULONG_PTR)base_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetModuleBaseNameA to Wine headers? */
extern DWORD WINAPI K32GetModuleBaseNameA(HANDLE process, HMODULE module, LPSTR base_name, DWORD size);
void qemu_K32GetModuleBaseNameA(struct qemu_syscall *call)
{
    struct qemu_K32GetModuleBaseNameA *c = (struct qemu_K32GetModuleBaseNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetModuleBaseNameA(QEMU_G2H(c->process), QEMU_G2H(c->module), QEMU_G2H(c->base_name), c->size);
}

#endif

struct qemu_K32GetModuleFileNameExW
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t module;
    uint64_t file_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetModuleFileNameExW(HANDLE process, HMODULE module, LPWSTR file_name, DWORD size)
{
    struct qemu_K32GetModuleFileNameExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMODULEFILENAMEEXW);
    call.process = (ULONG_PTR)process;
    call.module = (ULONG_PTR)module;
    call.file_name = (ULONG_PTR)file_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetModuleFileNameExW to Wine headers? */
extern DWORD WINAPI K32GetModuleFileNameExW(HANDLE process, HMODULE module, LPWSTR file_name, DWORD size);
void qemu_K32GetModuleFileNameExW(struct qemu_syscall *call)
{
    struct qemu_K32GetModuleFileNameExW *c = (struct qemu_K32GetModuleFileNameExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetModuleFileNameExW(QEMU_G2H(c->process), QEMU_G2H(c->module), QEMU_G2H(c->file_name), c->size);
}

#endif

struct qemu_K32GetModuleFileNameExA
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t module;
    uint64_t file_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetModuleFileNameExA(HANDLE process, HMODULE module, LPSTR file_name, DWORD size)
{
    struct qemu_K32GetModuleFileNameExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMODULEFILENAMEEXA);
    call.process = (ULONG_PTR)process;
    call.module = (ULONG_PTR)module;
    call.file_name = (ULONG_PTR)file_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetModuleFileNameExA to Wine headers? */
extern DWORD WINAPI K32GetModuleFileNameExA(HANDLE process, HMODULE module, LPSTR file_name, DWORD size);
void qemu_K32GetModuleFileNameExA(struct qemu_syscall *call)
{
    struct qemu_K32GetModuleFileNameExA *c = (struct qemu_K32GetModuleFileNameExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetModuleFileNameExA(QEMU_G2H(c->process), QEMU_G2H(c->module), QEMU_G2H(c->file_name), c->size);
}

#endif

struct qemu_K32GetModuleInformation
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t module;
    uint64_t modinfo;
    uint64_t cb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32GetModuleInformation(HANDLE process, HMODULE module, MODULEINFO *modinfo, DWORD cb)
{
    struct qemu_K32GetModuleInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETMODULEINFORMATION);
    call.process = (ULONG_PTR)process;
    call.module = (ULONG_PTR)module;
    call.modinfo = (ULONG_PTR)modinfo;
    call.cb = cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetModuleInformation(struct qemu_syscall *call)
{
    struct qemu_K32GetModuleInformation *c = (struct qemu_K32GetModuleInformation *)call;
    LDR_DATA_TABLE_ENTRY *ldr_module;
    MODULEINFO *modinfo;

    WINE_FIXME("Unverified!\n");

    if (c->cb < sizeof(*modinfo))
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        c->super.iret = FALSE;
        return;
    }

    modinfo = QEMU_G2H(c->modinfo);

    if (!qemu_ops->qemu_get_ldr_module((HANDLE)c->process, (HANDLE)c->module,
            (void **)&ldr_module))
    {
        c->super.iret = FALSE;
        return;
    }

    modinfo->lpBaseOfDll = ldr_module->DllBase;
    modinfo->SizeOfImage = ldr_module->SizeOfImage;
    modinfo->EntryPoint  = ldr_module->EntryPoint;

    c->super.iret = TRUE;
}

#endif

struct qemu_AddDllDirectory
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DLL_DIRECTORY_COOKIE WINAPI AddDllDirectory(const WCHAR *dir)
{
    struct qemu_AddDllDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDDLLDIRECTORY);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return (DLL_DIRECTORY_COOKIE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_AddDllDirectory(struct qemu_syscall *call)
{
    struct qemu_AddDllDirectory *c = (struct qemu_AddDllDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(AddDllDirectory(QEMU_G2H(c->dir)));
}

#endif

struct qemu_RemoveDllDirectory
{
    struct qemu_syscall super;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RemoveDllDirectory(DLL_DIRECTORY_COOKIE cookie)
{
    struct qemu_RemoveDllDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEDLLDIRECTORY);
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveDllDirectory(struct qemu_syscall *call)
{
    struct qemu_RemoveDllDirectory *c = (struct qemu_RemoveDllDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RemoveDllDirectory(QEMU_G2H(c->cookie));
}

#endif
