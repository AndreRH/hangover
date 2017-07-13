#ifndef SHELL32_H
#define SHELL32_H

#include <stdlib.h>

enum shell32_calls
{
    CALL_DLLGETCLASSOBJECT = 0,
    CALL_DRAGACCEPTFILES,
    CALL_DRAGFINISH,
    CALL_DRAGQUERYFILEA,
    CALL_DRAGQUERYFILEW,
    CALL_DRAGQUERYPOINT,
    CALL_SHALLOC,
    CALL_SHCLSIDFROMSTRING,
    CALL_SHCOCREATEINSTANCE,
    CALL_SHCREATEQUERYCANCELAUTOPLAYMONIKER,
    CALL_SHELLABOUTW,
    CALL_SHFREE,
    CALL_SHGETMALLOC,
    CALL_SHPROPSTGCREATE,
    CALL_SHPROPSTGREADMULTIPLE,
    CALL_SHPROPSTGWRITEMULTIPLE,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_DllGetClassObject(struct qemu_syscall *call);
void qemu_DragAcceptFiles(struct qemu_syscall *call);
void qemu_DragFinish(struct qemu_syscall *call);
void qemu_DragQueryFileA(struct qemu_syscall *call);
void qemu_DragQueryFileW(struct qemu_syscall *call);
void qemu_DragQueryPoint(struct qemu_syscall *call);
void qemu_SHAlloc(struct qemu_syscall *call);
void qemu_SHCLSIDFromString(struct qemu_syscall *call);
void qemu_SHCoCreateInstance(struct qemu_syscall *call);
void qemu_SHCreateQueryCancelAutoPlayMoniker(struct qemu_syscall *call);
void qemu_ShellAboutW(struct qemu_syscall *call);
void qemu_SHFree(struct qemu_syscall *call);
void qemu_SHGetMalloc(struct qemu_syscall *call);
void qemu_SHPropStgCreate(struct qemu_syscall *call);
void qemu_SHPropStgReadMultiple(struct qemu_syscall *call);
void qemu_SHPropStgWriteMultiple(struct qemu_syscall *call);

DWORD WINAPI (*p_SHCLSIDFromString)(const void *clsid, CLSID *id);

#endif

#endif
