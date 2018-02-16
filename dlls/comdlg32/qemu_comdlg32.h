#ifndef COMDLG32_H
#define COMDLG32_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_CHOOSECOLORA = 0,
    CALL_CHOOSECOLORW,
    CALL_CHOOSEFONTA,
    CALL_CHOOSEFONTW,
    CALL_COMMDLGEXTENDEDERROR,
    CALL_DLL_INIT,
    CALL_DLLGETCLASSOBJECT,
    CALL_DLLREGISTERSERVER,
    CALL_DLLUNREGISTERSERVER,
    CALL_FINDTEXTA,
    CALL_FINDTEXTW,
    CALL_GETFILETITLEA,
    CALL_GETFILETITLEW,
    CALL_GETOPENFILENAMEA,
    CALL_GETOPENFILENAMEW,
    CALL_GETSAVEFILENAMEA,
    CALL_GETSAVEFILENAMEW,
    CALL_PAGESETUPDLGA,
    CALL_PAGESETUPDLGW,
    CALL_PRINTDLGA,
    CALL_PRINTDLGEXA,
    CALL_PRINTDLGEXW,
    CALL_PRINTDLGW,
    CALL_REPLACETEXTA,
    CALL_REPLACETEXTW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_ChooseColorA(struct qemu_syscall *call);
void qemu_ChooseColorW(struct qemu_syscall *call);
void qemu_ChooseFontA(struct qemu_syscall *call);
void qemu_ChooseFontW(struct qemu_syscall *call);
void qemu_CommDlgExtendedError(struct qemu_syscall *call);
void qemu_DllGetClassObject(struct qemu_syscall *call);
void qemu_DllRegisterServer(struct qemu_syscall *call);
void qemu_DllUnregisterServer(struct qemu_syscall *call);
void qemu_FindTextA(struct qemu_syscall *call);
void qemu_FindTextW(struct qemu_syscall *call);
void qemu_GetFileTitleA(struct qemu_syscall *call);
void qemu_GetFileTitleW(struct qemu_syscall *call);
void qemu_GetOpenSaveFileName(struct qemu_syscall *call);
void qemu_PageSetupDlgA(struct qemu_syscall *call);
void qemu_PageSetupDlgW(struct qemu_syscall *call);
void qemu_PrintDlgA(struct qemu_syscall *call);
void qemu_PrintDlgExA(struct qemu_syscall *call);
void qemu_PrintDlgExW(struct qemu_syscall *call);
void qemu_PrintDlgW(struct qemu_syscall *call);
void qemu_ReplaceTextA(struct qemu_syscall *call);
void qemu_ReplaceTextW(struct qemu_syscall *call);

DWORD comdlg32_tls;

HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **ppv);
HRESULT (* WINAPI p_DllRegisterServer)(void);
HRESULT (* WINAPI p_DllUnregisterServer)(void);
DWORD (* WINAPI p_CommDlgExtendedError)(void);
HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **ppv);
HRESULT (* WINAPI p_DllRegisterServer)(void);
HRESULT (* WINAPI p_DllUnregisterServer)(void);
BOOL (* WINAPI p_GetOpenFileNameA)(OPENFILENAMEA *ofn);
BOOL (* WINAPI p_GetOpenFileNameW)(OPENFILENAMEW *ofn);
BOOL (* WINAPI p_GetSaveFileNameA)(OPENFILENAMEA *ofn);
BOOL (* WINAPI p_GetSaveFileNameW)(LPOPENFILENAMEW ofn);
short (* WINAPI p_GetFileTitleA)(LPCSTR lpFile, LPSTR lpTitle, WORD cbBuf);
short (* WINAPI p_GetFileTitleW)(LPCWSTR lpFile, LPWSTR lpTitle, WORD cbBuf);
BOOL (* WINAPI p_ChooseColorW)(CHOOSECOLORW *lpChCol);
BOOL (* WINAPI p_ChooseColorA)(LPCHOOSECOLORA lpChCol);
HWND (* WINAPI p_FindTextA)(LPFINDREPLACEA pfr);
HWND (* WINAPI p_ReplaceTextA)(LPFINDREPLACEA pfr);
HWND (* WINAPI p_FindTextW)(LPFINDREPLACEW pfr);
HWND (* WINAPI p_ReplaceTextW)(LPFINDREPLACEW pfr);
BOOL (* WINAPI p_ChooseFontW)(LPCHOOSEFONTW lpChFont);
BOOL (* WINAPI p_ChooseFontA)(LPCHOOSEFONTA lpChFont);
BOOL (* WINAPI p_PrintDlgA)(LPPRINTDLGA lppd);
BOOL (* WINAPI p_PrintDlgW)(LPPRINTDLGW lppd);
BOOL (* WINAPI p_PageSetupDlgA)(LPPAGESETUPDLGA setupdlg);
BOOL (* WINAPI p_PageSetupDlgW)(LPPAGESETUPDLGW setupdlg);
HRESULT (* WINAPI p_PrintDlgExA)(LPPRINTDLGEXA lppd);
HRESULT (* WINAPI p_PrintDlgExW)(LPPRINTDLGEXW lppd);

#endif

#endif
