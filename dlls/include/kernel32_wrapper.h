/*
 * Copyright 2017-2018 Stefan Dösinger for CodeWeavers
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

#ifndef QEMU_KERNEL32_WRAPPER_H
#define QEMU_KERNEL32_WRAPPER_H

#include <wine/rbtree.h>
#include <wine/list.h>
#include <ws2def.h>

struct OVERLAPPED_data
{
    OVERLAPPED ov;

    struct qemu_OVERLAPPED *guest_ov;
    uint64_t guest_cb;
    DWORD cb_thread;

    /* For WSARecvMsg / WSASendMsg. */
    WSAMSG *msg;
    struct qemu_WSAMSG *guest_msg;
    WSABUF *buffers;
    BOOL wsa;
    DWORD wsa_flags;

    struct list free_list_entry;
    struct wine_rb_entry rbtree_entry;
    BOOL in_tree;
};

typedef struct OVERLAPPED_data * (* WINAPI FN_alloc_OVERLAPPED_data)(void *ov32,
        uint64_t guest_completion_cb, BOOL event);
typedef void (* WINAPI FN_process_OVERLAPPED_data)(uint64_t retval, struct OVERLAPPED_data *data);

#endif
