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
    call.hglrcSrc = (uint64_t)hglrcSrc;
    call.hglrcDst = (uint64_t)hglrcDst;
    call.mask = (uint64_t)mask;

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
    call.hglrc = (uint64_t)hglrc;

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
    call.hdc = (uint64_t)hdc;
    call.hglrc = (uint64_t)hglrc;

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
    call.hdc = (uint64_t)hdc;
    call.share = (uint64_t)share;
    call.attribs = (uint64_t)attribs;

    qemu_syscall(&call.super);

    return (HGLRC)call.super.iret;
}

#else

void qemu_wglCreateContextAttribsARB(struct qemu_syscall *call)
{
    struct qemu_wglCreateContextAttribsARB *c = (struct qemu_wglCreateContextAttribsARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wglCreateContextAttribsARB(QEMU_G2H(c->hdc), QEMU_G2H(c->share), QEMU_G2H(c->attribs));
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
    call.draw_hdc = (uint64_t)draw_hdc;
    call.read_hdc = (uint64_t)read_hdc;
    call.hglrc = (uint64_t)hglrc;

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

    return (HDC)call.super.iret;
}

#else

void qemu_wglGetCurrentReadDCARB(struct qemu_syscall *call)
{
    struct qemu_wglGetCurrentReadDCARB *c = (struct qemu_wglGetCurrentReadDCARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wglGetCurrentReadDCARB();
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
    call.hglrcSrc = (uint64_t)hglrcSrc;
    call.hglrcDst = (uint64_t)hglrcDst;

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

    return (HDC)call.super.iret;
}

#else

void qemu_wglGetCurrentDC(struct qemu_syscall *call)
{
    struct qemu_wglGetCurrentDC *c = (struct qemu_wglGetCurrentDC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)wglGetCurrentDC();
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
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return (HGLRC)call.super.iret;
}

#else

void qemu_wglCreateContext(struct qemu_syscall *call)
{
    struct qemu_wglCreateContext *c = (struct qemu_wglCreateContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)wglCreateContext(QEMU_G2H(c->hdc));
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

    return (HGLRC)call.super.iret;
}

#else

void qemu_wglGetCurrentContext(struct qemu_syscall *call)
{
    struct qemu_wglGetCurrentContext *c = (struct qemu_wglGetCurrentContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)wglGetCurrentContext();
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
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.size = (uint64_t)size;
    call.descr = (uint64_t)descr;

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
    call.hdc = (uint64_t)hdc;
    call.ppfd = (uint64_t)ppfd;

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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.descr = (uint64_t)descr;

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
    call.hdc = (uint64_t)hdc;

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
    call.hdc = (uint64_t)hdc;
    call.iLayerPlane = (uint64_t)iLayerPlane;

    qemu_syscall(&call.super);

    return (HGLRC)call.super.iret;
}

#else

void qemu_wglCreateLayerContext(struct qemu_syscall *call)
{
    struct qemu_wglCreateLayerContext *c = (struct qemu_wglCreateLayerContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)wglCreateLayerContext(QEMU_G2H(c->hdc), c->iLayerPlane);
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
    call.hdc = (uint64_t)hdc;
    call.iPixelFormat = (uint64_t)iPixelFormat;
    call.iLayerPlane = (uint64_t)iLayerPlane;
    call.nBytes = (uint64_t)nBytes;
    call.plpd = (uint64_t)plpd;

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

WINBASEAPI int WINAPI wglGetLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart, int cEntries, COLORREF *pcr)
{
    struct qemu_wglGetLayerPaletteEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETLAYERPALETTEENTRIES);
    call.hdc = (uint64_t)hdc;
    call.iLayerPlane = (uint64_t)iLayerPlane;
    call.iStart = (uint64_t)iStart;
    call.cEntries = (uint64_t)cEntries;
    call.pcr = (uint64_t)pcr;

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
    call.pname = (uint64_t)pname;
    call.data = (uint64_t)data;

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
    call.name = (uint64_t)name;
    call.index = (uint64_t)index;

    qemu_syscall(&call.super);

    return (GLubyte *)call.super.iret;
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
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (PROC)call.super.iret;
}

#else

void qemu_wglGetProcAddress(struct qemu_syscall *call)
{
    struct qemu_wglGetProcAddress *c = (struct qemu_wglGetProcAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)wglGetProcAddress(QEMU_G2H(c->name));
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
    call.hdc = (uint64_t)hdc;
    call.iLayerPlane = (uint64_t)iLayerPlane;
    call.bRealize = (uint64_t)bRealize;

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
    call.hdc = (uint64_t)hdc;
    call.iLayerPlane = (uint64_t)iLayerPlane;
    call.iStart = (uint64_t)iStart;
    call.cEntries = (uint64_t)cEntries;
    call.pcr = (uint64_t)pcr;

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
    call.hdc = (uint64_t)hdc;
    call.fuPlanes = (uint64_t)fuPlanes;

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

struct qemu_wglAllocateMemoryNV
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t readfreq;
    uint64_t writefreq;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI wglAllocateMemoryNV(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority)
{
    struct qemu_wglAllocateMemoryNV call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLALLOCATEMEMORYNV);
    call.size = (uint64_t)size;
    call.readfreq = (uint64_t)readfreq;
    call.writefreq = (uint64_t)writefreq;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_wglAllocateMemoryNV(struct qemu_syscall *call)
{
    struct qemu_wglAllocateMemoryNV *c = (struct qemu_wglAllocateMemoryNV *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglAllocateMemoryNV(c->size, c->readfreq, c->writefreq, c->priority));
}

#endif

struct qemu_wglFreeMemoryNV
{
    struct qemu_syscall super;
    uint64_t pointer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI wglFreeMemoryNV(void *pointer)
{
    struct qemu_wglFreeMemoryNV call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLFREEMEMORYNV);
    call.pointer = (uint64_t)pointer;

    qemu_syscall(&call.super);
}

#else

void qemu_wglFreeMemoryNV(struct qemu_syscall *call)
{
    struct qemu_wglFreeMemoryNV *c = (struct qemu_wglFreeMemoryNV *)call;
    WINE_FIXME("Unverified!\n");
    p_wglFreeMemoryNV(QEMU_G2H(c->pointer));
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
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglBindTexImageARB(struct qemu_syscall *call)
{
    struct qemu_wglBindTexImageARB *c = (struct qemu_wglBindTexImageARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglBindTexImageARB((HPBUFFERARB)c->handle, c->buffer);
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
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglReleaseTexImageARB(struct qemu_syscall *call)
{
    struct qemu_wglReleaseTexImageARB *c = (struct qemu_wglReleaseTexImageARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglReleaseTexImageARB((HPBUFFERARB)c->handle, c->buffer);
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
    call.handle = (uint64_t)handle;
    call.attribs = (uint64_t)attribs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSetPbufferAttribARB(struct qemu_syscall *call)
{
    struct qemu_wglSetPbufferAttribARB *c = (struct qemu_wglSetPbufferAttribARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglSetPbufferAttribARB((HPBUFFERARB)c->handle, QEMU_G2H(c->attribs));
}

#endif

struct qemu_wglChoosePixelFormatARB
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iattribs;
    uint64_t fattribs;
    uint64_t max;
    uint64_t formats;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglChoosePixelFormatARB(HDC hdc, const int *iattribs, const FLOAT *fattribs, UINT max, int *formats, UINT *count)
{
    struct qemu_wglChoosePixelFormatARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLCHOOSEPIXELFORMATARB);
    call.hdc = (uint64_t)hdc;
    call.iattribs = (uint64_t)iattribs;
    call.fattribs = (uint64_t)fattribs;
    call.max = (uint64_t)max;
    call.formats = (uint64_t)formats;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglChoosePixelFormatARB(struct qemu_syscall *call)
{
    struct qemu_wglChoosePixelFormatARB *c = (struct qemu_wglChoosePixelFormatARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglChoosePixelFormatARB(QEMU_G2H(c->hdc), QEMU_G2H(c->iattribs), QEMU_G2H(c->fattribs), c->max, QEMU_G2H(c->formats), QEMU_G2H(c->count));
}

#endif

struct qemu_wglGetPixelFormatAttribivARB
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t layer;
    uint64_t count;
    uint64_t attribs;
    uint64_t values;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglGetPixelFormatAttribivARB(HDC hdc, int format, int layer, UINT count, const int *attribs, int *values)
{
    struct qemu_wglGetPixelFormatAttribivARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETPIXELFORMATATTRIBIVARB);
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.layer = (uint64_t)layer;
    call.count = (uint64_t)count;
    call.attribs = (uint64_t)attribs;
    call.values = (uint64_t)values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglGetPixelFormatAttribivARB(struct qemu_syscall *call)
{
    struct qemu_wglGetPixelFormatAttribivARB *c = (struct qemu_wglGetPixelFormatAttribivARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglGetPixelFormatAttribivARB(QEMU_G2H(c->hdc), c->format, c->layer, c->count, QEMU_G2H(c->attribs), QEMU_G2H(c->values));
}

#endif

struct qemu_wglGetPixelFormatAttribfvARB
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t layer;
    uint64_t count;
    uint64_t attribs;
    uint64_t values;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglGetPixelFormatAttribfvARB(HDC hdc, int format, int layer, UINT count, const int *attribs, FLOAT *values)
{
    struct qemu_wglGetPixelFormatAttribfvARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETPIXELFORMATATTRIBFVARB);
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.layer = (uint64_t)layer;
    call.count = (uint64_t)count;
    call.attribs = (uint64_t)attribs;
    call.values = (uint64_t)values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglGetPixelFormatAttribfvARB(struct qemu_syscall *call)
{
    struct qemu_wglGetPixelFormatAttribfvARB *c = (struct qemu_wglGetPixelFormatAttribfvARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglGetPixelFormatAttribfvARB(QEMU_G2H(c->hdc), c->format, c->layer, c->count, QEMU_G2H(c->attribs), QEMU_G2H(c->values));
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
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.attribs = (uint64_t)attribs;

    qemu_syscall(&call.super);

    return (HPBUFFERARB)call.super.iret;
}

#else

void qemu_wglCreatePbufferARB(struct qemu_syscall *call)
{
    struct qemu_wglCreatePbufferARB *c = (struct qemu_wglCreatePbufferARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wglCreatePbufferARB((HDC)c->hdc, c->format, c->width, c->height, QEMU_G2H(c->attribs));
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
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return (HDC)call.super.iret;
}

#else

void qemu_wglGetPbufferDCARB(struct qemu_syscall *call)
{
    struct qemu_wglGetPbufferDCARB *c = (struct qemu_wglGetPbufferDCARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wglGetPbufferDCARB((HPBUFFERARB)c->handle);
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
    call.handle = (uint64_t)handle;
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglReleasePbufferDCARB(struct qemu_syscall *call)
{
    struct qemu_wglReleasePbufferDCARB *c = (struct qemu_wglReleasePbufferDCARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglReleasePbufferDCARB((HPBUFFERARB)c->handle, (HDC)c->hdc);
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
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglDestroyPbufferARB(struct qemu_syscall *call)
{
    struct qemu_wglDestroyPbufferARB *c = (struct qemu_wglDestroyPbufferARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglDestroyPbufferARB((HPBUFFERARB)c->handle);
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
    call.handle = (uint64_t)handle;
    call.attrib = (uint64_t)attrib;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglQueryPbufferARB(struct qemu_syscall *call)
{
    struct qemu_wglQueryPbufferARB *c = (struct qemu_wglQueryPbufferARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglQueryPbufferARB((HPBUFFERARB)c->handle, c->attrib, QEMU_G2H(c->value));
}

#endif

struct qemu_wglGetExtensionsStringARB
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const char * WINAPI wglGetExtensionsStringARB(HDC hdc)
{
    struct qemu_wglGetExtensionsStringARB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETEXTENSIONSSTRINGARB);
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return (const char *)call.super.iret;
}

#else

void qemu_wglGetExtensionsStringARB(struct qemu_syscall *call)
{
    struct qemu_wglGetExtensionsStringARB *c = (struct qemu_wglGetExtensionsStringARB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglGetExtensionsStringARB(QEMU_G2H(c->hdc)));
}

#endif

struct qemu_wglGetExtensionsStringEXT
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const char * WINAPI wglGetExtensionsStringEXT(void)
{
    struct qemu_wglGetExtensionsStringEXT call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETEXTENSIONSSTRINGEXT);

    qemu_syscall(&call.super);

    return (const char *)call.super.iret;
}

#else

void qemu_wglGetExtensionsStringEXT(struct qemu_syscall *call)
{
    struct qemu_wglGetExtensionsStringEXT *c = (struct qemu_wglGetExtensionsStringEXT *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglGetExtensionsStringEXT());
}

#endif

struct qemu_wglSwapIntervalEXT
{
    struct qemu_syscall super;
    uint64_t interval;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglSwapIntervalEXT(int interval)
{
    struct qemu_wglSwapIntervalEXT call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSWAPINTERVALEXT);
    call.interval = (uint64_t)interval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSwapIntervalEXT(struct qemu_syscall *call)
{
    struct qemu_wglSwapIntervalEXT *c = (struct qemu_wglSwapIntervalEXT *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglSwapIntervalEXT(c->interval);
}

#endif

struct qemu_wglGetSwapIntervalEXT
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI wglGetSwapIntervalEXT(void)
{
    struct qemu_wglGetSwapIntervalEXT call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLGETSWAPINTERVALEXT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglGetSwapIntervalEXT(struct qemu_syscall *call)
{
    struct qemu_wglGetSwapIntervalEXT *c = (struct qemu_wglGetSwapIntervalEXT *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglGetSwapIntervalEXT();
}

#endif

struct qemu_wglSetPixelFormatWINE
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglSetPixelFormatWINE(HDC hdc, int format)
{
    struct qemu_wglSetPixelFormatWINE call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLSETPIXELFORMATWINE);
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglSetPixelFormatWINE(struct qemu_syscall *call)
{
    struct qemu_wglSetPixelFormatWINE *c = (struct qemu_wglSetPixelFormatWINE *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglSetPixelFormatWINE(QEMU_G2H(c->hdc), c->format);
}

#endif

struct qemu_wglQueryCurrentRendererIntegerWINE
{
    struct qemu_syscall super;
    uint64_t attribute;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglQueryCurrentRendererIntegerWINE(GLenum attribute, GLuint *value)
{
    struct qemu_wglQueryCurrentRendererIntegerWINE call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLQUERYCURRENTRENDERERINTEGERWINE);
    call.attribute = (uint64_t)attribute;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglQueryCurrentRendererIntegerWINE(struct qemu_syscall *call)
{
    struct qemu_wglQueryCurrentRendererIntegerWINE *c = (struct qemu_wglQueryCurrentRendererIntegerWINE *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglQueryCurrentRendererIntegerWINE(c->attribute, QEMU_G2H(c->value));
}

#endif

struct qemu_wglQueryCurrentRendererStringWINE
{
    struct qemu_syscall super;
    uint64_t attribute;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const GLchar * WINAPI wglQueryCurrentRendererStringWINE(GLenum attribute)
{
    struct qemu_wglQueryCurrentRendererStringWINE call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLQUERYCURRENTRENDERERSTRINGWINE);
    call.attribute = (uint64_t)attribute;

    qemu_syscall(&call.super);

    return (GLchar *)call.super.iret;
}

#else

void qemu_wglQueryCurrentRendererStringWINE(struct qemu_syscall *call)
{
    struct qemu_wglQueryCurrentRendererStringWINE *c = (struct qemu_wglQueryCurrentRendererStringWINE *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglQueryCurrentRendererStringWINE(c->attribute));
}

#endif

struct qemu_wglQueryRendererIntegerWINE
{
    struct qemu_syscall super;
    uint64_t dc;
    uint64_t renderer;
    uint64_t attribute;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI wglQueryRendererIntegerWINE(HDC dc, GLint renderer, GLenum attribute, GLuint *value)
{
    struct qemu_wglQueryRendererIntegerWINE call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLQUERYRENDERERINTEGERWINE);
    call.dc = (uint64_t)dc;
    call.renderer = (uint64_t)renderer;
    call.attribute = (uint64_t)attribute;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wglQueryRendererIntegerWINE(struct qemu_syscall *call)
{
    struct qemu_wglQueryRendererIntegerWINE *c = (struct qemu_wglQueryRendererIntegerWINE *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wglQueryRendererIntegerWINE(QEMU_G2H(c->dc), c->renderer, c->attribute, QEMU_G2H(c->value));
}

#endif

struct qemu_wglQueryRendererStringWINE
{
    struct qemu_syscall super;
    uint64_t dc;
    uint64_t renderer;
    uint64_t attribute;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const GLchar * WINAPI wglQueryRendererStringWINE(HDC dc, GLint renderer, GLenum attribute)
{
    struct qemu_wglQueryRendererStringWINE call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WGLQUERYRENDERERSTRINGWINE);
    call.dc = (uint64_t)dc;
    call.renderer = (uint64_t)renderer;
    call.attribute = (uint64_t)attribute;

    qemu_syscall(&call.super);

    return (GLchar *)call.super.iret;
}

#else

void qemu_wglQueryRendererStringWINE(struct qemu_syscall *call)
{
    struct qemu_wglQueryRendererStringWINE *c = (struct qemu_wglQueryRendererStringWINE *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wglQueryRendererStringWINE(QEMU_G2H(c->dc), c->renderer, c->attribute));
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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.count = (uint64_t)count;
    call.listBase = (uint64_t)listBase;

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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.count = (uint64_t)count;
    call.listBase = (uint64_t)listBase;

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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.count = (uint64_t)count;
    call.listBase = (uint64_t)listBase;
    call.deviation = (uint64_t)deviation;
    call.extrusion = (uint64_t)extrusion;
    call.format = (uint64_t)format;
    call.lpgmf = (uint64_t)lpgmf;

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
    call.hdc = (uint64_t)hdc;
    call.first = (uint64_t)first;
    call.count = (uint64_t)count;
    call.listBase = (uint64_t)listBase;
    call.deviation = (uint64_t)deviation;
    call.extrusion = (uint64_t)extrusion;
    call.format = (uint64_t)format;
    call.lpgmf = (uint64_t)lpgmf;

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
    call.unknown1 = (uint64_t)unknown1;
    call.unknown2 = (uint64_t)unknown2;

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
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (GLubyte *)call.super.iret;
}

#else

void qemu_glGetString(struct qemu_syscall *call)
{
    struct qemu_glGetString *c = (struct qemu_glGetString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(glGetString(c->name));
}

#endif

