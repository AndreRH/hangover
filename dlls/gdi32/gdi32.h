#ifndef GDI32_H
#define GDI32_H

#include <stdlib.h>

enum gdi32_calls
{
    CALL_COPYENHMETAFILEA = 0,
    CALL_COPYENHMETAFILEW,
    CALL_COPYMETAFILEA,
    CALL_COPYMETAFILEW,
    CALL_DELETEENHMETAFILE,
    CALL_DELETEMETAFILE,
    CALL_ENUMENHMETAFILE,
    CALL_ENUMMETAFILE,
    CALL_GETDEVICECAPS,
    CALL_GETENHMETAFILEA,
    CALL_GETENHMETAFILEBITS,
    CALL_GETENHMETAFILEDESCRIPTIONA,
    CALL_GETENHMETAFILEDESCRIPTIONW,
    CALL_GETENHMETAFILEHEADER,
    CALL_GETENHMETAFILEPALETTEENTRIES,
    CALL_GETENHMETAFILEW,
    CALL_GETMETAFILEA,
    CALL_GETMETAFILEBITSEX,
    CALL_GETMETAFILEW,
    CALL_GETWINMETAFILEBITS,
    CALL_PLAYENHMETAFILE,
    CALL_PLAYENHMETAFILERECORD,
    CALL_PLAYMETAFILE,
    CALL_PLAYMETAFILERECORD,
    CALL_SETENHMETAFILEBITS,
    CALL_SETMETAFILEBITSEX,
    CALL_SETWINMETAFILEBITS,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_CopyEnhMetaFileA(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileW(struct qemu_syscall *call);
void qemu_CopyMetaFileA(struct qemu_syscall *call);
void qemu_CopyMetaFileW(struct qemu_syscall *call);
void qemu_DeleteEnhMetaFile(struct qemu_syscall *call);
void qemu_DeleteMetaFile(struct qemu_syscall *call);
void qemu_EnumEnhMetaFile(struct qemu_syscall *call);
void qemu_EnumMetaFile(struct qemu_syscall *call);
void qemu_GetDeviceCaps(struct qemu_syscall *call);
void qemu_GetEnhMetaFileA(struct qemu_syscall *call);
void qemu_GetEnhMetaFileBits(struct qemu_syscall *call);
void qemu_GetEnhMetaFileDescriptionA(struct qemu_syscall *call);
void qemu_GetEnhMetaFileDescriptionW(struct qemu_syscall *call);
void qemu_GetEnhMetaFileHeader(struct qemu_syscall *call);
void qemu_GetEnhMetaFilePaletteEntries(struct qemu_syscall *call);
void qemu_GetEnhMetaFileW(struct qemu_syscall *call);
void qemu_GetMetaFileA(struct qemu_syscall *call);
void qemu_GetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_GetMetaFileW(struct qemu_syscall *call);
void qemu_GetWinMetaFileBits(struct qemu_syscall *call);
void qemu_PlayEnhMetaFile(struct qemu_syscall *call);
void qemu_PlayEnhMetaFileRecord(struct qemu_syscall *call);
void qemu_PlayMetaFile(struct qemu_syscall *call);
void qemu_PlayMetaFileRecord(struct qemu_syscall *call);
void qemu_SetEnhMetaFileBits(struct qemu_syscall *call);
void qemu_SetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_SetWinMetaFileBits(struct qemu_syscall *call);

#endif

#endif
