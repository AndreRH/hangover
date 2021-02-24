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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#define COBJMACROS

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_winspool.drv.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winspool);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AbortPrinter,
    qemu_AddFormA,
    qemu_AddFormW,
    qemu_AddJob,
    qemu_AddJob,
    qemu_AddMonitor,
    qemu_AddMonitor,
    qemu_AddPortA,
    qemu_AddPortEx,
    qemu_AddPortEx,
    qemu_AddPortW,
    qemu_AddPrinterA,
    qemu_AddPrinterConnectionA,
    qemu_AddPrinterConnectionW,
    qemu_AddPrinterDriverA,
    qemu_AddPrinterDriverExA,
    qemu_AddPrinterDriverExW,
    qemu_AddPrinterDriverW,
    qemu_AddPrinterW,
    qemu_AddPrintProcessorA,
    qemu_AddPrintProcessorW,
    qemu_AddPrintProvidorA,
    qemu_AddPrintProvidorW,
    qemu_AdvancedDocumentPropertiesA,
    qemu_AdvancedDocumentPropertiesW,
    qemu_ClosePrinter,
    qemu_ConfigurePortA,
    qemu_ConfigurePortW,
    qemu_ConnectToPrinterDlg,
    qemu_DeleteFormA,
    qemu_DeleteFormW,
    qemu_DeleteMonitorA,
    qemu_DeleteMonitorW,
    qemu_DeletePortA,
    qemu_DeletePortW,
    qemu_DeletePrinter,
    qemu_DeletePrinterConnectionA,
    qemu_DeletePrinterConnectionW,
    qemu_DeletePrinterDataExA,
    qemu_DeletePrinterDataExW,
    qemu_DeletePrinterDriverA,
    qemu_DeletePrinterDriverExA,
    qemu_DeletePrinterDriverExW,
    qemu_DeletePrinterDriverW,
    qemu_DeletePrintProcessorA,
    qemu_DeletePrintProcessorW,
    qemu_DeletePrintProvidorA,
    qemu_DeletePrintProvidorW,
    qemu_DeviceCapabilitiesA,
    qemu_DeviceCapabilitiesW,
    qemu_DocumentPropertiesA,
    qemu_DocumentPropertiesW,
    qemu_EndDocPrinter,
    qemu_EndPagePrinter,
    qemu_EnumFormsA,
    qemu_EnumFormsW,
    qemu_EnumJobsA,
    qemu_EnumJobsW,
    qemu_EnumMonitorsA,
    qemu_EnumMonitorsW,
    qemu_EnumPortsA,
    qemu_EnumPortsW,
    qemu_EnumPrinterDataA,
    qemu_EnumPrinterDataExA,
    qemu_EnumPrinterDataExW,
    qemu_EnumPrinterDataW,
    qemu_EnumPrinterDrivers,
    qemu_EnumPrinterDrivers,
    qemu_EnumPrinterKeyA,
    qemu_EnumPrinterKeyW,
    qemu_EnumPrinters,
    qemu_EnumPrinters,
    qemu_EnumPrintProcessorDatatypesA,
    qemu_EnumPrintProcessorDatatypesW,
    qemu_EnumPrintProcessorsA,
    qemu_EnumPrintProcessorsW,
    qemu_ExtDeviceMode,
    qemu_FindClosePrinterChangeNotification,
    qemu_FindFirstPrinterChangeNotification,
    qemu_FindNextPrinterChangeNotification,
    qemu_FreePrinterNotifyInfo,
    qemu_GetDefaultPrinterA,
    qemu_GetDefaultPrinterW,
    qemu_GetFormA,
    qemu_GetFormW,
    qemu_GetJob,
    qemu_GetJob,
    qemu_GetPrinter,
    qemu_GetPrinterDataA,
    qemu_GetPrinterDataExA,
    qemu_GetPrinterDataExW,
    qemu_GetPrinterDataW,
    qemu_GetPrinterDriver,
    qemu_GetPrinterDriverDirectoryA,
    qemu_GetPrinterDriverDirectoryW,
    qemu_GetPrinterDriver,
    qemu_GetPrinter,
    qemu_GetPrintProcessorDirectoryA,
    qemu_GetPrintProcessorDirectoryW,
    qemu_IsValidDevmodeA,
    qemu_IsValidDevmodeW,
    qemu_OpenPrinter,
    qemu_OpenPrinter,
    qemu_PrinterProperties,
    qemu_ReadPrinter,
    qemu_ResetPrinterA,
    qemu_ResetPrinterW,
    qemu_ScheduleJob,
    qemu_SetDefaultPrinterA,
    qemu_SetDefaultPrinterW,
    qemu_SetFormA,
    qemu_SetFormW,
    qemu_SetJobA,
    qemu_SetJobW,
    qemu_SetPrinterA,
    qemu_SetPrinterDataA,
    qemu_SetPrinterDataExA,
    qemu_SetPrinterDataExW,
    qemu_SetPrinterDataW,
    qemu_SetPrinterW,
    qemu_SpoolerInit,
    qemu_StartDocDlgA,
    qemu_StartDocDlgW,
    qemu_StartDocPrinterA,
    qemu_StartDocPrinterW,
    qemu_StartPagePrinter,
    qemu_UploadPrinterDriverPackageA,
    qemu_UploadPrinterDriverPackageW,
    qemu_WritePrinter,
    qemu_XcvDataW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE winspool;
    WINE_TRACE("Loading host-side winspool.drv wrapper.\n");

    winspool = LoadLibraryA("winspool.drv");
    if (!winspool)
    {
        WINE_FIXME("Could not load host winspool.drv.\n");
        return NULL;
    }

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    pDeviceCapabilitiesA = (void *)GetProcAddress(winspool, "DeviceCapabilitiesA");
    if (!pDeviceCapabilitiesA)
        WINE_ERR("Could not find DeviceCapabilitiesA in winspool.drv.\n");

    pDeviceCapabilitiesW = (void *)GetProcAddress(winspool, "DeviceCapabilitiesW");
    if (!pDeviceCapabilitiesW)
        WINE_ERR("Could not find DeviceCapabilitiesW in winspool.drv.\n");

    pDocumentPropertiesA = (void *)GetProcAddress(winspool, "DocumentPropertiesA");
    if (!pDocumentPropertiesA)
        WINE_ERR("Could not find DocumentPropertiesA in winspool.drv.\n");

    pDocumentPropertiesW = (void *)GetProcAddress(winspool, "DocumentPropertiesW");
    if (!pDocumentPropertiesW)
        WINE_ERR("Could not find DocumentPropertiesW in winspool.drv.\n");

    pIsValidDevmodeA = (void *)GetProcAddress(winspool, "IsValidDevmodeA");
    if (!pIsValidDevmodeA)
        WINE_ERR("Could not find IsValidDevmodeA in winspool.drv.\n");

    pIsValidDevmodeW = (void *)GetProcAddress(winspool, "IsValidDevmodeW");
    if (!pIsValidDevmodeW)
        WINE_ERR("Could not find IsValidDevmodeW in winspool.drv.\n");

    pOpenPrinterA = (void *)GetProcAddress(winspool, "OpenPrinterA");
    if (!pOpenPrinterA)
        WINE_ERR("Could not find OpenPrinterA in winspool.drv.\n");

    pOpenPrinterW = (void *)GetProcAddress(winspool, "OpenPrinterW");
    if (!pOpenPrinterW)
        WINE_ERR("Could not find OpenPrinterW in winspool.drv.\n");

    pAddMonitorA = (void *)GetProcAddress(winspool, "AddMonitorA");
    if (!pAddMonitorA)
        WINE_ERR("Could not find AddMonitorA in winspool.drv.\n");

    pAddMonitorW = (void *)GetProcAddress(winspool, "AddMonitorW");
    if (!pAddMonitorW)
        WINE_ERR("Could not find AddMonitorW in winspool.drv.\n");

    pDeletePrinterDriverA = (void *)GetProcAddress(winspool, "DeletePrinterDriverA");
    if (!pDeletePrinterDriverA)
        WINE_ERR("Could not find DeletePrinterDriverA in winspool.drv.\n");

    pDeletePrinterDriverW = (void *)GetProcAddress(winspool, "DeletePrinterDriverW");
    if (!pDeletePrinterDriverW)
        WINE_ERR("Could not find DeletePrinterDriverW in winspool.drv.\n");

    pDeleteMonitorA = (void *)GetProcAddress(winspool, "DeleteMonitorA");
    if (!pDeleteMonitorA)
        WINE_ERR("Could not find DeleteMonitorA in winspool.drv.\n");

    pDeleteMonitorW = (void *)GetProcAddress(winspool, "DeleteMonitorW");
    if (!pDeleteMonitorW)
        WINE_ERR("Could not find DeleteMonitorW in winspool.drv.\n");

    pDeletePortA = (void *)GetProcAddress(winspool, "DeletePortA");
    if (!pDeletePortA)
        WINE_ERR("Could not find DeletePortA in winspool.drv.\n");

    pDeletePortW = (void *)GetProcAddress(winspool, "DeletePortW");
    if (!pDeletePortW)
        WINE_ERR("Could not find DeletePortW in winspool.drv.\n");

    pWritePrinter = (void *)GetProcAddress(winspool, "WritePrinter");
    if (!pWritePrinter)
        WINE_ERR("Could not find WritePrinter in winspool.drv.\n");

    pAddFormA = (void *)GetProcAddress(winspool, "AddFormA");
    if (!pAddFormA)
        WINE_ERR("Could not find AddFormA in winspool.drv.\n");

    pAddFormW = (void *)GetProcAddress(winspool, "AddFormW");
    if (!pAddFormW)
        WINE_ERR("Could not find AddFormW in winspool.drv.\n");

    pAddJobA = (void *)GetProcAddress(winspool, "AddJobA");
    if (!pAddJobA)
        WINE_ERR("Could not find AddJobA in winspool.drv.\n");

    pAddJobW = (void *)GetProcAddress(winspool, "AddJobW");
    if (!pAddJobW)
        WINE_ERR("Could not find AddJobW in winspool.drv.\n");

    pGetPrintProcessorDirectoryA = (void *)GetProcAddress(winspool, "GetPrintProcessorDirectoryA");
    if (!pGetPrintProcessorDirectoryA)
        WINE_ERR("Could not find GetPrintProcessorDirectoryA in winspool.drv.\n");

    pGetPrintProcessorDirectoryW = (void *)GetProcAddress(winspool, "GetPrintProcessorDirectoryW");
    if (!pGetPrintProcessorDirectoryW)
        WINE_ERR("Could not find GetPrintProcessorDirectoryW in winspool.drv.\n");

    pAddPrinterW = (void *)GetProcAddress(winspool, "AddPrinterW");
    if (!pAddPrinterW)
        WINE_ERR("Could not find AddPrinterW in winspool.drv.\n");

    pAddPrinterA = (void *)GetProcAddress(winspool, "AddPrinterA");
    if (!pAddPrinterA)
        WINE_ERR("Could not find AddPrinterA in winspool.drv.\n");

    pClosePrinter = (void *)GetProcAddress(winspool, "ClosePrinter");
    if (!pClosePrinter)
        WINE_ERR("Could not find ClosePrinter in winspool.drv.\n");

    pDeleteFormA = (void *)GetProcAddress(winspool, "DeleteFormA");
    if (!pDeleteFormA)
        WINE_ERR("Could not find DeleteFormA in winspool.drv.\n");

    pDeleteFormW = (void *)GetProcAddress(winspool, "DeleteFormW");
    if (!pDeleteFormW)
        WINE_ERR("Could not find DeleteFormW in winspool.drv.\n");

    pDeletePrinter = (void *)GetProcAddress(winspool, "DeletePrinter");
    if (!pDeletePrinter)
        WINE_ERR("Could not find DeletePrinter in winspool.drv.\n");

    pSetPrinterA = (void *)GetProcAddress(winspool, "SetPrinterA");
    if (!pSetPrinterA)
        WINE_ERR("Could not find SetPrinterA in winspool.drv.\n");

    pSetPrinterW = (void *)GetProcAddress(winspool, "SetPrinterW");
    if (!pSetPrinterW)
        WINE_ERR("Could not find SetPrinterW in winspool.drv.\n");

    pSetJobA = (void *)GetProcAddress(winspool, "SetJobA");
    if (!pSetJobA)
        WINE_ERR("Could not find SetJobA in winspool.drv.\n");

    pSetJobW = (void *)GetProcAddress(winspool, "SetJobW");
    if (!pSetJobW)
        WINE_ERR("Could not find SetJobW in winspool.drv.\n");

    pEndDocPrinter = (void *)GetProcAddress(winspool, "EndDocPrinter");
    if (!pEndDocPrinter)
        WINE_ERR("Could not find EndDocPrinter in winspool.drv.\n");

    pEndPagePrinter = (void *)GetProcAddress(winspool, "EndPagePrinter");
    if (!pEndPagePrinter)
        WINE_ERR("Could not find EndPagePrinter in winspool.drv.\n");

    pStartDocPrinterA = (void *)GetProcAddress(winspool, "StartDocPrinterA");
    if (!pStartDocPrinterA)
        WINE_ERR("Could not find StartDocPrinterA in winspool.drv.\n");

    pStartDocPrinterW = (void *)GetProcAddress(winspool, "StartDocPrinterW");
    if (!pStartDocPrinterW)
        WINE_ERR("Could not find StartDocPrinterW in winspool.drv.\n");

    pStartPagePrinter = (void *)GetProcAddress(winspool, "StartPagePrinter");
    if (!pStartPagePrinter)
        WINE_ERR("Could not find StartPagePrinter in winspool.drv.\n");

    pGetFormA = (void *)GetProcAddress(winspool, "GetFormA");
    if (!pGetFormA)
        WINE_ERR("Could not find GetFormA in winspool.drv.\n");

    pGetFormW = (void *)GetProcAddress(winspool, "GetFormW");
    if (!pGetFormW)
        WINE_ERR("Could not find GetFormW in winspool.drv.\n");

    pSetFormA = (void *)GetProcAddress(winspool, "SetFormA");
    if (!pSetFormA)
        WINE_ERR("Could not find SetFormA in winspool.drv.\n");

    pSetFormW = (void *)GetProcAddress(winspool, "SetFormW");
    if (!pSetFormW)
        WINE_ERR("Could not find SetFormW in winspool.drv.\n");

    pReadPrinter = (void *)GetProcAddress(winspool, "ReadPrinter");
    if (!pReadPrinter)
        WINE_ERR("Could not find ReadPrinter in winspool.drv.\n");

    pResetPrinterA = (void *)GetProcAddress(winspool, "ResetPrinterA");
    if (!pResetPrinterA)
        WINE_ERR("Could not find ResetPrinterA in winspool.drv.\n");

    pResetPrinterW = (void *)GetProcAddress(winspool, "ResetPrinterW");
    if (!pResetPrinterW)
        WINE_ERR("Could not find ResetPrinterW in winspool.drv.\n");

    pGetPrinterW = (void *)GetProcAddress(winspool, "GetPrinterW");
    if (!pGetPrinterW)
        WINE_ERR("Could not find GetPrinterW in winspool.drv.\n");

    pGetPrinterA = (void *)GetProcAddress(winspool, "GetPrinterA");
    if (!pGetPrinterA)
        WINE_ERR("Could not find GetPrinterA in winspool.drv.\n");

    pEnumPrintersW = (void *)GetProcAddress(winspool, "EnumPrintersW");
    if (!pEnumPrintersW)
        WINE_ERR("Could not find EnumPrintersW in winspool.drv.\n");

    pEnumPrintersA = (void *)GetProcAddress(winspool, "EnumPrintersA");
    if (!pEnumPrintersA)
        WINE_ERR("Could not find EnumPrintersA in winspool.drv.\n");

    pGetPrinterDriverW = (void *)GetProcAddress(winspool, "GetPrinterDriverW");
    if (!pGetPrinterDriverW)
        WINE_ERR("Could not find GetPrinterDriverW in winspool.drv.\n");

    pGetPrinterDriverA = (void *)GetProcAddress(winspool, "GetPrinterDriverA");
    if (!pGetPrinterDriverA)
        WINE_ERR("Could not find GetPrinterDriverA in winspool.drv.\n");

    pGetPrinterDriverDirectoryW = (void *)GetProcAddress(winspool, "GetPrinterDriverDirectoryW");
    if (!pGetPrinterDriverDirectoryW)
        WINE_ERR("Could not find GetPrinterDriverDirectoryW in winspool.drv.\n");

    pGetPrinterDriverDirectoryA = (void *)GetProcAddress(winspool, "GetPrinterDriverDirectoryA");
    if (!pGetPrinterDriverDirectoryA)
        WINE_ERR("Could not find GetPrinterDriverDirectoryA in winspool.drv.\n");

    pAddPrinterDriverA = (void *)GetProcAddress(winspool, "AddPrinterDriverA");
    if (!pAddPrinterDriverA)
        WINE_ERR("Could not find AddPrinterDriverA in winspool.drv.\n");

    pAddPrinterDriverW = (void *)GetProcAddress(winspool, "AddPrinterDriverW");
    if (!pAddPrinterDriverW)
        WINE_ERR("Could not find AddPrinterDriverW in winspool.drv.\n");

    pAddPrintProcessorA = (void *)GetProcAddress(winspool, "AddPrintProcessorA");
    if (!pAddPrintProcessorA)
        WINE_ERR("Could not find AddPrintProcessorA in winspool.drv.\n");

    pAddPrintProcessorW = (void *)GetProcAddress(winspool, "AddPrintProcessorW");
    if (!pAddPrintProcessorW)
        WINE_ERR("Could not find AddPrintProcessorW in winspool.drv.\n");

    pAddPrintProvidorA = (void *)GetProcAddress(winspool, "AddPrintProvidorA");
    if (!pAddPrintProvidorA)
        WINE_ERR("Could not find AddPrintProvidorA in winspool.drv.\n");

    pAddPrintProvidorW = (void *)GetProcAddress(winspool, "AddPrintProvidorW");
    if (!pAddPrintProvidorW)
        WINE_ERR("Could not find AddPrintProvidorW in winspool.drv.\n");

    pAdvancedDocumentPropertiesA = (void *)GetProcAddress(winspool, "AdvancedDocumentPropertiesA");
    if (!pAdvancedDocumentPropertiesA)
        WINE_ERR("Could not find AdvancedDocumentPropertiesA in winspool.drv.\n");

    pAdvancedDocumentPropertiesW = (void *)GetProcAddress(winspool, "AdvancedDocumentPropertiesW");
    if (!pAdvancedDocumentPropertiesW)
        WINE_ERR("Could not find AdvancedDocumentPropertiesW in winspool.drv.\n");

    pPrinterProperties = (void *)GetProcAddress(winspool, "PrinterProperties");
    if (!pPrinterProperties)
        WINE_ERR("Could not find PrinterProperties in winspool.drv.\n");

    pEnumJobsA = (void *)GetProcAddress(winspool, "EnumJobsA");
    if (!pEnumJobsA)
        WINE_ERR("Could not find EnumJobsA in winspool.drv.\n");

    pEnumJobsW = (void *)GetProcAddress(winspool, "EnumJobsW");
    if (!pEnumJobsW)
        WINE_ERR("Could not find EnumJobsW in winspool.drv.\n");

    pEnumPrinterDriversW = (void *)GetProcAddress(winspool, "EnumPrinterDriversW");
    if (!pEnumPrinterDriversW)
        WINE_ERR("Could not find EnumPrinterDriversW in winspool.drv.\n");

    pEnumPrinterDriversA = (void *)GetProcAddress(winspool, "EnumPrinterDriversA");
    if (!pEnumPrinterDriversA)
        WINE_ERR("Could not find EnumPrinterDriversA in winspool.drv.\n");

    pEnumPortsA = (void *)GetProcAddress(winspool, "EnumPortsA");
    if (!pEnumPortsA)
        WINE_ERR("Could not find EnumPortsA in winspool.drv.\n");

    pEnumPortsW = (void *)GetProcAddress(winspool, "EnumPortsW");
    if (!pEnumPortsW)
        WINE_ERR("Could not find EnumPortsW in winspool.drv.\n");

    pGetDefaultPrinterW = (void *)GetProcAddress(winspool, "GetDefaultPrinterW");
    if (!pGetDefaultPrinterW)
        WINE_ERR("Could not find GetDefaultPrinterW in winspool.drv.\n");

    pGetDefaultPrinterA = (void *)GetProcAddress(winspool, "GetDefaultPrinterA");
    if (!pGetDefaultPrinterA)
        WINE_ERR("Could not find GetDefaultPrinterA in winspool.drv.\n");

    pSetDefaultPrinterW = (void *)GetProcAddress(winspool, "SetDefaultPrinterW");
    if (!pSetDefaultPrinterW)
        WINE_ERR("Could not find SetDefaultPrinterW in winspool.drv.\n");

    pSetDefaultPrinterA = (void *)GetProcAddress(winspool, "SetDefaultPrinterA");
    if (!pSetDefaultPrinterA)
        WINE_ERR("Could not find SetDefaultPrinterA in winspool.drv.\n");

    pSetPrinterDataExA = (void *)GetProcAddress(winspool, "SetPrinterDataExA");
    if (!pSetPrinterDataExA)
        WINE_ERR("Could not find SetPrinterDataExA in winspool.drv.\n");

    pSetPrinterDataExW = (void *)GetProcAddress(winspool, "SetPrinterDataExW");
    if (!pSetPrinterDataExW)
        WINE_ERR("Could not find SetPrinterDataExW in winspool.drv.\n");

    pSetPrinterDataA = (void *)GetProcAddress(winspool, "SetPrinterDataA");
    if (!pSetPrinterDataA)
        WINE_ERR("Could not find SetPrinterDataA in winspool.drv.\n");

    pSetPrinterDataW = (void *)GetProcAddress(winspool, "SetPrinterDataW");
    if (!pSetPrinterDataW)
        WINE_ERR("Could not find SetPrinterDataW in winspool.drv.\n");

    pGetPrinterDataExA = (void *)GetProcAddress(winspool, "GetPrinterDataExA");
    if (!pGetPrinterDataExA)
        WINE_ERR("Could not find GetPrinterDataExA in winspool.drv.\n");

    pGetPrinterDataExW = (void *)GetProcAddress(winspool, "GetPrinterDataExW");
    if (!pGetPrinterDataExW)
        WINE_ERR("Could not find GetPrinterDataExW in winspool.drv.\n");

    pGetPrinterDataA = (void *)GetProcAddress(winspool, "GetPrinterDataA");
    if (!pGetPrinterDataA)
        WINE_ERR("Could not find GetPrinterDataA in winspool.drv.\n");

    pGetPrinterDataW = (void *)GetProcAddress(winspool, "GetPrinterDataW");
    if (!pGetPrinterDataW)
        WINE_ERR("Could not find GetPrinterDataW in winspool.drv.\n");

    pEnumPrinterDataExW = (void *)GetProcAddress(winspool, "EnumPrinterDataExW");
    if (!pEnumPrinterDataExW)
        WINE_ERR("Could not find EnumPrinterDataExW in winspool.drv.\n");

    pEnumPrinterDataExA = (void *)GetProcAddress(winspool, "EnumPrinterDataExA");
    if (!pEnumPrinterDataExA)
        WINE_ERR("Could not find EnumPrinterDataExA in winspool.drv.\n");

    pAbortPrinter = (void *)GetProcAddress(winspool, "AbortPrinter");
    if (!pAbortPrinter)
        WINE_ERR("Could not find AbortPrinter in winspool.drv.\n");

    pAddPortA = (void *)GetProcAddress(winspool, "AddPortA");
    if (!pAddPortA)
        WINE_ERR("Could not find AddPortA in winspool.drv.\n");

    pAddPortW = (void *)GetProcAddress(winspool, "AddPortW");
    if (!pAddPortW)
        WINE_ERR("Could not find AddPortW in winspool.drv.\n");

    pAddPortExA = (void *)GetProcAddress(winspool, "AddPortExA");
    if (!pAddPortExA)
        WINE_ERR("Could not find AddPortExA in winspool.drv.\n");

    pAddPortExW = (void *)GetProcAddress(winspool, "AddPortExW");
    if (!pAddPortExW)
        WINE_ERR("Could not find AddPortExW in winspool.drv.\n");

    pAddPrinterConnectionA = (void *)GetProcAddress(winspool, "AddPrinterConnectionA");
    if (!pAddPrinterConnectionA)
        WINE_ERR("Could not find AddPrinterConnectionA in winspool.drv.\n");

    pAddPrinterConnectionW = (void *)GetProcAddress(winspool, "AddPrinterConnectionW");
    if (!pAddPrinterConnectionW)
        WINE_ERR("Could not find AddPrinterConnectionW in winspool.drv.\n");

    pAddPrinterDriverExW = (void *)GetProcAddress(winspool, "AddPrinterDriverExW");
    if (!pAddPrinterDriverExW)
        WINE_ERR("Could not find AddPrinterDriverExW in winspool.drv.\n");

    pAddPrinterDriverExA = (void *)GetProcAddress(winspool, "AddPrinterDriverExA");
    if (!pAddPrinterDriverExA)
        WINE_ERR("Could not find AddPrinterDriverExA in winspool.drv.\n");

    pConfigurePortA = (void *)GetProcAddress(winspool, "ConfigurePortA");
    if (!pConfigurePortA)
        WINE_ERR("Could not find ConfigurePortA in winspool.drv.\n");

    pConfigurePortW = (void *)GetProcAddress(winspool, "ConfigurePortW");
    if (!pConfigurePortW)
        WINE_ERR("Could not find ConfigurePortW in winspool.drv.\n");

    pConnectToPrinterDlg = (void *)GetProcAddress(winspool, "ConnectToPrinterDlg");
    if (!pConnectToPrinterDlg)
        WINE_ERR("Could not find ConnectToPrinterDlg in winspool.drv.\n");

    pDeletePrinterConnectionA = (void *)GetProcAddress(winspool, "DeletePrinterConnectionA");
    if (!pDeletePrinterConnectionA)
        WINE_ERR("Could not find DeletePrinterConnectionA in winspool.drv.\n");

    pDeletePrinterConnectionW = (void *)GetProcAddress(winspool, "DeletePrinterConnectionW");
    if (!pDeletePrinterConnectionW)
        WINE_ERR("Could not find DeletePrinterConnectionW in winspool.drv.\n");

    pDeletePrinterDriverExW = (void *)GetProcAddress(winspool, "DeletePrinterDriverExW");
    if (!pDeletePrinterDriverExW)
        WINE_ERR("Could not find DeletePrinterDriverExW in winspool.drv.\n");

    pDeletePrinterDriverExA = (void *)GetProcAddress(winspool, "DeletePrinterDriverExA");
    if (!pDeletePrinterDriverExA)
        WINE_ERR("Could not find DeletePrinterDriverExA in winspool.drv.\n");

    pDeletePrinterDataExW = (void *)GetProcAddress(winspool, "DeletePrinterDataExW");
    if (!pDeletePrinterDataExW)
        WINE_ERR("Could not find DeletePrinterDataExW in winspool.drv.\n");

    pDeletePrinterDataExA = (void *)GetProcAddress(winspool, "DeletePrinterDataExA");
    if (!pDeletePrinterDataExA)
        WINE_ERR("Could not find DeletePrinterDataExA in winspool.drv.\n");

    pDeletePrintProcessorA = (void *)GetProcAddress(winspool, "DeletePrintProcessorA");
    if (!pDeletePrintProcessorA)
        WINE_ERR("Could not find DeletePrintProcessorA in winspool.drv.\n");

    pDeletePrintProcessorW = (void *)GetProcAddress(winspool, "DeletePrintProcessorW");
    if (!pDeletePrintProcessorW)
        WINE_ERR("Could not find DeletePrintProcessorW in winspool.drv.\n");

    pDeletePrintProvidorA = (void *)GetProcAddress(winspool, "DeletePrintProvidorA");
    if (!pDeletePrintProvidorA)
        WINE_ERR("Could not find DeletePrintProvidorA in winspool.drv.\n");

    pDeletePrintProvidorW = (void *)GetProcAddress(winspool, "DeletePrintProvidorW");
    if (!pDeletePrintProvidorW)
        WINE_ERR("Could not find DeletePrintProvidorW in winspool.drv.\n");

    pEnumFormsA = (void *)GetProcAddress(winspool, "EnumFormsA");
    if (!pEnumFormsA)
        WINE_ERR("Could not find EnumFormsA in winspool.drv.\n");

    pEnumFormsW = (void *)GetProcAddress(winspool, "EnumFormsW");
    if (!pEnumFormsW)
        WINE_ERR("Could not find EnumFormsW in winspool.drv.\n");

    pEnumMonitorsA = (void *)GetProcAddress(winspool, "EnumMonitorsA");
    if (!pEnumMonitorsA)
        WINE_ERR("Could not find EnumMonitorsA in winspool.drv.\n");

    pEnumMonitorsW = (void *)GetProcAddress(winspool, "EnumMonitorsW");
    if (!pEnumMonitorsW)
        WINE_ERR("Could not find EnumMonitorsW in winspool.drv.\n");

    pSpoolerInit = (void *)GetProcAddress(winspool, "SpoolerInit");
    if (!pSpoolerInit)
        WINE_ERR("Could not find SpoolerInit in winspool.drv.\n");

    pXcvDataW = (void *)GetProcAddress(winspool, "XcvDataW");
    if (!pXcvDataW)
        WINE_ERR("Could not find XcvDataW in winspool.drv.\n");

    pEnumPrinterDataA = (void *)GetProcAddress(winspool, "EnumPrinterDataA");
    if (!pEnumPrinterDataA)
        WINE_ERR("Could not find EnumPrinterDataA in winspool.drv.\n");

    pEnumPrinterDataW = (void *)GetProcAddress(winspool, "EnumPrinterDataW");
    if (!pEnumPrinterDataW)
        WINE_ERR("Could not find EnumPrinterDataW in winspool.drv.\n");

    pEnumPrinterKeyA = (void *)GetProcAddress(winspool, "EnumPrinterKeyA");
    if (!pEnumPrinterKeyA)
        WINE_ERR("Could not find EnumPrinterKeyA in winspool.drv.\n");

    pEnumPrinterKeyW = (void *)GetProcAddress(winspool, "EnumPrinterKeyW");
    if (!pEnumPrinterKeyW)
        WINE_ERR("Could not find EnumPrinterKeyW in winspool.drv.\n");

    pEnumPrintProcessorDatatypesA = (void *)GetProcAddress(winspool, "EnumPrintProcessorDatatypesA");
    if (!pEnumPrintProcessorDatatypesA)
        WINE_ERR("Could not find EnumPrintProcessorDatatypesA in winspool.drv.\n");

    pEnumPrintProcessorDatatypesW = (void *)GetProcAddress(winspool, "EnumPrintProcessorDatatypesW");
    if (!pEnumPrintProcessorDatatypesW)
        WINE_ERR("Could not find EnumPrintProcessorDatatypesW in winspool.drv.\n");

    pEnumPrintProcessorsA = (void *)GetProcAddress(winspool, "EnumPrintProcessorsA");
    if (!pEnumPrintProcessorsA)
        WINE_ERR("Could not find EnumPrintProcessorsA in winspool.drv.\n");

    pEnumPrintProcessorsW = (void *)GetProcAddress(winspool, "EnumPrintProcessorsW");
    if (!pEnumPrintProcessorsW)
        WINE_ERR("Could not find EnumPrintProcessorsW in winspool.drv.\n");

    pFindClosePrinterChangeNotification = (void *)GetProcAddress(winspool, "FindClosePrinterChangeNotification");
    if (!pFindClosePrinterChangeNotification)
        WINE_ERR("Could not find FindClosePrinterChangeNotification in winspool.drv.\n");

    pFindFirstPrinterChangeNotification = (void *)GetProcAddress(winspool, "FindFirstPrinterChangeNotification");
    if (!pFindFirstPrinterChangeNotification)
        WINE_ERR("Could not find FindFirstPrinterChangeNotification in winspool.drv.\n");

    pFindNextPrinterChangeNotification = (void *)GetProcAddress(winspool, "FindNextPrinterChangeNotification");
    if (!pFindNextPrinterChangeNotification)
        WINE_ERR("Could not find FindNextPrinterChangeNotification in winspool.drv.\n");

    pFreePrinterNotifyInfo = (void *)GetProcAddress(winspool, "FreePrinterNotifyInfo");
    if (!pFreePrinterNotifyInfo)
        WINE_ERR("Could not find FreePrinterNotifyInfo in winspool.drv.\n");

    pGetJobA = (void *)GetProcAddress(winspool, "GetJobA");
    if (!pGetJobA)
        WINE_ERR("Could not find GetJobA in winspool.drv.\n");

    pGetJobW = (void *)GetProcAddress(winspool, "GetJobW");
    if (!pGetJobW)
        WINE_ERR("Could not find GetJobW in winspool.drv.\n");

    pScheduleJob = (void *)GetProcAddress(winspool, "ScheduleJob");
    if (!pScheduleJob)
        WINE_ERR("Could not find ScheduleJob in winspool.drv.\n");

    pStartDocDlgA = (void *)GetProcAddress(winspool, "StartDocDlgA");
    if (!pStartDocDlgA)
        WINE_ERR("Could not find StartDocDlgA in winspool.drv.\n");

    pStartDocDlgW = (void *)GetProcAddress(winspool, "StartDocDlgW");
    if (!pStartDocDlgW)
        WINE_ERR("Could not find StartDocDlgW in winspool.drv.\n");

    pUploadPrinterDriverPackageA = (void *)GetProcAddress(winspool, "UploadPrinterDriverPackageA");
    if (!pUploadPrinterDriverPackageA)
        WINE_ERR("Could not find UploadPrinterDriverPackageA in winspool.drv.\n");

    pUploadPrinterDriverPackageW = (void *)GetProcAddress(winspool, "UploadPrinterDriverPackageW");
    if (!pUploadPrinterDriverPackageW)
        WINE_ERR("Could not find UploadPrinterDriverPackageW in winspool.drv.\n");

    pExtDeviceMode = (void *)GetProcAddress(winspool, "ExtDeviceMode");
    if (!pExtDeviceMode)
        WINE_ERR("Could not find ExtDeviceMode in winspool.drv.\n");

    return dll_functions;
}

#endif
