#ifndef HAVE_QEMU_THUNK_USP10_H
#define HAVE_QEMU_THUNK_USP10_H

#include "thunk/qemu_windows.h"

struct qemu_SCRIPT_TABDEF
{
    int cTabStops;
    int iScale;
    qemu_ptr *pTabStops;
    int iTabOrigin;
};

static inline void SCRIPT_TABDEF_g2h(SCRIPT_TABDEF *host, const struct qemu_SCRIPT_TABDEF *guest)
{
    host->cTabStops = guest->cTabStops;
    host->iScale = guest->iScale;
    host->pTabStops = (int *)(ULONG_PTR)guest->pTabStops;
    host->iTabOrigin = guest->iTabOrigin;
}

#endif
