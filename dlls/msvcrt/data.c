/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#else

/* FIXME: This needs DllMain support to grab the pointer from the host. */
char **MSVCRT___initenv = NULL;
char *MSVCRT__acmdln = NULL;
WCHAR *MSVCRT__wcmdln = NULL;

unsigned int MSVCRT__commode = 0;
unsigned int MSVCRT__fmode = 0;

#endif

struct qemu___getmainargs
{
    struct qemu_syscall super;
    uint64_t argc, argv, envp;
    uint64_t expand_wildcards;
    uint64_t new_mode;
};


#ifdef QEMU_DLL_GUEST

void CDECL __getmainargs(int *argc, char** *argv, char** *envp, int expand_wildcards,
        int *new_mode)
{
    struct qemu___getmainargs call;
    call.super.id = QEMU_SYSCALL_ID(CALL___GETMAINARGS);
    call.argc = (uint64_t)argc;
    call.argv = (uint64_t)argv;
    call.envp = (uint64_t)envp;
    call.expand_wildcards = expand_wildcards;
    call.new_mode = (uint64_t)new_mode;

    qemu_syscall(&call.super);
}

#else

void qemu___getmainargs(struct qemu_syscall *call)
{
    char **host_argv, **host_envp;

    struct qemu___getmainargs *c = (struct qemu___getmainargs *)call;
    /* QEMU hacks up argc and argv after kernel32 consumes it but before
     * msvcrt does, so this *should* work. */
    WINE_TRACE("\n");
    p___getmainargs(QEMU_G2H(c->argc), &host_argv, &host_envp,
            c->expand_wildcards, QEMU_G2H(c->new_mode));

    *(uint64_t *)(QEMU_G2H(c->argv)) = QEMU_H2G(host_argv);
    *(uint64_t *)(QEMU_G2H(c->envp)) = QEMU_H2G(host_envp);
}

#endif

struct qemu___wgetmainargs
{
    struct qemu_syscall super;
    uint64_t argc, wargv, wenvp;
    uint64_t expand_wildcards;
    uint64_t new_mode;
};

#ifdef QEMU_DLL_GUEST

void CDECL __wgetmainargs(int *argc, WCHAR** *wargv, WCHAR** *wenvp,
                          int expand_wildcards, int *new_mode)
{
    struct qemu___getmainargs call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WGETMAINARGS);
    call.argc = (uint64_t)argc;
    call.argv = (uint64_t)wargv;
    call.envp = (uint64_t)wenvp;
    call.expand_wildcards = expand_wildcards;
    call.new_mode = (uint64_t)new_mode;

    qemu_syscall(&call.super);
}

#else

void qemu___wgetmainargs(struct qemu_syscall *call)
{
    WCHAR **host_argv, **host_envp;

    struct qemu___wgetmainargs *c = (struct qemu___wgetmainargs *)call;
    /* QEMU hacks up argc and argv after kernel32 consumes it but before
     * msvcrt does, so this *should* work. */
    WINE_TRACE("\n");
    p___wgetmainargs(QEMU_G2H(c->argc), &host_argv, &host_envp,
            c->expand_wildcards, QEMU_G2H(c->new_mode));

    *(uint64_t *)(QEMU_G2H(c->wargv)) = QEMU_H2G(host_argv);
    *(uint64_t *)(QEMU_G2H(c->wenvp)) = QEMU_H2G(host_envp);
}

#endif

struct qemu___set_app_type
{
    struct qemu_syscall super;
    uint64_t type;
};


#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT___set_app_type(int type)
{
    struct qemu___set_app_type call;
    call.super.id = QEMU_SYSCALL_ID(CALL___SET_APP_TYPE);
    call.type = type;

    qemu_syscall(&call.super);
}

#else

void qemu___set_app_type(struct qemu_syscall *call)
{
    struct qemu___set_app_type *c = (struct qemu___set_app_type *)call;
    WINE_TRACE("\n");
    /* No harm in forwarding this. If there is a conflict with qemu then qemu should
     * leave this thing alone. */
    p___set_app_type(c->type);
}

#endif

#ifdef QEMU_DLL_GUEST

