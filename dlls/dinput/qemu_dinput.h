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

#ifndef QEMU_DINPUT_H
#define QEMU_DINPUT_H

enum dinput_calls
{
    CALL_DIRECTINPUT_CREATE = 0,
    CALL_IDIRECTINPUT2AIMPL_FINDDEVICE,
    CALL_IDIRECTINPUT2WIMPL_FINDDEVICE,
    CALL_IDIRECTINPUT7AIMPL_CREATEDEVICEEX,
    CALL_IDIRECTINPUT7WIMPL_CREATEDEVICEEX,
    CALL_IDIRECTINPUT8AIMPL_ADDREF,
    CALL_IDIRECTINPUT8AIMPL_CONFIGUREDEVICES,
    CALL_IDIRECTINPUT8AIMPL_CREATEDEVICE,
    CALL_IDIRECTINPUT8AIMPL_ENUMDEVICESBYSEMANTICS,
    CALL_IDIRECTINPUT8AIMPL_FINDDEVICE,
    CALL_IDIRECTINPUT8AIMPL_GETDEVICESTATUS,
    CALL_IDIRECTINPUT8AIMPL_INITIALIZE,
    CALL_IDIRECTINPUT8AIMPL_RELEASE,
    CALL_IDIRECTINPUT8AIMPL_RUNCONTROLPANEL,
    CALL_IDIRECTINPUT8WIMPL_ADDREF,
    CALL_IDIRECTINPUT8WIMPL_CONFIGUREDEVICES,
    CALL_IDIRECTINPUT8WIMPL_CREATEDEVICE,
    CALL_IDIRECTINPUT8WIMPL_ENUMDEVICESBYSEMANTICS,
    CALL_IDIRECTINPUT8WIMPL_FINDDEVICE,
    CALL_IDIRECTINPUT8WIMPL_GETDEVICESTATUS,
    CALL_IDIRECTINPUT8WIMPL_INITIALIZE,
    CALL_IDIRECTINPUT8WIMPL_RELEASE,
    CALL_IDIRECTINPUT8WIMPL_RUNCONTROLPANEL,
    CALL_IDIRECTINPUTAIMPL_ADDREF,
    CALL_IDIRECTINPUTAIMPL_CREATEDEVICE,
    CALL_IDIRECTINPUTAIMPL_ENUMDEVICES,
    CALL_IDIRECTINPUTAIMPL_GETDEVICESTATUS,
    CALL_IDIRECTINPUTAIMPL_INITIALIZE,
    CALL_IDIRECTINPUTAIMPL_QUERYINTERFACE,
    CALL_IDIRECTINPUTAIMPL_RELEASE,
    CALL_IDIRECTINPUTAIMPL_RUNCONTROLPANEL,
    CALL_IDIRECTINPUTDEVICEAIMPL_ACQUIRE,
    CALL_IDIRECTINPUTDEVICEAIMPL_ADDREF,
    CALL_IDIRECTINPUTDEVICEAIMPL_BUILDACTIONMAP,
    CALL_IDIRECTINPUTDEVICEAIMPL_CREATEEFFECT,
    CALL_IDIRECTINPUTDEVICEAIMPL_ENUMCREATEDEFFECTOBJECTS,
    CALL_IDIRECTINPUTDEVICEAIMPL_ENUMEFFECTS,
    CALL_IDIRECTINPUTDEVICEAIMPL_ENUMEFFECTSINFILE,
    CALL_IDIRECTINPUTDEVICEAIMPL_ENUMOBJECTS,
    CALL_IDIRECTINPUTDEVICEAIMPL_ESCAPE,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETCAPABILITIES,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETDEVICEDATA,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETDEVICEINFO,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETDEVICESTATE,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETEFFECTINFO,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETFORCEFEEDBACKSTATE,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETIMAGEINFO,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETOBJECTINFO,
    CALL_IDIRECTINPUTDEVICEAIMPL_GETPROPERTY,
    CALL_IDIRECTINPUTDEVICEAIMPL_INITIALIZE,
    CALL_IDIRECTINPUTDEVICEAIMPL_POLL,
    CALL_IDIRECTINPUTDEVICEAIMPL_RELEASE,
    CALL_IDIRECTINPUTDEVICEAIMPL_RUNCONTROLPANEL,
    CALL_IDIRECTINPUTDEVICEAIMPL_SENDDEVICEDATA,
    CALL_IDIRECTINPUTDEVICEAIMPL_SENDFORCEFEEDBACKCOMMAND,
    CALL_IDIRECTINPUTDEVICEAIMPL_SETACTIONMAP,
    CALL_IDIRECTINPUTDEVICEAIMPL_SETCOOPERATIVELEVEL,
    CALL_IDIRECTINPUTDEVICEAIMPL_SETDATAFORMAT,
    CALL_IDIRECTINPUTDEVICEAIMPL_SETEVENTNOTIFICATION,
    CALL_IDIRECTINPUTDEVICEAIMPL_SETPROPERTY,
    CALL_IDIRECTINPUTDEVICEAIMPL_UNACQUIRE,
    CALL_IDIRECTINPUTDEVICEAIMPL_WRITEEFFECTTOFILE,
    CALL_IDIRECTINPUTDEVICEWIMPL_ACQUIRE,
    CALL_IDIRECTINPUTDEVICEWIMPL_ADDREF,
    CALL_IDIRECTINPUTDEVICEWIMPL_BUILDACTIONMAP,
    CALL_IDIRECTINPUTDEVICEWIMPL_CREATEEFFECT,
    CALL_IDIRECTINPUTDEVICEWIMPL_ENUMCREATEDEFFECTOBJECTS,
    CALL_IDIRECTINPUTDEVICEWIMPL_ENUMEFFECTS,
    CALL_IDIRECTINPUTDEVICEWIMPL_ENUMEFFECTSINFILE,
    CALL_IDIRECTINPUTDEVICEWIMPL_ENUMOBJECTS,
    CALL_IDIRECTINPUTDEVICEWIMPL_ESCAPE,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETCAPABILITIES,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETDEVICEDATA,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETDEVICEINFO,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETDEVICESTATE,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETEFFECTINFO,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETFORCEFEEDBACKSTATE,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETIMAGEINFO,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETOBJECTINFO,
    CALL_IDIRECTINPUTDEVICEWIMPL_GETPROPERTY,
    CALL_IDIRECTINPUTDEVICEWIMPL_INITIALIZE,
    CALL_IDIRECTINPUTDEVICEWIMPL_POLL,
    CALL_IDIRECTINPUTDEVICEWIMPL_QUERYINTERFACE,
    CALL_IDIRECTINPUTDEVICEWIMPL_RELEASE,
    CALL_IDIRECTINPUTDEVICEWIMPL_RUNCONTROLPANEL,
    CALL_IDIRECTINPUTDEVICEWIMPL_SENDDEVICEDATA,
    CALL_IDIRECTINPUTDEVICEWIMPL_SENDFORCEFEEDBACKCOMMAND,
    CALL_IDIRECTINPUTDEVICEWIMPL_SETACTIONMAP,
    CALL_IDIRECTINPUTDEVICEWIMPL_SETCOOPERATIVELEVEL,
    CALL_IDIRECTINPUTDEVICEWIMPL_SETDATAFORMAT,
    CALL_IDIRECTINPUTDEVICEWIMPL_SETEVENTNOTIFICATION,
    CALL_IDIRECTINPUTDEVICEWIMPL_SETPROPERTY,
    CALL_IDIRECTINPUTDEVICEWIMPL_UNACQUIRE,
    CALL_IDIRECTINPUTDEVICEWIMPL_WRITEEFFECTTOFILE,
    CALL_IDIRECTINPUTWIMPL_ADDREF,
    CALL_IDIRECTINPUTWIMPL_CREATEDEVICE,
    CALL_IDIRECTINPUTWIMPL_ENUMDEVICES,
    CALL_IDIRECTINPUTWIMPL_GETDEVICESTATUS,
    CALL_IDIRECTINPUTWIMPL_INITIALIZE,
    CALL_IDIRECTINPUTWIMPL_RELEASE,
    CALL_IDIRECTINPUTWIMPL_RUNCONTROLPANEL,
    CALL_INIT_DLL,
    CALL_JOYCONFIG8IMPL_ACQUIRE,
    CALL_JOYCONFIG8IMPL_ADDNEWHARDWARE,
    CALL_JOYCONFIG8IMPL_DELETECONFIG,
    CALL_JOYCONFIG8IMPL_DELETETYPE,
    CALL_JOYCONFIG8IMPL_ENUMTYPES,
    CALL_JOYCONFIG8IMPL_GETCONFIG,
    CALL_JOYCONFIG8IMPL_GETTYPEINFO,
    CALL_JOYCONFIG8IMPL_GETUSERVALUES,
    CALL_JOYCONFIG8IMPL_OPENAPPSTATUSKEY,
    CALL_JOYCONFIG8IMPL_OPENTYPEKEY,
    CALL_JOYCONFIG8IMPL_SENDNOTIFY,
    CALL_JOYCONFIG8IMPL_SETCONFIG,
    CALL_JOYCONFIG8IMPL_SETCOOPERATIVELEVEL,
    CALL_JOYCONFIG8IMPL_SETTYPEINFO,
    CALL_JOYCONFIG8IMPL_SETUSERVALUES,
    CALL_JOYCONFIG8IMPL_UNACQUIRE,
};

