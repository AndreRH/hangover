#ifndef SHELL32_H
#define SHELL32_H

#include <stdlib.h>

enum shell32_calls
{
    CALL_ARRANGEWINDOWS = 0,
    CALL_CALLCPLENTRY16,
    CALL_CDEFFOLDERMENU_CREATE2,
    CALL_CF_ADDREF,
    CALL_CF_CREATEINSTANCE,
    CALL_CF_LOCKSERVER,
    CALL_CF_QUERYINTERFACE,
    CALL_CF_RELEASE,
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
    CALL_FOLDERVIEW2_DORENAME,
    CALL_FOLDERVIEW2_GETCURRENTFOLDERFLAGS,
    CALL_FOLDERVIEW2_GETGROUPBY,
    CALL_FOLDERVIEW2_GETGROUPSUBSETCOUNT,
    CALL_FOLDERVIEW2_GETITEM,
    CALL_FOLDERVIEW2_GETSELECTEDITEM,
    CALL_FOLDERVIEW2_GETSELECTION,
    CALL_FOLDERVIEW2_GETSELECTIONSTATE,
    CALL_FOLDERVIEW2_GETSORTCOLUMNCOUNT,
    CALL_FOLDERVIEW2_GETSORTCOLUMNS,
    CALL_FOLDERVIEW2_GETVIEWMODEANDICONSIZE,
    CALL_FOLDERVIEW2_GETVIEWPROPERTY,
    CALL_FOLDERVIEW2_GETVISIBLEITEM,
    CALL_FOLDERVIEW2_INVOKEVERBONSELECTION,
    CALL_FOLDERVIEW2_ISMOVEINSAMEFOLDER,
    CALL_FOLDERVIEW2_SETCURRENTFOLDERFLAGS,
    CALL_FOLDERVIEW2_SETEXTENDEDTILEVIEWPROPERTIES,
    CALL_FOLDERVIEW2_SETGROUPBY,
    CALL_FOLDERVIEW2_SETGROUPSUBSETCOUNT,
    CALL_FOLDERVIEW2_SETREDRAW,
    CALL_FOLDERVIEW2_SETSORTCOLUMNS,
    CALL_FOLDERVIEW2_SETTEXT,
    CALL_FOLDERVIEW2_SETTILEVIEWPROPERTIES,
    CALL_FOLDERVIEW2_SETVIEWMODEANDICONSIZE,
    CALL_FOLDERVIEW2_SETVIEWPROPERTY,
    CALL_FOLDERVIEW_ADDREF,
    CALL_FOLDERVIEW_GETAUTOARRANGE,
    CALL_FOLDERVIEW_GETCURRENTVIEWMODE,
    CALL_FOLDERVIEW_GETDEFAULTSPACING,
    CALL_FOLDERVIEW_GETFOCUSEDITEM,
    CALL_FOLDERVIEW_GETFOLDER,
    CALL_FOLDERVIEW_GETITEMPOSITION,
    CALL_FOLDERVIEW_GETSELECTIONMARKEDITEM,
    CALL_FOLDERVIEW_GETSPACING,
    CALL_FOLDERVIEW_ITEM,
    CALL_FOLDERVIEW_ITEMCOUNT,
    CALL_FOLDERVIEW_ITEMS,
    CALL_FOLDERVIEW_QUERYINTERFACE,
    CALL_FOLDERVIEW_RELEASE,
    CALL_FOLDERVIEW_SELECTANDPOSITIONITEMS,
    CALL_FOLDERVIEW_SELECTITEM,
    CALL_FOLDERVIEW_SETCURRENTVIEWMODE,
    CALL_FREEICONLIST,
    CALL_GETCURRENTPROCESSEXPLICITAPPUSERMODELID,
    CALL_GETFILENAMEFROMBROWSE,
    CALL_GUIDFROMSTRINGW,
    CALL_IENUMIDLIST_ADDREF,
    CALL_IENUMIDLIST_CLONE,
    CALL_IENUMIDLIST_NEXT,
    CALL_IENUMIDLIST_QUERYINTERFACE,
    CALL_IENUMIDLIST_RELEASE,
    CALL_IENUMIDLIST_RESET,
    CALL_IENUMIDLIST_SKIP,
    CALL_ILAPPENDID,
    CALL_ILCLONE,
    CALL_ILCLONEFIRST,
    CALL_ILCOMBINE,
    CALL_ILCREATEFROMPATHA,
    CALL_ILCREATEFROMPATHAW,
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
    CALL_IPERSISTFOLDER3_GETCLASSID,
    CALL_IPERSISTFOLDER3_GETCURFOLDER,
    CALL_IPERSISTFOLDER3_GETFOLDERTARGETINFO,
    CALL_IPERSISTFOLDER3_INITIALIZE,
    CALL_IPERSISTFOLDER3_INITIALIZEEX,
    CALL_ISHELLFOLDER2_ADDREF,
    CALL_ISHELLFOLDER2_BINDTOOBJECT,
    CALL_ISHELLFOLDER2_BINDTOSTORAGE,
    CALL_ISHELLFOLDER2_COMPAREIDS,
    CALL_ISHELLFOLDER2_CREATEVIEWOBJECT,
    CALL_ISHELLFOLDER2_ENUMOBJECTS,
    CALL_ISHELLFOLDER2_ENUMSEARCHES,
    CALL_ISHELLFOLDER2_GETATTRIBUTESOF,
    CALL_ISHELLFOLDER2_GETDEFAULTCOLUMN,
    CALL_ISHELLFOLDER2_GETDEFAULTCOLUMNSTATE,
    CALL_ISHELLFOLDER2_GETDEFAULTSEARCHGUID,
    CALL_ISHELLFOLDER2_GETDETAILSEX,
    CALL_ISHELLFOLDER2_GETDETAILSOF,
    CALL_ISHELLFOLDER2_GETDISPLAYNAMEOF,
    CALL_ISHELLFOLDER2_GETUIOBJECTOF,
    CALL_ISHELLFOLDER2_MAPCOLUMNTOSCID,
    CALL_ISHELLFOLDER2_PARSEDISPLAYNAME,
    CALL_ISHELLFOLDER2_QUERYINTERFACE,
    CALL_ISHELLFOLDER2_RELEASE,
    CALL_ISHELLFOLDER2_SETNAMEOF,
    CALL_ISHELLFOLDERVIEW_ADDOBJECT,
    CALL_ISHELLFOLDERVIEW_ADDREF,
    CALL_ISHELLFOLDERVIEW_ARRANGEGRID,
    CALL_ISHELLFOLDERVIEW_AUTOARRANGE,
    CALL_ISHELLFOLDERVIEW_GETARRANGEPARAM,
    CALL_ISHELLFOLDERVIEW_GETAUTOARRANGE,
    CALL_ISHELLFOLDERVIEW_GETDRAGPOINT,
    CALL_ISHELLFOLDERVIEW_GETDROPPOINT,
    CALL_ISHELLFOLDERVIEW_GETITEMSPACING,
    CALL_ISHELLFOLDERVIEW_GETOBJECT,
    CALL_ISHELLFOLDERVIEW_GETOBJECTCOUNT,
    CALL_ISHELLFOLDERVIEW_GETSELECTEDCOUNT,
    CALL_ISHELLFOLDERVIEW_GETSELECTEDOBJECTS,
    CALL_ISHELLFOLDERVIEW_ISBKDROPTARGET,
    CALL_ISHELLFOLDERVIEW_ISDROPONSOURCE,
    CALL_ISHELLFOLDERVIEW_MOVEICONS,
    CALL_ISHELLFOLDERVIEW_QUERYINTERFACE,
    CALL_ISHELLFOLDERVIEW_QUERYSUPPORT,
    CALL_ISHELLFOLDERVIEW_REARRANGE,
    CALL_ISHELLFOLDERVIEW_REFRESHOBJECT,
    CALL_ISHELLFOLDERVIEW_RELEASE,
    CALL_ISHELLFOLDERVIEW_REMOVEOBJECT,
    CALL_ISHELLFOLDERVIEW_SELECT,
    CALL_ISHELLFOLDERVIEW_SETAUTOMATIONOBJECT,
    CALL_ISHELLFOLDERVIEW_SETCALLBACK,
    CALL_ISHELLFOLDERVIEW_SETCLIPBOARD,
    CALL_ISHELLFOLDERVIEW_SETITEMPOS,
    CALL_ISHELLFOLDERVIEW_SETOBJECTCOUNT,
    CALL_ISHELLFOLDERVIEW_SETPOINTS,
    CALL_ISHELLFOLDERVIEW_SETREDRAW,
    CALL_ISHELLFOLDERVIEW_UPDATEOBJECT,
    CALL_ISHELLVIEW2_CREATEVIEWWINDOW2,
    CALL_ISHELLVIEW2_GETVIEW,
    CALL_ISHELLVIEW2_HANDLERENAME,
    CALL_ISHELLVIEW2_SELECTANDPOSITIONITEM,
    CALL_ISHELLVIEW3_CREATEVIEWWINDOW3,
    CALL_ISHELLVIEW_ADDPROPERTYSHEETPAGES,
    CALL_ISHELLVIEW_ADDREF,
    CALL_ISHELLVIEW_CONTEXTSENSITIVEHELP,
    CALL_ISHELLVIEW_CREATEVIEWWINDOW,
    CALL_ISHELLVIEW_DESTROYVIEWWINDOW,
    CALL_ISHELLVIEW_ENABLEMODELESS,
    CALL_ISHELLVIEW_GETCURRENTINFO,
    CALL_ISHELLVIEW_GETITEMOBJECT,
    CALL_ISHELLVIEW_GETWINDOW,
    CALL_ISHELLVIEW_QUERYINTERFACE,
    CALL_ISHELLVIEW_REFRESH,
    CALL_ISHELLVIEW_RELEASE,
    CALL_ISHELLVIEW_SAVEVIEWSTATE,
    CALL_ISHELLVIEW_SELECTITEM,
    CALL_ISHELLVIEW_TRANSLATEACCELERATOR,
    CALL_ISHELLVIEW_UIACTIVATE,
    CALL_ISLFNDRIVEA,
    CALL_ISLFNDRIVEAW,
    CALL_ISLFNDRIVEW,
    CALL_ISNETDRIVE,
    CALL_ISUSERANADMIN,
    CALL_ISVDROPSOURCE_ADDREF,
    CALL_ISVDROPSOURCE_GIVEFEEDBACK,
    CALL_ISVDROPSOURCE_QUERYCONTINUEDRAG,
    CALL_ISVDROPSOURCE_QUERYINTERFACE,
    CALL_ISVDROPSOURCE_RELEASE,
    CALL_ISVDROPTARGET_ADDREF,
    CALL_ISVDROPTARGET_DRAGENTER,
    CALL_ISVDROPTARGET_DRAGLEAVE,
    CALL_ISVDROPTARGET_DRAGOVER,
    CALL_ISVDROPTARGET_DROP,
    CALL_ISVDROPTARGET_QUERYINTERFACE,
    CALL_ISVDROPTARGET_RELEASE,
    CALL_ISVOLECMDTARGET_ADDREF,
    CALL_ISVOLECMDTARGET_EXEC,
    CALL_ISVOLECMDTARGET_QUERYINTERFACE,
    CALL_ISVOLECMDTARGET_QUERYSTATUS,
    CALL_ISVOLECMDTARGET_RELEASE,
    CALL_ISVVIEWOBJECT_ADDREF,
    CALL_ISVVIEWOBJECT_DRAW,
    CALL_ISVVIEWOBJECT_FREEZE,
    CALL_ISVVIEWOBJECT_GETADVISE,
    CALL_ISVVIEWOBJECT_GETCOLORSET,
    CALL_ISVVIEWOBJECT_QUERYINTERFACE,
    CALL_ISVVIEWOBJECT_RELEASE,
    CALL_ISVVIEWOBJECT_SETADVISE,
    CALL_ISVVIEWOBJECT_UNFREEZE,
    CALL_LINKWINDOW_REGISTERCLASS,
    CALL_LINKWINDOW_UNREGISTERCLASS,
    CALL_NTSHCHANGENOTIFYDEREGISTER,
    CALL_NTSHCHANGENOTIFYREGISTER,
    CALL_OLESTRTOSTRNAW,
    CALL_OPENAS_RUNDLLA,
    CALL_OPENAS_RUNDLLW,
    CALL_PARSEFIELD,
    CALL_PATHADDBACKSLASHAW,
    CALL_PATHAPPENDAW,
    CALL_PATHBUILDROOTAW,
    CALL_PATHCLEANUPSPEC,
    CALL_PATHCOMBINEAW,
    CALL_PATHFILEEXISTSAW,
    CALL_PATHFINDEXTENSIONAW,
    CALL_PATHFINDFILENAMEAW,
    CALL_PATHFINDONPATHAW,
    CALL_PATHGETARGSAW,
    CALL_PATHGETDRIVENUMBERAW,
    CALL_PATHGETEXTENSIONAW,
    CALL_PATHGETSHORTPATHAW,
    CALL_PATHISDIRECTORYAW,
    CALL_PATHISEXEAW,
    CALL_PATHISRELATIVEAW,
    CALL_PATHISROOTAW,
    CALL_PATHISSAMEROOTAW,
    CALL_PATHISUNCAW,
    CALL_PATHMAKEUNIQUENAMEAW,
    CALL_PATHMATCHSPECAW,
    CALL_PATHPARSEICONLOCATIONAW,
    CALL_PATHPROCESSCOMMANDAW,
    CALL_PATHQUALIFYAW,
    CALL_PATHQUOTESPACESAW,
    CALL_PATHREMOVEARGSAW,
    CALL_PATHREMOVEBLANKSAW,
    CALL_PATHREMOVEEXTENSIONAW,
    CALL_PATHREMOVEFILESPECAW,
    CALL_PATHRESOLVEAW,
    CALL_PATHSETDLGITEMPATHAW,
    CALL_PATHSTRIPPATHAW,
    CALL_PATHSTRIPTOROOTAW,
    CALL_PATHUNQUOTESPACESAW,
    CALL_PATHYETANOTHERMAKEUNIQUENAME,
    CALL_PERSISTPROPERTYBAG_GETCLASSID,
    CALL_PERSISTPROPERTYBAG_INITNEW,
    CALL_PERSISTPROPERTYBAG_LOAD,
    CALL_PERSISTPROPERTYBAG_SAVE,
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
    CALL_SET_CALLBACKS,
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
    CALL_SHCREATEDEFCLASSOBJECT,
    CALL_SHCREATEDIRECTORY,
    CALL_SHCREATEDIRECTORYEXA,
    CALL_SHCREATEDIRECTORYEXW,
    CALL_SHCREATEFILEEXTRACTICONW,
    CALL_SHCREATEITEMFROMIDLIST,
    CALL_SHCREATEITEMFROMPARSINGNAME,
    CALL_SHCREATEITEMFROMRELATIVENAME,
    CALL_SHCREATEITEMINKNOWNFOLDER,
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
    CALL_SHELLFOLDERVIEWDUAL_ADDREF,
    CALL_SHELLFOLDERVIEWDUAL_FILTERVIEW,
    CALL_SHELLFOLDERVIEWDUAL_GET_APPLICATION,
    CALL_SHELLFOLDERVIEWDUAL_GET_CURRENTVIEWMODE,
    CALL_SHELLFOLDERVIEWDUAL_GET_FOCUSEDITEM,
    CALL_SHELLFOLDERVIEWDUAL_GET_FOLDER,
    CALL_SHELLFOLDERVIEWDUAL_GET_FOLDERFLAGS,
    CALL_SHELLFOLDERVIEWDUAL_GET_GROUPBY,
    CALL_SHELLFOLDERVIEWDUAL_GET_ICONSIZE,
    CALL_SHELLFOLDERVIEWDUAL_GET_PARENT,
    CALL_SHELLFOLDERVIEWDUAL_GET_SCRIPT,
    CALL_SHELLFOLDERVIEWDUAL_GET_SORTCOLUMNS,
    CALL_SHELLFOLDERVIEWDUAL_GET_VIEWOPTIONS,
    CALL_SHELLFOLDERVIEWDUAL_GETIDSOFNAMES,
    CALL_SHELLFOLDERVIEWDUAL_GETTYPEINFO,
    CALL_SHELLFOLDERVIEWDUAL_GETTYPEINFOCOUNT,
    CALL_SHELLFOLDERVIEWDUAL_INVOKE,
    CALL_SHELLFOLDERVIEWDUAL_POPUPITEMMENU,
    CALL_SHELLFOLDERVIEWDUAL_PUT_CURRENTVIEWMODE,
    CALL_SHELLFOLDERVIEWDUAL_PUT_FOLDERFLAGS,
    CALL_SHELLFOLDERVIEWDUAL_PUT_GROUPBY,
    CALL_SHELLFOLDERVIEWDUAL_PUT_ICONSIZE,
    CALL_SHELLFOLDERVIEWDUAL_PUT_SORTCOLUMNS,
    CALL_SHELLFOLDERVIEWDUAL_QUERYINTERFACE,
    CALL_SHELLFOLDERVIEWDUAL_RELEASE,
    CALL_SHELLFOLDERVIEWDUAL_SELECTEDITEMS,
    CALL_SHELLFOLDERVIEWDUAL_SELECTITEM,
    CALL_SHELLFOLDERVIEWDUAL_SELECTITEMRELATIVE,
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
    CALL_SHGETDESKTOPFOLDER,
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
    CALL_SHGETSPECIALFOLDERPATHAW,
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

#define SHELLFOLDER_HAS_PERSISTFOLDER3      0x1
#define SHELLFOLDER_HAS_PROPERTYBAG         0x2

struct qemu_shellfolder
{
    /* Shared fields */
    uint64_t                flags;

