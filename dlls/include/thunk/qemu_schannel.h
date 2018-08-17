#ifndef HAVE_QEMU_THUNK_SCHANNEL_H
#define HAVE_QEMU_THUNK_SCHANNEL_H

struct qemu_SecPkgCred_SupportedAlgs
{
    DWORD cSupportedAlgs;
    qemu_ptr palgSupportedAlgs;
};

static void SecPkgCred_SupportedAlgs_h2g(struct qemu_SecPkgCred_SupportedAlgs *guest, SecPkgCred_SupportedAlgs *host)
{
    guest->cSupportedAlgs = host->cSupportedAlgs;
    guest->palgSupportedAlgs = (ULONG_PTR)host->palgSupportedAlgs;
}

#endif
