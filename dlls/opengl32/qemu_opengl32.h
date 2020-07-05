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

#else

extern const struct qemu_ops *qemu_ops;
extern const syscall_handler dll_functions[];

#endif

#include "opengl_funcs.h"

extern struct opengl_funcs host_funcs;
void init_norm_funcs(void);

#endif
