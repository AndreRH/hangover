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

#endif

#endif
