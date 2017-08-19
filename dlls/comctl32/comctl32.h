#ifndef COMCTL32_H
#define COMCTL32_H

#include <stdlib.h>

enum comctl32_calls
{
    CALL_CREATEPROPERTYSHEETPAGEA = 0,
    CALL_CREATEPROPERTYSHEETPAGEW,
    CALL_DESTROYPROPERTYSHEETPAGE,
    CALL_INITCOMMONCONTROLS,
    CALL_PROPERTYSHEETA,
    CALL_PROPERTYSHEETW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_CreatePropertySheetPageA(struct qemu_syscall *call);
void qemu_CreatePropertySheetPageW(struct qemu_syscall *call);
void qemu_DestroyPropertySheetPage(struct qemu_syscall *call);
void qemu_InitCommonControls(struct qemu_syscall *call);
void qemu_PropertySheetA(struct qemu_syscall *call);
void qemu_PropertySheetW(struct qemu_syscall *call);

#endif

#endif