    /* Guest fields */
    IShellFolder2           IShellFolder2_iface;
    IPersistFolder3         IPersistFolder3_iface;
    IPersistPropertyBag     IPersistPropertyBag_iface;

    /* Host fields */
    IShellFolder2           *host_sf;
    IPersistFolder3         *host_pf;
    IPersistPropertyBag     *host_bag;
};

struct qemu_enumidlist
{
    /* Guest fields */
    IEnumIDList         IEnumIDList_iface;

    /* Host fields */
    IEnumIDList         *host;
};

struct qemu_shellview
{
    /* Guest fields */
    IShellView3             IShellView3_iface;
    IOleCommandTarget       IOleCommandTarget_iface;
    IDropTarget             IDropTarget_iface;
    IDropSource             IDropSource_iface;
    IViewObject             IViewObject_iface;
    IFolderView2            IFolderView2_iface;
    IShellFolderView        IShellFolderView_iface;
    IShellFolderViewDual3   IShellFolderViewDual3_iface;

    /* Host fields */
    IShellView3             *host_shellview;
    IOleCommandTarget       *host_cmd_target;
    IDropTarget             *host_drop_target;
    IDropSource             *host_drop_source;
    IViewObject             *host_view_object;
    IFolderView2            *host_folder_view;
    IShellFolderView        *host_shell_folder_view;
    IShellFolderViewDual3   *host_dual_view;
};

struct shellbrowser_wrapper;
struct shellbrowser_funcs
{
    uint64_t AddRef;
    uint64_t Release;
    uint64_t GetWindow;
    uint64_t SetMenuSB;
    uint64_t SendControlMsg;
    uint64_t QI;
    uint64_t IncludeObject;
    uint64_t OnViewWindowActive;
    uint64_t OnStateChange;
    uint64_t RemoveMenusSB;
    uint64_t InsertMenusSB;
};

#ifdef QEMU_DLL_GUEST

void qemu_shellfolder_guest_init(struct qemu_shellfolder *folder);
void qemu_enumidlist_guest_init(struct qemu_enumidlist *folder);
void qemu_shellview_guest_init(struct qemu_shellview *folder);

void shellbrowser_wrapper_get_funcs(struct shellbrowser_funcs *funcs);

#else

extern const struct qemu_ops *qemu_ops;

void qemu_ArrangeWindows(struct qemu_syscall *call);
void qemu_CDefFolderMenu_Create2(struct qemu_syscall *call);
void qemu_CIDLData_CreateFromIDArray(struct qemu_syscall *call);
void qemu_CallCPLEntry16(struct qemu_syscall *call);
void qemu_CheckEscapesA(struct qemu_syscall *call);
void qemu_CheckEscapesW(struct qemu_syscall *call);
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
void qemu_FolderView2_DoRename(struct qemu_syscall *call);
void qemu_FolderView2_GetCurrentFolderFlags(struct qemu_syscall *call);
void qemu_FolderView2_GetGroupBy(struct qemu_syscall *call);
void qemu_FolderView2_GetGroupSubsetCount(struct qemu_syscall *call);
void qemu_FolderView2_GetItem(struct qemu_syscall *call);
void qemu_FolderView2_GetSelectedItem(struct qemu_syscall *call);
void qemu_FolderView2_GetSelection(struct qemu_syscall *call);
void qemu_FolderView2_GetSelectionState(struct qemu_syscall *call);
void qemu_FolderView2_GetSortColumnCount(struct qemu_syscall *call);
void qemu_FolderView2_GetSortColumns(struct qemu_syscall *call);
void qemu_FolderView2_GetViewModeAndIconSize(struct qemu_syscall *call);
void qemu_FolderView2_GetViewProperty(struct qemu_syscall *call);
void qemu_FolderView2_GetVisibleItem(struct qemu_syscall *call);
void qemu_FolderView2_InvokeVerbOnSelection(struct qemu_syscall *call);
void qemu_FolderView2_IsMoveInSameFolder(struct qemu_syscall *call);
void qemu_FolderView2_SetCurrentFolderFlags(struct qemu_syscall *call);
void qemu_FolderView2_SetExtendedTileViewProperties(struct qemu_syscall *call);
void qemu_FolderView2_SetGroupBy(struct qemu_syscall *call);
void qemu_FolderView2_SetGroupSubsetCount(struct qemu_syscall *call);
void qemu_FolderView2_SetRedraw(struct qemu_syscall *call);
void qemu_FolderView2_SetSortColumns(struct qemu_syscall *call);
void qemu_FolderView2_SetText(struct qemu_syscall *call);
void qemu_FolderView2_SetTileViewProperties(struct qemu_syscall *call);
void qemu_FolderView2_SetViewModeAndIconSize(struct qemu_syscall *call);
void qemu_FolderView2_SetViewProperty(struct qemu_syscall *call);
void qemu_FolderView_AddRef(struct qemu_syscall *call);
void qemu_FolderView_GetAutoArrange(struct qemu_syscall *call);
void qemu_FolderView_GetCurrentViewMode(struct qemu_syscall *call);
void qemu_FolderView_GetDefaultSpacing(struct qemu_syscall *call);
void qemu_FolderView_GetFocusedItem(struct qemu_syscall *call);
void qemu_FolderView_GetFolder(struct qemu_syscall *call);
void qemu_FolderView_GetItemPosition(struct qemu_syscall *call);
void qemu_FolderView_GetSelectionMarkedItem(struct qemu_syscall *call);
void qemu_FolderView_GetSpacing(struct qemu_syscall *call);
void qemu_FolderView_Item(struct qemu_syscall *call);
void qemu_FolderView_ItemCount(struct qemu_syscall *call);
void qemu_FolderView_Items(struct qemu_syscall *call);
void qemu_FolderView_QueryInterface(struct qemu_syscall *call);
void qemu_FolderView_Release(struct qemu_syscall *call);
void qemu_FolderView_SelectAndPositionItems(struct qemu_syscall *call);
void qemu_FolderView_SelectItem(struct qemu_syscall *call);
void qemu_FolderView_SetCurrentViewMode(struct qemu_syscall *call);
void qemu_FreeIconList(struct qemu_syscall *call);
void qemu_GUIDFromStringW(struct qemu_syscall *call);
void qemu_GetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_GetFileNameFromBrowse(struct qemu_syscall *call);
void qemu_IEnumIDList_AddRef(struct qemu_syscall *call);
void qemu_IEnumIDList_Clone(struct qemu_syscall *call);
void qemu_IEnumIDList_Next(struct qemu_syscall *call);
void qemu_IEnumIDList_QueryInterface(struct qemu_syscall *call);
void qemu_IEnumIDList_Release(struct qemu_syscall *call);
void qemu_IEnumIDList_Reset(struct qemu_syscall *call);
void qemu_IEnumIDList_Skip(struct qemu_syscall *call);
void qemu_ILAppendID(struct qemu_syscall *call);
void qemu_ILClone(struct qemu_syscall *call);
void qemu_ILCloneFirst(struct qemu_syscall *call);
void qemu_ILCombine(struct qemu_syscall *call);
void qemu_ILCreateFromPathA(struct qemu_syscall *call);
void qemu_ILCreateFromPathAW(struct qemu_syscall *call);
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
void qemu_IPersistFolder3_GetClassID(struct qemu_syscall *call);
void qemu_IPersistFolder3_GetCurFolder(struct qemu_syscall *call);
void qemu_IPersistFolder3_GetFolderTargetInfo(struct qemu_syscall *call);
void qemu_IPersistFolder3_Initialize(struct qemu_syscall *call);
void qemu_IPersistFolder3_InitializeEx(struct qemu_syscall *call);
void qemu_ISVDropSource_AddRef(struct qemu_syscall *call);
void qemu_ISVDropSource_GiveFeedback(struct qemu_syscall *call);
void qemu_ISVDropSource_QueryContinueDrag(struct qemu_syscall *call);
void qemu_ISVDropSource_QueryInterface(struct qemu_syscall *call);
void qemu_ISVDropSource_Release(struct qemu_syscall *call);
void qemu_ISVDropTarget_AddRef(struct qemu_syscall *call);
void qemu_ISVDropTarget_DragEnter(struct qemu_syscall *call);
void qemu_ISVDropTarget_DragLeave(struct qemu_syscall *call);
void qemu_ISVDropTarget_DragOver(struct qemu_syscall *call);
void qemu_ISVDropTarget_Drop(struct qemu_syscall *call);
void qemu_ISVDropTarget_QueryInterface(struct qemu_syscall *call);
void qemu_ISVDropTarget_Release(struct qemu_syscall *call);
void qemu_ISVOleCmdTarget_AddRef(struct qemu_syscall *call);
void qemu_ISVOleCmdTarget_Exec(struct qemu_syscall *call);
void qemu_ISVOleCmdTarget_QueryInterface(struct qemu_syscall *call);
void qemu_ISVOleCmdTarget_QueryStatus(struct qemu_syscall *call);
void qemu_ISVOleCmdTarget_Release(struct qemu_syscall *call);
void qemu_ISVViewObject_AddRef(struct qemu_syscall *call);
void qemu_ISVViewObject_Draw(struct qemu_syscall *call);
void qemu_ISVViewObject_Freeze(struct qemu_syscall *call);
void qemu_ISVViewObject_GetAdvise(struct qemu_syscall *call);
void qemu_ISVViewObject_GetColorSet(struct qemu_syscall *call);
void qemu_ISVViewObject_QueryInterface(struct qemu_syscall *call);
void qemu_ISVViewObject_Release(struct qemu_syscall *call);
void qemu_ISVViewObject_SetAdvise(struct qemu_syscall *call);
void qemu_ISVViewObject_Unfreeze(struct qemu_syscall *call);
void qemu_IShellFolder2_AddRef(struct qemu_syscall *call);
void qemu_IShellFolder2_BindToObject(struct qemu_syscall *call);
void qemu_IShellFolder2_BindToStorage(struct qemu_syscall *call);
void qemu_IShellFolder2_CompareIDs(struct qemu_syscall *call);
void qemu_IShellFolder2_CreateViewObject(struct qemu_syscall *call);
void qemu_IShellFolder2_EnumObjects(struct qemu_syscall *call);
void qemu_IShellFolder2_EnumSearches(struct qemu_syscall *call);
void qemu_IShellFolder2_GetAttributesOf(struct qemu_syscall *call);
void qemu_IShellFolder2_GetDefaultColumn(struct qemu_syscall *call);
void qemu_IShellFolder2_GetDefaultColumnState(struct qemu_syscall *call);
void qemu_IShellFolder2_GetDefaultSearchGUID(struct qemu_syscall *call);
void qemu_IShellFolder2_GetDetailsEx(struct qemu_syscall *call);
void qemu_IShellFolder2_GetDetailsOf(struct qemu_syscall *call);
void qemu_IShellFolder2_GetDisplayNameOf(struct qemu_syscall *call);
void qemu_IShellFolder2_GetUIObjectOf(struct qemu_syscall *call);
void qemu_IShellFolder2_MapColumnToSCID(struct qemu_syscall *call);
void qemu_IShellFolder2_ParseDisplayName(struct qemu_syscall *call);
void qemu_IShellFolder2_QueryInterface(struct qemu_syscall *call);
void qemu_IShellFolder2_Release(struct qemu_syscall *call);
void qemu_IShellFolder2_SetNameOf(struct qemu_syscall *call);
void qemu_IShellFolderView_AddObject(struct qemu_syscall *call);
void qemu_IShellFolderView_AddRef(struct qemu_syscall *call);
void qemu_IShellFolderView_ArrangeGrid(struct qemu_syscall *call);
void qemu_IShellFolderView_AutoArrange(struct qemu_syscall *call);
void qemu_IShellFolderView_GetArrangeParam(struct qemu_syscall *call);
void qemu_IShellFolderView_GetAutoArrange(struct qemu_syscall *call);
void qemu_IShellFolderView_GetDragPoint(struct qemu_syscall *call);
void qemu_IShellFolderView_GetDropPoint(struct qemu_syscall *call);
void qemu_IShellFolderView_GetItemSpacing(struct qemu_syscall *call);
void qemu_IShellFolderView_GetObject(struct qemu_syscall *call);
void qemu_IShellFolderView_GetObjectCount(struct qemu_syscall *call);
void qemu_IShellFolderView_GetSelectedCount(struct qemu_syscall *call);
void qemu_IShellFolderView_GetSelectedObjects(struct qemu_syscall *call);
void qemu_IShellFolderView_IsBkDropTarget(struct qemu_syscall *call);
void qemu_IShellFolderView_IsDropOnSource(struct qemu_syscall *call);
void qemu_IShellFolderView_MoveIcons(struct qemu_syscall *call);
void qemu_IShellFolderView_QueryInterface(struct qemu_syscall *call);
void qemu_IShellFolderView_QuerySupport(struct qemu_syscall *call);
void qemu_IShellFolderView_Rearrange(struct qemu_syscall *call);
void qemu_IShellFolderView_RefreshObject(struct qemu_syscall *call);
void qemu_IShellFolderView_Release(struct qemu_syscall *call);
void qemu_IShellFolderView_RemoveObject(struct qemu_syscall *call);
void qemu_IShellFolderView_Select(struct qemu_syscall *call);
void qemu_IShellFolderView_SetAutomationObject(struct qemu_syscall *call);
void qemu_IShellFolderView_SetCallback(struct qemu_syscall *call);
void qemu_IShellFolderView_SetClipboard(struct qemu_syscall *call);
void qemu_IShellFolderView_SetItemPos(struct qemu_syscall *call);
void qemu_IShellFolderView_SetObjectCount(struct qemu_syscall *call);
void qemu_IShellFolderView_SetPoints(struct qemu_syscall *call);
void qemu_IShellFolderView_SetRedraw(struct qemu_syscall *call);
void qemu_IShellFolderView_UpdateObject(struct qemu_syscall *call);
void qemu_IShellView2_CreateViewWindow2(struct qemu_syscall *call);
void qemu_IShellView2_GetView(struct qemu_syscall *call);
void qemu_IShellView2_HandleRename(struct qemu_syscall *call);
void qemu_IShellView2_SelectAndPositionItem(struct qemu_syscall *call);
void qemu_IShellView3_CreateViewWindow3(struct qemu_syscall *call);
void qemu_IShellView_AddPropertySheetPages(struct qemu_syscall *call);
void qemu_IShellView_AddRef(struct qemu_syscall *call);
void qemu_IShellView_ContextSensitiveHelp(struct qemu_syscall *call);
void qemu_IShellView_CreateViewWindow(struct qemu_syscall *call);
void qemu_IShellView_DestroyViewWindow(struct qemu_syscall *call);
void qemu_IShellView_EnableModeless(struct qemu_syscall *call);
void qemu_IShellView_GetCurrentInfo(struct qemu_syscall *call);
void qemu_IShellView_GetItemObject(struct qemu_syscall *call);
void qemu_IShellView_GetWindow(struct qemu_syscall *call);
void qemu_IShellView_QueryInterface(struct qemu_syscall *call);
void qemu_IShellView_Refresh(struct qemu_syscall *call);
void qemu_IShellView_Release(struct qemu_syscall *call);
void qemu_IShellView_SaveViewState(struct qemu_syscall *call);
void qemu_IShellView_SelectItem(struct qemu_syscall *call);
void qemu_IShellView_TranslateAccelerator(struct qemu_syscall *call);
void qemu_IShellView_UIActivate(struct qemu_syscall *call);
void qemu_InitNetworkAddressControl(struct qemu_syscall *call);
void qemu_InvalidateDriveType(struct qemu_syscall *call);
void qemu_IsLFNDriveA(struct qemu_syscall *call);
void qemu_IsLFNDriveAW(struct qemu_syscall *call);
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
void qemu_PathAddBackslashAW(struct qemu_syscall *call);
void qemu_PathAppendAW(struct qemu_syscall *call);
void qemu_PathBuildRootAW(struct qemu_syscall *call);
void qemu_PathCleanupSpec(struct qemu_syscall *call);
void qemu_PathCombineAW(struct qemu_syscall *call);
void qemu_PathFileExistsAW(struct qemu_syscall *call);
void qemu_PathFindExtensionAW(struct qemu_syscall *call);
void qemu_PathFindFileNameAW(struct qemu_syscall *call);
void qemu_PathFindOnPathAW(struct qemu_syscall *call);
void qemu_PathGetArgsAW(struct qemu_syscall *call);
void qemu_PathGetDriveNumberAW(struct qemu_syscall *call);
void qemu_PathGetExtensionAW(struct qemu_syscall *call);
void qemu_PathGetShortPathAW(struct qemu_syscall *call);
void qemu_PathIsDirectoryAW(struct qemu_syscall *call);
void qemu_PathIsExeAW(struct qemu_syscall *call);
void qemu_PathIsRelativeAW(struct qemu_syscall *call);
void qemu_PathIsRootAW(struct qemu_syscall *call);
void qemu_PathIsSameRootAW(struct qemu_syscall *call);
void qemu_PathIsUNCAW(struct qemu_syscall *call);
void qemu_PathMakeUniqueNameAW(struct qemu_syscall *call);
void qemu_PathMatchSpecAW(struct qemu_syscall *call);
void qemu_PathParseIconLocationAW(struct qemu_syscall *call);
void qemu_PathProcessCommandAW(struct qemu_syscall *call);
void qemu_PathQualifyAW(struct qemu_syscall *call);
void qemu_PathQuoteSpacesAW(struct qemu_syscall *call);
void qemu_PathRemoveArgsAW(struct qemu_syscall *call);
void qemu_PathRemoveBlanksAW(struct qemu_syscall *call);
void qemu_PathRemoveExtensionAW(struct qemu_syscall *call);
void qemu_PathRemoveFileSpecAW(struct qemu_syscall *call);
void qemu_PathResolveAW(struct qemu_syscall *call);
void qemu_PathSetDlgItemPathAW(struct qemu_syscall *call);
void qemu_PathStripPathAW(struct qemu_syscall *call);
void qemu_PathStripToRootAW(struct qemu_syscall *call);
void qemu_PathUnquoteSpacesAW(struct qemu_syscall *call);
void qemu_PathYetAnotherMakeUniqueName(struct qemu_syscall *call);
void qemu_PersistPropertyBag_GetClassID(struct qemu_syscall *call);
void qemu_PersistPropertyBag_InitNew(struct qemu_syscall *call);
void qemu_PersistPropertyBag_Load(struct qemu_syscall *call);
void qemu_PersistPropertyBag_Save(struct qemu_syscall *call);
void qemu_PickIconDlg(struct qemu_syscall *call);
void qemu_Printer_LoadIconsW(struct qemu_syscall *call);
void qemu_Printers_RegisterWindowW(struct qemu_syscall *call);
void qemu_Printers_UnregisterWindow(struct qemu_syscall *call);
void qemu_RLBuildListOfPaths(struct qemu_syscall *call);
void qemu_ReadCabinetState(struct qemu_syscall *call);
void qemu_RealDriveType(struct qemu_syscall *call);
void qemu_RegenerateUserEnvironment(struct qemu_syscall *call);
void qemu_RegisterShellHook(struct qemu_syscall *call);
void qemu_RestartDialog(struct qemu_syscall *call);
void qemu_RestartDialogEx(struct qemu_syscall *call);
void qemu_RunFileDlgAW(struct qemu_syscall *call);
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
void qemu_SHCLSIDFromString(struct qemu_syscall *call);
void qemu_SHChangeNotification_Lock(struct qemu_syscall *call);
void qemu_SHChangeNotification_Unlock(struct qemu_syscall *call);
void qemu_SHChangeNotify(struct qemu_syscall *call);
void qemu_SHChangeNotifyDeregister(struct qemu_syscall *call);
void qemu_SHChangeNotifyRegister(struct qemu_syscall *call);
void qemu_SHChangeNotifyUpdateEntryList(struct qemu_syscall *call);
void qemu_SHCloneSpecialIDList(struct qemu_syscall *call);
void qemu_SHCoCreateInstance(struct qemu_syscall *call);
void qemu_SHCreateDefClassObject(struct qemu_syscall *call);
void qemu_SHCreateDefaultContextMenu(struct qemu_syscall *call);
void qemu_SHCreateDirectory(struct qemu_syscall *call);
void qemu_SHCreateDirectoryExA(struct qemu_syscall *call);
void qemu_SHCreateDirectoryExW(struct qemu_syscall *call);
void qemu_SHCreateFileExtractIconW(struct qemu_syscall *call);
void qemu_SHCreateItemFromIDList(struct qemu_syscall *call);
void qemu_SHCreateItemFromParsingName(struct qemu_syscall *call);
void qemu_SHCreateItemFromRelativeName(struct qemu_syscall *call);
void qemu_SHCreateItemInKnownFolder(struct qemu_syscall *call);
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
void qemu_SHEmptyRecycleBinA(struct qemu_syscall *call);
void qemu_SHEmptyRecycleBinW(struct qemu_syscall *call);
void qemu_SHEnumerateUnreadMailAccountsW(struct qemu_syscall *call);
void qemu_SHFileOperationA(struct qemu_syscall *call);
void qemu_SHFileOperationW(struct qemu_syscall *call);
void qemu_SHFindFiles(struct qemu_syscall *call);
void qemu_SHFind_InitMenuPopup(struct qemu_syscall *call);
void qemu_SHFlushClipboard(struct qemu_syscall *call);
void qemu_SHFlushSFCache(struct qemu_syscall *call);
void qemu_SHFormatDrive(struct qemu_syscall *call);
void qemu_SHFree(struct qemu_syscall *call);
void qemu_SHFreeNameMappings(struct qemu_syscall *call);
void qemu_SHFreeShared(struct qemu_syscall *call);
void qemu_SHFreeUnusedLibraries(struct qemu_syscall *call);
void qemu_SHGetDataFromIDListA(struct qemu_syscall *call);
void qemu_SHGetDataFromIDListW(struct qemu_syscall *call);
void qemu_SHGetDesktopFolder(struct qemu_syscall *call);
void qemu_SHGetFileInfoA(struct qemu_syscall *call);
void qemu_SHGetFileInfoW(struct qemu_syscall *call);
void qemu_SHGetFolderLocation(struct qemu_syscall *call);
void qemu_SHGetFolderPathA(struct qemu_syscall *call);
void qemu_SHGetFolderPathAndSubDirA(struct qemu_syscall *call);
void qemu_SHGetFolderPathAndSubDirW(struct qemu_syscall *call);
void qemu_SHGetFolderPathEx(struct qemu_syscall *call);
void qemu_SHGetFolderPathW(struct qemu_syscall *call);
void qemu_SHGetIDListFromObject(struct qemu_syscall *call);
void qemu_SHGetIconOverlayIndexA(struct qemu_syscall *call);
void qemu_SHGetIconOverlayIndexW(struct qemu_syscall *call);
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
void qemu_SHRegOpenKeyA(struct qemu_syscall *call);
void qemu_SHRegOpenKeyW(struct qemu_syscall *call);
void qemu_SHRegQueryValueA(struct qemu_syscall *call);
void qemu_SHRegQueryValueExA(struct qemu_syscall *call);
void qemu_SHRegQueryValueExW(struct qemu_syscall *call);
void qemu_SHRegQueryValueW(struct qemu_syscall *call);
void qemu_SHRegisterDragDrop(struct qemu_syscall *call);
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
void qemu_SetAppStartingCursor(struct qemu_syscall *call);
void qemu_SetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call);
void qemu_SheChangeDirA(struct qemu_syscall *call);
void qemu_SheChangeDirW(struct qemu_syscall *call);
void qemu_SheGetDirA(struct qemu_syscall *call);
void qemu_SheGetDirW(struct qemu_syscall *call);
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
void qemu_Shell_GetCachedImageIndexAW(struct qemu_syscall *call);
void qemu_Shell_GetImageLists(struct qemu_syscall *call);
void qemu_Shell_MergeMenus(struct qemu_syscall *call);
void qemu_Shell_NotifyIconA(struct qemu_syscall *call);
void qemu_Shell_NotifyIconW(struct qemu_syscall *call);
void qemu_SignalFileOpen(struct qemu_syscall *call);
void qemu_StrRetToStrNA(struct qemu_syscall *call);
void qemu_StrRetToStrNAW(struct qemu_syscall *call);
void qemu_StrRetToStrNW(struct qemu_syscall *call);
void qemu_StrToOleStrAW(struct qemu_syscall *call);
void qemu_StrToOleStrNAW(struct qemu_syscall *call);
void qemu_WOWShellExecute(struct qemu_syscall *call);
void qemu_Win32CreateDirectory(struct qemu_syscall *call);
void qemu_Win32DeleteFile(struct qemu_syscall *call);
void qemu_Win32RemoveDirectory(struct qemu_syscall *call);
void qemu_WriteCabinetState(struct qemu_syscall *call);
void qemu_cf_AddRef(struct qemu_syscall *call);
void qemu_cf_CreateInstance(struct qemu_syscall *call);
void qemu_cf_LockServer(struct qemu_syscall *call);
void qemu_cf_QueryInterface(struct qemu_syscall *call);
void qemu_cf_Release(struct qemu_syscall *call);
void qemu_shell32_243(struct qemu_syscall *call);
void qemu_shellfolderviewdual_AddRef(struct qemu_syscall *call);
void qemu_shellfolderviewdual_FilterView(struct qemu_syscall *call);
void qemu_shellfolderviewdual_GetIDsOfNames(struct qemu_syscall *call);
void qemu_shellfolderviewdual_GetTypeInfo(struct qemu_syscall *call);
void qemu_shellfolderviewdual_GetTypeInfoCount(struct qemu_syscall *call);
void qemu_shellfolderviewdual_Invoke(struct qemu_syscall *call);
void qemu_shellfolderviewdual_PopupItemMenu(struct qemu_syscall *call);
void qemu_shellfolderviewdual_QueryInterface(struct qemu_syscall *call);
void qemu_shellfolderviewdual_Release(struct qemu_syscall *call);
void qemu_shellfolderviewdual_SelectItem(struct qemu_syscall *call);
void qemu_shellfolderviewdual_SelectItemRelative(struct qemu_syscall *call);
void qemu_shellfolderviewdual_SelectedItems(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_Application(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_CurrentViewMode(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_FocusedItem(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_Folder(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_FolderFlags(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_GroupBy(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_IconSize(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_Parent(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_Script(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_SortColumns(struct qemu_syscall *call);
void qemu_shellfolderviewdual_get_ViewOptions(struct qemu_syscall *call);
void qemu_shellfolderviewdual_put_CurrentViewMode(struct qemu_syscall *call);
void qemu_shellfolderviewdual_put_FolderFlags(struct qemu_syscall *call);
void qemu_shellfolderviewdual_put_GroupBy(struct qemu_syscall *call);
void qemu_shellfolderviewdual_put_IconSize(struct qemu_syscall *call);
void qemu_shellfolderviewdual_put_SortColumns(struct qemu_syscall *call);

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
BOOL (* WINAPI p_PathAppend)(LPVOID lpszPath1, LPCVOID lpszPath2);
LPVOID (* WINAPI p_PathCombine)(LPVOID szDest, LPCVOID lpszDir, LPCVOID lpszFile);
LPVOID (* WINAPI p_PathFindFileName)(LPCVOID lpszPath);
LPVOID (* WINAPI p_PathFindExtension)(LPCVOID lpszPath);
LPVOID (* WINAPI p_PathGetArgs)(LPVOID lpszPath);
int (* WINAPI p_PathGetDriveNumber)(LPVOID lpszPath);
BOOL (* WINAPI p_PathStripToRoot)(LPVOID lpszPath);
void (* WINAPI p_PathRemoveArgs)(LPVOID lpszPath);
void (* WINAPI p_PathRemoveBlanks)(LPVOID str);
VOID (* WINAPI p_PathQuoteSpaces)(LPVOID lpszPath);
VOID (* WINAPI p_PathUnquoteSpaces)(LPVOID str);
int (* WINAPI p_PathParseIconLocation)(LPVOID lpszPath);
BOOL (* WINAPI p_PathIsRelative)(LPCVOID lpszPath);
BOOL (* WINAPI p_PathIsRoot)(LPCVOID lpszPath);
BOOL (* WINAPI p_PathIsDirectory)(LPCVOID lpszPath);
BOOL (* WINAPI p_PathFileExists)(LPCVOID lpszPath);
BOOL (* WINAPI p_PathIsSameRoot)(LPCVOID lpszPath1, LPCVOID lpszPath2);
BOOL (* WINAPI p_PathFindOnPath)(LPVOID sFile, LPCVOID *sOtherDirs);
BOOL (* WINAPI p_PathResolve)(LPVOID path, LPCVOID *paths, DWORD flags);
LONG (* WINAPI p_PathProcessCommand)(LPCVOID lpszPath, LPVOID lpszBuff, DWORD dwBuffSize, DWORD dwFlags);
VOID (* WINAPI p_PathSetDlgItemPath)(HWND hDlg, int id, LPCVOID pszPath);
LPVOID (* WINAPI p_PathBuildRoot)(LPVOID lpszPath, int drive);
LPVOID (* WINAPI p_PathAddBackslash)(LPVOID lpszPath);
BOOL (* WINAPI p_PathIsUNC)(LPCVOID lpszPath);
BOOL (* WINAPI p_PathMatchSpec)(LPVOID name, LPVOID mask);
void (* WINAPI p_PathRemoveExtension)(LPVOID lpszPath);
BOOL (* WINAPI p_PathRemoveFileSpec)(LPVOID lpszPath);
void (* WINAPI p_PathStripPath)(LPVOID lpszPath);

struct qemu_shellfolder *qemu_shellfolder_host_create(IShellFolder2 *host);
struct qemu_enumidlist *qemu_enumidlist_host_create(IEnumIDList *host);
struct qemu_shellview *qemu_shellview_host_create(IShellView3 *host);

void shellbrowser_wrapper_wrapper_set_funcs(const struct shellbrowser_funcs *funcs);
struct shellbrowser_wrapper *shellbrowser_wrapper_create(uint64_t guest_iface, struct qemu_shellview *shellview);
uint64_t shellbrowser_wrapper_guest_iface(struct shellbrowser_wrapper *wrapper);
IShellBrowser * shellbrowser_wrapper_host_iface(struct shellbrowser_wrapper *wrapper);

#endif

#endif
