#ifndef QEMU_RICHED20_H
#define QEMU_RICHED20_H

enum riched20_calls
{
    CALL_CREATETEXTSERVICES = 0,
    CALL_REEXTENDEDREGISTERCLASS,
    CALL_RICHEDIT10ANSIWNDPROC,
    CALL_RICHEDITANSIWNDPROC,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_REExtendedRegisterClass(struct qemu_syscall *call);
void qemu_CreateTextServices(struct qemu_syscall *call);
void qemu_RichEdit10ANSIWndProc(struct qemu_syscall *call);
void qemu_RichEditANSIWndProc(struct qemu_syscall *call);

#endif

#endif
