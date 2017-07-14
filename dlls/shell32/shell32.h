#ifndef SHELL32_H
#define SHELL32_H

#include <stdlib.h>

enum shell32_calls
{
    CALL_COMMANDLINETOARGVW = 0,
    CALL_DLLCANUNLOADNOW,
    CALL_DLLGETCLASSOBJECT,
    CALL_DLLGETVERSION,
    CALL_DLLINSTALL,
    CALL_DLLREGISTERSERVER,
    CALL_DLLUNREGISTERSERVER,
    CALL_DRAGACCEPTFILES,
    CALL_DRAGFINISH,
    CALL_DRAGQUERYFILEA,
    CALL_DRAGQUERYFILEW,
    CALL_DRAGQUERYPOINT,
    CALL_DUPLICATEICON,
    CALL_EXTRACTICONA,
    CALL_EXTRACTICONW,
    CALL_EXTRACTVERSIONRESOURCE16W,
    CALL_FINDEXECUTABLEA,
    CALL_FINDEXECUTABLEW,
    CALL_FREEICONLIST,
    CALL_GETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_INITNETWORKADDRESSCONTROL,
    CALL_OPENAS_RUNDLLA,
    CALL_OPENAS_RUNDLLW,
    CALL_PRINTER_LOADICONSW,
    CALL_PRINTERS_REGISTERWINDOWW,
    CALL_PRINTERS_UNREGISTERWINDOW,
    CALL_REGENERATEUSERENVIRONMENT,
    CALL_SETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_SHALLOC,
    CALL_SHCLSIDFROMSTRING,
    CALL_SHCOCREATEINSTANCE,
    CALL_SHCREATEFILEEXTRACTICONW,
    CALL_SHCREATEQUERYCANCELAUTOPLAYMONIKER,
    CALL_SHELLABOUTA,
    CALL_SHELLABOUTW,
    CALL_SHELLEXECUTEA,
    CALL_SHELLEXECUTEEXA,
    CALL_SHELLEXECUTEEXW,
    CALL_SHELLEXECUTEW,
    CALL_SHENUMERATEUNREADMAILACCOUNTSW,
    CALL_SHFREE,
    CALL_SHGETFILEINFOA,
    CALL_SHGETFILEINFOW,
    CALL_SHGETLOCALIZEDNAME,
    CALL_SHGETMALLOC,
    CALL_SHGETPROPERTYSTOREFORWINDOW,
    CALL_SHHELPSHORTCUTS_RUNDLLA,
    CALL_SHHELPSHORTCUTS_RUNDLLW,
    CALL_SHLOADINPROC,
    CALL_SHLOADNONLOADEDICONOVERLAYIDENTIFIERS,
    CALL_SHPROPSTGCREATE,
    CALL_SHPROPSTGREADMULTIPLE,
    CALL_SHPROPSTGWRITEMULTIPLE,
    CALL_SHQUERYUSERNOTIFICATIONSTATE,
    CALL_SHSETUNREADMAILCOUNTW,
    CALL_WOWSHELLEXECUTE,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_CommandLineToArgvW(struct qemu_syscall *call);
void qemu_DllCanUnloadNow(struct qemu_syscall *call);
void qemu_DllGetClassObject(struct qemu_syscall *call);
void qemu_DllGetVersion(struct qemu_syscall *call);
void qemu_DllInstall(struct qemu_syscall *call);
void qemu_DllRegisterServer(struct qemu_syscall *call);
void qemu_DllUnregisterServer(struct qemu_syscall *call);
void qemu_DragAcceptFiles(struct qemu_syscall *call);
void qemu_DragFinish(struct qemu_syscall *call);
void qemu_DragQueryFileA(struct qemu_syscall *call);
void qemu_DragQueryFileW(struct qemu_syscall *call);
void qemu_DragQueryPoint(struct qemu_syscall *call);
void qemu_DuplicateIcon(struct qemu_syscall *call);
void qemu_ExtractIconA(struct qemu_syscall *call);
void qemu_ExtractIconW(struct qemu_syscall *call);
void qemu_ExtractVersionResource16W(struct qemu_syscall *call);
void qemu_FindExecutableA(struct qemu_syscall *call);
void qemu_FindExecutableW(struct qemu_syscall *call);
void qemu_FreeIconList(struct qemu_syscall *call);
void qemu_GetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_InitNetworkAddressControl(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLA(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLW(struct qemu_syscall *call);
void qemu_Printer_LoadIconsW(struct qemu_syscall *call);
void qemu_Printers_RegisterWindowW(struct qemu_syscall *call);
void qemu_Printers_UnregisterWindow(struct qemu_syscall *call);
void qemu_RegenerateUserEnvironment(struct qemu_syscall *call);
void qemu_SetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_SHAlloc(struct qemu_syscall *call);
void qemu_SHCLSIDFromString(struct qemu_syscall *call);
void qemu_SHCoCreateInstance(struct qemu_syscall *call);
void qemu_SHCreateFileExtractIconW(struct qemu_syscall *call);
void qemu_SHCreateQueryCancelAutoPlayMoniker(struct qemu_syscall *call);
void qemu_ShellAboutA(struct qemu_syscall *call);
void qemu_ShellAboutW(struct qemu_syscall *call);
void qemu_ShellExecuteA(struct qemu_syscall *call);
void qemu_ShellExecuteExA(struct qemu_syscall *call);
void qemu_ShellExecuteExW(struct qemu_syscall *call);
void qemu_ShellExecuteW(struct qemu_syscall *call);
void qemu_SHEnumerateUnreadMailAccountsW(struct qemu_syscall *call);
void qemu_SHFree(struct qemu_syscall *call);
void qemu_SHGetFileInfoA(struct qemu_syscall *call);
void qemu_SHGetFileInfoW(struct qemu_syscall *call);
void qemu_SHGetLocalizedName(struct qemu_syscall *call);
void qemu_SHGetMalloc(struct qemu_syscall *call);
void qemu_SHGetPropertyStoreForWindow(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLA(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLW(struct qemu_syscall *call);
void qemu_SHLoadInProc(struct qemu_syscall *call);
void qemu_SHLoadNonloadedIconOverlayIdentifiers(struct qemu_syscall *call);
void qemu_SHPropStgCreate(struct qemu_syscall *call);
void qemu_SHPropStgReadMultiple(struct qemu_syscall *call);
void qemu_SHPropStgWriteMultiple(struct qemu_syscall *call);
void qemu_SHQueryUserNotificationState(struct qemu_syscall *call);
void qemu_SHSetUnreadMailCountW(struct qemu_syscall *call);
void qemu_WOWShellExecute(struct qemu_syscall *call);

DWORD WINAPI (*p_SHCLSIDFromString)(const void *clsid, CLSID *id);

#endif

#endif
