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

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_CreateFileW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t access;
    uint64_t share;
    uint64_t security;
    uint64_t disposition;
    uint64_t flags;
    uint64_t template;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFileW(const WCHAR *name, DWORD access, DWORD share,
        SECURITY_ATTRIBUTES *security, DWORD disposition, DWORD flags,
        HANDLE template)
{
    struct qemu_CreateFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILEW);
    call.name = (uint64_t)name;
    call.access = access;
    call.share = share;
    call.security = (uint64_t)security;
    call.disposition = disposition;
    call.flags = flags;
    call.template = (uint64_t)template;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateFileW(struct qemu_syscall *call)
{
    struct qemu_CreateFileW *c = (struct qemu_CreateFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateFileW(QEMU_G2H(c->name), c->access, c->share,
            QEMU_G2H(c->security), c->disposition, c->flags, (HANDLE)c->template);
}

#endif

struct qemu_FindClose
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI FindClose(HANDLE handle)
{
    struct qemu_FindClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDCLOSE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindClose(struct qemu_syscall *call)
{
    struct qemu_FindClose *c = (struct qemu_FindClose *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)FindClose((HANDLE)c->handle);
}

#endif

struct qemu_FindFirstFileW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t finddata;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstFileW(const WCHAR *name, WIN32_FIND_DATAW *finddata)
{
    struct qemu_FindFirstFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTFILEW);
    call.name = (uint64_t)name;
    call.finddata = (uint64_t)finddata;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_FindFirstFileW(struct qemu_syscall *call)
{
    struct qemu_FindFirstFileW *c = (struct qemu_FindFirstFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)FindFirstFileW(QEMU_G2H(c->name), QEMU_G2H(c->finddata));
}

#endif

struct qemu_GetFileSize
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileSize(HANDLE file, DWORD *high)
{
    struct qemu_GetFileSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILESIZE);
    call.file = (uint64_t)file;
    call.high = (uint64_t)high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileSize(struct qemu_syscall *call)
{
    struct qemu_GetFileSize *c = (struct qemu_GetFileSize *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileSize((HANDLE)c->file, QEMU_G2H(c->high));
}

#endif

struct qemu_ReadFile
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buffer;
    uint64_t to_read;
    uint64_t read;
    uint64_t ovl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI ReadFile(HANDLE file, void *buffer, DWORD to_read, DWORD *read, OVERLAPPED *ovl)
{
    struct qemu_ReadFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READFILE);
    call.file = (uint64_t)file;
    call.buffer = (uint64_t)buffer;
    call.to_read = to_read;
    call.read = (uint64_t)read;
    call.ovl = (uint64_t)ovl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadFile(struct qemu_syscall *call)
{
    struct qemu_ReadFile *c = (struct qemu_ReadFile *)call;
    WINE_TRACE("\n");
    c->super.iret = ReadFile((HANDLE)c->file, QEMU_G2H(c->buffer), c->to_read,
            QEMU_G2H(c->read), QEMU_G2H(c->ovl));
}

#endif

struct qemu_SetEndOfFile
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI SetEndOfFile(HANDLE file)
{
    struct qemu_SetEndOfFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENDOFFILE);
    call.file = (uint64_t)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEndOfFile(struct qemu_syscall *call)
{
    struct qemu_SetEndOfFile *c = (struct qemu_SetEndOfFile *)call;
    WINE_TRACE("\n");
    c->super.iret = SetEndOfFile((HANDLE)c->file);
}

#endif

struct qemu_SetFilePointer
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t distance;
    uint64_t highword;
    uint64_t method;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetFilePointer(HANDLE hFile, LONG distance, LONG *highword, DWORD method)
{
    struct qemu_SetFilePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEPOINTER);
    call.hFile = (uint64_t)hFile;
    call.distance = (uint64_t)distance;
    call.highword = (uint64_t)highword;
    call.method = (uint64_t)method;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFilePointer(struct qemu_syscall *call)
{
    struct qemu_SetFilePointer *c = (struct qemu_SetFilePointer *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFilePointer(QEMU_G2H(c->hFile), c->distance, QEMU_G2H(c->highword), c->method);
}

#endif

struct qemu_WriteFile
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buffer;
    uint64_t to_write;
    uint64_t written;
    uint64_t ovl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI WriteFile(HANDLE file, const void *buffer, DWORD to_write, DWORD *written, OVERLAPPED *ovl)
{
    struct qemu_WriteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEFILE);
    call.file = (uint64_t)file;
    call.buffer = (uint64_t)buffer;
    call.to_write = to_write;
    call.written = (uint64_t)written;
    call.ovl = (uint64_t)ovl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteFile(struct qemu_syscall *call)
{
    struct qemu_WriteFile *c = (struct qemu_WriteFile *)call;
    WINE_TRACE("\n");

    /* This structure probably works just fine when just passed on, but write a FIXME until tested. */
    if (c->ovl)
        WINE_FIXME("OVERLAPPED structure not handled yet.\n");

    c->super.iret = WriteFile((HANDLE)c->file, QEMU_G2H(c->buffer), c->to_write,
            QEMU_G2H(c->written), QEMU_G2H(c->ovl));
}

#endif

