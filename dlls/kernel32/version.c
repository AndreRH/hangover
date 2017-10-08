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

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetVersion(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETVERSION);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetVersion(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetVersion();
}

#endif

struct qemu_GetVersionExA
{
    struct qemu_syscall super;
    uint64_t v;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVersionExA(OSVERSIONINFOA *v)
{
    struct qemu_GetVersionExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONEXA);
    call.v = (ULONG_PTR)v;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_GetVersionExA(struct qemu_syscall *call)
{
    struct qemu_GetVersionExA *c = (struct qemu_GetVersionExA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVersionExA(QEMU_G2H(c->v));
}

#endif

struct qemu_GetVersionExW
{
    struct qemu_syscall super;
    uint64_t v;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVersionExW(OSVERSIONINFOW *v)
{
    struct qemu_GetVersionExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONEXW);
    call.v = (ULONG_PTR)v;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_GetVersionExW(struct qemu_syscall *call)
{
    struct qemu_GetVersionExW *c = (struct qemu_GetVersionExW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVersionExW(QEMU_G2H(c->v));
}

#endif

struct qemu_VerifyVersionInfoA
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t type_mask;
    uint64_t condition_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerifyVersionInfoA(OSVERSIONINFOEXA *info, DWORD type_mask,
                                          DWORDLONG condition_mask)
{
    struct qemu_VerifyVersionInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERIFYVERSIONINFOA);
    call.info = (ULONG_PTR)info;
    call.type_mask = (ULONG_PTR)type_mask;
    call.condition_mask = (ULONG_PTR)condition_mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerifyVersionInfoA(struct qemu_syscall *call)
{
    struct qemu_VerifyVersionInfoA *c = (struct qemu_VerifyVersionInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = VerifyVersionInfoA(QEMU_G2H(c->info), c->type_mask, c->condition_mask);
}

#endif

struct qemu_VerifyVersionInfoW
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t type_mask;
    uint64_t condition_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerifyVersionInfoW(LPOSVERSIONINFOEXW info, DWORD type_mask,
                                          DWORDLONG condition_mask)
{
    struct qemu_VerifyVersionInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERIFYVERSIONINFOW);
    call.info = (ULONG_PTR)info;
    call.type_mask = (ULONG_PTR)type_mask;
    call.condition_mask = (ULONG_PTR)condition_mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerifyVersionInfoW(struct qemu_syscall *call)
{
    struct qemu_VerifyVersionInfoW *c = (struct qemu_VerifyVersionInfoW *)call;
    WINE_TRACE("\n");
    c->super.iret = VerifyVersionInfoW(QEMU_G2H(c->info), c->type_mask, c->condition_mask);
}

#endif

struct qemu_TermsrvAppInstallMode
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TermsrvAppInstallMode(void)
{
    struct qemu_TermsrvAppInstallMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TERMSRVAPPINSTALLMODE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add TermsrvAppInstallMode to Wine headers? */
extern BOOL WINAPI TermsrvAppInstallMode(void);
void qemu_TermsrvAppInstallMode(struct qemu_syscall *call)
{
    struct qemu_TermsrvAppInstallMode *c = (struct qemu_TermsrvAppInstallMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TermsrvAppInstallMode();
}

#endif

struct qemu_SetTermsrvAppInstallMode
{
    struct qemu_syscall super;
    uint64_t bInstallMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetTermsrvAppInstallMode(BOOL bInstallMode)
{
    struct qemu_SetTermsrvAppInstallMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTERMSRVAPPINSTALLMODE);
    call.bInstallMode = (ULONG_PTR)bInstallMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetTermsrvAppInstallMode to Wine headers? */
extern DWORD WINAPI SetTermsrvAppInstallMode(BOOL bInstallMode);
void qemu_SetTermsrvAppInstallMode(struct qemu_syscall *call)
{
    struct qemu_SetTermsrvAppInstallMode *c = (struct qemu_SetTermsrvAppInstallMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetTermsrvAppInstallMode(c->bInstallMode);
}

#endif

struct qemu_GetProductInfo
{
    struct qemu_syscall super;
    uint64_t dwOSMajorVersion;
    uint64_t dwOSMinorVersion;
    uint64_t dwSpMajorVersion;
    uint64_t dwSpMinorVersion;
    uint64_t pdwReturnedProductType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProductInfo(DWORD dwOSMajorVersion, DWORD dwOSMinorVersion, DWORD dwSpMajorVersion, DWORD dwSpMinorVersion, PDWORD pdwReturnedProductType)
{
    struct qemu_GetProductInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRODUCTINFO);
    call.dwOSMajorVersion = dwOSMajorVersion;
    call.dwOSMinorVersion = dwOSMinorVersion;
    call.dwSpMajorVersion = dwSpMajorVersion;
    call.dwSpMinorVersion = dwSpMinorVersion;
    call.pdwReturnedProductType = (ULONG_PTR)pdwReturnedProductType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProductInfo(struct qemu_syscall *call)
{
    struct qemu_GetProductInfo *c = (struct qemu_GetProductInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetProductInfo(c->dwOSMajorVersion, c->dwOSMinorVersion, c->dwSpMajorVersion, c->dwSpMinorVersion, QEMU_G2H(c->pdwReturnedProductType));
}

#endif

struct qemu_GetCurrentPackageId
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI GetCurrentPackageId(UINT32 *len, BYTE *buffer)
{
    struct qemu_GetCurrentPackageId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPACKAGEID);
    call.len = (ULONG_PTR)len;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetCurrentPackageId to Wine headers? */
extern LONG WINAPI GetCurrentPackageId(UINT32 *len, BYTE *buffer);
void qemu_GetCurrentPackageId(struct qemu_syscall *call)
{
    struct qemu_GetCurrentPackageId *c = (struct qemu_GetCurrentPackageId *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCurrentPackageId(QEMU_G2H(c->len), QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetCurrentPackageFamilyName
{
    struct qemu_syscall super;
    uint64_t length;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI GetCurrentPackageFamilyName(UINT32 *length, PWSTR name)
{
    struct qemu_GetCurrentPackageFamilyName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPACKAGEFAMILYNAME);
    call.length = (ULONG_PTR)length;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetCurrentPackageFamilyName to Wine headers? */
extern LONG WINAPI GetCurrentPackageFamilyName(UINT32 *length, PWSTR name);
void qemu_GetCurrentPackageFamilyName(struct qemu_syscall *call)
{
    struct qemu_GetCurrentPackageFamilyName *c = (struct qemu_GetCurrentPackageFamilyName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentPackageFamilyName(QEMU_G2H(c->length), QEMU_G2H(c->name));
}

#endif

struct qemu_GetCurrentPackageFullName
{
    struct qemu_syscall super;
    uint64_t length;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI GetCurrentPackageFullName(UINT32 *length, PWSTR name)
{
    struct qemu_GetCurrentPackageFullName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPACKAGEFULLNAME);
    call.length = (ULONG_PTR)length;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetCurrentPackageFullName to Wine headers? */
extern LONG WINAPI GetCurrentPackageFullName(UINT32 *length, PWSTR name);
void qemu_GetCurrentPackageFullName(struct qemu_syscall *call)
{
    struct qemu_GetCurrentPackageFullName *c = (struct qemu_GetCurrentPackageFullName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentPackageFullName(QEMU_G2H(c->length), QEMU_G2H(c->name));
}

#endif

struct qemu_GetPackageFullName
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t length;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI GetPackageFullName(HANDLE process, UINT32 *length, PWSTR name)
{
    struct qemu_GetPackageFullName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPACKAGEFULLNAME);
    call.process = (ULONG_PTR)process;
    call.length = (ULONG_PTR)length;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetPackageFullName to Wine headers? */
extern LONG WINAPI GetPackageFullName(HANDLE process, UINT32 *length, PWSTR name);
void qemu_GetPackageFullName(struct qemu_syscall *call)
{
    struct qemu_GetPackageFullName *c = (struct qemu_GetPackageFullName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPackageFullName(QEMU_G2H(c->process), QEMU_G2H(c->length), QEMU_G2H(c->name));
}

#endif
