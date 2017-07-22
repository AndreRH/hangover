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
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu___p__pctype
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned short** CDECL MSVCRT___p__pctype(void)
{
    struct qemu___p__pctype call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__PCTYPE);

    qemu_syscall(&call.super);

    return (unsigned short **)call.super.iret;
}

#else

void qemu___p__pctype(struct qemu_syscall *call)
{
    struct qemu___p__pctype *c = (struct qemu___p__pctype *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__pctype());
}

#endif

struct qemu___pctype_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const unsigned short* CDECL MSVCRT___pctype_func(void)
{
    struct qemu___pctype_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL___PCTYPE_FUNC);

    qemu_syscall(&call.super);

    return (unsigned short *)call.super.iret;
}

#else

void qemu___pctype_func(struct qemu_syscall *call)
{
    struct qemu___pctype_func *c = (struct qemu___pctype_func *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___pctype_func());
}

#endif

struct qemu__isctype_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t type;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isctype_l(int c, int type, _locale_t locale)
{
    struct qemu__isctype_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISCTYPE_L);
    call.c = (uint64_t)c;
    call.type = (uint64_t)type;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isctype_l(struct qemu_syscall *call)
{
    struct qemu__isctype_l *c = (struct qemu__isctype_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isctype_l(c->c, c->type, QEMU_G2H(c->locale));
}

#endif

struct qemu__isctype
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isctype(int c, int type)
{
    struct qemu__isctype call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISCTYPE);
    call.c = (uint64_t)c;
    call.type = (uint64_t)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isctype(struct qemu_syscall *call)
{
    struct qemu__isctype *c = (struct qemu__isctype *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isctype(c->c, c->type);
}

#endif

struct qemu__isalnum_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isalnum_l(int c, _locale_t locale)
{
    struct qemu__isalnum_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISALNUM_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isalnum_l(struct qemu_syscall *call)
{
    struct qemu__isalnum_l *c = (struct qemu__isalnum_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isalnum_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isalnum
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isalnum(int c)
{
    struct qemu_isalnum call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISALNUM);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isalnum(struct qemu_syscall *call)
{
    struct qemu_isalnum *c = (struct qemu_isalnum *)call;
    WINE_TRACE("\n");
    c->super.iret = p_isalnum(c->c);
}

#endif

struct qemu__isalpha_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isalpha_l(int c, _locale_t locale)
{
    struct qemu__isalpha_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISALPHA_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isalpha_l(struct qemu_syscall *call)
{
    struct qemu__isalpha_l *c = (struct qemu__isalpha_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isalpha_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isalpha
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isalpha(int c)
{
    struct qemu_isalpha call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISALPHA);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isalpha(struct qemu_syscall *call)
{
    struct qemu_isalpha *c = (struct qemu_isalpha *)call;
    WINE_TRACE("\n");
    c->super.iret = p_isalpha(c->c);
}

#endif

struct qemu__iscntrl_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__iscntrl_l(int c, _locale_t locale)
{
    struct qemu__iscntrl_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISCNTRL_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iscntrl_l(struct qemu_syscall *call)
{
    struct qemu__iscntrl_l *c = (struct qemu__iscntrl_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iscntrl_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_iscntrl
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_iscntrl(int c)
{
    struct qemu_iscntrl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCNTRL);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iscntrl(struct qemu_syscall *call)
{
    struct qemu_iscntrl *c = (struct qemu_iscntrl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iscntrl(c->c);
}

#endif

struct qemu__isdigit_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isdigit_l(int c, _locale_t locale)
{
    struct qemu__isdigit_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISDIGIT_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isdigit_l(struct qemu_syscall *call)
{
    struct qemu__isdigit_l *c = (struct qemu__isdigit_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isdigit_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isdigit
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isdigit(int c)
{
    struct qemu_isdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDIGIT);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isdigit(struct qemu_syscall *call)
{
    struct qemu_isdigit *c = (struct qemu_isdigit *)call;
    WINE_TRACE("\n");
    c->super.iret = p_isdigit(c->c);
}

#endif

struct qemu__isgraph_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isgraph_l(int c, _locale_t locale)
{
    struct qemu__isgraph_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISGRAPH_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isgraph_l(struct qemu_syscall *call)
{
    struct qemu__isgraph_l *c = (struct qemu__isgraph_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isgraph_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isgraph
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isgraph(int c)
{
    struct qemu_isgraph call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISGRAPH);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isgraph(struct qemu_syscall *call)
{
    struct qemu_isgraph *c = (struct qemu_isgraph *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isgraph(c->c);
}

#endif

struct qemu__isleadbyte_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isleadbyte_l(int c, _locale_t locale)
{
    struct qemu__isleadbyte_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISLEADBYTE_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isleadbyte_l(struct qemu_syscall *call)
{
    struct qemu__isleadbyte_l *c = (struct qemu__isleadbyte_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isleadbyte_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isleadbyte
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isleadbyte(int c)
{
    struct qemu_isleadbyte call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISLEADBYTE);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isleadbyte(struct qemu_syscall *call)
{
    struct qemu_isleadbyte *c = (struct qemu_isleadbyte *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isleadbyte(c->c);
}

#endif

struct qemu__islower_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__islower_l(int c, _locale_t locale)
{
    struct qemu__islower_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISLOWER_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__islower_l(struct qemu_syscall *call)
{
    struct qemu__islower_l *c = (struct qemu__islower_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__islower_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_islower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_islower(int c)
{
    struct qemu_islower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISLOWER);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_islower(struct qemu_syscall *call)
{
    struct qemu_islower *c = (struct qemu_islower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_islower(c->c);
}

#endif

struct qemu__isprint_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isprint_l(int c, _locale_t locale)
{
    struct qemu__isprint_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISPRINT_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isprint_l(struct qemu_syscall *call)
{
    struct qemu__isprint_l *c = (struct qemu__isprint_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isprint_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isprint
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isprint(int c)
{
    struct qemu_isprint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPRINT);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isprint(struct qemu_syscall *call)
{
    struct qemu_isprint *c = (struct qemu_isprint *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isprint(c->c);
}

#endif

struct qemu_ispunct
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_ispunct(int c)
{
    struct qemu_ispunct call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPUNCT);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ispunct(struct qemu_syscall *call)
{
    struct qemu_ispunct *c = (struct qemu_ispunct *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ispunct(c->c);
}

#endif

struct qemu__isspace_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isspace_l(int c, _locale_t locale)
{
    struct qemu__isspace_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISSPACE_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isspace_l(struct qemu_syscall *call)
{
    struct qemu__isspace_l *c = (struct qemu__isspace_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isspace_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isspace
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isspace(int c)
{
    struct qemu_isspace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISSPACE);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isspace(struct qemu_syscall *call)
{
    struct qemu_isspace *c = (struct qemu_isspace *)call;
    WINE_TRACE("\n");
    c->super.iret = p_isspace(c->c);
}

#endif

struct qemu__isupper_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isupper_l(int c, _locale_t locale)
{
    struct qemu__isupper_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISUPPER_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isupper_l(struct qemu_syscall *call)
{
    struct qemu__isupper_l *c = (struct qemu__isupper_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isupper_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isupper(int c)
{
    struct qemu_isupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISUPPER);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isupper(struct qemu_syscall *call)
{
    struct qemu_isupper *c = (struct qemu_isupper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isupper(c->c);
}

#endif

struct qemu__isxdigit_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isxdigit_l(int c, _locale_t locale)
{
    struct qemu__isxdigit_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISXDIGIT_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isxdigit_l(struct qemu_syscall *call)
{
    struct qemu__isxdigit_l *c = (struct qemu__isxdigit_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isxdigit_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isxdigit
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isxdigit(int c)
{
    struct qemu_isxdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISXDIGIT);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isxdigit(struct qemu_syscall *call)
{
    struct qemu_isxdigit *c = (struct qemu_isxdigit *)call;
    WINE_TRACE("\n");
    c->super.iret = p_isxdigit(c->c);
}

#endif

struct qemu__isblank_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__isblank_l(int c, _locale_t locale)
{
    struct qemu__isblank_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISBLANK_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isblank_l(struct qemu_syscall *call)
{
    struct qemu__isblank_l *c = (struct qemu__isblank_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isblank_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_isblank
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_isblank(int c)
{
    struct qemu_isblank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISBLANK);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isblank(struct qemu_syscall *call)
{
    struct qemu_isblank *c = (struct qemu_isblank *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isblank(c->c);
}

#endif

struct qemu___isascii
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT___isascii(int c)
{
    struct qemu___isascii call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ISASCII);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___isascii(struct qemu_syscall *call)
{
    struct qemu___isascii *c = (struct qemu___isascii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___isascii(c->c);
}

#endif

struct qemu___toascii
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT___toascii(int c)
{
    struct qemu___toascii call;
    call.super.id = QEMU_SYSCALL_ID(CALL___TOASCII);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___toascii(struct qemu_syscall *call)
{
    struct qemu___toascii *c = (struct qemu___toascii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___toascii(c->c);
}

#endif

struct qemu_iswascii
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_iswascii(wchar_t c)
{
    struct qemu_iswascii call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWASCII);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswascii(struct qemu_syscall *call)
{
    struct qemu_iswascii *c = (struct qemu_iswascii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswascii(c->c);
}

#endif

struct qemu___iscsym
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT___iscsym(int c)
{
    struct qemu___iscsym call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ISCSYM);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___iscsym(struct qemu_syscall *call)
{
    struct qemu___iscsym *c = (struct qemu___iscsym *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___iscsym(c->c);
}

#endif

struct qemu___iscsymf
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT___iscsymf(int c)
{
    struct qemu___iscsymf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ISCSYMF);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___iscsymf(struct qemu_syscall *call)
{
    struct qemu___iscsymf *c = (struct qemu___iscsymf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___iscsymf(c->c);
}

#endif

struct qemu__toupper_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__toupper_l(int c, _locale_t locale)
{
    struct qemu__toupper_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOUPPER_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__toupper_l(struct qemu_syscall *call)
{
    struct qemu__toupper_l *c = (struct qemu__toupper_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__toupper_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_toupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_toupper(int c)
{
    struct qemu_toupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOUPPER);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_toupper(struct qemu_syscall *call)
{
    struct qemu_toupper *c = (struct qemu_toupper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_toupper(c->c);
}

#endif

struct qemu__toupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__toupper(int c)
{
    struct qemu__toupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOUPPER);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__toupper(struct qemu_syscall *call)
{
    struct qemu__toupper *c = (struct qemu__toupper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__toupper(c->c);
}

#endif

struct qemu__tolower_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__tolower_l(int c, _locale_t locale)
{
    struct qemu__tolower_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOLOWER_L);
    call.c = (uint64_t)c;
    call.locale = (uint64_t)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__tolower_l(struct qemu_syscall *call)
{
    struct qemu__tolower_l *c = (struct qemu__tolower_l *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__tolower_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_tolower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_tolower(int c)
{
    struct qemu_tolower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOLOWER);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_tolower(struct qemu_syscall *call)
{
    struct qemu_tolower *c = (struct qemu_tolower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_tolower(c->c);
}

#endif

struct qemu__tolower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__tolower(int c)
{
    struct qemu__tolower call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOLOWER);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__tolower(struct qemu_syscall *call)
{
    struct qemu__tolower *c = (struct qemu__tolower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__tolower(c->c);
}

#endif

