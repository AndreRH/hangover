/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

struct qemu___sys_nerr
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int* CDECL __sys_nerr(void)
{
    struct qemu___sys_nerr call;
    call.super.id = QEMU_SYSCALL_ID(CALL___SYS_NERR);

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___sys_nerr(struct qemu_syscall *call)
{
    struct qemu___sys_nerr *c = (struct qemu___sys_nerr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___sys_nerr());
}

#endif

struct qemu___sys_errlist
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

char** CDECL __sys_errlist(void)
{
    struct qemu___sys_errlist call;
    call.super.id = QEMU_SYSCALL_ID(CALL___SYS_ERRLIST);

    qemu_syscall(&call.super);

    return (char **)(ULONG_PTR)call.super.iret;
}

#else

void qemu___sys_errlist(struct qemu_syscall *call)
{
    struct qemu___sys_errlist *c = (struct qemu___sys_errlist *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___sys_errlist());
}

#endif

struct qemu__errno
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int * CDECL MSVCRT__errno(void)
{
    struct qemu__errno call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ERRNO);

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__errno(struct qemu_syscall *call)
{
    struct qemu__errno *c = (struct qemu__errno *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p__errno());
}

#endif

struct qemu___doserrno
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

ULONG* CDECL MSVCRT___doserrno(void)
{
    struct qemu___doserrno call;
    call.super.id = QEMU_SYSCALL_ID(CALL___DOSERRNO);

    qemu_syscall(&call.super);

    return (ULONG *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___doserrno(struct qemu_syscall *call)
{
    struct qemu___doserrno *c = (struct qemu___doserrno *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___doserrno());
}

#endif

struct qemu__get_errno
{
    struct qemu_syscall super;
    uint64_t pValue;
};

#ifdef QEMU_DLL_GUEST

int CDECL _get_errno(int *pValue)
{
    struct qemu__get_errno call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_ERRNO);
    call.pValue = (ULONG_PTR)pValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_errno(struct qemu_syscall *call)
{
    struct qemu__get_errno *c = (struct qemu__get_errno *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_errno(QEMU_G2H(c->pValue));
}

#endif

struct qemu__get_doserrno
{
    struct qemu_syscall super;
    uint64_t pValue;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__get_doserrno(int *pValue)
{
    struct qemu__get_doserrno call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_DOSERRNO);
    call.pValue = (ULONG_PTR)pValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_doserrno(struct qemu_syscall *call)
{
    struct qemu__get_doserrno *c = (struct qemu__get_doserrno *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_doserrno(QEMU_G2H(c->pValue));
}

#endif

struct qemu__set_errno
{
    struct qemu_syscall super;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

int CDECL _set_errno(int value)
{
    struct qemu__set_errno call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_ERRNO);
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_errno(struct qemu_syscall *call)
{
    struct qemu__set_errno *c = (struct qemu__set_errno *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_errno(c->value);
}

#endif

struct qemu__set_doserrno
{
    struct qemu_syscall super;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__set_doserrno(int value)
{
    struct qemu__set_doserrno call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_DOSERRNO);
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_doserrno(struct qemu_syscall *call)
{
    struct qemu__set_doserrno *c = (struct qemu__set_doserrno *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_doserrno(c->value);
}

#endif

struct qemu_strerror
{
    struct qemu_syscall super;
    uint64_t err;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT_strerror(int err)
{
    struct qemu_strerror call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRERROR);
    call.err = (ULONG_PTR)err;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strerror(struct qemu_syscall *call)
{
    struct qemu_strerror *c = (struct qemu_strerror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strerror(c->err));
}

#endif

struct qemu_strerror_s
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t numberOfElements;
    uint64_t errnum;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strerror_s(char *buffer, size_t numberOfElements, int errnum)
{
    struct qemu_strerror_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRERROR_S);
    call.buffer = (ULONG_PTR)buffer;
    call.numberOfElements = (ULONG_PTR)numberOfElements;
    call.errnum = (ULONG_PTR)errnum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strerror_s(struct qemu_syscall *call)
{
    struct qemu_strerror_s *c = (struct qemu_strerror_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strerror_s(QEMU_G2H(c->buffer), c->numberOfElements, c->errnum);
}

#endif

struct qemu__strerror
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__strerror(const char* str)
{
    struct qemu__strerror call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRERROR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strerror(struct qemu_syscall *call)
{
    struct qemu__strerror *c = (struct qemu__strerror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strerror(QEMU_G2H(c->str)));
}

#endif

struct qemu_perror
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_perror(const char* str)
{
    struct qemu_perror call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERROR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_perror(struct qemu_syscall *call)
{
    struct qemu_perror *c = (struct qemu_perror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_perror(QEMU_G2H(c->str));
}

#endif

struct qemu__wperror
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__wperror(const WCHAR* str)
{
    struct qemu__wperror call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WPERROR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu__wperror(struct qemu_syscall *call)
{
    struct qemu__wperror *c = (struct qemu__wperror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__wperror(QEMU_G2H(c->str));
}

#endif

struct qemu__wcserror_s
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t nc;
    uint64_t err;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wcserror_s(WCHAR* buffer, size_t nc, int err)
{
    struct qemu__wcserror_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSERROR_S);
    call.buffer = (ULONG_PTR)buffer;
    call.nc = (ULONG_PTR)nc;
    call.err = (ULONG_PTR)err;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcserror_s(struct qemu_syscall *call)
{
    struct qemu__wcserror_s *c = (struct qemu__wcserror_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcserror_s(QEMU_G2H(c->buffer), c->nc, c->err);
}

#endif

struct qemu__wcserror
{
    struct qemu_syscall super;
    uint64_t err;
};

#ifdef QEMU_DLL_GUEST

WCHAR* CDECL MSVCRT__wcserror(int err)
{
    struct qemu__wcserror call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSERROR);
    call.err = (ULONG_PTR)err;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcserror(struct qemu_syscall *call)
{
    struct qemu__wcserror *c = (struct qemu__wcserror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcserror(c->err));
}

#endif

struct qemu___wcserror_s
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t nc;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT___wcserror_s(WCHAR* buffer, size_t nc, const WCHAR* str)
{
    struct qemu___wcserror_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WCSERROR_S);
    call.buffer = (ULONG_PTR)buffer;
    call.nc = (ULONG_PTR)nc;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___wcserror_s(struct qemu_syscall *call)
{
    struct qemu___wcserror_s *c = (struct qemu___wcserror_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___wcserror_s(QEMU_G2H(c->buffer), c->nc, QEMU_G2H(c->str));
}

#endif

struct qemu___wcserror
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WCHAR* CDECL MSVCRT___wcserror(const WCHAR* str)
{
    struct qemu___wcserror call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WCSERROR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___wcserror(struct qemu_syscall *call)
{
    struct qemu___wcserror *c = (struct qemu___wcserror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___wcserror(QEMU_G2H(c->str)));
}

#endif

struct qemu__seterrormode
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__seterrormode(int mode)
{
    struct qemu__seterrormode call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SETERRORMODE);
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);
}

#else

void qemu__seterrormode(struct qemu_syscall *call)
{
    struct qemu__seterrormode *c = (struct qemu__seterrormode *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__seterrormode(c->mode);
}

#endif

struct qemu__invalid_parameter_noinfo
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

void CDECL _invalid_parameter_noinfo(void)
{
    struct qemu__invalid_parameter_noinfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL__INVALID_PARAMETER_NOINFO);

    qemu_syscall(&call.super);
}

#else

void qemu__invalid_parameter_noinfo(struct qemu_syscall *call)
{
    struct qemu__invalid_parameter_noinfo *c = (struct qemu__invalid_parameter_noinfo *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__invalid_parameter_noinfo();
}

#endif

struct qemu__invalid_parameter_noinfo_noreturn
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

void CDECL _invalid_parameter_noinfo_noreturn(void)
{
    struct qemu__invalid_parameter_noinfo_noreturn call;
    call.super.id = QEMU_SYSCALL_ID(CALL__INVALID_PARAMETER_NOINFO_NORETURN);

    qemu_syscall(&call.super);
}

#else

void qemu__invalid_parameter_noinfo_noreturn(struct qemu_syscall *call)
{
    struct qemu__invalid_parameter_noinfo_noreturn *c = (struct qemu__invalid_parameter_noinfo_noreturn *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__invalid_parameter_noinfo_noreturn();
}

#endif

struct qemu__get_invalid_parameter_handler
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

_invalid_parameter_handler CDECL MSVCRT__get_invalid_parameter_handler(void)
{
    struct qemu__get_invalid_parameter_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_INVALID_PARAMETER_HANDLER);

    qemu_syscall(&call.super);

    return (_invalid_parameter_handler)(ULONG_PTR)call.super.iret;
}

#else

void qemu__get_invalid_parameter_handler(struct qemu_syscall *call)
{
    struct qemu__get_invalid_parameter_handler *c = (struct qemu__get_invalid_parameter_handler *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_invalid_parameter_handler());
}

#endif

struct qemu__set_invalid_parameter_handler
{
    struct qemu_syscall super;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

_invalid_parameter_handler CDECL MSVCRT__set_invalid_parameter_handler(_invalid_parameter_handler handler)
{
    struct qemu__set_invalid_parameter_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_INVALID_PARAMETER_HANDLER);
    call.handler = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return (_invalid_parameter_handler)(ULONG_PTR)call.super.iret;
}

#else

void qemu__set_invalid_parameter_handler(struct qemu_syscall *call)
{
    struct qemu__set_invalid_parameter_handler *c = (struct qemu__set_invalid_parameter_handler *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__set_invalid_parameter_handler(QEMU_G2H(c->handler)));
}

#endif

struct qemu__get_thread_local_invalid_parameter_handler
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

_invalid_parameter_handler CDECL _get_thread_local_invalid_parameter_handler(void)
{
    struct qemu__get_thread_local_invalid_parameter_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_THREAD_LOCAL_INVALID_PARAMETER_HANDLER);

    qemu_syscall(&call.super);

    return (_invalid_parameter_handler)(ULONG_PTR)call.super.iret;
}

#else

void qemu__get_thread_local_invalid_parameter_handler(struct qemu_syscall *call)
{
    struct qemu__get_thread_local_invalid_parameter_handler *c = (struct qemu__get_thread_local_invalid_parameter_handler *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_thread_local_invalid_parameter_handler());
}

#endif

struct qemu__set_thread_local_invalid_parameter_handler
{
    struct qemu_syscall super;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

_invalid_parameter_handler CDECL _set_thread_local_invalid_parameter_handler(_invalid_parameter_handler handler)
{
    struct qemu__set_thread_local_invalid_parameter_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_THREAD_LOCAL_INVALID_PARAMETER_HANDLER);
    call.handler = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return (_invalid_parameter_handler)(ULONG_PTR)call.super.iret;
}

#else

void qemu__set_thread_local_invalid_parameter_handler(struct qemu_syscall *call)
{
    struct qemu__set_thread_local_invalid_parameter_handler *c = (struct qemu__set_thread_local_invalid_parameter_handler *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__set_thread_local_invalid_parameter_handler(QEMU_G2H(c->handler)));
}

#endif
