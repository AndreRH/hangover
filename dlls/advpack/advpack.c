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
#include <setupapi.h>
#include <advpub.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advpack.h"

#ifdef QEMU_DLL_GUEST

typedef struct _PERUSERSECTIONA PERUSERSECTIONA;
typedef struct _PERUSERSECTIONW PERUSERSECTIONW;

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advpack);

#endif


struct qemu_CloseINFEngine
{
    struct qemu_syscall super;
    uint64_t hInf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CloseINFEngine(HINF hInf)
{
    struct qemu_CloseINFEngine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEINFENGINE);
    call.hInf = (ULONG_PTR)hInf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseINFEngine(struct qemu_syscall *call)
{
    struct qemu_CloseINFEngine *c = (struct qemu_CloseINFEngine *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseINFEngine(QEMU_G2H(c->hInf));
}

#endif

struct qemu_IsNTAdmin
{
    struct qemu_syscall super;
    uint64_t reserved;
    uint64_t pReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsNTAdmin(DWORD reserved, LPDWORD pReserved)
{
    struct qemu_IsNTAdmin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISNTADMIN);
    call.reserved = (ULONG_PTR)reserved;
    call.pReserved = (ULONG_PTR)pReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsNTAdmin(struct qemu_syscall *call)
{
    struct qemu_IsNTAdmin *c = (struct qemu_IsNTAdmin *)call;
    WINE_TRACE("\n");
    c->super.iret = IsNTAdmin(c->reserved, QEMU_G2H(c->pReserved));
}

#endif

struct qemu_NeedRebootInit
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NeedRebootInit(VOID)
{
    struct qemu_NeedRebootInit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NEEDREBOOTINIT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NeedRebootInit(struct qemu_syscall *call)
{
    struct qemu_NeedRebootInit *c = (struct qemu_NeedRebootInit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NeedRebootInit();
}

#endif

struct qemu_NeedReboot
{
    struct qemu_syscall super;
    uint64_t dwRebootCheck;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI NeedReboot(DWORD dwRebootCheck)
{
    struct qemu_NeedReboot call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NEEDREBOOT);
    call.dwRebootCheck = (ULONG_PTR)dwRebootCheck;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NeedReboot(struct qemu_syscall *call)
{
    struct qemu_NeedReboot *c = (struct qemu_NeedReboot *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NeedReboot(c->dwRebootCheck);
}

#endif

struct qemu_OpenINFEngineA
{
    struct qemu_syscall super;
    uint64_t pszInfFilename;
    uint64_t pszInstallSection;
    uint64_t dwFlags;
    uint64_t phInf;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI OpenINFEngineA(LPCSTR pszInfFilename, LPCSTR pszInstallSection, DWORD dwFlags, HINF *phInf, PVOID pvReserved)
{
    struct qemu_OpenINFEngineA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENINFENGINEA);
    call.pszInfFilename = (ULONG_PTR)pszInfFilename;
    call.pszInstallSection = (ULONG_PTR)pszInstallSection;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phInf = (ULONG_PTR)phInf;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenINFEngineA(struct qemu_syscall *call)
{
    struct qemu_OpenINFEngineA *c = (struct qemu_OpenINFEngineA *)call;
    WINE_TRACE("\n");
    c->super.iret = OpenINFEngineA(QEMU_G2H(c->pszInfFilename), QEMU_G2H(c->pszInstallSection), c->dwFlags, QEMU_G2H(c->phInf), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_OpenINFEngineW
{
    struct qemu_syscall super;
    uint64_t pszInfFilename;
    uint64_t pszInstallSection;
    uint64_t dwFlags;
    uint64_t phInf;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI OpenINFEngineW(LPCWSTR pszInfFilename, LPCWSTR pszInstallSection, DWORD dwFlags, HINF *phInf, PVOID pvReserved)
{
    struct qemu_OpenINFEngineW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENINFENGINEW);
    call.pszInfFilename = (ULONG_PTR)pszInfFilename;
    call.pszInstallSection = (ULONG_PTR)pszInstallSection;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phInf = (ULONG_PTR)phInf;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenINFEngineW(struct qemu_syscall *call)
{
    struct qemu_OpenINFEngineW *c = (struct qemu_OpenINFEngineW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenINFEngineW(QEMU_G2H(c->pszInfFilename), QEMU_G2H(c->pszInstallSection), c->dwFlags, QEMU_G2H(c->phInf), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_RebootCheckOnInstallA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszINF;
    uint64_t pszSec;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RebootCheckOnInstallA(HWND hWnd, LPCSTR pszINF, LPCSTR pszSec, DWORD dwReserved)
{
    struct qemu_RebootCheckOnInstallA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REBOOTCHECKONINSTALLA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszINF = (ULONG_PTR)pszINF;
    call.pszSec = (ULONG_PTR)pszSec;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RebootCheckOnInstallA(struct qemu_syscall *call)
{
    struct qemu_RebootCheckOnInstallA *c = (struct qemu_RebootCheckOnInstallA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RebootCheckOnInstallA(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszINF), QEMU_G2H(c->pszSec), c->dwReserved);
}

#endif

struct qemu_RebootCheckOnInstallW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszINF;
    uint64_t pszSec;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RebootCheckOnInstallW(HWND hWnd, LPCWSTR pszINF, LPCWSTR pszSec, DWORD dwReserved)
{
    struct qemu_RebootCheckOnInstallW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REBOOTCHECKONINSTALLW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszINF = (ULONG_PTR)pszINF;
    call.pszSec = (ULONG_PTR)pszSec;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RebootCheckOnInstallW(struct qemu_syscall *call)
{
    struct qemu_RebootCheckOnInstallW *c = (struct qemu_RebootCheckOnInstallW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RebootCheckOnInstallW(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszINF), QEMU_G2H(c->pszSec), c->dwReserved);
}

#endif

struct qemu_RegisterOCX
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegisterOCX(HWND hWnd, HINSTANCE hInst, LPCSTR cmdline, INT show)
{
    struct qemu_RegisterOCX call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTEROCX);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterOCX to Wine headers? */
extern HRESULT WINAPI RegisterOCX(HWND hWnd, HINSTANCE hInst, LPCSTR cmdline, INT show);
void qemu_RegisterOCX(struct qemu_syscall *call)
{
    struct qemu_RegisterOCX *c = (struct qemu_RegisterOCX *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterOCX(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_SetPerUserSecValuesA
{
    struct qemu_syscall super;
    uint64_t pPerUser;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SetPerUserSecValuesA(PERUSERSECTIONA* pPerUser)
{
    struct qemu_SetPerUserSecValuesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPERUSERSECVALUESA);
    call.pPerUser = (ULONG_PTR)pPerUser;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPerUserSecValuesA(struct qemu_syscall *call)
{
    struct qemu_SetPerUserSecValuesA *c = (struct qemu_SetPerUserSecValuesA *)call;
    WINE_TRACE("\n");
    c->super.iret = SetPerUserSecValuesA(QEMU_G2H(c->pPerUser));
}

#endif

struct qemu_SetPerUserSecValuesW
{
    struct qemu_syscall super;
    uint64_t pPerUser;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SetPerUserSecValuesW(PERUSERSECTIONW* pPerUser)
{
    struct qemu_SetPerUserSecValuesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPERUSERSECVALUESW);
    call.pPerUser = (ULONG_PTR)pPerUser;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPerUserSecValuesW(struct qemu_syscall *call)
{
    struct qemu_SetPerUserSecValuesW *c = (struct qemu_SetPerUserSecValuesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPerUserSecValuesW(QEMU_G2H(c->pPerUser));
}

#endif

struct qemu_TranslateInfStringA
{
    struct qemu_syscall super;
    uint64_t pszInfFilename;
    uint64_t pszInstallSection;
    uint64_t pszTranslateSection;
    uint64_t pszTranslateKey;
    uint64_t pszBuffer;
    uint64_t dwBufferSize;
    uint64_t pdwRequiredSize;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI TranslateInfStringA(LPCSTR pszInfFilename, LPCSTR pszInstallSection, LPCSTR pszTranslateSection, LPCSTR pszTranslateKey, LPSTR pszBuffer, DWORD dwBufferSize, PDWORD pdwRequiredSize, PVOID pvReserved)
{
    struct qemu_TranslateInfStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEINFSTRINGA);
    call.pszInfFilename = (ULONG_PTR)pszInfFilename;
    call.pszInstallSection = (ULONG_PTR)pszInstallSection;
    call.pszTranslateSection = (ULONG_PTR)pszTranslateSection;
    call.pszTranslateKey = (ULONG_PTR)pszTranslateKey;
    call.pszBuffer = (ULONG_PTR)pszBuffer;
    call.dwBufferSize = (ULONG_PTR)dwBufferSize;
    call.pdwRequiredSize = (ULONG_PTR)pdwRequiredSize;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateInfStringA(struct qemu_syscall *call)
{
    struct qemu_TranslateInfStringA *c = (struct qemu_TranslateInfStringA *)call;
    WINE_TRACE("\n");
    c->super.iret = TranslateInfStringA(QEMU_G2H(c->pszInfFilename), QEMU_G2H(c->pszInstallSection), QEMU_G2H(c->pszTranslateSection), QEMU_G2H(c->pszTranslateKey), QEMU_G2H(c->pszBuffer), c->dwBufferSize, QEMU_G2H(c->pdwRequiredSize), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_TranslateInfStringW
{
    struct qemu_syscall super;
    uint64_t pszInfFilename;
    uint64_t pszInstallSection;
    uint64_t pszTranslateSection;
    uint64_t pszTranslateKey;
    uint64_t pszBuffer;
    uint64_t dwBufferSize;
    uint64_t pdwRequiredSize;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI TranslateInfStringW(LPCWSTR pszInfFilename, LPCWSTR pszInstallSection, LPCWSTR pszTranslateSection, LPCWSTR pszTranslateKey, LPWSTR pszBuffer, DWORD dwBufferSize, PDWORD pdwRequiredSize, PVOID pvReserved)
{
    struct qemu_TranslateInfStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEINFSTRINGW);
    call.pszInfFilename = (ULONG_PTR)pszInfFilename;
    call.pszInstallSection = (ULONG_PTR)pszInstallSection;
    call.pszTranslateSection = (ULONG_PTR)pszTranslateSection;
    call.pszTranslateKey = (ULONG_PTR)pszTranslateKey;
    call.pszBuffer = (ULONG_PTR)pszBuffer;
    call.dwBufferSize = (ULONG_PTR)dwBufferSize;
    call.pdwRequiredSize = (ULONG_PTR)pdwRequiredSize;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateInfStringW(struct qemu_syscall *call)
{
    struct qemu_TranslateInfStringW *c = (struct qemu_TranslateInfStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TranslateInfStringW(QEMU_G2H(c->pszInfFilename), QEMU_G2H(c->pszInstallSection), QEMU_G2H(c->pszTranslateSection), QEMU_G2H(c->pszTranslateKey), QEMU_G2H(c->pszBuffer), c->dwBufferSize, QEMU_G2H(c->pdwRequiredSize), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_TranslateInfStringExA
{
    struct qemu_syscall super;
    uint64_t hInf;
    uint64_t pszInfFilename;
    uint64_t pszTranslateSection;
    uint64_t pszTranslateKey;
    uint64_t pszBuffer;
    uint64_t dwBufferSize;
    uint64_t pdwRequiredSize;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI TranslateInfStringExA(HINF hInf, LPCSTR pszInfFilename, LPCSTR pszTranslateSection, LPCSTR pszTranslateKey, LPSTR pszBuffer, DWORD dwBufferSize, PDWORD pdwRequiredSize, PVOID pvReserved)
{
    struct qemu_TranslateInfStringExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEINFSTRINGEXA);
    call.hInf = (ULONG_PTR)hInf;
    call.pszInfFilename = (ULONG_PTR)pszInfFilename;
    call.pszTranslateSection = (ULONG_PTR)pszTranslateSection;
    call.pszTranslateKey = (ULONG_PTR)pszTranslateKey;
    call.pszBuffer = (ULONG_PTR)pszBuffer;
    call.dwBufferSize = (ULONG_PTR)dwBufferSize;
    call.pdwRequiredSize = (ULONG_PTR)pdwRequiredSize;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateInfStringExA(struct qemu_syscall *call)
{
    struct qemu_TranslateInfStringExA *c = (struct qemu_TranslateInfStringExA *)call;
    WINE_TRACE("\n");
    c->super.iret = TranslateInfStringExA(QEMU_G2H(c->hInf), QEMU_G2H(c->pszInfFilename), QEMU_G2H(c->pszTranslateSection), QEMU_G2H(c->pszTranslateKey), QEMU_G2H(c->pszBuffer), c->dwBufferSize, QEMU_G2H(c->pdwRequiredSize), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_TranslateInfStringExW
{
    struct qemu_syscall super;
    uint64_t hInf;
    uint64_t pszInfFilename;
    uint64_t pszTranslateSection;
    uint64_t pszTranslateKey;
    uint64_t pszBuffer;
    uint64_t dwBufferSize;
    uint64_t pdwRequiredSize;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI TranslateInfStringExW(HINF hInf, LPCWSTR pszInfFilename, LPCWSTR pszTranslateSection, LPCWSTR pszTranslateKey, LPWSTR pszBuffer, DWORD dwBufferSize, PDWORD pdwRequiredSize, PVOID pvReserved)
{
    struct qemu_TranslateInfStringExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEINFSTRINGEXW);
    call.hInf = (ULONG_PTR)hInf;
    call.pszInfFilename = (ULONG_PTR)pszInfFilename;
    call.pszTranslateSection = (ULONG_PTR)pszTranslateSection;
    call.pszTranslateKey = (ULONG_PTR)pszTranslateKey;
    call.pszBuffer = (ULONG_PTR)pszBuffer;
    call.dwBufferSize = (ULONG_PTR)dwBufferSize;
    call.pdwRequiredSize = (ULONG_PTR)pdwRequiredSize;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateInfStringExW(struct qemu_syscall *call)
{
    struct qemu_TranslateInfStringExW *c = (struct qemu_TranslateInfStringExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TranslateInfStringExW(QEMU_G2H(c->hInf), QEMU_G2H(c->pszInfFilename), QEMU_G2H(c->pszTranslateSection), QEMU_G2H(c->pszTranslateKey), QEMU_G2H(c->pszBuffer), c->dwBufferSize, QEMU_G2H(c->pdwRequiredSize), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_UserInstStubWrapperA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInstance;
    uint64_t pszParms;
    uint64_t nShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UserInstStubWrapperA(HWND hWnd, HINSTANCE hInstance, LPSTR pszParms, INT nShow)
{
    struct qemu_UserInstStubWrapperA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERINSTSTUBWRAPPERA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInstance = (ULONG_PTR)hInstance;
    call.pszParms = (ULONG_PTR)pszParms;
    call.nShow = (ULONG_PTR)nShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UserInstStubWrapperA(struct qemu_syscall *call)
{
    struct qemu_UserInstStubWrapperA *c = (struct qemu_UserInstStubWrapperA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserInstStubWrapperA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInstance), QEMU_G2H(c->pszParms), c->nShow);
}

#endif

struct qemu_UserInstStubWrapperW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInstance;
    uint64_t pszParms;
    uint64_t nShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UserInstStubWrapperW(HWND hWnd, HINSTANCE hInstance, LPWSTR pszParms, INT nShow)
{
    struct qemu_UserInstStubWrapperW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERINSTSTUBWRAPPERW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInstance = (ULONG_PTR)hInstance;
    call.pszParms = (ULONG_PTR)pszParms;
    call.nShow = (ULONG_PTR)nShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UserInstStubWrapperW(struct qemu_syscall *call)
{
    struct qemu_UserInstStubWrapperW *c = (struct qemu_UserInstStubWrapperW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserInstStubWrapperW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInstance), QEMU_G2H(c->pszParms), c->nShow);
}

#endif

struct qemu_UserUnInstStubWrapperA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInstance;
    uint64_t pszParms;
    uint64_t nShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UserUnInstStubWrapperA(HWND hWnd, HINSTANCE hInstance, LPSTR pszParms, INT nShow)
{
    struct qemu_UserUnInstStubWrapperA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERUNINSTSTUBWRAPPERA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInstance = (ULONG_PTR)hInstance;
    call.pszParms = (ULONG_PTR)pszParms;
    call.nShow = (ULONG_PTR)nShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UserUnInstStubWrapperA(struct qemu_syscall *call)
{
    struct qemu_UserUnInstStubWrapperA *c = (struct qemu_UserUnInstStubWrapperA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserUnInstStubWrapperA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInstance), QEMU_G2H(c->pszParms), c->nShow);
}

#endif

struct qemu_UserUnInstStubWrapperW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInstance;
    uint64_t pszParms;
    uint64_t nShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UserUnInstStubWrapperW(HWND hWnd, HINSTANCE hInstance, LPWSTR pszParms, INT nShow)
{
    struct qemu_UserUnInstStubWrapperW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERUNINSTSTUBWRAPPERW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInstance = (ULONG_PTR)hInstance;
    call.pszParms = (ULONG_PTR)pszParms;
    call.nShow = (ULONG_PTR)nShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UserUnInstStubWrapperW(struct qemu_syscall *call)
{
    struct qemu_UserUnInstStubWrapperW *c = (struct qemu_UserUnInstStubWrapperW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserUnInstStubWrapperW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInstance), QEMU_G2H(c->pszParms), c->nShow);
}

#endif

