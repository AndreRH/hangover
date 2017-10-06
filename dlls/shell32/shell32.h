#ifndef SHELL32_H
#define SHELL32_H

#include <stdlib.h>

enum shell32_calls
{
    CALL_ARRANGEWINDOWS = 0,
    CALL_CIDLDATA_CREATEFROMIDARRAY,
    CALL_COMMANDLINETOARGVW,
    CALL_DAD_AUTOSCROLL,
    CALL_DAD_DRAGENTER,
    CALL_DAD_DRAGENTEREX,
    CALL_DAD_DRAGLEAVE,
    CALL_DAD_DRAGMOVE,
    CALL_DAD_SETDRAGIMAGE,
    CALL_DAD_SHOWDRAGIMAGE,
    CALL_DLLCANUNLOADNOW,
    CALL_DLLGETCLASSOBJECT,
    CALL_DLLGETVERSION,
    CALL_DLLINSTALL,
    CALL_DLLREGISTERSERVER,
    CALL_DLLUNREGISTERSERVER,
    CALL_DOENVIRONMENTSUBST,
    CALL_DRAGACCEPTFILES,
    CALL_DRAGFINISH,
    CALL_DRAGQUERYFILEA,
    CALL_DRAGQUERYFILEW,
    CALL_DRAGQUERYPOINT,
    CALL_DRIVETYPE,
    CALL_DUPLICATEICON,
    CALL_EXTRACTICONA,
    CALL_EXTRACTICONW,
    CALL_EXTRACTVERSIONRESOURCE16W,
    CALL_FILEICONINIT,
    CALL_FINDEXECUTABLEA,
    CALL_FINDEXECUTABLEW,
    CALL_FREEICONLIST,
    CALL_GETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_GETFILENAMEFROMBROWSE,
    CALL_GUIDFROMSTRINGW,
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
    CALL_INVALIDATEDRIVETYPE,
    CALL_ISLFNDRIVEA,
    CALL_ISLFNDRIVEW,
    CALL_ISNETDRIVE,
    CALL_ISUSERANADMIN,
    CALL_LINKWINDOW_REGISTERCLASS,
    CALL_LINKWINDOW_UNREGISTERCLASS,
    CALL_OPENAS_RUNDLLA,
    CALL_OPENAS_RUNDLLW,
    CALL_PARSEFIELD,
    CALL_PATHYETANOTHERMAKEUNIQUENAME,
    CALL_PRINTER_LOADICONSW,
    CALL_PRINTERS_REGISTERWINDOWW,
    CALL_PRINTERS_UNREGISTERWINDOW,
    CALL_READCABINETSTATE,
    CALL_REALDRIVETYPE,
    CALL_REGENERATEUSERENVIRONMENT,
    CALL_REGISTERSHELLHOOK,
    CALL_RLBUILDLISTOFPATHS,
    CALL_SETAPPSTARTINGCURSOR,
    CALL_SETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_SHABORTINVOKECOMMAND,
    CALL_SHADDFROMPROPSHEETEXTARRAY,
    CALL_SHADDTORECENTDOCS,
    CALL_SHALLOC,
    CALL_SHALLOCSHARED,
    CALL_SHAPPBARMESSAGE,
    CALL_SHBINDTOPARENT,
    CALL_SHCLONESPECIALIDLIST,
    CALL_SHCLSIDFROMSTRING,
    CALL_SHCOCREATEINSTANCE,
    CALL_SHCREATEDIRECTORY,
    CALL_SHCREATEDIRECTORYEXA,
    CALL_SHCREATEDIRECTORYEXW,
    CALL_SHCREATEFILEEXTRACTICONW,
    CALL_SHCREATEITEMFROMIDLIST,
    CALL_SHCREATEITEMFROMPARSINGNAME,
    CALL_SHCREATELINKS,
    CALL_SHCREATEPROPSHEETEXTARRAY,
    CALL_SHCREATEPROPSHEETEXTARRAYEX,
    CALL_SHCREATEQUERYCANCELAUTOPLAYMONIKER,
    CALL_SHCREATESHELLITEM,
    CALL_SHCREATESHELLITEMARRAY,
    CALL_SHCREATESHELLITEMARRAYFROMDATAOBJECT,
    CALL_SHCREATESHELLITEMARRAYFROMIDLISTS,
    CALL_SHCREATESHELLITEMARRAYFROMSHELLITEM,
    CALL_SHCREATESTDENUMFMTETC,
    CALL_SHDESTROYPROPSHEETEXTARRAY,
    CALL_SHDODRAGDROP,
    CALL_SHECHANGEDIRA,
    CALL_SHECHANGEDIRW,
    CALL_SHEGETDIRA,
    CALL_SHEGETDIRW,
    CALL_SHELL32_243,
    CALL_SHELL_NOTIFYICONA,
    CALL_SHELL_NOTIFYICONW,
    CALL_SHELLABOUTA,
    CALL_SHELLABOUTW,
    CALL_SHELLEXECUTEA,
    CALL_SHELLEXECUTEEXA,
    CALL_SHELLEXECUTEEXW,
    CALL_SHELLEXECUTEW,
    CALL_SHENUMERATEUNREADMAILACCOUNTSW,
    CALL_SHFILEOPERATIONA,
    CALL_SHFILEOPERATIONW,
    CALL_SHFINDFILES,
    CALL_SHFLUSHCLIPBOARD,
    CALL_SHFLUSHSFCACHE,
    CALL_SHFORMATDRIVE,
    CALL_SHFREE,
    CALL_SHFREENAMEMAPPINGS,
    CALL_SHFREESHARED,
    CALL_SHFREEUNUSEDLIBRARIES,
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
    CALL_SHGETIMAGELIST,
    CALL_SHGETINSTANCEEXPLORER,
    CALL_SHGETITEMFROMDATAOBJECT,
    CALL_SHGETITEMFROMOBJECT,
    CALL_SHGETKNOWNFOLDERIDLIST,
    CALL_SHGETKNOWNFOLDERITEM,
    CALL_SHGETKNOWNFOLDERPATH,
    CALL_SHGETLOCALIZEDNAME,
    CALL_SHGETMALLOC,
    CALL_SHGETNAMEFROMIDLIST,
    CALL_SHGETNEWLINKINFOA,
    CALL_SHGETNEWLINKINFOW,
    CALL_SHGETPATHFROMIDLISTA,
    CALL_SHGETPATHFROMIDLISTEX,
    CALL_SHGETPATHFROMIDLISTW,
    CALL_SHGETPROPERTYSTOREFORWINDOW,
    CALL_SHGETPROPERTYSTOREFROMPARSINGNAME,
    CALL_SHGETREALIDL,
    CALL_SHGETSETFOLDERCUSTOMSETTINGS,
    CALL_SHGETSETSETTINGS,
    CALL_SHGETSETTINGS,
    CALL_SHGETSPECIALFOLDERLOCATION,
    CALL_SHGETSPECIALFOLDERPATHA,
    CALL_SHGETSPECIALFOLDERPATHW,
    CALL_SHHANDLEUPDATEIMAGE,
    CALL_SHHELPSHORTCUTS_RUNDLLA,
    CALL_SHHELPSHORTCUTS_RUNDLLW,
    CALL_SHILCREATEFROMPATHAW,
    CALL_SHISFILEAVAILABLEOFFLINE,
    CALL_SHLIMITINPUTEDIT,
    CALL_SHLOADINPROC,
    CALL_SHLOADNONLOADEDICONOVERLAYIDENTIFIERS,
    CALL_SHLOADOLE,
    CALL_SHLOCKSHARED,
    CALL_SHLOGILFROMFSIL,
    CALL_SHOBJECTPROPERTIES,
    CALL_SHOPENFOLDERANDSELECTITEMS,
    CALL_SHOUTOFMEMORYMESSAGEBOX,
    CALL_SHPARSEDISPLAYNAME,
    CALL_SHPATHPREPAREFORWRITEA,
    CALL_SHPATHPREPAREFORWRITEW,
    CALL_SHPROPSTGCREATE,
    CALL_SHPROPSTGREADMULTIPLE,
    CALL_SHPROPSTGWRITEMULTIPLE,
    CALL_SHQUERYUSERNOTIFICATIONSTATE,
    CALL_SHREGISTERDRAGDROP,
    CALL_SHREMOVELOCALIZEDNAME,
    CALL_SHREPLACEFROMPROPSHEETEXTARRAY,
    CALL_SHREVOKEDRAGDROP,
    CALL_SHRUNCONTROLPANEL,
    CALL_SHSETINSTANCEEXPLORER,
    CALL_SHSETLOCALIZEDNAME,
    CALL_SHSETUNREADMAILCOUNTW,
    CALL_SHSHELLFOLDERVIEW_MESSAGE,
    CALL_SHSIMPLEIDLISTFROMPATHAW,
    CALL_SHSTARTNETCONNECTIONDIALOG,
    CALL_SHUNLOCKSHARED,
    CALL_SHUPDATEIMAGEA,
    CALL_SHUPDATEIMAGEW,
    CALL_SHVALIDATEUNC,
    CALL_SHWAITFORFILETOOPEN,
    CALL_SHWINHELP,
    CALL_SIGNALFILEOPEN,
    CALL_WIN32CREATEDIRECTORY,
    CALL_WIN32DELETEFILE,
    CALL_WIN32REMOVEDIRECTORY,
    CALL_WOWSHELLEXECUTE,
    CALL_WRITECABINETSTATE,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_ArrangeWindows(struct qemu_syscall *call);
void qemu_CIDLData_CreateFromIDArray(struct qemu_syscall *call);
void qemu_CommandLineToArgvW(struct qemu_syscall *call);
void qemu_DAD_AutoScroll(struct qemu_syscall *call);
void qemu_DAD_DragEnter(struct qemu_syscall *call);
void qemu_DAD_DragEnterEx(struct qemu_syscall *call);
void qemu_DAD_DragLeave(struct qemu_syscall *call);
void qemu_DAD_DragMove(struct qemu_syscall *call);
void qemu_DAD_SetDragImage(struct qemu_syscall *call);
void qemu_DAD_ShowDragImage(struct qemu_syscall *call);
void qemu_DllCanUnloadNow(struct qemu_syscall *call);
void qemu_DllGetClassObject(struct qemu_syscall *call);
void qemu_DllGetVersion(struct qemu_syscall *call);
void qemu_DllInstall(struct qemu_syscall *call);
void qemu_DllRegisterServer(struct qemu_syscall *call);
void qemu_DllUnregisterServer(struct qemu_syscall *call);
void qemu_DoEnvironmentSubst(struct qemu_syscall *call);
void qemu_DragAcceptFiles(struct qemu_syscall *call);
void qemu_DragFinish(struct qemu_syscall *call);
void qemu_DragQueryFileA(struct qemu_syscall *call);
void qemu_DragQueryFileW(struct qemu_syscall *call);
void qemu_DragQueryPoint(struct qemu_syscall *call);
void qemu_DriveType(struct qemu_syscall *call);
void qemu_DuplicateIcon(struct qemu_syscall *call);
void qemu_ExtractIconA(struct qemu_syscall *call);
void qemu_ExtractIconW(struct qemu_syscall *call);
void qemu_ExtractVersionResource16W(struct qemu_syscall *call);
void qemu_FileIconInit(struct qemu_syscall *call);
void qemu_FindExecutableA(struct qemu_syscall *call);
void qemu_FindExecutableW(struct qemu_syscall *call);
void qemu_FreeIconList(struct qemu_syscall *call);
void qemu_GetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_GetFileNameFromBrowse(struct qemu_syscall *call);
void qemu_GUIDFromStringW(struct qemu_syscall *call);
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
void qemu_InvalidateDriveType(struct qemu_syscall *call);
void qemu_IsLFNDriveA(struct qemu_syscall *call);
void qemu_IsLFNDriveW(struct qemu_syscall *call);
void qemu_IsNetDrive(struct qemu_syscall *call);
void qemu_IsUserAnAdmin(struct qemu_syscall *call);
void qemu_LinkWindow_RegisterClass(struct qemu_syscall *call);
void qemu_LinkWindow_UnregisterClass(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLA(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLW(struct qemu_syscall *call);
void qemu_ParseField(struct qemu_syscall *call);
void qemu_PathYetAnotherMakeUniqueName(struct qemu_syscall *call);
void qemu_Printer_LoadIconsW(struct qemu_syscall *call);
void qemu_Printers_RegisterWindowW(struct qemu_syscall *call);
void qemu_Printers_UnregisterWindow(struct qemu_syscall *call);
void qemu_ReadCabinetState(struct qemu_syscall *call);
void qemu_RealDriveType(struct qemu_syscall *call);
void qemu_RegenerateUserEnvironment(struct qemu_syscall *call);
void qemu_RegisterShellHook(struct qemu_syscall *call);
void qemu_RLBuildListOfPaths(struct qemu_syscall *call);
void qemu_SetAppStartingCursor(struct qemu_syscall *call);
void qemu_SetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_SHAbortInvokeCommand(struct qemu_syscall *call);
void qemu_SHAddFromPropSheetExtArray(struct qemu_syscall *call);
void qemu_SHAddToRecentDocs(struct qemu_syscall *call);
void qemu_SHAlloc(struct qemu_syscall *call);
void qemu_SHAllocShared(struct qemu_syscall *call);
void qemu_SHAppBarMessage(struct qemu_syscall *call);
void qemu_SHBindToParent(struct qemu_syscall *call);
void qemu_SHCloneSpecialIDList(struct qemu_syscall *call);
void qemu_SHCLSIDFromString(struct qemu_syscall *call);
void qemu_SHCoCreateInstance(struct qemu_syscall *call);
void qemu_SHCreateDirectory(struct qemu_syscall *call);
void qemu_SHCreateDirectoryExA(struct qemu_syscall *call);
void qemu_SHCreateDirectoryExW(struct qemu_syscall *call);
void qemu_SHCreateFileExtractIconW(struct qemu_syscall *call);
void qemu_SHCreateItemFromIDList(struct qemu_syscall *call);
void qemu_SHCreateItemFromParsingName(struct qemu_syscall *call);
void qemu_SHCreateLinks(struct qemu_syscall *call);
void qemu_SHCreatePropSheetExtArray(struct qemu_syscall *call);
void qemu_SHCreatePropSheetExtArrayEx(struct qemu_syscall *call);
void qemu_SHCreateQueryCancelAutoPlayMoniker(struct qemu_syscall *call);
void qemu_SHCreateShellItem(struct qemu_syscall *call);
void qemu_SHCreateShellItemArray(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromDataObject(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromIDLists(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromShellItem(struct qemu_syscall *call);
void qemu_SHCreateStdEnumFmtEtc(struct qemu_syscall *call);
void qemu_SHDestroyPropSheetExtArray(struct qemu_syscall *call);
void qemu_SHDoDragDrop(struct qemu_syscall *call);
void qemu_SheChangeDirA(struct qemu_syscall *call);
void qemu_SheChangeDirW(struct qemu_syscall *call);
void qemu_SheGetDirA(struct qemu_syscall *call);
void qemu_SheGetDirW(struct qemu_syscall *call);
void qemu_shell32_243(struct qemu_syscall *call);
void qemu_Shell_NotifyIconA(struct qemu_syscall *call);
void qemu_Shell_NotifyIconW(struct qemu_syscall *call);
void qemu_ShellAboutA(struct qemu_syscall *call);
void qemu_ShellAboutW(struct qemu_syscall *call);
void qemu_ShellExecuteA(struct qemu_syscall *call);
void qemu_ShellExecuteExA(struct qemu_syscall *call);
void qemu_ShellExecuteExW(struct qemu_syscall *call);
void qemu_ShellExecuteW(struct qemu_syscall *call);
void qemu_SHEnumerateUnreadMailAccountsW(struct qemu_syscall *call);
void qemu_SHFileOperationA(struct qemu_syscall *call);
void qemu_SHFileOperationW(struct qemu_syscall *call);
void qemu_SHFindFiles(struct qemu_syscall *call);
void qemu_SHFlushClipboard(struct qemu_syscall *call);
void qemu_SHFlushSFCache(struct qemu_syscall *call);
void qemu_SHFormatDrive(struct qemu_syscall *call);
void qemu_SHFree(struct qemu_syscall *call);
void qemu_SHFreeNameMappings(struct qemu_syscall *call);
void qemu_SHFreeShared(struct qemu_syscall *call);
void qemu_SHFreeUnusedLibraries(struct qemu_syscall *call);
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
void qemu_SHGetImageList(struct qemu_syscall *call);
void qemu_SHGetInstanceExplorer(struct qemu_syscall *call);
void qemu_SHGetItemFromDataObject(struct qemu_syscall *call);
void qemu_SHGetItemFromObject(struct qemu_syscall *call);
void qemu_SHGetKnownFolderIDList(struct qemu_syscall *call);
void qemu_SHGetKnownFolderItem(struct qemu_syscall *call);
void qemu_SHGetKnownFolderPath(struct qemu_syscall *call);
void qemu_SHGetLocalizedName(struct qemu_syscall *call);
void qemu_SHGetMalloc(struct qemu_syscall *call);
void qemu_SHGetNameFromIDList(struct qemu_syscall *call);
void qemu_SHGetNewLinkInfoA(struct qemu_syscall *call);
void qemu_SHGetNewLinkInfoW(struct qemu_syscall *call);
void qemu_SHGetPathFromIDListA(struct qemu_syscall *call);
void qemu_SHGetPathFromIDListEx(struct qemu_syscall *call);
void qemu_SHGetPathFromIDListW(struct qemu_syscall *call);
void qemu_SHGetPropertyStoreForWindow(struct qemu_syscall *call);
void qemu_SHGetPropertyStoreFromParsingName(struct qemu_syscall *call);
void qemu_SHGetRealIDL(struct qemu_syscall *call);
void qemu_SHGetSetFolderCustomSettings(struct qemu_syscall *call);
void qemu_SHGetSetSettings(struct qemu_syscall *call);
void qemu_SHGetSettings(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderLocation(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderPathA(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderPathAW(struct qemu_syscall *call);
void qemu_SHGetSpecialFolderPathW(struct qemu_syscall *call);
void qemu_SHHandleUpdateImage(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLA(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLW(struct qemu_syscall *call);
void qemu_SHILCreateFromPathAW(struct qemu_syscall *call);
void qemu_SHIsFileAvailableOffline(struct qemu_syscall *call);
void qemu_SHLimitInputEdit(struct qemu_syscall *call);
void qemu_SHLoadInProc(struct qemu_syscall *call);
void qemu_SHLoadNonloadedIconOverlayIdentifiers(struct qemu_syscall *call);
void qemu_SHLoadOLE(struct qemu_syscall *call);
void qemu_SHLockShared(struct qemu_syscall *call);
void qemu_SHLogILFromFSIL(struct qemu_syscall *call);
void qemu_SHObjectProperties(struct qemu_syscall *call);
void qemu_SHOpenFolderAndSelectItems(struct qemu_syscall *call);
void qemu_SHOutOfMemoryMessageBox(struct qemu_syscall *call);
void qemu_SHParseDisplayName(struct qemu_syscall *call);
void qemu_SHPathPrepareForWriteA(struct qemu_syscall *call);
void qemu_SHPathPrepareForWriteW(struct qemu_syscall *call);
void qemu_SHPropStgCreate(struct qemu_syscall *call);
void qemu_SHPropStgReadMultiple(struct qemu_syscall *call);
void qemu_SHPropStgWriteMultiple(struct qemu_syscall *call);
void qemu_SHQueryUserNotificationState(struct qemu_syscall *call);
void qemu_SHRegisterDragDrop(struct qemu_syscall *call);
void qemu_SHRemoveLocalizedName(struct qemu_syscall *call);
void qemu_SHReplaceFromPropSheetExtArray(struct qemu_syscall *call);
void qemu_SHRevokeDragDrop(struct qemu_syscall *call);
void qemu_SHRunControlPanel(struct qemu_syscall *call);
void qemu_SHSetInstanceExplorer(struct qemu_syscall *call);
void qemu_SHSetLocalizedName(struct qemu_syscall *call);
void qemu_SHSetUnreadMailCountW(struct qemu_syscall *call);
void qemu_SHShellFolderView_Message(struct qemu_syscall *call);
void qemu_SHSimpleIDListFromPathAW(struct qemu_syscall *call);
void qemu_SHStartNetConnectionDialog(struct qemu_syscall *call);
void qemu_SHUnlockShared(struct qemu_syscall *call);
void qemu_SHUpdateImageA(struct qemu_syscall *call);
void qemu_SHUpdateImageW(struct qemu_syscall *call);
void qemu_SHValidateUNC(struct qemu_syscall *call);
void qemu_SHWaitForFileToOpen(struct qemu_syscall *call);
void qemu_SHWinHelp(struct qemu_syscall *call);
void qemu_SignalFileOpen(struct qemu_syscall *call);
void qemu_Win32CreateDirectory(struct qemu_syscall *call);
void qemu_Win32DeleteFile(struct qemu_syscall *call);
void qemu_Win32RemoveDirectory(struct qemu_syscall *call);
void qemu_WOWShellExecute(struct qemu_syscall *call);
void qemu_WriteCabinetState(struct qemu_syscall *call);

DWORD (* WINAPI p_SHCLSIDFromString)(const void *clsid, CLSID *id);
HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID iid, LPVOID *ppv);

#endif

#endif
