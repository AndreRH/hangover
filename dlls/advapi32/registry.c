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
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_RegOverridePredefKey
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t override;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOverridePredefKey(HKEY hkey, HKEY override)
{
    struct qemu_RegOverridePredefKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOVERRIDEPREDEFKEY);
    call.hkey = (LONG_PTR)hkey;
    call.override = (LONG_PTR)override;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegOverridePredefKey(struct qemu_syscall *call)
{
    struct qemu_RegOverridePredefKey *c = (struct qemu_RegOverridePredefKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegOverridePredefKey(QEMU_G2H(c->hkey), QEMU_G2H(c->override));
}

#endif

struct qemu_RegCreateKeyExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t class;
    uint64_t options;
    uint64_t access;
    uint64_t sa;
    uint64_t retkey;
    uint64_t dispos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCreateKeyExW(HKEY hkey, LPCWSTR name, DWORD reserved, LPWSTR class, DWORD options, REGSAM access, SECURITY_ATTRIBUTES *sa, PHKEY retkey, LPDWORD dispos)
{
    struct qemu_RegCreateKeyExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCREATEKEYEXW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.class = (ULONG_PTR)class;
    call.options = (ULONG_PTR)options;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;
    call.dispos = (ULONG_PTR)dispos;

    qemu_syscall(&call.super);

    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegCreateKeyExW(struct qemu_syscall *call)
{
    struct qemu_RegCreateKeyExW *c = (struct qemu_RegCreateKeyExW *)call;
    HKEY retkey = 0;
    WINE_TRACE("\n");
    c->super.iret = RegCreateKeyExW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->reserved, QEMU_G2H(c->class), c->options, c->access, QEMU_G2H(c->sa), &retkey, QEMU_G2H(c->dispos));

    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegCreateKeyExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t class;
    uint64_t options;
    uint64_t access;
    uint64_t sa;
    uint64_t retkey;
    uint64_t dispos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCreateKeyExA(HKEY hkey, LPCSTR name, DWORD reserved, char *class, DWORD options,
        REGSAM access, SECURITY_ATTRIBUTES *sa, PHKEY retkey, LPDWORD dispos)
{
    struct qemu_RegCreateKeyExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCREATEKEYEXA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = reserved;
    call.class = (ULONG_PTR)class;
    call.options = options;
    call.access = access;
    call.sa = (ULONG_PTR)sa;
    call.dispos = (ULONG_PTR)dispos;

    qemu_syscall(&call.super);

    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegCreateKeyExA(struct qemu_syscall *call)
{
    struct qemu_RegCreateKeyExA *c = (struct qemu_RegCreateKeyExA *)call;
    HKEY retkey = 0;
    WINE_TRACE("\n");

    c->super.iret = RegCreateKeyExA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->reserved, QEMU_G2H(c->class),
            c->options, c->access, QEMU_G2H(c->sa), &retkey, QEMU_G2H(c->dispos));
    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegCreateKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
    uint64_t phkResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCreateKeyW(HKEY hkey, LPCWSTR lpSubKey, PHKEY phkResult)
{
    struct qemu_RegCreateKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCREATEKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *phkResult = (HKEY)(ULONG_PTR)call.phkResult;

    return call.super.iret;
}

#else

void qemu_RegCreateKeyW(struct qemu_syscall *call)
{
    struct qemu_RegCreateKeyW *c = (struct qemu_RegCreateKeyW *)call;
    HKEY retkey;
    WINE_FIXME("Unverified!\n");

    c->super.iret = RegCreateKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey), &retkey);
    c->phkResult = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegCreateKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
    uint64_t phkResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCreateKeyA(HKEY hkey, LPCSTR lpSubKey, PHKEY phkResult)
{
    struct qemu_RegCreateKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCREATEKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *phkResult = (HKEY)(ULONG_PTR)call.phkResult;

    return call.super.iret;
}

#else

void qemu_RegCreateKeyA(struct qemu_syscall *call)
{
    struct qemu_RegCreateKeyA *c = (struct qemu_RegCreateKeyA *)call;
    HKEY retkey;
    WINE_TRACE("\n");

    c->super.iret = RegCreateKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey), &retkey);
    c->phkResult = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegCreateKeyTransactedW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t class;
    uint64_t options;
    uint64_t access;
    uint64_t sa;
    uint64_t retkey;
    uint64_t dispos;
    uint64_t transaction;
    uint64_t reserved2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCreateKeyTransactedW(HKEY hkey, LPCWSTR name, DWORD reserved, LPWSTR class, DWORD options, REGSAM access, SECURITY_ATTRIBUTES *sa, PHKEY retkey, LPDWORD dispos, HANDLE transaction, PVOID reserved2)
{
    struct qemu_RegCreateKeyTransactedW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCREATEKEYTRANSACTEDW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.class = (ULONG_PTR)class;
    call.options = (ULONG_PTR)options;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;
    call.dispos = (ULONG_PTR)dispos;
    call.transaction = (ULONG_PTR)transaction;
    call.reserved2 = (ULONG_PTR)reserved2;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

/* TODO: Add RegCreateKeyTransactedW to Wine headers? */
extern LSTATUS WINAPI RegCreateKeyTransactedW(HKEY hkey, LPCWSTR name, DWORD reserved, LPWSTR class, DWORD options, REGSAM access, SECURITY_ATTRIBUTES *sa, PHKEY retkey, LPDWORD dispos, HANDLE transaction, PVOID reserved2);
void qemu_RegCreateKeyTransactedW(struct qemu_syscall *call)
{
    struct qemu_RegCreateKeyTransactedW *c = (struct qemu_RegCreateKeyTransactedW *)call;
    HKEY retkey;
    WINE_FIXME("Unverified!\n");

    c->super.iret = RegCreateKeyTransactedW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->reserved,
            QEMU_G2H(c->class), c->options, c->access, QEMU_G2H(c->sa), &retkey,
            QEMU_G2H(c->dispos), QEMU_G2H(c->transaction), QEMU_G2H(c->reserved2));
    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegCreateKeyTransactedA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t class;
    uint64_t options;
    uint64_t access;
    uint64_t sa;
    uint64_t retkey;
    uint64_t dispos;
    uint64_t transaction;
    uint64_t reserved2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCreateKeyTransactedA(HKEY hkey, LPCSTR name, DWORD reserved, LPSTR class, DWORD options, REGSAM access, SECURITY_ATTRIBUTES *sa, PHKEY retkey, LPDWORD dispos, HANDLE transaction, PVOID reserved2)
{
    struct qemu_RegCreateKeyTransactedA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCREATEKEYTRANSACTEDA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.class = (ULONG_PTR)class;
    call.options = (ULONG_PTR)options;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;
    call.dispos = (ULONG_PTR)dispos;
    call.transaction = (ULONG_PTR)transaction;
    call.reserved2 = (ULONG_PTR)reserved2;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

/* TODO: Add RegCreateKeyTransactedA to Wine headers? */
extern LSTATUS WINAPI RegCreateKeyTransactedA(HKEY hkey, LPCSTR name, DWORD reserved, LPSTR class, DWORD options, REGSAM access, SECURITY_ATTRIBUTES *sa, PHKEY retkey, LPDWORD dispos, HANDLE transaction, PVOID reserved2);
void qemu_RegCreateKeyTransactedA(struct qemu_syscall *call)
{
    struct qemu_RegCreateKeyTransactedA *c = (struct qemu_RegCreateKeyTransactedA *)call;
    HKEY retkey;
    WINE_FIXME("Unverified!\n");

    c->super.iret = RegCreateKeyTransactedA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->reserved, QEMU_G2H(c->class),
            c->options, c->access, QEMU_G2H(c->sa), &retkey, QEMU_G2H(c->dispos), QEMU_G2H(c->transaction),
            QEMU_G2H(c->reserved2));
    c->retkey = QEMU_H2G(retkey);
}

#endif

struct qemu_RegOpenKeyExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t options;
    uint64_t access;
    uint64_t retkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOpenKeyExW(HKEY hkey, LPCWSTR name, DWORD options, REGSAM access, PHKEY retkey)
{
    struct qemu_RegOpenKeyExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENKEYEXW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.options = (ULONG_PTR)options;
    call.access = (ULONG_PTR)access;

    if (!retkey)
        return ERROR_INVALID_PARAMETER;

    qemu_syscall(&call.super);

    *retkey = (HKEY)(LONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegOpenKeyExW(struct qemu_syscall *call)
{
    struct qemu_RegOpenKeyExW *c = (struct qemu_RegOpenKeyExW *)call;
    HKEY retkey = 0;
    WINE_TRACE("\n");
    c->super.iret = RegOpenKeyExW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->options, c->access, &retkey);

    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegOpenKeyExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t options;
    uint64_t access;
    uint64_t retkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOpenKeyExA(HKEY hkey, LPCSTR name, DWORD options, REGSAM access, PHKEY retkey)
{
    struct qemu_RegOpenKeyExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENKEYEXA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.options = options;
    call.access = access;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegOpenKeyExA(struct qemu_syscall *call)
{
    struct qemu_RegOpenKeyExA *c = (struct qemu_RegOpenKeyExA *)call;
    HKEY retkey = 0;
    WINE_TRACE("\n");

    c->super.iret = RegOpenKeyExA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->options, c->access, &retkey);
    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegOpenKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t retkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOpenKeyW(HKEY hkey, LPCWSTR name, PHKEY retkey)
{
    struct qemu_RegOpenKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegOpenKeyW(struct qemu_syscall *call)
{
    struct qemu_RegOpenKeyW *c = (struct qemu_RegOpenKeyW *)call;
    HKEY retkey = 0;
    WINE_TRACE("\n");

    c->super.iret = RegOpenKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), &retkey);
    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegOpenKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t retkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOpenKeyA(HKEY hkey, LPCSTR name, PHKEY retkey)
{
    struct qemu_RegOpenKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegOpenKeyA(struct qemu_syscall *call)
{
    struct qemu_RegOpenKeyA *c = (struct qemu_RegOpenKeyA *)call;
    HKEY retkey = 0;
    WINE_TRACE("\n");

    c->super.iret = RegOpenKeyA((HKEY)c->hkey, QEMU_G2H(c->name), &retkey);
    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegOpenCurrentUser
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t retkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOpenCurrentUser(REGSAM access, PHKEY retkey)
{
    struct qemu_RegOpenCurrentUser call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENCURRENTUSER);
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    if (call.super.iret == ERROR_SUCCESS)
        *retkey = (HKEY)(ULONG_PTR)call.retkey;

    return call.super.iret;
}

#else

void qemu_RegOpenCurrentUser(struct qemu_syscall *call)
{
    struct qemu_RegOpenCurrentUser *c = (struct qemu_RegOpenCurrentUser *)call;
    HKEY retkey = 0;
    WINE_FIXME("Unverified!\n");

    c->super.iret = RegOpenCurrentUser(c->access, &retkey);
    c->retkey = (ULONG_PTR)retkey;
}

#endif

struct qemu_RegEnumKeyExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t index;
    uint64_t name;
    uint64_t name_len;
    uint64_t reserved;
    uint64_t class;
    uint64_t class_len;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegEnumKeyExW(HKEY hkey, DWORD index, LPWSTR name, LPDWORD name_len, LPDWORD reserved, LPWSTR class, LPDWORD class_len, FILETIME *ft)
{
    struct qemu_RegEnumKeyExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGENUMKEYEXW);
    call.hkey = (LONG_PTR)hkey;
    call.index = (ULONG_PTR)index;
    call.name = (ULONG_PTR)name;
    call.name_len = (ULONG_PTR)name_len;
    call.reserved = (ULONG_PTR)reserved;
    call.class = (ULONG_PTR)class;
    call.class_len = (ULONG_PTR)class_len;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegEnumKeyExW(struct qemu_syscall *call)
{
    struct qemu_RegEnumKeyExW *c = (struct qemu_RegEnumKeyExW *)call;
    WINE_TRACE("\n");
    c->super.iret = RegEnumKeyExW(QEMU_G2H(c->hkey), c->index, QEMU_G2H(c->name), QEMU_G2H(c->name_len), QEMU_G2H(c->reserved), QEMU_G2H(c->class), QEMU_G2H(c->class_len), QEMU_G2H(c->ft));
}

#endif

struct qemu_RegEnumKeyExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t index;
    uint64_t name;
    uint64_t name_len;
    uint64_t reserved;
    uint64_t class;
    uint64_t class_len;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegEnumKeyExA(HKEY hkey, DWORD index, char *name, DWORD *name_len, DWORD *reserved,
        char *class, DWORD *class_len, FILETIME *ft)
{
    struct qemu_RegEnumKeyExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGENUMKEYEXA);
    call.hkey = (LONG_PTR)hkey;
    call.index = (ULONG_PTR)index;
    call.name = (ULONG_PTR)name;
    call.name_len = (ULONG_PTR)name_len;
    call.reserved = (ULONG_PTR)reserved;
    call.class = (ULONG_PTR)class;
    call.class_len = (ULONG_PTR)class_len;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegEnumKeyExA(struct qemu_syscall *call)
{
    struct qemu_RegEnumKeyExA *c = (struct qemu_RegEnumKeyExA *)call;
    WINE_TRACE("\n");
    c->super.iret = RegEnumKeyExA(QEMU_G2H(c->hkey), c->index, QEMU_G2H(c->name), QEMU_G2H(c->name_len),
            QEMU_G2H(c->reserved), QEMU_G2H(c->class), QEMU_G2H(c->class_len), QEMU_G2H(c->ft));
}

#endif

struct qemu_RegEnumKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t index;
    uint64_t name;
    uint64_t name_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegEnumKeyW(HKEY hkey, DWORD index, LPWSTR name, DWORD name_len)
{
    struct qemu_RegEnumKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGENUMKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.index = (ULONG_PTR)index;
    call.name = (ULONG_PTR)name;
    call.name_len = (ULONG_PTR)name_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegEnumKeyW(struct qemu_syscall *call)
{
    struct qemu_RegEnumKeyW *c = (struct qemu_RegEnumKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegEnumKeyW(QEMU_G2H(c->hkey), c->index, QEMU_G2H(c->name), c->name_len);
}

#endif

struct qemu_RegEnumKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t index;
    uint64_t name;
    uint64_t name_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegEnumKeyA(HKEY hkey, DWORD index, LPSTR name, DWORD name_len)
{
    struct qemu_RegEnumKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGENUMKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.index = (ULONG_PTR)index;
    call.name = (ULONG_PTR)name;
    call.name_len = (ULONG_PTR)name_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegEnumKeyA(struct qemu_syscall *call)
{
    struct qemu_RegEnumKeyA *c = (struct qemu_RegEnumKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegEnumKeyA(QEMU_G2H(c->hkey), c->index, QEMU_G2H(c->name), c->name_len);
}

#endif

struct qemu_RegQueryInfoKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t class;
    uint64_t class_len;
    uint64_t reserved;
    uint64_t subkeys;
    uint64_t max_subkey;
    uint64_t max_class;
    uint64_t values;
    uint64_t max_value;
    uint64_t max_data;
    uint64_t security;
    uint64_t modif;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryInfoKeyW(HKEY hkey, LPWSTR class, LPDWORD class_len, LPDWORD reserved, LPDWORD subkeys, LPDWORD max_subkey, LPDWORD max_class, LPDWORD values, LPDWORD max_value, LPDWORD max_data, LPDWORD security, FILETIME *modif)
{
    struct qemu_RegQueryInfoKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYINFOKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.class = (ULONG_PTR)class;
    call.class_len = (ULONG_PTR)class_len;
    call.reserved = (ULONG_PTR)reserved;
    call.subkeys = (ULONG_PTR)subkeys;
    call.max_subkey = (ULONG_PTR)max_subkey;
    call.max_class = (ULONG_PTR)max_class;
    call.values = (ULONG_PTR)values;
    call.max_value = (ULONG_PTR)max_value;
    call.max_data = (ULONG_PTR)max_data;
    call.security = (ULONG_PTR)security;
    call.modif = (ULONG_PTR)modif;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryInfoKeyW(struct qemu_syscall *call)
{
    struct qemu_RegQueryInfoKeyW *c = (struct qemu_RegQueryInfoKeyW *)call;
    WINE_TRACE("\n");
    c->super.iret = RegQueryInfoKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->class), QEMU_G2H(c->class_len), QEMU_G2H(c->reserved), QEMU_G2H(c->subkeys), QEMU_G2H(c->max_subkey), QEMU_G2H(c->max_class), QEMU_G2H(c->values), QEMU_G2H(c->max_value), QEMU_G2H(c->max_data), QEMU_G2H(c->security), QEMU_G2H(c->modif));
}

#endif

struct qemu_RegQueryMultipleValuesA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t val_list;
    uint64_t num_vals;
    uint64_t lpValueBuf;
    uint64_t ldwTotsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryMultipleValuesA(HKEY hkey, PVALENTA val_list, DWORD num_vals, LPSTR lpValueBuf, LPDWORD ldwTotsize)
{
    struct qemu_RegQueryMultipleValuesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYMULTIPLEVALUESA);
    call.hkey = (LONG_PTR)hkey;
    call.val_list = (ULONG_PTR)val_list;
    call.num_vals = (ULONG_PTR)num_vals;
    call.lpValueBuf = (ULONG_PTR)lpValueBuf;
    call.ldwTotsize = (ULONG_PTR)ldwTotsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryMultipleValuesA(struct qemu_syscall *call)
{
    struct qemu_RegQueryMultipleValuesA *c = (struct qemu_RegQueryMultipleValuesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegQueryMultipleValuesA(QEMU_G2H(c->hkey), QEMU_G2H(c->val_list), c->num_vals, QEMU_G2H(c->lpValueBuf), QEMU_G2H(c->ldwTotsize));
}

#endif

struct qemu_RegQueryMultipleValuesW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t val_list;
    uint64_t num_vals;
    uint64_t lpValueBuf;
    uint64_t ldwTotsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryMultipleValuesW(HKEY hkey, PVALENTW val_list, DWORD num_vals, LPWSTR lpValueBuf, LPDWORD ldwTotsize)
{
    struct qemu_RegQueryMultipleValuesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYMULTIPLEVALUESW);
    call.hkey = (LONG_PTR)hkey;
    call.val_list = (ULONG_PTR)val_list;
    call.num_vals = (ULONG_PTR)num_vals;
    call.lpValueBuf = (ULONG_PTR)lpValueBuf;
    call.ldwTotsize = (ULONG_PTR)ldwTotsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryMultipleValuesW(struct qemu_syscall *call)
{
    struct qemu_RegQueryMultipleValuesW *c = (struct qemu_RegQueryMultipleValuesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegQueryMultipleValuesW(QEMU_G2H(c->hkey), QEMU_G2H(c->val_list), c->num_vals, QEMU_G2H(c->lpValueBuf), QEMU_G2H(c->ldwTotsize));
}

#endif

struct qemu_RegQueryInfoKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t class;
    uint64_t class_len;
    uint64_t reserved;
    uint64_t subkeys;
    uint64_t max_subkey;
    uint64_t max_class;
    uint64_t values;
    uint64_t max_value;
    uint64_t max_data;
    uint64_t security;
    uint64_t modif;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryInfoKeyA(HKEY hkey, LPSTR class, LPDWORD class_len, LPDWORD reserved, LPDWORD subkeys, LPDWORD max_subkey, LPDWORD max_class, LPDWORD values, LPDWORD max_value, LPDWORD max_data, LPDWORD security, FILETIME *modif)
{
    struct qemu_RegQueryInfoKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYINFOKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.class = (ULONG_PTR)class;
    call.class_len = (ULONG_PTR)class_len;
    call.reserved = (ULONG_PTR)reserved;
    call.subkeys = (ULONG_PTR)subkeys;
    call.max_subkey = (ULONG_PTR)max_subkey;
    call.max_class = (ULONG_PTR)max_class;
    call.values = (ULONG_PTR)values;
    call.max_value = (ULONG_PTR)max_value;
    call.max_data = (ULONG_PTR)max_data;
    call.security = (ULONG_PTR)security;
    call.modif = (ULONG_PTR)modif;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryInfoKeyA(struct qemu_syscall *call)
{
    struct qemu_RegQueryInfoKeyA *c = (struct qemu_RegQueryInfoKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegQueryInfoKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->class), QEMU_G2H(c->class_len), QEMU_G2H(c->reserved), QEMU_G2H(c->subkeys), QEMU_G2H(c->max_subkey), QEMU_G2H(c->max_class), QEMU_G2H(c->values), QEMU_G2H(c->max_value), QEMU_G2H(c->max_data), QEMU_G2H(c->security), QEMU_G2H(c->modif));
}

#endif

struct qemu_RegCloseKey
{
    struct qemu_syscall super;
    uint64_t hkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegCloseKey(HKEY hkey)
{
    struct qemu_RegCloseKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCLOSEKEY);
    call.hkey = (LONG_PTR)hkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegCloseKey(struct qemu_syscall *call)
{
    struct qemu_RegCloseKey *c = (struct qemu_RegCloseKey *)call;
    WINE_TRACE("\n");
    c->super.iret = RegCloseKey(QEMU_G2H(c->hkey));
}

#endif

struct qemu_RegDeleteKeyExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t access;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteKeyExW(HKEY hkey, LPCWSTR name, REGSAM access, DWORD reserved)
{
    struct qemu_RegDeleteKeyExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEKEYEXW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.access = (ULONG_PTR)access;
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteKeyExW(struct qemu_syscall *call)
{
    struct qemu_RegDeleteKeyExW *c = (struct qemu_RegDeleteKeyExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteKeyExW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->access, c->reserved);
}

#endif

struct qemu_RegDeleteKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteKeyW(HKEY hkey, LPCWSTR name)
{
    struct qemu_RegDeleteKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteKeyW(struct qemu_syscall *call)
{
    struct qemu_RegDeleteKeyW *c = (struct qemu_RegDeleteKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->name));
}

#endif

struct qemu_RegDeleteKeyExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t access;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteKeyExA(HKEY hkey, LPCSTR name, REGSAM access, DWORD reserved)
{
    struct qemu_RegDeleteKeyExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEKEYEXA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.access = (ULONG_PTR)access;
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteKeyExA(struct qemu_syscall *call)
{
    struct qemu_RegDeleteKeyExA *c = (struct qemu_RegDeleteKeyExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteKeyExA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->access, c->reserved);
}

#endif

struct qemu_RegDeleteKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteKeyA(HKEY hkey, LPCSTR name)
{
    struct qemu_RegDeleteKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteKeyA(struct qemu_syscall *call)
{
    struct qemu_RegDeleteKeyA *c = (struct qemu_RegDeleteKeyA *)call;
    WINE_TRACE("\n");
    c->super.iret = RegDeleteKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->name));
}

#endif

struct qemu_RegSetValueExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSetValueExW(HKEY hkey, LPCWSTR name, DWORD reserved, DWORD type, const BYTE *data, DWORD count)
{
    struct qemu_RegSetValueExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETVALUEEXW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetValueExW(struct qemu_syscall *call)
{
    struct qemu_RegSetValueExW *c = (struct qemu_RegSetValueExW *)call;
    WINE_TRACE("\n");
    c->super.iret = RegSetValueExW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->reserved, c->type, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_RegSetValueExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSetValueExA(HKEY hkey, LPCSTR name, DWORD reserved, DWORD type, const BYTE *data, DWORD count)
{
    struct qemu_RegSetValueExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETVALUEEXA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = reserved;
    call.type = type;
    call.data = (ULONG_PTR)data;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetValueExA(struct qemu_syscall *call)
{
    struct qemu_RegSetValueExA *c = (struct qemu_RegSetValueExA *)call;
    WINE_TRACE("\n");
    c->super.iret = RegSetValueExA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), c->reserved, c->type, QEMU_G2H(c->data),
            c->count);
}

#endif

struct qemu_RegSetValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSetValueW(HKEY hkey, LPCWSTR subkey, DWORD type, LPCWSTR data, DWORD count)
{
    struct qemu_RegSetValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETVALUEW);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetValueW(struct qemu_syscall *call)
{
    struct qemu_RegSetValueW *c = (struct qemu_RegSetValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSetValueW(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), c->type, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_RegSetValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSetValueA(HKEY hkey, LPCSTR subkey, DWORD type, LPCSTR data, DWORD count)
{
    struct qemu_RegSetValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETVALUEA);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetValueA(struct qemu_syscall *call)
{
    struct qemu_RegSetValueA *c = (struct qemu_RegSetValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSetValueA(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), c->type, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_RegSetKeyValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t name;
    uint64_t type;
    uint64_t data;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegSetKeyValueW(HKEY hkey, LPCWSTR subkey, LPCWSTR name, DWORD type, const void *data, DWORD len)
{
    struct qemu_RegSetKeyValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETKEYVALUEW);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.name = (ULONG_PTR)name;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetKeyValueW(struct qemu_syscall *call)
{
    struct qemu_RegSetKeyValueW *c = (struct qemu_RegSetKeyValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSetKeyValueW(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), QEMU_G2H(c->name), c->type, QEMU_G2H(c->data), c->len);
}

#endif

struct qemu_RegSetKeyValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t name;
    uint64_t type;
    uint64_t data;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegSetKeyValueA(HKEY hkey, LPCSTR subkey, LPCSTR name, DWORD type, const void *data, DWORD len)
{
    struct qemu_RegSetKeyValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETKEYVALUEA);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.name = (ULONG_PTR)name;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetKeyValueA(struct qemu_syscall *call)
{
    struct qemu_RegSetKeyValueA *c = (struct qemu_RegSetKeyValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSetKeyValueA(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), QEMU_G2H(c->name), c->type, QEMU_G2H(c->data), c->len);
}

#endif

struct qemu_RegQueryValueExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryValueExW(HKEY hkey, LPCWSTR name, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD count)
{
    struct qemu_RegQueryValueExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYVALUEEXW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryValueExW(struct qemu_syscall *call)
{
    struct qemu_RegQueryValueExW *c = (struct qemu_RegQueryValueExW *)call;
    WINE_TRACE("\n");
    c->super.iret = RegQueryValueExW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), QEMU_G2H(c->reserved), QEMU_G2H(c->type), QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif

struct qemu_RegQueryValueExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryValueExA(HKEY hkey, LPCSTR name, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD count)
{
    struct qemu_RegQueryValueExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYVALUEEXA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryValueExA(struct qemu_syscall *call)
{
    struct qemu_RegQueryValueExA *c = (struct qemu_RegQueryValueExA *)call;
    WINE_TRACE("\n");
    c->super.iret = RegQueryValueExA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), QEMU_G2H(c->reserved), QEMU_G2H(c->type),
            QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif

struct qemu_RegQueryValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryValueW(HKEY hkey, LPCWSTR name, LPWSTR data, LPLONG count)
{
    struct qemu_RegQueryValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYVALUEW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryValueW(struct qemu_syscall *call)
{
    struct qemu_RegQueryValueW *c = (struct qemu_RegQueryValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegQueryValueW(QEMU_G2H(c->hkey), QEMU_G2H(c->name), QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif

struct qemu_RegQueryValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegQueryValueA(HKEY hkey, LPCSTR name, LPSTR data, LPLONG count)
{
    struct qemu_RegQueryValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYVALUEA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryValueA(struct qemu_syscall *call)
{
    struct qemu_RegQueryValueA *c = (struct qemu_RegQueryValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegQueryValueA(QEMU_G2H(c->hkey), QEMU_G2H(c->name), QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif

struct qemu_RegGetValueW
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pszSubKey;
    uint64_t pszValue;
    uint64_t dwFlags;
    uint64_t pdwType;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegGetValueW(HKEY hKey, LPCWSTR pszSubKey, LPCWSTR pszValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{
    struct qemu_RegGetValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGGETVALUEW);
    call.hKey = (ULONG_PTR)hKey;
    call.pszSubKey = (ULONG_PTR)pszSubKey;
    call.pszValue = (ULONG_PTR)pszValue;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pdwType = (ULONG_PTR)pdwType;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegGetValueW(struct qemu_syscall *call)
{
    struct qemu_RegGetValueW *c = (struct qemu_RegGetValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegGetValueW(QEMU_G2H(c->hKey), QEMU_G2H(c->pszSubKey), QEMU_G2H(c->pszValue), c->dwFlags, QEMU_G2H(c->pdwType), QEMU_G2H(c->pvData), QEMU_G2H(c->pcbData));
}

#endif

struct qemu_RegGetValueA
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pszSubKey;
    uint64_t pszValue;
    uint64_t dwFlags;
    uint64_t pdwType;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegGetValueA(HKEY hKey, LPCSTR pszSubKey, LPCSTR pszValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
{
    struct qemu_RegGetValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGGETVALUEA);
    call.hKey = (ULONG_PTR)hKey;
    call.pszSubKey = (ULONG_PTR)pszSubKey;
    call.pszValue = (ULONG_PTR)pszValue;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pdwType = (ULONG_PTR)pdwType;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegGetValueA(struct qemu_syscall *call)
{
    struct qemu_RegGetValueA *c = (struct qemu_RegGetValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegGetValueA(QEMU_G2H(c->hKey), QEMU_G2H(c->pszSubKey), QEMU_G2H(c->pszValue), c->dwFlags, QEMU_G2H(c->pdwType), QEMU_G2H(c->pvData), QEMU_G2H(c->pcbData));
}

#endif

struct qemu_RegEnumValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t index;
    uint64_t value;
    uint64_t val_count;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegEnumValueW(HKEY hkey, DWORD index, LPWSTR value, LPDWORD val_count, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD count)
{
    struct qemu_RegEnumValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGENUMVALUEW);
    call.hkey = (LONG_PTR)hkey;
    call.index = (ULONG_PTR)index;
    call.value = (ULONG_PTR)value;
    call.val_count = (ULONG_PTR)val_count;
    call.reserved = (ULONG_PTR)reserved;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegEnumValueW(struct qemu_syscall *call)
{
    struct qemu_RegEnumValueW *c = (struct qemu_RegEnumValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegEnumValueW(QEMU_G2H(c->hkey), c->index, QEMU_G2H(c->value), QEMU_G2H(c->val_count), QEMU_G2H(c->reserved), QEMU_G2H(c->type), QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif

struct qemu_RegEnumValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t index;
    uint64_t value;
    uint64_t val_count;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegEnumValueA(HKEY hkey, DWORD index, LPSTR value, LPDWORD val_count, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD count)
{
    struct qemu_RegEnumValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGENUMVALUEA);
    call.hkey = (LONG_PTR)hkey;
    call.index = (ULONG_PTR)index;
    call.value = (ULONG_PTR)value;
    call.val_count = (ULONG_PTR)val_count;
    call.reserved = (ULONG_PTR)reserved;
    call.type = (ULONG_PTR)type;
    call.data = (ULONG_PTR)data;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegEnumValueA(struct qemu_syscall *call)
{
    struct qemu_RegEnumValueA *c = (struct qemu_RegEnumValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegEnumValueA(QEMU_G2H(c->hkey), c->index, QEMU_G2H(c->value), QEMU_G2H(c->val_count), QEMU_G2H(c->reserved), QEMU_G2H(c->type), QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif

struct qemu_RegDeleteValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteValueW(HKEY hkey, LPCWSTR name)
{
    struct qemu_RegDeleteValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEVALUEW);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteValueW(struct qemu_syscall *call)
{
    struct qemu_RegDeleteValueW *c = (struct qemu_RegDeleteValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteValueW(QEMU_G2H(c->hkey), QEMU_G2H(c->name));
}

#endif

struct qemu_RegDeleteValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteValueA(HKEY hkey, LPCSTR name)
{
    struct qemu_RegDeleteValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEVALUEA);
    call.hkey = (LONG_PTR)hkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteValueA(struct qemu_syscall *call)
{
    struct qemu_RegDeleteValueA *c = (struct qemu_RegDeleteValueA *)call;
    WINE_TRACE("\n");
    c->super.iret = RegDeleteValueA(QEMU_G2H(c->hkey), QEMU_G2H(c->name));
}

#endif

struct qemu_RegDeleteKeyValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegDeleteKeyValueW(HKEY hkey, LPCWSTR subkey, LPCWSTR name)
{
    struct qemu_RegDeleteKeyValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEKEYVALUEW);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteKeyValueW(struct qemu_syscall *call)
{
    struct qemu_RegDeleteKeyValueW *c = (struct qemu_RegDeleteKeyValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteKeyValueW(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), QEMU_G2H(c->name));
}

#endif

struct qemu_RegDeleteKeyValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegDeleteKeyValueA(HKEY hkey, LPCSTR subkey, LPCSTR name)
{
    struct qemu_RegDeleteKeyValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETEKEYVALUEA);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteKeyValueA(struct qemu_syscall *call)
{
    struct qemu_RegDeleteKeyValueA *c = (struct qemu_RegDeleteKeyValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteKeyValueA(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), QEMU_G2H(c->name));
}

#endif

struct qemu_RegLoadKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegLoadKeyW(HKEY hkey, LPCWSTR subkey, LPCWSTR filename)
{
    struct qemu_RegLoadKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGLOADKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.filename = (ULONG_PTR)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegLoadKeyW(struct qemu_syscall *call)
{
    struct qemu_RegLoadKeyW *c = (struct qemu_RegLoadKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegLoadKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), QEMU_G2H(c->filename));
}

#endif

struct qemu_RegLoadKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegLoadKeyA(HKEY hkey, LPCSTR subkey, LPCSTR filename)
{
    struct qemu_RegLoadKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGLOADKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;
    call.filename = (ULONG_PTR)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegLoadKeyA(struct qemu_syscall *call)
{
    struct qemu_RegLoadKeyA *c = (struct qemu_RegLoadKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegLoadKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey), QEMU_G2H(c->filename));
}

#endif

struct qemu_RegSaveKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t file;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSaveKeyW(HKEY hkey, LPCWSTR file, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_RegSaveKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVEKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.file = (ULONG_PTR)file;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveKeyW(struct qemu_syscall *call)
{
    struct qemu_RegSaveKeyW *c = (struct qemu_RegSaveKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->file), QEMU_G2H(c->sa));
}

#endif

struct qemu_RegSaveKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t file;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSaveKeyA(HKEY hkey, LPCSTR file, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_RegSaveKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVEKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.file = (ULONG_PTR)file;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveKeyA(struct qemu_syscall *call)
{
    struct qemu_RegSaveKeyA *c = (struct qemu_RegSaveKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->file), QEMU_G2H(c->sa));
}

#endif

struct qemu_RegSaveKeyExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t file;
    uint64_t sa;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSaveKeyExA(HKEY hkey, LPCSTR file, SECURITY_ATTRIBUTES *sa, DWORD flags)
{
    struct qemu_RegSaveKeyExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVEKEYEXA);
    call.hkey = (LONG_PTR)hkey;
    call.file = (ULONG_PTR)file;
    call.sa = (ULONG_PTR)sa;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveKeyExA(struct qemu_syscall *call)
{
    struct qemu_RegSaveKeyExA *c = (struct qemu_RegSaveKeyExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveKeyExA(QEMU_G2H(c->hkey), QEMU_G2H(c->file), QEMU_G2H(c->sa), c->flags);
}

#endif

struct qemu_RegSaveKeyExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t file;
    uint64_t sa;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSaveKeyExW(HKEY hkey, LPCWSTR file, SECURITY_ATTRIBUTES *sa, DWORD flags)
{
    struct qemu_RegSaveKeyExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVEKEYEXW);
    call.hkey = (LONG_PTR)hkey;
    call.file = (ULONG_PTR)file;
    call.sa = (ULONG_PTR)sa;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveKeyExW(struct qemu_syscall *call)
{
    struct qemu_RegSaveKeyExW *c = (struct qemu_RegSaveKeyExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveKeyExW(QEMU_G2H(c->hkey), QEMU_G2H(c->file), QEMU_G2H(c->sa), c->flags);
}

#endif

struct qemu_RegRestoreKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpFile;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegRestoreKeyW(HKEY hkey, LPCWSTR lpFile, DWORD dwFlags)
{
    struct qemu_RegRestoreKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGRESTOREKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.lpFile = (ULONG_PTR)lpFile;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegRestoreKeyW(struct qemu_syscall *call)
{
    struct qemu_RegRestoreKeyW *c = (struct qemu_RegRestoreKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegRestoreKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->lpFile), c->dwFlags);
}

#endif

struct qemu_RegRestoreKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpFile;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegRestoreKeyA(HKEY hkey, LPCSTR lpFile, DWORD dwFlags)
{
    struct qemu_RegRestoreKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGRESTOREKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.lpFile = (ULONG_PTR)lpFile;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegRestoreKeyA(struct qemu_syscall *call)
{
    struct qemu_RegRestoreKeyA *c = (struct qemu_RegRestoreKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegRestoreKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->lpFile), c->dwFlags);
}

#endif

struct qemu_RegUnLoadKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegUnLoadKeyW(HKEY hkey, LPCWSTR lpSubKey)
{
    struct qemu_RegUnLoadKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGUNLOADKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegUnLoadKeyW(struct qemu_syscall *call)
{
    struct qemu_RegUnLoadKeyW *c = (struct qemu_RegUnLoadKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegUnLoadKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey));
}

#endif

struct qemu_RegUnLoadKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegUnLoadKeyA(HKEY hkey, LPCSTR lpSubKey)
{
    struct qemu_RegUnLoadKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGUNLOADKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegUnLoadKeyA(struct qemu_syscall *call)
{
    struct qemu_RegUnLoadKeyA *c = (struct qemu_RegUnLoadKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegUnLoadKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey));
}

#endif

struct qemu_RegReplaceKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
    uint64_t lpNewFile;
    uint64_t lpOldFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegReplaceKeyW(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpNewFile, LPCWSTR lpOldFile)
{
    struct qemu_RegReplaceKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGREPLACEKEYW);
    call.hkey = (LONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;
    call.lpNewFile = (ULONG_PTR)lpNewFile;
    call.lpOldFile = (ULONG_PTR)lpOldFile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegReplaceKeyW(struct qemu_syscall *call)
{
    struct qemu_RegReplaceKeyW *c = (struct qemu_RegReplaceKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegReplaceKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey), QEMU_G2H(c->lpNewFile), QEMU_G2H(c->lpOldFile));
}

#endif

struct qemu_RegReplaceKeyA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
    uint64_t lpNewFile;
    uint64_t lpOldFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegReplaceKeyA(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpNewFile, LPCSTR lpOldFile)
{
    struct qemu_RegReplaceKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGREPLACEKEYA);
    call.hkey = (LONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;
    call.lpNewFile = (ULONG_PTR)lpNewFile;
    call.lpOldFile = (ULONG_PTR)lpOldFile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegReplaceKeyA(struct qemu_syscall *call)
{
    struct qemu_RegReplaceKeyA *c = (struct qemu_RegReplaceKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegReplaceKeyA(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey), QEMU_G2H(c->lpNewFile), QEMU_G2H(c->lpOldFile));
}

#endif

struct qemu_RegSetKeySecurity
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t SecurityInfo;
    uint64_t pSecurityDesc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegSetKeySecurity(HKEY hkey, SECURITY_INFORMATION SecurityInfo, PSECURITY_DESCRIPTOR pSecurityDesc)
{
    struct qemu_RegSetKeySecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSETKEYSECURITY);
    call.hkey = (LONG_PTR)hkey;
    call.SecurityInfo = (ULONG_PTR)SecurityInfo;
    call.pSecurityDesc = (ULONG_PTR)pSecurityDesc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSetKeySecurity(struct qemu_syscall *call)
{
    struct qemu_RegSetKeySecurity *c = (struct qemu_RegSetKeySecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSetKeySecurity(QEMU_G2H(c->hkey), c->SecurityInfo, QEMU_G2H(c->pSecurityDesc));
}

#endif

struct qemu_RegGetKeySecurity
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t SecurityInformation;
    uint64_t pSecurityDescriptor;
    uint64_t lpcbSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegGetKeySecurity(HKEY hkey, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, LPDWORD lpcbSecurityDescriptor)
{
    struct qemu_RegGetKeySecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGGETKEYSECURITY);
    call.hkey = (LONG_PTR)hkey;
    call.SecurityInformation = (ULONG_PTR)SecurityInformation;
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.lpcbSecurityDescriptor = (ULONG_PTR)lpcbSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegGetKeySecurity(struct qemu_syscall *call)
{
    struct qemu_RegGetKeySecurity *c = (struct qemu_RegGetKeySecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegGetKeySecurity(QEMU_G2H(c->hkey), c->SecurityInformation, QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->lpcbSecurityDescriptor));
}

#endif

struct qemu_RegFlushKey
{
    struct qemu_syscall super;
    uint64_t hkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegFlushKey(HKEY hkey)
{
    struct qemu_RegFlushKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGFLUSHKEY);
    call.hkey = (LONG_PTR)hkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegFlushKey(struct qemu_syscall *call)
{
    struct qemu_RegFlushKey *c = (struct qemu_RegFlushKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegFlushKey(QEMU_G2H(c->hkey));
}

#endif

struct qemu_RegConnectRegistryW
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t hKey;
    uint64_t phkResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegConnectRegistryW(LPCWSTR lpMachineName, HKEY hKey, PHKEY phkResult)
{
    struct qemu_RegConnectRegistryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCONNECTREGISTRYW);
    call.lpMachineName = (ULONG_PTR)lpMachineName;
    call.hKey = (ULONG_PTR)hKey;

    qemu_syscall(&call.super);
    *phkResult = (HKEY)(ULONG_PTR)call.phkResult;

    return call.super.iret;
}

#else

void qemu_RegConnectRegistryW(struct qemu_syscall *call)
{
    struct qemu_RegConnectRegistryW *c = (struct qemu_RegConnectRegistryW *)call;
    HKEY retkey;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegConnectRegistryW(QEMU_G2H(c->lpMachineName), QEMU_G2H(c->hKey), &retkey);
    c->phkResult = QEMU_H2G(retkey);
}

#endif

struct qemu_RegConnectRegistryA
{
    struct qemu_syscall super;
    uint64_t machine;
    uint64_t hkey;
    uint64_t reskey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegConnectRegistryA(LPCSTR machine, HKEY hkey, PHKEY reskey)
{
    struct qemu_RegConnectRegistryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCONNECTREGISTRYA);
    call.machine = (ULONG_PTR)machine;
    call.hkey = (LONG_PTR)hkey;

    qemu_syscall(&call.super);
    *reskey = (HKEY)(ULONG_PTR)call.reskey;

    return call.super.iret;
}

#else

void qemu_RegConnectRegistryA(struct qemu_syscall *call)
{
    struct qemu_RegConnectRegistryA *c = (struct qemu_RegConnectRegistryA *)call;
    HKEY reskey;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegConnectRegistryA(QEMU_G2H(c->machine), QEMU_G2H(c->hkey), &reskey);
    c->reskey = QEMU_H2G(reskey);
}

#endif

struct qemu_RegNotifyChangeKeyValue
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t fWatchSubTree;
    uint64_t fdwNotifyFilter;
    uint64_t hEvent;
    uint64_t fAsync;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegNotifyChangeKeyValue(HKEY hkey, BOOL fWatchSubTree, DWORD fdwNotifyFilter, HANDLE hEvent, BOOL fAsync)
{
    struct qemu_RegNotifyChangeKeyValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGNOTIFYCHANGEKEYVALUE);
    call.hkey = (LONG_PTR)hkey;
    call.fWatchSubTree = (ULONG_PTR)fWatchSubTree;
    call.fdwNotifyFilter = (ULONG_PTR)fdwNotifyFilter;
    call.hEvent = (ULONG_PTR)hEvent;
    call.fAsync = (ULONG_PTR)fAsync;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegNotifyChangeKeyValue(struct qemu_syscall *call)
{
    struct qemu_RegNotifyChangeKeyValue *c = (struct qemu_RegNotifyChangeKeyValue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegNotifyChangeKeyValue(QEMU_G2H(c->hkey), c->fWatchSubTree, c->fdwNotifyFilter, QEMU_G2H(c->hEvent), c->fAsync);
}

#endif

struct qemu_RegOpenUserClassesRoot
{
    struct qemu_syscall super;
    uint64_t hToken;
    uint64_t dwOptions;
    uint64_t samDesired;
    uint64_t phkResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegOpenUserClassesRoot(HANDLE hToken, DWORD dwOptions, REGSAM samDesired, PHKEY phkResult)
{
    struct qemu_RegOpenUserClassesRoot call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENUSERCLASSESROOT);
    call.hToken = (ULONG_PTR)hToken;
    call.dwOptions = (ULONG_PTR)dwOptions;
    call.samDesired = (ULONG_PTR)samDesired;

    qemu_syscall(&call.super);
    *phkResult = (HKEY)(ULONG_PTR)call.phkResult;

    return call.super.iret;
}

#else

void qemu_RegOpenUserClassesRoot(struct qemu_syscall *call)
{
    struct qemu_RegOpenUserClassesRoot *c = (struct qemu_RegOpenUserClassesRoot *)call;
    HKEY retkey;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegOpenUserClassesRoot(QEMU_G2H(c->hToken), c->dwOptions, c->samDesired, &retkey);
    c->phkResult = QEMU_H2G(retkey);
}

#endif

struct qemu_RegLoadMUIStringW
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pwszValue;
    uint64_t pwszBuffer;
    uint64_t cbBuffer;
    uint64_t pcbData;
    uint64_t dwFlags;
    uint64_t pwszBaseDir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegLoadMUIStringW(HKEY hKey, LPCWSTR pwszValue, LPWSTR pwszBuffer, DWORD cbBuffer, LPDWORD pcbData, DWORD dwFlags, LPCWSTR pwszBaseDir)
{
    struct qemu_RegLoadMUIStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGLOADMUISTRINGW);
    call.hKey = (ULONG_PTR)hKey;
    call.pwszValue = (ULONG_PTR)pwszValue;
    call.pwszBuffer = (ULONG_PTR)pwszBuffer;
    call.cbBuffer = (ULONG_PTR)cbBuffer;
    call.pcbData = (ULONG_PTR)pcbData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pwszBaseDir = (ULONG_PTR)pwszBaseDir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegLoadMUIStringW(struct qemu_syscall *call)
{
    struct qemu_RegLoadMUIStringW *c = (struct qemu_RegLoadMUIStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegLoadMUIStringW(QEMU_G2H(c->hKey), QEMU_G2H(c->pwszValue), QEMU_G2H(c->pwszBuffer), c->cbBuffer, QEMU_G2H(c->pcbData), c->dwFlags, QEMU_G2H(c->pwszBaseDir));
}

#endif

struct qemu_RegLoadMUIStringA
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pszValue;
    uint64_t pszBuffer;
    uint64_t cbBuffer;
    uint64_t pcbData;
    uint64_t dwFlags;
    uint64_t pszBaseDir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegLoadMUIStringA(HKEY hKey, LPCSTR pszValue, LPSTR pszBuffer, DWORD cbBuffer, LPDWORD pcbData, DWORD dwFlags, LPCSTR pszBaseDir)
{
    struct qemu_RegLoadMUIStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGLOADMUISTRINGA);
    call.hKey = (ULONG_PTR)hKey;
    call.pszValue = (ULONG_PTR)pszValue;
    call.pszBuffer = (ULONG_PTR)pszBuffer;
    call.cbBuffer = (ULONG_PTR)cbBuffer;
    call.pcbData = (ULONG_PTR)pcbData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pszBaseDir = (ULONG_PTR)pszBaseDir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegLoadMUIStringA(struct qemu_syscall *call)
{
    struct qemu_RegLoadMUIStringA *c = (struct qemu_RegLoadMUIStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegLoadMUIStringA(QEMU_G2H(c->hKey), QEMU_G2H(c->pszValue), QEMU_G2H(c->pszBuffer), c->cbBuffer, QEMU_G2H(c->pcbData), c->dwFlags, QEMU_G2H(c->pszBaseDir));
}

#endif

struct qemu_RegDisablePredefinedCache
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDisablePredefinedCache(void)
{
    struct qemu_RegDisablePredefinedCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDISABLEPREDEFINEDCACHE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDisablePredefinedCache(struct qemu_syscall *call)
{
    struct qemu_RegDisablePredefinedCache *c = (struct qemu_RegDisablePredefinedCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDisablePredefinedCache();
}

#endif

struct qemu_RegDeleteTreeW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteTreeW(HKEY hkey, const WCHAR *subkey)
{
    struct qemu_RegDeleteTreeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETETREEW);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteTreeW(struct qemu_syscall *call)
{
    struct qemu_RegDeleteTreeW *c = (struct qemu_RegDeleteTreeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteTreeW(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey));
}

#endif

struct qemu_RegDeleteTreeA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t subkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LSTATUS WINAPI RegDeleteTreeA(HKEY hkey, const char *subkey)
{
    struct qemu_RegDeleteTreeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDELETETREEA);
    call.hkey = (LONG_PTR)hkey;
    call.subkey = (ULONG_PTR)subkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegDeleteTreeA(struct qemu_syscall *call)
{
    struct qemu_RegDeleteTreeA *c = (struct qemu_RegDeleteTreeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDeleteTreeA(QEMU_G2H(c->hkey), QEMU_G2H(c->subkey));
}

#endif

struct qemu_RegCopyTreeW
{
    struct qemu_syscall super;
    uint64_t hsrc;
    uint64_t subkey;
    uint64_t hdst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegCopyTreeW(HKEY hsrc, const WCHAR *subkey, HKEY hdst)
{
    struct qemu_RegCopyTreeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCOPYTREEW);
    call.hsrc = (ULONG_PTR)hsrc;
    call.subkey = (ULONG_PTR)subkey;
    call.hdst = (ULONG_PTR)hdst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegCopyTreeW to Wine headers? */
extern LONG WINAPI RegCopyTreeW(HKEY hsrc, const WCHAR *subkey, HKEY hdst);
void qemu_RegCopyTreeW(struct qemu_syscall *call)
{
    struct qemu_RegCopyTreeW *c = (struct qemu_RegCopyTreeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegCopyTreeW(QEMU_G2H(c->hsrc), QEMU_G2H(c->subkey), QEMU_G2H(c->hdst));
}

#endif

struct qemu_RegCopyTreeA
{
    struct qemu_syscall super;
    uint64_t hsrc;
    uint64_t subkey;
    uint64_t hdst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegCopyTreeA(HKEY hsrc, const char *subkey, HKEY hdst)
{
    struct qemu_RegCopyTreeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCOPYTREEA);
    call.hsrc = (ULONG_PTR)hsrc;
    call.subkey = (ULONG_PTR)subkey;
    call.hdst = (ULONG_PTR)hdst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegCopyTreeA to Wine headers? */
extern LONG WINAPI RegCopyTreeA(HKEY hsrc, const char *subkey, HKEY hdst);
void qemu_RegCopyTreeA(struct qemu_syscall *call)
{
    struct qemu_RegCopyTreeA *c = (struct qemu_RegCopyTreeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegCopyTreeA(QEMU_G2H(c->hsrc), QEMU_G2H(c->subkey), QEMU_G2H(c->hdst));
}

#endif

struct qemu_RegDisableReflectionKey
{
    struct qemu_syscall super;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RegDisableReflectionKey(HKEY base)
{
    struct qemu_RegDisableReflectionKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGDISABLEREFLECTIONKEY);
    call.base = (ULONG_PTR)base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegDisableReflectionKey to Wine headers? */
extern LONG WINAPI RegDisableReflectionKey(HKEY base);
void qemu_RegDisableReflectionKey(struct qemu_syscall *call)
{
    struct qemu_RegDisableReflectionKey *c = (struct qemu_RegDisableReflectionKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegDisableReflectionKey(QEMU_G2H(c->base));
}

#endif

