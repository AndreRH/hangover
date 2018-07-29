#ifndef HAVE_QEMU_THUNK_DINPUT_H
#define HAVE_QEMU_THUNK_DINPUT_H

struct qemu_DIOBJECTDATAFORMAT
{
    qemu_ptr    pguid; /* const GUID * */
    DWORD       dwOfs;
    DWORD       dwType;
    DWORD       dwFlags;
};

static inline void DIOBJECTDATAFORMAT_g2h(DIOBJECTDATAFORMAT *host, const struct qemu_DIOBJECTDATAFORMAT *guest)
{
    host->pguid = (const GUID *)(ULONG_PTR)guest->pguid;
    host->dwOfs = guest->dwOfs;
    host->dwType = guest->dwType;
    host->dwFlags = guest->dwFlags;
}

static inline void DIOBJECTDATAFORMAT_h2g(struct qemu_DIOBJECTDATAFORMAT *guest, const DIOBJECTDATAFORMAT *host)
{
    guest->pguid = (ULONG_PTR)host->pguid;
    guest->dwOfs = host->dwOfs;
    guest->dwType = host->dwType;
    guest->dwFlags = host->dwFlags;
}

struct qemu_DIDATAFORMAT
{
    DWORD                   dwSize;
    DWORD                   dwObjSize;
    DWORD                   dwFlags;
    DWORD                   dwDataSize;
    DWORD                   dwNumObjs;
    qemu_ptr                rgodf; /* DIOBJECTDATAFORMAT * */
};

static inline void DIDATAFORMAT_g2h(DIDATAFORMAT *host, const struct qemu_DIDATAFORMAT *guest)
{
    host->dwSize = sizeof(*host);
    host->dwObjSize = sizeof(DIOBJECTDATAFORMAT);
    host->dwFlags = guest->dwFlags;
    host->dwDataSize = guest->dwDataSize;
    host->dwNumObjs = guest->dwNumObjs;
    /* This is an array, the caller has to convert it. */
    host->rgodf = (DIOBJECTDATAFORMAT *)(ULONG_PTR)guest->rgodf;
}

static inline void DIDATAFORMAT_h2g(struct qemu_DIDATAFORMAT *guest, const DIDATAFORMAT *host)
{
    guest->dwSize = host->dwSize;
    guest->dwObjSize = host->dwObjSize;
    guest->dwFlags = host->dwFlags;
    guest->dwDataSize = host->dwDataSize;
    guest->dwNumObjs = host->dwNumObjs;
    /* This is an array, the caller has to convert it. */
    guest->rgodf = (ULONG_PTR)host->rgodf;
}

struct qemu_DIDEVICEOBJECTDATA
{
    DWORD       dwOfs;
    DWORD       dwData;
    DWORD       dwTimeStamp;
    DWORD       dwSequence;
    qemu_ptr    uAppData;
};

static inline void DIDEVICEOBJECTDATA_g2h(DIDEVICEOBJECTDATA *host, const struct qemu_DIDEVICEOBJECTDATA *guest)
{
    host->dwOfs = guest->dwOfs;
    host->dwData = guest->dwData;
    host->dwTimeStamp = guest->dwTimeStamp;
    host->dwSequence = guest->dwSequence;
    host->uAppData = guest->uAppData;
}

static inline void DIDEVICEOBJECTDATA_h2g(struct qemu_DIDEVICEOBJECTDATA *guest, const DIDEVICEOBJECTDATA *host)
{
    guest->dwOfs = host->dwOfs;
    guest->dwData = host->dwData;
    guest->dwTimeStamp = host->dwTimeStamp;
    guest->dwSequence = host->dwSequence;
    guest->uAppData = host->uAppData;
}

struct qemu_DIACTION
{
    qemu_ptr        uAppData;
    DWORD           dwSemantic;
    DWORD           dwFlags;
    union
    {
        qemu_ptr    lptszActionName;
        UINT        uResIdString;
    } u1;
    GUID            guidInstance;
    DWORD           dwObjID;
    DWORD           dwHow;
};

static inline void DIACTION_g2h(DIACTIONW *host, const struct qemu_DIACTION *guest)
{
    host->uAppData = guest->uAppData;
    host->dwSemantic = guest->dwSemantic;
    host->dwFlags = guest->dwFlags;
    host->lptszActionName = (WCHAR *)(ULONG_PTR)guest->u1.lptszActionName;
    host->guidInstance = guest->guidInstance;
    host->dwObjID = guest->dwObjID;
    host->dwHow = guest->dwHow;
}

static inline void DIACTION_h2g(struct qemu_DIACTION *guest, const DIACTIONW *host)
{
    guest->uAppData = host->uAppData;
    guest->dwSemantic = host->dwSemantic;
    guest->dwFlags = host->dwFlags;
    guest->u1.lptszActionName = (ULONG_PTR)host->lptszActionName;
    guest->guidInstance = host->guidInstance;
    guest->dwObjID = host->dwObjID;
    guest->dwHow = host->dwHow;
}

struct qemu_DIACTIONFORMATA
{
    DWORD               dwSize;
    DWORD               dwActionSize;
    DWORD               dwDataSize;
    DWORD               dwNumActions;
    qemu_ptr            rgoAction;
    GUID                guidActionMap;
    DWORD               dwGenre;
    DWORD               dwBufferSize;
    LONG                lAxisMin;
    LONG                lAxisMax;
    qemu_ptr            hInstString;
    FILETIME            ftTimeStamp;
    DWORD               dwCRC;
    CHAR                tszActionMap[MAX_PATH];
};

