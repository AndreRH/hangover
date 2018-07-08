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

#ifndef QEMU_MMDEVAPI_H
#define QEMU_MMDEVAPI_H

enum mmdevapi_calls
{
    CALL_INIT_DLL = 0,
    CALL_MMDEVCOL_ADDREF,
    CALL_MMDEVCOL_GETCOUNT,
    CALL_MMDEVCOL_ITEM,
    CALL_MMDEVCOL_QUERYINTERFACE,
    CALL_MMDEVCOL_RELEASE,
    CALL_MMDEVENUM_ADDREF,
    CALL_MMDEVENUM_CREATE,
    CALL_MMDEVENUM_ENUMAUDIOENDPOINTS,
    CALL_MMDEVENUM_GETDEFAULTAUDIOENDPOINT,
    CALL_MMDEVENUM_GETDEVICE,
    CALL_MMDEVENUM_QUERYINTERFACE,
    CALL_MMDEVENUM_REGISTERENDPOINTNOTIFICATIONCALLBACK,
    CALL_MMDEVENUM_RELEASE,
    CALL_MMDEVENUM_UNREGISTERENDPOINTNOTIFICATIONCALLBACK,
    CALL_MMDEVICE_ACTIVATE,
    CALL_MMDEVICE_ADDREF,
    CALL_MMDEVICE_GETID,
    CALL_MMDEVICE_GETSTATE,
    CALL_MMDEVICE_OPENPROPERTYSTORE,
    CALL_MMDEVICE_QUERYINTERFACE,
    CALL_MMDEVICE_RELEASE,
    CALL_MMDEVPROPSTORE_ADDREF,
    CALL_MMDEVPROPSTORE_COMMIT,
    CALL_MMDEVPROPSTORE_GETAT,
    CALL_MMDEVPROPSTORE_GETCOUNT,
    CALL_MMDEVPROPSTORE_GETVALUE,
    CALL_MMDEVPROPSTORE_QUERYINTERFACE,
    CALL_MMDEVPROPSTORE_RELEASE,
    CALL_MMDEVPROPSTORE_SETVALUE,
    CALL_MMENDPOINT_ADDREF,
    CALL_MMENDPOINT_GETDATAFLOW,
    CALL_MMENDPOINT_QUERYINTERFACE,
    CALL_MMENDPOINT_RELEASE,
};

struct qemu_mmdevice
{
    /* Guest fields */
    IMMDevice IMMDevice_iface;
    IMMEndpoint IMMEndpoint_iface;

    /* Host fields */
    IMMDevice *host_device;
    IMMEndpoint *host_endpoint;
    struct list entry;
};

#ifdef QEMU_DLL_GUEST

HRESULT MMDevEnum_Create(const IID *iid, void **ppv);

#else

HMODULE mmdevapi_mod;
extern const struct qemu_ops *qemu_ops;

void qemu_MMDevCol_AddRef(struct qemu_syscall *call);
void qemu_MMDevCol_GetCount(struct qemu_syscall *call);
void qemu_MMDevCol_Item(struct qemu_syscall *call);
void qemu_MMDevCol_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevCol_Release(struct qemu_syscall *call);
void qemu_MMDevEnum_AddRef(struct qemu_syscall *call);
void qemu_MMDevEnum_Create(struct qemu_syscall *call);
void qemu_MMDevEnum_EnumAudioEndpoints(struct qemu_syscall *call);
void qemu_MMDevEnum_GetDefaultAudioEndpoint(struct qemu_syscall *call);
void qemu_MMDevEnum_GetDevice(struct qemu_syscall *call);
void qemu_MMDevEnum_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevEnum_RegisterEndpointNotificationCallback(struct qemu_syscall *call);
void qemu_MMDevEnum_Release(struct qemu_syscall *call);
void qemu_MMDevEnum_UnregisterEndpointNotificationCallback(struct qemu_syscall *call);
void qemu_MMDevPropStore_AddRef(struct qemu_syscall *call);
void qemu_MMDevPropStore_Commit(struct qemu_syscall *call);
void qemu_MMDevPropStore_GetAt(struct qemu_syscall *call);
void qemu_MMDevPropStore_GetCount(struct qemu_syscall *call);
void qemu_MMDevPropStore_GetValue(struct qemu_syscall *call);
void qemu_MMDevPropStore_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevPropStore_Release(struct qemu_syscall *call);
void qemu_MMDevPropStore_SetValue(struct qemu_syscall *call);
void qemu_MMDevice_Activate(struct qemu_syscall *call);
void qemu_MMDevice_AddRef(struct qemu_syscall *call);
void qemu_MMDevice_GetId(struct qemu_syscall *call);
void qemu_MMDevice_GetState(struct qemu_syscall *call);
void qemu_MMDevice_OpenPropertyStore(struct qemu_syscall *call);
void qemu_MMDevice_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevice_Release(struct qemu_syscall *call);
void qemu_MMEndpoint_AddRef(struct qemu_syscall *call);
void qemu_MMEndpoint_GetDataFlow(struct qemu_syscall *call);
void qemu_MMEndpoint_QueryInterface(struct qemu_syscall *call);
void qemu_MMEndpoint_Release(struct qemu_syscall *call);

#endif

#endif
