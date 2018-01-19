#ifndef QEMU_WS2_32_H
#define QEMU_WS2_32_H

#include <stdlib.h>

enum ws2_32_calls
{
    CALL___WSAFDISSET = 0,
    CALL_FREEADDRINFOEXW,
    CALL_FREEADDRINFOW,
    CALL_GETADDRINFOEXCANCEL,
    CALL_GETADDRINFOEXOVERLAPPEDRESULT,
    CALL_GETADDRINFOEXW,
    CALL_GETADDRINFOW,
    CALL_GETNAMEINFOW,
    CALL_INETNTOPW,
    CALL_INETPTONW,
    CALL_WPUCOMPLETEOVERLAPPEDREQUEST,
    CALL_WS2_ACCEPTEX,
    CALL_WS2_CONNECTEX,
    CALL_WS2_DISCONNECTEX,
    CALL_WS2_GETACCEPTEXSOCKADDRS,
    CALL_WS2_TRANSMITFILE,
    CALL_WS2_WSARECVMSG,
    CALL_WS_ACCEPT,
    CALL_WS_BIND,
    CALL_WS_CLOSESOCKET,
    CALL_WS_CONNECT,
    CALL_WS_FREEADDRINFO,
    CALL_WS_GETADDRINFO,
    CALL_WS_GETHOSTBYADDR,
    CALL_WS_GETHOSTBYNAME,
    CALL_WS_GETHOSTNAME,
    CALL_WS_GETNAMEINFO,
    CALL_WS_GETPEERNAME,
    CALL_WS_GETPROTOBYNAME,
    CALL_WS_GETPROTOBYNUMBER,
    CALL_WS_GETSERVBYNAME,
    CALL_WS_GETSERVBYPORT,
    CALL_WS_GETSOCKNAME,
    CALL_WS_GETSOCKOPT,
    CALL_WS_HTONL,
    CALL_WS_HTONS,
    CALL_WS_INET_ADDR,
    CALL_WS_INET_NTOA,
    CALL_WS_INET_NTOP,
    CALL_WS_INET_PTON,
    CALL_WS_IOCTLSOCKET,
    CALL_WS_LISTEN,
    CALL_WS_NTOHL,
    CALL_WS_NTOHS,
    CALL_WS_RECV,
    CALL_WS_RECVFROM,
    CALL_WS_SELECT,
    CALL_WS_SEND,
    CALL_WS_SENDTO,
    CALL_WS_SETSOCKOPT,
    CALL_WS_SHUTDOWN,
    CALL_WS_SOCKET,
    CALL_WSAACCEPT,
    CALL_WSAADDRESSTOSTRINGA,
    CALL_WSAADDRESSTOSTRINGW,
    CALL_WSAASYNCGETHOSTBYADDR,
    CALL_WSAASYNCGETHOSTBYNAME,
    CALL_WSAASYNCGETPROTOBYNAME,
    CALL_WSAASYNCGETPROTOBYNUMBER,
    CALL_WSAASYNCGETSERVBYNAME,
    CALL_WSAASYNCGETSERVBYPORT,
    CALL_WSAASYNCSELECT,
    CALL_WSACANCELASYNCREQUEST,
    CALL_WSACANCELBLOCKINGCALL,
    CALL_WSACLEANUP,
    CALL_WSACLOSEEVENT,
    CALL_WSACONNECT,
    CALL_WSACREATEEVENT,
    CALL_WSADUPLICATESOCKETA,
    CALL_WSADUPLICATESOCKETW,
    CALL_WSAENUMNAMESPACEPROVIDERSA,
    CALL_WSAENUMNAMESPACEPROVIDERSW,
    CALL_WSAENUMNETWORKEVENTS,
    CALL_WSAENUMPROTOCOLSA,
    CALL_WSAENUMPROTOCOLSW,
    CALL_WSAEVENTSELECT,
    CALL_WSAGETLASTERROR,
    CALL_WSAGETOVERLAPPEDRESULT,
    CALL_WSAGETQOSBYNAME,
    CALL_WSAGETSERVICECLASSINFOA,
    CALL_WSAGETSERVICECLASSINFOW,
    CALL_WSAGETSERVICECLASSNAMEBYCLASSIDA,
    CALL_WSAGETSERVICECLASSNAMEBYCLASSIDW,
    CALL_WSAHTONL,
    CALL_WSAHTONS,
    CALL_WSAINSTALLSERVICECLASSA,
    CALL_WSAINSTALLSERVICECLASSW,
    CALL_WSAIOCTL,
    CALL_WSAISBLOCKING,
    CALL_WSAJOINLEAF,
    CALL_WSALOOKUPSERVICEBEGINA,
    CALL_WSALOOKUPSERVICEBEGINW,
    CALL_WSALOOKUPSERVICEEND,
    CALL_WSALOOKUPSERVICENEXTA,
    CALL_WSALOOKUPSERVICENEXTW,
    CALL_WSANSPIOCTL,
    CALL_WSANTOHL,
    CALL_WSANTOHS,
    CALL_WSAPOLL,
    CALL_WSAPROVIDERCONFIGCHANGE,
    CALL_WSAPSETPOSTROUTINE,
    CALL_WSARECV,
    CALL_WSARECVDISCONNECT,
    CALL_WSARECVFROM,
    CALL_WSAREMOVESERVICECLASS,
    CALL_WSASEND,
    CALL_WSASENDDISCONNECT,
    CALL_WSASENDMSG,
    CALL_WSASENDTO,
    CALL_WSASETBLOCKINGHOOK,
    CALL_WSASETLASTERROR,
    CALL_WSASETSERVICEA,
    CALL_WSASETSERVICEW,
    CALL_WSASOCKETA,
    CALL_WSASOCKETW,
    CALL_WSASTARTUP,
    CALL_WSASTRINGTOADDRESSA,
    CALL_WSASTRINGTOADDRESSW,
    CALL_WSAUNHOOKBLOCKINGHOOK,
    CALL_WSCDEINSTALLPROVIDER,
    CALL_WSCENABLENSPROVIDER,
    CALL_WSCENUMPROTOCOLS,
    CALL_WSCGETPROVIDERPATH,
    CALL_WSCINSTALLNAMESPACE,
    CALL_WSCINSTALLPROVIDER,
    CALL_WSCUNINSTALLNAMESPACE,
    CALL_WSCWRITEPROVIDERORDER,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu___WSAFDIsSet(struct qemu_syscall *call);
void qemu_FreeAddrInfoExW(struct qemu_syscall *call);
void qemu_FreeAddrInfoW(struct qemu_syscall *call);
void qemu_GetAddrInfoExCancel(struct qemu_syscall *call);
void qemu_GetAddrInfoExOverlappedResult(struct qemu_syscall *call);
void qemu_GetAddrInfoExW(struct qemu_syscall *call);
void qemu_GetAddrInfoW(struct qemu_syscall *call);
void qemu_GetNameInfoW(struct qemu_syscall *call);
void qemu_InetNtopW(struct qemu_syscall *call);
void qemu_InetPtonW(struct qemu_syscall *call);
void qemu_WPUCompleteOverlappedRequest(struct qemu_syscall *call);
void qemu_WS2_AcceptEx(struct qemu_syscall *call);
void qemu_WS2_ConnectEx(struct qemu_syscall *call);
void qemu_WS2_DisconnectEx(struct qemu_syscall *call);
void qemu_WS2_GetAcceptExSockaddrs(struct qemu_syscall *call);
void qemu_WS2_TransmitFile(struct qemu_syscall *call);
void qemu_WS2_WSARecvMsg(struct qemu_syscall *call);
void qemu_WS_accept(struct qemu_syscall *call);
void qemu_WS_bind(struct qemu_syscall *call);
void qemu_WS_closesocket(struct qemu_syscall *call);
void qemu_WS_connect(struct qemu_syscall *call);
void qemu_WS_freeaddrinfo(struct qemu_syscall *call);
void qemu_WS_getaddrinfo(struct qemu_syscall *call);
void qemu_WS_gethostbyaddr(struct qemu_syscall *call);
void qemu_WS_gethostbyname(struct qemu_syscall *call);
void qemu_WS_gethostname(struct qemu_syscall *call);
void qemu_WS_getnameinfo(struct qemu_syscall *call);
void qemu_WS_getpeername(struct qemu_syscall *call);
void qemu_WS_getprotobyname(struct qemu_syscall *call);
void qemu_WS_getprotobynumber(struct qemu_syscall *call);
void qemu_WS_getservbyname(struct qemu_syscall *call);
void qemu_WS_getservbyport(struct qemu_syscall *call);
void qemu_WS_getsockname(struct qemu_syscall *call);
void qemu_WS_getsockopt(struct qemu_syscall *call);
void qemu_WS_htonl(struct qemu_syscall *call);
void qemu_WS_htons(struct qemu_syscall *call);
void qemu_WS_inet_addr(struct qemu_syscall *call);
void qemu_WS_inet_ntoa(struct qemu_syscall *call);
void qemu_WS_inet_ntop(struct qemu_syscall *call);
void qemu_WS_inet_pton(struct qemu_syscall *call);
void qemu_WS_ioctlsocket(struct qemu_syscall *call);
void qemu_WS_listen(struct qemu_syscall *call);
void qemu_WS_ntohl(struct qemu_syscall *call);
void qemu_WS_ntohs(struct qemu_syscall *call);
void qemu_WS_recv(struct qemu_syscall *call);
void qemu_WS_recvfrom(struct qemu_syscall *call);
void qemu_WS_select(struct qemu_syscall *call);
void qemu_WS_send(struct qemu_syscall *call);
void qemu_WS_sendto(struct qemu_syscall *call);
void qemu_WS_setsockopt(struct qemu_syscall *call);
void qemu_WS_shutdown(struct qemu_syscall *call);
void qemu_WS_socket(struct qemu_syscall *call);
void qemu_WSAAccept(struct qemu_syscall *call);
void qemu_WSAAddressToStringA(struct qemu_syscall *call);
void qemu_WSAAddressToStringW(struct qemu_syscall *call);
void qemu_WSAAsyncGetHostByAddr(struct qemu_syscall *call);
void qemu_WSAAsyncGetHostByName(struct qemu_syscall *call);
void qemu_WSAAsyncGetProtoByName(struct qemu_syscall *call);
void qemu_WSAAsyncGetProtoByNumber(struct qemu_syscall *call);
void qemu_WSAAsyncGetServByName(struct qemu_syscall *call);
void qemu_WSAAsyncGetServByPort(struct qemu_syscall *call);
void qemu_WSAAsyncSelect(struct qemu_syscall *call);
void qemu_WSACancelAsyncRequest(struct qemu_syscall *call);
void qemu_WSACancelBlockingCall(struct qemu_syscall *call);
void qemu_WSACleanup(struct qemu_syscall *call);
void qemu_WSACloseEvent(struct qemu_syscall *call);
void qemu_WSAConnect(struct qemu_syscall *call);
void qemu_WSACreateEvent(struct qemu_syscall *call);
void qemu_WSADuplicateSocketA(struct qemu_syscall *call);
void qemu_WSADuplicateSocketW(struct qemu_syscall *call);
void qemu_WSAEnumNameSpaceProvidersA(struct qemu_syscall *call);
void qemu_WSAEnumNameSpaceProvidersW(struct qemu_syscall *call);
void qemu_WSAEnumNetworkEvents(struct qemu_syscall *call);
void qemu_WSAEnumProtocolsA(struct qemu_syscall *call);
void qemu_WSAEnumProtocolsW(struct qemu_syscall *call);
void qemu_WSAEventSelect(struct qemu_syscall *call);
void qemu_WSAGetLastError(struct qemu_syscall *call);
void qemu_WSAGetOverlappedResult(struct qemu_syscall *call);
void qemu_WSAGetQOSByName(struct qemu_syscall *call);
void qemu_WSAGetServiceClassInfoA(struct qemu_syscall *call);
void qemu_WSAGetServiceClassInfoW(struct qemu_syscall *call);
void qemu_WSAGetServiceClassNameByClassIdA(struct qemu_syscall *call);
void qemu_WSAGetServiceClassNameByClassIdW(struct qemu_syscall *call);
void qemu_WSAHtonl(struct qemu_syscall *call);
void qemu_WSAHtons(struct qemu_syscall *call);
void qemu_WSAInstallServiceClassA(struct qemu_syscall *call);
void qemu_WSAInstallServiceClassW(struct qemu_syscall *call);
void qemu_WSAIoctl(struct qemu_syscall *call);
void qemu_WSAIsBlocking(struct qemu_syscall *call);
void qemu_WSAJoinLeaf(struct qemu_syscall *call);
void qemu_WSALookupServiceBeginA(struct qemu_syscall *call);
void qemu_WSALookupServiceBeginW(struct qemu_syscall *call);
void qemu_WSALookupServiceEnd(struct qemu_syscall *call);
void qemu_WSALookupServiceNextA(struct qemu_syscall *call);
void qemu_WSALookupServiceNextW(struct qemu_syscall *call);
void qemu_WSANSPIoctl(struct qemu_syscall *call);
void qemu_WSANtohl(struct qemu_syscall *call);
void qemu_WSANtohs(struct qemu_syscall *call);
void qemu_WSAPoll(struct qemu_syscall *call);
void qemu_WSAProviderConfigChange(struct qemu_syscall *call);
void qemu_WSApSetPostRoutine(struct qemu_syscall *call);
void qemu_WSARecv(struct qemu_syscall *call);
void qemu_WSARecvDisconnect(struct qemu_syscall *call);
void qemu_WSARecvFrom(struct qemu_syscall *call);
void qemu_WSARemoveServiceClass(struct qemu_syscall *call);
void qemu_WSASend(struct qemu_syscall *call);
void qemu_WSASendDisconnect(struct qemu_syscall *call);
void qemu_WSASendMsg(struct qemu_syscall *call);
void qemu_WSASendTo(struct qemu_syscall *call);
void qemu_WSASetBlockingHook(struct qemu_syscall *call);
void qemu_WSASetLastError(struct qemu_syscall *call);
void qemu_WSASetServiceA(struct qemu_syscall *call);
void qemu_WSASetServiceW(struct qemu_syscall *call);
void qemu_WSASocketA(struct qemu_syscall *call);
void qemu_WSASocketW(struct qemu_syscall *call);
void qemu_WSAStartup(struct qemu_syscall *call);
void qemu_WSAStringToAddressA(struct qemu_syscall *call);
void qemu_WSAStringToAddressW(struct qemu_syscall *call);
void qemu_WSAUnhookBlockingHook(struct qemu_syscall *call);
void qemu_WSCDeinstallProvider(struct qemu_syscall *call);
void qemu_WSCEnableNSProvider(struct qemu_syscall *call);
void qemu_WSCEnumProtocols(struct qemu_syscall *call);
void qemu_WSCGetProviderPath(struct qemu_syscall *call);
void qemu_WSCInstallNameSpace(struct qemu_syscall *call);
void qemu_WSCInstallProvider(struct qemu_syscall *call);
void qemu_WSCUnInstallNameSpace(struct qemu_syscall *call);
void qemu_WSCWriteProviderOrder(struct qemu_syscall *call);

SOCKET (* WINAPI p_accept)(SOCKET s, struct WS_sockaddr *addr, int *addrlen32);
int (* WINAPI p_bind)(SOCKET s, const struct WS_sockaddr* name, int namelen);
int (* WINAPI p_closesocket)(SOCKET s);
int (* WINAPI p_connect)(SOCKET s, const struct WS_sockaddr* name, int namelen);
void (* WINAPI p_freeaddrinfo)(ADDRINFOA *res);
int (* WINAPI p_getaddrinfo)(LPCSTR nodename, LPCSTR servname, const ADDRINFOA *hints, ADDRINFOA **res);
struct WS_hostent* (* WINAPI p_gethostbyaddr)(const char *addr, int len, int type);
struct WS_hostent* (* WINAPI p_gethostbyname)(const char* name);
int (* WINAPI p_gethostname)(char *name, int namelen);
int (* WINAPI p_getnameinfo)(const SOCKADDR *sa, WS_socklen_t salen, PCHAR host, DWORD hostlen, PCHAR serv, DWORD servlen, INT flags);
int (* WINAPI p_getpeername)(SOCKET s, struct WS_sockaddr *name, int *namelen);
struct WS_protoent* (* WINAPI p_getprotobyname)(const char* name);
struct WS_protoent* (* WINAPI p_getprotobynumber)(int number);
struct WS_servent* (* WINAPI p_getservbyname)(const char *name, const char *proto);
struct WS_servent* (* WINAPI p_getservbyport)(int port, const char *proto);
int (* WINAPI p_getsockname)(SOCKET s, struct WS_sockaddr *name, int *namelen);
INT (* WINAPI p_getsockopt)(SOCKET s, INT level, INT optname, char *optval, INT *optlen);
WS_u_long (* WINAPI p_htonl)(WS_u_long hostlong);
WS_u_short (* WINAPI p_htons)(WS_u_short hostshort);
WS_u_long (* WINAPI p_inet_addr)(const char *cp);
char* (* WINAPI p_inet_ntoa)(struct WS_in_addr in);
PCSTR (* WINAPI p_inet_ntop)(INT family, PVOID addr, PSTR buffer, SIZE_T len);
INT (* WINAPI p_inet_pton)(INT family, PCSTR addr, PVOID buffer);
int (* WINAPI p_ioctlsocket)(SOCKET s, LONG cmd, WS_u_long *argp);
int (* WINAPI p_listen)(SOCKET s, int backlog);
WS_u_long (* WINAPI p_ntohl)(WS_u_long netlong);
WS_u_short (* WINAPI p_ntohs)(WS_u_short netshort);
int (* WINAPI p_recv)(SOCKET s, char *buf, int len, int flags);
int (* WINAPI p_recvfrom)(SOCKET s, char *buf, INT len, int flags, struct WS_sockaddr *from, int *fromlen);
int (* WINAPI p_select)(int nfds, WS_fd_set *ws_readfds, WS_fd_set *ws_writefds, WS_fd_set *ws_exceptfds, const struct WS_timeval* ws_timeout);
int (* WINAPI p_send)(SOCKET s, const char *buf, int len, int flags);
int (* WINAPI p_sendto)(SOCKET s, const char *buf, int len, int flags, const struct WS_sockaddr *to, int tolen);
int (* WINAPI p_setsockopt)(SOCKET s, int level, int optname, const char *optval, int optlen);
int (* WINAPI p_shutdown)(SOCKET s, int how);
SOCKET (* WINAPI p_socket)(int af, int type, int protocol);

BOOL (* WINAPI p_AcceptEx)(SOCKET listener, SOCKET acceptor, PVOID dest, DWORD dest_len, DWORD local_addr_len, DWORD rem_addr_len, LPDWORD received, LPOVERLAPPED overlapped);
BOOL (* WINAPI p_DisconnectEx)(SOCKET s, LPOVERLAPPED ov, DWORD flags, DWORD reserved);
BOOL (* WINAPI p_ConnectEx)(SOCKET s, const struct WS_sockaddr* name, int namelen, PVOID sendBuf, DWORD sendBufLen, LPDWORD sent, LPOVERLAPPED ov);
void (* WINAPI p_GetAcceptExSockaddrs)(PVOID buffer, DWORD data_size, DWORD local_size, DWORD remote_size, struct WS_sockaddr **local_addr, LPINT local_addr_len, struct WS_sockaddr **remote_addr, LPINT remote_addr_len);
BOOL (* WINAPI p_TransmitFile)(SOCKET s, HANDLE h, DWORD file_bytes, DWORD bytes_per_send, LPOVERLAPPED overlapped, LPTRANSMIT_FILE_BUFFERS buffers, DWORD flags);
int (* WINAPI p_WSARecvMsg)(SOCKET s, LPWSAMSG msg, LPDWORD lpNumberOfBytesRecvd, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
int (* WINAPI p_WSASendMsg)(SOCKET s, LPWSAMSG msg, DWORD dwFlags, LPDWORD lpNumberOfBytesSent, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

struct per_thread_data
{
    struct qemu_WS_hostent *he_buffer;
    struct qemu_WS_servent *se_buffer;
    size_t he_len, se_len;
};

struct per_thread_data *get_per_thread_data(void);

#endif

#endif
