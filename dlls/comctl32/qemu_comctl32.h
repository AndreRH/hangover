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
    CALL_DPA_CLONE,
    CALL_DPA_CREATE,
    CALL_DPA_CREATEEX,
    CALL_DPA_DELETEALLPTRS,
    CALL_DPA_DELETEPTR,
    CALL_DPA_DESTROY,
    CALL_DPA_DESTROYCALLBACK,
    CALL_DPA_ENUMCALLBACK,
    CALL_DPA_GETPTR,
    CALL_DPA_GETPTRINDEX,
    CALL_DPA_GETSIZE,
    CALL_DPA_GROW,
    CALL_DPA_INSERTPTR,
    CALL_DPA_LOADSTREAM,
    CALL_DPA_MERGE,
    CALL_DPA_SAVESTREAM,
    CALL_DPA_SEARCH,
    CALL_DPA_SETPTR,
    CALL_DPA_SORT,
    CALL_DRAWINSERT,
    CALL_DRAWSHADOWTEXT,
    CALL_DRAWSTATUSTEXTA,
    CALL_DRAWSTATUSTEXTW,
    CALL_DSA_CLONE,
    CALL_DSA_CREATE,
    CALL_DSA_DELETEALLITEMS,
    CALL_DSA_DELETEITEM,
    CALL_DSA_DESTROY,
    CALL_DSA_DESTROYCALLBACK,
    CALL_DSA_ENUMCALLBACK,
    CALL_DSA_GETITEM,
    CALL_DSA_GETITEMPTR,
    CALL_DSA_GETSIZE,
    CALL_DSA_INSERTITEM,
    CALL_DSA_SETITEM,
    CALL_ENUMMRULISTA,
    CALL_ENUMMRULISTW,
    CALL_FINDMRUDATA,
    CALL_FINDMRUSTRINGA,
    CALL_FINDMRUSTRINGW,
    CALL_FLATSB_ENABLESCROLLBAR,
    CALL_FLATSB_GETSCROLLINFO,
    CALL_FLATSB_GETSCROLLPOS,
    CALL_FLATSB_GETSCROLLPROP,
    CALL_FLATSB_GETSCROLLRANGE,
    CALL_FLATSB_SETSCROLLINFO,
    CALL_FLATSB_SETSCROLLPOS,
    CALL_FLATSB_SETSCROLLPROP,
    CALL_FLATSB_SETSCROLLRANGE,
    CALL_FLATSB_SHOWSCROLLBAR,
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
    CALL_INITIALIZEFLATSB,
    CALL_INITMUILANGUAGE,
    CALL_INTLSTREQWORKERA,
    CALL_INTLSTREQWORKERW,
    CALL_LBITEMFROMPT,
    CALL_LOADICONMETRIC,
    CALL_LOADICONWITHSCALEDOWN,
    CALL_MAKEDRAGLIST,
    CALL_MENUHELP,
    CALL_MIRRORICON,
    CALL_PROPERTYSHEETA,
    CALL_PROPERTYSHEETW,
    CALL_REALLOC,
    CALL_REMOVEWINDOWSUBCLASS,
    CALL_SENDNOTIFY,
    CALL_SENDNOTIFYEX,
    CALL_SET_CALLBACKS,
    CALL_SETPATHWORDBREAKPROC,
    CALL_SETWINDOWSUBCLASS,
    CALL_SHOWHIDEMENUCTL,
    CALL_SMOOTHSCROLLWINDOW,
    CALL_STR_GETPTRA,
    CALL_STR_GETPTRW,
    CALL_STR_SETPTRA,
    CALL_STR_SETPTRW,
    CALL_STRCHRA,
    CALL_STRCHRIA,
    CALL_STRCHRIW,
    CALL_STRCHRW,
    CALL_STRCMPNA,
    CALL_STRCMPNIA,
    CALL_STRCMPNIW,
    CALL_STRCMPNW,
    CALL_STRCSPNA,
    CALL_STRCSPNIA,
    CALL_STRCSPNIW,
    CALL_STRCSPNW,
    CALL_STRRCHRA,
    CALL_STRRCHRIA,
    CALL_STRRCHRIW,
    CALL_STRRCHRW,
    CALL_STRRSTRIA,
    CALL_STRRSTRIW,
    CALL_STRSTRA,
    CALL_STRSTRIA,
    CALL_STRSTRIW,
    CALL_STRSTRW,
    CALL_STRTOINTA,
    CALL_STRTOINTW,
    CALL_TASKDIALOG,
    CALL_TASKDIALOGINDIRECT,
    CALL_UNINITIALIZEFLATSB,
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
void qemu_DPA_Clone(struct qemu_syscall *call);
void qemu_DPA_Create(struct qemu_syscall *call);
void qemu_DPA_CreateEx(struct qemu_syscall *call);
void qemu_DPA_DeleteAllPtrs(struct qemu_syscall *call);
void qemu_DPA_DeletePtr(struct qemu_syscall *call);
void qemu_DPA_Destroy(struct qemu_syscall *call);
void qemu_DPA_DestroyCallback(struct qemu_syscall *call);
void qemu_DPA_EnumCallback(struct qemu_syscall *call);
void qemu_DPA_GetPtr(struct qemu_syscall *call);
void qemu_DPA_GetPtrIndex(struct qemu_syscall *call);
void qemu_DPA_GetSize(struct qemu_syscall *call);
void qemu_DPA_Grow(struct qemu_syscall *call);
void qemu_DPA_InsertPtr(struct qemu_syscall *call);
void qemu_DPA_LoadStream(struct qemu_syscall *call);
void qemu_DPA_Merge(struct qemu_syscall *call);
void qemu_DPA_SaveStream(struct qemu_syscall *call);
void qemu_DPA_Search(struct qemu_syscall *call);
void qemu_DPA_SetPtr(struct qemu_syscall *call);
void qemu_DPA_Sort(struct qemu_syscall *call);
void qemu_DrawInsert(struct qemu_syscall *call);
void qemu_DrawShadowText(struct qemu_syscall *call);
void qemu_DrawStatusTextA(struct qemu_syscall *call);
void qemu_DrawStatusTextW(struct qemu_syscall *call);
void qemu_DSA_Clone(struct qemu_syscall *call);
void qemu_DSA_Create(struct qemu_syscall *call);
void qemu_DSA_DeleteAllItems(struct qemu_syscall *call);
void qemu_DSA_DeleteItem(struct qemu_syscall *call);
void qemu_DSA_Destroy(struct qemu_syscall *call);
void qemu_DSA_DestroyCallback(struct qemu_syscall *call);
void qemu_DSA_EnumCallback(struct qemu_syscall *call);
void qemu_DSA_GetItem(struct qemu_syscall *call);
void qemu_DSA_GetItemPtr(struct qemu_syscall *call);
void qemu_DSA_GetSize(struct qemu_syscall *call);
void qemu_DSA_InsertItem(struct qemu_syscall *call);
void qemu_DSA_SetItem(struct qemu_syscall *call);
void qemu_EnumMRUListA(struct qemu_syscall *call);
void qemu_EnumMRUListW(struct qemu_syscall *call);
void qemu_FindMRUData(struct qemu_syscall *call);
void qemu_FindMRUStringA(struct qemu_syscall *call);
void qemu_FindMRUStringW(struct qemu_syscall *call);
void qemu_FlatSB_EnableScrollBar(struct qemu_syscall *call);
void qemu_FlatSB_GetScrollInfo(struct qemu_syscall *call);
void qemu_FlatSB_GetScrollPos(struct qemu_syscall *call);
void qemu_FlatSB_GetScrollProp(struct qemu_syscall *call);
void qemu_FlatSB_GetScrollRange(struct qemu_syscall *call);
void qemu_FlatSB_SetScrollInfo(struct qemu_syscall *call);
void qemu_FlatSB_SetScrollPos(struct qemu_syscall *call);
void qemu_FlatSB_SetScrollProp(struct qemu_syscall *call);
void qemu_FlatSB_SetScrollRange(struct qemu_syscall *call);
void qemu_FlatSB_ShowScrollBar(struct qemu_syscall *call);
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
void qemu_InitializeFlatSB(struct qemu_syscall *call);
void qemu_InitMUILanguage(struct qemu_syscall *call);
void qemu_IntlStrEqWorkerA(struct qemu_syscall *call);
void qemu_IntlStrEqWorkerW(struct qemu_syscall *call);
void qemu_LBItemFromPt(struct qemu_syscall *call);
void qemu_LoadIconMetric(struct qemu_syscall *call);
void qemu_LoadIconWithScaleDown(struct qemu_syscall *call);
void qemu_MakeDragList(struct qemu_syscall *call);
void qemu_MenuHelp(struct qemu_syscall *call);
void qemu_MirrorIcon(struct qemu_syscall *call);
void qemu_PropertySheet(struct qemu_syscall *call);
void qemu_ReAlloc(struct qemu_syscall *call);
void qemu_RemoveWindowSubclass(struct qemu_syscall *call);
void qemu_SendNotify(struct qemu_syscall *call);
void qemu_SendNotifyEx(struct qemu_syscall *call);
void qemu_SetPathWordBreakProc(struct qemu_syscall *call);
void qemu_SetWindowSubclass(struct qemu_syscall *call);
void qemu_ShowHideMenuCtl(struct qemu_syscall *call);
void qemu_SmoothScrollWindow(struct qemu_syscall *call);
void qemu_Str_GetPtrA(struct qemu_syscall *call);
void qemu_Str_GetPtrW(struct qemu_syscall *call);
void qemu_Str_SetPtrA(struct qemu_syscall *call);
void qemu_Str_SetPtrW(struct qemu_syscall *call);
void qemu_StrChrA(struct qemu_syscall *call);
void qemu_StrChrIA(struct qemu_syscall *call);
void qemu_StrChrIW(struct qemu_syscall *call);
void qemu_StrChrW(struct qemu_syscall *call);
void qemu_StrCmpNA(struct qemu_syscall *call);
void qemu_StrCmpNIA(struct qemu_syscall *call);
void qemu_StrCmpNIW(struct qemu_syscall *call);
void qemu_StrCmpNW(struct qemu_syscall *call);
void qemu_StrCSpnA(struct qemu_syscall *call);
void qemu_StrCSpnIA(struct qemu_syscall *call);
void qemu_StrCSpnIW(struct qemu_syscall *call);
void qemu_StrCSpnW(struct qemu_syscall *call);
void qemu_StrRChrA(struct qemu_syscall *call);
void qemu_StrRChrIA(struct qemu_syscall *call);
void qemu_StrRChrIW(struct qemu_syscall *call);
void qemu_StrRChrW(struct qemu_syscall *call);
void qemu_StrRStrIA(struct qemu_syscall *call);
void qemu_StrRStrIW(struct qemu_syscall *call);
void qemu_StrStrA(struct qemu_syscall *call);
void qemu_StrStrIA(struct qemu_syscall *call);
void qemu_StrStrIW(struct qemu_syscall *call);
void qemu_StrStrW(struct qemu_syscall *call);
void qemu_StrToIntA(struct qemu_syscall *call);
void qemu_StrToIntW(struct qemu_syscall *call);
void qemu_TaskDialog(struct qemu_syscall *call);
void qemu_TaskDialogIndirect(struct qemu_syscall *call);
void qemu_UninitializeFlatSB(struct qemu_syscall *call);

UINT (* WINAPI p_ImageList_SetColorTable)(HIMAGELIST himl, UINT uStartIndex, UINT cEntries, const RGBQUAD *prgb);
HRESULT (* WINAPI p_DllGetVersion)(void *pdvi);

struct wndproc_wrapper
{
    int32_t ldrx4;
    int32_t ldrx5;
    int32_t br;
    void *selfptr;
    void *host_proc;
    uint64_t guest_proc;
};

struct propsheet_data
{
    /* Top level callback wrapper */
    int32_t ldrx3;
    int32_t ldrx4;
    int32_t br;
    void *selfptr;
    void *host_proc;

    PROPSHEETHEADERW header;
    ULONG ref;
    uint64_t guest_cb, guest_wrapper;

    /* I need to pass this array to PropertySheetW(), so I can't interleave it with my own data. */
    PROPSHEETPAGEW *pages;

    struct page_data
    {
        uint64_t guest_lparam, guest_cb;
        struct propsheet_data *header;
    } page_data[1];

};

WNDPROC wndproc_guest_to_host(uint64_t guest_func);

#endif

#endif
