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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_FormatMessage
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t src;
    uint64_t msg_id, lang_id;
    uint64_t buffer;
    uint64_t size;
    uint64_t array;
    uint64_t free;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI FormatMessageW(DWORD flags, const void *src, DWORD msg_id, DWORD lang_id,
        wchar_t *buffer, DWORD size, va_list *args)
{
    struct qemu_FormatMessage call;
    const wchar_t *local_string = src;
    DWORD_PTR array[100];
    BOOL is_float[100];
    char highest = 0;
    unsigned int i;

    call.super.id = QEMU_SYSCALL_ID(CALL_FORMATMESSAGEW);
    call.src = (uint64_t)src;
    call.msg_id = msg_id;
    call.lang_id = lang_id;
    call.size = size;
    call.free = 0;

    /* If we have a va_args list we need to count the number of parameters the string loads. */
    if (!(flags & (FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_IGNORE_INSERTS)))
    {
        /* If the string is not immediately accessible, we need to load it first. */
        if (!(flags & FORMAT_MESSAGE_FROM_STRING))
        {
            struct qemu_FormatMessage call2;
            call.flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS;
            call.flags |= flags & (FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM);
            call.buffer = (uint64_t)&local_string;
            call.size = 0;
            call.array = 0;
            qemu_syscall(&call.super);
        }

        for (i = 0; local_string[i]; i++)
        {
            if (local_string[i] == '%' && local_string[i + 1] >= '0' && local_string[i + 1] <= '9')
            {
                char cur;
                i++;
                cur = local_string[i] - '0';
                if (local_string[i + 1] >= '0' && local_string[i + 1] <= '9')
                {
                    i++;
                    cur *= 10;
                    cur += local_string[i] - '0';
                }

                /* TODO: Parse * that might require extra args. */

                if (highest > cur)
                    highest = cur;

                is_float[cur] = FALSE; /* TODO: Parse format. */
            }
        }

        if (!(flags & FORMAT_MESSAGE_FROM_STRING))
            call.free = (uint64_t)local_string;

        call.array = (uint64_t)array;
    }
    else
    {
        call.array = (uint64_t)args;
    }
    call.flags = flags;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FormatMessageW(struct qemu_syscall *call)
{
    struct qemu_FormatMessage *c = (struct qemu_FormatMessage *)call;
    WINE_TRACE("\n");
    void *src;
    wchar_t *local_buffer;
    void *buffer_arg;

    if (c->flags & FORMAT_MESSAGE_FROM_STRING)
        src = QEMU_G2H(c->src);
    else
        src = (HANDLE)c->src;

    if (c->flags & FORMAT_MESSAGE_FROM_HMODULE && !src)
    {
        src = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);
        WINE_TRACE("Replaced NULL source module with %p\n", src);
    }

    if (c->flags & FORMAT_MESSAGE_ALLOCATE_BUFFER)
        buffer_arg = &local_buffer;
    else
        buffer_arg = QEMU_G2H(c->buffer);

    if (c->flags & (FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_IGNORE_INSERTS))
    {
        c->super.iret = FormatMessageW(c->flags, src, c->msg_id, c->lang_id,
                buffer_arg, c->size, QEMU_G2H(c->array));
    }
    else
    {
        /* Passing the array does not work right in this case. The argument indices
         * are wrong, so we'd have to edit the source string. */
        WINE_FIXME("va_arg input not handled yet\n");
        c->super.iret = FormatMessageW(c->flags | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                src, c->msg_id, c->lang_id, buffer_arg, c->size, QEMU_G2H(c->array));
    }

    if (c->flags & FORMAT_MESSAGE_ALLOCATE_BUFFER)
        *((uint64_t *)(QEMU_G2H(c->buffer))) = QEMU_H2G(local_buffer);

    if (c->free)
        LocalFree(QEMU_G2H(c->free));
}

#endif