static inline void DIACTIONFORMATA_g2h(DIACTIONFORMATA *host, const struct qemu_DIACTIONFORMATA *guest,
        DIACTIONA *actions)
{
    unsigned int i;

    host->dwSize = sizeof(*host);
    host->dwActionSize = guest->dwActionSize;
    host->dwDataSize = guest->dwDataSize;
    host->dwNumActions = guest->dwNumActions;
    host->rgoAction = actions;
    for (i = 0; i < host->dwNumActions; ++i)
        DIACTION_g2h((DIACTIONW *)&actions[i], &((struct qemu_DIACTION *)(ULONG_PTR)guest->rgoAction)[i]);
    host->guidActionMap = guest->guidActionMap;
    host->dwGenre = guest->dwGenre;
    host->dwBufferSize = guest->dwBufferSize;
    host->lAxisMin = guest->lAxisMin;
    host->lAxisMax = guest->lAxisMax;
    host->hInstString = (HINSTANCE)(ULONG_PTR)guest->hInstString;
    host->ftTimeStamp = guest->ftTimeStamp;
    host->dwCRC = guest->dwCRC;
    memcpy(host->tszActionMap, guest->tszActionMap, sizeof(host->tszActionMap));
}

/* This call assumes that the guest already has an appropriately sized action array allocated. */
static inline void DIACTIONFORMATA_h2g(struct qemu_DIACTIONFORMATA *guest, const DIACTIONFORMATA *host)
{
    unsigned int i;

    guest->dwActionSize = host->dwActionSize;
    guest->dwDataSize = host->dwDataSize;
    guest->dwNumActions = host->dwNumActions;
    for (i = 0; i < guest->dwNumActions; ++i)
        DIACTION_h2g(&((struct qemu_DIACTION *)(ULONG_PTR)guest->rgoAction)[i], (DIACTIONW *)&host->rgoAction[i]);
    guest->guidActionMap = host->guidActionMap;
    guest->dwGenre = host->dwGenre;
    guest->dwBufferSize = host->dwBufferSize;
    guest->lAxisMin = host->lAxisMin;
    guest->lAxisMax = host->lAxisMax;
    guest->hInstString = (ULONG_PTR)host->hInstString;
    guest->ftTimeStamp = host->ftTimeStamp;
    guest->dwCRC = host->dwCRC;
    memcpy(guest->tszActionMap, host->tszActionMap, sizeof(guest->tszActionMap));
}

struct qemu_DIACTIONFORMATW
{
    DWORD               dwSize;
    DWORD               dwActionSize;
    DWORD               dwDataSize;
    DWORD               dwNumActions;
    qemu_ptr            rgoAction;
    GUID                guidActionMap;
    DWORD               dwGenre;
    DWORD               dwBufferSize;
    LONG                lAxisMin;
    LONG                lAxisMax;
    qemu_ptr            hInstString;
    FILETIME            ftTimeStamp;
    DWORD               dwCRC;
    WCHAR               tszActionMap[MAX_PATH];
};

static inline void DIACTIONFORMATW_g2h(DIACTIONFORMATW *host, const struct qemu_DIACTIONFORMATW *guest,
        DIACTIONW *actions)
{
    unsigned int i;

    host->dwSize = sizeof(*host);
    host->dwActionSize = guest->dwActionSize;
    host->dwDataSize = guest->dwDataSize;
    host->dwNumActions = guest->dwNumActions;
    host->rgoAction = actions;
    for (i = 0; i < host->dwNumActions; ++i)
        DIACTION_g2h(&actions[i], &((struct qemu_DIACTION *)(ULONG_PTR)guest->rgoAction)[i]);
    host->guidActionMap = guest->guidActionMap;
    host->dwGenre = guest->dwGenre;
    host->dwBufferSize = guest->dwBufferSize;
    host->lAxisMin = guest->lAxisMin;
    host->lAxisMax = guest->lAxisMax;
    host->hInstString = (HINSTANCE)(ULONG_PTR)guest->hInstString;
    host->ftTimeStamp = guest->ftTimeStamp;
    host->dwCRC = guest->dwCRC;
    memcpy(host->tszActionMap, guest->tszActionMap, sizeof(host->tszActionMap));
}

/* This call assumes that the guest already has an appropriately sized action array allocated. */
static inline void DIACTIONFORMATW_h2g(struct qemu_DIACTIONFORMATW *guest, const DIACTIONFORMATW *host)
{
    unsigned int i;

    guest->dwActionSize = host->dwActionSize;
    guest->dwDataSize = host->dwDataSize;
    guest->dwNumActions = host->dwNumActions;
    for (i = 0; i < guest->dwNumActions; ++i)
        DIACTION_h2g(&((struct qemu_DIACTION *)(ULONG_PTR)guest->rgoAction)[i], &host->rgoAction[i]);
    guest->guidActionMap = host->guidActionMap;
    guest->dwGenre = host->dwGenre;
    guest->dwBufferSize = host->dwBufferSize;
    guest->lAxisMin = host->lAxisMin;
    guest->lAxisMax = host->lAxisMax;
    guest->hInstString = (ULONG_PTR)host->hInstString;
    guest->ftTimeStamp = host->ftTimeStamp;
    guest->dwCRC = host->dwCRC;
    memcpy(guest->tszActionMap, host->tszActionMap, sizeof(guest->tszActionMap));
}

#endif
