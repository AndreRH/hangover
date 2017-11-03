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

/* These helper functions can be used when callbacks passed to Wine are called
 * without any custom data, e.g. WNDPROCs. */

#ifndef CALLBACK_HELPER_H
#define CALLBACK_HELPER_H

struct callback_entry
{
    int32_t ldr_self;
    int32_t ldr_proc;
    int32_t br;
    void *selfptr;
    void *host_proc;
    uint64_t guest_proc;
};

struct callback_entry_table;

extern BOOL callback_alloc_table(struct callback_entry_table **table, unsigned int count,
        size_t entry_size, void *func, unsigned int params);
extern struct callback_entry *callback_get(struct callback_entry_table *table, uint64_t guest_proc, BOOL *is_new);
extern BOOL callback_is_in_table(const struct callback_entry_table *table, const struct callback_entry *entry);

static inline uint64_t callback_get_guest_proc(const struct callback_entry *callback)
{
    return callback->guest_proc;
}

#endif

