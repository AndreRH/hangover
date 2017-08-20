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
    CALL_ILAPPENDID,
    CALL_ILCLONE,
    CALL_ILCLONEFIRST,
    CALL_ILCOMBINE,
    CALL_ILCREATEFROMPATHA,
    CALL_ILCREATEFROMPATHW,
    CALL_ILFINDCHILD,
    CALL_ILFINDLASTID,
    CALL_ILFREE,
    CALL_ILGETDISPLAYNAME,
    CALL_ILGETDISPLAYNAMEEX,
    CALL_ILGETNEXT,
    CALL_ILGETSIZE,
    CALL_ILGLOBALCLONE,
    CALL_ILGLOBALFREE,
    CALL_ILISEQUAL,
    CALL_ILISPARENT,
    CALL_ILLOADFROMSTREAM,
    CALL_ILREMOVELASTID,
    CALL_ILSAVETOSTREAM,
    CALL_INITNETWORKADDRESSCONTROL,
    CALL_ISLFNDRIVEA,
    CALL_ISLFNDRIVEW,
    CALL_OPENAS_RUNDLLA,
    CALL_OPENAS_RUNDLLW,
    CALL_PATHYETANOTHERMAKEUNIQUENAME,
    CALL_PRINTER_LOADICONSW,
    CALL_PRINTERS_REGISTERWINDOWW,
    CALL_PRINTERS_UNREGISTERWINDOW,
    CALL_REGENERATEUSERENVIRONMENT,
    CALL_SETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_SHALLOC,
    CALL_SHBINDTOPARENT,
    CALL_SHCLONESPECIALIDLIST,
    CALL_SHCLSIDFROMSTRING,
    CALL_SHCOCREATEINSTANCE,
    CALL_SHCREATEFILEEXTRACTICONW,
    CALL_SHCREATEITEMFROMIDLIST,
    CALL_SHCREATEITEMFROMPARSINGNAME,
    CALL_SHCREATELINKS,
    CALL_SHCREATEQUERYCANCELAUTOPLAYMONIKER,
    CALL_SHCREATESHELLITEM,
    CALL_SHCREATESHELLITEMARRAY,
    CALL_SHCREATESHELLITEMARRAYFROMDATAOBJECT,
    CALL_SHCREATESHELLITEMARRAYFROMIDLISTS,
    CALL_SHCREATESHELLITEMARRAYFROMSHELLITEM,
    CALL_SHELLABOUTA,
    CALL_SHELLABOUTW,
    CALL_SHELLEXECUTEA,
    CALL_SHELLEXECUTEEXA,
    CALL_SHELLEXECUTEEXW,
    CALL_SHELLEXECUTEW,
    CALL_SHENUMERATEUNREADMAILACCOUNTSW,
    CALL_SHFREE,
    CALL_SHGETDATAFROMIDLISTA,
    CALL_SHGETDATAFROMIDLISTW,
    CALL_SHGETFILEINFOA,
    CALL_SHGETFILEINFOW,
    CALL_SHGETFOLDERLOCATION,
    CALL_SHGETFOLDERPATHA,
    CALL_SHGETFOLDERPATHANDSUBDIRA,
    CALL_SHGETFOLDERPATHANDSUBDIRW,
    CALL_SHGETFOLDERPATHEX,
    CALL_SHGETFOLDERPATHW,
    CALL_SHGETIDLISTFROMOBJECT,
    CALL_SHGETITEMFROMDATAOBJECT,
    CALL_SHGETITEMFROMOBJECT,
    CALL_SHGETKNOWNFOLDERIDLIST,
    CALL_SHGETKNOWNFOLDERITEM,
    CALL_SHGETKNOWNFOLDERPATH,
    CALL_SHGETLOCALIZEDNAME,
    CALL_SHGETMALLOC,
    CALL_SHGETNAMEFROMIDLIST,
    CALL_SHGETPATHFROMIDLISTA,
    CALL_SHGETPATHFROMIDLISTEX,
    CALL_SHGETPATHFROMIDLISTW,
    CALL_SHGETPROPERTYSTOREFORWINDOW,
    CALL_SHGETPROPERTYSTOREFROMPARSINGNAME,
    CALL_SHGETREALIDL,
    CALL_SHGETSETFOLDERCUSTOMSETTINGS,
    CALL_SHGETSPECIALFOLDERLOCATION,
    CALL_SHGETSPECIALFOLDERPATHA,
    CALL_SHGETSPECIALFOLDERPATHW,
    CALL_SHHELPSHORTCUTS_RUNDLLA,
    CALL_SHHELPSHORTCUTS_RUNDLLW,
    CALL_SHILCREATEFROMPATHAW,
    CALL_SHLIMITINPUTEDIT,
    CALL_SHLOADINPROC,
    CALL_SHLOADNONLOADEDICONOVERLAYIDENTIFIERS,
    CALL_SHLOGILFROMFSIL,
    CALL_SHOPENFOLDERANDSELECTITEMS,
    CALL_SHPARSEDISPLAYNAME,
    CALL_SHPROPSTGCREATE,
    CALL_SHPROPSTGREADMULTIPLE,
    CALL_SHPROPSTGWRITEMULTIPLE,
    CALL_SHQUERYUSERNOTIFICATIONSTATE,
    CALL_SHSETUNREADMAILCOUNTW,
    CALL_SHSIMPLEIDLISTFROMPATHAW,
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
void qemu_ILAppendID(struct qemu_syscall *call);
void qemu_ILClone(struct qemu_syscall *call);
void qemu_ILCloneFirst(struct qemu_syscall *call);
void qemu_ILCombine(struct qemu_syscall *call);
void qemu_ILCreateFromPathA(struct qemu_syscall *call);
void qemu_ILCreateFromPathW(struct qemu_syscall *call);
void qemu_ILFindChild(struct qemu_syscall *call);
void qemu_ILFindLastID(struct qemu_syscall *call);
void qemu_ILFree(struct qemu_syscall *call);
void qemu_ILGetDisplayName(struct qemu_syscall *call);
void qemu_ILGetDisplayNameEx(struct qemu_syscall *call);
void qemu_ILGetNext(struct qemu_syscall *call);
void qemu_ILGetSize(struct qemu_syscall *call);
void qemu_ILGlobalClone(struct qemu_syscall *call);
void qemu_ILGlobalFree(struct qemu_syscall *call);
void qemu_ILIsEqual(struct qemu_syscall *call);
void qemu_ILIsParent(struct qemu_syscall *call);
void qemu_ILLoadFromStream(struct qemu_syscall *call);
void qemu_ILRemoveLastID(struct qemu_syscall *call);
void qemu_ILSaveToStream(struct qemu_syscall *call);
void qemu_InitNetworkAddressControl(struct qemu_syscall *call);
void qemu_IsLFNDriveA(struct qemu_syscall *call);
void qemu_IsLFNDriveW(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLA(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLW(struct qemu_syscall *call);
void qemu_PathYetAnotherMakeUniqueName(struct qemu_syscall *call);
void qemu_Printer_LoadIconsW(struct qemu_syscall *call);
void qemu_Printers_RegisterWindowW(struct qemu_syscall *call);
void qemu_Printers_UnregisterWindow(struct qemu_syscall *call);
void qemu_RegenerateUserEnvironment(struct qemu_syscall *call);
void qemu_SetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_SHAlloc(struct qemu_syscall *call);
void qemu_SHBindToParent(struct qemu_syscall *call);
void qemu_SHCloneSpecialIDList(struct qemu_syscall *call);
void qemu_SHCLSIDFromString(struct qemu_syscall *call);
void qemu_SHCoCreateInstance(struct qemu_syscall *call);
void qemu_SHCreateFileExtractIconW(struct qemu_syscall *call);
void qemu_SHCreateItemFromIDList(struct qemu_syscall *call);
void qemu_SHCreateItemFromParsingName(struct qemu_syscall *call);
void qemu_SHCreateLinks(struct qemu_syscall *call);
void qemu_SHCreateQueryCancelAutoPlayMoniker(struct qemu_syscall *call);
void qemu_SHCreateShellItem(struct qemu_syscall *call);
void qemu_SHCreateShellItemArray(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromDataObject(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromIDLists(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromShellItem(struct qemu_syscall *call);
void qemu_ShellAboutA(struct qemu_syscall *call);
void qemu_ShellAboutW(struct qemu_syscall *call);
void qemu_ShellExecuteA(struct qemu_syscall *call);
void qemu_ShellExecuteExA(struct qemu_syscall *call);
void qemu_ShellExecuteExW(struct qemu_syscall *call);
void qemu_ShellExecuteW(struct qemu_syscall *call);
void qemu_SHEnumerateUnreadMailAccountsW(struct qemu_syscall *call);
void qemu_SHFree(struct qemu_syscall *call);
void qemu_SHGetDataFromIDListA(struct qemu_syscall *call);
void qemu_SHGetDataFromIDListW(struct qemu_syscall *call);
void qemu_SHGetFileInfoA(struct qemu_syscall *call);
void qemu_SHGetFileInfoW(struct qemu_syscall *call);
void qemu_SHGetFolderLocation(struct qemu_syscall *call);
void qemu_SHGetFolderPathA(struct qemu_syscall *call);
void qemu_SHGetFolderPathAndSubDirA(struct qemu_syscall *call);
void qemu_SHGetFolderPathAndSubDirW(struct qemu_syscall *call);
void qemu_SHGetFolderPathEx(struct qemu_syscall *call);
void qemu_SHGetFolderPathW(struct qemu_syscall *call);
void qemu_SHGetIDListFromObject(struct qemu_syscall *call);
void qemu_SHGetItemFromDataObject(struct qemu_syscall *call);
void qemu_SHGetItemFromObject(struct qemu_syscall *call);
void qemu_SHGetKnownFolderIDList(struct qemu_syscall *call);
void qemu_SHGetKnownFolderItem(struct qemu_syscall *call);
void qemu_SHGetKnownFolderPath(struct qemu_syscall *call);
void qemu_SHGetLocalizedName(struct qemu_syscall *call);
void qemu_SHGetMalloc(struct qemu_syscall *call);
void qemu_SHGetNameFromIDList(struct qemu_syscall *call);
void qemu_SHGetPathFromIDListA(struct qemu_syscall *call);
void qemu_SHGetPathFromIDListEx(struct qemu_syscall *call);
void qemu_SHGetPathFromIDListW(struct qemu_syscall *call);
void qemu_SHGetPropertyStoreForWindow(struct qemu_syscall *call);
void qemu_SHGetPropertyStoreFromParsingName(struct qemu_syscall *call);
void qemu_SHGetRealIDL(struct qemu_syscall *call);
void qemu_SHGetSetFolderCustomSettings(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderLocation(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderPathA(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderPathAW(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderPathW(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLA(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLW(struct qemu_syscall *call);
void qemu_SHILCreateFromPathAW(struct qemu_syscall *call);
void qemu_SHLimitInputEdit(struct qemu_syscall *call);
void qemu_SHLoadInProc(struct qemu_syscall *call);
void qemu_SHLoadNonloadedIconOverlayIdentifiers(struct qemu_syscall *call);
void qemu_SHLogILFromFSIL(struct qemu_syscall *call);
void qemu_SHOpenFolderAndSelectItems(struct qemu_syscall *call);
void qemu_SHParseDisplayName(struct qemu_syscall *call);
void qemu_SHPropStgCreate(struct qemu_syscall *call);
void qemu_SHPropStgReadMultiple(struct qemu_syscall *call);
void qemu_SHPropStgWriteMultiple(struct qemu_syscall *call);
void qemu_SHQueryUserNotificationState(struct qemu_syscall *call);
void qemu_SHSetUnreadMailCountW(struct qemu_syscall *call);
void qemu_SHSimpleIDListFromPathAW(struct qemu_syscall *call);
void qemu_WOWShellExecute(struct qemu_syscall *call);

DWORD WINAPI (*p_SHCLSIDFromString)(const void *clsid, CLSID *id);

#endif

#endif
