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

#include <initguid.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <dsound.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#include <list.h>
#else
#include <wine/debug.h>
#include <wine/list.h>
#endif

#include "qemu_mmdevapi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_mmdevapi);

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t reason;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;
    HMODULE dxgi;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_ATTACH;
        qemu_syscall(&call.super);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_DETACH;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

HRESULT WINAPI DllCanUnloadNow(void)
{
    WINE_FIXME("Stub\n");
    return S_FALSE;
}


typedef HRESULT (*FnCreateInstance)(REFIID riid, LPVOID *ppobj);

typedef struct {
    IClassFactory IClassFactory_iface;
    REFCLSID rclsid;
    FnCreateInstance pfnCreateInstance;
} IClassFactoryImpl;

static inline IClassFactoryImpl *impl_from_IClassFactory(IClassFactory *iface)
{
    return CONTAINING_RECORD(iface, IClassFactoryImpl, IClassFactory_iface);
}

static HRESULT WINAPI MMCF_QueryInterface(IClassFactory *iface, REFIID riid, void **ppobj)
{
    IClassFactoryImpl *This = impl_from_IClassFactory(iface);
    WINE_TRACE("(%p, %s, %p)\n", This, wine_dbgstr_guid(riid), ppobj);

    if (ppobj == NULL)
        return E_POINTER;

    if (IsEqualIID(riid, &IID_IUnknown) ||
            IsEqualIID(riid, &IID_IClassFactory))
    {
        *ppobj = iface;
        IClassFactory_AddRef(iface);
        return S_OK;
    }
    *ppobj = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI MMCF_AddRef(IClassFactory *iface)
{
    return 2;
}

static ULONG WINAPI MMCF_Release(IClassFactory *iface)
{
    /* static class, won't be freed */
    return 1;
}

static HRESULT WINAPI MMCF_CreateInstance(IClassFactory *iface, IUnknown *pOuter, const IID *riid, void **ppobj)
{
    IClassFactoryImpl *This = impl_from_IClassFactory(iface);
    WINE_TRACE("(%p, %p, %s, %p)\n", This, pOuter, wine_dbgstr_guid(riid), ppobj);

    if (pOuter)
        return CLASS_E_NOAGGREGATION;

    if (ppobj == NULL)
    {
        WINE_WARN("invalid parameter\n");
        return E_POINTER;
    }
    *ppobj = NULL;
    return This->pfnCreateInstance(riid, ppobj);
}

static HRESULT WINAPI MMCF_LockServer(IClassFactory *iface, BOOL dolock)
{
    IClassFactoryImpl *This = impl_from_IClassFactory(iface);
    WINE_FIXME("(%p, %d) stub!\n", This, dolock);
    return S_OK;
}

static const IClassFactoryVtbl MMCF_Vtbl =
{
    MMCF_QueryInterface,
    MMCF_AddRef,
    MMCF_Release,
    MMCF_CreateInstance,
    MMCF_LockServer
};

static IClassFactoryImpl MMDEVAPI_CF[] =
{
    { { &MMCF_Vtbl }, &CLSID_MMDeviceEnumerator, (FnCreateInstance)MMDevEnum_Create }
};

HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    unsigned int i = 0;
    WINE_TRACE("(%s, %s, %p)\n", wine_dbgstr_guid(rclsid), wine_dbgstr_guid(riid), ppv);

    if (ppv == NULL)
    {
        WINE_WARN("invalid parameter\n");
        return E_INVALIDARG;
    }

    *ppv = NULL;

    if (!IsEqualIID(riid, &IID_IClassFactory)
            && !IsEqualIID(riid, &IID_IUnknown))
    {
        WINE_WARN("no interface for %s\n", wine_dbgstr_guid(riid));
        return E_NOINTERFACE;
    }

    for (i = 0; i < sizeof(MMDEVAPI_CF)/sizeof(MMDEVAPI_CF[0]); ++i)
    {
        if (IsEqualGUID(rclsid, MMDEVAPI_CF[i].rclsid))
        {
            IClassFactory_AddRef(&MMDEVAPI_CF[i].IClassFactory_iface);
            *ppv = &MMDEVAPI_CF[i];
            return S_OK;
        }
    }

    WINE_WARN("(%s, %s, %p): no class found.\n", wine_dbgstr_guid(rclsid),
            wine_dbgstr_guid(riid), ppv);
    return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT WINAPI DllRegisterServer(void)
{
    WINE_ERR("Should not be called on the wrapper.\n");
    return E_FAIL;
}

HRESULT WINAPI DllUnregisterServer(void)
{
    WINE_ERR("Should not be called on the wrapper.\n");
    return E_FAIL;
}

#else

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
    static HMODULE msvcrt;

    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            if (msvcrt)
                WINE_ERR("msvcrt already loaded.\n");

            msvcrt = LoadLibraryA("msvcrt");
            if (!msvcrt)
                WINE_ERR("Cannot get msvcrt module handle.\n");

            p_swscanf = (void *)GetProcAddress(msvcrt, "swscanf");
            if (!p_swscanf)
                WINE_ERR("Cannot find swscanf in msvcrt.dll.\n");

            break;

        case DLL_PROCESS_DETACH:
            if (!msvcrt)
                WINE_ERR("msvcrt not loaded.\n");

            FreeLibrary(msvcrt);
            msvcrt = NULL;
            break;
    }
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AEV_AddRef,
    qemu_AEV_GetChannelCount,
    qemu_AEV_GetChannelVolumeLevel,
    qemu_AEV_GetChannelVolumeLevelScalar,
    qemu_AEV_GetMasterVolumeLevel,
    qemu_AEV_GetMasterVolumeLevelScalar,
    qemu_AEV_GetMute,
    qemu_AEV_GetVolumeRange,
    qemu_AEV_GetVolumeRangeChannel,
    qemu_AEV_GetVolumeStepInfo,
    qemu_AEV_QueryHardwareSupport,
    qemu_AEV_QueryInterface,
    qemu_AEV_RegisterControlChangeNotify,
    qemu_AEV_Release,
    qemu_AEV_SetChannelVolumeLevel,
    qemu_AEV_SetChannelVolumeLevelScalar,
    qemu_AEV_SetMasterVolumeLevel,
    qemu_AEV_SetMasterVolumeLevelScalar,
    qemu_AEV_SetMute,
    qemu_AEV_UnregisterControlChangeNotify,
    qemu_AEV_VolumeStepDown,
    qemu_AEV_VolumeStepUp,
    qemu_AudioCaptureClient_GetBuffer,
    qemu_AudioCaptureClient_GetNextPacketSize,
    qemu_AudioCaptureClient_QueryInterface,
    qemu_AudioCaptureClient_ReleaseBuffer,
    qemu_AudioClient_AddRef,
    qemu_AudioClient_GetBufferSize,
    qemu_AudioClient_GetCurrentPadding,
    qemu_AudioClient_GetDevicePeriod,
    qemu_AudioClient_GetMixFormat,
    qemu_AudioClient_GetService,
    qemu_AudioClient_GetStreamLatency,
    qemu_AudioClient_Initialize,
    qemu_AudioClient_IsFormatSupported,
    qemu_AudioClient_QueryInterface,
    qemu_AudioClient_Release,
    qemu_AudioClient_Reset,
    qemu_AudioClient_SetEventHandle,
    qemu_AudioClient_Start,
    qemu_AudioClient_Stop,
    qemu_AudioClock2_GetDevicePosition,
    qemu_AudioClock2_QueryInterface,
    qemu_AudioClock_GetCharacteristics,
    qemu_AudioClock_GetFrequency,
    qemu_AudioClock_GetPosition,
    qemu_AudioClock_QueryInterface,
    qemu_AudioRenderClient_GetBuffer,
    qemu_AudioRenderClient_QueryInterface,
    qemu_AudioRenderClient_ReleaseBuffer,
    qemu_AudioSessionControl_AddRef,
    qemu_AudioSessionControl_GetDisplayName,
    qemu_AudioSessionControl_GetGroupingParam,
    qemu_AudioSessionControl_GetIconPath,
    qemu_AudioSessionControl_GetProcessId,
    qemu_AudioSessionControl_GetSessionIdentifier,
    qemu_AudioSessionControl_GetSessionInstanceIdentifier,
    qemu_AudioSessionControl_GetState,
    qemu_AudioSessionControl_IsSystemSoundsSession,
    qemu_AudioSessionControl_QueryInterface,
    qemu_AudioSessionControl_RegisterAudioSessionNotification,
    qemu_AudioSessionControl_Release,
    qemu_AudioSessionControl_SetDisplayName,
    qemu_AudioSessionControl_SetDuckingPreference,
    qemu_AudioSessionControl_SetGroupingParam,
    qemu_AudioSessionControl_SetIconPath,
    qemu_AudioSessionControl_UnregisterAudioSessionNotification,
    qemu_AudioSessionManager_AddRef,
    qemu_AudioSessionManager_GetAudioSessionControl,
    qemu_AudioSessionManager_GetSessionEnumerator,
    qemu_AudioSessionManager_GetSimpleAudioVolume,
    qemu_AudioSessionManager_QueryInterface,
    qemu_AudioSessionManager_RegisterDuckNotification,
    qemu_AudioSessionManager_RegisterSessionNotification,
    qemu_AudioSessionManager_Release,
    qemu_AudioSessionManager_UnregisterDuckNotification,
    qemu_AudioSessionManager_UnregisterSessionNotification,
    qemu_AudioStreamVolume_GetAllVolumes,
    qemu_AudioStreamVolume_GetChannelCount,
    qemu_AudioStreamVolume_GetChannelVolume,
    qemu_AudioStreamVolume_QueryInterface,
    qemu_AudioStreamVolume_SetAllVolumes,
    qemu_AudioStreamVolume_SetChannelVolume,
    qemu_ChannelAudioVolume_GetAllVolumes,
    qemu_ChannelAudioVolume_GetChannelCount,
    qemu_ChannelAudioVolume_GetChannelVolume,
    qemu_ChannelAudioVolume_QueryInterface,
    qemu_ChannelAudioVolume_SetAllVolumes,
    qemu_ChannelAudioVolume_SetChannelVolume,
    qemu_init_dll,
    qemu_MMDevCol_AddRef,
    qemu_MMDevCol_GetCount,
    qemu_MMDevCol_Item,
    qemu_MMDevCol_QueryInterface,
    qemu_MMDevCol_Release,
    qemu_MMDevEnum_AddRef,
    qemu_MMDevEnum_Create,
    qemu_MMDevEnum_EnumAudioEndpoints,
    qemu_MMDevEnum_GetDefaultAudioEndpoint,
    qemu_MMDevEnum_GetDevice,
    qemu_MMDevEnum_QueryInterface,
    qemu_MMDevEnum_RegisterEndpointNotificationCallback,
    qemu_MMDevEnum_Release,
    qemu_MMDevEnum_UnregisterEndpointNotificationCallback,
    qemu_MMDevice_Activate,
    qemu_MMDevice_AddRef,
    qemu_MMDevice_GetId,
    qemu_MMDevice_GetState,
    qemu_MMDevice_OpenPropertyStore,
    qemu_MMDevice_QueryInterface,
    qemu_MMDevice_Release,
    qemu_MMDevPropStore_AddRef,
    qemu_MMDevPropStore_Commit,
    qemu_MMDevPropStore_GetAt,
    qemu_MMDevPropStore_GetCount,
    qemu_MMDevPropStore_GetValue,
    qemu_MMDevPropStore_QueryInterface,
    qemu_MMDevPropStore_Release,
    qemu_MMDevPropStore_SetValue,
    qemu_MMEndpoint_AddRef,
    qemu_MMEndpoint_GetDataFlow,
    qemu_MMEndpoint_QueryInterface,
    qemu_MMEndpoint_Release,
    qemu_SimpleAudioVolume_GetMasterVolume,
    qemu_SimpleAudioVolume_GetMute,
    qemu_SimpleAudioVolume_QueryInterface,
    qemu_SimpleAudioVolume_SetMasterVolume,
    qemu_SimpleAudioVolume_SetMute,
};

int (*WINAPIV p_swscanf)(const WCHAR *str, const WCHAR *format, ...);
HMODULE mmdevapi_mod;

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side mmdevapi wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    mmdevapi_mod = LoadLibraryA("mmdevapi");
    if (!mmdevapi_mod)
        WINE_ERR("Failed to load mmdevapi.dll.\n");

    return dll_functions;
}

#endif
