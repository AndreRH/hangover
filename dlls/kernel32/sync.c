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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"
#include "ntdll_wrapper.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

#ifdef QEMU_DLL_GUEST
static inline PLARGE_INTEGER get_nt_timeout( PLARGE_INTEGER pTime, DWORD timeout )
{
    if (timeout == INFINITE) return NULL;
    pTime->QuadPart = (ULONGLONG)timeout * -10000;
    return pTime;
}

/* For now the main purpose of this one is to force this library to import ntdll for the RVA Forwards. */
extern NTSTATUS WINAPI RtlInitializeCriticalSectionEx(RTL_CRITICAL_SECTION *crit, ULONG spincount, ULONG flags);
extern void WINAPI RtlRaiseStatus(NTSTATUS status);
BOOL WINAPI qemu_InitializeCriticalSectionEx(CRITICAL_SECTION *section, DWORD spincount, DWORD flags)
{
    NTSTATUS ret = RtlInitializeCriticalSectionEx( section, spincount, flags );
    if (ret) RtlRaiseStatus( ret );
    return !ret;
}
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
    call.timeout = (ULONG_PTR)timeout;

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
    call.handle = guest_HANDLE_g2h(handle);
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
    call.handle = guest_HANDLE_g2h(handle);
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
    call.handles = (ULONG_PTR)handles;
    call.wait_all = wait_all;
    call.timeout = timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForMultipleObjects(struct qemu_syscall *call)
{
    struct qemu_WaitForMultipleObjects *c = (struct qemu_WaitForMultipleObjects *)call;
    HANDLE stack[10], *handles = stack;
    qemu_handle *handle32;
    unsigned int i;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    c->super.iret = WaitForMultipleObjects(c->count, QEMU_G2H(c->handles), c->wait_all, c->timeout);
    return;
#endif

    handle32 = QEMU_G2H(c->handles);
    if (c->count > sizeof(stack) / sizeof(*stack))
        handles = HeapAlloc(GetProcessHeap(), 0, c->count * sizeof(*handles));

    for (i = 0; i < c->count; ++i)
        handles[i] = HANDLE_g2h(handle32[i]);

    c->super.iret = WaitForMultipleObjects(c->count, handles, c->wait_all, c->timeout);

    if (handles != stack)
        HeapFree(GetProcessHeap(), 0, handles);
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
    call.count = (ULONG_PTR)count;
    call.handles = (ULONG_PTR)handles;
    call.wait_all = (ULONG_PTR)wait_all;
    call.timeout = (ULONG_PTR)timeout;
    call.alertable = (ULONG_PTR)alertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForMultipleObjectsEx(struct qemu_syscall *call)
{
    struct qemu_WaitForMultipleObjectsEx *c = (struct qemu_WaitForMultipleObjectsEx *)call;
    HANDLE stack[10], *handles = stack;
    qemu_handle *handle32;
    unsigned int i;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    c->super.iret = WaitForMultipleObjectsEx(c->count, QEMU_G2H(c->handles), c->wait_all, c->timeout, c->alertable);
    return;
#endif

    handle32 = QEMU_G2H(c->handles);
    if (c->count > sizeof(stack) / sizeof(*stack))
        handles = HeapAlloc(GetProcessHeap(), 0, c->count * sizeof(*handles));

    for (i = 0; i < c->count; ++i)
        handles[i] = HANDLE_g2h(handle32[i]);

    c->super.iret = WaitForMultipleObjectsEx(c->count, handles, c->wait_all, c->timeout, c->alertable);

    if (handles != stack)
        HeapFree(GetProcessHeap(), 0, handles);
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

static void __fastcall host_wait_callback(struct qemu_wait_callback *data)
{
    WAITORTIMERCALLBACK cb = (WAITORTIMERCALLBACK)(ULONG_PTR)data->func;
    cb((void *)(ULONG_PTR)data->context, data->timeout);
}

WINBASEAPI BOOL WINAPI RegisterWaitForSingleObject(PHANDLE phNewWaitObject, HANDLE hObject, WAITORTIMERCALLBACK Callback, PVOID Context, ULONG dwMilliseconds, ULONG dwFlags)
{
    struct qemu_RegisterWaitForSingleObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERWAITFORSINGLEOBJECT);
    call.phNewWaitObject = (ULONG_PTR)phNewWaitObject;
    call.hObject = guest_HANDLE_g2h(hObject);
    call.Callback = (ULONG_PTR)Callback;
    call.Context = (ULONG_PTR)Context;
    call.dwMilliseconds = dwMilliseconds;
    call.dwFlags = dwFlags;
    call.wrapper = (ULONG_PTR)host_wait_callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void CALLBACK guest_wait_callback(void *p, BOOLEAN timeout)
{
    struct qemu_ntdll_wait_work_item *item = p;
    struct qemu_wait_callback call;

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, %u).\n", (unsigned long)item->guest_cb,
            (unsigned long)item->context, timeout);

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
    call.hObject = guest_HANDLE_g2h(hObject);
    call.Callback = (ULONG_PTR)Callback;
    call.Context = (ULONG_PTR)Context;
    call.dwMilliseconds = (ULONG_PTR)dwMilliseconds;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterWaitForSingleObjectEx(struct qemu_syscall *call)
{
    struct qemu_RegisterWaitForSingleObjectEx *c = (struct qemu_RegisterWaitForSingleObjectEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterWaitForSingleObjectEx(QEMU_G2H(c->hObject), QEMU_G2H(c->Callback), QEMU_G2H(c->Context), c->dwMilliseconds, c->dwFlags);
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
    call.WaitHandle = guest_HANDLE_g2h(WaitHandle);

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
    call.WaitHandle = guest_HANDLE_g2h(WaitHandle);
    call.CompletionEvent = guest_HANDLE_g2h(CompletionEvent);

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
    call.hObjectToSignal = guest_HANDLE_g2h(hObjectToSignal);
    call.hObjectToWaitOn = guest_HANDLE_g2h(hObjectToWaitOn);
    call.dwMilliseconds = (ULONG_PTR)dwMilliseconds;
    call.bAlertable = (ULONG_PTR)bAlertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SignalObjectAndWait(struct qemu_syscall *call)
{
    struct qemu_SignalObjectAndWait *c = (struct qemu_SignalObjectAndWait *)call;
    WINE_TRACE("\n");
    c->super.iret = SignalObjectAndWait(QEMU_G2H(c->hObjectToSignal), QEMU_G2H(c->hObjectToWaitOn), c->dwMilliseconds, c->bAlertable);
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI InitializeCriticalSection(CRITICAL_SECTION *crit)
{
    qemu_InitializeCriticalSectionEx( crit, 0, 0 );
}

WINBASEAPI BOOL WINAPI InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION *crit, DWORD spincount)
{
    return qemu_InitializeCriticalSectionEx( crit, spincount, 0 );
}

NTSTATUS WINAPI RtlDeleteCriticalSection( RTL_CRITICAL_SECTION *crit );
WINBASEAPI void WINAPI UninitializeCriticalSection(CRITICAL_SECTION *crit)
{
    RtlDeleteCriticalSection( crit );
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
    call.crit = (ULONG_PTR)crit;

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
    call.crit = (ULONG_PTR)crit;

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
    call.sa = (ULONG_PTR)sa;
    call.manual_reset = manual_reset;
    call.initial_state = initial_state;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateEventA(struct qemu_syscall *call)
{
    struct qemu_CreateEventA *c = (struct qemu_CreateEventA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateEventA(sa, c->manual_reset, c->initial_state, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.manual_reset = (ULONG_PTR)manual_reset;
    call.initial_state = (ULONG_PTR)initial_state;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateEventW(struct qemu_syscall *call)
{
    struct qemu_CreateEventW *c = (struct qemu_CreateEventW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateEventW(sa, c->manual_reset, c->initial_state, QEMU_G2H(c->name));
}

#endif

struct qemu_CreateEventEx
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
    struct qemu_CreateEventEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTEXA);
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

WINBASEAPI HANDLE WINAPI CreateEventExW(SECURITY_ATTRIBUTES *sa, LPCWSTR name, DWORD flags, DWORD access)
{
    struct qemu_CreateEventEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTEXW);
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateEventEx(struct qemu_syscall *call)
{
    struct qemu_CreateEventEx *c = (struct qemu_CreateEventEx *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_CREATEEVENTEXW))
        c->super.iret = (ULONG_PTR)CreateEventExW(sa, QEMU_G2H(c->name), c->flags, c->access);
    else
        c->super.iret = (ULONG_PTR)CreateEventExA(sa, QEMU_G2H(c->name), c->flags, c->access);
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenEventA(struct qemu_syscall *call)
{
    struct qemu_OpenEventA *c = (struct qemu_OpenEventA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenEventA(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenEventW(struct qemu_syscall *call)
{
    struct qemu_OpenEventW *c = (struct qemu_OpenEventW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenEventW(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.handle = guest_HANDLE_g2h(handle);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PulseEvent(struct qemu_syscall *call)
{
    struct qemu_PulseEvent *c = (struct qemu_PulseEvent *)call;
    WINE_TRACE("\n");
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
    call.handle = guest_HANDLE_g2h(handle);

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
    call.handle = guest_HANDLE_g2h(handle);

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
    call.sa = (ULONG_PTR)sa;
    call.owner = (ULONG_PTR)owner;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMutexA(struct qemu_syscall *call)
{
    struct qemu_CreateMutexA *c = (struct qemu_CreateMutexA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateMutexA(sa, c->owner, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.owner = (ULONG_PTR)owner;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMutexW(struct qemu_syscall *call)
{
    struct qemu_CreateMutexW *c = (struct qemu_CreateMutexW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateMutexW(sa, c->owner, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMutexExA(struct qemu_syscall *call)
{
    struct qemu_CreateMutexExA *c = (struct qemu_CreateMutexExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMutexExA(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
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
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMutexExW(struct qemu_syscall *call)
{
    struct qemu_CreateMutexExW *c = (struct qemu_CreateMutexExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMutexExW(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenMutexA(struct qemu_syscall *call)
{
    struct qemu_OpenMutexA *c = (struct qemu_OpenMutexA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenMutexA(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenMutexW(struct qemu_syscall *call)
{
    struct qemu_OpenMutexW *c = (struct qemu_OpenMutexW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenMutexW(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.handle = guest_HANDLE_g2h(handle);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReleaseMutex(struct qemu_syscall *call)
{
    struct qemu_ReleaseMutex *c = (struct qemu_ReleaseMutex *)call;
    WINE_TRACE("\n");
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
    call.sa = (ULONG_PTR)sa;
    call.initial = (ULONG_PTR)initial;
    call.max = (ULONG_PTR)max;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateSemaphoreA(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreA *c = (struct qemu_CreateSemaphoreA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateSemaphoreA(sa, c->initial, c->max, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.initial = initial;
    call.max = max;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateSemaphoreW(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreW *c = (struct qemu_CreateSemaphoreW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateSemaphoreW(sa, c->initial, c->max, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.initial = (ULONG_PTR)initial;
    call.max = (ULONG_PTR)max;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateSemaphoreExA(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreExA *c = (struct qemu_CreateSemaphoreExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateSemaphoreExA(QEMU_G2H(c->sa), c->initial, c->max, QEMU_G2H(c->name), c->flags, c->access);
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
    call.sa = (ULONG_PTR)sa;
    call.initial = (ULONG_PTR)initial;
    call.max = (ULONG_PTR)max;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateSemaphoreExW(struct qemu_syscall *call)
{
    struct qemu_CreateSemaphoreExW *c = (struct qemu_CreateSemaphoreExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateSemaphoreExW(QEMU_G2H(c->sa), c->initial, c->max, QEMU_G2H(c->name), c->flags, c->access);
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenSemaphoreA(struct qemu_syscall *call)
{
    struct qemu_OpenSemaphoreA *c = (struct qemu_OpenSemaphoreA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenSemaphoreA(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenSemaphoreW(struct qemu_syscall *call)
{
    struct qemu_OpenSemaphoreW *c = (struct qemu_OpenSemaphoreW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenSemaphoreW(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.handle = guest_HANDLE_g2h(handle);
    call.count = count;
    call.previous = (ULONG_PTR)previous;

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

WINBASEAPI HANDLE WINAPI CreateJobObjectW(SECURITY_ATTRIBUTES *sa, LPCWSTR name)
{
    struct qemu_CreateJobObjectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEJOBOBJECTW);
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateJobObjectW(struct qemu_syscall *call)
{
    struct qemu_CreateJobObjectW *c = (struct qemu_CreateJobObjectW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateJobObjectW(sa, QEMU_G2H(c->name));
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
    call.attr = (ULONG_PTR)attr;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateJobObjectA(struct qemu_syscall *call)
{
    struct qemu_CreateJobObjectA *c = (struct qemu_CreateJobObjectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateJobObjectA(QEMU_G2H(c->attr), QEMU_G2H(c->name));
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenJobObjectW(struct qemu_syscall *call)
{
    struct qemu_OpenJobObjectW *c = (struct qemu_OpenJobObjectW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenJobObjectW(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenJobObjectA(struct qemu_syscall *call)
{
    struct qemu_OpenJobObjectA *c = (struct qemu_OpenJobObjectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenJobObjectA(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.job = guest_HANDLE_g2h(job);
    call.exit_code = (ULONG_PTR)exit_code;

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
    call.job = guest_HANDLE_g2h(job);
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.ret_len = (ULONG_PTR)ret_len;

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
    call.job = guest_HANDLE_g2h(job);
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetInformationJobObject(struct qemu_syscall *call)
{
    struct qemu_SetInformationJobObject *c = (struct qemu_SetInformationJobObject *)call;
    HANDLE job;
    JOBOBJECTINFOCLASS class;
    DWORD len;

    WINE_TRACE("\n");
    job = QEMU_G2H(c->job);
    class = c->class;
    len = c->len;

#if GUEST_BIT == HOST_BIT
    c->super.iret = SetInformationJobObject(job, class, QEMU_G2H(c->info), len);
    return;
#endif

    if (!c->info)
    {
        c->super.iret = SetInformationJobObject(job, class, NULL, len);
        return;
    }

    switch (c->class)
    {
        case JobObjectExtendedLimitInformation:
        {
            JOBOBJECT_EXTENDED_LIMIT_INFORMATION stack;

            WINE_TRACE("Translating JOBOBJECT_EXTENDED_LIMIT_INFORMATION.\n");

            if (len == sizeof(struct qemu_JOBOBJECT_EXTENDED_LIMIT_INFORMATION))
            {
                JOBOBJECT_EXTENDED_LIMIT_INFORMATION_g2h(&stack, QEMU_G2H(c->info));
                len = sizeof(stack);
            }
            else
            {
                len = 0;
            }

            c->super.iret = SetInformationJobObject(job, class, &stack, len);
            break;
        }
        case JobObjectBasicLimitInformation:
        {
            WINE_FIXME("Unhandled JobObjectBasicLimitInformation.\n");
            c->super.iret = SetInformationJobObject(job, class, QEMU_G2H(c->info), len);
            break;
        }
        case JobObjectAssociateCompletionPortInformation:
        {
            WINE_FIXME("Unhandled JobObjectAssociateCompletionPortInformation.\n");
            c->super.iret = SetInformationJobObject(job, class, QEMU_G2H(c->info), len);
            break;
        }
        case JobObjectBasicUIRestrictions:
        {
            WINE_FIXME("Unhandled JobObjectBasicUIRestrictions.\n");
            c->super.iret = SetInformationJobObject(job, class, QEMU_G2H(c->info), len);
            break;
        }

        default:
            WINE_FIXME("Unknown job object class %x\n", (JOBOBJECTINFOCLASS)c->class);
            c->super.iret = SetInformationJobObject(job, class, QEMU_G2H(c->info), len);
    }
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
    call.job = guest_HANDLE_g2h(job);
    call.process = guest_HANDLE_g2h(process);

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
    call.process = guest_HANDLE_g2h(process);
    call.job = guest_HANDLE_g2h(job);
    call.result = (ULONG_PTR)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsProcessInJob(struct qemu_syscall *call)
{
    struct qemu_IsProcessInJob *c = (struct qemu_IsProcessInJob *)call;
    WINE_TRACE("\n");
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
    call.sa = (ULONG_PTR)sa;
    call.manual = manual;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWaitableTimerA(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerA *c = (struct qemu_CreateWaitableTimerA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateWaitableTimerA(sa, c->manual, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.manual = (ULONG_PTR)manual;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWaitableTimerW(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerW *c = (struct qemu_CreateWaitableTimerW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateWaitableTimerW(sa, c->manual, QEMU_G2H(c->name));
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
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWaitableTimerExA(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerExA *c = (struct qemu_CreateWaitableTimerExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateWaitableTimerExA(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
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
    call.sa = (ULONG_PTR)sa;
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWaitableTimerExW(struct qemu_syscall *call)
{
    struct qemu_CreateWaitableTimerExW *c = (struct qemu_CreateWaitableTimerExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateWaitableTimerExW(QEMU_G2H(c->sa), QEMU_G2H(c->name), c->flags, c->access);
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenWaitableTimerA(struct qemu_syscall *call)
{
    struct qemu_OpenWaitableTimerA *c = (struct qemu_OpenWaitableTimerA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenWaitableTimerA(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.access = (ULONG_PTR)access;
    call.inherit = (ULONG_PTR)inherit;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenWaitableTimerW(struct qemu_syscall *call)
{
    struct qemu_OpenWaitableTimerW *c = (struct qemu_OpenWaitableTimerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenWaitableTimerW(c->access, c->inherit, QEMU_G2H(c->name));
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
    call.handle = guest_HANDLE_g2h(handle);
    call.when = (ULONG_PTR)when;
    call.period = period;
    call.callback = (ULONG_PTR)callback;
    call.arg = (ULONG_PTR)arg;
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
    call.handle = guest_HANDLE_g2h(handle);
    call.when = (ULONG_PTR)when;
    call.period = (ULONG_PTR)period;
    call.callback = (ULONG_PTR)callback;
    call.arg = (ULONG_PTR)arg;
    call.context = (ULONG_PTR)context;
    call.tolerabledelay = (ULONG_PTR)tolerabledelay;

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
    call.handle = guest_HANDLE_g2h(handle);

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

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateTimerQueue(struct qemu_syscall *call)
{
    struct qemu_CreateTimerQueue *c = (struct qemu_CreateTimerQueue *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateTimerQueue();
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
    call.TimerQueue = guest_HANDLE_g2h(TimerQueue);
    call.CompletionEvent = guest_HANDLE_g2h(CompletionEvent);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteTimerQueueEx(struct qemu_syscall *call)
{
    struct qemu_DeleteTimerQueueEx *c = (struct qemu_DeleteTimerQueueEx *)call;
    WINE_FIXME("How should I free the timer wrappers?\n");
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
    call.TimerQueue = guest_HANDLE_g2h(TimerQueue);

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
    uint64_t wrapper;
};

struct qemu_CreateTimerQueueTimer_cb
{
    uint64_t cb;
    uint64_t param;
    uint64_t timedout;
};

#ifdef QEMU_DLL_GUEST

static void __fastcall timer_guest_cb(struct qemu_CreateTimerQueueTimer_cb *data)
{
    WAITORTIMERCALLBACK cb = (WAITORTIMERCALLBACK)(ULONG_PTR)data->cb;
    cb((void *)(ULONG_PTR)data->param, data->timedout);
}

WINBASEAPI BOOL WINAPI CreateTimerQueueTimer(PHANDLE phNewTimer, HANDLE TimerQueue, WAITORTIMERCALLBACK Callback, PVOID Parameter, DWORD DueTime, DWORD Period, ULONG Flags)
{
    struct qemu_CreateTimerQueueTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETIMERQUEUETIMER);
    call.TimerQueue = guest_HANDLE_g2h(TimerQueue);
    call.Callback = (ULONG_PTR)Callback;
    call.Parameter = (ULONG_PTR)Parameter;
    call.DueTime = (ULONG_PTR)DueTime;
    call.Period = (ULONG_PTR)Period;
    call.Flags = (ULONG_PTR)Flags;
    call.wrapper = (ULONG_PTR)timer_guest_cb;

    qemu_syscall(&call.super);

    if (call.super.iret)
        *phNewTimer = (HANDLE)(ULONG_PTR)call.phNewTimer;

    return call.super.iret;
}

#else

/* FIXME: Considering the effort we need to properly free the structure and that we can't properly handle
 * DeleteTimerQueueEx without also tracking the timer queue it might be better to allocate never released
 * wrappers for callback functions similar to how we handle WNDPROCs. */
struct queue_timer
{
    HANDLE host_timer;
    uint64_t guest_param, guest_cb, wrapper;
    HANDLE wait_event, signal_event;
};

static void CALLBACK timer_host_cb(void *param, BOOLEAN timedOut)
{
    struct queue_timer *timer = param;
    struct qemu_CreateTimerQueueTimer_cb call;

    call.cb = timer->guest_cb;
    call.param = timer->guest_param;
    call.timedout = timedOut;

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, %u).\n", (unsigned long)call.cb,
            (unsigned long)call.param, timedOut);
    qemu_ops->qemu_execute(QEMU_G2H(timer->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned.\n");
}

void qemu_CreateTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_CreateTimerQueueTimer *c = (struct qemu_CreateTimerQueueTimer *)call;
    struct queue_timer *timer;
    WINE_TRACE("\n");

    timer = HeapAlloc(GetProcessHeap(), 0, sizeof(*timer));
    timer->guest_param = c->Parameter;
    timer->guest_cb = c->Callback;
    timer->wrapper = c->wrapper;
    timer->wait_event = timer->signal_event = NULL;

    c->super.iret = CreateTimerQueueTimer(&timer->host_timer, QEMU_G2H(c->TimerQueue),
            c->Callback ? timer_host_cb : NULL, timer, c->DueTime, c->Period, c->Flags);

    if (c->super.iret)
        c->phNewTimer = (ULONG_PTR)timer;
    else
        HeapFree(GetProcessHeap(), 0, timer);
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
    call.TimerQueue = guest_HANDLE_g2h(TimerQueue);
    call.Timer = guest_HANDLE_g2h(Timer);
    call.DueTime = (ULONG_PTR)DueTime;
    call.Period = (ULONG_PTR)Period;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_ChangeTimerQueueTimer *c = (struct qemu_ChangeTimerQueueTimer *)call;
    struct queue_timer *timer;
    WINE_TRACE("\n");

    timer = QEMU_G2H(c->Timer);
    c->super.iret = ChangeTimerQueueTimer(QEMU_G2H(c->TimerQueue), timer->host_timer, c->DueTime, c->Period);
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
    call.queue = guest_HANDLE_g2h(queue);
    call.timer = guest_HANDLE_g2h(timer);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_CancelTimerQueueTimer *c = (struct qemu_CancelTimerQueueTimer *)call;
    struct queue_timer *timer;
    WINE_TRACE("\n");

    timer = QEMU_G2H(c->timer);
    c->super.iret = CancelTimerQueueTimer(QEMU_G2H(c->queue), timer->host_timer);
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
    call.TimerQueue = guest_HANDLE_g2h(TimerQueue);
    call.Timer = guest_HANDLE_g2h(Timer);
    call.CompletionEvent = guest_HANDLE_g2h(CompletionEvent);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static DWORD CALLBACK delete_thread(void *data)
{
    struct queue_timer *timer = data;

    WaitForSingleObject(timer->wait_event, INFINITE);

    if (timer->signal_event)
        SetEvent(timer->signal_event);

    WINE_TRACE("Delayed destroying timer object %p (host %p).\n", timer, timer->host_timer);
    HeapFree(GetProcessHeap(), 0, timer);

    return 0;
}

void qemu_DeleteTimerQueueTimer(struct qemu_syscall *call)
{
    struct qemu_DeleteTimerQueueTimer *c = (struct qemu_DeleteTimerQueueTimer *)call;
    struct queue_timer *timer;
    HANDLE event = INVALID_HANDLE_VALUE, app_event;
    WINE_TRACE("\n");
    DWORD last_error;

    timer = QEMU_G2H(c->Timer);
    timer->signal_event = NULL;
    app_event = QEMU_G2H(c->CompletionEvent);
    if (app_event != INVALID_HANDLE_VALUE)
    {
        last_error = GetLastError();

        event = CreateEventW(NULL, 0, 0, NULL);
        timer->signal_event = app_event;
        timer->wait_event = event;

        /* CreateEventW calls SetLastError(0). */
        SetLastError(last_error);
    }

    c->super.iret = DeleteTimerQueueTimer(QEMU_G2H(c->TimerQueue), timer->host_timer, event);

    if (c->super.iret)
    {
        if (event != INVALID_HANDLE_VALUE)
        {
            CloseHandle(event);
            if (app_event)
                SetEvent(app_event);
        }
        WINE_TRACE("Destroying timer object %p (host %p).\n", timer, timer->host_timer);
        HeapFree(GetProcessHeap(), 0, timer);
    }
    else if (GetLastError() == ERROR_IO_PENDING)
    {
        /* FIXME: Consider using some threadpool API. */
        HANDLE thread;
        DWORD dw;

        WINE_TRACE("Scheduling destruction of timer object %p (host %p).\n", timer, timer->host_timer);
        thread = CreateThread(NULL, 0, delete_thread, timer, 0, &dw);
        CloseHandle(thread);

        /* Something in the above code calls SetLastError(0). */
        SetLastError(ERROR_IO_PENDING);
    }
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

WINBASEAPI HANDLE WINAPI CreateNamedPipeA(LPCSTR name, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances,
        DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES attr)
{
    struct qemu_CreateNamedPipeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATENAMEDPIPEA);
    call.name = (ULONG_PTR)name;
    call.dwOpenMode = dwOpenMode;
    call.dwPipeMode = dwPipeMode;
    call.nMaxInstances = nMaxInstances;
    call.nOutBufferSize = nOutBufferSize;
    call.nInBufferSize = nInBufferSize;
    call.nDefaultTimeOut = nDefaultTimeOut;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateNamedPipeA(struct qemu_syscall *call)
{
    struct qemu_CreateNamedPipeA *c = (struct qemu_CreateNamedPipeA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->attr);
#else
    if (c->attr)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->attr));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateNamedPipeA(QEMU_G2H(c->name), c->dwOpenMode, c->dwPipeMode, c->nMaxInstances,
            c->nOutBufferSize, c->nInBufferSize, c->nDefaultTimeOut, sa);
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
    call.name = (ULONG_PTR)name;
    call.dwOpenMode = (ULONG_PTR)dwOpenMode;
    call.dwPipeMode = (ULONG_PTR)dwPipeMode;
    call.nMaxInstances = (ULONG_PTR)nMaxInstances;
    call.nOutBufferSize = (ULONG_PTR)nOutBufferSize;
    call.nInBufferSize = (ULONG_PTR)nInBufferSize;
    call.nDefaultTimeOut = (ULONG_PTR)nDefaultTimeOut;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateNamedPipeW(struct qemu_syscall *call)
{
    struct qemu_CreateNamedPipeW *c = (struct qemu_CreateNamedPipeW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_FIXME("Unverified\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = (ULONG_PTR)CreateNamedPipeW(QEMU_G2H(c->name), c->dwOpenMode, c->dwPipeMode, c->nMaxInstances, c->nOutBufferSize, c->nInBufferSize, c->nDefaultTimeOut, sa);
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
    call.hPipe = guest_HANDLE_g2h(hPipe);
    call.lpvBuffer = (ULONG_PTR)lpvBuffer;
    call.cbBuffer = cbBuffer;
    call.lpcbRead = (ULONG_PTR)lpcbRead;
    call.lpcbAvail = (ULONG_PTR)lpcbAvail;
    call.lpcbMessage = (ULONG_PTR)lpcbMessage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekNamedPipe(struct qemu_syscall *call)
{
    struct qemu_PeekNamedPipe *c = (struct qemu_PeekNamedPipe *)call;
    WINE_TRACE("\n");
    c->super.iret = PeekNamedPipe(QEMU_G2H(c->hPipe), QEMU_G2H(c->lpvBuffer), c->cbBuffer, QEMU_G2H(c->lpcbRead),
            QEMU_G2H(c->lpcbAvail), QEMU_G2H(c->lpcbMessage));
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
    call.name = (ULONG_PTR)name;
    call.nTimeOut = nTimeOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitNamedPipeA(struct qemu_syscall *call)
{
    struct qemu_WaitNamedPipeA *c = (struct qemu_WaitNamedPipeA *)call;
    WINE_TRACE("\n");
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
    call.name = (ULONG_PTR)name;
    call.nTimeOut = (ULONG_PTR)nTimeOut;

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
    call.hPipe = guest_HANDLE_g2h(hPipe);
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConnectNamedPipe(struct qemu_syscall *call)
{
    struct qemu_ConnectNamedPipe *c = (struct qemu_ConnectNamedPipe *)call;
    struct qemu_OVERLAPPED *ov32;
    struct OVERLAPPED_data *ov_wrapper;
    HANDLE guest_event;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    c->super.iret = ConnectNamedPipe(QEMU_G2H(c->hPipe), QEMU_G2H(c->overlapped));
    return;
#endif

    ov32 = QEMU_G2H(c->overlapped);
    if (!ov32)
    {
        WINE_TRACE("Synchronous operation, easy...\n");
        c->super.iret = ConnectNamedPipe(QEMU_G2H(c->hPipe), NULL);
        return;
    }

    ov_wrapper = alloc_OVERLAPPED_data(ov32, 0, TRUE);
    guest_event = HANDLE_g2h(ov32->hEvent);

    WINE_TRACE("Async operation\n");
    c->super.iret = ConnectNamedPipe(QEMU_G2H(c->hPipe), &ov_wrapper->ov);

    OVERLAPPED_h2g(ov32, &ov_wrapper->ov);
    ov32->hEvent = (ULONG_PTR)guest_event;

    process_OVERLAPPED_data(c->super.iret, ov_wrapper);

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
    call.hPipe = guest_HANDLE_g2h(hPipe);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DisconnectNamedPipe(struct qemu_syscall *call)
{
    struct qemu_DisconnectNamedPipe *c = (struct qemu_DisconnectNamedPipe *)call;
    WINE_TRACE("\n");
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
    call.handle = guest_HANDLE_g2h(handle);
    call.write_buf = (ULONG_PTR)write_buf;
    call.write_size = (ULONG_PTR)write_size;
    call.read_buf = (ULONG_PTR)read_buf;
    call.read_size = (ULONG_PTR)read_size;
    call.bytes_read = (ULONG_PTR)bytes_read;
    call.overlapped = (ULONG_PTR)overlapped;

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
    call.hNamedPipe = guest_HANDLE_g2h(hNamedPipe);
    call.lpFlags = (ULONG_PTR)lpFlags;
    call.lpOutputBufferSize = (ULONG_PTR)lpOutputBufferSize;
    call.lpInputBufferSize = (ULONG_PTR)lpInputBufferSize;
    call.lpMaxInstances = (ULONG_PTR)lpMaxInstances;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedPipeInfo(struct qemu_syscall *call)
{
    struct qemu_GetNamedPipeInfo *c = (struct qemu_GetNamedPipeInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetNamedPipeInfo(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpFlags), QEMU_G2H(c->lpOutputBufferSize),
            QEMU_G2H(c->lpInputBufferSize), QEMU_G2H(c->lpMaxInstances));
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
    call.hNamedPipe = guest_HANDLE_g2h(hNamedPipe);
    call.lpState = (ULONG_PTR)lpState;
    call.lpCurInstances = (ULONG_PTR)lpCurInstances;
    call.lpMaxCollectionCount = (ULONG_PTR)lpMaxCollectionCount;
    call.lpCollectDataTimeout = (ULONG_PTR)lpCollectDataTimeout;
    call.lpUsername = (ULONG_PTR)lpUsername;
    call.nUsernameMaxSize = nUsernameMaxSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedPipeHandleStateA(struct qemu_syscall *call)
{
    struct qemu_GetNamedPipeHandleStateA *c = (struct qemu_GetNamedPipeHandleStateA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetNamedPipeHandleStateA(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpState), QEMU_G2H(c->lpCurInstances),
            QEMU_G2H(c->lpMaxCollectionCount), QEMU_G2H(c->lpCollectDataTimeout), QEMU_G2H(c->lpUsername),
            c->nUsernameMaxSize);
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
    call.hNamedPipe = guest_HANDLE_g2h(hNamedPipe);
    call.lpState = (ULONG_PTR)lpState;
    call.lpCurInstances = (ULONG_PTR)lpCurInstances;
    call.lpMaxCollectionCount = (ULONG_PTR)lpMaxCollectionCount;
    call.lpCollectDataTimeout = (ULONG_PTR)lpCollectDataTimeout;
    call.lpUsername = (ULONG_PTR)lpUsername;
    call.nUsernameMaxSize = (ULONG_PTR)nUsernameMaxSize;

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

WINBASEAPI BOOL WINAPI SetNamedPipeHandleState(HANDLE hNamedPipe, LPDWORD lpMode, LPDWORD lpMaxCollectionCount,
        LPDWORD lpCollectDataTimeout)
{
    struct qemu_SetNamedPipeHandleState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETNAMEDPIPEHANDLESTATE);
    call.hNamedPipe = guest_HANDLE_g2h(hNamedPipe);
    call.lpMode = (ULONG_PTR)lpMode;
    call.lpMaxCollectionCount = (ULONG_PTR)lpMaxCollectionCount;
    call.lpCollectDataTimeout = (ULONG_PTR)lpCollectDataTimeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetNamedPipeHandleState(struct qemu_syscall *call)
{
    struct qemu_SetNamedPipeHandleState *c = (struct qemu_SetNamedPipeHandleState *)call;
    WINE_TRACE("\n");
    c->super.iret = SetNamedPipeHandleState(QEMU_G2H(c->hNamedPipe), QEMU_G2H(c->lpMode),
            QEMU_G2H(c->lpMaxCollectionCount), QEMU_G2H(c->lpCollectDataTimeout));
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
    call.lpNamedPipeName = (ULONG_PTR)lpNamedPipeName;
    call.lpInput = (ULONG_PTR)lpInput;
    call.dwInputSize = (ULONG_PTR)dwInputSize;
    call.lpOutput = (ULONG_PTR)lpOutput;
    call.dwOutputSize = (ULONG_PTR)dwOutputSize;
    call.lpBytesRead = (ULONG_PTR)lpBytesRead;
    call.nTimeout = (ULONG_PTR)nTimeout;

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
    call.lpNamedPipeName = (ULONG_PTR)lpNamedPipeName;
    call.lpInput = (ULONG_PTR)lpInput;
    call.lpInputSize = (ULONG_PTR)lpInputSize;
    call.lpOutput = (ULONG_PTR)lpOutput;
    call.lpOutputSize = (ULONG_PTR)lpOutputSize;
    call.lpBytesRead = (ULONG_PTR)lpBytesRead;
    call.nTimeout = (ULONG_PTR)nTimeout;

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
    call.hReadPipe = (ULONG_PTR)hReadPipe;
    call.hWritePipe = (ULONG_PTR)hWritePipe;
    call.sa = (ULONG_PTR)sa;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreatePipe(struct qemu_syscall *call)
{
    struct qemu_CreatePipe *c = (struct qemu_CreatePipe *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = CreatePipe(QEMU_G2H(c->hReadPipe), QEMU_G2H(c->hWritePipe), sa, c->size);
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
    call.lpName = (ULONG_PTR)lpName;
    call.nMaxMessageSize = (ULONG_PTR)nMaxMessageSize;
    call.lReadTimeout = (ULONG_PTR)lReadTimeout;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMailslotA(struct qemu_syscall *call)
{
    struct qemu_CreateMailslotA *c = (struct qemu_CreateMailslotA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMailslotA(QEMU_G2H(c->lpName), c->nMaxMessageSize, c->lReadTimeout, QEMU_G2H(c->sa));
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
    call.lpName = (ULONG_PTR)lpName;
    call.nMaxMessageSize = (ULONG_PTR)nMaxMessageSize;
    call.lReadTimeout = (ULONG_PTR)lReadTimeout;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMailslotW(struct qemu_syscall *call)
{
    struct qemu_CreateMailslotW *c = (struct qemu_CreateMailslotW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMailslotW(QEMU_G2H(c->lpName), c->nMaxMessageSize, c->lReadTimeout, QEMU_G2H(c->sa));
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
    call.hMailslot = guest_HANDLE_g2h(hMailslot);
    call.lpMaxMessageSize = (ULONG_PTR)lpMaxMessageSize;
    call.lpNextSize = (ULONG_PTR)lpNextSize;
    call.lpMessageCount = (ULONG_PTR)lpMessageCount;
    call.lpReadTimeout = (ULONG_PTR)lpReadTimeout;

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
    call.hMailslot = guest_HANDLE_g2h(hMailslot);
    call.dwReadTimeout = (ULONG_PTR)dwReadTimeout;

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
    call.hFileHandle = guest_HANDLE_g2h(hFileHandle);
    call.hExistingCompletionPort = guest_HANDLE_g2h(hExistingCompletionPort);
    call.CompletionKey = CompletionKey;
    call.dwNumberOfConcurrentThreads = dwNumberOfConcurrentThreads;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateIoCompletionPort(struct qemu_syscall *call)
{
    struct qemu_CreateIoCompletionPort *c = (struct qemu_CreateIoCompletionPort *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateIoCompletionPort(QEMU_G2H(c->hFileHandle), QEMU_G2H(c->hExistingCompletionPort),
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
    call.CompletionPort = guest_HANDLE_g2h(CompletionPort);
    call.lpNumberOfBytesTransferred = (ULONG_PTR)lpNumberOfBytesTransferred;
    call.pCompletionKey = (ULONG_PTR)pCompletionKey;
    call.dwMilliseconds = dwMilliseconds;

    qemu_syscall(&call.super);
    *lpOverlapped = (OVERLAPPED *)(ULONG_PTR)call.lpOverlapped;
    if (call.lpOverlapped)
        *pCompletionKey = call.pCompletionKey;

    return call.super.iret;
}

#else

void qemu_GetQueuedCompletionStatus(struct qemu_syscall *call)
{
    struct qemu_GetQueuedCompletionStatus *c = (struct qemu_GetQueuedCompletionStatus *)call;
    OVERLAPPED *ov;
    struct OVERLAPPED_data *ov_data;
    ULONG_PTR key;

    WINE_TRACE("\n");

    c->super.iret = GetQueuedCompletionStatus(QEMU_G2H(c->CompletionPort), QEMU_G2H(c->lpNumberOfBytesTransferred),
            &key, &ov, c->dwMilliseconds);

    c->pCompletionKey = key;
#if GUEST_BIT == HOST_BIT
    c->lpOverlapped = QEMU_H2G(ov);
    return;
#endif
    if (!ov)
    {
        c->lpOverlapped = 0;
        return;
    }

    /* See comment in overlapped32_wait_func, main.c. */
    WINE_FIXME("This probably reads freed memory.\n");
    ov_data = CONTAINING_RECORD(ov, struct OVERLAPPED_data, ov);
    c->lpOverlapped = QEMU_H2G(ov_data->guest_ov);
    WINE_FIXME("Got guest OVERLAPPED pointer %p from host pointer %p.\n", (void *)c->lpOverlapped, ov);
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
    call.CompletionPort = guest_HANDLE_g2h(CompletionPort);
    call.dwNumberOfBytes = (ULONG_PTR)dwNumberOfBytes;
    call.dwCompletionKey = (ULONG_PTR)dwCompletionKey;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostQueuedCompletionStatus(struct qemu_syscall *call)
{
    struct qemu_PostQueuedCompletionStatus *c = (struct qemu_PostQueuedCompletionStatus *)call;
    struct OVERLAPPED_data *ov_wrapper;
    struct qemu_OVERLAPPED *ov32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = PostQueuedCompletionStatus(QEMU_G2H(c->CompletionPort), c->dwNumberOfBytes, c->dwCompletionKey,
            QEMU_G2H(c->lpOverlapped));
    return;
#endif

    ov32 = QEMU_G2H(c->lpOverlapped);
    if (!ov32)
    {
        c->super.iret = PostQueuedCompletionStatus(QEMU_G2H(c->CompletionPort), c->dwNumberOfBytes,
                c->dwCompletionKey, NULL);
        return;
    }

    /* Don't use alloc_OVERLAPPED_data here because it expects a struct qemu_OVERLAPPED. PostQueuedCompletionStatus
     * doesn't care what is inside the lpOverlapped pointer or that it points to valid memory at all. It will just
     * cause that pointer to be returned 1:1 in GetQueuedCompletionStatus. */
    ov_wrapper = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ov_wrapper));
    ov_wrapper->guest_ov = ov32;

    c->super.iret = PostQueuedCompletionStatus(QEMU_G2H(c->CompletionPort), c->dwNumberOfBytes, c->dwCompletionKey,
            &ov_wrapper->ov);
    /* Don't put it in the tree, we'll never get a callback for these operations. It'll just be reported in
     * GetQueuedCompletionStatus. */
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
    call.FileHandle = guest_HANDLE_g2h(FileHandle);
    call.Function = (ULONG_PTR)Function;
    call.Flags = (ULONG_PTR)Flags;

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
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMemoryResourceNotification(struct qemu_syscall *call)
{
    struct qemu_CreateMemoryResourceNotification *c = (struct qemu_CreateMemoryResourceNotification *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateMemoryResourceNotification(c->type);
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
    call.handle = guest_HANDLE_g2h(handle);
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryMemoryResourceNotification(struct qemu_syscall *call)
{
    struct qemu_QueryMemoryResourceNotification *c = (struct qemu_QueryMemoryResourceNotification *)call;
    WINE_TRACE("\n");
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
    call.once = (ULONG_PTR)once;
    call.flags = (ULONG_PTR)flags;
    call.pending = (ULONG_PTR)pending;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitOnceBeginInitialize(struct qemu_syscall *call)
{
    struct qemu_InitOnceBeginInitialize *c = (struct qemu_InitOnceBeginInitialize *)call;
    WINE_TRACE("\n");
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
    call.once = (ULONG_PTR)once;
    call.flags = (ULONG_PTR)flags;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitOnceComplete(struct qemu_syscall *call)
{
    struct qemu_InitOnceComplete *c = (struct qemu_InitOnceComplete *)call;
    WINE_TRACE("\n");
    c->super.iret = InitOnceComplete(QEMU_G2H(c->once), c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_InitOnceExecuteOnce
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

extern DWORD WINAPI RtlRunOnceExecuteOnce(PRTL_RUN_ONCE,PRTL_RUN_ONCE_INIT_FN,PVOID,PVOID*);

WINBASEAPI BOOL WINAPI InitOnceExecuteOnce( INIT_ONCE *once, PINIT_ONCE_FN func, void *param, void **context )
{
    struct qemu_InitOnceExecuteOnce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITONCEEXECUTEONCE);

    /* For logging */
    qemu_syscall(&call.super);

    return !RtlRunOnceExecuteOnce( once, (PRTL_RUN_ONCE_INIT_FN)func, param, context );
}

#else

void qemu_InitOnceExecuteOnce(struct qemu_syscall *call)
{
    struct qemu_InitOnceExecuteOnce *c = (struct qemu_InitOnceExecuteOnce *)call;

    WINE_TRACE("\n");
}

#endif

#ifdef QEMU_DLL_GUEST

extern NTSTATUS WINAPI RtlSleepConditionVariableCS(RTL_CONDITION_VARIABLE *variable, RTL_CRITICAL_SECTION *crit,
        const LARGE_INTEGER *timeout);
WINBASEAPI BOOL WINAPI SleepConditionVariableCS(CONDITION_VARIABLE *variable, CRITICAL_SECTION *crit, DWORD timeout)
{
    NTSTATUS status;
    LARGE_INTEGER time;

    status = RtlSleepConditionVariableCS( variable, crit, get_nt_timeout( &time, timeout ) );

    if (status)
    {
        kernel32_SetLastError( RtlNtStatusToDosError(status) );
        return FALSE;
    }
    return TRUE;
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
    call.variable = (ULONG_PTR)variable;
    call.lock = (ULONG_PTR)lock;
    call.timeout = (ULONG_PTR)timeout;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SleepConditionVariableSRW(struct qemu_syscall *call)
{
    struct qemu_SleepConditionVariableSRW *c = (struct qemu_SleepConditionVariableSRW *)call;
    WINE_TRACE("\n");
    c->super.iret = SleepConditionVariableSRW(QEMU_G2H(c->variable), QEMU_G2H(c->lock), c->timeout, c->flags);
}

#endif

#ifdef __i386__

/***********************************************************************
 *		InterlockedCompareExchange (KERNEL32.@)
 */
/* LONG WINAPI InterlockedCompareExchange( PLONG dest, LONG xchg, LONG compare ); */
__ASM_STDCALL_FUNC(InterlockedCompareExchange, 12,
                  "movl 12(%esp),%eax\n\t"
                  "movl 8(%esp),%ecx\n\t"
                  "movl 4(%esp),%edx\n\t"
                  "lock; cmpxchgl %ecx,(%edx)\n\t"
                  "ret $12")

/***********************************************************************
 *		InterlockedExchange (KERNEL32.@)
 */
/* LONG WINAPI InterlockedExchange( PLONG dest, LONG val ); */
__ASM_STDCALL_FUNC(InterlockedExchange, 8,
                  "movl 8(%esp),%eax\n\t"
                  "movl 4(%esp),%edx\n\t"
                  "lock; xchgl %eax,(%edx)\n\t"
                  "ret $8")

/***********************************************************************
 *		InterlockedExchangeAdd (KERNEL32.@)
 */
/* LONG WINAPI InterlockedExchangeAdd( PLONG dest, LONG incr ); */
__ASM_STDCALL_FUNC(InterlockedExchangeAdd, 8,
                  "movl 8(%esp),%eax\n\t"
                  "movl 4(%esp),%edx\n\t"
                  "lock; xaddl %eax,(%edx)\n\t"
                  "ret $8")

/***********************************************************************
 *		InterlockedIncrement (KERNEL32.@)
 */
/* LONG WINAPI InterlockedIncrement( PLONG dest ); */
__ASM_STDCALL_FUNC(InterlockedIncrement, 4,
                  "movl 4(%esp),%edx\n\t"
                  "movl $1,%eax\n\t"
                  "lock; xaddl %eax,(%edx)\n\t"
                  "incl %eax\n\t"
                  "ret $4")

/***********************************************************************
 *		InterlockedDecrement (KERNEL32.@)
 */
__ASM_STDCALL_FUNC(InterlockedDecrement, 4,
                  "movl 4(%esp),%edx\n\t"
                  "movl $-1,%eax\n\t"
                  "lock; xaddl %eax,(%edx)\n\t"
                  "decl %eax\n\t"
                  "ret $4")

#endif  /* __i386__ */

