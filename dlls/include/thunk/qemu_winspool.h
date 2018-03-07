#ifndef HAVE_QEMU_THUNK_WINSPOOL_H
#define HAVE_QEMU_THUNK_WINSPOOL_H

struct qemu_PRINTER_INFO_2
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

static inline void PRINTER_INFO_2_h2g(struct qemu_PRINTER_INFO_2 *guest, const PRINTER_INFO_2W *host)
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

struct qemu_PORT_INFO_2
{
    qemu_ptr    pPortName;
    qemu_ptr    pMonitorName;
    qemu_ptr    pDescription;
    DWORD       fPortType;
    DWORD       Reserved;
};

static inline void PORT_INFO_2_h2g(struct qemu_PORT_INFO_2 *guest, const PORT_INFO_2W *host)
{
    guest->pPortName = (ULONG_PTR)host->pPortName;
    guest->pMonitorName = (ULONG_PTR)host->pMonitorName;
    guest->pDescription = (ULONG_PTR)host->pDescription;
    guest->fPortType = host->fPortType;
    guest->Reserved = host->Reserved;
}

static inline void PORT_INFO_2_g2h(PORT_INFO_2W *host, const struct qemu_PORT_INFO_2 *guest)
{
    host->pPortName = (WCHAR *)(ULONG_PTR)guest->pPortName;
    host->pMonitorName = (WCHAR *)(ULONG_PTR)guest->pMonitorName;
    host->pDescription = (WCHAR *)(ULONG_PTR)guest->pDescription;
    host->fPortType = guest->fPortType;
    host->Reserved = guest->Reserved;
}

struct qemu_PRINTER_DEFAULTS
{
    qemu_ptr    pDatatype;
    qemu_ptr    pDevMode;
    ACCESS_MASK DesiredAccess;
};

static inline void PRINTER_DEFAULTS_h2g(struct qemu_PRINTER_DEFAULTS *guest, const PRINTER_DEFAULTSW *host)
{
    guest->pDatatype = (ULONG_PTR)host->pDatatype;
    guest->pDevMode = (ULONG_PTR)host->pDevMode;
    guest->DesiredAccess = host->DesiredAccess;
}

static inline void PRINTER_DEFAULTS_g2h(PRINTER_DEFAULTSW *host, const struct qemu_PRINTER_DEFAULTS *guest)
{
    host->pDatatype = (WCHAR *)(ULONG_PTR)guest->pDatatype;
    host->pDevMode = (DEVMODEW *)(ULONG_PTR)guest->pDevMode;
    host->DesiredAccess = guest->DesiredAccess;
}

struct qemu_DRIVER_INFO_1
{
  qemu_ptr  pName;
};

static inline void DRIVER_INFO_1_h2g(struct qemu_DRIVER_INFO_1 *guest, const DRIVER_INFO_1W *host)
{
    guest->pName = (ULONG_PTR)host->pName;
}

static inline void DRIVER_INFO_1_g2h(DRIVER_INFO_1W *host, const struct qemu_DRIVER_INFO_1 *guest)
{
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
}

struct qemu_DRIVER_INFO_2
{
    DWORD     cVersion;
    qemu_ptr  pName;
    qemu_ptr  pEnvironment;
    qemu_ptr  pDriverPath;
    qemu_ptr  pDataFile;
    qemu_ptr  pConfigFile;
};

static inline void DRIVER_INFO_2_h2g(struct qemu_DRIVER_INFO_2 *guest, const DRIVER_INFO_2W *host)
{
    guest->cVersion = host->cVersion;
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDriverPath = (ULONG_PTR)host->pDriverPath;
    guest->pDataFile = (ULONG_PTR)host->pDataFile;
    guest->pConfigFile = (ULONG_PTR)host->pConfigFile;
}

