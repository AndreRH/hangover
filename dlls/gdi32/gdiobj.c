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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

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
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteObject(struct qemu_syscall *call)
{
    struct qemu_DeleteObject *c = (struct qemu_DeleteObject *)call;
    WINE_TRACE("\n");
    c->super.iret = DeleteObject((HGDIOBJ)c->obj);
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
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return (HGDIOBJ)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetStockObject(struct qemu_syscall *call)
{
    struct qemu_GetStockObject *c = (struct qemu_GetStockObject *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetStockObject(c->obj);
}

#endif

struct qemu_GetObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetObjectA(HGDIOBJ handle, INT count, LPVOID buffer)
{
    struct qemu_GetObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOBJECTA);
    call.handle = (ULONG_PTR)handle;
    call.count = count;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINGDIAPI INT WINAPI GetObjectW(HGDIOBJ handle, INT count, LPVOID buffer)
{
    struct qemu_GetObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOBJECTW);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t call_GetObject(const struct qemu_GetObject *c, INT size, void *buffer)
{
    if (c->super.id == QEMU_SYSCALL_ID(CALL_GETOBJECTW))
        return GetObjectW(QEMU_G2H(c->handle), size, buffer);
    else
        return GetObjectA(QEMU_G2H(c->handle), size, buffer);
}

void qemu_GetObject(struct qemu_syscall *call)
{
    struct qemu_GetObject *c = (struct qemu_GetObject *)call;
    INT type;
    struct obj_type
    {
        size_t host_size;
        size_t guest_size;
        void (*func)(void *, const void *);
    } convert;
    union
    {
        long dummy;
        BITMAP bm;
        DIBSECTION dib;
        LOGBRUSH brush;
    } host_buf;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
    return;
#endif

    type = GetObjectType(QEMU_G2H(c->handle));

    switch (type)
    {
        case 0:
            WINE_WARN("Translating invalid object\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_PEN:
            WINE_FIXME("Unexpected object type OBJ_PEN\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_BRUSH:
            WINE_TRACE("Translating OBJ_BRUSH\n");
            convert.host_size = sizeof(host_buf.brush);
            convert.guest_size = sizeof(struct qemu_LOGBRUSH);
            convert.func = (void *)LOGBRUSH_h2g;
            break;

        case OBJ_DC:
            WINE_FIXME("Unexpected object type OBJ_DC\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_METADC:
            WINE_FIXME("Unexpected object type OBJ_METADC\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_PAL:
            WINE_FIXME("Unexpected object type OBJ_PAL\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_FONT:
            WINE_FIXME("Unexpected object type OBJ_FONT\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_BITMAP:
        {
            WINE_TRACE("Translating OBJ_BITMAP\n");

            /* If we ask a DIBSECTION for its size, it will return sizeof(BITMAP). To get a DIBSECTION
             * to admit to being a DIBSECTION we have to explicitly ask for enough bytes. However, note
             * that we also have to be able to work with the smaller part when the app only asks for
             * a BITMAP struct or if the object turns out to be a plain bitmap. */
            type = call_GetObject(c, sizeof(host_buf.dib), &host_buf.dib);
            if (c->count >= sizeof(struct qemu_DIBSECTION) && type == sizeof(DIBSECTION))
            {
                WINE_TRACE("Asking for DIBSECTION due to client request and actual object size.\n");
                convert.host_size = sizeof(host_buf.dib);
                convert.guest_size = sizeof(struct qemu_DIBSECTION);
                convert.func = (void *)DIBSECTION_h2g;
            }
            else
            {
                WINE_TRACE("Asking for struct BITMAP either because of input size or actual object.\n");
                convert.host_size = sizeof(host_buf.bm);
                convert.guest_size = sizeof(struct qemu_BITMAP);
                convert.func = (void *)BITMAP_h2g;
                break;
            }
            break;
        }

        case OBJ_REGION:
            WINE_FIXME("Unexpected object type OBJ_REGION\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_METAFILE:
            WINE_FIXME("Unexpected object type OBJ_METAFILE\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_MEMDC:
            WINE_FIXME("Unexpected object type OBJ_MEMDC\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_EXTPEN:
            WINE_FIXME("Unexpected object type OBJ_EXTPEN\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_ENHMETADC:
            WINE_FIXME("Unexpected object type OBJ_ENHMETADC\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_ENHMETAFILE:
            WINE_FIXME("Unexpected object type OBJ_ENHMETAFILE\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        case OBJ_COLORSPACE:
            WINE_FIXME("Unexpected object type OBJ_COLORSPACE\n");
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;

        default:
            WINE_FIXME("Unexpected object type %x\n", type);
            c->super.iret = call_GetObject(c, c->count, QEMU_G2H(c->buffer));
            return;
    }

    if (!c->buffer)
    {
        c->super.iret = convert.guest_size;
        return;
    }

    if (c->count < convert.guest_size)
    {
        WINE_WARN("Size too small\n");
        c->super.iret = 0;
        return;
    }

    c->super.iret = call_GetObject(c, convert.host_size, &host_buf.dummy);
    if (!c->super.iret)
        return;

    convert.func(QEMU_G2H(c->buffer), &host_buf.dummy);
    c->super.iret = convert.guest_size;
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
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetObjectType(struct qemu_syscall *call)
{
    struct qemu_GetObjectType *c = (struct qemu_GetObjectType *)call;
    WINE_TRACE("\n");
    c->super.iret = GetObjectType((HGDIOBJ)c->handle);
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
    call.hdc = (ULONG_PTR)hdc;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return (HGDIOBJ)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetCurrentObject(struct qemu_syscall *call)
{
    struct qemu_GetCurrentObject *c = (struct qemu_GetCurrentObject *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetCurrentObject((HANDLE)c->hdc, c->type);
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
    call.hdc = (ULONG_PTR)hdc;
    call.hObj = (ULONG_PTR)hObj;

    qemu_syscall(&call.super);

    return (HGDIOBJ)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SelectObject(struct qemu_syscall *call)
{
    struct qemu_SelectObject *c = (struct qemu_SelectObject *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)SelectObject((HDC)c->hdc, (HGDIOBJ)c->hObj);
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
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnrealizeObject(struct qemu_syscall *call)
{
    struct qemu_UnrealizeObject *c = (struct qemu_UnrealizeObject *)call;
    WINE_TRACE("\n");
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
    call.hdc = (ULONG_PTR)hdc;
    call.nObjType = (ULONG_PTR)nObjType;
    call.lpEnumFunc = (ULONG_PTR)lpEnumFunc;
    call.lParam = (ULONG_PTR)lParam;

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
    call.handle = (ULONG_PTR)handle;
    call.owner = (ULONG_PTR)owner;

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
    call.arg = (ULONG_PTR)arg;

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
    call.limit = (ULONG_PTR)limit;

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
    call.hdc = (ULONG_PTR)hdc;
    call.lpca = (ULONG_PTR)lpca;

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
    call.hdc = (ULONG_PTR)hdc;
    call.cbSize = (ULONG_PTR)cbSize;
    call.lpData = (ULONG_PTR)lpData;

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
    call.hdc = (ULONG_PTR)hdc;
    call.lpca = (ULONG_PTR)lpca;

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

