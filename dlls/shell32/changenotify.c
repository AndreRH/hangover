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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_SHChangeNotifyRegister
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t fSources;
    uint64_t wEventMask;
    uint64_t uMsg;
    uint64_t cItems;
    uint64_t lpItems;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI SHChangeNotifyRegister(HWND hwnd, int fSources, LONG wEventMask, UINT uMsg, int cItems, const SHChangeNotifyEntry *lpItems)
{
    struct qemu_SHChangeNotifyRegister call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCHANGENOTIFYREGISTER);
    call.hwnd = (ULONG_PTR)hwnd;
    call.fSources = fSources;
    call.wEventMask = wEventMask;
    call.uMsg = uMsg;
    call.cItems = cItems;
    call.lpItems = (ULONG_PTR)lpItems;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHChangeNotifyRegister(struct qemu_syscall *call)
{
    struct qemu_SHChangeNotifyRegister *c = (struct qemu_SHChangeNotifyRegister *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHChangeNotifyRegister(QEMU_G2H(c->hwnd), c->fSources, c->wEventMask, c->uMsg, c->cItems, QEMU_G2H(c->lpItems));
}

#endif

struct qemu_SHChangeNotifyDeregister
{
    struct qemu_syscall super;
    uint64_t hNotify;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHChangeNotifyDeregister(ULONG hNotify)
{
    struct qemu_SHChangeNotifyDeregister call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCHANGENOTIFYDEREGISTER);
    call.hNotify = hNotify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHChangeNotifyDeregister(struct qemu_syscall *call)
{
    struct qemu_SHChangeNotifyDeregister *c = (struct qemu_SHChangeNotifyDeregister *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHChangeNotifyDeregister(c->hNotify);
}

#endif

struct qemu_SHChangeNotifyUpdateEntryList
{
    struct qemu_syscall super;
    uint64_t unknown1;
    uint64_t unknown2;
    uint64_t unknown3;
    uint64_t unknown4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHChangeNotifyUpdateEntryList(DWORD unknown1, DWORD unknown2, DWORD unknown3, DWORD unknown4)
{
    struct qemu_SHChangeNotifyUpdateEntryList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCHANGENOTIFYUPDATEENTRYLIST);
    call.unknown1 = unknown1;
    call.unknown2 = unknown2;
    call.unknown3 = unknown3;
    call.unknown4 = unknown4;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHChangeNotifyUpdateEntryList to Wine headers? */
extern BOOL WINAPI SHChangeNotifyUpdateEntryList(DWORD unknown1, DWORD unknown2, DWORD unknown3, DWORD unknown4);
void qemu_SHChangeNotifyUpdateEntryList(struct qemu_syscall *call)
{
    struct qemu_SHChangeNotifyUpdateEntryList *c = (struct qemu_SHChangeNotifyUpdateEntryList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHChangeNotifyUpdateEntryList(c->unknown1, c->unknown2, c->unknown3, c->unknown4);
}

#endif

struct qemu_SHChangeNotify
{
    struct qemu_syscall super;
    uint64_t wEventId;
    uint64_t uFlags;
    uint64_t dwItem1;
    uint64_t dwItem2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHChangeNotify(LONG wEventId, UINT uFlags, LPCVOID dwItem1, LPCVOID dwItem2)
{
    struct qemu_SHChangeNotify call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCHANGENOTIFY);
    call.wEventId = wEventId;
    call.uFlags = uFlags;
    call.dwItem1 = (ULONG_PTR)dwItem1;
    call.dwItem2 = (ULONG_PTR)dwItem2;

    qemu_syscall(&call.super);
}

#else

void qemu_SHChangeNotify(struct qemu_syscall *call)
{
    struct qemu_SHChangeNotify *c = (struct qemu_SHChangeNotify *)call;
    WINE_FIXME("Unverified!\n");
    SHChangeNotify(c->wEventId, c->uFlags, QEMU_G2H(c->dwItem1), QEMU_G2H(c->dwItem2));
}

#endif

struct qemu_NTSHChangeNotifyRegister
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t events1;
    uint64_t events2;
    uint64_t msg;
    uint64_t count;
    uint64_t idlist;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NTSHChangeNotifyRegister(HWND hwnd, LONG events1, LONG events2, DWORD msg, int count, SHChangeNotifyEntry *idlist)
{
    struct qemu_NTSHChangeNotifyRegister call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSHCHANGENOTIFYREGISTER);
    call.hwnd = (ULONG_PTR)hwnd;
    call.events1 = events1;
    call.events2 = events2;
    call.msg = msg;
    call.count = count;
    call.idlist = (ULONG_PTR)idlist;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NTSHChangeNotifyRegister to Wine headers? */
extern DWORD WINAPI NTSHChangeNotifyRegister(HWND hwnd, LONG events1, LONG events2, DWORD msg, int count, SHChangeNotifyEntry *idlist);
void qemu_NTSHChangeNotifyRegister(struct qemu_syscall *call)
{
    struct qemu_NTSHChangeNotifyRegister *c = (struct qemu_NTSHChangeNotifyRegister *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NTSHChangeNotifyRegister(QEMU_G2H(c->hwnd), c->events1, c->events2, c->msg, c->count, QEMU_G2H(c->idlist));
}

#endif

struct qemu_SHChangeNotification_Lock
{
    struct qemu_syscall super;
    uint64_t hChange;
    uint64_t dwProcessId;
    uint64_t lppidls;
    uint64_t lpwEventId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI SHChangeNotification_Lock(HANDLE hChange, DWORD dwProcessId, LPITEMIDLIST **lppidls, LPLONG lpwEventId)
{
    struct qemu_SHChangeNotification_Lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCHANGENOTIFICATION_LOCK);
    call.hChange = (ULONG_PTR)hChange;
    call.dwProcessId = dwProcessId;
    call.lppidls = (ULONG_PTR)lppidls;
    call.lpwEventId = (ULONG_PTR)lpwEventId;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_SHChangeNotification_Lock(struct qemu_syscall *call)
{
    struct qemu_SHChangeNotification_Lock *c = (struct qemu_SHChangeNotification_Lock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SHChangeNotification_Lock(QEMU_G2H(c->hChange), c->dwProcessId, QEMU_G2H(c->lppidls), QEMU_G2H(c->lpwEventId));
}

#endif

struct qemu_SHChangeNotification_Unlock
{
    struct qemu_syscall super;
    uint64_t hLock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHChangeNotification_Unlock (HANDLE hLock)
{
    struct qemu_SHChangeNotification_Unlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCHANGENOTIFICATION_UNLOCK);
    call.hLock = (ULONG_PTR)hLock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHChangeNotification_Unlock(struct qemu_syscall *call)
{
    struct qemu_SHChangeNotification_Unlock *c = (struct qemu_SHChangeNotification_Unlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHChangeNotification_Unlock(QEMU_G2H(c->hLock));
}

#endif

struct qemu_NTSHChangeNotifyDeregister
{
    struct qemu_syscall super;
    uint64_t x1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NTSHChangeNotifyDeregister(ULONG x1)
{
    struct qemu_NTSHChangeNotifyDeregister call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSHCHANGENOTIFYDEREGISTER);
    call.x1 = x1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NTSHChangeNotifyDeregister to Wine headers? */
extern DWORD WINAPI NTSHChangeNotifyDeregister(ULONG x1);
void qemu_NTSHChangeNotifyDeregister(struct qemu_syscall *call)
{
    struct qemu_NTSHChangeNotifyDeregister *c = (struct qemu_NTSHChangeNotifyDeregister *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NTSHChangeNotifyDeregister(c->x1);
}

#endif

