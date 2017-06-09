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

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

int CDECL __lconv_init(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___LCONV_INIT);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu___lconv_init(struct qemu_syscall *call)
{
    /* This may be called by some other library if they use Wine's msvcrt.dll, but there is no
     * guarantee because many host-side libs will be linked against Linux libc. There is no harm
     * in calling this again it seems. */
    WINE_TRACE("\n");
    p___lconv_init();
}

#endif
