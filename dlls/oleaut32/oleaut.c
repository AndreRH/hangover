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
#include <ocidl.h>
#include <olectl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "oleaut32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_oleaut32);
#endif


struct qemu_SysStringLen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SysStringLen(BSTR str)
{
    struct qemu_SysStringLen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSSTRINGLEN);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SysStringLen(struct qemu_syscall *call)
{
    struct qemu_SysStringLen *c = (struct qemu_SysStringLen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SysStringLen(QEMU_G2H(c->str));
}

#endif

struct qemu_SysStringByteLen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SysStringByteLen(BSTR str)
{
    struct qemu_SysStringByteLen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSSTRINGBYTELEN);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SysStringByteLen(struct qemu_syscall *call)
{
    struct qemu_SysStringByteLen *c = (struct qemu_SysStringByteLen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SysStringByteLen(QEMU_G2H(c->str));
}

#endif

struct qemu_SysAllocString
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BSTR WINAPI SysAllocString(LPCOLESTR str)
{
    struct qemu_SysAllocString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSALLOCSTRING);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return (BSTR)call.super.iret;
}

#else

void qemu_SysAllocString(struct qemu_syscall *call)
{
    struct qemu_SysAllocString *c = (struct qemu_SysAllocString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SysAllocString(QEMU_G2H(c->str));
}

#endif

struct qemu_SysFreeString
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SysFreeString(BSTR str)
{
    struct qemu_SysFreeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSFREESTRING);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);
}

#else

void qemu_SysFreeString(struct qemu_syscall *call)
{
    struct qemu_SysFreeString *c = (struct qemu_SysFreeString *)call;
    WINE_FIXME("Unverified!\n");
    SysFreeString(QEMU_G2H(c->str));
}

#endif

struct qemu_SysAllocStringLen
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BSTR WINAPI SysAllocStringLen(const OLECHAR *str, unsigned int len)
{
    struct qemu_SysAllocStringLen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSALLOCSTRINGLEN);
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return (BSTR)call.super.iret;
}

#else

