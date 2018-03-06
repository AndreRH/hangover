#ifndef HAVE_QEMU_THUNK_WINSPOOL_H
#define HAVE_QEMU_THUNK_WINSPOOL_H

struct PRINTER_INFO_2
{
  qemu_ptr  pServerName;
  qemu_ptr  pPrinterName;
  qemu_ptr  pShareName;
  qemu_ptr  pPortName;
  qemu_ptr  pDriverName;
  qemu_ptr  pComment;
  qemu_ptr  pLocation;
  qemu_ptr  pDevMode;
  qemu_ptr  pSepFile;
  qemu_ptr  pPrintProcessor;
  qemu_ptr  pDatatype;
  qemu_ptr  pParameters;
  qemu_ptr  pSecurityDescriptor;
  DWORD     Attributes;
  DWORD     Priority;
  DWORD     DefaultPriority;
  DWORD     StartTime;
  DWORD     UntilTime;
  DWORD     Status;
  DWORD     cJobs;
  DWORD     AveragePPM;
};

static inline void PRINTER_INFO_2_h2g(struct PRINTER_INFO_2 *guest, const PRINTER_INFO_2W *host)
{
    guest->pServerName = (ULONG_PTR)host->pServerName;
    guest->pPrinterName = (ULONG_PTR)host->pPrinterName;
    guest->pShareName = (ULONG_PTR)host->pShareName;
    guest->pPortName = (ULONG_PTR)host->pPortName;
    guest->pDriverName = (ULONG_PTR)host->pDriverName;
    guest->pComment = (ULONG_PTR)host->pComment;
    guest->pLocation = (ULONG_PTR)host->pLocation;
    guest->pDevMode = (ULONG_PTR)host->pDevMode;
    guest->pSepFile = (ULONG_PTR)host->pSepFile;
    guest->pPrintProcessor = (ULONG_PTR)host->pPrintProcessor;
    guest->pDatatype = (ULONG_PTR)host->pDatatype;
    guest->pParameters = (ULONG_PTR)host->pParameters;
    guest->pSecurityDescriptor = (ULONG_PTR)host->pSecurityDescriptor;
    guest->Attributes = host->Attributes;
    guest->Priority = host->Priority;
    guest->DefaultPriority = host->DefaultPriority;
    guest->StartTime = host->StartTime;
    guest->UntilTime = host->UntilTime;
    guest->Status = host->Status;
    guest->cJobs = host->cJobs;
    guest->AveragePPM = host->AveragePPM;
}

#endif
