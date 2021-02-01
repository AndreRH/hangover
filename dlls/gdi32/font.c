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
#include <usp10.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_GdiGetCodePage
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GdiGetCodePage(HDC hdc)
{
    struct qemu_GdiGetCodePage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIGETCODEPAGE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiGetCodePage(struct qemu_syscall *call)
{
    struct qemu_GdiGetCodePage *c = (struct qemu_GdiGetCodePage *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiGetCodePage(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GetTextCharsetInfo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t fs;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI int WINAPI GetTextCharsetInfo(HDC hdc, FONTSIGNATURE *fs, DWORD flags)
{
    struct qemu_GetTextCharsetInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTCHARSETINFO);
    call.hdc = (ULONG_PTR)hdc;
    call.fs = (ULONG_PTR)fs;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextCharsetInfo(struct qemu_syscall *call)
{
    struct qemu_GetTextCharsetInfo *c = (struct qemu_GetTextCharsetInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextCharsetInfo(QEMU_G2H(c->hdc), QEMU_G2H(c->fs), c->flags);
}

#endif

struct qemu_CreateFontIndirectExA
{
    struct qemu_syscall super;
    uint64_t penumexA;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HFONT WINAPI CreateFontIndirectExA(const ENUMLOGFONTEXDVA *penumexA)
{
    struct qemu_CreateFontIndirectExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFONTINDIRECTEXA);
    call.penumexA = (ULONG_PTR)penumexA;

    qemu_syscall(&call.super);

    return (HFONT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFontIndirectExA(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectExA *c = (struct qemu_CreateFontIndirectExA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateFontIndirectExA(QEMU_G2H(c->penumexA));
}

#endif

struct qemu_CreateFontIndirectExW
{
    struct qemu_syscall super;
    uint64_t penumex;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HFONT WINAPI CreateFontIndirectExW(const ENUMLOGFONTEXDVW *penumex)
{
    struct qemu_CreateFontIndirectExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFONTINDIRECTEXW);
    call.penumex = (ULONG_PTR)penumex;

    qemu_syscall(&call.super);

    return (HFONT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFontIndirectExW(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectExW *c = (struct qemu_CreateFontIndirectExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateFontIndirectExW(QEMU_G2H(c->penumex));
}

#endif

struct qemu_CreateFontIndirectA
{
    struct qemu_syscall super;
    uint64_t plfA;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HFONT WINAPI CreateFontIndirectA(const LOGFONTA *plfA)
{
    struct qemu_CreateFontIndirectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFONTINDIRECTA);
    call.plfA = (ULONG_PTR)plfA;

    qemu_syscall(&call.super);

    return (HFONT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFontIndirectA(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectA *c = (struct qemu_CreateFontIndirectA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateFontIndirectA(QEMU_G2H(c->plfA));
}

#endif

struct qemu_CreateFontIndirectW
{
    struct qemu_syscall super;
    uint64_t plf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HFONT WINAPI CreateFontIndirectW(const LOGFONTW *plf)
{
    struct qemu_CreateFontIndirectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFONTINDIRECTW);
    call.plf = (ULONG_PTR)plf;

    qemu_syscall(&call.super);

    return (HFONT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFontIndirectW(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectW *c = (struct qemu_CreateFontIndirectW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateFontIndirectW(QEMU_G2H(c->plf));
}

#endif

struct qemu_CreateFontA
{
    struct qemu_syscall super;
    uint64_t height;
    uint64_t width;
    uint64_t esc;
    uint64_t orient;
    uint64_t weight;
    uint64_t italic;
    uint64_t underline;
    uint64_t strikeout;
    uint64_t charset;
    uint64_t outpres;
    uint64_t clippres;
    uint64_t quality;
    uint64_t pitch;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HFONT WINAPI CreateFontA(INT height, INT width, INT esc, INT orient, INT weight, DWORD italic, DWORD underline, DWORD strikeout, DWORD charset, DWORD outpres, DWORD clippres, DWORD quality, DWORD pitch, LPCSTR name)
{
    struct qemu_CreateFontA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFONTA);
    call.height = (ULONG_PTR)height;
    call.width = (ULONG_PTR)width;
    call.esc = (ULONG_PTR)esc;
    call.orient = (ULONG_PTR)orient;
    call.weight = (ULONG_PTR)weight;
    call.italic = (ULONG_PTR)italic;
    call.underline = (ULONG_PTR)underline;
    call.strikeout = (ULONG_PTR)strikeout;
    call.charset = (ULONG_PTR)charset;
    call.outpres = (ULONG_PTR)outpres;
    call.clippres = (ULONG_PTR)clippres;
    call.quality = (ULONG_PTR)quality;
    call.pitch = (ULONG_PTR)pitch;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HFONT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFontA(struct qemu_syscall *call)
{
    struct qemu_CreateFontA *c = (struct qemu_CreateFontA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateFontA(c->height, c->width, c->esc, c->orient, c->weight, c->italic, c->underline, c->strikeout, c->charset, c->outpres, c->clippres, c->quality, c->pitch, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateFontW
{
    struct qemu_syscall super;
    uint64_t height;
    uint64_t width;
    uint64_t esc;
    uint64_t orient;
    uint64_t weight;
    uint64_t italic;
    uint64_t underline;
    uint64_t strikeout;
    uint64_t charset;
    uint64_t outpres;
    uint64_t clippres;
    uint64_t quality;
    uint64_t pitch;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HFONT WINAPI CreateFontW(INT height, INT width, INT esc, INT orient, INT weight, DWORD italic, DWORD underline, DWORD strikeout, DWORD charset, DWORD outpres, DWORD clippres, DWORD quality, DWORD pitch, LPCWSTR name)
{
    struct qemu_CreateFontW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFONTW);
    call.height = (ULONG_PTR)height;
    call.width = (ULONG_PTR)width;
    call.esc = (ULONG_PTR)esc;
    call.orient = (ULONG_PTR)orient;
    call.weight = (ULONG_PTR)weight;
    call.italic = (ULONG_PTR)italic;
    call.underline = (ULONG_PTR)underline;
    call.strikeout = (ULONG_PTR)strikeout;
    call.charset = (ULONG_PTR)charset;
    call.outpres = (ULONG_PTR)outpres;
    call.clippres = (ULONG_PTR)clippres;
    call.quality = (ULONG_PTR)quality;
    call.pitch = (ULONG_PTR)pitch;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HFONT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFontW(struct qemu_syscall *call)
{
    struct qemu_CreateFontW *c = (struct qemu_CreateFontW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateFontW(c->height, c->width, c->esc, c->orient, c->weight, c->italic, c->underline, c->strikeout, c->charset, c->outpres, c->clippres, c->quality, c->pitch, QEMU_G2H(c->name));
}

#endif

struct qemu_EnumFontFamiliesExW
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t plf;
    uint64_t efproc;
    uint64_t lParam;
    uint64_t dwFlags;
    uint64_t wrapper;
};

struct qemu_EnumFontFamilies_cb
{
    uint64_t proc;
    uint64_t font;
    uint64_t metric;
    uint64_t type;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumFontFamiliesW_guest_cb(const struct qemu_EnumFontFamilies_cb *data)
{
    FONTENUMPROCW proc = (FONTENUMPROCW)(ULONG_PTR)data->proc;
    return proc((const LOGFONTW *)(ULONG_PTR)data->font, (const TEXTMETRICW *)(ULONG_PTR)data->metric, data->type, data->param);
}

WINGDIAPI INT WINAPI EnumFontFamiliesExW(HDC hDC, LPLOGFONTW plf, FONTENUMPROCW efproc, LPARAM lParam, DWORD dwFlags)
{
    struct qemu_EnumFontFamiliesExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTFAMILIESEXW);
    call.hDC = (ULONG_PTR)hDC;
    call.plf = (ULONG_PTR)plf;
    call.efproc = (ULONG_PTR)efproc;
    call.lParam = (ULONG_PTR)lParam;
    call.dwFlags = dwFlags;
    call.wrapper = (ULONG_PTR)EnumFontFamiliesW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_EnumFontFamilies_host_data
{
    uint64_t wrapper, guest_func;
    uint64_t guest_data;
};

static INT CALLBACK qemu_EnumFontFamiliesW_host_proc(const LOGFONTW *font, const TEXTMETRICW *metric, DWORD type, LPARAM param)
{
    struct qemu_EnumFontFamilies_host_data *data = (struct qemu_EnumFontFamilies_host_data *)param;
    struct qemu_EnumFontFamilies_cb stack, *call = &stack;
    INT ret;
    struct
    {
        ENUMLOGFONTW font;
        NEWTEXTMETRICEXW metric;
        struct qemu_EnumFontFamilies_cb call;
    } *alloc = NULL;

#if HOST_BIT != GUEST_BIT
    alloc = HeapAlloc(GetProcessHeap(), 0, sizeof(*alloc));
    memcpy(&alloc->font, font, sizeof(alloc->font));
    font = (LOGFONTW *)&alloc->font;
    memcpy(&alloc->metric, metric, sizeof(alloc->metric));
    metric = (TEXTMETRICW *)&alloc->metric;
    call = &alloc->call;
#endif

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %u, 0x%lx).\n", (unsigned long)data->guest_func, font,
            metric, type, (unsigned long)data->guest_data);
    call->proc = data->guest_func;
    call->font = QEMU_H2G(font);
    call->metric = QEMU_H2G(metric);
    call->type = type;
    call->param = data->guest_data;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(call));

    WINE_TRACE("Callback returned %u.\n", ret);
    if (alloc) /* Redundant, but the idea is the compiler knows it can remove the call. */
        HeapFree(GetProcessHeap(), 0, alloc);

    return ret;
}

void qemu_EnumFontFamiliesExW(struct qemu_syscall *call)
{
    struct qemu_EnumFontFamiliesExW *c = (struct qemu_EnumFontFamiliesExW *)call;
    struct qemu_EnumFontFamilies_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->efproc;
    data.guest_data = c->lParam;

    c->super.iret = EnumFontFamiliesExW((HDC)c->hDC, QEMU_G2H(c->plf),
            c->efproc ? qemu_EnumFontFamiliesW_host_proc : NULL, (LPARAM)&data, c->dwFlags);
}

#endif

struct qemu_EnumFontFamiliesExA
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t plf;
    uint64_t efproc;
    uint64_t lParam;
    uint64_t dwFlags;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumFontFamiliesA_guest_cb(const struct qemu_EnumFontFamilies_cb *data)
{
    FONTENUMPROCA proc = (FONTENUMPROCA)(ULONG_PTR)data->proc;
    return proc((const LOGFONTA *)(ULONG_PTR)data->font, (const TEXTMETRICA *)(ULONG_PTR)data->metric, data->type, data->param);
}

WINGDIAPI INT WINAPI EnumFontFamiliesExA(HDC hDC, LPLOGFONTA plf, FONTENUMPROCA efproc, LPARAM lParam, DWORD dwFlags)
{
    struct qemu_EnumFontFamiliesExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTFAMILIESEXA);
    call.hDC = (ULONG_PTR)hDC;
    call.plf = (ULONG_PTR)plf;
    call.efproc = (ULONG_PTR)efproc;
    call.lParam = (ULONG_PTR)lParam;
    call.dwFlags = dwFlags;
    call.wrapper = (ULONG_PTR)EnumFontFamiliesA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* LOGFONTA and LOGFONTW have different sizes. */
static INT CALLBACK qemu_EnumFontFamiliesA_host_proc(const LOGFONTA *font, const TEXTMETRICA *metric, DWORD type, LPARAM param)
{
    struct qemu_EnumFontFamilies_host_data *data = (struct qemu_EnumFontFamilies_host_data *)param;
    struct qemu_EnumFontFamilies_cb stack, *call = &stack;
    INT ret;
    struct
    {
        ENUMLOGFONTA font;
        NEWTEXTMETRICEXA metric;
        struct qemu_EnumFontFamilies_cb call;
    } *alloc = NULL;

#if HOST_BIT != GUEST_BIT
    alloc = HeapAlloc(GetProcessHeap(), 0, sizeof(*alloc));
    memcpy(&alloc->font, font, sizeof(alloc->font));
    font = (LOGFONTA *)&alloc->font;
    memcpy(&alloc->metric, metric, sizeof(alloc->metric));
    metric = (TEXTMETRICA *)&alloc->metric;
    call = &alloc->call;
#endif

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %u, 0x%lx).\n", (unsigned long)data->guest_func, font,
            metric, type, (unsigned long)data->guest_data);
    call->proc = data->guest_func;
    call->font = QEMU_H2G(font);
    call->metric = QEMU_H2G(metric);
    call->type = type;
    call->param = data->guest_data;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(call));

    WINE_TRACE("Callback returned %u.\n", ret);
    if (alloc) /* Redundant, but the idea is the compiler knows it can remove the call. */
        HeapFree(GetProcessHeap(), 0, alloc);

    return ret;
}

void qemu_EnumFontFamiliesExA(struct qemu_syscall *call)
{
    struct qemu_EnumFontFamiliesExA *c = (struct qemu_EnumFontFamiliesExA *)call;
    struct qemu_EnumFontFamilies_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->efproc;
    data.guest_data = c->lParam;

    c->super.iret = EnumFontFamiliesExA((HDC)c->hDC, QEMU_G2H(c->plf),
            c->efproc ? (void *)qemu_EnumFontFamiliesA_host_proc : NULL, (LPARAM)&data, c->dwFlags);
}

#endif

struct qemu_EnumFontFamiliesA
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpFamily;
    uint64_t efproc;
    uint64_t lpData;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumFontFamiliesA(HDC hDC, LPCSTR lpFamily, FONTENUMPROCA efproc, LPARAM lpData)
{
    struct qemu_EnumFontFamiliesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTFAMILIESA);
    call.hDC = (ULONG_PTR)hDC;
    call.lpFamily = (ULONG_PTR)lpFamily;
    call.efproc = (ULONG_PTR)efproc;
    call.lpData = (ULONG_PTR)lpData;
    call.wrapper = (ULONG_PTR)EnumFontFamiliesA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFontFamiliesA(struct qemu_syscall *call)
{
    struct qemu_EnumFontFamiliesA *c = (struct qemu_EnumFontFamiliesA *)call;
    struct qemu_EnumFontFamilies_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->efproc;
    data.guest_data = c->lpData;

    c->super.iret = EnumFontFamiliesA(QEMU_G2H(c->hDC), QEMU_G2H(c->lpFamily),
            c->efproc ? qemu_EnumFontFamiliesA_host_proc : NULL, (LPARAM)&data);
}

#endif

struct qemu_EnumFontFamiliesW
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpFamily;
    uint64_t efproc;
    uint64_t lpData;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumFontFamiliesW(HDC hDC, LPCWSTR lpFamily, FONTENUMPROCW efproc, LPARAM lpData)
{
    struct qemu_EnumFontFamiliesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTFAMILIESW);
    call.hDC = (ULONG_PTR)hDC;
    call.lpFamily = (ULONG_PTR)lpFamily;
    call.efproc = (ULONG_PTR)efproc;
    call.lpData = (ULONG_PTR)lpData;
    call.wrapper = (ULONG_PTR)EnumFontFamiliesW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFontFamiliesW(struct qemu_syscall *call)
{
    struct qemu_EnumFontFamiliesW *c = (struct qemu_EnumFontFamiliesW *)call;
    struct qemu_EnumFontFamilies_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->efproc;
    data.guest_data = c->lpData;

    c->super.iret = EnumFontFamiliesW(QEMU_G2H(c->hDC), QEMU_G2H(c->lpFamily),
            c->efproc ? qemu_EnumFontFamiliesW_host_proc : NULL, (LPARAM)&data);
}

#endif

struct qemu_EnumFontsA
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpName;
    uint64_t efproc;
    uint64_t lpData;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumFontsA(HDC hDC, LPCSTR lpName, FONTENUMPROCA efproc, LPARAM lpData)
{
    struct qemu_EnumFontsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTSA);
    call.hDC = (ULONG_PTR)hDC;
    call.lpName = (ULONG_PTR)lpName;
    call.efproc = (ULONG_PTR)efproc;
    call.lpData = (ULONG_PTR)lpData;
    call.wrapper = (ULONG_PTR)EnumFontFamiliesW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFontsA(struct qemu_syscall *call)
{
    struct qemu_EnumFontsA *c = (struct qemu_EnumFontsA *)call;
    struct qemu_EnumFontFamilies_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->efproc;
    data.guest_data = c->lpData;

    c->super.iret = EnumFontsA(QEMU_G2H(c->hDC), QEMU_G2H(c->lpName),
            c->efproc ? qemu_EnumFontFamiliesA_host_proc : NULL, (LPARAM)&data);
}

#endif

struct qemu_EnumFontsW
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpName;
    uint64_t efproc;
    uint64_t lpData;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumFontsW(HDC hDC, LPCWSTR lpName, FONTENUMPROCW efproc, LPARAM lpData)
{
    struct qemu_EnumFontsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTSW);
    call.hDC = (ULONG_PTR)hDC;
    call.lpName = (ULONG_PTR)lpName;
    call.efproc = (ULONG_PTR)efproc;
    call.lpData = (ULONG_PTR)lpData;
    call.wrapper = (ULONG_PTR)EnumFontFamiliesW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFontsW(struct qemu_syscall *call)
{
    struct qemu_EnumFontsW *c = (struct qemu_EnumFontsW *)call;
    struct qemu_EnumFontFamilies_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->efproc;
    data.guest_data = c->lpData;

    c->super.iret = EnumFontsW(QEMU_G2H(c->hDC), QEMU_G2H(c->lpName),
            c->efproc ? qemu_EnumFontFamiliesW_host_proc : NULL, (LPARAM)&data);
}

#endif

struct qemu_GetTextCharacterExtra
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetTextCharacterExtra(HDC hdc)
{
    struct qemu_GetTextCharacterExtra call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTCHARACTEREXTRA);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextCharacterExtra(struct qemu_syscall *call)
{
    struct qemu_GetTextCharacterExtra *c = (struct qemu_GetTextCharacterExtra *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextCharacterExtra(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetTextCharacterExtra
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t extra;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetTextCharacterExtra(HDC hdc, INT extra)
{
    struct qemu_SetTextCharacterExtra call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTEXTCHARACTEREXTRA);
    call.hdc = (ULONG_PTR)hdc;
    call.extra = (ULONG_PTR)extra;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTextCharacterExtra(struct qemu_syscall *call)
{
    struct qemu_SetTextCharacterExtra *c = (struct qemu_SetTextCharacterExtra *)call;
    WINE_TRACE("\n");
    c->super.iret = SetTextCharacterExtra(QEMU_G2H(c->hdc), c->extra);
}

#endif

struct qemu_SetTextJustification
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t extra;
    uint64_t breaks;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetTextJustification(HDC hdc, INT extra, INT breaks)
{
    struct qemu_SetTextJustification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTEXTJUSTIFICATION);
    call.hdc = (ULONG_PTR)hdc;
    call.extra = (ULONG_PTR)extra;
    call.breaks = (ULONG_PTR)breaks;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTextJustification(struct qemu_syscall *call)
{
    struct qemu_SetTextJustification *c = (struct qemu_SetTextJustification *)call;
    WINE_TRACE("\n");
    c->super.iret = SetTextJustification(QEMU_G2H(c->hdc), c->extra, c->breaks);
}

#endif

struct qemu_GetTextFaceA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t count;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetTextFaceA(HDC hdc, INT count, LPSTR name)
{
    struct qemu_GetTextFaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTFACEA);
    call.hdc = (ULONG_PTR)hdc;
    call.count = (ULONG_PTR)count;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextFaceA(struct qemu_syscall *call)
{
    struct qemu_GetTextFaceA *c = (struct qemu_GetTextFaceA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextFaceA(QEMU_G2H(c->hdc), c->count, QEMU_G2H(c->name));
}

#endif

struct qemu_GetTextFaceW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t count;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetTextFaceW(HDC hdc, INT count, LPWSTR name)
{
    struct qemu_GetTextFaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTFACEW);
    call.hdc = (ULONG_PTR)hdc;
    call.count = (ULONG_PTR)count;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextFaceW(struct qemu_syscall *call)
{
    struct qemu_GetTextFaceW *c = (struct qemu_GetTextFaceW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextFaceW(QEMU_G2H(c->hdc), c->count, QEMU_G2H(c->name));
}

#endif

struct qemu_GetTextExtentPoint32A
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextExtentPoint32A(HDC hdc, LPCSTR str, INT count, LPSIZE size)
{
    struct qemu_GetTextExtentPoint32A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTPOINT32A);
    call.hdc = (ULONG_PTR)hdc;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentPoint32A(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentPoint32A *c = (struct qemu_GetTextExtentPoint32A *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentPoint32A(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentPoint32W
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextExtentPoint32W(HDC hdc, LPCWSTR str, INT count, LPSIZE size)
{
    struct qemu_GetTextExtentPoint32W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTPOINT32W);
    call.hdc = (ULONG_PTR)hdc;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentPoint32W(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentPoint32W *c = (struct qemu_GetTextExtentPoint32W *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentPoint32W(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentExPointI
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t indices;
    uint64_t count;
    uint64_t max_ext;
    uint64_t nfit;
    uint64_t dxs;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI WINBOOL WINAPI GetTextExtentExPointI(HDC hdc, WORD *indices, int count, int max_ext, LPINT nfit, LPINT dxs, LPSIZE size)
{
    struct qemu_GetTextExtentExPointI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTEXPOINTI);
    call.hdc = (ULONG_PTR)hdc;
    call.indices = (ULONG_PTR)indices;
    call.count = (ULONG_PTR)count;
    call.max_ext = (ULONG_PTR)max_ext;
    call.nfit = (ULONG_PTR)nfit;
    call.dxs = (ULONG_PTR)dxs;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentExPointI(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentExPointI *c = (struct qemu_GetTextExtentExPointI *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentExPointI(QEMU_G2H(c->hdc), QEMU_G2H(c->indices), c->count, c->max_ext, QEMU_G2H(c->nfit), QEMU_G2H(c->dxs), QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentPointI
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t indices;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI WINBOOL WINAPI GetTextExtentPointI(HDC hdc, WORD *indices, int count, LPSIZE size)
{
    struct qemu_GetTextExtentPointI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTPOINTI);
    call.hdc = (ULONG_PTR)hdc;
    call.indices = (ULONG_PTR)indices;
    call.count = (ULONG_PTR)count;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentPointI(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentPointI *c = (struct qemu_GetTextExtentPointI *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTextExtentPointI(QEMU_G2H(c->hdc), QEMU_G2H(c->indices), c->count, QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentPointA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextExtentPointA(HDC hdc, LPCSTR str, INT count, LPSIZE size)
{
    struct qemu_GetTextExtentPointA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTPOINTA);
    call.hdc = (ULONG_PTR)hdc;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentPointA(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentPointA *c = (struct qemu_GetTextExtentPointA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentPointA(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentPointW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextExtentPointW(HDC hdc, LPCWSTR str, INT count, LPSIZE size)
{
    struct qemu_GetTextExtentPointW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTPOINTW);
    call.hdc = (ULONG_PTR)hdc;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentPointW(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentPointW *c = (struct qemu_GetTextExtentPointW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentPointW(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentExPointA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t maxExt;
    uint64_t lpnFit;
    uint64_t alpDx;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextExtentExPointA(HDC hdc, LPCSTR str, INT count, INT maxExt, LPINT lpnFit, LPINT alpDx, LPSIZE size)
{
    struct qemu_GetTextExtentExPointA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTEXPOINTA);
    call.hdc = (ULONG_PTR)hdc;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.maxExt = (ULONG_PTR)maxExt;
    call.lpnFit = (ULONG_PTR)lpnFit;
    call.alpDx = (ULONG_PTR)alpDx;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentExPointA(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentExPointA *c = (struct qemu_GetTextExtentExPointA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentExPointA(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, c->maxExt, QEMU_G2H(c->lpnFit), QEMU_G2H(c->alpDx), QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextExtentExPointW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t max_ext;
    uint64_t nfit;
    uint64_t dxs;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextExtentExPointW(HDC hdc, LPCWSTR str, INT count, INT max_ext, LPINT nfit, LPINT dxs, LPSIZE size)
{
    struct qemu_GetTextExtentExPointW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTEXTENTEXPOINTW);
    call.hdc = (ULONG_PTR)hdc;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.max_ext = (ULONG_PTR)max_ext;
    call.nfit = (ULONG_PTR)nfit;
    call.dxs = (ULONG_PTR)dxs;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentExPointW(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentExPointW *c = (struct qemu_GetTextExtentExPointW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextExtentExPointW(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, c->max_ext, QEMU_G2H(c->nfit), QEMU_G2H(c->dxs), QEMU_G2H(c->size));
}

#endif

struct qemu_GetTextMetricsA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t metrics;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextMetricsA(HDC hdc, TEXTMETRICA *metrics)
{
    struct qemu_GetTextMetricsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTMETRICSA);
    call.hdc = (ULONG_PTR)hdc;
    call.metrics = (ULONG_PTR)metrics;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextMetricsA(struct qemu_syscall *call)
{
    struct qemu_GetTextMetricsA *c = (struct qemu_GetTextMetricsA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextMetricsA(QEMU_G2H(c->hdc), QEMU_G2H(c->metrics));
}

#endif

struct qemu_GetTextMetricsW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t metrics;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTextMetricsW(HDC hdc, TEXTMETRICW *metrics)
{
    struct qemu_GetTextMetricsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTMETRICSW);
    call.hdc = (ULONG_PTR)hdc;
    call.metrics = (ULONG_PTR)metrics;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextMetricsW(struct qemu_syscall *call)
{
    struct qemu_GetTextMetricsW *c = (struct qemu_GetTextMetricsW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextMetricsW((HDC)c->hdc, QEMU_G2H(c->metrics));
}

#endif

struct qemu_GetOutlineTextMetricsA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t cbData;
    uint64_t lpOTM;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetOutlineTextMetricsA(HDC hdc, UINT cbData, LPOUTLINETEXTMETRICA lpOTM)
{
    struct qemu_GetOutlineTextMetricsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOUTLINETEXTMETRICSA);
    call.hdc = (ULONG_PTR)hdc;
    call.cbData = (ULONG_PTR)cbData;
    call.lpOTM = (ULONG_PTR)lpOTM;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOutlineTextMetricsA(struct qemu_syscall *call)
{
    struct qemu_GetOutlineTextMetricsA *c = (struct qemu_GetOutlineTextMetricsA *)call;
    OUTLINETEXTMETRICA *metric;
    UINT size, num, i;
    struct qemu_OUTLINETEXTMETRICA *metric32, copy32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    metric = QEMU_G2H(c->lpOTM);
    size = c->cbData;
#else
    if (!c->lpOTM)
    {
        metric = NULL;
        size = c->cbData;
    }
    else
    {
        size = c->cbData + sizeof(*metric) - sizeof(*metric32);
        WINE_TRACE("Size in %u, size out %u.\n", (unsigned int)c->cbData, size);
        metric = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        metric->otmSize = size;
    }
#endif

    c->super.iret = GetOutlineTextMetricsA(QEMU_G2H(c->hdc), size, metric);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret)
    {
        if (c->lpOTM)
        {
            metric32 = QEMU_G2H(c->lpOTM);
            OUTLINETEXTMETRICA_h2g(&copy32, metric);
            copy32.otmSize += sizeof(copy32) - sizeof(*metric);
            memcpy(metric32, &copy32, min(sizeof(copy32), c->cbData));

            if (size > sizeof(*metric))
            {
                memcpy((char *)metric32 + sizeof(*metric32), (char *)metric + sizeof(*metric), size - sizeof(*metric));

                /* The string pointers are relative to the start of the metric structure, so just adjust for size. */
                if (metric32->otmpFamilyName)
                    metric32->otmpFamilyName += sizeof(*metric32) - sizeof(*metric);

                if (metric32->otmpFaceName)
                    metric32->otmpFaceName += sizeof(*metric32) - sizeof(*metric);

                if (metric32->otmpStyleName)
                    metric32->otmpStyleName += sizeof(*metric32) - sizeof(*metric);

                if (metric32->otmpFullName)
                    metric32->otmpFullName += sizeof(*metric32) - sizeof(*metric);
            }
        }
        c->super.iret += sizeof(struct qemu_OUTLINETEXTMETRICA) - sizeof(OUTLINETEXTMETRICA);
    }
    HeapFree(GetProcessHeap(), 0, metric);
#endif
}

#endif

struct qemu_GetOutlineTextMetricsW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t cbData;
    uint64_t lpOTM;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetOutlineTextMetricsW(HDC hdc, UINT cbData, LPOUTLINETEXTMETRICW lpOTM)
{
    struct qemu_GetOutlineTextMetricsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOUTLINETEXTMETRICSW);
    call.hdc = (ULONG_PTR)hdc;
    call.cbData = (ULONG_PTR)cbData;
    call.lpOTM = (ULONG_PTR)lpOTM;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOutlineTextMetricsW(struct qemu_syscall *call)
{
    struct qemu_GetOutlineTextMetricsW *c = (struct qemu_GetOutlineTextMetricsW *)call;
    OUTLINETEXTMETRICW *metric;
    UINT size, num, i;
    struct qemu_OUTLINETEXTMETRICW *metric32, copy32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    metric = QEMU_G2H(c->lpOTM);
    size = c->cbData;
#else
    if (!c->lpOTM)
    {
        metric = NULL;
        size = c->cbData;
    }
    else
    {
        size = c->cbData + sizeof(*metric) - sizeof(*metric32);
        WINE_TRACE("size in %u, size out %u\n", (unsigned int)c->cbData, size);
        metric = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        metric->otmSize = size;
    }
#endif

    c->super.iret = GetOutlineTextMetricsW(QEMU_G2H(c->hdc), size, metric);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret)
    {
        if (c->lpOTM)
        {
            metric32 = QEMU_G2H(c->lpOTM);
            OUTLINETEXTMETRICW_h2g(&copy32, metric);
            copy32.otmSize += sizeof(copy32) - sizeof(*metric);
            memcpy(metric32, &copy32, min(sizeof(copy32), c->cbData));

            if (size > sizeof(*metric))
            {
                memcpy((char *)metric32 + sizeof(*metric32), (char *)metric + sizeof(*metric), size - sizeof(*metric));

                /* The string pointers are relative to the start of the metric structure, so just adjust for size. */
                if (metric32->otmpFamilyName)
                    metric32->otmpFamilyName += sizeof(*metric32) - sizeof(*metric);

                if (metric32->otmpFaceName)
                    metric32->otmpFaceName += sizeof(*metric32) - sizeof(*metric);

                if (metric32->otmpStyleName)
                    metric32->otmpStyleName += sizeof(*metric32) - sizeof(*metric);

                if (metric32->otmpFullName)
                    metric32->otmpFullName += sizeof(*metric32) - sizeof(*metric);
            }
        }
        c->super.iret += sizeof(struct qemu_OUTLINETEXTMETRICW) - sizeof(OUTLINETEXTMETRICW);
    }
    HeapFree(GetProcessHeap(), 0, metric);
#endif
}

#endif

struct qemu_GetCharWidth32W
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t firstChar;
    uint64_t lastChar;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharWidth32W(HDC hdc, UINT firstChar, UINT lastChar, LPINT buffer)
{
    struct qemu_GetCharWidth32W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARWIDTH32W);
    call.hdc = (ULONG_PTR)hdc;
    call.firstChar = (ULONG_PTR)firstChar;
    call.lastChar = (ULONG_PTR)lastChar;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharWidth32W(struct qemu_syscall *call)
{
    struct qemu_GetCharWidth32W *c = (struct qemu_GetCharWidth32W *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharWidth32W(QEMU_G2H(c->hdc), c->firstChar, c->lastChar, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetCharWidth32A
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t firstChar;
    uint64_t lastChar;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharWidth32A(HDC hdc, UINT firstChar, UINT lastChar, LPINT buffer)
{
    struct qemu_GetCharWidth32A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARWIDTH32A);
    call.hdc = (ULONG_PTR)hdc;
    call.firstChar = (ULONG_PTR)firstChar;
    call.lastChar = (ULONG_PTR)lastChar;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharWidth32A(struct qemu_syscall *call)
{
    struct qemu_GetCharWidth32A *c = (struct qemu_GetCharWidth32A *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharWidth32A(QEMU_G2H(c->hdc), c->firstChar, c->lastChar, QEMU_G2H(c->buffer));
}

#endif

struct qemu_ExtTextOutA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t flags;
    uint64_t lprect;
    uint64_t str;
    uint64_t count;
    uint64_t lpDx;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI ExtTextOutA(HDC hdc, INT x, INT y, UINT flags, const RECT *lprect, LPCSTR str, UINT count, const INT *lpDx)
{
    struct qemu_ExtTextOutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTTEXTOUTA);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.flags = (ULONG_PTR)flags;
    call.lprect = (ULONG_PTR)lprect;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;
    call.lpDx = (ULONG_PTR)lpDx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtTextOutA(struct qemu_syscall *call)
{
    struct qemu_ExtTextOutA *c = (struct qemu_ExtTextOutA *)call;
    WINE_TRACE("\n");
    c->super.iret = ExtTextOutA(QEMU_G2H(c->hdc), c->x, c->y, c->flags, QEMU_G2H(c->lprect), QEMU_G2H(c->str), c->count, QEMU_G2H(c->lpDx));
}

#endif

struct qemu_ExtTextOutW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t flags;
    uint64_t lprect;
    uint64_t str;
    uint64_t count;
    uint64_t lpDx;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI ExtTextOutW(HDC hdc, INT x, INT y, UINT flags, const RECT *lprect, LPCWSTR str, UINT count, const INT *lpDx)
{
    struct qemu_ExtTextOutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTTEXTOUTW);
    call.hdc = (ULONG_PTR)hdc;
    call.x = x;
    call.y = y;
    call.flags = flags;
    call.lprect = (ULONG_PTR)lprect;
    call.str = (ULONG_PTR)str;
    call.count = count;
    call.lpDx = (ULONG_PTR)lpDx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtTextOutW(struct qemu_syscall *call)
{
    struct qemu_ExtTextOutW *c = (struct qemu_ExtTextOutW *)call;
    WINE_TRACE("\n");
    c->super.iret = ExtTextOutW(QEMU_G2H(c->hdc), c->x, c->y, c->flags, QEMU_G2H(c->lprect), QEMU_G2H(c->str), c->count, QEMU_G2H(c->lpDx));
}

#endif

struct qemu_TextOutA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t str;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI TextOutA(HDC hdc, INT x, INT y, LPCSTR str, INT count)
{
    struct qemu_TextOutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TEXTOUTA);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TextOutA(struct qemu_syscall *call)
{
    struct qemu_TextOutA *c = (struct qemu_TextOutA *)call;
    WINE_TRACE("\n");
    c->super.iret = TextOutA(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->str), c->count);
}

#endif

struct qemu_TextOutW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t str;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI TextOutW(HDC hdc, INT x, INT y, LPCWSTR str, INT count)
{
    struct qemu_TextOutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TEXTOUTW);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TextOutW(struct qemu_syscall *call)
{
    struct qemu_TextOutW *c = (struct qemu_TextOutW *)call;
    WINE_TRACE("\n");
    c->super.iret = TextOutW(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->str), c->count);
}

#endif

struct qemu_PolyTextOutA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pptxt;
    uint64_t cStrings;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI PolyTextOutA(HDC hdc, const POLYTEXTA *pptxt, INT cStrings)
{
    struct qemu_PolyTextOutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYTEXTOUTA);
    call.hdc = (ULONG_PTR)hdc;
    call.pptxt = (ULONG_PTR)pptxt;
    call.cStrings = (ULONG_PTR)cStrings;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyTextOutA(struct qemu_syscall *call)
{
    struct qemu_PolyTextOutA *c = (struct qemu_PolyTextOutA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolyTextOutA(QEMU_G2H(c->hdc), QEMU_G2H(c->pptxt), c->cStrings);
}

#endif

struct qemu_PolyTextOutW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pptxt;
    uint64_t cStrings;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI PolyTextOutW(HDC hdc, const POLYTEXTW *pptxt, INT cStrings)
{
    struct qemu_PolyTextOutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYTEXTOUTW);
    call.hdc = (ULONG_PTR)hdc;
    call.pptxt = (ULONG_PTR)pptxt;
    call.cStrings = (ULONG_PTR)cStrings;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyTextOutW(struct qemu_syscall *call)
{
    struct qemu_PolyTextOutW *c = (struct qemu_PolyTextOutW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolyTextOutW(QEMU_G2H(c->hdc), QEMU_G2H(c->pptxt), c->cStrings);
}

#endif

struct qemu_SetMapperFlags
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI SetMapperFlags(HDC hdc, DWORD flags)
{
    struct qemu_SetMapperFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMAPPERFLAGS);
    call.hdc = (ULONG_PTR)hdc;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMapperFlags(struct qemu_syscall *call)
{
    struct qemu_SetMapperFlags *c = (struct qemu_SetMapperFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMapperFlags(QEMU_G2H(c->hdc), c->flags);
}

#endif

struct qemu_GetAspectRatioFilterEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pAspectRatio;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetAspectRatioFilterEx(HDC hdc, LPSIZE pAspectRatio)
{
    struct qemu_GetAspectRatioFilterEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETASPECTRATIOFILTEREX);
    call.hdc = (ULONG_PTR)hdc;
    call.pAspectRatio = (ULONG_PTR)pAspectRatio;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAspectRatioFilterEx(struct qemu_syscall *call)
{
    struct qemu_GetAspectRatioFilterEx *c = (struct qemu_GetAspectRatioFilterEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAspectRatioFilterEx(QEMU_G2H(c->hdc), QEMU_G2H(c->pAspectRatio));
}

#endif

struct qemu_GetCharABCWidthsA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t firstChar;
    uint64_t lastChar;
    uint64_t abc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharABCWidthsA(HDC hdc, UINT firstChar, UINT lastChar, LPABC abc)
{
    struct qemu_GetCharABCWidthsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARABCWIDTHSA);
    call.hdc = (ULONG_PTR)hdc;
    call.firstChar = (ULONG_PTR)firstChar;
    call.lastChar = (ULONG_PTR)lastChar;
    call.abc = (ULONG_PTR)abc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharABCWidthsA(struct qemu_syscall *call)
{
    struct qemu_GetCharABCWidthsA *c = (struct qemu_GetCharABCWidthsA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharABCWidthsA(QEMU_G2H(c->hdc), c->firstChar, c->lastChar, QEMU_G2H(c->abc));
}

#endif

struct qemu_GetCharABCWidthsW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t firstChar;
    uint64_t lastChar;
    uint64_t abc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharABCWidthsW(HDC hdc, UINT firstChar, UINT lastChar, LPABC abc)
{
    struct qemu_GetCharABCWidthsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARABCWIDTHSW);
    call.hdc = (ULONG_PTR)hdc;
    call.firstChar = (ULONG_PTR)firstChar;
    call.lastChar = (ULONG_PTR)lastChar;
    call.abc = (ULONG_PTR)abc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharABCWidthsW(struct qemu_syscall *call)
{
    struct qemu_GetCharABCWidthsW *c = (struct qemu_GetCharABCWidthsW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharABCWidthsW(QEMU_G2H(c->hdc), c->firstChar, c->lastChar, QEMU_G2H(c->abc));
}

#endif

struct qemu_GetCharABCWidthsI
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t firstChar;
    uint64_t count;
    uint64_t pgi;
    uint64_t abc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharABCWidthsI(HDC hdc, UINT firstChar, UINT count, LPWORD pgi, LPABC abc)
{
    struct qemu_GetCharABCWidthsI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARABCWIDTHSI);
    call.hdc = (ULONG_PTR)hdc;
    call.firstChar = firstChar;
    call.count = count;
    call.pgi = (ULONG_PTR)pgi;
    call.abc = (ULONG_PTR)abc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharABCWidthsI(struct qemu_syscall *call)
{
    struct qemu_GetCharABCWidthsI *c = (struct qemu_GetCharABCWidthsI *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharABCWidthsI(QEMU_G2H(c->hdc), c->firstChar, c->count, QEMU_G2H(c->pgi), QEMU_G2H(c->abc));
}

#endif

struct qemu_GetGlyphOutlineA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t uChar;
    uint64_t fuFormat;
    uint64_t lpgm;
    uint64_t cbBuffer;
    uint64_t lpBuffer;
    uint64_t lpmat2;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetGlyphOutlineA(HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2 *lpmat2)
{
    struct qemu_GetGlyphOutlineA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGLYPHOUTLINEA);
    call.hdc = (ULONG_PTR)hdc;
    call.uChar = (ULONG_PTR)uChar;
    call.fuFormat = (ULONG_PTR)fuFormat;
    call.lpgm = (ULONG_PTR)lpgm;
    call.cbBuffer = (ULONG_PTR)cbBuffer;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.lpmat2 = (ULONG_PTR)lpmat2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGlyphOutlineA(struct qemu_syscall *call)
{
    struct qemu_GetGlyphOutlineA *c = (struct qemu_GetGlyphOutlineA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetGlyphOutlineA(QEMU_G2H(c->hdc), c->uChar, c->fuFormat, QEMU_G2H(c->lpgm), c->cbBuffer, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpmat2));
}

#endif

struct qemu_GetGlyphOutlineW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t uChar;
    uint64_t fuFormat;
    uint64_t lpgm;
    uint64_t cbBuffer;
    uint64_t lpBuffer;
    uint64_t lpmat2;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetGlyphOutlineW(HDC hdc, UINT uChar, UINT fuFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer, const MAT2 *lpmat2)
{
    struct qemu_GetGlyphOutlineW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGLYPHOUTLINEW);
    call.hdc = (ULONG_PTR)hdc;
    call.uChar = (ULONG_PTR)uChar;
    call.fuFormat = (ULONG_PTR)fuFormat;
    call.lpgm = (ULONG_PTR)lpgm;
    call.cbBuffer = (ULONG_PTR)cbBuffer;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.lpmat2 = (ULONG_PTR)lpmat2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGlyphOutlineW(struct qemu_syscall *call)
{
    struct qemu_GetGlyphOutlineW *c = (struct qemu_GetGlyphOutlineW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetGlyphOutlineW(QEMU_G2H(c->hdc), c->uChar, c->fuFormat, QEMU_G2H(c->lpgm), c->cbBuffer, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpmat2));
}

#endif

struct qemu_CreateScalableFontResourceA
{
    struct qemu_syscall super;
    uint64_t fHidden;
    uint64_t lpszResourceFile;
    uint64_t lpszFontFile;
    uint64_t lpszCurrentPath;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI CreateScalableFontResourceA(DWORD fHidden, LPCSTR lpszResourceFile, LPCSTR lpszFontFile, LPCSTR lpszCurrentPath)
{
    struct qemu_CreateScalableFontResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESCALABLEFONTRESOURCEA);
    call.fHidden = (ULONG_PTR)fHidden;
    call.lpszResourceFile = (ULONG_PTR)lpszResourceFile;
    call.lpszFontFile = (ULONG_PTR)lpszFontFile;
    call.lpszCurrentPath = (ULONG_PTR)lpszCurrentPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateScalableFontResourceA(struct qemu_syscall *call)
{
    struct qemu_CreateScalableFontResourceA *c = (struct qemu_CreateScalableFontResourceA *)call;
    WINE_TRACE("\n");
    c->super.iret = CreateScalableFontResourceA(c->fHidden, QEMU_G2H(c->lpszResourceFile), QEMU_G2H(c->lpszFontFile), QEMU_G2H(c->lpszCurrentPath));
}

#endif

struct qemu_CreateScalableFontResourceW
{
    struct qemu_syscall super;
    uint64_t hidden;
    uint64_t resource_file;
    uint64_t font_file;
    uint64_t font_path;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI CreateScalableFontResourceW(DWORD hidden, LPCWSTR resource_file, LPCWSTR font_file, LPCWSTR font_path)
{
    struct qemu_CreateScalableFontResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESCALABLEFONTRESOURCEW);
    call.hidden = (ULONG_PTR)hidden;
    call.resource_file = (ULONG_PTR)resource_file;
    call.font_file = (ULONG_PTR)font_file;
    call.font_path = (ULONG_PTR)font_path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateScalableFontResourceW(struct qemu_syscall *call)
{
    struct qemu_CreateScalableFontResourceW *c = (struct qemu_CreateScalableFontResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateScalableFontResourceW(c->hidden, QEMU_G2H(c->resource_file), QEMU_G2H(c->font_file), QEMU_G2H(c->font_path));
}

#endif

struct qemu_GetKerningPairsA
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t cPairs;
    uint64_t kern_pairA;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetKerningPairsA(HDC hDC, DWORD cPairs, LPKERNINGPAIR kern_pairA)
{
    struct qemu_GetKerningPairsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKERNINGPAIRSA);
    call.hDC = (ULONG_PTR)hDC;
    call.cPairs = (ULONG_PTR)cPairs;
    call.kern_pairA = (ULONG_PTR)kern_pairA;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKerningPairsA(struct qemu_syscall *call)
{
    struct qemu_GetKerningPairsA *c = (struct qemu_GetKerningPairsA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetKerningPairsA(QEMU_G2H(c->hDC), c->cPairs, QEMU_G2H(c->kern_pairA));
}

#endif

struct qemu_GetKerningPairsW
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t cPairs;
    uint64_t lpKerningPairs;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetKerningPairsW(HDC hDC, DWORD cPairs, LPKERNINGPAIR lpKerningPairs)
{
    struct qemu_GetKerningPairsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKERNINGPAIRSW);
    call.hDC = (ULONG_PTR)hDC;
    call.cPairs = (ULONG_PTR)cPairs;
    call.lpKerningPairs = (ULONG_PTR)lpKerningPairs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKerningPairsW(struct qemu_syscall *call)
{
    struct qemu_GetKerningPairsW *c = (struct qemu_GetKerningPairsW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetKerningPairsW(QEMU_G2H(c->hDC), c->cPairs, QEMU_G2H(c->lpKerningPairs));
}

#endif

struct qemu_TranslateCharsetInfo
{
    struct qemu_syscall super;
    uint64_t lpSrc;
    uint64_t lpCs;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI TranslateCharsetInfo(LPDWORD lpSrc, LPCHARSETINFO lpCs, DWORD flags)
{
    struct qemu_TranslateCharsetInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATECHARSETINFO);
    call.lpSrc = (ULONG_PTR)lpSrc;
    call.lpCs = (ULONG_PTR)lpCs;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateCharsetInfo(struct qemu_syscall *call)
{
    struct qemu_TranslateCharsetInfo *c = (struct qemu_TranslateCharsetInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = TranslateCharsetInfo(QEMU_G2H(c->lpSrc), QEMU_G2H(c->lpCs), c->flags);
}

#endif

struct qemu_GetFontLanguageInfo
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetFontLanguageInfo(HDC hdc)
{
    struct qemu_GetFontLanguageInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFONTLANGUAGEINFO);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFontLanguageInfo(struct qemu_syscall *call)
{
    struct qemu_GetFontLanguageInfo *c = (struct qemu_GetFontLanguageInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFontLanguageInfo((HDC)c->hdc);
}

#endif

struct qemu_GetFontData
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t table;
    uint64_t offset;
    uint64_t buffer;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetFontData(HDC hdc, DWORD table, DWORD offset, LPVOID buffer, DWORD length)
{
    struct qemu_GetFontData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFONTDATA);
    call.hdc = (ULONG_PTR)hdc;
    call.table = (ULONG_PTR)table;
    call.offset = (ULONG_PTR)offset;
    call.buffer = (ULONG_PTR)buffer;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFontData(struct qemu_syscall *call)
{
    struct qemu_GetFontData *c = (struct qemu_GetFontData *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFontData(QEMU_G2H(c->hdc), c->table, c->offset, QEMU_G2H(c->buffer), c->length);
}

#endif

struct qemu_GetGlyphIndicesA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpstr;
    uint64_t count;
    uint64_t pgi;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetGlyphIndicesA(HDC hdc, LPCSTR lpstr, INT count, LPWORD pgi, DWORD flags)
{
    struct qemu_GetGlyphIndicesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGLYPHINDICESA);
    call.hdc = (ULONG_PTR)hdc;
    call.lpstr = (ULONG_PTR)lpstr;
    call.count = (ULONG_PTR)count;
    call.pgi = (ULONG_PTR)pgi;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGlyphIndicesA(struct qemu_syscall *call)
{
    struct qemu_GetGlyphIndicesA *c = (struct qemu_GetGlyphIndicesA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetGlyphIndicesA(QEMU_G2H(c->hdc), QEMU_G2H(c->lpstr), c->count, QEMU_G2H(c->pgi), c->flags);
}

#endif

struct qemu_GetGlyphIndicesW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpstr;
    uint64_t count;
    uint64_t pgi;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetGlyphIndicesW(HDC hdc, LPCWSTR lpstr, INT count, LPWORD pgi, DWORD flags)
{
    struct qemu_GetGlyphIndicesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGLYPHINDICESW);
    call.hdc = (ULONG_PTR)hdc;
    call.lpstr = (ULONG_PTR)lpstr;
    call.count = (ULONG_PTR)count;
    call.pgi = (ULONG_PTR)pgi;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGlyphIndicesW(struct qemu_syscall *call)
{
    struct qemu_GetGlyphIndicesW *c = (struct qemu_GetGlyphIndicesW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetGlyphIndicesW(QEMU_G2H(c->hdc), QEMU_G2H(c->lpstr), c->count, QEMU_G2H(c->pgi), c->flags);
}

#endif

struct qemu_GetCharacterPlacementA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpString;
    uint64_t uCount;
    uint64_t nMaxExtent;
    uint64_t lpResults;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetCharacterPlacementA(HDC hdc, LPCSTR lpString, INT uCount, INT nMaxExtent, GCP_RESULTSA *lpResults, DWORD dwFlags)
{
    struct qemu_GetCharacterPlacementA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARACTERPLACEMENTA);
    call.hdc = (ULONG_PTR)hdc;
    call.lpString = (ULONG_PTR)lpString;
    call.uCount = (ULONG_PTR)uCount;
    call.nMaxExtent = (ULONG_PTR)nMaxExtent;
    call.lpResults = (ULONG_PTR)lpResults;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharacterPlacementA(struct qemu_syscall *call)
{
    struct qemu_GetCharacterPlacementA *c = (struct qemu_GetCharacterPlacementA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCharacterPlacementA(QEMU_G2H(c->hdc), QEMU_G2H(c->lpString), c->uCount, c->nMaxExtent, QEMU_G2H(c->lpResults), c->dwFlags);
}

#endif

struct qemu_GetCharacterPlacementW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpString;
    uint64_t uCount;
    uint64_t nMaxExtent;
    uint64_t lpResults;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetCharacterPlacementW(HDC hdc, LPCWSTR lpString, INT uCount, INT nMaxExtent, GCP_RESULTSW *lpResults, DWORD dwFlags)
{
    struct qemu_GetCharacterPlacementW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARACTERPLACEMENTW);
    call.hdc = (ULONG_PTR)hdc;
    call.lpString = (ULONG_PTR)lpString;
    call.uCount = uCount;
    call.nMaxExtent = nMaxExtent;
    call.lpResults = (ULONG_PTR)lpResults;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharacterPlacementW(struct qemu_syscall *call)
{
    struct qemu_GetCharacterPlacementW *c = (struct qemu_GetCharacterPlacementW *)call;
    GCP_RESULTSW stack, *results = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    results = QEMU_G2H(c->lpResults);
#else
    if (c->lpResults)
        GCP_RESULTS_g2h(results, QEMU_G2H(c->lpResults));
    else
        results = NULL;
#endif

    c->super.iret = GetCharacterPlacementW((HDC)c->hdc, QEMU_G2H(c->lpString), c->uCount, c->nMaxExtent, results, c->dwFlags);

#if GUEST_BIT != HOST_BIT
    if (c->lpResults)
        GCP_RESULTS_h2g(QEMU_G2H(c->lpResults), results);
#endif
}

#endif

struct qemu_GetCharABCWidthsFloatA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t last;
    uint64_t abcf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharABCWidthsFloatA(HDC hdc, UINT first, UINT last, LPABCFLOAT abcf)
{
    struct qemu_GetCharABCWidthsFloatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARABCWIDTHSFLOATA);
    call.hdc = (ULONG_PTR)hdc;
    call.first = (ULONG_PTR)first;
    call.last = (ULONG_PTR)last;
    call.abcf = (ULONG_PTR)abcf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharABCWidthsFloatA(struct qemu_syscall *call)
{
    struct qemu_GetCharABCWidthsFloatA *c = (struct qemu_GetCharABCWidthsFloatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCharABCWidthsFloatA(QEMU_G2H(c->hdc), c->first, c->last, QEMU_G2H(c->abcf));
}

#endif

struct qemu_GetCharABCWidthsFloatW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t last;
    uint64_t abcf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharABCWidthsFloatW(HDC hdc, UINT first, UINT last, LPABCFLOAT abcf)
{
    struct qemu_GetCharABCWidthsFloatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARABCWIDTHSFLOATW);
    call.hdc = (ULONG_PTR)hdc;
    call.first = (ULONG_PTR)first;
    call.last = (ULONG_PTR)last;
    call.abcf = (ULONG_PTR)abcf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharABCWidthsFloatW(struct qemu_syscall *call)
{
    struct qemu_GetCharABCWidthsFloatW *c = (struct qemu_GetCharABCWidthsFloatW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharABCWidthsFloatW(QEMU_G2H(c->hdc), c->first, c->last, QEMU_G2H(c->abcf));
}

#endif

struct qemu_GetCharWidthFloatA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iFirstChar;
    uint64_t iLastChar;
    uint64_t pxBuffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharWidthFloatA(HDC hdc, UINT iFirstChar, UINT iLastChar, PFLOAT pxBuffer)
{
    struct qemu_GetCharWidthFloatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARWIDTHFLOATA);
    call.hdc = (ULONG_PTR)hdc;
    call.iFirstChar = (ULONG_PTR)iFirstChar;
    call.iLastChar = (ULONG_PTR)iLastChar;
    call.pxBuffer = (ULONG_PTR)pxBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharWidthFloatA(struct qemu_syscall *call)
{
    struct qemu_GetCharWidthFloatA *c = (struct qemu_GetCharWidthFloatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCharWidthFloatA(QEMU_G2H(c->hdc), c->iFirstChar, c->iLastChar, QEMU_G2H(c->pxBuffer));
}

#endif

struct qemu_GetCharWidthFloatW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iFirstChar;
    uint64_t iLastChar;
    uint64_t pxBuffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharWidthFloatW(HDC hdc, UINT iFirstChar, UINT iLastChar, PFLOAT pxBuffer)
{
    struct qemu_GetCharWidthFloatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARWIDTHFLOATW);
    call.hdc = (ULONG_PTR)hdc;
    call.iFirstChar = (ULONG_PTR)iFirstChar;
    call.iLastChar = (ULONG_PTR)iLastChar;
    call.pxBuffer = (ULONG_PTR)pxBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharWidthFloatW(struct qemu_syscall *call)
{
    struct qemu_GetCharWidthFloatW *c = (struct qemu_GetCharWidthFloatW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCharWidthFloatW(QEMU_G2H(c->hdc), c->iFirstChar, c->iLastChar, QEMU_G2H(c->pxBuffer));
}

#endif

struct qemu_AddFontResourceA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI AddFontResourceA(LPCSTR str)
{
    struct qemu_AddFontResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFONTRESOURCEA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddFontResourceA(struct qemu_syscall *call)
{
    struct qemu_AddFontResourceA *c = (struct qemu_AddFontResourceA *)call;
    WINE_TRACE("\n");
    c->super.iret = AddFontResourceA(QEMU_G2H(c->str));
}

#endif

struct qemu_AddFontResourceW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI AddFontResourceW(LPCWSTR str)
{
    struct qemu_AddFontResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFONTRESOURCEW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddFontResourceW(struct qemu_syscall *call)
{
    struct qemu_AddFontResourceW *c = (struct qemu_AddFontResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddFontResourceW(QEMU_G2H(c->str));
}

#endif

struct qemu_AddFontResourceExA
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t fl;
    uint64_t pdv;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI AddFontResourceExA(LPCSTR str, DWORD fl, PVOID pdv)
{
    struct qemu_AddFontResourceExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFONTRESOURCEEXA);
    call.str = (ULONG_PTR)str;
    call.fl = (ULONG_PTR)fl;
    call.pdv = (ULONG_PTR)pdv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddFontResourceExA(struct qemu_syscall *call)
{
    struct qemu_AddFontResourceExA *c = (struct qemu_AddFontResourceExA *)call;
    WINE_TRACE("\n");
    c->super.iret = AddFontResourceExA(QEMU_G2H(c->str), c->fl, QEMU_G2H(c->pdv));
}

#endif

struct qemu_AddFontResourceExW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t fl;
    uint64_t pdv;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI AddFontResourceExW(LPCWSTR str, DWORD fl, PVOID pdv)
{
    struct qemu_AddFontResourceExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFONTRESOURCEEXW);
    call.str = (ULONG_PTR)str;
    call.fl = (ULONG_PTR)fl;
    call.pdv = (ULONG_PTR)pdv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddFontResourceExW(struct qemu_syscall *call)
{
    struct qemu_AddFontResourceExW *c = (struct qemu_AddFontResourceExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddFontResourceExW(QEMU_G2H(c->str), c->fl, QEMU_G2H(c->pdv));
}

#endif

struct qemu_RemoveFontResourceA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI RemoveFontResourceA(LPCSTR str)
{
    struct qemu_RemoveFontResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEFONTRESOURCEA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveFontResourceA(struct qemu_syscall *call)
{
    struct qemu_RemoveFontResourceA *c = (struct qemu_RemoveFontResourceA *)call;
    WINE_TRACE("\n");
    c->super.iret = RemoveFontResourceA(QEMU_G2H(c->str));
}

#endif

struct qemu_RemoveFontResourceW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI RemoveFontResourceW(LPCWSTR str)
{
    struct qemu_RemoveFontResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEFONTRESOURCEW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveFontResourceW(struct qemu_syscall *call)
{
    struct qemu_RemoveFontResourceW *c = (struct qemu_RemoveFontResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RemoveFontResourceW(QEMU_G2H(c->str));
}

#endif

struct qemu_AddFontMemResourceEx
{
    struct qemu_syscall super;
    uint64_t pbFont;
    uint64_t cbFont;
    uint64_t pdv;
    uint64_t pcFonts;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HANDLE WINAPI AddFontMemResourceEx(PVOID pbFont, DWORD cbFont, PVOID pdv, DWORD *pcFonts)
{
    struct qemu_AddFontMemResourceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFONTMEMRESOURCEEX);
    call.pbFont = (ULONG_PTR)pbFont;
    call.cbFont = (ULONG_PTR)cbFont;
    call.pdv = (ULONG_PTR)pdv;
    call.pcFonts = (ULONG_PTR)pcFonts;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_AddFontMemResourceEx(struct qemu_syscall *call)
{
    struct qemu_AddFontMemResourceEx *c = (struct qemu_AddFontMemResourceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)AddFontMemResourceEx(QEMU_G2H(c->pbFont), c->cbFont, QEMU_G2H(c->pdv), QEMU_G2H(c->pcFonts));
}

#endif

struct qemu_RemoveFontMemResourceEx
{
    struct qemu_syscall super;
    uint64_t fh;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI RemoveFontMemResourceEx(HANDLE fh)
{
    struct qemu_RemoveFontMemResourceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEFONTMEMRESOURCEEX);
    call.fh = (ULONG_PTR)fh;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveFontMemResourceEx(struct qemu_syscall *call)
{
    struct qemu_RemoveFontMemResourceEx *c = (struct qemu_RemoveFontMemResourceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RemoveFontMemResourceEx(QEMU_G2H(c->fh));
}

#endif

struct qemu_RemoveFontResourceExA
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t fl;
    uint64_t pdv;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI RemoveFontResourceExA(LPCSTR str, DWORD fl, PVOID pdv)
{
    struct qemu_RemoveFontResourceExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEFONTRESOURCEEXA);
    call.str = (ULONG_PTR)str;
    call.fl = (ULONG_PTR)fl;
    call.pdv = (ULONG_PTR)pdv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveFontResourceExA(struct qemu_syscall *call)
{
    struct qemu_RemoveFontResourceExA *c = (struct qemu_RemoveFontResourceExA *)call;
    WINE_TRACE("\n");
    c->super.iret = RemoveFontResourceExA(QEMU_G2H(c->str), c->fl, QEMU_G2H(c->pdv));
}

#endif

struct qemu_RemoveFontResourceExW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t fl;
    uint64_t pdv;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI RemoveFontResourceExW(LPCWSTR str, DWORD fl, PVOID pdv)
{
    struct qemu_RemoveFontResourceExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEFONTRESOURCEEXW);
    call.str = (ULONG_PTR)str;
    call.fl = (ULONG_PTR)fl;
    call.pdv = (ULONG_PTR)pdv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveFontResourceExW(struct qemu_syscall *call)
{
    struct qemu_RemoveFontResourceExW *c = (struct qemu_RemoveFontResourceExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RemoveFontResourceExW(QEMU_G2H(c->str), c->fl, QEMU_G2H(c->pdv));
}

#endif

struct qemu_GetFontResourceInfoW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size;
    uint64_t buffer;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetFontResourceInfoW(LPCWSTR str, LPDWORD size, PVOID buffer, DWORD type)
{
    struct qemu_GetFontResourceInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFONTRESOURCEINFOW);
    call.str = (ULONG_PTR)str;
    call.size = (ULONG_PTR)size;
    call.buffer = (ULONG_PTR)buffer;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFontResourceInfoW to Wine headers? */
extern BOOL WINAPI GetFontResourceInfoW(LPCWSTR str, LPDWORD size, PVOID buffer, DWORD type);
void qemu_GetFontResourceInfoW(struct qemu_syscall *call)
{
    struct qemu_GetFontResourceInfoW *c = (struct qemu_GetFontResourceInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFontResourceInfoW(QEMU_G2H(c->str), QEMU_G2H(c->size), QEMU_G2H(c->buffer), c->type);
}

#endif

struct qemu_GetTextCharset
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI int WINAPI GetTextCharset(HDC hdc)
{
    struct qemu_GetTextCharset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTCHARSET);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextCharset(struct qemu_syscall *call)
{
    struct qemu_GetTextCharset *c = (struct qemu_GetTextCharset *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextCharset(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GdiGetCharDimensions
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lptm;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI LONG WINAPI GdiGetCharDimensions(HDC hdc, LPTEXTMETRICW lptm, LONG *height)
{
    struct qemu_GdiGetCharDimensions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIGETCHARDIMENSIONS);
    call.hdc = (ULONG_PTR)hdc;
    call.lptm = (ULONG_PTR)lptm;
    call.height = (ULONG_PTR)height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiGetCharDimensions(struct qemu_syscall *call)
{
    struct qemu_GdiGetCharDimensions *c = (struct qemu_GdiGetCharDimensions *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiGetCharDimensions(QEMU_G2H(c->hdc), QEMU_G2H(c->lptm), QEMU_G2H(c->height));
}

#endif

struct qemu_EnableEUDC
{
    struct qemu_syscall super;
    uint64_t fEnableEUDC;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI EnableEUDC(BOOL fEnableEUDC)
{
    struct qemu_EnableEUDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLEEUDC);
    call.fEnableEUDC = (ULONG_PTR)fEnableEUDC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EnableEUDC to Wine headers? */
extern BOOL WINAPI EnableEUDC(BOOL fEnableEUDC);
void qemu_EnableEUDC(struct qemu_syscall *call)
{
    struct qemu_EnableEUDC *c = (struct qemu_EnableEUDC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableEUDC(c->fEnableEUDC);
}

#endif

struct qemu_GetCharWidthI
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t count;
    uint64_t glyphs;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCharWidthI(HDC hdc, UINT first, UINT count, LPWORD glyphs, LPINT buffer)
{
    struct qemu_GetCharWidthI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARWIDTHI);
    call.hdc = (ULONG_PTR)hdc;
    call.first = (ULONG_PTR)first;
    call.count = (ULONG_PTR)count;
    call.glyphs = (ULONG_PTR)glyphs;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharWidthI(struct qemu_syscall *call)
{
    struct qemu_GetCharWidthI *c = (struct qemu_GetCharWidthI *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharWidthI(QEMU_G2H(c->hdc), c->first, c->count, QEMU_G2H(c->glyphs), QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetFontUnicodeRanges
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpgs;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetFontUnicodeRanges(HDC hdc, LPGLYPHSET lpgs)
{
    struct qemu_GetFontUnicodeRanges call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFONTUNICODERANGES);
    call.hdc = (ULONG_PTR)hdc;
    call.lpgs = (ULONG_PTR)lpgs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFontUnicodeRanges(struct qemu_syscall *call)
{
    struct qemu_GetFontUnicodeRanges *c = (struct qemu_GetFontUnicodeRanges *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFontUnicodeRanges(QEMU_G2H(c->hdc), QEMU_G2H(c->lpgs));
}

#endif

struct qemu_FontIsLinked
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI FontIsLinked(HDC hdc)
{
    struct qemu_FontIsLinked call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FONTISLINKED);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FontIsLinked to Wine headers? */
extern BOOL WINAPI FontIsLinked(HDC hdc);
void qemu_FontIsLinked(struct qemu_syscall *call)
{
    struct qemu_FontIsLinked *c = (struct qemu_FontIsLinked *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FontIsLinked(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GetFontRealizationInfo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetFontRealizationInfo(HDC hdc, void *info)
{
    struct qemu_GetFontRealizationInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFONTREALIZATIONINFO);
    call.hdc = (ULONG_PTR)hdc;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFontRealizationInfo to Wine headers? */
extern BOOL WINAPI GetFontRealizationInfo(HDC hdc, void *info);
void qemu_GetFontRealizationInfo(struct qemu_syscall *call)
{
    struct qemu_GetFontRealizationInfo *c = (struct qemu_GetFontRealizationInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFontRealizationInfo(QEMU_G2H(c->hdc), QEMU_G2H(c->info));
}

#endif

struct qemu_GdiRealizationInfo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GdiRealizationInfo(HDC hdc, void *info)
{
    struct qemu_GdiRealizationInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIREALIZATIONINFO);
    call.hdc = (ULONG_PTR)hdc;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiRealizationInfo to Wine headers? */
extern BOOL WINAPI GdiRealizationInfo(HDC hdc, void *info);
void qemu_GdiRealizationInfo(struct qemu_syscall *call)
{
    struct qemu_GdiRealizationInfo *c = (struct qemu_GdiRealizationInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiRealizationInfo(QEMU_G2H(c->hdc), QEMU_G2H(c->info));
}

#endif

struct qemu_GetCharWidthInfo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

/* This struct is undocumented, but according to wine/dlls/gdi32/gdi_private.h consists only of INTs. */
struct char_width_info;

WINBASEAPI BOOL WINAPI GetCharWidthInfo(HDC hdc, struct char_width_info *info)
{
    struct qemu_GetCharWidthInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHARWIDTHINFO);
    call.hdc = (ULONG_PTR)hdc;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

WINBASEAPI BOOL WINAPI GetCharWidthInfo(HDC hdc, void *info);
void qemu_GetCharWidthInfo(struct qemu_syscall *call)
{
    struct qemu_GetCharWidthInfo *c = (struct qemu_GetCharWidthInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCharWidthInfo(QEMU_G2H(c->hdc), QEMU_G2H(c->info));
}

#endif
