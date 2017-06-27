#ifndef USER32_H
#define USER32_H

#include <stdlib.h>

enum user32_calls
{
    CALL_CREATECARET = 0,
    CALL_DESTROYCARET,
    CALL_GETCARETBLINKTIME,
    CALL_GETCARETPOS,
    CALL_HIDECARET,
    CALL_OEMTOCHARA,
    CALL_SETCARETBLINKTIME,
    CALL_SETCARETPOS,
    CALL_SHOWCARET,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_CreateCaret(struct qemu_syscall *call);
void qemu_DestroyCaret(struct qemu_syscall *call);
void qemu_GetCaretBlinkTime(struct qemu_syscall *call);
void qemu_GetCaretPos(struct qemu_syscall *call);
void qemu_HideCaret(struct qemu_syscall *call);
void qemu_OemToCharA(struct qemu_syscall *call);
void qemu_SetCaretBlinkTime(struct qemu_syscall *call);
void qemu_SetCaretPos(struct qemu_syscall *call);
void qemu_ShowCaret(struct qemu_syscall *call);

#endif

#endif
