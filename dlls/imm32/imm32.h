#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

enum imm32_calls
{
    CALL_IMMASSOCIATECONTEXT,
    CALL_IMMASSOCIATECONTEXTEX,
    CALL_IMMCONFIGUREIMEA,
    CALL_IMMCONFIGUREIMEW,
    CALL_IMMCREATECONTEXT,
    CALL_IMMCREATEIMCC,
    CALL_IMMCREATESOFTKEYBOARD,
    CALL_IMMDESTROYCONTEXT,
    CALL_IMMDESTROYIMCC,
    CALL_IMMDESTROYSOFTKEYBOARD,
    CALL_IMMDISABLEIME,
    CALL_IMMDISABLETEXTFRAMESERVICE,
    CALL_IMMENUMINPUTCONTEXT,
    CALL_IMMENUMREGISTERWORDA,
    CALL_IMMENUMREGISTERWORDW,
    CALL_IMMESCAPEA,
    CALL_IMMESCAPEW,
    CALL_IMMGENERATEMESSAGE,
    CALL_IMMGETCANDIDATELISTA,
    CALL_IMMGETCANDIDATELISTCOUNTA,
    CALL_IMMGETCANDIDATELISTCOUNTW,
    CALL_IMMGETCANDIDATELISTW,
    CALL_IMMGETCANDIDATEWINDOW,
    CALL_IMMGETCOMPOSITIONFONTA,
    CALL_IMMGETCOMPOSITIONFONTW,
    CALL_IMMGETCOMPOSITIONSTRINGA,
    CALL_IMMGETCOMPOSITIONSTRINGW,
    CALL_IMMGETCOMPOSITIONWINDOW,
    CALL_IMMGETCONTEXT,
    CALL_IMMGETCONVERSIONLISTA,
    CALL_IMMGETCONVERSIONLISTW,
    CALL_IMMGETCONVERSIONSTATUS,
    CALL_IMMGETDEFAULTIMEWND,
    CALL_IMMGETDESCRIPTIONA,
    CALL_IMMGETDESCRIPTIONW,
    CALL_IMMGETGUIDELINEA,
    CALL_IMMGETGUIDELINEW,
    CALL_IMMGETHOTKEY,
    CALL_IMMGETIMCCLOCKCOUNT,
    CALL_IMMGETIMCCSIZE,
    CALL_IMMGETIMCLOCKCOUNT,
    CALL_IMMGETIMEFILENAMEA,
    CALL_IMMGETIMEFILENAMEW,
    CALL_IMMGETIMEMENUITEMSA,
    CALL_IMMGETIMEMENUITEMSW,
    CALL_IMMGETOPENSTATUS,
    CALL_IMMGETPROPERTY,
    CALL_IMMGETREGISTERWORDSTYLEA,
    CALL_IMMGETREGISTERWORDSTYLEW,
    CALL_IMMGETSTATUSWINDOWPOS,
    CALL_IMMGETVIRTUALKEY,
    CALL_IMMINSTALLIMEA,
    CALL_IMMINSTALLIMEW,
    CALL_IMMISIME,
    CALL_IMMISUIMESSAGEA,
    CALL_IMMISUIMESSAGEW,
    CALL_IMMLOCKIMC,
    CALL_IMMLOCKIMCC,
    CALL_IMMNOTIFYIME,
    CALL_IMMPROCESSKEY,
    CALL_IMMREGISTERWORDA,
    CALL_IMMREGISTERWORDW,
    CALL_IMMRELEASECONTEXT,
    CALL_IMMREQUESTMESSAGEA,
    CALL_IMMREQUESTMESSAGEW,
    CALL_IMMRESIZEIMCC,
    CALL_IMMSETCANDIDATEWINDOW,
    CALL_IMMSETCOMPOSITIONFONTA,
    CALL_IMMSETCOMPOSITIONFONTW,
    CALL_IMMSETCOMPOSITIONSTRINGA,
    CALL_IMMSETCOMPOSITIONSTRINGW,
    CALL_IMMSETCOMPOSITIONWINDOW,
    CALL_IMMSETCONVERSIONSTATUS,
    CALL_IMMSETOPENSTATUS,
    CALL_IMMSETSTATUSWINDOWPOS,
    CALL_IMMSHOWSOFTKEYBOARD,
    CALL_IMMSIMULATEHOTKEY,
    CALL_IMMTRANSLATEMESSAGE,
    CALL_IMMUNLOCKIMC,
    CALL_IMMUNLOCKIMCC,
    CALL_IMMUNREGISTERWORDA,
    CALL_IMMUNREGISTERWORDW,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_ImmAssociateContext(struct qemu_syscall *call);
void qemu_ImmAssociateContextEx(struct qemu_syscall *call);
void qemu_ImmConfigureIMEA(struct qemu_syscall *call);
void qemu_ImmConfigureIMEW(struct qemu_syscall *call);
void qemu_ImmCreateContext(struct qemu_syscall *call);
void qemu_ImmCreateIMCC(struct qemu_syscall *call);
void qemu_ImmCreateSoftKeyboard(struct qemu_syscall *call);
void qemu_ImmDestroyContext(struct qemu_syscall *call);
void qemu_ImmDestroyIMCC(struct qemu_syscall *call);
void qemu_ImmDestroySoftKeyboard(struct qemu_syscall *call);
void qemu_ImmDisableIME(struct qemu_syscall *call);
void qemu_ImmDisableTextFrameService(struct qemu_syscall *call);
void qemu_ImmEnumInputContext(struct qemu_syscall *call);
void qemu_ImmEnumRegisterWordA(struct qemu_syscall *call);
void qemu_ImmEnumRegisterWordW(struct qemu_syscall *call);
void qemu_ImmEscapeA(struct qemu_syscall *call);
void qemu_ImmEscapeW(struct qemu_syscall *call);
void qemu_ImmGenerateMessage(struct qemu_syscall *call);
void qemu_ImmGetCandidateListA(struct qemu_syscall *call);
void qemu_ImmGetCandidateListCountA(struct qemu_syscall *call);
void qemu_ImmGetCandidateListCountW(struct qemu_syscall *call);
void qemu_ImmGetCandidateListW(struct qemu_syscall *call);
void qemu_ImmGetCandidateWindow(struct qemu_syscall *call);
void qemu_ImmGetCompositionFontA(struct qemu_syscall *call);
void qemu_ImmGetCompositionFontW(struct qemu_syscall *call);
void qemu_ImmGetCompositionStringA(struct qemu_syscall *call);
void qemu_ImmGetCompositionStringW(struct qemu_syscall *call);
void qemu_ImmGetCompositionWindow(struct qemu_syscall *call);
void qemu_ImmGetContext(struct qemu_syscall *call);
void qemu_ImmGetConversionListA(struct qemu_syscall *call);
void qemu_ImmGetConversionListW(struct qemu_syscall *call);
void qemu_ImmGetConversionStatus(struct qemu_syscall *call);
void qemu_ImmGetDefaultIMEWnd(struct qemu_syscall *call);
void qemu_ImmGetDescriptionA(struct qemu_syscall *call);
void qemu_ImmGetDescriptionW(struct qemu_syscall *call);
void qemu_ImmGetGuideLineA(struct qemu_syscall *call);
void qemu_ImmGetGuideLineW(struct qemu_syscall *call);
void qemu_ImmGetHotKey(struct qemu_syscall *call);
void qemu_ImmGetIMCCLockCount(struct qemu_syscall *call);
void qemu_ImmGetIMCCSize(struct qemu_syscall *call);
void qemu_ImmGetIMCLockCount(struct qemu_syscall *call);
void qemu_ImmGetIMEFileNameA(struct qemu_syscall *call);
void qemu_ImmGetIMEFileNameW(struct qemu_syscall *call);
void qemu_ImmGetImeMenuItemsA(struct qemu_syscall *call);
void qemu_ImmGetImeMenuItemsW(struct qemu_syscall *call);
void qemu_ImmGetOpenStatus(struct qemu_syscall *call);
void qemu_ImmGetProperty(struct qemu_syscall *call);
void qemu_ImmGetRegisterWordStyleA(struct qemu_syscall *call);
void qemu_ImmGetRegisterWordStyleW(struct qemu_syscall *call);
void qemu_ImmGetStatusWindowPos(struct qemu_syscall *call);
void qemu_ImmGetVirtualKey(struct qemu_syscall *call);
void qemu_ImmInstallIMEA(struct qemu_syscall *call);
void qemu_ImmInstallIMEW(struct qemu_syscall *call);
void qemu_ImmIsIME(struct qemu_syscall *call);
void qemu_ImmIsUIMessageA(struct qemu_syscall *call);
void qemu_ImmIsUIMessageW(struct qemu_syscall *call);
void qemu_ImmLockIMC(struct qemu_syscall *call);
void qemu_ImmLockIMCC(struct qemu_syscall *call);
void qemu_ImmNotifyIME(struct qemu_syscall *call);
void qemu_ImmProcessKey(struct qemu_syscall *call);
void qemu_ImmRegisterWordA(struct qemu_syscall *call);
void qemu_ImmRegisterWordW(struct qemu_syscall *call);
void qemu_ImmReleaseContext(struct qemu_syscall *call);
void qemu_ImmRequestMessageA(struct qemu_syscall *call);
void qemu_ImmRequestMessageW(struct qemu_syscall *call);
void qemu_ImmReSizeIMCC(struct qemu_syscall *call);
void qemu_ImmSetCandidateWindow(struct qemu_syscall *call);
void qemu_ImmSetCompositionFontA(struct qemu_syscall *call);
void qemu_ImmSetCompositionFontW(struct qemu_syscall *call);
void qemu_ImmSetCompositionStringA(struct qemu_syscall *call);
void qemu_ImmSetCompositionStringW(struct qemu_syscall *call);
void qemu_ImmSetCompositionWindow(struct qemu_syscall *call);
void qemu_ImmSetConversionStatus(struct qemu_syscall *call);
void qemu_ImmSetOpenStatus(struct qemu_syscall *call);
void qemu_ImmSetStatusWindowPos(struct qemu_syscall *call);
void qemu_ImmShowSoftKeyboard(struct qemu_syscall *call);
void qemu_ImmSimulateHotKey(struct qemu_syscall *call);
void qemu_ImmTranslateMessage(struct qemu_syscall *call);
void qemu_ImmUnlockIMC(struct qemu_syscall *call);
void qemu_ImmUnlockIMCC(struct qemu_syscall *call);
void qemu_ImmUnregisterWordA(struct qemu_syscall *call);
void qemu_ImmUnregisterWordW(struct qemu_syscall *call);

#endif

#endif
