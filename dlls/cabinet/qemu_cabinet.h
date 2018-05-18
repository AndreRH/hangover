/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#ifndef QEMU_CABINET_H
#define QEMU_CABINET_H

enum cabinet_calls
{
    CALL_DLLGETVERSION = 0,
    CALL_EXTRACT,
    CALL_FCIADDFILE,
    CALL_FCICREATE,
    CALL_FCIDESTROY,
    CALL_FCIFLUSHCABINET,
    CALL_FCIFLUSHFOLDER,
    CALL_FDICOPY,
    CALL_FDICREATE,
    CALL_FDIDESTROY,
    CALL_FDIISCABINET,
    CALL_FDITRUNCATECABINET,
};

struct FILELIST
{
    LPSTR FileName;
    struct FILELIST *next;
    BOOL DoExtract;
};

typedef struct
{
    INT FileSize;
    ERF Error;
    struct FILELIST *FileList;
    INT FileCount;
    INT Operation;
    CHAR Destination[MAX_PATH];
    CHAR CurrentFile[MAX_PATH];
    CHAR Reserved[MAX_PATH];
    struct FILELIST *FilterList;
} SESSION;

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_FCIAddFile(struct qemu_syscall *call);
void qemu_FCICreate(struct qemu_syscall *call);
void qemu_FCIDestroy(struct qemu_syscall *call);
void qemu_FCIFlushCabinet(struct qemu_syscall *call);
void qemu_FCIFlushFolder(struct qemu_syscall *call);
void qemu_FDICopy(struct qemu_syscall *call);
void qemu_FDICreate(struct qemu_syscall *call);
void qemu_FDIDestroy(struct qemu_syscall *call);
void qemu_FDIIsCabinet(struct qemu_syscall *call);
void qemu_FDITruncateCabinet(struct qemu_syscall *call);

#endif

#endif
