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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers.
 *
 * Wrapping msvcrt like this is not my first choice. In theory it only calls Windows
 * API functions and has a lot of small functions, so running it as a Win32/64 DLL
 * would save a lot of work and would most likely be faster and more compatible. Keep
 * in mind that CRT code is embedded into every crt-linked binary. Things will go
 * wrong if the host-side msvcrt.dll tries to access the module image - and it seems
 * the code in dlls/msvcrt/cpp.c is doing just that.
 *
 * Unfortunately Wine's msvcrt is not stand-alone and imports symbols from Linux/OSX
 * libc. So it is disabled in a mingw cross compile build, and if it is forced on it
 * will link against itself...
 */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu___getmainargs,
    qemu___iob_func,
    qemu___lconv_init,
    qemu___set_app_type,
    qemu___setusermatherr,
    qemu__amsg_exit,
    qemu__cexit,
    qemu__lock,
    qemu__matherr,
    qemu__onexit,
    qemu__unlock,
    qemu_abort,
    qemu_calloc,
    qemu_exit,
    qemu_fprintf,
    qemu_free,
    qemu_fwrite,
    qemu_malloc,
    qemu_memcpy,
    qemu_memset,
    qemu_fprintf,
    qemu_puts,
    qemu_realloc,
    qemu_signal,
    qemu_strlen,
    qemu_strncmp
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE msvcrt;
    WINE_TRACE("Loading host-side msvcrt wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    msvcrt = LoadLibraryA("msvcrt.dll");
    if (!msvcrt)
        WINE_ERR("Cannot find msvcrt.dll\n");

    p___getmainargs = (void *)GetProcAddress(msvcrt, "__getmainargs");
    p___iob_func = (void *)GetProcAddress(msvcrt, "__iob_func");
    p___lconv_init = (void *)GetProcAddress(msvcrt, "__lconv_init");
    p___set_app_type = (void *)GetProcAddress(msvcrt, "__set_app_type");
    p___setusermatherr = (void *)GetProcAddress(msvcrt, "__setusermatherr");
    p__amsg_exit = (void *)GetProcAddress(msvcrt, "_amsg_exit");
    p__cexit = (void *)GetProcAddress(msvcrt, "_cexit");
    p__lock = (void *)GetProcAddress(msvcrt, "_lock");
    p__matherr = (void *)GetProcAddress(msvcrt, "_matherr");
    p__onexit = (void *)GetProcAddress(msvcrt, "_onexit");
    p__unlock = (void *)GetProcAddress(msvcrt, "_unlock");
    p_abort = (void *)GetProcAddress(msvcrt, "abort");
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_fprintf = (void *)GetProcAddress(msvcrt, "fprintf");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_puts = (void *)GetProcAddress(msvcrt, "puts");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");
    p_strncmp = (void *)GetProcAddress(msvcrt, "strncmp");

    return dll_functions;
}

#endif
