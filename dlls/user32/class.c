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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST

#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);

#endif

struct qemu_RegisterClass
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

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
    call.wc = (ULONG_PTR)&wcex;

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
    call.wc = (ULONG_PTR)&wcex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ATOM WINAPI RegisterClassExA(const WNDCLASSEXA* wc)
{
    struct qemu_RegisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXA);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ATOM WINAPI RegisterClassExW(const WNDCLASSEXW* wc)
{
    struct qemu_RegisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXW);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterClassEx(struct qemu_syscall *call)
{
    struct qemu_RegisterClass *c = (struct qemu_RegisterClass *)call;
    uint64_t guest_proc;
    struct qemu_WNDCLASSEX *class32;

    WINE_TRACE("\n");

    if (c->super.id == QEMU_SYSCALL_ID(CALL_REGISTERCLASSEXW))
    {
        WNDCLASSEXW exw;
#if HOST_BIT == GUEST_BIT
        exw = *(WNDCLASSEXW *)QEMU_G2H(c->wc);
#else
        class32 = QEMU_G2H(c->wc);
        if (class32->cbSize != sizeof(*class32))
        {
            WINE_WARN("Invalid size, passing invalid struct to host.\n");
            memset(&exw, 0, sizeof(exw));
            c->super.iret = RegisterClassExW(&exw);
            return;
        }
        WNDCLASSEX_g2h(&exw, class32);

        /* DLGPROC and LPARAM are 8 bytes in Wine. DLGWINDOWEXTRA may cause issues,
         * but it seems to be a "comdlg32 needs this much" value, and not a "read from
         * resources" marker. */
        if (exw.cbWndExtra > 0)
            exw.cbWndExtra += 2 * (sizeof(void *) - sizeof(qemu_ptr));
#endif

        guest_proc = (ULONG_PTR)exw.lpfnWndProc;
        exw.lpfnWndProc = wndproc_guest_to_host(guest_proc);
        exw.hInstance = qemu_ops->qemu_module_g2h((uint64_t)exw.hInstance);

        c->super.iret = RegisterClassExW(&exw);
    }
    else
    {
        WNDCLASSEXA exa;
#if HOST_BIT == GUEST_BIT
        exa = *(WNDCLASSEXA *)QEMU_G2H(c->wc);
#else
        class32 = QEMU_G2H(c->wc);
        if (class32->cbSize != sizeof(*class32))
        {
            WINE_WARN("Invalid size, passing invalid struct to host.\n");
            memset(&exa, 0, sizeof(exa));
            c->super.iret = RegisterClassExA(&exa);
            return;
        }
        WNDCLASSEX_g2h((WNDCLASSEXW *)&exa, class32);

        /* DLGPROC and LPARAM are 8 bytes in Wine. DLGWINDOWEXTRA may cause issues,
         * but it seems to be a "comdlg32 needs this much" value, and not a "read from
         * resources" marker. */
        if (exa.cbWndExtra > 0)
            exa.cbWndExtra += 2 * (sizeof(void *) - sizeof(qemu_ptr));
#endif

        guest_proc = (ULONG_PTR)exa.lpfnWndProc;
        exa.lpfnWndProc = wndproc_guest_to_host(guest_proc);
        exa.hInstance = qemu_ops->qemu_module_g2h((uint64_t)exa.hInstance);

        c->super.iret = RegisterClassExA(&exa);
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
    call.className = (ULONG_PTR)className;
    call.hInstance = (ULONG_PTR)hInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI BOOL WINAPI UnregisterClassW(const WCHAR *className, HINSTANCE hInstance)
{
    struct qemu_UnregisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERCLASSW);
    call.className = (ULONG_PTR)className;
    call.hInstance = (ULONG_PTR)hInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterClass(struct qemu_syscall *call)
{
    struct qemu_UnregisterClass *c = (struct qemu_UnregisterClass *)call;
    unsigned int i;
    HINSTANCE inst;
    ULONG_PTR proc;
    WINE_TRACE("\n");

    if (c->hInstance)
        inst = qemu_ops->qemu_module_g2h(c->hInstance);
    else
        inst = NULL;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_UNREGISTERCLASSA))
        c->super.iret = UnregisterClassA(QEMU_G2H(c->className), inst);
    else
        c->super.iret = UnregisterClassW(QEMU_G2H(c->className), inst);
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
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

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

DWORD WINAPI user32_GetClassLongW(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

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

    return wndproc_host_to_guest((WNDPROC)host_proc);
}

void qemu_GetClassLongW(struct qemu_syscall *call)
{
    struct qemu_GetClassLongW *c = (struct qemu_GetClassLongW *)call;
    HWND win;
    DWORD_PTR module;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = get_class_wndproc(win, TRUE);
            break;

        case GCLP_HMODULE:
            module = GetClassLongPtrW(win, c->offset);
            c->super.iret = qemu_ops->qemu_module_h2g((HMODULE)module);
            break;

#if 0
        case GCL_CBWNDEXTRA:
            WINE_FIXME("Check correct return value for GCL_CBWNDEXTRA.\n");
            /* Drop through */
#endif
        default:
            c->super.iret = GetClassLongW(win, c->offset);
    }
}

