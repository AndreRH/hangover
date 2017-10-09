#ifndef QEMU_XINPUT_H
#define QEMU_XINPUT_H

#include <stdlib.h>

enum opengl32_calls
{
    CALL_GLDEBUGENTRY = 0,
    CALL_GLGETINTEGERV,
    CALL_GLGETSTRING,
    CALL_GLGETSTRINGI,
    CALL_WGLALLOCATEMEMORYNV,
    CALL_WGLBINDTEXIMAGEARB,
    CALL_WGLCHOOSEPIXELFORMAT,
    CALL_WGLCHOOSEPIXELFORMATARB,
    CALL_WGLCOPYCONTEXT,
    CALL_WGLCREATECONTEXT,
    CALL_WGLCREATECONTEXTATTRIBSARB,
    CALL_WGLCREATELAYERCONTEXT,
    CALL_WGLCREATEPBUFFERARB,
    CALL_WGLDELETECONTEXT,
    CALL_WGLDESCRIBELAYERPLANE,
    CALL_WGLDESCRIBEPIXELFORMAT,
    CALL_WGLDESTROYPBUFFERARB,
    CALL_WGLFREEMEMORYNV,
    CALL_WGLGETCURRENTCONTEXT,
    CALL_WGLGETCURRENTDC,
    CALL_WGLGETCURRENTREADDCARB,
    CALL_WGLGETEXTENSIONSSTRINGARB,
    CALL_WGLGETEXTENSIONSSTRINGEXT,
    CALL_WGLGETLAYERPALETTEENTRIES,
    CALL_WGLGETPBUFFERDCARB,
    CALL_WGLGETPIXELFORMAT,
    CALL_WGLGETPIXELFORMATATTRIBFVARB,
    CALL_WGLGETPIXELFORMATATTRIBIVARB,
    CALL_WGLGETPROCADDRESS,
    CALL_WGLGETSWAPINTERVALEXT,
    CALL_WGLMAKECONTEXTCURRENTARB,
    CALL_WGLMAKECURRENT,
    CALL_WGLQUERYCURRENTRENDERERINTEGERWINE,
    CALL_WGLQUERYCURRENTRENDERERSTRINGWINE,
    CALL_WGLQUERYPBUFFERARB,
    CALL_WGLQUERYRENDERERINTEGERWINE,
    CALL_WGLQUERYRENDERERSTRINGWINE,
    CALL_WGLREALIZELAYERPALETTE,
    CALL_WGLRELEASEPBUFFERDCARB,
    CALL_WGLRELEASETEXIMAGEARB,
    CALL_WGLSETLAYERPALETTEENTRIES,
    CALL_WGLSETPBUFFERATTRIBARB,
    CALL_WGLSETPIXELFORMAT,
    CALL_WGLSETPIXELFORMATWINE,
    CALL_WGLSHARELISTS,
    CALL_WGLSWAPBUFFERS,
    CALL_WGLSWAPINTERVALEXT,
    CALL_WGLSWAPLAYERBUFFERS,
    CALL_WGLUSEFONTBITMAPSA,
    CALL_WGLUSEFONTBITMAPSW,
    CALL_WGLUSEFONTOUTLINESA,
    CALL_WGLUSEFONTOUTLINESW,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_glDebugEntry(struct qemu_syscall *call);
void qemu_glGetIntegerv(struct qemu_syscall *call);
void qemu_glGetString(struct qemu_syscall *call);
void qemu_glGetStringi(struct qemu_syscall *call);
void qemu_wglAllocateMemoryNV(struct qemu_syscall *call);
void qemu_wglBindTexImageARB(struct qemu_syscall *call);
void qemu_wglChoosePixelFormat(struct qemu_syscall *call);
void qemu_wglChoosePixelFormatARB(struct qemu_syscall *call);
void qemu_wglCopyContext(struct qemu_syscall *call);
void qemu_wglCreateContext(struct qemu_syscall *call);
void qemu_wglCreateContextAttribsARB(struct qemu_syscall *call);
void qemu_wglCreateLayerContext(struct qemu_syscall *call);
void qemu_wglCreatePbufferARB(struct qemu_syscall *call);
void qemu_wglDeleteContext(struct qemu_syscall *call);
void qemu_wglDescribeLayerPlane(struct qemu_syscall *call);
void qemu_wglDescribePixelFormat(struct qemu_syscall *call);
void qemu_wglDestroyPbufferARB(struct qemu_syscall *call);
void qemu_wglFreeMemoryNV(struct qemu_syscall *call);
void qemu_wglGetCurrentContext(struct qemu_syscall *call);
void qemu_wglGetCurrentDC(struct qemu_syscall *call);
void qemu_wglGetCurrentReadDCARB(struct qemu_syscall *call);
void qemu_wglGetExtensionsStringARB(struct qemu_syscall *call);
void qemu_wglGetExtensionsStringEXT(struct qemu_syscall *call);
void qemu_wglGetLayerPaletteEntries(struct qemu_syscall *call);
void qemu_wglGetPbufferDCARB(struct qemu_syscall *call);
void qemu_wglGetPixelFormat(struct qemu_syscall *call);
void qemu_wglGetPixelFormatAttribfvARB(struct qemu_syscall *call);
void qemu_wglGetPixelFormatAttribivARB(struct qemu_syscall *call);
void qemu_wglGetProcAddress(struct qemu_syscall *call);
void qemu_wglGetSwapIntervalEXT(struct qemu_syscall *call);
void qemu_wglMakeContextCurrentARB(struct qemu_syscall *call);
void qemu_wglMakeCurrent(struct qemu_syscall *call);
void qemu_wglQueryCurrentRendererIntegerWINE(struct qemu_syscall *call);
void qemu_wglQueryCurrentRendererStringWINE(struct qemu_syscall *call);
void qemu_wglQueryPbufferARB(struct qemu_syscall *call);
void qemu_wglQueryRendererIntegerWINE(struct qemu_syscall *call);
void qemu_wglQueryRendererStringWINE(struct qemu_syscall *call);
void qemu_wglRealizeLayerPalette(struct qemu_syscall *call);
void qemu_wglReleasePbufferDCARB(struct qemu_syscall *call);
void qemu_wglReleaseTexImageARB(struct qemu_syscall *call);
void qemu_wglSetLayerPaletteEntries(struct qemu_syscall *call);
void qemu_wglSetPbufferAttribARB(struct qemu_syscall *call);
void qemu_wglSetPixelFormat(struct qemu_syscall *call);
void qemu_wglSetPixelFormatWINE(struct qemu_syscall *call);
void qemu_wglShareLists(struct qemu_syscall *call);
void qemu_wglSwapBuffers(struct qemu_syscall *call);
void qemu_wglSwapIntervalEXT(struct qemu_syscall *call);
void qemu_wglSwapLayerBuffers(struct qemu_syscall *call);
void qemu_wglUseFontBitmapsA(struct qemu_syscall *call);
void qemu_wglUseFontBitmapsW(struct qemu_syscall *call);
void qemu_wglUseFontOutlinesA(struct qemu_syscall *call);
void qemu_wglUseFontOutlinesW(struct qemu_syscall *call);

HGLRC (* WINAPI p_wglCreateContextAttribsARB)(HDC hdc, HGLRC share, const int *attribs);
BOOL (* WINAPI p_wglMakeContextCurrentARB)(HDC draw_hdc, HDC read_hdc, HGLRC hglrc);
HDC (* WINAPI p_wglGetCurrentReadDCARB)(void);
const GLubyte * (* WINAPI p_glGetStringi)(GLenum name, GLuint index);
void * (* WINAPI p_wglAllocateMemoryNV)(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
void (* WINAPI p_wglFreeMemoryNV)(void *pointer);
BOOL (* WINAPI p_wglBindTexImageARB)(HPBUFFERARB handle, int buffer);
BOOL (* WINAPI p_wglReleaseTexImageARB)(HPBUFFERARB handle, int buffer);
BOOL (* WINAPI p_wglSetPbufferAttribARB)(HPBUFFERARB handle, const int *attribs);
BOOL (* WINAPI p_wglChoosePixelFormatARB)(HDC hdc, const int *iattribs, const FLOAT *fattribs, UINT max, int *formats, UINT *count);
BOOL (* WINAPI p_wglGetPixelFormatAttribivARB)(HDC hdc, int format, int layer, UINT count, const int *attribs, int *values);
BOOL (* WINAPI p_wglGetPixelFormatAttribfvARB)(HDC hdc, int format, int layer, UINT count, const int *attribs, FLOAT *values);
HPBUFFERARB (* WINAPI p_wglCreatePbufferARB)(HDC hdc, int format, int width, int height, const int *attribs);
HDC (* WINAPI p_wglGetPbufferDCARB)(HPBUFFERARB handle);
int (* WINAPI p_wglReleasePbufferDCARB)(HPBUFFERARB handle, HDC hdc);
BOOL (* WINAPI p_wglDestroyPbufferARB)(HPBUFFERARB handle);
BOOL (* WINAPI p_wglQueryPbufferARB)(HPBUFFERARB handle, int attrib, int *value);
INT (* WINAPI p_wglDescribePixelFormat)(HDC hdc, INT format, UINT size, PIXELFORMATDESCRIPTOR *descr);
const char * (* WINAPI p_wglGetExtensionsStringARB)(HDC hdc);
const char * (* WINAPI p_wglGetExtensionsStringEXT)(void);
BOOL (* WINAPI p_wglSwapIntervalEXT)(int interval);
int (* WINAPI p_wglGetSwapIntervalEXT)(void);
BOOL (* WINAPI p_wglSetPixelFormatWINE)(HDC hdc, int format);
BOOL (* WINAPI p_wglQueryCurrentRendererIntegerWINE)(GLenum attribute, GLuint *value);
const GLchar * (* WINAPI p_wglQueryCurrentRendererStringWINE)(GLenum attribute);
BOOL (* WINAPI p_wglQueryRendererIntegerWINE)(HDC dc, GLint renderer, GLenum attribute, GLuint *value);
const GLchar * (* WINAPI p_wglQueryRendererStringWINE)(HDC dc, GLint renderer, GLenum attribute);
INT (* WINAPI p_wglChoosePixelFormat)(HDC hdc, const PIXELFORMATDESCRIPTOR* ppfd);
INT (* WINAPI p_wglGetPixelFormat)(HDC hdc);
BOOL (* WINAPI p_wglSetPixelFormat)(HDC hdc, INT format, const PIXELFORMATDESCRIPTOR *descr);
BOOL (* WINAPI p_wglSwapBuffers)(HDC hdc);
GLint (* WINAPI p_glDebugEntry)(GLint unknown1, GLint unknown2);

#endif

#endif
