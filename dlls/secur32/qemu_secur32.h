#ifndef QEMU_SECUR32_H
#define QEMU_SECUR32_H

#include <stdlib.h>

enum secur32_calls
{
    CALL_ACCEPTSECURITYCONTEXT = 0,
    CALL_ACQUIRECREDENTIALSHANDLEA,
    CALL_ACQUIRECREDENTIALSHANDLEW,
    CALL_ADDCREDENTIALSA,
    CALL_ADDCREDENTIALSW,
    CALL_ADDSECURITYPACKAGEA,
    CALL_ADDSECURITYPACKAGEW,
    CALL_APPLYCONTROLTOKEN,
    CALL_COMPLETEAUTHTOKEN,
    CALL_DECRYPTMESSAGE,
    CALL_DELETESECURITYCONTEXT,
    CALL_ENCRYPTMESSAGE,
    CALL_ENUMERATESECURITYPACKAGESA,
    CALL_ENUMERATESECURITYPACKAGESW,
    CALL_EXPORTSECURITYCONTEXT,
    CALL_FREECONTEXTBUFFER,
    CALL_FREECREDENTIALSHANDLE,
    CALL_GETCOMPUTEROBJECTNAMEA,
    CALL_GETCOMPUTEROBJECTNAMEW,
    CALL_GETUSERNAMEEXA,
    CALL_GETUSERNAMEEXW,
    CALL_IMPERSONATESECURITYCONTEXT,
    CALL_IMPORTSECURITYCONTEXTA,
    CALL_IMPORTSECURITYCONTEXTW,
    CALL_INITIALIZESECURITYCONTEXTA,
    CALL_INITIALIZESECURITYCONTEXTW,
    CALL_INITSECURITYINTERFACEA,
    CALL_INITSECURITYINTERFACEW,
    CALL_LSACALLAUTHENTICATIONPACKAGE,
    CALL_LSACONNECTUNTRUSTED,
    CALL_LSADEREGISTERLOGONPROCESS,
    CALL_LSAENUMERATELOGONSESSIONS,
    CALL_LSAFREERETURNBUFFER,
    CALL_LSAGETLOGONSESSIONDATA,
    CALL_LSALOGONUSER,
    CALL_LSALOOKUPAUTHENTICATIONPACKAGE,
    CALL_LSAREGISTERLOGONPROCESS,
    CALL_MAKESIGNATURE,
    CALL_QUERYCONTEXTATTRIBUTESA,
    CALL_QUERYCONTEXTATTRIBUTESW,
    CALL_QUERYCREDENTIALSATTRIBUTESA,
    CALL_QUERYCREDENTIALSATTRIBUTESW,
    CALL_QUERYSECURITYCONTEXTTOKEN,
    CALL_QUERYSECURITYPACKAGEINFOA,
    CALL_QUERYSECURITYPACKAGEINFOW,
    CALL_REVERTSECURITYCONTEXT,
    CALL_SETCONTEXTATTRIBUTESA,
    CALL_SETCONTEXTATTRIBUTESW,
    CALL_TRANSLATENAMEA,
    CALL_TRANSLATENAMEW,
    CALL_VERIFYSIGNATURE,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_AcceptSecurityContext(struct qemu_syscall *call);
void qemu_AcquireCredentialsHandle(struct qemu_syscall *call);
void qemu_AddCredentialsA(struct qemu_syscall *call);
void qemu_AddCredentialsW(struct qemu_syscall *call);
void qemu_AddSecurityPackageA(struct qemu_syscall *call);
void qemu_AddSecurityPackageW(struct qemu_syscall *call);
void qemu_ApplyControlToken(struct qemu_syscall *call);
void qemu_CompleteAuthToken(struct qemu_syscall *call);
void qemu_DecryptMessage(struct qemu_syscall *call);
void qemu_DeleteSecurityContext(struct qemu_syscall *call);
void qemu_EncryptMessage(struct qemu_syscall *call);
void qemu_EnumerateSecurityPackagesA(struct qemu_syscall *call);
void qemu_EnumerateSecurityPackagesW(struct qemu_syscall *call);
void qemu_ExportSecurityContext(struct qemu_syscall *call);
void qemu_FreeContextBuffer(struct qemu_syscall *call);
void qemu_FreeCredentialsHandle(struct qemu_syscall *call);
void qemu_GetComputerObjectNameA(struct qemu_syscall *call);
void qemu_GetComputerObjectNameW(struct qemu_syscall *call);
void qemu_GetUserNameExA(struct qemu_syscall *call);
void qemu_GetUserNameExW(struct qemu_syscall *call);
void qemu_ImpersonateSecurityContext(struct qemu_syscall *call);
void qemu_ImportSecurityContextA(struct qemu_syscall *call);
void qemu_ImportSecurityContextW(struct qemu_syscall *call);
void qemu_InitializeSecurityContext(struct qemu_syscall *call);
void qemu_InitSecurityInterfaceA(struct qemu_syscall *call);
void qemu_InitSecurityInterfaceW(struct qemu_syscall *call);
void qemu_LsaCallAuthenticationPackage(struct qemu_syscall *call);
void qemu_LsaConnectUntrusted(struct qemu_syscall *call);
void qemu_LsaDeregisterLogonProcess(struct qemu_syscall *call);
void qemu_LsaEnumerateLogonSessions(struct qemu_syscall *call);
void qemu_LsaFreeReturnBuffer(struct qemu_syscall *call);
void qemu_LsaGetLogonSessionData(struct qemu_syscall *call);
void qemu_LsaLogonUser(struct qemu_syscall *call);
void qemu_LsaLookupAuthenticationPackage(struct qemu_syscall *call);
void qemu_LsaRegisterLogonProcess(struct qemu_syscall *call);
void qemu_MakeSignature(struct qemu_syscall *call);
void qemu_QueryContextAttributes(struct qemu_syscall *call);
void qemu_QueryCredentialsAttributes(struct qemu_syscall *call);
void qemu_QuerySecurityContextToken(struct qemu_syscall *call);
void qemu_QuerySecurityPackageInfoA(struct qemu_syscall *call);
void qemu_QuerySecurityPackageInfoW(struct qemu_syscall *call);
void qemu_RevertSecurityContext(struct qemu_syscall *call);
void qemu_SetContextAttributesA(struct qemu_syscall *call);
void qemu_SetContextAttributesW(struct qemu_syscall *call);
void qemu_TranslateNameA(struct qemu_syscall *call);
void qemu_TranslateNameW(struct qemu_syscall *call);
void qemu_VerifySignature(struct qemu_syscall *call);

#endif

#endif
