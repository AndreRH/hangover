#ifndef HAVE_QEMU_THUNK_PROPIDL_H
#define HAVE_QEMU_THUNK_PROPIDL_H

struct qemu_CAUB
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAI
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAUI {
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAL
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAUL
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAFLT
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CADBL
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CACY
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CADATE {
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CABSTR
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CABSTRBLOB
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CABOOL {
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CASCODE
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAPROPVARIANT
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAH
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAUH
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CALPSTR
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CALPWSTR
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CAFILETIME
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CACLIPDATA
{
    ULONG cElems;
    qemu_ptr pElems;
};
struct qemu_CACLSID
{
    ULONG cElems;
    qemu_ptr pElems;
};

struct qemu_PROPVARIANT
{
    VARTYPE vt;
    WORD wReserved1;
    WORD wReserved2;
    WORD wReserved3;
    union {
        char cVal;
        UCHAR bVal;
        short iVal;
        USHORT uiVal;
        VARIANT_BOOL boolVal;
        LONG lVal;
        ULONG ulVal;
        float fltVal;
        SCODE scode;
        LARGE_INTEGER hVal;
        ULARGE_INTEGER uhVal;
        double dblVal;
        CY cyVal;
        DATE date;
        FILETIME filetime;
        qemu_ptr puuid;
        struct qemu_BLOB blob;
        qemu_ptr pclipdata;
        qemu_ptr pStream;
        qemu_ptr pStorage;
        BSTR bstrVal;
        struct qemu_CABSTRBLOB bstrblobVal;
        qemu_ptr pszVal;
        qemu_ptr pwszVal;
        qemu_ptr punkVal;
        qemu_ptr pdispVal;
        struct qemu_CAUB caub;
        struct qemu_CAI cai;
        struct qemu_CAUI caui;
        struct qemu_CABOOL cabool;
        struct qemu_CAL cal;
        struct qemu_CAUL caul;
        struct qemu_CAFLT caflt;
        struct qemu_CASCODE cascode;
        struct qemu_CAH cah;
        struct qemu_CAUH cauh;
        struct qemu_CADBL cadbl;
        struct qemu_CACY cacy;
        struct qemu_CADATE cadate;
        struct qemu_CAFILETIME cafiletime;
        struct qemu_CACLSID cauuid;
        struct qemu_CACLIPDATA caclipdata;
        struct qemu_CABSTR cabstr;
        struct qemu_CABSTRBLOB cabstrblob;
        struct qemu_CALPSTR calpstr;
        struct qemu_CALPWSTR calpwstr;
        struct qemu_CAPROPVARIANT capropvar;
        qemu_ptr parray;
        qemu_ptr pcVal;
        qemu_ptr pbVal;
        qemu_ptr piVal;
        qemu_ptr puiVal;
        qemu_ptr plVal;
        qemu_ptr pulVal;
        qemu_ptr pintVal;
        qemu_ptr puintVal;
        qemu_ptr pfltVal;
        qemu_ptr pdblVal;
        qemu_ptr pboolVal;
        qemu_ptr pdecVal;
        qemu_ptr pscode;
        qemu_ptr pcyVal;
        qemu_ptr pdate;
        qemu_ptr pbstrVal;
        qemu_ptr ppunkVal;
        qemu_ptr ppdispVal;
        qemu_ptr pparray;
        qemu_ptr pvarVal;
    } u1;
};

static inline void PROPVARIANT_g2h(PROPVARIANT *host, const struct qemu_PROPVARIANT *guest)
{
    /* Well, this doesn't quite do the job. Some possible members are VARIANTs themselves, or arrays of this shit.
     * There are also cases of COM interfaces, those need to be handled by the caller. */
    memset(host, 0, sizeof(*host));
    host->vt = guest->vt;

    switch (host->vt)
    {
        case VT_BLOB:
            host->blob.cbSize = guest->u1.blob.cbSize;
            host->blob.pBlobData = (void *)(ULONG_PTR)guest->u1.blob.pBlobData;
            break;

        case VT_I1 | VT_VECTOR:
        case VT_UI1 | VT_VECTOR:
            host->caub.cElems = guest->u1.caub.cElems;
            host->caub.pElems = (unsigned char *)(ULONG_PTR)guest->u1.caub.pElems;
            break;

        case VT_I2 | VT_VECTOR:
        case VT_UI2| VT_VECTOR :
            host->caui.cElems = guest->u1.caui.cElems;
            host->caui.pElems = (USHORT *)(ULONG_PTR)guest->u1.caui.pElems;
            break;

        case VT_I4 | VT_VECTOR:
        case VT_UI4 | VT_VECTOR:
        case VT_R4 | VT_VECTOR:
            host->caul.cElems = guest->u1.caul.cElems;
            host->caul.pElems = (ULONG *)(ULONG_PTR)guest->u1.caul.pElems;
            break;

        case VT_I8 | VT_VECTOR:
        case VT_UI8 | VT_VECTOR:
        case VT_R8 | VT_VECTOR:
            host->cauh.cElems = guest->u1.cauh.cElems;
            host->cauh.pElems = (ULARGE_INTEGER *)(ULONG_PTR)guest->u1.cauh.pElems;
            break;

        case VT_UI8:
            host->uhVal = guest->u1.uhVal;
            break;

        case VT_I8:
            host->hVal = guest->u1.hVal;
            break;

        /* TODO: There are more 8 vs 16 byte sized structs. */

        default:
            host->punkVal = (void *)(ULONG_PTR)guest->u1.punkVal;
    }
}

static inline void PROPVARIANT_h2g(struct qemu_PROPVARIANT *guest, const PROPVARIANT *host)
{
    /* Well, this doesn't quite do the job. Some possible members are VARIANTs themselves, or arrays of this shit.
     * There are also cases of COM interfaces, those need to be handled by the caller. */
    memset(guest, 0, sizeof(*guest));
    guest->vt = host->vt;
    switch (host->vt)
    {
        case VT_BLOB:
            guest->u1.blob.cbSize = host->blob.cbSize;
            guest->u1.blob.pBlobData = (ULONG_PTR)host->blob.pBlobData;
            break;

        case VT_I1 | VT_VECTOR:
        case VT_UI1 | VT_VECTOR:
            guest->u1.caub.cElems = host->caub.cElems;
            guest->u1.caub.pElems = (ULONG_PTR)host->caub.pElems;
            break;

        case VT_I2 | VT_VECTOR:
        case VT_UI2 | VT_VECTOR:
            guest->u1.caui.cElems = host->caui.cElems;
            guest->u1.caui.pElems = (ULONG_PTR)host->caui.pElems;
            break;

        case VT_I4 | VT_VECTOR:
        case VT_UI4 | VT_VECTOR:
        case VT_R4 | VT_VECTOR:
            guest->u1.caul.cElems = host->caul.cElems;
            guest->u1.caul.pElems = (ULONG_PTR)host->caul.pElems;
            break;

        case VT_I8 | VT_VECTOR:
        case VT_UI8 | VT_VECTOR:
        case VT_R8 | VT_VECTOR:
            guest->u1.cauh.cElems = host->cauh.cElems;
            guest->u1.cauh.pElems = (ULONG_PTR)host->cauh.pElems;
            break;

        case VT_UI8:
            guest->u1.uhVal = host->uhVal;
            break;

        case VT_I8:
            guest->u1.hVal = host->hVal;
            break;

        /* TODO: There are more 8 vs 16 byte sized structs. */

        default:
            guest->u1.punkVal = (ULONG_PTR)host->punkVal;
    }
}

#endif