static inline void DRIVER_INFO_2_g2h(DRIVER_INFO_2W *host, const struct qemu_DRIVER_INFO_2 *guest)
{
    host->cVersion = guest->cVersion;
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDriverPath = (WCHAR *)(ULONG_PTR)guest->pDriverPath;
    host->pDataFile = (WCHAR *)(ULONG_PTR)guest->pDataFile;
    host->pConfigFile = (WCHAR *)(ULONG_PTR)guest->pConfigFile;
}

struct qemu_DRIVER_INFO_3
{
    DWORD    cVersion;
    qemu_ptr pName;
    qemu_ptr pEnvironment;
    qemu_ptr pDriverPath;
    qemu_ptr pDataFile;
    qemu_ptr pConfigFile;
    qemu_ptr pHelpFile;
    qemu_ptr pDependentFiles;
    qemu_ptr pMonitorName;
    qemu_ptr pDefaultDataType;
};

static inline void DRIVER_INFO_3_h2g(struct qemu_DRIVER_INFO_3 *guest, const DRIVER_INFO_3W *host)
{
    guest->cVersion = host->cVersion;
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDriverPath = (ULONG_PTR)host->pDriverPath;
    guest->pDataFile = (ULONG_PTR)host->pDataFile;
    guest->pConfigFile = (ULONG_PTR)host->pConfigFile;
    guest->pHelpFile = (ULONG_PTR)host->pHelpFile;
    guest->pDependentFiles = (ULONG_PTR)host->pDependentFiles;
    guest->pMonitorName = (ULONG_PTR)host->pMonitorName;
    guest->pDefaultDataType = (ULONG_PTR)host->pDefaultDataType;
}

static inline void DRIVER_INFO_3_g2h(DRIVER_INFO_3W *host, const struct qemu_DRIVER_INFO_3 *guest)
{
    host->cVersion = guest->cVersion;
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDriverPath = (WCHAR *)(ULONG_PTR)guest->pDriverPath;
    host->pDataFile = (WCHAR *)(ULONG_PTR)guest->pDataFile;
    host->pConfigFile = (WCHAR *)(ULONG_PTR)guest->pConfigFile;
    host->pHelpFile = (WCHAR *)(ULONG_PTR)guest->pHelpFile;
    host->pDependentFiles = (WCHAR *)(ULONG_PTR)guest->pDependentFiles;
    host->pMonitorName = (WCHAR *)(ULONG_PTR)guest->pMonitorName;
    host->pDefaultDataType = (WCHAR *)(ULONG_PTR)guest->pDefaultDataType;
}

struct qemu_DRIVER_INFO_4
{
    DWORD    cVersion;
    qemu_ptr pName;
    qemu_ptr pEnvironment;
    qemu_ptr pDriverPath;
    qemu_ptr pDataFile;
    qemu_ptr pConfigFile;
    qemu_ptr pHelpFile;
    qemu_ptr pDependentFiles;
    qemu_ptr pMonitorName;
    qemu_ptr pDefaultDataType;
    qemu_ptr pszzPreviousNames;
};

static inline void DRIVER_INFO_4_h2g(struct qemu_DRIVER_INFO_4 *guest, const DRIVER_INFO_4W *host)
{
    guest->cVersion = host->cVersion;
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDriverPath = (ULONG_PTR)host->pDriverPath;
    guest->pDataFile = (ULONG_PTR)host->pDataFile;
    guest->pConfigFile = (ULONG_PTR)host->pConfigFile;
    guest->pHelpFile = (ULONG_PTR)host->pHelpFile;
    guest->pDependentFiles = (ULONG_PTR)host->pDependentFiles;
    guest->pMonitorName = (ULONG_PTR)host->pMonitorName;
    guest->pDefaultDataType = (ULONG_PTR)host->pDefaultDataType;
    guest->pszzPreviousNames = (ULONG_PTR)host->pszzPreviousNames;
}

