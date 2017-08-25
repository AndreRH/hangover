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
#include "user32.h"

#ifndef QEMU_DLL_GUEST

#include <wine/debug.h>
#include <assert.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);

#endif

struct qemu_RegisterClass
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t wndproc_wrapper;
};

#ifdef QEMU_DLL_GUEST

LRESULT wndproc_wrapper(const struct wndproc_call *call)
{
    WNDPROC proc = (WNDPROC)call->wndproc;

    return proc((HWND)call->win, call->msg, call->wparam, call->lparam);
}

WINUSERAPI ATOM WINAPI RegisterClassA(const WNDCLASSA *wc)
{
    struct qemu_RegisterClass call;
    WNDCLASSEXA wcex;

    wcex.cbSize        = sizeof(wcex);
    wcex.style         = wc->style;
    wcex.lpfnWndProc   = wc->lpfnWndProc;
    wcex.cbClsExtra    = wc->cbClsExtra;
    wcex.cbWndExtra    = wc->cbWndExtra;
    wcex.hInstance     = wc->hInstance;
    wcex.hIcon         = wc->hIcon;
    wcex.hCursor       = wc->hCursor;
    wcex.hbrBackground = wc->hbrBackground;
    wcex.lpszMenuName  = wc->lpszMenuName;
    wcex.lpszClassName = wc->lpszClassName;
    wcex.hIconSm       = 0;

    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXA);
    call.wc = (uint64_t)&wcex;
    call.wndproc_wrapper = (uint64_t)wndproc_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ATOM WINAPI RegisterClassW(const WNDCLASSW *wc)
{
    WNDCLASSEXW wcex;
    struct qemu_RegisterClass call;

    wcex.cbSize        = sizeof(wcex);
    wcex.style         = wc->style;
    wcex.lpfnWndProc   = wc->lpfnWndProc;
    wcex.cbClsExtra    = wc->cbClsExtra;
    wcex.cbWndExtra    = wc->cbWndExtra;
    wcex.hInstance     = wc->hInstance;
    wcex.hIcon         = wc->hIcon;
    wcex.hCursor       = wc->hCursor;
    wcex.hbrBackground = wc->hbrBackground;
    wcex.lpszMenuName  = wc->lpszMenuName;
    wcex.lpszClassName = wc->lpszClassName;
    wcex.hIconSm       = 0;

    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXW);
    call.wc = (uint64_t)&wcex;
    call.wndproc_wrapper = (uint64_t)wndproc_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ATOM WINAPI RegisterClassExA(const WNDCLASSEXA* wc)
{
    struct qemu_RegisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXA);
    call.wc = (uint64_t)wc;
    call.wndproc_wrapper = (uint64_t)wndproc_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ATOM WINAPI RegisterClassExW(const WNDCLASSEXW* wc)
{
    struct qemu_RegisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXW);
    call.wc = (uint64_t)wc;
    call.wndproc_wrapper = (uint64_t)wndproc_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterClassEx(struct qemu_syscall *call)
{
    unsigned int i;
    struct qemu_RegisterClass *c = (struct qemu_RegisterClass *)call;
    uint64_t guest_proc;
    BOOL wrapper_used = TRUE;

    WINE_TRACE("\n");

    guest_wndproc_wrapper = c->wndproc_wrapper;

    for (i = 0; i < class_wrapper_count; ++i)
    {
        if (!class_wrappers[i].atom)
            break;
    }
    if (i == class_wrapper_count)
    {
        /* Growing the array requires updating all WNDPROCs for the existing classes
         * to the new location. It is doable, but requires more code than a simple
         * new allocation. */
        WINE_FIXME("All class wrappers are in use\n");
        c->super.iret = 0;
        return;
    }

    if (c->super.id == QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXW))
    {
        WNDCLASSEXW exw = *(WNDCLASSEXW *)QEMU_G2H(c->wc);

        guest_proc = (uint64_t)exw.lpfnWndProc;

        if (guest_proc >= (ULONG_PTR)&reverse_classproc_wrappers[0]
                && guest_proc <= (ULONG_PTR)&reverse_classproc_wrappers[REVERSE_CLASSPROC_WRAPPER_COUNT])
        {
            struct reverse_classproc_wrapper *rev_wrapper = (struct reverse_classproc_wrapper *)guest_proc;

            WINE_TRACE("Guest function %p is a reverse wrapper for host function %p.\n",
                    rev_wrapper, rev_wrapper->host_func);
            exw.lpfnWndProc = rev_wrapper->host_func;
            wrapper_used = FALSE;
        }
        else
        {
            WINE_TRACE("Using wrapper %p for the new class, wndproc 0x%lx.\n", &class_wrappers[i], guest_proc);
            exw.lpfnWndProc = (WNDPROC)&class_wrappers[i];
        }

        if (!exw.hInstance)
            exw.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

        c->super.iret = RegisterClassExW(&exw);
    }
    else
    {
        WNDCLASSEXA exa = *(WNDCLASSEXA *)QEMU_G2H(c->wc);

        guest_proc = (uint64_t)exa.lpfnWndProc;

        if (guest_proc >= (ULONG_PTR)&reverse_classproc_wrappers[0]
                && guest_proc <= (ULONG_PTR)&reverse_classproc_wrappers[REVERSE_CLASSPROC_WRAPPER_COUNT])
        {
            struct reverse_classproc_wrapper *rev_wrapper = (struct reverse_classproc_wrapper *)guest_proc;

            WINE_TRACE("Guest function %p is a reverse wrapper for host function %p.\n",
                    rev_wrapper, rev_wrapper->host_func);
            exa.lpfnWndProc = rev_wrapper->host_func;
            wrapper_used = FALSE;
        }
        else
        {
            WINE_TRACE("Using wrapper %p for the new class, wndproc 0x%lx.\n", &class_wrappers[i], guest_proc);
            exa.lpfnWndProc = (WNDPROC)&class_wrappers[i];
        }

        if (!exa.hInstance)
            exa.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

        c->super.iret = RegisterClassExA(&exa);
    }

    if (c->super.iret && wrapper_used)
    {
        class_wrappers[i].atom = c->super.iret;
        class_wrappers[i].guest_proc = guest_proc;
    }
}

