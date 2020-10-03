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

extern const int extension_registry_size;
extern const OpenGL_extension extension_registry[];

#if __MINGW64_VERSION_MAJOR < 7
typedef void *GLeglClientBufferEXT;
typedef void *GLeglImageOES;
typedef void (APIENTRY  *GLVULKANPROCNV)(void);
GLAPI GLVULKANPROCNV APIENTRY glGetVkProcAddrNV (const GLchar *name);
GLAPI void APIENTRY glBufferStorageExternalEXT (GLenum target, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags);
GLAPI void APIENTRY glEGLImageTargetTexStorageEXT (GLenum target, GLeglImageOES image, const GLint* attrib_list);
GLAPI void APIENTRY glEGLImageTargetTextureStorageEXT (GLuint texture, GLeglImageOES image, const GLint* attrib_list);
GLAPI void APIENTRY glNamedBufferStorageExternalEXT (GLuint buffer, GLintptr offset, GLsizeiptr size, GLeglClientBufferEXT clientBuffer, GLbitfield flags);
#endif

#else

extern const struct qemu_ops *qemu_ops;
extern const syscall_handler dll_functions[];

#endif

#include "opengl_funcs.h"

extern struct opengl_funcs host_funcs;
void init_norm_funcs(void);

#endif
