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
    memcpy(&guest->IpAddress, &host->IpAddress, sizeof(guest->IpAddress));
    memcpy(&guest->IpMask, &host->IpMask, sizeof(guest->IpMask));
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
    memcpy(guest->AdapterName, host->AdapterName, sizeof(guest->AdapterName));
    memcpy(guest->Description, host->Description, sizeof(guest->Description));
    guest->AddressLength = host->AddressLength;
    memcpy(guest->Address, host->Address, sizeof(guest->Address));
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

#endif