#endif

struct qemu_UnregisterClass
{
    struct qemu_syscall super;
    uint64_t className;
    uint64_t hInstance;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnregisterClassA(const char *className, HINSTANCE hInstance)
{
    struct qemu_UnregisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERCLASSA);
    call.className = (uint64_t)className;
    call.hInstance = (uint64_t)hInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI BOOL WINAPI UnregisterClassW(const WCHAR *className, HINSTANCE hInstance)
{
    struct qemu_UnregisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERCLASSW);
    call.className = (uint64_t)className;
    call.hInstance = (uint64_t)hInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterClass(struct qemu_syscall *call)
{
    struct qemu_UnregisterClass *c = (struct qemu_UnregisterClass *)call;
    ATOM atom;
    unsigned int i;
    HINSTANCE inst;
    ULONG_PTR proc;
    WINE_TRACE("\n");

    inst = (HINSTANCE)c->hInstance;
    if (!inst)
        inst = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    if (c->super.id == QEMU_SYSCALL_ID(CALL_UNREGISTERCLASSA))
    {
        WNDCLASSEXA info;
        atom = GetClassInfoExA(inst, QEMU_G2H(c->className), &info);
        c->super.iret = UnregisterClassA(QEMU_G2H(c->className), inst);
        proc = (ULONG_PTR)info.lpfnWndProc;
    }
    else
    {
        WNDCLASSEXW info;
        atom = GetClassInfoExW(inst, QEMU_G2H(c->className), &info);
        c->super.iret = UnregisterClassW(QEMU_G2H(c->className), inst);
        proc = (ULONG_PTR)info.lpfnWndProc;
    }

    if (c->super.iret)
    {
        if (!atom)
            WINE_ERR("Atom is 0, but unregistering suceeded.\n");

        if ((proc >= (ULONG_PTR)&class_wrappers[0] && proc <= (ULONG_PTR)&class_wrappers[class_wrapper_count])
                || (proc >= (ULONG_PTR)&win_wrappers[0] && proc <= (ULONG_PTR)&win_wrappers[win_wrapper_count]))
        {
            /* This happens when the app passed in a reverse wrapper when registering the class. */
            WINE_TRACE("Class did not use a wndproc wrapper.\n");
            return;
        }

        for (i = 0; i < class_wrapper_count; ++i)
        {
            if (class_wrappers[i].atom == atom)
            {
                WINE_TRACE("Releasing wndproc wrapper %p.\n", &class_wrappers[i]);
                class_wrappers[i].atom = 0;
                class_wrappers[i].guest_proc = 0;
                return;
            }
        }
        WINE_ERR("Could not find atom %x in class table\n", atom);
    }
}

#endif

struct qemu_GetClassWord
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI GetClassWord(HWND hwnd, INT offset)
{
    struct qemu_GetClassWord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSWORD);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassWord(struct qemu_syscall *call)
{
    struct qemu_GetClassWord *c = (struct qemu_GetClassWord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassWord(QEMU_G2H(c->hwnd), c->offset);
}

#endif

struct qemu_GetClassLongW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetClassLongW(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGW);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassLongW(struct qemu_syscall *call)
{
    struct qemu_GetClassLongW *c = (struct qemu_GetClassLongW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassLongW(QEMU_G2H(c->hwnd), c->offset);
}

#endif

struct qemu_GetClassLongA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetClassLongA(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGA);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassLongA(struct qemu_syscall *call)
{
    struct qemu_GetClassLongA *c = (struct qemu_GetClassLongA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassLongA(QEMU_G2H(c->hwnd), c->offset);
}

#endif

struct qemu_SetClassWord
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI SetClassWord(HWND hwnd, INT offset, WORD newval)
{
    struct qemu_SetClassWord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSWORD);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetClassWord(struct qemu_syscall *call)
{
    struct qemu_SetClassWord *c = (struct qemu_SetClassWord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetClassWord(QEMU_G2H(c->hwnd), c->offset, c->newval);
}

#endif

struct qemu_SetClassLongW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI SetClassLongW(HWND hwnd, INT offset, LONG newval)
{
    struct qemu_SetClassLongW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGW);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetClassLongW(struct qemu_syscall *call)
{
    struct qemu_SetClassLongW *c = (struct qemu_SetClassLongW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetClassLongW(QEMU_G2H(c->hwnd), c->offset, c->newval);
}

#endif

struct qemu_SetClassLongA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI SetClassLongA(HWND hwnd, INT offset, LONG newval)
{
    struct qemu_SetClassLongA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGA);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetClassLongA(struct qemu_syscall *call)
{
    struct qemu_SetClassLongA *c = (struct qemu_SetClassLongA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetClassLongA(QEMU_G2H(c->hwnd), c->offset, c->newval);
}

#endif

struct qemu_GetClassNameA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetClassNameA(HWND hwnd, LPSTR buffer, INT count)
{
    struct qemu_GetClassNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSNAMEA);
    call.hwnd = (uint64_t)hwnd;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassNameA(struct qemu_syscall *call)
{
    struct qemu_GetClassNameA *c = (struct qemu_GetClassNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassNameA(QEMU_G2H(c->hwnd), QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_GetClassNameW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetClassNameW(HWND hwnd, LPWSTR buffer, INT count)
{
    struct qemu_GetClassNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSNAMEW);
    call.hwnd = (uint64_t)hwnd;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassNameW(struct qemu_syscall *call)
{
    struct qemu_GetClassNameW *c = (struct qemu_GetClassNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassNameW(QEMU_G2H(c->hwnd), QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_RealGetWindowClassA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI RealGetWindowClassA(HWND hwnd, LPSTR buffer, UINT count)
{
    struct qemu_RealGetWindowClassA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALGETWINDOWCLASSA);
    call.hwnd = (uint64_t)hwnd;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RealGetWindowClassA(struct qemu_syscall *call)
{
    struct qemu_RealGetWindowClassA *c = (struct qemu_RealGetWindowClassA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RealGetWindowClassA(QEMU_G2H(c->hwnd), QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_RealGetWindowClassW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI RealGetWindowClassW(HWND hwnd, LPWSTR buffer, UINT count)
{
    struct qemu_RealGetWindowClassW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALGETWINDOWCLASSW);
    call.hwnd = (uint64_t)hwnd;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RealGetWindowClassW(struct qemu_syscall *call)
{
    struct qemu_RealGetWindowClassW *c = (struct qemu_RealGetWindowClassW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RealGetWindowClassW(QEMU_G2H(c->hwnd), QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_GetClassInfoA
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t name;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetClassInfoA(HINSTANCE hInstance, LPCSTR name, WNDCLASSA *wc)
{
    struct qemu_GetClassInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSINFOA);
    call.hInstance = (uint64_t)hInstance;
    call.name = (uint64_t)name;
    call.wc = (uint64_t)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct reverse_classproc_wrapper *find_reverse_wndproc_wrapper(void *host_func)
{
    unsigned int i;

    for (i = 0; i < REVERSE_CLASSPROC_WRAPPER_COUNT; ++i)
    {
        if (reverse_classproc_wrappers[i].host_func == host_func)
            return &reverse_classproc_wrappers[i];
        if (!reverse_classproc_wrappers[i].host_func)
        {
            reverse_classproc_wrappers[i].host_func = host_func;
            return &reverse_classproc_wrappers[i];
        }
    }

    /* Need to make the array bigger if we ran out of it. Can't grow it dynamically. */
    assert(0);
}

static ULONG_PTR qemu_GetClassInfo_wndproc(ULONG_PTR host_proc)
{
    struct classproc_wrapper *wrapper;
    struct reverse_classproc_wrapper *reverse_wrapper;

    if (host_proc >= (ULONG_PTR)&class_wrappers[0]
            && host_proc <= (ULONG_PTR)&class_wrappers[class_wrapper_count])
    {
        wrapper = (struct classproc_wrapper *)host_proc;
        WINE_TRACE("Host wndproc is a wrapper function. Returning guest wndproc 0x%lx.\n", wrapper->guest_proc);
        return wrapper->guest_proc;
    }
    else
    {
        reverse_wrapper = find_reverse_wndproc_wrapper((void *)host_proc);
        reverse_wrapper->guest_func = reverse_classproc_func;
        WINE_TRACE("Returning reverse wrapper %p for host function 0x%lx.\n", reverse_wrapper, host_proc);
        return QEMU_H2G(reverse_wrapper);
    }
}

void qemu_GetClassInfoA(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoA *c = (struct qemu_GetClassInfoA *)call;
    WNDCLASSA *wc;

    WINE_FIXME("Unverified!\n");
    wc = QEMU_G2H(c->wc);
    c->super.iret = GetClassInfoA(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), wc);

    if (c->super.iret)
        wc->lpfnWndProc = (void *)qemu_GetClassInfo_wndproc((ULONG_PTR)wc->lpfnWndProc);
}

#endif

struct qemu_GetClassInfoW
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t name;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetClassInfoW(HINSTANCE hInstance, LPCWSTR name, WNDCLASSW *wc)
{
    struct qemu_GetClassInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSINFOW);
    call.hInstance = (uint64_t)hInstance;
    call.name = (uint64_t)name;
    call.wc = (uint64_t)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoW(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoW *c = (struct qemu_GetClassInfoW *)call;
    WNDCLASSW *wc;

    WINE_FIXME("Unverified!\n");
    wc = QEMU_G2H(c->wc);
    c->super.iret = GetClassInfoW(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), wc);

    if (c->super.iret)
        wc->lpfnWndProc = (void *)qemu_GetClassInfo_wndproc((ULONG_PTR)wc->lpfnWndProc);
}

#endif

struct qemu_GetClassInfoExA
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t name;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetClassInfoExA(HINSTANCE hInstance, LPCSTR name, WNDCLASSEXA *wc)
{
    struct qemu_GetClassInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSINFOEXA);
    call.hInstance = (uint64_t)hInstance;
    call.name = (uint64_t)name;
    call.wc = (uint64_t)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoExA *c = (struct qemu_GetClassInfoExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassInfoExA(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), QEMU_G2H(c->wc));
}

#endif

struct qemu_GetClassInfoExW
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t name;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetClassInfoExW(HINSTANCE hInstance, LPCWSTR name, WNDCLASSEXW *wc)
{
    struct qemu_GetClassInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSINFOEXW);
    call.hInstance = (uint64_t)hInstance;
    call.name = (uint64_t)name;
    call.wc = (uint64_t)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoExW *c = (struct qemu_GetClassInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassInfoExW(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), QEMU_G2H(c->wc));
}

#endif

struct qemu_GetClassLongPtrA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

struct qemu_call_wndproc
{
    struct qemu_syscall super;
    uint64_t win;
    uint64_t msg;
    uint64_t wp;
    uint64_t lp;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

LRESULT CALLBACK reverse_classproc_func(HWND win, UINT msg, WPARAM wp, LPARAM lp, void *data)
{
    struct qemu_call_wndproc call;

    call.super.id = QEMU_SYSCALL_ID(CALL_CALL_WNDPROC);
    call.win = (uint64_t)win;
    call.msg = msg;
    call.wp = wp;
    call.lp = lp;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ULONG_PTR WINAPI GetClassLongPtrA(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGPTRA);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG_PTR get_class_wndproc(HWND win, BOOL wide)
{
    ULONG_PTR host_proc;
    const struct classproc_wrapper *wrapper;
    struct reverse_classproc_wrapper *reverse_wrapper;

    if (wide)
        host_proc = GetClassLongPtrW(win, GCLP_WNDPROC);
    else
        host_proc = GetClassLongPtrA(win, GCLP_WNDPROC);

    return qemu_GetClassInfo_wndproc(host_proc);
}

void qemu_GetClassLongPtrA(struct qemu_syscall *call)
{
    struct qemu_GetClassLongPtrA *c = (struct qemu_GetClassLongPtrA *)call;
    HWND win;
    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = get_class_wndproc(win, FALSE);
            break;

        default:
            c->super.iret = GetClassLongPtrA(win, c->offset);
    }
}

void qemu_call_wndproc(struct qemu_syscall *call)
{
    struct qemu_call_wndproc *c = (struct qemu_call_wndproc *)call;
    struct reverse_classproc_wrapper *wrapper;

    WINE_TRACE("\n");
    wrapper = QEMU_G2H(c->data);
    WINE_TRACE("Calling function %p from reverse wrapper %p.\n", wrapper->host_func, wrapper);

    c->super.iret = CallWindowProcW(wrapper->host_func, (HWND)c->win, c->msg, c->wp, c->lp);

    WINE_TRACE("Returning 0x%lx.\n", c->super.iret);
}

#endif

struct qemu_GetClassLongPtrW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI ULONG_PTR WINAPI GetClassLongPtrW(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGPTRW);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassLongPtrW(struct qemu_syscall *call)
{
    struct qemu_GetClassLongPtrW *c = (struct qemu_GetClassLongPtrW *)call;
    HWND win;
    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = get_class_wndproc(win, TRUE);
            break;

        default:
            c->super.iret = GetClassLongPtrW(win, c->offset);
    }
}

#endif

struct qemu_SetClassLongPtrW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI ULONG_PTR WINAPI SetClassLongPtrW(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetClassLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGPTRW);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static struct classproc_wrapper *find_free_classproc_wrapper(void)
{
    unsigned int i;

    /* Find a forward wrapper to call the new guest proc. */
    for (i = 0; i < class_wrapper_count; ++i)
    {
        if (!class_wrappers[i].atom)
        {
            WINE_TRACE("Returning wrapper %p\n", &win_wrappers[i]);
            return &class_wrappers[i];
        }
    }
    WINE_FIXME("All class wrappers are in use\n");
    return NULL;
}

ULONG_PTR set_class_wndproc(HWND win, BOOL wide, LONG_PTR newval)
{
    LONG_PTR ret, ret2;
    ATOM atom;
    struct classproc_wrapper *wrapper;
    struct reverse_classproc_wrapper *reverse_wrapper;
    BOOL restore = FALSE;

    if (wide)
    {
        ret = GetClassLongPtrW(win, GCLP_WNDPROC);
        atom = GetClassLongW(win, GCW_ATOM);
    }
    else
    {
        ret = GetClassLongPtrA(win, GCLP_WNDPROC);
        atom = GetClassLongA(win, GCW_ATOM);
    }

    if (newval >= (LONG_PTR)&reverse_classproc_wrappers[0]
            && newval <= (LONG_PTR)&reverse_classproc_wrappers[REVERSE_CLASSPROC_WRAPPER_COUNT])
    {
        reverse_wrapper = (struct reverse_classproc_wrapper *)newval;
        WINE_TRACE("Restoring native class function %p\n", reverse_wrapper->host_func);
        if (wide)
            SetClassLongPtrW(win, GCLP_WNDPROC, (LONG_PTR)reverse_wrapper->host_func);
        else
            SetClassLongPtrA(win, GCLP_WNDPROC, (LONG_PTR)reverse_wrapper->host_func);

        restore = TRUE;
    }

    if (ret >= (ULONG_PTR)&class_wrappers[0] && ret <= (ULONG_PTR)&class_wrappers[class_wrapper_count])
    {
        WINE_TRACE("Old host proc 0x%lx is our wrapper.\n", ret);

        wrapper = (struct classproc_wrapper *)ret;
        if (wrapper->atom != atom)
            WINE_ERR("Expected atom %x, got %x.\n", wrapper->atom, atom);

        /* FIXME: The behavior of Wine's SetClassLongPtr suggests that this should not affect
         * windows that already exist. That would require overwriting the WNDPROC with something
         * window specific whenever a new window is created. */
        WINE_TRACE("Setting guest proc of wndproc wrapper %p to 0x%lx.\n", wrapper, newval);
        ret = wrapper->guest_proc;
        wrapper->guest_proc = newval;
        return ret;
    }

    if (restore)
        WINE_ERR("Did not expect to get here.\n");

    /* Find / Create a reverse wrapper for the old function. */
    reverse_wrapper = find_reverse_wndproc_wrapper((void *)ret);
    reverse_wrapper->guest_func = reverse_classproc_func;
    WINE_TRACE("Returning reverse wrapper %p for host function 0x%lx\n", reverse_wrapper, ret);
    ret = (ULONG_PTR)reverse_wrapper;

    wrapper = find_free_classproc_wrapper();
    assert(wrapper);

    /* NOTE: We don't have a way to free the forward wrapper slot because the app didn't
     * register the class and we will not see the UnregisterClass call if the Wine DLL ever
     * unregisters its classes. This is acceptable for classes because I don't expect the
     * builtin classes to be unregistered in practise. */
    WINE_TRACE("Setting new forward wndproc wrapper %p for function 0x%lx.\n",
            wrapper, newval);
    if (wide)
        ret2 = SetClassLongPtrW(win, GCLP_WNDPROC, (LONG_PTR)wrapper);
    else
        ret2 = SetClassLongPtrA(win, GCLP_WNDPROC, (LONG_PTR)wrapper);
    WINE_TRACE("SetClassLongPtr returned 0x%lx.\n", ret2);

    wrapper->atom = atom;
    wrapper->guest_proc = newval;

    return ret;
}

void qemu_SetClassLongPtrW(struct qemu_syscall *call)
{
    struct qemu_SetClassLongPtrW *c = (struct qemu_SetClassLongPtrW *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = set_class_wndproc(win, TRUE, c->newval);
            break;

        default:
            c->super.iret = SetClassLongPtrW(win, c->offset, c->newval);
            break;
    }
}

#endif

struct qemu_SetClassLongPtrA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
    uint64_t reverse_wrapper;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI ULONG_PTR WINAPI SetClassLongPtrA(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetClassLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGPTRA);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetClassLongPtrA(struct qemu_syscall *call)
{
    struct qemu_SetClassLongPtrW *c = (struct qemu_SetClassLongPtrW *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = set_class_wndproc(win, FALSE, c->newval);
            break;

        default:
            c->super.iret = SetClassLongPtrA(win, c->offset, c->newval);
            break;
    }
}

#endif

