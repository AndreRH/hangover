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
#include <commctrl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

typedef void MRUINFOA, MRUINFOW;

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif

struct qemu_Alloc
{
    struct qemu_syscall super;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI Alloc (DWORD dwSize)
{
    struct qemu_Alloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOC);
    call.dwSize = dwSize;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

extern LPVOID WINAPI Alloc (DWORD dwSize);
void qemu_Alloc(struct qemu_syscall *call)
{
    struct qemu_Alloc *c = (struct qemu_Alloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)Alloc(c->dwSize);
}

#endif

struct qemu_ReAlloc
{
    struct qemu_syscall super;
    uint64_t lpSrc;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI ReAlloc (LPVOID lpSrc, DWORD dwSize)
{
    struct qemu_ReAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALLOC);
    call.lpSrc = (ULONG_PTR)lpSrc;
    call.dwSize = dwSize;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

extern LPVOID WINAPI ReAlloc (LPVOID lpSrc, DWORD dwSize);
void qemu_ReAlloc(struct qemu_syscall *call)
{
    struct qemu_ReAlloc *c = (struct qemu_ReAlloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ReAlloc(QEMU_G2H(c->lpSrc), c->dwSize);
}

#endif

struct qemu_Free
{
    struct qemu_syscall super;
    uint64_t lpMem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Free (LPVOID lpMem)
{
    struct qemu_Free call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREE);
    call.lpMem = (ULONG_PTR)lpMem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI Free (LPVOID lpMem);
void qemu_Free(struct qemu_syscall *call)
{
    struct qemu_Free *c = (struct qemu_Free *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Free(QEMU_G2H(c->lpMem));
}

#endif

struct qemu_GetSize
{
    struct qemu_syscall super;
    uint64_t lpMem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetSize (LPVOID lpMem)
{
    struct qemu_GetSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSIZE);
    call.lpMem = (ULONG_PTR)lpMem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern DWORD WINAPI GetSize (LPVOID lpMem);
void qemu_GetSize(struct qemu_syscall *call)
{
    struct qemu_GetSize *c = (struct qemu_GetSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSize(QEMU_G2H(c->lpMem));
}

#endif

struct qemu_FreeMRUList
{
    struct qemu_syscall super;
    uint64_t hMRUList;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FreeMRUList (HANDLE hMRUList)
{
    struct qemu_FreeMRUList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEMRULIST);
    call.hMRUList = (ULONG_PTR)hMRUList;

    qemu_syscall(&call.super);
}

#else

extern void WINAPI FreeMRUList (HANDLE hMRUList);
void qemu_FreeMRUList(struct qemu_syscall *call)
{
    struct qemu_FreeMRUList *c = (struct qemu_FreeMRUList *)call;
    WINE_FIXME("Unverified!\n");
    FreeMRUList(QEMU_G2H(c->hMRUList));
}

#endif

struct qemu_FindMRUData
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t lpData;
    uint64_t cbData;
    uint64_t lpRegNum;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FindMRUData (HANDLE hList, LPCVOID lpData, DWORD cbData, LPINT lpRegNum)
{
    struct qemu_FindMRUData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDMRUDATA);
    call.hList = (ULONG_PTR)hList;
    call.lpData = (ULONG_PTR)lpData;
    call.cbData = cbData;
    call.lpRegNum = (ULONG_PTR)lpRegNum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI FindMRUData (HANDLE hList, LPCVOID lpData, DWORD cbData, LPINT lpRegNum);
void qemu_FindMRUData(struct qemu_syscall *call)
{
    struct qemu_FindMRUData *c = (struct qemu_FindMRUData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindMRUData(QEMU_G2H(c->hList), QEMU_G2H(c->lpData), c->cbData, QEMU_G2H(c->lpRegNum));
}

#endif

struct qemu_AddMRUData
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t lpData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI AddMRUData (HANDLE hList, LPCVOID lpData, DWORD cbData)
{
    struct qemu_AddMRUData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDMRUDATA);
    call.hList = (ULONG_PTR)hList;
    call.lpData = (ULONG_PTR)lpData;
    call.cbData = cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI AddMRUData (HANDLE hList, LPCVOID lpData, DWORD cbData);
void qemu_AddMRUData(struct qemu_syscall *call)
{
    struct qemu_AddMRUData *c = (struct qemu_AddMRUData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddMRUData(QEMU_G2H(c->hList), QEMU_G2H(c->lpData), c->cbData);
}

#endif

struct qemu_AddMRUStringW
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t lpszString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI AddMRUStringW(HANDLE hList, LPCWSTR lpszString)
{
    struct qemu_AddMRUStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDMRUSTRINGW);
    call.hList = (ULONG_PTR)hList;
    call.lpszString = (ULONG_PTR)lpszString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI AddMRUStringW(HANDLE hList, LPCWSTR lpszString);
void qemu_AddMRUStringW(struct qemu_syscall *call)
{
    struct qemu_AddMRUStringW *c = (struct qemu_AddMRUStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddMRUStringW(QEMU_G2H(c->hList), QEMU_G2H(c->lpszString));
}

#endif

struct qemu_AddMRUStringA
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t lpszString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI AddMRUStringA(HANDLE hList, LPCSTR lpszString)
{
    struct qemu_AddMRUStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDMRUSTRINGA);
    call.hList = (ULONG_PTR)hList;
    call.lpszString = (ULONG_PTR)lpszString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI AddMRUStringA(HANDLE hList, LPCSTR lpszString);
void qemu_AddMRUStringA(struct qemu_syscall *call)
{
    struct qemu_AddMRUStringA *c = (struct qemu_AddMRUStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddMRUStringA(QEMU_G2H(c->hList), QEMU_G2H(c->lpszString));
}

#endif

struct qemu_DelMRUString
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t nItemPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DelMRUString(HANDLE hList, INT nItemPos)
{
    struct qemu_DelMRUString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELMRUSTRING);
    call.hList = (ULONG_PTR)hList;
    call.nItemPos = nItemPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI DelMRUString(HANDLE hList, INT nItemPos);
void qemu_DelMRUString(struct qemu_syscall *call)
{
    struct qemu_DelMRUString *c = (struct qemu_DelMRUString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DelMRUString(QEMU_G2H(c->hList), c->nItemPos);
}

#endif

struct qemu_FindMRUStringW
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t lpszString;
    uint64_t lpRegNum;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FindMRUStringW (HANDLE hList, LPCWSTR lpszString, LPINT lpRegNum)
{
    struct qemu_FindMRUStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDMRUSTRINGW);
    call.hList = (ULONG_PTR)hList;
    call.lpszString = (ULONG_PTR)lpszString;
    call.lpRegNum = (ULONG_PTR)lpRegNum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI FindMRUStringW (HANDLE hList, LPCWSTR lpszString, LPINT lpRegNum);
void qemu_FindMRUStringW(struct qemu_syscall *call)
{
    struct qemu_FindMRUStringW *c = (struct qemu_FindMRUStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindMRUStringW(QEMU_G2H(c->hList), QEMU_G2H(c->lpszString), QEMU_G2H(c->lpRegNum));
}

#endif

struct qemu_FindMRUStringA
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t lpszString;
    uint64_t lpRegNum;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FindMRUStringA (HANDLE hList, LPCSTR lpszString, LPINT lpRegNum)
{
    struct qemu_FindMRUStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDMRUSTRINGA);
    call.hList = (ULONG_PTR)hList;
    call.lpszString = (ULONG_PTR)lpszString;
    call.lpRegNum = (ULONG_PTR)lpRegNum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI FindMRUStringA (HANDLE hList, LPCSTR lpszString, LPINT lpRegNum);
void qemu_FindMRUStringA(struct qemu_syscall *call)
{
    struct qemu_FindMRUStringA *c = (struct qemu_FindMRUStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindMRUStringA(QEMU_G2H(c->hList), QEMU_G2H(c->lpszString), QEMU_G2H(c->lpRegNum));
}

#endif

struct qemu_CreateMRUListLazyW
{
    struct qemu_syscall super;
    uint64_t infoW;
    uint64_t dwParam2;
    uint64_t dwParam3;
    uint64_t dwParam4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMRUListLazyW (const MRUINFOW *infoW, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4)
{
    struct qemu_CreateMRUListLazyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMRULISTLAZYW);
    call.infoW = (ULONG_PTR)infoW;
    call.dwParam2 = dwParam2;
    call.dwParam3 = dwParam3;
    call.dwParam4 = dwParam4;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

extern HANDLE WINAPI CreateMRUListLazyW (const MRUINFOW *infoW, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4);
void qemu_CreateMRUListLazyW(struct qemu_syscall *call)
{
    struct qemu_CreateMRUListLazyW *c = (struct qemu_CreateMRUListLazyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMRUListLazyW(QEMU_G2H(c->infoW), c->dwParam2, c->dwParam3, c->dwParam4);
}

#endif

struct qemu_CreateMRUListLazyA
{
    struct qemu_syscall super;
    uint64_t lpcml;
    uint64_t dwParam2;
    uint64_t dwParam3;
    uint64_t dwParam4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMRUListLazyA (const MRUINFOA *lpcml, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4)
{
    struct qemu_CreateMRUListLazyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMRULISTLAZYA);
    call.lpcml = (ULONG_PTR)lpcml;
    call.dwParam2 = dwParam2;
    call.dwParam3 = dwParam3;
    call.dwParam4 = dwParam4;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

extern HANDLE WINAPI CreateMRUListLazyA (const MRUINFOA *lpcml, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4);
void qemu_CreateMRUListLazyA(struct qemu_syscall *call)
{
    struct qemu_CreateMRUListLazyA *c = (struct qemu_CreateMRUListLazyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMRUListLazyA(QEMU_G2H(c->lpcml), c->dwParam2, c->dwParam3, c->dwParam4);
}

#endif

struct qemu_CreateMRUListW
{
    struct qemu_syscall super;
    uint64_t infoW;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMRUListW (const MRUINFOW *infoW)
{
    struct qemu_CreateMRUListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMRULISTW);
    call.infoW = (ULONG_PTR)infoW;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

extern HANDLE WINAPI CreateMRUListW (const MRUINFOW *infoW);
void qemu_CreateMRUListW(struct qemu_syscall *call)
{
    struct qemu_CreateMRUListW *c = (struct qemu_CreateMRUListW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMRUListW(QEMU_G2H(c->infoW));
}

#endif

struct qemu_CreateMRUListA
{
    struct qemu_syscall super;
    uint64_t lpcml;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMRUListA (const MRUINFOA *lpcml)
{
    struct qemu_CreateMRUListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMRULISTA);
    call.lpcml = (ULONG_PTR)lpcml;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

extern HANDLE WINAPI CreateMRUListA (const MRUINFOA *lpcml);
void qemu_CreateMRUListA(struct qemu_syscall *call)
{
    struct qemu_CreateMRUListA *c = (struct qemu_CreateMRUListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMRUListA(QEMU_G2H(c->lpcml));
}

#endif

struct qemu_EnumMRUListW
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t nItemPos;
    uint64_t lpBuffer;
    uint64_t nBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI EnumMRUListW (HANDLE hList, INT nItemPos, LPVOID lpBuffer, DWORD nBufferSize)
{
    struct qemu_EnumMRUListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMMRULISTW);
    call.hList = (ULONG_PTR)hList;
    call.nItemPos = nItemPos;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.nBufferSize = nBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI EnumMRUListW (HANDLE hList, INT nItemPos, LPVOID lpBuffer, DWORD nBufferSize);
void qemu_EnumMRUListW(struct qemu_syscall *call)
{
    struct qemu_EnumMRUListW *c = (struct qemu_EnumMRUListW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumMRUListW(QEMU_G2H(c->hList), c->nItemPos, QEMU_G2H(c->lpBuffer), c->nBufferSize);
}

#endif

struct qemu_EnumMRUListA
{
    struct qemu_syscall super;
    uint64_t hList;
    uint64_t nItemPos;
    uint64_t lpBuffer;
    uint64_t nBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI EnumMRUListA (HANDLE hList, INT nItemPos, LPVOID lpBuffer, DWORD nBufferSize)
{
    struct qemu_EnumMRUListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMMRULISTA);
    call.hList = (ULONG_PTR)hList;
    call.nItemPos = nItemPos;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.nBufferSize = nBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI EnumMRUListA (HANDLE hList, INT nItemPos, LPVOID lpBuffer, DWORD nBufferSize);
void qemu_EnumMRUListA(struct qemu_syscall *call)
{
    struct qemu_EnumMRUListA *c = (struct qemu_EnumMRUListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumMRUListA(QEMU_G2H(c->hList), c->nItemPos, QEMU_G2H(c->lpBuffer), c->nBufferSize);
}

#endif

struct qemu_SendNotify
{
    struct qemu_syscall super;
    uint64_t hwndTo;
    uint64_t hwndFrom;
    uint64_t uCode;
    uint64_t lpHdr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI SendNotify (HWND hwndTo, HWND hwndFrom, UINT uCode, LPNMHDR lpHdr)
{
    struct qemu_SendNotify call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDNOTIFY);
    call.hwndTo = (ULONG_PTR)hwndTo;
    call.hwndFrom = (ULONG_PTR)hwndFrom;
    call.uCode = uCode;
    call.lpHdr = (ULONG_PTR)lpHdr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern LRESULT WINAPI SendNotify (HWND hwndTo, HWND hwndFrom, UINT uCode, LPNMHDR lpHdr);
void qemu_SendNotify(struct qemu_syscall *call)
{
    struct qemu_SendNotify *c = (struct qemu_SendNotify *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendNotify(QEMU_G2H(c->hwndTo), QEMU_G2H(c->hwndFrom), c->uCode, QEMU_G2H(c->lpHdr));
}

#endif

struct qemu_SendNotifyEx
{
    struct qemu_syscall super;
    uint64_t hwndTo;
    uint64_t hwndFrom;
    uint64_t uCode;
    uint64_t lpHdr;
    uint64_t dwParam5;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI SendNotifyEx (HWND hwndTo, HWND hwndFrom, UINT uCode, LPNMHDR lpHdr, DWORD dwParam5)
{
    struct qemu_SendNotifyEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDNOTIFYEX);
    call.hwndTo = (ULONG_PTR)hwndTo;
    call.hwndFrom = (ULONG_PTR)hwndFrom;
    call.uCode = uCode;
    call.lpHdr = (ULONG_PTR)lpHdr;
    call.dwParam5 = dwParam5;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern LRESULT WINAPI SendNotifyEx (HWND hwndTo, HWND hwndFrom, UINT uCode, LPNMHDR lpHdr, DWORD dwParam5);
void qemu_SendNotifyEx(struct qemu_syscall *call)
{
    struct qemu_SendNotifyEx *c = (struct qemu_SendNotifyEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendNotifyEx(QEMU_G2H(c->hwndTo), QEMU_G2H(c->hwndFrom), c->uCode, QEMU_G2H(c->lpHdr), c->dwParam5);
}

#endif

