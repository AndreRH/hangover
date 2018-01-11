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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_GetFullPathNameW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t len;
    uint64_t buffer;
    uint64_t lastpart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFullPathNameW(LPCWSTR name, DWORD len, LPWSTR buffer, LPWSTR *lastpart)
{
    struct qemu_GetFullPathNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFULLPATHNAMEW);
    call.name = (ULONG_PTR)name;
    call.len = len;
    call.buffer = (ULONG_PTR)buffer;
    call.lastpart = (ULONG_PTR)lastpart;

    if (lastpart)
        call.lastpart = (ULONG_PTR)*lastpart;

    qemu_syscall(&call.super);

    if (lastpart)
        *lastpart = (WCHAR *)(ULONG_PTR)call.lastpart;

    return call.super.iret;
}

#else

void qemu_GetFullPathNameW(struct qemu_syscall *call)
{
    struct qemu_GetFullPathNameW *c = (struct qemu_GetFullPathNameW *)call;
    WCHAR *lastpart;
    WINE_TRACE("\n");

    lastpart = QEMU_G2H(c->lastpart);

    c->super.iret = GetFullPathNameW(QEMU_G2H(c->name), c->len, QEMU_G2H(c->buffer), &lastpart);

    c->lastpart = QEMU_H2G(lastpart);
}

#endif

struct qemu_GetFullPathNameA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t len;
    uint64_t buffer;
    uint64_t lastpart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFullPathNameA(LPCSTR name, DWORD len, LPSTR buffer, LPSTR *lastpart)
{
    struct qemu_GetFullPathNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFULLPATHNAMEA);
    call.name = (ULONG_PTR)name;
    call.len = len;
    call.buffer = (ULONG_PTR)buffer;

    if (lastpart)
        call.lastpart = (ULONG_PTR)*lastpart;

    qemu_syscall(&call.super);

    if (lastpart)
        *lastpart = (char *)(ULONG_PTR)call.lastpart;

    return call.super.iret;
}

#else

void qemu_GetFullPathNameA(struct qemu_syscall *call)
{
    struct qemu_GetFullPathNameA *c = (struct qemu_GetFullPathNameA *)call;
    char *lastpart;
    WINE_TRACE("\n");

    lastpart = QEMU_G2H(c->lastpart);

    c->super.iret = GetFullPathNameA(QEMU_G2H(c->name), c->len, QEMU_G2H(c->buffer), &lastpart);

    c->lastpart = QEMU_H2G(lastpart);
}

#endif

