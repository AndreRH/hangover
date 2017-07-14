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
#include "va_helper_impl.h"
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu___getmainargs,
    qemu___crt_debugger_hook,
    qemu___cxxframehandler,
    qemu___iob_func,
    qemu___lconv_init,
    qemu___set_app_type,
    qemu___setusermatherr,
    qemu___wgetmainargs,
    qemu__amsg_exit,
    qemu__cexit,
    qemu__configthreadlocale,
    qemu__exit,
    qemu__lock,
    qemu__matherr,
    qemu__onexit,
    qemu__snwprintf,
    qemu__unlock,
    qemu__xcptfilter,
    qemu_abort,
    qemu_calloc,
    qemu_exit,
    qemu_fprintf,
    qemu_fprintf,
    qemu_free,
    qemu_fwrite,
    qemu_malloc,
    qemu_memcmp,
    qemu_memcpy,
    qemu_memset,
    qemu_fprintf,
    qemu_puts,
    qemu_qsort,
    qemu_raise,
    qemu_realloc,
    qemu_signal,
    qemu_sprintf,
    qemu_strlen,
    qemu_strncmp,
    qemu_terminate,
    qemu_wcscpy,
    qemu_fprintf,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE msvcrt;
    const char *dll_name;
    WINE_TRACE("Loading host-side msvcrt wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    if (QEMU_CURRENT_DLL == DLL_MSVCR100)
        dll_name = "msvcr100.dll";
    else
        dll_name = "msvcrt.dll";

    msvcrt = LoadLibraryA(dll_name);
    if (!msvcrt)
        WINE_ERR("Cannot find %s.\n", dll_name);

    p___crt_debugger_hook = (void *)GetProcAddress(msvcrt, "__crt_debugger_hook");
    p___getmainargs = (void *)GetProcAddress(msvcrt, "__getmainargs");
    p___iob_func = (void *)GetProcAddress(msvcrt, "__iob_func");
    p___lconv_init = (void *)GetProcAddress(msvcrt, "__lconv_init");
    p___set_app_type = (void *)GetProcAddress(msvcrt, "__set_app_type");
    p___setusermatherr = (void *)GetProcAddress(msvcrt, "__setusermatherr");
    p___wgetmainargs = (void *)GetProcAddress(msvcrt, "__wgetmainargs");
    p__amsg_exit = (void *)GetProcAddress(msvcrt, "_amsg_exit");
    p__cexit = (void *)GetProcAddress(msvcrt, "_cexit");
    p__configthreadlocale = (void *)GetProcAddress(msvcrt, "_configthreadlocale");
    p__exit = (void *)GetProcAddress(msvcrt, "_exit");
    p__lock = (void *)GetProcAddress(msvcrt, "_lock");
    p__matherr = (void *)GetProcAddress(msvcrt, "_matherr");
    p__onexit = (void *)GetProcAddress(msvcrt, "_onexit");
    p__unlock = (void *)GetProcAddress(msvcrt, "_unlock");
    p_abort = (void *)GetProcAddress(msvcrt, "abort");
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_memcmp = (void *)GetProcAddress(msvcrt, "memcmp");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_puts = (void *)GetProcAddress(msvcrt, "puts");
    p_qsort = (void *)GetProcAddress(msvcrt, "qsort");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");
    p_strncmp = (void *)GetProcAddress(msvcrt, "strncmp");
    p_terminate = (void *)GetProcAddress(msvcrt, "?terminate@@YAXXZ");
    p_vfprintf = (void *)GetProcAddress(msvcrt, "vfprintf");
    p_vfwprintf = (void *)GetProcAddress(msvcrt, "vfwprintf");
    p_vsprintf = (void *)GetProcAddress(msvcrt, "vsprintf");
    p_wcscpy = (void *)GetProcAddress(msvcrt, "wcscpy");

    msvcrt_tls = TlsAlloc();
    if (msvcrt_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    return dll_functions;
}

#endif
