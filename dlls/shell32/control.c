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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_Control_RunDLLW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmd;
    uint64_t nCmdShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI Control_RunDLLW(HWND hWnd, HINSTANCE hInst, LPCWSTR cmd, DWORD nCmdShow)
{
    struct qemu_Control_RunDLLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROL_RUNDLLW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmd = (ULONG_PTR)cmd;
    call.nCmdShow = nCmdShow;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add Control_RunDLLW to Wine headers? */
extern void WINAPI Control_RunDLLW(HWND hWnd, HINSTANCE hInst, LPCWSTR cmd, DWORD nCmdShow);
void qemu_Control_RunDLLW(struct qemu_syscall *call)
{
    struct qemu_Control_RunDLLW *c = (struct qemu_Control_RunDLLW *)call;
    WINE_FIXME("Unverified!\n");
    Control_RunDLLW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmd), c->nCmdShow);
}

#endif

struct qemu_Control_RunDLLA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmd;
    uint64_t nCmdShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI Control_RunDLLA(HWND hWnd, HINSTANCE hInst, LPCSTR cmd, DWORD nCmdShow)
{
    struct qemu_Control_RunDLLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROL_RUNDLLA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmd = (ULONG_PTR)cmd;
    call.nCmdShow = nCmdShow;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add Control_RunDLLA to Wine headers? */
extern void WINAPI Control_RunDLLA(HWND hWnd, HINSTANCE hInst, LPCSTR cmd, DWORD nCmdShow);
void qemu_Control_RunDLLA(struct qemu_syscall *call)
{
    struct qemu_Control_RunDLLA *c = (struct qemu_Control_RunDLLA *)call;
    WINE_FIXME("Unverified!\n");
    Control_RunDLLA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmd), c->nCmdShow);
}

#endif

struct qemu_Control_FillCache_RunDLLW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hModule;
    uint64_t w;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI Control_FillCache_RunDLLW(HWND hWnd, HANDLE hModule, DWORD w, DWORD x)
{
    struct qemu_Control_FillCache_RunDLLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROL_FILLCACHE_RUNDLLW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hModule = (ULONG_PTR)hModule;
    call.w = w;
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add Control_FillCache_RunDLLW to Wine headers? */
extern HRESULT WINAPI Control_FillCache_RunDLLW(HWND hWnd, HANDLE hModule, DWORD w, DWORD x);
void qemu_Control_FillCache_RunDLLW(struct qemu_syscall *call)
{
    struct qemu_Control_FillCache_RunDLLW *c = (struct qemu_Control_FillCache_RunDLLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Control_FillCache_RunDLLW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hModule), c->w, c->x);
}

#endif

struct qemu_Control_FillCache_RunDLLA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hModule;
    uint64_t w;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI Control_FillCache_RunDLLA(HWND hWnd, HANDLE hModule, DWORD w, DWORD x)
{
    struct qemu_Control_FillCache_RunDLLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROL_FILLCACHE_RUNDLLA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hModule = (ULONG_PTR)hModule;
    call.w = w;
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add Control_FillCache_RunDLLA to Wine headers? */
extern HRESULT WINAPI Control_FillCache_RunDLLA(HWND hWnd, HANDLE hModule, DWORD w, DWORD x);
void qemu_Control_FillCache_RunDLLA(struct qemu_syscall *call)
{
    struct qemu_Control_FillCache_RunDLLA *c = (struct qemu_Control_FillCache_RunDLLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Control_FillCache_RunDLLA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hModule), c->w, c->x);
}

#endif

struct qemu_CallCPLEntry16
{
    struct qemu_syscall super;
    uint64_t hMod;
    uint64_t pFunc;
    uint64_t dw3;
    uint64_t dw4;
    uint64_t dw5;
    uint64_t dw6;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CallCPLEntry16(HMODULE hMod, FARPROC pFunc, DWORD dw3, DWORD dw4, DWORD dw5, DWORD dw6)
{
    struct qemu_CallCPLEntry16 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLCPLENTRY16);
    call.hMod = (ULONG_PTR)hMod;
    call.pFunc = (ULONG_PTR)pFunc;
    call.dw3 = dw3;
    call.dw4 = dw4;
    call.dw5 = dw5;
    call.dw6 = dw6;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CallCPLEntry16 to Wine headers? */
extern DWORD WINAPI CallCPLEntry16(HMODULE hMod, FARPROC pFunc, DWORD dw3, DWORD dw4, DWORD dw5, DWORD dw6);
void qemu_CallCPLEntry16(struct qemu_syscall *call)
{
    struct qemu_CallCPLEntry16 *c = (struct qemu_CallCPLEntry16 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallCPLEntry16(QEMU_G2H(c->hMod), QEMU_G2H(c->pFunc), c->dw3, c->dw4, c->dw5, c->dw6);
}

#endif

