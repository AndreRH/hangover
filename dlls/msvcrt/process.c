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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu__cwait
{
    struct qemu_syscall super;
    uint64_t status;
    uint64_t pid;
    uint64_t action;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _cwait(int *status, intptr_t pid, int action)
{
    struct qemu__cwait call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CWAIT);
    call.status = (uint64_t)status;
    call.pid = (uint64_t)pid;
    call.action = (uint64_t)action;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__cwait(struct qemu_syscall *call)
{
    struct qemu__cwait *c = (struct qemu__cwait *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__cwait(QEMU_G2H(c->status), c->pid, c->action);
}

#endif

struct qemu__wexecv
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _wexecv(const WCHAR* name, const WCHAR* const* argv)
{
    struct qemu__wexecv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WEXECV);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wexecv(struct qemu_syscall *call)
{
    struct qemu__wexecv *c = (struct qemu__wexecv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wexecv(QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__execv
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _execv(const char* name, const char* const* argv)
{
    struct qemu__execv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EXECV);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__execv(struct qemu_syscall *call)
{
    struct qemu__execv *c = (struct qemu__execv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__execv(QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__wexecve
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _wexecve(const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv)
{
    struct qemu__wexecve call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WEXECVE);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wexecve(struct qemu_syscall *call)
{
    struct qemu__wexecve *c = (struct qemu__wexecve *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wexecve(QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__execve
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__execve(const char* name, const char* const* argv, const char* const* envv)
{
    struct qemu__execve call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EXECVE);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__execve(struct qemu_syscall *call)
{
    struct qemu__execve *c = (struct qemu__execve *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__execve(QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__wexecvpe
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _wexecvpe(const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv)
{
    struct qemu__wexecvpe call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WEXECVPE);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wexecvpe(struct qemu_syscall *call)
{
    struct qemu__wexecvpe *c = (struct qemu__wexecvpe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wexecvpe(QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__execvpe
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _execvpe(const char* name, const char* const* argv, const char* const* envv)
{
    struct qemu__execvpe call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EXECVPE);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__execvpe(struct qemu_syscall *call)
{
    struct qemu__execvpe *c = (struct qemu__execvpe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__execvpe(QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__wexecvp
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _wexecvp(const WCHAR* name, const WCHAR* const* argv)
{
    struct qemu__wexecvp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WEXECVP);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wexecvp(struct qemu_syscall *call)
{
    struct qemu__wexecvp *c = (struct qemu__wexecvp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wexecvp(QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__execvp
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _execvp(const char* name, const char* const* argv)
{
    struct qemu__execvp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EXECVP);
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__execvp(struct qemu_syscall *call)
{
    struct qemu__execvp *c = (struct qemu__execvp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__execvp(QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__spawnve
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__spawnve(int flags, const char* name, const char* const* argv, const char* const* envv)
{
    struct qemu__spawnve call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPAWNVE);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__spawnve(struct qemu_syscall *call)
{
    struct qemu__spawnve *c = (struct qemu__spawnve *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__spawnve(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__wspawnve
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wspawnve(int flags, const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv)
{
    struct qemu__wspawnve call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSPAWNVE);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wspawnve(struct qemu_syscall *call)
{
    struct qemu__wspawnve *c = (struct qemu__wspawnve *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wspawnve(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__spawnv
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__spawnv(int flags, const char* name, const char* const* argv)
{
    struct qemu__spawnv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPAWNV);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__spawnv(struct qemu_syscall *call)
{
    struct qemu__spawnv *c = (struct qemu__spawnv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__spawnv(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__wspawnv
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wspawnv(int flags, const WCHAR* name, const WCHAR* const* argv)
{
    struct qemu__wspawnv call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSPAWNV);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wspawnv(struct qemu_syscall *call)
{
    struct qemu__wspawnv *c = (struct qemu__wspawnv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wspawnv(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__spawnvpe
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__spawnvpe(int flags, const char* name, const char* const* argv, const char* const* envv)
{
    struct qemu__spawnvpe call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPAWNVPE);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__spawnvpe(struct qemu_syscall *call)
{
    struct qemu__spawnvpe *c = (struct qemu__spawnvpe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__spawnvpe(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__wspawnvpe
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
    uint64_t envv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wspawnvpe(int flags, const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv)
{
    struct qemu__wspawnvpe call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSPAWNVPE);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;
    call.envv = (uint64_t)envv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wspawnvpe(struct qemu_syscall *call)
{
    struct qemu__wspawnvpe *c = (struct qemu__wspawnvpe *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wspawnvpe(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv), QEMU_G2H(c->envv));
}

#endif

struct qemu__spawnvp
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__spawnvp(int flags, const char* name, const char* const* argv)
{
    struct qemu__spawnvp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPAWNVP);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__spawnvp(struct qemu_syscall *call)
{
    struct qemu__spawnvp *c = (struct qemu__spawnvp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__spawnvp(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__wspawnvp
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t name;
    uint64_t argv;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__wspawnvp(int flags, const WCHAR* name, const WCHAR* const* argv)
{
    struct qemu__wspawnvp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSPAWNVP);
    call.flags = (uint64_t)flags;
    call.name = (uint64_t)name;
    call.argv = (uint64_t)argv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wspawnvp(struct qemu_syscall *call)
{
    struct qemu__wspawnvp *c = (struct qemu__wspawnvp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wspawnvp(c->flags, QEMU_G2H(c->name), QEMU_G2H(c->argv));
}

#endif

struct qemu__wpopen
{
    struct qemu_syscall super;
    uint64_t command;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

FILE* CDECL MSVCRT__wpopen(const WCHAR* command, const WCHAR* mode)
{
    struct qemu__wpopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WPOPEN);
    call.command = (uint64_t)command;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return (FILE *)call.super.iret;
}

#else

void qemu__wpopen(struct qemu_syscall *call)
{
    struct qemu__wpopen *c = (struct qemu__wpopen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wpopen(QEMU_G2H(c->command), QEMU_G2H(c->mode)));
}

#endif

struct qemu__popen
{
    struct qemu_syscall super;
    uint64_t command;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

FILE* CDECL MSVCRT__popen(const char* command, const char* mode)
{
    struct qemu__popen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__POPEN);
    call.command = (uint64_t)command;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return (FILE *)call.super.iret;
}

#else

void qemu__popen(struct qemu_syscall *call)
{
    struct qemu__popen *c = (struct qemu__popen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__popen(QEMU_G2H(c->command), QEMU_G2H(c->mode)));
}

#endif

struct qemu__pclose
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__pclose(FILE* file)
{
    struct qemu__pclose call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PCLOSE);
    call.file = (uint64_t)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__pclose(struct qemu_syscall *call)
{
    struct qemu__pclose *c = (struct qemu__pclose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__pclose(QEMU_G2H(c->file));
}

#endif

struct qemu__wsystem
{
    struct qemu_syscall super;
    uint64_t cmd;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wsystem(const WCHAR* cmd)
{
    struct qemu__wsystem call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSYSTEM);
    call.cmd = (uint64_t)cmd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wsystem(struct qemu_syscall *call)
{
    struct qemu__wsystem *c = (struct qemu__wsystem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wsystem(QEMU_G2H(c->cmd));
}

#endif

struct qemu_system
{
    struct qemu_syscall super;
    uint64_t cmd;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_system(const char* cmd)
{
    struct qemu_system call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEM);
    call.cmd = (uint64_t)cmd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_system(struct qemu_syscall *call)
{
    struct qemu_system *c = (struct qemu_system *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_system(QEMU_G2H(c->cmd));
}

#endif

struct qemu__loaddll
{
    struct qemu_syscall super;
    uint64_t dllname;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL _loaddll(const char* dllname)
{
    struct qemu__loaddll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOADDLL);
    call.dllname = (uint64_t)dllname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__loaddll(struct qemu_syscall *call)
{
    struct qemu__loaddll *c = (struct qemu__loaddll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__loaddll(QEMU_G2H(c->dllname));
}

#endif

struct qemu__unloaddll
{
    struct qemu_syscall super;
    uint64_t dll;
};

#ifdef QEMU_DLL_GUEST

int CDECL _unloaddll(intptr_t dll)
{
    struct qemu__unloaddll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLOADDLL);
    call.dll = (uint64_t)dll;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__unloaddll(struct qemu_syscall *call)
{
    struct qemu__unloaddll *c = (struct qemu__unloaddll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__unloaddll(c->dll);
}

#endif

struct qemu__getdllprocaddr
{
    struct qemu_syscall super;
    uint64_t dll;
    uint64_t name;
    uint64_t ordinal;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT__getdllprocaddr(intptr_t dll, const char *name, int ordinal)
{
    struct qemu__getdllprocaddr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETDLLPROCADDR);
    call.dll = (uint64_t)dll;
    call.name = (uint64_t)name;
    call.ordinal = (uint64_t)ordinal;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu__getdllprocaddr(struct qemu_syscall *call)
{
    struct qemu__getdllprocaddr *c = (struct qemu__getdllprocaddr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__getdllprocaddr(c->dll, QEMU_G2H(c->name), c->ordinal));
}

#endif

struct qemu__getpid
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL _getpid(void)
{
    struct qemu__getpid call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETPID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getpid(struct qemu_syscall *call)
{
    struct qemu__getpid *c = (struct qemu__getpid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getpid();
}

#endif

struct qemu__crtTerminateProcess
{
    struct qemu_syscall super;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCR110__crtTerminateProcess(UINT exit_code)
{
    struct qemu__crtTerminateProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CRTTERMINATEPROCESS);
    call.exit_code = (uint64_t)exit_code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__crtTerminateProcess(struct qemu_syscall *call)
{
    struct qemu__crtTerminateProcess *c = (struct qemu__crtTerminateProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__crtTerminateProcess(c->exit_code);
}

#endif

