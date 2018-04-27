#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>

enum advapi32_calls
{
    CALL_A_SHAFINAL = 0,
    CALL_A_SHAINIT,
    CALL_A_SHAUPDATE,
    CALL_ABORTSYSTEMSHUTDOWNA,
    CALL_ABORTSYSTEMSHUTDOWNW,
    CALL_ACCESSCHECK,
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
    CALL_BACKUPEVENTLOGA,
    CALL_BACKUPEVENTLOGW,
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
    CALL_CHANGESERVICECONFIG2A,
    CALL_CHANGESERVICECONFIG2W,
    CALL_CHANGESERVICECONFIGA,
    CALL_CHANGESERVICECONFIGW,
    CALL_CHECKTOKENMEMBERSHIP,
    CALL_CLEAREVENTLOGA,
    CALL_CLEAREVENTLOGW,
    CALL_CLOSEENCRYPTEDFILERAW,
    CALL_CLOSEEVENTLOG,
    CALL_CLOSESERVICEHANDLE,
    CALL_CLOSETRACE,
    CALL_COMMANDLINEFROMMSIDESCRIPTOR,
    CALL_CONTROLSERVICE,
    CALL_CONTROLTRACEA,
    CALL_CONTROLTRACEW,
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
    CALL_CREATESERVICEA,
    CALL_CREATESERVICEW,
    CALL_CREATEWELLKNOWNSID,
    CALL_CREDDELETEA,
    CALL_CREDDELETEW,
    CALL_CREDENUMERATEA,
    CALL_CREDENUMERATEW,
    CALL_CREDFREE,
    CALL_CREDGETSESSIONTYPES,
    CALL_CREDISMARSHALEDCREDENTIALA,
    CALL_CREDISMARSHALEDCREDENTIALW,
    CALL_CREDMARSHALCREDENTIALA,
    CALL_CREDMARSHALCREDENTIALW,
    CALL_CREDREADA,
    CALL_CREDREADDOMAINCREDENTIALSA,
    CALL_CREDREADDOMAINCREDENTIALSW,
    CALL_CREDREADW,
    CALL_CREDUNMARSHALCREDENTIALA,
    CALL_CREDUNMARSHALCREDENTIALW,
    CALL_CREDWRITEA,
    CALL_CREDWRITEW,
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
    CALL_DELETESERVICE,
    CALL_DEREGISTEREVENTSOURCE,
    CALL_DESTROYPRIVATEOBJECTSECURITY,
    CALL_DUPLICATETOKEN,
    CALL_DUPLICATETOKENEX,
    CALL_ENABLETRACE,
    CALL_ENABLETRACEEX,
    CALL_ENABLETRACEEX2,
    CALL_ENCRYPTFILEA,
    CALL_ENCRYPTFILEW,
    CALL_ENUMDEPENDENTSERVICESA,
    CALL_ENUMDEPENDENTSERVICESW,
    CALL_ENUMERATETRACEGUIDS,
    CALL_ENUMSERVICESSTATUSA,
    CALL_ENUMSERVICESSTATUSEXA,
    CALL_ENUMSERVICESSTATUSEXW,
    CALL_ENUMSERVICESSTATUSW,
    CALL_EQUALPREFIXSID,
    CALL_EQUALSID,
    CALL_EVENTACTIVITYIDCONTROL,
    CALL_EVENTPROVIDERENABLED,
    CALL_EVENTWRITETRANSFER,
    CALL_FILEENCRYPTIONSTATUSA,
    CALL_FILEENCRYPTIONSTATUSW,
    CALL_FINDFIRSTFREEACE,
    CALL_FLUSHTRACEA,
    CALL_FLUSHTRACEW,
    CALL_FREESID,
    CALL_GETACE,
    CALL_GETACLINFORMATION,
    CALL_GETAUDITEDPERMISSIONSFROMACLA,
    CALL_GETAUDITEDPERMISSIONSFROMACLW,
    CALL_GETCURRENTHWPROFILEA,
    CALL_GETCURRENTHWPROFILEW,
    CALL_GETEFFECTIVERIGHTSFROMACLA,
    CALL_GETEFFECTIVERIGHTSFROMACLW,
    CALL_GETEVENTLOGINFORMATION,
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
    CALL_GETNUMBEROFEVENTLOGRECORDS,
    CALL_GETOLDESTEVENTLOGRECORD,
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
    CALL_GETSERVICEDISPLAYNAMEA,
    CALL_GETSERVICEDISPLAYNAMEW,
    CALL_GETSERVICEKEYNAMEA,
    CALL_GETSERVICEKEYNAMEW,
    CALL_GETSIDIDENTIFIERAUTHORITY,
    CALL_GETSIDLENGTHREQUIRED,
    CALL_GETSIDSUBAUTHORITY,
    CALL_GETSIDSUBAUTHORITYCOUNT,
    CALL_GETTOKENINFORMATION,
    CALL_GETTRACEENABLEFLAGS,
    CALL_GETTRACEENABLELEVEL,
    CALL_GETTRACELOGGERHANDLE,
    CALL_GETTRUSTEEFORMA,
    CALL_GETTRUSTEEFORMW,
    CALL_GETTRUSTEENAMEA,
    CALL_GETTRUSTEENAMEW,
    CALL_GETTRUSTEETYPEA,
    CALL_GETTRUSTEETYPEW,
    CALL_GETUSERNAMEA,
    CALL_GETUSERNAMEW,
    CALL_GETWINDOWSACCOUNTDOMAINSID,
    CALL_IMPERSONATEANONYMOUSTOKEN,
    CALL_IMPERSONATELOGGEDONUSER,
    CALL_IMPERSONATENAMEDPIPECLIENT,
    CALL_IMPERSONATESELF,
    CALL_INITIALIZEACL,
    CALL_INITIALIZESECURITYDESCRIPTOR,
    CALL_INITIALIZESID,
    CALL_INITIATESYSTEMSHUTDOWNA,
    CALL_INITIATESYSTEMSHUTDOWNEXA,
    CALL_INITIATESYSTEMSHUTDOWNEXW,
    CALL_INITIATESYSTEMSHUTDOWNW,
    CALL_ISTEXTUNICODE,
    CALL_ISTOKENRESTRICTED,
    CALL_ISVALIDACL,
    CALL_ISVALIDSECURITYDESCRIPTOR,
    CALL_ISVALIDSID,
    CALL_ISWELLKNOWNSID,
    CALL_LOCKSERVICEDATABASE,
    CALL_LOGONUSERA,
    CALL_LOGONUSERW,
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
    CALL_LSAADDACCOUNTRIGHTS,
    CALL_LSACLOSE,
    CALL_LSACREATETRUSTEDDOMAINEX,
    CALL_LSADELETETRUSTEDDOMAIN,
    CALL_LSAENUMERATEACCOUNTRIGHTS,
    CALL_LSAENUMERATEACCOUNTSWITHUSERRIGHT,
    CALL_LSAENUMERATETRUSTEDDOMAINS,
    CALL_LSAENUMERATETRUSTEDDOMAINSEX,
    CALL_LSAFREEMEMORY,
    CALL_LSALOOKUPNAMES,
    CALL_LSALOOKUPNAMES2,
    CALL_LSALOOKUPPRIVILEGENAME,
    CALL_LSALOOKUPSIDS,
    CALL_LSANTSTATUSTOWINERROR,
    CALL_LSAOPENPOLICY,
    CALL_LSAOPENTRUSTEDDOMAINBYNAME,
    CALL_LSAQUERYINFORMATIONPOLICY,
    CALL_LSAQUERYTRUSTEDDOMAININFO,
    CALL_LSAQUERYTRUSTEDDOMAININFOBYNAME,
    CALL_LSAREGISTERPOLICYCHANGENOTIFICATION,
    CALL_LSAREMOVEACCOUNTRIGHTS,
    CALL_LSARETRIEVEPRIVATEDATA,
    CALL_LSASETINFORMATIONPOLICY,
    CALL_LSASETSECRET,
    CALL_LSASETTRUSTEDDOMAININFOBYNAME,
    CALL_LSASETTRUSTEDDOMAININFORMATION,
    CALL_LSASTOREPRIVATEDATA,
    CALL_LSAUNREGISTERPOLICYCHANGENOTIFICATION,
    CALL_MAKEABSOLUTESD,
    CALL_MAKESELFRELATIVESD,
    CALL_MAPGENERICMASK,
    CALL_MD4FINAL,
    CALL_MD4INIT,
    CALL_MD4UPDATE,
    CALL_MD5FINAL,
    CALL_MD5INIT,
    CALL_MD5UPDATE,
    CALL_NOTIFYBOOTCONFIGSTATUS,
    CALL_NOTIFYCHANGEEVENTLOG,
    CALL_NOTIFYSERVICESTATUSCHANGEW,
    CALL_OBJECTCLOSEAUDITALARMA,
    CALL_OBJECTCLOSEAUDITALARMW,
    CALL_OBJECTDELETEAUDITALARMW,
    CALL_OBJECTOPENAUDITALARMA,
    CALL_OBJECTOPENAUDITALARMW,
    CALL_OBJECTPRIVILEGEAUDITALARMA,
    CALL_OBJECTPRIVILEGEAUDITALARMW,
    CALL_OPENBACKUPEVENTLOGA,
    CALL_OPENBACKUPEVENTLOGW,
    CALL_OPENENCRYPTEDFILERAWA,
    CALL_OPENENCRYPTEDFILERAWW,
    CALL_OPENEVENTLOGA,
    CALL_OPENEVENTLOGW,
    CALL_OPENPROCESSTOKEN,
    CALL_OPENSCMANAGERA,
    CALL_OPENSCMANAGERW,
    CALL_OPENSERVICEA,
    CALL_OPENSERVICEW,
    CALL_OPENTHREADTOKEN,
    CALL_OPENTRACEA,
    CALL_OPENTRACEW,
    CALL_PRIVILEGECHECK,
    CALL_PRIVILEGEDSERVICEAUDITALARMA,
    CALL_PRIVILEGEDSERVICEAUDITALARMW,
    CALL_PROCESSTRACE,
    CALL_QUERYALLTRACESA,
    CALL_QUERYALLTRACESW,
    CALL_QUERYSERVICECONFIG2A,
    CALL_QUERYSERVICECONFIG2W,
    CALL_QUERYSERVICECONFIGA,
    CALL_QUERYSERVICECONFIGW,
    CALL_QUERYSERVICELOCKSTATUSA,
    CALL_QUERYSERVICELOCKSTATUSW,
    CALL_QUERYSERVICEOBJECTSECURITY,
    CALL_QUERYSERVICESTATUS,
    CALL_QUERYSERVICESTATUSEX,
    CALL_QUERYTRACEW,
    CALL_QUERYWINDOWS31FILESMIGRATION,
    CALL_READENCRYPTEDFILERAW,
    CALL_READEVENTLOGA,
    CALL_READEVENTLOGW,
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
    CALL_REGISTEREVENTSOURCEA,
    CALL_REGISTEREVENTSOURCEW,
    CALL_REGISTERSERVICECTRLHANDLERA,
    CALL_REGISTERSERVICECTRLHANDLEREXA,
    CALL_REGISTERSERVICECTRLHANDLEREXW,
    CALL_REGISTERSERVICECTRLHANDLERW,
    CALL_REGISTERWAITCHAINCOMCALLBACK,
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
    CALL_REPORTEVENTA,
    CALL_REPORTEVENTW,
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
    CALL_SETSERVICEBITS,
    CALL_SETSERVICEOBJECTSECURITY,
    CALL_SETSERVICESTATUS,
    CALL_SETTHREADTOKEN,
    CALL_SETTOKENINFORMATION,
    CALL_STARTSERVICEA,
    CALL_STARTSERVICECTRLDISPATCHERA,
    CALL_STARTSERVICECTRLDISPATCHERW,
    CALL_STARTSERVICEW,
    CALL_STARTTRACEA,
    CALL_STARTTRACEW,
    CALL_STOPTRACEA,
    CALL_STOPTRACEW,
    CALL_SYNCHRONIZEWINDOWS31FILESANDWINDOWSNTREGISTRY,
    CALL_SYSTEMFUNCTION001,
    CALL_SYSTEMFUNCTION002,
    CALL_SYSTEMFUNCTION003,
    CALL_SYSTEMFUNCTION004,
    CALL_SYSTEMFUNCTION005,
    CALL_SYSTEMFUNCTION006,
    CALL_SYSTEMFUNCTION007,
    CALL_SYSTEMFUNCTION008,
    CALL_SYSTEMFUNCTION009,
    CALL_SYSTEMFUNCTION010,
    CALL_SYSTEMFUNCTION012,
    CALL_SYSTEMFUNCTION013,
    CALL_SYSTEMFUNCTION024,
    CALL_SYSTEMFUNCTION025,
    CALL_SYSTEMFUNCTION030,
    CALL_SYSTEMFUNCTION032,
    CALL_SYSTEMFUNCTION035,
    CALL_SYSTEMFUNCTION036,
    CALL_SYSTEMFUNCTION040,
    CALL_SYSTEMFUNCTION041,
    CALL_TRACEEVENT,
    CALL_TRACEMESSAGEVA,
    CALL_TREERESETNAMEDSECURITYINFOW,
    CALL_UNLOCKSERVICEDATABASE,
    CALL_WMIEXECUTEMETHODA,
    CALL_WMIEXECUTEMETHODW,
    CALL_WMIFREEBUFFER,
    CALL_WMIMOFENUMERATERESOURCESA,
    CALL_WMIMOFENUMERATERESOURCESW,
    CALL_WMINOTIFICATIONREGISTRATIONA,
    CALL_WMINOTIFICATIONREGISTRATIONW,
    CALL_WMIOPENBLOCK,
    CALL_WMIQUERYALLDATAA,
    CALL_WMIQUERYALLDATAW,
    CALL_WMIQUERYGUIDINFORMATION,
    CALL_WMISETSINGLEINSTANCEA,
    CALL_WMISETSINGLEINSTANCEW,
    CALL_WMISETSINGLEITEMA,
    CALL_WMISETSINGLEITEMW,
    CALL_WRITEENCRYPTEDFILERAW,
};

