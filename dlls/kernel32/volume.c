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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetVolumeInformationW
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t label;
    uint64_t label_len;
    uint64_t serial;
    uint64_t filename_len;
    uint64_t flags;
    uint64_t fsname;
    uint64_t fsname_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumeInformationW(LPCWSTR root, LPWSTR label, DWORD label_len, DWORD *serial, DWORD *filename_len, DWORD *flags, LPWSTR fsname, DWORD fsname_len)
{
    struct qemu_GetVolumeInformationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEINFORMATIONW);
    call.root = (uint64_t)root;
    call.label = (uint64_t)label;
    call.label_len = (uint64_t)label_len;
    call.serial = (uint64_t)serial;
    call.filename_len = (uint64_t)filename_len;
    call.flags = (uint64_t)flags;
    call.fsname = (uint64_t)fsname;
    call.fsname_len = (uint64_t)fsname_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumeInformationW(struct qemu_syscall *call)
{
    struct qemu_GetVolumeInformationW *c = (struct qemu_GetVolumeInformationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetVolumeInformationW(QEMU_G2H(c->root), QEMU_G2H(c->label), c->label_len, QEMU_G2H(c->serial), QEMU_G2H(c->filename_len), QEMU_G2H(c->flags), QEMU_G2H(c->fsname), c->fsname_len);
}

#endif

struct qemu_GetVolumeInformationA
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t label;
    uint64_t label_len;
    uint64_t serial;
    uint64_t filename_len;
    uint64_t flags;
    uint64_t fsname;
    uint64_t fsname_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumeInformationA(LPCSTR root, LPSTR label, DWORD label_len, DWORD *serial, DWORD *filename_len, DWORD *flags, LPSTR fsname, DWORD fsname_len)
{
    struct qemu_GetVolumeInformationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEINFORMATIONA);
    call.root = (uint64_t)root;
    call.label = (uint64_t)label;
    call.label_len = label_len;
    call.serial = (uint64_t)serial;
    call.filename_len = (uint64_t)filename_len;
    call.flags = (uint64_t)flags;
    call.fsname = (uint64_t)fsname;
    call.fsname_len = fsname_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumeInformationA(struct qemu_syscall *call)
{
    struct qemu_GetVolumeInformationA *c = (struct qemu_GetVolumeInformationA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumeInformationA(QEMU_G2H(c->root), QEMU_G2H(c->label), c->label_len, QEMU_G2H(c->serial), QEMU_G2H(c->filename_len), QEMU_G2H(c->flags), QEMU_G2H(c->fsname), c->fsname_len);
}

#endif

struct qemu_SetVolumeLabelW
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t label;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetVolumeLabelW(LPCWSTR root, LPCWSTR label)
{
    struct qemu_SetVolumeLabelW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVOLUMELABELW);
    call.root = (uint64_t)root;
    call.label = (uint64_t)label;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetVolumeLabelW(struct qemu_syscall *call)
{
    struct qemu_SetVolumeLabelW *c = (struct qemu_SetVolumeLabelW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetVolumeLabelW(QEMU_G2H(c->root), QEMU_G2H(c->label));
}

#endif

struct qemu_SetVolumeLabelA
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t volname;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetVolumeLabelA(LPCSTR root, LPCSTR volname)
{
    struct qemu_SetVolumeLabelA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVOLUMELABELA);
    call.root = (uint64_t)root;
    call.volname = (uint64_t)volname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetVolumeLabelA(struct qemu_syscall *call)
{
    struct qemu_SetVolumeLabelA *c = (struct qemu_SetVolumeLabelA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetVolumeLabelA(QEMU_G2H(c->root), QEMU_G2H(c->volname));
}

#endif

struct qemu_GetVolumeNameForVolumeMountPointA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t volume;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumeNameForVolumeMountPointA(LPCSTR path, LPSTR volume, DWORD size)
{
    struct qemu_GetVolumeNameForVolumeMountPointA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMENAMEFORVOLUMEMOUNTPOINTA);
    call.path = (uint64_t)path;
    call.volume = (uint64_t)volume;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumeNameForVolumeMountPointA(struct qemu_syscall *call)
{
    struct qemu_GetVolumeNameForVolumeMountPointA *c = (struct qemu_GetVolumeNameForVolumeMountPointA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumeNameForVolumeMountPointA(QEMU_G2H(c->path), QEMU_G2H(c->volume), c->size);
}

#endif

struct qemu_GetVolumeNameForVolumeMountPointW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t volume;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumeNameForVolumeMountPointW(LPCWSTR path, LPWSTR volume, DWORD size)
{
    struct qemu_GetVolumeNameForVolumeMountPointW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMENAMEFORVOLUMEMOUNTPOINTW);
    call.path = (uint64_t)path;
    call.volume = (uint64_t)volume;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumeNameForVolumeMountPointW(struct qemu_syscall *call)
{
    struct qemu_GetVolumeNameForVolumeMountPointW *c = (struct qemu_GetVolumeNameForVolumeMountPointW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumeNameForVolumeMountPointW(QEMU_G2H(c->path), QEMU_G2H(c->volume), c->size);
}

#endif

struct qemu_DefineDosDeviceW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t devname;
    uint64_t targetpath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DefineDosDeviceW(DWORD flags, LPCWSTR devname, LPCWSTR targetpath)
{
    struct qemu_DefineDosDeviceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFINEDOSDEVICEW);
    call.flags = (uint64_t)flags;
    call.devname = (uint64_t)devname;
    call.targetpath = (uint64_t)targetpath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefineDosDeviceW(struct qemu_syscall *call)
{
    struct qemu_DefineDosDeviceW *c = (struct qemu_DefineDosDeviceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefineDosDeviceW(c->flags, QEMU_G2H(c->devname), QEMU_G2H(c->targetpath));
}

#endif

struct qemu_DefineDosDeviceA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t devname;
    uint64_t targetpath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DefineDosDeviceA(DWORD flags, LPCSTR devname, LPCSTR targetpath)
{
    struct qemu_DefineDosDeviceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFINEDOSDEVICEA);
    call.flags = flags;
    call.devname = (uint64_t)devname;
    call.targetpath = (uint64_t)targetpath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefineDosDeviceA(struct qemu_syscall *call)
{
    struct qemu_DefineDosDeviceA *c = (struct qemu_DefineDosDeviceA *)call;
    WINE_TRACE("\n");
    c->super.iret = DefineDosDeviceA(c->flags, QEMU_G2H(c->devname), QEMU_G2H(c->targetpath));
}

#endif

struct qemu_QueryDosDeviceW
{
    struct qemu_syscall super;
    uint64_t devname;
    uint64_t target;
    uint64_t bufsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI QueryDosDeviceW(LPCWSTR devname, LPWSTR target, DWORD bufsize)
{
    struct qemu_QueryDosDeviceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYDOSDEVICEW);
    call.devname = (uint64_t)devname;
    call.target = (uint64_t)target;
    call.bufsize = (uint64_t)bufsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryDosDeviceW(struct qemu_syscall *call)
{
    struct qemu_QueryDosDeviceW *c = (struct qemu_QueryDosDeviceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryDosDeviceW(QEMU_G2H(c->devname), QEMU_G2H(c->target), c->bufsize);
}

#endif

struct qemu_QueryDosDeviceA
{
    struct qemu_syscall super;
    uint64_t devname;
    uint64_t target;
    uint64_t bufsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI QueryDosDeviceA(LPCSTR devname, LPSTR target, DWORD bufsize)
{
    struct qemu_QueryDosDeviceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYDOSDEVICEA);
    call.devname = (uint64_t)devname;
    call.target = (uint64_t)target;
    call.bufsize = bufsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryDosDeviceA(struct qemu_syscall *call)
{
    struct qemu_QueryDosDeviceA *c = (struct qemu_QueryDosDeviceA *)call;
    WINE_TRACE("\n");
    c->super.iret = QueryDosDeviceA(QEMU_G2H(c->devname), QEMU_G2H(c->target), c->bufsize);
}

#endif

struct qemu_GetLogicalDrives
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLogicalDrives(void)
{
    struct qemu_GetLogicalDrives call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGICALDRIVES);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogicalDrives(struct qemu_syscall *call)
{
    struct qemu_GetLogicalDrives *c = (struct qemu_GetLogicalDrives *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLogicalDrives();
}

#endif

struct qemu_GetLogicalDriveStringsA
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLogicalDriveStringsA(DWORD len, LPSTR buffer)
{
    struct qemu_GetLogicalDriveStringsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGICALDRIVESTRINGSA);
    call.len = len;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogicalDriveStringsA(struct qemu_syscall *call)
{
    struct qemu_GetLogicalDriveStringsA *c = (struct qemu_GetLogicalDriveStringsA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLogicalDriveStringsA(c->len, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetLogicalDriveStringsW
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLogicalDriveStringsW(DWORD len, LPWSTR buffer)
{
    struct qemu_GetLogicalDriveStringsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGICALDRIVESTRINGSW);
    call.len = len;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogicalDriveStringsW(struct qemu_syscall *call)
{
    struct qemu_GetLogicalDriveStringsW *c = (struct qemu_GetLogicalDriveStringsW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLogicalDriveStringsW(c->len, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetDriveTypeW
{
    struct qemu_syscall super;
    uint64_t root;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetDriveTypeW(LPCWSTR root)
{
    struct qemu_GetDriveTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDRIVETYPEW);
    call.root = (uint64_t)root;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDriveTypeW(struct qemu_syscall *call)
{
    struct qemu_GetDriveTypeW *c = (struct qemu_GetDriveTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDriveTypeW(QEMU_G2H(c->root));
}

#endif

struct qemu_GetDriveTypeA
{
    struct qemu_syscall super;
    uint64_t root;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetDriveTypeA(LPCSTR root)
{
    struct qemu_GetDriveTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDRIVETYPEA);
    call.root = (uint64_t)root;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDriveTypeA(struct qemu_syscall *call)
{
    struct qemu_GetDriveTypeA *c = (struct qemu_GetDriveTypeA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDriveTypeA(QEMU_G2H(c->root));
}

#endif

struct qemu_GetDiskFreeSpaceExW
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t avail;
    uint64_t total;
    uint64_t totalfree;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDiskFreeSpaceExW(LPCWSTR root, PULARGE_INTEGER avail, PULARGE_INTEGER total, PULARGE_INTEGER totalfree)
{
    struct qemu_GetDiskFreeSpaceExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISKFREESPACEEXW);
    call.root = (uint64_t)root;
    call.avail = (uint64_t)avail;
    call.total = (uint64_t)total;
    call.totalfree = (uint64_t)totalfree;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDiskFreeSpaceExW(struct qemu_syscall *call)
{
    struct qemu_GetDiskFreeSpaceExW *c = (struct qemu_GetDiskFreeSpaceExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDiskFreeSpaceExW(QEMU_G2H(c->root), QEMU_G2H(c->avail), QEMU_G2H(c->total), QEMU_G2H(c->totalfree));
}

#endif

struct qemu_GetDiskFreeSpaceExA
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t avail;
    uint64_t total;
    uint64_t totalfree;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDiskFreeSpaceExA(LPCSTR root, PULARGE_INTEGER avail, PULARGE_INTEGER total, PULARGE_INTEGER totalfree)
{
    struct qemu_GetDiskFreeSpaceExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISKFREESPACEEXA);
    call.root = (uint64_t)root;
    call.avail = (uint64_t)avail;
    call.total = (uint64_t)total;
    call.totalfree = (uint64_t)totalfree;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDiskFreeSpaceExA(struct qemu_syscall *call)
{
    struct qemu_GetDiskFreeSpaceExA *c = (struct qemu_GetDiskFreeSpaceExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDiskFreeSpaceExA(QEMU_G2H(c->root), QEMU_G2H(c->avail), QEMU_G2H(c->total), QEMU_G2H(c->totalfree));
}

#endif

struct qemu_GetDiskFreeSpaceW
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t cluster_sectors;
    uint64_t sector_bytes;
    uint64_t free_clusters;
    uint64_t total_clusters;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDiskFreeSpaceW(LPCWSTR root, LPDWORD cluster_sectors, LPDWORD sector_bytes, LPDWORD free_clusters, LPDWORD total_clusters)
{
    struct qemu_GetDiskFreeSpaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISKFREESPACEW);
    call.root = (uint64_t)root;
    call.cluster_sectors = (uint64_t)cluster_sectors;
    call.sector_bytes = (uint64_t)sector_bytes;
    call.free_clusters = (uint64_t)free_clusters;
    call.total_clusters = (uint64_t)total_clusters;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDiskFreeSpaceW(struct qemu_syscall *call)
{
    struct qemu_GetDiskFreeSpaceW *c = (struct qemu_GetDiskFreeSpaceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDiskFreeSpaceW(QEMU_G2H(c->root), QEMU_G2H(c->cluster_sectors), QEMU_G2H(c->sector_bytes), QEMU_G2H(c->free_clusters), QEMU_G2H(c->total_clusters));
}

#endif

struct qemu_GetDiskFreeSpaceA
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t cluster_sectors;
    uint64_t sector_bytes;
    uint64_t free_clusters;
    uint64_t total_clusters;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDiskFreeSpaceA(LPCSTR root, LPDWORD cluster_sectors, LPDWORD sector_bytes, LPDWORD free_clusters, LPDWORD total_clusters)
{
    struct qemu_GetDiskFreeSpaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISKFREESPACEA);
    call.root = (uint64_t)root;
    call.cluster_sectors = (uint64_t)cluster_sectors;
    call.sector_bytes = (uint64_t)sector_bytes;
    call.free_clusters = (uint64_t)free_clusters;
    call.total_clusters = (uint64_t)total_clusters;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDiskFreeSpaceA(struct qemu_syscall *call)
{
    struct qemu_GetDiskFreeSpaceA *c = (struct qemu_GetDiskFreeSpaceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDiskFreeSpaceA(QEMU_G2H(c->root), QEMU_G2H(c->cluster_sectors), QEMU_G2H(c->sector_bytes), QEMU_G2H(c->free_clusters), QEMU_G2H(c->total_clusters));
}

#endif

struct qemu_GetVolumePathNameA
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t volumepathname;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumePathNameA(LPCSTR filename, LPSTR volumepathname, DWORD buflen)
{
    struct qemu_GetVolumePathNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEPATHNAMEA);
    call.filename = (uint64_t)filename;
    call.volumepathname = (uint64_t)volumepathname;
    call.buflen = buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumePathNameA(struct qemu_syscall *call)
{
    struct qemu_GetVolumePathNameA *c = (struct qemu_GetVolumePathNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumePathNameA(QEMU_G2H(c->filename), QEMU_G2H(c->volumepathname), c->buflen);
}

#endif

struct qemu_GetVolumePathNameW
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t volumepathname;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumePathNameW(LPCWSTR filename, LPWSTR volumepathname, DWORD buflen)
{
    struct qemu_GetVolumePathNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEPATHNAMEW);
    call.filename = (uint64_t)filename;
    call.volumepathname = (uint64_t)volumepathname;
    call.buflen = buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumePathNameW(struct qemu_syscall *call)
{
    struct qemu_GetVolumePathNameW *c = (struct qemu_GetVolumePathNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumePathNameW(QEMU_G2H(c->filename), QEMU_G2H(c->volumepathname), c->buflen);
}

#endif

struct qemu_GetVolumePathNamesForVolumeNameA
{
    struct qemu_syscall super;
    uint64_t volumename;
    uint64_t volumepathname;
    uint64_t buflen;
    uint64_t returnlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumePathNamesForVolumeNameA(LPCSTR volumename, LPSTR volumepathname, DWORD buflen, PDWORD returnlen)
{
    struct qemu_GetVolumePathNamesForVolumeNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEPATHNAMESFORVOLUMENAMEA);
    call.volumename = (uint64_t)volumename;
    call.volumepathname = (uint64_t)volumepathname;
    call.buflen = buflen;
    call.returnlen = (uint64_t)returnlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumePathNamesForVolumeNameA(struct qemu_syscall *call)
{
    struct qemu_GetVolumePathNamesForVolumeNameA *c = (struct qemu_GetVolumePathNamesForVolumeNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumePathNamesForVolumeNameA(QEMU_G2H(c->volumename), QEMU_G2H(c->volumepathname), c->buflen, QEMU_G2H(c->returnlen));
}

#endif

struct qemu_GetVolumePathNamesForVolumeNameW
{
    struct qemu_syscall super;
    uint64_t volumename;
    uint64_t volumepathname;
    uint64_t buflen;
    uint64_t returnlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumePathNamesForVolumeNameW(LPCWSTR volumename, LPWSTR volumepathname, DWORD buflen, PDWORD returnlen)
{
    struct qemu_GetVolumePathNamesForVolumeNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEPATHNAMESFORVOLUMENAMEW);
    call.volumename = (uint64_t)volumename;
    call.volumepathname = (uint64_t)volumepathname;
    call.buflen = buflen;
    call.returnlen = (uint64_t)returnlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumePathNamesForVolumeNameW(struct qemu_syscall *call)
{
    struct qemu_GetVolumePathNamesForVolumeNameW *c = (struct qemu_GetVolumePathNamesForVolumeNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetVolumePathNamesForVolumeNameW(QEMU_G2H(c->volumename), QEMU_G2H(c->volumepathname), c->buflen, QEMU_G2H(c->returnlen));
}

#endif

struct qemu_FindFirstVolumeA
{
    struct qemu_syscall super;
    uint64_t volume;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstVolumeA(LPSTR volume, DWORD len)
{
    struct qemu_FindFirstVolumeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTVOLUMEA);
    call.volume = (uint64_t)volume;
    call.len = len;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_FindFirstVolumeA(struct qemu_syscall *call)
{
    struct qemu_FindFirstVolumeA *c = (struct qemu_FindFirstVolumeA *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)FindFirstVolumeA(QEMU_G2H(c->volume), c->len);
}

#endif

struct qemu_FindFirstVolumeW
{
    struct qemu_syscall super;
    uint64_t volume;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstVolumeW(LPWSTR volume, DWORD len)
{
    struct qemu_FindFirstVolumeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTVOLUMEW);
    call.volume = (uint64_t)volume;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_FindFirstVolumeW(struct qemu_syscall *call)
{
    struct qemu_FindFirstVolumeW *c = (struct qemu_FindFirstVolumeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindFirstVolumeW(QEMU_G2H(c->volume), c->len);
}

#endif

struct qemu_FindNextVolumeA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t volume;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextVolumeA(HANDLE handle, LPSTR volume, DWORD len)
{
    struct qemu_FindNextVolumeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTVOLUMEA);
    call.handle = (uint64_t)handle;
    call.volume = (uint64_t)volume;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextVolumeA(struct qemu_syscall *call)
{
    struct qemu_FindNextVolumeA *c = (struct qemu_FindNextVolumeA *)call;
    WINE_TRACE("\n");
    c->super.iret = FindNextVolumeA((HANDLE)c->handle, QEMU_G2H(c->volume), c->len);
}

#endif

struct qemu_FindNextVolumeW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t volume;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextVolumeW(HANDLE handle, LPWSTR volume, DWORD len)
{
    struct qemu_FindNextVolumeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTVOLUMEW);
    call.handle = (uint64_t)handle;
    call.volume = (uint64_t)volume;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextVolumeW(struct qemu_syscall *call)
{
    struct qemu_FindNextVolumeW *c = (struct qemu_FindNextVolumeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextVolumeW(QEMU_G2H(c->handle), QEMU_G2H(c->volume), c->len);
}

#endif

struct qemu_FindVolumeClose
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindVolumeClose(HANDLE handle)
{
    struct qemu_FindVolumeClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDVOLUMECLOSE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindVolumeClose(struct qemu_syscall *call)
{
    struct qemu_FindVolumeClose *c = (struct qemu_FindVolumeClose *)call;
    WINE_TRACE("\n");
    c->super.iret = FindVolumeClose((HANDLE)c->handle);
}

#endif

struct qemu_FindFirstVolumeMountPointA
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t mount_point;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstVolumeMountPointA(LPCSTR root, LPSTR mount_point, DWORD len)
{
    struct qemu_FindFirstVolumeMountPointA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTVOLUMEMOUNTPOINTA);
    call.root = (uint64_t)root;
    call.mount_point = (uint64_t)mount_point;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_FindFirstVolumeMountPointA(struct qemu_syscall *call)
{
    struct qemu_FindFirstVolumeMountPointA *c = (struct qemu_FindFirstVolumeMountPointA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindFirstVolumeMountPointA(QEMU_G2H(c->root), QEMU_G2H(c->mount_point), c->len);
}

#endif

struct qemu_FindFirstVolumeMountPointW
{
    struct qemu_syscall super;
    uint64_t root;
    uint64_t mount_point;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstVolumeMountPointW(LPCWSTR root, LPWSTR mount_point, DWORD len)
{
    struct qemu_FindFirstVolumeMountPointW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTVOLUMEMOUNTPOINTW);
    call.root = (uint64_t)root;
    call.mount_point = (uint64_t)mount_point;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_FindFirstVolumeMountPointW(struct qemu_syscall *call)
{
    struct qemu_FindFirstVolumeMountPointW *c = (struct qemu_FindFirstVolumeMountPointW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindFirstVolumeMountPointW(QEMU_G2H(c->root), QEMU_G2H(c->mount_point), c->len);
}

#endif

struct qemu_FindVolumeMountPointClose
{
    struct qemu_syscall super;
    uint64_t h;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindVolumeMountPointClose(HANDLE h)
{
    struct qemu_FindVolumeMountPointClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDVOLUMEMOUNTPOINTCLOSE);
    call.h = (uint64_t)h;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindVolumeMountPointClose(struct qemu_syscall *call)
{
    struct qemu_FindVolumeMountPointClose *c = (struct qemu_FindVolumeMountPointClose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindVolumeMountPointClose(QEMU_G2H(c->h));
}

#endif

struct qemu_DeleteVolumeMountPointA
{
    struct qemu_syscall super;
    uint64_t mountpoint;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteVolumeMountPointA(LPCSTR mountpoint)
{
    struct qemu_DeleteVolumeMountPointA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEVOLUMEMOUNTPOINTA);
    call.mountpoint = (uint64_t)mountpoint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteVolumeMountPointA(struct qemu_syscall *call)
{
    struct qemu_DeleteVolumeMountPointA *c = (struct qemu_DeleteVolumeMountPointA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteVolumeMountPointA(QEMU_G2H(c->mountpoint));
}

#endif

struct qemu_DeleteVolumeMountPointW
{
    struct qemu_syscall super;
    uint64_t mountpoint;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteVolumeMountPointW(LPCWSTR mountpoint)
{
    struct qemu_DeleteVolumeMountPointW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEVOLUMEMOUNTPOINTW);
    call.mountpoint = (uint64_t)mountpoint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteVolumeMountPointW(struct qemu_syscall *call)
{
    struct qemu_DeleteVolumeMountPointW *c = (struct qemu_DeleteVolumeMountPointW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteVolumeMountPointW(QEMU_G2H(c->mountpoint));
}

#endif

struct qemu_SetVolumeMountPointA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t volume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetVolumeMountPointA(LPCSTR path, LPCSTR volume)
{
    struct qemu_SetVolumeMountPointA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVOLUMEMOUNTPOINTA);
    call.path = (uint64_t)path;
    call.volume = (uint64_t)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetVolumeMountPointA(struct qemu_syscall *call)
{
    struct qemu_SetVolumeMountPointA *c = (struct qemu_SetVolumeMountPointA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetVolumeMountPointA(QEMU_G2H(c->path), QEMU_G2H(c->volume));
}

#endif

struct qemu_SetVolumeMountPointW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t volume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetVolumeMountPointW(LPCWSTR path, LPCWSTR volume)
{
    struct qemu_SetVolumeMountPointW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVOLUMEMOUNTPOINTW);
    call.path = (uint64_t)path;
    call.volume = (uint64_t)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetVolumeMountPointW(struct qemu_syscall *call)
{
    struct qemu_SetVolumeMountPointW *c = (struct qemu_SetVolumeMountPointW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetVolumeMountPointW(QEMU_G2H(c->path), QEMU_G2H(c->volume));
}

#endif

struct qemu_GetVolumeInformationByHandleW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t volnamebuf;
    uint64_t volnamesize;
    uint64_t volserial;
    uint64_t maxlength;
    uint64_t flags;
    uint64_t fsnamebuf;
    uint64_t fsnamesize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVolumeInformationByHandleW(HANDLE handle, WCHAR *volnamebuf, DWORD volnamesize, DWORD *volserial, DWORD *maxlength, DWORD *flags, WCHAR *fsnamebuf, DWORD fsnamesize)
{
    struct qemu_GetVolumeInformationByHandleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVOLUMEINFORMATIONBYHANDLEW);
    call.handle = (uint64_t)handle;
    call.volnamebuf = (uint64_t)volnamebuf;
    call.volnamesize = (uint64_t)volnamesize;
    call.volserial = (uint64_t)volserial;
    call.maxlength = (uint64_t)maxlength;
    call.flags = (uint64_t)flags;
    call.fsnamebuf = (uint64_t)fsnamebuf;
    call.fsnamesize = (uint64_t)fsnamesize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVolumeInformationByHandleW(struct qemu_syscall *call)
{
    struct qemu_GetVolumeInformationByHandleW *c = (struct qemu_GetVolumeInformationByHandleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetVolumeInformationByHandleW(QEMU_G2H(c->handle), QEMU_G2H(c->volnamebuf), c->volnamesize, QEMU_G2H(c->volserial), QEMU_G2H(c->maxlength), QEMU_G2H(c->flags), QEMU_G2H(c->fsnamebuf), c->fsnamesize);
}

#endif

