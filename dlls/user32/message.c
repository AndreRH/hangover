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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;
    call.flags = (uint64_t)flags;
    call.timeout = (uint64_t)timeout;
    call.res_ptr = (uint64_t)res_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageTimeoutW(struct qemu_syscall *call)
{
    struct qemu_SendMessageTimeoutW *c = (struct qemu_SendMessageTimeoutW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;
    call.flags = (uint64_t)flags;
    call.timeout = (uint64_t)timeout;
    call.res_ptr = (uint64_t)res_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageTimeoutA(struct qemu_syscall *call)
{
    struct qemu_SendMessageTimeoutA *c = (struct qemu_SendMessageTimeoutA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageW(struct qemu_syscall *call)
{
    struct qemu_SendMessageW *c = (struct qemu_SendMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendMessageW(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam);
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendMessageA(struct qemu_syscall *call)
{
    struct qemu_SendMessageA *c = (struct qemu_SendMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendMessageA(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam);
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendNotifyMessageA(struct qemu_syscall *call)
{
    struct qemu_SendNotifyMessageA *c = (struct qemu_SendNotifyMessageA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;
    call.callback = (uint64_t)callback;
    call.data = (uint64_t)data;

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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;
    call.callback = (uint64_t)callback;
    call.data = (uint64_t)data;

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
    call.result = (uint64_t)result;

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
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InSendMessageEx(struct qemu_syscall *call)
{
    struct qemu_InSendMessageEx *c = (struct qemu_InSendMessageEx *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostMessageA(struct qemu_syscall *call)
{
    struct qemu_PostMessageA *c = (struct qemu_PostMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PostMessageA(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam);
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
    call.hwnd = (uint64_t)hwnd;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostMessageW(struct qemu_syscall *call)
{
    struct qemu_PostMessageW *c = (struct qemu_PostMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PostMessageW(QEMU_G2H(c->hwnd), c->msg, c->wparam, c->lparam);
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
    call.thread = (uint64_t)thread;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostThreadMessageA(struct qemu_syscall *call)
{
    struct qemu_PostThreadMessageA *c = (struct qemu_PostThreadMessageA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.thread = (uint64_t)thread;
    call.msg = (uint64_t)msg;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PostThreadMessageW(struct qemu_syscall *call)
{
    struct qemu_PostThreadMessageW *c = (struct qemu_PostThreadMessageW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.exit_code = (uint64_t)exit_code;

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
    call.msg_out = (uint64_t)msg_out;
    call.hwnd = (uint64_t)hwnd;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekMessageW(struct qemu_syscall *call)
{
    struct qemu_PeekMessageW *c = (struct qemu_PeekMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PeekMessageW(QEMU_G2H(c->msg_out), QEMU_G2H(c->hwnd), c->first, c->last, c->flags);
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
    call.msg = (uint64_t)msg;
    call.hwnd = (uint64_t)hwnd;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekMessageA(struct qemu_syscall *call)
{
    struct qemu_PeekMessageA *c = (struct qemu_PeekMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PeekMessageA(QEMU_G2H(c->msg), QEMU_G2H(c->hwnd), c->first, c->last, c->flags);
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
    call.msg = (uint64_t)msg;
    call.hwnd = (uint64_t)hwnd;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessageW(struct qemu_syscall *call)
{
    struct qemu_GetMessageW *c = (struct qemu_GetMessageW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMessageW(QEMU_G2H(c->msg), (HWND)c->hwnd, c->first, c->last);
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
    call.msg = (uint64_t)msg;
    call.hwnd = (uint64_t)hwnd;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMessageA(struct qemu_syscall *call)
{
    struct qemu_GetMessageA *c = (struct qemu_GetMessageA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMessageA(QEMU_G2H(c->msg), (HWND)c->hwnd, c->first, c->last);
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
    call.hwndDlg = (uint64_t)hwndDlg;
    call.pmsg = (uint64_t)pmsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsDialogMessageA(struct qemu_syscall *call)
{
    struct qemu_IsDialogMessageA *c = (struct qemu_IsDialogMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsDialogMessageA(QEMU_G2H(c->hwndDlg), QEMU_G2H(c->pmsg));
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
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateMessage(struct qemu_syscall *call)
{
    struct qemu_TranslateMessage *c = (struct qemu_TranslateMessage *)call;
    WINE_TRACE("\n");
    c->super.iret = TranslateMessage(QEMU_G2H(c->msg));
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
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DispatchMessageA(struct qemu_syscall *call)
{
    struct qemu_DispatchMessageA *c = (struct qemu_DispatchMessageA *)call;
    WINE_TRACE("\n");
    c->super.iret = DispatchMessageA(QEMU_G2H(c->msg));
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
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DispatchMessageW(struct qemu_syscall *call)
{
    struct qemu_DispatchMessageW *c = (struct qemu_DispatchMessageW *)call;
    WINE_TRACE("\n");
    c->super.iret = DispatchMessageW(QEMU_G2H(c->msg));
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
    WINE_FIXME("Unverified!\n");
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
    WINE_FIXME("Unverified!\n");
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
    call.lParam = (uint64_t)lParam;

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
    call.count = (uint64_t)count;
    call.pHandles = (uint64_t)pHandles;
    call.timeout = (uint64_t)timeout;
    call.mask = (uint64_t)mask;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MsgWaitForMultipleObjectsEx(struct qemu_syscall *call)
{
    struct qemu_MsgWaitForMultipleObjectsEx *c = (struct qemu_MsgWaitForMultipleObjectsEx *)call;
    WINE_FIXME("Unverified!\n");
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
    call.count = (uint64_t)count;
    call.handles = (uint64_t)handles;
    call.wait_all = (uint64_t)wait_all;
    call.timeout = (uint64_t)timeout;
    call.mask = (uint64_t)mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MsgWaitForMultipleObjects(struct qemu_syscall *call)
{
    struct qemu_MsgWaitForMultipleObjects *c = (struct qemu_MsgWaitForMultipleObjects *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MsgWaitForMultipleObjects(c->count, QEMU_G2H(c->handles), c->wait_all, c->timeout, c->mask);
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
    call.hProcess = (uint64_t)hProcess;
    call.dwTimeOut = (uint64_t)dwTimeOut;

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
    call.str = (uint64_t)str;

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
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegisterWindowMessageW(struct qemu_syscall *call)
{
    struct qemu_RegisterWindowMessageW *c = (struct qemu_RegisterWindowMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterWindowMessageW(QEMU_G2H(c->str));
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
    call.flags = (uint64_t)flags;
    call.recipients = (uint64_t)recipients;
    call.msg = (uint64_t)msg;
    call.wp = (uint64_t)wp;
    call.lp = (uint64_t)lp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageA(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageA *c = (struct qemu_BroadcastSystemMessageA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.flags = (uint64_t)flags;
    call.recipients = (uint64_t)recipients;
    call.msg = (uint64_t)msg;
    call.wp = (uint64_t)wp;
    call.lp = (uint64_t)lp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageW(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageW *c = (struct qemu_BroadcastSystemMessageW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.flags = (uint64_t)flags;
    call.recipients = (uint64_t)recipients;
    call.msg = (uint64_t)msg;
    call.wp = (uint64_t)wp;
    call.lp = (uint64_t)lp;
    call.pinfo = (uint64_t)pinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageExA(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageExA *c = (struct qemu_BroadcastSystemMessageExA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.flags = (uint64_t)flags;
    call.recipients = (uint64_t)recipients;
    call.msg = (uint64_t)msg;
    call.wp = (uint64_t)wp;
    call.lp = (uint64_t)lp;
    call.pinfo = (uint64_t)pinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BroadcastSystemMessageExW(struct qemu_syscall *call)
{
    struct qemu_BroadcastSystemMessageExW *c = (struct qemu_BroadcastSystemMessageExW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.size = (uint64_t)size;

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
    call.i = (uint64_t)i;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBeep(struct qemu_syscall *call)
{
    struct qemu_MessageBeep *c = (struct qemu_MessageBeep *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.timeout = (uint64_t)timeout;
    call.proc = (uint64_t)proc;
    call.tolerance = (uint64_t)tolerance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCoalescableTimer(struct qemu_syscall *call)
{
    struct qemu_SetCoalescableTimer *c = (struct qemu_SetCoalescableTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCoalescableTimer(QEMU_G2H(c->hwnd), c->id, c->timeout, QEMU_G2H(c->proc), c->tolerance);
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
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.timeout = (uint64_t)timeout;
    call.proc = (uint64_t)proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTimer(struct qemu_syscall *call)
{
    struct qemu_SetTimer *c = (struct qemu_SetTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetTimer(QEMU_G2H(c->hwnd), c->id, c->timeout, QEMU_G2H(c->proc));
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
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;
    call.timeout = (uint64_t)timeout;
    call.proc = (uint64_t)proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSystemTimer(struct qemu_syscall *call)
{
    struct qemu_SetSystemTimer *c = (struct qemu_SetSystemTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSystemTimer(QEMU_G2H(c->hwnd), c->id, c->timeout, QEMU_G2H(c->proc));
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
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_KillTimer(struct qemu_syscall *call)
{
    struct qemu_KillTimer *c = (struct qemu_KillTimer *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;

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
    call.convert = (uint64_t)convert;

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
    call.id = (uint64_t)id;
    call.info = (uint64_t)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGUIThreadInfo(struct qemu_syscall *call)
{
    struct qemu_GetGUIThreadInfo *c = (struct qemu_GetGUIThreadInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetGUIThreadInfo(c->id, QEMU_G2H(c->info));
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
    call.hWnd = (uint64_t)hWnd;

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
    call.message = (uint64_t)message;
    call.flag = (uint64_t)flag;

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

