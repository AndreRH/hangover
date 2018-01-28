#ifndef HAVE_QEMU_DSCONF_H
#define HAVE_QEMU_DSCONF_H

struct qemu_DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_X_DATA
{
    qemu_ptr Callback;
    qemu_ptr Context;
};

static inline void DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_X_DATA_g2h(
        DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_1_DATA *host,
        const struct qemu_DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_X_DATA *guest)
{
    host->Callback = (void *)(ULONG_PTR)guest->Callback;
    host->Context = (void *)(ULONG_PTR)guest->Context;
}

struct qemu_DSPROPERTY_DIRECTSOUNDDEVICE_WAVEDEVICEMAPPING_DATA
{
        qemu_ptr                        DeviceName;
        DIRECTSOUNDDEVICE_DATAFLOW      DataFlow;
        GUID                            DeviceId;
};

struct qemu_DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA
{
        DIRECTSOUNDDEVICE_TYPE          Type;
        DIRECTSOUNDDEVICE_DATAFLOW      DataFlow;
        GUID                            DeviceId;
        qemu_ptr                        Description;
        qemu_ptr                        Module;
        qemu_ptr                        Interface;
        ULONG                           WaveDeviceId;
};

static inline void DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA_h2g(
        struct qemu_DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA *guest,
        const DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W_DATA *host)
{
    guest->Type = host->Type;
    guest->DataFlow = host->DataFlow;
    guest->DeviceId = host->DeviceId;
    guest->Description = (ULONG_PTR)host->Description;
    guest->Module = (ULONG_PTR)host->Module;
    guest->Interface = (ULONG_PTR)host->Interface;
    guest->WaveDeviceId = host->WaveDeviceId;
}

#endif
