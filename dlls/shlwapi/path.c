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
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shlwapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi);
#endif


struct qemu_PathAppendA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszAppend;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathAppendA (LPSTR lpszPath, LPCSTR lpszAppend)
{
    struct qemu_PathAppendA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHAPPENDA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszAppend = (uint64_t)lpszAppend;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathAppendA(struct qemu_syscall *call)
{
    struct qemu_PathAppendA *c = (struct qemu_PathAppendA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathAppendA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszAppend));
}

#endif

struct qemu_PathAppendW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszAppend;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathAppendW(LPWSTR lpszPath, LPCWSTR lpszAppend)
{
    struct qemu_PathAppendW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHAPPENDW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszAppend = (uint64_t)lpszAppend;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathAppendW(struct qemu_syscall *call)
{
    struct qemu_PathAppendW *c = (struct qemu_PathAppendW *)call;
    WINE_TRACE("\n");
    c->super.iret = PathAppendW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszAppend));
}

#endif

struct qemu_PathCombineA
{
    struct qemu_syscall super;
    uint64_t lpszDest;
    uint64_t lpszDir;
    uint64_t lpszFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathCombineA(LPSTR lpszDest, LPCSTR lpszDir, LPCSTR lpszFile)
{
    struct qemu_PathCombineA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMBINEA);
    call.lpszDest = (uint64_t)lpszDest;
    call.lpszDir = (uint64_t)lpszDir;
    call.lpszFile = (uint64_t)lpszFile;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathCombineA(struct qemu_syscall *call)
{
    struct qemu_PathCombineA *c = (struct qemu_PathCombineA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathCombineA(QEMU_G2H(c->lpszDest), QEMU_G2H(c->lpszDir), QEMU_G2H(c->lpszFile));
}

#endif

struct qemu_PathCombineW
{
    struct qemu_syscall super;
    uint64_t lpszDest;
    uint64_t lpszDir;
    uint64_t lpszFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathCombineW(LPWSTR lpszDest, LPCWSTR lpszDir, LPCWSTR lpszFile)
{
    struct qemu_PathCombineW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMBINEW);
    call.lpszDest = (uint64_t)lpszDest;
    call.lpszDir = (uint64_t)lpszDir;
    call.lpszFile = (uint64_t)lpszFile;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathCombineW(struct qemu_syscall *call)
{
    struct qemu_PathCombineW *c = (struct qemu_PathCombineW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathCombineW(QEMU_G2H(c->lpszDest), QEMU_G2H(c->lpszDir), QEMU_G2H(c->lpszFile));
}

#endif

struct qemu_PathAddBackslashA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathAddBackslashA(LPSTR lpszPath)
{
    struct qemu_PathAddBackslashA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHADDBACKSLASHA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathAddBackslashA(struct qemu_syscall *call)
{
    struct qemu_PathAddBackslashA *c = (struct qemu_PathAddBackslashA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathAddBackslashA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathAddBackslashW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathAddBackslashW(LPWSTR lpszPath)
{
    struct qemu_PathAddBackslashW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHADDBACKSLASHW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathAddBackslashW(struct qemu_syscall *call)
{
    struct qemu_PathAddBackslashW *c = (struct qemu_PathAddBackslashW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathAddBackslashW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathBuildRootA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t drive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathBuildRootA(LPSTR lpszPath, int drive)
{
    struct qemu_PathBuildRootA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHBUILDROOTA);
    call.lpszPath = (uint64_t)lpszPath;
    call.drive = (uint64_t)drive;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathBuildRootA(struct qemu_syscall *call)
{
    struct qemu_PathBuildRootA *c = (struct qemu_PathBuildRootA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathBuildRootA(QEMU_G2H(c->lpszPath), c->drive);
}

#endif

struct qemu_PathBuildRootW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t drive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathBuildRootW(LPWSTR lpszPath, int drive)
{
    struct qemu_PathBuildRootW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHBUILDROOTW);
    call.lpszPath = (uint64_t)lpszPath;
    call.drive = (uint64_t)drive;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathBuildRootW(struct qemu_syscall *call)
{
    struct qemu_PathBuildRootW *c = (struct qemu_PathBuildRootW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathBuildRootW(QEMU_G2H(c->lpszPath), c->drive);
}

#endif

struct qemu_PathFindFileNameA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathFindFileNameA(LPCSTR lpszPath)
{
    struct qemu_PathFindFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDFILENAMEA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathFindFileNameA(struct qemu_syscall *call)
{
    struct qemu_PathFindFileNameA *c = (struct qemu_PathFindFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathFindFileNameA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindFileNameW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathFindFileNameW(LPCWSTR lpszPath)
{
    struct qemu_PathFindFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDFILENAMEW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathFindFileNameW(struct qemu_syscall *call)
{
    struct qemu_PathFindFileNameW *c = (struct qemu_PathFindFileNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)PathFindFileNameW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindExtensionA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathFindExtensionA(LPCSTR lpszPath)
{
    struct qemu_PathFindExtensionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDEXTENSIONA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathFindExtensionA(struct qemu_syscall *call)
{
    struct qemu_PathFindExtensionA *c = (struct qemu_PathFindExtensionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathFindExtensionA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindExtensionW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathFindExtensionW(LPCWSTR lpszPath)
{
    struct qemu_PathFindExtensionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDEXTENSIONW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathFindExtensionW(struct qemu_syscall *call)
{
    struct qemu_PathFindExtensionW *c = (struct qemu_PathFindExtensionW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)PathFindExtensionW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetArgsA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathGetArgsA(LPCSTR lpszPath)
{
    struct qemu_PathGetArgsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETARGSA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathGetArgsA(struct qemu_syscall *call)
{
    struct qemu_PathGetArgsA *c = (struct qemu_PathGetArgsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathGetArgsA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetArgsW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathGetArgsW(LPCWSTR lpszPath)
{
    struct qemu_PathGetArgsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETARGSW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathGetArgsW(struct qemu_syscall *call)
{
    struct qemu_PathGetArgsW *c = (struct qemu_PathGetArgsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathGetArgsW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetDriveNumberA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathGetDriveNumberA(LPCSTR lpszPath)
{
    struct qemu_PathGetDriveNumberA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETDRIVENUMBERA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathGetDriveNumberA(struct qemu_syscall *call)
{
    struct qemu_PathGetDriveNumberA *c = (struct qemu_PathGetDriveNumberA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathGetDriveNumberA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetDriveNumberW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathGetDriveNumberW(LPCWSTR lpszPath)
{
    struct qemu_PathGetDriveNumberW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETDRIVENUMBERW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathGetDriveNumberW(struct qemu_syscall *call)
{
    struct qemu_PathGetDriveNumberW *c = (struct qemu_PathGetDriveNumberW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathGetDriveNumberW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveFileSpecA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRemoveFileSpecA(LPSTR lpszPath)
{
    struct qemu_PathRemoveFileSpecA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEFILESPECA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRemoveFileSpecA(struct qemu_syscall *call)
{
    struct qemu_PathRemoveFileSpecA *c = (struct qemu_PathRemoveFileSpecA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathRemoveFileSpecA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveFileSpecW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRemoveFileSpecW(LPWSTR lpszPath)
{
    struct qemu_PathRemoveFileSpecW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEFILESPECW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRemoveFileSpecW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveFileSpecW *c = (struct qemu_PathRemoveFileSpecW *)call;
    WINE_TRACE("\n");
    c->super.iret = PathRemoveFileSpecW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathStripPathA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathStripPathA(LPSTR lpszPath)
{
    struct qemu_PathStripPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSTRIPPATHA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathStripPathA(struct qemu_syscall *call)
{
    struct qemu_PathStripPathA *c = (struct qemu_PathStripPathA *)call;
    WINE_FIXME("Unverified!\n");
    PathStripPathA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathStripPathW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathStripPathW(LPWSTR lpszPath)
{
    struct qemu_PathStripPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSTRIPPATHW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathStripPathW(struct qemu_syscall *call)
{
    struct qemu_PathStripPathW *c = (struct qemu_PathStripPathW *)call;
    WINE_FIXME("Unverified!\n");
    PathStripPathW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathStripToRootA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathStripToRootA(LPSTR lpszPath)
{
    struct qemu_PathStripToRootA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSTRIPTOROOTA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathStripToRootA(struct qemu_syscall *call)
{
    struct qemu_PathStripToRootA *c = (struct qemu_PathStripToRootA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathStripToRootA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathStripToRootW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathStripToRootW(LPWSTR lpszPath)
{
    struct qemu_PathStripToRootW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSTRIPTOROOTW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathStripToRootW(struct qemu_syscall *call)
{
    struct qemu_PathStripToRootW *c = (struct qemu_PathStripToRootW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathStripToRootW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveArgsA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveArgsA(LPSTR lpszPath)
{
    struct qemu_PathRemoveArgsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEARGSA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveArgsA(struct qemu_syscall *call)
{
    struct qemu_PathRemoveArgsA *c = (struct qemu_PathRemoveArgsA *)call;
    WINE_FIXME("Unverified!\n");
    PathRemoveArgsA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveArgsW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveArgsW(LPWSTR lpszPath)
{
    struct qemu_PathRemoveArgsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEARGSW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveArgsW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveArgsW *c = (struct qemu_PathRemoveArgsW *)call;
    WINE_FIXME("Unverified!\n");
    PathRemoveArgsW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveExtensionA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveExtensionA(LPSTR lpszPath)
{
    struct qemu_PathRemoveExtensionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEEXTENSIONA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveExtensionA(struct qemu_syscall *call)
{
    struct qemu_PathRemoveExtensionA *c = (struct qemu_PathRemoveExtensionA *)call;
    WINE_FIXME("Unverified!\n");
    PathRemoveExtensionA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveExtensionW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveExtensionW(LPWSTR lpszPath)
{
    struct qemu_PathRemoveExtensionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEEXTENSIONW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveExtensionW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveExtensionW *c = (struct qemu_PathRemoveExtensionW *)call;
    WINE_TRACE("\n");
    PathRemoveExtensionW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveBackslashA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathRemoveBackslashA(LPSTR lpszPath)
{
    struct qemu_PathRemoveBackslashA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEBACKSLASHA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathRemoveBackslashA(struct qemu_syscall *call)
{
    struct qemu_PathRemoveBackslashA *c = (struct qemu_PathRemoveBackslashA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathRemoveBackslashA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveBackslashW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathRemoveBackslashW(LPWSTR lpszPath)
{
    struct qemu_PathRemoveBackslashW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEBACKSLASHW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathRemoveBackslashW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveBackslashW *c = (struct qemu_PathRemoveBackslashW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathRemoveBackslashW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveBlanksA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathRemoveBlanksA(LPSTR lpszPath)
{
    struct qemu_PathRemoveBlanksA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEBLANKSA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveBlanksA(struct qemu_syscall *call)
{
    struct qemu_PathRemoveBlanksA *c = (struct qemu_PathRemoveBlanksA *)call;
    WINE_FIXME("Unverified!\n");
    PathRemoveBlanksA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveBlanksW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathRemoveBlanksW(LPWSTR lpszPath)
{
    struct qemu_PathRemoveBlanksW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEBLANKSW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveBlanksW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveBlanksW *c = (struct qemu_PathRemoveBlanksW *)call;
    WINE_FIXME("Unverified!\n");
    PathRemoveBlanksW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathQuoteSpacesA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathQuoteSpacesA(LPSTR lpszPath)
{
    struct qemu_PathQuoteSpacesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHQUOTESPACESA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathQuoteSpacesA(struct qemu_syscall *call)
{
    struct qemu_PathQuoteSpacesA *c = (struct qemu_PathQuoteSpacesA *)call;
    WINE_FIXME("Unverified!\n");
    PathQuoteSpacesA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathQuoteSpacesW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathQuoteSpacesW(LPWSTR lpszPath)
{
    struct qemu_PathQuoteSpacesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHQUOTESPACESW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathQuoteSpacesW(struct qemu_syscall *call)
{
    struct qemu_PathQuoteSpacesW *c = (struct qemu_PathQuoteSpacesW *)call;
    WINE_FIXME("Unverified!\n");
    PathQuoteSpacesW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathUnquoteSpacesA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathUnquoteSpacesA(LPSTR lpszPath)
{
    struct qemu_PathUnquoteSpacesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNQUOTESPACESA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathUnquoteSpacesA(struct qemu_syscall *call)
{
    struct qemu_PathUnquoteSpacesA *c = (struct qemu_PathUnquoteSpacesA *)call;
    WINE_FIXME("Unverified!\n");
    PathUnquoteSpacesA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathUnquoteSpacesW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathUnquoteSpacesW(LPWSTR lpszPath)
{
    struct qemu_PathUnquoteSpacesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNQUOTESPACESW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathUnquoteSpacesW(struct qemu_syscall *call)
{
    struct qemu_PathUnquoteSpacesW *c = (struct qemu_PathUnquoteSpacesW *)call;
    WINE_FIXME("Unverified!\n");
    PathUnquoteSpacesW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathParseIconLocationA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathParseIconLocationA(LPSTR lpszPath)
{
    struct qemu_PathParseIconLocationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHPARSEICONLOCATIONA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathParseIconLocationA(struct qemu_syscall *call)
{
    struct qemu_PathParseIconLocationA *c = (struct qemu_PathParseIconLocationA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathParseIconLocationA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathParseIconLocationW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathParseIconLocationW(LPWSTR lpszPath)
{
    struct qemu_PathParseIconLocationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHPARSEICONLOCATIONW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathParseIconLocationW(struct qemu_syscall *call)
{
    struct qemu_PathParseIconLocationW *c = (struct qemu_PathParseIconLocationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathParseIconLocationW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFileExistsDefExtW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwWhich;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsDefExtW(LPWSTR lpszPath,DWORD dwWhich)
{
    struct qemu_PathFileExistsDefExtW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSDEFEXTW);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwWhich = (uint64_t)dwWhich;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathFileExistsDefExtW to Wine headers? */
extern BOOL WINAPI PathFileExistsDefExtW(LPWSTR lpszPath,DWORD dwWhich);
void qemu_PathFileExistsDefExtW(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsDefExtW *c = (struct qemu_PathFileExistsDefExtW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFileExistsDefExtW(QEMU_G2H(c->lpszPath), c->dwWhich);
}

#endif

struct qemu_PathFileExistsDefExtA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwWhich;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsDefExtA(LPSTR lpszPath,DWORD dwWhich)
{
    struct qemu_PathFileExistsDefExtA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSDEFEXTA);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwWhich = (uint64_t)dwWhich;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathFileExistsDefExtA to Wine headers? */
extern BOOL WINAPI PathFileExistsDefExtA(LPSTR lpszPath,DWORD dwWhich);
void qemu_PathFileExistsDefExtA(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsDefExtA *c = (struct qemu_PathFileExistsDefExtA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFileExistsDefExtA(QEMU_G2H(c->lpszPath), c->dwWhich);
}

#endif

struct qemu_PathFindOnPathExA
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t lppszOtherDirs;
    uint64_t dwWhich;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFindOnPathExA(LPSTR lpszFile,LPCSTR *lppszOtherDirs,DWORD dwWhich)
{
    struct qemu_PathFindOnPathExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDONPATHEXA);
    call.lpszFile = (uint64_t)lpszFile;
    call.lppszOtherDirs = (uint64_t)lppszOtherDirs;
    call.dwWhich = (uint64_t)dwWhich;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathFindOnPathExA to Wine headers? */
extern BOOL WINAPI PathFindOnPathExA(LPSTR lpszFile,LPCSTR *lppszOtherDirs,DWORD dwWhich);
void qemu_PathFindOnPathExA(struct qemu_syscall *call)
{
    struct qemu_PathFindOnPathExA *c = (struct qemu_PathFindOnPathExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFindOnPathExA(QEMU_G2H(c->lpszFile), QEMU_G2H(c->lppszOtherDirs), c->dwWhich);
}

#endif

struct qemu_PathFindOnPathExW
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t lppszOtherDirs;
    uint64_t dwWhich;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFindOnPathExW(LPWSTR lpszFile,LPCWSTR *lppszOtherDirs,DWORD dwWhich)
{
    struct qemu_PathFindOnPathExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDONPATHEXW);
    call.lpszFile = (uint64_t)lpszFile;
    call.lppszOtherDirs = (uint64_t)lppszOtherDirs;
    call.dwWhich = (uint64_t)dwWhich;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathFindOnPathExW to Wine headers? */
extern BOOL WINAPI PathFindOnPathExW(LPWSTR lpszFile,LPCWSTR *lppszOtherDirs,DWORD dwWhich);
void qemu_PathFindOnPathExW(struct qemu_syscall *call)
{
    struct qemu_PathFindOnPathExW *c = (struct qemu_PathFindOnPathExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFindOnPathExW(QEMU_G2H(c->lpszFile), QEMU_G2H(c->lppszOtherDirs), c->dwWhich);
}

#endif

struct qemu_PathFindOnPathA
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t lppszOtherDirs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFindOnPathA(LPSTR lpszFile, LPCSTR *lppszOtherDirs)
{
    struct qemu_PathFindOnPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDONPATHA);
    call.lpszFile = (uint64_t)lpszFile;
    call.lppszOtherDirs = (uint64_t)lppszOtherDirs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFindOnPathA(struct qemu_syscall *call)
{
    struct qemu_PathFindOnPathA *c = (struct qemu_PathFindOnPathA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFindOnPathA(QEMU_G2H(c->lpszFile), QEMU_G2H(c->lppszOtherDirs));
}

#endif

struct qemu_PathFindOnPathW
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t lppszOtherDirs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFindOnPathW(LPWSTR lpszFile, LPCWSTR *lppszOtherDirs)
{
    struct qemu_PathFindOnPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDONPATHW);
    call.lpszFile = (uint64_t)lpszFile;
    call.lppszOtherDirs = (uint64_t)lppszOtherDirs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFindOnPathW(struct qemu_syscall *call)
{
    struct qemu_PathFindOnPathW *c = (struct qemu_PathFindOnPathW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFindOnPathW(QEMU_G2H(c->lpszFile), QEMU_G2H(c->lppszOtherDirs));
}

#endif

struct qemu_PathCompactPathExA
{
    struct qemu_syscall super;
    uint64_t lpszDest;
    uint64_t lpszPath;
    uint64_t cchMax;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathCompactPathExA(LPSTR lpszDest, LPCSTR lpszPath, UINT cchMax, DWORD dwFlags)
{
    struct qemu_PathCompactPathExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMPACTPATHEXA);
    call.lpszDest = (uint64_t)lpszDest;
    call.lpszPath = (uint64_t)lpszPath;
    call.cchMax = (uint64_t)cchMax;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCompactPathExA(struct qemu_syscall *call)
{
    struct qemu_PathCompactPathExA *c = (struct qemu_PathCompactPathExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCompactPathExA(QEMU_G2H(c->lpszDest), QEMU_G2H(c->lpszPath), c->cchMax, c->dwFlags);
}

#endif

struct qemu_PathCompactPathExW
{
    struct qemu_syscall super;
    uint64_t lpszDest;
    uint64_t lpszPath;
    uint64_t cchMax;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathCompactPathExW(LPWSTR lpszDest, LPCWSTR lpszPath, UINT cchMax, DWORD dwFlags)
{
    struct qemu_PathCompactPathExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMPACTPATHEXW);
    call.lpszDest = (uint64_t)lpszDest;
    call.lpszPath = (uint64_t)lpszPath;
    call.cchMax = (uint64_t)cchMax;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCompactPathExW(struct qemu_syscall *call)
{
    struct qemu_PathCompactPathExW *c = (struct qemu_PathCompactPathExW *)call;
    WINE_TRACE("\n");
    c->super.iret = PathCompactPathExW(QEMU_G2H(c->lpszDest), QEMU_G2H(c->lpszPath), c->cchMax, c->dwFlags);
}

#endif

struct qemu_PathIsRelativeA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsRelativeA (LPCSTR lpszPath)
{
    struct qemu_PathIsRelativeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISRELATIVEA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsRelativeA(struct qemu_syscall *call)
{
    struct qemu_PathIsRelativeA *c = (struct qemu_PathIsRelativeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsRelativeA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsRelativeW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsRelativeW (LPCWSTR lpszPath)
{
    struct qemu_PathIsRelativeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISRELATIVEW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsRelativeW(struct qemu_syscall *call)
{
    struct qemu_PathIsRelativeW *c = (struct qemu_PathIsRelativeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsRelativeW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsRootA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsRootA(LPCSTR lpszPath)
{
    struct qemu_PathIsRootA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISROOTA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsRootA(struct qemu_syscall *call)
{
    struct qemu_PathIsRootA *c = (struct qemu_PathIsRootA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsRootA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsRootW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsRootW(LPCWSTR lpszPath)
{
    struct qemu_PathIsRootW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISROOTW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsRootW(struct qemu_syscall *call)
{
    struct qemu_PathIsRootW *c = (struct qemu_PathIsRootW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsRootW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsDirectoryA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsDirectoryA(LPCSTR lpszPath)
{
    struct qemu_PathIsDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISDIRECTORYA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsDirectoryA(struct qemu_syscall *call)
{
    struct qemu_PathIsDirectoryA *c = (struct qemu_PathIsDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsDirectoryA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsDirectoryW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsDirectoryW(LPCWSTR lpszPath)
{
    struct qemu_PathIsDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISDIRECTORYW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsDirectoryW(struct qemu_syscall *call)
{
    struct qemu_PathIsDirectoryW *c = (struct qemu_PathIsDirectoryW *)call;
    WINE_TRACE("\n");
    c->super.iret = PathIsDirectoryW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFileExistsA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsA(LPCSTR lpszPath)
{
    struct qemu_PathFileExistsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFileExistsA(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsA *c = (struct qemu_PathFileExistsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFileExistsA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFileExistsW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsW(LPCWSTR lpszPath)
{
    struct qemu_PathFileExistsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFileExistsW(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsW *c = (struct qemu_PathFileExistsW *)call;
    WINE_TRACE("\n");
    c->super.iret = PathFileExistsW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFileExistsAndAttributesA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwAttr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsAndAttributesA(LPCSTR lpszPath, DWORD *dwAttr)
{
    struct qemu_PathFileExistsAndAttributesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSANDATTRIBUTESA);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwAttr = (uint64_t)dwAttr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFileExistsAndAttributesA(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsAndAttributesA *c = (struct qemu_PathFileExistsAndAttributesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFileExistsAndAttributesA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->dwAttr));
}

#endif

struct qemu_PathFileExistsAndAttributesW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwAttr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsAndAttributesW(LPCWSTR lpszPath, DWORD *dwAttr)
{
    struct qemu_PathFileExistsAndAttributesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSANDATTRIBUTESW);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwAttr = (uint64_t)dwAttr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFileExistsAndAttributesW(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsAndAttributesW *c = (struct qemu_PathFileExistsAndAttributesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathFileExistsAndAttributesW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->dwAttr));
}

#endif

struct qemu_PathMatchSpecA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMatchSpecA(LPCSTR lpszPath, LPCSTR lpszMask)
{
    struct qemu_PathMatchSpecA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMATCHSPECA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszMask = (uint64_t)lpszMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMatchSpecA(struct qemu_syscall *call)
{
    struct qemu_PathMatchSpecA *c = (struct qemu_PathMatchSpecA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathMatchSpecA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszMask));
}

#endif

struct qemu_PathMatchSpecW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMatchSpecW(LPCWSTR lpszPath, LPCWSTR lpszMask)
{
    struct qemu_PathMatchSpecW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMATCHSPECW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszMask = (uint64_t)lpszMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMatchSpecW(struct qemu_syscall *call)
{
    struct qemu_PathMatchSpecW *c = (struct qemu_PathMatchSpecW *)call;
    WINE_TRACE("\n");
    c->super.iret = PathMatchSpecW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszMask));
}

#endif

struct qemu_PathIsSameRootA
{
    struct qemu_syscall super;
    uint64_t lpszPath1;
    uint64_t lpszPath2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsSameRootA(LPCSTR lpszPath1, LPCSTR lpszPath2)
{
    struct qemu_PathIsSameRootA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISSAMEROOTA);
    call.lpszPath1 = (uint64_t)lpszPath1;
    call.lpszPath2 = (uint64_t)lpszPath2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsSameRootA(struct qemu_syscall *call)
{
    struct qemu_PathIsSameRootA *c = (struct qemu_PathIsSameRootA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsSameRootA(QEMU_G2H(c->lpszPath1), QEMU_G2H(c->lpszPath2));
}

#endif

struct qemu_PathIsSameRootW
{
    struct qemu_syscall super;
    uint64_t lpszPath1;
    uint64_t lpszPath2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsSameRootW(LPCWSTR lpszPath1, LPCWSTR lpszPath2)
{
    struct qemu_PathIsSameRootW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISSAMEROOTW);
    call.lpszPath1 = (uint64_t)lpszPath1;
    call.lpszPath2 = (uint64_t)lpszPath2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsSameRootW(struct qemu_syscall *call)
{
    struct qemu_PathIsSameRootW *c = (struct qemu_PathIsSameRootW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsSameRootW(QEMU_G2H(c->lpszPath1), QEMU_G2H(c->lpszPath2));
}

#endif

struct qemu_PathIsContentTypeA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszContentType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsContentTypeA(LPCSTR lpszPath, LPCSTR lpszContentType)
{
    struct qemu_PathIsContentTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISCONTENTTYPEA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszContentType = (uint64_t)lpszContentType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsContentTypeA(struct qemu_syscall *call)
{
    struct qemu_PathIsContentTypeA *c = (struct qemu_PathIsContentTypeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsContentTypeA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszContentType));
}

#endif

struct qemu_PathIsContentTypeW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszContentType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsContentTypeW(LPCWSTR lpszPath, LPCWSTR lpszContentType)
{
    struct qemu_PathIsContentTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISCONTENTTYPEW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszContentType = (uint64_t)lpszContentType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsContentTypeW(struct qemu_syscall *call)
{
    struct qemu_PathIsContentTypeW *c = (struct qemu_PathIsContentTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsContentTypeW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszContentType));
}

#endif

struct qemu_PathIsFileSpecA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsFileSpecA(LPCSTR lpszPath)
{
    struct qemu_PathIsFileSpecA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISFILESPECA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsFileSpecA(struct qemu_syscall *call)
{
    struct qemu_PathIsFileSpecA *c = (struct qemu_PathIsFileSpecA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsFileSpecA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsFileSpecW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsFileSpecW(LPCWSTR lpszPath)
{
    struct qemu_PathIsFileSpecW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISFILESPECW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsFileSpecW(struct qemu_syscall *call)
{
    struct qemu_PathIsFileSpecW *c = (struct qemu_PathIsFileSpecW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsFileSpecW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsPrefixA
{
    struct qemu_syscall super;
    uint64_t lpszPrefix;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsPrefixA (LPCSTR lpszPrefix, LPCSTR lpszPath)
{
    struct qemu_PathIsPrefixA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISPREFIXA);
    call.lpszPrefix = (uint64_t)lpszPrefix;
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsPrefixA(struct qemu_syscall *call)
{
    struct qemu_PathIsPrefixA *c = (struct qemu_PathIsPrefixA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsPrefixA(QEMU_G2H(c->lpszPrefix), QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsPrefixW
{
    struct qemu_syscall super;
    uint64_t lpszPrefix;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsPrefixW(LPCWSTR lpszPrefix, LPCWSTR lpszPath)
{
    struct qemu_PathIsPrefixW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISPREFIXW);
    call.lpszPrefix = (uint64_t)lpszPrefix;
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsPrefixW(struct qemu_syscall *call)
{
    struct qemu_PathIsPrefixW *c = (struct qemu_PathIsPrefixW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsPrefixW(QEMU_G2H(c->lpszPrefix), QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsSystemFolderA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwAttrib;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsSystemFolderA(LPCSTR lpszPath, DWORD dwAttrib)
{
    struct qemu_PathIsSystemFolderA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISSYSTEMFOLDERA);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwAttrib = (uint64_t)dwAttrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsSystemFolderA(struct qemu_syscall *call)
{
    struct qemu_PathIsSystemFolderA *c = (struct qemu_PathIsSystemFolderA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsSystemFolderA(QEMU_G2H(c->lpszPath), c->dwAttrib);
}

#endif

struct qemu_PathIsSystemFolderW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwAttrib;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsSystemFolderW(LPCWSTR lpszPath, DWORD dwAttrib)
{
    struct qemu_PathIsSystemFolderW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISSYSTEMFOLDERW);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwAttrib = (uint64_t)dwAttrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsSystemFolderW(struct qemu_syscall *call)
{
    struct qemu_PathIsSystemFolderW *c = (struct qemu_PathIsSystemFolderW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsSystemFolderW(QEMU_G2H(c->lpszPath), c->dwAttrib);
}

#endif

struct qemu_PathIsUNCA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCA(LPCSTR lpszPath)
{
    struct qemu_PathIsUNCA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCA(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCA *c = (struct qemu_PathIsUNCA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsUNCA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsUNCW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCW(LPCWSTR lpszPath)
{
    struct qemu_PathIsUNCW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCW(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCW *c = (struct qemu_PathIsUNCW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsUNCW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsUNCServerA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCServerA(LPCSTR lpszPath)
{
    struct qemu_PathIsUNCServerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCSERVERA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCServerA(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCServerA *c = (struct qemu_PathIsUNCServerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsUNCServerA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsUNCServerW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCServerW(LPCWSTR lpszPath)
{
    struct qemu_PathIsUNCServerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCSERVERW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCServerW(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCServerW *c = (struct qemu_PathIsUNCServerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsUNCServerW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsUNCServerShareA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCServerShareA(LPCSTR lpszPath)
{
    struct qemu_PathIsUNCServerShareA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCSERVERSHAREA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCServerShareA(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCServerShareA *c = (struct qemu_PathIsUNCServerShareA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsUNCServerShareA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsUNCServerShareW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCServerShareW(LPCWSTR lpszPath)
{
    struct qemu_PathIsUNCServerShareW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCSERVERSHAREW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCServerShareW(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCServerShareW *c = (struct qemu_PathIsUNCServerShareW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsUNCServerShareW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathCanonicalizeA
{
    struct qemu_syscall super;
    uint64_t lpszBuf;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathCanonicalizeA(LPSTR lpszBuf, LPCSTR lpszPath)
{
    struct qemu_PathCanonicalizeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCANONICALIZEA);
    call.lpszBuf = (uint64_t)lpszBuf;
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCanonicalizeA(struct qemu_syscall *call)
{
    struct qemu_PathCanonicalizeA *c = (struct qemu_PathCanonicalizeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCanonicalizeA(QEMU_G2H(c->lpszBuf), QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathCanonicalizeW
{
    struct qemu_syscall super;
    uint64_t lpszBuf;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathCanonicalizeW(LPWSTR lpszBuf, LPCWSTR lpszPath)
{
    struct qemu_PathCanonicalizeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCANONICALIZEW);
    call.lpszBuf = (uint64_t)lpszBuf;
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCanonicalizeW(struct qemu_syscall *call)
{
    struct qemu_PathCanonicalizeW *c = (struct qemu_PathCanonicalizeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCanonicalizeW(QEMU_G2H(c->lpszBuf), QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindNextComponentA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathFindNextComponentA(LPCSTR lpszPath)
{
    struct qemu_PathFindNextComponentA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDNEXTCOMPONENTA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathFindNextComponentA(struct qemu_syscall *call)
{
    struct qemu_PathFindNextComponentA *c = (struct qemu_PathFindNextComponentA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathFindNextComponentA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindNextComponentW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathFindNextComponentW(LPCWSTR lpszPath)
{
    struct qemu_PathFindNextComponentW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDNEXTCOMPONENTW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathFindNextComponentW(struct qemu_syscall *call)
{
    struct qemu_PathFindNextComponentW *c = (struct qemu_PathFindNextComponentW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathFindNextComponentW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathAddExtensionA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszExtension;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathAddExtensionA(LPSTR lpszPath, LPCSTR lpszExtension)
{
    struct qemu_PathAddExtensionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHADDEXTENSIONA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszExtension = (uint64_t)lpszExtension;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathAddExtensionA(struct qemu_syscall *call)
{
    struct qemu_PathAddExtensionA *c = (struct qemu_PathAddExtensionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathAddExtensionA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszExtension));
}

#endif

struct qemu_PathAddExtensionW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszExtension;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathAddExtensionW(LPWSTR lpszPath, LPCWSTR lpszExtension)
{
    struct qemu_PathAddExtensionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHADDEXTENSIONW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszExtension = (uint64_t)lpszExtension;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathAddExtensionW(struct qemu_syscall *call)
{
    struct qemu_PathAddExtensionW *c = (struct qemu_PathAddExtensionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathAddExtensionW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszExtension));
}

#endif

struct qemu_PathMakePrettyA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMakePrettyA(LPSTR lpszPath)
{
    struct qemu_PathMakePrettyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMAKEPRETTYA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMakePrettyA(struct qemu_syscall *call)
{
    struct qemu_PathMakePrettyA *c = (struct qemu_PathMakePrettyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathMakePrettyA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathMakePrettyW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMakePrettyW(LPWSTR lpszPath)
{
    struct qemu_PathMakePrettyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMAKEPRETTYW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMakePrettyW(struct qemu_syscall *call)
{
    struct qemu_PathMakePrettyW *c = (struct qemu_PathMakePrettyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathMakePrettyW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathCommonPrefixA
{
    struct qemu_syscall super;
    uint64_t lpszFile1;
    uint64_t lpszFile2;
    uint64_t achPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathCommonPrefixA(LPCSTR lpszFile1, LPCSTR lpszFile2, LPSTR achPath)
{
    struct qemu_PathCommonPrefixA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMMONPREFIXA);
    call.lpszFile1 = (uint64_t)lpszFile1;
    call.lpszFile2 = (uint64_t)lpszFile2;
    call.achPath = (uint64_t)achPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCommonPrefixA(struct qemu_syscall *call)
{
    struct qemu_PathCommonPrefixA *c = (struct qemu_PathCommonPrefixA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCommonPrefixA(QEMU_G2H(c->lpszFile1), QEMU_G2H(c->lpszFile2), QEMU_G2H(c->achPath));
}

#endif

struct qemu_PathCommonPrefixW
{
    struct qemu_syscall super;
    uint64_t lpszFile1;
    uint64_t lpszFile2;
    uint64_t achPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathCommonPrefixW(LPCWSTR lpszFile1, LPCWSTR lpszFile2, LPWSTR achPath)
{
    struct qemu_PathCommonPrefixW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMMONPREFIXW);
    call.lpszFile1 = (uint64_t)lpszFile1;
    call.lpszFile2 = (uint64_t)lpszFile2;
    call.achPath = (uint64_t)achPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCommonPrefixW(struct qemu_syscall *call)
{
    struct qemu_PathCommonPrefixW *c = (struct qemu_PathCommonPrefixW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCommonPrefixW(QEMU_G2H(c->lpszFile1), QEMU_G2H(c->lpszFile2), QEMU_G2H(c->achPath));
}

#endif

struct qemu_PathCompactPathA
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpszPath;
    uint64_t dx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathCompactPathA(HDC hDC, LPSTR lpszPath, UINT dx)
{
    struct qemu_PathCompactPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMPACTPATHA);
    call.hDC = (uint64_t)hDC;
    call.lpszPath = (uint64_t)lpszPath;
    call.dx = (uint64_t)dx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCompactPathA(struct qemu_syscall *call)
{
    struct qemu_PathCompactPathA *c = (struct qemu_PathCompactPathA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCompactPathA(QEMU_G2H(c->hDC), QEMU_G2H(c->lpszPath), c->dx);
}

#endif

struct qemu_PathCompactPathW
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpszPath;
    uint64_t dx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathCompactPathW(HDC hDC, LPWSTR lpszPath, UINT dx)
{
    struct qemu_PathCompactPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMPACTPATHW);
    call.hDC = (uint64_t)hDC;
    call.lpszPath = (uint64_t)lpszPath;
    call.dx = (uint64_t)dx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCompactPathW(struct qemu_syscall *call)
{
    struct qemu_PathCompactPathW *c = (struct qemu_PathCompactPathW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCompactPathW(QEMU_G2H(c->hDC), QEMU_G2H(c->lpszPath), c->dx);
}

#endif

struct qemu_PathGetCharTypeA
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI PathGetCharTypeA(UCHAR ch)
{
    struct qemu_PathGetCharTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETCHARTYPEA);
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathGetCharTypeA(struct qemu_syscall *call)
{
    struct qemu_PathGetCharTypeA *c = (struct qemu_PathGetCharTypeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathGetCharTypeA(c->ch);
}

#endif

struct qemu_PathGetCharTypeW
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI PathGetCharTypeW(WCHAR ch)
{
    struct qemu_PathGetCharTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETCHARTYPEW);
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathGetCharTypeW(struct qemu_syscall *call)
{
    struct qemu_PathGetCharTypeW *c = (struct qemu_PathGetCharTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathGetCharTypeW(c->ch);
}

#endif

struct qemu_PathMakeSystemFolderA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMakeSystemFolderA(LPCSTR lpszPath)
{
    struct qemu_PathMakeSystemFolderA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMAKESYSTEMFOLDERA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMakeSystemFolderA(struct qemu_syscall *call)
{
    struct qemu_PathMakeSystemFolderA *c = (struct qemu_PathMakeSystemFolderA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathMakeSystemFolderA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathMakeSystemFolderW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMakeSystemFolderW(LPCWSTR lpszPath)
{
    struct qemu_PathMakeSystemFolderW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMAKESYSTEMFOLDERW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMakeSystemFolderW(struct qemu_syscall *call)
{
    struct qemu_PathMakeSystemFolderW *c = (struct qemu_PathMakeSystemFolderW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathMakeSystemFolderW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRenameExtensionA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszExt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRenameExtensionA(LPSTR lpszPath, LPCSTR lpszExt)
{
    struct qemu_PathRenameExtensionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHRENAMEEXTENSIONA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszExt = (uint64_t)lpszExt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRenameExtensionA(struct qemu_syscall *call)
{
    struct qemu_PathRenameExtensionA *c = (struct qemu_PathRenameExtensionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathRenameExtensionA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszExt));
}

#endif

struct qemu_PathRenameExtensionW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszExt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRenameExtensionW(LPWSTR lpszPath, LPCWSTR lpszExt)
{
    struct qemu_PathRenameExtensionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHRENAMEEXTENSIONW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszExt = (uint64_t)lpszExt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRenameExtensionW(struct qemu_syscall *call)
{
    struct qemu_PathRenameExtensionW *c = (struct qemu_PathRenameExtensionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathRenameExtensionW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszExt));
}

#endif

struct qemu_PathSearchAndQualifyA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszBuf;
    uint64_t cchBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathSearchAndQualifyA(LPCSTR lpszPath, LPSTR lpszBuf, UINT cchBuf)
{
    struct qemu_PathSearchAndQualifyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSEARCHANDQUALIFYA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszBuf = (uint64_t)lpszBuf;
    call.cchBuf = (uint64_t)cchBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathSearchAndQualifyA(struct qemu_syscall *call)
{
    struct qemu_PathSearchAndQualifyA *c = (struct qemu_PathSearchAndQualifyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathSearchAndQualifyA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszBuf), c->cchBuf);
}

#endif

struct qemu_PathSearchAndQualifyW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszBuf;
    uint64_t cchBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathSearchAndQualifyW(LPCWSTR lpszPath, LPWSTR lpszBuf, UINT cchBuf)
{
    struct qemu_PathSearchAndQualifyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSEARCHANDQUALIFYW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszBuf = (uint64_t)lpszBuf;
    call.cchBuf = (uint64_t)cchBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathSearchAndQualifyW(struct qemu_syscall *call)
{
    struct qemu_PathSearchAndQualifyW *c = (struct qemu_PathSearchAndQualifyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathSearchAndQualifyW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszBuf), c->cchBuf);
}

#endif

struct qemu_PathSkipRootA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI PathSkipRootA(LPCSTR lpszPath)
{
    struct qemu_PathSkipRootA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSKIPROOTA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_PathSkipRootA(struct qemu_syscall *call)
{
    struct qemu_PathSkipRootA *c = (struct qemu_PathSkipRootA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathSkipRootA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathSkipRootW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI PathSkipRootW(LPCWSTR lpszPath)
{
    struct qemu_PathSkipRootW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSKIPROOTW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_PathSkipRootW(struct qemu_syscall *call)
{
    struct qemu_PathSkipRootW *c = (struct qemu_PathSkipRootW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathSkipRootW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathCreateFromUrlA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszPath;
    uint64_t pcchPath;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI PathCreateFromUrlA(LPCSTR pszUrl, LPSTR pszPath, LPDWORD pcchPath, DWORD dwReserved)
{
    struct qemu_PathCreateFromUrlA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCREATEFROMURLA);
    call.pszUrl = (uint64_t)pszUrl;
    call.pszPath = (uint64_t)pszPath;
    call.pcchPath = (uint64_t)pcchPath;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCreateFromUrlA(struct qemu_syscall *call)
{
    struct qemu_PathCreateFromUrlA *c = (struct qemu_PathCreateFromUrlA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCreateFromUrlA(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszPath), QEMU_G2H(c->pcchPath), c->dwReserved);
}

#endif

struct qemu_PathCreateFromUrlW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszPath;
    uint64_t pcchPath;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI PathCreateFromUrlW(LPCWSTR pszUrl, LPWSTR pszPath, LPDWORD pcchPath, DWORD dwReserved)
{
    struct qemu_PathCreateFromUrlW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCREATEFROMURLW);
    call.pszUrl = (uint64_t)pszUrl;
    call.pszPath = (uint64_t)pszPath;
    call.pcchPath = (uint64_t)pcchPath;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCreateFromUrlW(struct qemu_syscall *call)
{
    struct qemu_PathCreateFromUrlW *c = (struct qemu_PathCreateFromUrlW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCreateFromUrlW(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszPath), QEMU_G2H(c->pcchPath), c->dwReserved);
}

#endif

struct qemu_PathCreateFromUrlAlloc
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszPath;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI PathCreateFromUrlAlloc(LPCWSTR pszUrl, LPWSTR *pszPath, DWORD dwReserved)
{
    struct qemu_PathCreateFromUrlAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCREATEFROMURLALLOC);
    call.pszUrl = (uint64_t)pszUrl;
    call.pszPath = (uint64_t)pszPath;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCreateFromUrlAlloc(struct qemu_syscall *call)
{
    struct qemu_PathCreateFromUrlAlloc *c = (struct qemu_PathCreateFromUrlAlloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCreateFromUrlAlloc(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszPath), c->dwReserved);
}

#endif

struct qemu_PathRelativePathToA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszFrom;
    uint64_t dwAttrFrom;
    uint64_t lpszTo;
    uint64_t dwAttrTo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRelativePathToA(LPSTR lpszPath, LPCSTR lpszFrom, DWORD dwAttrFrom, LPCSTR lpszTo, DWORD dwAttrTo)
{
    struct qemu_PathRelativePathToA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHRELATIVEPATHTOA);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszFrom = (uint64_t)lpszFrom;
    call.dwAttrFrom = (uint64_t)dwAttrFrom;
    call.lpszTo = (uint64_t)lpszTo;
    call.dwAttrTo = (uint64_t)dwAttrTo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRelativePathToA(struct qemu_syscall *call)
{
    struct qemu_PathRelativePathToA *c = (struct qemu_PathRelativePathToA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathRelativePathToA(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszFrom), c->dwAttrFrom, QEMU_G2H(c->lpszTo), c->dwAttrTo);
}

#endif

struct qemu_PathRelativePathToW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszFrom;
    uint64_t dwAttrFrom;
    uint64_t lpszTo;
    uint64_t dwAttrTo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRelativePathToW(LPWSTR lpszPath, LPCWSTR lpszFrom, DWORD dwAttrFrom, LPCWSTR lpszTo, DWORD dwAttrTo)
{
    struct qemu_PathRelativePathToW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHRELATIVEPATHTOW);
    call.lpszPath = (uint64_t)lpszPath;
    call.lpszFrom = (uint64_t)lpszFrom;
    call.dwAttrFrom = (uint64_t)dwAttrFrom;
    call.lpszTo = (uint64_t)lpszTo;
    call.dwAttrTo = (uint64_t)dwAttrTo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRelativePathToW(struct qemu_syscall *call)
{
    struct qemu_PathRelativePathToW *c = (struct qemu_PathRelativePathToW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathRelativePathToW(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszFrom), c->dwAttrFrom, QEMU_G2H(c->lpszTo), c->dwAttrTo);
}

#endif

struct qemu_PathUnmakeSystemFolderA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathUnmakeSystemFolderA(LPCSTR lpszPath)
{
    struct qemu_PathUnmakeSystemFolderA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNMAKESYSTEMFOLDERA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathUnmakeSystemFolderA(struct qemu_syscall *call)
{
    struct qemu_PathUnmakeSystemFolderA *c = (struct qemu_PathUnmakeSystemFolderA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathUnmakeSystemFolderA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathUnmakeSystemFolderW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathUnmakeSystemFolderW(LPCWSTR lpszPath)
{
    struct qemu_PathUnmakeSystemFolderW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNMAKESYSTEMFOLDERW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathUnmakeSystemFolderW(struct qemu_syscall *call)
{
    struct qemu_PathUnmakeSystemFolderW *c = (struct qemu_PathUnmakeSystemFolderW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathUnmakeSystemFolderW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathSetDlgItemPathA
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t id;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathSetDlgItemPathA(HWND hDlg, int id, LPCSTR lpszPath)
{
    struct qemu_PathSetDlgItemPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSETDLGITEMPATHA);
    call.hDlg = (uint64_t)hDlg;
    call.id = (uint64_t)id;
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathSetDlgItemPathA(struct qemu_syscall *call)
{
    struct qemu_PathSetDlgItemPathA *c = (struct qemu_PathSetDlgItemPathA *)call;
    WINE_FIXME("Unverified!\n");
    PathSetDlgItemPathA(QEMU_G2H(c->hDlg), c->id, QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathSetDlgItemPathW
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t id;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathSetDlgItemPathW(HWND hDlg, int id, LPCWSTR lpszPath)
{
    struct qemu_PathSetDlgItemPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSETDLGITEMPATHW);
    call.hDlg = (uint64_t)hDlg;
    call.id = (uint64_t)id;
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathSetDlgItemPathW(struct qemu_syscall *call)
{
    struct qemu_PathSetDlgItemPathW *c = (struct qemu_PathSetDlgItemPathW *)call;
    WINE_FIXME("Unverified!\n");
    PathSetDlgItemPathW(QEMU_G2H(c->hDlg), c->id, QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsNetworkPathA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsNetworkPathA(LPCSTR lpszPath)
{
    struct qemu_PathIsNetworkPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISNETWORKPATHA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsNetworkPathA(struct qemu_syscall *call)
{
    struct qemu_PathIsNetworkPathA *c = (struct qemu_PathIsNetworkPathA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsNetworkPathA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsNetworkPathW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsNetworkPathW(LPCWSTR lpszPath)
{
    struct qemu_PathIsNetworkPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISNETWORKPATHW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsNetworkPathW(struct qemu_syscall *call)
{
    struct qemu_PathIsNetworkPathW *c = (struct qemu_PathIsNetworkPathW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsNetworkPathW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsLFNFileSpecA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsLFNFileSpecA(LPCSTR lpszPath)
{
    struct qemu_PathIsLFNFileSpecA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISLFNFILESPECA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsLFNFileSpecA(struct qemu_syscall *call)
{
    struct qemu_PathIsLFNFileSpecA *c = (struct qemu_PathIsLFNFileSpecA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsLFNFileSpecA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsLFNFileSpecW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsLFNFileSpecW(LPCWSTR lpszPath)
{
    struct qemu_PathIsLFNFileSpecW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISLFNFILESPECW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsLFNFileSpecW(struct qemu_syscall *call)
{
    struct qemu_PathIsLFNFileSpecW *c = (struct qemu_PathIsLFNFileSpecW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsLFNFileSpecW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsDirectoryEmptyA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsDirectoryEmptyA(LPCSTR lpszPath)
{
    struct qemu_PathIsDirectoryEmptyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISDIRECTORYEMPTYA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsDirectoryEmptyA(struct qemu_syscall *call)
{
    struct qemu_PathIsDirectoryEmptyA *c = (struct qemu_PathIsDirectoryEmptyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsDirectoryEmptyA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsDirectoryEmptyW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsDirectoryEmptyW(LPCWSTR lpszPath)
{
    struct qemu_PathIsDirectoryEmptyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISDIRECTORYEMPTYW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsDirectoryEmptyW(struct qemu_syscall *call)
{
    struct qemu_PathIsDirectoryEmptyW *c = (struct qemu_PathIsDirectoryEmptyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsDirectoryEmptyW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindSuffixArrayA
{
    struct qemu_syscall super;
    uint64_t lpszSuffix;
    uint64_t lppszArray;
    uint64_t dwCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPCSTR WINAPI PathFindSuffixArrayA(LPCSTR lpszSuffix, const LPCSTR *lppszArray, int dwCount)
{
    struct qemu_PathFindSuffixArrayA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDSUFFIXARRAYA);
    call.lpszSuffix = (uint64_t)lpszSuffix;
    call.lppszArray = (uint64_t)lppszArray;
    call.dwCount = (uint64_t)dwCount;

    qemu_syscall(&call.super);

    return (LPCSTR)call.super.iret;
}

#else

void qemu_PathFindSuffixArrayA(struct qemu_syscall *call)
{
    struct qemu_PathFindSuffixArrayA *c = (struct qemu_PathFindSuffixArrayA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathFindSuffixArrayA(QEMU_G2H(c->lpszSuffix), QEMU_G2H(c->lppszArray), c->dwCount);
}

#endif

struct qemu_PathFindSuffixArrayW
{
    struct qemu_syscall super;
    uint64_t lpszSuffix;
    uint64_t lppszArray;
    uint64_t dwCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPCWSTR WINAPI PathFindSuffixArrayW(LPCWSTR lpszSuffix, const LPCWSTR *lppszArray, int dwCount)
{
    struct qemu_PathFindSuffixArrayW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDSUFFIXARRAYW);
    call.lpszSuffix = (uint64_t)lpszSuffix;
    call.lppszArray = (uint64_t)lppszArray;
    call.dwCount = (uint64_t)dwCount;

    qemu_syscall(&call.super);

    return (LPCWSTR)call.super.iret;
}

#else

void qemu_PathFindSuffixArrayW(struct qemu_syscall *call)
{
    struct qemu_PathFindSuffixArrayW *c = (struct qemu_PathFindSuffixArrayW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathFindSuffixArrayW(QEMU_G2H(c->lpszSuffix), QEMU_G2H(c->lppszArray), c->dwCount);
}

#endif

struct qemu_PathUndecorateA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathUndecorateA(LPSTR lpszPath)
{
    struct qemu_PathUndecorateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNDECORATEA);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathUndecorateA(struct qemu_syscall *call)
{
    struct qemu_PathUndecorateA *c = (struct qemu_PathUndecorateA *)call;
    WINE_FIXME("Unverified!\n");
    PathUndecorateA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathUndecorateW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathUndecorateW(LPWSTR lpszPath)
{
    struct qemu_PathUndecorateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNDECORATEW);
    call.lpszPath = (uint64_t)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathUndecorateW(struct qemu_syscall *call)
{
    struct qemu_PathUndecorateW *c = (struct qemu_PathUndecorateW *)call;
    WINE_FIXME("Unverified!\n");
    PathUndecorateW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathUnExpandEnvStringsA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buffer;
    uint64_t buf_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathUnExpandEnvStringsA(LPCSTR path, LPSTR buffer, UINT buf_len)
{
    struct qemu_PathUnExpandEnvStringsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNEXPANDENVSTRINGSA);
    call.path = (uint64_t)path;
    call.buffer = (uint64_t)buffer;
    call.buf_len = (uint64_t)buf_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathUnExpandEnvStringsA(struct qemu_syscall *call)
{
    struct qemu_PathUnExpandEnvStringsA *c = (struct qemu_PathUnExpandEnvStringsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathUnExpandEnvStringsA(QEMU_G2H(c->path), QEMU_G2H(c->buffer), c->buf_len);
}

#endif

struct qemu_PathUnExpandEnvStringsW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buffer;
    uint64_t buf_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathUnExpandEnvStringsW(LPCWSTR path, LPWSTR buffer, UINT buf_len)
{
    struct qemu_PathUnExpandEnvStringsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNEXPANDENVSTRINGSW);
    call.path = (uint64_t)path;
    call.buffer = (uint64_t)buffer;
    call.buf_len = (uint64_t)buf_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathUnExpandEnvStringsW(struct qemu_syscall *call)
{
    struct qemu_PathUnExpandEnvStringsW *c = (struct qemu_PathUnExpandEnvStringsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathUnExpandEnvStringsW(QEMU_G2H(c->path), QEMU_G2H(c->buffer), c->buf_len);
}

#endif

struct qemu_SHGetWebFolderFilePathA
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t lpszPath;
    uint64_t dwPathLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetWebFolderFilePathA(LPCSTR lpszFile, LPSTR lpszPath, DWORD dwPathLen)
{
    struct qemu_SHGetWebFolderFilePathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETWEBFOLDERFILEPATHA);
    call.lpszFile = (uint64_t)lpszFile;
    call.lpszPath = (uint64_t)lpszPath;
    call.dwPathLen = (uint64_t)dwPathLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetWebFolderFilePathA to Wine headers? */
extern HRESULT WINAPI SHGetWebFolderFilePathA(LPCSTR lpszFile, LPSTR lpszPath, DWORD dwPathLen);
void qemu_SHGetWebFolderFilePathA(struct qemu_syscall *call)
{
    struct qemu_SHGetWebFolderFilePathA *c = (struct qemu_SHGetWebFolderFilePathA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetWebFolderFilePathA(QEMU_G2H(c->lpszFile), QEMU_G2H(c->lpszPath), c->dwPathLen);
}

#endif

struct qemu_SHGetWebFolderFilePathW
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t lpszPath;
    uint64_t dwPathLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetWebFolderFilePathW(LPCWSTR lpszFile, LPWSTR lpszPath, DWORD dwPathLen)
{
    struct qemu_SHGetWebFolderFilePathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETWEBFOLDERFILEPATHW);
    call.lpszFile = (uint64_t)lpszFile;
    call.lpszPath = (uint64_t)lpszPath;
    call.dwPathLen = (uint64_t)dwPathLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetWebFolderFilePathW to Wine headers? */
extern HRESULT WINAPI SHGetWebFolderFilePathW(LPCWSTR lpszFile, LPWSTR lpszPath, DWORD dwPathLen);
void qemu_SHGetWebFolderFilePathW(struct qemu_syscall *call)
{
    struct qemu_SHGetWebFolderFilePathW *c = (struct qemu_SHGetWebFolderFilePathW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetWebFolderFilePathW(QEMU_G2H(c->lpszFile), QEMU_G2H(c->lpszPath), c->dwPathLen);
}

#endif

struct qemu_PathIsValidCharA
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t class;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsValidCharA(char c, DWORD class)
{
    struct qemu_PathIsValidCharA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISVALIDCHARA);
    call.c = (uint64_t)c;
    call.class = (uint64_t)class;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathIsValidCharA to Wine headers? */
extern BOOL WINAPI PathIsValidCharA(WCHAR c, DWORD class);
void qemu_PathIsValidCharA(struct qemu_syscall *call)
{
    struct qemu_PathIsValidCharA *c = (struct qemu_PathIsValidCharA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsValidCharA(c->c, c->class);
}

#endif

struct qemu_PathIsValidCharW
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t class;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsValidCharW(WCHAR c, DWORD class)
{
    struct qemu_PathIsValidCharW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISVALIDCHARW);
    call.c = (uint64_t)c;
    call.class = (uint64_t)class;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathIsValidCharW to Wine headers? */
extern BOOL WINAPI PathIsValidCharW(WCHAR c, DWORD class);
void qemu_PathIsValidCharW(struct qemu_syscall *call)
{
    struct qemu_PathIsValidCharW *c = (struct qemu_PathIsValidCharW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsValidCharW(c->c, c->class);
}

#endif

