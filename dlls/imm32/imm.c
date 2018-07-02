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
#ifdef QEMU_DLL_GUEST
#include <dimm.h>
#else
#include <ddk/imm.h>
#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_imm32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_imm32);
#endif

struct qemu_ImmAssociateContext
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMC WINAPI ImmAssociateContext(HWND hWnd, HIMC hIMC)
{
    struct qemu_ImmAssociateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMASSOCIATECONTEXT);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return (HIMC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmAssociateContext(struct qemu_syscall *call)
{
    struct qemu_ImmAssociateContext *c = (struct qemu_ImmAssociateContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmAssociateContext(QEMU_G2H(c->hWnd), QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmAssociateContextEx
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hIMC;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmAssociateContextEx(HWND hWnd, HIMC hIMC, DWORD dwFlags)
{
    struct qemu_ImmAssociateContextEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMASSOCIATECONTEXTEX);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmAssociateContextEx(struct qemu_syscall *call)
{
    struct qemu_ImmAssociateContextEx *c = (struct qemu_ImmAssociateContextEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmAssociateContextEx(QEMU_G2H(c->hWnd), QEMU_G2H(c->hIMC), c->dwFlags);
}

#endif

struct qemu_ImmConfigureIMEA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t hWnd;
    uint64_t dwMode;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmConfigureIMEA(HKL hKL, HWND hWnd, DWORD dwMode, LPVOID lpData)
{
    struct qemu_ImmConfigureIMEA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMCONFIGUREIMEA);
    call.hKL = (ULONG_PTR)hKL;
    call.hWnd = (ULONG_PTR)hWnd;
    call.dwMode = (ULONG_PTR)dwMode;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmConfigureIMEA(struct qemu_syscall *call)
{
    struct qemu_ImmConfigureIMEA *c = (struct qemu_ImmConfigureIMEA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmConfigureIMEA(QEMU_G2H(c->hKL), QEMU_G2H(c->hWnd), c->dwMode, QEMU_G2H(c->lpData));
}

#endif

struct qemu_ImmConfigureIMEW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t hWnd;
    uint64_t dwMode;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmConfigureIMEW(HKL hKL, HWND hWnd, DWORD dwMode, LPVOID lpData)
{
    struct qemu_ImmConfigureIMEW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMCONFIGUREIMEW);
    call.hKL = (ULONG_PTR)hKL;
    call.hWnd = (ULONG_PTR)hWnd;
    call.dwMode = (ULONG_PTR)dwMode;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmConfigureIMEW(struct qemu_syscall *call)
{
    struct qemu_ImmConfigureIMEW *c = (struct qemu_ImmConfigureIMEW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmConfigureIMEW(QEMU_G2H(c->hKL), QEMU_G2H(c->hWnd), c->dwMode, QEMU_G2H(c->lpData));
}

#endif

struct qemu_ImmCreateContext
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMC WINAPI ImmCreateContext(void)
{
    struct qemu_ImmCreateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMCREATECONTEXT);

    qemu_syscall(&call.super);

    return (HIMC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmCreateContext(struct qemu_syscall *call)
{
    struct qemu_ImmCreateContext *c = (struct qemu_ImmCreateContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmCreateContext();
}

#endif

struct qemu_ImmDestroyContext
{
    struct qemu_syscall super;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmDestroyContext(HIMC hIMC)
{
    struct qemu_ImmDestroyContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMDESTROYCONTEXT);
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmDestroyContext(struct qemu_syscall *call)
{
    struct qemu_ImmDestroyContext *c = (struct qemu_ImmDestroyContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmDestroyContext(QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmDisableIME
{
    struct qemu_syscall super;
    uint64_t idThread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmDisableIME(DWORD idThread)
{
    struct qemu_ImmDisableIME call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMDISABLEIME);
    call.idThread = (ULONG_PTR)idThread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmDisableIME(struct qemu_syscall *call)
{
    struct qemu_ImmDisableIME *c = (struct qemu_ImmDisableIME *)call;
    WINE_TRACE("\n");
    c->super.iret = ImmDisableIME(c->idThread);
}

#endif

struct qemu_ImmEnumRegisterWordA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpfnEnumProc;
    uint64_t lpszReading;
    uint64_t dwStyle;
    uint64_t lpszRegister;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmEnumRegisterWordA(HKL hKL, REGISTERWORDENUMPROCA lpfnEnumProc, LPCSTR lpszReading, DWORD dwStyle, LPCSTR lpszRegister, LPVOID lpData)
{
    struct qemu_ImmEnumRegisterWordA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMENUMREGISTERWORDA);
    call.hKL = (ULONG_PTR)hKL;
    call.lpfnEnumProc = (ULONG_PTR)lpfnEnumProc;
    call.lpszReading = (ULONG_PTR)lpszReading;
    call.dwStyle = (ULONG_PTR)dwStyle;
    call.lpszRegister = (ULONG_PTR)lpszRegister;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmEnumRegisterWordA(struct qemu_syscall *call)
{
    struct qemu_ImmEnumRegisterWordA *c = (struct qemu_ImmEnumRegisterWordA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmEnumRegisterWordA(QEMU_G2H(c->hKL), QEMU_G2H(c->lpfnEnumProc), QEMU_G2H(c->lpszReading), c->dwStyle, QEMU_G2H(c->lpszRegister), QEMU_G2H(c->lpData));
}

#endif

struct qemu_ImmEnumRegisterWordW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpfnEnumProc;
    uint64_t lpszReading;
    uint64_t dwStyle;
    uint64_t lpszRegister;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmEnumRegisterWordW(HKL hKL, REGISTERWORDENUMPROCW lpfnEnumProc, LPCWSTR lpszReading, DWORD dwStyle, LPCWSTR lpszRegister, LPVOID lpData)
{
    struct qemu_ImmEnumRegisterWordW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMENUMREGISTERWORDW);
    call.hKL = (ULONG_PTR)hKL;
    call.lpfnEnumProc = (ULONG_PTR)lpfnEnumProc;
    call.lpszReading = (ULONG_PTR)lpszReading;
    call.dwStyle = (ULONG_PTR)dwStyle;
    call.lpszRegister = (ULONG_PTR)lpszRegister;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmEnumRegisterWordW(struct qemu_syscall *call)
{
    struct qemu_ImmEnumRegisterWordW *c = (struct qemu_ImmEnumRegisterWordW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmEnumRegisterWordW(QEMU_G2H(c->hKL), QEMU_G2H(c->lpfnEnumProc), QEMU_G2H(c->lpszReading), c->dwStyle, QEMU_G2H(c->lpszRegister), QEMU_G2H(c->lpData));
}

#endif

struct qemu_ImmEscapeA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t hIMC;
    uint64_t uEscape;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI ImmEscapeA(HKL hKL, HIMC hIMC, UINT uEscape, LPVOID lpData)
{
    struct qemu_ImmEscapeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMESCAPEA);
    call.hKL = (ULONG_PTR)hKL;
    call.hIMC = (ULONG_PTR)hIMC;
    call.uEscape = (ULONG_PTR)uEscape;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmEscapeA(struct qemu_syscall *call)
{
    struct qemu_ImmEscapeA *c = (struct qemu_ImmEscapeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmEscapeA(QEMU_G2H(c->hKL), QEMU_G2H(c->hIMC), c->uEscape, QEMU_G2H(c->lpData));
}

#endif

struct qemu_ImmEscapeW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t hIMC;
    uint64_t uEscape;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI ImmEscapeW(HKL hKL, HIMC hIMC, UINT uEscape, LPVOID lpData)
{
    struct qemu_ImmEscapeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMESCAPEW);
    call.hKL = (ULONG_PTR)hKL;
    call.hIMC = (ULONG_PTR)hIMC;
    call.uEscape = (ULONG_PTR)uEscape;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmEscapeW(struct qemu_syscall *call)
{
    struct qemu_ImmEscapeW *c = (struct qemu_ImmEscapeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmEscapeW(QEMU_G2H(c->hKL), QEMU_G2H(c->hIMC), c->uEscape, QEMU_G2H(c->lpData));
}

#endif

struct qemu_ImmGetCandidateListA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpCandList;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetCandidateListA(HIMC hIMC, DWORD dwIndex, LPCANDIDATELIST lpCandList, DWORD dwBufLen)
{
    struct qemu_ImmGetCandidateListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCANDIDATELISTA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpCandList = (ULONG_PTR)lpCandList;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCandidateListA(struct qemu_syscall *call)
{
    struct qemu_ImmGetCandidateListA *c = (struct qemu_ImmGetCandidateListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCandidateListA(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpCandList), c->dwBufLen);
}

#endif

struct qemu_ImmGetCandidateListCountA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpdwListCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetCandidateListCountA(HIMC hIMC, LPDWORD lpdwListCount)
{
    struct qemu_ImmGetCandidateListCountA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCANDIDATELISTCOUNTA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpdwListCount = (ULONG_PTR)lpdwListCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCandidateListCountA(struct qemu_syscall *call)
{
    struct qemu_ImmGetCandidateListCountA *c = (struct qemu_ImmGetCandidateListCountA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCandidateListCountA(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpdwListCount));
}

#endif

struct qemu_ImmGetCandidateListCountW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpdwListCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetCandidateListCountW(HIMC hIMC, LPDWORD lpdwListCount)
{
    struct qemu_ImmGetCandidateListCountW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCANDIDATELISTCOUNTW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpdwListCount = (ULONG_PTR)lpdwListCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCandidateListCountW(struct qemu_syscall *call)
{
    struct qemu_ImmGetCandidateListCountW *c = (struct qemu_ImmGetCandidateListCountW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCandidateListCountW(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpdwListCount));
}

#endif

struct qemu_ImmGetCandidateListW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpCandList;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetCandidateListW(HIMC hIMC, DWORD dwIndex, LPCANDIDATELIST lpCandList, DWORD dwBufLen)
{
    struct qemu_ImmGetCandidateListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCANDIDATELISTW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpCandList = (ULONG_PTR)lpCandList;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCandidateListW(struct qemu_syscall *call)
{
    struct qemu_ImmGetCandidateListW *c = (struct qemu_ImmGetCandidateListW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCandidateListW(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpCandList), c->dwBufLen);
}

#endif

struct qemu_ImmGetCandidateWindow
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpCandidate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetCandidateWindow(HIMC hIMC, DWORD dwIndex, LPCANDIDATEFORM lpCandidate)
{
    struct qemu_ImmGetCandidateWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCANDIDATEWINDOW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpCandidate = (ULONG_PTR)lpCandidate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCandidateWindow(struct qemu_syscall *call)
{
    struct qemu_ImmGetCandidateWindow *c = (struct qemu_ImmGetCandidateWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCandidateWindow(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpCandidate));
}

#endif

struct qemu_ImmGetCompositionFontA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lplf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetCompositionFontA(HIMC hIMC, LPLOGFONTA lplf)
{
    struct qemu_ImmGetCompositionFontA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCOMPOSITIONFONTA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lplf = (ULONG_PTR)lplf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCompositionFontA(struct qemu_syscall *call)
{
    struct qemu_ImmGetCompositionFontA *c = (struct qemu_ImmGetCompositionFontA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCompositionFontA(QEMU_G2H(c->hIMC), QEMU_G2H(c->lplf));
}

#endif

struct qemu_ImmGetCompositionFontW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lplf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetCompositionFontW(HIMC hIMC, LPLOGFONTW lplf)
{
    struct qemu_ImmGetCompositionFontW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCOMPOSITIONFONTW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lplf = (ULONG_PTR)lplf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCompositionFontW(struct qemu_syscall *call)
{
    struct qemu_ImmGetCompositionFontW *c = (struct qemu_ImmGetCompositionFontW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCompositionFontW(QEMU_G2H(c->hIMC), QEMU_G2H(c->lplf));
}

#endif

struct qemu_ImmGetCompositionStringA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpBuf;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI ImmGetCompositionStringA(HIMC hIMC, DWORD dwIndex, LPVOID lpBuf, DWORD dwBufLen)
{
    struct qemu_ImmGetCompositionStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCOMPOSITIONSTRINGA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpBuf = (ULONG_PTR)lpBuf;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCompositionStringA(struct qemu_syscall *call)
{
    struct qemu_ImmGetCompositionStringA *c = (struct qemu_ImmGetCompositionStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCompositionStringA(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpBuf), c->dwBufLen);
}

#endif

struct qemu_ImmGetCompositionStringW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpBuf;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI ImmGetCompositionStringW(HIMC hIMC, DWORD dwIndex, LPVOID lpBuf, DWORD dwBufLen)
{
    struct qemu_ImmGetCompositionStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCOMPOSITIONSTRINGW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpBuf = (ULONG_PTR)lpBuf;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCompositionStringW(struct qemu_syscall *call)
{
    struct qemu_ImmGetCompositionStringW *c = (struct qemu_ImmGetCompositionStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCompositionStringW(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpBuf), c->dwBufLen);
}

#endif

struct qemu_ImmGetCompositionWindow
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpCompForm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetCompositionWindow(HIMC hIMC, LPCOMPOSITIONFORM lpCompForm)
{
    struct qemu_ImmGetCompositionWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCOMPOSITIONWINDOW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpCompForm = (ULONG_PTR)lpCompForm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetCompositionWindow(struct qemu_syscall *call)
{
    struct qemu_ImmGetCompositionWindow *c = (struct qemu_ImmGetCompositionWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetCompositionWindow(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpCompForm));
}

#endif

struct qemu_ImmGetContext
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMC WINAPI ImmGetContext(HWND hWnd)
{
    struct qemu_ImmGetContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCONTEXT);
    call.hWnd = (ULONG_PTR)hWnd;

    qemu_syscall(&call.super);

    return (HIMC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmGetContext(struct qemu_syscall *call)
{
    struct qemu_ImmGetContext *c = (struct qemu_ImmGetContext *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)ImmGetContext(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_ImmGetConversionListA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t hIMC;
    uint64_t pSrc;
    uint64_t lpDst;
    uint64_t dwBufLen;
    uint64_t uFlag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetConversionListA(HKL hKL, HIMC hIMC, LPCSTR pSrc, LPCANDIDATELIST lpDst, DWORD dwBufLen, UINT uFlag)
{
    struct qemu_ImmGetConversionListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCONVERSIONLISTA);
    call.hKL = (ULONG_PTR)hKL;
    call.hIMC = (ULONG_PTR)hIMC;
    call.pSrc = (ULONG_PTR)pSrc;
    call.lpDst = (ULONG_PTR)lpDst;
    call.dwBufLen = (ULONG_PTR)dwBufLen;
    call.uFlag = (ULONG_PTR)uFlag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetConversionListA(struct qemu_syscall *call)
{
    struct qemu_ImmGetConversionListA *c = (struct qemu_ImmGetConversionListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetConversionListA(QEMU_G2H(c->hKL), QEMU_G2H(c->hIMC), QEMU_G2H(c->pSrc), QEMU_G2H(c->lpDst), c->dwBufLen, c->uFlag);
}

#endif

struct qemu_ImmGetConversionListW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t hIMC;
    uint64_t pSrc;
    uint64_t lpDst;
    uint64_t dwBufLen;
    uint64_t uFlag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetConversionListW(HKL hKL, HIMC hIMC, LPCWSTR pSrc, LPCANDIDATELIST lpDst, DWORD dwBufLen, UINT uFlag)
{
    struct qemu_ImmGetConversionListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCONVERSIONLISTW);
    call.hKL = (ULONG_PTR)hKL;
    call.hIMC = (ULONG_PTR)hIMC;
    call.pSrc = (ULONG_PTR)pSrc;
    call.lpDst = (ULONG_PTR)lpDst;
    call.dwBufLen = (ULONG_PTR)dwBufLen;
    call.uFlag = (ULONG_PTR)uFlag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetConversionListW(struct qemu_syscall *call)
{
    struct qemu_ImmGetConversionListW *c = (struct qemu_ImmGetConversionListW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetConversionListW(QEMU_G2H(c->hKL), QEMU_G2H(c->hIMC), QEMU_G2H(c->pSrc), QEMU_G2H(c->lpDst), c->dwBufLen, c->uFlag);
}

#endif

struct qemu_ImmGetConversionStatus
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpfdwConversion;
    uint64_t lpfdwSentence;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetConversionStatus(HIMC hIMC, LPDWORD lpfdwConversion, LPDWORD lpfdwSentence)
{
    struct qemu_ImmGetConversionStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETCONVERSIONSTATUS);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpfdwConversion = (ULONG_PTR)lpfdwConversion;
    call.lpfdwSentence = (ULONG_PTR)lpfdwSentence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetConversionStatus(struct qemu_syscall *call)
{
    struct qemu_ImmGetConversionStatus *c = (struct qemu_ImmGetConversionStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetConversionStatus(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpfdwConversion), QEMU_G2H(c->lpfdwSentence));
}

#endif

struct qemu_ImmGetDefaultIMEWnd
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI ImmGetDefaultIMEWnd(HWND hWnd)
{
    struct qemu_ImmGetDefaultIMEWnd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETDEFAULTIMEWND);
    call.hWnd = (ULONG_PTR)hWnd;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmGetDefaultIMEWnd(struct qemu_syscall *call)
{
    struct qemu_ImmGetDefaultIMEWnd *c = (struct qemu_ImmGetDefaultIMEWnd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmGetDefaultIMEWnd(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_ImmGetDescriptionA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszDescription;
    uint64_t uBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetDescriptionA(HKL hKL, LPSTR lpszDescription, UINT uBufLen)
{
    struct qemu_ImmGetDescriptionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETDESCRIPTIONA);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszDescription = (ULONG_PTR)lpszDescription;
    call.uBufLen = (ULONG_PTR)uBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetDescriptionA(struct qemu_syscall *call)
{
    struct qemu_ImmGetDescriptionA *c = (struct qemu_ImmGetDescriptionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetDescriptionA(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszDescription), c->uBufLen);
}

#endif

struct qemu_ImmGetDescriptionW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszDescription;
    uint64_t uBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetDescriptionW(HKL hKL, LPWSTR lpszDescription, UINT uBufLen)
{
    struct qemu_ImmGetDescriptionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETDESCRIPTIONW);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszDescription = (ULONG_PTR)lpszDescription;
    call.uBufLen = (ULONG_PTR)uBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetDescriptionW(struct qemu_syscall *call)
{
    struct qemu_ImmGetDescriptionW *c = (struct qemu_ImmGetDescriptionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetDescriptionW(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszDescription), c->uBufLen);
}

#endif

struct qemu_ImmGetGuideLineA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpBuf;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetGuideLineA(HIMC hIMC, DWORD dwIndex, LPSTR lpBuf, DWORD dwBufLen)
{
    struct qemu_ImmGetGuideLineA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETGUIDELINEA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpBuf = (ULONG_PTR)lpBuf;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetGuideLineA(struct qemu_syscall *call)
{
    struct qemu_ImmGetGuideLineA *c = (struct qemu_ImmGetGuideLineA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetGuideLineA(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpBuf), c->dwBufLen);
}

#endif

struct qemu_ImmGetGuideLineW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpBuf;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetGuideLineW(HIMC hIMC, DWORD dwIndex, LPWSTR lpBuf, DWORD dwBufLen)
{
    struct qemu_ImmGetGuideLineW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETGUIDELINEW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpBuf = (ULONG_PTR)lpBuf;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetGuideLineW(struct qemu_syscall *call)
{
    struct qemu_ImmGetGuideLineW *c = (struct qemu_ImmGetGuideLineW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetGuideLineW(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpBuf), c->dwBufLen);
}

#endif

struct qemu_ImmGetIMEFileNameA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszFileName;
    uint64_t uBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetIMEFileNameA(HKL hKL, LPSTR lpszFileName, UINT uBufLen)
{
    struct qemu_ImmGetIMEFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMEFILENAMEA);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.uBufLen = (ULONG_PTR)uBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetIMEFileNameA(struct qemu_syscall *call)
{
    struct qemu_ImmGetIMEFileNameA *c = (struct qemu_ImmGetIMEFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetIMEFileNameA(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszFileName), c->uBufLen);
}

#endif

struct qemu_ImmGetIMEFileNameW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszFileName;
    uint64_t uBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetIMEFileNameW(HKL hKL, LPWSTR lpszFileName, UINT uBufLen)
{
    struct qemu_ImmGetIMEFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMEFILENAMEW);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.uBufLen = (ULONG_PTR)uBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetIMEFileNameW(struct qemu_syscall *call)
{
    struct qemu_ImmGetIMEFileNameW *c = (struct qemu_ImmGetIMEFileNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetIMEFileNameW(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszFileName), c->uBufLen);
}

#endif

struct qemu_ImmGetOpenStatus
{
    struct qemu_syscall super;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetOpenStatus(HIMC hIMC)
{
    struct qemu_ImmGetOpenStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETOPENSTATUS);
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetOpenStatus(struct qemu_syscall *call)
{
    struct qemu_ImmGetOpenStatus *c = (struct qemu_ImmGetOpenStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetOpenStatus(QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmGetProperty
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t fdwIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetProperty(HKL hKL, DWORD fdwIndex)
{
    struct qemu_ImmGetProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETPROPERTY);
    call.hKL = (ULONG_PTR)hKL;
    call.fdwIndex = (ULONG_PTR)fdwIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetProperty(struct qemu_syscall *call)
{
    struct qemu_ImmGetProperty *c = (struct qemu_ImmGetProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetProperty(QEMU_G2H(c->hKL), c->fdwIndex);
}

#endif

struct qemu_ImmGetRegisterWordStyleA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t nItem;
    uint64_t lpStyleBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetRegisterWordStyleA(HKL hKL, UINT nItem, LPSTYLEBUFA lpStyleBuf)
{
    struct qemu_ImmGetRegisterWordStyleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETREGISTERWORDSTYLEA);
    call.hKL = (ULONG_PTR)hKL;
    call.nItem = (ULONG_PTR)nItem;
    call.lpStyleBuf = (ULONG_PTR)lpStyleBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetRegisterWordStyleA(struct qemu_syscall *call)
{
    struct qemu_ImmGetRegisterWordStyleA *c = (struct qemu_ImmGetRegisterWordStyleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetRegisterWordStyleA(QEMU_G2H(c->hKL), c->nItem, QEMU_G2H(c->lpStyleBuf));
}

#endif

struct qemu_ImmGetRegisterWordStyleW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t nItem;
    uint64_t lpStyleBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetRegisterWordStyleW(HKL hKL, UINT nItem, LPSTYLEBUFW lpStyleBuf)
{
    struct qemu_ImmGetRegisterWordStyleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETREGISTERWORDSTYLEW);
    call.hKL = (ULONG_PTR)hKL;
    call.nItem = (ULONG_PTR)nItem;
    call.lpStyleBuf = (ULONG_PTR)lpStyleBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetRegisterWordStyleW(struct qemu_syscall *call)
{
    struct qemu_ImmGetRegisterWordStyleW *c = (struct qemu_ImmGetRegisterWordStyleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetRegisterWordStyleW(QEMU_G2H(c->hKL), c->nItem, QEMU_G2H(c->lpStyleBuf));
}

#endif

struct qemu_ImmGetStatusWindowPos
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpptPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetStatusWindowPos(HIMC hIMC, LPPOINT lpptPos)
{
    struct qemu_ImmGetStatusWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETSTATUSWINDOWPOS);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpptPos = (ULONG_PTR)lpptPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetStatusWindowPos(struct qemu_syscall *call)
{
    struct qemu_ImmGetStatusWindowPos *c = (struct qemu_ImmGetStatusWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetStatusWindowPos(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpptPos));
}

#endif

struct qemu_ImmGetVirtualKey
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImmGetVirtualKey(HWND hWnd)
{
    struct qemu_ImmGetVirtualKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETVIRTUALKEY);
    call.hWnd = (ULONG_PTR)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetVirtualKey(struct qemu_syscall *call)
{
    struct qemu_ImmGetVirtualKey *c = (struct qemu_ImmGetVirtualKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetVirtualKey(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_ImmInstallIMEA
{
    struct qemu_syscall super;
    uint64_t lpszIMEFileName;
    uint64_t lpszLayoutText;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HKL WINAPI ImmInstallIMEA(LPCSTR lpszIMEFileName, LPCSTR lpszLayoutText)
{
    struct qemu_ImmInstallIMEA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMINSTALLIMEA);
    call.lpszIMEFileName = (ULONG_PTR)lpszIMEFileName;
    call.lpszLayoutText = (ULONG_PTR)lpszLayoutText;

    qemu_syscall(&call.super);

    return (HKL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmInstallIMEA(struct qemu_syscall *call)
{
    struct qemu_ImmInstallIMEA *c = (struct qemu_ImmInstallIMEA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmInstallIMEA(QEMU_G2H(c->lpszIMEFileName), QEMU_G2H(c->lpszLayoutText));
}

#endif

struct qemu_ImmInstallIMEW
{
    struct qemu_syscall super;
    uint64_t lpszIMEFileName;
    uint64_t lpszLayoutText;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HKL WINAPI ImmInstallIMEW(LPCWSTR lpszIMEFileName, LPCWSTR lpszLayoutText)
{
    struct qemu_ImmInstallIMEW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMINSTALLIMEW);
    call.lpszIMEFileName = (ULONG_PTR)lpszIMEFileName;
    call.lpszLayoutText = (ULONG_PTR)lpszLayoutText;

    qemu_syscall(&call.super);

    return (HKL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmInstallIMEW(struct qemu_syscall *call)
{
    struct qemu_ImmInstallIMEW *c = (struct qemu_ImmInstallIMEW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmInstallIMEW(QEMU_G2H(c->lpszIMEFileName), QEMU_G2H(c->lpszLayoutText));
}

#endif

struct qemu_ImmIsIME
{
    struct qemu_syscall super;
    uint64_t hKL;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmIsIME(HKL hKL)
{
    struct qemu_ImmIsIME call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMISIME);
    call.hKL = (ULONG_PTR)hKL;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmIsIME(struct qemu_syscall *call)
{
    struct qemu_ImmIsIME *c = (struct qemu_ImmIsIME *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmIsIME(QEMU_G2H(c->hKL));
}

#endif

struct qemu_ImmIsUIMessageA
{
    struct qemu_syscall super;
    uint64_t hWndIME;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmIsUIMessageA(HWND hWndIME, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_ImmIsUIMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMISUIMESSAGEA);
    call.hWndIME = (ULONG_PTR)hWndIME;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmIsUIMessageA(struct qemu_syscall *call)
{
    struct qemu_ImmIsUIMessageA *c = (struct qemu_ImmIsUIMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmIsUIMessageA(QEMU_G2H(c->hWndIME), c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_ImmIsUIMessageW
{
    struct qemu_syscall super;
    uint64_t hWndIME;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmIsUIMessageW(HWND hWndIME, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_ImmIsUIMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMISUIMESSAGEW);
    call.hWndIME = (ULONG_PTR)hWndIME;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmIsUIMessageW(struct qemu_syscall *call)
{
    struct qemu_ImmIsUIMessageW *c = (struct qemu_ImmIsUIMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmIsUIMessageW(QEMU_G2H(c->hWndIME), c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_ImmNotifyIME
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwAction;
    uint64_t dwIndex;
    uint64_t dwValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmNotifyIME(HIMC hIMC, DWORD dwAction, DWORD dwIndex, DWORD dwValue)
{
    struct qemu_ImmNotifyIME call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMNOTIFYIME);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwAction = (ULONG_PTR)dwAction;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.dwValue = (ULONG_PTR)dwValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmNotifyIME(struct qemu_syscall *call)
{
    struct qemu_ImmNotifyIME *c = (struct qemu_ImmNotifyIME *)call;
    WINE_TRACE("\n");
    c->super.iret = ImmNotifyIME(QEMU_G2H(c->hIMC), c->dwAction, c->dwIndex, c->dwValue);
}

#endif

struct qemu_ImmRegisterWordA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszReading;
    uint64_t dwStyle;
    uint64_t lpszRegister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmRegisterWordA(HKL hKL, LPCSTR lpszReading, DWORD dwStyle, LPCSTR lpszRegister)
{
    struct qemu_ImmRegisterWordA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMREGISTERWORDA);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszReading = (ULONG_PTR)lpszReading;
    call.dwStyle = (ULONG_PTR)dwStyle;
    call.lpszRegister = (ULONG_PTR)lpszRegister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmRegisterWordA(struct qemu_syscall *call)
{
    struct qemu_ImmRegisterWordA *c = (struct qemu_ImmRegisterWordA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmRegisterWordA(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszReading), c->dwStyle, QEMU_G2H(c->lpszRegister));
}

#endif

struct qemu_ImmRegisterWordW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszReading;
    uint64_t dwStyle;
    uint64_t lpszRegister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmRegisterWordW(HKL hKL, LPCWSTR lpszReading, DWORD dwStyle, LPCWSTR lpszRegister)
{
    struct qemu_ImmRegisterWordW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMREGISTERWORDW);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszReading = (ULONG_PTR)lpszReading;
    call.dwStyle = (ULONG_PTR)dwStyle;
    call.lpszRegister = (ULONG_PTR)lpszRegister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmRegisterWordW(struct qemu_syscall *call)
{
    struct qemu_ImmRegisterWordW *c = (struct qemu_ImmRegisterWordW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmRegisterWordW(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszReading), c->dwStyle, QEMU_G2H(c->lpszRegister));
}

#endif

struct qemu_ImmReleaseContext
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmReleaseContext(HWND hWnd, HIMC hIMC)
{
    struct qemu_ImmReleaseContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMRELEASECONTEXT);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmReleaseContext(struct qemu_syscall *call)
{
    struct qemu_ImmReleaseContext *c = (struct qemu_ImmReleaseContext *)call;
    WINE_TRACE("\n");
    c->super.iret = ImmReleaseContext(QEMU_G2H(c->hWnd), QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmRequestMessageA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI ImmRequestMessageA(HIMC hIMC, WPARAM wParam, LPARAM lParam)
{
    struct qemu_ImmRequestMessageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMREQUESTMESSAGEA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmRequestMessageA(struct qemu_syscall *call)
{
    struct qemu_ImmRequestMessageA *c = (struct qemu_ImmRequestMessageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmRequestMessageA(QEMU_G2H(c->hIMC), c->wParam, c->lParam);
}

#endif

struct qemu_ImmRequestMessageW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI ImmRequestMessageW(HIMC hIMC, WPARAM wParam, LPARAM lParam)
{
    struct qemu_ImmRequestMessageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMREQUESTMESSAGEW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmRequestMessageW(struct qemu_syscall *call)
{
    struct qemu_ImmRequestMessageW *c = (struct qemu_ImmRequestMessageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmRequestMessageW(QEMU_G2H(c->hIMC), c->wParam, c->lParam);
}

#endif

struct qemu_ImmSetCandidateWindow
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpCandidate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetCandidateWindow(HIMC hIMC, LPCANDIDATEFORM lpCandidate)
{
    struct qemu_ImmSetCandidateWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCANDIDATEWINDOW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpCandidate = (ULONG_PTR)lpCandidate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetCandidateWindow(struct qemu_syscall *call)
{
    struct qemu_ImmSetCandidateWindow *c = (struct qemu_ImmSetCandidateWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetCandidateWindow(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpCandidate));
}

#endif

struct qemu_ImmSetCompositionFontA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lplf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetCompositionFontA(HIMC hIMC, LPLOGFONTA lplf)
{
    struct qemu_ImmSetCompositionFontA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCOMPOSITIONFONTA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lplf = (ULONG_PTR)lplf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetCompositionFontA(struct qemu_syscall *call)
{
    struct qemu_ImmSetCompositionFontA *c = (struct qemu_ImmSetCompositionFontA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetCompositionFontA(QEMU_G2H(c->hIMC), QEMU_G2H(c->lplf));
}

#endif

struct qemu_ImmSetCompositionFontW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lplf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetCompositionFontW(HIMC hIMC, LPLOGFONTW lplf)
{
    struct qemu_ImmSetCompositionFontW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCOMPOSITIONFONTW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lplf = (ULONG_PTR)lplf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetCompositionFontW(struct qemu_syscall *call)
{
    struct qemu_ImmSetCompositionFontW *c = (struct qemu_ImmSetCompositionFontW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetCompositionFontW(QEMU_G2H(c->hIMC), QEMU_G2H(c->lplf));
}

#endif

struct qemu_ImmSetCompositionStringA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpComp;
    uint64_t dwCompLen;
    uint64_t lpRead;
    uint64_t dwReadLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetCompositionStringA(HIMC hIMC, DWORD dwIndex, LPVOID lpComp, DWORD dwCompLen, LPVOID lpRead, DWORD dwReadLen)
{
    struct qemu_ImmSetCompositionStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCOMPOSITIONSTRINGA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpComp = (ULONG_PTR)lpComp;
    call.dwCompLen = (ULONG_PTR)dwCompLen;
    call.lpRead = (ULONG_PTR)lpRead;
    call.dwReadLen = (ULONG_PTR)dwReadLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetCompositionStringA(struct qemu_syscall *call)
{
    struct qemu_ImmSetCompositionStringA *c = (struct qemu_ImmSetCompositionStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetCompositionStringA(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpComp), c->dwCompLen, QEMU_G2H(c->lpRead), c->dwReadLen);
}

#endif

struct qemu_ImmSetCompositionStringW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwIndex;
    uint64_t lpComp;
    uint64_t dwCompLen;
    uint64_t lpRead;
    uint64_t dwReadLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetCompositionStringW(HIMC hIMC, DWORD dwIndex, LPVOID lpComp, DWORD dwCompLen, LPVOID lpRead, DWORD dwReadLen)
{
    struct qemu_ImmSetCompositionStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCOMPOSITIONSTRINGW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.lpComp = (ULONG_PTR)lpComp;
    call.dwCompLen = (ULONG_PTR)dwCompLen;
    call.lpRead = (ULONG_PTR)lpRead;
    call.dwReadLen = (ULONG_PTR)dwReadLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetCompositionStringW(struct qemu_syscall *call)
{
    struct qemu_ImmSetCompositionStringW *c = (struct qemu_ImmSetCompositionStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetCompositionStringW(QEMU_G2H(c->hIMC), c->dwIndex, QEMU_G2H(c->lpComp), c->dwCompLen, QEMU_G2H(c->lpRead), c->dwReadLen);
}

#endif

struct qemu_ImmSetCompositionWindow
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpCompForm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetCompositionWindow(HIMC hIMC, LPCOMPOSITIONFORM lpCompForm)
{
    struct qemu_ImmSetCompositionWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCOMPOSITIONWINDOW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpCompForm = (ULONG_PTR)lpCompForm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetCompositionWindow(struct qemu_syscall *call)
{
    struct qemu_ImmSetCompositionWindow *c = (struct qemu_ImmSetCompositionWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetCompositionWindow(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpCompForm));
}

#endif

struct qemu_ImmSetConversionStatus
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t fdwConversion;
    uint64_t fdwSentence;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetConversionStatus(HIMC hIMC, DWORD fdwConversion, DWORD fdwSentence)
{
    struct qemu_ImmSetConversionStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETCONVERSIONSTATUS);
    call.hIMC = (ULONG_PTR)hIMC;
    call.fdwConversion = (ULONG_PTR)fdwConversion;
    call.fdwSentence = (ULONG_PTR)fdwSentence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetConversionStatus(struct qemu_syscall *call)
{
    struct qemu_ImmSetConversionStatus *c = (struct qemu_ImmSetConversionStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetConversionStatus(QEMU_G2H(c->hIMC), c->fdwConversion, c->fdwSentence);
}

#endif

struct qemu_ImmSetOpenStatus
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t fOpen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetOpenStatus(HIMC hIMC, BOOL fOpen)
{
    struct qemu_ImmSetOpenStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETOPENSTATUS);
    call.hIMC = (ULONG_PTR)hIMC;
    call.fOpen = (ULONG_PTR)fOpen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetOpenStatus(struct qemu_syscall *call)
{
    struct qemu_ImmSetOpenStatus *c = (struct qemu_ImmSetOpenStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetOpenStatus(QEMU_G2H(c->hIMC), c->fOpen);
}

#endif

struct qemu_ImmSetStatusWindowPos
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t lpptPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSetStatusWindowPos(HIMC hIMC, LPPOINT lpptPos)
{
    struct qemu_ImmSetStatusWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSETSTATUSWINDOWPOS);
    call.hIMC = (ULONG_PTR)hIMC;
    call.lpptPos = (ULONG_PTR)lpptPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSetStatusWindowPos(struct qemu_syscall *call)
{
    struct qemu_ImmSetStatusWindowPos *c = (struct qemu_ImmSetStatusWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSetStatusWindowPos(QEMU_G2H(c->hIMC), QEMU_G2H(c->lpptPos));
}

#endif

struct qemu_ImmCreateSoftKeyboard
{
    struct qemu_syscall super;
    uint64_t uType;
    uint64_t hOwner;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI ImmCreateSoftKeyboard(UINT uType, UINT hOwner, int x, int y)
{
    struct qemu_ImmCreateSoftKeyboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMCREATESOFTKEYBOARD);
    call.uType = (ULONG_PTR)uType;
    call.hOwner = (ULONG_PTR)hOwner;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmCreateSoftKeyboard(struct qemu_syscall *call)
{
    struct qemu_ImmCreateSoftKeyboard *c = (struct qemu_ImmCreateSoftKeyboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmCreateSoftKeyboard(c->uType, c->hOwner, c->x, c->y);
}

#endif

struct qemu_ImmDestroySoftKeyboard
{
    struct qemu_syscall super;
    uint64_t hSoftWnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmDestroySoftKeyboard(HWND hSoftWnd)
{
    struct qemu_ImmDestroySoftKeyboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMDESTROYSOFTKEYBOARD);
    call.hSoftWnd = (ULONG_PTR)hSoftWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmDestroySoftKeyboard(struct qemu_syscall *call)
{
    struct qemu_ImmDestroySoftKeyboard *c = (struct qemu_ImmDestroySoftKeyboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmDestroySoftKeyboard(QEMU_G2H(c->hSoftWnd));
}

#endif

struct qemu_ImmShowSoftKeyboard
{
    struct qemu_syscall super;
    uint64_t hSoftWnd;
    uint64_t nCmdShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmShowSoftKeyboard(HWND hSoftWnd, int nCmdShow)
{
    struct qemu_ImmShowSoftKeyboard call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSHOWSOFTKEYBOARD);
    call.hSoftWnd = (ULONG_PTR)hSoftWnd;
    call.nCmdShow = (ULONG_PTR)nCmdShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmShowSoftKeyboard(struct qemu_syscall *call)
{
    struct qemu_ImmShowSoftKeyboard *c = (struct qemu_ImmShowSoftKeyboard *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmShowSoftKeyboard(QEMU_G2H(c->hSoftWnd), c->nCmdShow);
}

#endif

struct qemu_ImmSimulateHotKey
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t dwHotKeyID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmSimulateHotKey(HWND hWnd, DWORD dwHotKeyID)
{
    struct qemu_ImmSimulateHotKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMSIMULATEHOTKEY);
    call.hWnd = (ULONG_PTR)hWnd;
    call.dwHotKeyID = (ULONG_PTR)dwHotKeyID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmSimulateHotKey(struct qemu_syscall *call)
{
    struct qemu_ImmSimulateHotKey *c = (struct qemu_ImmSimulateHotKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmSimulateHotKey(QEMU_G2H(c->hWnd), c->dwHotKeyID);
}

#endif

struct qemu_ImmUnregisterWordA
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszReading;
    uint64_t dwStyle;
    uint64_t lpszUnregister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmUnregisterWordA(HKL hKL, LPCSTR lpszReading, DWORD dwStyle, LPCSTR lpszUnregister)
{
    struct qemu_ImmUnregisterWordA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMUNREGISTERWORDA);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszReading = (ULONG_PTR)lpszReading;
    call.dwStyle = (ULONG_PTR)dwStyle;
    call.lpszUnregister = (ULONG_PTR)lpszUnregister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmUnregisterWordA(struct qemu_syscall *call)
{
    struct qemu_ImmUnregisterWordA *c = (struct qemu_ImmUnregisterWordA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmUnregisterWordA(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszReading), c->dwStyle, QEMU_G2H(c->lpszUnregister));
}

#endif

struct qemu_ImmUnregisterWordW
{
    struct qemu_syscall super;
    uint64_t hKL;
    uint64_t lpszReading;
    uint64_t dwStyle;
    uint64_t lpszUnregister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmUnregisterWordW(HKL hKL, LPCWSTR lpszReading, DWORD dwStyle, LPCWSTR lpszUnregister)
{
    struct qemu_ImmUnregisterWordW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMUNREGISTERWORDW);
    call.hKL = (ULONG_PTR)hKL;
    call.lpszReading = (ULONG_PTR)lpszReading;
    call.dwStyle = (ULONG_PTR)dwStyle;
    call.lpszUnregister = (ULONG_PTR)lpszUnregister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmUnregisterWordW(struct qemu_syscall *call)
{
    struct qemu_ImmUnregisterWordW *c = (struct qemu_ImmUnregisterWordW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmUnregisterWordW(QEMU_G2H(c->hKL), QEMU_G2H(c->lpszReading), c->dwStyle, QEMU_G2H(c->lpszUnregister));
}

#endif

struct qemu_ImmGetImeMenuItemsA
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwFlags;
    uint64_t dwType;
    uint64_t lpImeParentMenu;
    uint64_t lpImeMenu;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetImeMenuItemsA(HIMC hIMC, DWORD dwFlags, DWORD dwType, LPIMEMENUITEMINFOA lpImeParentMenu, LPIMEMENUITEMINFOA lpImeMenu, DWORD dwSize)
{
    struct qemu_ImmGetImeMenuItemsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMEMENUITEMSA);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwType = (ULONG_PTR)dwType;
    call.lpImeParentMenu = (ULONG_PTR)lpImeParentMenu;
    call.lpImeMenu = (ULONG_PTR)lpImeMenu;
    call.dwSize = (ULONG_PTR)dwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetImeMenuItemsA(struct qemu_syscall *call)
{
    struct qemu_ImmGetImeMenuItemsA *c = (struct qemu_ImmGetImeMenuItemsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetImeMenuItemsA(QEMU_G2H(c->hIMC), c->dwFlags, c->dwType, QEMU_G2H(c->lpImeParentMenu), QEMU_G2H(c->lpImeMenu), c->dwSize);
}

#endif

struct qemu_ImmGetImeMenuItemsW
{
    struct qemu_syscall super;
    uint64_t hIMC;
    uint64_t dwFlags;
    uint64_t dwType;
    uint64_t lpImeParentMenu;
    uint64_t lpImeMenu;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetImeMenuItemsW(HIMC hIMC, DWORD dwFlags, DWORD dwType, LPIMEMENUITEMINFOW lpImeParentMenu, LPIMEMENUITEMINFOW lpImeMenu, DWORD dwSize)
{
    struct qemu_ImmGetImeMenuItemsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMEMENUITEMSW);
    call.hIMC = (ULONG_PTR)hIMC;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwType = (ULONG_PTR)dwType;
    call.lpImeParentMenu = (ULONG_PTR)lpImeParentMenu;
    call.lpImeMenu = (ULONG_PTR)lpImeMenu;
    call.dwSize = (ULONG_PTR)dwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetImeMenuItemsW(struct qemu_syscall *call)
{
    struct qemu_ImmGetImeMenuItemsW *c = (struct qemu_ImmGetImeMenuItemsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetImeMenuItemsW(QEMU_G2H(c->hIMC), c->dwFlags, c->dwType, QEMU_G2H(c->lpImeParentMenu), QEMU_G2H(c->lpImeMenu), c->dwSize);
}

#endif

struct qemu_ImmLockIMC
{
    struct qemu_syscall super;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INPUTCONTEXT * WINAPI ImmLockIMC(HIMC hIMC)
{
    struct qemu_ImmLockIMC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMLOCKIMC);
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return (INPUTCONTEXT *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmLockIMC(struct qemu_syscall *call)
{
    struct qemu_ImmLockIMC *c = (struct qemu_ImmLockIMC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmLockIMC(QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmUnlockIMC
{
    struct qemu_syscall super;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmUnlockIMC(HIMC hIMC)
{
    struct qemu_ImmUnlockIMC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMUNLOCKIMC);
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmUnlockIMC(struct qemu_syscall *call)
{
    struct qemu_ImmUnlockIMC *c = (struct qemu_ImmUnlockIMC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmUnlockIMC(QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmGetIMCLockCount
{
    struct qemu_syscall super;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetIMCLockCount(HIMC hIMC)
{
    struct qemu_ImmGetIMCLockCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMCLOCKCOUNT);
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetIMCLockCount(struct qemu_syscall *call)
{
    struct qemu_ImmGetIMCLockCount *c = (struct qemu_ImmGetIMCLockCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetIMCLockCount(QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmCreateIMCC
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMCC WINAPI ImmCreateIMCC(DWORD size)
{
    struct qemu_ImmCreateIMCC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMCREATEIMCC);
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (HIMCC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmCreateIMCC(struct qemu_syscall *call)
{
    struct qemu_ImmCreateIMCC *c = (struct qemu_ImmCreateIMCC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmCreateIMCC(c->size);
}

#endif

struct qemu_ImmDestroyIMCC
{
    struct qemu_syscall super;
    uint64_t block;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMCC WINAPI ImmDestroyIMCC(HIMCC block)
{
    struct qemu_ImmDestroyIMCC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMDESTROYIMCC);
    call.block = (ULONG_PTR)block;

    qemu_syscall(&call.super);

    return (HIMCC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmDestroyIMCC(struct qemu_syscall *call)
{
    struct qemu_ImmDestroyIMCC *c = (struct qemu_ImmDestroyIMCC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmDestroyIMCC((HIMCC)c->block);
}

#endif

struct qemu_ImmLockIMCC
{
    struct qemu_syscall super;
    uint64_t imcc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI ImmLockIMCC(HIMCC imcc)
{
    struct qemu_ImmLockIMCC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMLOCKIMCC);
    call.imcc = (ULONG_PTR)imcc;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmLockIMCC(struct qemu_syscall *call)
{
    struct qemu_ImmLockIMCC *c = (struct qemu_ImmLockIMCC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmLockIMCC((HIMCC)c->imcc);
}

#endif

struct qemu_ImmUnlockIMCC
{
    struct qemu_syscall super;
    uint64_t imcc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmUnlockIMCC(HIMCC imcc)
{
    struct qemu_ImmUnlockIMCC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMUNLOCKIMCC);
    call.imcc = (ULONG_PTR)imcc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmUnlockIMCC(struct qemu_syscall *call)
{
    struct qemu_ImmUnlockIMCC *c = (struct qemu_ImmUnlockIMCC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmUnlockIMCC((HIMCC)c->imcc);
}

#endif

struct qemu_ImmGetIMCCLockCount
{
    struct qemu_syscall super;
    uint64_t imcc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetIMCCLockCount(HIMCC imcc)
{
    struct qemu_ImmGetIMCCLockCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMCCLOCKCOUNT);
    call.imcc = (ULONG_PTR)imcc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetIMCCLockCount(struct qemu_syscall *call)
{
    struct qemu_ImmGetIMCCLockCount *c = (struct qemu_ImmGetIMCCLockCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetIMCCLockCount((HIMCC)c->imcc);
}

#endif

struct qemu_ImmReSizeIMCC
{
    struct qemu_syscall super;
    uint64_t imcc;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMCC WINAPI ImmReSizeIMCC(HIMCC imcc, DWORD size)
{
    struct qemu_ImmReSizeIMCC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMRESIZEIMCC);
    call.imcc = (ULONG_PTR)imcc;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (HIMCC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImmReSizeIMCC(struct qemu_syscall *call)
{
    struct qemu_ImmReSizeIMCC *c = (struct qemu_ImmReSizeIMCC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImmReSizeIMCC((HIMCC)c->imcc, c->size);
}

#endif

struct qemu_ImmGetIMCCSize
{
    struct qemu_syscall super;
    uint64_t imcc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImmGetIMCCSize(HIMCC imcc)
{
    struct qemu_ImmGetIMCCSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETIMCCSIZE);
    call.imcc = (ULONG_PTR)imcc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGetIMCCSize(struct qemu_syscall *call)
{
    struct qemu_ImmGetIMCCSize *c = (struct qemu_ImmGetIMCCSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetIMCCSize((HIMCC)c->imcc);
}

#endif

struct qemu_ImmGenerateMessage
{
    struct qemu_syscall super;
    uint64_t hIMC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGenerateMessage(HIMC hIMC)
{
    struct qemu_ImmGenerateMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGENERATEMESSAGE);
    call.hIMC = (ULONG_PTR)hIMC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmGenerateMessage(struct qemu_syscall *call)
{
    struct qemu_ImmGenerateMessage *c = (struct qemu_ImmGenerateMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGenerateMessage(QEMU_G2H(c->hIMC));
}

#endif

struct qemu_ImmTranslateMessage
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lKeyData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmTranslateMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lKeyData)
{
    struct qemu_ImmTranslateMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMTRANSLATEMESSAGE);
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lKeyData = (ULONG_PTR)lKeyData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmTranslateMessage(struct qemu_syscall *call)
{
    struct qemu_ImmTranslateMessage *c = (struct qemu_ImmTranslateMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmTranslateMessage(QEMU_G2H(c->hwnd), c->msg, c->wParam, c->lKeyData);
}

#endif

struct qemu_ImmProcessKey
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hKL;
    uint64_t vKey;
    uint64_t lKeyData;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmProcessKey(HWND hwnd, HKL hKL, UINT vKey, LPARAM lKeyData, DWORD unknown)
{
    struct qemu_ImmProcessKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMPROCESSKEY);
    call.hwnd = (ULONG_PTR)hwnd;
    call.hKL = (ULONG_PTR)hKL;
    call.vKey = (ULONG_PTR)vKey;
    call.lKeyData = (ULONG_PTR)lKeyData;
    call.unknown = (ULONG_PTR)unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmProcessKey(struct qemu_syscall *call)
{
    struct qemu_ImmProcessKey *c = (struct qemu_ImmProcessKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmProcessKey(QEMU_G2H(c->hwnd), QEMU_G2H(c->hKL), c->vKey, c->lKeyData, c->unknown);
}

#endif

/* TODO: Add ImmDisableTextFrameService to Wine headers? */
extern BOOL WINAPI ImmDisableTextFrameService(DWORD idThread);
struct qemu_ImmDisableTextFrameService
{
    struct qemu_syscall super;
    uint64_t idThread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmDisableTextFrameService(DWORD idThread)
{
    struct qemu_ImmDisableTextFrameService call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMDISABLETEXTFRAMESERVICE);
    call.idThread = (ULONG_PTR)idThread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmDisableTextFrameService(struct qemu_syscall *call)
{
    struct qemu_ImmDisableTextFrameService *c = (struct qemu_ImmDisableTextFrameService *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmDisableTextFrameService(c->idThread);
}

#endif

struct qemu_ImmEnumInputContext
{
    struct qemu_syscall super;
    uint64_t idThread;
    uint64_t lpfn;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmEnumInputContext(DWORD idThread, IMCENUMPROC lpfn, LPARAM lParam)
{
    struct qemu_ImmEnumInputContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMENUMINPUTCONTEXT);
    call.idThread = (ULONG_PTR)idThread;
    call.lpfn = (ULONG_PTR)lpfn;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmEnumInputContext(struct qemu_syscall *call)
{
    struct qemu_ImmEnumInputContext *c = (struct qemu_ImmEnumInputContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmEnumInputContext(c->idThread, QEMU_G2H(c->lpfn), c->lParam);
}

#endif

struct qemu_ImmGetHotKey
{
    struct qemu_syscall super;
    uint64_t hotkey;
    uint64_t modifiers;
    uint64_t key;
    uint64_t hkl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmGetHotKey(DWORD hotkey, UINT *modifiers, UINT *key, HKL hkl)
{
    struct qemu_ImmGetHotKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMGETHOTKEY);
    call.hotkey = (ULONG_PTR)hotkey;
    call.modifiers = (ULONG_PTR)modifiers;
    call.key = (ULONG_PTR)key;
    call.hkl = (ULONG_PTR)hkl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ImmGetHotKey to Wine headers? */
extern BOOL WINAPI ImmGetHotKey(DWORD hotkey, UINT *modifiers, UINT *key, HKL hkl);
void qemu_ImmGetHotKey(struct qemu_syscall *call)
{
    struct qemu_ImmGetHotKey *c = (struct qemu_ImmGetHotKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmGetHotKey(c->hotkey, QEMU_G2H(c->modifiers), QEMU_G2H(c->key), QEMU_G2H(c->hkl));
}

#endif

struct qemu_ImmDisableLegacyIME
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImmDisableLegacyIME(void)
{
    struct qemu_ImmDisableLegacyIME call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMMDISABLELEGACYIME);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImmDisableLegacyIME(struct qemu_syscall *call)
{
    struct qemu_ImmDisableLegacyIME *c = (struct qemu_ImmDisableLegacyIME *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImmDisableLegacyIME();
}

#endif
