#ifndef QEMU_OPENGL_H
#define QEMU_OPENGL_H

#include <stdlib.h>

#ifdef QEMU_DLL_GUEST

typedef struct
{
    const char  *name;     /* name of the extension */
    const char  *extension; /* name of the GL/WGL extension */
    void  *func;     /* pointer to the Wine function for this extension */
} OpenGL_extension;

#else

extern const struct qemu_ops *qemu_ops;
extern const syscall_handler dll_functions[];

void qemu_glDebugEntry(struct qemu_syscall *call);
/*
void qemu_wglChoosePixelFormat(struct qemu_syscall *call);
void qemu_wglCreateLayerContext(struct qemu_syscall *call);
void qemu_wglDescribeLayerPlane(struct qemu_syscall *call);
void qemu_wglGetCurrentContext(struct qemu_syscall *call);
void qemu_wglGetCurrentDC(struct qemu_syscall *call);
void qemu_wglGetDefaultProcAddress(struct qemu_syscall *call);
void qemu_wglGetLayerPaletteEntries(struct qemu_syscall *call);
void qemu_wglRealizeLayerPalette(struct qemu_syscall *call);
void qemu_wglSetLayerPaletteEntries(struct qemu_syscall *call);
void qemu_wglSwapLayerBuffers(struct qemu_syscall *call);
void qemu_wglUseFontBitmapsA(struct qemu_syscall *call);
void qemu_wglUseFontBitmapsW(struct qemu_syscall *call);
*/

GLint (* WINAPI p_glDebugEntry)(GLint unknown1, GLint unknown2);
INT (* WINAPI p_wglChoosePixelFormat)(HDC hdc, const PIXELFORMATDESCRIPTOR* ppfd);

#endif

#include "opengl_funcs.h"

#endif
