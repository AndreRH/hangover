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

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"
#include "ntdll_wrapper.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_Sleep
{
    struct qemu_syscall super;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI Sleep(DWORD timeout)
{
    struct qemu_Sleep call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SLEEP);
    call.timeout = (uint64_t)timeout;

    qemu_syscall(&call.super);
}

#else

void qemu_Sleep(struct qemu_syscall *call)
{
    struct qemu_Sleep *c = (struct qemu_Sleep *)call;
    WINE_TRACE("\n");
    Sleep(c->timeout);
}

#endif

struct qemu_SleepEx
{
    struct qemu_syscall super;
    uint64_t timeout;
    uint64_t alertable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SleepEx(DWORD timeout, BOOL alertable)
{
    struct qemu_SleepEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SLEEPEX);
    call.timeout = timeout;
    call.alertable = alertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SleepEx(struct qemu_syscall *call)
{
    struct qemu_SleepEx *c = (struct qemu_SleepEx *)call;
    WINE_TRACE("\n");
    c->super.iret = SleepEx(c->timeout, c->alertable);
}

#endif

struct qemu_SwitchToThread
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SwitchToThread(void)
{
    struct qemu_SwitchToThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SWITCHTOTHREAD);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SwitchToThread(struct qemu_syscall *call)
{
    struct qemu_SwitchToThread *c = (struct qemu_SwitchToThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SwitchToThread();
}

#endif

struct qemu_WaitForSingleObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WaitForSingleObject(HANDLE handle, DWORD timeout)
{
    struct qemu_WaitForSingleObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITFORSINGLEOBJECT);
    call.handle = (uint64_t)handle;
    call.timeout = timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForSingleObject(struct qemu_syscall *call)
{
    struct qemu_WaitForSingleObject *c = (struct qemu_WaitForSingleObject *)call;
    WINE_TRACE("\n");
    c->super.iret = WaitForSingleObject((HANDLE)c->handle, c->timeout);
}

#endif

struct qemu_WaitForSingleObjectEx
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t timeout;
    uint64_t alertable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WaitForSingleObjectEx(HANDLE handle, DWORD timeout, BOOL alertable)
{
    struct qemu_WaitForSingleObjectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITFORSINGLEOBJECTEX);
    call.handle = (uint64_t)handle;
    call.timeout = timeout;
    call.alertable = alertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForSingleObjectEx(struct qemu_syscall *call)
{
    struct qemu_WaitForSingleObjectEx *c = (struct qemu_WaitForSingleObjectEx *)call;
    WINE_TRACE("\n");
    c->super.iret = WaitForSingleObjectEx(QEMU_G2H(c->handle), c->timeout, c->alertable);
}

#endif

struct qemu_WaitForMultipleObjects
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t handles;
    uint64_t wait_all;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WaitForMultipleObjects(DWORD count, const HANDLE *handles, BOOL wait_all, DWORD timeout)
{
    struct qemu_WaitForMultipleObjects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITFORMULTIPLEOBJECTS);
    call.count = count;
    call.handles = (uint64_t)handles;
    call.wait_all = wait_all;
    call.timeout = timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForMultipleObjects(struct qemu_syscall *call)
{
    struct qemu_WaitForMultipleObjects *c = (struct qemu_WaitForMultipleObjects *)call;
    WINE_TRACE("\n");
    c->super.iret = WaitForMultipleObjects(c->count, QEMU_G2H(c->handles), c->wait_all, c->timeout);
}

#endif

struct qemu_WaitForMultipleObjectsEx
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t handles;
    uint64_t wait_all;
    uint64_t timeout;
    uint64_t alertable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WaitForMultipleObjectsEx(DWORD count, const HANDLE *handles, BOOL wait_all, DWORD timeout, BOOL alertable)
{
    struct qemu_WaitForMultipleObjectsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITFORMULTIPLEOBJECTSEX);
    call.count = (uint64_t)count;
    call.handles = (uint64_t)handles;
    call.wait_all = (uint64_t)wait_all;
    call.timeout = (uint64_t)timeout;
    call.alertable = (uint64_t)alertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForMultipleObjectsEx(struct qemu_syscall *call)
{
    struct qemu_WaitForMultipleObjectsEx *c = (struct qemu_WaitForMultipleObjectsEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WaitForMultipleObjectsEx(c->count, QEMU_G2H(c->handles), c->wait_all, c->timeout, c->alertable);
}

#endif

struct qemu_RegisterWaitForSingleObject
{
    struct qemu_syscall super;
    uint64_t phNewWaitObject;
    uint64_t hObject;
    uint64_t Callback;
    uint64_t Context;
    uint64_t dwMilliseconds;
    uint64_t dwFlags;
    uint64_t wrapper;
};

struct qemu_wait_callback
{
    uint64_t func;
    uint64_t context;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

static void CALLBACK host_wait_callback(struct qemu_wait_callback *data)
{
    WAITORTIMERCALLBACK cb = (WAITORTIMERCALLBACK)data->func;
    cb((void *)data->context, data->timeout);
}

WINBASEAPI BOOL WINAPI RegisterWaitForSingleObject(PHANDLE phNewWaitObject, HANDLE hObject, WAITORTIMERCALLBACK Callback, PVOID Context, ULONG dwMilliseconds, ULONG dwFlags)
{
    struct qemu_RegisterWaitForSingleObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERWAITFORSINGLEOBJECT);
    call.phNewWaitObject = (uint64_t)phNewWaitObject;
    call.hObject = (uint64_t)hObject;
    call.Callback = (uint64_t)Callback;
    call.Context = (uint64_t)Context;
    call.dwMilliseconds = dwMilliseconds;
    call.dwFlags = dwFlags;
    call.wrapper = (uint64_t)host_wait_callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void CALLBACK guest_wait_callback(void *p, BOOLEAN timeout)
{
    struct qemu_ntdll_wait_work_item *item = p;
    struct qemu_wait_callback call;

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, %u).\n", item->guest_cb, item->context, timeout);

    call.func = item->guest_cb;
    call.context = item->context;
    call.timeout = timeout;

    qemu_ops->qemu_execute(QEMU_G2H(item->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned.\n");
}

void qemu_RegisterWaitForSingleObject(struct qemu_syscall *call)
{
    struct qemu_RegisterWaitForSingleObject *c = (struct qemu_RegisterWaitForSingleObject *)call;
    struct qemu_ntdll_wait_work_item *item;

    WINE_TRACE("Unverified!\n");

    item = HeapAlloc(GetProcessHeap(), 0, sizeof(*item));
    if (!item)
    {
        c->super.iret = FALSE;
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return;
    }
    item->context = c->Context;
    item->guest_cb = c->Callback;
    item->wrapper = c->wrapper;

    c->super.iret = RegisterWaitForSingleObject(&item->host_handle, (HANDLE)c->hObject, guest_wait_callback,
            item, c->dwMilliseconds, c->dwFlags);
    if (!c->super.iret)
    {
        HeapFree(GetProcessHeap(), 0, item);
        return;
    }

    *(uint64_t *)QEMU_G2H(c->phNewWaitObject) = QEMU_H2G(item);
}

#endif

struct qemu_RegisterWaitForSingleObjectEx
{
    struct qemu_syscall super;
    uint64_t hObject;
    uint64_t Callback;
    uint64_t Context;
    uint64_t dwMilliseconds;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RegisterWaitForSingleObjectEx(HANDLE hObject, WAITORTIMERCALLBACK Callback, PVOID Context, ULONG dwMilliseconds, ULONG dwFlags)
{
    struct qemu_RegisterWaitForSingleObjectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERWAITFORSINGLEOBJECTEX);
    call.hObject = (uint64_t)hObject;
    call.Callback = (uint64_t)Callback;
    call.Context = (uint64_t)Context;
    call.dwMilliseconds = (uint64_t)dwMilliseconds;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_RegisterWaitForSingleObjectEx(struct qemu_syscall *call)
{
    struct qemu_RegisterWaitForSingleObjectEx *c = (struct qemu_RegisterWaitForSingleObjectEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RegisterWaitForSingleObjectEx(QEMU_G2H(c->hObject), QEMU_G2H(c->Callback), QEMU_G2H(c->Context), c->dwMilliseconds, c->dwFlags);
}

#endif

struct qemu_UnregisterWait
{
    struct qemu_syscall super;
    uint64_t WaitHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnregisterWait(HANDLE WaitHandle)
{
    struct qemu_UnregisterWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERWAIT);
    call.WaitHandle = (uint64_t)WaitHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterWait(struct qemu_syscall *call)
{
    struct qemu_UnregisterWait *c = (struct qemu_UnregisterWait *)call;
    struct qemu_ntdll_wait_work_item *item;

    WINE_TRACE("\n");
    item = QEMU_G2H(c->WaitHandle);

    c->super.iret = UnregisterWait(item ? item->host_handle : NULL);
    HeapFree(GetProcessHeap(), 0, item);
}

#endif

struct qemu_UnregisterWaitEx
{
    struct qemu_syscall super;
    uint64_t WaitHandle;
    uint64_t CompletionEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnregisterWaitEx(HANDLE WaitHandle, HANDLE CompletionEvent)
{
    struct qemu_UnregisterWaitEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERWAITEX);
    call.WaitHandle = (uint64_t)WaitHandle;
    call.CompletionEvent = (uint64_t)CompletionEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterWaitEx(struct qemu_syscall *call)
{
    struct qemu_UnregisterWaitEx *c = (struct qemu_UnregisterWaitEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnregisterWaitEx(QEMU_G2H(c->WaitHandle), QEMU_G2H(c->CompletionEvent));
}

#endif

struct qemu_SignalObjectAndWait
{
    struct qemu_syscall super;
    uint64_t hObjectToSignal;
    uint64_t hObjectToWaitOn;
    uint64_t dwMilliseconds;
    uint64_t bAlertable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SignalObjectAndWait(HANDLE hObjectToSignal, HANDLE hObjectToWaitOn, DWORD dwMilliseconds, BOOL bAlertable)
{
    struct qemu_SignalObjectAndWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SIGNALOBJECTANDWAIT);
    call.hObjectToSignal = (uint64_t)hObjectToSignal;
    call.hObjectToWaitOn = (uint64_t)hObjectToWaitOn;
    call.dwMilliseconds = (uint64_t)dwMilliseconds;
    call.bAlertable = (uint64_t)bAlertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SignalObjectAndWait(struct qemu_syscall *call)
{
    struct qemu_SignalObjectAndWait *c = (struct qemu_SignalObjectAndWait *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SignalObjectAndWait(QEMU_G2H(c->hObjectToSignal), QEMU_G2H(c->hObjectToWaitOn), c->dwMilliseconds, c->bAlertable);
}

#endif

/* Critical section already destroy the hope of 32 bit emulation in a 64 bit emulator
 * and 64 bit libs. The structure is allocated by the guest app and contains pointers,
 * so it will have a different size in 32 and 64 bit.
 *
 * There are a few options around this for this particular data structure. The best seems
 * to reimplement them ourselves instead of calling Wine and using the LockSemaphore
 * entry to store a pointer or handle to a Win64 sync object. Because we need to limit
 * the address space anyway we can fit this pointer into the 32 bit HANDLE. */
struct qemu_InitializeCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI InitializeCriticalSection(CRITICAL_SECTION *crit)
{
    struct qemu_InitializeCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZECRITICALSECTION);
    call.crit = (uint64_t)crit;

    qemu_syscall(&call.super);
}

#else

void qemu_InitializeCriticalSection(struct qemu_syscall *call)
{
    struct qemu_InitializeCriticalSection *c = (struct qemu_InitializeCriticalSection *)call;
    WINE_TRACE("\n");
    InitializeCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_InitializeCriticalSectionAndSpinCount
{
    struct qemu_syscall super;
    uint64_t crit;
    uint64_t spincount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION *crit, DWORD spincount)
{
    struct qemu_InitializeCriticalSectionAndSpinCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZECRITICALSECTIONANDSPINCOUNT);
    call.crit = (uint64_t)crit;
    call.spincount = spincount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeCriticalSectionAndSpinCount(struct qemu_syscall *call)
{
    struct qemu_InitializeCriticalSectionAndSpinCount *c = (struct qemu_InitializeCriticalSectionAndSpinCount *)call;
    WINE_TRACE("\n");
    c->super.iret = InitializeCriticalSectionAndSpinCount(QEMU_G2H(c->crit), c->spincount);
}

#endif

#ifdef QEMU_DLL_GUEST
/* For now the main purpose of this one is to force this library to import ntdll for the RVA Forwards. */
NTSYSAPI NTSTATUS WINAPI RtlInitializeCriticalSectionEx(RTL_CRITICAL_SECTION *,ULONG,ULONG);
WINBASEAPI BOOL WINAPI InitializeCriticalSectionEx(CRITICAL_SECTION *section, DWORD spincount, DWORD flags)
{
    return !RtlInitializeCriticalSectionEx(section, spincount, flags);
}
#endif

struct qemu_MakeCriticalSectionGlobal
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI MakeCriticalSectionGlobal(CRITICAL_SECTION *crit)
{
    struct qemu_MakeCriticalSectionGlobal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAKECRITICALSECTIONGLOBAL);
    call.crit = (uint64_t)crit;

    qemu_syscall(&call.super);
}

#else

void qemu_MakeCriticalSectionGlobal(struct qemu_syscall *call)
{
    struct qemu_MakeCriticalSectionGlobal *c = (struct qemu_MakeCriticalSectionGlobal *)call;
    WINE_FIXME("Unverified!\n");
    MakeCriticalSectionGlobal(QEMU_G2H(c->crit));
}

#endif

struct qemu_ReinitializeCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ReinitializeCriticalSection(CRITICAL_SECTION *crit)
{
    struct qemu_ReinitializeCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REINITIALIZECRITICALSECTION);
    call.crit = (uint64_t)crit;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add ReinitializeCriticalSection to Wine headers? */
extern void WINAPI ReinitializeCriticalSection(CRITICAL_SECTION *crit);
void qemu_ReinitializeCriticalSection(struct qemu_syscall *call)
{
    struct qemu_ReinitializeCriticalSection *c = (struct qemu_ReinitializeCriticalSection *)call;
    WINE_FIXME("Unverified!\n");
    ReinitializeCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_UninitializeCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI UninitializeCriticalSection(CRITICAL_SECTION *crit)
{
    struct qemu_UninitializeCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNINITIALIZECRITICALSECTION);
    call.crit = (uint64_t)crit;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add UninitializeCriticalSection to Wine headers? */
extern void WINAPI UninitializeCriticalSection(CRITICAL_SECTION *crit);
void qemu_UninitializeCriticalSection(struct qemu_syscall *call)
{
    struct qemu_UninitializeCriticalSection *c = (struct qemu_UninitializeCriticalSection *)call;
    WINE_FIXME("Unverified!\n");
    UninitializeCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_CreateEventA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t manual_reset;
    uint64_t initial_state;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateEventA(SECURITY_ATTRIBUTES *sa, BOOL manual_reset, BOOL initial_state, LPCSTR name)
{
    struct qemu_CreateEventA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTA);
    call.sa = (uint64_t)sa;
    call.manual_reset = (uint64_t)manual_reset;
    call.initial_state = (uint64_t)initial_state;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateEventA(struct qemu_syscall *call)
{
    struct qemu_CreateEventA *c = (struct qemu_CreateEventA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateEventA(QEMU_G2H(c->sa), c->manual_reset, c->initial_state, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateEventW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t manual_reset;
    uint64_t initial_state;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateEventW(SECURITY_ATTRIBUTES *sa, BOOL manual_reset, BOOL initial_state, LPCWSTR name)
{
    struct qemu_CreateEventW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTW);
    call.sa = (uint64_t)sa;
    call.manual_reset = (uint64_t)manual_reset;
    call.initial_state = (uint64_t)initial_state;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateEventW(struct qemu_syscall *call)
{
    struct qemu_CreateEventW *c = (struct qemu_CreateEventW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateEventW(QEMU_G2H(c->sa), c->manual_reset, c->initial_state, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateEventExA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateEventExA(SECURITY_ATTRIBUTES *sa, LPCSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateEventExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTEXA);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateEventExA(struct qemu_syscall *call)
{
    struct qemu_CreateEventExA *c = (struct qemu_CreateEventExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateEventExA(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_CreateEventExW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateEventExW(SECURITY_ATTRIBUTES *sa, LPCWSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateEventExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTEXW);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateEventExW(struct qemu_syscall *call)
{
    struct qemu_CreateEventExW *c = (struct qemu_CreateEventExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateEventExW(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_OpenEventA
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenEventA(DWORD access, BOOL inherit, LPCSTR name)
{
    struct qemu_OpenEventA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENEVENTA);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenEventA(struct qemu_syscall *call)
{
    struct qemu_OpenEventA *c = (struct qemu_OpenEventA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenEventA(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenEventW
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenEventW(DWORD access, BOOL inherit, LPCWSTR name)
{
    struct qemu_OpenEventW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENEVENTW);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenEventW(struct qemu_syscall *call)
{
    struct qemu_OpenEventW *c = (struct qemu_OpenEventW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenEventW(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_PulseEvent
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PulseEvent(HANDLE handle)
{
    struct qemu_PulseEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PULSEEVENT);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PulseEvent(struct qemu_syscall *call)
{
    struct qemu_PulseEvent *c = (struct qemu_PulseEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PulseEvent(QEMU_G2H(c->handle));
}

#endif

struct qemu_SetEvent
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetEvent(HANDLE handle)
{
    struct qemu_SetEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETEVENT);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEvent(struct qemu_syscall *call)
{
    struct qemu_SetEvent *c = (struct qemu_SetEvent *)call;
    WINE_TRACE("\n");
    c->super.iret = SetEvent((HANDLE)c->handle);
}

#endif

struct qemu_ResetEvent
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ResetEvent(HANDLE handle)
{
    struct qemu_ResetEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESETEVENT);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResetEvent(struct qemu_syscall *call)
{
    struct qemu_ResetEvent *c = (struct qemu_ResetEvent *)call;
    WINE_TRACE("\n");
    c->super.iret = ResetEvent((HANDLE)c->handle);
}

#endif

struct qemu_CreateMutexA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t owner;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMutexA(SECURITY_ATTRIBUTES *sa, BOOL owner, LPCSTR name)
{
    struct qemu_CreateMutexA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMUTEXA);
    call.sa = (uint64_t)sa;
    call.owner = (uint64_t)owner;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMutexA(struct qemu_syscall *call)
{
    struct qemu_CreateMutexA *c = (struct qemu_CreateMutexA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMutexA(QEMU_G2H(c->sa), c->owner, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateMutexW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t owner;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMutexW(SECURITY_ATTRIBUTES *sa, BOOL owner, LPCWSTR name)
{
    struct qemu_CreateMutexW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMUTEXW);
    call.sa = (uint64_t)sa;
    call.owner = (uint64_t)owner;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMutexW(struct qemu_syscall *call)
{
    struct qemu_CreateMutexW *c = (struct qemu_CreateMutexW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMutexW(QEMU_G2H(c->sa), c->owner, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateMutexExA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMutexExA(SECURITY_ATTRIBUTES *sa, LPCSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateMutexExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMUTEXEXA);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMutexExA(struct qemu_syscall *call)
{
    struct qemu_CreateMutexExA *c = (struct qemu_CreateMutexExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMutexExA(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_CreateMutexExW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMutexExW(SECURITY_ATTRIBUTES *sa, LPCWSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateMutexExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMUTEXEXW);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMutexExW(struct qemu_syscall *call)
{
    struct qemu_CreateMutexExW *c = (struct qemu_CreateMutexExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMutexExW(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_OpenMutexA
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenMutexA(DWORD access, BOOL inherit, LPCSTR name)
{
    struct qemu_OpenMutexA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENMUTEXA);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenMutexA(struct qemu_syscall *call)
{
    struct qemu_OpenMutexA *c = (struct qemu_OpenMutexA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenMutexA(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenMutexW
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenMutexW(DWORD access, BOOL inherit, LPCWSTR name)
{
    struct qemu_OpenMutexW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENMUTEXW);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenMutexW(struct qemu_syscall *call)
{
    struct qemu_OpenMutexW *c = (struct qemu_OpenMutexW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenMutexW(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_ReleaseMutex
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReleaseMutex(HANDLE handle)
{
    struct qemu_ReleaseMutex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RELEASEMUTEX);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReleaseMutex(struct qemu_syscall *call)
{
    struct qemu_ReleaseMutex *c = (struct qemu_ReleaseMutex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReleaseMutex(QEMU_G2H(c->handle));
}

#endif

struct qemu_CreateSemaphoreA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t initial;
    uint64_t max;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateSemaphoreA(SECURITY_ATTRIBUTES *sa, LONG initial, LONG max, LPCSTR name)
{
    struct qemu_CreateSemaphoreA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESEMAPHOREA);
    call.sa = (uint64_t)sa;
    call.initial = (uint64_t)initial;
    call.max = (uint64_t)max;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateSemaphoreA(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreA *c = (struct qemu_CreateSemaphoreA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateSemaphoreA(QEMU_G2H(c->sa), c->initial, c->max, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateSemaphoreW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t initial;
    uint64_t max;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateSemaphoreW(SECURITY_ATTRIBUTES *sa, LONG initial, LONG max, LPCWSTR name)
{
    struct qemu_CreateSemaphoreW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESEMAPHOREW);
    call.sa = (uint64_t)sa;
    call.initial = initial;
    call.max = max;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateSemaphoreW(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreW *c = (struct qemu_CreateSemaphoreW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateSemaphoreW(QEMU_G2H(c->sa), c->initial, c->max, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateSemaphoreExA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t initial;
    uint64_t max;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateSemaphoreExA(SECURITY_ATTRIBUTES *sa, LONG initial, LONG max, LPCSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateSemaphoreExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESEMAPHOREEXA);
    call.sa = (uint64_t)sa;
    call.initial = (uint64_t)initial;
    call.max = (uint64_t)max;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateSemaphoreExA(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreExA *c = (struct qemu_CreateSemaphoreExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateSemaphoreExA(QEMU_G2H(c->sa), c->initial, c->max, QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_CreateSemaphoreExW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t initial;
    uint64_t max;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateSemaphoreExW(SECURITY_ATTRIBUTES *sa, LONG initial, LONG max, LPCWSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateSemaphoreExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESEMAPHOREEXW);
    call.sa = (uint64_t)sa;
    call.initial = (uint64_t)initial;
    call.max = (uint64_t)max;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateSemaphoreExW(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreExW *c = (struct qemu_CreateSemaphoreExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateSemaphoreExW(QEMU_G2H(c->sa), c->initial, c->max, QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_OpenSemaphoreA
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenSemaphoreA(DWORD access, BOOL inherit, LPCSTR name)
{
    struct qemu_OpenSemaphoreA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENSEMAPHOREA);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenSemaphoreA(struct qemu_syscall *call)
{
    struct qemu_OpenSemaphoreA *c = (struct qemu_OpenSemaphoreA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenSemaphoreA(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenSemaphoreW
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenSemaphoreW(DWORD access, BOOL inherit, LPCWSTR name)
{
    struct qemu_OpenSemaphoreW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENSEMAPHOREW);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenSemaphoreW(struct qemu_syscall *call)
{
    struct qemu_OpenSemaphoreW *c = (struct qemu_OpenSemaphoreW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenSemaphoreW(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_ReleaseSemaphore
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t previous;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReleaseSemaphore(HANDLE handle, LONG count, LONG *previous)
{
    struct qemu_ReleaseSemaphore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RELEASESEMAPHORE);
    call.handle = (uint64_t)handle;
    call.count = count;
    call.previous = (uint64_t)previous;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReleaseSemaphore(struct qemu_syscall *call)
{
    struct qemu_ReleaseSemaphore *c = (struct qemu_ReleaseSemaphore *)call;
    WINE_TRACE("\n");
    c->super.iret = ReleaseSemaphore(QEMU_G2H(c->handle), c->count, QEMU_G2H(c->previous));
}

#endif

struct qemu_CreateJobObjectW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateJobObjectW(LPSECURITY_ATTRIBUTES sa, LPCWSTR name)
{
    struct qemu_CreateJobObjectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEJOBOBJECTW);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateJobObjectW(struct qemu_syscall *call)
{
    struct qemu_CreateJobObjectW *c = (struct qemu_CreateJobObjectW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateJobObjectW(QEMU_G2H(c->sa), QEMU_G2H(c->name));
}

#endif

struct qemu_CreateJobObjectA
{
    struct qemu_syscall super;
    uint64_t attr;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateJobObjectA(LPSECURITY_ATTRIBUTES attr, LPCSTR name)
{
    struct qemu_CreateJobObjectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEJOBOBJECTA);
    call.attr = (uint64_t)attr;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateJobObjectA(struct qemu_syscall *call)
{
    struct qemu_CreateJobObjectA *c = (struct qemu_CreateJobObjectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateJobObjectA(QEMU_G2H(c->attr), QEMU_G2H(c->name));
}

#endif

struct qemu_OpenJobObjectW
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenJobObjectW(DWORD access, BOOL inherit, LPCWSTR name)
{
    struct qemu_OpenJobObjectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENJOBOBJECTW);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenJobObjectW(struct qemu_syscall *call)
{
    struct qemu_OpenJobObjectW *c = (struct qemu_OpenJobObjectW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenJobObjectW(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenJobObjectA
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenJobObjectA(DWORD access, BOOL inherit, LPCSTR name)
{
    struct qemu_OpenJobObjectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENJOBOBJECTA);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenJobObjectA(struct qemu_syscall *call)
{
    struct qemu_OpenJobObjectA *c = (struct qemu_OpenJobObjectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenJobObjectA(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_TerminateJobObject
{
    struct qemu_syscall super;
    uint64_t job;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TerminateJobObject(HANDLE job, UINT exit_code)
{
    struct qemu_TerminateJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TERMINATEJOBOBJECT);
    call.job = (uint64_t)job;
    call.exit_code = (uint64_t)exit_code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TerminateJobObject(struct qemu_syscall *call)
{
    struct qemu_TerminateJobObject *c = (struct qemu_TerminateJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TerminateJobObject(QEMU_G2H(c->job), c->exit_code);
}

#endif

struct qemu_QueryInformationJobObject
{
    struct qemu_syscall super;
    uint64_t job;
    uint64_t class;
    uint64_t info;
    uint64_t len;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryInformationJobObject(HANDLE job, JOBOBJECTINFOCLASS class, LPVOID info, DWORD len, DWORD *ret_len)
{
    struct qemu_QueryInformationJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYINFORMATIONJOBOBJECT);
    call.job = (uint64_t)job;
    call.class = (uint64_t)class;
    call.info = (uint64_t)info;
    call.len = (uint64_t)len;
    call.ret_len = (uint64_t)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryInformationJobObject(struct qemu_syscall *call)
{
    struct qemu_QueryInformationJobObject *c = (struct qemu_QueryInformationJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryInformationJobObject(QEMU_G2H(c->job), c->class, QEMU_G2H(c->info), c->len, QEMU_G2H(c->ret_len));
}

#endif

struct qemu_SetInformationJobObject
{
    struct qemu_syscall super;
    uint64_t job;
    uint64_t class;
    uint64_t info;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetInformationJobObject(HANDLE job, JOBOBJECTINFOCLASS class, LPVOID info, DWORD len)
{
    struct qemu_SetInformationJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETINFORMATIONJOBOBJECT);
    call.job = (uint64_t)job;
    call.class = (uint64_t)class;
    call.info = (uint64_t)info;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetInformationJobObject(struct qemu_syscall *call)
{
    struct qemu_SetInformationJobObject *c = (struct qemu_SetInformationJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetInformationJobObject(QEMU_G2H(c->job), c->class, QEMU_G2H(c->info), c->len);
}

#endif

struct qemu_AssignProcessToJobObject
{
    struct qemu_syscall super;
    uint64_t job;
    uint64_t process;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AssignProcessToJobObject(HANDLE job, HANDLE process)
{
    struct qemu_AssignProcessToJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSIGNPROCESSTOJOBOBJECT);
    call.job = (uint64_t)job;
    call.process = (uint64_t)process;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssignProcessToJobObject(struct qemu_syscall *call)
{
    struct qemu_AssignProcessToJobObject *c = (struct qemu_AssignProcessToJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssignProcessToJobObject(QEMU_G2H(c->job), QEMU_G2H(c->process));
}

#endif

struct qemu_IsProcessInJob
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t job;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsProcessInJob(HANDLE process, HANDLE job, PBOOL result)
{
    struct qemu_IsProcessInJob call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPROCESSINJOB);
    call.process = (uint64_t)process;
    call.job = (uint64_t)job;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsProcessInJob(struct qemu_syscall *call)
{
    struct qemu_IsProcessInJob *c = (struct qemu_IsProcessInJob *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsProcessInJob(QEMU_G2H(c->process), QEMU_G2H(c->job), QEMU_G2H(c->result));
}

#endif

struct qemu_CreateWaitableTimerA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t manual;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateWaitableTimerA(SECURITY_ATTRIBUTES *sa, BOOL manual, LPCSTR name)
{
    struct qemu_CreateWaitableTimerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWAITABLETIMERA);
    call.sa = (uint64_t)sa;
    call.manual = manual;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateWaitableTimerA(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerA *c = (struct qemu_CreateWaitableTimerA *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateWaitableTimerA(QEMU_G2H(c->sa), c->manual, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateWaitableTimerW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t manual;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateWaitableTimerW(SECURITY_ATTRIBUTES *sa, BOOL manual, LPCWSTR name)
{
    struct qemu_CreateWaitableTimerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWAITABLETIMERW);
    call.sa = (uint64_t)sa;
    call.manual = (uint64_t)manual;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateWaitableTimerW(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerW *c = (struct qemu_CreateWaitableTimerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateWaitableTimerW(QEMU_G2H(c->sa), c->manual, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateWaitableTimerExA
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateWaitableTimerExA(SECURITY_ATTRIBUTES *sa, LPCSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateWaitableTimerExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWAITABLETIMEREXA);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateWaitableTimerExA(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerExA *c = (struct qemu_CreateWaitableTimerExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateWaitableTimerExA(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_CreateWaitableTimerExW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t name;
    uint64_t flags;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateWaitableTimerExW(SECURITY_ATTRIBUTES *sa, LPCWSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateWaitableTimerExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWAITABLETIMEREXW);
    call.sa = (uint64_t)sa;
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.access = (uint64_t)access;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateWaitableTimerExW(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerExW *c = (struct qemu_CreateWaitableTimerExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateWaitableTimerExW(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
}

#endif

struct qemu_OpenWaitableTimerA
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenWaitableTimerA(DWORD access, BOOL inherit, LPCSTR name)
{
    struct qemu_OpenWaitableTimerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENWAITABLETIMERA);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenWaitableTimerA(struct qemu_syscall *call)
{
    struct qemu_OpenWaitableTimerA *c = (struct qemu_OpenWaitableTimerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenWaitableTimerA(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_OpenWaitableTimerW
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenWaitableTimerW(DWORD access, BOOL inherit, LPCWSTR name)
{
    struct qemu_OpenWaitableTimerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENWAITABLETIMERW);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenWaitableTimerW(struct qemu_syscall *call)
{
    struct qemu_OpenWaitableTimerW *c = (struct qemu_OpenWaitableTimerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenWaitableTimerW(c->access, c->inherit, QEMU_G2H(c->name));
}

#endif

struct qemu_SetWaitableTimer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t when;
    uint64_t period;
    uint64_t callback;
    uint64_t arg;
    uint64_t resume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetWaitableTimer(HANDLE handle, const LARGE_INTEGER *when, LONG period, PTIMERAPCROUTINE callback, LPVOID arg, BOOL resume)
{
    struct qemu_SetWaitableTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWAITABLETIMER);
    call.handle = (uint64_t)handle;
    call.when = (uint64_t)when;
    call.period = period;
    call.callback = (uint64_t)callback;
    call.arg = (uint64_t)arg;
    call.resume = resume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWaitableTimer(struct qemu_syscall *call)
{
    struct qemu_SetWaitableTimer *c = (struct qemu_SetWaitableTimer *)call;
    WINE_TRACE("\n");
    if (c->callback)
        WINE_FIXME("Wrap non-NULL callback.\n");
    c->super.iret = SetWaitableTimer(QEMU_G2H(c->handle), QEMU_G2H(c->when), c->period, QEMU_G2H(c->callback), QEMU_G2H(c->arg), c->resume);
}

#endif

struct qemu_SetWaitableTimerEx
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t when;
    uint64_t period;
    uint64_t callback;
    uint64_t arg;
    uint64_t context;
    uint64_t tolerabledelay;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetWaitableTimerEx(HANDLE handle, const LARGE_INTEGER *when, LONG period, PTIMERAPCROUTINE callback, LPVOID arg, REASON_CONTEXT *context, ULONG tolerabledelay)
{
    struct qemu_SetWaitableTimerEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWAITABLETIMEREX);
    call.handle = (uint64_t)handle;
    call.when = (uint64_t)when;
    call.period = (uint64_t)period;
    call.callback = (uint64_t)callback;
    call.arg = (uint64_t)arg;
    call.context = (uint64_t)context;
    call.tolerabledelay = (uint64_t)tolerabledelay;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWaitableTimerEx(struct qemu_syscall *call)
{
    struct qemu_SetWaitableTimerEx *c = (struct qemu_SetWaitableTimerEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWaitableTimerEx(QEMU_G2H(c->handle), QEMU_G2H(c->when), c->period, QEMU_G2H(c->callback), QEMU_G2H(c->arg), QEMU_G2H(c->context), c->tolerabledelay);
}

#endif

struct qemu_CancelWaitableTimer
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CancelWaitableTimer(HANDLE handle)
{
    struct qemu_CancelWaitableTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELWAITABLETIMER);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelWaitableTimer(struct qemu_syscall *call)
{
    struct qemu_CancelWaitableTimer *c = (struct qemu_CancelWaitableTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelWaitableTimer(QEMU_G2H(c->handle));
}

#endif

struct qemu_CreateTimerQueue
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateTimerQueue(void)
{
    struct qemu_CreateTimerQueue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETIMERQUEUE);

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateTimerQueue(struct qemu_syscall *call)
{
    struct qemu_CreateTimerQueue *c = (struct qemu_CreateTimerQueue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateTimerQueue();
}

#endif

struct qemu_DeleteTimerQueueEx
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
    uint64_t CompletionEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteTimerQueueEx(HANDLE TimerQueue, HANDLE CompletionEvent)
{
    struct qemu_DeleteTimerQueueEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETETIMERQUEUEEX);
    call.TimerQueue = (uint64_t)TimerQueue;
    call.CompletionEvent = (uint64_t)CompletionEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteTimerQueueEx(struct qemu_syscall *call)
{
    struct qemu_DeleteTimerQueueEx *c = (struct qemu_DeleteTimerQueueEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteTimerQueueEx(QEMU_G2H(c->TimerQueue), QEMU_G2H(c->CompletionEvent));
}

#endif

struct qemu_DeleteTimerQueue
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteTimerQueue(HANDLE TimerQueue)
{
    struct qemu_DeleteTimerQueue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETETIMERQUEUE);
    call.TimerQueue = (uint64_t)TimerQueue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteTimerQueue(struct qemu_syscall *call)
{
    struct qemu_DeleteTimerQueue *c = (struct qemu_DeleteTimerQueue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteTimerQueue(QEMU_G2H(c->TimerQueue));
}

#endif

struct qemu_CreateTimerQueueTimer
{
    struct qemu_syscall super;
    uint64_t phNewTimer;
    uint64_t TimerQueue;
    uint64_t Callback;
    uint64_t Parameter;
    uint64_t DueTime;
    uint64_t Period;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateTimerQueueTimer(PHANDLE phNewTimer, HANDLE TimerQueue, WAITORTIMERCALLBACK Callback, PVOID Parameter, DWORD DueTime, DWORD Period, ULONG Flags)
{
    struct qemu_CreateTimerQueueTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETIMERQUEUETIMER);
    call.phNewTimer = (uint64_t)phNewTimer;
    call.TimerQueue = (uint64_t)TimerQueue;
    call.Callback = (uint64_t)Callback;
    call.Parameter = (uint64_t)Parameter;
    call.DueTime = (uint64_t)DueTime;
    call.Period = (uint64_t)Period;
    call.Flags = (uint64_t)Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_CreateTimerQueueTimer *c = (struct qemu_CreateTimerQueueTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateTimerQueueTimer(QEMU_G2H(c->phNewTimer), QEMU_G2H(c->TimerQueue), QEMU_G2H(c->Callback), QEMU_G2H(c->Parameter), c->DueTime, c->Period, c->Flags);
}

#endif

struct qemu_ChangeTimerQueueTimer
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
    uint64_t Timer;
    uint64_t DueTime;
    uint64_t Period;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChangeTimerQueueTimer(HANDLE TimerQueue, HANDLE Timer, ULONG DueTime, ULONG Period)
{
    struct qemu_ChangeTimerQueueTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGETIMERQUEUETIMER);
    call.TimerQueue = (uint64_t)TimerQueue;
    call.Timer = (uint64_t)Timer;
    call.DueTime = (uint64_t)DueTime;
    call.Period = (uint64_t)Period;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_ChangeTimerQueueTimer *c = (struct qemu_ChangeTimerQueueTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeTimerQueueTimer(QEMU_G2H(c->TimerQueue), QEMU_G2H(c->Timer), c->DueTime, c->Period);
}

#endif

struct qemu_CancelTimerQueueTimer
{
    struct qemu_syscall super;
    uint64_t queue;
    uint64_t timer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CancelTimerQueueTimer(HANDLE queue, HANDLE timer)
{
    struct qemu_CancelTimerQueueTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELTIMERQUEUETIMER);
    call.queue = (uint64_t)queue;
    call.timer = (uint64_t)timer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_CancelTimerQueueTimer *c = (struct qemu_CancelTimerQueueTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelTimerQueueTimer(QEMU_G2H(c->queue), QEMU_G2H(c->timer));
}

#endif

struct qemu_DeleteTimerQueueTimer
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
    uint64_t Timer;
    uint64_t CompletionEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteTimerQueueTimer(HANDLE TimerQueue, HANDLE Timer, HANDLE CompletionEvent)
{
    struct qemu_DeleteTimerQueueTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETETIMERQUEUETIMER);
    call.TimerQueue = (uint64_t)TimerQueue;
    call.Timer = (uint64_t)Timer;
    call.CompletionEvent = (uint64_t)CompletionEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_DeleteTimerQueueTimer *c = (struct qemu_DeleteTimerQueueTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteTimerQueueTimer(QEMU_G2H(c->TimerQueue), QEMU_G2H(c->Timer), QEMU_G2H(c->CompletionEvent));
}

#endif

struct qemu_CreateNamedPipeA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t dwOpenMode;
    uint64_t dwPipeMode;
    uint64_t nMaxInstances;
    uint64_t nOutBufferSize;
    uint64_t nInBufferSize;
    uint64_t nDefaultTimeOut;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateNamedPipeA(LPCSTR name, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES attr)
{
    struct qemu_CreateNamedPipeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATENAMEDPIPEA);
    call.name = (uint64_t)name;
    call.dwOpenMode = (uint64_t)dwOpenMode;
    call.dwPipeMode = (uint64_t)dwPipeMode;
    call.nMaxInstances = (uint64_t)nMaxInstances;
    call.nOutBufferSize = (uint64_t)nOutBufferSize;
    call.nInBufferSize = (uint64_t)nInBufferSize;
    call.nDefaultTimeOut = (uint64_t)nDefaultTimeOut;
    call.attr = (uint64_t)attr;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateNamedPipeA(struct qemu_syscall *call)
{
    struct qemu_CreateNamedPipeA *c = (struct qemu_CreateNamedPipeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateNamedPipeA(QEMU_G2H(c->name), c->dwOpenMode, c->dwPipeMode, c->nMaxInstances, c->nOutBufferSize, c->nInBufferSize, c->nDefaultTimeOut, QEMU_G2H(c->attr));
}

#endif

struct qemu_CreateNamedPipeW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t dwOpenMode;
    uint64_t dwPipeMode;
    uint64_t nMaxInstances;
    uint64_t nOutBufferSize;
    uint64_t nInBufferSize;
    uint64_t nDefaultTimeOut;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateNamedPipeW(LPCWSTR name, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateNamedPipeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATENAMEDPIPEW);
    call.name = (uint64_t)name;
    call.dwOpenMode = (uint64_t)dwOpenMode;
    call.dwPipeMode = (uint64_t)dwPipeMode;
    call.nMaxInstances = (uint64_t)nMaxInstances;
    call.nOutBufferSize = (uint64_t)nOutBufferSize;
    call.nInBufferSize = (uint64_t)nInBufferSize;
    call.nDefaultTimeOut = (uint64_t)nDefaultTimeOut;
    call.sa = (uint64_t)sa;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateNamedPipeW(struct qemu_syscall *call)
{
    struct qemu_CreateNamedPipeW *c = (struct qemu_CreateNamedPipeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateNamedPipeW(QEMU_G2H(c->name), c->dwOpenMode, c->dwPipeMode, c->nMaxInstances, c->nOutBufferSize, c->nInBufferSize, c->nDefaultTimeOut, QEMU_G2H(c->sa));
}

#endif

struct qemu_PeekNamedPipe
{
    struct qemu_syscall super;
    uint64_t hPipe;
    uint64_t lpvBuffer;
    uint64_t cbBuffer;
    uint64_t lpcbRead;
    uint64_t lpcbAvail;
    uint64_t lpcbMessage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PeekNamedPipe(HANDLE hPipe, LPVOID lpvBuffer, DWORD cbBuffer, LPDWORD lpcbRead, LPDWORD lpcbAvail, LPDWORD lpcbMessage)
{
    struct qemu_PeekNamedPipe call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PEEKNAMEDPIPE);
    call.hPipe = (uint64_t)hPipe;
    call.lpvBuffer = (uint64_t)lpvBuffer;
    call.cbBuffer = (uint64_t)cbBuffer;
    call.lpcbRead = (uint64_t)lpcbRead;
    call.lpcbAvail = (uint64_t)lpcbAvail;
    call.lpcbMessage = (uint64_t)lpcbMessage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekNamedPipe(struct qemu_syscall *call)
{
    struct qemu_PeekNamedPipe *c = (struct qemu_PeekNamedPipe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PeekNamedPipe(QEMU_G2H(c->hPipe), QEMU_G2H(c->lpvBuffer), c->cbBuffer, QEMU_G2H(c->lpcbRead), QEMU_G2H(c->lpcbAvail), QEMU_G2H(c->lpcbMessage));
}

#endif

struct qemu_WaitNamedPipeA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t nTimeOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WaitNamedPipeA (LPCSTR name, DWORD nTimeOut)
{
    struct qemu_WaitNamedPipeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITNAMEDPIPEA);
    call.name = (uint64_t)name;
    call.nTimeOut = (uint64_t)nTimeOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitNamedPipeA(struct qemu_syscall *call)
{
    struct qemu_WaitNamedPipeA *c = (struct qemu_WaitNamedPipeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WaitNamedPipeA(QEMU_G2H(c->name), c->nTimeOut);
}

#endif

struct qemu_WaitNamedPipeW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t nTimeOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WaitNamedPipeW (LPCWSTR name, DWORD nTimeOut)
{
    struct qemu_WaitNamedPipeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITNAMEDPIPEW);
    call.name = (uint64_t)name;
    call.nTimeOut = (uint64_t)nTimeOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitNamedPipeW(struct qemu_syscall *call)
{
    struct qemu_WaitNamedPipeW *c = (struct qemu_WaitNamedPipeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WaitNamedPipeW(QEMU_G2H(c->name), c->nTimeOut);
}

#endif

struct qemu_ConnectNamedPipe
{
    struct qemu_syscall super;
    uint64_t hPipe;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConnectNamedPipe(HANDLE hPipe, LPOVERLAPPED overlapped)
{
    struct qemu_ConnectNamedPipe call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONNECTNAMEDPIPE);
    call.hPipe = (uint64_t)hPipe;
    call.overlapped = (uint64_t)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConnectNamedPipe(struct qemu_syscall *call)
{
    struct qemu_ConnectNamedPipe *c = (struct qemu_ConnectNamedPipe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConnectNamedPipe(QEMU_G2H(c->hPipe), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_DisconnectNamedPipe
{
    struct qemu_syscall super;
    uint64_t hPipe;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DisconnectNamedPipe(HANDLE hPipe)
{
    struct qemu_DisconnectNamedPipe call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DISCONNECTNAMEDPIPE);
    call.hPipe = (uint64_t)hPipe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DisconnectNamedPipe(struct qemu_syscall *call)
{
    struct qemu_DisconnectNamedPipe *c = (struct qemu_DisconnectNamedPipe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DisconnectNamedPipe(QEMU_G2H(c->hPipe));
}

#endif

struct qemu_TransactNamedPipe
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t write_buf;
    uint64_t write_size;
    uint64_t read_buf;
    uint64_t read_size;
    uint64_t bytes_read;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TransactNamedPipe(HANDLE handle, LPVOID write_buf, DWORD write_size, LPVOID read_buf, DWORD read_size, LPDWORD bytes_read, LPOVERLAPPED overlapped)
{
    struct qemu_TransactNamedPipe call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSACTNAMEDPIPE);
    call.handle = (uint64_t)handle;
    call.write_buf = (uint64_t)write_buf;
    call.write_size = (uint64_t)write_size;
    call.read_buf = (uint64_t)read_buf;
    call.read_size = (uint64_t)read_size;
    call.bytes_read = (uint64_t)bytes_read;
    call.overlapped = (uint64_t)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TransactNamedPipe(struct qemu_syscall *call)
{
    struct qemu_TransactNamedPipe *c = (struct qemu_TransactNamedPipe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TransactNamedPipe(QEMU_G2H(c->handle), QEMU_G2H(c->write_buf), c->write_size, QEMU_G2H(c->read_buf), c->read_size, QEMU_G2H(c->bytes_read), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_GetNamedPipeInfo
{
    struct qemu_syscall super;
    uint64_t hNamedPipe;
    uint64_t lpFlags;
    uint64_t lpOutputBufferSize;
    uint64_t lpInputBufferSize;
    uint64_t lpMaxInstances;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNamedPipeInfo(HANDLE hNamedPipe, LPDWORD lpFlags, LPDWORD lpOutputBufferSize, LPDWORD lpInputBufferSize, LPDWORD lpMaxInstances)
{
    struct qemu_GetNamedPipeInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDPIPEINFO);
    call.hNamedPipe = (uint64_t)hNamedPipe;
    call.lpFlags = (uint64_t)lpFlags;
    call.lpOutputBufferSize = (uint64_t)lpOutputBufferSize;
    call.lpInputBufferSize = (uint64_t)lpInputBufferSize;
    call.lpMaxInstances = (uint64_t)lpMaxInstances;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedPipeInfo(struct qemu_syscall *call)
{
    struct qemu_GetNamedPipeInfo *c = (struct qemu_GetNamedPipeInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedPipeInfo(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpFlags), QEMU_G2H(c->lpOutputBufferSize), QEMU_G2H(c->lpInputBufferSize), QEMU_G2H(c->lpMaxInstances));
}

#endif

struct qemu_GetNamedPipeHandleStateA
{
    struct qemu_syscall super;
    uint64_t hNamedPipe;
    uint64_t lpState;
    uint64_t lpCurInstances;
    uint64_t lpMaxCollectionCount;
    uint64_t lpCollectDataTimeout;
    uint64_t lpUsername;
    uint64_t nUsernameMaxSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNamedPipeHandleStateA(HANDLE hNamedPipe, LPDWORD lpState, LPDWORD lpCurInstances, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout, LPSTR lpUsername, DWORD nUsernameMaxSize)
{
    struct qemu_GetNamedPipeHandleStateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDPIPEHANDLESTATEA);
    call.hNamedPipe = (uint64_t)hNamedPipe;
    call.lpState = (uint64_t)lpState;
    call.lpCurInstances = (uint64_t)lpCurInstances;
    call.lpMaxCollectionCount = (uint64_t)lpMaxCollectionCount;
    call.lpCollectDataTimeout = (uint64_t)lpCollectDataTimeout;
    call.lpUsername = (uint64_t)lpUsername;
    call.nUsernameMaxSize = (uint64_t)nUsernameMaxSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedPipeHandleStateA(struct qemu_syscall *call)
{
    struct qemu_GetNamedPipeHandleStateA *c = (struct qemu_GetNamedPipeHandleStateA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedPipeHandleStateA(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpState), QEMU_G2H(c->lpCurInstances), QEMU_G2H(c->lpMaxCollectionCount), QEMU_G2H(c->lpCollectDataTimeout), QEMU_G2H(c->lpUsername), c->nUsernameMaxSize);
}

#endif

struct qemu_GetNamedPipeHandleStateW
{
    struct qemu_syscall super;
    uint64_t hNamedPipe;
    uint64_t lpState;
    uint64_t lpCurInstances;
    uint64_t lpMaxCollectionCount;
    uint64_t lpCollectDataTimeout;
    uint64_t lpUsername;
    uint64_t nUsernameMaxSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNamedPipeHandleStateW(HANDLE hNamedPipe, LPDWORD lpState, LPDWORD lpCurInstances, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout, LPWSTR lpUsername, DWORD nUsernameMaxSize)
{
    struct qemu_GetNamedPipeHandleStateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDPIPEHANDLESTATEW);
    call.hNamedPipe = (uint64_t)hNamedPipe;
    call.lpState = (uint64_t)lpState;
    call.lpCurInstances = (uint64_t)lpCurInstances;
    call.lpMaxCollectionCount = (uint64_t)lpMaxCollectionCount;
    call.lpCollectDataTimeout = (uint64_t)lpCollectDataTimeout;
    call.lpUsername = (uint64_t)lpUsername;
    call.nUsernameMaxSize = (uint64_t)nUsernameMaxSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedPipeHandleStateW(struct qemu_syscall *call)
{
    struct qemu_GetNamedPipeHandleStateW *c = (struct qemu_GetNamedPipeHandleStateW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedPipeHandleStateW(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpState), QEMU_G2H(c->lpCurInstances), QEMU_G2H(c->lpMaxCollectionCount), QEMU_G2H(c->lpCollectDataTimeout), QEMU_G2H(c->lpUsername), c->nUsernameMaxSize);
}

#endif

struct qemu_SetNamedPipeHandleState
{
    struct qemu_syscall super;
    uint64_t hNamedPipe;
    uint64_t lpMode;
    uint64_t lpMaxCollectionCount;
    uint64_t lpCollectDataTimeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetNamedPipeHandleState(HANDLE hNamedPipe, LPDWORD lpMode, LPDWORD lpMaxCollectionCount, LPDWORD lpCollectDataTimeout)
{
    struct qemu_SetNamedPipeHandleState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETNAMEDPIPEHANDLESTATE);
    call.hNamedPipe = (uint64_t)hNamedPipe;
    call.lpMode = (uint64_t)lpMode;
    call.lpMaxCollectionCount = (uint64_t)lpMaxCollectionCount;
    call.lpCollectDataTimeout = (uint64_t)lpCollectDataTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetNamedPipeHandleState(struct qemu_syscall *call)
{
    struct qemu_SetNamedPipeHandleState *c = (struct qemu_SetNamedPipeHandleState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetNamedPipeHandleState(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpMode), QEMU_G2H(c->lpMaxCollectionCount), QEMU_G2H(c->lpCollectDataTimeout));
}

#endif

struct qemu_CallNamedPipeA
{
    struct qemu_syscall super;
    uint64_t lpNamedPipeName;
    uint64_t lpInput;
    uint64_t dwInputSize;
    uint64_t lpOutput;
    uint64_t dwOutputSize;
    uint64_t lpBytesRead;
    uint64_t nTimeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CallNamedPipeA(LPCSTR lpNamedPipeName, LPVOID lpInput, DWORD dwInputSize, LPVOID lpOutput, DWORD dwOutputSize, LPDWORD lpBytesRead, DWORD nTimeout)
{
    struct qemu_CallNamedPipeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLNAMEDPIPEA);
    call.lpNamedPipeName = (uint64_t)lpNamedPipeName;
    call.lpInput = (uint64_t)lpInput;
    call.dwInputSize = (uint64_t)dwInputSize;
    call.lpOutput = (uint64_t)lpOutput;
    call.dwOutputSize = (uint64_t)dwOutputSize;
    call.lpBytesRead = (uint64_t)lpBytesRead;
    call.nTimeout = (uint64_t)nTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallNamedPipeA(struct qemu_syscall *call)
{
    struct qemu_CallNamedPipeA *c = (struct qemu_CallNamedPipeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallNamedPipeA(QEMU_G2H(c->lpNamedPipeName), QEMU_G2H(c->lpInput), c->dwInputSize, QEMU_G2H(c->lpOutput), c->dwOutputSize, QEMU_G2H(c->lpBytesRead), c->nTimeout);
}

#endif

struct qemu_CallNamedPipeW
{
    struct qemu_syscall super;
    uint64_t lpNamedPipeName;
    uint64_t lpInput;
    uint64_t lpInputSize;
    uint64_t lpOutput;
    uint64_t lpOutputSize;
    uint64_t lpBytesRead;
    uint64_t nTimeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CallNamedPipeW(LPCWSTR lpNamedPipeName, LPVOID lpInput, DWORD lpInputSize, LPVOID lpOutput, DWORD lpOutputSize, LPDWORD lpBytesRead, DWORD nTimeout)
{
    struct qemu_CallNamedPipeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLNAMEDPIPEW);
    call.lpNamedPipeName = (uint64_t)lpNamedPipeName;
    call.lpInput = (uint64_t)lpInput;
    call.lpInputSize = (uint64_t)lpInputSize;
    call.lpOutput = (uint64_t)lpOutput;
    call.lpOutputSize = (uint64_t)lpOutputSize;
    call.lpBytesRead = (uint64_t)lpBytesRead;
    call.nTimeout = (uint64_t)nTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallNamedPipeW(struct qemu_syscall *call)
{
    struct qemu_CallNamedPipeW *c = (struct qemu_CallNamedPipeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallNamedPipeW(QEMU_G2H(c->lpNamedPipeName), QEMU_G2H(c->lpInput), c->lpInputSize, QEMU_G2H(c->lpOutput), c->lpOutputSize, QEMU_G2H(c->lpBytesRead), c->nTimeout);
}

#endif

struct qemu_CreatePipe
{
    struct qemu_syscall super;
    uint64_t hReadPipe;
    uint64_t hWritePipe;
    uint64_t sa;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreatePipe(PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES sa, DWORD size)
{
    struct qemu_CreatePipe call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPIPE);
    call.hReadPipe = (uint64_t)hReadPipe;
    call.hWritePipe = (uint64_t)hWritePipe;
    call.sa = (uint64_t)sa;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreatePipe(struct qemu_syscall *call)
{
    struct qemu_CreatePipe *c = (struct qemu_CreatePipe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreatePipe(QEMU_G2H(c->hReadPipe), QEMU_G2H(c->hWritePipe), QEMU_G2H(c->sa), c->size);
}

#endif

struct qemu_CreateMailslotA
{
    struct qemu_syscall super;
    uint64_t lpName;
    uint64_t nMaxMessageSize;
    uint64_t lReadTimeout;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMailslotA(LPCSTR lpName, DWORD nMaxMessageSize, DWORD lReadTimeout, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateMailslotA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMAILSLOTA);
    call.lpName = (uint64_t)lpName;
    call.nMaxMessageSize = (uint64_t)nMaxMessageSize;
    call.lReadTimeout = (uint64_t)lReadTimeout;
    call.sa = (uint64_t)sa;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMailslotA(struct qemu_syscall *call)
{
    struct qemu_CreateMailslotA *c = (struct qemu_CreateMailslotA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMailslotA(QEMU_G2H(c->lpName), c->nMaxMessageSize, c->lReadTimeout, QEMU_G2H(c->sa));
}

#endif

struct qemu_CreateMailslotW
{
    struct qemu_syscall super;
    uint64_t lpName;
    uint64_t nMaxMessageSize;
    uint64_t lReadTimeout;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMailslotW(LPCWSTR lpName, DWORD nMaxMessageSize, DWORD lReadTimeout, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateMailslotW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMAILSLOTW);
    call.lpName = (uint64_t)lpName;
    call.nMaxMessageSize = (uint64_t)nMaxMessageSize;
    call.lReadTimeout = (uint64_t)lReadTimeout;
    call.sa = (uint64_t)sa;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMailslotW(struct qemu_syscall *call)
{
    struct qemu_CreateMailslotW *c = (struct qemu_CreateMailslotW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMailslotW(QEMU_G2H(c->lpName), c->nMaxMessageSize, c->lReadTimeout, QEMU_G2H(c->sa));
}

#endif

struct qemu_GetMailslotInfo
{
    struct qemu_syscall super;
    uint64_t hMailslot;
    uint64_t lpMaxMessageSize;
    uint64_t lpNextSize;
    uint64_t lpMessageCount;
    uint64_t lpReadTimeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetMailslotInfo(HANDLE hMailslot, LPDWORD lpMaxMessageSize, LPDWORD lpNextSize, LPDWORD lpMessageCount, LPDWORD lpReadTimeout)
{
    struct qemu_GetMailslotInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMAILSLOTINFO);
    call.hMailslot = (uint64_t)hMailslot;
    call.lpMaxMessageSize = (uint64_t)lpMaxMessageSize;
    call.lpNextSize = (uint64_t)lpNextSize;
    call.lpMessageCount = (uint64_t)lpMessageCount;
    call.lpReadTimeout = (uint64_t)lpReadTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMailslotInfo(struct qemu_syscall *call)
{
    struct qemu_GetMailslotInfo *c = (struct qemu_GetMailslotInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMailslotInfo(QEMU_G2H(c->hMailslot), QEMU_G2H(c->lpMaxMessageSize), QEMU_G2H(c->lpNextSize), QEMU_G2H(c->lpMessageCount), QEMU_G2H(c->lpReadTimeout));
}

#endif

struct qemu_SetMailslotInfo
{
    struct qemu_syscall super;
    uint64_t hMailslot;
    uint64_t dwReadTimeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetMailslotInfo(HANDLE hMailslot, DWORD dwReadTimeout)
{
    struct qemu_SetMailslotInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMAILSLOTINFO);
    call.hMailslot = (uint64_t)hMailslot;
    call.dwReadTimeout = (uint64_t)dwReadTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMailslotInfo(struct qemu_syscall *call)
{
    struct qemu_SetMailslotInfo *c = (struct qemu_SetMailslotInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMailslotInfo(QEMU_G2H(c->hMailslot), c->dwReadTimeout);
}

#endif

struct qemu_CreateIoCompletionPort
{
    struct qemu_syscall super;
    uint64_t hFileHandle;
    uint64_t hExistingCompletionPort;
    uint64_t CompletionKey;
    uint64_t dwNumberOfConcurrentThreads;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateIoCompletionPort(HANDLE hFileHandle, HANDLE hExistingCompletionPort, ULONG_PTR CompletionKey, DWORD dwNumberOfConcurrentThreads)
{
    struct qemu_CreateIoCompletionPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEIOCOMPLETIONPORT);
    call.hFileHandle = (uint64_t)hFileHandle;
    call.hExistingCompletionPort = (uint64_t)hExistingCompletionPort;
    call.CompletionKey = CompletionKey;
    call.dwNumberOfConcurrentThreads = dwNumberOfConcurrentThreads;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateIoCompletionPort(struct qemu_syscall *call)
{
    struct qemu_CreateIoCompletionPort *c = (struct qemu_CreateIoCompletionPort *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateIoCompletionPort(QEMU_G2H(c->hFileHandle), QEMU_G2H(c->hExistingCompletionPort),
            c->CompletionKey, c->dwNumberOfConcurrentThreads);
}

#endif

struct qemu_GetQueuedCompletionStatus
{
    struct qemu_syscall super;
    uint64_t CompletionPort;
    uint64_t lpNumberOfBytesTransferred;
    uint64_t pCompletionKey;
    uint64_t lpOverlapped;
    uint64_t dwMilliseconds;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetQueuedCompletionStatus(HANDLE CompletionPort, LPDWORD lpNumberOfBytesTransferred,
        PULONG_PTR pCompletionKey, LPOVERLAPPED *lpOverlapped, DWORD dwMilliseconds)
{
    struct qemu_GetQueuedCompletionStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETQUEUEDCOMPLETIONSTATUS);
    call.CompletionPort = (uint64_t)CompletionPort;
    call.lpNumberOfBytesTransferred = (uint64_t)lpNumberOfBytesTransferred;
    call.pCompletionKey = (uint64_t)pCompletionKey;
    call.lpOverlapped = (uint64_t)lpOverlapped;
    call.dwMilliseconds = dwMilliseconds;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetQueuedCompletionStatus(struct qemu_syscall *call)
{
    struct qemu_GetQueuedCompletionStatus *c = (struct qemu_GetQueuedCompletionStatus *)call;
    WINE_TRACE("\n");
    c->super.iret = GetQueuedCompletionStatus(QEMU_G2H(c->CompletionPort), QEMU_G2H(c->lpNumberOfBytesTransferred),
            QEMU_G2H(c->pCompletionKey), QEMU_G2H(c->lpOverlapped), c->dwMilliseconds);
}

#endif

struct qemu_PostQueuedCompletionStatus
{
    struct qemu_syscall super;
    uint64_t CompletionPort;
    uint64_t dwNumberOfBytes;
    uint64_t dwCompletionKey;
    uint64_t lpOverlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PostQueuedCompletionStatus(HANDLE CompletionPort, DWORD dwNumberOfBytes, ULONG_PTR dwCompletionKey, LPOVERLAPPED lpOverlapped)
{
    struct qemu_PostQueuedCompletionStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POSTQUEUEDCOMPLETIONSTATUS);
    call.CompletionPort = (uint64_t)CompletionPort;
    call.dwNumberOfBytes = (uint64_t)dwNumberOfBytes;
    call.dwCompletionKey = (uint64_t)dwCompletionKey;
    call.lpOverlapped = (uint64_t)lpOverlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostQueuedCompletionStatus(struct qemu_syscall *call)
{
    struct qemu_PostQueuedCompletionStatus *c = (struct qemu_PostQueuedCompletionStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PostQueuedCompletionStatus(QEMU_G2H(c->CompletionPort), c->dwNumberOfBytes, c->dwCompletionKey, QEMU_G2H(c->lpOverlapped));
}

#endif

struct qemu_BindIoCompletionCallback
{
    struct qemu_syscall super;
    uint64_t FileHandle;
    uint64_t Function;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BindIoCompletionCallback(HANDLE FileHandle, LPOVERLAPPED_COMPLETION_ROUTINE Function, ULONG Flags)
{
    struct qemu_BindIoCompletionCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BINDIOCOMPLETIONCALLBACK);
    call.FileHandle = (uint64_t)FileHandle;
    call.Function = (uint64_t)Function;
    call.Flags = (uint64_t)Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BindIoCompletionCallback(struct qemu_syscall *call)
{
    struct qemu_BindIoCompletionCallback *c = (struct qemu_BindIoCompletionCallback *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BindIoCompletionCallback(QEMU_G2H(c->FileHandle), QEMU_G2H(c->Function), c->Flags);
}

#endif

struct qemu_CreateMemoryResourceNotification
{
    struct qemu_syscall super;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateMemoryResourceNotification(MEMORY_RESOURCE_NOTIFICATION_TYPE type)
{
    struct qemu_CreateMemoryResourceNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMEMORYRESOURCENOTIFICATION);
    call.type = (uint64_t)type;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateMemoryResourceNotification(struct qemu_syscall *call)
{
    struct qemu_CreateMemoryResourceNotification *c = (struct qemu_CreateMemoryResourceNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMemoryResourceNotification(c->type);
}

#endif

struct qemu_QueryMemoryResourceNotification
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryMemoryResourceNotification(HANDLE handle, PBOOL state)
{
    struct qemu_QueryMemoryResourceNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYMEMORYRESOURCENOTIFICATION);
    call.handle = (uint64_t)handle;
    call.state = (uint64_t)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryMemoryResourceNotification(struct qemu_syscall *call)
{
    struct qemu_QueryMemoryResourceNotification *c = (struct qemu_QueryMemoryResourceNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryMemoryResourceNotification(QEMU_G2H(c->handle), QEMU_G2H(c->state));
}

#endif

struct qemu_InitOnceBeginInitialize
{
    struct qemu_syscall super;
    uint64_t once;
    uint64_t flags;
    uint64_t pending;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitOnceBeginInitialize(INIT_ONCE *once, DWORD flags, BOOL *pending, void **context)
{
    struct qemu_InitOnceBeginInitialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITONCEBEGININITIALIZE);
    call.once = (uint64_t)once;
    call.flags = (uint64_t)flags;
    call.pending = (uint64_t)pending;
    call.context = (uint64_t)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitOnceBeginInitialize(struct qemu_syscall *call)
{
    struct qemu_InitOnceBeginInitialize *c = (struct qemu_InitOnceBeginInitialize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitOnceBeginInitialize(QEMU_G2H(c->once), c->flags, QEMU_G2H(c->pending), QEMU_G2H(c->context));
}

#endif

struct qemu_InitOnceComplete
{
    struct qemu_syscall super;
    uint64_t once;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitOnceComplete(INIT_ONCE *once, DWORD flags, void *context)
{
    struct qemu_InitOnceComplete call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITONCECOMPLETE);
    call.once = (uint64_t)once;
    call.flags = (uint64_t)flags;
    call.context = (uint64_t)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitOnceComplete(struct qemu_syscall *call)
{
    struct qemu_InitOnceComplete *c = (struct qemu_InitOnceComplete *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitOnceComplete(QEMU_G2H(c->once), c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_InitOnceExecuteOnce
{
    struct qemu_syscall super;
    uint64_t once;
    uint64_t func;
    uint64_t param;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitOnceExecuteOnce(INIT_ONCE *once, PINIT_ONCE_FN func, void *param, void **context)
{
    struct qemu_InitOnceExecuteOnce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITONCEEXECUTEONCE);
    call.once = (uint64_t)once;
    call.func = (uint64_t)func;
    call.param = (uint64_t)param;
    call.context = (uint64_t)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitOnceExecuteOnce(struct qemu_syscall *call)
{
    struct qemu_InitOnceExecuteOnce *c = (struct qemu_InitOnceExecuteOnce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitOnceExecuteOnce(QEMU_G2H(c->once), QEMU_G2H(c->func), QEMU_G2H(c->param), QEMU_G2H(c->context));
}

#endif

struct qemu_SleepConditionVariableCS
{
    struct qemu_syscall super;
    uint64_t variable;
    uint64_t crit;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SleepConditionVariableCS(CONDITION_VARIABLE *variable, CRITICAL_SECTION *crit, DWORD timeout)
{
    struct qemu_SleepConditionVariableCS call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SLEEPCONDITIONVARIABLECS);
    call.variable = (uint64_t)variable;
    call.crit = (uint64_t)crit;
    call.timeout = (uint64_t)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SleepConditionVariableCS(struct qemu_syscall *call)
{
    struct qemu_SleepConditionVariableCS *c = (struct qemu_SleepConditionVariableCS *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SleepConditionVariableCS(QEMU_G2H(c->variable), QEMU_G2H(c->crit), c->timeout);
}

#endif

struct qemu_SleepConditionVariableSRW
{
    struct qemu_syscall super;
    uint64_t variable;
    uint64_t lock;
    uint64_t timeout;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SleepConditionVariableSRW(RTL_CONDITION_VARIABLE *variable, RTL_SRWLOCK *lock, DWORD timeout, ULONG flags)
{
    struct qemu_SleepConditionVariableSRW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SLEEPCONDITIONVARIABLESRW);
    call.variable = (uint64_t)variable;
    call.lock = (uint64_t)lock;
    call.timeout = (uint64_t)timeout;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SleepConditionVariableSRW(struct qemu_syscall *call)
{
    struct qemu_SleepConditionVariableSRW *c = (struct qemu_SleepConditionVariableSRW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SleepConditionVariableSRW(QEMU_G2H(c->variable), QEMU_G2H(c->lock), c->timeout, c->flags);
}

#endif

