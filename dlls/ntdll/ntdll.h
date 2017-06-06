#ifndef NTDLL_H
#define NTDLL_H

enum ntdll_calls
{
    CALL_RTLADDFUNCTIONTABLE = 0,
    CALL_RTLDELETECRITICALSECTION,
    CALL_RTLENTERCRITICALSECTION,
    CALL_RTLINITIALIZECRITICALSECTIONEX,
    CALL_RTLLEAVECRITICALSECTION,
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu_RtlAddFunctionTable(struct qemu_syscall *call);
void qemu_RtlDeleteCriticalSection(struct qemu_syscall *call);
void qemu_RtlEnterCriticalSection(struct qemu_syscall *call);
void qemu_RtlInitializeCriticalSectionEx(struct qemu_syscall *call);
void qemu_RtlLeaveCriticalSection(struct qemu_syscall *call);
#endif

#endif
