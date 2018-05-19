/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif


struct qemu_CertAddStoreToCollection
{
    struct qemu_syscall super;
    uint64_t hCollectionStore;
    uint64_t hSiblingStore;
    uint64_t dwUpdateFlags;
    uint64_t dwPriority;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddStoreToCollection(HCERTSTORE hCollectionStore, HCERTSTORE hSiblingStore,
        DWORD dwUpdateFlags, DWORD dwPriority)
{
    struct qemu_CertAddStoreToCollection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDSTORETOCOLLECTION);
    call.hCollectionStore = (ULONG_PTR)hCollectionStore;
    call.hSiblingStore = (ULONG_PTR)hSiblingStore;
    call.dwUpdateFlags = dwUpdateFlags;
    call.dwPriority = dwPriority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddStoreToCollection(struct qemu_syscall *call)
{
    struct qemu_CertAddStoreToCollection *c = (struct qemu_CertAddStoreToCollection *)call;
    WINE_TRACE("\n");
    c->super.iret = CertAddStoreToCollection(QEMU_G2H(c->hCollectionStore), QEMU_G2H(c->hSiblingStore),
            c->dwUpdateFlags, c->dwPriority);
}

#endif

struct qemu_CertRemoveStoreFromCollection
{
    struct qemu_syscall super;
    uint64_t hCollectionStore;
    uint64_t hSiblingStore;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CertRemoveStoreFromCollection(HCERTSTORE hCollectionStore, HCERTSTORE hSiblingStore)
{
    struct qemu_CertRemoveStoreFromCollection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTREMOVESTOREFROMCOLLECTION);
    call.hCollectionStore = (ULONG_PTR)hCollectionStore;
    call.hSiblingStore = (ULONG_PTR)hSiblingStore;

    qemu_syscall(&call.super);
}

#else

void qemu_CertRemoveStoreFromCollection(struct qemu_syscall *call)
{
    struct qemu_CertRemoveStoreFromCollection *c = (struct qemu_CertRemoveStoreFromCollection *)call;
    WINE_FIXME("Unverified!\n");
    CertRemoveStoreFromCollection(QEMU_G2H(c->hCollectionStore), QEMU_G2H(c->hSiblingStore));
}

#endif

