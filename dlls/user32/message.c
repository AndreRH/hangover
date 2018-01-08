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
#include <wine/unicode.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_SendMessageTimeoutW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
    uint64_t flags;
    uint64_t timeout;
    uint64_t res_ptr;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendMessageTimeoutW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, UINT flags, UINT timeout, PDWORD_PTR res_ptr)
{
    struct qemu_SendMessageTimeoutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDMESSAGETIMEOUTW);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;
    call.flags = (ULONG_PTR)flags;
    call.timeout = (ULONG_PTR)timeout;
    call.res_ptr = (ULONG_PTR)res_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageTimeoutW(struct qemu_syscall *call)
{
    struct qemu_SendMessageTimeoutW *c = (struct qemu_SendMessageTimeoutW *)call;
    WINE_FIXME("Unverified!\n");

    switch (c->msg)
    {
        case WM_TIMER:
        case WM_SYSTIMER:
            WINE_FIXME("Do I have to fix up WM_TIMER.lParam here?\n");
            break;
    }

    c->super.iret = SendMessageTimeoutW(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam, c->flags, c->timeout, QEMU_G2H(c->res_ptr));
}

#endif

struct qemu_SendMessageTimeoutA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
    uint64_t flags;
    uint64_t timeout;
    uint64_t res_ptr;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendMessageTimeoutA(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, UINT flags, UINT timeout, PDWORD_PTR res_ptr)
{
    struct qemu_SendMessageTimeoutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDMESSAGETIMEOUTA);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;
    call.flags = (ULONG_PTR)flags;
    call.timeout = (ULONG_PTR)timeout;
    call.res_ptr = (ULONG_PTR)res_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageTimeoutA(struct qemu_syscall *call)
{
    struct qemu_SendMessageTimeoutA *c = (struct qemu_SendMessageTimeoutA *)call;
    WINE_FIXME("Unverified!\n");

    switch (c->msg)
    {
        case WM_TIMER:
        case WM_SYSTIMER:
            WINE_FIXME("Do I have to fix up WM_TIMER.lParam here?\n");
            break;
    }

    c->super.iret = SendMessageTimeoutA(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam, c->flags, c->timeout, QEMU_G2H(c->res_ptr));
}

#endif

struct qemu_SendMessageW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendMessageW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_SendMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDMESSAGEW);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageW(struct qemu_syscall *call)
{
    struct qemu_SendMessageW *c = (struct qemu_SendMessageW *)call;
    MSG msg_in;
    MSG msg_out;
    WINE_TRACE("\n");

    msg_in.hwnd = QEMU_G2H(c->hwnd);
    msg_in.message = c->msg;
    msg_in.wParam = c->wparam;
    msg_in.lParam = c->lparam;
    msg_guest_to_host(&msg_out, &msg_in);

    c->super.iret = SendMessageW(msg_out.hwnd, msg_out.message, msg_out.wParam, msg_out.lParam);

    msg_guest_to_host_return(&msg_in, &msg_out);
}

#endif

struct qemu_SendMessageA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendMessageA(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_SendMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDMESSAGEA);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageA(struct qemu_syscall *call)
{
    struct qemu_SendMessageA *c = (struct qemu_SendMessageA *)call;
    MSG msg_in;
    MSG msg_out;
    WINE_TRACE("\n");

    msg_in.hwnd = QEMU_G2H(c->hwnd);
    msg_in.message = c->msg;
    msg_in.wParam = c->wparam;
    msg_in.lParam = c->lparam;
    msg_guest_to_host(&msg_out, &msg_in);

    c->super.iret = SendMessageA(msg_out.hwnd, msg_out.message, msg_out.wParam, msg_out.lParam);

    msg_guest_to_host_return(&msg_in, &msg_out);
}

#endif

struct qemu_SendNotifyMessageA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SendNotifyMessageA(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_SendNotifyMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDNOTIFYMESSAGEA);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendNotifyMessageA(struct qemu_syscall *call)
{
    struct qemu_SendNotifyMessageA *c = (struct qemu_SendNotifyMessageA *)call;
    WINE_TRACE("\n");
    c->super.iret = SendNotifyMessageA(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam);
}

#endif

