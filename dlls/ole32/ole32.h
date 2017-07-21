#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

enum ole32_calls
{
    CALL_CLSIDFROMPROGID,
    CALL_CLSIDFROMPROGIDEX,
    CALL_CLSIDFROMSTRING,
    CALL_COADDREFSERVERPROCESS,
    CALL_COALLOWSETFOREGROUNDWINDOW,
    CALL_COBUILDVERSION,
    CALL_COCOPYPROXY,
    CALL_COCREATEGUID,
    CALL_COCREATEINSTANCE,
    CALL_COCREATEINSTANCEEX,
    CALL_CODISCONNECTOBJECT,
    CALL_COFILETIMENOW,
    CALL_COFREEALLLIBRARIES,
    CALL_COFREELIBRARY,
    CALL_COFREEUNUSEDLIBRARIES,
    CALL_COFREEUNUSEDLIBRARIESEX,
    CALL_COGETAPARTMENTTYPE,
    CALL_COGETCALLCONTEXT,
    CALL_COGETCLASSOBJECT,
    CALL_COGETCONTEXTTOKEN,
    CALL_COGETCURRENTLOGICALTHREADID,
    CALL_COGETCURRENTPROCESS,
    CALL_COGETDEFAULTCONTEXT,
    CALL_COGETINSTANCEFROMFILE,
    CALL_COGETINSTANCEFROMISTORAGE,
    CALL_COGETOBJECT,
    CALL_COGETOBJECTCONTEXT,
    CALL_COGETPSCLSID,
    CALL_COGETSTATE,
    CALL_COGETTREATASCLASS,
    CALL_COIMPERSONATECLIENT,
    CALL_COINITIALIZE,
    CALL_COINITIALIZEEX,
    CALL_COINITIALIZESECURITY,
    CALL_COINITIALIZEWOW,
    CALL_COISHANDLERCONNECTED,
    CALL_COISOLE1CLASS,
    CALL_COLOADLIBRARY,
    CALL_COLOCKOBJECTEXTERNAL,
    CALL_COQUERYCLIENTBLANKET,
    CALL_COQUERYPROXYBLANKET,
    CALL_COREGISTERCHANNELHOOK,
    CALL_COREGISTERCLASSOBJECT,
    CALL_COREGISTERINITIALIZESPY,
    CALL_COREGISTERMESSAGEFILTER,
    CALL_COREGISTERPSCLSID,
    CALL_COREGISTERSURROGATE,
    CALL_COREGISTERSURROGATEEX,
    CALL_CORELEASESERVERPROCESS,
    CALL_CORESUMECLASSOBJECTS,
    CALL_COREVERTTOSELF,
    CALL_COREVOKECLASSOBJECT,
    CALL_COREVOKEINITIALIZESPY,
    CALL_COSETPROXYBLANKET,
    CALL_COSETSTATE,
    CALL_COSUSPENDCLASSOBJECTS,
    CALL_COSWITCHCALLCONTEXT,
    CALL_COTREATASCLASS,
    CALL_COUNINITIALIZE,
    CALL_COWAITFORMULTIPLEHANDLES,
    CALL_IIDFROMSTRING,
    CALL_ISEQUALGUID,
    CALL_PROGIDFROMCLSID,
    CALL_STRINGFROMCLSID,
    CALL_STRINGFROMGUID2,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_CLSIDFromProgID(struct qemu_syscall *call);
void qemu_CLSIDFromProgIDEx(struct qemu_syscall *call);
void qemu_CLSIDFromString(struct qemu_syscall *call);
void qemu_CoAddRefServerProcess(struct qemu_syscall *call);
void qemu_CoAllowSetForegroundWindow(struct qemu_syscall *call);
void qemu_CoBuildVersion(struct qemu_syscall *call);
void qemu_CoCopyProxy(struct qemu_syscall *call);
void qemu_CoCreateGuid(struct qemu_syscall *call);
void qemu_CoCreateInstance(struct qemu_syscall *call);
void qemu_CoCreateInstanceEx(struct qemu_syscall *call);
void qemu_CoDisconnectObject(struct qemu_syscall *call);
void qemu_CoFileTimeNow(struct qemu_syscall *call);
void qemu_CoFreeAllLibraries(struct qemu_syscall *call);
void qemu_CoFreeLibrary(struct qemu_syscall *call);
void qemu_CoFreeUnusedLibraries(struct qemu_syscall *call);
void qemu_CoFreeUnusedLibrariesEx(struct qemu_syscall *call);
void qemu_CoGetApartmentType(struct qemu_syscall *call);
void qemu_CoGetCallContext(struct qemu_syscall *call);
void qemu_CoGetClassObject(struct qemu_syscall *call);
void qemu_CoGetContextToken(struct qemu_syscall *call);
void qemu_CoGetCurrentLogicalThreadId(struct qemu_syscall *call);
void qemu_CoGetCurrentProcess(struct qemu_syscall *call);
void qemu_CoGetDefaultContext(struct qemu_syscall *call);
void qemu_CoGetInstanceFromFile(struct qemu_syscall *call);
void qemu_CoGetInstanceFromIStorage(struct qemu_syscall *call);
void qemu_CoGetObject(struct qemu_syscall *call);
void qemu_CoGetObjectContext(struct qemu_syscall *call);
void qemu_CoGetPSClsid(struct qemu_syscall *call);
void qemu_CoGetState(struct qemu_syscall *call);
void qemu_CoGetTreatAsClass(struct qemu_syscall *call);
void qemu_CoImpersonateClient(struct qemu_syscall *call);
void qemu_CoInitialize(struct qemu_syscall *call);
void qemu_CoInitializeEx(struct qemu_syscall *call);
void qemu_CoInitializeSecurity(struct qemu_syscall *call);
void qemu_CoInitializeWOW(struct qemu_syscall *call);
void qemu_CoIsHandlerConnected(struct qemu_syscall *call);
void qemu_CoIsOle1Class(struct qemu_syscall *call);
void qemu_CoLoadLibrary(struct qemu_syscall *call);
void qemu_CoLockObjectExternal(struct qemu_syscall *call);
void qemu_CoQueryClientBlanket(struct qemu_syscall *call);
void qemu_CoQueryProxyBlanket(struct qemu_syscall *call);
void qemu_CoRegisterChannelHook(struct qemu_syscall *call);
void qemu_CoRegisterClassObject(struct qemu_syscall *call);
void qemu_CoRegisterInitializeSpy(struct qemu_syscall *call);
void qemu_CoRegisterMessageFilter(struct qemu_syscall *call);
void qemu_CoRegisterPSClsid(struct qemu_syscall *call);
void qemu_CoRegisterSurrogate(struct qemu_syscall *call);
void qemu_CoRegisterSurrogateEx(struct qemu_syscall *call);
void qemu_CoReleaseServerProcess(struct qemu_syscall *call);
void qemu_CoResumeClassObjects(struct qemu_syscall *call);
void qemu_CoRevertToSelf(struct qemu_syscall *call);
void qemu_CoRevokeClassObject(struct qemu_syscall *call);
void qemu_CoRevokeInitializeSpy(struct qemu_syscall *call);
void qemu_CoSetProxyBlanket(struct qemu_syscall *call);
void qemu_CoSetState(struct qemu_syscall *call);
void qemu_CoSuspendClassObjects(struct qemu_syscall *call);
void qemu_CoSwitchCallContext(struct qemu_syscall *call);
void qemu_CoTreatAsClass(struct qemu_syscall *call);
void qemu_CoUninitialize(struct qemu_syscall *call);
void qemu_CoWaitForMultipleHandles(struct qemu_syscall *call);
void qemu_IIDFromString(struct qemu_syscall *call);
void qemu_IsEqualGUID(struct qemu_syscall *call);
void qemu_ProgIDFromCLSID(struct qemu_syscall *call);
void qemu_StringFromCLSID(struct qemu_syscall *call);
void qemu_StringFromGUID2(struct qemu_syscall *call);

#endif

#endif
