#ifndef SHELL32_H
#define SHELL32_H

#include <stdlib.h>

enum shell32_calls
{
    CALL_ARRANGEWINDOWS = 0,
    CALL_CALLCPLENTRY16,
    CALL_CDEFFOLDERMENU_CREATE2,
    CALL_CHECKESCAPESA,
    CALL_CHECKESCAPESW,
    CALL_CIDLDATA_CREATEFROMIDARRAY,
    CALL_COMMANDLINETOARGVW,
    CALL_CONTROL_FILLCACHE_RUNDLLA,
    CALL_CONTROL_FILLCACHE_RUNDLLW,
    CALL_CONTROL_RUNDLLA,
    CALL_CONTROL_RUNDLLW,
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
    CALL_DOENVIRONMENTSUBSTA,
    CALL_DOENVIRONMENTSUBSTW,
    CALL_DRAGACCEPTFILES,
    CALL_DRAGFINISH,
    CALL_DRAGQUERYFILEA,
    CALL_DRAGQUERYFILEW,
    CALL_DRAGQUERYPOINT,
    CALL_DRIVETYPE,
    CALL_DUPLICATEICON,
    CALL_EXITWINDOWSDIALOG,
    CALL_EXTRACTASSOCIATEDICONA,
    CALL_EXTRACTASSOCIATEDICONEXA,
    CALL_EXTRACTASSOCIATEDICONEXW,
    CALL_EXTRACTASSOCIATEDICONW,
    CALL_EXTRACTICONA,
    CALL_EXTRACTICONEXA,
    CALL_EXTRACTICONEXW,
    CALL_EXTRACTICONW,
    CALL_EXTRACTVERSIONRESOURCE16W,
    CALL_FILEICONINIT,
    CALL_FILEMENU_ABORTINITMENU,
    CALL_FILEMENU_ADDFILESFORPIDL,
    CALL_FILEMENU_APPENDFILESFORPIDL,
    CALL_FILEMENU_APPENDITEMAW,
    CALL_FILEMENU_CREATE,
    CALL_FILEMENU_DELETEALLITEMS,
    CALL_FILEMENU_DELETEITEMBYCMD,
    CALL_FILEMENU_DELETEITEMBYFIRSTID,
    CALL_FILEMENU_DELETEITEMBYINDEX,
    CALL_FILEMENU_DELETESEPARATOR,
    CALL_FILEMENU_DESTROY,
    CALL_FILEMENU_DRAWITEM,
    CALL_FILEMENU_ENABLEITEMBYCMD,
    CALL_FILEMENU_FINDSUBMENUBYPIDL,
    CALL_FILEMENU_GETITEMEXTENT,
    CALL_FILEMENU_GETLASTSELECTEDITEMPIDLS,
    CALL_FILEMENU_HANDLEMENUCHAR,
    CALL_FILEMENU_INITMENUPOPUP,
    CALL_FILEMENU_INSERTUSINGPIDL,
    CALL_FILEMENU_INVALIDATE,
    CALL_FILEMENU_MEASUREITEM,
    CALL_FILEMENU_REPLACEUSINGPIDL,
    CALL_FILEMENU_TRACKPOPUPMENUEX,
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
    CALL_NTSHCHANGENOTIFYDEREGISTER,
    CALL_NTSHCHANGENOTIFYREGISTER,
    CALL_OLESTRTOSTRNAW,
    CALL_OPENAS_RUNDLLA,
    CALL_OPENAS_RUNDLLW,
    CALL_PARSEFIELD,
    CALL_PATHYETANOTHERMAKEUNIQUENAME,
    CALL_PICKICONDLG,
    CALL_PRINTER_LOADICONSW,
    CALL_PRINTERS_REGISTERWINDOWW,
    CALL_PRINTERS_UNREGISTERWINDOW,
    CALL_READCABINETSTATE,
    CALL_REALDRIVETYPE,
    CALL_REGENERATEUSERENVIRONMENT,
    CALL_REGISTERSHELLHOOK,
    CALL_RESTARTDIALOG,
    CALL_RESTARTDIALOGEX,
    CALL_RLBUILDLISTOFPATHS,
    CALL_RUNFILEDLGAW,
    CALL_SETAPPSTARTINGCURSOR,
    CALL_SETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_SHABORTINVOKECOMMAND,
    CALL_SHADDFROMPROPSHEETEXTARRAY,
    CALL_SHADDTORECENTDOCS,
    CALL_SHALLOC,
    CALL_SHALLOCSHARED,
    CALL_SHAPPBARMESSAGE,
    CALL_SHASSOCENUMHANDLERS,
    CALL_SHBINDTOPARENT,
    CALL_SHBROWSEFORFOLDERA,
    CALL_SHBROWSEFORFOLDERW,
    CALL_SHCHANGENOTIFICATION_LOCK,
    CALL_SHCHANGENOTIFICATION_UNLOCK,
    CALL_SHCHANGENOTIFY,
    CALL_SHCHANGENOTIFYDEREGISTER,
    CALL_SHCHANGENOTIFYREGISTER,
    CALL_SHCHANGENOTIFYUPDATEENTRYLIST,
    CALL_SHCLONESPECIALIDLIST,
    CALL_SHCLSIDFROMSTRING,
    CALL_SHCOCREATEINSTANCE,
    CALL_SHCREATEDEFAULTCONTEXTMENU,
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
    CALL_SHCREATESESSIONKEY,
    CALL_SHCREATESHELLFOLDERVIEW,
    CALL_SHCREATESHELLFOLDERVIEWEX,
    CALL_SHCREATESHELLITEM,
    CALL_SHCREATESHELLITEMARRAY,
    CALL_SHCREATESHELLITEMARRAYFROMDATAOBJECT,
    CALL_SHCREATESHELLITEMARRAYFROMIDLISTS,
    CALL_SHCREATESHELLITEMARRAYFROMSHELLITEM,
    CALL_SHCREATESTDENUMFMTETC,
    CALL_SHDEFEXTRACTICONA,
    CALL_SHDEFEXTRACTICONW,
    CALL_SHDESTROYPROPSHEETEXTARRAY,
    CALL_SHDODRAGDROP,
    CALL_SHECHANGEDIRA,
    CALL_SHECHANGEDIRW,
    CALL_SHEGETDIRA,
    CALL_SHEGETDIRW,
    CALL_SHELL32_243,
    CALL_SHELL_GETCACHEDIMAGEINDEXAW,
    CALL_SHELL_GETIMAGELISTS,
    CALL_SHELL_MERGEMENUS,
    CALL_SHELL_NOTIFYICONA,
    CALL_SHELL_NOTIFYICONW,
    CALL_SHELLABOUTA,
    CALL_SHELLABOUTW,
    CALL_SHELLDDEINIT,
    CALL_SHELLEXEC_RUNDLLA,
    CALL_SHELLEXEC_RUNDLLW,
    CALL_SHELLEXECUTEA,
    CALL_SHELLEXECUTEEXA,
    CALL_SHELLEXECUTEEXW,
    CALL_SHELLEXECUTEW,
    CALL_SHELLHOOKPROC,
    CALL_SHELLMESSAGEBOX,
    CALL_SHEMPTYRECYCLEBINA,
    CALL_SHEMPTYRECYCLEBINW,
    CALL_SHENUMERATEUNREADMAILACCOUNTSW,
    CALL_SHFILEOPERATIONA,
    CALL_SHFILEOPERATIONW,
    CALL_SHFIND_INITMENUPOPUP,
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
    CALL_SHGETICONOVERLAYINDEXA,
    CALL_SHGETICONOVERLAYINDEXW,
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
    CALL_SHGETSTOCKICONINFO,
    CALL_SHHANDLEUPDATEIMAGE,
    CALL_SHHELPSHORTCUTS_RUNDLLA,
    CALL_SHHELPSHORTCUTS_RUNDLLW,
    CALL_SHILCREATEFROMPATHAW,
    CALL_SHINITRESTRICTED,
    CALL_SHISFILEAVAILABLEOFFLINE,
    CALL_SHLIMITINPUTEDIT,
    CALL_SHLOADINPROC,
    CALL_SHLOADNONLOADEDICONOVERLAYIDENTIFIERS,
    CALL_SHLOADOLE,
    CALL_SHLOCKSHARED,
    CALL_SHLOGILFROMFSIL,
    CALL_SHMAPIDLISTTOIMAGELISTINDEXASYNC,
    CALL_SHMAPPIDLTOSYSTEMIMAGELISTINDEX,
    CALL_SHOBJECTPROPERTIES,
    CALL_SHOPENFOLDERANDSELECTITEMS,
    CALL_SHOPENWITHDIALOG,
    CALL_SHOUTOFMEMORYMESSAGEBOX,
    CALL_SHPARSEDISPLAYNAME,
    CALL_SHPATHPREPAREFORWRITEA,
    CALL_SHPATHPREPAREFORWRITEW,
    CALL_SHPROPSTGCREATE,
    CALL_SHPROPSTGREADMULTIPLE,
    CALL_SHPROPSTGWRITEMULTIPLE,
    CALL_SHQUERYRECYCLEBINA,
    CALL_SHQUERYRECYCLEBINW,
    CALL_SHQUERYUSERNOTIFICATIONSTATE,
    CALL_SHREGCLOSEKEY,
    CALL_SHREGDELETEKEYW,
    CALL_SHREGISTERDRAGDROP,
    CALL_SHREGOPENKEYA,
    CALL_SHREGOPENKEYW,
    CALL_SHREGQUERYVALUEA,
    CALL_SHREGQUERYVALUEEXA,
    CALL_SHREGQUERYVALUEEXW,
    CALL_SHREGQUERYVALUEW,
    CALL_SHREMOVELOCALIZEDNAME,
    CALL_SHREPLACEFROMPROPSHEETEXTARRAY,
    CALL_SHRESTRICTED,
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
    CALL_SHUPDATERECYCLEBINICON,
    CALL_SHVALIDATEUNC,
    CALL_SHWAITFORFILETOOPEN,
    CALL_SHWINHELP,
    CALL_SIGNALFILEOPEN,
    CALL_STRRETTOSTRNAW,
    CALL_STRTOOLESTRAW,
    CALL_STRTOOLESTRNAW,
    CALL_WIN32CREATEDIRECTORY,
    CALL_WIN32DELETEFILE,
    CALL_WIN32REMOVEDIRECTORY,
    CALL_WOWSHELLEXECUTE,
    CALL_WRITECABINETSTATE,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_ArrangeWindows(struct qemu_syscall *call);
void qemu_CallCPLEntry16(struct qemu_syscall *call);
void qemu_CDefFolderMenu_Create2(struct qemu_syscall *call);
void qemu_CheckEscapesA(struct qemu_syscall *call);
void qemu_CheckEscapesW(struct qemu_syscall *call);
void qemu_CIDLData_CreateFromIDArray(struct qemu_syscall *call);
void qemu_CommandLineToArgvW(struct qemu_syscall *call);
void qemu_Control_FillCache_RunDLLA(struct qemu_syscall *call);
void qemu_Control_FillCache_RunDLLW(struct qemu_syscall *call);
void qemu_Control_RunDLLA(struct qemu_syscall *call);
void qemu_Control_RunDLLW(struct qemu_syscall *call);
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
void qemu_DoEnvironmentSubstA(struct qemu_syscall *call);
void qemu_DoEnvironmentSubstW(struct qemu_syscall *call);
void qemu_DragAcceptFiles(struct qemu_syscall *call);
void qemu_DragFinish(struct qemu_syscall *call);
void qemu_DragQueryFileA(struct qemu_syscall *call);
void qemu_DragQueryFileW(struct qemu_syscall *call);
void qemu_DragQueryPoint(struct qemu_syscall *call);
void qemu_DriveType(struct qemu_syscall *call);
void qemu_DuplicateIcon(struct qemu_syscall *call);
void qemu_ExitWindowsDialog(struct qemu_syscall *call);
void qemu_ExtractAssociatedIconA(struct qemu_syscall *call);
void qemu_ExtractAssociatedIconExA(struct qemu_syscall *call);
void qemu_ExtractAssociatedIconExW(struct qemu_syscall *call);
void qemu_ExtractAssociatedIconW(struct qemu_syscall *call);
void qemu_ExtractIconA(struct qemu_syscall *call);
void qemu_ExtractIconExA(struct qemu_syscall *call);
void qemu_ExtractIconExW(struct qemu_syscall *call);
void qemu_ExtractIconW(struct qemu_syscall *call);
void qemu_ExtractVersionResource16W(struct qemu_syscall *call);
void qemu_FileIconInit(struct qemu_syscall *call);
void qemu_FileMenu_AbortInitMenu(struct qemu_syscall *call);
void qemu_FileMenu_AddFilesForPidl(struct qemu_syscall *call);
void qemu_FileMenu_AppendFilesForPidl(struct qemu_syscall *call);
void qemu_FileMenu_AppendItemAW(struct qemu_syscall *call);
void qemu_FileMenu_Create(struct qemu_syscall *call);
void qemu_FileMenu_DeleteAllItems(struct qemu_syscall *call);
void qemu_FileMenu_DeleteItemByCmd(struct qemu_syscall *call);
void qemu_FileMenu_DeleteItemByFirstID(struct qemu_syscall *call);
void qemu_FileMenu_DeleteItemByIndex(struct qemu_syscall *call);
void qemu_FileMenu_DeleteSeparator(struct qemu_syscall *call);
void qemu_FileMenu_Destroy(struct qemu_syscall *call);
void qemu_FileMenu_DrawItem(struct qemu_syscall *call);
void qemu_FileMenu_EnableItemByCmd(struct qemu_syscall *call);
void qemu_FileMenu_FindSubMenuByPidl(struct qemu_syscall *call);
void qemu_FileMenu_GetItemExtent(struct qemu_syscall *call);
void qemu_FileMenu_GetLastSelectedItemPidls(struct qemu_syscall *call);
void qemu_FileMenu_HandleMenuChar(struct qemu_syscall *call);
void qemu_FileMenu_InitMenuPopup(struct qemu_syscall *call);
void qemu_FileMenu_InsertUsingPidl(struct qemu_syscall *call);
void qemu_FileMenu_Invalidate(struct qemu_syscall *call);
void qemu_FileMenu_MeasureItem(struct qemu_syscall *call);
void qemu_FileMenu_ReplaceUsingPidl(struct qemu_syscall *call);
void qemu_FileMenu_TrackPopupMenuEx(struct qemu_syscall *call);
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
void qemu_NTSHChangeNotifyDeregister(struct qemu_syscall *call);
void qemu_NTSHChangeNotifyRegister(struct qemu_syscall *call);
void qemu_OleStrToStrNAW(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLA(struct qemu_syscall *call);
void qemu_OpenAs_RunDLLW(struct qemu_syscall *call);
void qemu_ParseField(struct qemu_syscall *call);
void qemu_PathYetAnotherMakeUniqueName(struct qemu_syscall *call);
void qemu_PickIconDlg(struct qemu_syscall *call);
void qemu_Printer_LoadIconsW(struct qemu_syscall *call);
void qemu_Printers_RegisterWindowW(struct qemu_syscall *call);
void qemu_Printers_UnregisterWindow(struct qemu_syscall *call);
void qemu_ReadCabinetState(struct qemu_syscall *call);
void qemu_RealDriveType(struct qemu_syscall *call);
void qemu_RegenerateUserEnvironment(struct qemu_syscall *call);
void qemu_RegisterShellHook(struct qemu_syscall *call);
void qemu_RestartDialog(struct qemu_syscall *call);
void qemu_RestartDialogEx(struct qemu_syscall *call);
void qemu_RLBuildListOfPaths(struct qemu_syscall *call);
void qemu_RunFileDlgAW(struct qemu_syscall *call);
void qemu_SetAppStartingCursor(struct qemu_syscall *call);
void qemu_SetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_SHAbortInvokeCommand(struct qemu_syscall *call);
void qemu_SHAddFromPropSheetExtArray(struct qemu_syscall *call);
void qemu_SHAddToRecentDocs(struct qemu_syscall *call);
void qemu_SHAlloc(struct qemu_syscall *call);
void qemu_SHAllocShared(struct qemu_syscall *call);
void qemu_SHAppBarMessage(struct qemu_syscall *call);
void qemu_SHAssocEnumHandlers(struct qemu_syscall *call);
void qemu_SHBindToParent(struct qemu_syscall *call);
void qemu_SHBrowseForFolderA(struct qemu_syscall *call);
void qemu_SHBrowseForFolderW(struct qemu_syscall *call);
void qemu_SHChangeNotification_Lock(struct qemu_syscall *call);
void qemu_SHChangeNotification_Unlock(struct qemu_syscall *call);
void qemu_SHChangeNotify(struct qemu_syscall *call);
void qemu_SHChangeNotifyDeregister(struct qemu_syscall *call);
void qemu_SHChangeNotifyRegister(struct qemu_syscall *call);
void qemu_SHChangeNotifyUpdateEntryList(struct qemu_syscall *call);
void qemu_SHCloneSpecialIDList(struct qemu_syscall *call);
void qemu_SHCLSIDFromString(struct qemu_syscall *call);
void qemu_SHCoCreateInstance(struct qemu_syscall *call);
void qemu_SHCreateDefaultContextMenu(struct qemu_syscall *call);
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
void qemu_SHCreateSessionKey(struct qemu_syscall *call);
void qemu_SHCreateShellFolderView(struct qemu_syscall *call);
void qemu_SHCreateShellFolderViewEx(struct qemu_syscall *call);
void qemu_SHCreateShellItem(struct qemu_syscall *call);
void qemu_SHCreateShellItemArray(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromDataObject(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromIDLists(struct qemu_syscall *call);
void qemu_SHCreateShellItemArrayFromShellItem(struct qemu_syscall *call);
void qemu_SHCreateStdEnumFmtEtc(struct qemu_syscall *call);
void qemu_SHDefExtractIconA(struct qemu_syscall *call);
void qemu_SHDefExtractIconW(struct qemu_syscall *call);
void qemu_SHDestroyPropSheetExtArray(struct qemu_syscall *call);
void qemu_SHDoDragDrop(struct qemu_syscall *call);
void qemu_SheChangeDirA(struct qemu_syscall *call);
void qemu_SheChangeDirW(struct qemu_syscall *call);
void qemu_SheGetDirA(struct qemu_syscall *call);
void qemu_SheGetDirW(struct qemu_syscall *call);
void qemu_shell32_243(struct qemu_syscall *call);
void qemu_Shell_GetCachedImageIndexAW(struct qemu_syscall *call);
void qemu_Shell_GetImageLists(struct qemu_syscall *call);
void qemu_Shell_MergeMenus(struct qemu_syscall *call);
void qemu_Shell_NotifyIconA(struct qemu_syscall *call);
void qemu_Shell_NotifyIconW(struct qemu_syscall *call);
void qemu_ShellAboutA(struct qemu_syscall *call);
void qemu_ShellAboutW(struct qemu_syscall *call);
void qemu_ShellDDEInit(struct qemu_syscall *call);
void qemu_ShellExec_RunDLLA(struct qemu_syscall *call);
void qemu_ShellExec_RunDLLW(struct qemu_syscall *call);
void qemu_ShellExecuteA(struct qemu_syscall *call);
void qemu_ShellExecuteExA(struct qemu_syscall *call);
void qemu_ShellExecuteExW(struct qemu_syscall *call);
void qemu_ShellExecuteW(struct qemu_syscall *call);
void qemu_ShellHookProc(struct qemu_syscall *call);
void qemu_ShellMessageBox(struct qemu_syscall *call);
void qemu_SHEmptyRecycleBinA(struct qemu_syscall *call);
void qemu_SHEmptyRecycleBinW(struct qemu_syscall *call);
void qemu_SHEnumerateUnreadMailAccountsW(struct qemu_syscall *call);
void qemu_SHFileOperationA(struct qemu_syscall *call);
void qemu_SHFileOperationW(struct qemu_syscall *call);
void qemu_SHFind_InitMenuPopup(struct qemu_syscall *call);
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
void qemu_SHGetIconOverlayIndexA(struct qemu_syscall *call);
void qemu_SHGetIconOverlayIndexW(struct qemu_syscall *call);
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
void qemu_SHGetStockIconInfo(struct qemu_syscall *call);
void qemu_SHHandleUpdateImage(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLA(struct qemu_syscall *call);
void qemu_SHHelpShortcuts_RunDLLW(struct qemu_syscall *call);
void qemu_SHILCreateFromPathAW(struct qemu_syscall *call);
void qemu_SHInitRestricted(struct qemu_syscall *call);
void qemu_SHIsFileAvailableOffline(struct qemu_syscall *call);
void qemu_SHLimitInputEdit(struct qemu_syscall *call);
void qemu_SHLoadInProc(struct qemu_syscall *call);
void qemu_SHLoadNonloadedIconOverlayIdentifiers(struct qemu_syscall *call);
void qemu_SHLoadOLE(struct qemu_syscall *call);
void qemu_SHLockShared(struct qemu_syscall *call);
void qemu_SHLogILFromFSIL(struct qemu_syscall *call);
void qemu_SHMapIDListToImageListIndexAsync(struct qemu_syscall *call);
void qemu_SHMapPIDLToSystemImageListIndex(struct qemu_syscall *call);
void qemu_SHObjectProperties(struct qemu_syscall *call);
void qemu_SHOpenFolderAndSelectItems(struct qemu_syscall *call);
void qemu_SHOpenWithDialog(struct qemu_syscall *call);
void qemu_SHOutOfMemoryMessageBox(struct qemu_syscall *call);
void qemu_SHParseDisplayName(struct qemu_syscall *call);
void qemu_SHPathPrepareForWriteA(struct qemu_syscall *call);
void qemu_SHPathPrepareForWriteW(struct qemu_syscall *call);
void qemu_SHPropStgCreate(struct qemu_syscall *call);
void qemu_SHPropStgReadMultiple(struct qemu_syscall *call);
void qemu_SHPropStgWriteMultiple(struct qemu_syscall *call);
void qemu_SHQueryRecycleBinA(struct qemu_syscall *call);
void qemu_SHQueryRecycleBinW(struct qemu_syscall *call);
void qemu_SHQueryUserNotificationState(struct qemu_syscall *call);
void qemu_SHRegCloseKey(struct qemu_syscall *call);
void qemu_SHRegDeleteKeyW(struct qemu_syscall *call);
void qemu_SHRegisterDragDrop(struct qemu_syscall *call);
void qemu_SHRegOpenKeyA(struct qemu_syscall *call);
void qemu_SHRegOpenKeyW(struct qemu_syscall *call);
void qemu_SHRegQueryValueA(struct qemu_syscall *call);
void qemu_SHRegQueryValueExA(struct qemu_syscall *call);
void qemu_SHRegQueryValueExW(struct qemu_syscall *call);
void qemu_SHRegQueryValueW(struct qemu_syscall *call);
void qemu_SHRemoveLocalizedName(struct qemu_syscall *call);
void qemu_SHReplaceFromPropSheetExtArray(struct qemu_syscall *call);
void qemu_SHRestricted(struct qemu_syscall *call);
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
void qemu_SHUpdateRecycleBinIcon(struct qemu_syscall *call);
void qemu_SHValidateUNC(struct qemu_syscall *call);
void qemu_SHWaitForFileToOpen(struct qemu_syscall *call);
void qemu_SHWinHelp(struct qemu_syscall *call);
void qemu_SignalFileOpen(struct qemu_syscall *call);
void qemu_StrRetToStrNA(struct qemu_syscall *call);
void qemu_StrRetToStrNAW(struct qemu_syscall *call);
void qemu_StrRetToStrNW(struct qemu_syscall *call);
void qemu_StrToOleStrAW(struct qemu_syscall *call);
void qemu_StrToOleStrNAW(struct qemu_syscall *call);
void qemu_Win32CreateDirectory(struct qemu_syscall *call);
void qemu_Win32DeleteFile(struct qemu_syscall *call);
void qemu_Win32RemoveDirectory(struct qemu_syscall *call);
void qemu_WOWShellExecute(struct qemu_syscall *call);
void qemu_WriteCabinetState(struct qemu_syscall *call);

DWORD (* WINAPI p_SHCLSIDFromString)(const void *clsid, CLSID *id);
HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID iid, LPVOID *ppv);
void (* WINAPI p_RunFileDlgAW)(HWND hwndOwner, HICON hIcon, LPCVOID lpstrDirectory, LPCVOID lpstrTitle, LPCVOID lpstrDescription, UINT uFlags);
void (* WINAPI p_ExitWindowsDialog)(HWND hWndOwner);
INT (* WINAPI p_Shell_GetCachedImageIndexAW)(LPCVOID szPath, INT nIndex, BOOL bSimulateDoc);
HRESULT ( * WINAPI p_SHMapIDListToImageListIndexAsync)(IUnknown *pts, IShellFolder *psf, LPCITEMIDLIST pidl, UINT flags, void *pfn, void *pvData, void *pvHint, int *piIndex, int *piIndexSel);
BOOL (* WINAPI p_StrRetToStrNAW)(LPVOID dest, DWORD len, LPSTRRET src, const ITEMIDLIST *pidl);
BOOL (* WINAPI p_StrToOleStrAW)(LPWSTR lpWideCharStr, LPCVOID lpString);
BOOL (* WINAPI p_StrToOleStrNAW)(LPWSTR lpWide, INT nWide, LPCVOID lpStr, INT nStr);
BOOL (* WINAPI p_OleStrToStrNAW)(LPVOID lpOut, INT nOut, LPCVOID lpIn, INT nIn);

#endif

#endif
