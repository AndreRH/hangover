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

#ifdef QEMU_DLL_GUEST

#include <GL/gl.h>
#include <GL/wglext.h>
#include <GL/glext.h>

#else

#define WGL_WGLEXT_PROTOTYPES
#include <wine/wgl.h>

#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_opengl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_opengl32);
#endif

struct qemu_wglCopyContext
{
    struct qemu_syscall super;
    uint64_t hglrcSrc;
    uint64_t hglrcDst;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglCopyContext(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask)
{
    struct qemu_wglCopyContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCOPYCONTEXT);
    call.hglrcSrc = (ULONG_PTR)hglrcSrc;
    call.hglrcDst = (ULONG_PTR)hglrcDst;
    call.mask = mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglCopyContext(struct qemu_syscall *call)
{
    struct qemu_wglCopyContext *c = (struct qemu_wglCopyContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglCopyContext(QEMU_G2H(c->hglrcSrc), QEMU_G2H(c->hglrcDst), c->mask);
}

#endif

struct qemu_wglDeleteContext
{
    struct qemu_syscall super;
    uint64_t hglrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglDeleteContext(HGLRC hglrc)
{
    struct qemu_wglDeleteContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLDELETECONTEXT);
    call.hglrc = (ULONG_PTR)hglrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglDeleteContext(struct qemu_syscall *call)
{
    struct qemu_wglDeleteContext *c = (struct qemu_wglDeleteContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglDeleteContext(QEMU_G2H(c->hglrc));
}

#endif

struct qemu_wglMakeCurrent
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hglrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglMakeCurrent(HDC hdc, HGLRC hglrc)
{
    struct qemu_wglMakeCurrent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLMAKECURRENT);
    call.hdc = (ULONG_PTR)hdc;
    call.hglrc = (ULONG_PTR)hglrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglMakeCurrent(struct qemu_syscall *call)
{
    struct qemu_wglMakeCurrent *c = (struct qemu_wglMakeCurrent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglMakeCurrent(QEMU_G2H(c->hdc), QEMU_G2H(c->hglrc));
}

#endif

struct qemu_wglCreateContextAttribsARB
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t share;
    uint64_t attribs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLRC WINAPI wglCreateContextAttribsARB(HDC hdc, HGLRC share, const int *attribs)
{
    struct qemu_wglCreateContextAttribsARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCREATECONTEXTATTRIBSARB);
    call.hdc = (ULONG_PTR)hdc;
    call.share = (ULONG_PTR)share;
    call.attribs = (ULONG_PTR)attribs;

    qemu_syscall(&call.super);

    return (HGLRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglCreateContextAttribsARB(struct qemu_syscall *call)
{
    struct qemu_wglCreateContextAttribsARB *c = (struct qemu_wglCreateContextAttribsARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglCreateContextAttribsARB(QEMU_G2H(c->hdc), QEMU_G2H(c->share), QEMU_G2H(c->attribs)));
}

#endif

struct qemu_wglMakeContextCurrentARB
{
    struct qemu_syscall super;
    uint64_t draw_hdc;
    uint64_t read_hdc;
    uint64_t hglrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglMakeContextCurrentARB(HDC draw_hdc, HDC read_hdc, HGLRC hglrc)
{
    struct qemu_wglMakeContextCurrentARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLMAKECONTEXTCURRENTARB);
    call.draw_hdc = (ULONG_PTR)draw_hdc;
    call.read_hdc = (ULONG_PTR)read_hdc;
    call.hglrc = (ULONG_PTR)hglrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglMakeContextCurrentARB(struct qemu_syscall *call)
{
    struct qemu_wglMakeContextCurrentARB *c = (struct qemu_wglMakeContextCurrentARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglMakeContextCurrentARB(QEMU_G2H(c->draw_hdc), QEMU_G2H(c->read_hdc), QEMU_G2H(c->hglrc));
}

#endif

struct qemu_wglGetCurrentReadDCARB
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI wglGetCurrentReadDCARB(void)
{
    struct qemu_wglGetCurrentReadDCARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETCURRENTREADDCARB);

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglGetCurrentReadDCARB(struct qemu_syscall *call)
{
    struct qemu_wglGetCurrentReadDCARB *c = (struct qemu_wglGetCurrentReadDCARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglGetCurrentReadDCARB());
}

#endif

struct qemu_wglShareLists
{
    struct qemu_syscall super;
    uint64_t hglrcSrc;
    uint64_t hglrcDst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglShareLists(HGLRC hglrcSrc, HGLRC hglrcDst)
{
    struct qemu_wglShareLists call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSHARELISTS);
    call.hglrcSrc = (ULONG_PTR)hglrcSrc;
    call.hglrcDst = (ULONG_PTR)hglrcDst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglShareLists(struct qemu_syscall *call)
{
    struct qemu_wglShareLists *c = (struct qemu_wglShareLists *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglShareLists(QEMU_G2H(c->hglrcSrc), QEMU_G2H(c->hglrcDst));
}

#endif

struct qemu_wglGetCurrentDC
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI wglGetCurrentDC(void)
{
    struct qemu_wglGetCurrentDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETCURRENTDC);

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglGetCurrentDC(struct qemu_syscall *call)
{
    struct qemu_wglGetCurrentDC *c = (struct qemu_wglGetCurrentDC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(wglGetCurrentDC());
}

#endif

struct qemu_wglCreateContext
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLRC WINAPI wglCreateContext(HDC hdc)
{
    struct qemu_wglCreateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCREATECONTEXT);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return (HGLRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglCreateContext(struct qemu_syscall *call)
{
    struct qemu_wglCreateContext *c = (struct qemu_wglCreateContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(wglCreateContext(QEMU_G2H(c->hdc)));
}

#endif

struct qemu_wglGetCurrentContext
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLRC WINAPI wglGetCurrentContext(void)
{
    struct qemu_wglGetCurrentContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETCURRENTCONTEXT);

    qemu_syscall(&call.super);

    return (HGLRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglGetCurrentContext(struct qemu_syscall *call)
{
    struct qemu_wglGetCurrentContext *c = (struct qemu_wglGetCurrentContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(wglGetCurrentContext());
}

#endif

struct qemu_wglDescribePixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t size;
    uint64_t descr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI wglDescribePixelFormat(HDC hdc, INT format, UINT size, PIXELFORMATDESCRIPTOR *descr)
{
    struct qemu_wglDescribePixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLDESCRIBEPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;
    call.format = format;
    call.size = size;
    call.descr = (ULONG_PTR)descr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglDescribePixelFormat(struct qemu_syscall *call)
{
    struct qemu_wglDescribePixelFormat *c = (struct qemu_wglDescribePixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglDescribePixelFormat(QEMU_G2H(c->hdc), c->format, c->size, QEMU_G2H(c->descr));
}

#endif

struct qemu_wglChoosePixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t ppfd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI wglChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR* ppfd)
{
    struct qemu_wglChoosePixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCHOOSEPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;
    call.ppfd = (ULONG_PTR)ppfd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglChoosePixelFormat(struct qemu_syscall *call)
{
    struct qemu_wglChoosePixelFormat *c = (struct qemu_wglChoosePixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglChoosePixelFormat(QEMU_G2H(c->hdc), QEMU_G2H(c->ppfd));
}

#endif

struct qemu_wglGetPixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI wglGetPixelFormat(HDC hdc)
{
    struct qemu_wglGetPixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglGetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_wglGetPixelFormat *c = (struct qemu_wglGetPixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglGetPixelFormat(QEMU_G2H(c->hdc));
}

#endif

struct qemu_wglSetPixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t descr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglSetPixelFormat(HDC hdc, INT format, const PIXELFORMATDESCRIPTOR *descr)
{
    struct qemu_wglSetPixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSETPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;
    call.format = format;
    call.descr = (ULONG_PTR)descr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_wglSetPixelFormat *c = (struct qemu_wglSetPixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglSetPixelFormat(QEMU_G2H(c->hdc), c->format, QEMU_G2H(c->descr));
}

#endif

struct qemu_wglSwapBuffers
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglSwapBuffers(HDC hdc)
{
    struct qemu_wglSwapBuffers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSWAPBUFFERS);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSwapBuffers(struct qemu_syscall *call)
{
    struct qemu_wglSwapBuffers *c = (struct qemu_wglSwapBuffers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglSwapBuffers(QEMU_G2H(c->hdc));
}

#endif

struct qemu_wglCreateLayerContext
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iLayerPlane;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLRC WINAPI wglCreateLayerContext(HDC hdc, int iLayerPlane)
{
    struct qemu_wglCreateLayerContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCREATELAYERCONTEXT);
    call.hdc = (ULONG_PTR)hdc;
    call.iLayerPlane = iLayerPlane;

    qemu_syscall(&call.super);

    return (HGLRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglCreateLayerContext(struct qemu_syscall *call)
{
    struct qemu_wglCreateLayerContext *c = (struct qemu_wglCreateLayerContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(wglCreateLayerContext(QEMU_G2H(c->hdc), c->iLayerPlane));
}

#endif

struct qemu_wglDescribeLayerPlane
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iPixelFormat;
    uint64_t iLayerPlane;
    uint64_t nBytes;
    uint64_t plpd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglDescribeLayerPlane(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nBytes, LPLAYERPLANEDESCRIPTOR plpd)
{
    struct qemu_wglDescribeLayerPlane call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLDESCRIBELAYERPLANE);
    call.hdc = (ULONG_PTR)hdc;
    call.iPixelFormat = iPixelFormat;
    call.iLayerPlane = iLayerPlane;
    call.nBytes = nBytes;
    call.plpd = (ULONG_PTR)plpd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglDescribeLayerPlane(struct qemu_syscall *call)
{
    struct qemu_wglDescribeLayerPlane *c = (struct qemu_wglDescribeLayerPlane *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglDescribeLayerPlane(QEMU_G2H(c->hdc), c->iPixelFormat, c->iLayerPlane, c->nBytes, QEMU_G2H(c->plpd));
}

#endif

struct qemu_wglGetLayerPaletteEntries
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iLayerPlane;
    uint64_t iStart;
    uint64_t cEntries;
    uint64_t pcr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI wglGetLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF *pcr)
{
    struct qemu_wglGetLayerPaletteEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETLAYERPALETTEENTRIES);
    call.hdc = (ULONG_PTR)hdc;
    call.iLayerPlane = iLayerPlane;
    call.iStart = iStart;
    call.cEntries = cEntries;
    call.pcr = (ULONG_PTR)pcr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglGetLayerPaletteEntries(struct qemu_syscall *call)
{
    struct qemu_wglGetLayerPaletteEntries *c = (struct qemu_wglGetLayerPaletteEntries *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglGetLayerPaletteEntries(QEMU_G2H(c->hdc), c->iLayerPlane, c->iStart, c->cEntries, QEMU_G2H(c->pcr));
}

#endif

struct qemu_glGetIntegerv
{
    struct qemu_syscall super;
    uint64_t pname;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI glGetIntegerv(GLenum pname, GLint *data)
{
    struct qemu_glGetIntegerv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLGETINTEGERV);
    call.pname = pname;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);
}

#else

void qemu_glGetIntegerv(struct qemu_syscall *call)
{
    struct qemu_glGetIntegerv *c = (struct qemu_glGetIntegerv *)call;
    WINE_FIXME("Unverified!\n");
    glGetIntegerv(c->pname, QEMU_G2H(c->data));
}

#endif

struct qemu_glGetStringi
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const GLubyte * WINAPI glGetStringi(GLenum name, GLuint index)
{
    struct qemu_glGetStringi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLGETSTRINGI);
    call.name = name;
    call.index = index;

    qemu_syscall(&call.super);

    return (const GLubyte *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_glGetStringi(struct qemu_syscall *call)
{
    struct qemu_glGetStringi *c = (struct qemu_glGetStringi *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_glGetStringi(c->name, c->index));
}

#endif

struct qemu_wglGetProcAddress
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PROC WINAPI wglGetProcAddress(LPCSTR name)
{
    struct qemu_wglGetProcAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETPROCADDRESS);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (PROC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglGetProcAddress(struct qemu_syscall *call)
{
    struct qemu_wglGetProcAddress *c = (struct qemu_wglGetProcAddress *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif

struct qemu_wglRealizeLayerPalette
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iLayerPlane;
    uint64_t bRealize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglRealizeLayerPalette(HDC hdc, int iLayerPlane, BOOL bRealize)
{
    struct qemu_wglRealizeLayerPalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLREALIZELAYERPALETTE);
    call.hdc = (ULONG_PTR)hdc;
    call.iLayerPlane = iLayerPlane;
    call.bRealize = bRealize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglRealizeLayerPalette(struct qemu_syscall *call)
{
    struct qemu_wglRealizeLayerPalette *c = (struct qemu_wglRealizeLayerPalette *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglRealizeLayerPalette(QEMU_G2H(c->hdc), c->iLayerPlane, c->bRealize);
}

#endif

struct qemu_wglSetLayerPaletteEntries
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iLayerPlane;
    uint64_t iStart;
    uint64_t cEntries;
    uint64_t pcr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI wglSetLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF *pcr)
{
    struct qemu_wglSetLayerPaletteEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSETLAYERPALETTEENTRIES);
    call.hdc = (ULONG_PTR)hdc;
    call.iLayerPlane = iLayerPlane;
    call.iStart = iStart;
    call.cEntries = cEntries;
    call.pcr = (ULONG_PTR)pcr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSetLayerPaletteEntries(struct qemu_syscall *call)
{
    struct qemu_wglSetLayerPaletteEntries *c = (struct qemu_wglSetLayerPaletteEntries *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglSetLayerPaletteEntries(QEMU_G2H(c->hdc), c->iLayerPlane, c->iStart, c->cEntries, QEMU_G2H(c->pcr));
}

#endif

struct qemu_wglGetDefaultProcAddress
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PROC WINAPI wglGetDefaultProcAddress(LPCSTR name)
{
    struct qemu_wglGetDefaultProcAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETDEFAULTPROCADDRESS);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (PROC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglGetDefaultProcAddress(struct qemu_syscall *call)
{
    struct qemu_wglGetDefaultProcAddress *c = (struct qemu_wglGetDefaultProcAddress *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;/*(uint64_t)p_wglGetDefaultProcAddress(QEMU_G2H(c->name));*/
}

#endif

struct qemu_wglSwapLayerBuffers
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t fuPlanes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglSwapLayerBuffers(HDC hdc, UINT fuPlanes)
{
    struct qemu_wglSwapLayerBuffers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSWAPLAYERBUFFERS);
    call.hdc = (ULONG_PTR)hdc;
    call.fuPlanes = fuPlanes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSwapLayerBuffers(struct qemu_syscall *call)
{
    struct qemu_wglSwapLayerBuffers *c = (struct qemu_wglSwapLayerBuffers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglSwapLayerBuffers(QEMU_G2H(c->hdc), c->fuPlanes);
}

#endif

struct qemu_wglBindTexImageARB
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglBindTexImageARB(HPBUFFERARB handle, int buffer)
{
    struct qemu_wglBindTexImageARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLBINDTEXIMAGEARB);
    call.handle = (ULONG_PTR)handle;
    call.buffer = buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglBindTexImageARB(struct qemu_syscall *call)
{
    struct qemu_wglBindTexImageARB *c = (struct qemu_wglBindTexImageARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglBindTexImageARB(QEMU_G2H(c->handle), c->buffer);
}

#endif

struct qemu_wglReleaseTexImageARB
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglReleaseTexImageARB(HPBUFFERARB handle, int buffer)
{
    struct qemu_wglReleaseTexImageARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLRELEASETEXIMAGEARB);
    call.handle = (ULONG_PTR)handle;
    call.buffer = buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglReleaseTexImageARB(struct qemu_syscall *call)
{
    struct qemu_wglReleaseTexImageARB *c = (struct qemu_wglReleaseTexImageARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglReleaseTexImageARB(QEMU_G2H(c->handle), c->buffer);
}

#endif

struct qemu_wglSetPbufferAttribARB
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t attribs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglSetPbufferAttribARB(HPBUFFERARB handle, const int *attribs)
{
    struct qemu_wglSetPbufferAttribARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSETPBUFFERATTRIBARB);
    call.handle = (ULONG_PTR)handle;
    call.attribs = (ULONG_PTR)attribs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSetPbufferAttribARB(struct qemu_syscall *call)
{
    struct qemu_wglSetPbufferAttribARB *c = (struct qemu_wglSetPbufferAttribARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglSetPbufferAttribARB(QEMU_G2H(c->handle), QEMU_G2H(c->attribs));
}

#endif

struct qemu_wglCreatePbufferARB
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t width;
    uint64_t height;
    uint64_t attribs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPBUFFERARB WINAPI wglCreatePbufferARB(HDC hdc, int format, int width, int height, const int *attribs)
{
    struct qemu_wglCreatePbufferARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCREATEPBUFFERARB);
    call.hdc = (ULONG_PTR)hdc;
    call.format = format;
    call.width = width;
    call.height = height;
    call.attribs = (ULONG_PTR)attribs;

    qemu_syscall(&call.super);

    return (HPBUFFERARB)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglCreatePbufferARB(struct qemu_syscall *call)
{
    struct qemu_wglCreatePbufferARB *c = (struct qemu_wglCreatePbufferARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglCreatePbufferARB(QEMU_G2H(c->hdc), c->format, c->width, c->height, QEMU_G2H(c->attribs)));
}

#endif

struct qemu_wglGetPbufferDCARB
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI wglGetPbufferDCARB(HPBUFFERARB handle)
{
    struct qemu_wglGetPbufferDCARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETPBUFFERDCARB);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wglGetPbufferDCARB(struct qemu_syscall *call)
{
    struct qemu_wglGetPbufferDCARB *c = (struct qemu_wglGetPbufferDCARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglGetPbufferDCARB(QEMU_G2H(c->handle)));
}

#endif

struct qemu_wglReleasePbufferDCARB
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI wglReleasePbufferDCARB(HPBUFFERARB handle, HDC hdc)
{
    struct qemu_wglReleasePbufferDCARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLRELEASEPBUFFERDCARB);
    call.handle = (ULONG_PTR)handle;
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglReleasePbufferDCARB(struct qemu_syscall *call)
{
    struct qemu_wglReleasePbufferDCARB *c = (struct qemu_wglReleasePbufferDCARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglReleasePbufferDCARB(QEMU_G2H(c->handle), QEMU_G2H(c->hdc));
}

#endif

struct qemu_wglDestroyPbufferARB
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglDestroyPbufferARB(HPBUFFERARB handle)
{
    struct qemu_wglDestroyPbufferARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLDESTROYPBUFFERARB);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglDestroyPbufferARB(struct qemu_syscall *call)
{
    struct qemu_wglDestroyPbufferARB *c = (struct qemu_wglDestroyPbufferARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglDestroyPbufferARB(QEMU_G2H(c->handle));
}

#endif

struct qemu_wglQueryPbufferARB
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t attrib;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglQueryPbufferARB(HPBUFFERARB handle, int attrib, int *value)
{
    struct qemu_wglQueryPbufferARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLQUERYPBUFFERARB);
    call.handle = (ULONG_PTR)handle;
    call.attrib = attrib;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglQueryPbufferARB(struct qemu_syscall *call)
{
    struct qemu_wglQueryPbufferARB *c = (struct qemu_wglQueryPbufferARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglQueryPbufferARB(QEMU_G2H(c->handle), c->attrib, QEMU_G2H(c->value));
}

#endif

struct qemu_wglUseFontBitmapsA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t count;
    uint64_t listBase;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglUseFontBitmapsA(HDC hdc, DWORD first, DWORD count, DWORD listBase)
{
    struct qemu_wglUseFontBitmapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLUSEFONTBITMAPSA);
    call.hdc = (ULONG_PTR)hdc;
    call.first = first;
    call.count = count;
    call.listBase = listBase;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglUseFontBitmapsA(struct qemu_syscall *call)
{
    struct qemu_wglUseFontBitmapsA *c = (struct qemu_wglUseFontBitmapsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglUseFontBitmapsA(QEMU_G2H(c->hdc), c->first, c->count, c->listBase);
}

#endif

struct qemu_wglUseFontBitmapsW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t count;
    uint64_t listBase;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglUseFontBitmapsW(HDC hdc, DWORD first, DWORD count, DWORD listBase)
{
    struct qemu_wglUseFontBitmapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLUSEFONTBITMAPSW);
    call.hdc = (ULONG_PTR)hdc;
    call.first = first;
    call.count = count;
    call.listBase = listBase;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglUseFontBitmapsW(struct qemu_syscall *call)
{
    struct qemu_wglUseFontBitmapsW *c = (struct qemu_wglUseFontBitmapsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglUseFontBitmapsW(QEMU_G2H(c->hdc), c->first, c->count, c->listBase);
}

#endif

struct qemu_wglUseFontOutlinesA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t count;
    uint64_t listBase;
    uint64_t deviation;
    uint64_t extrusion;
    uint64_t format;
    uint64_t lpgmf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglUseFontOutlinesA(HDC hdc, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf)
{
    struct qemu_wglUseFontOutlinesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLUSEFONTOUTLINESA);
    call.hdc = (ULONG_PTR)hdc;
    call.first = first;
    call.count = count;
    call.listBase = listBase;
    call.deviation = deviation;
    call.extrusion = extrusion;
    call.format = format;
    call.lpgmf = (ULONG_PTR)lpgmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglUseFontOutlinesA(struct qemu_syscall *call)
{
    struct qemu_wglUseFontOutlinesA *c = (struct qemu_wglUseFontOutlinesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglUseFontOutlinesA(QEMU_G2H(c->hdc), c->first, c->count, c->listBase, c->deviation, c->extrusion, c->format, QEMU_G2H(c->lpgmf));
}

#endif

struct qemu_wglUseFontOutlinesW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t first;
    uint64_t count;
    uint64_t listBase;
    uint64_t deviation;
    uint64_t extrusion;
    uint64_t format;
    uint64_t lpgmf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglUseFontOutlinesW(HDC hdc, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf)
{
    struct qemu_wglUseFontOutlinesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLUSEFONTOUTLINESW);
    call.hdc = (ULONG_PTR)hdc;
    call.first = first;
    call.count = count;
    call.listBase = listBase;
    call.deviation = deviation;
    call.extrusion = extrusion;
    call.format = format;
    call.lpgmf = (ULONG_PTR)lpgmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglUseFontOutlinesW(struct qemu_syscall *call)
{
    struct qemu_wglUseFontOutlinesW *c = (struct qemu_wglUseFontOutlinesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wglUseFontOutlinesW(QEMU_G2H(c->hdc), c->first, c->count, c->listBase, c->deviation, c->extrusion, c->format, QEMU_G2H(c->lpgmf));
}

#endif

struct qemu_glDebugEntry
{
    struct qemu_syscall super;
    uint64_t unknown1;
    uint64_t unknown2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI GLint WINAPI glDebugEntry(GLint unknown1, GLint unknown2)
{
    struct qemu_glDebugEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLDEBUGENTRY);
    call.unknown1 = unknown1;
    call.unknown2 = unknown2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_glDebugEntry(struct qemu_syscall *call)
{
    struct qemu_glDebugEntry *c = (struct qemu_glDebugEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_glDebugEntry(c->unknown1, c->unknown2);
}

#endif

struct qemu_glGetString
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const GLubyte * WINAPI glGetString(GLenum name)
{
    struct qemu_glGetString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLGETSTRING);
    call.name = name;

    qemu_syscall(&call.super);

    return (const GLubyte *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_glGetString(struct qemu_syscall *call)
{
    struct qemu_glGetString *c = (struct qemu_glGetString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(glGetString(c->name));
}

#endif

struct qemu_glDebugMessageCallback
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
{
    struct qemu_glDebugMessageCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLDEBUGMESSAGECALLBACK);
    call.callback = (ULONG_PTR)callback;
    call.userParam = (ULONG_PTR)userParam;

    qemu_syscall(&call.super);
}

#else

void qemu_glDebugMessageCallback(struct qemu_syscall *call)
{
    struct qemu_glDebugMessageCallback *c = (struct qemu_glDebugMessageCallback *)call;
    WINE_FIXME("Unverified!\n");
    p_glDebugMessageCallback(QEMU_G2H(c->callback), QEMU_G2H(c->userParam));
}

#endif

struct qemu_glDebugMessageCallbackAMD
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback, void *userParam)
{
    struct qemu_glDebugMessageCallbackAMD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLDEBUGMESSAGECALLBACKAMD);
    call.callback = (ULONG_PTR)callback;
    call.userParam = (ULONG_PTR)userParam;

    qemu_syscall(&call.super);
}

#else

void qemu_glDebugMessageCallbackAMD(struct qemu_syscall *call)
{
    struct qemu_glDebugMessageCallbackAMD *c = (struct qemu_glDebugMessageCallbackAMD *)call;
    WINE_FIXME("Unverified!\n");
    p_glDebugMessageCallbackAMD(QEMU_G2H(c->callback), QEMU_G2H(c->userParam));
}

#endif

struct qemu_glDebugMessageCallbackARB
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void *userParam)
{
    struct qemu_glDebugMessageCallbackARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLDEBUGMESSAGECALLBACKARB);
    call.callback = (ULONG_PTR)callback;
    call.userParam = (ULONG_PTR)userParam;

    qemu_syscall(&call.super);
}

#else

void qemu_glDebugMessageCallbackARB(struct qemu_syscall *call)
{
    struct qemu_glDebugMessageCallbackARB *c = (struct qemu_glDebugMessageCallbackARB *)call;
    WINE_FIXME("Unverified!\n");
    p_glDebugMessageCallbackARB(QEMU_G2H(c->callback), QEMU_G2H(c->userParam));
}

#endif