struct ustring
{
    DWORD Length;
    DWORD MaximumLength;
    unsigned char *Buffer;
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_A_SHAFinal(struct qemu_syscall *call);
void qemu_A_SHAInit(struct qemu_syscall *call);
void qemu_A_SHAUpdate(struct qemu_syscall *call);
void qemu_AbortSystemShutdownA(struct qemu_syscall *call);
void qemu_AbortSystemShutdownW(struct qemu_syscall *call);
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
void qemu_BackupEventLogA(struct qemu_syscall *call);
void qemu_BackupEventLogW(struct qemu_syscall *call);
void qemu_BuildExplicitAccessWithNameA(struct qemu_syscall *call);
void qemu_BuildExplicitAccessWithNameW(struct qemu_syscall *call);
void qemu_BuildSecurityDescriptorA(struct qemu_syscall *call);
void qemu_BuildSecurityDescriptorW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithNameA(struct qemu_syscall *call);
void qemu_BuildTrusteeWithNameW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndNameA(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndNameW(struct qemu_syscall *call);
void qemu_BuildTrusteeWithObjectsAndSid(struct qemu_syscall *call);
void qemu_BuildTrusteeWithSid(struct qemu_syscall *call);
void qemu_ChangeServiceConfig2A(struct qemu_syscall *call);
void qemu_ChangeServiceConfig2W(struct qemu_syscall *call);
void qemu_ChangeServiceConfigA(struct qemu_syscall *call);
void qemu_ChangeServiceConfigW(struct qemu_syscall *call);
void qemu_CheckTokenMembership(struct qemu_syscall *call);
void qemu_ClearEventLogA(struct qemu_syscall *call);
void qemu_ClearEventLogW(struct qemu_syscall *call);
void qemu_CloseEncryptedFileRaw(struct qemu_syscall *call);
void qemu_CloseEventLog(struct qemu_syscall *call);
void qemu_CloseServiceHandle(struct qemu_syscall *call);
void qemu_CloseTrace(struct qemu_syscall *call);
void qemu_CommandLineFromMsiDescriptor(struct qemu_syscall *call);
void qemu_ControlService(struct qemu_syscall *call);
void qemu_ControlTrace(struct qemu_syscall *call);
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
void qemu_CreateServiceA(struct qemu_syscall *call);
void qemu_CreateServiceW(struct qemu_syscall *call);
void qemu_CreateWellKnownSid(struct qemu_syscall *call);
void qemu_CredDeleteA(struct qemu_syscall *call);
void qemu_CredDeleteW(struct qemu_syscall *call);
void qemu_CredEnumerate(struct qemu_syscall *call);
void qemu_CredFree(struct qemu_syscall *call);
void qemu_CredGetSessionTypes(struct qemu_syscall *call);
void qemu_CredIsMarshaledCredentialA(struct qemu_syscall *call);
void qemu_CredIsMarshaledCredentialW(struct qemu_syscall *call);
void qemu_CredMarshalCredential(struct qemu_syscall *call);
void qemu_CredRead(struct qemu_syscall *call);
void qemu_CredReadDomainCredentialsA(struct qemu_syscall *call);
void qemu_CredReadDomainCredentialsW(struct qemu_syscall *call);
void qemu_CredUnmarshalCredentialA(struct qemu_syscall *call);
void qemu_CredUnmarshalCredentialW(struct qemu_syscall *call);
void qemu_CredWrite(struct qemu_syscall *call);
void qemu_CryptAcquireContext(struct qemu_syscall *call);
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
void qemu_DeleteService(struct qemu_syscall *call);
void qemu_DeregisterEventSource(struct qemu_syscall *call);
void qemu_DestroyPrivateObjectSecurity(struct qemu_syscall *call);
void qemu_DuplicateToken(struct qemu_syscall *call);
void qemu_DuplicateTokenEx(struct qemu_syscall *call);
void qemu_EnableTrace(struct qemu_syscall *call);
void qemu_EnableTraceEx(struct qemu_syscall *call);
void qemu_EnableTraceEx2(struct qemu_syscall *call);
void qemu_EncryptFileA(struct qemu_syscall *call);
void qemu_EncryptFileW(struct qemu_syscall *call);
void qemu_EnumDependentServicesA(struct qemu_syscall *call);
void qemu_EnumDependentServicesW(struct qemu_syscall *call);
void qemu_EnumerateTraceGuids(struct qemu_syscall *call);
void qemu_EnumServicesStatusA(struct qemu_syscall *call);
void qemu_EnumServicesStatusExA(struct qemu_syscall *call);
void qemu_EnumServicesStatusExW(struct qemu_syscall *call);
void qemu_EnumServicesStatusW(struct qemu_syscall *call);
void qemu_EqualPrefixSid(struct qemu_syscall *call);
void qemu_EqualSid(struct qemu_syscall *call);
void qemu_EventActivityIdControl(struct qemu_syscall *call);
void qemu_EventProviderEnabled(struct qemu_syscall *call);
void qemu_EventWriteTransfer(struct qemu_syscall *call);
void qemu_FileEncryptionStatusA(struct qemu_syscall *call);
void qemu_FileEncryptionStatusW(struct qemu_syscall *call);
void qemu_FindFirstFreeAce(struct qemu_syscall *call);
void qemu_FlushTrace(struct qemu_syscall *call);
void qemu_FreeSid(struct qemu_syscall *call);
void qemu_GetAce(struct qemu_syscall *call);
void qemu_GetAclInformation(struct qemu_syscall *call);
void qemu_GetAuditedPermissionsFromAclA(struct qemu_syscall *call);
void qemu_GetAuditedPermissionsFromAclW(struct qemu_syscall *call);
void qemu_GetCurrentHwProfileA(struct qemu_syscall *call);
void qemu_GetCurrentHwProfileW(struct qemu_syscall *call);
void qemu_GetEffectiveRightsFromAclA(struct qemu_syscall *call);
void qemu_GetEffectiveRightsFromAclW(struct qemu_syscall *call);
void qemu_GetEventLogInformation(struct qemu_syscall *call);
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
void qemu_GetNumberOfEventLogRecords(struct qemu_syscall *call);
void qemu_GetOldestEventLogRecord(struct qemu_syscall *call);
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
void qemu_GetServiceDisplayNameA(struct qemu_syscall *call);
void qemu_GetServiceDisplayNameW(struct qemu_syscall *call);
void qemu_GetServiceKeyNameA(struct qemu_syscall *call);
void qemu_GetServiceKeyNameW(struct qemu_syscall *call);
void qemu_GetSidIdentifierAuthority(struct qemu_syscall *call);
void qemu_GetSidLengthRequired(struct qemu_syscall *call);
void qemu_GetSidSubAuthority(struct qemu_syscall *call);
void qemu_GetSidSubAuthorityCount(struct qemu_syscall *call);
void qemu_GetTokenInformation(struct qemu_syscall *call);
void qemu_GetTraceEnableFlags(struct qemu_syscall *call);
void qemu_GetTraceEnableLevel(struct qemu_syscall *call);
void qemu_GetTraceLoggerHandle(struct qemu_syscall *call);
void qemu_GetTrusteeFormA(struct qemu_syscall *call);
void qemu_GetTrusteeFormW(struct qemu_syscall *call);
void qemu_GetTrusteeNameA(struct qemu_syscall *call);
void qemu_GetTrusteeNameW(struct qemu_syscall *call);
void qemu_GetTrusteeTypeA(struct qemu_syscall *call);
void qemu_GetTrusteeTypeW(struct qemu_syscall *call);
void qemu_GetUserNameA(struct qemu_syscall *call);
void qemu_GetUserNameW(struct qemu_syscall *call);
void qemu_GetWindowsAccountDomainSid(struct qemu_syscall *call);
void qemu_ImpersonateAnonymousToken(struct qemu_syscall *call);
void qemu_ImpersonateLoggedOnUser(struct qemu_syscall *call);
void qemu_ImpersonateNamedPipeClient(struct qemu_syscall *call);
void qemu_ImpersonateSelf(struct qemu_syscall *call);
void qemu_InitializeAcl(struct qemu_syscall *call);
void qemu_InitializeSecurityDescriptor(struct qemu_syscall *call);
void qemu_InitializeSid(struct qemu_syscall *call);
void qemu_InitiateSystemShutdownA(struct qemu_syscall *call);
void qemu_InitiateSystemShutdownExA(struct qemu_syscall *call);
void qemu_InitiateSystemShutdownExW(struct qemu_syscall *call);
void qemu_InitiateSystemShutdownW(struct qemu_syscall *call);
void qemu_IsTextUnicode(struct qemu_syscall *call);
void qemu_IsTokenRestricted(struct qemu_syscall *call);
void qemu_IsValidAcl(struct qemu_syscall *call);
void qemu_IsValidSecurityDescriptor(struct qemu_syscall *call);
void qemu_IsValidSid(struct qemu_syscall *call);
void qemu_IsWellKnownSid(struct qemu_syscall *call);
void qemu_LockServiceDatabase(struct qemu_syscall *call);
void qemu_LogonUserA(struct qemu_syscall *call);
void qemu_LogonUserW(struct qemu_syscall *call);
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
void qemu_LsaAddAccountRights(struct qemu_syscall *call);
void qemu_LsaClose(struct qemu_syscall *call);
void qemu_LsaCreateTrustedDomainEx(struct qemu_syscall *call);
void qemu_LsaDeleteTrustedDomain(struct qemu_syscall *call);
void qemu_LsaEnumerateAccountRights(struct qemu_syscall *call);
void qemu_LsaEnumerateAccountsWithUserRight(struct qemu_syscall *call);
void qemu_LsaEnumerateTrustedDomains(struct qemu_syscall *call);
void qemu_LsaEnumerateTrustedDomainsEx(struct qemu_syscall *call);
void qemu_LsaFreeMemory(struct qemu_syscall *call);
void qemu_LsaLookupNames(struct qemu_syscall *call);
void qemu_LsaLookupNames2(struct qemu_syscall *call);
void qemu_LsaLookupPrivilegeName(struct qemu_syscall *call);
void qemu_LsaLookupSids(struct qemu_syscall *call);
void qemu_LsaNtStatusToWinError(struct qemu_syscall *call);
void qemu_LsaOpenPolicy(struct qemu_syscall *call);
void qemu_LsaOpenTrustedDomainByName(struct qemu_syscall *call);
void qemu_LsaQueryInformationPolicy(struct qemu_syscall *call);
void qemu_LsaQueryTrustedDomainInfo(struct qemu_syscall *call);
void qemu_LsaQueryTrustedDomainInfoByName(struct qemu_syscall *call);
void qemu_LsaRegisterPolicyChangeNotification(struct qemu_syscall *call);
void qemu_LsaRemoveAccountRights(struct qemu_syscall *call);
void qemu_LsaRetrievePrivateData(struct qemu_syscall *call);
void qemu_LsaSetInformationPolicy(struct qemu_syscall *call);
void qemu_LsaSetSecret(struct qemu_syscall *call);
void qemu_LsaSetTrustedDomainInfoByName(struct qemu_syscall *call);
void qemu_LsaSetTrustedDomainInformation(struct qemu_syscall *call);
void qemu_LsaStorePrivateData(struct qemu_syscall *call);
void qemu_LsaUnregisterPolicyChangeNotification(struct qemu_syscall *call);
void qemu_MakeAbsoluteSD(struct qemu_syscall *call);
void qemu_MakeSelfRelativeSD(struct qemu_syscall *call);
void qemu_MapGenericMask(struct qemu_syscall *call);
void qemu_MD4Final(struct qemu_syscall *call);
void qemu_MD4Init(struct qemu_syscall *call);
void qemu_MD4Update(struct qemu_syscall *call);
void qemu_MD5Final(struct qemu_syscall *call);
void qemu_MD5Init(struct qemu_syscall *call);
void qemu_MD5Update(struct qemu_syscall *call);
void qemu_NotifyBootConfigStatus(struct qemu_syscall *call);
void qemu_NotifyChangeEventLog(struct qemu_syscall *call);
void qemu_NotifyServiceStatusChangeW(struct qemu_syscall *call);
void qemu_ObjectCloseAuditAlarmA(struct qemu_syscall *call);
void qemu_ObjectCloseAuditAlarmW(struct qemu_syscall *call);
void qemu_ObjectDeleteAuditAlarmW(struct qemu_syscall *call);
void qemu_ObjectOpenAuditAlarmA(struct qemu_syscall *call);
void qemu_ObjectOpenAuditAlarmW(struct qemu_syscall *call);
void qemu_ObjectPrivilegeAuditAlarmA(struct qemu_syscall *call);
void qemu_ObjectPrivilegeAuditAlarmW(struct qemu_syscall *call);
void qemu_OpenBackupEventLogA(struct qemu_syscall *call);
void qemu_OpenBackupEventLogW(struct qemu_syscall *call);
void qemu_OpenEncryptedFileRawA(struct qemu_syscall *call);
void qemu_OpenEncryptedFileRawW(struct qemu_syscall *call);
void qemu_OpenEventLogA(struct qemu_syscall *call);
void qemu_OpenEventLogW(struct qemu_syscall *call);
void qemu_OpenProcessToken(struct qemu_syscall *call);
void qemu_OpenSCManagerA(struct qemu_syscall *call);
void qemu_OpenSCManagerW(struct qemu_syscall *call);
void qemu_OpenServiceA(struct qemu_syscall *call);
void qemu_OpenServiceW(struct qemu_syscall *call);
void qemu_OpenThreadToken(struct qemu_syscall *call);
void qemu_OpenTraceA(struct qemu_syscall *call);
void qemu_OpenTraceW(struct qemu_syscall *call);
void qemu_PrivilegeCheck(struct qemu_syscall *call);
void qemu_PrivilegedServiceAuditAlarmA(struct qemu_syscall *call);
void qemu_PrivilegedServiceAuditAlarmW(struct qemu_syscall *call);
void qemu_ProcessTrace(struct qemu_syscall *call);
void qemu_QueryAllTracesA(struct qemu_syscall *call);
void qemu_QueryAllTracesW(struct qemu_syscall *call);
void qemu_QueryServiceConfig2A(struct qemu_syscall *call);
void qemu_QueryServiceConfig2W(struct qemu_syscall *call);
void qemu_QueryServiceConfigA(struct qemu_syscall *call);
void qemu_QueryServiceConfigW(struct qemu_syscall *call);
void qemu_QueryServiceLockStatusA(struct qemu_syscall *call);
void qemu_QueryServiceLockStatusW(struct qemu_syscall *call);
void qemu_QueryServiceObjectSecurity(struct qemu_syscall *call);
void qemu_QueryServiceStatus(struct qemu_syscall *call);
void qemu_QueryServiceStatusEx(struct qemu_syscall *call);
void qemu_QueryTraceW(struct qemu_syscall *call);
void qemu_QueryWindows31FilesMigration(struct qemu_syscall *call);
void qemu_ReadEncryptedFileRaw(struct qemu_syscall *call);
void qemu_ReadEventLogA(struct qemu_syscall *call);
void qemu_ReadEventLogW(struct qemu_syscall *call);
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
void qemu_RegisterEventSourceA(struct qemu_syscall *call);
void qemu_RegisterEventSourceW(struct qemu_syscall *call);
void qemu_RegisterServiceCtrlHandlerA(struct qemu_syscall *call);
void qemu_RegisterServiceCtrlHandlerExA(struct qemu_syscall *call);
void qemu_RegisterServiceCtrlHandlerExW(struct qemu_syscall *call);
void qemu_RegisterServiceCtrlHandlerW(struct qemu_syscall *call);
void qemu_RegisterWaitChainCOMCallback(struct qemu_syscall *call);
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
void qemu_ReportEvent(struct qemu_syscall *call);
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
void qemu_SetServiceBits(struct qemu_syscall *call);
void qemu_SetServiceObjectSecurity(struct qemu_syscall *call);
void qemu_SetServiceStatus(struct qemu_syscall *call);
void qemu_SetThreadToken(struct qemu_syscall *call);
void qemu_SetTokenInformation(struct qemu_syscall *call);
void qemu_StartServiceA(struct qemu_syscall *call);
void qemu_StartServiceCtrlDispatcherA(struct qemu_syscall *call);
void qemu_StartServiceCtrlDispatcherW(struct qemu_syscall *call);
void qemu_StartServiceW(struct qemu_syscall *call);
void qemu_StartTraceA(struct qemu_syscall *call);
void qemu_StartTraceW(struct qemu_syscall *call);
void qemu_StopTraceA(struct qemu_syscall *call);
void qemu_StopTraceW(struct qemu_syscall *call);
void qemu_SynchronizeWindows31FilesAndWindowsNTRegistry(struct qemu_syscall *call);
void qemu_SystemFunction001(struct qemu_syscall *call);
void qemu_SystemFunction002(struct qemu_syscall *call);
void qemu_SystemFunction003(struct qemu_syscall *call);
void qemu_SystemFunction004_5(struct qemu_syscall *call);
void qemu_SystemFunction006(struct qemu_syscall *call);
void qemu_SystemFunction007(struct qemu_syscall *call);
void qemu_SystemFunction008(struct qemu_syscall *call);
void qemu_SystemFunction009(struct qemu_syscall *call);
void qemu_SystemFunction010(struct qemu_syscall *call);
void qemu_SystemFunction012(struct qemu_syscall *call);
void qemu_SystemFunction013(struct qemu_syscall *call);
void qemu_SystemFunction024(struct qemu_syscall *call);
void qemu_SystemFunction025(struct qemu_syscall *call);
void qemu_SystemFunction030(struct qemu_syscall *call);
void qemu_SystemFunction032(struct qemu_syscall *call);
void qemu_SystemFunction035(struct qemu_syscall *call);
void qemu_SystemFunction036(struct qemu_syscall *call);
void qemu_SystemFunction040(struct qemu_syscall *call);
void qemu_SystemFunction041(struct qemu_syscall *call);
void qemu_TraceEvent(struct qemu_syscall *call);
void qemu_TraceMessageVa(struct qemu_syscall *call);
void qemu_TreeResetNamedSecurityInfoW(struct qemu_syscall *call);
void qemu_UnlockServiceDatabase(struct qemu_syscall *call);
void qemu_WmiExecuteMethodA(struct qemu_syscall *call);
void qemu_WmiExecuteMethodW(struct qemu_syscall *call);
void qemu_WmiFreeBuffer(struct qemu_syscall *call);
void qemu_WmiMofEnumerateResourcesA(struct qemu_syscall *call);
void qemu_WmiMofEnumerateResourcesW(struct qemu_syscall *call);
void qemu_WmiNotificationRegistrationA(struct qemu_syscall *call);
void qemu_WmiNotificationRegistrationW(struct qemu_syscall *call);
void qemu_WmiOpenBlock(struct qemu_syscall *call);
void qemu_WmiQueryAllDataA(struct qemu_syscall *call);
void qemu_WmiQueryAllDataW(struct qemu_syscall *call);
void qemu_WmiQueryGuidInformation(struct qemu_syscall *call);
void qemu_WmiSetSingleInstanceA(struct qemu_syscall *call);
void qemu_WmiSetSingleInstanceW(struct qemu_syscall *call);
void qemu_WmiSetSingleItemA(struct qemu_syscall *call);
void qemu_WmiSetSingleItemW(struct qemu_syscall *call);
void qemu_WriteEncryptedFileRaw(struct qemu_syscall *call);

/* Not a public struct, so it is here instead of the thunk headers. */
struct qemu_ustring
{
    DWORD Length;
    DWORD MaximumLength;
    qemu_ptr Buffer;
};

#endif

#endif
