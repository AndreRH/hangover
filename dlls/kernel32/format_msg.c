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
#include "qemu_kernel32.h"
#include "va_helper.h"

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

/* Duplicate the logic from the real implementation to count how often va_list is actually
 * read. I tried to simplify it, but just banged my head against the wall. */
static void get_arg(int nr, unsigned int *last, unsigned int *read)
{
    if (nr == -1) nr = *last + 1;
    while (nr > *last)
    {
        (*last)++;
        (*read)++;
    }
    if (nr > *last) *last = nr;
}

WINBASEAPI DWORD WINAPI FormatMessageA(DWORD flags, const void *src, DWORD msg_id, DWORD lang_id,
        char *buffer, DWORD size, va_list *args)
{
    struct qemu_FormatMessage call;
    const char *local_string = src;
    struct va_array array[100];
    unsigned int last = 0, read = 0;
    unsigned int i;

    call.super.id = QEMU_SYSCALL_ID(CALL_FORMATMESSAGEA);
    call.src = (ULONG_PTR)src;
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
            call.buffer = (ULONG_PTR)&local_string;
            call.size = 0;
            call.array = 0;
            qemu_syscall(&call.super);
            local_string = (char *)(ULONG_PTR)call.buffer;
            if (!call.super.iret)
                return call.super.iret;
        }

        for (i = 0; local_string[i]; ++i)
        {
            if (local_string[i] == '%' && local_string[i + 1] >= '0' && local_string[i + 1] <= '9')
            {
                int cur = 0;
                i++;

                cur = local_string[i] - '0';
                if (local_string[i + 1] >= '0' && local_string[i + 1] <= '9')
                {
                    i++;
                    cur *= 10;
                    cur += local_string[i] - '0';
                }

                if (local_string[i + 1] == '!')
                {
                    unsigned int args_found = 0;
                    i++;
                    while (local_string[i + 1] != '!')
                    {
                        if (local_string[i + 1] == '*')
                        {
                            get_arg(cur, &last, &read);
                            cur = -1;
                        }
                        i++;
                    }
                }
                /* replicate MS bug: drop an argument when using va_list with width/precision */
                if (cur == -1)
                    last--;
                get_arg(cur, &last, &read);
            }
        }

        /* Note that this function does not support floats. */
        for (i = 0; i < read; i++)
        {
            array[i].arg = va_arg(*args, ULONG_PTR);
            array[i].is_float = FALSE;
        }
        call.array_size = read;

        if (!(flags & FORMAT_MESSAGE_FROM_STRING))
            call.free = (ULONG_PTR)local_string;

        call.array = (ULONG_PTR)array;
    }
    else
    {
        call.array = (ULONG_PTR)args;
    }
    call.flags = flags;
    call.buffer = (ULONG_PTR)buffer;
    call.size = size;

    qemu_syscall(&call.super);
    if (flags & FORMAT_MESSAGE_ALLOCATE_BUFFER && buffer)
        *(char **)buffer = (char *)(ULONG_PTR)call.buffer;

    return call.super.iret;
}

WINBASEAPI DWORD WINAPI FormatMessageW(DWORD flags, const void *src, DWORD msg_id, DWORD lang_id,
        WCHAR *buffer, DWORD size, va_list *args)
{
    struct qemu_FormatMessage call;
    const WCHAR *local_string = src;
    struct va_array array[100];
    unsigned int last = 0, read = 0;
    unsigned int i;

    call.super.id = QEMU_SYSCALL_ID(CALL_FORMATMESSAGEW);
    call.src = (ULONG_PTR)src;
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
            call.buffer = (ULONG_PTR)&local_string;
            call.size = 0;
            call.array = 0;
            qemu_syscall(&call.super);
            local_string = (WCHAR *)(ULONG_PTR)call.buffer;
            if (!call.super.iret)
                return call.super.iret;
        }

        for (i = 0; local_string[i]; ++i)
        {
            if (local_string[i] == '%' && local_string[i + 1] >= '0' && local_string[i + 1] <= '9')
            {
                int cur = 0;
                i++;

                cur = local_string[i] - '0';
                if (local_string[i + 1] >= '0' && local_string[i + 1] <= '9')
                {
                    i++;
                    cur *= 10;
                    cur += local_string[i] - '0';
                }

                if (local_string[i + 1] == '!')
                {
                    unsigned int args_found = 0;
                    i++;
                    while (local_string[i + 1] != '!')
                    {
                        if (local_string[i + 1] == '*')
                        {
                            get_arg(cur, &last, &read);
                            cur = -1;
                        }
                        i++;
                    }
                }
                /* replicate MS bug: drop an argument when using va_list with width/precision */
                if (cur == -1)
                    last--;
                get_arg(cur, &last, &read);
            }
        }

        /* Note that this function does not support floats. */
        for (i = 0; i < read; i++)
        {
            array[i].arg = va_arg(*args, ULONG_PTR);
            array[i].is_float = FALSE;
        }
        call.array_size = read;

        if (!(flags & FORMAT_MESSAGE_FROM_STRING))
            call.free = (ULONG_PTR)local_string;

        call.array = (ULONG_PTR)array;
    }
    else
    {
        call.array = (ULONG_PTR)args;
    }
    call.flags = flags;
    call.buffer = (ULONG_PTR)buffer;
    call.size = size;

    qemu_syscall(&call.super);
    if (flags & FORMAT_MESSAGE_ALLOCATE_BUFFER && buffer)
        *(WCHAR **)buffer = (WCHAR *)(ULONG_PTR)call.buffer;

    return call.super.iret;
}

