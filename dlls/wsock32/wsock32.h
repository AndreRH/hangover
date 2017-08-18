#ifndef QEMU_WSOCK32_H
#define QEMU_WSOCK32_H

#include <stdlib.h>

enum wsock32_calls
{
    CALL_ENUMPROTOCOLSA,
    CALL_ENUMPROTOCOLSW,
    CALL_GETADDRESSBYNAMEA,
    CALL_GETADDRESSBYNAMEW,
    CALL_GETSERVICEA,
    CALL_GETSERVICEW,
    CALL_GETTYPEBYNAMEA,
    CALL_GETTYPEBYNAMEW,
    CALL_S_PERROR,
    CALL_SETSERVICEA,
    CALL_SETSERVICEW,
    CALL_WS1_GETSOCKOPT,
    CALL_WS1_SETSOCKOPT,
    CALL_WSARECVEX,
    CALL_WSCONTROL,
    CALL_WSOCK32_GETNETBYNAME,
    CALL_WSOCK32_INET_NETWORK,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_EnumProtocolsA(struct qemu_syscall *call);
void qemu_EnumProtocolsW(struct qemu_syscall *call);
void qemu_GetAddressByNameA(struct qemu_syscall *call);
void qemu_GetAddressByNameW(struct qemu_syscall *call);
void qemu_GetServiceA(struct qemu_syscall *call);
void qemu_GetServiceW(struct qemu_syscall *call);
void qemu_GetTypeByNameA(struct qemu_syscall *call);
void qemu_GetTypeByNameW(struct qemu_syscall *call);
void qemu_s_perror(struct qemu_syscall *call);
void qemu_SetServiceA(struct qemu_syscall *call);
void qemu_SetServiceW(struct qemu_syscall *call);
void qemu_WS1_getsockopt(struct qemu_syscall *call);
void qemu_WS1_setsockopt(struct qemu_syscall *call);
void qemu_WSARecvEx(struct qemu_syscall *call);
void qemu_WsControl(struct qemu_syscall *call);
void qemu_WSOCK32_getnetbyname(struct qemu_syscall *call);
void qemu_WSOCK32_inet_network(struct qemu_syscall *call);

INT (* WINAPI p_EnumProtocolsA)(LPINT protocols, LPVOID buffer, LPDWORD buflen);
INT (* WINAPI p_EnumProtocolsW)(LPINT protocols, LPVOID buffer, LPDWORD buflen);
struct netent *(* WINAPI p_getnetbyname)(const char *name);
INT (* WINAPI p_getsockopt)(SOCKET s, INT level, INT optname, char *optval, INT *optlen);
UINT (* WINAPI p_inet_network)(const char *cp);
INT (* WINAPI p_setsockopt)(SOCKET s, INT level, INT optname, char *optval, INT optlen);
DWORD (* WINAPI p_WsControl)(DWORD protocol, DWORD action, LPVOID pRequestInfo, LPDWORD pcbRequestInfoLen, LPVOID pResponseInfo, LPDWORD pcbResponseInfoLen);

#endif

#endif
