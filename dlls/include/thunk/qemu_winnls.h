#ifndef HAVE_QEMU_WINNLS_H
#define HAVE_QEMU_WINNLS_H

struct qemu_CURRENCYFMT
{
    UINT NumDigits;
    UINT LeadingZero;
    UINT Grouping;
    qemu_ptr lpDecimalSep;
    qemu_ptr lpThousandSep;
    UINT NegativeOrder;
    UINT PositiveOrder;
    qemu_ptr lpCurrencySymbol;
};

static inline void CURRENCYFMT_g2h(CURRENCYFMTW *host, const struct qemu_CURRENCYFMT *guest)
{
    host->NumDigits = guest->NumDigits;
    host->LeadingZero = guest->LeadingZero;
    host->Grouping = guest->Grouping;
    host->lpDecimalSep = (WCHAR *)(ULONG_PTR)guest->lpDecimalSep;
    host->lpThousandSep = (WCHAR *)(ULONG_PTR)guest->lpThousandSep;
    host->NegativeOrder = guest->NegativeOrder;
    host->PositiveOrder = guest->PositiveOrder;
    host->lpCurrencySymbol = (WCHAR *)(ULONG_PTR)guest->lpCurrencySymbol;
}

static inline void CURRENCYFMT_h2g(struct qemu_CURRENCYFMT *guest, const CURRENCYFMTW *host)
{
    guest->NumDigits = host->NumDigits;
    guest->LeadingZero = host->LeadingZero;
    guest->Grouping = host->Grouping;
    guest->lpDecimalSep = (ULONG_PTR)host->lpDecimalSep;
    guest->lpThousandSep = (ULONG_PTR)host->lpThousandSep;
    guest->NegativeOrder = host->NegativeOrder;
    guest->PositiveOrder = host->PositiveOrder;
    guest->lpCurrencySymbol = (ULONG_PTR)host->lpCurrencySymbol;
}

struct qemu_NUMBERFMT
{
    UINT NumDigits;
    UINT LeadingZero;
    UINT Grouping;
    qemu_ptr lpDecimalSep;
    qemu_ptr lpThousandSep;
    UINT NegativeOrder;
};

static inline void NUMBERFMT_g2h(NUMBERFMTW *host, const struct qemu_NUMBERFMT *guest)
{
    host->NumDigits = guest->NumDigits;
    host->LeadingZero = guest->LeadingZero;
    host->Grouping = guest->Grouping;
    host->lpDecimalSep = (WCHAR *)(ULONG_PTR)guest->lpDecimalSep;
    host->lpThousandSep = (WCHAR *)(ULONG_PTR)guest->lpThousandSep;
    host->NegativeOrder = guest->NegativeOrder;
}

static inline void NUMBERFMT_h2g(struct qemu_NUMBERFMT *guest, const NUMBERFMTW *host)
{
    guest->NumDigits = host->NumDigits;
    guest->LeadingZero = host->LeadingZero;
    guest->Grouping = host->Grouping;
    guest->lpDecimalSep = (ULONG_PTR)host->lpDecimalSep;
    guest->lpThousandSep = (ULONG_PTR)host->lpThousandSep;
    guest->NegativeOrder = host->NegativeOrder;
}

#endif