#else

struct format_message_data
{
    BOOL unicode;
    DWORD flags;
    const void *src;
    DWORD msg_id, lang_id;
    void *buffer;
    DWORD size;
};

static uint64_t CDECL call_FormatMessage_va_list(void *data, ...)
{
    const struct format_message_data *d = data;
    uint64_t ret;
    __ms_va_list list;

    __ms_va_start(list, data);
    if (d->unicode)
        ret = FormatMessageW(d->flags, d->src, d->msg_id, d->lang_id, d->buffer, d->size, (void *)&list);
    else
        ret = FormatMessageA(d->flags, d->src, d->msg_id, d->lang_id, d->buffer, d->size, (void *)&list);
    __ms_va_end(list);

    return ret;
}

void qemu_FormatMessage(struct qemu_syscall *call)
{
    struct qemu_FormatMessage *c = (struct qemu_FormatMessage *)call;
    WINE_TRACE("\n");
    void *src;
    WCHAR *local_buffer;
    void *buffer_arg;
    BOOL unicode;

    unicode = c->super.id == QEMU_SYSCALL_ID(CALL_FORMATMESSAGEW);

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
        buffer_arg = c->buffer ? &local_buffer : NULL;
    else
        buffer_arg = QEMU_G2H(c->buffer);

    if (c->flags & (FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_IGNORE_INSERTS)
            || !c->array)
    {
#if GUEST_BIT == HOST_BIT
        ULONG_PTR *array;
        array = QEMU_G2H(c->array);
#else
        ULONG_PTR *array, copy[100];
        qemu_handle *guest_array = QEMU_G2H(c->array);
        unsigned int i;

        if (guest_array)
        {
            WINE_FIXME("Implement array-style counting for nicer 32 bit conversion\n");
            for (i = 0; i < sizeof(copy) / sizeof(*copy); ++i)
            {
                if (IsBadReadPtr(&guest_array[i], sizeof(guest_array[i])))
                    break;
                copy[i] = guest_array[i];
            }
            array = copy;
        }
        else
        {
            array = NULL;
        }
#endif
        if (unicode)
            c->super.iret = FormatMessageW(c->flags, src, c->msg_id, c->lang_id,
                    buffer_arg, c->size, (void *)array);
        else
            c->super.iret = FormatMessageA(c->flags, src, c->msg_id, c->lang_id,
                    buffer_arg, c->size, (void *)array);
    }
    else
    {
        struct va_array *array = QEMU_G2H(c->array);
        struct format_message_data data = {unicode, c->flags, src, c->msg_id,
                c->lang_id, buffer_arg, c->size};

        WINE_TRACE("Calling va_arg version, %lu args\n", (unsigned long)c->array_size);
        /* You'd think we can just add FORMAT_MESSAGE_ARGUMENT_ARRAY and pass the array,
         * but you'd be wrong. Using argument-dependent width and precision specifiers
         * shifts the argument offsets, and it does so in a different way for va_args
         * and arrays. So we can either fix up the string or call the va_args version.
         * I opted for the va_args version because of the hypothetical issue of 64 bit
         * ints in Win32 and because the extra offset that is added for arrays may
         * push a message with 99 inserts beyond the 99 limit. */
        c->super.iret = call_va(call_FormatMessage_va_list, &data, c->array_size, 0, array);
    }

    if (c->flags & FORMAT_MESSAGE_ALLOCATE_BUFFER)
        c->buffer = QEMU_H2G(local_buffer);

    if (c->free)
    {
        WINE_TRACE("Freeing old buffer %p\n", QEMU_G2H(c->free));
        LocalFree(QEMU_G2H(c->free));
    }
}

#endif
