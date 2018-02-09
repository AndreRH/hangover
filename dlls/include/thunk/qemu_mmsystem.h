#ifndef HAVE_QEMU_THUNK_MMSYSTEM_H
#define HAVE_QEMU_THUNK_MMSYSTEM_H

struct qemu_WAVEHDR
{
    qemu_ptr    lpData;
    DWORD       dwBufferLength;
    DWORD       dwBytesRecorded;
    qemu_ptr    dwUser;
    DWORD       dwFlags;
    DWORD       dwLoops;
    qemu_ptr    lpNext;
    qemu_ptr    reserved;
};

static inline void WAVEHDR_g2h(WAVEHDR *host, const struct qemu_WAVEHDR *guest)
{
    host->lpData = (char *)(ULONG_PTR)guest->lpData;
    host->dwBufferLength = guest->dwBufferLength;
    host->dwBytesRecorded = guest->dwBytesRecorded;
    host->dwUser = guest->dwUser;
    host->dwFlags = guest->dwFlags;
    host->dwLoops = guest->dwLoops;
    host->lpNext = (WAVEHDR *)(ULONG_PTR)guest->lpNext; /* Note: MSDN says "reserved" */
    host->reserved = guest->reserved;
}

static inline void WAVEHDR_h2g(struct qemu_WAVEHDR *guest, const WAVEHDR *host)
{
    guest->lpData = (ULONG_PTR)host->lpData;
    guest->dwBufferLength = host->dwBufferLength;
    guest->dwBytesRecorded = host->dwBytesRecorded;
    guest->dwUser = host->dwUser;
    guest->dwFlags = host->dwFlags;
    guest->dwLoops = host->dwLoops;
    guest->lpNext = (ULONG_PTR)host->lpNext; /* Note: MSDN says "reserved" */
    guest->reserved = host->reserved;
}

struct qemu_MIXERLINEA
{
    DWORD       cbStruct;
    DWORD       dwDestination;
    DWORD       dwSource;
    DWORD       dwLineID;
    DWORD       fdwLine;
    qemu_ptr    dwUser;
    DWORD       dwComponentType;
    DWORD       cChannels;
    DWORD       cConnections;
    DWORD       cControls;
    CHAR        szShortName[MIXER_SHORT_NAME_CHARS];
    CHAR        szName[MIXER_LONG_NAME_CHARS];
    struct
    {
        DWORD       dwType;
        DWORD       dwDeviceID;
        WORD        wMid;
        WORD        wPid;
        MMVERSION   vDriverVersion;
        CHAR        szPname[MAXPNAMELEN];
    } Target;
};

static inline void MIXERLINEA_g2h(MIXERLINEA *host, const struct qemu_MIXERLINEA *guest)
{
    host->cbStruct = sizeof(*host);
    host->dwDestination = guest->dwDestination;
    host->dwSource = guest->dwSource;
    host->dwLineID = guest->dwLineID;
    host->fdwLine = guest->fdwLine;
    host->dwUser = guest->dwUser;
    host->dwComponentType = guest->dwComponentType;
    host->cChannels = guest->cChannels;
    host->cConnections = guest->cConnections;
    host->cControls = guest->cControls;
    memcpy(host->szShortName, guest->szShortName, sizeof(host->szShortName));
    memcpy(host->szName, guest->szName, sizeof(host->szName));

    host->Target.dwType = guest->Target.dwType;
    host->Target.dwDeviceID = guest->Target.dwDeviceID;
    host->Target.wMid = guest->Target.wMid;
    host->Target.wPid = guest->Target.wPid;
    host->Target.vDriverVersion = guest->Target.vDriverVersion;
    memcpy(host->Target.szPname, guest->Target.szPname, sizeof(host->Target.szPname));
}

static inline void MIXERLINEA_h2g(struct qemu_MIXERLINEA *guest, const MIXERLINEA *host)
{
    guest->dwDestination = host->dwDestination;
    guest->dwSource = host->dwSource;
    guest->dwLineID = host->dwLineID;
    guest->fdwLine = host->fdwLine;
    guest->dwUser = host->dwUser;
    guest->dwComponentType = host->dwComponentType;
    guest->cChannels = host->cChannels;
    guest->cConnections = host->cConnections;
    guest->cControls = host->cControls;
    memcpy(guest->szShortName, host->szShortName, sizeof(guest->szShortName));
    memcpy(guest->szName, host->szName, sizeof(guest->szName));

    guest->Target.dwType = host->Target.dwType;
    guest->Target.dwDeviceID = host->Target.dwDeviceID;
    guest->Target.wMid = host->Target.wMid;
    guest->Target.wPid = host->Target.wPid;
    guest->Target.vDriverVersion = host->Target.vDriverVersion;
    memcpy(guest->Target.szPname, host->Target.szPname, sizeof(guest->Target.szPname));
}