struct qemu_dinput
{
    /* Guest fields */
    IDirectInput7A              IDirectInput7A_iface;
    IDirectInput7W              IDirectInput7W_iface;
    IDirectInput8A              IDirectInput8A_iface;
    IDirectInput8W              IDirectInput8W_iface;
    IDirectInputJoyConfig8      IDirectInputJoyConfig8_iface;

    /* Host fields */
    IDirectInput7A              *host_7a;
    IDirectInput7W              *host_7w;
    IDirectInput8A              *host_8a;
    IDirectInput8W              *host_8w;
    IDirectInputJoyConfig8      *host_joy_config;
};

struct qemu_dinput_device
{
    /* Guest fields */
    IDirectInputDevice8A        IDirectInputDevice8A_iface;
    IDirectInputDevice8W        IDirectInputDevice8W_iface;

    /* Host fields */
    IDirectInputDevice8A        *host_a;
    IDirectInputDevice8W        *host_w;

    struct qemu_dinput          *parent;
};

#ifdef QEMU_DLL_GUEST

void qemu_dinput_device_guest_init(struct qemu_dinput_device *device);

#else

extern const struct qemu_ops *qemu_ops;

void qemu_IDirectInputDeviceAImpl_Acquire(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_AddRef(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_BuildActionMap(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_CreateEffect(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_EnumEffects(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_EnumEffectsInFile(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_Escape(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetCapabilities(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetDeviceInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetDeviceState(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetEffectInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetForceFeedbackState(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetImageInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetObjectInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_GetProperty(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_Initialize(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_Poll(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_RunControlPanel(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_SendDeviceData(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_SetActionMap(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_SetEventNotification(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_SetProperty(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_Unacquire(struct qemu_syscall *call);
void qemu_IDirectInputDeviceAImpl_WriteEffectToFile(struct qemu_syscall *call);
void qemu_IDirectInputDeviceImpl_EnumObjects(struct qemu_syscall *call);
void qemu_IDirectInputDeviceImpl_GetDeviceData(struct qemu_syscall *call);
void qemu_IDirectInputDeviceImpl_QueryInterface(struct qemu_syscall *call);
void qemu_IDirectInputDeviceImpl_Release(struct qemu_syscall *call);
void qemu_IDirectInputDeviceImpl_SetDataFormat(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_Acquire(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_AddRef(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_BuildActionMap(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_CreateEffect(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_EnumEffects(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_EnumEffectsInFile(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_Escape(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetCapabilities(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetDeviceInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetDeviceState(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetEffectInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetForceFeedbackState(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetImageInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetObjectInfo(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_GetProperty(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_Initialize(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_Poll(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_RunControlPanel(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_SendDeviceData(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_SetActionMap(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_SetEventNotification(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_SetProperty(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_Unacquire(struct qemu_syscall *call);
void qemu_IDirectInputDeviceWImpl_WriteEffectToFile(struct qemu_syscall *call);

ULONG qemu_IDirectInputImpl_Release_internal(struct qemu_dinput *dinput);

#endif

#endif