static inline void DRIVER_INFO_4_g2h(DRIVER_INFO_4W *host, const struct qemu_DRIVER_INFO_4 *guest)
{
    host->cVersion = guest->cVersion;
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDriverPath = (WCHAR *)(ULONG_PTR)guest->pDriverPath;
    host->pDataFile = (WCHAR *)(ULONG_PTR)guest->pDataFile;
    host->pConfigFile = (WCHAR *)(ULONG_PTR)guest->pConfigFile;
    host->pHelpFile = (WCHAR *)(ULONG_PTR)guest->pHelpFile;
    host->pDependentFiles = (WCHAR *)(ULONG_PTR)guest->pDependentFiles;
    host->pMonitorName = (WCHAR *)(ULONG_PTR)guest->pMonitorName;
    host->pDefaultDataType = (WCHAR *)(ULONG_PTR)guest->pDefaultDataType;
    host->pszzPreviousNames = (WCHAR *)(ULONG_PTR)guest->pszzPreviousNames;
}

struct qemu_DRIVER_INFO_5
{
    DWORD    cVersion;
    qemu_ptr pName;
    qemu_ptr pEnvironment;
    qemu_ptr pDriverPath;
    qemu_ptr pDataFile;
    qemu_ptr pConfigFile;
    DWORD dwDriverAttributes;
    DWORD dwConfigVersion;
    DWORD dwDriverVersion;
};

static inline void DRIVER_INFO_5_h2g(struct qemu_DRIVER_INFO_5 *guest, const DRIVER_INFO_5W *host)
{
    guest->cVersion = host->cVersion;
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDriverPath = (ULONG_PTR)host->pDriverPath;
    guest->pDataFile = (ULONG_PTR)host->pDataFile;
    guest->pConfigFile = (ULONG_PTR)host->pConfigFile;
    guest->dwDriverAttributes = host->dwDriverAttributes;
    guest->dwConfigVersion = host->dwConfigVersion;
    guest->dwDriverVersion = host->dwDriverVersion;
}

static inline void DRIVER_INFO_5_g2h(DRIVER_INFO_5W *host, const struct qemu_DRIVER_INFO_5 *guest)
{
    host->cVersion = guest->cVersion;
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDriverPath = (WCHAR *)(ULONG_PTR)guest->pDriverPath;
    host->pDataFile = (WCHAR *)(ULONG_PTR)guest->pDataFile;
    host->pConfigFile = (WCHAR *)(ULONG_PTR)guest->pConfigFile;
    host->dwDriverAttributes = guest->dwDriverAttributes;
    host->dwConfigVersion = guest->dwConfigVersion;
    host->dwDriverVersion = guest->dwDriverVersion;
}

struct qemu_DRIVER_INFO_6
{
    DWORD    cVersion;
    qemu_ptr pName;
    qemu_ptr pEnvironment;
    qemu_ptr pDriverPath;
    qemu_ptr pDataFile;
    qemu_ptr pConfigFile;
    qemu_ptr pHelpFile;
    qemu_ptr pDependentFiles;
    qemu_ptr pMonitorName;
    qemu_ptr pDefaultDataType;
    qemu_ptr pszzPreviousNames;
    FILETIME ftDriverDate;
    qemu_ptr dwlDriverVersion;
    qemu_ptr pszMfgName;
    qemu_ptr pszOEMUrl;
    qemu_ptr pszHardwareID;
    qemu_ptr pszProvider;
};

static inline void DRIVER_INFO_6_h2g(struct qemu_DRIVER_INFO_6 *guest, const DRIVER_INFO_6W *host)
{
    guest->cVersion = host->cVersion;
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDriverPath = (ULONG_PTR)host->pDriverPath;
    guest->pDataFile = (ULONG_PTR)host->pDataFile;
    guest->pConfigFile = (ULONG_PTR)host->pConfigFile;
    guest->pHelpFile = (ULONG_PTR)host->pHelpFile;
    guest->pDependentFiles = (ULONG_PTR)host->pDependentFiles;
    guest->pMonitorName = (ULONG_PTR)host->pMonitorName;
    guest->pDefaultDataType = (ULONG_PTR)host->pDefaultDataType;
    guest->pszzPreviousNames = (ULONG_PTR)host->pszzPreviousNames;
    guest->ftDriverDate = host->ftDriverDate;
    guest->dwlDriverVersion = host->dwlDriverVersion;
    guest->pszMfgName = (ULONG_PTR)host->pszMfgName;
    guest->pszOEMUrl = (ULONG_PTR)host->pszOEMUrl;
    guest->pszHardwareID = (ULONG_PTR)host->pszHardwareID;
    guest->pszProvider = (ULONG_PTR)host->pszProvider;
}

