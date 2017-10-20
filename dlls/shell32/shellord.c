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
#include <shtypes.h>
#include <shlobj.h>
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_ParseField
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t nField;
    uint64_t dst;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ParseFieldAW(LPCVOID src, DWORD nField, LPVOID dst, DWORD len)
{
    struct qemu_ParseField call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PARSEFIELD);
    call.src = (ULONG_PTR)src;
    call.nField = (ULONG_PTR)nField;
    call.dst = (ULONG_PTR)dst;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ParseField to Wine headers? */
extern DWORD WINAPI ParseField(LPCVOID src, DWORD nField, LPVOID dst, DWORD len);
void qemu_ParseField(struct qemu_syscall *call)
{
    struct qemu_ParseField *c = (struct qemu_ParseField *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ParseField(QEMU_G2H(c->src), c->nField, QEMU_G2H(c->dst), c->len);
}

#endif

struct qemu_GetFileNameFromBrowse
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t lpstrFile;
    uint64_t nMaxFile;
    uint64_t lpstrInitialDir;
    uint64_t lpstrDefExt;
    uint64_t lpstrFilter;
    uint64_t lpstrTitle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileNameFromBrowseAW(HWND hwndOwner, PWSTR lpstrFile, UINT nMaxFile, PCWSTR lpstrInitialDir, PCWSTR lpstrDefExt, PCWSTR lpstrFilter, PCWSTR lpstrTitle)
{
    struct qemu_GetFileNameFromBrowse call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILENAMEFROMBROWSE);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.lpstrFile = (ULONG_PTR)lpstrFile;
    call.nMaxFile = (ULONG_PTR)nMaxFile;
    call.lpstrInitialDir = (ULONG_PTR)lpstrInitialDir;
    call.lpstrDefExt = (ULONG_PTR)lpstrDefExt;
    call.lpstrFilter = (ULONG_PTR)lpstrFilter;
    call.lpstrTitle = (ULONG_PTR)lpstrTitle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileNameFromBrowse(struct qemu_syscall *call)
{
    struct qemu_GetFileNameFromBrowse *c = (struct qemu_GetFileNameFromBrowse *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileNameFromBrowse(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->lpstrFile), c->nMaxFile, QEMU_G2H(c->lpstrInitialDir), QEMU_G2H(c->lpstrDefExt), QEMU_G2H(c->lpstrFilter), QEMU_G2H(c->lpstrTitle));
}

#endif

struct qemu_SHGetSetSettings
{
    struct qemu_syscall super;
    uint64_t lpss;
    uint64_t dwMask;
    uint64_t bSet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SHGetSetSettings(LPSHELLSTATE lpss, DWORD dwMask, BOOL bSet)
{
    struct qemu_SHGetSetSettings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSETSETTINGS);
    call.lpss = (ULONG_PTR)lpss;
    call.dwMask = (ULONG_PTR)dwMask;
    call.bSet = (ULONG_PTR)bSet;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add SHGetSetSettings to Wine headers? */
extern VOID WINAPI SHGetSetSettings(LPSHELLSTATE lpss, DWORD dwMask, BOOL bSet);
void qemu_SHGetSetSettings(struct qemu_syscall *call)
{
    struct qemu_SHGetSetSettings *c = (struct qemu_SHGetSetSettings *)call;
    WINE_FIXME("Unverified!\n");
    SHGetSetSettings(QEMU_G2H(c->lpss), c->dwMask, c->bSet);
}

#endif

struct qemu_SHGetSettings
{
    struct qemu_syscall super;
    uint64_t lpsfs;
    uint64_t dwMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SHGetSettings(LPSHELLFLAGSTATE lpsfs, DWORD dwMask)
{
    struct qemu_SHGetSettings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSETTINGS);
    call.lpsfs = (ULONG_PTR)lpsfs;
    call.dwMask = (ULONG_PTR)dwMask;

    qemu_syscall(&call.super);
}

#else

void qemu_SHGetSettings(struct qemu_syscall *call)
{
    struct qemu_SHGetSettings *c = (struct qemu_SHGetSettings *)call;
    WINE_FIXME("Unverified!\n");
    SHGetSettings(QEMU_G2H(c->lpsfs), c->dwMask);
}

#endif

struct qemu_SHShellFolderView_Message
{
    struct qemu_syscall super;
    uint64_t hwndCabinet;
    uint64_t uMessage;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI SHShellFolderView_Message(HWND hwndCabinet, UINT uMessage, LPARAM lParam)
{
    struct qemu_SHShellFolderView_Message call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSHELLFOLDERVIEW_MESSAGE);
    call.hwndCabinet = (ULONG_PTR)hwndCabinet;
    call.uMessage = (ULONG_PTR)uMessage;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHShellFolderView_Message(struct qemu_syscall *call)
{
    struct qemu_SHShellFolderView_Message *c = (struct qemu_SHShellFolderView_Message *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHShellFolderView_Message(QEMU_G2H(c->hwndCabinet), c->uMessage, c->lParam);
}

#endif

struct qemu_RegisterShellHook
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t dwType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RegisterShellHook(HWND hWnd, DWORD dwType)
{
    struct qemu_RegisterShellHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSHELLHOOK);
    call.hWnd = (ULONG_PTR)hWnd;
    call.dwType = (ULONG_PTR)dwType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterShellHook to Wine headers? */
extern BOOL WINAPI RegisterShellHook(HWND hWnd, DWORD dwType);
void qemu_RegisterShellHook(struct qemu_syscall *call)
{
    struct qemu_RegisterShellHook *c = (struct qemu_RegisterShellHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterShellHook(QEMU_G2H(c->hWnd), c->dwType);
}

#endif

struct qemu_SHRegisterDragDrop
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pDropTarget;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegisterDragDrop(HWND hWnd, LPDROPTARGET pDropTarget)
{
    struct qemu_SHRegisterDragDrop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGISTERDRAGDROP);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pDropTarget = (ULONG_PTR)pDropTarget;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegisterDragDrop to Wine headers? */
extern HRESULT WINAPI SHRegisterDragDrop(HWND hWnd, LPDROPTARGET pDropTarget);
void qemu_SHRegisterDragDrop(struct qemu_syscall *call)
{
    struct qemu_SHRegisterDragDrop *c = (struct qemu_SHRegisterDragDrop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegisterDragDrop(QEMU_G2H(c->hWnd), QEMU_G2H(c->pDropTarget));
}

#endif

struct qemu_SHRevokeDragDrop
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRevokeDragDrop(HWND hWnd)
{
    struct qemu_SHRevokeDragDrop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREVOKEDRAGDROP);
    call.hWnd = (ULONG_PTR)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRevokeDragDrop to Wine headers? */
extern HRESULT WINAPI SHRevokeDragDrop(HWND hWnd);
void qemu_SHRevokeDragDrop(struct qemu_syscall *call)
{
    struct qemu_SHRevokeDragDrop *c = (struct qemu_SHRevokeDragDrop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRevokeDragDrop(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_SHDoDragDrop
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t lpDataObject;
    uint64_t lpDropSource;
    uint64_t dwOKEffect;
    uint64_t pdwEffect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHDoDragDrop(HWND hWnd, LPDATAOBJECT lpDataObject, LPDROPSOURCE lpDropSource, DWORD dwOKEffect, LPDWORD pdwEffect)
{
    struct qemu_SHDoDragDrop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHDODRAGDROP);
    call.hWnd = (ULONG_PTR)hWnd;
    call.lpDataObject = (ULONG_PTR)lpDataObject;
    call.lpDropSource = (ULONG_PTR)lpDropSource;
    call.dwOKEffect = (ULONG_PTR)dwOKEffect;
    call.pdwEffect = (ULONG_PTR)pdwEffect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHDoDragDrop(struct qemu_syscall *call)
{
    struct qemu_SHDoDragDrop *c = (struct qemu_SHDoDragDrop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHDoDragDrop(QEMU_G2H(c->hWnd), QEMU_G2H(c->lpDataObject), QEMU_G2H(c->lpDropSource), c->dwOKEffect, QEMU_G2H(c->pdwEffect));
}

#endif

struct qemu_ArrangeWindows
{
    struct qemu_syscall super;
    uint64_t hwndParent;
    uint64_t dwReserved;
    uint64_t lpRect;
    uint64_t cKids;
    uint64_t lpKids;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WORD WINAPI ArrangeWindows(HWND hwndParent, DWORD dwReserved, const RECT *lpRect, WORD cKids, const HWND *lpKids)
{
    struct qemu_ArrangeWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ARRANGEWINDOWS);
    call.hwndParent = (ULONG_PTR)hwndParent;
    call.dwReserved = (ULONG_PTR)dwReserved;
    call.lpRect = (ULONG_PTR)lpRect;
    call.cKids = (ULONG_PTR)cKids;
    call.lpKids = (ULONG_PTR)lpKids;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ArrangeWindows to Wine headers? */
extern WORD WINAPI ArrangeWindows(HWND hwndParent, DWORD dwReserved, const RECT *lpRect, WORD cKids, const HWND *lpKids);
void qemu_ArrangeWindows(struct qemu_syscall *call)
{
    struct qemu_ArrangeWindows *c = (struct qemu_ArrangeWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ArrangeWindows(QEMU_G2H(c->hwndParent), c->dwReserved, QEMU_G2H(c->lpRect), c->cKids, QEMU_G2H(c->lpKids));
}

#endif

struct qemu_SignalFileOpen
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SignalFileOpen (PCIDLIST_ABSOLUTE pidl)
{
    struct qemu_SignalFileOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SIGNALFILEOPEN);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SignalFileOpen(struct qemu_syscall *call)
{
    struct qemu_SignalFileOpen *c = (struct qemu_SignalFileOpen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SignalFileOpen(QEMU_G2H(c->pidl));
}

#endif

struct qemu_SHAddToRecentDocs
{
    struct qemu_syscall super;
    uint64_t uFlags;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHAddToRecentDocs (UINT uFlags,LPCVOID pv)
{
    struct qemu_SHAddToRecentDocs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHADDTORECENTDOCS);
    call.uFlags = (ULONG_PTR)uFlags;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);
}

#else

void qemu_SHAddToRecentDocs(struct qemu_syscall *call)
{
    struct qemu_SHAddToRecentDocs *c = (struct qemu_SHAddToRecentDocs *)call;
    WINE_FIXME("Unverified!\n");
    SHAddToRecentDocs(c->uFlags, QEMU_G2H(c->pv));
}

#endif

struct qemu_SHWinHelp
{
    struct qemu_syscall super;
    uint64_t v;
    uint64_t w;
    uint64_t x;
    uint64_t z;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHWinHelp (DWORD v, DWORD w, DWORD x, DWORD z)
{
    struct qemu_SHWinHelp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHWINHELP);
    call.v = (ULONG_PTR)v;
    call.w = (ULONG_PTR)w;
    call.x = (ULONG_PTR)x;
    call.z = (ULONG_PTR)z;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHWinHelp to Wine headers? */
extern HRESULT WINAPI SHWinHelp (DWORD v, DWORD w, DWORD x, DWORD z);
void qemu_SHWinHelp(struct qemu_syscall *call)
{
    struct qemu_SHWinHelp *c = (struct qemu_SHWinHelp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHWinHelp(c->v, c->w, c->x, c->z);
}

#endif

struct qemu_SHRunControlPanel
{
    struct qemu_syscall super;
    uint64_t commandLine;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHRunControlPanel (LPCWSTR commandLine, HWND parent)
{
    struct qemu_SHRunControlPanel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHRUNCONTROLPANEL);
    call.commandLine = (ULONG_PTR)commandLine;
    call.parent = (ULONG_PTR)parent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHRunControlPanel(struct qemu_syscall *call)
{
    struct qemu_SHRunControlPanel *c = (struct qemu_SHRunControlPanel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRunControlPanel(QEMU_G2H(c->commandLine), QEMU_G2H(c->parent));
}

#endif

struct qemu_SHSetInstanceExplorer
{
    struct qemu_syscall super;
    uint64_t lpUnknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SHSetInstanceExplorer (LPUNKNOWN lpUnknown)
{
    struct qemu_SHSetInstanceExplorer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSETINSTANCEEXPLORER);
    call.lpUnknown = (ULONG_PTR)lpUnknown;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add SHSetInstanceExplorer to Wine headers? */
extern VOID WINAPI SHSetInstanceExplorer (LPUNKNOWN lpUnknown);
void qemu_SHSetInstanceExplorer(struct qemu_syscall *call)
{
    struct qemu_SHSetInstanceExplorer *c = (struct qemu_SHSetInstanceExplorer *)call;
    WINE_FIXME("Unverified!\n");
    SHSetInstanceExplorer(QEMU_G2H(c->lpUnknown));
}

#endif

struct qemu_SHGetInstanceExplorer
{
    struct qemu_syscall super;
    uint64_t lpUnknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetInstanceExplorer (IUnknown **lpUnknown)
{
    struct qemu_SHGetInstanceExplorer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETINSTANCEEXPLORER);
    call.lpUnknown = (ULONG_PTR)lpUnknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetInstanceExplorer(struct qemu_syscall *call)
{
    struct qemu_SHGetInstanceExplorer *c = (struct qemu_SHGetInstanceExplorer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetInstanceExplorer(QEMU_G2H(c->lpUnknown));
}

#endif

struct qemu_SHFreeUnusedLibraries
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHFreeUnusedLibraries (void)
{
    struct qemu_SHFreeUnusedLibraries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFREEUNUSEDLIBRARIES);

    qemu_syscall(&call.super);
}

#else

/* TODO: Add SHFreeUnusedLibraries to Wine headers? */
extern void WINAPI SHFreeUnusedLibraries (void);
void qemu_SHFreeUnusedLibraries(struct qemu_syscall *call)
{
    struct qemu_SHFreeUnusedLibraries *c = (struct qemu_SHFreeUnusedLibraries *)call;
    WINE_FIXME("Unverified!\n");
    SHFreeUnusedLibraries();
}

#endif

struct qemu_DAD_AutoScroll
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t samples;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI DAD_AutoScroll(HWND hwnd, AUTO_SCROLL_DATA *samples, const POINT *pt)
{
    struct qemu_DAD_AutoScroll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_AUTOSCROLL);
    call.hwnd = (ULONG_PTR)hwnd;
    call.samples = (ULONG_PTR)samples;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DAD_AutoScroll(struct qemu_syscall *call)
{
    struct qemu_DAD_AutoScroll *c = (struct qemu_DAD_AutoScroll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DAD_AutoScroll(QEMU_G2H(c->hwnd), QEMU_G2H(c->samples), QEMU_G2H(c->pt));
}

#endif

struct qemu_DAD_DragEnter
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DAD_DragEnter(HWND hwnd)
{
    struct qemu_DAD_DragEnter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_DRAGENTER);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DAD_DragEnter to Wine headers? */
extern BOOL WINAPI DAD_DragEnter(HWND hwnd);
void qemu_DAD_DragEnter(struct qemu_syscall *call)
{
    struct qemu_DAD_DragEnter *c = (struct qemu_DAD_DragEnter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DAD_DragEnter(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_DAD_DragEnterEx
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pX, pY;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DAD_DragEnterEx(HWND hwnd, POINT p)
{
    struct qemu_DAD_DragEnterEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_DRAGENTEREX);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pX = p.x;
    call.pY = p.y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DAD_DragEnterEx(struct qemu_syscall *call)
{
    struct qemu_DAD_DragEnterEx *c = (struct qemu_DAD_DragEnterEx *)call;
    POINT p;

    WINE_FIXME("Unverified!\n");
    p.x = c->pX;
    p.y = c->pY;
    c->super.iret = DAD_DragEnterEx(QEMU_G2H(c->hwnd), p);
}

#endif

struct qemu_DAD_DragMove
{
    struct qemu_syscall super;
    uint64_t pX, pY;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DAD_DragMove(POINT p)
{
    struct qemu_DAD_DragMove call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_DRAGMOVE);
    call.pX = p.x;
    call.pY = p.y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DAD_DragMove(struct qemu_syscall *call)
{
    struct qemu_DAD_DragMove *c = (struct qemu_DAD_DragMove *)call;
    POINT p;

    WINE_FIXME("Unverified!\n");
    p.x = c->pX;
    p.y = c->pY;
    c->super.iret = DAD_DragMove(p);
}

#endif

struct qemu_DAD_DragLeave
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DAD_DragLeave(VOID)
{
    struct qemu_DAD_DragLeave call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_DRAGLEAVE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DAD_DragLeave(struct qemu_syscall *call)
{
    struct qemu_DAD_DragLeave *c = (struct qemu_DAD_DragLeave *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DAD_DragLeave();
}

#endif

struct qemu_DAD_SetDragImage
{
    struct qemu_syscall super;
    uint64_t himlTrack;
    uint64_t lppt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DAD_SetDragImage(HIMAGELIST himlTrack, LPPOINT lppt)
{
    struct qemu_DAD_SetDragImage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_SETDRAGIMAGE);
    call.himlTrack = (ULONG_PTR)himlTrack;
    call.lppt = (ULONG_PTR)lppt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DAD_SetDragImage(struct qemu_syscall *call)
{
    struct qemu_DAD_SetDragImage *c = (struct qemu_DAD_SetDragImage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DAD_SetDragImage(QEMU_G2H(c->himlTrack), QEMU_G2H(c->lppt));
}

#endif

struct qemu_DAD_ShowDragImage
{
    struct qemu_syscall super;
    uint64_t bShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DAD_ShowDragImage(BOOL bShow)
{
    struct qemu_DAD_ShowDragImage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DAD_SHOWDRAGIMAGE);
    call.bShow = (ULONG_PTR)bShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DAD_ShowDragImage to Wine headers? */
extern BOOL WINAPI DAD_ShowDragImage(BOOL bShow);
void qemu_DAD_ShowDragImage(struct qemu_syscall *call)
{
    struct qemu_DAD_ShowDragImage *c = (struct qemu_DAD_ShowDragImage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DAD_ShowDragImage(c->bShow);
}

#endif

struct qemu_ReadCabinetState
{
    struct qemu_syscall super;
    uint64_t cs;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadCabinetState(CABINETSTATE *cs, int length)
{
    struct qemu_ReadCabinetState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCABINETSTATE);
    call.cs = (ULONG_PTR)cs;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadCabinetState(struct qemu_syscall *call)
{
    struct qemu_ReadCabinetState *c = (struct qemu_ReadCabinetState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadCabinetState(QEMU_G2H(c->cs), c->length);
}

#endif

struct qemu_WriteCabinetState
{
    struct qemu_syscall super;
    uint64_t cs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteCabinetState(CABINETSTATE *cs)
{
    struct qemu_WriteCabinetState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECABINETSTATE);
    call.cs = (ULONG_PTR)cs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteCabinetState(struct qemu_syscall *call)
{
    struct qemu_WriteCabinetState *c = (struct qemu_WriteCabinetState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteCabinetState(QEMU_G2H(c->cs));
}

#endif

struct qemu_FileIconInit
{
    struct qemu_syscall super;
    uint64_t bFullInit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileIconInit(BOOL bFullInit)
{
    struct qemu_FileIconInit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEICONINIT);
    call.bFullInit = (ULONG_PTR)bFullInit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileIconInit to Wine headers? */
extern BOOL WINAPI FileIconInit(BOOL bFullInit);
void qemu_FileIconInit(struct qemu_syscall *call)
{
    struct qemu_FileIconInit *c = (struct qemu_FileIconInit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileIconInit(c->bFullInit);
}

#endif

struct qemu_IsUserAnAdmin
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsUserAnAdmin(VOID)
{
    struct qemu_IsUserAnAdmin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISUSERANADMIN);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsUserAnAdmin(struct qemu_syscall *call)
{
    struct qemu_IsUserAnAdmin *c = (struct qemu_IsUserAnAdmin *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsUserAnAdmin();
}

#endif

struct qemu_SHAllocShared
{
    struct qemu_syscall super;
    uint64_t lpvData;
    uint64_t dwSize;
    uint64_t dwProcId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI SHAllocShared(LPVOID lpvData, DWORD dwSize, DWORD dwProcId)
{
    struct qemu_SHAllocShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHALLOCSHARED);
    call.lpvData = (ULONG_PTR)lpvData;
    call.dwSize = (ULONG_PTR)dwSize;
    call.dwProcId = (ULONG_PTR)dwProcId;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add SHAllocShared to Wine headers? */
extern HANDLE WINAPI SHAllocShared(LPVOID lpvData, DWORD dwSize, DWORD dwProcId);
void qemu_SHAllocShared(struct qemu_syscall *call)
{
    struct qemu_SHAllocShared *c = (struct qemu_SHAllocShared *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHAllocShared(QEMU_G2H(c->lpvData), c->dwSize, c->dwProcId);
}

#endif

struct qemu_SHLockShared
{
    struct qemu_syscall super;
    uint64_t hShared;
    uint64_t dwProcId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI SHLockShared(HANDLE hShared, DWORD dwProcId)
{
    struct qemu_SHLockShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLOCKSHARED);
    call.hShared = (ULONG_PTR)hShared;
    call.dwProcId = (ULONG_PTR)dwProcId;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add SHLockShared to Wine headers? */
extern LPVOID WINAPI SHLockShared(HANDLE hShared, DWORD dwProcId);
void qemu_SHLockShared(struct qemu_syscall *call)
{
    struct qemu_SHLockShared *c = (struct qemu_SHLockShared *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHLockShared(QEMU_G2H(c->hShared), c->dwProcId);
}

#endif

struct qemu_SHUnlockShared
{
    struct qemu_syscall super;
    uint64_t lpView;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHUnlockShared(LPVOID lpView)
{
    struct qemu_SHUnlockShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUNLOCKSHARED);
    call.lpView = (ULONG_PTR)lpView;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHUnlockShared to Wine headers? */
extern BOOL WINAPI SHUnlockShared(LPVOID lpView);
void qemu_SHUnlockShared(struct qemu_syscall *call)
{
    struct qemu_SHUnlockShared *c = (struct qemu_SHUnlockShared *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHUnlockShared(QEMU_G2H(c->lpView));
}

#endif

struct qemu_SHFreeShared
{
    struct qemu_syscall super;
    uint64_t hShared;
    uint64_t dwProcId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHFreeShared(HANDLE hShared, DWORD dwProcId)
{
    struct qemu_SHFreeShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFREESHARED);
    call.hShared = (ULONG_PTR)hShared;
    call.dwProcId = (ULONG_PTR)dwProcId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHFreeShared to Wine headers? */
extern BOOL WINAPI SHFreeShared(HANDLE hShared, DWORD dwProcId);
void qemu_SHFreeShared(struct qemu_syscall *call)
{
    struct qemu_SHFreeShared *c = (struct qemu_SHFreeShared *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHFreeShared(QEMU_G2H(c->hShared), c->dwProcId);
}

#endif

struct qemu_SetAppStartingCursor
{
    struct qemu_syscall super;
    uint64_t u;
    uint64_t v;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SetAppStartingCursor(HWND u, DWORD v)
{
    struct qemu_SetAppStartingCursor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETAPPSTARTINGCURSOR);
    call.u = (ULONG_PTR)u;
    call.v = (ULONG_PTR)v;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetAppStartingCursor to Wine headers? */
extern HRESULT WINAPI SetAppStartingCursor(HWND u, DWORD v);
void qemu_SetAppStartingCursor(struct qemu_syscall *call)
{
    struct qemu_SetAppStartingCursor *c = (struct qemu_SetAppStartingCursor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetAppStartingCursor(QEMU_G2H(c->u), c->v);
}

#endif

struct qemu_SHLoadOLE
{
    struct qemu_syscall super;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHLoadOLE(LPARAM lParam)
{
    struct qemu_SHLoadOLE call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLOADOLE);
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHLoadOLE(struct qemu_syscall *call)
{
    struct qemu_SHLoadOLE *c = (struct qemu_SHLoadOLE *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHLoadOLE(c->lParam);
}

#endif

struct qemu_DriveType
{
    struct qemu_syscall super;
    uint64_t u;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI DriveType(int u)
{
    struct qemu_DriveType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRIVETYPE);
    call.u = (ULONG_PTR)u;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DriveType(struct qemu_syscall *call)
{
    struct qemu_DriveType *c = (struct qemu_DriveType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DriveType(c->u);
}

#endif

struct qemu_InvalidateDriveType
{
    struct qemu_syscall super;
    uint64_t u;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI InvalidateDriveType(int u)
{
    struct qemu_InvalidateDriveType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INVALIDATEDRIVETYPE);
    call.u = (ULONG_PTR)u;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InvalidateDriveType to Wine headers? */
extern int WINAPI InvalidateDriveType(int u);
void qemu_InvalidateDriveType(struct qemu_syscall *call)
{
    struct qemu_InvalidateDriveType *c = (struct qemu_InvalidateDriveType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InvalidateDriveType(c->u);
}

#endif

struct qemu_SHAbortInvokeCommand
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHAbortInvokeCommand(void)
{
    struct qemu_SHAbortInvokeCommand call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHABORTINVOKECOMMAND);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHAbortInvokeCommand to Wine headers? */
extern HRESULT WINAPI SHAbortInvokeCommand(void);
void qemu_SHAbortInvokeCommand(struct qemu_syscall *call)
{
    struct qemu_SHAbortInvokeCommand *c = (struct qemu_SHAbortInvokeCommand *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAbortInvokeCommand();
}

#endif

struct qemu_SHOutOfMemoryMessageBox
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t lpCaption;
    uint64_t uType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHOutOfMemoryMessageBox(HWND hwndOwner, LPCSTR lpCaption, UINT uType)
{
    struct qemu_SHOutOfMemoryMessageBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOUTOFMEMORYMESSAGEBOX);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.lpCaption = (ULONG_PTR)lpCaption;
    call.uType = (ULONG_PTR)uType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHOutOfMemoryMessageBox to Wine headers? */
extern int WINAPI SHOutOfMemoryMessageBox(HWND hwndOwner, LPCSTR lpCaption, UINT uType);
void qemu_SHOutOfMemoryMessageBox(struct qemu_syscall *call)
{
    struct qemu_SHOutOfMemoryMessageBox *c = (struct qemu_SHOutOfMemoryMessageBox *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHOutOfMemoryMessageBox(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->lpCaption), c->uType);
}

#endif

struct qemu_SHFlushClipboard
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHFlushClipboard(void)
{
    struct qemu_SHFlushClipboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFLUSHCLIPBOARD);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHFlushClipboard to Wine headers? */
extern HRESULT WINAPI SHFlushClipboard(void);
void qemu_SHFlushClipboard(struct qemu_syscall *call)
{
    struct qemu_SHFlushClipboard *c = (struct qemu_SHFlushClipboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHFlushClipboard();
}

#endif

struct qemu_SHWaitForFileToOpen
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t dwFlags;
    uint64_t dwTimeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHWaitForFileToOpen(LPCITEMIDLIST pidl, DWORD dwFlags, DWORD dwTimeout)
{
    struct qemu_SHWaitForFileToOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHWAITFORFILETOOPEN);
    call.pidl = (ULONG_PTR)pidl;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwTimeout = (ULONG_PTR)dwTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHWaitForFileToOpen to Wine headers? */
extern BOOL WINAPI SHWaitForFileToOpen(LPCITEMIDLIST pidl, DWORD dwFlags, DWORD dwTimeout);
void qemu_SHWaitForFileToOpen(struct qemu_syscall *call)
{
    struct qemu_SHWaitForFileToOpen *c = (struct qemu_SHWaitForFileToOpen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHWaitForFileToOpen(QEMU_G2H(c->pidl), c->dwFlags, c->dwTimeout);
}

#endif

struct qemu_RLBuildListOfPaths
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RLBuildListOfPaths (void)
{
    struct qemu_RLBuildListOfPaths call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RLBUILDLISTOFPATHS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RLBuildListOfPaths to Wine headers? */
extern DWORD WINAPI RLBuildListOfPaths (void);
void qemu_RLBuildListOfPaths(struct qemu_syscall *call)
{
    struct qemu_RLBuildListOfPaths *c = (struct qemu_RLBuildListOfPaths *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RLBuildListOfPaths();
}

#endif

struct qemu_SHValidateUNC
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t pszFile;
    uint64_t fConnect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHValidateUNC (HWND hwndOwner, PWSTR pszFile, UINT fConnect)
{
    struct qemu_SHValidateUNC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHVALIDATEUNC);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.pszFile = (ULONG_PTR)pszFile;
    call.fConnect = (ULONG_PTR)fConnect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHValidateUNC to Wine headers? */
extern BOOL WINAPI SHValidateUNC (HWND hwndOwner, PWSTR pszFile, UINT fConnect);
void qemu_SHValidateUNC(struct qemu_syscall *call)
{
    struct qemu_SHValidateUNC *c = (struct qemu_SHValidateUNC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHValidateUNC(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->pszFile), c->fConnect);
}

#endif

struct qemu_DoEnvironmentSubst
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI DoEnvironmentSubstAW(LPSTR x, UINT y)
{
    struct qemu_DoEnvironmentSubst call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOENVIRONMENTSUBST);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DoEnvironmentSubst(struct qemu_syscall *call)
{
    struct qemu_DoEnvironmentSubst *c = (struct qemu_DoEnvironmentSubst *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DoEnvironmentSubst(QEMU_G2H(c->x), c->y);
}

#endif

struct qemu_DoEnvironmentSubstW
{
    struct qemu_syscall super;
    uint64_t pszString;
    uint64_t cchString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DoEnvironmentSubstW(LPWSTR pszString, UINT cchString)
{
    struct qemu_DoEnvironmentSubstW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOENVIRONMENTSUBSTW);
    call.pszString = (ULONG_PTR)pszString;
    call.cchString = cchString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DoEnvironmentSubstW(struct qemu_syscall *call)
{
    struct qemu_DoEnvironmentSubstW *c = (struct qemu_DoEnvironmentSubstW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DoEnvironmentSubstW(QEMU_G2H(c->pszString), c->cchString);
}

#endif

struct qemu_DoEnvironmentSubstA
{
    struct qemu_syscall super;
    uint64_t pszString;
    uint64_t cchString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DoEnvironmentSubstA(LPSTR pszString, UINT cchString)
{
    struct qemu_DoEnvironmentSubstA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOENVIRONMENTSUBSTA);
    call.pszString = (ULONG_PTR)pszString;
    call.cchString = cchString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DoEnvironmentSubstA(struct qemu_syscall *call)
{
    struct qemu_DoEnvironmentSubstA *c = (struct qemu_DoEnvironmentSubstA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DoEnvironmentSubstA(QEMU_G2H(c->pszString), c->cchString);
}

#endif

struct qemu_shell32_243
{
    struct qemu_syscall super;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI shell32_243(DWORD a, DWORD b)
{
    struct qemu_shell32_243 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELL32_243);
    call.a = (ULONG_PTR)a;
    call.b = (ULONG_PTR)b;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shell32_243(struct qemu_syscall *call)
{
    struct qemu_shell32_243 *c = (struct qemu_shell32_243 *)call;
    /* Import this by ordinal. */
    WINE_FIXME("Stub!\n");
    c->super.iret = FALSE;
}

#endif

struct qemu_GUIDFromStringW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GUIDFromStringW(LPCWSTR str, LPGUID guid)
{
    struct qemu_GUIDFromStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GUIDFROMSTRINGW);
    call.str = (ULONG_PTR)str;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GUIDFromStringW to Wine headers? */
extern BOOL WINAPI GUIDFromStringW(LPCWSTR str, LPGUID guid);
void qemu_GUIDFromStringW(struct qemu_syscall *call)
{
    struct qemu_GUIDFromStringW *c = (struct qemu_GUIDFromStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GUIDFromStringW(QEMU_G2H(c->str), QEMU_G2H(c->guid));
}

#endif

struct qemu_SHAddFromPropSheetExtArray
{
    struct qemu_syscall super;
    uint64_t hpsxa;
    uint64_t lpfnAddPage;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SHAddFromPropSheetExtArray(HPSXA hpsxa, LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
    struct qemu_SHAddFromPropSheetExtArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHADDFROMPROPSHEETEXTARRAY);
    call.hpsxa = (ULONG_PTR)hpsxa;
    call.lpfnAddPage = (ULONG_PTR)lpfnAddPage;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHAddFromPropSheetExtArray(struct qemu_syscall *call)
{
    struct qemu_SHAddFromPropSheetExtArray *c = (struct qemu_SHAddFromPropSheetExtArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAddFromPropSheetExtArray(QEMU_G2H(c->hpsxa), QEMU_G2H(c->lpfnAddPage), c->lParam);
}

#endif

struct qemu_SHCreatePropSheetExtArray
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pszSubKey;
    uint64_t max_iface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPSXA WINAPI SHCreatePropSheetExtArray(HKEY hKey, LPCWSTR pszSubKey, UINT max_iface)
{
    struct qemu_SHCreatePropSheetExtArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEPROPSHEETEXTARRAY);
    call.hKey = (ULONG_PTR)hKey;
    call.pszSubKey = (ULONG_PTR)pszSubKey;
    call.max_iface = (ULONG_PTR)max_iface;

    qemu_syscall(&call.super);

    return (HPSXA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SHCreatePropSheetExtArray(struct qemu_syscall *call)
{
    struct qemu_SHCreatePropSheetExtArray *c = (struct qemu_SHCreatePropSheetExtArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHCreatePropSheetExtArray(QEMU_G2H(c->hKey), QEMU_G2H(c->pszSubKey), c->max_iface);
}

#endif

struct qemu_SHCreatePropSheetExtArrayEx
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pszSubKey;
    uint64_t max_iface;
    uint64_t pDataObj;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPSXA WINAPI SHCreatePropSheetExtArrayEx(HKEY hKey, LPCWSTR pszSubKey, UINT max_iface, LPDATAOBJECT pDataObj)
{
    struct qemu_SHCreatePropSheetExtArrayEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEPROPSHEETEXTARRAYEX);
    call.hKey = (ULONG_PTR)hKey;
    call.pszSubKey = (ULONG_PTR)pszSubKey;
    call.max_iface = (ULONG_PTR)max_iface;
    call.pDataObj = (ULONG_PTR)pDataObj;

    qemu_syscall(&call.super);

    return (HPSXA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SHCreatePropSheetExtArrayEx(struct qemu_syscall *call)
{
    struct qemu_SHCreatePropSheetExtArrayEx *c = (struct qemu_SHCreatePropSheetExtArrayEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHCreatePropSheetExtArrayEx(QEMU_G2H(c->hKey), QEMU_G2H(c->pszSubKey), c->max_iface, QEMU_G2H(c->pDataObj));
}

#endif

struct qemu_SHReplaceFromPropSheetExtArray
{
    struct qemu_syscall super;
    uint64_t hpsxa;
    uint64_t uPageID;
    uint64_t lpfnReplaceWith;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SHReplaceFromPropSheetExtArray(HPSXA hpsxa, UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam)
{
    struct qemu_SHReplaceFromPropSheetExtArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREPLACEFROMPROPSHEETEXTARRAY);
    call.hpsxa = (ULONG_PTR)hpsxa;
    call.uPageID = (ULONG_PTR)uPageID;
    call.lpfnReplaceWith = (ULONG_PTR)lpfnReplaceWith;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHReplaceFromPropSheetExtArray(struct qemu_syscall *call)
{
    struct qemu_SHReplaceFromPropSheetExtArray *c = (struct qemu_SHReplaceFromPropSheetExtArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHReplaceFromPropSheetExtArray(QEMU_G2H(c->hpsxa), c->uPageID, QEMU_G2H(c->lpfnReplaceWith), c->lParam);
}

#endif

struct qemu_SHDestroyPropSheetExtArray
{
    struct qemu_syscall super;
    uint64_t hpsxa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHDestroyPropSheetExtArray(HPSXA hpsxa)
{
    struct qemu_SHDestroyPropSheetExtArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHDESTROYPROPSHEETEXTARRAY);
    call.hpsxa = (ULONG_PTR)hpsxa;

    qemu_syscall(&call.super);
}

#else

void qemu_SHDestroyPropSheetExtArray(struct qemu_syscall *call)
{
    struct qemu_SHDestroyPropSheetExtArray *c = (struct qemu_SHDestroyPropSheetExtArray *)call;
    WINE_FIXME("Unverified!\n");
    SHDestroyPropSheetExtArray(QEMU_G2H(c->hpsxa));
}

#endif

struct qemu_CIDLData_CreateFromIDArray
{
    struct qemu_syscall super;
    uint64_t pidlFolder;
    uint64_t cpidlFiles;
    uint64_t lppidlFiles;
    uint64_t ppdataObject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CIDLData_CreateFromIDArray(LPCITEMIDLIST pidlFolder, UINT cpidlFiles, LPCITEMIDLIST *lppidlFiles, LPDATAOBJECT *ppdataObject)
{
    struct qemu_CIDLData_CreateFromIDArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CIDLDATA_CREATEFROMIDARRAY);
    call.pidlFolder = (ULONG_PTR)pidlFolder;
    call.cpidlFiles = (ULONG_PTR)cpidlFiles;
    call.lppidlFiles = (ULONG_PTR)lppidlFiles;
    call.ppdataObject = (ULONG_PTR)ppdataObject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CIDLData_CreateFromIDArray to Wine headers? */
extern HRESULT WINAPI CIDLData_CreateFromIDArray(LPCITEMIDLIST pidlFolder, DWORD cpidlFiles, LPCITEMIDLIST *lppidlFiles, LPDATAOBJECT *ppdataObject);
void qemu_CIDLData_CreateFromIDArray(struct qemu_syscall *call)
{
    struct qemu_CIDLData_CreateFromIDArray *c = (struct qemu_CIDLData_CreateFromIDArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CIDLData_CreateFromIDArray(QEMU_G2H(c->pidlFolder), c->cpidlFiles, QEMU_G2H(c->lppidlFiles), QEMU_G2H(c->ppdataObject));
}

#endif

struct qemu_SHCreateStdEnumFmtEtc
{
    struct qemu_syscall super;
    uint64_t cFormats;
    uint64_t lpFormats;
    uint64_t ppenumFormatetc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateStdEnumFmtEtc(UINT cFormats, const FORMATETC *lpFormats, LPENUMFORMATETC *ppenumFormatetc)
{
    struct qemu_SHCreateStdEnumFmtEtc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESTDENUMFMTETC);
    call.cFormats = (ULONG_PTR)cFormats;
    call.lpFormats = (ULONG_PTR)lpFormats;
    call.ppenumFormatetc = (ULONG_PTR)ppenumFormatetc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateStdEnumFmtEtc(struct qemu_syscall *call)
{
    struct qemu_SHCreateStdEnumFmtEtc *c = (struct qemu_SHCreateStdEnumFmtEtc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateStdEnumFmtEtc(c->cFormats, QEMU_G2H(c->lpFormats), QEMU_G2H(c->ppenumFormatetc));
}

#endif

struct qemu_SHFindFiles
{
    struct qemu_syscall super;
    uint64_t pidlFolder;
    uint64_t pidlSaveFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHFindFiles(LPCITEMIDLIST pidlFolder, LPCITEMIDLIST pidlSaveFile)
{
    struct qemu_SHFindFiles call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFINDFILES);
    call.pidlFolder = (ULONG_PTR)pidlFolder;
    call.pidlSaveFile = (ULONG_PTR)pidlSaveFile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHFindFiles(struct qemu_syscall *call)
{
    struct qemu_SHFindFiles *c = (struct qemu_SHFindFiles *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHFindFiles(QEMU_G2H(c->pidlFolder), QEMU_G2H(c->pidlSaveFile));
}

#endif

struct qemu_SHUpdateImageW
{
    struct qemu_syscall super;
    uint64_t pszHashItem;
    uint64_t iIndex;
    uint64_t uFlags;
    uint64_t iImageIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHUpdateImageW(LPCWSTR pszHashItem, int iIndex, UINT uFlags, int iImageIndex)
{
    struct qemu_SHUpdateImageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUPDATEIMAGEW);
    call.pszHashItem = (ULONG_PTR)pszHashItem;
    call.iIndex = (ULONG_PTR)iIndex;
    call.uFlags = (ULONG_PTR)uFlags;
    call.iImageIndex = (ULONG_PTR)iImageIndex;

    qemu_syscall(&call.super);
}

#else

void qemu_SHUpdateImageW(struct qemu_syscall *call)
{
    struct qemu_SHUpdateImageW *c = (struct qemu_SHUpdateImageW *)call;
    WINE_FIXME("Unverified!\n");
    SHUpdateImageW(QEMU_G2H(c->pszHashItem), c->iIndex, c->uFlags, c->iImageIndex);
}

#endif

struct qemu_SHUpdateImageA
{
    struct qemu_syscall super;
    uint64_t pszHashItem;
    uint64_t iIndex;
    uint64_t uFlags;
    uint64_t iImageIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SHUpdateImageA(LPCSTR pszHashItem, INT iIndex, UINT uFlags, INT iImageIndex)
{
    struct qemu_SHUpdateImageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUPDATEIMAGEA);
    call.pszHashItem = (ULONG_PTR)pszHashItem;
    call.iIndex = (ULONG_PTR)iIndex;
    call.uFlags = (ULONG_PTR)uFlags;
    call.iImageIndex = (ULONG_PTR)iImageIndex;

    qemu_syscall(&call.super);
}

#else

void qemu_SHUpdateImageA(struct qemu_syscall *call)
{
    struct qemu_SHUpdateImageA *c = (struct qemu_SHUpdateImageA *)call;
    WINE_FIXME("Unverified!\n");
    SHUpdateImageA(QEMU_G2H(c->pszHashItem), c->iIndex, c->uFlags, c->iImageIndex);
}

#endif

struct qemu_SHHandleUpdateImage
{
    struct qemu_syscall super;
    uint64_t pidlExtra;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SHHandleUpdateImage(LPCITEMIDLIST pidlExtra)
{
    struct qemu_SHHandleUpdateImage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHHANDLEUPDATEIMAGE);
    call.pidlExtra = (ULONG_PTR)pidlExtra;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHHandleUpdateImage(struct qemu_syscall *call)
{
    struct qemu_SHHandleUpdateImage *c = (struct qemu_SHHandleUpdateImage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHHandleUpdateImage(QEMU_G2H(c->pidlExtra));
}

#endif

struct qemu_SHObjectProperties
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t dwType;
    uint64_t szObject;
    uint64_t szPage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHObjectProperties(HWND hwnd, DWORD dwType, LPCWSTR szObject, LPCWSTR szPage)
{
    struct qemu_SHObjectProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOBJECTPROPERTIES);
    call.hwnd = (ULONG_PTR)hwnd;
    call.dwType = (ULONG_PTR)dwType;
    call.szObject = (ULONG_PTR)szObject;
    call.szPage = (ULONG_PTR)szPage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHObjectProperties(struct qemu_syscall *call)
{
    struct qemu_SHObjectProperties *c = (struct qemu_SHObjectProperties *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHObjectProperties(QEMU_G2H(c->hwnd), c->dwType, QEMU_G2H(c->szObject), QEMU_G2H(c->szPage));
}

#endif

struct qemu_SHGetNewLinkInfoA
{
    struct qemu_syscall super;
    uint64_t pszLinkTo;
    uint64_t pszDir;
    uint64_t pszName;
    uint64_t pfMustCopy;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetNewLinkInfoA(LPCSTR pszLinkTo, LPCSTR pszDir, LPSTR pszName, BOOL *pfMustCopy, UINT uFlags)
{
    struct qemu_SHGetNewLinkInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETNEWLINKINFOA);
    call.pszLinkTo = (ULONG_PTR)pszLinkTo;
    call.pszDir = (ULONG_PTR)pszDir;
    call.pszName = (ULONG_PTR)pszName;
    call.pfMustCopy = (ULONG_PTR)pfMustCopy;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetNewLinkInfoA(struct qemu_syscall *call)
{
    struct qemu_SHGetNewLinkInfoA *c = (struct qemu_SHGetNewLinkInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetNewLinkInfoA(QEMU_G2H(c->pszLinkTo), QEMU_G2H(c->pszDir), QEMU_G2H(c->pszName), QEMU_G2H(c->pfMustCopy), c->uFlags);
}

#endif

struct qemu_SHGetNewLinkInfoW
{
    struct qemu_syscall super;
    uint64_t pszLinkTo;
    uint64_t pszDir;
    uint64_t pszName;
    uint64_t pfMustCopy;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetNewLinkInfoW(LPCWSTR pszLinkTo, LPCWSTR pszDir, LPWSTR pszName, BOOL *pfMustCopy, UINT uFlags)
{
    struct qemu_SHGetNewLinkInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETNEWLINKINFOW);
    call.pszLinkTo = (ULONG_PTR)pszLinkTo;
    call.pszDir = (ULONG_PTR)pszDir;
    call.pszName = (ULONG_PTR)pszName;
    call.pfMustCopy = (ULONG_PTR)pfMustCopy;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetNewLinkInfoW(struct qemu_syscall *call)
{
    struct qemu_SHGetNewLinkInfoW *c = (struct qemu_SHGetNewLinkInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetNewLinkInfoW(QEMU_G2H(c->pszLinkTo), QEMU_G2H(c->pszDir), QEMU_G2H(c->pszName), QEMU_G2H(c->pfMustCopy), c->uFlags);
}

#endif

struct qemu_SHStartNetConnectionDialog
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pszRemoteName;
    uint64_t dwType;
};

#ifdef QEMU_DLL_GUEST

HRESULT WINAPI shell32_SHStartNetConnectionDialog(HWND hwnd, LPCSTR pszRemoteName, DWORD dwType)
{
    struct qemu_SHStartNetConnectionDialog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSTARTNETCONNECTIONDIALOG);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pszRemoteName = (ULONG_PTR)pszRemoteName;
    call.dwType = (ULONG_PTR)dwType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHStartNetConnectionDialog(struct qemu_syscall *call)
{
    struct qemu_SHStartNetConnectionDialog *c = (struct qemu_SHStartNetConnectionDialog *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHStartNetConnectionDialog(QEMU_G2H(c->hwnd), QEMU_G2H(c->pszRemoteName), c->dwType);
}

#endif

struct qemu_SHFormatDrive
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t drive;
    uint64_t fmtID;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHFormatDrive(HWND hwnd, UINT drive, UINT fmtID, UINT options)
{
    struct qemu_SHFormatDrive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFORMATDRIVE);
    call.hwnd = (ULONG_PTR)hwnd;
    call.drive = (ULONG_PTR)drive;
    call.fmtID = (ULONG_PTR)fmtID;
    call.options = (ULONG_PTR)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHFormatDrive(struct qemu_syscall *call)
{
    struct qemu_SHFormatDrive *c = (struct qemu_SHFormatDrive *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHFormatDrive(QEMU_G2H(c->hwnd), c->drive, c->fmtID, c->options);
}

#endif

struct qemu_SHRemoveLocalizedName
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRemoveLocalizedName(const WCHAR *path)
{
    struct qemu_SHRemoveLocalizedName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREMOVELOCALIZEDNAME);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRemoveLocalizedName to Wine headers? */
extern HRESULT WINAPI SHRemoveLocalizedName(const WCHAR *path);
void qemu_SHRemoveLocalizedName(struct qemu_syscall *call)
{
    struct qemu_SHRemoveLocalizedName *c = (struct qemu_SHRemoveLocalizedName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRemoveLocalizedName(QEMU_G2H(c->path));
}

#endif

struct qemu_SHSetLocalizedName
{
    struct qemu_syscall super;
    uint64_t pszPath;
    uint64_t pszResModule;
    uint64_t idsRes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHSetLocalizedName(LPCWSTR pszPath, LPCWSTR pszResModule, int idsRes)
{
    struct qemu_SHSetLocalizedName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSETLOCALIZEDNAME);
    call.pszPath = (ULONG_PTR)pszPath;
    call.pszResModule = (ULONG_PTR)pszResModule;
    call.idsRes = (ULONG_PTR)idsRes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHSetLocalizedName to Wine headers? */
extern HRESULT WINAPI SHSetLocalizedName(LPWSTR pszPath, LPCWSTR pszResModule, int idsRes);
void qemu_SHSetLocalizedName(struct qemu_syscall *call)
{
    struct qemu_SHSetLocalizedName *c = (struct qemu_SHSetLocalizedName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHSetLocalizedName(QEMU_G2H(c->pszPath), QEMU_G2H(c->pszResModule), c->idsRes);
}

#endif

struct qemu_LinkWindow_RegisterClass
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LinkWindow_RegisterClass(void)
{
    struct qemu_LinkWindow_RegisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LINKWINDOW_REGISTERCLASS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LinkWindow_RegisterClass to Wine headers? */
extern BOOL WINAPI LinkWindow_RegisterClass(void);
void qemu_LinkWindow_RegisterClass(struct qemu_syscall *call)
{
    struct qemu_LinkWindow_RegisterClass *c = (struct qemu_LinkWindow_RegisterClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LinkWindow_RegisterClass();
}

#endif

struct qemu_LinkWindow_UnregisterClass
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LinkWindow_UnregisterClass(void)
{
    struct qemu_LinkWindow_UnregisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LINKWINDOW_UNREGISTERCLASS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LinkWindow_UnregisterClass to Wine headers? */
extern BOOL WINAPI LinkWindow_UnregisterClass(void);
void qemu_LinkWindow_UnregisterClass(struct qemu_syscall *call)
{
    struct qemu_LinkWindow_UnregisterClass *c = (struct qemu_LinkWindow_UnregisterClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LinkWindow_UnregisterClass();
}

#endif

struct qemu_SHFlushSFCache
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHFlushSFCache(void)
{
    struct qemu_SHFlushSFCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFLUSHSFCACHE);

    qemu_syscall(&call.super);
}

#else

/* TODO: Add SHFlushSFCache to Wine headers? */
extern void WINAPI SHFlushSFCache(void);
void qemu_SHFlushSFCache(struct qemu_syscall *call)
{
    struct qemu_SHFlushSFCache *c = (struct qemu_SHFlushSFCache *)call;
    WINE_FIXME("Unverified!\n");
    SHFlushSFCache();
}

#endif

struct qemu_SHGetImageList
{
    struct qemu_syscall super;
    uint64_t iImageList;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetImageList(int iImageList, REFIID riid, void **ppv)
{
    struct qemu_SHGetImageList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETIMAGELIST);
    call.iImageList = (ULONG_PTR)iImageList;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetImageList(struct qemu_syscall *call)
{
    struct qemu_SHGetImageList *c = (struct qemu_SHGetImageList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetImageList(c->iImageList, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_ShellMessageBox
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV ShellMessageBoxA(HINSTANCE hInstance, HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, ...)
{
    struct qemu_ShellMessageBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLMESSAGEBOX);

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI int WINAPIV ShellMessageBoxW(HINSTANCE hInstance, HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, ...)
{
    struct qemu_ShellMessageBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLMESSAGEBOX);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShellMessageBox(struct qemu_syscall *call)
{
    struct qemu_ShellMessageBox *c = (struct qemu_ShellMessageBox *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif
