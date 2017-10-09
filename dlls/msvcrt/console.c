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

struct qemu__cputs
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _cputs(const char* str)
{
    struct qemu__cputs call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CPUTS);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__cputs(struct qemu_syscall *call)
{
    struct qemu__cputs *c = (struct qemu__cputs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__cputs(QEMU_G2H(c->str));
}

#endif

struct qemu__cputws
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _cputws(const WCHAR* str)
{
    struct qemu__cputws call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CPUTWS);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__cputws(struct qemu_syscall *call)
{
    struct qemu__cputws *c = (struct qemu__cputws *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__cputws(QEMU_G2H(c->str));
}

#endif

struct qemu__getch_nolock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _getch_nolock(void)
{
    struct qemu__getch_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETCH_NOLOCK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getch_nolock(struct qemu_syscall *call)
{
    struct qemu__getch_nolock *c = (struct qemu__getch_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getch_nolock();
}

#endif

struct qemu__getch
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _getch(void)
{
    struct qemu__getch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETCH);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getch(struct qemu_syscall *call)
{
    struct qemu__getch *c = (struct qemu__getch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getch();
}

#endif

struct qemu__getwch_nolock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _getwch_nolock(void)
{
    struct qemu__getwch_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETWCH_NOLOCK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getwch_nolock(struct qemu_syscall *call)
{
    struct qemu__getwch_nolock *c = (struct qemu__getwch_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getwch_nolock();
}

#endif

struct qemu__getwch
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _getwch(void)
{
    struct qemu__getwch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETWCH);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getwch(struct qemu_syscall *call)
{
    struct qemu__getwch *c = (struct qemu__getwch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getwch();
}

#endif

struct qemu__putch_nolock
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _putch_nolock(int c)
{
    struct qemu__putch_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTCH_NOLOCK);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putch_nolock(struct qemu_syscall *call)
{
    struct qemu__putch_nolock *c = (struct qemu__putch_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putch_nolock(c->c);
}

#endif

struct qemu__putch
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _putch(int c)
{
    struct qemu__putch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTCH);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putch(struct qemu_syscall *call)
{
    struct qemu__putch *c = (struct qemu__putch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putch(c->c);
}

#endif

struct qemu__putwch_nolock
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _putwch_nolock(WCHAR c)
{
    struct qemu__putwch_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTWCH_NOLOCK);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putwch_nolock(struct qemu_syscall *call)
{
    struct qemu__putwch_nolock *c = (struct qemu__putwch_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putwch_nolock(c->c);
}

#endif

struct qemu__putwch
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _putwch(WCHAR c)
{
    struct qemu__putwch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTWCH);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putwch(struct qemu_syscall *call)
{
    struct qemu__putwch *c = (struct qemu__putwch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putwch(c->c);
}

#endif

struct qemu__getche_nolock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _getche_nolock(void)
{
    struct qemu__getche_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETCHE_NOLOCK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getche_nolock(struct qemu_syscall *call)
{
    struct qemu__getche_nolock *c = (struct qemu__getche_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getche_nolock();
}

#endif

struct qemu__getche
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _getche(void)
{
    struct qemu__getche call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETCHE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getche(struct qemu_syscall *call)
{
    struct qemu__getche *c = (struct qemu__getche *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getche();
}

#endif

struct qemu__getwche_nolock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _getwche_nolock(void)
{
    struct qemu__getwche_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETWCHE_NOLOCK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getwche_nolock(struct qemu_syscall *call)
{
    struct qemu__getwche_nolock *c = (struct qemu__getwche_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getwche_nolock();
}

#endif

struct qemu__getwche
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _getwche(void)
{
    struct qemu__getwche call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETWCHE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getwche(struct qemu_syscall *call)
{
    struct qemu__getwche *c = (struct qemu__getwche *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getwche();
}

#endif

struct qemu__cgets
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL _cgets(char* str)
{
    struct qemu__cgets call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CGETS);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__cgets(struct qemu_syscall *call)
{
    struct qemu__cgets *c = (struct qemu__cgets *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__cgets(QEMU_G2H(c->str)));
}

#endif

struct qemu__ungetch_nolock
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _ungetch_nolock(int c)
{
    struct qemu__ungetch_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNGETCH_NOLOCK);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ungetch_nolock(struct qemu_syscall *call)
{
    struct qemu__ungetch_nolock *c = (struct qemu__ungetch_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ungetch_nolock(c->c);
}

#endif

struct qemu__ungetch
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _ungetch(int c)
{
    struct qemu__ungetch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNGETCH);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ungetch(struct qemu_syscall *call)
{
    struct qemu__ungetch *c = (struct qemu__ungetch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ungetch(c->c);
}

#endif

struct qemu__ungetwch_nolock
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _ungetwch_nolock(WCHAR c)
{
    struct qemu__ungetwch_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNGETWCH_NOLOCK);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ungetwch_nolock(struct qemu_syscall *call)
{
    struct qemu__ungetwch_nolock *c = (struct qemu__ungetwch_nolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ungetwch_nolock(c->c);
}

#endif

struct qemu__ungetwch
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL _ungetwch(WCHAR c)
{
    struct qemu__ungetwch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNGETWCH);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ungetwch(struct qemu_syscall *call)
{
    struct qemu__ungetwch *c = (struct qemu__ungetwch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ungetwch(c->c);
}

#endif

struct qemu__kbhit
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _kbhit(void)
{
    struct qemu__kbhit call;
    call.super.id = QEMU_SYSCALL_ID(CALL__KBHIT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__kbhit(struct qemu_syscall *call)
{
    struct qemu__kbhit *c = (struct qemu__kbhit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__kbhit();
}

#endif

