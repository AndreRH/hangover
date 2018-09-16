#ifndef HAVE_QEMU_THUNK_OBJIDL_H
#define HAVE_QEMU_THUNK_OBJIDL_H

struct qemu_STATSTG
{
    qemu_ptr pwcsName;
    DWORD type;
    ULARGE_INTEGER cbSize;
    FILETIME mtime;
    FILETIME ctime;
    FILETIME atime;
    DWORD grfMode;
    DWORD grfLocksSupported;
    CLSID clsid;
    DWORD grfStateBits;
    DWORD reserved;
};

static inline void STATSTG_g2h(STATSTG *host, const struct qemu_STATSTG *guest)
{
    host->pwcsName = (LPOLESTR)(ULONG_PTR)guest->pwcsName;
    host->type = guest->type;
    host->cbSize = guest->cbSize;
    host->mtime = guest->mtime;
    host->ctime = guest->ctime;
    host->atime = guest->atime;
    host->grfMode = guest->grfMode;
    host->grfLocksSupported = guest->grfLocksSupported;
    host->clsid = guest->clsid;
    host->grfStateBits = guest->grfStateBits;
    host->reserved = guest->reserved;
}

static inline void STATSTG_h2g(struct qemu_STATSTG *guest, const STATSTG *host)
{
    guest->pwcsName = (ULONG_PTR)host->pwcsName;
    guest->type = host->type;
    guest->cbSize = host->cbSize;
    guest->mtime = host->mtime;
    guest->ctime = host->ctime;
    guest->atime = host->atime;
    guest->grfMode = host->grfMode;
    guest->grfLocksSupported = host->grfLocksSupported;
    guest->clsid = host->clsid;
    guest->grfStateBits = host->grfStateBits;
    guest->reserved = host->reserved;
}

#endif
