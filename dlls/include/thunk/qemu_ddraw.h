#ifndef HAVE_QEMU_THUNK_DDRAW_H
#define HAVE_QEMU_THUNK_DDRAW_H

struct qemu_DDSURFACEDESC
{
    DWORD           dwSize;
    DWORD           dwFlags;
    DWORD           dwHeight;
    DWORD           dwWidth;
    union
    {
        LONG        lPitch;
        DWORD       dwLinearSize;
    } DUMMYUNIONNAME1;
    DWORD   dwBackBufferCount;
    union
    {
        DWORD       dwMipMapCount;
        DWORD       dwZBufferBitDepth;
        DWORD       dwRefreshRate;
    } DUMMYUNIONNAME2;
    DWORD           dwAlphaBitDepth;
    DWORD           dwReserved;
    qemu_ptr        lpSurface;
    DDCOLORKEY      ddckCKDestOverlay;
    DDCOLORKEY      ddckCKDestBlt;
    DDCOLORKEY      ddckCKSrcOverlay;
    DDCOLORKEY      ddckCKSrcBlt;
    DDPIXELFORMAT   ddpfPixelFormat;
    DDSCAPS         ddsCaps;
};

/* Don't call this on invalid sized structs. */
static inline void DDSURFACEDESC_g2h(DDSURFACEDESC *host, const struct qemu_DDSURFACEDESC *guest)
{
    host->dwSize = sizeof(*host);
    host->dwFlags = guest->dwFlags;
    host->dwHeight = guest->dwHeight;
    host->dwWidth = guest->dwWidth;
    host->lPitch = guest->lPitch;
    host->dwBackBufferCount = guest->dwBackBufferCount;
    host->dwMipMapCount = guest->dwMipMapCount;
    host->dwAlphaBitDepth = guest->dwAlphaBitDepth;
    host->dwReserved = guest->dwReserved;
    host->lpSurface = (void *)(ULONG_PTR)guest->lpSurface;
    host->ddckCKDestOverlay = guest->ddckCKDestOverlay;
    host->ddckCKDestBlt = guest->ddckCKDestBlt;
    host->ddckCKSrcOverlay = guest->ddckCKSrcOverlay;
    host->ddckCKSrcBlt = guest->ddckCKSrcBlt;
    host->ddpfPixelFormat = guest->ddpfPixelFormat;
    host->ddsCaps = guest->ddsCaps;
}

/* Initialize guest->dwSize yourself, and check before calling on app data. */
static inline void DDSURFACEDESC_h2g(struct qemu_DDSURFACEDESC *guest, const DDSURFACEDESC *host)
{
    guest->dwFlags = host->dwFlags;
    guest->dwHeight = host->dwHeight;
    guest->dwWidth = host->dwWidth;
    guest->lPitch = host->lPitch;
    guest->dwBackBufferCount = host->dwBackBufferCount;
    guest->dwMipMapCount = host->dwMipMapCount;
    guest->dwAlphaBitDepth = host->dwAlphaBitDepth;
    guest->dwReserved = host->dwReserved;
    guest->lpSurface = (ULONG_PTR)host->lpSurface;
    guest->ddckCKDestOverlay = host->ddckCKDestOverlay;
    guest->ddckCKDestBlt = host->ddckCKDestBlt;
    guest->ddckCKSrcOverlay = host->ddckCKSrcOverlay;
    guest->ddckCKSrcBlt = host->ddckCKSrcBlt;
    guest->ddpfPixelFormat = host->ddpfPixelFormat;
    guest->ddsCaps = host->ddsCaps;
}

struct qemu_DDSURFACEDESC2
{
    DWORD   dwSize;
    DWORD   dwFlags;
    DWORD   dwHeight;
    DWORD   dwWidth;
    union
    {
        LONG	lPitch;
        DWORD   dwLinearSize;
    } DUMMYUNIONNAME1;
    union
    {
        DWORD   dwBackBufferCount;
        DWORD   dwDepth;
    } DUMMYUNIONNAME5;
    union
    {
        DWORD   dwMipMapCount;
        DWORD   dwRefreshRate;
        DWORD   dwSrcVBHandle;
    } DUMMYUNIONNAME2;
    DWORD   dwAlphaBitDepth;
    DWORD   dwReserved;
    qemu_ptr lpSurface;
    union
    {
        DDCOLORKEY      ddckCKDestOverlay;
        DWORD           dwEmptyFaceColor;
    } DUMMYUNIONNAME3;
    DDCOLORKEY          ddckCKDestBlt;
    DDCOLORKEY          ddckCKSrcOverlay;
    DDCOLORKEY          ddckCKSrcBlt;

    union
    {
        DDPIXELFORMAT   ddpfPixelFormat;
        DWORD           dwFVF;
    } DUMMYUNIONNAME4;
    DDSCAPS2            ddsCaps;
    DWORD               dwTextureStage;
};

/* Call this only on DDSURFACEDESC or DDSURFACEDESC2 sized structs! */
static inline void DDSURFACEDESC2_g2h(DDSURFACEDESC2 *host, const struct qemu_DDSURFACEDESC2 *guest)
{
    DDSURFACEDESC_g2h((DDSURFACEDESC *)host, (const struct qemu_DDSURFACEDESC *)guest);
    if (guest->dwSize < sizeof(*guest))
        return;

    host->dwSize = sizeof(*host);
    host->ddsCaps = guest->ddsCaps;
    host->dwTextureStage = guest->dwTextureStage;

}

/* Initialize guest->dwSize yourself, and check before calling on app data. */
static inline void DDSURFACEDESC2_h2g(struct qemu_DDSURFACEDESC2 *guest, const DDSURFACEDESC2 *host)
{
    DDSURFACEDESC_h2g((struct qemu_DDSURFACEDESC *)guest, (const DDSURFACEDESC *)host);
    guest->ddsCaps = host->ddsCaps;
    guest->dwTextureStage = host->dwTextureStage;

}

#endif
