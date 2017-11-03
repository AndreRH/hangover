/*
 * Copyright 2017 Stefan Dösinger
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

/* Include this only in your main file. */

#include "callback_helper.h"

struct callback_entry_table
{
    unsigned int count;
    struct callback_entry entries[1];
};

void callback_init(struct callback_entry *entry, unsigned int params, void *proc)
{
    size_t offset;

    /* Note: A maximum of 4 parameters are supported. */

    offset = offsetof(struct callback_entry, selfptr) - offsetof(struct callback_entry, ldr_self);
    /* The load offset is stored in bits 5-24. The stored offset is left-shifted by 2 to generate the 21
     * bit real offset. So to place it in the right place we need our offset (multiple of 4, unless the
     * compiler screwed up terribly) shifted by another 3 bits.
     *
     * the register index is in the bottom bits, so for a callback that receives 4 parameters (in x0-x3)
     * we just OR 4 to store the selfptr in the 5th parameter (x4). */
    entry->ldr_self = 0x58000000 | params | (offset << 3); /* ldr x[params], offset */

    offset = offsetof(struct callback_entry, host_proc) - offsetof(struct callback_entry, ldr_proc);
    entry->ldr_proc = 0x58000000 | (params + 1) | (offset << 3);   /* ldr x[params + 1], offset */

    entry->br = 0xd61f0000 | ((params + 1) << 5); /* br x[params + 1] */

    entry->selfptr = entry;
    entry->host_proc = proc;
    entry->guest_proc = 0;

    __clear_cache(&entry->ldr_self, &entry->br + 1);
}

BOOL callback_alloc_table(struct callback_entry_table **table, unsigned int count,
        size_t entry_size, void *func, unsigned int params)
{
    struct callback_entry_table *ret;
    unsigned int i;

    ret = VirtualAlloc(NULL, entry_size * count + sizeof(ret->count),
            MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!ret)
        return FALSE;

    for (i = 0; i < count; ++i)
        callback_init(&ret->entries[i], params, func);

    ret->count = count;
    *table = ret;
    return TRUE;
}

struct callback_entry *callback_get(struct callback_entry_table *table, uint64_t guest_proc, BOOL *is_new)
{
    unsigned int i;

    /* Note that I cannot sort this thing because once a callback has been passed to Wine, it
     * needs to start at the same address. If the search speed becomes an issue a possible choice
     * is to create a separate rbtree that points to entries in this table. */
    for (i = 0; i < table->count; ++i)
    {
        if (table->entries[i].guest_proc == guest_proc)
        {
            if (is_new)
                *is_new = FALSE;

            return (struct callback_entry *)&table->entries[i];
        }

        if (!table->entries[i].guest_proc)
        {
            if (is_new)
                *is_new = TRUE;

            table->entries[i].guest_proc = guest_proc;
            return (struct callback_entry *)&table->entries[i];
        }
    }

    return NULL;
}

BOOL callback_is_in_table(const struct callback_entry_table *table, const struct callback_entry *entry)
{
    return (ULONG_PTR)entry >= (ULONG_PTR)&table->entries[0]
            && (ULONG_PTR)entry <= (ULONG_PTR)&table->entries[table->count];
}