static inline void DRIVER_INFO_6_g2h(DRIVER_INFO_6W *host, const struct qemu_DRIVER_INFO_6 *guest)
{
    host->cVersion = guest->cVersion;
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDriverPath = (WCHAR *)(ULONG_PTR)guest->pDriverPath;
    host->pDataFile = (WCHAR *)(ULONG_PTR)guest->pDataFile;
    host->pConfigFile = (WCHAR *)(ULONG_PTR)guest->pConfigFile;
    host->pHelpFile = (WCHAR *)(ULONG_PTR)guest->pHelpFile;
    host->pDependentFiles = (WCHAR *)(ULONG_PTR)guest->pDependentFiles;
    host->pMonitorName = (WCHAR *)(ULONG_PTR)guest->pMonitorName;
    host->pDefaultDataType = (WCHAR *)(ULONG_PTR)guest->pDefaultDataType;
    host->pszzPreviousNames = (WCHAR *)(ULONG_PTR)guest->pszzPreviousNames;
    host->ftDriverDate = guest->ftDriverDate;
    host->dwlDriverVersion = guest->dwlDriverVersion;
    host->pszMfgName = (WCHAR *)(ULONG_PTR)guest->pszMfgName;
    host->pszOEMUrl = (WCHAR *)(ULONG_PTR)guest->pszOEMUrl;
    host->pszHardwareID = (WCHAR *)(ULONG_PTR)guest->pszHardwareID;
    host->pszProvider = (WCHAR *)(ULONG_PTR)guest->pszProvider;
}

struct qemu_DRIVER_INFO_8
{
    DWORD    cVersion;
    qemu_ptr pName;
    qemu_ptr pEnvironment;
    qemu_ptr pDriverPath;
    qemu_ptr pDataFile;
    qemu_ptr pConfigFile;
    qemu_ptr pHelpFile;
    qemu_ptr pDependentFiles;
    qemu_ptr pMonitorName;
    qemu_ptr pDefaultDataType;
    qemu_ptr pszzPreviousNames;
    FILETIME ftDriverDate;
    qemu_ptr dwlDriverVersion;
    qemu_ptr pszMfgName;
    qemu_ptr pszOEMUrl;
    qemu_ptr pszHardwareID;
    qemu_ptr pszProvider;
    qemu_ptr pszPrintProcessor;
    qemu_ptr pszVendorSetup;
    qemu_ptr pszzColorProfiles;
    qemu_ptr pszInfPath;
    DWORD    dwPrinterDriverAttributes;
    qemu_ptr pszzCoreDriverDependencies;
    FILETIME ftMinInboxDriverVerDate;
    DWORDLONG dwlMinInboxDriverVerVersion;
};

