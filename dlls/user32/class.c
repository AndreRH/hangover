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
        exw.lpfnWndProc = (WNDPROC)&class_wrappers[i];
        if (!exw.hInstance)
            exw.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

        c->super.iret = RegisterClassExW(&exw);
    }
    else
    {
        WNDCLASSEXA exa = *(WNDCLASSEXA *)QEMU_G2H(c->wc);

        guest_proc = (uint64_t)exa.lpfnWndProc;
        exa.lpfnWndProc = (WNDPROC)&class_wrappers[i];
        if (!exa.hInstance)
            exa.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

        c->super.iret = RegisterClassExA(&exa);
    }

    if (c->super.iret)
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
    WINE_TRACE("\n");

    inst = (HINSTANCE)c->hInstance;
    if (!inst)
        inst = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    if (c->super.id == QEMU_SYSCALL_ID(CALL_UNREGISTERCLASSA))
    {
        WNDCLASSEXA info;
        atom = GetClassInfoExA(QEMU_G2H(c->hInstance), QEMU_G2H(c->className), &info);
        c->super.iret = UnregisterClassA(QEMU_G2H(c->className), inst);
    }
    else
    {
        WNDCLASSEXW info;
        atom = GetClassInfoExW(QEMU_G2H(c->hInstance), QEMU_G2H(c->className), &info);
        c->super.iret = UnregisterClassW(QEMU_G2H(c->className), inst);
    }

    if (c->super.iret)
    {
        for (i = 0; i < class_wrapper_count; ++i)
        {
            if (!class_wrappers[i].atom == atom)
            {
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

void qemu_GetClassInfoA(struct qemu_syscall *call)
{
    struct qemu_GetClassInfoA *c = (struct qemu_GetClassInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassInfoA(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), QEMU_G2H(c->wc));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassInfoW(QEMU_G2H(c->hInstance), QEMU_G2H(c->name), QEMU_G2H(c->wc));
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

#ifdef QEMU_DLL_GUEST

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

void qemu_GetClassLongPtrA(struct qemu_syscall *call)
{
    struct qemu_GetClassLongPtrA *c = (struct qemu_GetClassLongPtrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassLongPtrA(QEMU_G2H(c->hwnd), c->offset);
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetClassLongPtrW(QEMU_G2H(c->hwnd), c->offset);
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

void qemu_SetClassLongPtrW(struct qemu_syscall *call)
{
    struct qemu_SetClassLongPtrW *c = (struct qemu_SetClassLongPtrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetClassLongPtrW(QEMU_G2H(c->hwnd), c->offset, c->newval);
}

#endif

struct qemu_SetClassLongPtrA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
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
    struct qemu_SetClassLongPtrA *c = (struct qemu_SetClassLongPtrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetClassLongPtrA(QEMU_G2H(c->hwnd), c->offset, c->newval);
}

#endif

