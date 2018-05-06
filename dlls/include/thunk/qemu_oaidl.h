#ifndef HAVE_QEMU_THUNK_OAIDL_H
#define HAVE_QEMU_THUNK_OAIDL_H

struct qemu_VARIANT {
  union {
    struct qemu__tagVARIANT {
      VARTYPE vt;
      WORD wReserved1;
      WORD wReserved2;
      WORD wReserved3;
      union {
        signed char cVal;
        USHORT uiVal;
        ULONG ulVal;
        INT intVal;
        UINT uintVal;
        BYTE bVal;
        SHORT iVal;
        LONG lVal;
        FLOAT fltVal;
        DOUBLE dblVal;
        VARIANT_BOOL boolVal;
#if 0 /* illegal in C++ */
        _VARIANT_BOOL bool;
#endif
        SCODE scode;
        DATE date;
        BSTR bstrVal;
        CY cyVal;
        qemu_ptr punkVal;
        qemu_ptr pdispVal;
        qemu_ptr parray;
        LONGLONG llVal;
        ULONGLONG ullVal;
        qemu_ptr pcVal;
        qemu_ptr puiVal;
        qemu_ptr pulVal;
        qemu_ptr pintVal;
        qemu_ptr puintVal;
        qemu_ptr pbVal;
        qemu_ptr piVal;
        qemu_ptr plVal;
        qemu_ptr pfltVal;
        qemu_ptr pdblVal;
        qemu_ptr pboolVal;
#if 0
        qemu_ptr pbool;
#endif
        qemu_ptr pscode;
        qemu_ptr pdate;
        qemu_ptr pbstrVal;
        qemu_ptr pvarVal;
        qemu_ptr byref;
        qemu_ptr pcyVal;
        qemu_ptr pdecVal;
        qemu_ptr ppunkVal;
        qemu_ptr ppdispVal;
        qemu_ptr pparray;
        qemu_ptr pllVal;
        qemu_ptr pullVal;
        struct qemu__tagBRECORD {
          qemu_ptr Record;
          qemu_ptr pRecInfo;
        } v4;
      } v3;
    } v2;

    DECIMAL decVal;
  } v1;
};

static inline void VARIANT_g2h(VARIANT *host, const struct qemu_VARIANT *guest)
{
    /* Well, this doesn't quite do the job. Some possible members are VARIANTs themselves, or arrays of this shit. */
    memset(host, 0, sizeof(*host));
    V_VT(host) = guest->v1.v2.vt;
    V_BYREF(host) = (void *)(ULONG_PTR)guest->v1.v2.v3.byref;
}

static inline void VARIANT_h2g(struct qemu_VARIANT *guest, const VARIANT *host)
{
    /* Well, this doesn't quite do the job. Some possible members are VARIANTs themselves, or arrays of this shit. */
    memset(guest, 0, sizeof(*guest));
    guest->v1.v2.vt = V_VT(host);
    guest->v1.v2.v3.byref = (ULONG_PTR)V_BYREF(host);
}

#endif
