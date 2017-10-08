#ifndef COMCTL32_H
#define COMCTL32_H

#include <stdlib.h>

enum comctl32_calls
{
    CALL__TRACKMOUSEEVENT = 0,
    CALL_ADDMRUDATA,
    CALL_ADDMRUSTRINGA,
    CALL_ADDMRUSTRINGW,
    CALL_ALLOC,
    CALL_CREATEMAPPEDBITMAP,
    CALL_CREATEMRULISTA,
    CALL_CREATEMRULISTLAZYA,
    CALL_CREATEMRULISTLAZYW,
    CALL_CREATEMRULISTW,
    CALL_CREATEPROPERTYSHEETPAGEA,
    CALL_CREATEPROPERTYSHEETPAGEW,
    CALL_CREATESTATUSWINDOWA,
    CALL_CREATESTATUSWINDOWW,
    CALL_CREATETOOLBAR,
    CALL_CREATETOOLBAREX,
    CALL_CREATEUPDOWNCONTROL,
    CALL_DEFSUBCLASSPROC,
    CALL_DELMRUSTRING,
    CALL_DESTROYPROPERTYSHEETPAGE,
    CALL_DLLGETVERSION,
    CALL_DLLINSTALL,
    CALL_DRAWSHADOWTEXT,
    CALL_DRAWSTATUSTEXTA,
    CALL_DRAWSTATUSTEXTW,
    CALL_ENUMMRULISTA,
    CALL_ENUMMRULISTW,
    CALL_FINDMRUDATA,
    CALL_FINDMRUSTRINGA,
    CALL_FINDMRUSTRINGW,
    CALL_FREE,
    CALL_FREEMRULIST,
    CALL_GETEFFECTIVECLIENTRECT,
    CALL_GETMUILANGUAGE,
    CALL_GETSIZE,
    CALL_GETWINDOWSUBCLASS,
    CALL_HIMAGELIST_QUERYINTERFACE,
    CALL_IMAGELIST_ADD,
    CALL_IMAGELIST_ADDICON,
    CALL_IMAGELIST_ADDMASKED,
    CALL_IMAGELIST_BEGINDRAG,
    CALL_IMAGELIST_COCREATEINSTANCE,
    CALL_IMAGELIST_COPY,
    CALL_IMAGELIST_CREATE,
    CALL_IMAGELIST_DESTROY,
    CALL_IMAGELIST_DRAGENTER,
    CALL_IMAGELIST_DRAGLEAVE,
    CALL_IMAGELIST_DRAGMOVE,
    CALL_IMAGELIST_DRAGSHOWNOLOCK,
    CALL_IMAGELIST_DRAW,
    CALL_IMAGELIST_DRAWEX,
    CALL_IMAGELIST_DRAWINDIRECT,
    CALL_IMAGELIST_DUPLICATE,
    CALL_IMAGELIST_ENDDRAG,
    CALL_IMAGELIST_GETBKCOLOR,
    CALL_IMAGELIST_GETDRAGIMAGE,
    CALL_IMAGELIST_GETFLAGS,
    CALL_IMAGELIST_GETICON,
    CALL_IMAGELIST_GETICONSIZE,
    CALL_IMAGELIST_GETIMAGECOUNT,
    CALL_IMAGELIST_GETIMAGEINFO,
    CALL_IMAGELIST_GETIMAGERECT,
    CALL_IMAGELIST_LOADIMAGEA,
    CALL_IMAGELIST_LOADIMAGEW,
    CALL_IMAGELIST_MERGE,
    CALL_IMAGELIST_READ,
    CALL_IMAGELIST_REMOVE,
    CALL_IMAGELIST_REPLACE,
    CALL_IMAGELIST_REPLACEICON,
    CALL_IMAGELIST_SETBKCOLOR,
    CALL_IMAGELIST_SETCOLORTABLE,
    CALL_IMAGELIST_SETDRAGCURSORIMAGE,
    CALL_IMAGELIST_SETFILTER,
    CALL_IMAGELIST_SETFLAGS,
    CALL_IMAGELIST_SETICONSIZE,
    CALL_IMAGELIST_SETIMAGECOUNT,
    CALL_IMAGELIST_SETOVERLAYIMAGE,
    CALL_IMAGELIST_WRITE,
    CALL_INITCOMMONCONTROLS,
    CALL_INITCOMMONCONTROLSEX,
    CALL_INITMUILANGUAGE,
    CALL_LOADICONMETRIC,
    CALL_LOADICONWITHSCALEDOWN,
    CALL_MENUHELP,
    CALL_MIRRORICON,
    CALL_PROPERTYSHEETA,
    CALL_PROPERTYSHEETW,
    CALL_REALLOC,
    CALL_REMOVEWINDOWSUBCLASS,
    CALL_SENDNOTIFY,
    CALL_SENDNOTIFYEX,
    CALL_SETPATHWORDBREAKPROC,
    CALL_SETWINDOWSUBCLASS,
    CALL_SHOWHIDEMENUCTL,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu__TrackMouseEvent(struct qemu_syscall *call);
void qemu_AddMRUData(struct qemu_syscall *call);
void qemu_AddMRUStringA(struct qemu_syscall *call);
void qemu_AddMRUStringW(struct qemu_syscall *call);
void qemu_Alloc(struct qemu_syscall *call);
void qemu_CreateMappedBitmap(struct qemu_syscall *call);
void qemu_CreateMRUListA(struct qemu_syscall *call);
void qemu_CreateMRUListLazyA(struct qemu_syscall *call);
void qemu_CreateMRUListLazyW(struct qemu_syscall *call);
void qemu_CreateMRUListW(struct qemu_syscall *call);
void qemu_CreatePropertySheetPageA(struct qemu_syscall *call);
void qemu_CreatePropertySheetPageW(struct qemu_syscall *call);
void qemu_CreateStatusWindowA(struct qemu_syscall *call);
void qemu_CreateStatusWindowW(struct qemu_syscall *call);
void qemu_CreateToolbar(struct qemu_syscall *call);
void qemu_CreateToolbarEx(struct qemu_syscall *call);
void qemu_CreateUpDownControl(struct qemu_syscall *call);
void qemu_DefSubclassProc(struct qemu_syscall *call);
void qemu_DelMRUString(struct qemu_syscall *call);
void qemu_DestroyPropertySheetPage(struct qemu_syscall *call);
void qemu_DllGetVersion(struct qemu_syscall *call);
void qemu_DllInstall(struct qemu_syscall *call);
void qemu_DrawShadowText(struct qemu_syscall *call);
void qemu_DrawStatusTextA(struct qemu_syscall *call);
void qemu_DrawStatusTextW(struct qemu_syscall *call);
void qemu_EnumMRUListA(struct qemu_syscall *call);
void qemu_EnumMRUListW(struct qemu_syscall *call);
void qemu_FindMRUData(struct qemu_syscall *call);
void qemu_FindMRUStringA(struct qemu_syscall *call);
void qemu_FindMRUStringW(struct qemu_syscall *call);
void qemu_Free(struct qemu_syscall *call);
void qemu_FreeMRUList(struct qemu_syscall *call);
void qemu_GetEffectiveClientRect(struct qemu_syscall *call);
void qemu_GetMUILanguage(struct qemu_syscall *call);
void qemu_GetSize(struct qemu_syscall *call);
void qemu_GetWindowSubclass(struct qemu_syscall *call);
void qemu_HIMAGELIST_QueryInterface(struct qemu_syscall *call);
void qemu_ImageList_Add(struct qemu_syscall *call);
void qemu_ImageList_AddIcon(struct qemu_syscall *call);
void qemu_ImageList_AddMasked(struct qemu_syscall *call);
void qemu_ImageList_BeginDrag(struct qemu_syscall *call);
void qemu_ImageList_CoCreateInstance(struct qemu_syscall *call);
void qemu_ImageList_Copy(struct qemu_syscall *call);
void qemu_ImageList_Create(struct qemu_syscall *call);
void qemu_ImageList_Destroy(struct qemu_syscall *call);
void qemu_ImageList_DragEnter(struct qemu_syscall *call);
void qemu_ImageList_DragLeave(struct qemu_syscall *call);
void qemu_ImageList_DragMove(struct qemu_syscall *call);
void qemu_ImageList_DragShowNolock(struct qemu_syscall *call);
void qemu_ImageList_Draw(struct qemu_syscall *call);
void qemu_ImageList_DrawEx(struct qemu_syscall *call);
void qemu_ImageList_DrawIndirect(struct qemu_syscall *call);
void qemu_ImageList_Duplicate(struct qemu_syscall *call);
void qemu_ImageList_EndDrag(struct qemu_syscall *call);
void qemu_ImageList_GetBkColor(struct qemu_syscall *call);
void qemu_ImageList_GetDragImage(struct qemu_syscall *call);
void qemu_ImageList_GetFlags(struct qemu_syscall *call);
void qemu_ImageList_GetIcon(struct qemu_syscall *call);
void qemu_ImageList_GetIconSize(struct qemu_syscall *call);
void qemu_ImageList_GetImageCount(struct qemu_syscall *call);
void qemu_ImageList_GetImageInfo(struct qemu_syscall *call);
void qemu_ImageList_GetImageRect(struct qemu_syscall *call);
void qemu_ImageList_LoadImageA(struct qemu_syscall *call);
void qemu_ImageList_LoadImageW(struct qemu_syscall *call);
void qemu_ImageList_Merge(struct qemu_syscall *call);
void qemu_ImageList_Read(struct qemu_syscall *call);
void qemu_ImageList_Remove(struct qemu_syscall *call);
void qemu_ImageList_Replace(struct qemu_syscall *call);
void qemu_ImageList_ReplaceIcon(struct qemu_syscall *call);
void qemu_ImageList_SetBkColor(struct qemu_syscall *call);
void qemu_ImageList_SetColorTable(struct qemu_syscall *call);
void qemu_ImageList_SetDragCursorImage(struct qemu_syscall *call);
void qemu_ImageList_SetFilter(struct qemu_syscall *call);
void qemu_ImageList_SetFlags(struct qemu_syscall *call);
void qemu_ImageList_SetIconSize(struct qemu_syscall *call);
void qemu_ImageList_SetImageCount(struct qemu_syscall *call);
void qemu_ImageList_SetOverlayImage(struct qemu_syscall *call);
void qemu_ImageList_Write(struct qemu_syscall *call);
void qemu_InitCommonControls(struct qemu_syscall *call);
void qemu_InitCommonControlsEx(struct qemu_syscall *call);
void qemu_InitMUILanguage(struct qemu_syscall *call);
void qemu_LoadIconMetric(struct qemu_syscall *call);
void qemu_LoadIconWithScaleDown(struct qemu_syscall *call);
void qemu_MenuHelp(struct qemu_syscall *call);
void qemu_MirrorIcon(struct qemu_syscall *call);
void qemu_PropertySheetA(struct qemu_syscall *call);
void qemu_PropertySheetW(struct qemu_syscall *call);
void qemu_ReAlloc(struct qemu_syscall *call);
void qemu_RemoveWindowSubclass(struct qemu_syscall *call);
void qemu_SendNotify(struct qemu_syscall *call);
void qemu_SendNotifyEx(struct qemu_syscall *call);
void qemu_SetPathWordBreakProc(struct qemu_syscall *call);
void qemu_SetWindowSubclass(struct qemu_syscall *call);
void qemu_ShowHideMenuCtl(struct qemu_syscall *call);

UINT (* WINAPI p_ImageList_SetColorTable)(HIMAGELIST himl, UINT uStartIndex, UINT cEntries, const RGBQUAD *prgb);
HRESULT (* WINAPI p_DllGetVersion)(void *pdvi);

#endif

#endif
