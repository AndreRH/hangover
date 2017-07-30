/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include <GL/gl.h>

#ifdef QEMU_DLL_GUEST

#include <GL/wglext.h>
#include <GL/glext.h>

#else

#define WGL_WGLEXT_PROTOTYPES
#include <wine/wglext.h>

#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "opengl32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_opengl32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_glDebugEntry,
    qemu_glGetIntegerv,
    qemu_glGetString,
    qemu_glGetStringi,
    qemu_wglAllocateMemoryNV,
    qemu_wglBindTexImageARB,
    qemu_wglChoosePixelFormat,
    qemu_wglChoosePixelFormatARB,
    qemu_wglCopyContext,
    qemu_wglCreateContext,
    qemu_wglCreateContextAttribsARB,
    qemu_wglCreateLayerContext,
    qemu_wglCreatePbufferARB,
    qemu_wglDeleteContext,
    qemu_wglDescribeLayerPlane,
    qemu_wglDescribePixelFormat,
    qemu_wglDestroyPbufferARB,
    qemu_wglFreeMemoryNV,
    qemu_wglGetCurrentContext,
    qemu_wglGetCurrentDC,
    qemu_wglGetCurrentReadDCARB,
    qemu_wglGetExtensionsStringARB,
    qemu_wglGetExtensionsStringEXT,
    qemu_wglGetLayerPaletteEntries,
    qemu_wglGetPbufferDCARB,
    qemu_wglGetPixelFormat,
    qemu_wglGetPixelFormatAttribfvARB,
    qemu_wglGetPixelFormatAttribivARB,
    qemu_wglGetProcAddress,
    qemu_wglGetSwapIntervalEXT,
    qemu_wglMakeContextCurrentARB,
    qemu_wglMakeCurrent,
    qemu_wglQueryCurrentRendererIntegerWINE,
    qemu_wglQueryCurrentRendererStringWINE,
    qemu_wglQueryPbufferARB,
    qemu_wglQueryRendererIntegerWINE,
    qemu_wglQueryRendererStringWINE,
    qemu_wglRealizeLayerPalette,
    qemu_wglReleasePbufferDCARB,
    qemu_wglReleaseTexImageARB,
    qemu_wglSetLayerPaletteEntries,
    qemu_wglSetPbufferAttribARB,
    qemu_wglSetPixelFormat,
    qemu_wglSetPixelFormatWINE,
    qemu_wglShareLists,
    qemu_wglSwapBuffers,
    qemu_wglSwapIntervalEXT,
    qemu_wglSwapLayerBuffers,
    qemu_wglUseFontBitmapsA,
    qemu_wglUseFontBitmapsW,
    qemu_wglUseFontOutlinesA,
    qemu_wglUseFontOutlinesW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side opengl32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    /* Failing to load some functions is not an error. It means that an extension is not
     * supported. */
    p_wglCreateContextAttribsARB = (void *)wglGetProcAddress("wglCreateContextAttribsARB");
    if (!p_wglCreateContextAttribsARB)
        WINE_WARN("Failed to load wglCreateContextAttribsARB.\n");
    p_wglMakeContextCurrentARB = (void *)wglGetProcAddress("wglMakeContextCurrentARB");
    if (!p_wglMakeContextCurrentARB)
        WINE_WARN("Failed to load wglMakeContextCurrentARB.\n");
    p_wglGetCurrentReadDCARB = (void *)wglGetProcAddress("wglGetCurrentReadDCARB");
    if (!p_wglGetCurrentReadDCARB)
        WINE_WARN("Failed to load wglGetCurrentReadDCARB.\n");
    p_glGetStringi = (void *)wglGetProcAddress("glGetStringi");
    if (!p_glGetStringi)
        WINE_WARN("Failed to load glGetStringi.\n");
    p_wglAllocateMemoryNV = (void *)wglGetProcAddress("wglAllocateMemoryNV");
    if (!p_wglAllocateMemoryNV)
        WINE_WARN("Failed to load wglAllocateMemoryNV.\n");
    p_wglFreeMemoryNV = (void *)wglGetProcAddress("wglFreeMemoryNV");
    if (!p_wglFreeMemoryNV)
        WINE_WARN("Failed to load wglFreeMemoryNV.\n");
    p_wglBindTexImageARB = (void *)wglGetProcAddress("wglBindTexImageARB");
    if (!p_wglBindTexImageARB)
        WINE_WARN("Failed to load wglBindTexImageARB.\n");
    p_wglReleaseTexImageARB = (void *)wglGetProcAddress("wglReleaseTexImageARB");
    if (!p_wglReleaseTexImageARB)
        WINE_WARN("Failed to load wglReleaseTexImageARB.\n");
    p_wglSetPbufferAttribARB = (void *)wglGetProcAddress("wglSetPbufferAttribARB");
    if (!p_wglSetPbufferAttribARB)
        WINE_WARN("Failed to load wglSetPbufferAttribARB.\n");
    p_wglChoosePixelFormatARB = (void *)wglGetProcAddress("wglChoosePixelFormatARB");
    if (!p_wglChoosePixelFormatARB)
        WINE_WARN("Failed to load wglChoosePixelFormatARB.\n");
    p_wglGetPixelFormatAttribivARB = (void *)wglGetProcAddress("wglGetPixelFormatAttribivARB");
    if (!p_wglGetPixelFormatAttribivARB)
        WINE_WARN("Failed to load wglGetPixelFormatAttribivARB.\n");
    p_wglGetPixelFormatAttribfvARB = (void *)wglGetProcAddress("wglGetPixelFormatAttribfvARB");
    if (!p_wglGetPixelFormatAttribfvARB)
        WINE_WARN("Failed to load wglGetPixelFormatAttribfvARB.\n");
    p_wglCreatePbufferARB = (void *)wglGetProcAddress("wglCreatePbufferARB");
    if (!p_wglCreatePbufferARB)
        WINE_WARN("Failed to load wglCreatePbufferARB.\n");
    p_wglGetPbufferDCARB = (void *)wglGetProcAddress("wglGetPbufferDCARB");
    if (!p_wglGetPbufferDCARB)
        WINE_WARN("Failed to load wglGetPbufferDCARB.\n");
    p_wglReleasePbufferDCARB = (void *)wglGetProcAddress("wglReleasePbufferDCARB");
    if (!p_wglReleasePbufferDCARB)
        WINE_WARN("Failed to load wglReleasePbufferDCARB.\n");
    p_wglDestroyPbufferARB = (void *)wglGetProcAddress("wglDestroyPbufferARB");
    if (!p_wglDestroyPbufferARB)
        WINE_WARN("Failed to load wglDestroyPbufferARB.\n");
    p_wglQueryPbufferARB = (void *)wglGetProcAddress("wglQueryPbufferARB");
    if (!p_wglQueryPbufferARB)
        WINE_WARN("Failed to load wglQueryPbufferARB.\n");
    p_wglDescribePixelFormat = (void *)wglGetProcAddress("wglDescribePixelFormat");
    if (!p_wglDescribePixelFormat)
        WINE_WARN("Failed to load wglDescribePixelFormat.\n");
    p_wglGetExtensionsStringARB = (void *)wglGetProcAddress("wglGetExtensionsStringARB");
    if (!p_wglGetExtensionsStringARB)
        WINE_WARN("Failed to load wglGetExtensionsStringARB.\n");
    p_wglGetExtensionsStringEXT = (void *)wglGetProcAddress("wglGetExtensionsStringEXT");
    if (!p_wglGetExtensionsStringEXT)
        WINE_WARN("Failed to load wglGetExtensionsStringEXT.\n");
    p_wglSwapIntervalEXT = (void *)wglGetProcAddress("wglSwapIntervalEXT");
    if (!p_wglSwapIntervalEXT)
        WINE_WARN("Failed to load wglSwapIntervalEXT.\n");
    p_wglGetSwapIntervalEXT = (void *)wglGetProcAddress("wglGetSwapIntervalEXT");
    if (!p_wglGetSwapIntervalEXT)
        WINE_WARN("Failed to load wglGetSwapIntervalEXT.\n");
    p_wglSetPixelFormatWINE = (void *)wglGetProcAddress("wglSetPixelFormatWINE");
    if (!p_wglSetPixelFormatWINE)
        WINE_WARN("Failed to load wglSetPixelFormatWINE.\n");
    p_wglQueryCurrentRendererIntegerWINE = (void *)wglGetProcAddress("wglQueryCurrentRendererIntegerWINE");
    if (!p_wglQueryCurrentRendererIntegerWINE)
        WINE_WARN("Failed to load wglQueryCurrentRendererIntegerWINE.\n");
    p_wglQueryCurrentRendererStringWINE = (void *)wglGetProcAddress("wglQueryCurrentRendererStringWINE");
    if (!p_wglQueryCurrentRendererStringWINE)
        WINE_WARN("Failed to load wglQueryCurrentRendererStringWINE.\n");
    p_wglQueryRendererIntegerWINE = (void *)wglGetProcAddress("wglQueryRendererIntegerWINE");
    if (!p_wglQueryRendererIntegerWINE)
        WINE_WARN("Failed to load wglQueryRendererIntegerWINE.\n");
    p_wglQueryRendererStringWINE = (void *)wglGetProcAddress("wglQueryRendererStringWINE");
    if (!p_wglQueryRendererStringWINE)
        WINE_WARN("Failed to load wglQueryRendererStringWINE.\n");
    p_wglChoosePixelFormat = (void *)wglGetProcAddress("wglChoosePixelFormat");
    if (!p_wglChoosePixelFormat)
        WINE_WARN("Failed to load wglChoosePixelFormat.\n");
    p_wglGetPixelFormat = (void *)wglGetProcAddress("wglGetPixelFormat");
    if (!p_wglGetPixelFormat)
        WINE_WARN("Failed to load wglGetPixelFormat.\n");
    p_wglSetPixelFormat = (void *)wglGetProcAddress("wglSetPixelFormat");
    if (!p_wglSetPixelFormat)
        WINE_WARN("Failed to load wglSetPixelFormat.\n");
    p_wglSwapBuffers = (void *)wglGetProcAddress("wglSwapBuffers");
    if (!p_wglSwapBuffers)
        WINE_WARN("Failed to load wglSwapBuffers.\n");
    p_glDebugEntry = (void *)wglGetProcAddress("glDebugEntry");
    if (!p_glDebugEntry)
        WINE_WARN("Failed to load glDebugEntry.\n");

    return dll_functions;
}

#endif
