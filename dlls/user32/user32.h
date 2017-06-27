#ifndef USER32_H
#define USER32_H

#include <stdlib.h>

enum user32_calls
{
    CALL_ADDCLIPBOARDFORMATLISTENER = 0,
    CALL_CHANGECLIPBOARDCHAIN,
    CALL_CLOSECLIPBOARD,
    CALL_COUNTCLIPBOARDFORMATS,
    CALL_CREATECARET,
    CALL_DESTROYCARET,
    CALL_EMPTYCLIPBOARD,
    CALL_ENUMCLIPBOARDFORMATS,
    CALL_GETCARETBLINKTIME,
    CALL_GETCARETPOS,
    CALL_GETCLASSINFOA,
    CALL_GETCLASSINFOEXA,
    CALL_GETCLASSINFOEXW,
    CALL_GETCLASSINFOW,
    CALL_GETCLASSLONGA,
    CALL_GETCLASSLONGPTRA,
    CALL_GETCLASSLONGPTRW,
    CALL_GETCLASSLONGW,
    CALL_GETCLASSNAMEA,
    CALL_GETCLASSNAMEW,
    CALL_GETCLASSWORD,
    CALL_GETCLIPBOARDDATA,
    CALL_GETCLIPBOARDFORMATNAMEA,
    CALL_GETCLIPBOARDFORMATNAMEW,
    CALL_GETCLIPBOARDOWNER,
    CALL_GETCLIPBOARDSEQUENCENUMBER,
    CALL_GETCLIPBOARDVIEWER,
    CALL_GETOPENCLIPBOARDWINDOW,
    CALL_GETPRIORITYCLIPBOARDFORMAT,
    CALL_GETUPDATEDCLIPBOARDFORMATS,
    CALL_HIDECARET,
    CALL_ISCLIPBOARDFORMATAVAILABLE,
    CALL_OEMTOCHARA,
    CALL_OPENCLIPBOARD,
    CALL_REALGETWINDOWCLASSA,
    CALL_REALGETWINDOWCLASSW,
    CALL_REGISTERCLASSA,
    CALL_REGISTERCLASSEXA,
    CALL_REGISTERCLASSEXW,
    CALL_REGISTERCLASSW,
    CALL_REGISTERCLIPBOARDFORMATA,
    CALL_REGISTERCLIPBOARDFORMATW,
    CALL_REMOVECLIPBOARDFORMATLISTENER,
    CALL_SETCARETBLINKTIME,
    CALL_SETCARETPOS,
    CALL_SETCLASSLONGA,
    CALL_SETCLASSLONGPTRA,
    CALL_SETCLASSLONGPTRW,
    CALL_SETCLASSLONGW,
    CALL_SETCLASSWORD,
    CALL_SETCLIPBOARDDATA,
    CALL_SETCLIPBOARDVIEWER,
    CALL_SHOWCARET,
    CALL_UNREGISTERCLASSA,
    CALL_UNREGISTERCLASSW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_AddClipboardFormatListener(struct qemu_syscall *call);
void qemu_ChangeClipboardChain(struct qemu_syscall *call);
void qemu_CloseClipboard(struct qemu_syscall *call);
void qemu_CountClipboardFormats(struct qemu_syscall *call);
void qemu_CreateCaret(struct qemu_syscall *call);
void qemu_DestroyCaret(struct qemu_syscall *call);
void qemu_EmptyClipboard(struct qemu_syscall *call);
void qemu_EnumClipboardFormats(struct qemu_syscall *call);
void qemu_GetCaretBlinkTime(struct qemu_syscall *call);
void qemu_GetCaretPos(struct qemu_syscall *call);
void qemu_GetClassInfoA(struct qemu_syscall *call);
void qemu_GetClassInfoExA(struct qemu_syscall *call);
void qemu_GetClassInfoExW(struct qemu_syscall *call);
void qemu_GetClassInfoW(struct qemu_syscall *call);
void qemu_GetClassLongA(struct qemu_syscall *call);
void qemu_GetClassLongPtrA(struct qemu_syscall *call);
void qemu_GetClassLongPtrW(struct qemu_syscall *call);
void qemu_GetClassLongW(struct qemu_syscall *call);
void qemu_GetClassNameA(struct qemu_syscall *call);
void qemu_GetClassNameW(struct qemu_syscall *call);
void qemu_GetClassWord(struct qemu_syscall *call);
void qemu_GetClipboardData(struct qemu_syscall *call);
void qemu_GetClipboardFormatNameA(struct qemu_syscall *call);
void qemu_GetClipboardFormatNameW(struct qemu_syscall *call);
void qemu_GetClipboardOwner(struct qemu_syscall *call);
void qemu_GetClipboardSequenceNumber(struct qemu_syscall *call);
void qemu_GetClipboardViewer(struct qemu_syscall *call);
void qemu_GetOpenClipboardWindow(struct qemu_syscall *call);
void qemu_GetPriorityClipboardFormat(struct qemu_syscall *call);
void qemu_GetUpdatedClipboardFormats(struct qemu_syscall *call);
void qemu_HideCaret(struct qemu_syscall *call);
void qemu_IsClipboardFormatAvailable(struct qemu_syscall *call);
void qemu_OemToCharA(struct qemu_syscall *call);
void qemu_OpenClipboard(struct qemu_syscall *call);
void qemu_RealGetWindowClassA(struct qemu_syscall *call);
void qemu_RealGetWindowClassW(struct qemu_syscall *call);
void qemu_RegisterClassA(struct qemu_syscall *call);
void qemu_RegisterClassExA(struct qemu_syscall *call);
void qemu_RegisterClassExW(struct qemu_syscall *call);
void qemu_RegisterClassW(struct qemu_syscall *call);
void qemu_RegisterClipboardFormatA(struct qemu_syscall *call);
void qemu_RegisterClipboardFormatW(struct qemu_syscall *call);
void qemu_RemoveClipboardFormatListener(struct qemu_syscall *call);
void qemu_SetCaretBlinkTime(struct qemu_syscall *call);
void qemu_SetCaretPos(struct qemu_syscall *call);
void qemu_SetClassLongA(struct qemu_syscall *call);
void qemu_SetClassLongPtrA(struct qemu_syscall *call);
void qemu_SetClassLongPtrW(struct qemu_syscall *call);
void qemu_SetClassLongW(struct qemu_syscall *call);
void qemu_SetClassWord(struct qemu_syscall *call);
void qemu_SetClipboardData(struct qemu_syscall *call);
void qemu_SetClipboardViewer(struct qemu_syscall *call);
void qemu_ShowCaret(struct qemu_syscall *call);
void qemu_UnregisterClassA(struct qemu_syscall *call);
void qemu_UnregisterClassW(struct qemu_syscall *call);

#endif

#endif
