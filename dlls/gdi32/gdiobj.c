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
#include "gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_DeleteObject
{
    struct qemu_syscall super;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI DeleteObject(HGDIOBJ obj)
{
    struct qemu_DeleteObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEOBJECT);
    call.obj = (uint64_t)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteObject(struct qemu_syscall *call)
{
    struct qemu_DeleteObject *c = (struct qemu_DeleteObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteObject(QEMU_G2H(c->obj));
}

#endif

struct qemu_GetStockObject
{
    struct qemu_syscall super;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HGDIOBJ WINAPI GetStockObject(INT obj)
{
    struct qemu_GetStockObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTOCKOBJECT);
    call.obj = (uint64_t)obj;

    qemu_syscall(&call.super);

    return (HGDIOBJ)call.super.iret;
}

#else

void qemu_GetStockObject(struct qemu_syscall *call)
{
    struct qemu_GetStockObject *c = (struct qemu_GetStockObject *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetStockObject(c->obj);
}

#endif

struct qemu_GetObjectA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetObjectA(HGDIOBJ handle, INT count, LPVOID buffer)
{
    struct qemu_GetObjectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOBJECTA);
    call.handle = (uint64_t)handle;
    call.count = (uint64_t)count;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetObjectA(struct qemu_syscall *call)
{
    struct qemu_GetObjectA *c = (struct qemu_GetObjectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetObjectA(QEMU_G2H(c->handle), c->count, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetObjectW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetObjectW(HGDIOBJ handle, INT count, LPVOID buffer)
{
    struct qemu_GetObjectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOBJECTW);
    call.handle = (uint64_t)handle;
    call.count = (uint64_t)count;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetObjectW(struct qemu_syscall *call)
{
    struct qemu_GetObjectW *c = (struct qemu_GetObjectW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetObjectW(QEMU_G2H(c->handle), c->count, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetObjectType
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetObjectType(HGDIOBJ handle)
{
    struct qemu_GetObjectType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOBJECTTYPE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetObjectType(struct qemu_syscall *call)
{
    struct qemu_GetObjectType *c = (struct qemu_GetObjectType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetObjectType(QEMU_G2H(c->handle));
}

#endif

struct qemu_GetCurrentObject
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HGDIOBJ WINAPI GetCurrentObject(HDC hdc,UINT type)
{
    struct qemu_GetCurrentObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTOBJECT);
    call.hdc = (uint64_t)hdc;
    call.type = (uint64_t)type;

    qemu_syscall(&call.super);

    return (HGDIOBJ)call.super.iret;
}

#else

void qemu_GetCurrentObject(struct qemu_syscall *call)
{
    struct qemu_GetCurrentObject *c = (struct qemu_GetCurrentObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetCurrentObject(QEMU_G2H(c->hdc), c->type);
}

#endif

struct qemu_SelectObject
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hObj;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HGDIOBJ WINAPI SelectObject(HDC hdc, HGDIOBJ hObj)
{
    struct qemu_SelectObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SELECTOBJECT);
    call.hdc = (uint64_t)hdc;
    call.hObj = (uint64_t)hObj;

    qemu_syscall(&call.super);

    return (HGDIOBJ)call.super.iret;
}

#else

void qemu_SelectObject(struct qemu_syscall *call)
{
    struct qemu_SelectObject *c = (struct qemu_SelectObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SelectObject(QEMU_G2H(c->hdc), QEMU_G2H(c->hObj));
}

#endif

struct qemu_UnrealizeObject
{
    struct qemu_syscall super;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI UnrealizeObject(HGDIOBJ obj)
{
    struct qemu_UnrealizeObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREALIZEOBJECT);
    call.obj = (uint64_t)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnrealizeObject(struct qemu_syscall *call)
{
    struct qemu_UnrealizeObject *c = (struct qemu_UnrealizeObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnrealizeObject(QEMU_G2H(c->obj));
}

#endif

struct qemu_EnumObjects
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t nObjType;
    uint64_t lpEnumFunc;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumObjects(HDC hdc, INT nObjType, GOBJENUMPROC lpEnumFunc, LPARAM lParam)
{
    struct qemu_EnumObjects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMOBJECTS);
    call.hdc = (uint64_t)hdc;
    call.nObjType = (uint64_t)nObjType;
    call.lpEnumFunc = (uint64_t)lpEnumFunc;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumObjects(struct qemu_syscall *call)
{
    struct qemu_EnumObjects *c = (struct qemu_EnumObjects *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumObjects(QEMU_G2H(c->hdc), c->nObjType, QEMU_G2H(c->lpEnumFunc), c->lParam);
}

#endif

struct qemu_SetObjectOwner
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t owner;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI void WINAPI SetObjectOwner(HGDIOBJ handle, HANDLE owner)
{
    struct qemu_SetObjectOwner call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETOBJECTOWNER);
    call.handle = (uint64_t)handle;
    call.owner = (uint64_t)owner;

    qemu_syscall(&call.super);

    return;
}

#else

/* TODO: Add SetObjectOwner to Wine headers? */
extern void WINAPI SetObjectOwner(HGDIOBJ handle, HANDLE owner);
void qemu_SetObjectOwner(struct qemu_syscall *call)
{
    struct qemu_SetObjectOwner *c = (struct qemu_SetObjectOwner *)call;
    WINE_FIXME("Unverified!\n");
    SetObjectOwner(QEMU_G2H(c->handle), QEMU_G2H(c->owner));
}

#endif

struct qemu_GdiInitializeLanguagePack
{
    struct qemu_syscall super;
    uint64_t arg;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GdiInitializeLanguagePack(DWORD arg)
{
    struct qemu_GdiInitializeLanguagePack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIINITIALIZELANGUAGEPACK);
    call.arg = (uint64_t)arg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiInitializeLanguagePack to Wine headers? */
extern DWORD WINAPI GdiInitializeLanguagePack(DWORD arg);
void qemu_GdiInitializeLanguagePack(struct qemu_syscall *call)
{
    struct qemu_GdiInitializeLanguagePack *c = (struct qemu_GdiInitializeLanguagePack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiInitializeLanguagePack(c->arg);
}

#endif

struct qemu_GdiFlush
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GdiFlush(void)
{
    struct qemu_GdiFlush call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIFLUSH);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiFlush(struct qemu_syscall *call)
{
    struct qemu_GdiFlush *c = (struct qemu_GdiFlush *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiFlush();
}

#endif

struct qemu_GdiGetBatchLimit
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GdiGetBatchLimit(void)
{
    struct qemu_GdiGetBatchLimit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIGETBATCHLIMIT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiGetBatchLimit(struct qemu_syscall *call)
{
    struct qemu_GdiGetBatchLimit *c = (struct qemu_GdiGetBatchLimit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiGetBatchLimit();
}

#endif

struct qemu_GdiSetBatchLimit
{
    struct qemu_syscall super;
    uint64_t limit;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GdiSetBatchLimit(DWORD limit)
{
    struct qemu_GdiSetBatchLimit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDISETBATCHLIMIT);
    call.limit = (uint64_t)limit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiSetBatchLimit(struct qemu_syscall *call)
{
    struct qemu_GdiSetBatchLimit *c = (struct qemu_GdiSetBatchLimit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiSetBatchLimit(c->limit);
}

#endif

struct qemu_GetColorAdjustment
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpca;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetColorAdjustment(HDC hdc, LPCOLORADJUSTMENT lpca)
{
    struct qemu_GetColorAdjustment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOLORADJUSTMENT);
    call.hdc = (uint64_t)hdc;
    call.lpca = (uint64_t)lpca;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetColorAdjustment(struct qemu_syscall *call)
{
    struct qemu_GetColorAdjustment *c = (struct qemu_GetColorAdjustment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetColorAdjustment(QEMU_G2H(c->hdc), QEMU_G2H(c->lpca));
}

#endif

struct qemu_GdiComment
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t cbSize;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GdiComment(HDC hdc, UINT cbSize, const BYTE *lpData)
{
    struct qemu_GdiComment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDICOMMENT);
    call.hdc = (uint64_t)hdc;
    call.cbSize = (uint64_t)cbSize;
    call.lpData = (uint64_t)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiComment(struct qemu_syscall *call)
{
    struct qemu_GdiComment *c = (struct qemu_GdiComment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiComment(QEMU_G2H(c->hdc), c->cbSize, QEMU_G2H(c->lpData));
}

#endif

struct qemu_SetColorAdjustment
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpca;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetColorAdjustment(HDC hdc, const COLORADJUSTMENT* lpca)
{
    struct qemu_SetColorAdjustment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOLORADJUSTMENT);
    call.hdc = (uint64_t)hdc;
    call.lpca = (uint64_t)lpca;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetColorAdjustment(struct qemu_syscall *call)
{
    struct qemu_SetColorAdjustment *c = (struct qemu_SetColorAdjustment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetColorAdjustment(QEMU_G2H(c->hdc), QEMU_G2H(c->lpca));
}

#endif

