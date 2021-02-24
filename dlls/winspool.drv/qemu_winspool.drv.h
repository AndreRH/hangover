/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef QEMU_WINSPOOL_H
#define QEMU_WINSPOOL_H

enum winspool_calls
{
    CALL_ABORTPRINTER = 0,
    CALL_ADDFORMA,
    CALL_ADDFORMW,
    CALL_ADDJOBA,
    CALL_ADDJOBW,
    CALL_ADDMONITORA,
    CALL_ADDMONITORW,
    CALL_ADDPORTA,
    CALL_ADDPORTEXA,
    CALL_ADDPORTEXW,
    CALL_ADDPORTW,
    CALL_ADDPRINTERA,
    CALL_ADDPRINTERCONNECTIONA,
    CALL_ADDPRINTERCONNECTIONW,
    CALL_ADDPRINTERDRIVERA,
    CALL_ADDPRINTERDRIVEREXA,
    CALL_ADDPRINTERDRIVEREXW,
    CALL_ADDPRINTERDRIVERW,
    CALL_ADDPRINTERW,
    CALL_ADDPRINTPROCESSORA,
    CALL_ADDPRINTPROCESSORW,
    CALL_ADDPRINTPROVIDORA,
    CALL_ADDPRINTPROVIDORW,
    CALL_ADVANCEDDOCUMENTPROPERTIESA,
    CALL_ADVANCEDDOCUMENTPROPERTIESW,
    CALL_CLOSEPRINTER,
    CALL_CONFIGUREPORTA,
    CALL_CONFIGUREPORTW,
    CALL_CONNECTTOPRINTERDLG,
    CALL_DELETEFORMA,
    CALL_DELETEFORMW,
    CALL_DELETEMONITORA,
    CALL_DELETEMONITORW,
    CALL_DELETEPORTA,
    CALL_DELETEPORTW,
    CALL_DELETEPRINTER,
    CALL_DELETEPRINTERCONNECTIONA,
    CALL_DELETEPRINTERCONNECTIONW,
    CALL_DELETEPRINTERDATAEXA,
    CALL_DELETEPRINTERDATAEXW,
    CALL_DELETEPRINTERDRIVERA,
    CALL_DELETEPRINTERDRIVEREXA,
    CALL_DELETEPRINTERDRIVEREXW,
    CALL_DELETEPRINTERDRIVERW,
    CALL_DELETEPRINTPROCESSORA,
    CALL_DELETEPRINTPROCESSORW,
    CALL_DELETEPRINTPROVIDORA,
    CALL_DELETEPRINTPROVIDORW,
    CALL_DEVICECAPABILITIESA,
    CALL_DEVICECAPABILITIESW,
    CALL_DOCUMENTPROPERTIESA,
    CALL_DOCUMENTPROPERTIESW,
    CALL_ENDDOCPRINTER,
    CALL_ENDPAGEPRINTER,
    CALL_ENUMFORMSA,
    CALL_ENUMFORMSW,
    CALL_ENUMJOBSA,
    CALL_ENUMJOBSW,
    CALL_ENUMMONITORSA,
    CALL_ENUMMONITORSW,
    CALL_ENUMPORTSA,
    CALL_ENUMPORTSW,
    CALL_ENUMPRINTERDATAA,
    CALL_ENUMPRINTERDATAEXA,
    CALL_ENUMPRINTERDATAEXW,
    CALL_ENUMPRINTERDATAW,
    CALL_ENUMPRINTERDRIVERSA,
    CALL_ENUMPRINTERDRIVERSW,
    CALL_ENUMPRINTERKEYA,
    CALL_ENUMPRINTERKEYW,
    CALL_ENUMPRINTERSA,
    CALL_ENUMPRINTERSW,
    CALL_ENUMPRINTPROCESSORDATATYPESA,
    CALL_ENUMPRINTPROCESSORDATATYPESW,
    CALL_ENUMPRINTPROCESSORSA,
    CALL_ENUMPRINTPROCESSORSW,
    CALL_EXTDEVICEMODE,
    CALL_FINDCLOSEPRINTERCHANGENOTIFICATION,
    CALL_FINDFIRSTPRINTERCHANGENOTIFICATION,
    CALL_FINDNEXTPRINTERCHANGENOTIFICATION,
    CALL_FREEPRINTERNOTIFYINFO,
    CALL_GETDEFAULTPRINTERA,
    CALL_GETDEFAULTPRINTERW,
    CALL_GETFORMA,
    CALL_GETFORMW,
    CALL_GETJOBA,
    CALL_GETJOBW,
    CALL_GETPRINTERA,
    CALL_GETPRINTERDATAA,
    CALL_GETPRINTERDATAEXA,
    CALL_GETPRINTERDATAEXW,
    CALL_GETPRINTERDATAW,
    CALL_GETPRINTERDRIVERA,
    CALL_GETPRINTERDRIVERDIRECTORYA,
    CALL_GETPRINTERDRIVERDIRECTORYW,
    CALL_GETPRINTERDRIVERW,
    CALL_GETPRINTERW,
    CALL_GETPRINTPROCESSORDIRECTORYA,
    CALL_GETPRINTPROCESSORDIRECTORYW,
    CALL_ISVALIDDEVMODEA,
    CALL_ISVALIDDEVMODEW,
    CALL_OPENPRINTERA,
    CALL_OPENPRINTERW,
    CALL_PRINTERPROPERTIES,
    CALL_READPRINTER,
    CALL_RESETPRINTERA,
    CALL_RESETPRINTERW,
    CALL_SCHEDULEJOB,
    CALL_SETDEFAULTPRINTERA,
    CALL_SETDEFAULTPRINTERW,
    CALL_SETFORMA,
    CALL_SETFORMW,
    CALL_SETJOBA,
    CALL_SETJOBW,
    CALL_SETPRINTERA,
    CALL_SETPRINTERDATAA,
    CALL_SETPRINTERDATAEXA,
    CALL_SETPRINTERDATAEXW,
    CALL_SETPRINTERDATAW,
    CALL_SETPRINTERW,
    CALL_SPOOLERINIT,
    CALL_STARTDOCDLGA,
    CALL_STARTDOCDLGW,
    CALL_STARTDOCPRINTERA,
    CALL_STARTDOCPRINTERW,
    CALL_STARTPAGEPRINTER,
    CALL_UPLOADPRINTERDRIVERPACKAGEA,
    CALL_UPLOADPRINTERDRIVERPACKAGEW,
    CALL_WRITEPRINTER,
    CALL_XCVDATAW,
};