struct qemu_SendNotifyMessageW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SendNotifyMessageW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_SendNotifyMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDNOTIFYMESSAGEW);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendNotifyMessageW(struct qemu_syscall *call)
{
    struct qemu_SendNotifyMessageW *c = (struct qemu_SendNotifyMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendNotifyMessageW(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam);
}

#endif

struct qemu_SendMessageCallbackA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
    uint64_t callback;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SendMessageCallbackA(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, SENDASYNCPROC callback, ULONG_PTR data)
{
    struct qemu_SendMessageCallbackA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDMESSAGECALLBACKA);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;
    call.callback = (ULONG_PTR)callback;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageCallbackA(struct qemu_syscall *call)
{
    struct qemu_SendMessageCallbackA *c = (struct qemu_SendMessageCallbackA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendMessageCallbackA(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam, QEMU_G2H(c->callback), c->data);
}

#endif

struct qemu_SendMessageCallbackW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
    uint64_t callback;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SendMessageCallbackW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, SENDASYNCPROC callback, ULONG_PTR data)
{
    struct qemu_SendMessageCallbackW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDMESSAGECALLBACKW);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;
    call.callback = (ULONG_PTR)callback;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageCallbackW(struct qemu_syscall *call)
{
    struct qemu_SendMessageCallbackW *c = (struct qemu_SendMessageCallbackW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendMessageCallbackW(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam, QEMU_G2H(c->callback), c->data);
}

#endif

struct qemu_ReplyMessage
{
    struct qemu_syscall super;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ReplyMessage(LRESULT result)
{
    struct qemu_ReplyMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPLYMESSAGE);
    call.result = (ULONG_PTR)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReplyMessage(struct qemu_syscall *call)
{
    struct qemu_ReplyMessage *c = (struct qemu_ReplyMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReplyMessage(c->result);
}

#endif

struct qemu_InSendMessage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InSendMessage(void)
{
    struct qemu_InSendMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INSENDMESSAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InSendMessage(struct qemu_syscall *call)
{
    struct qemu_InSendMessage *c = (struct qemu_InSendMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InSendMessage();
}

#endif

struct qemu_InSendMessageEx
{
    struct qemu_syscall super;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI InSendMessageEx(LPVOID reserved)
{
    struct qemu_InSendMessageEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INSENDMESSAGEEX);
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InSendMessageEx(struct qemu_syscall *call)
{
    struct qemu_InSendMessageEx *c = (struct qemu_InSendMessageEx *)call;
    WINE_TRACE("\n");
    c->super.iret = InSendMessageEx(QEMU_G2H(c->reserved));
}

#endif

struct qemu_PostMessageA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PostMessageA(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_PostMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POSTMESSAGEA);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostMessageA(struct qemu_syscall *call)
{
    struct qemu_PostMessageA *c = (struct qemu_PostMessageA *)call;
    MSG msg_in, msg_out;
    WINE_TRACE("\n");

    msg_in.hwnd = QEMU_G2H(c->hwnd);
    msg_in.message = c->msg;
    msg_in.wParam = c->wparam;
    msg_in.lParam = c->lparam;

    msg_guest_to_host(&msg_out, &msg_in);
    c->super.iret = PostMessageA(msg_out.hwnd, msg_out.message, msg_out.wParam, msg_out.lParam);
    msg_guest_to_host_return(&msg_out, &msg_in);
}

#endif

struct qemu_PostMessageW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PostMessageW(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_PostMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POSTMESSAGEW);
    call.hwnd = (LONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostMessageW(struct qemu_syscall *call)
{
    struct qemu_PostMessageW *c = (struct qemu_PostMessageW *)call;
    MSG msg_in, msg_out;
    WINE_TRACE("\n");

    msg_in.hwnd = QEMU_G2H(c->hwnd);
    msg_in.message = c->msg;
    msg_in.wParam = c->wparam;
    msg_in.lParam = c->lparam;

    msg_guest_to_host(&msg_out, &msg_in);
    c->super.iret = PostMessageW(msg_out.hwnd, msg_out.message, msg_out.wParam, msg_out.lParam);
    msg_guest_to_host_return(&msg_out, &msg_in);
}

#endif

struct qemu_PostThreadMessageA
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PostThreadMessageA(DWORD thread, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_PostThreadMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POSTTHREADMESSAGEA);
    call.thread = (ULONG_PTR)thread;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostThreadMessageA(struct qemu_syscall *call)
{
    struct qemu_PostThreadMessageA *c = (struct qemu_PostThreadMessageA *)call;
    WINE_TRACE("\n");
    c->super.iret = PostThreadMessageA(c->thread, c->msg, c->wparam, c->lparam);
}

#endif

struct qemu_PostThreadMessageW
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t msg;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PostThreadMessageW(DWORD thread, UINT msg, WPARAM wparam, LPARAM lparam)
{
    struct qemu_PostThreadMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POSTTHREADMESSAGEW);
    call.thread = (ULONG_PTR)thread;
    call.msg = (ULONG_PTR)msg;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostThreadMessageW(struct qemu_syscall *call)
{
    struct qemu_PostThreadMessageW *c = (struct qemu_PostThreadMessageW *)call;
    WINE_TRACE("\n");
    c->super.iret = PostThreadMessageW(c->thread, c->msg, c->wparam, c->lparam);
}

#endif

struct qemu_PostQuitMessage
{
    struct qemu_syscall super;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI PostQuitMessage(INT exit_code)
{
    struct qemu_PostQuitMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POSTQUITMESSAGE);
    call.exit_code = (ULONG_PTR)exit_code;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_PostQuitMessage(struct qemu_syscall *call)
{
    struct qemu_PostQuitMessage *c = (struct qemu_PostQuitMessage *)call;
    WINE_TRACE("\n");
    PostQuitMessage(c->exit_code);
}

#endif

struct qemu_PeekMessageW
{
    struct qemu_syscall super;
    uint64_t msg_out;
    uint64_t hwnd;
    uint64_t first;
    uint64_t last;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PeekMessageW(MSG *msg_out, HWND hwnd, UINT first, UINT last, UINT flags)
{
    struct qemu_PeekMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PEEKMESSAGEW);
    call.msg_out = (ULONG_PTR)msg_out;
    call.hwnd = (LONG_PTR)hwnd;
    call.first = (ULONG_PTR)first;
    call.last = (ULONG_PTR)last;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekMessageW(struct qemu_syscall *call)
{
    struct qemu_PeekMessageW *c = (struct qemu_PeekMessageW *)call;
    MSG stack, *msg = &stack;
    WINE_WARN("\n");

#if GUEST_BIT == HOST_BIT
    msg = QEMU_G2H(c->msg_out);
#else
    if (!c->msg_out)
        msg = NULL;
#endif

    c->super.iret = PeekMessageW(msg, QEMU_G2H(c->hwnd), c->first, c->last, c->flags);

#if GUEST_BIT != HOST_BIT
    if (c->msg_out && c->super.iret)
        MSG_h2g(QEMU_G2H(c->msg_out), msg);
#endif

    /* FIXME: I should probably run this through msg_host_to_guest, but if I allocate any
     * helper memory I won't be able to free it. */
}

#endif

struct qemu_PeekMessageA
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t hwnd;
    uint64_t first;
    uint64_t last;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PeekMessageA(MSG *msg, HWND hwnd, UINT first, UINT last, UINT flags)
{
    struct qemu_PeekMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PEEKMESSAGEA);
    call.msg = (ULONG_PTR)msg;
    call.hwnd = (LONG_PTR)hwnd;
    call.first = (ULONG_PTR)first;
    call.last = (ULONG_PTR)last;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekMessageA(struct qemu_syscall *call)
{
    struct qemu_PeekMessageA *c = (struct qemu_PeekMessageA *)call;
    MSG stack, *msg = &stack;
    WINE_WARN("\n");

#if GUEST_BIT == HOST_BIT
    msg = QEMU_G2H(c->msg);
#else
    if (!c->msg)
        msg = NULL;
#endif

    c->super.iret = PeekMessageA(msg, QEMU_G2H(c->hwnd), c->first, c->last, c->flags);

#if GUEST_BIT != HOST_BIT
    if (c->msg && c->super.iret)
        MSG_h2g(QEMU_G2H(c->msg), msg);
#endif

    /* FIXME: I should probably run this through msg_host_to_guest, but if I allocate any
     * helper memory I won't be able to free it. */
}

#endif

struct qemu_GetMessageW
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t hwnd;
    uint64_t first;
    uint64_t last;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMessageW(MSG *msg, HWND hwnd, UINT first, UINT last)
{
    struct qemu_GetMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMESSAGEW);
    call.msg = (ULONG_PTR)msg;
    call.hwnd = (LONG_PTR)hwnd;
    call.first = (ULONG_PTR)first;
    call.last = (ULONG_PTR)last;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessageW(struct qemu_syscall *call)
{
    struct qemu_GetMessageW *c = (struct qemu_GetMessageW *)call;
    MSG stack, *msg = &stack;
    WINE_WARN("\n");

#if GUEST_BIT == HOST_BIT
    msg = QEMU_G2H(c->msg);
#else
    if (!c->msg)
        msg = NULL;
#endif

    c->super.iret = GetMessageW(msg, (HWND)c->hwnd, c->first, c->last);

#if GUEST_BIT != HOST_BIT
    if (c->msg && c->super.iret)
        MSG_h2g(QEMU_G2H(c->msg), msg);
#endif

    /* FIXME: I should probably run this through msg_host_to_guest, but if I allocate any
     * helper memory I won't be able to free it. */
}

#endif

struct qemu_GetMessageA
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t hwnd;
    uint64_t first;
    uint64_t last;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMessageA(MSG *msg, HWND hwnd, UINT first, UINT last)
{
    struct qemu_GetMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMESSAGEA);
    call.msg = (ULONG_PTR)msg;
    call.hwnd = (LONG_PTR)hwnd;
    call.first = (ULONG_PTR)first;
    call.last = (ULONG_PTR)last;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessageA(struct qemu_syscall *call)
{
    struct qemu_GetMessageA *c = (struct qemu_GetMessageA *)call;
    MSG stack, *msg = &stack;
    WINE_WARN("\n");

#if GUEST_BIT == HOST_BIT
    msg = QEMU_G2H(c->msg);
#else
    if (!c->msg)
        msg = NULL;
#endif

    c->super.iret = GetMessageA(msg, (HWND)c->hwnd, c->first, c->last);

#if GUEST_BIT != HOST_BIT
    if (c->msg && c->super.iret)
        MSG_h2g(QEMU_G2H(c->msg), msg);
#endif

    /* FIXME: I should probably run this through msg_host_to_guest, but if I allocate any
     * helper memory I won't be able to free it. */
}

#endif

struct qemu_IsDialogMessageA
{
    struct qemu_syscall super;
    uint64_t hwndDlg;
    uint64_t pmsg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsDialogMessageA(HWND hwndDlg, LPMSG pmsg)
{
    struct qemu_IsDialogMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDIALOGMESSAGEA);
    call.hwndDlg = (LONG_PTR)hwndDlg;
    call.pmsg = (ULONG_PTR)pmsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsDialogMessageA(struct qemu_syscall *call)
{
    struct qemu_IsDialogMessageA *c = (struct qemu_IsDialogMessageA *)call;
    MSG stack, *msg = &stack;
    MSG msg_out;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    msg = QEMU_G2H(c->pmsg);
#else
    MSG_g2h(msg, QEMU_G2H(c->pmsg));
#endif

    msg_guest_to_host(&msg_out, msg);
    c->super.iret = IsDialogMessageA(QEMU_G2H(c->hwndDlg), &msg_out);
    msg_guest_to_host_return(msg, &msg_out);
}

#endif

struct qemu_TranslateMessage
{
    struct qemu_syscall super;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI TranslateMessage(const MSG *msg)
{
    struct qemu_TranslateMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEMESSAGE);
    call.msg = (ULONG_PTR)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateMessage(struct qemu_syscall *call)
{
    struct qemu_TranslateMessage *c = (struct qemu_TranslateMessage *)call;
    MSG stack;
    const MSG *msg = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    msg = QEMU_G2H(c->msg);
#else
    MSG_g2h(&stack, QEMU_G2H(c->msg));
#endif
    c->super.iret = TranslateMessage(msg);
}

#endif

struct qemu_DispatchMessageA
{
    struct qemu_syscall super;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DispatchMessageA(const MSG* msg)
{
    struct qemu_DispatchMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DISPATCHMESSAGEA);
    call.msg = (ULONG_PTR)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DispatchMessageA(struct qemu_syscall *call)
{
    struct qemu_DispatchMessageA *c = (struct qemu_DispatchMessageA *)call;
    MSG stack, *msg_in = &stack;
    MSG msg_out;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    msg_in = QEMU_G2H(c->msg);
#else
    MSG_g2h(msg_in, QEMU_G2H(c->msg));
#endif
    msg_guest_to_host(&msg_out, msg_in);

    c->super.iret = DispatchMessageA(&msg_out);

    msg_guest_to_host_return(msg_in, &msg_out);

#if GUEST_BIT != HOST_BIT
    MSG_h2g(QEMU_G2H(c->msg), msg_in);
#endif
}

#endif

struct qemu_DispatchMessageW
{
    struct qemu_syscall super;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DispatchMessageW(const MSG* msg)
{
    struct qemu_DispatchMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DISPATCHMESSAGEW);
    call.msg = (ULONG_PTR)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DispatchMessageW(struct qemu_syscall *call)
{
    struct qemu_DispatchMessageW *c = (struct qemu_DispatchMessageW *)call;
    MSG stack, *msg_in = &stack;
    MSG msg_out;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    msg_in = QEMU_G2H(c->msg);
#else
    MSG_g2h(msg_in, QEMU_G2H(c->msg));
#endif
    msg_guest_to_host(&msg_out, msg_in);

    c->super.iret = DispatchMessageW(&msg_out);

    msg_guest_to_host_return(msg_in, &msg_out);

#if GUEST_BIT != HOST_BIT
    MSG_h2g(QEMU_G2H(c->msg), msg_in);
#endif
}

#endif

struct qemu_GetMessagePos
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetMessagePos(void)
{
    struct qemu_GetMessagePos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMESSAGEPOS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessagePos(struct qemu_syscall *call)
{
    struct qemu_GetMessagePos *c = (struct qemu_GetMessagePos *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMessagePos();
}

#endif

struct qemu_GetMessageTime
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI GetMessageTime(void)
{
    struct qemu_GetMessageTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMESSAGETIME);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessageTime(struct qemu_syscall *call)
{
    struct qemu_GetMessageTime *c = (struct qemu_GetMessageTime *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMessageTime();
}

#endif

struct qemu_GetMessageExtraInfo
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPARAM WINAPI GetMessageExtraInfo(void)
{
    struct qemu_GetMessageExtraInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMESSAGEEXTRAINFO);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessageExtraInfo(struct qemu_syscall *call)
{
    struct qemu_GetMessageExtraInfo *c = (struct qemu_GetMessageExtraInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMessageExtraInfo();
}

#endif

struct qemu_SetMessageExtraInfo
{
    struct qemu_syscall super;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPARAM WINAPI SetMessageExtraInfo(LPARAM lParam)
{
    struct qemu_SetMessageExtraInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMESSAGEEXTRAINFO);
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMessageExtraInfo(struct qemu_syscall *call)
{
    struct qemu_SetMessageExtraInfo *c = (struct qemu_SetMessageExtraInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMessageExtraInfo(c->lParam);
}

#endif

struct qemu_WaitMessage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI WaitMessage(void)
{
    struct qemu_WaitMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITMESSAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitMessage(struct qemu_syscall *call)
{
    struct qemu_WaitMessage *c = (struct qemu_WaitMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WaitMessage();
}

#endif

struct qemu_MsgWaitForMultipleObjectsEx
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t pHandles;
    uint64_t timeout;
    uint64_t mask;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD count, const HANDLE *pHandles, DWORD timeout, DWORD mask, DWORD flags)
{
    struct qemu_MsgWaitForMultipleObjectsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MSGWAITFORMULTIPLEOBJECTSEX);
    call.count = count;
    call.pHandles = (ULONG_PTR)pHandles;
    call.timeout = timeout;
    call.mask = mask;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MsgWaitForMultipleObjectsEx(struct qemu_syscall *call)
{
    struct qemu_MsgWaitForMultipleObjectsEx *c = (struct qemu_MsgWaitForMultipleObjectsEx *)call;
    WINE_TRACE("\n");
    c->super.iret = MsgWaitForMultipleObjectsEx(c->count, QEMU_G2H(c->pHandles), c->timeout, c->mask, c->flags);
}

#endif

struct qemu_MsgWaitForMultipleObjects
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t handles;
    uint64_t wait_all;
    uint64_t timeout;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI MsgWaitForMultipleObjects(DWORD count, const HANDLE *handles, BOOL wait_all, DWORD timeout, DWORD mask)
{
    struct qemu_MsgWaitForMultipleObjects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MSGWAITFORMULTIPLEOBJECTS);
    call.count = (ULONG_PTR)count;
    call.handles = (ULONG_PTR)handles;
    call.wait_all = (ULONG_PTR)wait_all;
    call.timeout = (ULONG_PTR)timeout;
    call.mask = (ULONG_PTR)mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MsgWaitForMultipleObjects(struct qemu_syscall *call)
{
    struct qemu_MsgWaitForMultipleObjects *c = (struct qemu_MsgWaitForMultipleObjects *)call;
    HANDLE *handles;
    qemu_handle *handles32;
    unsigned int i;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    handles = QEMU_G2H(c->handles);
#else
    handles32 = QEMU_G2H(c->handles);
    handles = HeapAlloc(GetProcessHeap(), 0, c->count);
    for (i = 0; i < c->count; ++i)
        handles[i] = (HANDLE)(LONG_PTR)handles32[i];
#endif

    c->super.iret = MsgWaitForMultipleObjects(c->count, handles, c->wait_all, c->timeout, c->mask);

    if (handles != QEMU_G2H(c->handles))
        HeapFree(GetProcessHeap(), 0, handles);
}

#endif

struct qemu_WaitForInputIdle
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t dwTimeOut;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI WaitForInputIdle(HANDLE hProcess, DWORD dwTimeOut)
{
    struct qemu_WaitForInputIdle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITFORINPUTIDLE);
    call.hProcess = (ULONG_PTR)hProcess;
    call.dwTimeOut = (ULONG_PTR)dwTimeOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitForInputIdle(struct qemu_syscall *call)
{
    struct qemu_WaitForInputIdle *c = (struct qemu_WaitForInputIdle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WaitForInputIdle(QEMU_G2H(c->hProcess), c->dwTimeOut);
}

#endif

struct qemu_RegisterWindowMessageA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI RegisterWindowMessageA(LPCSTR str)
{
    struct qemu_RegisterWindowMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERWINDOWMESSAGEA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterWindowMessageA(struct qemu_syscall *call)
{
    struct qemu_RegisterWindowMessageA *c = (struct qemu_RegisterWindowMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterWindowMessageA(QEMU_G2H(c->str));
}

#endif

struct qemu_RegisterWindowMessageW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI RegisterWindowMessageW(LPCWSTR str)
{
    struct qemu_RegisterWindowMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERWINDOWMESSAGEW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterWindowMessageW(struct qemu_syscall *call)
{
    struct qemu_RegisterWindowMessageW *c = (struct qemu_RegisterWindowMessageW *)call;
    ATOM ret;

    WINE_TRACE("\n");
    ret = RegisterWindowMessageW(QEMU_G2H(c->str));

    if (ret)
    {
        if (!strcmpW(QEMU_G2H(c->str), FINDMSGSTRINGW))
        {
            if (msg_FINDMSGSTRING && msg_FINDMSGSTRING != ret)
                WINE_ERR("FINDMSGSTRINGW already has atom %x, now I got %x.\n",
                        msg_FINDMSGSTRING, ret);
            msg_FINDMSGSTRING = ret;
        }
    }

    c->super.iret = ret;
}

#endif

struct qemu_BroadcastSystemMessageA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t recipients;
    uint64_t msg;
    uint64_t wp;
    uint64_t lp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI BroadcastSystemMessageA(DWORD flags, LPDWORD recipients, UINT msg, WPARAM wp, LPARAM lp)
{
    struct qemu_BroadcastSystemMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BROADCASTSYSTEMMESSAGEA);
    call.flags = (ULONG_PTR)flags;
    call.recipients = (ULONG_PTR)recipients;
    call.msg = (ULONG_PTR)msg;
    call.wp = (ULONG_PTR)wp;
    call.lp = (ULONG_PTR)lp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageA(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageA *c = (struct qemu_BroadcastSystemMessageA *)call;
    WINE_TRACE("\n");
    c->super.iret = BroadcastSystemMessageA(c->flags, QEMU_G2H(c->recipients), c->msg, c->wp, c->lp);
}

#endif

struct qemu_BroadcastSystemMessageW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t recipients;
    uint64_t msg;
    uint64_t wp;
    uint64_t lp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI BroadcastSystemMessageW(DWORD flags, LPDWORD recipients, UINT msg, WPARAM wp, LPARAM lp)
{
    struct qemu_BroadcastSystemMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BROADCASTSYSTEMMESSAGEW);
    call.flags = (ULONG_PTR)flags;
    call.recipients = (ULONG_PTR)recipients;
    call.msg = (ULONG_PTR)msg;
    call.wp = (ULONG_PTR)wp;
    call.lp = (ULONG_PTR)lp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageW(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageW *c = (struct qemu_BroadcastSystemMessageW *)call;
    WINE_TRACE("\n");
    c->super.iret = BroadcastSystemMessageW(c->flags, QEMU_G2H(c->recipients), c->msg, c->wp, c->lp);
}

#endif

struct qemu_BroadcastSystemMessageExA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t recipients;
    uint64_t msg;
    uint64_t wp;
    uint64_t lp;
    uint64_t pinfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI BroadcastSystemMessageExA(DWORD flags, LPDWORD recipients, UINT msg, WPARAM wp, LPARAM lp, PBSMINFO pinfo)
{
    struct qemu_BroadcastSystemMessageExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BROADCASTSYSTEMMESSAGEEXA);
    call.flags = (ULONG_PTR)flags;
    call.recipients = (ULONG_PTR)recipients;
    call.msg = (ULONG_PTR)msg;
    call.wp = (ULONG_PTR)wp;
    call.lp = (ULONG_PTR)lp;
    call.pinfo = (ULONG_PTR)pinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageExA(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageExA *c = (struct qemu_BroadcastSystemMessageExA *)call;
    WINE_TRACE("\n");
    c->super.iret = BroadcastSystemMessageExA(c->flags, QEMU_G2H(c->recipients), c->msg, c->wp, c->lp, QEMU_G2H(c->pinfo));
}

#endif

struct qemu_BroadcastSystemMessageExW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t recipients;
    uint64_t msg;
    uint64_t wp;
    uint64_t lp;
    uint64_t pinfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI BroadcastSystemMessageExW(DWORD flags, LPDWORD recipients, UINT msg, WPARAM wp, LPARAM lp, PBSMINFO pinfo)
{
    struct qemu_BroadcastSystemMessageExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BROADCASTSYSTEMMESSAGEEXW);
    call.flags = (ULONG_PTR)flags;
    call.recipients = (ULONG_PTR)recipients;
    call.msg = (ULONG_PTR)msg;
    call.wp = (ULONG_PTR)wp;
    call.lp = (ULONG_PTR)lp;
    call.pinfo = (ULONG_PTR)pinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageExW(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageExW *c = (struct qemu_BroadcastSystemMessageExW *)call;
    WINE_TRACE("\n");
    c->super.iret = BroadcastSystemMessageExW(c->flags, QEMU_G2H(c->recipients), c->msg, c->wp, c->lp, QEMU_G2H(c->pinfo));
}

#endif

struct qemu_SetMessageQueue
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMessageQueue(INT size)
{
    struct qemu_SetMessageQueue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMESSAGEQUEUE);
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMessageQueue(struct qemu_syscall *call)
{
    struct qemu_SetMessageQueue *c = (struct qemu_SetMessageQueue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMessageQueue(c->size);
}

#endif

struct qemu_MessageBeep
{
    struct qemu_syscall super;
    uint64_t i;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI MessageBeep(UINT i)
{
    struct qemu_MessageBeep call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBEEP);
    call.i = (ULONG_PTR)i;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBeep(struct qemu_syscall *call)
{
    struct qemu_MessageBeep *c = (struct qemu_MessageBeep *)call;
    WINE_TRACE("\n");
    c->super.iret = MessageBeep(c->i);
}

#endif

struct qemu_SetCoalescableTimer
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t timeout;
    uint64_t proc;
    uint64_t tolerance;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT_PTR WINAPI SetCoalescableTimer(HWND hwnd, UINT_PTR id, UINT timeout, TIMERPROC proc, ULONG tolerance)
{
    struct qemu_SetCoalescableTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOALESCABLETIMER);
    call.hwnd = (LONG_PTR)hwnd;
    call.id = (ULONG_PTR)id;
    call.timeout = (ULONG_PTR)timeout;
    call.proc = (ULONG_PTR)proc;
    call.tolerance = (ULONG_PTR)tolerance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCoalescableTimer(struct qemu_syscall *call)
{
    struct qemu_SetCoalescableTimer *c = (struct qemu_SetCoalescableTimer *)call;
    TIMERPROC proc;

    WINE_TRACE("\n");
    proc = (TIMERPROC)wndproc_guest_to_host(c->proc);

    c->super.iret = SetCoalescableTimer(QEMU_G2H(c->hwnd), c->id, c->timeout, proc, c->tolerance);
}

#endif

struct qemu_SetTimer
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t timeout;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT_PTR WINAPI SetTimer(HWND hwnd, UINT_PTR id, UINT timeout, TIMERPROC proc)
{
    struct qemu_SetTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTIMER);
    call.hwnd = (LONG_PTR)hwnd;
    call.id = (ULONG_PTR)id;
    call.timeout = (ULONG_PTR)timeout;
    call.proc = (ULONG_PTR)proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTimer(struct qemu_syscall *call)
{
    struct qemu_SetTimer *c = (struct qemu_SetTimer *)call;
    TIMERPROC proc;

    WINE_TRACE("\n");
    proc = (TIMERPROC)wndproc_guest_to_host(c->proc);

    c->super.iret = SetTimer(QEMU_G2H(c->hwnd), c->id, c->timeout, proc);
}

#endif

struct qemu_SetSystemTimer
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
    uint64_t timeout;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT_PTR WINAPI SetSystemTimer(HWND hwnd, UINT_PTR id, UINT timeout, TIMERPROC proc)
{
    struct qemu_SetSystemTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSTEMTIMER);
    call.hwnd = (LONG_PTR)hwnd;
    call.id = (ULONG_PTR)id;
    call.timeout = (ULONG_PTR)timeout;
    call.proc = (ULONG_PTR)proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSystemTimer(struct qemu_syscall *call)
{
    struct qemu_SetSystemTimer *c = (struct qemu_SetSystemTimer *)call;
    TIMERPROC proc;

    WINE_FIXME("Unverified!\n");
    proc = (TIMERPROC)wndproc_guest_to_host(c->proc);

    c->super.iret = SetSystemTimer(QEMU_G2H(c->hwnd), c->id, c->timeout, proc);
}

#endif

struct qemu_KillTimer
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI KillTimer(HWND hwnd, UINT_PTR id)
{
    struct qemu_KillTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_KILLTIMER);
    call.hwnd = (LONG_PTR)hwnd;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_KillTimer(struct qemu_syscall *call)
{
    struct qemu_KillTimer *c = (struct qemu_KillTimer *)call;
    WINE_TRACE("\n");
    c->super.iret = KillTimer(QEMU_G2H(c->hwnd), c->id);
}

#endif

struct qemu_KillSystemTimer
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI KillSystemTimer(HWND hwnd, UINT_PTR id)
{
    struct qemu_KillSystemTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_KILLSYSTEMTIMER);
    call.hwnd = (LONG_PTR)hwnd;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_KillSystemTimer(struct qemu_syscall *call)
{
    struct qemu_KillSystemTimer *c = (struct qemu_KillSystemTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = KillSystemTimer(QEMU_G2H(c->hwnd), c->id);
}

#endif

struct qemu_IsGUIThread
{
    struct qemu_syscall super;
    uint64_t convert;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsGUIThread(BOOL convert)
{
    struct qemu_IsGUIThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISGUITHREAD);
    call.convert = (ULONG_PTR)convert;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsGUIThread(struct qemu_syscall *call)
{
    struct qemu_IsGUIThread *c = (struct qemu_IsGUIThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsGUIThread(c->convert);
}

#endif

struct qemu_GetGUIThreadInfo
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetGUIThreadInfo(DWORD id, GUITHREADINFO *info)
{
    struct qemu_GetGUIThreadInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGUITHREADINFO);
    call.id = (ULONG_PTR)id;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGUIThreadInfo(struct qemu_syscall *call)
{
    struct qemu_GetGUIThreadInfo *c = (struct qemu_GetGUIThreadInfo *)call;
    GUITHREADINFO stack, *info = &stack;
    struct qemu_GUITHREADINFO *info32;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->info);
#else
    info32 = QEMU_G2H(c->info);
    if (info32)
    {
        if (info32->cbSize == sizeof(*info32))
            info->cbSize = sizeof(*info);
        else
            info->cbSize = 0;
    }
    else
    {
        info = NULL;
    }
#endif

    c->super.iret = GetGUIThreadInfo(c->id, info);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret && info)
        GUITHREADINFO_h2g(info32, info);
#endif
}

#endif

struct qemu_IsHungAppWindow
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsHungAppWindow(HWND hWnd)
{
    struct qemu_IsHungAppWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISHUNGAPPWINDOW);
    call.hWnd = (LONG_PTR)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsHungAppWindow(struct qemu_syscall *call)
{
    struct qemu_IsHungAppWindow *c = (struct qemu_IsHungAppWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsHungAppWindow(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_ChangeWindowMessageFilter
{
    struct qemu_syscall super;
    uint64_t message;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ChangeWindowMessageFilter(UINT message, DWORD flag)
{
    struct qemu_ChangeWindowMessageFilter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEWINDOWMESSAGEFILTER);
    call.message = (ULONG_PTR)message;
    call.flag = (ULONG_PTR)flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeWindowMessageFilter(struct qemu_syscall *call)
{
    struct qemu_ChangeWindowMessageFilter *c = (struct qemu_ChangeWindowMessageFilter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeWindowMessageFilter(c->message, c->flag);
}

#endif

struct qemu_ChangeWindowMessageFilterEx
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t message;
    uint64_t action;
    uint64_t changefilter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChangeWindowMessageFilterEx(HWND hwnd, UINT message, DWORD action, CHANGEFILTERSTRUCT *changefilter)
{
    struct qemu_ChangeWindowMessageFilterEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEWINDOWMESSAGEFILTEREX);
    call.hwnd = (LONG_PTR)hwnd;
    call.message = message;
    call.action = action;
    call.changefilter = (ULONG_PTR)changefilter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeWindowMessageFilterEx(struct qemu_syscall *call)
{
    struct qemu_ChangeWindowMessageFilterEx *c = (struct qemu_ChangeWindowMessageFilterEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeWindowMessageFilterEx(QEMU_G2H(c->hwnd), c->message, c->action, QEMU_G2H(c->changefilter));
}

#endif
