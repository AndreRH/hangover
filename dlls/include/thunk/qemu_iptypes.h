#ifndef HAVE_QEMU_THUNK_IPTYPES_H
#define HAVE_QEMU_THUNK_IPTYPES_H

struct qemu_IP_ADDR_STRING
{
    qemu_ptr Next; /* IP_ADDR_STRING */
    IP_ADDRESS_STRING IpAddress;
    IP_MASK_STRING IpMask;
    DWORD Context;
};

/* Note that this function only supports in-place conversion because it does not allocate new
 * structs for the address string chain. */
static inline void IP_ADDR_STRING_h2g(struct qemu_IP_ADDR_STRING *guest, const IP_ADDR_STRING *host)
{
    guest->Next = (ULONG_PTR)host->Next;
    if (host->Next)
        IP_ADDR_STRING_h2g((struct qemu_IP_ADDR_STRING *)host->Next, host->Next);
    memmove(&guest->IpAddress, &host->IpAddress, sizeof(guest->IpAddress));
    memmove(&guest->IpMask, &host->IpMask, sizeof(guest->IpMask));
    guest->Context = host->Context;
}

struct qemu_IP_ADAPTER_INFO
{
    qemu_ptr Next; /* struct _IP_ADAPTER_INFO * */
    DWORD ComboIndex;
    char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4];
    char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
    UINT AddressLength;
    BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
    DWORD Index;
    UINT Type;
    UINT DhcpEnabled;
    qemu_ptr CurrentIpAddress; /* IP_ADDR_STRING * */
    struct qemu_IP_ADDR_STRING IpAddressList;
    struct qemu_IP_ADDR_STRING GatewayList;
    struct qemu_IP_ADDR_STRING DhcpServer;
    BOOL HaveWins;
    struct qemu_IP_ADDR_STRING PrimaryWinsServer;
    struct qemu_IP_ADDR_STRING SecondaryWinsServer;
    unsigned int LeaseObtained;
    unsigned int LeaseExpires;
};

/* Note that this function only supports in-place conversion because it does not allocate new
 * structs for the address string chain or the adapter chain. */
static inline void IP_ADAPTER_INFO_h2g(struct qemu_IP_ADAPTER_INFO *guest, const IP_ADAPTER_INFO *host)
{
    guest->Next = (ULONG_PTR)host->Next;
    if (guest->Next)
        IP_ADAPTER_INFO_h2g((struct qemu_IP_ADAPTER_INFO *)host->Next, host->Next);
    guest->ComboIndex = host->ComboIndex;
    memmove(guest->AdapterName, host->AdapterName, sizeof(guest->AdapterName));
    memmove(guest->Description, host->Description, sizeof(guest->Description));
    guest->AddressLength = host->AddressLength;
    memmove(guest->Address, host->Address, sizeof(guest->Address));
    guest->Index = host->Index;
    guest->Type = host->Type;
    guest->DhcpEnabled = host->DhcpEnabled;
    /* I assume this points into IpAddressList, so we don't need to convert it, but I can't find the place where
     * it is set in Wine. Maybe always NULL. */
    guest->CurrentIpAddress = (ULONG_PTR)host->CurrentIpAddress;
    IP_ADDR_STRING_h2g(&guest->IpAddressList, &host->IpAddressList);
    IP_ADDR_STRING_h2g(&guest->GatewayList, &host->GatewayList);
    IP_ADDR_STRING_h2g(&guest->DhcpServer, &host->DhcpServer);
    guest->HaveWins = host->HaveWins;
    IP_ADDR_STRING_h2g(&guest->PrimaryWinsServer, &host->PrimaryWinsServer);
    IP_ADDR_STRING_h2g(&guest->SecondaryWinsServer, &host->SecondaryWinsServer);
    guest->LeaseObtained = host->LeaseObtained;
    guest->LeaseExpires = host->LeaseExpires;
}

struct qemu_IP_PER_ADAPTER_INFO
{
    UINT AutoconfigEnabled;
    UINT AutoconfigActive;
    qemu_ptr CurrentDnsServer; /* IP_ADDR_STRING * */
    struct qemu_IP_ADDR_STRING DnsServerList;
};

/* Note that this function only supports in-place conversion because it does not allocate new
 * structs for the DNS list chain. */