#ifdef QEMU_DLL_GUEST

#else


void qemu_AbortPrinter(struct qemu_syscall *call);
void qemu_AddFormA(struct qemu_syscall *call);
void qemu_AddFormW(struct qemu_syscall *call);
void qemu_AddJob(struct qemu_syscall *call);
void qemu_AddMonitor(struct qemu_syscall *call);
void qemu_AddPortA(struct qemu_syscall *call);
void qemu_AddPortEx(struct qemu_syscall *call);
void qemu_AddPortW(struct qemu_syscall *call);
void qemu_AddPrintProcessorA(struct qemu_syscall *call);
void qemu_AddPrintProcessorW(struct qemu_syscall *call);
void qemu_AddPrintProvidorA(struct qemu_syscall *call);
void qemu_AddPrintProvidorW(struct qemu_syscall *call);
void qemu_AddPrinterA(struct qemu_syscall *call);
void qemu_AddPrinterConnectionA(struct qemu_syscall *call);
void qemu_AddPrinterConnectionW(struct qemu_syscall *call);
void qemu_AddPrinterDriverA(struct qemu_syscall *call);
void qemu_AddPrinterDriverExA(struct qemu_syscall *call);
void qemu_AddPrinterDriverExW(struct qemu_syscall *call);
void qemu_AddPrinterDriverW(struct qemu_syscall *call);
void qemu_AddPrinterW(struct qemu_syscall *call);
void qemu_AdvancedDocumentPropertiesA(struct qemu_syscall *call);
void qemu_AdvancedDocumentPropertiesW(struct qemu_syscall *call);
void qemu_ClosePrinter(struct qemu_syscall *call);
void qemu_ConfigurePortA(struct qemu_syscall *call);
void qemu_ConfigurePortW(struct qemu_syscall *call);
void qemu_ConnectToPrinterDlg(struct qemu_syscall *call);
void qemu_DeleteFormA(struct qemu_syscall *call);
void qemu_DeleteFormW(struct qemu_syscall *call);
void qemu_DeleteMonitorA(struct qemu_syscall *call);
void qemu_DeleteMonitorW(struct qemu_syscall *call);
void qemu_DeletePortA(struct qemu_syscall *call);
void qemu_DeletePortW(struct qemu_syscall *call);
void qemu_DeletePrintProcessorA(struct qemu_syscall *call);
void qemu_DeletePrintProcessorW(struct qemu_syscall *call);
void qemu_DeletePrintProvidorA(struct qemu_syscall *call);
void qemu_DeletePrintProvidorW(struct qemu_syscall *call);
void qemu_DeletePrinter(struct qemu_syscall *call);
void qemu_DeletePrinterConnectionA(struct qemu_syscall *call);
void qemu_DeletePrinterConnectionW(struct qemu_syscall *call);
void qemu_DeletePrinterDataExA(struct qemu_syscall *call);
void qemu_DeletePrinterDataExW(struct qemu_syscall *call);
void qemu_DeletePrinterDriverA(struct qemu_syscall *call);
void qemu_DeletePrinterDriverExA(struct qemu_syscall *call);
void qemu_DeletePrinterDriverExW(struct qemu_syscall *call);
void qemu_DeletePrinterDriverW(struct qemu_syscall *call);
void qemu_DeviceCapabilitiesA(struct qemu_syscall *call);
void qemu_DeviceCapabilitiesW(struct qemu_syscall *call);
void qemu_DocumentPropertiesA(struct qemu_syscall *call);
void qemu_DocumentPropertiesW(struct qemu_syscall *call);
void qemu_EndDocPrinter(struct qemu_syscall *call);
void qemu_EndPagePrinter(struct qemu_syscall *call);
void qemu_EnumFormsA(struct qemu_syscall *call);
void qemu_EnumFormsW(struct qemu_syscall *call);
void qemu_EnumJobsA(struct qemu_syscall *call);
void qemu_EnumJobsW(struct qemu_syscall *call);
void qemu_EnumMonitorsA(struct qemu_syscall *call);
void qemu_EnumMonitorsW(struct qemu_syscall *call);
void qemu_EnumPortsA(struct qemu_syscall *call);
void qemu_EnumPortsW(struct qemu_syscall *call);
void qemu_EnumPrintProcessorDatatypesA(struct qemu_syscall *call);
void qemu_EnumPrintProcessorDatatypesW(struct qemu_syscall *call);
void qemu_EnumPrintProcessorsA(struct qemu_syscall *call);
void qemu_EnumPrintProcessorsW(struct qemu_syscall *call);
void qemu_EnumPrinterDataA(struct qemu_syscall *call);
void qemu_EnumPrinterDataExA(struct qemu_syscall *call);
void qemu_EnumPrinterDataExW(struct qemu_syscall *call);
void qemu_EnumPrinterDataW(struct qemu_syscall *call);
void qemu_EnumPrinterDrivers(struct qemu_syscall *call);
void qemu_EnumPrinterKeyA(struct qemu_syscall *call);
void qemu_EnumPrinterKeyW(struct qemu_syscall *call);
void qemu_EnumPrinters(struct qemu_syscall *call);
void qemu_ExtDeviceMode(struct qemu_syscall *call);
void qemu_FindClosePrinterChangeNotification(struct qemu_syscall *call);
void qemu_FindFirstPrinterChangeNotification(struct qemu_syscall *call);
void qemu_FindNextPrinterChangeNotification(struct qemu_syscall *call);
void qemu_FreePrinterNotifyInfo(struct qemu_syscall *call);
void qemu_GetDefaultPrinterA(struct qemu_syscall *call);
void qemu_GetDefaultPrinterW(struct qemu_syscall *call);
void qemu_GetFormA(struct qemu_syscall *call);
void qemu_GetFormW(struct qemu_syscall *call);
void qemu_GetJob(struct qemu_syscall *call);
void qemu_GetPrintProcessorDirectoryA(struct qemu_syscall *call);
void qemu_GetPrintProcessorDirectoryW(struct qemu_syscall *call);
void qemu_GetPrinter(struct qemu_syscall *call);
void qemu_GetPrinterDataA(struct qemu_syscall *call);
void qemu_GetPrinterDataExA(struct qemu_syscall *call);
void qemu_GetPrinterDataExW(struct qemu_syscall *call);
void qemu_GetPrinterDataW(struct qemu_syscall *call);
void qemu_GetPrinterDriver(struct qemu_syscall *call);
void qemu_GetPrinterDriverDirectoryA(struct qemu_syscall *call);
void qemu_GetPrinterDriverDirectoryW(struct qemu_syscall *call);
void qemu_IsValidDevmodeA(struct qemu_syscall *call);
void qemu_IsValidDevmodeW(struct qemu_syscall *call);
void qemu_OpenPrinter(struct qemu_syscall *call);
void qemu_PrinterProperties(struct qemu_syscall *call);
void qemu_ReadPrinter(struct qemu_syscall *call);
void qemu_ResetPrinterA(struct qemu_syscall *call);
void qemu_ResetPrinterW(struct qemu_syscall *call);
void qemu_ScheduleJob(struct qemu_syscall *call);
void qemu_SetDefaultPrinterA(struct qemu_syscall *call);
void qemu_SetDefaultPrinterW(struct qemu_syscall *call);
void qemu_SetFormA(struct qemu_syscall *call);
void qemu_SetFormW(struct qemu_syscall *call);
void qemu_SetJobA(struct qemu_syscall *call);
void qemu_SetJobW(struct qemu_syscall *call);
void qemu_SetPrinterA(struct qemu_syscall *call);
void qemu_SetPrinterDataA(struct qemu_syscall *call);
void qemu_SetPrinterDataExA(struct qemu_syscall *call);
void qemu_SetPrinterDataExW(struct qemu_syscall *call);
void qemu_SetPrinterDataW(struct qemu_syscall *call);
void qemu_SetPrinterW(struct qemu_syscall *call);
void qemu_SpoolerInit(struct qemu_syscall *call);
void qemu_StartDocDlgA(struct qemu_syscall *call);
void qemu_StartDocDlgW(struct qemu_syscall *call);
void qemu_StartDocPrinterA(struct qemu_syscall *call);
void qemu_StartDocPrinterW(struct qemu_syscall *call);
void qemu_StartPagePrinter(struct qemu_syscall *call);
void qemu_UploadPrinterDriverPackageA(struct qemu_syscall *call);
void qemu_UploadPrinterDriverPackageW(struct qemu_syscall *call);
void qemu_WritePrinter(struct qemu_syscall *call);
void qemu_XcvDataW(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

INT (WINAPI *pDeviceCapabilitiesA)(LPCSTR pDevice,LPCSTR pPort, WORD cap, LPSTR pOutput, const DEVMODEA *lpdm);
INT (WINAPI *pDeviceCapabilitiesW)(LPCWSTR pDevice, LPCWSTR pPort, WORD fwCapability, LPWSTR pOutput, const DEVMODEW *pDevMode);
LONG (WINAPI *pDocumentPropertiesA)(HWND hWnd,HANDLE hPrinter, LPSTR pDeviceName, LPDEVMODEA pDevModeOutput,
        LPDEVMODEA pDevModeInput,DWORD fMode);
LONG (WINAPI *pDocumentPropertiesW)(HWND hWnd, HANDLE hPrinter, LPWSTR pDeviceName, LPDEVMODEW pDevModeOutput,
        LPDEVMODEW pDevModeInput, DWORD fMode);
BOOL (WINAPI *pIsValidDevmodeA)(PDEVMODEA pDevMode, size_t size);
BOOL (WINAPI *pIsValidDevmodeW)(PDEVMODEW pDevMode, size_t size);
BOOL (WINAPI *pOpenPrinterA)(LPSTR lpPrinterName,HANDLE *phPrinter, LPPRINTER_DEFAULTSA pDefault);
BOOL (WINAPI *pOpenPrinterW)(LPWSTR lpPrinterName,HANDLE *phPrinter, LPPRINTER_DEFAULTSW pDefault);
BOOL (WINAPI *pAddMonitorA)(LPSTR pName, DWORD Level, LPBYTE pMonitors);
BOOL (WINAPI *pAddMonitorW)(LPWSTR pName, DWORD Level, LPBYTE pMonitors);
BOOL (WINAPI *pDeletePrinterDriverA )(LPSTR pName, LPSTR pEnvironment, LPSTR pDriverName);
BOOL (WINAPI *pDeletePrinterDriverW )(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pDriverName);
BOOL (WINAPI *pDeleteMonitorA )(LPSTR pName, LPSTR pEnvironment, LPSTR pMonitorName);
BOOL (WINAPI *pDeleteMonitorW)(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pMonitorName);
BOOL (WINAPI *pDeletePortA )(LPSTR pName, HWND hWnd, LPSTR pPortName);
BOOL (WINAPI *pDeletePortW )(LPWSTR pName, HWND hWnd, LPWSTR pPortName);
BOOL (WINAPI *pWritePrinter)(HANDLE hPrinter, LPVOID pBuf, DWORD cbBuf, LPDWORD pcWritten);
BOOL (WINAPI *pAddFormA)(HANDLE hPrinter, DWORD Level, LPBYTE pForm);
BOOL (WINAPI *pAddFormW)(HANDLE hPrinter, DWORD Level, LPBYTE pForm);
BOOL (WINAPI *pAddJobA)(HANDLE hPrinter, DWORD Level, LPBYTE pData, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pAddJobW)(HANDLE hPrinter, DWORD Level, LPBYTE pData, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetPrintProcessorDirectoryA)(LPSTR server, LPSTR env, DWORD level, LPBYTE Info,
        DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetPrintProcessorDirectoryW)(LPWSTR server, LPWSTR env, DWORD level, LPBYTE Info,
        DWORD cbBuf, LPDWORD pcbNeeded);
HANDLE (WINAPI *pAddPrinterW)(LPWSTR pName, DWORD Level, LPBYTE pPrinter);
HANDLE (WINAPI *pAddPrinterA)(LPSTR pName, DWORD Level, LPBYTE pPrinter);
BOOL (WINAPI *pClosePrinter)(HANDLE hPrinter);
BOOL (WINAPI *pDeleteFormA)(HANDLE hPrinter, LPSTR pFormName);
BOOL (WINAPI *pDeleteFormW)(HANDLE hPrinter, LPWSTR pFormName);
BOOL (WINAPI *pDeletePrinter)(HANDLE hPrinter);
BOOL (WINAPI *pSetPrinterA)(HANDLE printer, DWORD level, LPBYTE data, DWORD command);
BOOL (WINAPI *pSetPrinterW)(HANDLE printer, DWORD level, LPBYTE data, DWORD command);
BOOL (WINAPI *pSetJobA)(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD Command);
BOOL (WINAPI *pSetJobW)(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD Command);
BOOL (WINAPI *pEndDocPrinter)(HANDLE hPrinter);
BOOL (WINAPI *pEndPagePrinter)(HANDLE hPrinter);
DWORD (WINAPI *pStartDocPrinterA)(HANDLE hPrinter, DWORD Level, LPBYTE pDocInfo);
DWORD (WINAPI *pStartDocPrinterW)(HANDLE hPrinter, DWORD Level, LPBYTE pDocInfo);
BOOL (WINAPI *pStartPagePrinter)(HANDLE hPrinter);
BOOL (WINAPI *pGetFormA)(HANDLE hPrinter, LPSTR pFormName, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetFormW)(HANDLE hPrinter, LPWSTR pFormName, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pSetFormA)(HANDLE hPrinter, LPSTR pFormName, DWORD Level, LPBYTE pForm);
BOOL (WINAPI *pSetFormW)(HANDLE hPrinter, LPWSTR pFormName, DWORD Level, LPBYTE pForm);
BOOL (WINAPI *pReadPrinter)(HANDLE hPrinter, LPVOID pBuf, DWORD cbBuf, LPDWORD pNoBytesRead);
BOOL (WINAPI *pResetPrinterA)(HANDLE hPrinter, LPPRINTER_DEFAULTSA pDefault);
BOOL (WINAPI *pResetPrinterW)(HANDLE hPrinter, LPPRINTER_DEFAULTSW pDefault);
BOOL (WINAPI *pGetPrinterW)(HANDLE hPrinter, DWORD Level, LPBYTE pPrinter, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetPrinterA)(HANDLE hPrinter, DWORD Level, LPBYTE pPrinter, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pEnumPrintersW)(DWORD dwType, LPWSTR lpszName, DWORD dwLevel, LPBYTE lpbPrinters, DWORD cbBuf,
        LPDWORD lpdwNeeded, LPDWORD lpdwReturned);
BOOL (WINAPI *pEnumPrintersA)(DWORD dwType, LPSTR lpszName, DWORD dwLevel, LPBYTE lpbPrinters, DWORD cbBuf,
        LPDWORD lpdwNeeded, LPDWORD lpdwReturned);
BOOL (WINAPI *pGetPrinterDriverW)(HANDLE hPrinter, LPWSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetPrinterDriverA)(HANDLE hPrinter, LPSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetPrinterDriverDirectoryW)(LPWSTR pName, LPWSTR pEnvironment, DWORD Level,
        LPBYTE pDriverDirectory, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetPrinterDriverDirectoryA)(LPSTR pName, LPSTR pEnvironment, DWORD Level,
        LPBYTE pDriverDirectory, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pAddPrinterDriverA)(LPSTR pName, DWORD level, LPBYTE pDriverInfo);
BOOL (WINAPI *pAddPrinterDriverW)(LPWSTR pName, DWORD level, LPBYTE pDriverInfo);
BOOL (WINAPI *pAddPrintProcessorA)(LPSTR pName, LPSTR pEnvironment, LPSTR pPathName, LPSTR pPrintProcessorName);
BOOL (WINAPI *pAddPrintProcessorW)(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pPathName, LPWSTR pPrintProcessorName);
BOOL (WINAPI *pAddPrintProvidorA)(LPSTR pName, DWORD Level, LPBYTE pProviderInfo);
BOOL (WINAPI *pAddPrintProvidorW)(LPWSTR pName, DWORD Level, LPBYTE pProviderInfo);
LONG (WINAPI *pAdvancedDocumentPropertiesA)(HWND hWnd, HANDLE hPrinter, LPSTR pDeviceName, PDEVMODEA pDevModeOutput, PDEVMODEA pDevModeInput);
LONG (WINAPI *pAdvancedDocumentPropertiesW)(HWND hWnd, HANDLE hPrinter, LPWSTR pDeviceName, PDEVMODEW pDevModeOutput, PDEVMODEW pDevModeInput);
BOOL (WINAPI *pPrinterProperties)(HWND hWnd, HANDLE hPrinter);
BOOL (WINAPI *pEnumJobsA)(HANDLE hPrinter, DWORD FirstJob, DWORD NoJobs, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumJobsW)(HANDLE hPrinter, DWORD FirstJob, DWORD NoJobs, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPrinterDriversW)(LPWSTR pName, LPWSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo,
        DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPrinterDriversA)(LPSTR pName, LPSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo,
        DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPortsA)(LPSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPortsW)(LPWSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pGetDefaultPrinterW)(LPWSTR name, LPDWORD namesize);
BOOL (WINAPI *pGetDefaultPrinterA)(LPSTR name, LPDWORD namesize);
BOOL (WINAPI *pSetDefaultPrinterW)(LPCWSTR pszPrinter);
BOOL (WINAPI *pSetDefaultPrinterA)(LPCSTR pszPrinter);
DWORD (WINAPI *pSetPrinterDataExA)(HANDLE hPrinter, LPCSTR pKeyName, LPCSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData);
DWORD (WINAPI *pSetPrinterDataExW)(HANDLE hPrinter, LPCWSTR pKeyName, LPCWSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData);
DWORD (WINAPI *pSetPrinterDataA)(HANDLE hPrinter, LPSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData);
DWORD (WINAPI *pSetPrinterDataW)(HANDLE hPrinter, LPWSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData);
DWORD (WINAPI *pGetPrinterDataExA)(HANDLE hPrinter, LPCSTR pKeyName, LPCSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded);
DWORD (WINAPI *pGetPrinterDataExW)(HANDLE hPrinter, LPCWSTR pKeyName, LPCWSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded);
DWORD (WINAPI *pGetPrinterDataA)(HANDLE hPrinter, LPSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded);
DWORD (WINAPI *pGetPrinterDataW)(HANDLE hPrinter, LPWSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded);
DWORD (WINAPI *pEnumPrinterDataExW)(HANDLE hPrinter, LPCWSTR pKeyName, LPBYTE pEnumValues, DWORD cbEnumValues, LPDWORD pcbEnumValues, LPDWORD pnEnumValues);
DWORD (WINAPI *pEnumPrinterDataExA)(HANDLE hPrinter, LPCSTR pKeyName, LPBYTE pEnumValues, DWORD cbEnumValues, LPDWORD pcbEnumValues, LPDWORD pnEnumValues);
BOOL (WINAPI *pAbortPrinter)(HANDLE hPrinter);
BOOL (WINAPI *pAddPortA)(LPSTR pName, HWND hWnd, LPSTR pMonitorName);
BOOL (WINAPI *pAddPortW)(LPWSTR pName, HWND hWnd, LPWSTR pMonitorName);
BOOL (WINAPI *pAddPortExA)(LPSTR pName, DWORD level, LPBYTE pBuffer, LPSTR pMonitorName);
BOOL (WINAPI *pAddPortExW)(LPWSTR pName, DWORD level, LPBYTE pBuffer, LPWSTR pMonitorName);
BOOL (WINAPI *pAddPrinterConnectionA)(LPSTR pName);
BOOL (WINAPI *pAddPrinterConnectionW)(LPWSTR pName);
BOOL (WINAPI *pAddPrinterDriverExW)(LPWSTR pName, DWORD level, LPBYTE pDriverInfo, DWORD dwFileCopyFlags);
BOOL (WINAPI *pAddPrinterDriverExA)(LPSTR pName, DWORD Level, LPBYTE pDriverInfo, DWORD dwFileCopyFlags);
BOOL (WINAPI *pConfigurePortA)(LPSTR pName, HWND hWnd, LPSTR pPortName);
BOOL (WINAPI *pConfigurePortW)(LPWSTR pName, HWND hWnd, LPWSTR pPortName);
HANDLE (WINAPI *pConnectToPrinterDlg)(HWND hWnd, DWORD Flags);
BOOL (WINAPI *pDeletePrinterConnectionA)(LPSTR pName);
BOOL (WINAPI *pDeletePrinterConnectionW)(LPWSTR pName);
BOOL (WINAPI *pDeletePrinterDriverExW)(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pDriverName, DWORD dwDeleteFlag, DWORD dwVersionFlag);
BOOL (WINAPI *pDeletePrinterDriverExA)(LPSTR pName, LPSTR pEnvironment, LPSTR pDriverName, DWORD dwDeleteFlag, DWORD dwVersionFlag);
DWORD (WINAPI *pDeletePrinterDataExW)(HANDLE hPrinter, LPCWSTR pKeyName, LPCWSTR pValueName);
DWORD (WINAPI *pDeletePrinterDataExA)(HANDLE hPrinter, LPCSTR pKeyName, LPCSTR pValueName);
BOOL (WINAPI *pDeletePrintProcessorA)(LPSTR pName, LPSTR pEnvironment, LPSTR pPrintProcessorName);
BOOL (WINAPI *pDeletePrintProcessorW)(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pPrintProcessorName);
BOOL (WINAPI *pDeletePrintProvidorA)(LPSTR pName, LPSTR pEnvironment, LPSTR pPrintProviderName);
BOOL (WINAPI *pDeletePrintProvidorW)(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pPrintProviderName);
BOOL (WINAPI *pEnumFormsA)(HANDLE hPrinter, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumFormsW)(HANDLE hPrinter, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumMonitorsA)(LPSTR pName, DWORD Level, LPBYTE pMonitors, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumMonitorsW)(LPWSTR pName, DWORD Level, LPBYTE pMonitors, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pSpoolerInit)(void);
BOOL (WINAPI *pXcvDataW)(HANDLE hXcv, LPCWSTR pszDataName, PBYTE pInputData, DWORD cbInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded, PDWORD pdwStatus);
DWORD (WINAPI *pEnumPrinterDataA)(HANDLE hPrinter, DWORD dwIndex, LPSTR pValueName, DWORD cbValueName, LPDWORD pcbValueName, LPDWORD pType, LPBYTE pData, DWORD cbData, LPDWORD pcbData);
DWORD (WINAPI *pEnumPrinterDataW)(HANDLE hPrinter, DWORD dwIndex, LPWSTR pValueName, DWORD cbValueName, LPDWORD pcbValueName, LPDWORD pType, LPBYTE pData, DWORD cbData, LPDWORD pcbData);
DWORD (WINAPI *pEnumPrinterKeyA)(HANDLE printer, const CHAR *key, CHAR *subkey, DWORD size, DWORD *needed);
DWORD (WINAPI *pEnumPrinterKeyW)(HANDLE printer, const WCHAR *key, WCHAR *subkey, DWORD size, DWORD *needed);
BOOL (WINAPI *pEnumPrintProcessorDatatypesA)(LPSTR pName, LPSTR pPrintProcessorName, DWORD Level, LPBYTE pDatatypes, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPrintProcessorDatatypesW)(LPWSTR pName, LPWSTR pPrintProcessorName, DWORD Level, LPBYTE pDatatypes, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPrintProcessorsA)(LPSTR pName, LPSTR pEnvironment, DWORD Level, LPBYTE pPPInfo, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pEnumPrintProcessorsW)(LPWSTR pName, LPWSTR pEnvironment, DWORD Level, LPBYTE pPPInfo, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
BOOL (WINAPI *pFindClosePrinterChangeNotification)(HANDLE hChange);
HANDLE (WINAPI *pFindFirstPrinterChangeNotification)(HANDLE hPrinter, DWORD fdwFlags, DWORD fdwOptions, LPVOID pPrinterNotifyOptions);
BOOL (WINAPI *pFindNextPrinterChangeNotification)(HANDLE hChange, PDWORD pdwChange, LPVOID pPrinterNotifyOptions, LPVOID *ppPrinterNotifyInfo);
BOOL (WINAPI *pFreePrinterNotifyInfo)(PPRINTER_NOTIFY_INFO pPrinterNotifyInfo);
BOOL (WINAPI *pGetJobA)(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pGetJobW)(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded);
BOOL (WINAPI *pScheduleJob)(HANDLE hPrinter, DWORD dwJobID);
LPSTR (WINAPI *pStartDocDlgA)(HANDLE hPrinter, DOCINFOA *doc);
LPWSTR (WINAPI *pStartDocDlgW)(HANDLE hPrinter, DOCINFOW *doc);
HRESULT (WINAPI *pUploadPrinterDriverPackageA)(LPCSTR server, LPCSTR path, LPCSTR env, DWORD flags, HWND hwnd, LPSTR dst, PULONG dstlen);
HRESULT (WINAPI *pUploadPrinterDriverPackageW)(LPCWSTR server, LPCWSTR path, LPCWSTR env, DWORD flags, HWND hwnd, LPWSTR dst, PULONG dstlen);
LONG (WINAPI *pExtDeviceMode)(HWND hWnd, HANDLE hInst, LPDEVMODEA pDevModeOutput, LPSTR pDeviceName, LPSTR pPort, LPDEVMODEA pDevModeInput, LPSTR pProfile, DWORD fMode);
#endif

#endif
