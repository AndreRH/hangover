#ifndef HAVE_QEMU_THUNK_D3DTYPES_H
#define HAVE_QEMU_THUNK_D3DTYPES_H

struct qemu_D3DDP_PTRSTRIDE
{
  qemu_ptr  lpvData;
  DWORD     dwStride;
};

static inline void D3DDP_PTRSTRIDE_g2h(D3DDP_PTRSTRIDE *host, const struct qemu_D3DDP_PTRSTRIDE *guest)
{
    host->lpvData = (void *)(ULONG_PTR)guest->lpvData;
    host->dwStride = guest->dwStride;
}

struct qemu_D3DDRAWPRIMITIVESTRIDEDDATA
{
    struct qemu_D3DDP_PTRSTRIDE position;
    struct qemu_D3DDP_PTRSTRIDE normal;
    struct qemu_D3DDP_PTRSTRIDE diffuse;
    struct qemu_D3DDP_PTRSTRIDE specular;
    struct qemu_D3DDP_PTRSTRIDE textureCoords[D3DDP_MAXTEXCOORD];
};

static inline void D3DDRAWPRIMITIVESTRIDEDDATA_g2h(D3DDRAWPRIMITIVESTRIDEDDATA *host,
        const struct qemu_D3DDRAWPRIMITIVESTRIDEDDATA *guest)
{
    unsigned int i;

    D3DDP_PTRSTRIDE_g2h(&host->position, &guest->position);
    D3DDP_PTRSTRIDE_g2h(&host->normal, &guest->normal);
    D3DDP_PTRSTRIDE_g2h(&host->diffuse, &guest->diffuse);
    D3DDP_PTRSTRIDE_g2h(&host->specular, &guest->specular);

    for (i = 0; i < sizeof(host->textureCoords) / sizeof(*host->textureCoords); ++i)
        D3DDP_PTRSTRIDE_g2h(&host->textureCoords[i], &guest->textureCoords[i]);
}

#endif
