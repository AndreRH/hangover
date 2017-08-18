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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.fs = (uint64_t)fs;
    call.flags = (uint64_t)flags;

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
    call.penumexA = (uint64_t)penumexA;

    qemu_syscall(&call.super);

    return (HFONT)call.super.iret;
}

#else

void qemu_CreateFontIndirectExA(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectExA *c = (struct qemu_CreateFontIndirectExA *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateFontIndirectExA(QEMU_G2H(c->penumexA));
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
    call.penumex = (uint64_t)penumex;

    qemu_syscall(&call.super);

    return (HFONT)call.super.iret;
}

#else

void qemu_CreateFontIndirectExW(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectExW *c = (struct qemu_CreateFontIndirectExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateFontIndirectExW(QEMU_G2H(c->penumex));
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
    call.plfA = (uint64_t)plfA;

    qemu_syscall(&call.super);

    return (HFONT)call.super.iret;
}

#else

void qemu_CreateFontIndirectA(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectA *c = (struct qemu_CreateFontIndirectA *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateFontIndirectA(QEMU_G2H(c->plfA));
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
    call.plf = (uint64_t)plf;

    qemu_syscall(&call.super);

    return (HFONT)call.super.iret;
}

#else

void qemu_CreateFontIndirectW(struct qemu_syscall *call)
{
    struct qemu_CreateFontIndirectW *c = (struct qemu_CreateFontIndirectW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateFontIndirectW(QEMU_G2H(c->plf));
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
    call.height = (uint64_t)height;
    call.width = (uint64_t)width;
    call.esc = (uint64_t)esc;
    call.orient = (uint64_t)orient;
    call.weight = (uint64_t)weight;
    call.italic = (uint64_t)italic;
    call.underline = (uint64_t)underline;
    call.strikeout = (uint64_t)strikeout;
    call.charset = (uint64_t)charset;
    call.outpres = (uint64_t)outpres;
    call.clippres = (uint64_t)clippres;
    call.quality = (uint64_t)quality;
    call.pitch = (uint64_t)pitch;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HFONT)call.super.iret;
}

#else

void qemu_CreateFontA(struct qemu_syscall *call)
{
    struct qemu_CreateFontA *c = (struct qemu_CreateFontA *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateFontA(c->height, c->width, c->esc, c->orient, c->weight, c->italic, c->underline, c->strikeout, c->charset, c->outpres, c->clippres, c->quality, c->pitch, QEMU_G2H(c->name));
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
    call.height = (uint64_t)height;
    call.width = (uint64_t)width;
    call.esc = (uint64_t)esc;
    call.orient = (uint64_t)orient;
    call.weight = (uint64_t)weight;
    call.italic = (uint64_t)italic;
    call.underline = (uint64_t)underline;
    call.strikeout = (uint64_t)strikeout;
    call.charset = (uint64_t)charset;
    call.outpres = (uint64_t)outpres;
    call.clippres = (uint64_t)clippres;
    call.quality = (uint64_t)quality;
    call.pitch = (uint64_t)pitch;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HFONT)call.super.iret;
}

#else

void qemu_CreateFontW(struct qemu_syscall *call)
{
    struct qemu_CreateFontW *c = (struct qemu_CreateFontW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateFontW(c->height, c->width, c->esc, c->orient, c->weight, c->italic, c->underline, c->strikeout, c->charset, c->outpres, c->clippres, c->quality, c->pitch, QEMU_G2H(c->name));
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

static uint64_t EnumFontFamiliesW_guest_cb(struct qemu_EnumFontFamilies_cb *data)
{
    FONTENUMPROCW proc = (FONTENUMPROCW)data->proc;
    return proc((const LOGFONTW *)data->font, (const TEXTMETRICW *)data->metric, data->type, data->param);
}

WINGDIAPI INT WINAPI EnumFontFamiliesExW(HDC hDC, LPLOGFONTW plf, FONTENUMPROCW efproc, LPARAM lParam, DWORD dwFlags)
{
    struct qemu_EnumFontFamiliesExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTFAMILIESEXW);
    call.hDC = (uint64_t)hDC;
    call.plf = (uint64_t)plf;
    call.efproc = (uint64_t)efproc;
    call.lParam = (uint64_t)lParam;
    call.dwFlags = dwFlags;
    call.wrapper = (uint64_t)EnumFontFamiliesW_guest_cb;

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
    struct qemu_EnumFontFamilies_cb call;
    INT ret;

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %u, 0x%lx).\n", data->guest_func, font, metric, type, data->guest_data);
    call.proc = data->guest_func;
    call.font = QEMU_H2G(font);
    call.metric = QEMU_H2G(metric);
    call.type = type;
    call.param = data->guest_data;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %u.\n", ret);
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

static uint64_t EnumFontFamiliesA_guest_cb(struct qemu_EnumFontFamilies_cb *data)
{
    FONTENUMPROCA proc = (FONTENUMPROCA)data->proc;
    return proc((const LOGFONTA *)data->font, (const TEXTMETRICA *)data->metric, data->type, data->param);
}

WINGDIAPI INT WINAPI EnumFontFamiliesExA(HDC hDC, LPLOGFONTA plf, FONTENUMPROCA efproc, LPARAM lParam, DWORD dwFlags)
{
    struct qemu_EnumFontFamiliesExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTFAMILIESEXA);
    call.hDC = (uint64_t)hDC;
    call.plf = (uint64_t)plf;
    call.efproc = (uint64_t)efproc;
    call.lParam = (uint64_t)lParam;
    call.dwFlags = dwFlags;
    call.wrapper = (uint64_t)EnumFontFamiliesA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static INT CALLBACK qemu_EnumFontFamiliesA_host_proc(const LOGFONTA *font, const TEXTMETRICA *metric, DWORD type, LPARAM param)
{
    struct qemu_EnumFontFamilies_host_data *data = (struct qemu_EnumFontFamilies_host_data *)param;
    struct qemu_EnumFontFamilies_cb call;
    INT ret;

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %u, 0x%lx).\n", data->guest_func, font, metric, type, data->guest_data);
    call.proc = data->guest_func;
    call.font = QEMU_H2G(font);
    call.metric = QEMU_H2G(metric);
    call.type = type;
    call.param = data->guest_data;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %u.\n", ret);
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
            c->efproc ? qemu_EnumFontFamiliesA_host_proc : NULL, (LPARAM)&data, c->dwFlags);
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
    call.hDC = (uint64_t)hDC;
    call.lpFamily = (uint64_t)lpFamily;
    call.efproc = (uint64_t)efproc;
    call.lpData = (uint64_t)lpData;
    call.wrapper = (uint64_t)EnumFontFamiliesA_guest_cb;

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
    call.hDC = (uint64_t)hDC;
    call.lpFamily = (uint64_t)lpFamily;
    call.efproc = (uint64_t)efproc;
    call.lpData = (uint64_t)lpData;
    call.wrapper = (uint64_t)EnumFontFamiliesW_guest_cb;

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
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumFontsA(HDC hDC, LPCSTR lpName, FONTENUMPROCA efproc, LPARAM lpData)
{
    struct qemu_EnumFontsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTSA);
    call.hDC = (uint64_t)hDC;
    call.lpName = (uint64_t)lpName;
    call.efproc = (uint64_t)efproc;
    call.lpData = (uint64_t)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFontsA(struct qemu_syscall *call)
{
    struct qemu_EnumFontsA *c = (struct qemu_EnumFontsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumFontsA(QEMU_G2H(c->hDC), QEMU_G2H(c->lpName), QEMU_G2H(c->efproc), c->lpData);
}

#endif

struct qemu_EnumFontsW
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpName;
    uint64_t efproc;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EnumFontsW(HDC hDC, LPCWSTR lpName, FONTENUMPROCW efproc, LPARAM lpData)
{
    struct qemu_EnumFontsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFONTSW);
    call.hDC = (uint64_t)hDC;
    call.lpName = (uint64_t)lpName;
    call.efproc = (uint64_t)efproc;
    call.lpData = (uint64_t)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFontsW(struct qemu_syscall *call)
{
    struct qemu_EnumFontsW *c = (struct qemu_EnumFontsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumFontsW(QEMU_G2H(c->hDC), QEMU_G2H(c->lpName), QEMU_G2H(c->efproc), c->lpData);
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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.extra = (uint64_t)extra;

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
    call.hdc = (uint64_t)hdc;
    call.extra = (uint64_t)extra;
    call.breaks = (uint64_t)breaks;

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
    call.hdc = (uint64_t)hdc;
    call.count = (uint64_t)count;
    call.name = (uint64_t)name;

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
    call.hdc = (uint64_t)hdc;
    call.count = (uint64_t)count;
    call.name = (uint64_t)name;

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
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextExtentPoint32W(struct qemu_syscall *call)
{
    struct qemu_GetTextExtentPoint32W *c = (struct qemu_GetTextExtentPoint32W *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hdc = (uint64_t)hdc;
    call.indices = (uint64_t)indices;
    call.count = (uint64_t)count;
    call.max_ext = (uint64_t)max_ext;
    call.nfit = (uint64_t)nfit;
    call.dxs = (uint64_t)dxs;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.indices = (uint64_t)indices;
    call.count = (uint64_t)count;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.maxExt = (uint64_t)maxExt;
    call.lpnFit = (uint64_t)lpnFit;
    call.alpDx = (uint64_t)alpDx;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.max_ext = (uint64_t)max_ext;
    call.nfit = (uint64_t)nfit;
    call.dxs = (uint64_t)dxs;
    call.size = (uint64_t)size;

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
    call.hdc = (uint64_t)hdc;
    call.metrics = (uint64_t)metrics;

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
    call.hdc = (uint64_t)hdc;
    call.metrics = (uint64_t)metrics;

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
    call.hdc = (uint64_t)hdc;
    call.cbData = (uint64_t)cbData;
    call.lpOTM = (uint64_t)lpOTM;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOutlineTextMetricsA(struct qemu_syscall *call)
{
    struct qemu_GetOutlineTextMetricsA *c = (struct qemu_GetOutlineTextMetricsA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetOutlineTextMetricsA(QEMU_G2H(c->hdc), c->cbData, QEMU_G2H(c->lpOTM));
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
    call.hdc = (uint64_t)hdc;
    call.cbData = (uint64_t)cbData;
    call.lpOTM = (uint64_t)lpOTM;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOutlineTextMetricsW(struct qemu_syscall *call)
{
    struct qemu_GetOutlineTextMetricsW *c = (struct qemu_GetOutlineTextMetricsW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetOutlineTextMetricsW(QEMU_G2H(c->hdc), c->cbData, QEMU_G2H(c->lpOTM));
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
    call.hdc = (uint64_t)hdc;
    call.firstChar = (uint64_t)firstChar;
    call.lastChar = (uint64_t)lastChar;
    call.buffer = (uint64_t)buffer;

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
    call.hdc = (uint64_t)hdc;
    call.firstChar = (uint64_t)firstChar;
    call.lastChar = (uint64_t)lastChar;
    call.buffer = (uint64_t)buffer;

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
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.flags = (uint64_t)flags;
    call.lprect = (uint64_t)lprect;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.lpDx = (uint64_t)lpDx;

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
    call.hdc = (uint64_t)hdc;
    call.x = x;
    call.y = y;
    call.flags = flags;
    call.lprect = (uint64_t)lprect;
    call.str = (uint64_t)str;
    call.count = count;
    call.lpDx = (uint64_t)lpDx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtTextOutW(struct qemu_syscall *call)
{
    struct qemu_ExtTextOutW *c = (struct qemu_ExtTextOutW *)call;
    WINE_TRACE("Unverified!\n");
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
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TextOutA(struct qemu_syscall *call)
{
    struct qemu_TextOutA *c = (struct qemu_TextOutA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TextOutW(struct qemu_syscall *call)
{
    struct qemu_TextOutW *c = (struct qemu_TextOutW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hdc = (uint64_t)hdc;
    call.pptxt = (uint64_t)pptxt;
    call.cStrings = (uint64_t)cStrings;

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
    call.hdc = (uint64_t)hdc;
    call.pptxt = (uint64_t)pptxt;
    call.cStrings = (uint64_t)cStrings;

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
    call.hdc = (uint64_t)hdc;
    call.flags = (uint64_t)flags;

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
    call.hdc = (uint64_t)hdc;
    call.pAspectRatio = (uint64_t)pAspectRatio;

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
    call.hdc = (uint64_t)hdc;
    call.firstChar = (uint64_t)firstChar;
    call.lastChar = (uint64_t)lastChar;
    call.abc = (uint64_t)abc;

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
    call.hdc = (uint64_t)hdc;
    call.firstChar = (uint64_t)firstChar;
    call.lastChar = (uint64_t)lastChar;
    call.abc = (uint64_t)abc;

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
    call.hdc = (uint64_t)hdc;
    call.firstChar = firstChar;
    call.count = count;
    call.pgi = (uint64_t)pgi;
    call.abc = (uint64_t)abc;

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
    call.hdc = (uint64_t)hdc;
    call.uChar = (uint64_t)uChar;
    call.fuFormat = (uint64_t)fuFormat;
    call.lpgm = (uint64_t)lpgm;
    call.cbBuffer = (uint64_t)cbBuffer;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.lpmat2 = (uint64_t)lpmat2;

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
    call.hdc = (uint64_t)hdc;
    call.uChar = (uint64_t)uChar;
    call.fuFormat = (uint64_t)fuFormat;
    call.lpgm = (uint64_t)lpgm;
    call.cbBuffer = (uint64_t)cbBuffer;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.lpmat2 = (uint64_t)lpmat2;

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
    call.fHidden = (uint64_t)fHidden;
    call.lpszResourceFile = (uint64_t)lpszResourceFile;
    call.lpszFontFile = (uint64_t)lpszFontFile;
    call.lpszCurrentPath = (uint64_t)lpszCurrentPath;

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
    call.hidden = (uint64_t)hidden;
    call.resource_file = (uint64_t)resource_file;
    call.font_file = (uint64_t)font_file;
    call.font_path = (uint64_t)font_path;

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
    call.hDC = (uint64_t)hDC;
    call.cPairs = (uint64_t)cPairs;
    call.kern_pairA = (uint64_t)kern_pairA;

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
    call.hDC = (uint64_t)hDC;
    call.cPairs = (uint64_t)cPairs;
    call.lpKerningPairs = (uint64_t)lpKerningPairs;

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
    call.lpSrc = (uint64_t)lpSrc;
    call.lpCs = (uint64_t)lpCs;
    call.flags = (uint64_t)flags;

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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.table = (uint64_t)table;
    call.offset = (uint64_t)offset;
    call.buffer = (uint64_t)buffer;
    call.length = (uint64_t)length;

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
    call.hdc = (uint64_t)hdc;
    call.lpstr = (uint64_t)lpstr;
    call.count = (uint64_t)count;
    call.pgi = (uint64_t)pgi;
    call.flags = (uint64_t)flags;

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
    call.hdc = (uint64_t)hdc;
    call.lpstr = (uint64_t)lpstr;
    call.count = (uint64_t)count;
    call.pgi = (uint64_t)pgi;
    call.flags = (uint64_t)flags;

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
    call.hdc = (uint64_t)hdc;
    call.lpString = (uint64_t)lpString;
    call.uCount = (uint64_t)uCount;
    call.nMaxExtent = (uint64_t)nMaxExtent;
    call.lpResults = (uint64_t)lpResults;
    call.dwFlags = (uint64_t)dwFlags;

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
    call.hdc = (uint64_t)hdc;
    call.lpString = (uint64_t)lpString;
    call.uCount = uCount;
    call.nMaxExtent = nMaxExtent;
    call.lpResults = (uint64_t)lpResults;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCharacterPlacementW(struct qemu_syscall *call)
{
    struct qemu_GetCharacterPlacementW *c = (struct qemu_GetCharacterPlacementW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCharacterPlacementW((HDC)c->hdc, QEMU_G2H(c->lpString), c->uCount, c->nMaxExtent, QEMU_G2H(c->lpResults), c->dwFlags);
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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;
    call.abcf = (uint64_t)abcf;

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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;
    call.abcf = (uint64_t)abcf;

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
    call.hdc = (uint64_t)hdc;
    call.iFirstChar = (uint64_t)iFirstChar;
    call.iLastChar = (uint64_t)iLastChar;
    call.pxBuffer = (uint64_t)pxBuffer;

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
    call.hdc = (uint64_t)hdc;
    call.iFirstChar = (uint64_t)iFirstChar;
    call.iLastChar = (uint64_t)iLastChar;
    call.pxBuffer = (uint64_t)pxBuffer;

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
    call.str = (uint64_t)str;

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
    call.str = (uint64_t)str;

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
    call.str = (uint64_t)str;
    call.fl = (uint64_t)fl;
    call.pdv = (uint64_t)pdv;

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
    call.str = (uint64_t)str;
    call.fl = (uint64_t)fl;
    call.pdv = (uint64_t)pdv;

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
    call.str = (uint64_t)str;

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
    call.str = (uint64_t)str;

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
    call.pbFont = (uint64_t)pbFont;
    call.cbFont = (uint64_t)cbFont;
    call.pdv = (uint64_t)pdv;
    call.pcFonts = (uint64_t)pcFonts;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_AddFontMemResourceEx(struct qemu_syscall *call)
{
    struct qemu_AddFontMemResourceEx *c = (struct qemu_AddFontMemResourceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)AddFontMemResourceEx(QEMU_G2H(c->pbFont), c->cbFont, QEMU_G2H(c->pdv), QEMU_G2H(c->pcFonts));
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
    call.fh = (uint64_t)fh;

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
    call.str = (uint64_t)str;
    call.fl = (uint64_t)fl;
    call.pdv = (uint64_t)pdv;

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
    call.str = (uint64_t)str;
    call.fl = (uint64_t)fl;
    call.pdv = (uint64_t)pdv;

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
    call.str = (uint64_t)str;
    call.size = (uint64_t)size;
    call.buffer = (uint64_t)buffer;
    call.type = (uint64_t)type;

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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.lptm = (uint64_t)lptm;
    call.height = (uint64_t)height;

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
    call.fEnableEUDC = (uint64_t)fEnableEUDC;

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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.count = (uint64_t)count;
    call.glyphs = (uint64_t)glyphs;
    call.buffer = (uint64_t)buffer;

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
    call.hdc = (uint64_t)hdc;
    call.lpgs = (uint64_t)lpgs;

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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.info = (uint64_t)info;

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
    call.hdc = (uint64_t)hdc;
    call.info = (uint64_t)info;

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

