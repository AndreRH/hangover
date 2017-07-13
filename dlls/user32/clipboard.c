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
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_RegisterClipboardFormatW
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI RegisterClipboardFormatW(LPCWSTR name)
{
    struct qemu_RegisterClipboardFormatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLIPBOARDFORMATW);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterClipboardFormatW(struct qemu_syscall *call)
{
    struct qemu_RegisterClipboardFormatW *c = (struct qemu_RegisterClipboardFormatW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterClipboardFormatW(QEMU_G2H(c->name));
}

#endif

struct qemu_RegisterClipboardFormatA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI RegisterClipboardFormatA(LPCSTR name)
{
    struct qemu_RegisterClipboardFormatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLIPBOARDFORMATA);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterClipboardFormatA(struct qemu_syscall *call)
{
    struct qemu_RegisterClipboardFormatA *c = (struct qemu_RegisterClipboardFormatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterClipboardFormatA(QEMU_G2H(c->name));
}

#endif

struct qemu_GetClipboardFormatNameW
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t buffer;
    uint64_t maxlen;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetClipboardFormatNameW(UINT format, LPWSTR buffer, INT maxlen)
{
    struct qemu_GetClipboardFormatNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOARDFORMATNAMEW);
    call.format = (uint64_t)format;
    call.buffer = (uint64_t)buffer;
    call.maxlen = (uint64_t)maxlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClipboardFormatNameW(struct qemu_syscall *call)
{
    struct qemu_GetClipboardFormatNameW *c = (struct qemu_GetClipboardFormatNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClipboardFormatNameW(c->format, QEMU_G2H(c->buffer), c->maxlen);
}

#endif

struct qemu_GetClipboardFormatNameA
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t buffer;
    uint64_t maxlen;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetClipboardFormatNameA(UINT format, LPSTR buffer, INT maxlen)
{
    struct qemu_GetClipboardFormatNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOARDFORMATNAMEA);
    call.format = (uint64_t)format;
    call.buffer = (uint64_t)buffer;
    call.maxlen = (uint64_t)maxlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClipboardFormatNameA(struct qemu_syscall *call)
{
    struct qemu_GetClipboardFormatNameA *c = (struct qemu_GetClipboardFormatNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClipboardFormatNameA(c->format, QEMU_G2H(c->buffer), c->maxlen);
}

#endif

struct qemu_OpenClipboard
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OpenClipboard(HWND hwnd)
{
    struct qemu_OpenClipboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENCLIPBOARD);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenClipboard(struct qemu_syscall *call)
{
    struct qemu_OpenClipboard *c = (struct qemu_OpenClipboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenClipboard(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_CloseClipboard
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CloseClipboard(void)
{
    struct qemu_CloseClipboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSECLIPBOARD);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseClipboard(struct qemu_syscall *call)
{
    struct qemu_CloseClipboard *c = (struct qemu_CloseClipboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseClipboard();
}

#endif

struct qemu_EmptyClipboard
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EmptyClipboard(void)
{
    struct qemu_EmptyClipboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EMPTYCLIPBOARD);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EmptyClipboard(struct qemu_syscall *call)
{
    struct qemu_EmptyClipboard *c = (struct qemu_EmptyClipboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EmptyClipboard();
}

#endif

struct qemu_GetClipboardOwner
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetClipboardOwner(void)
{
    struct qemu_GetClipboardOwner call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOARDOWNER);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetClipboardOwner(struct qemu_syscall *call)
{
    struct qemu_GetClipboardOwner *c = (struct qemu_GetClipboardOwner *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetClipboardOwner();
}

#endif

struct qemu_GetOpenClipboardWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetOpenClipboardWindow(void)
{
    struct qemu_GetOpenClipboardWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOPENCLIPBOARDWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetOpenClipboardWindow(struct qemu_syscall *call)
{
    struct qemu_GetOpenClipboardWindow *c = (struct qemu_GetOpenClipboardWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetOpenClipboardWindow();
}

#endif

struct qemu_SetClipboardViewer
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetClipboardViewer(HWND hwnd)
{
    struct qemu_SetClipboardViewer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLIPBOARDVIEWER);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_SetClipboardViewer(struct qemu_syscall *call)
{
    struct qemu_SetClipboardViewer *c = (struct qemu_SetClipboardViewer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetClipboardViewer(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetClipboardViewer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetClipboardViewer(void)
{
    struct qemu_GetClipboardViewer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOARDVIEWER);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetClipboardViewer(struct qemu_syscall *call)
{
    struct qemu_GetClipboardViewer *c = (struct qemu_GetClipboardViewer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetClipboardViewer();
}

#endif

struct qemu_ChangeClipboardChain
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t next;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ChangeClipboardChain(HWND hwnd, HWND next)
{
    struct qemu_ChangeClipboardChain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGECLIPBOARDCHAIN);
    call.hwnd = (uint64_t)hwnd;
    call.next = (uint64_t)next;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeClipboardChain(struct qemu_syscall *call)
{
    struct qemu_ChangeClipboardChain *c = (struct qemu_ChangeClipboardChain *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeClipboardChain(QEMU_G2H(c->hwnd), QEMU_G2H(c->next));
}

#endif

struct qemu_SetClipboardData
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HANDLE WINAPI SetClipboardData(UINT format, HANDLE data)
{
    struct qemu_SetClipboardData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLIPBOARDDATA);
    call.format = (uint64_t)format;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_SetClipboardData(struct qemu_syscall *call)
{
    struct qemu_SetClipboardData *c = (struct qemu_SetClipboardData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetClipboardData(c->format, QEMU_G2H(c->data));
}

#endif

struct qemu_CountClipboardFormats
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI CountClipboardFormats(void)
{
    struct qemu_CountClipboardFormats call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COUNTCLIPBOARDFORMATS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CountClipboardFormats(struct qemu_syscall *call)
{
    struct qemu_CountClipboardFormats *c = (struct qemu_CountClipboardFormats *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CountClipboardFormats();
}

#endif

struct qemu_EnumClipboardFormats
{
    struct qemu_syscall super;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI EnumClipboardFormats(UINT format)
{
    struct qemu_EnumClipboardFormats call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCLIPBOARDFORMATS);
    call.format = (uint64_t)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumClipboardFormats(struct qemu_syscall *call)
{
    struct qemu_EnumClipboardFormats *c = (struct qemu_EnumClipboardFormats *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumClipboardFormats(c->format);
}

#endif

struct qemu_IsClipboardFormatAvailable
{
    struct qemu_syscall super;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsClipboardFormatAvailable(UINT format)
{
    struct qemu_IsClipboardFormatAvailable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCLIPBOARDFORMATAVAILABLE);
    call.format = (uint64_t)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsClipboardFormatAvailable(struct qemu_syscall *call)
{
    struct qemu_IsClipboardFormatAvailable *c = (struct qemu_IsClipboardFormatAvailable *)call;
    WINE_TRACE("\n");
    c->super.iret = IsClipboardFormatAvailable(c->format);
}

#endif

struct qemu_GetUpdatedClipboardFormats
{
    struct qemu_syscall super;
    uint64_t formats;
    uint64_t size;
    uint64_t out_size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetUpdatedClipboardFormats(UINT *formats, UINT size, UINT *out_size)
{
    struct qemu_GetUpdatedClipboardFormats call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUPDATEDCLIPBOARDFORMATS);
    call.formats = (uint64_t)formats;
    call.size = (uint64_t)size;
    call.out_size = (uint64_t)out_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUpdatedClipboardFormats(struct qemu_syscall *call)
{
    struct qemu_GetUpdatedClipboardFormats *c = (struct qemu_GetUpdatedClipboardFormats *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUpdatedClipboardFormats(QEMU_G2H(c->formats), c->size, QEMU_G2H(c->out_size));
}

#endif

struct qemu_GetClipboardData
{
    struct qemu_syscall super;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HANDLE WINAPI GetClipboardData(UINT format)
{
    struct qemu_GetClipboardData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOARDDATA);
    call.format = (uint64_t)format;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_GetClipboardData(struct qemu_syscall *call)
{
    struct qemu_GetClipboardData *c = (struct qemu_GetClipboardData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetClipboardData(c->format);
}

#endif

struct qemu_GetPriorityClipboardFormat
{
    struct qemu_syscall super;
    uint64_t list;
    uint64_t nCount;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetPriorityClipboardFormat(UINT *list, INT nCount)
{
    struct qemu_GetPriorityClipboardFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIORITYCLIPBOARDFORMAT);
    call.list = (uint64_t)list;
    call.nCount = (uint64_t)nCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPriorityClipboardFormat(struct qemu_syscall *call)
{
    struct qemu_GetPriorityClipboardFormat *c = (struct qemu_GetPriorityClipboardFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPriorityClipboardFormat(QEMU_G2H(c->list), c->nCount);
}

#endif

struct qemu_GetClipboardSequenceNumber
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetClipboardSequenceNumber(VOID)
{
    struct qemu_GetClipboardSequenceNumber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOARDSEQUENCENUMBER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClipboardSequenceNumber(struct qemu_syscall *call)
{
    struct qemu_GetClipboardSequenceNumber *c = (struct qemu_GetClipboardSequenceNumber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClipboardSequenceNumber();
}

#endif

struct qemu_AddClipboardFormatListener
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AddClipboardFormatListener(HWND hwnd)
{
    struct qemu_AddClipboardFormatListener call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDCLIPBOARDFORMATLISTENER);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddClipboardFormatListener(struct qemu_syscall *call)
{
    struct qemu_AddClipboardFormatListener *c = (struct qemu_AddClipboardFormatListener *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddClipboardFormatListener(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_RemoveClipboardFormatListener
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI RemoveClipboardFormatListener(HWND hwnd)
{
    struct qemu_RemoveClipboardFormatListener call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVECLIPBOARDFORMATLISTENER);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveClipboardFormatListener(struct qemu_syscall *call)
{
    struct qemu_RemoveClipboardFormatListener *c = (struct qemu_RemoveClipboardFormatListener *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RemoveClipboardFormatListener(QEMU_G2H(c->hwnd));
}

#endif

