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

struct MONITOR_INFO_2
{
    qemu_ptr pName;
    qemu_ptr pEnvironment;
    qemu_ptr pDLLName;
};

static inline void MONITOR_INFO_2_h2g(struct MONITOR_INFO_2 *guest, const MONITOR_INFO_2W *host)
{
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDLLName = (ULONG_PTR)host->pDLLName;
}

static inline void MONITOR_INFO_2_g2h(MONITOR_INFO_2W *host, const struct MONITOR_INFO_2 *guest)
{
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDLLName = (WCHAR *)(ULONG_PTR)guest->pDLLName;
}

#endif
