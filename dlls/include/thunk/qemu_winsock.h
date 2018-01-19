#ifndef HAVE_QEMU_WINSOCK_H
#define HAVE_QEMU_WINSOCK_H

struct qemu_WS_hostent
{
    qemu_ptr h_name;               /* official name of host - char * */
    qemu_ptr h_aliases;            /* alias list - char  ** */
    short h_addrtype;              /* host address type */
    short h_length;                /* length of address */
    qemu_ptr h_addr_list;          /* list of addresses from name server - char ** */
};

#endif
