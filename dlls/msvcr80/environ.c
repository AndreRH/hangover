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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif


struct qemu_getenv
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_getenv(const char *name)
{
    struct qemu_getenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENV);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_getenv(struct qemu_syscall *call)
{
    struct qemu_getenv *c = (struct qemu_getenv *)(ULONG_PTR)call;
    WINE_TRACE(" %s\n", (char *)QEMU_G2H(c->name));
    c->super.iret = QEMU_H2G(p_getenv(QEMU_G2H(c->name)));
    WINE_TRACE("Ret %p\n", QEMU_G2H(c->super.iret));
}

#endif

struct qemu__wgetenv
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT__wgetenv(const WCHAR *name)
{
    struct qemu__wgetenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WGETENV);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wgetenv(struct qemu_syscall *call)
{
    struct qemu__wgetenv *c = (struct qemu__wgetenv *)(ULONG_PTR)call;
    WINE_TRACE(" %s\n", wine_dbgstr_w(QEMU_G2H(c->name)));
    c->super.iret = QEMU_H2G(p__wgetenv(QEMU_G2H(c->name)));
    WINE_TRACE("Ret %p\n", QEMU_G2H(c->super.iret));
}

#endif

struct qemu__putenv
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__putenv(const char *str)
{
    struct qemu__putenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTENV);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putenv(struct qemu_syscall *call)
{
    struct qemu__putenv *c = (struct qemu__putenv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putenv(QEMU_G2H(c->str));
}

#endif

struct qemu__wputenv
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wputenv(const WCHAR *str)
{
    struct qemu__wputenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WPUTENV);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wputenv(struct qemu_syscall *call)
{
    struct qemu__wputenv *c = (struct qemu__wputenv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wputenv(QEMU_G2H(c->str));
}

#endif

struct qemu__putenv_s
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

int CDECL _putenv_s(const char *name, const char *value)
{
    struct qemu__putenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTENV_S);
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putenv_s(struct qemu_syscall *call)
{
    struct qemu__putenv_s *c = (struct qemu__putenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putenv_s(QEMU_G2H(c->name), QEMU_G2H(c->value));
}

#endif

struct qemu__wputenv_s
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

int CDECL _wputenv_s(const WCHAR *name, const WCHAR *value)
{
    struct qemu__wputenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WPUTENV_S);
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wputenv_s(struct qemu_syscall *call)
{
    struct qemu__wputenv_s *c = (struct qemu__wputenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wputenv_s(QEMU_G2H(c->name), QEMU_G2H(c->value));
}

#endif

struct qemu__dupenv_s
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t numberOfElements;
    uint64_t varname;
};

#ifdef QEMU_DLL_GUEST

int CDECL _dupenv_s(char **buffer, size_t *numberOfElements, const char *varname)
{
    struct qemu__dupenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DUPENV_S);
    call.buffer = (ULONG_PTR)buffer;
    call.numberOfElements = (ULONG_PTR)numberOfElements;
    call.varname = (ULONG_PTR)varname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dupenv_s(struct qemu_syscall *call)
{
    struct qemu__dupenv_s *c = (struct qemu__dupenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dupenv_s(QEMU_G2H(c->buffer), QEMU_G2H(c->numberOfElements), QEMU_G2H(c->varname));
}

#endif

struct qemu__wdupenv_s
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t numberOfElements;
    uint64_t varname;
};

#ifdef QEMU_DLL_GUEST

int CDECL _wdupenv_s(WCHAR **buffer, size_t *numberOfElements, const WCHAR *varname)
{
    struct qemu__wdupenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WDUPENV_S);
    call.buffer = (ULONG_PTR)buffer;
    call.numberOfElements = (ULONG_PTR)numberOfElements;
    call.varname = (ULONG_PTR)varname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wdupenv_s(struct qemu_syscall *call)
{
    struct qemu__wdupenv_s *c = (struct qemu__wdupenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wdupenv_s(QEMU_G2H(c->buffer), QEMU_G2H(c->numberOfElements), QEMU_G2H(c->varname));
}

#endif

struct qemu_getenv_s
{
    struct qemu_syscall super;
    uint64_t pReturnValue;
    uint64_t buffer;
    uint64_t numberOfElements;
    uint64_t varname;
};

#ifdef QEMU_DLL_GUEST

int CDECL getenv_s(size_t *pReturnValue, char* buffer, size_t numberOfElements, const char *varname)
{
    struct qemu_getenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENV_S);
    call.pReturnValue = (ULONG_PTR)pReturnValue;
    call.buffer = (ULONG_PTR)buffer;
    call.numberOfElements = (ULONG_PTR)numberOfElements;
    call.varname = (ULONG_PTR)varname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_getenv_s(struct qemu_syscall *call)
{
    struct qemu_getenv_s *c = (struct qemu_getenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getenv_s(QEMU_G2H(c->pReturnValue), QEMU_G2H(c->buffer), c->numberOfElements, QEMU_G2H(c->varname));
}

#endif

struct qemu__wgetenv_s
{
    struct qemu_syscall super;
    uint64_t pReturnValue;
    uint64_t buffer;
    uint64_t numberOfElements;
    uint64_t varname;
};

#ifdef QEMU_DLL_GUEST

int CDECL _wgetenv_s(size_t *pReturnValue, WCHAR *buffer, size_t numberOfElements, const WCHAR *varname)
{
    struct qemu__wgetenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WGETENV_S);
    call.pReturnValue = (ULONG_PTR)pReturnValue;
    call.buffer = (ULONG_PTR)buffer;
    call.numberOfElements = (ULONG_PTR)numberOfElements;
    call.varname = (ULONG_PTR)varname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wgetenv_s(struct qemu_syscall *call)
{
    struct qemu__wgetenv_s *c = (struct qemu__wgetenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wgetenv_s(QEMU_G2H(c->pReturnValue), QEMU_G2H(c->buffer), c->numberOfElements, QEMU_G2H(c->varname));
}

#endif

