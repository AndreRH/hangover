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

typedef void MRUINFOA, MRUINFOW;
typedef void SMOOTHSCROLLSTRUCT;

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
LPVOID (* WINAPI p_Alloc)(DWORD dwSize);
LPVOID (* WINAPI p_ReAlloc)(LPVOID lpSrc, DWORD dwSize);
BOOL (* WINAPI p_Free)(LPVOID lpMem);
DWORD (* WINAPI p_GetSize)(LPVOID lpMem);
void (* WINAPI p_FreeMRUList)(HANDLE hMRUList);
INT (* WINAPI p_FindMRUData)(HANDLE hList, LPCVOID lpData, DWORD cbData, LPINT lpRegNum);
INT (* WINAPI p_AddMRUData)(HANDLE hList, LPCVOID lpData, DWORD cbData);
INT (* WINAPI p_AddMRUStringW)(HANDLE hList, LPCWSTR lpszString);
INT (* WINAPI p_AddMRUStringA)(HANDLE hList, LPCSTR lpszString);
BOOL (* WINAPI p_DelMRUString)(HANDLE hList, INT nItemPos);
INT (* WINAPI p_FindMRUStringW)(HANDLE hList, LPCWSTR lpszString, LPINT lpRegNum);
INT (* WINAPI p_FindMRUStringA)(HANDLE hList, LPCSTR lpszString, LPINT lpRegNum);
HANDLE (* WINAPI p_CreateMRUListLazyW)(const MRUINFOW *infoW, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4);
HANDLE (* WINAPI p_CreateMRUListLazyA)(const MRUINFOA *lpcml, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4);
HANDLE (* WINAPI p_CreateMRUListW)(const MRUINFOW *infoW);
HANDLE (* WINAPI p_CreateMRUListA)(const MRUINFOA *lpcml);
INT (* WINAPI p_EnumMRUListW)(HANDLE hList, INT nItemPos, LPVOID lpBuffer, DWORD nBufferSize);
INT (* WINAPI p_EnumMRUListA)(HANDLE hList, INT nItemPos, LPVOID lpBuffer, DWORD nBufferSize);
LRESULT (* WINAPI p_SendNotify)(HWND hwndTo, HWND hwndFrom, UINT uCode, LPNMHDR lpHdr);
LRESULT (* WINAPI p_SendNotifyEx)(HWND hwndTo, HWND hwndFrom, UINT uCode, LPNMHDR lpHdr, DWORD dwParam5);
VOID (* WINAPI p_MenuHelp)(UINT uMsg, WPARAM wParam, LPARAM lParam, HMENU hMainMenu, HINSTANCE hInst, HWND hwndStatus, UINT* lpwIDs);
BOOL (* WINAPI p_ShowHideMenuCtl)(HWND hwnd, UINT_PTR uFlags, LPINT lpInfo);
VOID (* WINAPI p_GetEffectiveClientRect)(HWND hwnd, LPRECT lpRect, const INT *lpInfo);
void (* WINAPI p_DrawStatusTextW)(HDC hdc, LPCRECT lprc, LPCWSTR text, UINT style);
void (* WINAPI p_DrawStatusTextA)(HDC hdc, LPCRECT lprc, LPCSTR text, UINT style);
HWND (* WINAPI p_CreateStatusWindowA)(LONG style, LPCSTR text, HWND parent, UINT wid);
HWND (* WINAPI p_CreateStatusWindowW)(LONG style, LPCWSTR text, HWND parent, UINT wid);
HWND (* WINAPI p_CreateUpDownControl)(DWORD style, INT x, INT y, INT cx, INT cy, HWND parent, INT id, HINSTANCE inst, HWND buddy, INT maxVal, INT minVal, INT curVal);
VOID (* WINAPI p_InitCommonControls)(void);
BOOL (* WINAPI p_InitCommonControlsEx)(const INITCOMMONCONTROLSEX *lpInitCtrls);
HWND (* WINAPI p_CreateToolbarEx)(HWND hwnd, DWORD style, UINT wID, INT nBitmaps, HINSTANCE hBMInst, UINT_PTR wBMID, LPCTBBUTTON lpButtons, INT iNumButtons, INT dxButton, INT dyButton, INT dxBitmap, INT dyBitmap, UINT uStructSize);
HBITMAP (* WINAPI p_CreateMappedBitmap)(HINSTANCE hInstance, INT_PTR idBitmap, UINT wFlags, LPCOLORMAP lpColorMap, INT iNumMaps);
HWND (* WINAPI p_CreateToolbar)(HWND hwnd, DWORD style, UINT wID, INT nBitmaps, HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons,INT iNumButtons);
HRESULT (* WINAPI p_DllGetVersion)(void *pdvi);
HRESULT (* WINAPI p_DllInstall)(BOOL bInstall, LPCWSTR cmdline);
BOOL (* WINAPI p__TrackMouseEvent)(TRACKMOUSEEVENT *ptme);
LANGID (* WINAPI p_GetMUILanguage)(VOID);
VOID (* WINAPI p_InitMUILanguage)(LANGID uiLang);
BOOL (* WINAPI p_SetWindowSubclass)(HWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uIDSubclass, DWORD_PTR dwRef);
BOOL (* WINAPI p_GetWindowSubclass)(HWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uID, DWORD_PTR *pdwRef);
BOOL (* WINAPI p_RemoveWindowSubclass)(HWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uID);
LRESULT (* WINAPI p_DefSubclassProc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL (* WINAPI p_MirrorIcon)(HICON *phicon1, HICON *phicon2);
LRESULT (* WINAPI p_SetPathWordBreakProc)(HWND hwnd, BOOL bSet);
int (* WINAPI p_DrawShadowText)(HDC hdc, LPCWSTR text, UINT length, RECT *rect, DWORD flags, COLORREF crText, COLORREF crShadow, int offset_x, int offset_y);
HRESULT (* WINAPI p_LoadIconWithScaleDown)(HINSTANCE hinst, const WCHAR *name, int cx, int cy, HICON *icon);
HRESULT (* WINAPI p_LoadIconMetric)(HINSTANCE hinst, const WCHAR *name, int size, HICON *icon);
HRESULT (* WINAPI p_DPA_LoadStream)(HDPA *phDpa, PFNDPASTREAM loadProc, IStream *pStream, LPVOID pData);
HRESULT (* WINAPI p_DPA_SaveStream)(HDPA hDpa, PFNDPASTREAM saveProc, IStream *pStream, LPVOID pData);
BOOL (* WINAPI p_DPA_Merge)(HDPA hdpa1, HDPA hdpa2, DWORD dwFlags, PFNDPACOMPARE pfnCompare, PFNDPAMERGE pfnMerge, LPARAM lParam);
BOOL (* WINAPI p_DPA_Destroy)(HDPA hdpa);
BOOL (* WINAPI p_DPA_Grow)(HDPA hdpa, INT nGrow);
HDPA (* WINAPI p_DPA_Clone)(const HDPA hdpa, HDPA hdpaNew);
LPVOID (* WINAPI p_DPA_GetPtr)(HDPA hdpa, INT_PTR nIndex);
INT (* WINAPI p_DPA_GetPtrIndex)(HDPA hdpa, LPCVOID p);
INT (* WINAPI p_DPA_InsertPtr)(HDPA hdpa, INT i, LPVOID p);
BOOL (* WINAPI p_DPA_SetPtr)(HDPA hdpa, INT i, LPVOID p);
LPVOID (* WINAPI p_DPA_DeletePtr)(HDPA hdpa, INT i);
BOOL (* WINAPI p_DPA_DeleteAllPtrs)(HDPA hdpa);
BOOL (* WINAPI p_DPA_Sort)(HDPA hdpa, PFNDPACOMPARE pfnCompare, LPARAM lParam);
INT (* WINAPI p_DPA_Search)(HDPA hdpa, LPVOID pFind, INT nStart, PFNDPACOMPARE pfnCompare, LPARAM lParam, UINT uOptions);
HDPA (* WINAPI p_DPA_CreateEx)(INT nGrow, HANDLE hHeap);
HDPA (* WINAPI p_DPA_Create)(INT nGrow);
VOID (* WINAPI p_DPA_EnumCallback)(HDPA hdpa, PFNDPAENUMCALLBACK enumProc, LPVOID lParam);
void (* WINAPI p_DPA_DestroyCallback)(HDPA hdpa, PFNDPAENUMCALLBACK enumProc, LPVOID lParam);
ULONGLONG (* WINAPI p_DPA_GetSize)(HDPA hdpa);
BOOL (* WINAPI p_MakeDragList)(HWND hwndLB);
VOID (* WINAPI p_DrawInsert)(HWND hwndParent, HWND hwndLB, INT nItem);
INT (* WINAPI p_LBItemFromPt)(HWND hwndLB, POINT pt, BOOL bAutoScroll);
HDSA (* WINAPI p_DSA_Create)(INT nSize, INT nGrow);
BOOL (* WINAPI p_DSA_Destroy)(HDSA hdsa);
BOOL (* WINAPI p_DSA_GetItem)(HDSA hdsa, INT nIndex, LPVOID pDest);
LPVOID (* WINAPI p_DSA_GetItemPtr)(HDSA hdsa, INT nIndex);
BOOL (* WINAPI p_DSA_SetItem)(HDSA hdsa, int nIndex, const void *pSrc);
int (* WINAPI p_DSA_InsertItem)(HDSA hdsa, int nIndex, const void *pSrc);
INT (* WINAPI p_DSA_DeleteItem)(HDSA hdsa, INT nIndex);
BOOL (* WINAPI p_DSA_DeleteAllItems)(HDSA hdsa);
VOID (* WINAPI p_DSA_EnumCallback)(HDSA hdsa, PFNDSAENUMCALLBACK enumProc, LPVOID lParam);
void (* WINAPI p_DSA_DestroyCallback)(HDSA hdsa, PFNDSAENUMCALLBACK enumProc, LPVOID lParam);
HDSA (* WINAPI p_DSA_Clone)(HDSA hdsa);
ULONGLONG (* WINAPI p_DSA_GetSize)(HDSA hdsa);
BOOL (* WINAPI p_InitializeFlatSB)(HWND hwnd);
HRESULT (* WINAPI p_UninitializeFlatSB)(HWND hwnd);
BOOL (* WINAPI p_FlatSB_GetScrollProp)(HWND hwnd, INT propIndex, LPINT prop);
BOOL (* WINAPI p_FlatSB_SetScrollProp)(HWND hwnd, UINT index, INT_PTR newValue, BOOL flag);
BOOL (* WINAPI p_FlatSB_EnableScrollBar)(HWND hwnd, int nBar, UINT flags);
BOOL (* WINAPI p_FlatSB_ShowScrollBar)(HWND hwnd, int nBar, BOOL fShow);
BOOL (* WINAPI p_FlatSB_GetScrollRange)(HWND hwnd, int nBar, LPINT min, LPINT max);
BOOL (* WINAPI p_FlatSB_GetScrollInfo)(HWND hwnd, int nBar, LPSCROLLINFO info);
INT (* WINAPI p_FlatSB_GetScrollPos)(HWND hwnd, int nBar);
INT (* WINAPI p_FlatSB_SetScrollPos)(HWND hwnd, int nBar, INT pos, BOOL bRedraw);
INT (* WINAPI p_FlatSB_SetScrollInfo)(HWND hwnd, int nBar, LPSCROLLINFO info, BOOL bRedraw);
INT (* WINAPI p_FlatSB_SetScrollRange)(HWND hwnd, int nBar, INT min, INT max, BOOL bRedraw);
INT (* WINAPI p_ImageList_Add)(HIMAGELIST himl, HBITMAP hbmImage, HBITMAP hbmMask);
INT (* WINAPI p_ImageList_AddIcon)(HIMAGELIST himl, HICON hIcon);
INT (* WINAPI p_ImageList_AddMasked)(HIMAGELIST himl, HBITMAP hBitmap, COLORREF clrMask);
BOOL (* WINAPI p_ImageList_BeginDrag)(HIMAGELIST himlTrack, INT iTrack, INT dxHotspot, INT dyHotspot);
BOOL (* WINAPI p_ImageList_Copy)(HIMAGELIST himlDst, INT iDst, HIMAGELIST himlSrc, INT iSrc, UINT uFlags);
HIMAGELIST (* WINAPI p_ImageList_Create)(INT cx, INT cy, UINT flags, INT cInitial, INT cGrow);
BOOL (* WINAPI p_ImageList_Destroy)(HIMAGELIST himl);
BOOL (* WINAPI p_ImageList_DragEnter)(HWND hwndLock, INT x, INT y);
BOOL (* WINAPI p_ImageList_DragLeave)(HWND hwndLock);
BOOL (* WINAPI p_ImageList_DragMove)(INT x, INT y);
BOOL (* WINAPI p_ImageList_DragShowNolock)(BOOL bShow);
BOOL (* WINAPI p_ImageList_Draw)(HIMAGELIST himl, INT i, HDC hdc, INT x, INT y, UINT fStyle);
BOOL (* WINAPI p_ImageList_DrawEx)(HIMAGELIST himl, INT i, HDC hdc, INT x, INT y, INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle);
BOOL (* WINAPI p_ImageList_DrawIndirect)(IMAGELISTDRAWPARAMS *pimldp);
HIMAGELIST (* WINAPI p_ImageList_Duplicate)(HIMAGELIST himlSrc);
VOID (* WINAPI p_ImageList_EndDrag)(void);
COLORREF (* WINAPI p_ImageList_GetBkColor)(HIMAGELIST himl);
HIMAGELIST (* WINAPI p_ImageList_GetDragImage)(POINT *ppt, POINT *pptHotspot);
DWORD (* WINAPI p_ImageList_GetFlags)(HIMAGELIST himl);
HICON (* WINAPI p_ImageList_GetIcon)(HIMAGELIST himl, INT i, UINT fStyle);
BOOL (* WINAPI p_ImageList_GetIconSize)(HIMAGELIST himl, INT *cx, INT *cy);
INT (* WINAPI p_ImageList_GetImageCount)(HIMAGELIST himl);
BOOL (* WINAPI p_ImageList_GetImageInfo)(HIMAGELIST himl, INT i, IMAGEINFO *pImageInfo);
BOOL (* WINAPI p_ImageList_GetImageRect)(HIMAGELIST himl, INT i, LPRECT lpRect);
HIMAGELIST (* WINAPI p_ImageList_LoadImageA)(HINSTANCE hi, LPCSTR lpbmp, INT cx, INT cGrow, COLORREF clrMask, UINT uType, UINT uFlags);
HIMAGELIST (* WINAPI p_ImageList_LoadImageW)(HINSTANCE hi, LPCWSTR lpbmp, INT cx, INT cGrow, COLORREF clrMask, UINT uType, UINT uFlags);
HIMAGELIST (* WINAPI p_ImageList_Merge)(HIMAGELIST himl1, INT i1, HIMAGELIST himl2, INT i2, INT dx, INT dy);
HIMAGELIST (* WINAPI p_ImageList_Read)(IStream *pstm);
BOOL (* WINAPI p_ImageList_Remove)(HIMAGELIST himl, INT i);
BOOL (* WINAPI p_ImageList_Replace)(HIMAGELIST himl, INT i, HBITMAP hbmImage, HBITMAP hbmMask);
INT (* WINAPI p_ImageList_ReplaceIcon)(HIMAGELIST himl, INT nIndex, HICON hIcon);
COLORREF (* WINAPI p_ImageList_SetBkColor)(HIMAGELIST himl, COLORREF clrBk);
BOOL (* WINAPI p_ImageList_SetDragCursorImage)(HIMAGELIST himlDrag, INT iDrag, INT dxHotspot, INT dyHotspot);
BOOL (* WINAPI p_ImageList_SetFilter)(HIMAGELIST himl, INT i, DWORD dwFilter);
DWORD (* WINAPI p_ImageList_SetFlags)(HIMAGELIST himl, DWORD flags);
BOOL (* WINAPI p_ImageList_SetIconSize)(HIMAGELIST himl, INT cx, INT cy);
BOOL (* WINAPI p_ImageList_SetImageCount)(HIMAGELIST himl, UINT iImageCount);
BOOL (* WINAPI p_ImageList_SetOverlayImage)(HIMAGELIST himl, INT iImage, INT iOverlay);
BOOL (* WINAPI p_ImageList_Write)(HIMAGELIST himl, IStream *pstm);
HRESULT (* WINAPI p_ImageList_CoCreateInstance)(REFCLSID rclsid, const IUnknown *punkOuter, REFIID riid, void **ppv);
HRESULT (* WINAPI p_HIMAGELIST_QueryInterface)(HIMAGELIST himl, REFIID riid, void **ppv);
INT_PTR (* WINAPI p_PropertySheetA)(LPCPROPSHEETHEADERA lppsh);
INT_PTR (* WINAPI p_PropertySheetW)(LPCPROPSHEETHEADERW lppsh);
HPROPSHEETPAGE (* WINAPI p_CreatePropertySheetPageA)(LPCPROPSHEETPAGEA lpPropSheetPage);
HPROPSHEETPAGE (* WINAPI p_CreatePropertySheetPageW)(LPCPROPSHEETPAGEW lpPropSheetPage);
BOOL (* WINAPI p_DestroyPropertySheetPage)(HPROPSHEETPAGE hPropPage);
BOOL (* WINAPI p_SmoothScrollWindow)(const SMOOTHSCROLLSTRUCT *smooth);
INT (* WINAPI p_Str_GetPtrA)(LPCSTR lpSrc, LPSTR lpDest, INT nMaxLen);
BOOL (* WINAPI p_Str_SetPtrA)(LPSTR *lppDest, LPCSTR lpSrc);
INT (* WINAPI p_Str_GetPtrW)(LPCWSTR lpSrc, LPWSTR lpDest, INT nMaxLen);
BOOL (* WINAPI p_Str_SetPtrW)(LPWSTR *lppDest, LPCWSTR lpSrc);
LPSTR (* WINAPI p_StrChrA)(LPCSTR lpszStr, WORD ch);
INT (* WINAPI p_StrCmpNIA)(LPCSTR lpszStr, LPCSTR lpszComp, INT iLen);
INT (* WINAPI p_StrCmpNIW)(LPCWSTR lpszStr, LPCWSTR lpszComp, INT iLen);
LPSTR (* WINAPI p_StrStrIA)(LPCSTR lpszStr, LPCSTR lpszSearch);
INT (* WINAPI p_StrToIntA)(LPCSTR lpszStr);
LPWSTR (* WINAPI p_StrStrIW)(LPCWSTR lpszStr, LPCWSTR lpszSearch);
INT (* WINAPI p_StrToIntW)(LPCWSTR lpString);
int (* WINAPI p_StrCSpnA)(LPCSTR lpszStr, LPCSTR lpszMatch);
LPWSTR (* WINAPI p_StrChrW)(LPCWSTR lpszStr, WCHAR ch);
INT (* WINAPI p_StrCmpNA)(LPCSTR lpszStr, LPCSTR lpszComp, INT iLen);
INT (* WINAPI p_StrCmpNW)(LPCWSTR lpszStr, LPCWSTR lpszComp, INT iLen);
LPSTR (* WINAPI p_StrRChrA)(LPCSTR lpszStr, LPCSTR lpszEnd, WORD ch);
LPWSTR (* WINAPI p_StrRChrW)(LPCWSTR str, LPCWSTR end, WORD ch);
LPSTR (* WINAPI p_StrStrA)(LPCSTR lpszStr, LPCSTR lpszSearch);
LPWSTR (* WINAPI p_StrStrW)(LPCWSTR lpszStr, LPCWSTR lpszSearch);
LPSTR (* WINAPI p_StrChrIA)(LPCSTR lpszStr, WORD ch);
LPWSTR (* WINAPI p_StrChrIW)(LPCWSTR lpszStr, WCHAR ch);
LPSTR (* WINAPI p_StrRStrIA)(LPCSTR lpszStr, LPCSTR lpszEnd, LPCSTR lpszSearch);
LPWSTR (* WINAPI p_StrRStrIW)(LPCWSTR lpszStr, LPCWSTR lpszEnd, LPCWSTR lpszSearch);
int (* WINAPI p_StrCSpnIA)(LPCSTR lpszStr, LPCSTR lpszMatch);
int (* WINAPI p_StrCSpnIW)(LPCWSTR lpszStr, LPCWSTR lpszMatch);
LPSTR (* WINAPI p_StrRChrIA)(LPCSTR lpszStr, LPCSTR lpszEnd, WORD ch);
LPWSTR (* WINAPI p_StrRChrIW)(LPCWSTR str, LPCWSTR end, WORD ch);
int (* WINAPI p_StrCSpnW)(LPCWSTR lpszStr, LPCWSTR lpszMatch);
BOOL (* WINAPI p_IntlStrEqWorkerA)(BOOL bCase, LPCSTR lpszStr, LPCSTR lpszComp, int iLen);
BOOL (* WINAPI p_IntlStrEqWorkerW)(BOOL bCase, LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen);
HRESULT (* WINAPI p_TaskDialogIndirect)(const TASKDIALOGCONFIG *taskconfig, int *button, int *radio_button, BOOL *verification_flag_checked);
HRESULT (* WINAPI p_TaskDialog)(HWND owner, HINSTANCE hinst, const WCHAR *title, const WCHAR *main_instruction, const WCHAR *content, TASKDIALOG_COMMON_BUTTON_FLAGS common_buttons, const WCHAR *icon, int *button);

WNDPROC wndproc_guest_to_host(uint64_t guest_func);

void hook_wndprocs(void);
void register_notify_callbacks(void);

struct qemu_NMHDR *propsheet_notify_h2g(NMHDR *host);
void propsheet_notify_g2h(NMHDR *host, NMHDR *guest);

struct page_data
{
    uint64_t guest_lparam, guest_cb;
    struct propsheet_data *header;
};

#endif

#endif
