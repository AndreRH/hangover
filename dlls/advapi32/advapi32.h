#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>

enum advapi32_calls
{
    CALL_ACCESSCHECK = 0,
    CALL_ACCESSCHECKANDAUDITALARMA,
    CALL_ACCESSCHECKANDAUDITALARMW,
    CALL_ACCESSCHECKBYTYPE,
    CALL_ADDACCESSALLOWEDACE,
    CALL_ADDACCESSALLOWEDACEEX,
    CALL_ADDACCESSALLOWEDOBJECTACE,
    CALL_ADDACCESSDENIEDACE,
    CALL_ADDACCESSDENIEDACEEX,
    CALL_ADDACCESSDENIEDOBJECTACE,
    CALL_ADDACE,
    CALL_ADDAUDITACCESSACE,
    CALL_ADDAUDITACCESSACEEX,
    CALL_ADDAUDITACCESSOBJECTACE,
    CALL_ADDMANDATORYACE,
    CALL_ADJUSTTOKENGROUPS,
    CALL_ADJUSTTOKENPRIVILEGES,
    CALL_ALLOCATEANDINITIALIZESID,
    CALL_ALLOCATELOCALLYUNIQUEID,
    CALL_AREALLACCESSESGRANTED,
    CALL_AREANYACCESSESGRANTED,
    CALL_BUILDEXPLICITACCESSWITHNAMEA,
    CALL_BUILDEXPLICITACCESSWITHNAMEW,
    CALL_BUILDSECURITYDESCRIPTORA,
    CALL_BUILDSECURITYDESCRIPTORW,
    CALL_BUILDTRUSTEEWITHNAMEA,
    CALL_BUILDTRUSTEEWITHNAMEW,
    CALL_BUILDTRUSTEEWITHOBJECTSANDNAMEA,
    CALL_BUILDTRUSTEEWITHOBJECTSANDNAMEW,
    CALL_BUILDTRUSTEEWITHOBJECTSANDSIDA,
    CALL_BUILDTRUSTEEWITHOBJECTSANDSIDW,
    CALL_BUILDTRUSTEEWITHSIDA,
    CALL_BUILDTRUSTEEWITHSIDW,
    CALL_CHECKTOKENMEMBERSHIP,
    CALL_CLOSEENCRYPTEDFILERAW,
    CALL_CONVERTSECURITYDESCRIPTORTOSTRINGSECURITYDESCRIPTORA,
    CALL_CONVERTSECURITYDESCRIPTORTOSTRINGSECURITYDESCRIPTORW,
    CALL_CONVERTSIDTOSTRINGSIDA,
    CALL_CONVERTSIDTOSTRINGSIDW,
    CALL_CONVERTSTRINGSECURITYDESCRIPTORTOSECURITYDESCRIPTORA,
    CALL_CONVERTSTRINGSECURITYDESCRIPTORTOSECURITYDESCRIPTORW,
    CALL_CONVERTSTRINGSIDTOSIDA,
    CALL_CONVERTSTRINGSIDTOSIDW,
    CALL_CONVERTTOAUTOINHERITPRIVATEOBJECTSECURITY,
    CALL_COPYSID,
    CALL_CREATEPRIVATEOBJECTSECURITY,
    CALL_CREATEPRIVATEOBJECTSECURITYEX,
    CALL_CREATEPRIVATEOBJECTSECURITYWITHMULTIPLEINHERITANCE,
    CALL_CREATEPROCESSASUSERA,
    CALL_CREATEPROCESSASUSERW,
    CALL_CREATEPROCESSWITHLOGONW,
    CALL_CREATEPROCESSWITHTOKENW,
    CALL_CREATERESTRICTEDTOKEN,
    CALL_CREATEWELLKNOWNSID,
    CALL_CRYPTACQUIRECONTEXTA,
    CALL_CRYPTACQUIRECONTEXTW,
    CALL_CRYPTCONTEXTADDREF,
    CALL_CRYPTCREATEHASH,
    CALL_CRYPTDECRYPT,
    CALL_CRYPTDERIVEKEY,
    CALL_CRYPTDESTROYHASH,
    CALL_CRYPTDESTROYKEY,
    CALL_CRYPTDUPLICATEHASH,
    CALL_CRYPTDUPLICATEKEY,
    CALL_CRYPTENCRYPT,
    CALL_CRYPTENUMPROVIDERSA,
    CALL_CRYPTENUMPROVIDERSW,
    CALL_CRYPTENUMPROVIDERTYPESA,
    CALL_CRYPTENUMPROVIDERTYPESW,
    CALL_CRYPTEXPORTKEY,
    CALL_CRYPTGENKEY,
    CALL_CRYPTGENRANDOM,
    CALL_CRYPTGETDEFAULTPROVIDERA,
    CALL_CRYPTGETDEFAULTPROVIDERW,
    CALL_CRYPTGETHASHPARAM,
    CALL_CRYPTGETKEYPARAM,
    CALL_CRYPTGETPROVPARAM,
    CALL_CRYPTGETUSERKEY,
    CALL_CRYPTHASHDATA,
    CALL_CRYPTHASHSESSIONKEY,
    CALL_CRYPTIMPORTKEY,
    CALL_CRYPTRELEASECONTEXT,
    CALL_CRYPTSETHASHPARAM,
    CALL_CRYPTSETKEYPARAM,
    CALL_CRYPTSETPROVIDERA,
    CALL_CRYPTSETPROVIDEREXA,
    CALL_CRYPTSETPROVIDEREXW,
    CALL_CRYPTSETPROVIDERW,
    CALL_CRYPTSETPROVPARAM,
    CALL_CRYPTSIGNHASHA,
    CALL_CRYPTSIGNHASHW,
    CALL_CRYPTVERIFYSIGNATUREA,
    CALL_CRYPTVERIFYSIGNATUREW,
    CALL_DECRYPTFILEA,
    CALL_DECRYPTFILEW,
    CALL_DELETEACE,
    CALL_DESTROYPRIVATEOBJECTSECURITY,
    CALL_DUPLICATETOKEN,
    CALL_DUPLICATETOKENEX,
    CALL_ENCRYPTFILEA,
    CALL_ENCRYPTFILEW,
    CALL_EQUALPREFIXSID,
    CALL_EQUALSID,
    CALL_FILEENCRYPTIONSTATUSA,
    CALL_FILEENCRYPTIONSTATUSW,
    CALL_FINDFIRSTFREEACE,
    CALL_FREESID,
    CALL_GETACE,
    CALL_GETACLINFORMATION,
    CALL_GETAUDITEDPERMISSIONSFROMACLA,
    CALL_GETAUDITEDPERMISSIONSFROMACLW,
    CALL_GETEFFECTIVERIGHTSFROMACLA,
    CALL_GETEFFECTIVERIGHTSFROMACLW,
    CALL_GETEXPLICITENTRIESFROMACLA,
    CALL_GETEXPLICITENTRIESFROMACLW,
    CALL_GETFILESECURITYA,
    CALL_GETFILESECURITYW,
    CALL_GETKERNELOBJECTSECURITY,
    CALL_GETLENGTHSID,
    CALL_GETNAMEDSECURITYINFOA,
    CALL_GETNAMEDSECURITYINFOEXA,
    CALL_GETNAMEDSECURITYINFOEXW,
    CALL_GETNAMEDSECURITYINFOW,
    CALL_GETPRIVATEOBJECTSECURITY,
    CALL_GETSECURITYDESCRIPTORCONTROL,
    CALL_GETSECURITYDESCRIPTORDACL,
    CALL_GETSECURITYDESCRIPTORGROUP,
    CALL_GETSECURITYDESCRIPTORLENGTH,
    CALL_GETSECURITYDESCRIPTOROWNER,
    CALL_GETSECURITYDESCRIPTORSACL,
    CALL_GETSECURITYINFO,
    CALL_GETSECURITYINFOEXA,
    CALL_GETSECURITYINFOEXW,
    CALL_GETSIDIDENTIFIERAUTHORITY,
    CALL_GETSIDLENGTHREQUIRED,
    CALL_GETSIDSUBAUTHORITY,
    CALL_GETSIDSUBAUTHORITYCOUNT,
    CALL_GETTOKENINFORMATION,
    CALL_GETTRUSTEEFORMA,
    CALL_GETTRUSTEEFORMW,
    CALL_GETTRUSTEENAMEA,
    CALL_GETTRUSTEENAMEW,
    CALL_GETTRUSTEETYPEA,
    CALL_GETTRUSTEETYPEW,
    CALL_GETWINDOWSACCOUNTDOMAINSID,
    CALL_IMPERSONATEANONYMOUSTOKEN,
    CALL_IMPERSONATELOGGEDONUSER,
    CALL_IMPERSONATENAMEDPIPECLIENT,
    CALL_IMPERSONATESELF,
    CALL_INITIALIZEACL,
    CALL_INITIALIZESECURITYDESCRIPTOR,
    CALL_INITIALIZESID,
    CALL_ISTEXTUNICODE,
    CALL_ISTOKENRESTRICTED,
    CALL_ISVALIDACL,
    CALL_ISVALIDSECURITYDESCRIPTOR,
    CALL_ISVALIDSID,
    CALL_ISWELLKNOWNSID,
    CALL_LOOKUPACCOUNTNAMEA,
    CALL_LOOKUPACCOUNTNAMEW,
    CALL_LOOKUPACCOUNTSIDA,
    CALL_LOOKUPACCOUNTSIDW,
    CALL_LOOKUPPRIVILEGEDISPLAYNAMEA,
    CALL_LOOKUPPRIVILEGEDISPLAYNAMEW,
    CALL_LOOKUPPRIVILEGENAMEA,
    CALL_LOOKUPPRIVILEGENAMEW,
    CALL_LOOKUPPRIVILEGEVALUEA,
    CALL_LOOKUPPRIVILEGEVALUEW,
    CALL_LOOKUPSECURITYDESCRIPTORPARTSA,
    CALL_LOOKUPSECURITYDESCRIPTORPARTSW,
    CALL_MAKEABSOLUTESD,
    CALL_MAKESELFRELATIVESD,
    CALL_MAPGENERICMASK,
    CALL_NOTIFYBOOTCONFIGSTATUS,
    CALL_OBJECTCLOSEAUDITALARMA,
    CALL_OBJECTCLOSEAUDITALARMW,
    CALL_OBJECTDELETEAUDITALARMW,
    CALL_OBJECTOPENAUDITALARMA,
    CALL_OBJECTOPENAUDITALARMW,
    CALL_OBJECTPRIVILEGEAUDITALARMA,
    CALL_OBJECTPRIVILEGEAUDITALARMW,
    CALL_OPENENCRYPTEDFILERAWA,
    CALL_OPENENCRYPTEDFILERAWW,
    CALL_OPENPROCESSTOKEN,
    CALL_OPENTHREADTOKEN,
    CALL_PRIVILEGECHECK,
    CALL_PRIVILEGEDSERVICEAUDITALARMA,
    CALL_PRIVILEGEDSERVICEAUDITALARMW,
    CALL_QUERYWINDOWS31FILESMIGRATION,
    CALL_READENCRYPTEDFILERAW,
    CALL_REGCLOSEKEY,
    CALL_REGCONNECTREGISTRYA,
    CALL_REGCONNECTREGISTRYW,
    CALL_REGCOPYTREEA,
    CALL_REGCOPYTREEW,
    CALL_REGCREATEKEYA,
    CALL_REGCREATEKEYEXA,
    CALL_REGCREATEKEYEXW,
    CALL_REGCREATEKEYTRANSACTEDA,
    CALL_REGCREATEKEYTRANSACTEDW,
    CALL_REGCREATEKEYW,
    CALL_REGDELETEKEYA,
    CALL_REGDELETEKEYEXA,
    CALL_REGDELETEKEYEXW,
    CALL_REGDELETEKEYVALUEA,
    CALL_REGDELETEKEYVALUEW,
    CALL_REGDELETEKEYW,
    CALL_REGDELETETREEA,
    CALL_REGDELETETREEW,
    CALL_REGDELETEVALUEA,
    CALL_REGDELETEVALUEW,
    CALL_REGDISABLEPREDEFINEDCACHE,
    CALL_REGDISABLEREFLECTIONKEY,
    CALL_REGENUMKEYA,
    CALL_REGENUMKEYEXA,
    CALL_REGENUMKEYEXW,
    CALL_REGENUMKEYW,
    CALL_REGENUMVALUEA,
    CALL_REGENUMVALUEW,
    CALL_REGFLUSHKEY,
    CALL_REGGETKEYSECURITY,
    CALL_REGGETVALUEA,
    CALL_REGGETVALUEW,
    CALL_REGLOADKEYA,
    CALL_REGLOADKEYW,
    CALL_REGLOADMUISTRINGA,
    CALL_REGLOADMUISTRINGW,
    CALL_REGNOTIFYCHANGEKEYVALUE,
    CALL_REGOPENCURRENTUSER,
    CALL_REGOPENKEYA,
    CALL_REGOPENKEYEXA,
    CALL_REGOPENKEYEXW,
    CALL_REGOPENKEYW,
    CALL_REGOPENUSERCLASSESROOT,
    CALL_REGOVERRIDEPREDEFKEY,
    CALL_REGQUERYINFOKEYA,
    CALL_REGQUERYINFOKEYW,
    CALL_REGQUERYMULTIPLEVALUESA,
    CALL_REGQUERYMULTIPLEVALUESW,
    CALL_REGQUERYVALUEA,
    CALL_REGQUERYVALUEEXA,
    CALL_REGQUERYVALUEEXW,
    CALL_REGQUERYVALUEW,
    CALL_REGREPLACEKEYA,
    CALL_REGREPLACEKEYW,
    CALL_REGRESTOREKEYA,
    CALL_REGRESTOREKEYW,
    CALL_REGSAVEKEYA,
    CALL_REGSAVEKEYEXA,
    CALL_REGSAVEKEYEXW,
    CALL_REGSAVEKEYW,
    CALL_REGSETKEYSECURITY,
    CALL_REGSETKEYVALUEA,
    CALL_REGSETKEYVALUEW,
    CALL_REGSETVALUEA,
    CALL_REGSETVALUEEXA,
    CALL_REGSETVALUEEXW,
    CALL_REGSETVALUEW,
    CALL_REGUNLOADKEYA,
    CALL_REGUNLOADKEYW,
    CALL_REVERTTOSELF,
    CALL_SAFERCLOSELEVEL,
    CALL_SAFERCOMPUTETOKENFROMLEVEL,
    CALL_SAFERCREATELEVEL,
    CALL_SAFERGETPOLICYINFORMATION,
    CALL_SAFERSETLEVELINFORMATION,
    CALL_SETACLINFORMATION,
    CALL_SETENTRIESINACLA,
    CALL_SETENTRIESINACLW,
    CALL_SETFILESECURITYA,
    CALL_SETFILESECURITYW,
    CALL_SETKERNELOBJECTSECURITY,
    CALL_SETNAMEDSECURITYINFOA,
    CALL_SETNAMEDSECURITYINFOW,
    CALL_SETPRIVATEOBJECTSECURITY,
    CALL_SETSECURITYDESCRIPTORCONTROL,
    CALL_SETSECURITYDESCRIPTORDACL,
    CALL_SETSECURITYDESCRIPTORGROUP,
    CALL_SETSECURITYDESCRIPTOROWNER,
    CALL_SETSECURITYDESCRIPTORSACL,
    CALL_SETSECURITYINFO,
    CALL_SETTHREADTOKEN,
    CALL_SETTOKENINFORMATION,
    CALL_SYNCHRONIZEWINDOWS31FILESANDWINDOWSNTREGISTRY,
    CALL_SYSTEMFUNCTION030,
    CALL_SYSTEMFUNCTION035,
    CALL_SYSTEMFUNCTION036,
    CALL_SYSTEMFUNCTION040,
    CALL_SYSTEMFUNCTION041,
    CALL_TREERESETNAMEDSECURITYINFOW,
    CALL_WRITEENCRYPTEDFILERAW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_AccessCheck(struct qemu_syscall *call);
void qemu_AccessCheckAndAuditAlarmA(struct qemu_syscall *call);
void qemu_AccessCheckAndAuditAlarmW(struct qemu_syscall *call);
void qemu_AccessCheckByType(struct qemu_syscall *call);
void qemu_AddAccessAllowedAce(struct qemu_syscall *call);
void qemu_AddAccessAllowedAceEx(struct qemu_syscall *call);
void qemu_AddAccessAllowedObjectAce(struct qemu_syscall *call);
void qemu_AddAccessDeniedAce(struct qemu_syscall *call);
void qemu_AddAccessDeniedAceEx(struct qemu_syscall *call);
void qemu_AddAccessDeniedObjectAce(struct qemu_syscall *call);
void qemu_AddAce(struct qemu_syscall *call);
void qemu_AddAuditAccessAce(struct qemu_syscall *call);
void qemu_AddAuditAccessAceEx(struct qemu_syscall *call);
void qemu_AddAuditAccessObjectAce(struct qemu_syscall *call);
void qemu_AddMandatoryAce(struct qemu_syscall *call);
void qemu_AdjustTokenGroups(struct qemu_syscall *call);
void qemu_AdjustTokenPrivileges(struct qemu_syscall *call);
void qemu_AllocateAndInitializeSid(struct qemu_syscall *call);
void qemu_AllocateLocallyUniqueId(struct qemu_syscall *call);
void qemu_AreAllAccessesGranted(struct qemu_syscall *call);
void qemu_AreAnyAccessesGranted(struct qemu_syscall *call);
void qemu_BuildExplicitAccessWithNameA(struct qemu_syscall *call);
void qemu_BuildExplicitAccessWithNameW(struct qemu_syscall *call);
void qemu_BuildSecurityDescriptorA(struct qemu_syscall *call);
void qemu_BuildSecurityDescriptorW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithNameA(struct qemu_syscall *call);
void qemu_BuildTrusteeWithNameW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndNameA(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndNameW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndSidA(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndSidW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithSidA(struct qemu_syscall *call);
void qemu_BuildTrusteeWithSidW(struct qemu_syscall *call);
void qemu_CheckTokenMembership(struct qemu_syscall *call);
void qemu_CloseEncryptedFileRaw(struct qemu_syscall *call);
void qemu_ConvertSecurityDescriptorToStringSecurityDescriptorA(struct qemu_syscall *call);
void qemu_ConvertSecurityDescriptorToStringSecurityDescriptorW(struct qemu_syscall *call);
void qemu_ConvertSidToStringSidA(struct qemu_syscall *call);
void qemu_ConvertSidToStringSidW(struct qemu_syscall *call);
void qemu_ConvertStringSecurityDescriptorToSecurityDescriptorA(struct qemu_syscall *call);
void qemu_ConvertStringSecurityDescriptorToSecurityDescriptorW(struct qemu_syscall *call);
void qemu_ConvertStringSidToSidA(struct qemu_syscall *call);
void qemu_ConvertStringSidToSidW(struct qemu_syscall *call);
void qemu_ConvertToAutoInheritPrivateObjectSecurity(struct qemu_syscall *call);
void qemu_CopySid(struct qemu_syscall *call);
void qemu_CreatePrivateObjectSecurity(struct qemu_syscall *call);
void qemu_CreatePrivateObjectSecurityEx(struct qemu_syscall *call);
void qemu_CreatePrivateObjectSecurityWithMultipleInheritance(struct qemu_syscall *call);
void qemu_CreateProcessAsUserA(struct qemu_syscall *call);
void qemu_CreateProcessAsUserW(struct qemu_syscall *call);
void qemu_CreateProcessWithLogonW(struct qemu_syscall *call);
void qemu_CreateProcessWithTokenW(struct qemu_syscall *call);
void qemu_CreateRestrictedToken(struct qemu_syscall *call);
void qemu_CreateWellKnownSid(struct qemu_syscall *call);
void qemu_CryptAcquireContextA(struct qemu_syscall *call);
void qemu_CryptAcquireContextW(struct qemu_syscall *call);
void qemu_CryptContextAddRef(struct qemu_syscall *call);
void qemu_CryptCreateHash(struct qemu_syscall *call);
void qemu_CryptDecrypt(struct qemu_syscall *call);
void qemu_CryptDeriveKey(struct qemu_syscall *call);
void qemu_CryptDestroyHash(struct qemu_syscall *call);
void qemu_CryptDestroyKey(struct qemu_syscall *call);
void qemu_CryptDuplicateHash(struct qemu_syscall *call);
void qemu_CryptDuplicateKey(struct qemu_syscall *call);
void qemu_CryptEncrypt(struct qemu_syscall *call);
void qemu_CryptEnumProvidersA(struct qemu_syscall *call);
void qemu_CryptEnumProvidersW(struct qemu_syscall *call);
void qemu_CryptEnumProviderTypesA(struct qemu_syscall *call);
void qemu_CryptEnumProviderTypesW(struct qemu_syscall *call);
void qemu_CryptExportKey(struct qemu_syscall *call);
void qemu_CryptGenKey(struct qemu_syscall *call);
void qemu_CryptGenRandom(struct qemu_syscall *call);
void qemu_CryptGetDefaultProviderA(struct qemu_syscall *call);
void qemu_CryptGetDefaultProviderW(struct qemu_syscall *call);
void qemu_CryptGetHashParam(struct qemu_syscall *call);
void qemu_CryptGetKeyParam(struct qemu_syscall *call);
void qemu_CryptGetProvParam(struct qemu_syscall *call);
void qemu_CryptGetUserKey(struct qemu_syscall *call);
void qemu_CryptHashData(struct qemu_syscall *call);
void qemu_CryptHashSessionKey(struct qemu_syscall *call);
void qemu_CryptImportKey(struct qemu_syscall *call);
void qemu_CryptReleaseContext(struct qemu_syscall *call);
void qemu_CryptSetHashParam(struct qemu_syscall *call);
void qemu_CryptSetKeyParam(struct qemu_syscall *call);
void qemu_CryptSetProviderA(struct qemu_syscall *call);
void qemu_CryptSetProviderExA(struct qemu_syscall *call);
void qemu_CryptSetProviderExW(struct qemu_syscall *call);
void qemu_CryptSetProviderW(struct qemu_syscall *call);
void qemu_CryptSetProvParam(struct qemu_syscall *call);
void qemu_CryptSignHashA(struct qemu_syscall *call);
void qemu_CryptSignHashW(struct qemu_syscall *call);
void qemu_CryptVerifySignatureA(struct qemu_syscall *call);
void qemu_CryptVerifySignatureW(struct qemu_syscall *call);
void qemu_DecryptFileA(struct qemu_syscall *call);
void qemu_DecryptFileW(struct qemu_syscall *call);
void qemu_DeleteAce(struct qemu_syscall *call);
void qemu_DestroyPrivateObjectSecurity(struct qemu_syscall *call);
void qemu_DuplicateToken(struct qemu_syscall *call);
void qemu_DuplicateTokenEx(struct qemu_syscall *call);
void qemu_EncryptFileA(struct qemu_syscall *call);
void qemu_EncryptFileW(struct qemu_syscall *call);
void qemu_EqualPrefixSid(struct qemu_syscall *call);
void qemu_EqualSid(struct qemu_syscall *call);
void qemu_FileEncryptionStatusA(struct qemu_syscall *call);
void qemu_FileEncryptionStatusW(struct qemu_syscall *call);
void qemu_FindFirstFreeAce(struct qemu_syscall *call);
void qemu_FreeSid(struct qemu_syscall *call);
void qemu_GetAce(struct qemu_syscall *call);
void qemu_GetAclInformation(struct qemu_syscall *call);
void qemu_GetAuditedPermissionsFromAclA(struct qemu_syscall *call);
void qemu_GetAuditedPermissionsFromAclW(struct qemu_syscall *call);
void qemu_GetEffectiveRightsFromAclA(struct qemu_syscall *call);
void qemu_GetEffectiveRightsFromAclW(struct qemu_syscall *call);
void qemu_GetExplicitEntriesFromAclA(struct qemu_syscall *call);
void qemu_GetExplicitEntriesFromAclW(struct qemu_syscall *call);
void qemu_GetFileSecurityA(struct qemu_syscall *call);
void qemu_GetFileSecurityW(struct qemu_syscall *call);
void qemu_GetKernelObjectSecurity(struct qemu_syscall *call);
void qemu_GetLengthSid(struct qemu_syscall *call);
void qemu_GetNamedSecurityInfoA(struct qemu_syscall *call);
void qemu_GetNamedSecurityInfoExA(struct qemu_syscall *call);
void qemu_GetNamedSecurityInfoExW(struct qemu_syscall *call);
void qemu_GetNamedSecurityInfoW(struct qemu_syscall *call);
void qemu_GetPrivateObjectSecurity(struct qemu_syscall *call);
void qemu_GetSecurityDescriptorControl(struct qemu_syscall *call);
void qemu_GetSecurityDescriptorDacl(struct qemu_syscall *call);
void qemu_GetSecurityDescriptorGroup(struct qemu_syscall *call);
void qemu_GetSecurityDescriptorLength(struct qemu_syscall *call);
void qemu_GetSecurityDescriptorOwner(struct qemu_syscall *call);
void qemu_GetSecurityDescriptorSacl(struct qemu_syscall *call);
void qemu_GetSecurityInfo(struct qemu_syscall *call);
void qemu_GetSecurityInfoExA(struct qemu_syscall *call);
void qemu_GetSecurityInfoExW(struct qemu_syscall *call);
void qemu_GetSidIdentifierAuthority(struct qemu_syscall *call);
void qemu_GetSidLengthRequired(struct qemu_syscall *call);
void qemu_GetSidSubAuthority(struct qemu_syscall *call);
void qemu_GetSidSubAuthorityCount(struct qemu_syscall *call);
void qemu_GetTokenInformation(struct qemu_syscall *call);
void qemu_GetTrusteeFormA(struct qemu_syscall *call);
void qemu_GetTrusteeFormW(struct qemu_syscall *call);
void qemu_GetTrusteeNameA(struct qemu_syscall *call);
void qemu_GetTrusteeNameW(struct qemu_syscall *call);
void qemu_GetTrusteeTypeA(struct qemu_syscall *call);
void qemu_GetTrusteeTypeW(struct qemu_syscall *call);
void qemu_GetWindowsAccountDomainSid(struct qemu_syscall *call);
void qemu_ImpersonateAnonymousToken(struct qemu_syscall *call);
void qemu_ImpersonateLoggedOnUser(struct qemu_syscall *call);
void qemu_ImpersonateNamedPipeClient(struct qemu_syscall *call);
void qemu_ImpersonateSelf(struct qemu_syscall *call);
void qemu_InitializeAcl(struct qemu_syscall *call);
void qemu_InitializeSecurityDescriptor(struct qemu_syscall *call);
void qemu_InitializeSid(struct qemu_syscall *call);
void qemu_IsTextUnicode(struct qemu_syscall *call);
void qemu_IsTokenRestricted(struct qemu_syscall *call);
void qemu_IsValidAcl(struct qemu_syscall *call);
void qemu_IsValidSecurityDescriptor(struct qemu_syscall *call);
void qemu_IsValidSid(struct qemu_syscall *call);
void qemu_IsWellKnownSid(struct qemu_syscall *call);
void qemu_LookupAccountNameA(struct qemu_syscall *call);
void qemu_LookupAccountNameW(struct qemu_syscall *call);
void qemu_LookupAccountSidA(struct qemu_syscall *call);
void qemu_LookupAccountSidW(struct qemu_syscall *call);
void qemu_LookupPrivilegeDisplayNameA(struct qemu_syscall *call);
void qemu_LookupPrivilegeDisplayNameW(struct qemu_syscall *call);
void qemu_LookupPrivilegeNameA(struct qemu_syscall *call);
void qemu_LookupPrivilegeNameW(struct qemu_syscall *call);
void qemu_LookupPrivilegeValueA(struct qemu_syscall *call);
void qemu_LookupPrivilegeValueW(struct qemu_syscall *call);
void qemu_LookupSecurityDescriptorPartsA(struct qemu_syscall *call);
void qemu_LookupSecurityDescriptorPartsW(struct qemu_syscall *call);
void qemu_MakeAbsoluteSD(struct qemu_syscall *call);
void qemu_MakeSelfRelativeSD(struct qemu_syscall *call);
void qemu_MapGenericMask(struct qemu_syscall *call);
void qemu_NotifyBootConfigStatus(struct qemu_syscall *call);
void qemu_ObjectCloseAuditAlarmA(struct qemu_syscall *call);
void qemu_ObjectCloseAuditAlarmW(struct qemu_syscall *call);
void qemu_ObjectDeleteAuditAlarmW(struct qemu_syscall *call);
void qemu_ObjectOpenAuditAlarmA(struct qemu_syscall *call);
void qemu_ObjectOpenAuditAlarmW(struct qemu_syscall *call);
void qemu_ObjectPrivilegeAuditAlarmA(struct qemu_syscall *call);
void qemu_ObjectPrivilegeAuditAlarmW(struct qemu_syscall *call);
void qemu_OpenEncryptedFileRawA(struct qemu_syscall *call);
void qemu_OpenEncryptedFileRawW(struct qemu_syscall *call);
void qemu_OpenProcessToken(struct qemu_syscall *call);
void qemu_OpenThreadToken(struct qemu_syscall *call);
void qemu_PrivilegeCheck(struct qemu_syscall *call);
void qemu_PrivilegedServiceAuditAlarmA(struct qemu_syscall *call);
void qemu_PrivilegedServiceAuditAlarmW(struct qemu_syscall *call);
void qemu_QueryWindows31FilesMigration(struct qemu_syscall *call);
void qemu_ReadEncryptedFileRaw(struct qemu_syscall *call);
void qemu_RegCloseKey(struct qemu_syscall *call);
void qemu_RegConnectRegistryA(struct qemu_syscall *call);
void qemu_RegConnectRegistryW(struct qemu_syscall *call);
void qemu_RegCopyTreeA(struct qemu_syscall *call);
void qemu_RegCopyTreeW(struct qemu_syscall *call);
void qemu_RegCreateKeyA(struct qemu_syscall *call);
void qemu_RegCreateKeyExA(struct qemu_syscall *call);
void qemu_RegCreateKeyExW(struct qemu_syscall *call);
void qemu_RegCreateKeyTransactedA(struct qemu_syscall *call);
void qemu_RegCreateKeyTransactedW(struct qemu_syscall *call);
void qemu_RegCreateKeyW(struct qemu_syscall *call);
void qemu_RegDeleteKeyA(struct qemu_syscall *call);
void qemu_RegDeleteKeyExA(struct qemu_syscall *call);
void qemu_RegDeleteKeyExW(struct qemu_syscall *call);
void qemu_RegDeleteKeyValueA(struct qemu_syscall *call);
void qemu_RegDeleteKeyValueW(struct qemu_syscall *call);
void qemu_RegDeleteKeyW(struct qemu_syscall *call);
void qemu_RegDeleteTreeA(struct qemu_syscall *call);
void qemu_RegDeleteTreeW(struct qemu_syscall *call);
void qemu_RegDeleteValueA(struct qemu_syscall *call);
void qemu_RegDeleteValueW(struct qemu_syscall *call);
void qemu_RegDisablePredefinedCache(struct qemu_syscall *call);
void qemu_RegDisableReflectionKey(struct qemu_syscall *call);
void qemu_RegEnumKeyA(struct qemu_syscall *call);
void qemu_RegEnumKeyExA(struct qemu_syscall *call);
void qemu_RegEnumKeyExW(struct qemu_syscall *call);
void qemu_RegEnumKeyW(struct qemu_syscall *call);
void qemu_RegEnumValueA(struct qemu_syscall *call);
void qemu_RegEnumValueW(struct qemu_syscall *call);
void qemu_RegFlushKey(struct qemu_syscall *call);
void qemu_RegGetKeySecurity(struct qemu_syscall *call);
void qemu_RegGetValueA(struct qemu_syscall *call);
void qemu_RegGetValueW(struct qemu_syscall *call);
void qemu_RegLoadKeyA(struct qemu_syscall *call);
void qemu_RegLoadKeyW(struct qemu_syscall *call);
void qemu_RegLoadMUIStringA(struct qemu_syscall *call);
void qemu_RegLoadMUIStringW(struct qemu_syscall *call);
void qemu_RegNotifyChangeKeyValue(struct qemu_syscall *call);
void qemu_RegOpenCurrentUser(struct qemu_syscall *call);
void qemu_RegOpenKeyA(struct qemu_syscall *call);
void qemu_RegOpenKeyExA(struct qemu_syscall *call);
void qemu_RegOpenKeyExW(struct qemu_syscall *call);
void qemu_RegOpenKeyW(struct qemu_syscall *call);
void qemu_RegOpenUserClassesRoot(struct qemu_syscall *call);
void qemu_RegOverridePredefKey(struct qemu_syscall *call);
void qemu_RegQueryInfoKeyA(struct qemu_syscall *call);
void qemu_RegQueryInfoKeyW(struct qemu_syscall *call);
void qemu_RegQueryMultipleValuesA(struct qemu_syscall *call);
void qemu_RegQueryMultipleValuesW(struct qemu_syscall *call);
void qemu_RegQueryValueA(struct qemu_syscall *call);
void qemu_RegQueryValueExA(struct qemu_syscall *call);
void qemu_RegQueryValueExW(struct qemu_syscall *call);
void qemu_RegQueryValueW(struct qemu_syscall *call);
void qemu_RegReplaceKeyA(struct qemu_syscall *call);
void qemu_RegReplaceKeyW(struct qemu_syscall *call);
void qemu_RegRestoreKeyA(struct qemu_syscall *call);
void qemu_RegRestoreKeyW(struct qemu_syscall *call);
void qemu_RegSaveKeyA(struct qemu_syscall *call);
void qemu_RegSaveKeyExA(struct qemu_syscall *call);
void qemu_RegSaveKeyExW(struct qemu_syscall *call);
void qemu_RegSaveKeyW(struct qemu_syscall *call);
void qemu_RegSetKeySecurity(struct qemu_syscall *call);
void qemu_RegSetKeyValueA(struct qemu_syscall *call);
void qemu_RegSetKeyValueW(struct qemu_syscall *call);
void qemu_RegSetValueA(struct qemu_syscall *call);
void qemu_RegSetValueExA(struct qemu_syscall *call);
void qemu_RegSetValueExW(struct qemu_syscall *call);
void qemu_RegSetValueW(struct qemu_syscall *call);
void qemu_RegUnLoadKeyA(struct qemu_syscall *call);
void qemu_RegUnLoadKeyW(struct qemu_syscall *call);
void qemu_RevertToSelf(struct qemu_syscall *call);
void qemu_SaferCloseLevel(struct qemu_syscall *call);
void qemu_SaferComputeTokenFromLevel(struct qemu_syscall *call);
void qemu_SaferCreateLevel(struct qemu_syscall *call);
void qemu_SaferGetPolicyInformation(struct qemu_syscall *call);
void qemu_SaferSetLevelInformation(struct qemu_syscall *call);
void qemu_SetAclInformation(struct qemu_syscall *call);
void qemu_SetEntriesInAclA(struct qemu_syscall *call);
void qemu_SetEntriesInAclW(struct qemu_syscall *call);
void qemu_SetFileSecurityA(struct qemu_syscall *call);
void qemu_SetFileSecurityW(struct qemu_syscall *call);
void qemu_SetKernelObjectSecurity(struct qemu_syscall *call);
void qemu_SetNamedSecurityInfoA(struct qemu_syscall *call);
void qemu_SetNamedSecurityInfoW(struct qemu_syscall *call);
void qemu_SetPrivateObjectSecurity(struct qemu_syscall *call);
void qemu_SetSecurityDescriptorControl(struct qemu_syscall *call);
void qemu_SetSecurityDescriptorDacl(struct qemu_syscall *call);
void qemu_SetSecurityDescriptorGroup(struct qemu_syscall *call);
void qemu_SetSecurityDescriptorOwner(struct qemu_syscall *call);
void qemu_SetSecurityDescriptorSacl(struct qemu_syscall *call);
void qemu_SetSecurityInfo(struct qemu_syscall *call);
void qemu_SetThreadToken(struct qemu_syscall *call);
void qemu_SetTokenInformation(struct qemu_syscall *call);
void qemu_SynchronizeWindows31FilesAndWindowsNTRegistry(struct qemu_syscall *call);
void qemu_SystemFunction030(struct qemu_syscall *call);
void qemu_SystemFunction035(struct qemu_syscall *call);
void qemu_SystemFunction036(struct qemu_syscall *call);
void qemu_SystemFunction040(struct qemu_syscall *call);
void qemu_SystemFunction041(struct qemu_syscall *call);
void qemu_TreeResetNamedSecurityInfoW(struct qemu_syscall *call);
void qemu_WriteEncryptedFileRaw(struct qemu_syscall *call);

#endif

#endif
