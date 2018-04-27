#ifndef HAVE_QEMU_ACCCTRL_H
#define HAVE_QEMU_ACCCTRL_H

struct qemu_TRUSTEE
{
    qemu_ptr                    pMultipleTrustee;
    MULTIPLE_TRUSTEE_OPERATION  MultipleTrusteeOperation;
    TRUSTEE_FORM                TrusteeForm;
    TRUSTEE_TYPE                TrusteeType;
    qemu_ptr                    ptstrName;
};

static inline void TRUSTEE_g2h(TRUSTEE_W *host, const struct qemu_TRUSTEE *guest)
{
    host->pMultipleTrustee = (TRUSTEE_W *)(ULONG_PTR)guest->pMultipleTrustee;
    host->MultipleTrusteeOperation = guest->MultipleTrusteeOperation;
    host->TrusteeForm = guest->TrusteeForm;
    host->TrusteeType = guest->TrusteeType;
    host->ptstrName = (WCHAR *)(ULONG_PTR)guest->ptstrName;
}

static inline void TRUSTEE_h2g(struct qemu_TRUSTEE *guest, const TRUSTEE_W *host)
{
    guest->pMultipleTrustee = (ULONG_PTR)host->pMultipleTrustee;
    guest->MultipleTrusteeOperation = host->MultipleTrusteeOperation;
    guest->TrusteeForm = host->TrusteeForm;
    guest->TrusteeType = host->TrusteeType;
    guest->ptstrName = (ULONG_PTR)host->ptstrName;
}


#endif

