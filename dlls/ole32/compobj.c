/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "ole32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ole32);
#endif


struct qemu_CoRevokeClassObject
{
    struct qemu_syscall super;
    uint64_t dwRegister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRevokeClassObject(DWORD dwRegister)
{
    struct qemu_CoRevokeClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREVOKECLASSOBJECT);
    call.dwRegister = (uint64_t)dwRegister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRevokeClassObject(struct qemu_syscall *call)
{
    struct qemu_CoRevokeClassObject *c = (struct qemu_CoRevokeClassObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRevokeClassObject(c->dwRegister);
}

#endif

struct qemu_CoBuildVersion
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CoBuildVersion(void)
{
    struct qemu_CoBuildVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COBUILDVERSION);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoBuildVersion(struct qemu_syscall *call)
{
    struct qemu_CoBuildVersion *c = (struct qemu_CoBuildVersion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoBuildVersion();
}

#endif

struct qemu_CoRegisterInitializeSpy
{
    struct qemu_syscall super;
    uint64_t spy;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterInitializeSpy(IInitializeSpy *spy, ULARGE_INTEGER *cookie)
{
    struct qemu_CoRegisterInitializeSpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERINITIALIZESPY);
    call.spy = (uint64_t)spy;
    call.cookie = (uint64_t)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRegisterInitializeSpy(struct qemu_syscall *call)
{
    struct qemu_CoRegisterInitializeSpy *c = (struct qemu_CoRegisterInitializeSpy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterInitializeSpy(QEMU_G2H(c->spy), QEMU_G2H(c->cookie));
}

#endif

struct qemu_CoRevokeInitializeSpy
{
    struct qemu_syscall super;
    uint64_t cookie_high;
    uint64_t cookie_low;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRevokeInitializeSpy(ULARGE_INTEGER cookie)
{
    struct qemu_CoRevokeInitializeSpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREVOKEINITIALIZESPY);
    call.cookie_high = cookie.HighPart;
    call.cookie_low = cookie.LowPart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRevokeInitializeSpy(struct qemu_syscall *call)
{
    struct qemu_CoRevokeInitializeSpy *c = (struct qemu_CoRevokeInitializeSpy *)call;
    ULARGE_INTEGER cookie;
    WINE_FIXME("Unverified!\n");
    cookie.HighPart = c->cookie_high;
    cookie.LowPart = c->cookie_low;
    c->super.iret = CoRevokeInitializeSpy(cookie);
}

#endif

struct qemu_CoInitialize
{
    struct qemu_syscall super;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoInitialize(LPVOID lpReserved)
{
    struct qemu_CoInitialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COINITIALIZE);
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoInitialize(struct qemu_syscall *call)
{
    struct qemu_CoInitialize *c = (struct qemu_CoInitialize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoInitialize(QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_CoInitializeEx
{
    struct qemu_syscall super;
    uint64_t lpReserved;
    uint64_t dwCoInit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoInitializeEx(LPVOID lpReserved, DWORD dwCoInit)
{
    struct qemu_CoInitializeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COINITIALIZEEX);
    call.lpReserved = (uint64_t)lpReserved;
    call.dwCoInit = (uint64_t)dwCoInit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoInitializeEx(struct qemu_syscall *call)
{
    struct qemu_CoInitializeEx *c = (struct qemu_CoInitializeEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoInitializeEx(QEMU_G2H(c->lpReserved), c->dwCoInit);
}

#endif

struct qemu_CoUninitialize
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CoUninitialize(void)
{
    struct qemu_CoUninitialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COUNINITIALIZE);

    qemu_syscall(&call.super);
}

#else

void qemu_CoUninitialize(struct qemu_syscall *call)
{
    struct qemu_CoUninitialize *c = (struct qemu_CoUninitialize *)call;
    WINE_FIXME("Unverified!\n");
    CoUninitialize();
}

#endif

struct qemu_CoDisconnectObject
{
    struct qemu_syscall super;
    uint64_t lpUnk;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoDisconnectObject(LPUNKNOWN lpUnk, DWORD reserved)
{
    struct qemu_CoDisconnectObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CODISCONNECTOBJECT);
    call.lpUnk = (uint64_t)lpUnk;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoDisconnectObject(struct qemu_syscall *call)
{
    struct qemu_CoDisconnectObject *c = (struct qemu_CoDisconnectObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoDisconnectObject(QEMU_G2H(c->lpUnk), c->reserved);
}

#endif

struct qemu_CoCreateGuid
{
    struct qemu_syscall super;
    uint64_t pguid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoCreateGuid(GUID *pguid)
{
    struct qemu_CoCreateGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COCREATEGUID);
    call.pguid = (uint64_t)pguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoCreateGuid(struct qemu_syscall *call)
{
    struct qemu_CoCreateGuid *c = (struct qemu_CoCreateGuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoCreateGuid(QEMU_G2H(c->pguid));
}

#endif

struct qemu_CLSIDFromString
{
    struct qemu_syscall super;
    uint64_t idstr;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CLSIDFromString(LPCOLESTR idstr, LPCLSID id)
{
    struct qemu_CLSIDFromString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLSIDFROMSTRING);
    call.idstr = (uint64_t)idstr;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CLSIDFromString(struct qemu_syscall *call)
{
    struct qemu_CLSIDFromString *c = (struct qemu_CLSIDFromString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CLSIDFromString(QEMU_G2H(c->idstr), QEMU_G2H(c->id));
}

#endif

struct qemu_IIDFromString
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI IIDFromString(LPCOLESTR s, IID *iid)
{
    struct qemu_IIDFromString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IIDFROMSTRING);
    call.s = (uint64_t)s;
    call.iid = (uint64_t)iid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IIDFromString(struct qemu_syscall *call)
{
    struct qemu_IIDFromString *c = (struct qemu_IIDFromString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IIDFromString(QEMU_G2H(c->s), QEMU_G2H(c->iid));
}

#endif

struct qemu_StringFromCLSID
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t idstr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI StringFromCLSID(REFCLSID id, LPOLESTR *idstr)
{
    struct qemu_StringFromCLSID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRINGFROMCLSID);
    call.id = (uint64_t)id;
    call.idstr = (uint64_t)idstr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StringFromCLSID(struct qemu_syscall *call)
{
    struct qemu_StringFromCLSID *c = (struct qemu_StringFromCLSID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StringFromCLSID(QEMU_G2H(c->id), QEMU_G2H(c->idstr));
}

#endif

struct qemu_StringFromGUID2
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t str;
    uint64_t cmax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StringFromGUID2(REFGUID id, LPOLESTR str, INT cmax)
{
    struct qemu_StringFromGUID2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRINGFROMGUID2);
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;
    call.cmax = (uint64_t)cmax;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StringFromGUID2(struct qemu_syscall *call)
{
    struct qemu_StringFromGUID2 *c = (struct qemu_StringFromGUID2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StringFromGUID2(QEMU_G2H(c->id), QEMU_G2H(c->str), c->cmax);
}

#endif

struct qemu_ProgIDFromCLSID
{
    struct qemu_syscall super;
    uint64_t clsid;
    uint64_t ppszProgID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ProgIDFromCLSID(REFCLSID clsid, LPOLESTR *ppszProgID)
{
    struct qemu_ProgIDFromCLSID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROGIDFROMCLSID);
    call.clsid = (uint64_t)clsid;
    call.ppszProgID = (uint64_t)ppszProgID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ProgIDFromCLSID(struct qemu_syscall *call)
{
    struct qemu_ProgIDFromCLSID *c = (struct qemu_ProgIDFromCLSID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ProgIDFromCLSID(QEMU_G2H(c->clsid), QEMU_G2H(c->ppszProgID));
}

#endif

struct qemu_CLSIDFromProgID
{
    struct qemu_syscall super;
    uint64_t progid;
    uint64_t clsid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CLSIDFromProgID(LPCOLESTR progid, LPCLSID clsid)
{
    struct qemu_CLSIDFromProgID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLSIDFROMPROGID);
    call.progid = (uint64_t)progid;
    call.clsid = (uint64_t)clsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CLSIDFromProgID(struct qemu_syscall *call)
{
    struct qemu_CLSIDFromProgID *c = (struct qemu_CLSIDFromProgID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CLSIDFromProgID(QEMU_G2H(c->progid), QEMU_G2H(c->clsid));
}

#endif

struct qemu_CLSIDFromProgIDEx
{
    struct qemu_syscall super;
    uint64_t progid;
    uint64_t clsid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CLSIDFromProgIDEx(LPCOLESTR progid, LPCLSID clsid)
{
    struct qemu_CLSIDFromProgIDEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLSIDFROMPROGIDEX);
    call.progid = (uint64_t)progid;
    call.clsid = (uint64_t)clsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CLSIDFromProgIDEx to Wine headers? */
extern HRESULT WINAPI CLSIDFromProgIDEx(LPCOLESTR progid, LPCLSID clsid);
void qemu_CLSIDFromProgIDEx(struct qemu_syscall *call)
{
    struct qemu_CLSIDFromProgIDEx *c = (struct qemu_CLSIDFromProgIDEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CLSIDFromProgIDEx(QEMU_G2H(c->progid), QEMU_G2H(c->clsid));
}

#endif

struct qemu_CoGetPSClsid
{
    struct qemu_syscall super;
    uint64_t riid;
    uint64_t pclsid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetPSClsid(REFIID riid, CLSID *pclsid)
{
    struct qemu_CoGetPSClsid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETPSCLSID);
    call.riid = (uint64_t)riid;
    call.pclsid = (uint64_t)pclsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetPSClsid(struct qemu_syscall *call)
{
    struct qemu_CoGetPSClsid *c = (struct qemu_CoGetPSClsid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetPSClsid(QEMU_G2H(c->riid), QEMU_G2H(c->pclsid));
}

#endif

struct qemu_CoRegisterPSClsid
{
    struct qemu_syscall super;
    uint64_t riid;
    uint64_t rclsid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterPSClsid(REFIID riid, REFCLSID rclsid)
{
    struct qemu_CoRegisterPSClsid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERPSCLSID);
    call.riid = (uint64_t)riid;
    call.rclsid = (uint64_t)rclsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRegisterPSClsid(struct qemu_syscall *call)
{
    struct qemu_CoRegisterPSClsid *c = (struct qemu_CoRegisterPSClsid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterPSClsid(QEMU_G2H(c->riid), QEMU_G2H(c->rclsid));
}

#endif

struct qemu_CoRegisterClassObject
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t pUnk;
    uint64_t dwClsContext;
    uint64_t flags;
    uint64_t lpdwRegister;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterClassObject(REFCLSID rclsid, LPUNKNOWN pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister)
{
    struct qemu_CoRegisterClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERCLASSOBJECT);
    call.rclsid = (uint64_t)rclsid;
    call.pUnk = (uint64_t)pUnk;
    call.dwClsContext = (uint64_t)dwClsContext;
    call.flags = (uint64_t)flags;
    call.lpdwRegister = (uint64_t)lpdwRegister;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRegisterClassObject(struct qemu_syscall *call)
{
    struct qemu_CoRegisterClassObject *c = (struct qemu_CoRegisterClassObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterClassObject(QEMU_G2H(QEMU_G2H(c->rclsid)), QEMU_G2H(c->pUnk), c->dwClsContext, c->flags, QEMU_G2H(c->lpdwRegister));
}

#endif

struct qemu_CoGetClassObject
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t dwClsContext;
    uint64_t pServerInfo;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetClassObject(REFCLSID rclsid, DWORD dwClsContext, void *pServerInfo, REFIID iid, LPVOID *ppv)
{
    struct qemu_CoGetClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETCLASSOBJECT);
    call.rclsid = (uint64_t)rclsid;
    call.dwClsContext = (uint64_t)dwClsContext;
    call.pServerInfo = (uint64_t)pServerInfo;
    call.iid = (uint64_t)iid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetClassObject(struct qemu_syscall *call)
{
    struct qemu_CoGetClassObject *c = (struct qemu_CoGetClassObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetClassObject(QEMU_G2H(QEMU_G2H(c->rclsid)), c->dwClsContext, QEMU_G2H(c->pServerInfo), QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoResumeClassObjects
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoResumeClassObjects(void)
{
    struct qemu_CoResumeClassObjects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CORESUMECLASSOBJECTS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoResumeClassObjects(struct qemu_syscall *call)
{
    struct qemu_CoResumeClassObjects *c = (struct qemu_CoResumeClassObjects *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoResumeClassObjects();
}

#endif

struct qemu_CoCreateInstance
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t pUnkOuter;
    uint64_t dwClsContext;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID iid, LPVOID *ppv)
{
    struct qemu_CoCreateInstance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COCREATEINSTANCE);
    call.rclsid = (uint64_t)rclsid;
    call.pUnkOuter = (uint64_t)pUnkOuter;
    call.dwClsContext = (uint64_t)dwClsContext;
    call.iid = (uint64_t)iid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoCreateInstance(struct qemu_syscall *call)
{
    struct qemu_CoCreateInstance *c = (struct qemu_CoCreateInstance *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoCreateInstance(QEMU_G2H(QEMU_G2H(c->rclsid)), QEMU_G2H(c->pUnkOuter), c->dwClsContext, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoCreateInstanceEx
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t pUnkOuter;
    uint64_t dwClsContext;
    uint64_t pServerInfo;
    uint64_t cmq;
    uint64_t pResults;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoCreateInstanceEx(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, COSERVERINFO* pServerInfo, ULONG cmq, MULTI_QI* pResults)
{
    struct qemu_CoCreateInstanceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COCREATEINSTANCEEX);
    call.rclsid = (uint64_t)rclsid;
    call.pUnkOuter = (uint64_t)pUnkOuter;
    call.dwClsContext = (uint64_t)dwClsContext;
    call.pServerInfo = (uint64_t)pServerInfo;
    call.cmq = (uint64_t)cmq;
    call.pResults = (uint64_t)pResults;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoCreateInstanceEx(struct qemu_syscall *call)
{
    struct qemu_CoCreateInstanceEx *c = (struct qemu_CoCreateInstanceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoCreateInstanceEx(QEMU_G2H(QEMU_G2H(c->rclsid)), QEMU_G2H(c->pUnkOuter), c->dwClsContext, QEMU_G2H(c->pServerInfo), c->cmq, QEMU_G2H(c->pResults));
}

#endif

struct qemu_CoGetInstanceFromFile
{
    struct qemu_syscall super;
    uint64_t server_info;
    uint64_t rclsid;
    uint64_t outer;
    uint64_t cls_context;
    uint64_t grfmode;
    uint64_t filename;
    uint64_t count;
    uint64_t results;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetInstanceFromFile(COSERVERINFO *server_info, CLSID *rclsid, IUnknown *outer, DWORD cls_context, DWORD grfmode, OLECHAR *filename, DWORD count, MULTI_QI *results)
{
    struct qemu_CoGetInstanceFromFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETINSTANCEFROMFILE);
    call.server_info = (uint64_t)server_info;
    call.rclsid = (uint64_t)rclsid;
    call.outer = (uint64_t)outer;
    call.cls_context = (uint64_t)cls_context;
    call.grfmode = (uint64_t)grfmode;
    call.filename = (uint64_t)filename;
    call.count = (uint64_t)count;
    call.results = (uint64_t)results;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetInstanceFromFile(struct qemu_syscall *call)
{
    struct qemu_CoGetInstanceFromFile *c = (struct qemu_CoGetInstanceFromFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetInstanceFromFile(QEMU_G2H(c->server_info), QEMU_G2H(QEMU_G2H(c->rclsid)), QEMU_G2H(c->outer), c->cls_context, c->grfmode, QEMU_G2H(c->filename), c->count, QEMU_G2H(c->results));
}

#endif

struct qemu_CoGetInstanceFromIStorage
{
    struct qemu_syscall super;
    uint64_t server_info;
    uint64_t rclsid;
    uint64_t outer;
    uint64_t cls_context;
    uint64_t storage;
    uint64_t count;
    uint64_t results;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetInstanceFromIStorage(COSERVERINFO *server_info, CLSID *rclsid, IUnknown *outer, DWORD cls_context, IStorage *storage, DWORD count, MULTI_QI *results)
{
    struct qemu_CoGetInstanceFromIStorage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETINSTANCEFROMISTORAGE);
    call.server_info = (uint64_t)server_info;
    call.rclsid = (uint64_t)rclsid;
    call.outer = (uint64_t)outer;
    call.cls_context = (uint64_t)cls_context;
    call.storage = (uint64_t)storage;
    call.count = (uint64_t)count;
    call.results = (uint64_t)results;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetInstanceFromIStorage(struct qemu_syscall *call)
{
    struct qemu_CoGetInstanceFromIStorage *c = (struct qemu_CoGetInstanceFromIStorage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetInstanceFromIStorage(QEMU_G2H(c->server_info), QEMU_G2H(QEMU_G2H(c->rclsid)), QEMU_G2H(c->outer), c->cls_context, QEMU_G2H(c->storage), c->count, QEMU_G2H(c->results));
}

#endif

struct qemu_CoLoadLibrary
{
    struct qemu_syscall super;
    uint64_t lpszLibName;
    uint64_t bAutoFree;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINSTANCE WINAPI CoLoadLibrary(LPOLESTR lpszLibName, BOOL bAutoFree)
{
    struct qemu_CoLoadLibrary call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COLOADLIBRARY);
    call.lpszLibName = (uint64_t)lpszLibName;
    call.bAutoFree = (uint64_t)bAutoFree;

    qemu_syscall(&call.super);

    return (HINSTANCE)call.super.iret;
}

#else

void qemu_CoLoadLibrary(struct qemu_syscall *call)
{
    struct qemu_CoLoadLibrary *c = (struct qemu_CoLoadLibrary *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CoLoadLibrary(QEMU_G2H(c->lpszLibName), c->bAutoFree);
}

#endif

struct qemu_CoFreeLibrary
{
    struct qemu_syscall super;
    uint64_t hLibrary;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CoFreeLibrary(HINSTANCE hLibrary)
{
    struct qemu_CoFreeLibrary call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COFREELIBRARY);
    call.hLibrary = (uint64_t)hLibrary;

    qemu_syscall(&call.super);
}

#else

void qemu_CoFreeLibrary(struct qemu_syscall *call)
{
    struct qemu_CoFreeLibrary *c = (struct qemu_CoFreeLibrary *)call;
    WINE_FIXME("Unverified!\n");
    CoFreeLibrary(QEMU_G2H(c->hLibrary));
}

#endif

struct qemu_CoFreeAllLibraries
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CoFreeAllLibraries(void)
{
    struct qemu_CoFreeAllLibraries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COFREEALLLIBRARIES);

    qemu_syscall(&call.super);
}

#else

void qemu_CoFreeAllLibraries(struct qemu_syscall *call)
{
    struct qemu_CoFreeAllLibraries *c = (struct qemu_CoFreeAllLibraries *)call;
    WINE_FIXME("Unverified!\n");
    CoFreeAllLibraries();
}

#endif

struct qemu_CoFreeUnusedLibrariesEx
{
    struct qemu_syscall super;
    uint64_t dwUnloadDelay;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CoFreeUnusedLibrariesEx(DWORD dwUnloadDelay, DWORD dwReserved)
{
    struct qemu_CoFreeUnusedLibrariesEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COFREEUNUSEDLIBRARIESEX);
    call.dwUnloadDelay = (uint64_t)dwUnloadDelay;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);
}

#else

void qemu_CoFreeUnusedLibrariesEx(struct qemu_syscall *call)
{
    struct qemu_CoFreeUnusedLibrariesEx *c = (struct qemu_CoFreeUnusedLibrariesEx *)call;
    WINE_FIXME("Unverified!\n");
    CoFreeUnusedLibrariesEx(c->dwUnloadDelay, c->dwReserved);
}

#endif

struct qemu_CoFreeUnusedLibraries
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CoFreeUnusedLibraries(void)
{
    struct qemu_CoFreeUnusedLibraries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COFREEUNUSEDLIBRARIES);

    qemu_syscall(&call.super);
}

#else

void qemu_CoFreeUnusedLibraries(struct qemu_syscall *call)
{
    struct qemu_CoFreeUnusedLibraries *c = (struct qemu_CoFreeUnusedLibraries *)call;
    WINE_FIXME("Unverified!\n");
    CoFreeUnusedLibraries();
}

#endif

struct qemu_CoFileTimeNow
{
    struct qemu_syscall super;
    uint64_t lpFileTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoFileTimeNow(FILETIME *lpFileTime)
{
    struct qemu_CoFileTimeNow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COFILETIMENOW);
    call.lpFileTime = (uint64_t)lpFileTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoFileTimeNow(struct qemu_syscall *call)
{
    struct qemu_CoFileTimeNow *c = (struct qemu_CoFileTimeNow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoFileTimeNow(QEMU_G2H(c->lpFileTime));
}

#endif

struct qemu_CoLockObjectExternal
{
    struct qemu_syscall super;
    uint64_t pUnk;
    uint64_t fLock;
    uint64_t fLastUnlockReleases;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoLockObjectExternal(LPUNKNOWN pUnk, BOOL fLock, BOOL fLastUnlockReleases)
{
    struct qemu_CoLockObjectExternal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COLOCKOBJECTEXTERNAL);
    call.pUnk = (uint64_t)pUnk;
    call.fLock = (uint64_t)fLock;
    call.fLastUnlockReleases = (uint64_t)fLastUnlockReleases;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoLockObjectExternal(struct qemu_syscall *call)
{
    struct qemu_CoLockObjectExternal *c = (struct qemu_CoLockObjectExternal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoLockObjectExternal(QEMU_G2H(c->pUnk), c->fLock, c->fLastUnlockReleases);
}

#endif

struct qemu_CoInitializeWOW
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoInitializeWOW(DWORD x,DWORD y)
{
    struct qemu_CoInitializeWOW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COINITIALIZEWOW);
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CoInitializeWOW to Wine headers? */
extern HRESULT WINAPI CoInitializeWOW(DWORD x,DWORD y);
void qemu_CoInitializeWOW(struct qemu_syscall *call)
{
    struct qemu_CoInitializeWOW *c = (struct qemu_CoInitializeWOW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoInitializeWOW(c->x, c->y);
}

#endif

struct qemu_CoGetState
{
    struct qemu_syscall super;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetState(IUnknown ** ppv)
{
    struct qemu_CoGetState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETSTATE);
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CoGetState to Wine headers? */
extern HRESULT WINAPI CoGetState(IUnknown ** ppv);
void qemu_CoGetState(struct qemu_syscall *call)
{
    struct qemu_CoGetState *c = (struct qemu_CoGetState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetState(QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoSetState
{
    struct qemu_syscall super;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoSetState(IUnknown * pv)
{
    struct qemu_CoSetState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSETSTATE);
    call.pv = (uint64_t)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CoSetState to Wine headers? */
extern HRESULT WINAPI CoSetState(IUnknown * pv);
void qemu_CoSetState(struct qemu_syscall *call)
{
    struct qemu_CoSetState *c = (struct qemu_CoSetState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoSetState(QEMU_G2H(c->pv));
}

#endif

struct qemu_CoTreatAsClass
{
    struct qemu_syscall super;
    uint64_t clsidOld;
    uint64_t clsidNew;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoTreatAsClass(REFCLSID clsidOld, REFCLSID clsidNew)
{
    struct qemu_CoTreatAsClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COTREATASCLASS);
    call.clsidOld = (uint64_t)clsidOld;
    call.clsidNew = (uint64_t)clsidNew;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoTreatAsClass(struct qemu_syscall *call)
{
    struct qemu_CoTreatAsClass *c = (struct qemu_CoTreatAsClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoTreatAsClass(QEMU_G2H(c->clsidOld), QEMU_G2H(c->clsidNew));
}

#endif

struct qemu_CoGetTreatAsClass
{
    struct qemu_syscall super;
    uint64_t clsidOld;
    uint64_t clsidNew;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetTreatAsClass(REFCLSID clsidOld, LPCLSID clsidNew)
{
    struct qemu_CoGetTreatAsClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETTREATASCLASS);
    call.clsidOld = (uint64_t)clsidOld;
    call.clsidNew = (uint64_t)clsidNew;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetTreatAsClass(struct qemu_syscall *call)
{
    struct qemu_CoGetTreatAsClass *c = (struct qemu_CoGetTreatAsClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetTreatAsClass(QEMU_G2H(c->clsidOld), QEMU_G2H(c->clsidNew));
}

#endif

struct qemu_CoGetCurrentProcess
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CoGetCurrentProcess(void)
{
    struct qemu_CoGetCurrentProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETCURRENTPROCESS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetCurrentProcess(struct qemu_syscall *call)
{
    struct qemu_CoGetCurrentProcess *c = (struct qemu_CoGetCurrentProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetCurrentProcess();
}

#endif

struct qemu_CoGetCurrentLogicalThreadId
{
    struct qemu_syscall super;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetCurrentLogicalThreadId(GUID *id)
{
    struct qemu_CoGetCurrentLogicalThreadId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETCURRENTLOGICALTHREADID);
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetCurrentLogicalThreadId(struct qemu_syscall *call)
{
    struct qemu_CoGetCurrentLogicalThreadId *c = (struct qemu_CoGetCurrentLogicalThreadId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetCurrentLogicalThreadId(QEMU_G2H(c->id));
}

#endif

struct qemu_CoRegisterMessageFilter
{
    struct qemu_syscall super;
    uint64_t lpMessageFilter;
    uint64_t lplpMessageFilter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter, LPMESSAGEFILTER *lplpMessageFilter)
{
    struct qemu_CoRegisterMessageFilter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERMESSAGEFILTER);
    call.lpMessageFilter = (uint64_t)lpMessageFilter;
    call.lplpMessageFilter = (uint64_t)lplpMessageFilter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRegisterMessageFilter(struct qemu_syscall *call)
{
    struct qemu_CoRegisterMessageFilter *c = (struct qemu_CoRegisterMessageFilter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterMessageFilter(QEMU_G2H(c->lpMessageFilter), QEMU_G2H(c->lplpMessageFilter));
}

#endif

struct qemu_CoIsOle1Class
{
    struct qemu_syscall super;
    uint64_t clsid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CoIsOle1Class(REFCLSID clsid)
{
    struct qemu_CoIsOle1Class call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COISOLE1CLASS);
    call.clsid = (uint64_t)clsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoIsOle1Class(struct qemu_syscall *call)
{
    struct qemu_CoIsOle1Class *c = (struct qemu_CoIsOle1Class *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoIsOle1Class(QEMU_G2H(c->clsid));
}

#endif

struct qemu_IsEqualGUID
{
    struct qemu_syscall super;
    uint64_t rguid1;
    uint64_t rguid2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI my_IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
    struct qemu_IsEqualGUID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISEQUALGUID);
    call.rguid1 = (uint64_t)rguid1;
    call.rguid2 = (uint64_t)rguid2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsEqualGUID(struct qemu_syscall *call)
{
    struct qemu_IsEqualGUID *c = (struct qemu_IsEqualGUID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsEqualGUID(QEMU_G2H(c->rguid1), QEMU_G2H(c->rguid2));
}

#endif

struct qemu_CoInitializeSecurity
{
    struct qemu_syscall super;
    uint64_t pSecDesc;
    uint64_t cAuthSvc;
    uint64_t asAuthSvc;
    uint64_t pReserved1;
    uint64_t dwAuthnLevel;
    uint64_t dwImpLevel;
    uint64_t pReserved2;
    uint64_t dwCapabilities;
    uint64_t pReserved3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoInitializeSecurity(PSECURITY_DESCRIPTOR pSecDesc, LONG cAuthSvc, SOLE_AUTHENTICATION_SERVICE* asAuthSvc, void* pReserved1, DWORD dwAuthnLevel, DWORD dwImpLevel, void* pReserved2, DWORD dwCapabilities, void* pReserved3)
{
    struct qemu_CoInitializeSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COINITIALIZESECURITY);
    call.pSecDesc = (uint64_t)pSecDesc;
    call.cAuthSvc = (uint64_t)cAuthSvc;
    call.asAuthSvc = (uint64_t)asAuthSvc;
    call.pReserved1 = (uint64_t)pReserved1;
    call.dwAuthnLevel = (uint64_t)dwAuthnLevel;
    call.dwImpLevel = (uint64_t)dwImpLevel;
    call.pReserved2 = (uint64_t)pReserved2;
    call.dwCapabilities = (uint64_t)dwCapabilities;
    call.pReserved3 = (uint64_t)pReserved3;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoInitializeSecurity(struct qemu_syscall *call)
{
    struct qemu_CoInitializeSecurity *c = (struct qemu_CoInitializeSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoInitializeSecurity(QEMU_G2H(c->pSecDesc), c->cAuthSvc, QEMU_G2H(c->asAuthSvc), QEMU_G2H(c->pReserved1), c->dwAuthnLevel, c->dwImpLevel, QEMU_G2H(c->pReserved2), c->dwCapabilities, QEMU_G2H(c->pReserved3));
}

#endif

struct qemu_CoSuspendClassObjects
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoSuspendClassObjects(void)
{
    struct qemu_CoSuspendClassObjects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSUSPENDCLASSOBJECTS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoSuspendClassObjects(struct qemu_syscall *call)
{
    struct qemu_CoSuspendClassObjects *c = (struct qemu_CoSuspendClassObjects *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoSuspendClassObjects();
}

#endif

struct qemu_CoAddRefServerProcess
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI CoAddRefServerProcess(void)
{
    struct qemu_CoAddRefServerProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COADDREFSERVERPROCESS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoAddRefServerProcess(struct qemu_syscall *call)
{
    struct qemu_CoAddRefServerProcess *c = (struct qemu_CoAddRefServerProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoAddRefServerProcess();
}

#endif

struct qemu_CoReleaseServerProcess
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI CoReleaseServerProcess(void)
{
    struct qemu_CoReleaseServerProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CORELEASESERVERPROCESS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoReleaseServerProcess(struct qemu_syscall *call)
{
    struct qemu_CoReleaseServerProcess *c = (struct qemu_CoReleaseServerProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoReleaseServerProcess();
}

#endif

struct qemu_CoIsHandlerConnected
{
    struct qemu_syscall super;
    uint64_t pUnk;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CoIsHandlerConnected(IUnknown *pUnk)
{
    struct qemu_CoIsHandlerConnected call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COISHANDLERCONNECTED);
    call.pUnk = (uint64_t)pUnk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoIsHandlerConnected(struct qemu_syscall *call)
{
    struct qemu_CoIsHandlerConnected *c = (struct qemu_CoIsHandlerConnected *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoIsHandlerConnected(QEMU_G2H(c->pUnk));
}

#endif

struct qemu_CoAllowSetForegroundWindow
{
    struct qemu_syscall super;
    uint64_t pUnk;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoAllowSetForegroundWindow(IUnknown *pUnk, void *pvReserved)
{
    struct qemu_CoAllowSetForegroundWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COALLOWSETFOREGROUNDWINDOW);
    call.pUnk = (uint64_t)pUnk;
    call.pvReserved = (uint64_t)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoAllowSetForegroundWindow(struct qemu_syscall *call)
{
    struct qemu_CoAllowSetForegroundWindow *c = (struct qemu_CoAllowSetForegroundWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoAllowSetForegroundWindow(QEMU_G2H(c->pUnk), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CoQueryProxyBlanket
{
    struct qemu_syscall super;
    uint64_t pProxy;
    uint64_t pAuthnSvc;
    uint64_t pAuthzSvc;
    uint64_t ppServerPrincName;
    uint64_t pAuthnLevel;
    uint64_t pImpLevel;
    uint64_t ppAuthInfo;
    uint64_t pCapabilities;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoQueryProxyBlanket(IUnknown *pProxy, DWORD *pAuthnSvc, DWORD *pAuthzSvc, OLECHAR **ppServerPrincName, DWORD *pAuthnLevel, DWORD *pImpLevel, void **ppAuthInfo, DWORD *pCapabilities)
{
    struct qemu_CoQueryProxyBlanket call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COQUERYPROXYBLANKET);
    call.pProxy = (uint64_t)pProxy;
    call.pAuthnSvc = (uint64_t)pAuthnSvc;
    call.pAuthzSvc = (uint64_t)pAuthzSvc;
    call.ppServerPrincName = (uint64_t)ppServerPrincName;
    call.pAuthnLevel = (uint64_t)pAuthnLevel;
    call.pImpLevel = (uint64_t)pImpLevel;
    call.ppAuthInfo = (uint64_t)ppAuthInfo;
    call.pCapabilities = (uint64_t)pCapabilities;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoQueryProxyBlanket(struct qemu_syscall *call)
{
    struct qemu_CoQueryProxyBlanket *c = (struct qemu_CoQueryProxyBlanket *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoQueryProxyBlanket(QEMU_G2H(c->pProxy), QEMU_G2H(c->pAuthnSvc), QEMU_G2H(c->pAuthzSvc), QEMU_G2H(c->ppServerPrincName), QEMU_G2H(c->pAuthnLevel), QEMU_G2H(c->pImpLevel), QEMU_G2H(c->ppAuthInfo), QEMU_G2H(c->pCapabilities));
}

#endif

struct qemu_CoSetProxyBlanket
{
    struct qemu_syscall super;
    uint64_t pProxy;
    uint64_t AuthnSvc;
    uint64_t AuthzSvc;
    uint64_t pServerPrincName;
    uint64_t AuthnLevel;
    uint64_t ImpLevel;
    uint64_t pAuthInfo;
    uint64_t Capabilities;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoSetProxyBlanket(IUnknown *pProxy, DWORD AuthnSvc, DWORD AuthzSvc, OLECHAR *pServerPrincName, DWORD AuthnLevel, DWORD ImpLevel, void *pAuthInfo, DWORD Capabilities)
{
    struct qemu_CoSetProxyBlanket call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSETPROXYBLANKET);
    call.pProxy = (uint64_t)pProxy;
    call.AuthnSvc = (uint64_t)AuthnSvc;
    call.AuthzSvc = (uint64_t)AuthzSvc;
    call.pServerPrincName = (uint64_t)pServerPrincName;
    call.AuthnLevel = (uint64_t)AuthnLevel;
    call.ImpLevel = (uint64_t)ImpLevel;
    call.pAuthInfo = (uint64_t)pAuthInfo;
    call.Capabilities = (uint64_t)Capabilities;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoSetProxyBlanket(struct qemu_syscall *call)
{
    struct qemu_CoSetProxyBlanket *c = (struct qemu_CoSetProxyBlanket *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoSetProxyBlanket(QEMU_G2H(c->pProxy), c->AuthnSvc, c->AuthzSvc, QEMU_G2H(c->pServerPrincName), c->AuthnLevel, c->ImpLevel, QEMU_G2H(c->pAuthInfo), c->Capabilities);
}

#endif

struct qemu_CoCopyProxy
{
    struct qemu_syscall super;
    uint64_t pProxy;
    uint64_t ppCopy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoCopyProxy(IUnknown *pProxy, IUnknown **ppCopy)
{
    struct qemu_CoCopyProxy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COCOPYPROXY);
    call.pProxy = (uint64_t)pProxy;
    call.ppCopy = (uint64_t)ppCopy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoCopyProxy(struct qemu_syscall *call)
{
    struct qemu_CoCopyProxy *c = (struct qemu_CoCopyProxy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoCopyProxy(QEMU_G2H(c->pProxy), QEMU_G2H(c->ppCopy));
}

#endif

struct qemu_CoGetCallContext
{
    struct qemu_syscall super;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetCallContext(REFIID riid, void **ppv)
{
    struct qemu_CoGetCallContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETCALLCONTEXT);
    call.riid = (uint64_t)riid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetCallContext(struct qemu_syscall *call)
{
    struct qemu_CoGetCallContext *c = (struct qemu_CoGetCallContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetCallContext(QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoSwitchCallContext
{
    struct qemu_syscall super;
    uint64_t pObject;
    uint64_t ppOldObject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoSwitchCallContext(IUnknown *pObject, IUnknown **ppOldObject)
{
    struct qemu_CoSwitchCallContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSWITCHCALLCONTEXT);
    call.pObject = (uint64_t)pObject;
    call.ppOldObject = (uint64_t)ppOldObject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoSwitchCallContext(struct qemu_syscall *call)
{
    struct qemu_CoSwitchCallContext *c = (struct qemu_CoSwitchCallContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoSwitchCallContext(QEMU_G2H(c->pObject), QEMU_G2H(c->ppOldObject));
}

#endif

struct qemu_CoQueryClientBlanket
{
    struct qemu_syscall super;
    uint64_t pAuthnSvc;
    uint64_t pAuthzSvc;
    uint64_t pServerPrincName;
    uint64_t pAuthnLevel;
    uint64_t pImpLevel;
    uint64_t pPrivs;
    uint64_t pCapabilities;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoQueryClientBlanket(DWORD *pAuthnSvc, DWORD *pAuthzSvc, OLECHAR **pServerPrincName, DWORD *pAuthnLevel, DWORD *pImpLevel, RPC_AUTHZ_HANDLE *pPrivs, DWORD *pCapabilities)
{
    struct qemu_CoQueryClientBlanket call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COQUERYCLIENTBLANKET);
    call.pAuthnSvc = (uint64_t)pAuthnSvc;
    call.pAuthzSvc = (uint64_t)pAuthzSvc;
    call.pServerPrincName = (uint64_t)pServerPrincName;
    call.pAuthnLevel = (uint64_t)pAuthnLevel;
    call.pImpLevel = (uint64_t)pImpLevel;
    call.pPrivs = (uint64_t)pPrivs;
    call.pCapabilities = (uint64_t)pCapabilities;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoQueryClientBlanket(struct qemu_syscall *call)
{
    struct qemu_CoQueryClientBlanket *c = (struct qemu_CoQueryClientBlanket *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoQueryClientBlanket(QEMU_G2H(c->pAuthnSvc), QEMU_G2H(c->pAuthzSvc), QEMU_G2H(c->pServerPrincName), QEMU_G2H(c->pAuthnLevel), QEMU_G2H(c->pImpLevel), QEMU_G2H(c->pPrivs), QEMU_G2H(c->pCapabilities));
}

#endif

struct qemu_CoImpersonateClient
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoImpersonateClient(void)
{
    struct qemu_CoImpersonateClient call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COIMPERSONATECLIENT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoImpersonateClient(struct qemu_syscall *call)
{
    struct qemu_CoImpersonateClient *c = (struct qemu_CoImpersonateClient *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoImpersonateClient();
}

#endif

struct qemu_CoRevertToSelf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRevertToSelf(void)
{
    struct qemu_CoRevertToSelf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREVERTTOSELF);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRevertToSelf(struct qemu_syscall *call)
{
    struct qemu_CoRevertToSelf *c = (struct qemu_CoRevertToSelf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRevertToSelf();
}

#endif

struct qemu_CoWaitForMultipleHandles
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t dwTimeout;
    uint64_t cHandles;
    uint64_t pHandles;
    uint64_t lpdwindex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoWaitForMultipleHandles(DWORD dwFlags, DWORD dwTimeout, ULONG cHandles, LPHANDLE pHandles, LPDWORD lpdwindex)
{
    struct qemu_CoWaitForMultipleHandles call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COWAITFORMULTIPLEHANDLES);
    call.dwFlags = (uint64_t)dwFlags;
    call.dwTimeout = (uint64_t)dwTimeout;
    call.cHandles = (uint64_t)cHandles;
    call.pHandles = (uint64_t)pHandles;
    call.lpdwindex = (uint64_t)lpdwindex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoWaitForMultipleHandles(struct qemu_syscall *call)
{
    struct qemu_CoWaitForMultipleHandles *c = (struct qemu_CoWaitForMultipleHandles *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoWaitForMultipleHandles(c->dwFlags, c->dwTimeout, c->cHandles, QEMU_G2H(c->pHandles), QEMU_G2H(c->lpdwindex));
}

#endif

struct qemu_CoGetObject
{
    struct qemu_syscall super;
    uint64_t pszName;
    uint64_t pBindOptions;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetObject(LPCWSTR pszName, BIND_OPTS *pBindOptions, REFIID riid, void **ppv)
{
    struct qemu_CoGetObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETOBJECT);
    call.pszName = (uint64_t)pszName;
    call.pBindOptions = (uint64_t)pBindOptions;
    call.riid = (uint64_t)riid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetObject(struct qemu_syscall *call)
{
    struct qemu_CoGetObject *c = (struct qemu_CoGetObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetObject(QEMU_G2H(c->pszName), QEMU_G2H(c->pBindOptions), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoRegisterChannelHook
{
    struct qemu_syscall super;
    uint64_t guidExtension;
    uint64_t pChannelHook;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterChannelHook(REFGUID guidExtension, IChannelHook *pChannelHook)
{
    struct qemu_CoRegisterChannelHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERCHANNELHOOK);
    call.guidExtension = (uint64_t)guidExtension;
    call.pChannelHook = (uint64_t)pChannelHook;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRegisterChannelHook(struct qemu_syscall *call)
{
    struct qemu_CoRegisterChannelHook *c = (struct qemu_CoRegisterChannelHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterChannelHook(QEMU_G2H(c->guidExtension), QEMU_G2H(c->pChannelHook));
}

#endif

struct qemu_CoGetObjectContext
{
    struct qemu_syscall super;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetObjectContext(REFIID riid, void **ppv)
{
    struct qemu_CoGetObjectContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETOBJECTCONTEXT);
    call.riid = (uint64_t)riid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetObjectContext(struct qemu_syscall *call)
{
    struct qemu_CoGetObjectContext *c = (struct qemu_CoGetObjectContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetObjectContext(QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoGetContextToken
{
    struct qemu_syscall super;
    uint64_t token;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetContextToken(ULONG_PTR *token)
{
    struct qemu_CoGetContextToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETCONTEXTTOKEN);
    call.token = (uint64_t)token;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetContextToken(struct qemu_syscall *call)
{
    struct qemu_CoGetContextToken *c = (struct qemu_CoGetContextToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetContextToken(QEMU_G2H(c->token));
}

#endif

struct qemu_CoGetDefaultContext
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetDefaultContext(APTTYPE type, REFIID riid, LPVOID *ppv)
{
    struct qemu_CoGetDefaultContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETDEFAULTCONTEXT);
    call.type = (uint64_t)type;
    call.riid = (uint64_t)riid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CoGetDefaultContext to Wine headers? */
extern HRESULT WINAPI CoGetDefaultContext(APTTYPE type, REFIID riid, LPVOID *ppv);
void qemu_CoGetDefaultContext(struct qemu_syscall *call)
{
    struct qemu_CoGetDefaultContext *c = (struct qemu_CoGetDefaultContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetDefaultContext(c->type, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_CoGetApartmentType
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t qualifier;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoGetApartmentType(APTTYPE *type, APTTYPEQUALIFIER *qualifier)
{
    struct qemu_CoGetApartmentType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COGETAPARTMENTTYPE);
    call.type = (uint64_t)type;
    call.qualifier = (uint64_t)qualifier;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoGetApartmentType(struct qemu_syscall *call)
{
    struct qemu_CoGetApartmentType *c = (struct qemu_CoGetApartmentType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoGetApartmentType(QEMU_G2H(c->type), QEMU_G2H(c->qualifier));
}

#endif

struct qemu_CoRegisterSurrogate
{
    struct qemu_syscall super;
    uint64_t surrogate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterSurrogate(ISurrogate *surrogate)
{
    struct qemu_CoRegisterSurrogate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERSURROGATE);
    call.surrogate = (uint64_t)surrogate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CoRegisterSurrogate(struct qemu_syscall *call)
{
    struct qemu_CoRegisterSurrogate *c = (struct qemu_CoRegisterSurrogate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterSurrogate(QEMU_G2H(c->surrogate));
}

#endif

struct qemu_CoRegisterSurrogateEx
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CoRegisterSurrogateEx(REFGUID guid, void *reserved)
{
    struct qemu_CoRegisterSurrogateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COREGISTERSURROGATEEX);
    call.guid = (uint64_t)guid;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CoRegisterSurrogateEx to Wine headers? */
extern HRESULT WINAPI CoRegisterSurrogateEx(REFGUID guid, void *reserved);
void qemu_CoRegisterSurrogateEx(struct qemu_syscall *call)
{
    struct qemu_CoRegisterSurrogateEx *c = (struct qemu_CoRegisterSurrogateEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CoRegisterSurrogateEx(QEMU_G2H(c->guid), QEMU_G2H(c->reserved));
}

#endif