struct qemu_MIXERLINEW
{
    DWORD       cbStruct;
    DWORD       dwDestination;
    DWORD       dwSource;
    DWORD       dwLineID;
    DWORD       fdwLine;
    qemu_ptr    dwUser;
    DWORD       dwComponentType;
    DWORD       cChannels;
    DWORD       cConnections;
    DWORD       cControls;
    WCHAR       szShortName[MIXER_SHORT_NAME_CHARS];
    WCHAR       szName[MIXER_LONG_NAME_CHARS];
    struct
    {
        DWORD       dwType;
        DWORD       dwDeviceID;
        WORD        wMid;
        WORD        wPid;
        MMVERSION   vDriverVersion;
        WCHAR       szPname[MAXPNAMELEN];
    } Target;
};

static inline void MIXERLINEW_g2h(MIXERLINEW *host, const struct qemu_MIXERLINEW *guest)
{
    host->cbStruct = sizeof(*host);
    host->dwDestination = guest->dwDestination;
    host->dwSource = guest->dwSource;
    host->dwLineID = guest->dwLineID;
    host->fdwLine = guest->fdwLine;
    host->dwUser = guest->dwUser;
    host->dwComponentType = guest->dwComponentType;
    host->cChannels = guest->cChannels;
    host->cConnections = guest->cConnections;
    host->cControls = guest->cControls;
    memcpy(host->szShortName, guest->szShortName, sizeof(host->szShortName));
    memcpy(host->szName, guest->szName, sizeof(host->szName));

    host->Target.dwType = guest->Target.dwType;
    host->Target.dwDeviceID = guest->Target.dwDeviceID;
    host->Target.wMid = guest->Target.wMid;
    host->Target.wPid = guest->Target.wPid;
    host->Target.vDriverVersion = guest->Target.vDriverVersion;
    memcpy(host->Target.szPname, guest->Target.szPname, sizeof(host->Target.szPname));
}

static inline void MIXERLINEW_h2g(struct qemu_MIXERLINEW *guest, const MIXERLINEW *host)
{
    guest->dwDestination = host->dwDestination;
    guest->dwSource = host->dwSource;
    guest->dwLineID = host->dwLineID;
    guest->fdwLine = host->fdwLine;
    guest->dwUser = host->dwUser;
    guest->dwComponentType = host->dwComponentType;
    guest->cChannels = host->cChannels;
    guest->cConnections = host->cConnections;
    guest->cControls = host->cControls;
    memcpy(guest->szShortName, host->szShortName, sizeof(guest->szShortName));
    memcpy(guest->szName, host->szName, sizeof(guest->szName));

    guest->Target.dwType = host->Target.dwType;
    guest->Target.dwDeviceID = host->Target.dwDeviceID;
    guest->Target.wMid = host->Target.wMid;
    guest->Target.wPid = host->Target.wPid;
    guest->Target.vDriverVersion = host->Target.vDriverVersion;
    memcpy(guest->Target.szPname, host->Target.szPname, sizeof(guest->Target.szPname));
}

struct qemu_MIXERLINECONTROLS
{
    DWORD       cbStruct;
    DWORD       dwLineID;
    union
    {
        DWORD   dwControlID;
        DWORD   dwControlType;
    } DUMMYUNIONNAME;
    DWORD       cControls;
    DWORD       cbmxctrl;
    qemu_ptr    pamxctrl;
};

static inline void MIXERLINECONTROLS_g2h(MIXERLINECONTROLSW *host, const struct qemu_MIXERLINECONTROLS *guest)
{
    host->cbStruct = sizeof(*host);
    host->dwLineID = guest->dwLineID;
    host->dwControlID = guest->dwControlID;
    host->cControls = guest->cControls;
    host->cbmxctrl = guest->cbmxctrl;
    host->pamxctrl = (MIXERCONTROLW *)(ULONG_PTR)guest->pamxctrl;
}

static inline void MIXERLINECONTROLS_h2g(struct qemu_MIXERLINECONTROLS *guest, const MIXERLINECONTROLSW *host)
{
    guest->dwLineID = host->dwLineID;
    guest->dwControlID = host->dwControlID;
    guest->cControls = host->cControls;
    guest->cbmxctrl = host->cbmxctrl;
    guest->pamxctrl = (ULONG_PTR)host->pamxctrl;
}

#endif
