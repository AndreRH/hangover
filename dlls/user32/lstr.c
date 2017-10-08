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
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_CharNextA
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharNextA(LPCSTR ptr)
{
    struct qemu_CharNextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARNEXTA);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharNextA(struct qemu_syscall *call)
{
    struct qemu_CharNextA *c = (struct qemu_CharNextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharNextA(QEMU_G2H(c->ptr));
}

#endif

struct qemu_CharNextExA
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t ptr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharNextExA(WORD codepage, LPCSTR ptr, DWORD flags)
{
    struct qemu_CharNextExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARNEXTEXA);
    call.codepage = (ULONG_PTR)codepage;
    call.ptr = (ULONG_PTR)ptr;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharNextExA(struct qemu_syscall *call)
{
    struct qemu_CharNextExA *c = (struct qemu_CharNextExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharNextExA(c->codepage, QEMU_G2H(c->ptr), c->flags);
}

#endif

struct qemu_CharNextExW
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t ptr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPWSTR WINAPI CharNextExW(WORD codepage, LPCWSTR ptr, DWORD flags)
{
    struct qemu_CharNextExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARNEXTEXW);
    call.codepage = (ULONG_PTR)codepage;
    call.ptr = (ULONG_PTR)ptr;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add CharNextExW to Wine headers? */
extern LPWSTR WINAPI CharNextExW(WORD codepage, LPCWSTR ptr, DWORD flags);
void qemu_CharNextExW(struct qemu_syscall *call)
{
    struct qemu_CharNextExW *c = (struct qemu_CharNextExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharNextExW(c->codepage, QEMU_G2H(c->ptr), c->flags);
}

#endif

struct qemu_CharNextW
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPWSTR WINAPI CharNextW(LPCWSTR x)
{
    struct qemu_CharNextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARNEXTW);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharNextW(struct qemu_syscall *call)
{
    struct qemu_CharNextW *c = (struct qemu_CharNextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharNextW(QEMU_G2H(c->x));
}

#endif

struct qemu_CharPrevA
{
    struct qemu_syscall super;
    uint64_t start;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharPrevA(LPCSTR start, LPCSTR ptr)
{
    struct qemu_CharPrevA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARPREVA);
    call.start = (ULONG_PTR)start;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharPrevA(struct qemu_syscall *call)
{
    struct qemu_CharPrevA *c = (struct qemu_CharPrevA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharPrevA(QEMU_G2H(c->start), QEMU_G2H(c->ptr));
}

#endif

struct qemu_CharPrevExA
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t start;
    uint64_t ptr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharPrevExA(WORD codepage, LPCSTR start, LPCSTR ptr, DWORD flags)
{
    struct qemu_CharPrevExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARPREVEXA);
    call.codepage = (ULONG_PTR)codepage;
    call.start = (ULONG_PTR)start;
    call.ptr = (ULONG_PTR)ptr;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharPrevExA(struct qemu_syscall *call)
{
    struct qemu_CharPrevExA *c = (struct qemu_CharPrevExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharPrevExA(c->codepage, QEMU_G2H(c->start), QEMU_G2H(c->ptr), c->flags);
}

#endif

struct qemu_CharPrevExW
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t start;
    uint64_t ptr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharPrevExW(WORD codepage, LPCWSTR start, LPCWSTR ptr, DWORD flags)
{
    struct qemu_CharPrevExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARPREVEXW);
    call.codepage = (ULONG_PTR)codepage;
    call.start = (ULONG_PTR)start;
    call.ptr = (ULONG_PTR)ptr;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add CharPrevExW to Wine headers? */
extern LPSTR WINAPI CharPrevExW(WORD codepage, LPCWSTR start, LPCWSTR ptr, DWORD flags);
void qemu_CharPrevExW(struct qemu_syscall *call)
{
    struct qemu_CharPrevExW *c = (struct qemu_CharPrevExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharPrevExW(c->codepage, QEMU_G2H(c->start), QEMU_G2H(c->ptr), c->flags);
}

#endif

struct qemu_CharPrevW
{
    struct qemu_syscall super;
    uint64_t start;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPWSTR WINAPI CharPrevW(LPCWSTR start,LPCWSTR x)
{
    struct qemu_CharPrevW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARPREVW);
    call.start = (ULONG_PTR)start;
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharPrevW(struct qemu_syscall *call)
{
    struct qemu_CharPrevW *c = (struct qemu_CharPrevW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharPrevW(QEMU_G2H(c->start), QEMU_G2H(c->x));
}

#endif

struct qemu_CharToOemA
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CharToOemA(LPCSTR s, LPSTR d)
{
    struct qemu_CharToOemA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARTOOEMA);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharToOemA(struct qemu_syscall *call)
{
    struct qemu_CharToOemA *c = (struct qemu_CharToOemA *)call;
    WINE_TRACE("\n");
    c->super.iret = CharToOemA(QEMU_G2H(c->s), QEMU_G2H(c->d));
}

#endif

struct qemu_CharToOemBuffA
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CharToOemBuffA(LPCSTR s, LPSTR d, DWORD len)
{
    struct qemu_CharToOemBuffA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARTOOEMBUFFA);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharToOemBuffA(struct qemu_syscall *call)
{
    struct qemu_CharToOemBuffA *c = (struct qemu_CharToOemBuffA *)call;
    WINE_TRACE("\n");
    c->super.iret = CharToOemBuffA(QEMU_G2H(c->s), QEMU_G2H(c->d), c->len);
}

#endif

struct qemu_CharToOemBuffW
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CharToOemBuffW(LPCWSTR s, LPSTR d, DWORD len)
{
    struct qemu_CharToOemBuffW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARTOOEMBUFFW);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharToOemBuffW(struct qemu_syscall *call)
{
    struct qemu_CharToOemBuffW *c = (struct qemu_CharToOemBuffW *)call;
    WINE_TRACE("\n");
    c->super.iret = CharToOemBuffW(QEMU_G2H(c->s), QEMU_G2H(c->d), c->len);
}

#endif

struct qemu_CharToOemW
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CharToOemW(LPCWSTR s, LPSTR d)
{
    struct qemu_CharToOemW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARTOOEMW);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharToOemW(struct qemu_syscall *call)
{
    struct qemu_CharToOemW *c = (struct qemu_CharToOemW *)call;
    WINE_TRACE("\n");
    c->super.iret = CharToOemW(QEMU_G2H(c->s), QEMU_G2H(c->d));
}

#endif

struct qemu_OemToCharA
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OemToCharA(LPCSTR s, LPSTR d)
{
    struct qemu_OemToCharA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OEMTOCHARA);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OemToCharA(struct qemu_syscall *call)
{
    struct qemu_OemToCharA *c = (struct qemu_OemToCharA *)call;
    WINE_TRACE("\n");
    c->super.iret = OemToCharA(QEMU_G2H(c->s), QEMU_G2H(c->d));
}

#endif

struct qemu_OemToCharBuffA
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OemToCharBuffA(LPCSTR s, LPSTR d, DWORD len)
{
    struct qemu_OemToCharBuffA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OEMTOCHARBUFFA);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OemToCharBuffA(struct qemu_syscall *call)
{
    struct qemu_OemToCharBuffA *c = (struct qemu_OemToCharBuffA *)call;
    WINE_TRACE("\n");
    c->super.iret = OemToCharBuffA(QEMU_G2H(c->s), QEMU_G2H(c->d), c->len);
}

#endif

struct qemu_OemToCharBuffW
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OemToCharBuffW(LPCSTR s, LPWSTR d, DWORD len)
{
    struct qemu_OemToCharBuffW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OEMTOCHARBUFFW);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OemToCharBuffW(struct qemu_syscall *call)
{
    struct qemu_OemToCharBuffW *c = (struct qemu_OemToCharBuffW *)call;
    WINE_TRACE("\n");
    c->super.iret = OemToCharBuffW(QEMU_G2H(c->s), QEMU_G2H(c->d), c->len);
}

#endif

struct qemu_OemToCharW
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OemToCharW(LPCSTR s, LPWSTR d)
{
    struct qemu_OemToCharW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OEMTOCHARW);
    call.s = (ULONG_PTR)s;
    call.d = (ULONG_PTR)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OemToCharW(struct qemu_syscall *call)
{
    struct qemu_OemToCharW *c = (struct qemu_OemToCharW *)call;
    WINE_TRACE("\n");
    c->super.iret = OemToCharW(QEMU_G2H(c->s), QEMU_G2H(c->d));
}

#endif

struct qemu_CharLowerA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharLowerA(LPSTR str)
{
    struct qemu_CharLowerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARLOWERA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharLowerA(struct qemu_syscall *call)
{
    struct qemu_CharLowerA *c = (struct qemu_CharLowerA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CharLowerA(QEMU_G2H(c->str));
}

#endif

struct qemu_CharUpperA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPSTR WINAPI CharUpperA(LPSTR str)
{
    struct qemu_CharUpperA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARUPPERA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharUpperA(struct qemu_syscall *call)
{
    struct qemu_CharUpperA *c = (struct qemu_CharUpperA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CharUpperA(QEMU_G2H(c->str));
}

#endif

struct qemu_CharLowerW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPWSTR WINAPI CharLowerW(LPWSTR str)
{
    struct qemu_CharLowerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARLOWERW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharLowerW(struct qemu_syscall *call)
{
    struct qemu_CharLowerW *c = (struct qemu_CharLowerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharLowerW(QEMU_G2H(c->str));
}

#endif

struct qemu_CharUpperW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPWSTR WINAPI CharUpperW(LPWSTR str)
{
    struct qemu_CharUpperW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARUPPERW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CharUpperW(struct qemu_syscall *call)
{
    struct qemu_CharUpperW *c = (struct qemu_CharUpperW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CharUpperW(QEMU_G2H(c->str));
}

#endif

struct qemu_CharLowerBuffA
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI CharLowerBuffA(LPSTR str, DWORD len)
{
    struct qemu_CharLowerBuffA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARLOWERBUFFA);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharLowerBuffA(struct qemu_syscall *call)
{
    struct qemu_CharLowerBuffA *c = (struct qemu_CharLowerBuffA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CharLowerBuffA(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_CharLowerBuffW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI CharLowerBuffW(LPWSTR str, DWORD len)
{
    struct qemu_CharLowerBuffW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARLOWERBUFFW);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharLowerBuffW(struct qemu_syscall *call)
{
    struct qemu_CharLowerBuffW *c = (struct qemu_CharLowerBuffW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CharLowerBuffW(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_CharUpperBuffA
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI CharUpperBuffA(LPSTR str, DWORD len)
{
    struct qemu_CharUpperBuffA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARUPPERBUFFA);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharUpperBuffA(struct qemu_syscall *call)
{
    struct qemu_CharUpperBuffA *c = (struct qemu_CharUpperBuffA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CharUpperBuffA(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_CharUpperBuffW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI CharUpperBuffW(LPWSTR str, DWORD len)
{
    struct qemu_CharUpperBuffW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHARUPPERBUFFW);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CharUpperBuffW(struct qemu_syscall *call)
{
    struct qemu_CharUpperBuffW *c = (struct qemu_CharUpperBuffW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CharUpperBuffW(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_IsCharLowerA
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharLowerA(CHAR x)
{
    struct qemu_IsCharLowerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARLOWERA);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharLowerA(struct qemu_syscall *call)
{
    struct qemu_IsCharLowerA *c = (struct qemu_IsCharLowerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharLowerA(c->x);
}

#endif

struct qemu_IsCharLowerW
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharLowerW(WCHAR ch)
{
    struct qemu_IsCharLowerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARLOWERW);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharLowerW(struct qemu_syscall *call)
{
    struct qemu_IsCharLowerW *c = (struct qemu_IsCharLowerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharLowerW(c->ch);
}

#endif

struct qemu_IsCharUpperA
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharUpperA(CHAR x)
{
    struct qemu_IsCharUpperA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARUPPERA);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharUpperA(struct qemu_syscall *call)
{
    struct qemu_IsCharUpperA *c = (struct qemu_IsCharUpperA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharUpperA(c->x);
}

#endif

struct qemu_IsCharUpperW
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharUpperW(WCHAR ch)
{
    struct qemu_IsCharUpperW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARUPPERW);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharUpperW(struct qemu_syscall *call)
{
    struct qemu_IsCharUpperW *c = (struct qemu_IsCharUpperW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharUpperW(c->ch);
}

#endif

struct qemu_IsCharAlphaNumericA
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharAlphaNumericA(CHAR x)
{
    struct qemu_IsCharAlphaNumericA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARALPHANUMERICA);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharAlphaNumericA(struct qemu_syscall *call)
{
    struct qemu_IsCharAlphaNumericA *c = (struct qemu_IsCharAlphaNumericA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharAlphaNumericA(c->x);
}

#endif

struct qemu_IsCharAlphaNumericW
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharAlphaNumericW(WCHAR ch)
{
    struct qemu_IsCharAlphaNumericW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARALPHANUMERICW);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharAlphaNumericW(struct qemu_syscall *call)
{
    struct qemu_IsCharAlphaNumericW *c = (struct qemu_IsCharAlphaNumericW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharAlphaNumericW(c->ch);
}

#endif

struct qemu_IsCharAlphaA
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharAlphaA(CHAR x)
{
    struct qemu_IsCharAlphaA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARALPHAA);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharAlphaA(struct qemu_syscall *call)
{
    struct qemu_IsCharAlphaA *c = (struct qemu_IsCharAlphaA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharAlphaA(c->x);
}

#endif

struct qemu_IsCharAlphaW
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsCharAlphaW(WCHAR ch)
{
    struct qemu_IsCharAlphaW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARALPHAW);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsCharAlphaW(struct qemu_syscall *call)
{
    struct qemu_IsCharAlphaW *c = (struct qemu_IsCharAlphaW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharAlphaW(c->ch);
}

#endif

