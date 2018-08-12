#ifndef HAVE_QEMU_THUNK_RPCDCE_H
#define HAVE_QEMU_THUNK_RPCDCE_H

struct qemu_SEC_WINNT_AUTH_IDENTITY
{
    qemu_ptr User;
    ULONG UserLength;
    qemu_ptr Domain;
    ULONG DomainLength;
    qemu_ptr Password;
    ULONG PasswordLength;
    ULONG Flags;
};

static inline void SEC_WINNT_AUTH_IDENTITY_g2h(SEC_WINNT_AUTH_IDENTITY_W *host,
        const struct qemu_SEC_WINNT_AUTH_IDENTITY *guest)
{
    host->User = (WCHAR *)(ULONG_PTR)guest->User;
    host->UserLength = guest->UserLength;
    host->Domain = (WCHAR *)(ULONG_PTR)guest->Domain;
    host->DomainLength = guest->DomainLength;
    host->Password = (WCHAR *)(ULONG_PTR)guest->Password;
    host->PasswordLength = guest->PasswordLength;
    host->Flags = guest->Flags;
}

#endif
