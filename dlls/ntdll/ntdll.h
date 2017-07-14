#ifndef NTDLL_H
#define NTDLL_H

enum ntdll_calls
{
    CALL___C_SPECIFIC_HANDLER = 0,
    CALL_RTLADDFUNCTIONTABLE,
    CALL_RTLCAPTURECONTEXT,
    CALL_RTLDECODEPOINTER,
    CALL_RTLDELETECRITICALSECTION,
    CALL_RTLENCODEPOINTER,
    CALL_RTLENTERCRITICALSECTION,
    CALL_RTLINITIALIZECRITICALSECTIONEX,
    CALL_RTLLEAVECRITICALSECTION,
    CALL_RTLLOOKUPFUNCTIONENTRY,
    CALL_RTLVIRTUALUNWIND,
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu___C_specific_handler(struct qemu_syscall *call);
void qemu_RtlAddFunctionTable(struct qemu_syscall *call);
void qemu_RtlCaptureContext(struct qemu_syscall *call);
void qemu_RtlDecodePointer(struct qemu_syscall *call);
void qemu_RtlDeleteCriticalSection(struct qemu_syscall *call);
void qemu_RtlEncodePointer(struct qemu_syscall *call);
void qemu_RtlEnterCriticalSection(struct qemu_syscall *call);
void qemu_RtlInitializeCriticalSectionEx(struct qemu_syscall *call);
void qemu_RtlLeaveCriticalSection(struct qemu_syscall *call);
void qemu_RtlLookupFunctionEntry(struct qemu_syscall *call);
void qemu_RtlVirtualUnwind(struct qemu_syscall *call);
#endif

#endif