static inline void IP_PER_ADAPTER_INFO_h2g(struct qemu_IP_PER_ADAPTER_INFO *guest, const IP_PER_ADAPTER_INFO *host)
{
    guest->AutoconfigEnabled = host->AutoconfigEnabled;
    guest->AutoconfigActive = host->AutoconfigActive;
    guest->CurrentDnsServer = (ULONG_PTR)host->CurrentDnsServer;
    IP_ADDR_STRING_h2g(&guest->DnsServerList, &host->DnsServerList);
}

struct qemu_FIXED_INFO
{
    char HostName[MAX_HOSTNAME_LEN + 4] ;
    char DomainName[MAX_DOMAIN_NAME_LEN + 4];
    qemu_ptr CurrentDnsServer; /* IP_ADDR_STRING * */
    struct qemu_IP_ADDR_STRING DnsServerList;
    UINT NodeType;
    char ScopeId[MAX_SCOPE_ID_LEN + 4];
    UINT EnableRouting;
    UINT EnableProxy;
    UINT EnableDns;
};

/* Note that this function only supports in-place conversion because it does not allocate new
 * structs for the DNS list chain. */
static inline void FIXED_INFO_h2g(struct qemu_FIXED_INFO *guest, const FIXED_INFO *host)
{
    memmove(guest->HostName, host->HostName, sizeof(guest->HostName));
    memmove(guest->DomainName, host->DomainName, sizeof(guest->DomainName));
    guest->CurrentDnsServer = (ULONG_PTR)host->CurrentDnsServer;
    IP_ADDR_STRING_h2g(&guest->DnsServerList, &host->DnsServerList);
    guest->NodeType = host->NodeType;
    memmove(guest->ScopeId, host->ScopeId, sizeof(guest->ScopeId));
    guest->EnableRouting = host->EnableRouting;
    guest->EnableProxy = host->EnableProxy;
    guest->EnableDns = host->EnableDns;
}

struct qemu_IP_ADAPTER_UNICAST_ADDRESS
{
    union
    {
        struct
        {
            ULONG Length;
            DWORD Flags;
        } s1;
    } u1;
    qemu_ptr                                Next; /* struct qemu_IP_ADAPTER_UNICAST_ADDRESS * */
    struct qemu_SOCKET_ADDRESS              Address;
    IP_PREFIX_ORIGIN                        PrefixOrigin;
    IP_SUFFIX_ORIGIN                        SuffixOrigin;
    IP_DAD_STATE                            DadState;
    ULONG                                   ValidLifetime;
    ULONG                                   PreferredLifetime;
    ULONG                                   LeaseLifetime;
    UINT8                                   OnLinkPrefixLength;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_UNICAST_ADDRESS_h2g(struct qemu_IP_ADAPTER_UNICAST_ADDRESS *guest,
        const IP_ADAPTER_UNICAST_ADDRESS *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Flags = host->Flags;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);
    guest->PrefixOrigin = host->PrefixOrigin;
    guest->SuffixOrigin = host->SuffixOrigin;
    guest->DadState = host->DadState;
    guest->ValidLifetime = host->ValidLifetime;
    guest->PrefixOrigin = host->PrefixOrigin;
    guest->PreferredLifetime = host->PreferredLifetime;
    guest->LeaseLifetime = host->LeaseLifetime;
    guest->OnLinkPrefixLength = host->OnLinkPrefixLength;

