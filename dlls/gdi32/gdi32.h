#ifndef GDI32_H
#define GDI32_H

#include <stdlib.h>

enum gdi32_calls
{
    CALL_ABORTDOC = 0,
    CALL_COPYENHMETAFILEA,
    CALL_COPYENHMETAFILEW,
    CALL_COPYMETAFILEA,
    CALL_COPYMETAFILEW,
    CALL_DELETEENHMETAFILE,
    CALL_DELETEMETAFILE,
    CALL_DPTOLP,
    CALL_ENDDOC,
    CALL_ENDPAGE,
    CALL_ENUMENHMETAFILE,
    CALL_ENUMMETAFILE,
    CALL_GDIGETSPOOLMESSAGE,
    CALL_GDIINITSPOOL,
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
    CALL_LPTODP,
    CALL_MODIFYWORLDTRANSFORM,
    CALL_OFFSETVIEWPORTORGEX,
    CALL_OFFSETWINDOWORGEX,
    CALL_PLAYENHMETAFILE,
    CALL_PLAYENHMETAFILERECORD,
    CALL_PLAYMETAFILE,
    CALL_PLAYMETAFILERECORD,
    CALL_SCALEVIEWPORTEXTEX,
    CALL_SCALEWINDOWEXTEX,
    CALL_SETABORTPROC,
    CALL_SETENHMETAFILEBITS,
    CALL_SETMAPMODE,
    CALL_SETMETAFILEBITSEX,
    CALL_SETVIEWPORTEXTEX,
    CALL_SETVIEWPORTORGEX,
    CALL_SETVIRTUALRESOLUTION,
    CALL_SETWINDOWEXTEX,
    CALL_SETWINDOWORGEX,
    CALL_SETWINMETAFILEBITS,
    CALL_SETWORLDTRANSFORM,
    CALL_STARTDOCA,
    CALL_STARTDOCW,
    CALL_STARTPAGE,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_AbortDoc(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileA(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileW(struct qemu_syscall *call);
void qemu_CopyMetaFileA(struct qemu_syscall *call);
void qemu_CopyMetaFileW(struct qemu_syscall *call);
void qemu_DeleteEnhMetaFile(struct qemu_syscall *call);
void qemu_DeleteMetaFile(struct qemu_syscall *call);
void qemu_DPtoLP(struct qemu_syscall *call);
void qemu_EndDoc(struct qemu_syscall *call);
void qemu_EndPage(struct qemu_syscall *call);
void qemu_EnumEnhMetaFile(struct qemu_syscall *call);
void qemu_EnumMetaFile(struct qemu_syscall *call);
void qemu_GdiGetSpoolMessage(struct qemu_syscall *call);
void qemu_GdiInitSpool(struct qemu_syscall *call);
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
void qemu_LPtoDP(struct qemu_syscall *call);
void qemu_ModifyWorldTransform(struct qemu_syscall *call);
void qemu_OffsetViewportOrgEx(struct qemu_syscall *call);
void qemu_OffsetWindowOrgEx(struct qemu_syscall *call);
void qemu_PlayEnhMetaFile(struct qemu_syscall *call);
void qemu_PlayEnhMetaFileRecord(struct qemu_syscall *call);
void qemu_PlayMetaFile(struct qemu_syscall *call);
void qemu_PlayMetaFileRecord(struct qemu_syscall *call);
void qemu_ScaleViewportExtEx(struct qemu_syscall *call);
void qemu_ScaleWindowExtEx(struct qemu_syscall *call);
void qemu_SetAbortProc(struct qemu_syscall *call);
void qemu_SetEnhMetaFileBits(struct qemu_syscall *call);
void qemu_SetMapMode(struct qemu_syscall *call);
void qemu_SetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_SetViewportExtEx(struct qemu_syscall *call);
void qemu_SetViewportOrgEx(struct qemu_syscall *call);
void qemu_SetVirtualResolution(struct qemu_syscall *call);
void qemu_SetWindowExtEx(struct qemu_syscall *call);
void qemu_SetWindowOrgEx(struct qemu_syscall *call);
void qemu_SetWinMetaFileBits(struct qemu_syscall *call);
void qemu_SetWorldTransform(struct qemu_syscall *call);
void qemu_StartDocA(struct qemu_syscall *call);
void qemu_StartDocW(struct qemu_syscall *call);
void qemu_StartPage(struct qemu_syscall *call);

#endif

#endif
