/*
 * Copyright 2017 André Hentschel
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
#include <wchar.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_msvcrt.h"

#ifdef QEMU_DLL_GUEST

#include <io.h>
#include <dos.h>

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);

#endif

struct qemu__chdir
{
    struct qemu_syscall super;
    uint64_t newdir;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__chdir(const char * newdir)
{
    struct qemu__chdir call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHDIR);
    call.newdir = (ULONG_PTR)newdir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__chdir(struct qemu_syscall *call)
{
    struct qemu__chdir *c = (struct qemu__chdir *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__chdir(QEMU_G2H(c->newdir));
}

#endif

struct qemu__wchdir
{
    struct qemu_syscall super;
    uint64_t newdir;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wchdir(const WCHAR * newdir)
{
    struct qemu__wchdir call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCHDIR);
    call.newdir = (ULONG_PTR)newdir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wchdir(struct qemu_syscall *call)
{
    struct qemu__wchdir *c = (struct qemu__wchdir *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wchdir(QEMU_G2H(c->newdir));
}

#endif

struct qemu__chdrive
{
    struct qemu_syscall super;
    uint64_t newdrive;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__chdrive(int newdrive)
{
    struct qemu__chdrive call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHDRIVE);
    call.newdrive = (ULONG_PTR)newdrive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__chdrive(struct qemu_syscall *call)
{
    struct qemu__chdrive *c = (struct qemu__chdrive *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__chdrive(c->newdrive);
}

#endif

struct qemu__findclose
{
    struct qemu_syscall super;
    uint64_t hand;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__findclose(intptr_t hand)
{
    struct qemu__findclose call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDCLOSE);
    call.hand = (ULONG_PTR)hand;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findclose(struct qemu_syscall *call)
{
    struct qemu__findclose *c = (struct qemu__findclose *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findclose(c->hand);
}

#endif

struct qemu__findfirst
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__findfirst(const char * fspec, struct _finddata_t* ft)
{
    struct qemu__findfirst call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDFIRST);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findfirst(struct qemu_syscall *call)
{
    struct qemu__findfirst *c = (struct qemu__findfirst *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findfirst(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__findfirst32
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__findfirst32(const char * fspec, struct _finddata32_t* ft)
{
    struct qemu__findfirst32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDFIRST32);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findfirst32(struct qemu_syscall *call)
{
    struct qemu__findfirst32 *c = (struct qemu__findfirst32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findfirst32(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindfirst
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wfindfirst(const WCHAR * fspec, struct _wfinddata_t* ft)
{
    struct qemu__wfindfirst call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDFIRST);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindfirst(struct qemu_syscall *call)
{
    struct qemu__wfindfirst *c = (struct qemu__wfindfirst *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindfirst(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindfirst32
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wfindfirst32(const WCHAR * fspec, struct _wfinddata32_t* ft)
{
    struct qemu__wfindfirst32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDFIRST32);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindfirst32(struct qemu_syscall *call)
{
    struct qemu__wfindfirst32 *c = (struct qemu__wfindfirst32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindfirst32(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__findfirsti64
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__findfirsti64(const char * fspec, struct _finddatai64_t* ft)
{
    struct qemu__findfirsti64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDFIRSTI64);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findfirsti64(struct qemu_syscall *call)
{
    struct qemu__findfirsti64 *c = (struct qemu__findfirsti64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findfirsti64(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__findfirst64
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__findfirst64(const char * fspec, struct __finddata64_t* ft)
{
    struct qemu__findfirst64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDFIRST64);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findfirst64(struct qemu_syscall *call)
{
    struct qemu__findfirst64 *c = (struct qemu__findfirst64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findfirst64(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindfirst64
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wfindfirst64(const WCHAR * fspec, struct _wfinddata64_t* ft)
{
    struct qemu__wfindfirst64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDFIRST64);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindfirst64(struct qemu_syscall *call)
{
    struct qemu__wfindfirst64 *c = (struct qemu__wfindfirst64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindfirst64(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__findfirst64i32
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__findfirst64i32(const char * fspec, struct _finddata64i32_t* ft)
{
    struct qemu__findfirst64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDFIRST64I32);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findfirst64i32(struct qemu_syscall *call)
{
    struct qemu__findfirst64i32 *c = (struct qemu__findfirst64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findfirst64i32(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindfirst64i32
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wfindfirst64i32(const WCHAR * fspec, struct _wfinddata64i32_t* ft)
{
    struct qemu__wfindfirst64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDFIRST64I32);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindfirst64i32(struct qemu_syscall *call)
{
    struct qemu__wfindfirst64i32 *c = (struct qemu__wfindfirst64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindfirst64i32(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindfirsti64
{
    struct qemu_syscall super;
    uint64_t fspec;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wfindfirsti64(const WCHAR * fspec, struct _wfinddatai64_t* ft)
{
    struct qemu__wfindfirsti64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDFIRSTI64);
    call.fspec = (ULONG_PTR)fspec;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindfirsti64(struct qemu_syscall *call)
{
    struct qemu__wfindfirsti64 *c = (struct qemu__wfindfirsti64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindfirsti64(QEMU_G2H(c->fspec), QEMU_G2H(c->ft));
}

#endif

struct qemu__findnext
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__findnext(intptr_t hand, struct _finddata_t * ft)
{
    struct qemu__findnext call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDNEXT);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findnext(struct qemu_syscall *call)
{
    struct qemu__findnext *c = (struct qemu__findnext *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findnext(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__findnext32
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__findnext32(intptr_t hand, struct _finddata32_t * ft)
{
    struct qemu__findnext32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDNEXT32);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findnext32(struct qemu_syscall *call)
{
    struct qemu__findnext32 *c = (struct qemu__findnext32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findnext32(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindnext32
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfindnext32(intptr_t hand, struct _wfinddata32_t * ft)
{
    struct qemu__wfindnext32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDNEXT32);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindnext32(struct qemu_syscall *call)
{
    struct qemu__wfindnext32 *c = (struct qemu__wfindnext32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindnext32(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindnext
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfindnext(intptr_t hand, struct _wfinddata_t * ft)
{
    struct qemu__wfindnext call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDNEXT);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindnext(struct qemu_syscall *call)
{
    struct qemu__wfindnext *c = (struct qemu__wfindnext *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindnext(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__findnexti64
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__findnexti64(intptr_t hand, struct _finddatai64_t * ft)
{
    struct qemu__findnexti64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDNEXTI64);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findnexti64(struct qemu_syscall *call)
{
    struct qemu__findnexti64 *c = (struct qemu__findnexti64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findnexti64(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__findnext64
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__findnext64(intptr_t hand, struct __finddata64_t * ft)
{
    struct qemu__findnext64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDNEXT64);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findnext64(struct qemu_syscall *call)
{
    struct qemu__findnext64 *c = (struct qemu__findnext64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findnext64(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindnext64
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfindnext64(intptr_t hand, struct _wfinddata64_t * ft)
{
    struct qemu__wfindnext64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDNEXT64);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindnext64(struct qemu_syscall *call)
{
    struct qemu__wfindnext64 *c = (struct qemu__wfindnext64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindnext64(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__findnext64i32
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__findnext64i32(intptr_t hand, struct _finddata64i32_t * ft)
{
    struct qemu__findnext64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINDNEXT64I32);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__findnext64i32(struct qemu_syscall *call)
{
    struct qemu__findnext64i32 *c = (struct qemu__findnext64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__findnext64i32(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindnexti64
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfindnexti64(intptr_t hand, struct _wfinddatai64_t * ft)
{
    struct qemu__wfindnexti64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDNEXTI64);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindnexti64(struct qemu_syscall *call)
{
    struct qemu__wfindnexti64 *c = (struct qemu__wfindnexti64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindnexti64(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__wfindnext64i32
{
    struct qemu_syscall super;
    uint64_t hand;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfindnext64i32(intptr_t hand, struct _wfinddata64i32_t * ft)
{
    struct qemu__wfindnext64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFINDNEXT64I32);
    call.hand = (ULONG_PTR)hand;
    call.ft = (ULONG_PTR)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfindnext64i32(struct qemu_syscall *call)
{
    struct qemu__wfindnext64i32 *c = (struct qemu__wfindnext64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfindnext64i32(c->hand, QEMU_G2H(c->ft));
}

#endif

struct qemu__getcwd
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__getcwd(char * buf, int size)
{
    struct qemu__getcwd call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETCWD);
    call.buf = (ULONG_PTR)buf;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__getcwd(struct qemu_syscall *call)
{
    struct qemu__getcwd *c = (struct qemu__getcwd *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p__getcwd(QEMU_G2H(c->buf), c->size));
}

#endif

struct qemu__wgetcwd
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WCHAR* CDECL MSVCRT__wgetcwd(WCHAR * buf, int size)
{
    struct qemu__wgetcwd call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WGETCWD);
    call.buf = (ULONG_PTR)buf;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wgetcwd(struct qemu_syscall *call)
{
    struct qemu__wgetcwd *c = (struct qemu__wgetcwd *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wgetcwd(QEMU_G2H(c->buf), c->size));
}

#endif

struct qemu__getdrive
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__getdrive(void)
{
    struct qemu__getdrive call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETDRIVE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getdrive(struct qemu_syscall *call)
{
    struct qemu__getdrive *c = (struct qemu__getdrive *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getdrive();
}

#endif

struct qemu__getdcwd
{
    struct qemu_syscall super;
    uint64_t drive;
    uint64_t buf;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__getdcwd(int drive, char * buf, int size)
{
    struct qemu__getdcwd call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETDCWD);
    call.drive = (ULONG_PTR)drive;
    call.buf = (ULONG_PTR)buf;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__getdcwd(struct qemu_syscall *call)
{
    struct qemu__getdcwd *c = (struct qemu__getdcwd *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__getdcwd(c->drive, QEMU_G2H(c->buf), c->size));
}

#endif

struct qemu__wgetdcwd
{
    struct qemu_syscall super;
    uint64_t drive;
    uint64_t buf;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WCHAR* CDECL MSVCRT__wgetdcwd(int drive, WCHAR * buf, int size)
{
    struct qemu__wgetdcwd call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WGETDCWD);
    call.drive = (ULONG_PTR)drive;
    call.buf = (ULONG_PTR)buf;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wgetdcwd(struct qemu_syscall *call)
{
    struct qemu__wgetdcwd *c = (struct qemu__wgetdcwd *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wgetdcwd(c->drive, QEMU_G2H(c->buf), c->size));
}

#endif

struct qemu__getdiskfree
{
    struct qemu_syscall super;
    uint64_t disk;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL MSVCRT__getdiskfree(unsigned int disk, struct _diskfree_t * d)
{
    struct qemu__getdiskfree call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETDISKFREE);
    call.disk = (ULONG_PTR)disk;
    call.d = (ULONG_PTR)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getdiskfree(struct qemu_syscall *call)
{
    struct qemu__getdiskfree *c = (struct qemu__getdiskfree *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getdiskfree(c->disk, QEMU_G2H(c->d));
}

#endif

struct qemu__mkdir
{
    struct qemu_syscall super;
    uint64_t newdir;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__mkdir(const char * newdir)
{
    struct qemu__mkdir call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKDIR);
    call.newdir = (ULONG_PTR)newdir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mkdir(struct qemu_syscall *call)
{
    struct qemu__mkdir *c = (struct qemu__mkdir *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mkdir(QEMU_G2H(c->newdir));
}

#endif

struct qemu__wmkdir
{
    struct qemu_syscall super;
    uint64_t newdir;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wmkdir(const WCHAR* newdir)
{
    struct qemu__wmkdir call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WMKDIR);
    call.newdir = (ULONG_PTR)newdir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wmkdir(struct qemu_syscall *call)
{
    struct qemu__wmkdir *c = (struct qemu__wmkdir *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wmkdir(QEMU_G2H(c->newdir));
}

#endif

struct qemu__rmdir
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__rmdir(const char * dir)
{
    struct qemu__rmdir call;
    call.super.id = QEMU_SYSCALL_ID(CALL__RMDIR);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__rmdir(struct qemu_syscall *call)
{
    struct qemu__rmdir *c = (struct qemu__rmdir *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__rmdir(QEMU_G2H(c->dir));
}

#endif

struct qemu__wrmdir
{
    struct qemu_syscall super;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wrmdir(const WCHAR * dir)
{
    struct qemu__wrmdir call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WRMDIR);
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wrmdir(struct qemu_syscall *call)
{
    struct qemu__wrmdir *c = (struct qemu__wrmdir *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wrmdir(QEMU_G2H(c->dir));
}

#endif

struct qemu__splitpath_s
{
    struct qemu_syscall super;
    uint64_t inpath;
    uint64_t drive;
    uint64_t sz_drive;
    uint64_t dir;
    uint64_t sz_dir;
    uint64_t fname;
    uint64_t sz_fname;
    uint64_t ext;
    uint64_t sz_ext;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__splitpath_s(const char* inpath, char* drive, size_t sz_drive, char* dir, size_t sz_dir, char* fname, size_t sz_fname, char* ext, size_t sz_ext)
{
    struct qemu__splitpath_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPLITPATH_S);
    call.inpath = (ULONG_PTR)inpath;
    call.drive = (ULONG_PTR)drive;
    call.sz_drive = (ULONG_PTR)sz_drive;
    call.dir = (ULONG_PTR)dir;
    call.sz_dir = (ULONG_PTR)sz_dir;
    call.fname = (ULONG_PTR)fname;
    call.sz_fname = (ULONG_PTR)sz_fname;
    call.ext = (ULONG_PTR)ext;
    call.sz_ext = (ULONG_PTR)sz_ext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__splitpath_s(struct qemu_syscall *call)
{
    struct qemu__splitpath_s *c = (struct qemu__splitpath_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__splitpath_s(QEMU_G2H(c->inpath), QEMU_G2H(c->drive), c->sz_drive, QEMU_G2H(c->dir), c->sz_dir, QEMU_G2H(c->fname), c->sz_fname, QEMU_G2H(c->ext), c->sz_ext);
}

#endif

struct qemu__splitpath
{
    struct qemu_syscall super;
    uint64_t inpath;
    uint64_t drv;
    uint64_t dir;
    uint64_t fname;
    uint64_t ext;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__splitpath(const char *inpath, char *drv, char *dir, char *fname, char *ext)
{
    struct qemu__splitpath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPLITPATH);
    call.inpath = (ULONG_PTR)inpath;
    call.drv = (ULONG_PTR)drv;
    call.dir = (ULONG_PTR)dir;
    call.fname = (ULONG_PTR)fname;
    call.ext = (ULONG_PTR)ext;

    qemu_syscall(&call.super);
}

#else

void qemu__splitpath(struct qemu_syscall *call)
{
    struct qemu__splitpath *c = (struct qemu__splitpath *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p__splitpath(QEMU_G2H(c->inpath), QEMU_G2H(c->drv), QEMU_G2H(c->dir), QEMU_G2H(c->fname), QEMU_G2H(c->ext));
}

#endif

struct qemu__wsplitpath_s
{
    struct qemu_syscall super;
    uint64_t inpath;
    uint64_t drive;
    uint64_t sz_drive;
    uint64_t dir;
    uint64_t sz_dir;
    uint64_t fname;
    uint64_t sz_fname;
    uint64_t ext;
    uint64_t sz_ext;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wsplitpath_s(const WCHAR* inpath, WCHAR* drive, size_t sz_drive, WCHAR* dir, size_t sz_dir, WCHAR* fname, size_t sz_fname, WCHAR* ext, size_t sz_ext)
{
    struct qemu__wsplitpath_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSPLITPATH_S);
    call.inpath = (ULONG_PTR)inpath;
    call.drive = (ULONG_PTR)drive;
    call.sz_drive = (ULONG_PTR)sz_drive;
    call.dir = (ULONG_PTR)dir;
    call.sz_dir = (ULONG_PTR)sz_dir;
    call.fname = (ULONG_PTR)fname;
    call.sz_fname = (ULONG_PTR)sz_fname;
    call.ext = (ULONG_PTR)ext;
    call.sz_ext = (ULONG_PTR)sz_ext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wsplitpath_s(struct qemu_syscall *call)
{
    struct qemu__wsplitpath_s *c = (struct qemu__wsplitpath_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wsplitpath_s(QEMU_G2H(c->inpath), QEMU_G2H(c->drive), c->sz_drive, QEMU_G2H(c->dir), c->sz_dir, QEMU_G2H(c->fname), c->sz_fname, QEMU_G2H(c->ext), c->sz_ext);
}

#endif

struct qemu__wsplitpath
{
    struct qemu_syscall super;
    uint64_t inpath;
    uint64_t drv;
    uint64_t dir;
    uint64_t fname;
    uint64_t ext;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__wsplitpath(const WCHAR *inpath, WCHAR *drv, WCHAR *dir, WCHAR *fname, WCHAR *ext)
{
    struct qemu__wsplitpath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSPLITPATH);
    call.inpath = (ULONG_PTR)inpath;
    call.drv = (ULONG_PTR)drv;
    call.dir = (ULONG_PTR)dir;
    call.fname = (ULONG_PTR)fname;
    call.ext = (ULONG_PTR)ext;

    qemu_syscall(&call.super);
}

#else

void qemu__wsplitpath(struct qemu_syscall *call)
{
    struct qemu__wsplitpath *c = (struct qemu__wsplitpath *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__wsplitpath(QEMU_G2H(c->inpath), QEMU_G2H(c->drv), QEMU_G2H(c->dir), QEMU_G2H(c->fname), QEMU_G2H(c->ext));
}

#endif

struct qemu__wfullpath
{
    struct qemu_syscall super;
    uint64_t absPath;
    uint64_t relPath;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT__wfullpath(WCHAR * absPath, const WCHAR* relPath, size_t size)
{
    struct qemu__wfullpath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFULLPATH);
    call.absPath = (ULONG_PTR)absPath;
    call.relPath = (ULONG_PTR)relPath;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wfullpath(struct qemu_syscall *call)
{
    struct qemu__wfullpath *c = (struct qemu__wfullpath *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wfullpath(QEMU_G2H(c->absPath), QEMU_G2H(c->relPath), c->size));
}

#endif

struct qemu__fullpath
{
    struct qemu_syscall super;
    uint64_t absPath;
    uint64_t relPath;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__fullpath(char * absPath, const char* relPath, unsigned int size)
{
    struct qemu__fullpath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FULLPATH);
    call.absPath = (ULONG_PTR)absPath;
    call.relPath = (ULONG_PTR)relPath;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__fullpath(struct qemu_syscall *call)
{
    struct qemu__fullpath *c = (struct qemu__fullpath *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__fullpath(QEMU_G2H(c->absPath), QEMU_G2H(c->relPath), c->size));
}

#endif

struct qemu__makepath
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t drive;
    uint64_t directory;
    uint64_t filename;
    uint64_t extension;
};

#ifdef QEMU_DLL_GUEST

VOID CDECL MSVCRT__makepath(char * path, const char * drive, const char *directory, const char * filename, const char * extension)
{
    struct qemu__makepath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MAKEPATH);
    call.path = (ULONG_PTR)path;
    call.drive = (ULONG_PTR)drive;
    call.directory = (ULONG_PTR)directory;
    call.filename = (ULONG_PTR)filename;
    call.extension = (ULONG_PTR)extension;

    qemu_syscall(&call.super);
}

#else

void qemu__makepath(struct qemu_syscall *call)
{
    struct qemu__makepath *c = (struct qemu__makepath *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__makepath(QEMU_G2H(c->path), QEMU_G2H(c->drive), QEMU_G2H(c->directory), QEMU_G2H(c->filename), QEMU_G2H(c->extension));
}

#endif

struct qemu__wmakepath
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t drive;
    uint64_t directory;
    uint64_t filename;
    uint64_t extension;
};

#ifdef QEMU_DLL_GUEST

VOID CDECL MSVCRT__wmakepath(WCHAR *path, const WCHAR *drive, const WCHAR *directory, const WCHAR *filename, const WCHAR *extension)
{
    struct qemu__wmakepath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WMAKEPATH);
    call.path = (ULONG_PTR)path;
    call.drive = (ULONG_PTR)drive;
    call.directory = (ULONG_PTR)directory;
    call.filename = (ULONG_PTR)filename;
    call.extension = (ULONG_PTR)extension;

    qemu_syscall(&call.super);
}

#else

void qemu__wmakepath(struct qemu_syscall *call)
{
    struct qemu__wmakepath *c = (struct qemu__wmakepath *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__wmakepath(QEMU_G2H(c->path), QEMU_G2H(c->drive), QEMU_G2H(c->directory), QEMU_G2H(c->filename), QEMU_G2H(c->extension));
}

#endif

struct qemu__makepath_s
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t size;
    uint64_t drive;
    uint64_t directory;
    uint64_t filename;
    uint64_t extension;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__makepath_s(char *path, size_t size, const char *drive, const char *directory, const char *filename, const char *extension)
{
    struct qemu__makepath_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MAKEPATH_S);
    call.path = (ULONG_PTR)path;
    call.size = (ULONG_PTR)size;
    call.drive = (ULONG_PTR)drive;
    call.directory = (ULONG_PTR)directory;
    call.filename = (ULONG_PTR)filename;
    call.extension = (ULONG_PTR)extension;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__makepath_s(struct qemu_syscall *call)
{
    struct qemu__makepath_s *c = (struct qemu__makepath_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__makepath_s(QEMU_G2H(c->path), c->size, QEMU_G2H(c->drive), QEMU_G2H(c->directory), QEMU_G2H(c->filename), QEMU_G2H(c->extension));
}

#endif

struct qemu__wmakepath_s
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t size;
    uint64_t drive;
    uint64_t directory;
    uint64_t filename;
    uint64_t extension;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wmakepath_s(WCHAR *path, size_t size, const WCHAR *drive, const WCHAR *directory, const WCHAR *filename, const WCHAR *extension)
{
    struct qemu__wmakepath_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WMAKEPATH_S);
    call.path = (ULONG_PTR)path;
    call.size = (ULONG_PTR)size;
    call.drive = (ULONG_PTR)drive;
    call.directory = (ULONG_PTR)directory;
    call.filename = (ULONG_PTR)filename;
    call.extension = (ULONG_PTR)extension;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wmakepath_s(struct qemu_syscall *call)
{
    struct qemu__wmakepath_s *c = (struct qemu__wmakepath_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wmakepath_s(QEMU_G2H(c->path), c->size, QEMU_G2H(c->drive), QEMU_G2H(c->directory), QEMU_G2H(c->filename), QEMU_G2H(c->extension));
}

#endif

struct qemu__searchenv
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t env;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__searchenv(const char* file, const char* env, char *buf)
{
    struct qemu__searchenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SEARCHENV);
    call.file = (ULONG_PTR)file;
    call.env = (ULONG_PTR)env;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);
}

#else

void qemu__searchenv(struct qemu_syscall *call)
{
    struct qemu__searchenv *c = (struct qemu__searchenv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__searchenv(QEMU_G2H(c->file), QEMU_G2H(c->env), QEMU_G2H(c->buf));
}

#endif

struct qemu__searchenv_s
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t env;
    uint64_t buf;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__searchenv_s(const char* file, const char* env, char *buf, size_t count)
{
    struct qemu__searchenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SEARCHENV_S);
    call.file = (ULONG_PTR)file;
    call.env = (ULONG_PTR)env;
    call.buf = (ULONG_PTR)buf;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__searchenv_s(struct qemu_syscall *call)
{
    struct qemu__searchenv_s *c = (struct qemu__searchenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__searchenv_s(QEMU_G2H(c->file), QEMU_G2H(c->env), QEMU_G2H(c->buf), c->count);
}

#endif

struct qemu__wsearchenv
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t env;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__wsearchenv(const WCHAR* file, const WCHAR* env, WCHAR *buf)
{
    struct qemu__wsearchenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSEARCHENV);
    call.file = (ULONG_PTR)file;
    call.env = (ULONG_PTR)env;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);
}

#else

void qemu__wsearchenv(struct qemu_syscall *call)
{
    struct qemu__wsearchenv *c = (struct qemu__wsearchenv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__wsearchenv(QEMU_G2H(c->file), QEMU_G2H(c->env), QEMU_G2H(c->buf));
}

#endif

struct qemu__wsearchenv_s
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t env;
    uint64_t buf;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wsearchenv_s(const WCHAR* file, const WCHAR* env, WCHAR *buf, size_t count)
{
    struct qemu__wsearchenv_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSEARCHENV_S);
    call.file = (ULONG_PTR)file;
    call.env = (ULONG_PTR)env;
    call.buf = (ULONG_PTR)buf;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wsearchenv_s(struct qemu_syscall *call)
{
    struct qemu__wsearchenv_s *c = (struct qemu__wsearchenv_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wsearchenv_s(QEMU_G2H(c->file), QEMU_G2H(c->env), QEMU_G2H(c->buf), c->count);
}

#endif

