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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_DdeConnectList
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hszService;
    uint64_t hszTopic;
    uint64_t hConvList;
    uint64_t pCC;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HCONVLIST WINAPI DdeConnectList(DWORD idInst, HSZ hszService, HSZ hszTopic, HCONVLIST hConvList, PCONVCONTEXT pCC)
{
    struct qemu_DdeConnectList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECONNECTLIST);
    call.idInst = (ULONG_PTR)idInst;
    call.hszService = (ULONG_PTR)hszService;
    call.hszTopic = (ULONG_PTR)hszTopic;
    call.hConvList = (ULONG_PTR)hConvList;
    call.pCC = (ULONG_PTR)pCC;

    qemu_syscall(&call.super);

    return (HCONVLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeConnectList(struct qemu_syscall *call)
{
    struct qemu_DdeConnectList *c = (struct qemu_DdeConnectList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeConnectList(c->idInst, QEMU_G2H(c->hszService), QEMU_G2H(c->hszTopic), QEMU_G2H(c->hConvList), QEMU_G2H(c->pCC));
}

#endif

struct qemu_DdeQueryNextServer
{
    struct qemu_syscall super;
    uint64_t hConvList;
    uint64_t hConvPrev;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HCONV WINAPI DdeQueryNextServer(HCONVLIST hConvList, HCONV hConvPrev)
{
    struct qemu_DdeQueryNextServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEQUERYNEXTSERVER);
    call.hConvList = (ULONG_PTR)hConvList;
    call.hConvPrev = (ULONG_PTR)hConvPrev;

    qemu_syscall(&call.super);

    return (HCONV)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeQueryNextServer(struct qemu_syscall *call)
{
    struct qemu_DdeQueryNextServer *c = (struct qemu_DdeQueryNextServer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeQueryNextServer(QEMU_G2H(c->hConvList), QEMU_G2H(c->hConvPrev));
}

#endif

struct qemu_DdeDisconnectList
{
    struct qemu_syscall super;
    uint64_t hConvList;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeDisconnectList(HCONVLIST hConvList)
{
    struct qemu_DdeDisconnectList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEDISCONNECTLIST);
    call.hConvList = (ULONG_PTR)hConvList;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeDisconnectList(struct qemu_syscall *call)
{
    struct qemu_DdeDisconnectList *c = (struct qemu_DdeDisconnectList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeDisconnectList(QEMU_G2H(c->hConvList));
}

#endif

struct qemu_DdeConnect
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hszService;
    uint64_t hszTopic;
    uint64_t pCC;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HCONV WINAPI DdeConnect(DWORD idInst, HSZ hszService, HSZ hszTopic, PCONVCONTEXT pCC)
{
    struct qemu_DdeConnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECONNECT);
    call.idInst = (ULONG_PTR)idInst;
    call.hszService = (ULONG_PTR)hszService;
    call.hszTopic = (ULONG_PTR)hszTopic;
    call.pCC = (ULONG_PTR)pCC;

    qemu_syscall(&call.super);

    return (HCONV)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeConnect(struct qemu_syscall *call)
{
    struct qemu_DdeConnect *c = (struct qemu_DdeConnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeConnect(c->idInst, QEMU_G2H(c->hszService), QEMU_G2H(c->hszTopic), QEMU_G2H(c->pCC));
}

#endif

struct qemu_DdeReconnect
{
    struct qemu_syscall super;
    uint64_t hConv;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HCONV WINAPI DdeReconnect(HCONV hConv)
{
    struct qemu_DdeReconnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDERECONNECT);
    call.hConv = (ULONG_PTR)hConv;

    qemu_syscall(&call.super);

    return (HCONV)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeReconnect(struct qemu_syscall *call)
{
    struct qemu_DdeReconnect *c = (struct qemu_DdeReconnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeReconnect(QEMU_G2H(c->hConv));
}

#endif

struct qemu_DdeClientTransaction
{
    struct qemu_syscall super;
    uint64_t pData;
    uint64_t cbData;
    uint64_t hConv;
    uint64_t hszItem;
    uint64_t wFmt;
    uint64_t wType;
    uint64_t dwTimeout;
    uint64_t pdwResult;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDDEDATA WINAPI DdeClientTransaction(LPBYTE pData, DWORD cbData, HCONV hConv, HSZ hszItem, UINT wFmt, UINT wType, DWORD dwTimeout, LPDWORD pdwResult)
{
    struct qemu_DdeClientTransaction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECLIENTTRANSACTION);
    call.pData = (ULONG_PTR)pData;
    call.cbData = (ULONG_PTR)cbData;
    call.hConv = (ULONG_PTR)hConv;
    call.hszItem = (ULONG_PTR)hszItem;
    call.wFmt = (ULONG_PTR)wFmt;
    call.wType = (ULONG_PTR)wType;
    call.dwTimeout = (ULONG_PTR)dwTimeout;
    call.pdwResult = (ULONG_PTR)pdwResult;

    qemu_syscall(&call.super);

    return (HDDEDATA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeClientTransaction(struct qemu_syscall *call)
{
    struct qemu_DdeClientTransaction *c = (struct qemu_DdeClientTransaction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeClientTransaction(QEMU_G2H(c->pData), c->cbData, QEMU_G2H(c->hConv), QEMU_G2H(c->hszItem), c->wFmt, c->wType, c->dwTimeout, QEMU_G2H(c->pdwResult));
}

#endif

struct qemu_DdeAbandonTransaction
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hConv;
    uint64_t idTransaction;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeAbandonTransaction(DWORD idInst, HCONV hConv, DWORD idTransaction)
{
    struct qemu_DdeAbandonTransaction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEABANDONTRANSACTION);
    call.idInst = (ULONG_PTR)idInst;
    call.hConv = (ULONG_PTR)hConv;
    call.idTransaction = (ULONG_PTR)idTransaction;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeAbandonTransaction(struct qemu_syscall *call)
{
    struct qemu_DdeAbandonTransaction *c = (struct qemu_DdeAbandonTransaction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeAbandonTransaction(c->idInst, QEMU_G2H(c->hConv), c->idTransaction);
}

#endif

struct qemu_DdeDisconnect
{
    struct qemu_syscall super;
    uint64_t hConv;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeDisconnect(HCONV hConv)
{
    struct qemu_DdeDisconnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEDISCONNECT);
    call.hConv = (ULONG_PTR)hConv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeDisconnect(struct qemu_syscall *call)
{
    struct qemu_DdeDisconnect *c = (struct qemu_DdeDisconnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeDisconnect(QEMU_G2H(c->hConv));
}

#endif

struct qemu_DdeImpersonateClient
{
    struct qemu_syscall super;
    uint64_t hConv;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeImpersonateClient(HCONV hConv)
{
    struct qemu_DdeImpersonateClient call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEIMPERSONATECLIENT);
    call.hConv = (ULONG_PTR)hConv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeImpersonateClient(struct qemu_syscall *call)
{
    struct qemu_DdeImpersonateClient *c = (struct qemu_DdeImpersonateClient *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeImpersonateClient(QEMU_G2H(c->hConv));
}

#endif

struct qemu_PackDDElParam
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t uiLo;
    uint64_t uiHi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPARAM WINAPI PackDDElParam(UINT msg, UINT_PTR uiLo, UINT_PTR uiHi)
{
    struct qemu_PackDDElParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PACKDDELPARAM);
    call.msg = (ULONG_PTR)msg;
    call.uiLo = (ULONG_PTR)uiLo;
    call.uiHi = (ULONG_PTR)uiHi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PackDDElParam(struct qemu_syscall *call)
{
    struct qemu_PackDDElParam *c = (struct qemu_PackDDElParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PackDDElParam(c->msg, c->uiLo, c->uiHi);
}

#endif

struct qemu_UnpackDDElParam
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t lParam;
    uint64_t uiLo;
    uint64_t uiHi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnpackDDElParam(UINT msg, LPARAM lParam, PUINT_PTR uiLo, PUINT_PTR uiHi)
{
    struct qemu_UnpackDDElParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNPACKDDELPARAM);
    call.msg = (ULONG_PTR)msg;
    call.lParam = (ULONG_PTR)lParam;
    call.uiLo = (ULONG_PTR)uiLo;
    call.uiHi = (ULONG_PTR)uiHi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnpackDDElParam(struct qemu_syscall *call)
{
    struct qemu_UnpackDDElParam *c = (struct qemu_UnpackDDElParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnpackDDElParam(c->msg, c->lParam, QEMU_G2H(c->uiLo), QEMU_G2H(c->uiHi));
}

#endif

struct qemu_FreeDDElParam
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI FreeDDElParam(UINT msg, LPARAM lParam)
{
    struct qemu_FreeDDElParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEDDELPARAM);
    call.msg = (ULONG_PTR)msg;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeDDElParam(struct qemu_syscall *call)
{
    struct qemu_FreeDDElParam *c = (struct qemu_FreeDDElParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeDDElParam(c->msg, c->lParam);
}

#endif

struct qemu_ReuseDDElParam
{
    struct qemu_syscall super;
    uint64_t lParam;
    uint64_t msgIn;
    uint64_t msgOut;
    uint64_t uiLo;
    uint64_t uiHi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPARAM WINAPI ReuseDDElParam(LPARAM lParam, UINT msgIn, UINT msgOut, UINT_PTR uiLo, UINT_PTR uiHi)
{
    struct qemu_ReuseDDElParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REUSEDDELPARAM);
    call.lParam = (ULONG_PTR)lParam;
    call.msgIn = (ULONG_PTR)msgIn;
    call.msgOut = (ULONG_PTR)msgOut;
    call.uiLo = (ULONG_PTR)uiLo;
    call.uiHi = (ULONG_PTR)uiHi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReuseDDElParam(struct qemu_syscall *call)
{
    struct qemu_ReuseDDElParam *c = (struct qemu_ReuseDDElParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReuseDDElParam(c->lParam, c->msgIn, c->msgOut, c->uiLo, c->uiHi);
}

#endif

struct qemu_ImpersonateDdeClientWindow
{
    struct qemu_syscall super;
    uint64_t hWndClient;
    uint64_t hWndServer;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ImpersonateDdeClientWindow(HWND hWndClient, HWND hWndServer)
{
    struct qemu_ImpersonateDdeClientWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPERSONATEDDECLIENTWINDOW);
    call.hWndClient = (ULONG_PTR)hWndClient;
    call.hWndServer = (ULONG_PTR)hWndServer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImpersonateDdeClientWindow(struct qemu_syscall *call)
{
    struct qemu_ImpersonateDdeClientWindow *c = (struct qemu_ImpersonateDdeClientWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImpersonateDdeClientWindow(QEMU_G2H(c->hWndClient), QEMU_G2H(c->hWndServer));
}

#endif

struct qemu_DdeSetQualityOfService
{
    struct qemu_syscall super;
    uint64_t hwndClient;
    uint64_t pqosNew;
    uint64_t pqosPrev;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeSetQualityOfService(HWND hwndClient, const SECURITY_QUALITY_OF_SERVICE *pqosNew, PSECURITY_QUALITY_OF_SERVICE pqosPrev)
{
    struct qemu_DdeSetQualityOfService call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDESETQUALITYOFSERVICE);
    call.hwndClient = (ULONG_PTR)hwndClient;
    call.pqosNew = (ULONG_PTR)pqosNew;
    call.pqosPrev = (ULONG_PTR)pqosPrev;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeSetQualityOfService(struct qemu_syscall *call)
{
    struct qemu_DdeSetQualityOfService *c = (struct qemu_DdeSetQualityOfService *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeSetQualityOfService(QEMU_G2H(c->hwndClient), QEMU_G2H(c->pqosNew), QEMU_G2H(c->pqosPrev));
}

#endif

struct qemu_DdeGetLastError
{
    struct qemu_syscall super;
    uint64_t idInst;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI DdeGetLastError(DWORD idInst)
{
    struct qemu_DdeGetLastError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEGETLASTERROR);
    call.idInst = (ULONG_PTR)idInst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeGetLastError(struct qemu_syscall *call)
{
    struct qemu_DdeGetLastError *c = (struct qemu_DdeGetLastError *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeGetLastError(c->idInst);
}

#endif

struct qemu_DdeQueryStringA
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hsz;
    uint64_t psz;
    uint64_t cchMax;
    uint64_t iCodePage;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI DdeQueryStringA(DWORD idInst, HSZ hsz, LPSTR psz, DWORD cchMax, INT iCodePage)
{
    struct qemu_DdeQueryStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEQUERYSTRINGA);
    call.idInst = (ULONG_PTR)idInst;
    call.hsz = (ULONG_PTR)hsz;
    call.psz = (ULONG_PTR)psz;
    call.cchMax = (ULONG_PTR)cchMax;
    call.iCodePage = (ULONG_PTR)iCodePage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeQueryStringA(struct qemu_syscall *call)
{
    struct qemu_DdeQueryStringA *c = (struct qemu_DdeQueryStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeQueryStringA(c->idInst, QEMU_G2H(c->hsz), QEMU_G2H(c->psz), c->cchMax, c->iCodePage);
}

#endif

struct qemu_DdeQueryStringW
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hsz;
    uint64_t psz;
    uint64_t cchMax;
    uint64_t iCodePage;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI DdeQueryStringW(DWORD idInst, HSZ hsz, LPWSTR psz, DWORD cchMax, INT iCodePage)
{
    struct qemu_DdeQueryStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEQUERYSTRINGW);
    call.idInst = (ULONG_PTR)idInst;
    call.hsz = (ULONG_PTR)hsz;
    call.psz = (ULONG_PTR)psz;
    call.cchMax = (ULONG_PTR)cchMax;
    call.iCodePage = (ULONG_PTR)iCodePage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeQueryStringW(struct qemu_syscall *call)
{
    struct qemu_DdeQueryStringW *c = (struct qemu_DdeQueryStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeQueryStringW(c->idInst, QEMU_G2H(c->hsz), QEMU_G2H(c->psz), c->cchMax, c->iCodePage);
}

#endif

struct qemu_DdeCreateStringHandleA
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t psz;
    uint64_t codepage;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HSZ WINAPI DdeCreateStringHandleA(DWORD idInst, LPCSTR psz, INT codepage)
{
    struct qemu_DdeCreateStringHandleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECREATESTRINGHANDLEA);
    call.idInst = (ULONG_PTR)idInst;
    call.psz = (ULONG_PTR)psz;
    call.codepage = (ULONG_PTR)codepage;

    qemu_syscall(&call.super);

    return (HSZ)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeCreateStringHandleA(struct qemu_syscall *call)
{
    struct qemu_DdeCreateStringHandleA *c = (struct qemu_DdeCreateStringHandleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeCreateStringHandleA(c->idInst, QEMU_G2H(c->psz), c->codepage);
}

#endif

struct qemu_DdeCreateStringHandleW
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t psz;
    uint64_t codepage;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HSZ WINAPI DdeCreateStringHandleW(DWORD idInst, LPCWSTR psz, INT codepage)
{
    struct qemu_DdeCreateStringHandleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECREATESTRINGHANDLEW);
    call.idInst = (ULONG_PTR)idInst;
    call.psz = (ULONG_PTR)psz;
    call.codepage = (ULONG_PTR)codepage;

    qemu_syscall(&call.super);

    return (HSZ)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeCreateStringHandleW(struct qemu_syscall *call)
{
    struct qemu_DdeCreateStringHandleW *c = (struct qemu_DdeCreateStringHandleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeCreateStringHandleW(c->idInst, QEMU_G2H(c->psz), c->codepage);
}

#endif

struct qemu_DdeFreeStringHandle
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hsz;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeFreeStringHandle(DWORD idInst, HSZ hsz)
{
    struct qemu_DdeFreeStringHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEFREESTRINGHANDLE);
    call.idInst = (ULONG_PTR)idInst;
    call.hsz = (ULONG_PTR)hsz;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeFreeStringHandle(struct qemu_syscall *call)
{
    struct qemu_DdeFreeStringHandle *c = (struct qemu_DdeFreeStringHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeFreeStringHandle(c->idInst, QEMU_G2H(c->hsz));
}

#endif

struct qemu_DdeKeepStringHandle
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hsz;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeKeepStringHandle(DWORD idInst, HSZ hsz)
{
    struct qemu_DdeKeepStringHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEKEEPSTRINGHANDLE);
    call.idInst = (ULONG_PTR)idInst;
    call.hsz = (ULONG_PTR)hsz;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeKeepStringHandle(struct qemu_syscall *call)
{
    struct qemu_DdeKeepStringHandle *c = (struct qemu_DdeKeepStringHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeKeepStringHandle(c->idInst, QEMU_G2H(c->hsz));
}

#endif

struct qemu_DdeCmpStringHandles
{
    struct qemu_syscall super;
    uint64_t hsz1;
    uint64_t hsz2;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DdeCmpStringHandles(HSZ hsz1, HSZ hsz2)
{
    struct qemu_DdeCmpStringHandles call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECMPSTRINGHANDLES);
    call.hsz1 = (ULONG_PTR)hsz1;
    call.hsz2 = (ULONG_PTR)hsz2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeCmpStringHandles(struct qemu_syscall *call)
{
    struct qemu_DdeCmpStringHandles *c = (struct qemu_DdeCmpStringHandles *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeCmpStringHandles(QEMU_G2H(c->hsz1), QEMU_G2H(c->hsz2));
}

#endif

struct qemu_DdeInitializeA
{
    struct qemu_syscall super;
    uint64_t pidInst;
    uint64_t pfnCallback;
    uint64_t afCmd;
    uint64_t ulRes;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI DdeInitializeA(LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes)
{
    struct qemu_DdeInitializeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEINITIALIZEA);
    call.pidInst = (ULONG_PTR)pidInst;
    call.pfnCallback = (ULONG_PTR)pfnCallback;
    call.afCmd = (ULONG_PTR)afCmd;
    call.ulRes = (ULONG_PTR)ulRes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeInitializeA(struct qemu_syscall *call)
{
    struct qemu_DdeInitializeA *c = (struct qemu_DdeInitializeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeInitializeA(QEMU_G2H(c->pidInst), QEMU_G2H(c->pfnCallback), c->afCmd, c->ulRes);
}

#endif

struct qemu_DdeInitializeW
{
    struct qemu_syscall super;
    uint64_t pidInst;
    uint64_t pfnCallback;
    uint64_t afCmd;
    uint64_t ulRes;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI DdeInitializeW(LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes)
{
    struct qemu_DdeInitializeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEINITIALIZEW);
    call.pidInst = (ULONG_PTR)pidInst;
    call.pfnCallback = (ULONG_PTR)pfnCallback;
    call.afCmd = (ULONG_PTR)afCmd;
    call.ulRes = (ULONG_PTR)ulRes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeInitializeW(struct qemu_syscall *call)
{
    struct qemu_DdeInitializeW *c = (struct qemu_DdeInitializeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeInitializeW(QEMU_G2H(c->pidInst), QEMU_G2H(c->pfnCallback), c->afCmd, c->ulRes);
}

#endif

struct qemu_DdeUninitialize
{
    struct qemu_syscall super;
    uint64_t idInst;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeUninitialize(DWORD idInst)
{
    struct qemu_DdeUninitialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEUNINITIALIZE);
    call.idInst = (ULONG_PTR)idInst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeUninitialize(struct qemu_syscall *call)
{
    struct qemu_DdeUninitialize *c = (struct qemu_DdeUninitialize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeUninitialize(c->idInst);
}

#endif

struct qemu_DdeCreateDataHandle
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t pSrc;
    uint64_t cb;
    uint64_t cbOff;
    uint64_t hszItem;
    uint64_t wFmt;
    uint64_t afCmd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDDEDATA WINAPI DdeCreateDataHandle(DWORD idInst, LPBYTE pSrc, DWORD cb, DWORD cbOff, HSZ hszItem, UINT wFmt, UINT afCmd)
{
    struct qemu_DdeCreateDataHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDECREATEDATAHANDLE);
    call.idInst = (ULONG_PTR)idInst;
    call.pSrc = (ULONG_PTR)pSrc;
    call.cb = (ULONG_PTR)cb;
    call.cbOff = (ULONG_PTR)cbOff;
    call.hszItem = (ULONG_PTR)hszItem;
    call.wFmt = (ULONG_PTR)wFmt;
    call.afCmd = (ULONG_PTR)afCmd;

    qemu_syscall(&call.super);

    return (HDDEDATA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeCreateDataHandle(struct qemu_syscall *call)
{
    struct qemu_DdeCreateDataHandle *c = (struct qemu_DdeCreateDataHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeCreateDataHandle(c->idInst, QEMU_G2H(c->pSrc), c->cb, c->cbOff, QEMU_G2H(c->hszItem), c->wFmt, c->afCmd);
}

#endif

struct qemu_DdeAddData
{
    struct qemu_syscall super;
    uint64_t hData;
    uint64_t pSrc;
    uint64_t cb;
    uint64_t cbOff;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDDEDATA WINAPI DdeAddData(HDDEDATA hData, LPBYTE pSrc, DWORD cb, DWORD cbOff)
{
    struct qemu_DdeAddData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEADDDATA);
    call.hData = (ULONG_PTR)hData;
    call.pSrc = (ULONG_PTR)pSrc;
    call.cb = (ULONG_PTR)cb;
    call.cbOff = (ULONG_PTR)cbOff;

    qemu_syscall(&call.super);

    return (HDDEDATA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeAddData(struct qemu_syscall *call)
{
    struct qemu_DdeAddData *c = (struct qemu_DdeAddData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeAddData(QEMU_G2H(c->hData), QEMU_G2H(c->pSrc), c->cb, c->cbOff);
}

#endif

struct qemu_DdeGetData
{
    struct qemu_syscall super;
    uint64_t hData;
    uint64_t pDst;
    uint64_t cbMax;
    uint64_t cbOff;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI DdeGetData(HDDEDATA hData, LPBYTE pDst, DWORD cbMax, DWORD cbOff)
{
    struct qemu_DdeGetData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEGETDATA);
    call.hData = (ULONG_PTR)hData;
    call.pDst = (ULONG_PTR)pDst;
    call.cbMax = (ULONG_PTR)cbMax;
    call.cbOff = (ULONG_PTR)cbOff;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeGetData(struct qemu_syscall *call)
{
    struct qemu_DdeGetData *c = (struct qemu_DdeGetData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeGetData(QEMU_G2H(c->hData), QEMU_G2H(c->pDst), c->cbMax, c->cbOff);
}

#endif

struct qemu_DdeAccessData
{
    struct qemu_syscall super;
    uint64_t hData;
    uint64_t pcbDataSize;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LPBYTE WINAPI DdeAccessData(HDDEDATA hData, LPDWORD pcbDataSize)
{
    struct qemu_DdeAccessData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEACCESSDATA);
    call.hData = (ULONG_PTR)hData;
    call.pcbDataSize = (ULONG_PTR)pcbDataSize;

    qemu_syscall(&call.super);

    return (LPBYTE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeAccessData(struct qemu_syscall *call)
{
    struct qemu_DdeAccessData *c = (struct qemu_DdeAccessData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeAccessData(QEMU_G2H(c->hData), QEMU_G2H(c->pcbDataSize));
}

#endif

struct qemu_DdeUnaccessData
{
    struct qemu_syscall super;
    uint64_t hData;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeUnaccessData(HDDEDATA hData)
{
    struct qemu_DdeUnaccessData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEUNACCESSDATA);
    call.hData = (ULONG_PTR)hData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeUnaccessData(struct qemu_syscall *call)
{
    struct qemu_DdeUnaccessData *c = (struct qemu_DdeUnaccessData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeUnaccessData(QEMU_G2H(c->hData));
}

#endif

struct qemu_DdeFreeDataHandle
{
    struct qemu_syscall super;
    uint64_t hData;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeFreeDataHandle(HDDEDATA hData)
{
    struct qemu_DdeFreeDataHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEFREEDATAHANDLE);
    call.hData = (ULONG_PTR)hData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeFreeDataHandle(struct qemu_syscall *call)
{
    struct qemu_DdeFreeDataHandle *c = (struct qemu_DdeFreeDataHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeFreeDataHandle(QEMU_G2H(c->hData));
}

#endif

struct qemu_DdeEnableCallback
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hConv;
    uint64_t wCmd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdeEnableCallback(DWORD idInst, HCONV hConv, UINT wCmd)
{
    struct qemu_DdeEnableCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEENABLECALLBACK);
    call.idInst = (ULONG_PTR)idInst;
    call.hConv = (ULONG_PTR)hConv;
    call.wCmd = (ULONG_PTR)wCmd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeEnableCallback(struct qemu_syscall *call)
{
    struct qemu_DdeEnableCallback *c = (struct qemu_DdeEnableCallback *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeEnableCallback(c->idInst, QEMU_G2H(c->hConv), c->wCmd);
}

#endif

struct qemu_DdeQueryConvInfo
{
    struct qemu_syscall super;
    uint64_t hConv;
    uint64_t id;
    uint64_t lpConvInfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI DdeQueryConvInfo(HCONV hConv, DWORD id, PCONVINFO lpConvInfo)
{
    struct qemu_DdeQueryConvInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEQUERYCONVINFO);
    call.hConv = (ULONG_PTR)hConv;
    call.id = (ULONG_PTR)id;
    call.lpConvInfo = (ULONG_PTR)lpConvInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeQueryConvInfo(struct qemu_syscall *call)
{
    struct qemu_DdeQueryConvInfo *c = (struct qemu_DdeQueryConvInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeQueryConvInfo(QEMU_G2H(c->hConv), c->id, QEMU_G2H(c->lpConvInfo));
}

#endif

struct qemu_DdePostAdvise
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hszTopic;
    uint64_t hszItem;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DdePostAdvise(DWORD idInst, HSZ hszTopic, HSZ hszItem)
{
    struct qemu_DdePostAdvise call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDEPOSTADVISE);
    call.idInst = (ULONG_PTR)idInst;
    call.hszTopic = (ULONG_PTR)hszTopic;
    call.hszItem = (ULONG_PTR)hszItem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdePostAdvise(struct qemu_syscall *call)
{
    struct qemu_DdePostAdvise *c = (struct qemu_DdePostAdvise *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdePostAdvise(c->idInst, QEMU_G2H(c->hszTopic), QEMU_G2H(c->hszItem));
}

#endif

struct qemu_DdeNameService
{
    struct qemu_syscall super;
    uint64_t idInst;
    uint64_t hsz1;
    uint64_t hsz2;
    uint64_t afCmd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDDEDATA WINAPI DdeNameService(DWORD idInst, HSZ hsz1, HSZ hsz2, UINT afCmd)
{
    struct qemu_DdeNameService call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDENAMESERVICE);
    call.idInst = (ULONG_PTR)idInst;
    call.hsz1 = (ULONG_PTR)hsz1;
    call.hsz2 = (ULONG_PTR)hsz2;
    call.afCmd = (ULONG_PTR)afCmd;

    qemu_syscall(&call.super);

    return (HDDEDATA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DdeNameService(struct qemu_syscall *call)
{
    struct qemu_DdeNameService *c = (struct qemu_DdeNameService *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DdeNameService(c->idInst, QEMU_G2H(c->hsz1), QEMU_G2H(c->hsz2), c->afCmd);
}

#endif

struct qemu_DdeSetUserHandle
{
    struct qemu_syscall super;
    uint64_t hConv;
    uint64_t id;
    uint64_t hUser;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI user32_DdeSetUserHandle(HCONV hConv, DWORD id, DWORD hUser)
{
    struct qemu_DdeSetUserHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDESETUSERHANDLE);
    call.hConv = (ULONG_PTR)hConv;
    call.id = id;
    call.hUser = hUser;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DdeSetUserHandle(struct qemu_syscall *call)
{
    struct qemu_DdeSetUserHandle *c = (struct qemu_DdeSetUserHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DdeSetUserHandle(QEMU_G2H(c->hConv), c->id, c->hUser);
}

#endif
