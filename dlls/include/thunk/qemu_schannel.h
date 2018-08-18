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

struct qemu_SCHANNEL_CRED
{
    DWORD dwVersion;
    DWORD cCreds;
    qemu_ptr paCred;
    qemu_ptr hRootStore;
    DWORD cMappers;
    qemu_ptr aphMappers;
    DWORD cSupportedAlgs;
    qemu_ptr palgSupportedAlgs;
    DWORD grbitEnabledProtocols;
    DWORD dwMinimumCipherStrength;
    DWORD dwMaximumCipherStrength;
    DWORD dwSessionLifespan;
    DWORD dwFlags;
    DWORD dwCredFormat;
};

/* paCred, aphMappers and hRootStore need to be handled by the caller. */
static void SCHANNEL_CRED_g2h(SCHANNEL_CRED *host, const struct qemu_SCHANNEL_CRED *guest)
{
    host->dwVersion = guest->dwVersion;
    host->cCreds = guest->cCreds;
    host->paCred = NULL;
    host->hRootStore = NULL;
    host->cMappers = guest->cMappers;
    host->aphMappers = NULL;
    host->cSupportedAlgs = guest->cSupportedAlgs;
    host->palgSupportedAlgs = (ALG_ID *)(ULONG_PTR)guest->palgSupportedAlgs;
    host->grbitEnabledProtocols = guest->grbitEnabledProtocols;
    host->dwMinimumCipherStrength = guest->dwMinimumCipherStrength;
    host->dwMaximumCipherStrength = guest->dwMaximumCipherStrength;
    host->dwSessionLifespan = guest->dwSessionLifespan;
    host->dwFlags = guest->dwFlags;
    host->dwCredFormat = guest->dwCredFormat;
}

#endif