#ifndef QEMU_DLL_GUEST
static inline void DRIVER_INFO_8_h2g(struct qemu_DRIVER_INFO_8 *guest, const DRIVER_INFO_8W *host)
{
    guest->cVersion = host->cVersion;
    guest->pName = (ULONG_PTR)host->pName;
    guest->pEnvironment = (ULONG_PTR)host->pEnvironment;
    guest->pDriverPath = (ULONG_PTR)host->pDriverPath;
    guest->pDataFile = (ULONG_PTR)host->pDataFile;
    guest->pConfigFile = (ULONG_PTR)host->pConfigFile;
    guest->pHelpFile = (ULONG_PTR)host->pHelpFile;
    guest->pDependentFiles = (ULONG_PTR)host->pDependentFiles;
    guest->pMonitorName = (ULONG_PTR)host->pMonitorName;
    guest->pDefaultDataType = (ULONG_PTR)host->pDefaultDataType;
    guest->pszzPreviousNames = (ULONG_PTR)host->pszzPreviousNames;
    guest->ftDriverDate = host->ftDriverDate;
    guest->dwlDriverVersion = host->dwlDriverVersion;
    guest->pszMfgName = (ULONG_PTR)host->pszMfgName;
    guest->pszOEMUrl = (ULONG_PTR)host->pszOEMUrl;
    guest->pszHardwareID = (ULONG_PTR)host->pszHardwareID;
    guest->pszProvider = (ULONG_PTR)host->pszProvider;
    guest->pszPrintProcessor = (ULONG_PTR)host->pszPrintProcessor;
    guest->pszVendorSetup = (ULONG_PTR)host->pszVendorSetup;
    guest->pszzColorProfiles = (ULONG_PTR)host->pszzColorProfiles;
    guest->pszInfPath = (ULONG_PTR)host->pszInfPath;
    guest->dwPrinterDriverAttributes = host->dwPrinterDriverAttributes;
    guest->pszzCoreDriverDependencies = (ULONG_PTR)host->pszzCoreDriverDependencies;
    guest->ftMinInboxDriverVerDate = host->ftMinInboxDriverVerDate;
    guest->dwlMinInboxDriverVerVersion = host->dwlMinInboxDriverVerVersion;
}

static inline void DRIVER_INFO_8_g2h(DRIVER_INFO_8W *host, const struct qemu_DRIVER_INFO_8 *guest)
{
    host->cVersion = guest->cVersion;
    host->pName = (WCHAR *)(ULONG_PTR)guest->pName;
    host->pEnvironment = (WCHAR *)(ULONG_PTR)guest->pEnvironment;
    host->pDriverPath = (WCHAR *)(ULONG_PTR)guest->pDriverPath;
    host->pDataFile = (WCHAR *)(ULONG_PTR)guest->pDataFile;
    host->pConfigFile = (WCHAR *)(ULONG_PTR)guest->pConfigFile;
    host->pHelpFile = (WCHAR *)(ULONG_PTR)guest->pHelpFile;
    host->pDependentFiles = (WCHAR *)(ULONG_PTR)guest->pDependentFiles;
    host->pMonitorName = (WCHAR *)(ULONG_PTR)guest->pMonitorName;
    host->pDefaultDataType = (WCHAR *)(ULONG_PTR)guest->pDefaultDataType;
    host->pszzPreviousNames = (WCHAR *)(ULONG_PTR)guest->pszzPreviousNames;
    host->ftDriverDate = guest->ftDriverDate;
    host->dwlDriverVersion = guest->dwlDriverVersion;
    host->pszMfgName = (WCHAR *)(ULONG_PTR)guest->pszMfgName;
    host->pszOEMUrl = (WCHAR *)(ULONG_PTR)guest->pszOEMUrl;
    host->pszHardwareID = (WCHAR *)(ULONG_PTR)guest->pszHardwareID;
    host->pszProvider = (WCHAR *)(ULONG_PTR)guest->pszProvider;
    host->pszPrintProcessor = (WCHAR *)(ULONG_PTR)guest->pszPrintProcessor;
    host->pszVendorSetup = (WCHAR *)(ULONG_PTR)guest->pszVendorSetup;
    host->pszzColorProfiles = (WCHAR *)(ULONG_PTR)guest->pszzColorProfiles;
    host->pszInfPath = (WCHAR *)(ULONG_PTR)guest->pszInfPath;
    host->dwPrinterDriverAttributes = guest->dwPrinterDriverAttributes;
    host->pszzCoreDriverDependencies = (WCHAR *)(ULONG_PTR)guest->pszzCoreDriverDependencies;
    host->ftMinInboxDriverVerDate = guest->ftMinInboxDriverVerDate;
    host->dwlMinInboxDriverVerVersion = guest->dwlMinInboxDriverVerVersion;
}
#endif

#endif