    if (host->Next)
        IP_ADAPTER_UNICAST_ADDRESS_h2g((struct qemu_IP_ADAPTER_UNICAST_ADDRESS *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_ANYCAST_ADDRESS
{
    union
    {
        ULONGLONG Alignment;
        struct
        {
            ULONG Length;
            DWORD Flags;
        } s1;
    } u1;
    qemu_ptr                            Next; /* struct qemu_IP_ADAPTER_ANYCAST_ADDRESS */
    struct qemu_SOCKET_ADDRESS          Address;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_ANYCAST_ADDRESS_h2g(struct qemu_IP_ADAPTER_ANYCAST_ADDRESS *guest,
        const IP_ADAPTER_ANYCAST_ADDRESS *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Flags = host->Flags;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);

    if (host->Next)
        IP_ADAPTER_ANYCAST_ADDRESS_h2g((struct qemu_IP_ADAPTER_ANYCAST_ADDRESS *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_DNS_SERVER_ADDRESS
{
    union
    {
        ULONGLONG Alignment;
        struct
        {
            ULONG Length;
            DWORD Reserved;
        } s1;
    } u1;
    qemu_ptr                            Next; /* struct qemu_IP_ADAPTER_DNS_SERVER_ADDRESS */
    struct qemu_SOCKET_ADDRESS          Address;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_DNS_SERVER_ADDRESS_h2g(struct qemu_IP_ADAPTER_DNS_SERVER_ADDRESS *guest,
        const IP_ADAPTER_DNS_SERVER_ADDRESS *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Reserved = host->Reserved;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);

    if (host->Next)
        IP_ADAPTER_DNS_SERVER_ADDRESS_h2g((struct qemu_IP_ADAPTER_DNS_SERVER_ADDRESS *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_MULTICAST_ADDRESS
{
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD Flags;
        } s1;
    } u1;
    qemu_ptr                            Next; /* struct qemu_IP_ADAPTER_MULTICAST_ADDRESS */
    struct qemu_SOCKET_ADDRESS          Address;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_MULTICAST_ADDRESS_h2g(struct qemu_IP_ADAPTER_MULTICAST_ADDRESS *guest,
        const IP_ADAPTER_MULTICAST_ADDRESS *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Flags = host->Flags;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);

    if (host->Next)
        IP_ADAPTER_MULTICAST_ADDRESS_h2g((struct qemu_IP_ADAPTER_MULTICAST_ADDRESS *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_DNS_SUFFIX
{
    qemu_ptr Next; /* struct qemu_IP_ADAPTER_DNS_SUFFIX * */
    WCHAR String[MAX_DNS_SUFFIX_STRING_LENGTH];
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_DNS_SUFFIX_h2g(struct qemu_IP_ADAPTER_DNS_SUFFIX *guest,
        const IP_ADAPTER_DNS_SUFFIX *host)
{
    guest->Next = (ULONG_PTR)host->Next;
    memmove(guest->String, host->String, sizeof(guest->String));
    if (host->Next)
        IP_ADAPTER_DNS_SUFFIX_h2g((struct qemu_IP_ADAPTER_DNS_SUFFIX *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_PREFIX
{
    union
    {
        ULONGLONG Alignment;
        struct
        {
            ULONG Length;
            DWORD Flags;
        } s1;
    } u1;
    qemu_ptr                            Next; /* struct qemu_IP_ADAPTER_PREFIX * */
    struct qemu_SOCKET_ADDRESS          Address;
    ULONG                               PrefixLength;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_PREFIX_h2g(struct qemu_IP_ADAPTER_PREFIX *guest,
        const IP_ADAPTER_PREFIX *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Flags = host->Flags;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);
    guest->PrefixLength = host->PrefixLength;

    if (host->Next)
        IP_ADAPTER_PREFIX_h2g((struct qemu_IP_ADAPTER_PREFIX *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_WINS_SERVER_ADDRESS
{
    union
    {
        ULONGLONG Alignment;
        struct
        {
            ULONG Length;
            DWORD Reserved;
        } s1;
    } u1;
    qemu_ptr Next;
    struct qemu_SOCKET_ADDRESS          Address;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_WINS_SERVER_ADDRESS_h2g(struct qemu_IP_ADAPTER_WINS_SERVER_ADDRESS *guest,
        const IP_ADAPTER_WINS_SERVER_ADDRESS *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Reserved = host->Reserved;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);

    if (host->Next)
        IP_ADAPTER_WINS_SERVER_ADDRESS_h2g((struct qemu_IP_ADAPTER_WINS_SERVER_ADDRESS *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_GATEWAY_ADDRESS
{
    union
    {
        ULONGLONG Alignment;
        struct
        {
            ULONG Length;
            DWORD Reserved;
        } s1;
    } u1;
    qemu_ptr Next;
    struct qemu_SOCKET_ADDRESS          Address;
};

/* Only in place conversion is supported. */
static inline void IP_ADAPTER_GATEWAY_ADDRESS_h2g(struct qemu_IP_ADAPTER_GATEWAY_ADDRESS *guest,
        const IP_ADAPTER_GATEWAY_ADDRESS *host)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.Reserved = host->Reserved;
    guest->Next = (ULONG_PTR)host->Next;
    SOCKET_ADDRESS_h2g(&guest->Address, &host->Address);

    if (host->Next)
        IP_ADAPTER_GATEWAY_ADDRESS_h2g((struct qemu_IP_ADAPTER_GATEWAY_ADDRESS *)host->Next, host->Next);
}

struct qemu_IP_ADAPTER_ADDRESSES
{
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD IfIndex;
        } s1;
    } u1;
    qemu_ptr                        Next; /* IP_ADAPTER_ADDRESSES */
    qemu_ptr                        AdapterName; /* char */
    qemu_ptr                        FirstUnicastAddress; /* IP_ADAPTER_UNICAST_ADDRESS * */
    qemu_ptr                        FirstAnycastAddress; /* IP_ADAPTER_ANYCAST_ADDRESS * */
    qemu_ptr                        FirstMulticastAddress; /* IP_ADAPTER_MULTICAST_ADDRESS * */
    qemu_ptr                        FirstDnsServerAddress; /* IP_ADAPTER_DNS_SERVER_ADDRESS *. WARNING: ONLY 1 COPY */
    qemu_ptr                        DnsSuffix; /* WCHAR * */
    qemu_ptr                        Description; /* WCHAR * */
    qemu_ptr                        FriendlyName; /* WCHAR * */
    BYTE                            PhysicalAddress[MAX_ADAPTER_ADDRESS_LENGTH];
    DWORD                           PhysicalAddressLength;
    union {
        DWORD                       Flags;
        struct {
            DWORD                   DdnsEnabled : 1;
            DWORD                   RegisterAdapterSuffix : 1;
            DWORD                   Dhcpv4Enabled : 1;
            DWORD                   ReceiveOnly : 1;
            DWORD                   NoMulticast : 1;
            DWORD                   Ipv6OtherStatefulConfig : 1;
            DWORD                   NetbiosOverTcpipEnabled : 1;
            DWORD                   Ipv4Enabled : 1;
            DWORD                   Ipv6Enabled : 1;
            DWORD                   Ipv6ManagedAddressConfigurationSupported : 1;
        } s1;
    } u2;
    DWORD                           Mtu;
    DWORD                           IfType;
    IF_OPER_STATUS                  OperStatus;
    DWORD                           Ipv6IfIndex;
    DWORD                           ZoneIndices[16];
    qemu_ptr                        FirstPrefix; /* IP_ADAPTER_PREFIX * */
    ULONG64                         TransmitLinkSpeed;
    ULONG64                         ReceiveLinkSpeed;
    qemu_ptr                        FirstWinsServerAddress; /* PIP_ADAPTER_WINS_SERVER_ADDRESS_LH */
    qemu_ptr                        FirstGatewayAddress; /* PIP_ADAPTER_GATEWAY_ADDRESS_LH */
    ULONG                           Ipv4Metric;
    ULONG                           Ipv6Metric;
    IF_LUID                         Luid;
    struct qemu_SOCKET_ADDRESS      Dhcpv4Server;
    NET_IF_COMPARTMENT_ID           CompartmentId;
    NET_IF_NETWORK_GUID             NetworkGuid;
    NET_IF_CONNECTION_TYPE          ConnectionType;
    TUNNEL_TYPE                     TunnelType;
    struct qemu_SOCKET_ADDRESS      Dhcpv6Server;
    BYTE                            Dhcpv6ClientDuid[MAX_DHCPV6_DUID_LENGTH];
    ULONG                           Dhcpv6ClientDuidLength;
    ULONG                           Dhcpv6Iaid;
    qemu_ptr                        FirstDnsSuffix; /* PIP_ADAPTER_DNS_SUFFIX */
};

/* Only in place conversion is supported. */
static inline void _IP_ADAPTER_ADDRESSES_h2g(struct qemu_IP_ADAPTER_ADDRESSES *guest, const IP_ADAPTER_ADDRESSES *host,
        BOOL first)
{
    guest->u1.s1.Length = sizeof(*guest);
    guest->u1.s1.IfIndex = host->IfIndex;
    guest->Next = (ULONG_PTR)host->Next;
    guest->AdapterName = (ULONG_PTR)host->AdapterName;

    guest->FirstUnicastAddress = (ULONG_PTR)host->FirstUnicastAddress;
    if (host->FirstUnicastAddress)
    {
        IP_ADAPTER_UNICAST_ADDRESS_h2g((struct qemu_IP_ADAPTER_UNICAST_ADDRESS *)host->FirstUnicastAddress,
                host->FirstUnicastAddress);
    }
    guest->FirstAnycastAddress = (ULONG_PTR)host->FirstAnycastAddress;
    if (host->FirstAnycastAddress)
    {
        IP_ADAPTER_ANYCAST_ADDRESS_h2g((struct qemu_IP_ADAPTER_ANYCAST_ADDRESS *)host->FirstAnycastAddress,
                host->FirstAnycastAddress);
    }

    guest->FirstMulticastAddress = (ULONG_PTR)host->FirstMulticastAddress;
    if (host->FirstMulticastAddress)
    {
        IP_ADAPTER_MULTICAST_ADDRESS_h2g((struct qemu_IP_ADAPTER_MULTICAST_ADDRESS *)host->FirstMulticastAddress,
                host->FirstMulticastAddress);
    }

    guest->FirstDnsServerAddress = (ULONG_PTR)host->FirstDnsServerAddress;
    if (host->FirstDnsServerAddress && first) /* FIXME: Verify that there's only one DNS server address in the list. */
    {
        IP_ADAPTER_DNS_SERVER_ADDRESS_h2g((struct qemu_IP_ADAPTER_DNS_SERVER_ADDRESS *)host->FirstDnsServerAddress,
                host->FirstDnsServerAddress);
    }

    guest->DnsSuffix = (ULONG_PTR)host->DnsSuffix;
    guest->Description = (ULONG_PTR)host->Description;
    guest->FriendlyName = (ULONG_PTR)host->FriendlyName;
    memmove(guest->PhysicalAddress, host->PhysicalAddress, sizeof(guest->PhysicalAddress));
    guest->PhysicalAddressLength = host->PhysicalAddressLength;
    guest->u2.Flags = host->Flags;
    guest->Mtu = host->Mtu;
    guest->IfType = host->IfType;
    guest->OperStatus = host->OperStatus;
    guest->Ipv6IfIndex = host->Ipv6IfIndex;
    memmove(guest->ZoneIndices, host->ZoneIndices, sizeof(guest->ZoneIndices));

    guest->FirstPrefix = (ULONG_PTR)host->FirstPrefix;
    if (host->FirstPrefix)
    {
        IP_ADAPTER_PREFIX_h2g((struct qemu_IP_ADAPTER_PREFIX *)host->FirstPrefix, host->FirstPrefix);
    }

    guest->TransmitLinkSpeed = host->TransmitLinkSpeed;
    guest->ReceiveLinkSpeed = host->ReceiveLinkSpeed;

    guest->FirstWinsServerAddress = (ULONG_PTR)host->FirstWinsServerAddress;
    if (host->FirstWinsServerAddress)
    {
        IP_ADAPTER_WINS_SERVER_ADDRESS_h2g((struct qemu_IP_ADAPTER_WINS_SERVER_ADDRESS *)host->FirstWinsServerAddress,
                host->FirstWinsServerAddress);
    }

    guest->FirstGatewayAddress = (ULONG_PTR)host->FirstGatewayAddress;
    if (host->FirstGatewayAddress)
    {
        IP_ADAPTER_GATEWAY_ADDRESS_h2g((struct qemu_IP_ADAPTER_GATEWAY_ADDRESS *)host->FirstGatewayAddress,
                host->FirstGatewayAddress);
    }

    guest->Ipv4Metric = host->Ipv4Metric;
    guest->Ipv6Metric = host->Ipv6Metric;
    guest->Luid = host->Luid;
    SOCKET_ADDRESS_h2g(&guest->Dhcpv4Server, &host->Dhcpv4Server);
    guest->CompartmentId = host->CompartmentId;
    guest->NetworkGuid = host->NetworkGuid;
    guest->ConnectionType = host->ConnectionType;
    guest->TunnelType = host->TunnelType;
    SOCKET_ADDRESS_h2g(&guest->Dhcpv6Server, &host->Dhcpv6Server);
    memmove(guest->Dhcpv6ClientDuid, host->Dhcpv6ClientDuid, sizeof(guest->Dhcpv6ClientDuid));
    guest->Dhcpv6ClientDuidLength = host->Dhcpv6ClientDuidLength;
    guest->Dhcpv6Iaid = host->Dhcpv6Iaid;

    guest->FirstDnsSuffix = (ULONG_PTR)host->FirstDnsSuffix;
    if (host->FirstDnsSuffix)
    {
        IP_ADAPTER_DNS_SUFFIX_h2g((struct qemu_IP_ADAPTER_DNS_SUFFIX *)host->FirstDnsSuffix, host->FirstDnsSuffix);
    }

    if (host->Next)
        _IP_ADAPTER_ADDRESSES_h2g((struct qemu_IP_ADAPTER_ADDRESSES *)host->Next, host->Next, FALSE);
}

static inline void IP_ADAPTER_ADDRESSES_h2g(struct qemu_IP_ADAPTER_ADDRESSES *guest, const IP_ADAPTER_ADDRESSES *host)
{
    _IP_ADAPTER_ADDRESSES_h2g(guest, host, TRUE);
}

#endif
