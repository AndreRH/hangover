#ifndef QEMU_ADVPACK_H
#define QEMU_ADVPACK_H

enum advpack_calls
{
    CALL_ADDDELBACKUPENTRYA = 0,
    CALL_ADDDELBACKUPENTRYW,
    CALL_ADVINSTALLFILEA,
    CALL_ADVINSTALLFILEW,
    CALL_CLOSEINFENGINE,
    CALL_DELNODEA,
    CALL_DELNODERUNDLL32A,
    CALL_DELNODERUNDLL32W,
    CALL_DELNODEW,
    CALL_DOINFINSTALL,
    CALL_EXECUTECABA,
    CALL_EXECUTECABW,
    CALL_EXTRACTFILESA,
    CALL_EXTRACTFILESW,
    CALL_FILESAVEMARKNOTEXISTA,
    CALL_FILESAVEMARKNOTEXISTW,
    CALL_FILESAVERESTOREA,
    CALL_FILESAVERESTOREONINFA,
    CALL_FILESAVERESTOREONINFW,
    CALL_FILESAVERESTOREW,
    CALL_GETVERSIONFROMFILEA,
    CALL_GETVERSIONFROMFILEEXA,
    CALL_GETVERSIONFROMFILEEXW,
    CALL_GETVERSIONFROMFILEW,
    CALL_ISNTADMIN,
    CALL_LAUNCHINFSECTIONA,
    CALL_LAUNCHINFSECTIONEXA,
    CALL_LAUNCHINFSECTIONEXW,
    CALL_LAUNCHINFSECTIONW,
    CALL_NEEDREBOOT,
    CALL_NEEDREBOOTINIT,
    CALL_OPENINFENGINEA,
    CALL_OPENINFENGINEW,
    CALL_REBOOTCHECKONINSTALLA,
    CALL_REBOOTCHECKONINSTALLW,
    CALL_REGINSTALLA,
    CALL_REGINSTALLW,
    CALL_REGISTEROCX,
    CALL_REGRESTOREALLA,
    CALL_REGRESTOREALLW,
    CALL_REGSAVERESTOREA,
    CALL_REGSAVERESTOREONINFA,
    CALL_REGSAVERESTOREONINFW,
    CALL_REGSAVERESTOREW,
    CALL_RUNSETUPCOMMANDA,
    CALL_RUNSETUPCOMMANDW,
    CALL_SETPERUSERSECVALUESA,
    CALL_SETPERUSERSECVALUESW,
    CALL_TRANSLATEINFSTRINGA,
    CALL_TRANSLATEINFSTRINGEXA,
    CALL_TRANSLATEINFSTRINGEXW,
    CALL_TRANSLATEINFSTRINGW,
    CALL_USERINSTSTUBWRAPPERA,
    CALL_USERINSTSTUBWRAPPERW,
    CALL_USERUNINSTSTUBWRAPPERA,
    CALL_USERUNINSTSTUBWRAPPERW,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_AddDelBackupEntryA(struct qemu_syscall *call);
void qemu_AddDelBackupEntryW(struct qemu_syscall *call);
void qemu_AdvInstallFileA(struct qemu_syscall *call);
void qemu_AdvInstallFileW(struct qemu_syscall *call);
void qemu_CloseINFEngine(struct qemu_syscall *call);
void qemu_DelNodeA(struct qemu_syscall *call);
void qemu_DelNodeRunDLL32A(struct qemu_syscall *call);
void qemu_DelNodeRunDLL32W(struct qemu_syscall *call);
void qemu_DelNodeW(struct qemu_syscall *call);
void qemu_DoInfInstall(struct qemu_syscall *call);
void qemu_ExecuteCabA(struct qemu_syscall *call);
void qemu_ExecuteCabW(struct qemu_syscall *call);
void qemu_ExtractFilesA(struct qemu_syscall *call);
void qemu_ExtractFilesW(struct qemu_syscall *call);
void qemu_FileSaveMarkNotExistA(struct qemu_syscall *call);
void qemu_FileSaveMarkNotExistW(struct qemu_syscall *call);
void qemu_FileSaveRestoreA(struct qemu_syscall *call);
void qemu_FileSaveRestoreOnINFA(struct qemu_syscall *call);
void qemu_FileSaveRestoreOnINFW(struct qemu_syscall *call);
void qemu_FileSaveRestoreW(struct qemu_syscall *call);
void qemu_GetVersionFromFileA(struct qemu_syscall *call);
void qemu_GetVersionFromFileExA(struct qemu_syscall *call);
void qemu_GetVersionFromFileExW(struct qemu_syscall *call);
void qemu_GetVersionFromFileW(struct qemu_syscall *call);
void qemu_IsNTAdmin(struct qemu_syscall *call);
void qemu_LaunchINFSectionA(struct qemu_syscall *call);
void qemu_LaunchINFSectionExA(struct qemu_syscall *call);
void qemu_LaunchINFSectionExW(struct qemu_syscall *call);
void qemu_LaunchINFSectionW(struct qemu_syscall *call);
void qemu_NeedReboot(struct qemu_syscall *call);
void qemu_NeedRebootInit(struct qemu_syscall *call);
void qemu_OpenINFEngineA(struct qemu_syscall *call);
void qemu_OpenINFEngineW(struct qemu_syscall *call);
void qemu_RebootCheckOnInstallA(struct qemu_syscall *call);
void qemu_RebootCheckOnInstallW(struct qemu_syscall *call);
void qemu_RegInstallA(struct qemu_syscall *call);
void qemu_RegInstallW(struct qemu_syscall *call);
void qemu_RegisterOCX(struct qemu_syscall *call);
void qemu_RegRestoreAllA(struct qemu_syscall *call);
void qemu_RegRestoreAllW(struct qemu_syscall *call);
void qemu_RegSaveRestoreA(struct qemu_syscall *call);
void qemu_RegSaveRestoreOnINFA(struct qemu_syscall *call);
void qemu_RegSaveRestoreOnINFW(struct qemu_syscall *call);
void qemu_RegSaveRestoreW(struct qemu_syscall *call);
void qemu_RunSetupCommandA(struct qemu_syscall *call);
void qemu_RunSetupCommandW(struct qemu_syscall *call);
void qemu_SetPerUserSecValuesA(struct qemu_syscall *call);
void qemu_SetPerUserSecValuesW(struct qemu_syscall *call);
void qemu_TranslateInfStringA(struct qemu_syscall *call);
void qemu_TranslateInfStringExA(struct qemu_syscall *call);
void qemu_TranslateInfStringExW(struct qemu_syscall *call);
void qemu_TranslateInfStringW(struct qemu_syscall *call);
void qemu_UserInstStubWrapperA(struct qemu_syscall *call);
void qemu_UserInstStubWrapperW(struct qemu_syscall *call);
void qemu_UserUnInstStubWrapperA(struct qemu_syscall *call);
void qemu_UserUnInstStubWrapperW(struct qemu_syscall *call);

#endif

#endif
