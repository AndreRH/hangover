#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>

enum msvcrt_calls
{
    CALL_ISTEXTUNICODE = 0,
    CALL_REGCLOSEKEY,
    CALL_REGCONNECTREGISTRYA,
    CALL_REGCONNECTREGISTRYW,
    CALL_REGCOPYTREEA,
    CALL_REGCOPYTREEW,
    CALL_REGCREATEKEYA,
    CALL_REGCREATEKEYEXA,
    CALL_REGCREATEKEYEXW,
    CALL_REGCREATEKEYTRANSACTEDA,
    CALL_REGCREATEKEYTRANSACTEDW,
    CALL_REGCREATEKEYW,
    CALL_REGDELETEKEYA,
    CALL_REGDELETEKEYEXA,
    CALL_REGDELETEKEYEXW,
    CALL_REGDELETEKEYVALUEA,
    CALL_REGDELETEKEYVALUEW,
    CALL_REGDELETEKEYW,
    CALL_REGDELETETREEA,
    CALL_REGDELETETREEW,
    CALL_REGDELETEVALUEA,
    CALL_REGDELETEVALUEW,
    CALL_REGDISABLEPREDEFINEDCACHE,
    CALL_REGDISABLEREFLECTIONKEY,
    CALL_REGENUMKEYA,
    CALL_REGENUMKEYEXA,
    CALL_REGENUMKEYEXW,
    CALL_REGENUMKEYW,
    CALL_REGENUMVALUEA,
    CALL_REGENUMVALUEW,
    CALL_REGFLUSHKEY,
    CALL_REGGETKEYSECURITY,
    CALL_REGGETVALUEA,
    CALL_REGGETVALUEW,
    CALL_REGLOADKEYA,
    CALL_REGLOADKEYW,
    CALL_REGLOADMUISTRINGA,
    CALL_REGLOADMUISTRINGW,
    CALL_REGNOTIFYCHANGEKEYVALUE,
    CALL_REGOPENCURRENTUSER,
    CALL_REGOPENKEYA,
    CALL_REGOPENKEYEXA,
    CALL_REGOPENKEYEXW,
    CALL_REGOPENKEYW,
    CALL_REGOPENUSERCLASSESROOT,
    CALL_REGOVERRIDEPREDEFKEY,
    CALL_REGQUERYINFOKEYA,
    CALL_REGQUERYINFOKEYW,
    CALL_REGQUERYMULTIPLEVALUESA,
    CALL_REGQUERYMULTIPLEVALUESW,
    CALL_REGQUERYVALUEA,
    CALL_REGQUERYVALUEEXA,
    CALL_REGQUERYVALUEEXW,
    CALL_REGQUERYVALUEW,
    CALL_REGREPLACEKEYA,
    CALL_REGREPLACEKEYW,
    CALL_REGRESTOREKEYA,
    CALL_REGRESTOREKEYW,
    CALL_REGSAVEKEYA,
    CALL_REGSAVEKEYEXA,
    CALL_REGSAVEKEYEXW,
    CALL_REGSAVEKEYW,
    CALL_REGSETKEYSECURITY,
    CALL_REGSETKEYVALUEA,
    CALL_REGSETKEYVALUEW,
    CALL_REGSETVALUEA,
    CALL_REGSETVALUEEXA,
    CALL_REGSETVALUEEXW,
    CALL_REGSETVALUEW,
    CALL_REGUNLOADKEYA,
    CALL_REGUNLOADKEYW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_IsTextUnicode(struct qemu_syscall *call);
void qemu_RegCloseKey(struct qemu_syscall *call);
void qemu_RegConnectRegistryA(struct qemu_syscall *call);
void qemu_RegConnectRegistryW(struct qemu_syscall *call);
void qemu_RegCopyTreeA(struct qemu_syscall *call);
void qemu_RegCopyTreeW(struct qemu_syscall *call);
void qemu_RegCreateKeyA(struct qemu_syscall *call);
void qemu_RegCreateKeyExA(struct qemu_syscall *call);
void qemu_RegCreateKeyExW(struct qemu_syscall *call);
void qemu_RegCreateKeyTransactedA(struct qemu_syscall *call);
void qemu_RegCreateKeyTransactedW(struct qemu_syscall *call);
void qemu_RegCreateKeyW(struct qemu_syscall *call);
void qemu_RegDeleteKeyA(struct qemu_syscall *call);
void qemu_RegDeleteKeyExA(struct qemu_syscall *call);
void qemu_RegDeleteKeyExW(struct qemu_syscall *call);
void qemu_RegDeleteKeyValueA(struct qemu_syscall *call);
void qemu_RegDeleteKeyValueW(struct qemu_syscall *call);
void qemu_RegDeleteKeyW(struct qemu_syscall *call);
void qemu_RegDeleteTreeA(struct qemu_syscall *call);
void qemu_RegDeleteTreeW(struct qemu_syscall *call);
void qemu_RegDeleteValueA(struct qemu_syscall *call);
void qemu_RegDeleteValueW(struct qemu_syscall *call);
void qemu_RegDisablePredefinedCache(struct qemu_syscall *call);
void qemu_RegDisableReflectionKey(struct qemu_syscall *call);
void qemu_RegEnumKeyA(struct qemu_syscall *call);
void qemu_RegEnumKeyExA(struct qemu_syscall *call);
void qemu_RegEnumKeyExW(struct qemu_syscall *call);
void qemu_RegEnumKeyW(struct qemu_syscall *call);
void qemu_RegEnumValueA(struct qemu_syscall *call);
void qemu_RegEnumValueW(struct qemu_syscall *call);
void qemu_RegFlushKey(struct qemu_syscall *call);
void qemu_RegGetKeySecurity(struct qemu_syscall *call);
void qemu_RegGetValueA(struct qemu_syscall *call);
void qemu_RegGetValueW(struct qemu_syscall *call);
void qemu_RegLoadKeyA(struct qemu_syscall *call);
void qemu_RegLoadKeyW(struct qemu_syscall *call);
void qemu_RegLoadMUIStringA(struct qemu_syscall *call);
void qemu_RegLoadMUIStringW(struct qemu_syscall *call);
void qemu_RegNotifyChangeKeyValue(struct qemu_syscall *call);
void qemu_RegOpenCurrentUser(struct qemu_syscall *call);
void qemu_RegOpenKeyA(struct qemu_syscall *call);
void qemu_RegOpenKeyExA(struct qemu_syscall *call);
void qemu_RegOpenKeyExW(struct qemu_syscall *call);
void qemu_RegOpenKeyW(struct qemu_syscall *call);
void qemu_RegOpenUserClassesRoot(struct qemu_syscall *call);
void qemu_RegOverridePredefKey(struct qemu_syscall *call);
void qemu_RegQueryInfoKeyA(struct qemu_syscall *call);
void qemu_RegQueryInfoKeyW(struct qemu_syscall *call);
void qemu_RegQueryMultipleValuesA(struct qemu_syscall *call);
void qemu_RegQueryMultipleValuesW(struct qemu_syscall *call);
void qemu_RegQueryValueA(struct qemu_syscall *call);
void qemu_RegQueryValueExA(struct qemu_syscall *call);
void qemu_RegQueryValueExW(struct qemu_syscall *call);
void qemu_RegQueryValueW(struct qemu_syscall *call);
void qemu_RegReplaceKeyA(struct qemu_syscall *call);
void qemu_RegReplaceKeyW(struct qemu_syscall *call);
void qemu_RegRestoreKeyA(struct qemu_syscall *call);
void qemu_RegRestoreKeyW(struct qemu_syscall *call);
void qemu_RegSaveKeyA(struct qemu_syscall *call);
void qemu_RegSaveKeyExA(struct qemu_syscall *call);
void qemu_RegSaveKeyExW(struct qemu_syscall *call);
void qemu_RegSaveKeyW(struct qemu_syscall *call);
void qemu_RegSetKeySecurity(struct qemu_syscall *call);
void qemu_RegSetKeyValueA(struct qemu_syscall *call);
void qemu_RegSetKeyValueW(struct qemu_syscall *call);
void qemu_RegSetValueA(struct qemu_syscall *call);
void qemu_RegSetValueExA(struct qemu_syscall *call);
void qemu_RegSetValueExW(struct qemu_syscall *call);
void qemu_RegSetValueW(struct qemu_syscall *call);
void qemu_RegUnLoadKeyA(struct qemu_syscall *call);
void qemu_RegUnLoadKeyW(struct qemu_syscall *call);

#endif

#endif