struct qemu_GetLongPathNameW
{
    struct qemu_syscall super;
    uint64_t shortpath;
    uint64_t longpath;
    uint64_t longlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLongPathNameW(LPCWSTR shortpath, LPWSTR longpath, DWORD longlen)
{
    struct qemu_GetLongPathNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLONGPATHNAMEW);
    call.shortpath = (ULONG_PTR)shortpath;
    call.longpath = (ULONG_PTR)longpath;
    call.longlen = longlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLongPathNameW(struct qemu_syscall *call)
{
    struct qemu_GetLongPathNameW *c = (struct qemu_GetLongPathNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLongPathNameW(QEMU_G2H(c->shortpath), QEMU_G2H(c->longpath), c->longlen);
}

#endif

struct qemu_GetLongPathNameA
{
    struct qemu_syscall super;
    uint64_t shortpath;
    uint64_t longpath;
    uint64_t longlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLongPathNameA(LPCSTR shortpath, LPSTR longpath, DWORD longlen)
{
    struct qemu_GetLongPathNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLONGPATHNAMEA);
    call.shortpath = (ULONG_PTR)shortpath;
    call.longpath = (ULONG_PTR)longpath;
    call.longlen = longlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLongPathNameA(struct qemu_syscall *call)
{
    struct qemu_GetLongPathNameA *c = (struct qemu_GetLongPathNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLongPathNameA(QEMU_G2H(c->shortpath), QEMU_G2H(c->longpath), c->longlen);
}

#endif

struct qemu_GetShortPathNameW
{
    struct qemu_syscall super;
    uint64_t longpath;
    uint64_t shortpath;
    uint64_t shortlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetShortPathNameW(LPCWSTR longpath, LPWSTR shortpath, DWORD shortlen)
{
    struct qemu_GetShortPathNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSHORTPATHNAMEW);
    call.longpath = (ULONG_PTR)longpath;
    call.shortpath = (ULONG_PTR)shortpath;
    call.shortlen = shortlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetShortPathNameW(struct qemu_syscall *call)
{
    struct qemu_GetShortPathNameW *c = (struct qemu_GetShortPathNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetShortPathNameW(QEMU_G2H(c->longpath), QEMU_G2H(c->shortpath), c->shortlen);
}

#endif

struct qemu_GetShortPathNameA
{
    struct qemu_syscall super;
    uint64_t longpath;
    uint64_t shortpath;
    uint64_t shortlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetShortPathNameA(LPCSTR longpath, LPSTR shortpath, DWORD shortlen)
{
    struct qemu_GetShortPathNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSHORTPATHNAMEA);
    call.longpath = (ULONG_PTR)longpath;
    call.shortpath = (ULONG_PTR)shortpath;
    call.shortlen = shortlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetShortPathNameA(struct qemu_syscall *call)
{
    struct qemu_GetShortPathNameA *c = (struct qemu_GetShortPathNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetShortPathNameA(QEMU_G2H(c->longpath), QEMU_G2H(c->shortpath), c->shortlen);
}

#endif

struct qemu_GetTempPathA
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTempPathA(DWORD count, LPSTR path)
{
    struct qemu_GetTempPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEMPPATHA);
    call.count = count;
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTempPathA(struct qemu_syscall *call)
{
    struct qemu_GetTempPathA *c = (struct qemu_GetTempPathA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTempPathA(c->count, QEMU_G2H(c->path));
}

#endif

struct qemu_GetTempPathW
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTempPathW(DWORD count, LPWSTR path)
{
    struct qemu_GetTempPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEMPPATHW);
    call.count = count;
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTempPathW(struct qemu_syscall *call)
{
    struct qemu_GetTempPathW *c = (struct qemu_GetTempPathW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTempPathW(c->count, QEMU_G2H(c->path));
}

#endif

struct qemu_GetTempFileNameA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t prefix;
    uint64_t unique;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetTempFileNameA(LPCSTR path, LPCSTR prefix, UINT unique, LPSTR buffer)
{
    struct qemu_GetTempFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEMPFILENAMEA);
    call.path = (ULONG_PTR)path;
    call.prefix = (ULONG_PTR)prefix;
    call.unique = unique;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTempFileNameA(struct qemu_syscall *call)
{
    struct qemu_GetTempFileNameA *c = (struct qemu_GetTempFileNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTempFileNameA(QEMU_G2H(c->path), QEMU_G2H(c->prefix), c->unique, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetTempFileNameW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t prefix;
    uint64_t unique;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetTempFileNameW(LPCWSTR path, LPCWSTR prefix, UINT unique, LPWSTR buffer)
{
    struct qemu_GetTempFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEMPFILENAMEW);
    call.path = (ULONG_PTR)path;
    call.prefix = (ULONG_PTR)prefix;
    call.unique = unique;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTempFileNameW(struct qemu_syscall *call)
{
    struct qemu_GetTempFileNameW *c = (struct qemu_GetTempFileNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTempFileNameW(QEMU_G2H(c->path), QEMU_G2H(c->prefix), c->unique, QEMU_G2H(c->buffer));
}

#endif

struct qemu_SearchPathW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t name;
    uint64_t ext;
    uint64_t buflen;
    uint64_t buffer;
    uint64_t lastpart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SearchPathW(LPCWSTR path, LPCWSTR name, LPCWSTR ext, DWORD buflen, LPWSTR buffer, LPWSTR *lastpart)
{
    struct qemu_SearchPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SEARCHPATHW);
    call.path = (ULONG_PTR)path;
    call.name = (ULONG_PTR)name;
    call.ext = (ULONG_PTR)ext;
    call.buflen = buflen;
    call.buffer = (ULONG_PTR)buffer;
    call.lastpart = (ULONG_PTR)lastpart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SearchPathW(struct qemu_syscall *call)
{
    struct qemu_SearchPathW *c = (struct qemu_SearchPathW *)call;
    WINE_TRACE("\n");
    c->super.iret = SearchPathW(QEMU_G2H(c->path), QEMU_G2H(c->name), QEMU_G2H(c->ext), c->buflen, QEMU_G2H(c->buffer), QEMU_G2H(c->lastpart));
}

#endif

struct qemu_SearchPathA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t name;
    uint64_t ext;
    uint64_t buflen;
    uint64_t buffer;
    uint64_t lastpart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SearchPathA(LPCSTR path, LPCSTR name, LPCSTR ext, DWORD buflen, LPSTR buffer, LPSTR *lastpart)
{
    struct qemu_SearchPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SEARCHPATHA);
    call.path = (ULONG_PTR)path;
    call.name = (ULONG_PTR)name;
    call.ext = (ULONG_PTR)ext;
    call.buflen = buflen;
    call.buffer = (ULONG_PTR)buffer;
    call.lastpart = (ULONG_PTR)lastpart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SearchPathA(struct qemu_syscall *call)
{
    struct qemu_SearchPathA *c = (struct qemu_SearchPathA *)call;
    WINE_TRACE("\n");
    c->super.iret = SearchPathA(QEMU_G2H(c->path), QEMU_G2H(c->name), QEMU_G2H(c->ext), c->buflen, QEMU_G2H(c->buffer), QEMU_G2H(c->lastpart));
}

#endif

struct qemu_CopyFileW
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t fail_if_exists;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CopyFileW(LPCWSTR source, LPCWSTR dest, BOOL fail_if_exists)
{
    struct qemu_CopyFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYFILEW);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.fail_if_exists = fail_if_exists;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyFileW(struct qemu_syscall *call)
{
    struct qemu_CopyFileW *c = (struct qemu_CopyFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = CopyFileW(QEMU_G2H(c->source), QEMU_G2H(c->dest), c->fail_if_exists);
}

#endif

struct qemu_CopyFileA
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t fail_if_exists;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CopyFileA(LPCSTR source, LPCSTR dest, BOOL fail_if_exists)
{
    struct qemu_CopyFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYFILEA);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.fail_if_exists = fail_if_exists;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyFileA(struct qemu_syscall *call)
{
    struct qemu_CopyFileA *c = (struct qemu_CopyFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = CopyFileA(QEMU_G2H(c->source), QEMU_G2H(c->dest), c->fail_if_exists);
}

#endif

struct qemu_CopyFileExW
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t progress;
    uint64_t param;
    uint64_t cancel_ptr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CopyFileExW(LPCWSTR source, LPCWSTR dest, LPPROGRESS_ROUTINE progress, LPVOID param, LPBOOL cancel_ptr, DWORD flags)
{
    struct qemu_CopyFileExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYFILEEXW);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.progress = (ULONG_PTR)progress;
    call.param = (ULONG_PTR)param;
    call.cancel_ptr = (ULONG_PTR)cancel_ptr;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyFileExW(struct qemu_syscall *call)
{
    struct qemu_CopyFileExW *c = (struct qemu_CopyFileExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CopyFileExW(QEMU_G2H(c->source), QEMU_G2H(c->dest), QEMU_G2H(c->progress), QEMU_G2H(c->param), QEMU_G2H(c->cancel_ptr), c->flags);
}

#endif

struct qemu_CopyFileExA
{
    struct qemu_syscall super;
    uint64_t sourceFilename;
    uint64_t destFilename;
    uint64_t progressRoutine;
    uint64_t appData;
    uint64_t cancelFlagPointer;
    uint64_t copyFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CopyFileExA(LPCSTR sourceFilename, LPCSTR destFilename, LPPROGRESS_ROUTINE progressRoutine, LPVOID appData, LPBOOL cancelFlagPointer, DWORD copyFlags)
{
    struct qemu_CopyFileExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYFILEEXA);
    call.sourceFilename = (ULONG_PTR)sourceFilename;
    call.destFilename = (ULONG_PTR)destFilename;
    call.progressRoutine = (ULONG_PTR)progressRoutine;
    call.appData = (ULONG_PTR)appData;
    call.cancelFlagPointer = (ULONG_PTR)cancelFlagPointer;
    call.copyFlags = copyFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyFileExA(struct qemu_syscall *call)
{
    struct qemu_CopyFileExA *c = (struct qemu_CopyFileExA *)call;
    WINE_TRACE("\n");
    if (c->progressRoutine)
        WINE_FIXME("I probably have to do something about progressRoutine.\n");
    c->super.iret = CopyFileExA(QEMU_G2H(c->sourceFilename), QEMU_G2H(c->destFilename),
            QEMU_G2H(c->progressRoutine), QEMU_G2H(c->appData), QEMU_G2H(c->cancelFlagPointer), c->copyFlags);
}

#endif

struct qemu_MoveFileWithProgressW
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t fnProgress;
    uint64_t param;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveFileWithProgressW(LPCWSTR source, LPCWSTR dest, LPPROGRESS_ROUTINE fnProgress, LPVOID param, DWORD flag)
{
    struct qemu_MoveFileWithProgressW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEFILEWITHPROGRESSW);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.fnProgress = (ULONG_PTR)fnProgress;
    call.param = (ULONG_PTR)param;
    call.flag = flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveFileWithProgressW(struct qemu_syscall *call)
{
    struct qemu_MoveFileWithProgressW *c = (struct qemu_MoveFileWithProgressW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MoveFileWithProgressW(QEMU_G2H(c->source), QEMU_G2H(c->dest), QEMU_G2H(c->fnProgress), QEMU_G2H(c->param), c->flag);
}

#endif

struct qemu_MoveFileWithProgressA
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t fnProgress;
    uint64_t param;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveFileWithProgressA(LPCSTR source, LPCSTR dest, LPPROGRESS_ROUTINE fnProgress, LPVOID param, DWORD flag)
{
    struct qemu_MoveFileWithProgressA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEFILEWITHPROGRESSA);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.fnProgress = (ULONG_PTR)fnProgress;
    call.param = (ULONG_PTR)param;
    call.flag = flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveFileWithProgressA(struct qemu_syscall *call)
{
    struct qemu_MoveFileWithProgressA *c = (struct qemu_MoveFileWithProgressA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MoveFileWithProgressA(QEMU_G2H(c->source), QEMU_G2H(c->dest), QEMU_G2H(c->fnProgress), QEMU_G2H(c->param), c->flag);
}

#endif

struct qemu_MoveFileExW
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveFileExW(LPCWSTR source, LPCWSTR dest, DWORD flag)
{
    struct qemu_MoveFileExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEFILEEXW);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.flag = flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveFileExW(struct qemu_syscall *call)
{
    struct qemu_MoveFileExW *c = (struct qemu_MoveFileExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MoveFileExW(QEMU_G2H(c->source), QEMU_G2H(c->dest), c->flag);
}

#endif

struct qemu_MoveFileExA
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveFileExA(LPCSTR source, LPCSTR dest, DWORD flag)
{
    struct qemu_MoveFileExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEFILEEXA);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;
    call.flag = flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveFileExA(struct qemu_syscall *call)
{
    struct qemu_MoveFileExA *c = (struct qemu_MoveFileExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MoveFileExA(QEMU_G2H(c->source), QEMU_G2H(c->dest), c->flag);
}

#endif

struct qemu_MoveFileW
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveFileW(LPCWSTR source, LPCWSTR dest)
{
    struct qemu_MoveFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEFILEW);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveFileW(struct qemu_syscall *call)
{
    struct qemu_MoveFileW *c = (struct qemu_MoveFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = MoveFileW(QEMU_G2H(c->source), QEMU_G2H(c->dest));
}

#endif

struct qemu_MoveFileA
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t dest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveFileA(LPCSTR source, LPCSTR dest)
{
    struct qemu_MoveFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEFILEA);
    call.source = (ULONG_PTR)source;
    call.dest = (ULONG_PTR)dest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveFileA(struct qemu_syscall *call)
{
    struct qemu_MoveFileA *c = (struct qemu_MoveFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = MoveFileA(QEMU_G2H(c->source), QEMU_G2H(c->dest));
}

#endif

struct qemu_CreateHardLinkW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t lpExistingFileName;
    uint64_t lpSecurityAttributes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateHardLinkW(LPCWSTR lpFileName, LPCWSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    struct qemu_CreateHardLinkW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEHARDLINKW);
    call.lpFileName = (ULONG_PTR)lpFileName;
    call.lpExistingFileName = (ULONG_PTR)lpExistingFileName;
    call.lpSecurityAttributes = (ULONG_PTR)lpSecurityAttributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateHardLinkW(struct qemu_syscall *call)
{
    struct qemu_CreateHardLinkW *c = (struct qemu_CreateHardLinkW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateHardLinkW(QEMU_G2H(c->lpFileName), QEMU_G2H(c->lpExistingFileName), QEMU_G2H(c->lpSecurityAttributes));
}

#endif

struct qemu_CreateHardLinkA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t lpExistingFileName;
    uint64_t lpSecurityAttributes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateHardLinkA(LPCSTR lpFileName, LPCSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    struct qemu_CreateHardLinkA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEHARDLINKA);
    call.lpFileName = (ULONG_PTR)lpFileName;
    call.lpExistingFileName = (ULONG_PTR)lpExistingFileName;
    call.lpSecurityAttributes = (ULONG_PTR)lpSecurityAttributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateHardLinkA(struct qemu_syscall *call)
{
    struct qemu_CreateHardLinkA *c = (struct qemu_CreateHardLinkA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateHardLinkA(QEMU_G2H(c->lpFileName), QEMU_G2H(c->lpExistingFileName), QEMU_G2H(c->lpSecurityAttributes));
}

#endif

struct qemu_CreateDirectoryW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateDirectoryW(LPCWSTR path, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIRECTORYW);
    call.path = (ULONG_PTR)path;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateDirectoryW(struct qemu_syscall *call)
{
    struct qemu_CreateDirectoryW *c = (struct qemu_CreateDirectoryW *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->sa)
        WINE_FIXME("Convert SECURITY_ATTRIBUTES.\n");
#endif

    c->super.iret = CreateDirectoryW(QEMU_G2H(c->path), QEMU_G2H(c->sa));
}

#endif

struct qemu_CreateDirectoryA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateDirectoryA(LPCSTR path, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIRECTORYA);
    call.path = (ULONG_PTR)path;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateDirectoryA(struct qemu_syscall *call)
{
    struct qemu_CreateDirectoryA *c = (struct qemu_CreateDirectoryA *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->sa)
        WINE_FIXME("Convert SECURITY_ATTRIBUTES.\n");
#endif

    c->super.iret = CreateDirectoryA(QEMU_G2H(c->path), QEMU_G2H(c->sa));
}

#endif

struct qemu_CreateDirectoryExA
{
    struct qemu_syscall super;
    uint64_t template;
    uint64_t path;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateDirectoryExA(LPCSTR template, LPCSTR path, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateDirectoryExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIRECTORYEXA);
    call.template = (ULONG_PTR)template;
    call.path = (ULONG_PTR)path;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateDirectoryExA(struct qemu_syscall *call)
{
    struct qemu_CreateDirectoryExA *c = (struct qemu_CreateDirectoryExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateDirectoryExA(QEMU_G2H(c->template), QEMU_G2H(c->path), QEMU_G2H(c->sa));
}

#endif

struct qemu_CreateDirectoryExW
{
    struct qemu_syscall super;
    uint64_t template;
    uint64_t path;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateDirectoryExW(LPCWSTR template, LPCWSTR path, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateDirectoryExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDIRECTORYEXW);
    call.template = (ULONG_PTR)template;
    call.path = (ULONG_PTR)path;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateDirectoryExW(struct qemu_syscall *call)
{
    struct qemu_CreateDirectoryExW *c = (struct qemu_CreateDirectoryExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateDirectoryExW(QEMU_G2H(c->template), QEMU_G2H(c->path), QEMU_G2H(c->sa));
}

#endif

struct qemu_RemoveDirectoryW
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RemoveDirectoryW(LPCWSTR path)
{
    struct qemu_RemoveDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEDIRECTORYW);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveDirectoryW(struct qemu_syscall *call)
{
    struct qemu_RemoveDirectoryW *c = (struct qemu_RemoveDirectoryW *)call;
    WINE_TRACE("\n");
    c->super.iret = RemoveDirectoryW(QEMU_G2H(c->path));
}

#endif

struct qemu_RemoveDirectoryA
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RemoveDirectoryA(LPCSTR path)
{
    struct qemu_RemoveDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEDIRECTORYA);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveDirectoryA(struct qemu_syscall *call)
{
    struct qemu_RemoveDirectoryA *c = (struct qemu_RemoveDirectoryA *)call;
    WINE_TRACE("\n");
    c->super.iret = RemoveDirectoryA(QEMU_G2H(c->path));
}

#endif

struct qemu_GetCurrentDirectoryW
{
    struct qemu_syscall super;
    uint64_t buflen;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCurrentDirectoryW(DWORD buflen, LPWSTR buf)
{
    struct qemu_GetCurrentDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTDIRECTORYW);
    call.buflen = buflen;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetCurrentDirectoryW *c = (struct qemu_GetCurrentDirectoryW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCurrentDirectoryW(c->buflen, QEMU_G2H(c->buf));
}

#endif

struct qemu_GetCurrentDirectoryA
{
    struct qemu_syscall super;
    uint64_t buflen;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCurrentDirectoryA(DWORD buflen, LPSTR buf)
{
    struct qemu_GetCurrentDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTDIRECTORYA);
    call.buflen = buflen;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetCurrentDirectoryA *c = (struct qemu_GetCurrentDirectoryA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCurrentDirectoryA(c->buflen, QEMU_G2H(c->buf));
}

#endif

struct qemu_SetCurrentDirectoryW
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCurrentDirectoryW(LPCWSTR dir)
{
    struct qemu_SetCurrentDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCURRENTDIRECTORYW);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCurrentDirectoryW(struct qemu_syscall *call)
{
    struct qemu_SetCurrentDirectoryW *c = (struct qemu_SetCurrentDirectoryW *)call;
    WINE_TRACE("\n");
    c->super.iret = SetCurrentDirectoryW(QEMU_G2H(c->dir));
}

#endif

struct qemu_SetCurrentDirectoryA
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCurrentDirectoryA(LPCSTR dir)
{
    struct qemu_SetCurrentDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCURRENTDIRECTORYA);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCurrentDirectoryA(struct qemu_syscall *call)
{
    struct qemu_SetCurrentDirectoryA *c = (struct qemu_SetCurrentDirectoryA *)call;
    WINE_TRACE("\n");
    c->super.iret = SetCurrentDirectoryA(QEMU_G2H(c->dir));
}

#endif

struct qemu_GetWindowsDirectoryW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetWindowsDirectoryW(LPWSTR path, UINT count)
{
    struct qemu_GetWindowsDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWSDIRECTORYW);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowsDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetWindowsDirectoryW *c = (struct qemu_GetWindowsDirectoryW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowsDirectoryW(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetWindowsDirectoryA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetWindowsDirectoryA(LPSTR path, UINT count)
{
    struct qemu_GetWindowsDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWSDIRECTORYA);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowsDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetWindowsDirectoryA *c = (struct qemu_GetWindowsDirectoryA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowsDirectoryA(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetSystemWindowsDirectoryA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemWindowsDirectoryA(LPSTR path, UINT count)
{
    struct qemu_GetSystemWindowsDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMWINDOWSDIRECTORYA);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemWindowsDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetSystemWindowsDirectoryA *c = (struct qemu_GetSystemWindowsDirectoryA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemWindowsDirectoryA(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetSystemWindowsDirectoryW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemWindowsDirectoryW(LPWSTR path, UINT count)
{
    struct qemu_GetSystemWindowsDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMWINDOWSDIRECTORYW);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemWindowsDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetSystemWindowsDirectoryW *c = (struct qemu_GetSystemWindowsDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemWindowsDirectoryW(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetSystemDirectoryW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemDirectoryW(LPWSTR path, UINT count)
{
    struct qemu_GetSystemDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDIRECTORYW);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetSystemDirectoryW *c = (struct qemu_GetSystemDirectoryW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemDirectoryW(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetSystemDirectoryA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemDirectoryA(LPSTR path, UINT count)
{
    struct qemu_GetSystemDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDIRECTORYA);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetSystemDirectoryA *c = (struct qemu_GetSystemDirectoryA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemDirectoryA(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetSystemWow64DirectoryW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemWow64DirectoryW(LPWSTR path, UINT count)
{
    struct qemu_GetSystemWow64DirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMWOW64DIRECTORYW);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemWow64DirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetSystemWow64DirectoryW *c = (struct qemu_GetSystemWow64DirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemWow64DirectoryW(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_GetSystemWow64DirectoryA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemWow64DirectoryA(LPSTR path, UINT count)
{
    struct qemu_GetSystemWow64DirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMWOW64DIRECTORYA);
    call.path = (ULONG_PTR)path;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemWow64DirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetSystemWow64DirectoryA *c = (struct qemu_GetSystemWow64DirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemWow64DirectoryA(QEMU_G2H(c->path), c->count);
}

#endif

struct qemu_Wow64EnableWow64FsRedirection
{
    struct qemu_syscall super;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI Wow64EnableWow64FsRedirection(BOOLEAN enable)
{
    struct qemu_Wow64EnableWow64FsRedirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WOW64ENABLEWOW64FSREDIRECTION);
    call.enable = enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Wow64EnableWow64FsRedirection(struct qemu_syscall *call)
{
    struct qemu_Wow64EnableWow64FsRedirection *c = (struct qemu_Wow64EnableWow64FsRedirection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Wow64EnableWow64FsRedirection(c->enable);
}

#endif

struct qemu_Wow64DisableWow64FsRedirection
{
    struct qemu_syscall super;
    uint64_t old_value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Wow64DisableWow64FsRedirection(PVOID *old_value)
{
    struct qemu_Wow64DisableWow64FsRedirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WOW64DISABLEWOW64FSREDIRECTION);
    call.old_value = (ULONG_PTR)old_value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Wow64DisableWow64FsRedirection(struct qemu_syscall *call)
{
    struct qemu_Wow64DisableWow64FsRedirection *c = (struct qemu_Wow64DisableWow64FsRedirection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Wow64DisableWow64FsRedirection(QEMU_G2H(c->old_value));
}

#endif

struct qemu_Wow64RevertWow64FsRedirection
{
    struct qemu_syscall super;
    uint64_t old_value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Wow64RevertWow64FsRedirection(PVOID old_value)
{
    struct qemu_Wow64RevertWow64FsRedirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WOW64REVERTWOW64FSREDIRECTION);
    call.old_value = (ULONG_PTR)old_value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Wow64RevertWow64FsRedirection(struct qemu_syscall *call)
{
    struct qemu_Wow64RevertWow64FsRedirection *c = (struct qemu_Wow64RevertWow64FsRedirection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Wow64RevertWow64FsRedirection(QEMU_G2H(c->old_value));
}

#endif

struct qemu_NeedCurrentDirectoryForExePathW
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI NeedCurrentDirectoryForExePathW(LPCWSTR name)
{
    struct qemu_NeedCurrentDirectoryForExePathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NEEDCURRENTDIRECTORYFOREXEPATHW);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NeedCurrentDirectoryForExePathW(struct qemu_syscall *call)
{
    struct qemu_NeedCurrentDirectoryForExePathW *c = (struct qemu_NeedCurrentDirectoryForExePathW *)call;
    WINE_TRACE("\n");
    c->super.iret = NeedCurrentDirectoryForExePathW(QEMU_G2H(c->name));
}

#endif

struct qemu_NeedCurrentDirectoryForExePathA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI NeedCurrentDirectoryForExePathA(LPCSTR name)
{
    struct qemu_NeedCurrentDirectoryForExePathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NEEDCURRENTDIRECTORYFOREXEPATHA);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NeedCurrentDirectoryForExePathA(struct qemu_syscall *call)
{
    struct qemu_NeedCurrentDirectoryForExePathA *c = (struct qemu_NeedCurrentDirectoryForExePathA *)call;
    WINE_TRACE("\n");
    c->super.iret = NeedCurrentDirectoryForExePathA(QEMU_G2H(c->name));
}

#endif

struct qemu_CreateSymbolicLinkW
{
    struct qemu_syscall super;
    uint64_t link;
    uint64_t target;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI CreateSymbolicLinkW(LPCWSTR link, LPCWSTR target, DWORD flags)
{
    struct qemu_CreateSymbolicLinkW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESYMBOLICLINKW);
    call.link = (ULONG_PTR)link;
    call.target = (ULONG_PTR)target;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateSymbolicLinkW(struct qemu_syscall *call)
{
    struct qemu_CreateSymbolicLinkW *c = (struct qemu_CreateSymbolicLinkW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateSymbolicLinkW(QEMU_G2H(c->link), QEMU_G2H(c->target), c->flags);
}

#endif

struct qemu_CreateSymbolicLinkA
{
    struct qemu_syscall super;
    uint64_t link;
    uint64_t target;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI CreateSymbolicLinkA(LPCSTR link, LPCSTR target, DWORD flags)
{
    struct qemu_CreateSymbolicLinkA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESYMBOLICLINKA);
    call.link = (ULONG_PTR)link;
    call.target = (ULONG_PTR)target;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateSymbolicLinkA(struct qemu_syscall *call)
{
    struct qemu_CreateSymbolicLinkA *c = (struct qemu_CreateSymbolicLinkA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateSymbolicLinkA(QEMU_G2H(c->link), QEMU_G2H(c->target), c->flags);
}

#endif

struct qemu_CreateHardLinkTransactedA
{
    struct qemu_syscall super;
    uint64_t link;
    uint64_t target;
    uint64_t sa;
    uint64_t transaction;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateHardLinkTransactedA(LPCSTR link, LPCSTR target, LPSECURITY_ATTRIBUTES sa, HANDLE transaction)
{
    struct qemu_CreateHardLinkTransactedA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEHARDLINKTRANSACTEDA);
    call.link = (ULONG_PTR)link;
    call.target = (ULONG_PTR)target;
    call.sa = (ULONG_PTR)sa;
    call.transaction = (ULONG_PTR)transaction;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CreateHardLinkTransactedA to Wine headers? */
extern BOOL WINAPI CreateHardLinkTransactedA(LPCSTR link, LPCSTR target, LPSECURITY_ATTRIBUTES sa, HANDLE transaction);
void qemu_CreateHardLinkTransactedA(struct qemu_syscall *call)
{
    struct qemu_CreateHardLinkTransactedA *c = (struct qemu_CreateHardLinkTransactedA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateHardLinkTransactedA(QEMU_G2H(c->link), QEMU_G2H(c->target), QEMU_G2H(c->sa), QEMU_G2H(c->transaction));
}

#endif

struct qemu_CreateHardLinkTransactedW
{
    struct qemu_syscall super;
    uint64_t link;
    uint64_t target;
    uint64_t sa;
    uint64_t transaction;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateHardLinkTransactedW(LPCWSTR link, LPCWSTR target, LPSECURITY_ATTRIBUTES sa, HANDLE transaction)
{
    struct qemu_CreateHardLinkTransactedW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEHARDLINKTRANSACTEDW);
    call.link = (ULONG_PTR)link;
    call.target = (ULONG_PTR)target;
    call.sa = (ULONG_PTR)sa;
    call.transaction = (ULONG_PTR)transaction;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CreateHardLinkTransactedW to Wine headers? */
extern BOOL WINAPI CreateHardLinkTransactedW(LPCWSTR link, LPCWSTR target, LPSECURITY_ATTRIBUTES sa, HANDLE transaction);
void qemu_CreateHardLinkTransactedW(struct qemu_syscall *call)
{
    struct qemu_CreateHardLinkTransactedW *c = (struct qemu_CreateHardLinkTransactedW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateHardLinkTransactedW(QEMU_G2H(c->link), QEMU_G2H(c->target), QEMU_G2H(c->sa), QEMU_G2H(c->transaction));
}

#endif

struct qemu_CheckNameLegalDOS8Dot3A
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t oemname;
    uint64_t oemname_len;
    uint64_t contains_spaces;
    uint64_t is_legal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CheckNameLegalDOS8Dot3A(const char *name, char *oemname, DWORD oemname_len, BOOL *contains_spaces, BOOL *is_legal)
{
    struct qemu_CheckNameLegalDOS8Dot3A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKNAMELEGALDOS8DOT3A);
    call.name = (ULONG_PTR)name;
    call.oemname = (ULONG_PTR)oemname;
    call.oemname_len = oemname_len;
    call.contains_spaces = (ULONG_PTR)contains_spaces;
    call.is_legal = (ULONG_PTR)is_legal;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckNameLegalDOS8Dot3A(struct qemu_syscall *call)
{
    struct qemu_CheckNameLegalDOS8Dot3A *c = (struct qemu_CheckNameLegalDOS8Dot3A *)call;
    WINE_TRACE("\n");
    c->super.iret = CheckNameLegalDOS8Dot3A(QEMU_G2H(c->name), QEMU_G2H(c->oemname), c->oemname_len, QEMU_G2H(c->contains_spaces), QEMU_G2H(c->is_legal));
}

#endif

struct qemu_CheckNameLegalDOS8Dot3W
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t oemname;
    uint64_t oemname_len;
    uint64_t contains_spaces_ret;
    uint64_t is_legal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CheckNameLegalDOS8Dot3W(const WCHAR *name, char *oemname, DWORD oemname_len, BOOL *contains_spaces_ret, BOOL *is_legal)
{
    struct qemu_CheckNameLegalDOS8Dot3W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKNAMELEGALDOS8DOT3W);
    call.name = (ULONG_PTR)name;
    call.oemname = (ULONG_PTR)oemname;
    call.oemname_len = oemname_len;
    call.contains_spaces_ret = (ULONG_PTR)contains_spaces_ret;
    call.is_legal = (ULONG_PTR)is_legal;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckNameLegalDOS8Dot3W(struct qemu_syscall *call)
{
    struct qemu_CheckNameLegalDOS8Dot3W *c = (struct qemu_CheckNameLegalDOS8Dot3W *)call;
    WINE_TRACE("\n");
    c->super.iret = CheckNameLegalDOS8Dot3W(QEMU_G2H(c->name), QEMU_G2H(c->oemname), c->oemname_len, QEMU_G2H(c->contains_spaces_ret), QEMU_G2H(c->is_legal));
}

#endif

struct qemu_SetSearchPathMode
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSearchPathMode(DWORD flags)
{
    struct qemu_SetSearchPathMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSEARCHPATHMODE);
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetSearchPathMode to Wine headers? */
extern BOOL WINAPI SetSearchPathMode(DWORD flags);
void qemu_SetSearchPathMode(struct qemu_syscall *call)
{
    struct qemu_SetSearchPathMode *c = (struct qemu_SetSearchPathMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetSearchPathMode(c->flags);
}

#endif

struct qemu_SetDefaultDllDirectories
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDefaultDllDirectories(DWORD flags)
{
    struct qemu_SetDefaultDllDirectories call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEFAULTDLLDIRECTORIES);
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetDefaultDllDirectories to Wine headers? */
extern BOOL WINAPI SetDefaultDllDirectories(DWORD flags);
void qemu_SetDefaultDllDirectories(struct qemu_syscall *call)
{
    struct qemu_SetDefaultDllDirectories *c = (struct qemu_SetDefaultDllDirectories *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDefaultDllDirectories(c->flags);
}

#endif

