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
    uint64_t array_size;
    uint64_t free;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI FormatMessageW(DWORD flags, const void *src, DWORD msg_id, DWORD lang_id,
        WCHAR *buffer, DWORD size, va_list *args)
{
    struct qemu_FormatMessage call;
    const WCHAR *local_string = src;
    DWORD_PTR array[100];
    char highest = 0;
    unsigned int i;

    call.super.id = QEMU_SYSCALL_ID(CALL_FORMATMESSAGEW);
    call.src = (uint64_t)src;
    call.msg_id = msg_id;
    call.lang_id = lang_id;
    call.free = 0;

    /* If we have a va_args list we need to count the number of parameters the string loads. */
    if (!(flags & (FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_IGNORE_INSERTS)) && args)
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

        for (i = 0; local_string[i]; ++i)
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

                if (cur > highest)
                    highest = cur;
            }
        }

        /* Note that this function does not support floats. */
        for (i = 0; i < highest; i++)
            array[i] = va_arg(*args, uint64_t);
        call.array_size = highest;

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
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static DWORD call_FormatMessageW_va_list(DWORD flags, const void *src, DWORD msg_id, DWORD lang_id,
        WCHAR *buffer, DWORD size, ...)
{
    DWORD ret;
    va_list list;

    va_start(list, size);
    ret = FormatMessageW(flags, src, msg_id, lang_id, buffer, size, &list);
    va_end(list);

    return ret;
}

void qemu_FormatMessageW(struct qemu_syscall *call)
{
    struct qemu_FormatMessage *c = (struct qemu_FormatMessage *)call;
    WINE_TRACE("\n");
    void *src;
    WCHAR *local_buffer;
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

    if (c->flags & (FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_IGNORE_INSERTS)
            || !c->array)
    {
        c->super.iret = FormatMessageW(c->flags, src, c->msg_id, c->lang_id,
                buffer_arg, c->size, QEMU_G2H(c->array));
    }
    else
    {
        uint64_t *array = QEMU_G2H(c->array);

        WINE_TRACE("Calling va_arg version, %lu args\n", c->array_size);
        /* You'd think we can just add FORMAT_MESSAGE_ARGUMENT_ARRAY and pass the array,
         * but you'd be wrong. Using argument-dependent width and precision specifiers
         * shifts the argument offsets, and it does so in a different way for va_args
         * and arrays. So we can either fix up the string or call the va_args version.
         * I opted for the va_args version because of the hypothetical issue of 64 bit
         * ints in Win32 and because the extra offset that is added for arrays may
         * push a message with 99 inserts beyond the 99 limit. */
        switch(c->array_size)
        {
            case 0:
                c->super.iret = call_FormatMessageW_va_list(c->flags, src, c->msg_id,
                        c->lang_id, buffer_arg, c->size);
                break;
            case 1:
                c->super.iret = call_FormatMessageW_va_list(c->flags, src, c->msg_id,
                        c->lang_id, buffer_arg, c->size, array[0]);
                break;

            case 2:
                c->super.iret = call_FormatMessageW_va_list(c->flags, src, c->msg_id,
                        c->lang_id, buffer_arg, c->size, array[0], array[1]);
                break;

            case 3:
                c->super.iret = call_FormatMessageW_va_list(c->flags, src, c->msg_id,
                        c->lang_id, buffer_arg, c->size, array[0], array[1], array[2]);
                break;

            case 4:
                c->super.iret = call_FormatMessageW_va_list(c->flags, src, c->msg_id,
                        c->lang_id, buffer_arg, c->size, array[0], array[1], array[2],
                        array[3]);
                break;

            default:
                WINE_FIXME("Handle arbitrary number of arguments\n");
            case 5:
                c->super.iret = call_FormatMessageW_va_list(c->flags, src, c->msg_id,
                        c->lang_id, buffer_arg, c->size, array[0], array[1], array[2],
                        array[3], array[4]);
                break;
        }
    }

    if (c->flags & FORMAT_MESSAGE_ALLOCATE_BUFFER)
        *((uint64_t *)(QEMU_G2H(c->buffer))) = QEMU_H2G(local_buffer);

    if (c->free)
    {
        WINE_TRACE("Freeing old buffer %p\n", QEMU_G2H(c->free));
        LocalFree(QEMU_G2H(c->free));
    }
}

#endif
