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

/* These types are missing in mingw. */
typedef enum
{
    INVALID_PATH = 0,
    UNC_PATH,              /* "//foo" */
    ABSOLUTE_DRIVE_PATH,   /* "c:/foo" */
    RELATIVE_DRIVE_PATH,   /* "c:foo" */
    ABSOLUTE_PATH,         /* "/foo" */
    RELATIVE_PATH,         /* "foo" */
    DEVICE_PATH,           /* "//./foo" */
    UNC_DOT_PATH           /* "//." */
} DOS_PATHNAME_TYPE;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlDetermineDosPathNameType_U
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DOS_PATHNAME_TYPE WINAPI RtlDetermineDosPathNameType_U(PCWSTR path)
{
    struct qemu_RtlDetermineDosPathNameType_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDETERMINEDOSPATHNAMETYPE_U);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDetermineDosPathNameType_U(struct qemu_syscall *call)
{
    struct qemu_RtlDetermineDosPathNameType_U *c = (struct qemu_RtlDetermineDosPathNameType_U *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlDetermineDosPathNameType_U(QEMU_G2H(c->path));
}

#endif

struct qemu_RtlIsDosDeviceName_U
{
    struct qemu_syscall super;
    uint64_t dos_name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlIsDosDeviceName_U(PCWSTR dos_name)
{
    struct qemu_RtlIsDosDeviceName_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISDOSDEVICENAME_U);
    call.dos_name = (ULONG_PTR)dos_name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsDosDeviceName_U(struct qemu_syscall *call)
{
    struct qemu_RtlIsDosDeviceName_U *c = (struct qemu_RtlIsDosDeviceName_U *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlIsDosDeviceName_U(QEMU_G2H(c->dos_name));
}

#endif

struct qemu_RtlDosPathNameToNtPathName_U
{
    struct qemu_syscall super;
    uint64_t dos_path;
    uint64_t ntpath;
    uint64_t file_part;
    uint64_t cd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlDosPathNameToNtPathName_U(const WCHAR *dos_path, PUNICODE_STRING ntpath, PCWSTR* file_part, VOID* cd)
{
    struct qemu_RtlDosPathNameToNtPathName_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOSPATHNAMETONTPATHNAME_U);
    call.dos_path = (ULONG_PTR)dos_path;
    call.ntpath = (ULONG_PTR)ntpath;
    call.file_part = (ULONG_PTR)file_part;
    call.cd = (ULONG_PTR)cd;

    qemu_syscall(&call.super);
    if (file_part)
        *file_part = (WCHAR *)(ULONG_PTR)call.file_part;

    return call.super.iret;
}

#else

void qemu_RtlDosPathNameToNtPathName_U(struct qemu_syscall *call)
{
    struct qemu_RtlDosPathNameToNtPathName_U *c = (struct qemu_RtlDosPathNameToNtPathName_U *)call;
    UNICODE_STRING path_stack, *path = &path_stack;
    WCHAR *file_part;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    path = QEMU_G2H(c->ntpath);
#endif

    c->super.iret = RtlDosPathNameToNtPathName_U(QEMU_G2H(c->dos_path), path,
            QEMU_G2H(c->file_part) ? &file_part : NULL, QEMU_G2H(c->cd));
    c->file_part = QEMU_H2G(file_part);

#if GUEST_BIT != HOST_BIT
    UNICODE_STRING_h2g(QEMU_G2H(c->ntpath), path);
#endif
}

#endif

struct qemu_RtlDosSearchPath_U
{
    struct qemu_syscall super;
    uint64_t paths;
    uint64_t search;
    uint64_t ext;
    uint64_t buffer_size;
    uint64_t buffer;
    uint64_t file_part;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlDosSearchPath_U(LPCWSTR paths, LPCWSTR search, LPCWSTR ext, ULONG buffer_size, LPWSTR buffer, LPWSTR* file_part)
{
    struct qemu_RtlDosSearchPath_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOSSEARCHPATH_U);
    call.paths = (ULONG_PTR)paths;
    call.search = (ULONG_PTR)search;
    call.ext = (ULONG_PTR)ext;
    call.buffer_size = (ULONG_PTR)buffer_size;
    call.buffer = (ULONG_PTR)buffer;
    call.file_part = (ULONG_PTR)file_part;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDosSearchPath_U(struct qemu_syscall *call)
{
    struct qemu_RtlDosSearchPath_U *c = (struct qemu_RtlDosSearchPath_U *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDosSearchPath_U(QEMU_G2H(c->paths), QEMU_G2H(c->search), QEMU_G2H(c->ext), c->buffer_size, QEMU_G2H(c->buffer), QEMU_G2H(c->file_part));
}

#endif

struct qemu_RtlGetFullPathName_U
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t size;
    uint64_t buffer;
    uint64_t file_part;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlGetFullPathName_U(const WCHAR* name, ULONG size, WCHAR* buffer, WCHAR** file_part)
{
    struct qemu_RtlGetFullPathName_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETFULLPATHNAME_U);
    call.name = (ULONG_PTR)name;
    call.size = (ULONG_PTR)size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);
    if (file_part)
        *file_part = (WCHAR *)(ULONG_PTR)call.file_part;

    return call.super.iret;
}

#else

void qemu_RtlGetFullPathName_U(struct qemu_syscall *call)
{
    struct qemu_RtlGetFullPathName_U *c = (struct qemu_RtlGetFullPathName_U *)call;
    WCHAR *file_part;

    WINE_TRACE("\n");
    c->super.iret = RtlGetFullPathName_U(QEMU_G2H(c->name), c->size, QEMU_G2H(c->buffer), &file_part);
    c->file_part = QEMU_H2G(file_part);
}

#endif

struct qemu_RtlGetLongestNtPathLength
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlGetLongestNtPathLength(void)
{
    struct qemu_RtlGetLongestNtPathLength call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETLONGESTNTPATHLENGTH);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetLongestNtPathLength(struct qemu_syscall *call)
{
    struct qemu_RtlGetLongestNtPathLength *c = (struct qemu_RtlGetLongestNtPathLength *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetLongestNtPathLength();
}

#endif

struct qemu_RtlIsNameLegalDOS8Dot3
{
    struct qemu_syscall super;
    uint64_t unicode;
    uint64_t oem;
    uint64_t spaces;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlIsNameLegalDOS8Dot3(UNICODE_STRING *unicode, OEM_STRING *oem, BOOLEAN *spaces)
{
    struct qemu_RtlIsNameLegalDOS8Dot3 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISNAMELEGALDOS8DOT3);
    call.unicode = (ULONG_PTR)unicode;
    call.oem = (ULONG_PTR)oem;
    call.spaces = (ULONG_PTR)spaces;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsNameLegalDOS8Dot3(struct qemu_syscall *call)
{
    struct qemu_RtlIsNameLegalDOS8Dot3 *c = (struct qemu_RtlIsNameLegalDOS8Dot3 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsNameLegalDOS8Dot3(QEMU_G2H(c->unicode), QEMU_G2H(c->oem), QEMU_G2H(c->spaces));
}

#endif

struct qemu_RtlGetCurrentDirectory_U
{
    struct qemu_syscall super;
    uint64_t buflen;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetCurrentDirectory_U(ULONG buflen, LPWSTR buf)
{
    struct qemu_RtlGetCurrentDirectory_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETCURRENTDIRECTORY_U);
    call.buflen = (ULONG_PTR)buflen;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetCurrentDirectory_U(struct qemu_syscall *call)
{
    struct qemu_RtlGetCurrentDirectory_U *c = (struct qemu_RtlGetCurrentDirectory_U *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetCurrentDirectory_U(c->buflen, QEMU_G2H(c->buf));
}

#endif

struct qemu_RtlSetCurrentDirectory_U
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetCurrentDirectory_U(const UNICODE_STRING* dir)
{
    struct qemu_RtlSetCurrentDirectory_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETCURRENTDIRECTORY_U);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetCurrentDirectory_U(struct qemu_syscall *call)
{
    struct qemu_RtlSetCurrentDirectory_U *c = (struct qemu_RtlSetCurrentDirectory_U *)call;
    TEB *qemu_teb = qemu_ops->qemu_getTEB(), *wine_teb = NtCurrentTeb();
    TEB32 *qemu_teb32 = qemu_ops->qemu_getTEB32();

    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetCurrentDirectory_U(QEMU_G2H(c->dir));

    /* No need to update dosPath, it always points to the same place anyway. */
    qemu_teb->Peb->ProcessParameters->CurrentDirectory.Handle =
            wine_teb->Peb->ProcessParameters->CurrentDirectory.Handle;

    if (qemu_teb32)
    {
        PEB32 *peb32 = (PEB32 *)(ULONG_PTR)qemu_teb32->Peb;
        RTL_USER_PROCESS_PARAMETERS32 *pp32 = (RTL_USER_PROCESS_PARAMETERS32 *)(ULONG_PTR)peb32->ProcessParameters;
        pp32->CurrentDirectory.Handle = (ULONG_PTR)wine_teb->Peb->ProcessParameters->CurrentDirectory.Handle;
        memcpy((void *)(ULONG_PTR)pp32->CurrentDirectory.DosPath.Buffer,
                wine_teb->Peb->ProcessParameters->CurrentDirectory.DosPath.Buffer,
                pp32->CurrentDirectory.DosPath.MaximumLength);
    }
}

#endif

struct qemu_RtlDosPathNameToNtPathName_U_WithStatus
{
    struct qemu_syscall super;
    uint64_t dos_path;
    uint64_t ntpath;
    uint64_t file_part;
    uint64_t cd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDosPathNameToNtPathName_U_WithStatus(const WCHAR *dos_path, UNICODE_STRING *ntpath, WCHAR **file_part, VOID *cd)
{
    struct qemu_RtlDosPathNameToNtPathName_U_WithStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOSPATHNAMETONTPATHNAME_U_WITHSTATUS);
    call.dos_path = (ULONG_PTR)dos_path;
    call.ntpath = (ULONG_PTR)ntpath;
    call.file_part = (ULONG_PTR)file_part;
    call.cd = (ULONG_PTR)cd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDosPathNameToNtPathName_U_WithStatus(struct qemu_syscall *call)
{
    struct qemu_RtlDosPathNameToNtPathName_U_WithStatus *c = (struct qemu_RtlDosPathNameToNtPathName_U_WithStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDosPathNameToNtPathName_U_WithStatus(QEMU_G2H(c->dos_path), QEMU_G2H(c->ntpath), QEMU_G2H(c->file_part), QEMU_G2H(c->cd));
}

#endif
