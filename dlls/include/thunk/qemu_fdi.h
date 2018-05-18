#ifndef HAVE_QEMU_THUNK_FDI_H
#define HAVE_QEMU_THUNK_FDI_H

#ifndef _WIN64
#include <pshpack4.h>
#endif

struct qemu_FDINOTIFICATION
{
    LONG  cb;
    qemu_ptr psz1;
    qemu_ptr psz2;
    qemu_ptr psz3;  /* Points to a 256 character buffer */
    qemu_ptr pv;    /* Value for client */

    qemu_ptr hf;

    USHORT date;
    USHORT time;
    USHORT attribs;

    USHORT setID;     /* Cabinet set ID */
    USHORT iCabinet;  /* Cabinet number (0-based) */
    USHORT iFolder;   /* Folder number (0-based) */

    FDIERROR fdie;
};

static inline void FDINOTIFICATION_h2g(struct qemu_FDINOTIFICATION *guest, const FDINOTIFICATION *host)
{
    guest->cb = host->cb;
    guest->psz1 = (ULONG_PTR)host->psz1;
    guest->psz2 = (ULONG_PTR)host->psz2;
    guest->psz3 = (ULONG_PTR)host->psz3;
    guest->pv = (ULONG_PTR)host->pv;
    guest->hf = host->hf;
    guest->date = host->date;
    guest->time = host->time;
    guest->attribs = host->attribs;
    guest->setID = host->setID;
    guest->iCabinet = host->iCabinet;
    guest->iFolder = host->iFolder;
    guest->fdie = host->fdie;
}

#ifndef _WIN64
#include <poppack.h>
#endif

#endif