void qemu_SysAllocStringLen(struct qemu_syscall *call)
{
    struct qemu_SysAllocStringLen *c = (struct qemu_SysAllocStringLen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SysAllocStringLen(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_SysReAllocStringLen
{
    struct qemu_syscall super;
    uint64_t old;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SysReAllocStringLen(BSTR* old, const OLECHAR* str, unsigned int len)
{
    struct qemu_SysReAllocStringLen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSREALLOCSTRINGLEN);
    call.old = (uint64_t)old;
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SysReAllocStringLen(struct qemu_syscall *call)
{
    struct qemu_SysReAllocStringLen *c = (struct qemu_SysReAllocStringLen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SysReAllocStringLen(QEMU_G2H(c->old), QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_SysAllocStringByteLen
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BSTR WINAPI SysAllocStringByteLen(LPCSTR str, UINT len)
{
    struct qemu_SysAllocStringByteLen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSALLOCSTRINGBYTELEN);
    call.str = (uint64_t)str;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return (BSTR)call.super.iret;
}

#else

void qemu_SysAllocStringByteLen(struct qemu_syscall *call)
{
    struct qemu_SysAllocStringByteLen *c = (struct qemu_SysAllocStringByteLen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SysAllocStringByteLen(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_SysReAllocString
{
    struct qemu_syscall super;
    uint64_t old;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SysReAllocString(LPBSTR old,LPCOLESTR str)
{
    struct qemu_SysReAllocString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSREALLOCSTRING);
    call.old = (uint64_t)old;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SysReAllocString(struct qemu_syscall *call)
{
    struct qemu_SysReAllocString *c = (struct qemu_SysReAllocString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SysReAllocString(QEMU_G2H(c->old), QEMU_G2H(c->str));
}

#endif

struct qemu_SetOaNoCache
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SetOaNoCache(void)
{
    struct qemu_SetOaNoCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETOANOCACHE);

    qemu_syscall(&call.super);
}

#else

/* TODO: Add SetOaNoCache to Wine headers? */
extern void WINAPI SetOaNoCache(void);
void qemu_SetOaNoCache(struct qemu_syscall *call)
{
    struct qemu_SetOaNoCache *c = (struct qemu_SetOaNoCache *)call;
    WINE_FIXME("Unverified!\n");
    SetOaNoCache();
}

#endif

struct qemu_RegisterActiveObject
{
    struct qemu_syscall super;
    uint64_t punk;
    uint64_t rcid;
    uint64_t dwFlags;
    uint64_t pdwRegister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegisterActiveObject(LPUNKNOWN punk,REFCLSID rcid,DWORD dwFlags,LPDWORD pdwRegister)
{
    struct qemu_RegisterActiveObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERACTIVEOBJECT);
    call.punk = (uint64_t)punk;
    call.rcid = (uint64_t)rcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.pdwRegister = (uint64_t)pdwRegister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterActiveObject(struct qemu_syscall *call)
{
    struct qemu_RegisterActiveObject *c = (struct qemu_RegisterActiveObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterActiveObject(QEMU_G2H(c->punk), QEMU_G2H(c->rcid), c->dwFlags, QEMU_G2H(c->pdwRegister));
}

#endif

struct qemu_RevokeActiveObject
{
    struct qemu_syscall super;
    uint64_t xregister;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RevokeActiveObject(DWORD xregister,LPVOID reserved)
{
    struct qemu_RevokeActiveObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REVOKEACTIVEOBJECT);
    call.xregister = (uint64_t)xregister;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RevokeActiveObject(struct qemu_syscall *call)
{
    struct qemu_RevokeActiveObject *c = (struct qemu_RevokeActiveObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RevokeActiveObject(c->xregister, QEMU_G2H(c->reserved));
}

#endif

struct qemu_GetActiveObject
{
    struct qemu_syscall super;
    uint64_t rcid;
    uint64_t preserved;
    uint64_t ppunk;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetActiveObject(REFCLSID rcid,LPVOID preserved,LPUNKNOWN *ppunk)
{
    struct qemu_GetActiveObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACTIVEOBJECT);
    call.rcid = (uint64_t)rcid;
    call.preserved = (uint64_t)preserved;
    call.ppunk = (uint64_t)ppunk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetActiveObject(struct qemu_syscall *call)
{
    struct qemu_GetActiveObject *c = (struct qemu_GetActiveObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetActiveObject(QEMU_G2H(c->rcid), QEMU_G2H(c->preserved), QEMU_G2H(c->ppunk));
}

#endif

struct qemu_OaBuildVersion
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI OaBuildVersion(void)
{
    struct qemu_OaBuildVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OABUILDVERSION);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OaBuildVersion(struct qemu_syscall *call)
{
    struct qemu_OaBuildVersion *c = (struct qemu_OaBuildVersion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OaBuildVersion();
}

#endif

struct qemu_OleTranslateColor
{
    struct qemu_syscall super;
    uint64_t clr;
    uint64_t hpal;
    uint64_t pColorRef;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI OleTranslateColor(OLE_COLOR clr, HPALETTE hpal, COLORREF* pColorRef)
{
    struct qemu_OleTranslateColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OLETRANSLATECOLOR);
    call.clr = (uint64_t)clr;
    call.hpal = (uint64_t)hpal;
    call.pColorRef = (uint64_t)pColorRef;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OleTranslateColor(struct qemu_syscall *call)
{
    struct qemu_OleTranslateColor *c = (struct qemu_OleTranslateColor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OleTranslateColor(c->clr, (HPALETTE)c->hpal, QEMU_G2H(c->pColorRef));
}

#endif

struct qemu_OleIconToCursor
{
    struct qemu_syscall super;
    uint64_t hinstExe;
    uint64_t hIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCURSOR WINAPI OleIconToCursor(HINSTANCE hinstExe, HICON hIcon)
{
    struct qemu_OleIconToCursor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OLEICONTOCURSOR);
    call.hinstExe = (uint64_t)hinstExe;
    call.hIcon = (uint64_t)hIcon;

    qemu_syscall(&call.super);

    return (HCURSOR)call.super.iret;
}

#else

void qemu_OleIconToCursor(struct qemu_syscall *call)
{
    struct qemu_OleIconToCursor *c = (struct qemu_OleIconToCursor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OleIconToCursor(QEMU_G2H(c->hinstExe), QEMU_G2H(c->hIcon));
}

#endif

struct qemu_GetAltMonthNames
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetAltMonthNames(LCID lcid, LPOLESTR **str)
{
    struct qemu_GetAltMonthNames call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETALTMONTHNAMES);
    call.lcid = (uint64_t)lcid;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAltMonthNames(struct qemu_syscall *call)
{
    struct qemu_GetAltMonthNames *c = (struct qemu_GetAltMonthNames *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAltMonthNames(c->lcid, QEMU_G2H(c->str));
}

#endif

