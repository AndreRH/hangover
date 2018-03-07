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

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
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
    qemu_EnumPrintersA,
    qemu_EnumPrintersW,
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
    qemu_GetJobA,
    qemu_GetJobW,
    qemu_GetPrinter,
    qemu_GetPrinterDataA,
    qemu_GetPrinterDataExA,
    qemu_GetPrinterDataExW,
    qemu_GetPrinterDataW,
    qemu_GetPrinterDriverA,
    qemu_GetPrinterDriverDirectoryA,
    qemu_GetPrinterDriverDirectoryW,
    qemu_GetPrinterDriverW,
    qemu_GetPrinter,
    qemu_GetPrintProcessorDirectoryA,
    qemu_GetPrintProcessorDirectoryW,
    qemu_IsValidDevmodeA,
    qemu_IsValidDevmodeW,
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
    WINE_TRACE("Loading host-side winspool.drv wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
