/*
 * Copyright 2017 André Hentschel
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
#include <wct.h>
#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifdef QEMU_DLL_GUEST
typedef void *WMIHANDLE, *MOFHANDLE, MOFRESOURCEINFOA, MOFRESOURCEINFOW, WMIGUIDINFORMATION;
#else
#include <wine/debug.h>
#include <wmium.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_WmiExecuteMethodA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t method;
    uint64_t inputsize;
    uint64_t inputbuffer;
    uint64_t outputsize;
    uint64_t outputbuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiExecuteMethodA(WMIHANDLE handle, const char *name, ULONG method, ULONG inputsize, void *inputbuffer, ULONG *outputsize, void *outputbuffer)
{
    struct qemu_WmiExecuteMethodA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIEXECUTEMETHODA);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.method = method;
    call.inputsize = inputsize;
    call.inputbuffer = (ULONG_PTR)inputbuffer;
    call.outputsize = (ULONG_PTR)outputsize;
    call.outputbuffer = (ULONG_PTR)outputbuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiExecuteMethodA(struct qemu_syscall *call)
{
    struct qemu_WmiExecuteMethodA *c = (struct qemu_WmiExecuteMethodA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiExecuteMethodA(QEMU_G2H(c->handle), QEMU_G2H(c->name), c->method, c->inputsize, QEMU_G2H(c->inputbuffer), QEMU_G2H(c->outputsize), QEMU_G2H(c->outputbuffer));
}

#endif

struct qemu_WmiExecuteMethodW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t method;
    uint64_t inputsize;
    uint64_t inputbuffer;
    uint64_t outputsize;
    uint64_t outputbuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiExecuteMethodW(WMIHANDLE handle, const WCHAR *name, ULONG method, ULONG inputsize, void *inputbuffer, ULONG *outputsize, void *outputbuffer)
{
    struct qemu_WmiExecuteMethodW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIEXECUTEMETHODW);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.method = method;
    call.inputsize = inputsize;
    call.inputbuffer = (ULONG_PTR)inputbuffer;
    call.outputsize = (ULONG_PTR)outputsize;
    call.outputbuffer = (ULONG_PTR)outputbuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiExecuteMethodW(struct qemu_syscall *call)
{
    struct qemu_WmiExecuteMethodW *c = (struct qemu_WmiExecuteMethodW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiExecuteMethodW(QEMU_G2H(c->handle), QEMU_G2H(c->name), c->method, c->inputsize, QEMU_G2H(c->inputbuffer), QEMU_G2H(c->outputsize), QEMU_G2H(c->outputbuffer));
}

#endif

struct qemu_WmiFreeBuffer
{
    struct qemu_syscall super;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WMIAPI WmiFreeBuffer(void *buffer)
{
    struct qemu_WmiFreeBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIFREEBUFFER);
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);
}

#else

void qemu_WmiFreeBuffer(struct qemu_syscall *call)
{
    struct qemu_WmiFreeBuffer *c = (struct qemu_WmiFreeBuffer *)call;
    WINE_FIXME("Unverified!\n");
    WmiFreeBuffer(QEMU_G2H(c->buffer));
}

#endif

struct qemu_WmiMofEnumerateResourcesA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiMofEnumerateResourcesA(MOFHANDLE handle, ULONG *count, MOFRESOURCEINFOA **resource)
{
    struct qemu_WmiMofEnumerateResourcesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIMOFENUMERATERESOURCESA);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiMofEnumerateResourcesA(struct qemu_syscall *call)
{
    struct qemu_WmiMofEnumerateResourcesA *c = (struct qemu_WmiMofEnumerateResourcesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiMofEnumerateResourcesA(QEMU_G2H(c->handle), QEMU_G2H(c->count), QEMU_G2H(c->resource));
}

#endif

struct qemu_WmiMofEnumerateResourcesW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiMofEnumerateResourcesW(MOFHANDLE handle, ULONG *count, MOFRESOURCEINFOW **resource)
{
    struct qemu_WmiMofEnumerateResourcesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIMOFENUMERATERESOURCESW);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiMofEnumerateResourcesW(struct qemu_syscall *call)
{
    struct qemu_WmiMofEnumerateResourcesW *c = (struct qemu_WmiMofEnumerateResourcesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiMofEnumerateResourcesW(QEMU_G2H(c->handle), QEMU_G2H(c->count), QEMU_G2H(c->resource));
}

#endif

struct qemu_WmiNotificationRegistrationA
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t enable;
    uint64_t info;
    uint64_t context;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiNotificationRegistrationA(GUID *guid, BOOLEAN enable, void *info, ULONG_PTR context, ULONG flags)
{
    struct qemu_WmiNotificationRegistrationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMINOTIFICATIONREGISTRATIONA);
    call.guid = (ULONG_PTR)guid;
    call.enable = enable;
    call.info = (ULONG_PTR)info;
    call.context = context;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiNotificationRegistrationA(struct qemu_syscall *call)
{
    struct qemu_WmiNotificationRegistrationA *c = (struct qemu_WmiNotificationRegistrationA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiNotificationRegistrationA(QEMU_G2H(c->guid), c->enable, QEMU_G2H(c->info), c->context, c->flags);
}

#endif

struct qemu_WmiNotificationRegistrationW
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t enable;
    uint64_t info;
    uint64_t context;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiNotificationRegistrationW(GUID *guid, BOOLEAN enable, void *info, ULONG_PTR context, ULONG flags)
{
    struct qemu_WmiNotificationRegistrationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMINOTIFICATIONREGISTRATIONW);
    call.guid = (ULONG_PTR)guid;
    call.enable = enable;
    call.info = (ULONG_PTR)info;
    call.context = context;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiNotificationRegistrationW(struct qemu_syscall *call)
{
    struct qemu_WmiNotificationRegistrationW *c = (struct qemu_WmiNotificationRegistrationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiNotificationRegistrationW(QEMU_G2H(c->guid), c->enable, QEMU_G2H(c->info), c->context, c->flags);
}

#endif

struct qemu_WmiOpenBlock
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t access;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI WmiOpenBlock(GUID *guid, ULONG access, WMIHANDLE *handle)
{
    struct qemu_WmiOpenBlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIOPENBLOCK);
    call.guid = (ULONG_PTR)guid;
    call.access = access;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiOpenBlock(struct qemu_syscall *call)
{
    struct qemu_WmiOpenBlock *c = (struct qemu_WmiOpenBlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiOpenBlock(QEMU_G2H(c->guid), c->access, QEMU_G2H(c->handle));
}

#endif

struct qemu_WmiQueryAllDataA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiQueryAllDataA(WMIHANDLE handle, ULONG *size, void *buffer)
{
    struct qemu_WmiQueryAllDataA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIQUERYALLDATAA);
    call.handle = (ULONG_PTR)handle;
    call.size = (ULONG_PTR)size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiQueryAllDataA(struct qemu_syscall *call)
{
    struct qemu_WmiQueryAllDataA *c = (struct qemu_WmiQueryAllDataA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiQueryAllDataA(QEMU_G2H(c->handle), QEMU_G2H(c->size), QEMU_G2H(c->buffer));
}

#endif

struct qemu_WmiQueryAllDataW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiQueryAllDataW(WMIHANDLE handle, ULONG *size, void *buffer)
{
    struct qemu_WmiQueryAllDataW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIQUERYALLDATAW);
    call.handle = (ULONG_PTR)handle;
    call.size = (ULONG_PTR)size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiQueryAllDataW(struct qemu_syscall *call)
{
    struct qemu_WmiQueryAllDataW *c = (struct qemu_WmiQueryAllDataW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiQueryAllDataW(QEMU_G2H(c->handle), QEMU_G2H(c->size), QEMU_G2H(c->buffer));
}

#endif

struct qemu_WmiQueryGuidInformation
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiQueryGuidInformation(WMIHANDLE handle, WMIGUIDINFORMATION *info)
{
    struct qemu_WmiQueryGuidInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMIQUERYGUIDINFORMATION);
    call.handle = (ULONG_PTR)handle;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiQueryGuidInformation(struct qemu_syscall *call)
{
    struct qemu_WmiQueryGuidInformation *c = (struct qemu_WmiQueryGuidInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiQueryGuidInformation(QEMU_G2H(c->handle), QEMU_G2H(c->info));
}

#endif

struct qemu_WmiSetSingleInstanceA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t reserved;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiSetSingleInstanceA(WMIHANDLE handle, const char *name, ULONG reserved, ULONG size, void *buffer)
{
    struct qemu_WmiSetSingleInstanceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMISETSINGLEINSTANCEA);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.reserved = reserved;
    call.size = size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiSetSingleInstanceA(struct qemu_syscall *call)
{
    struct qemu_WmiSetSingleInstanceA *c = (struct qemu_WmiSetSingleInstanceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiSetSingleInstanceA(QEMU_G2H(c->handle), QEMU_G2H(c->name), c->reserved, c->size, QEMU_G2H(c->buffer));
}

#endif

struct qemu_WmiSetSingleInstanceW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t reserved;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiSetSingleInstanceW(WMIHANDLE handle, const WCHAR *name, ULONG reserved, ULONG size, void *buffer)
{
    struct qemu_WmiSetSingleInstanceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMISETSINGLEINSTANCEW);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.reserved = reserved;
    call.size = size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiSetSingleInstanceW(struct qemu_syscall *call)
{
    struct qemu_WmiSetSingleInstanceW *c = (struct qemu_WmiSetSingleInstanceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiSetSingleInstanceW(QEMU_G2H(c->handle), QEMU_G2H(c->name), c->reserved, c->size, QEMU_G2H(c->buffer));
}

#endif

struct qemu_WmiSetSingleItemA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t id;
    uint64_t reserved;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiSetSingleItemA(WMIHANDLE handle, const char *name, ULONG id, ULONG reserved, ULONG size, void *buffer)
{
    struct qemu_WmiSetSingleItemA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMISETSINGLEITEMA);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.id = id;
    call.reserved = reserved;
    call.size = size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiSetSingleItemA(struct qemu_syscall *call)
{
    struct qemu_WmiSetSingleItemA *c = (struct qemu_WmiSetSingleItemA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiSetSingleItemA(QEMU_G2H(c->handle), QEMU_G2H(c->name), c->id, c->reserved, c->size, QEMU_G2H(c->buffer));
}

#endif

struct qemu_WmiSetSingleItemW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t id;
    uint64_t reserved;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WMIAPI WmiSetSingleItemW(WMIHANDLE handle, const WCHAR *name, ULONG id, ULONG reserved, ULONG size, void *buffer)
{
    struct qemu_WmiSetSingleItemW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMISETSINGLEITEMW);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.id = id;
    call.reserved = reserved;
    call.size = size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WmiSetSingleItemW(struct qemu_syscall *call)
{
    struct qemu_WmiSetSingleItemW *c = (struct qemu_WmiSetSingleItemW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WmiSetSingleItemW(QEMU_G2H(c->handle), QEMU_G2H(c->name), c->id, c->reserved, c->size, QEMU_G2H(c->buffer));
}

#endif