typedef void (CDECL *_INITTERMFUN)(void);
void CDECL _initterm(_INITTERMFUN *start,_INITTERMFUN *end)
{
    _INITTERMFUN* current = start;

    while (current<end)
    {
        if (*current)
        {
            (**current)();
        }
        current++;
    }
}

typedef int (CDECL *_INITTERM_E_FN)(void);
int CDECL _initterm_e(_INITTERM_E_FN *table, _INITTERM_E_FN *end)
{
    int res = 0;

    while (!res && table < end)
    {
        if (*table)
        {
            res = (**table)();
        }
        table++;
    }
    return res;
}

#endif

struct qemu__get_pgmptr
{
    struct qemu_syscall super;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _get_pgmptr(char** p)
{
    struct qemu__get_pgmptr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_PGMPTR);
    call.p = (ULONG_PTR)p;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_pgmptr(struct qemu_syscall *call)
{
    struct qemu__get_pgmptr *c = (struct qemu__get_pgmptr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_pgmptr(QEMU_G2H(c->p));
}

#endif

struct qemu__get_wpgmptr
{
    struct qemu_syscall super;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _get_wpgmptr(WCHAR** p)
{
    struct qemu__get_wpgmptr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_WPGMPTR);
    call.p = (ULONG_PTR)p;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_wpgmptr(struct qemu_syscall *call)
{
    struct qemu__get_wpgmptr *c = (struct qemu__get_wpgmptr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_wpgmptr(QEMU_G2H(c->p));
}

#endif

struct qemu__set_fmode
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__set_fmode(int mode)
{
    struct qemu__set_fmode call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_FMODE);
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_fmode(struct qemu_syscall *call)
{
    struct qemu__set_fmode *c = (struct qemu__set_fmode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_fmode(c->mode);
}

#endif

struct qemu__get_fmode
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__get_fmode(int *mode)
{
    struct qemu__get_fmode call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_FMODE);
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_fmode(struct qemu_syscall *call)
{
    struct qemu__get_fmode *c = (struct qemu__get_fmode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_fmode(QEMU_G2H(c->mode));
}

#endif

struct qemu___p__environ
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char*** CDECL MSVCRT___p__environ(void)
{
    struct qemu___p__environ call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__ENVIRON);

    qemu_syscall(&call.super);

    return (char***)call.super.iret;
}

#else

void qemu___p__environ(struct qemu_syscall *call)
{
    struct qemu___p__environ *c = (struct qemu___p__environ *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__environ());
}

#endif

struct qemu___p__wenviron
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR*** CDECL MSVCRT___p__wenviron(void)
{
    struct qemu___p__wenviron call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__WENVIRON);

    qemu_syscall(&call.super);

    return (WCHAR ***)call.super.iret;
}

#else

void qemu___p__wenviron(struct qemu_syscall *call)
{
    struct qemu___p__wenviron *c = (struct qemu___p__wenviron *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__wenviron());
}

#endif

struct qemu__get_osplatform
{
    struct qemu_syscall super;
    uint64_t pValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__get_osplatform(int *pValue)
{
    struct qemu__get_osplatform call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_OSPLATFORM);
    call.pValue = (ULONG_PTR)pValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_osplatform(struct qemu_syscall *call)
{
    struct qemu__get_osplatform *c = (struct qemu__get_osplatform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_osplatform(QEMU_G2H(c->pValue));
}

#endif

struct qemu____unguarded_readlc_active_add_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int * CDECL MSVCRT____unguarded_readlc_active_add_func(void)
{
    struct qemu____unguarded_readlc_active_add_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____UNGUARDED_READLC_ACTIVE_ADD_FUNC);

    qemu_syscall(&call.super);

    return (unsigned int *)call.super.iret;
}

#else

void qemu____unguarded_readlc_active_add_func(struct qemu_syscall *call)
{
    struct qemu____unguarded_readlc_active_add_func *c = (struct qemu____unguarded_readlc_active_add_func *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p____unguarded_readlc_active_add_func());
}

#endif

struct qemu____setlc_active_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL MSVCRT____setlc_active_func(void)
{
    struct qemu____setlc_active_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____SETLC_ACTIVE_FUNC);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu____setlc_active_func(struct qemu_syscall *call)
{
    struct qemu____setlc_active_func *c = (struct qemu____setlc_active_func *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p____setlc_active_func();
}

#endif

struct qemu__get_initial_narrow_environment
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char** CDECL _get_initial_narrow_environment(void)
{
    struct qemu__get_initial_narrow_environment call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_INITIAL_NARROW_ENVIRONMENT);

    qemu_syscall(&call.super);

    return (char **)call.super.iret;
}

#else

void qemu__get_initial_narrow_environment(struct qemu_syscall *call)
{
    struct qemu__get_initial_narrow_environment *c = (struct qemu__get_initial_narrow_environment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_initial_narrow_environment());
}

#endif

struct qemu__configure_narrow_argv
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _configure_narrow_argv(int mode)
{
    struct qemu__configure_narrow_argv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CONFIGURE_NARROW_ARGV);
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__configure_narrow_argv(struct qemu_syscall *call)
{
    struct qemu__configure_narrow_argv *c = (struct qemu__configure_narrow_argv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__configure_narrow_argv(c->mode);
}

#endif

struct qemu__initialize_narrow_environment
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _initialize_narrow_environment(void)
{
    struct qemu__initialize_narrow_environment call;
    call.super.id = QEMU_SYSCALL_ID(CALL__INITIALIZE_NARROW_ENVIRONMENT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__initialize_narrow_environment(struct qemu_syscall *call)
{
    struct qemu__initialize_narrow_environment *c = (struct qemu__initialize_narrow_environment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__initialize_narrow_environment();
}

#endif

struct qemu__get_initial_wide_environment
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR** CDECL _get_initial_wide_environment(void)
{
    struct qemu__get_initial_wide_environment call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_INITIAL_WIDE_ENVIRONMENT);

    qemu_syscall(&call.super);

    return (WCHAR **)call.super.iret;
}

#else

void qemu__get_initial_wide_environment(struct qemu_syscall *call)
{
    struct qemu__get_initial_wide_environment *c = (struct qemu__get_initial_wide_environment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_initial_wide_environment());
}

#endif

struct qemu__configure_wide_argv
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _configure_wide_argv(int mode)
{
    struct qemu__configure_wide_argv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CONFIGURE_WIDE_ARGV);
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__configure_wide_argv(struct qemu_syscall *call)
{
    struct qemu__configure_wide_argv *c = (struct qemu__configure_wide_argv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__configure_wide_argv(c->mode);
}

#endif

struct qemu__initialize_wide_environment
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _initialize_wide_environment(void)
{
    struct qemu__initialize_wide_environment call;
    call.super.id = QEMU_SYSCALL_ID(CALL__INITIALIZE_WIDE_ENVIRONMENT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__initialize_wide_environment(struct qemu_syscall *call)
{
    struct qemu__initialize_wide_environment *c = (struct qemu__initialize_wide_environment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__initialize_wide_environment();
}

#endif

struct qemu__get_narrow_winmain_command_line
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL _get_narrow_winmain_command_line(void)
{
    struct qemu__get_narrow_winmain_command_line call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_NARROW_WINMAIN_COMMAND_LINE);

    qemu_syscall(&call.super);

    return (char *)call.super.iret;
}

#else

void qemu__get_narrow_winmain_command_line(struct qemu_syscall *call)
{
    struct qemu__get_narrow_winmain_command_line *c = (struct qemu__get_narrow_winmain_command_line *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_narrow_winmain_command_line());
}

#endif

struct qemu__get_wide_winmain_command_line
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL _get_wide_winmain_command_line(void)
{
    struct qemu__get_wide_winmain_command_line call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_WIDE_WINMAIN_COMMAND_LINE);

    qemu_syscall(&call.super);

    return (WCHAR *)call.super.iret;
}

#else

void qemu__get_wide_winmain_command_line(struct qemu_syscall *call)
{
    struct qemu__get_wide_winmain_command_line *c = (struct qemu__get_wide_winmain_command_line *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_wide_winmain_command_line());
}

#endif