#endif

struct qemu_GetClassLongA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI user32_GetClassLongA(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassLongA(struct qemu_syscall *call)
{
    struct qemu_GetClassLongA *c = (struct qemu_GetClassLongA *)call;
    HWND win;
    DWORD_PTR module;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = get_class_wndproc(win, FALSE);
            break;

        case GCLP_HMODULE:
            module = GetClassLongPtrA(win, c->offset);
            c->super.iret = qemu_ops->qemu_module_h2g((HMODULE)module);
            break;

#if 0
        case GCL_CBWNDEXTRA:
            WINE_FIXME("Check correct return value for GCL_CBWNDEXTRA.\n");
            /* Drop through */
#endif
        default:
            c->super.iret = GetClassLongA(win, c->offset);
    }
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
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = (ULONG_PTR)newval;

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

DWORD WINAPI user32_SetClassLongW(HWND hwnd, INT offset, LONG newval)
{
    struct qemu_SetClassLongW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = (ULONG_PTR)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG_PTR set_class_wndproc(HWND win, BOOL wide, LONG_PTR newval)
{
    LONG_PTR host_proc = (LONG_PTR)wndproc_guest_to_host(newval);
    LONG_PTR old;
    ULONG_PTR guest_old;

    WINE_TRACE("Application is setting the class proc to 0x%lx, setting host proc 0x%lx.\n",
            newval, host_proc);

    if (wide)
        old = SetClassLongPtrW(win, GCLP_WNDPROC, (LONG_PTR)host_proc);
    else
        old = SetClassLongPtrA(win, GCLP_WNDPROC, (LONG_PTR)host_proc);

    guest_old = wndproc_host_to_guest((WNDPROC)old);

    WINE_TRACE("Returning old wndproc 0x%lx for host wndproc 0x%lx.\n", guest_old, old);

    return guest_old;
}

void qemu_SetClassLongW(struct qemu_syscall *call)
{
    struct qemu_SetClassLongW *c = (struct qemu_SetClassLongW *)call;
    HWND win;
    WINE_TRACE("\n");

    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = set_class_wndproc(win, TRUE, c->newval);
            break;

        case GCLP_HMODULE:
            if (c->newval)
                c->newval = (ULONG_PTR)qemu_ops->qemu_module_g2h(c->newval);

            c->super.iret = SetClassLongPtrW(win, c->offset, c->newval);
            break;

#if 0
        case GCL_CBWNDEXTRA:
            WINE_FIXME("Check correct return value for GCL_CBWNDEXTRA.\n");
            /* Drop through */
#endif
        default:
            c->super.iret = SetClassLongW(win, c->offset, c->newval);
            break;
    }
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

DWORD WINAPI user32_SetClassLongA(HWND hwnd, INT offset, LONG newval)
{
    struct qemu_SetClassLongA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = (ULONG_PTR)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetClassLongA(struct qemu_syscall *call)
{
    struct qemu_SetClassLongA *c = (struct qemu_SetClassLongA *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = set_class_wndproc(win, FALSE, c->newval);
            break;

        case GCLP_HMODULE:
            if (c->newval)
                c->newval = (ULONG_PTR)qemu_ops->qemu_module_g2h(c->newval);

            c->super.iret = SetClassLongPtrA(win, c->offset, c->newval);
            break;

#if 0
        case GCL_CBWNDEXTRA:
            WINE_FIXME("Check correct return value for GCL_CBWNDEXTRA.\n");
            /* Drop through */
#endif
        default:
            c->super.iret = SetClassLongA(win, c->offset, c->newval);
            break;
    }
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
    call.hwnd = (ULONG_PTR)hwnd;
    call.buffer = (ULONG_PTR)buffer;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassNameA(struct qemu_syscall *call)
{
    struct qemu_GetClassNameA *c = (struct qemu_GetClassNameA *)call;
    WINE_TRACE("\n");
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
    call.hwnd = (ULONG_PTR)hwnd;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassNameW(struct qemu_syscall *call)
{
    struct qemu_GetClassNameW *c = (struct qemu_GetClassNameW *)call;
    WINE_TRACE("\n");
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
    call.hwnd = (ULONG_PTR)hwnd;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

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
    call.hwnd = (ULONG_PTR)hwnd;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

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
    call.hInstance = (ULONG_PTR)hInstance;
    call.name = (ULONG_PTR)name;
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoA(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoA *c = (struct qemu_GetClassInfoA *)call;
    WNDCLASSA stack, *wc = &stack;
    HINSTANCE inst;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    wc = QEMU_G2H(c->wc);
#endif

    if (c->hInstance)
        inst = qemu_ops->qemu_module_g2h(c->hInstance);
    else
        inst = NULL;

    c->super.iret = GetClassInfoA(inst, QEMU_G2H(c->name), wc);

    if (c->super.iret)
    {
        wc->lpfnWndProc = (void *)wndproc_host_to_guest(wc->lpfnWndProc);
        wc->hInstance = (HINSTANCE)qemu_ops->qemu_module_h2g(wc->hInstance);
#if GUEST_BIT != HOST_BIT
        WNDCLASS_h2g(QEMU_G2H(c->wc), (WNDCLASSW *)wc);
#endif
    }
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
    call.hInstance = (ULONG_PTR)hInstance;
    call.name = (ULONG_PTR)name;
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoW(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoW *c = (struct qemu_GetClassInfoW *)call;
    WNDCLASSW stack, *wc = &stack;
    HINSTANCE inst;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    wc = QEMU_G2H(c->wc);
#endif

    if (c->hInstance)
        inst = qemu_ops->qemu_module_g2h(c->hInstance);
    else
        inst = NULL;

    c->super.iret = GetClassInfoW(inst, QEMU_G2H(c->name), wc);

    if (c->super.iret)
    {
        wc->lpfnWndProc = (void *)wndproc_host_to_guest(wc->lpfnWndProc);
        wc->hInstance = (HINSTANCE)qemu_ops->qemu_module_h2g(wc->hInstance);
#if GUEST_BIT != HOST_BIT
        WNDCLASS_h2g(QEMU_G2H(c->wc), wc);
#endif
    }
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
    call.hInstance = (ULONG_PTR)hInstance;
    call.name = (ULONG_PTR)name;
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoExA *c = (struct qemu_GetClassInfoExA *)call;
    WNDCLASSEXA stack, *wc = &stack;
    struct qemu_WNDCLASSEX *class32;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    wc = QEMU_G2H(c->wc);
#else
    class32 = QEMU_G2H(c->wc);
    if (class32)
    {
        if (class32->cbSize == sizeof(*class32))
            wc->cbSize = sizeof(*wc);
        else
            wc->cbSize = 0;
    }
    else
    {
        wc = NULL;
    }
#endif

    c->super.iret = GetClassInfoExA(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), wc);

    if (c->super.iret)
    {
        wc->lpfnWndProc = (void *)wndproc_host_to_guest(wc->lpfnWndProc);
#if GUEST_BIT != HOST_BIT
        WNDCLASSEX_h2g(class32, (WNDCLASSEXW *)wc);
#endif
    }
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
    call.hInstance = (ULONG_PTR)hInstance;
    call.name = (ULONG_PTR)name;
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoExW *c = (struct qemu_GetClassInfoExW *)call;
    WNDCLASSEXW stack, *wc = &stack;
    struct qemu_WNDCLASSEX *class32;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    wc = QEMU_G2H(c->wc);
#else
    class32 = QEMU_G2H(c->wc);
    if (class32)
    {
        if (class32->cbSize == sizeof(*class32))
            wc->cbSize = sizeof(*wc);
        else
            wc->cbSize = 0;
    }
    else
    {
        wc = NULL;
    }
#endif

    c->super.iret = GetClassInfoExW(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), wc);

    if (c->super.iret)
    {
        wc->lpfnWndProc = (void *)wndproc_host_to_guest(wc->lpfnWndProc);
#if GUEST_BIT != HOST_BIT
        WNDCLASSEX_h2g(class32, wc);
#endif
    }
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

LRESULT CALLBACK reverse_wndproc_func(HWND win, UINT msg, WPARAM wp, LPARAM lp, void *data)
{
    struct qemu_call_wndproc call;

    call.super.id = QEMU_SYSCALL_ID(CALL_CALL_WNDPROC);
    call.win = (ULONG_PTR)win;
    call.msg = msg;
    call.wp = (ULONG_PTR)wp;
    call.lp = (ULONG_PTR)lp;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI ULONG_PTR WINAPI GetClassLongPtrA(HWND hwnd, INT offset)
{
    struct qemu_GetClassLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLASSLONGPTRA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassLongPtrA(struct qemu_syscall *call)
{
    struct qemu_GetClassLongPtrA *c = (struct qemu_GetClassLongPtrA *)call;
    HWND win;
    ULONG_PTR module;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;
    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = get_class_wndproc(win, FALSE);
            break;

        case GCLP_HMODULE:
            module = GetClassLongPtrA(win, c->offset);
            c->super.iret = qemu_ops->qemu_module_h2g((HMODULE)module);
            break;

        default:
            c->super.iret = GetClassLongPtrA(win, c->offset);
    }
}

void qemu_call_wndproc(struct qemu_syscall *call)
{
    struct qemu_call_wndproc *c = (struct qemu_call_wndproc *)call;
    struct reverse_wndproc_wrapper *wrapper;
    MSG msg_in = {(HWND)c->win, c->msg, c->wp, c->lp};
    MSG msg_out;

    WINE_TRACE("\n");
    wrapper = QEMU_G2H(c->data);
    WINE_TRACE("Calling function %p from reverse wrapper %p.\n", wrapper->host_proc, wrapper);

    /* A or W? I think it shouldn't matter, we end up here only for an actual function pointer,
     * not for a WNDPROC handle, so Wine doesn't do any conversion anyway. */
    if (wndproc_is_handle((ULONG_PTR)wrapper->host_proc))
        WINE_ERR("Calling a WNDPROC handle via a reverse wrapper.\n");

    /* When the WM_TIMER callback is actually invoked by DispatchMessage, the lparam callback pointer is
     * replaced with the value of GetTickCount(). Do not translate it. */
    if (msg_in.message == WM_TIMER || msg_in.message == WM_SYSTIMER)
        msg_out = msg_in;
    else
        msg_guest_to_host(&msg_out, &msg_in);

    c->super.iret = CallWindowProcW(wrapper->host_proc, msg_out.hwnd, msg_out.message,
            msg_out.wParam, msg_out.lParam);
    msg_guest_to_host_return(&msg_in, &msg_out);

    WINE_TRACE("Returning 0x%lx.\n", (unsigned long)c->super.iret);
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
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClassLongPtrW(struct qemu_syscall *call)
{
    struct qemu_GetClassLongPtrW *c = (struct qemu_GetClassLongPtrW *)call;
    HWND win;
    ULONG_PTR module;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = get_class_wndproc(win, TRUE);
            break;

        case GCLP_HMODULE:
            module = GetClassLongPtrW(win, c->offset);
            c->super.iret = qemu_ops->qemu_module_h2g((HMODULE)module);
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

ULONG_PTR WINAPI user32_SetClassLongPtrW(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetClassLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGPTRW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = (ULONG_PTR)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetClassLongPtrW(struct qemu_syscall *call)
{
    struct qemu_SetClassLongPtrW *c = (struct qemu_SetClassLongPtrW *)call;
    HWND win;
    LONG_PTR mod;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GCLP_WNDPROC:
            c->super.iret = set_class_wndproc(win, TRUE, c->newval);
            break;

        case GCLP_HMODULE:
            if (c->newval)
                c->newval = (ULONG_PTR)qemu_ops->qemu_module_g2h(c->newval);

            c->super.iret = SetClassLongPtrW(win, c->offset, c->newval);
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

ULONG_PTR WINAPI user32_SetClassLongPtrA(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetClassLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCLASSLONGPTRA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = (ULONG_PTR)newval;

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

        case GCLP_HMODULE:
            if (c->newval)
                c->newval = (ULONG_PTR)qemu_ops->qemu_module_g2h(c->newval);

            c->super.iret = SetClassLongPtrA(win, c->offset, c->newval);
            break;

        default:
            c->super.iret = SetClassLongPtrA(win, c->offset, c->newval);
            break;
    }
}

#endif

