/*
 * Copyright 2017 André Hentschel
 * Copyright 2017 Stefan Dösinger
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

#include <windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "d3dx9_43.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3dx9_43);
#endif


struct qemu_D3DXColorAdjustContrast
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pc;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXCOLOR* WINAPI D3DXColorAdjustContrast(D3DXCOLOR *pout, const D3DXCOLOR *pc, FLOAT s)
{
    struct qemu_D3DXColorAdjustContrast call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXCOLORADJUSTCONTRAST);
    call.pout = (uint64_t)pout;
    call.pc = (uint64_t)pc;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXCOLOR *)call.super.iret;
}

#else

void qemu_D3DXColorAdjustContrast(struct qemu_syscall *call)
{
    struct qemu_D3DXColorAdjustContrast *c = (struct qemu_D3DXColorAdjustContrast *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXColorAdjustContrast(QEMU_G2H(c->pout), QEMU_G2H(c->pc), c->s));
}

#endif

struct qemu_D3DXColorAdjustSaturation
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pc;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXCOLOR* WINAPI D3DXColorAdjustSaturation(D3DXCOLOR *pout, const D3DXCOLOR *pc, FLOAT s)
{
    struct qemu_D3DXColorAdjustSaturation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXCOLORADJUSTSATURATION);
    call.pout = (uint64_t)pout;
    call.pc = (uint64_t)pc;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXCOLOR *)call.super.iret;
}

#else

void qemu_D3DXColorAdjustSaturation(struct qemu_syscall *call)
{
    struct qemu_D3DXColorAdjustSaturation *c = (struct qemu_D3DXColorAdjustSaturation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXColorAdjustSaturation(QEMU_G2H(c->pout), QEMU_G2H(c->pc), c->s));
}

#endif

struct qemu_D3DXFresnelTerm
{
    struct qemu_syscall super;
    double costheta;
    double refractionindex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT WINAPI D3DXFresnelTerm(FLOAT costheta, FLOAT refractionindex)
{
    struct qemu_D3DXFresnelTerm call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXFRESNELTERM);
    call.costheta = costheta;
    call.refractionindex = refractionindex;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_D3DXFresnelTerm(struct qemu_syscall *call)
{
    struct qemu_D3DXFresnelTerm *c = (struct qemu_D3DXFresnelTerm *)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = D3DXFresnelTerm(c->costheta, c->refractionindex);
}

#endif

struct qemu_D3DXMatrixAffineTransformation
{
    struct qemu_syscall super;
    uint64_t out;
    double scaling;
    uint64_t rotationcenter;
    uint64_t rotation;
    uint64_t translation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX * WINAPI D3DXMatrixAffineTransformation(D3DXMATRIX *out, FLOAT scaling, const D3DXVECTOR3 *rotationcenter, const D3DXQUATERNION *rotation, const D3DXVECTOR3 *translation)
{
    struct qemu_D3DXMatrixAffineTransformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXAFFINETRANSFORMATION);
    call.out = (uint64_t)out;
    call.scaling = scaling;
    call.rotationcenter = (uint64_t)rotationcenter;
    call.rotation = (uint64_t)rotation;
    call.translation = (uint64_t)translation;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixAffineTransformation(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixAffineTransformation *c = (struct qemu_D3DXMatrixAffineTransformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixAffineTransformation(QEMU_G2H(c->out), c->scaling, QEMU_G2H(c->rotationcenter), QEMU_G2H(c->rotation), QEMU_G2H(c->translation)));
}

#endif

struct qemu_D3DXMatrixAffineTransformation2D
{
    struct qemu_syscall super;
    uint64_t out;
    double scaling;
    uint64_t rotationcenter;
    double rotation;
    uint64_t translation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX * WINAPI D3DXMatrixAffineTransformation2D(D3DXMATRIX *out, FLOAT scaling, const D3DXVECTOR2 *rotationcenter, FLOAT rotation, const D3DXVECTOR2 *translation)
{
    struct qemu_D3DXMatrixAffineTransformation2D call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXAFFINETRANSFORMATION2D);
    call.out = (uint64_t)out;
    call.scaling = scaling;
    call.rotationcenter = (uint64_t)rotationcenter;
    call.rotation = rotation;
    call.translation = (uint64_t)translation;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixAffineTransformation2D(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixAffineTransformation2D *c = (struct qemu_D3DXMatrixAffineTransformation2D *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixAffineTransformation2D(QEMU_G2H(c->out), c->scaling, QEMU_G2H(c->rotationcenter), c->rotation, QEMU_G2H(c->translation)));
}

#endif

struct qemu_D3DXMatrixDecompose
{
    struct qemu_syscall super;
    uint64_t poutscale;
    uint64_t poutrotation;
    uint64_t pouttranslation;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3DXMatrixDecompose(D3DXVECTOR3 *poutscale, D3DXQUATERNION *poutrotation, D3DXVECTOR3 *pouttranslation, const D3DXMATRIX *pm)
{
    struct qemu_D3DXMatrixDecompose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXDECOMPOSE);
    call.poutscale = (uint64_t)poutscale;
    call.poutrotation = (uint64_t)poutrotation;
    call.pouttranslation = (uint64_t)pouttranslation;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DXMatrixDecompose(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixDecompose *c = (struct qemu_D3DXMatrixDecompose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3DXMatrixDecompose(QEMU_G2H(c->poutscale), QEMU_G2H(c->poutrotation), QEMU_G2H(c->pouttranslation), QEMU_G2H(c->pm));
}

#endif

struct qemu_D3DXMatrixDeterminant
{
    struct qemu_syscall super;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT WINAPI D3DXMatrixDeterminant(const D3DXMATRIX *pm)
{
    struct qemu_D3DXMatrixDeterminant call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXDETERMINANT);
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_D3DXMatrixDeterminant(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixDeterminant *c = (struct qemu_D3DXMatrixDeterminant *)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = D3DXMatrixDeterminant(QEMU_G2H(c->pm));
}

#endif

struct qemu_D3DXMatrixInverse
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pdeterminant;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixInverse(D3DXMATRIX *pout, FLOAT *pdeterminant, const D3DXMATRIX *pm)
{
    struct qemu_D3DXMatrixInverse call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXINVERSE);
    call.pout = (uint64_t)pout;
    call.pdeterminant = (uint64_t)pdeterminant;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixInverse(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixInverse *c = (struct qemu_D3DXMatrixInverse *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixInverse(QEMU_G2H(c->pout), QEMU_G2H(c->pdeterminant), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXMatrixLookAtLH
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t eye;
    uint64_t at;
    uint64_t up;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX * WINAPI D3DXMatrixLookAtLH(D3DXMATRIX *out, const D3DXVECTOR3 *eye, const D3DXVECTOR3 *at, const D3DXVECTOR3 *up)
{
    struct qemu_D3DXMatrixLookAtLH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXLOOKATLH);
    call.out = (uint64_t)out;
    call.eye = (uint64_t)eye;
    call.at = (uint64_t)at;
    call.up = (uint64_t)up;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixLookAtLH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixLookAtLH *c = (struct qemu_D3DXMatrixLookAtLH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixLookAtLH(QEMU_G2H(c->out), QEMU_G2H(c->eye), QEMU_G2H(c->at), QEMU_G2H(c->up)));
}

#endif

struct qemu_D3DXMatrixLookAtRH
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t eye;
    uint64_t at;
    uint64_t up;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX * WINAPI D3DXMatrixLookAtRH(D3DXMATRIX *out, const D3DXVECTOR3 *eye, const D3DXVECTOR3 *at, const D3DXVECTOR3 *up)
{
    struct qemu_D3DXMatrixLookAtRH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXLOOKATRH);
    call.out = (uint64_t)out;
    call.eye = (uint64_t)eye;
    call.at = (uint64_t)at;
    call.up = (uint64_t)up;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixLookAtRH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixLookAtRH *c = (struct qemu_D3DXMatrixLookAtRH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixLookAtRH(QEMU_G2H(c->out), QEMU_G2H(c->eye), QEMU_G2H(c->at), QEMU_G2H(c->up)));
}

#endif

struct qemu_D3DXMatrixMultiply
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pm1;
    uint64_t pm2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixMultiply(D3DXMATRIX *pout, const D3DXMATRIX *pm1, const D3DXMATRIX *pm2)
{
    struct qemu_D3DXMatrixMultiply call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXMULTIPLY);
    call.pout = (uint64_t)pout;
    call.pm1 = (uint64_t)pm1;
    call.pm2 = (uint64_t)pm2;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixMultiply(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixMultiply *c = (struct qemu_D3DXMatrixMultiply *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixMultiply(QEMU_G2H(c->pout), QEMU_G2H(c->pm1), QEMU_G2H(c->pm2)));
}

#endif

struct qemu_D3DXMatrixMultiplyTranspose
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pm1;
    uint64_t pm2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixMultiplyTranspose(D3DXMATRIX *pout, const D3DXMATRIX *pm1, const D3DXMATRIX *pm2)
{
    struct qemu_D3DXMatrixMultiplyTranspose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXMULTIPLYTRANSPOSE);
    call.pout = (uint64_t)pout;
    call.pm1 = (uint64_t)pm1;
    call.pm2 = (uint64_t)pm2;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixMultiplyTranspose(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixMultiplyTranspose *c = (struct qemu_D3DXMatrixMultiplyTranspose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixMultiplyTranspose(QEMU_G2H(c->pout), QEMU_G2H(c->pm1), QEMU_G2H(c->pm2)));
}

#endif

struct qemu_D3DXMatrixOrthoLH
{
    struct qemu_syscall super;
    uint64_t pout;
    double w;
    double h;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixOrthoLH(D3DXMATRIX *pout, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixOrthoLH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXORTHOLH);
    call.pout = (uint64_t)pout;
    call.w = w;
    call.h = h;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixOrthoLH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixOrthoLH *c = (struct qemu_D3DXMatrixOrthoLH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixOrthoLH(QEMU_G2H(c->pout), c->w, c->h, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixOrthoOffCenterLH
{
    struct qemu_syscall super;
    uint64_t pout;
    double l;
    double r;
    double b;
    double t;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixOrthoOffCenterLH(D3DXMATRIX *pout, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixOrthoOffCenterLH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXORTHOOFFCENTERLH);
    call.pout = (uint64_t)pout;
    call.l = l;
    call.r = r;
    call.b = b;
    call.t = t;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixOrthoOffCenterLH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixOrthoOffCenterLH *c = (struct qemu_D3DXMatrixOrthoOffCenterLH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixOrthoOffCenterLH(QEMU_G2H(c->pout), c->l, c->r, c->b, c->t, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixOrthoOffCenterRH
{
    struct qemu_syscall super;
    uint64_t pout;
    double l;
    double r;
    double b;
    double t;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixOrthoOffCenterRH(D3DXMATRIX *pout, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixOrthoOffCenterRH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXORTHOOFFCENTERRH);
    call.pout = (uint64_t)pout;
    call.l = l;
    call.r = r;
    call.b = b;
    call.t = t;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixOrthoOffCenterRH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixOrthoOffCenterRH *c = (struct qemu_D3DXMatrixOrthoOffCenterRH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixOrthoOffCenterRH(QEMU_G2H(c->pout), c->l, c->r, c->b, c->t, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixOrthoRH
{
    struct qemu_syscall super;
    uint64_t pout;
    double w;
    double h;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixOrthoRH(D3DXMATRIX *pout, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixOrthoRH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXORTHORH);
    call.pout = (uint64_t)pout;
    call.w = w;
    call.h = h;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixOrthoRH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixOrthoRH *c = (struct qemu_D3DXMatrixOrthoRH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixOrthoRH(QEMU_G2H(c->pout), c->w, c->h, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixPerspectiveFovLH
{
    struct qemu_syscall super;
    uint64_t pout;
    double fovy;
    double aspect;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixPerspectiveFovLH(D3DXMATRIX *pout, FLOAT fovy, FLOAT aspect, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixPerspectiveFovLH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXPERSPECTIVEFOVLH);
    call.pout = (uint64_t)pout;
    call.fovy = fovy;
    call.aspect = aspect;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixPerspectiveFovLH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixPerspectiveFovLH *c = (struct qemu_D3DXMatrixPerspectiveFovLH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixPerspectiveFovLH(QEMU_G2H(c->pout), c->fovy, c->aspect, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixPerspectiveFovRH
{
    struct qemu_syscall super;
    uint64_t pout;
    double fovy;
    double aspect;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixPerspectiveFovRH(D3DXMATRIX *pout, FLOAT fovy, FLOAT aspect, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixPerspectiveFovRH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXPERSPECTIVEFOVRH);
    call.pout = (uint64_t)pout;
    call.fovy = fovy;
    call.aspect = aspect;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixPerspectiveFovRH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixPerspectiveFovRH *c = (struct qemu_D3DXMatrixPerspectiveFovRH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixPerspectiveFovRH(QEMU_G2H(c->pout), c->fovy, c->aspect, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixPerspectiveLH
{
    struct qemu_syscall super;
    uint64_t pout;
    double w;
    double h;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixPerspectiveLH(D3DXMATRIX *pout, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixPerspectiveLH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXPERSPECTIVELH);
    call.pout = (uint64_t)pout;
    call.w = w;
    call.h = h;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixPerspectiveLH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixPerspectiveLH *c = (struct qemu_D3DXMatrixPerspectiveLH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixPerspectiveLH(QEMU_G2H(c->pout), c->w, c->h, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixPerspectiveOffCenterLH
{
    struct qemu_syscall super;
    uint64_t pout;
    double l;
    double r;
    double b;
    double t;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixPerspectiveOffCenterLH(D3DXMATRIX *pout, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixPerspectiveOffCenterLH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXPERSPECTIVEOFFCENTERLH);
    call.pout = (uint64_t)pout;
    call.l = l;
    call.r = r;
    call.b = b;
    call.t = t;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixPerspectiveOffCenterLH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixPerspectiveOffCenterLH *c = (struct qemu_D3DXMatrixPerspectiveOffCenterLH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixPerspectiveOffCenterLH(QEMU_G2H(c->pout), c->l, c->r, c->b, c->t, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixPerspectiveOffCenterRH
{
    struct qemu_syscall super;
    uint64_t pout;
    double l;
    double r;
    double b;
    double t;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixPerspectiveOffCenterRH(D3DXMATRIX *pout, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixPerspectiveOffCenterRH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXPERSPECTIVEOFFCENTERRH);
    call.pout = (uint64_t)pout;
    call.l = l;
    call.r = r;
    call.b = b;
    call.t = t;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixPerspectiveOffCenterRH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixPerspectiveOffCenterRH *c = (struct qemu_D3DXMatrixPerspectiveOffCenterRH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixPerspectiveOffCenterRH(QEMU_G2H(c->pout), c->l, c->r, c->b, c->t, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixPerspectiveRH
{
    struct qemu_syscall super;
    uint64_t pout;
    double w;
    double h;
    double zn;
    double zf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixPerspectiveRH(D3DXMATRIX *pout, FLOAT w, FLOAT h, FLOAT zn, FLOAT zf)
{
    struct qemu_D3DXMatrixPerspectiveRH call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXPERSPECTIVERH);
    call.pout = (uint64_t)pout;
    call.w = w;
    call.h = h;
    call.zn = zn;
    call.zf = zf;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixPerspectiveRH(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixPerspectiveRH *c = (struct qemu_D3DXMatrixPerspectiveRH *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixPerspectiveRH(QEMU_G2H(c->pout), c->w, c->h, c->zn, c->zf));
}

#endif

struct qemu_D3DXMatrixReflect
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pplane;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixReflect(D3DXMATRIX *pout, const D3DXPLANE *pplane)
{
    struct qemu_D3DXMatrixReflect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXREFLECT);
    call.pout = (uint64_t)pout;
    call.pplane = (uint64_t)pplane;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixReflect(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixReflect *c = (struct qemu_D3DXMatrixReflect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixReflect(QEMU_G2H(c->pout), QEMU_G2H(c->pplane)));
}

#endif

struct qemu_D3DXMatrixRotationAxis
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t v;
    double angle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX * WINAPI D3DXMatrixRotationAxis(D3DXMATRIX *out, const D3DXVECTOR3 *v, FLOAT angle)
{
    struct qemu_D3DXMatrixRotationAxis call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXROTATIONAXIS);
    call.out = (uint64_t)out;
    call.v = (uint64_t)v;
    call.angle = angle;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixRotationAxis(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixRotationAxis *c = (struct qemu_D3DXMatrixRotationAxis *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixRotationAxis(QEMU_G2H(c->out), QEMU_G2H(c->v), c->angle));
}

#endif

struct qemu_D3DXMatrixRotationQuaternion
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pq;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixRotationQuaternion(D3DXMATRIX *pout, const D3DXQUATERNION *pq)
{
    struct qemu_D3DXMatrixRotationQuaternion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXROTATIONQUATERNION);
    call.pout = (uint64_t)pout;
    call.pq = (uint64_t)pq;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixRotationQuaternion(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixRotationQuaternion *c = (struct qemu_D3DXMatrixRotationQuaternion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixRotationQuaternion(QEMU_G2H(c->pout), QEMU_G2H(c->pq)));
}

#endif

struct qemu_D3DXMatrixRotationX
{
    struct qemu_syscall super;
    uint64_t pout;
    double angle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixRotationX(D3DXMATRIX *pout, FLOAT angle)
{
    struct qemu_D3DXMatrixRotationX call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXROTATIONX);
    call.pout = (uint64_t)pout;
    call.angle = angle;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixRotationX(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixRotationX *c = (struct qemu_D3DXMatrixRotationX *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixRotationX(QEMU_G2H(c->pout), c->angle));
}

#endif

struct qemu_D3DXMatrixRotationY
{
    struct qemu_syscall super;
    uint64_t pout;
    double angle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixRotationY(D3DXMATRIX *pout, FLOAT angle)
{
    struct qemu_D3DXMatrixRotationY call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXROTATIONY);
    call.pout = (uint64_t)pout;
    call.angle = angle;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixRotationY(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixRotationY *c = (struct qemu_D3DXMatrixRotationY *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixRotationY(QEMU_G2H(c->pout), c->angle));
}

#endif

struct qemu_D3DXMatrixRotationYawPitchRoll
{
    struct qemu_syscall super;
    uint64_t out;
    double yaw;
    double pitch;
    double roll;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX * WINAPI D3DXMatrixRotationYawPitchRoll(D3DXMATRIX *out, FLOAT yaw, FLOAT pitch, FLOAT roll)
{
    struct qemu_D3DXMatrixRotationYawPitchRoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXROTATIONYAWPITCHROLL);
    call.out = (uint64_t)out;
    call.yaw = yaw;
    call.pitch = pitch;
    call.roll = roll;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixRotationYawPitchRoll(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixRotationYawPitchRoll *c = (struct qemu_D3DXMatrixRotationYawPitchRoll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixRotationYawPitchRoll(QEMU_G2H(c->out), c->yaw, c->pitch, c->roll));
}

#endif

struct qemu_D3DXMatrixRotationZ
{
    struct qemu_syscall super;
    uint64_t pout;
    double angle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixRotationZ(D3DXMATRIX *pout, FLOAT angle)
{
    struct qemu_D3DXMatrixRotationZ call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXROTATIONZ);
    call.pout = (uint64_t)pout;
    call.angle = angle;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixRotationZ(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixRotationZ *c = (struct qemu_D3DXMatrixRotationZ *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixRotationZ(QEMU_G2H(c->pout), c->angle));
}

#endif

struct qemu_D3DXMatrixScaling
{
    struct qemu_syscall super;
    uint64_t pout;
    double sx;
    double sy;
    double sz;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixScaling(D3DXMATRIX *pout, FLOAT sx, FLOAT sy, FLOAT sz)
{
    struct qemu_D3DXMatrixScaling call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXSCALING);
    call.pout = (uint64_t)pout;
    call.sx = sx;
    call.sy = sy;
    call.sz = sz;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixScaling(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixScaling *c = (struct qemu_D3DXMatrixScaling *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixScaling(QEMU_G2H(c->pout), c->sx, c->sy, c->sz));
}

#endif

struct qemu_D3DXMatrixShadow
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t plight;
    uint64_t pplane;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixShadow(D3DXMATRIX *pout, const D3DXVECTOR4 *plight, const D3DXPLANE *pplane)
{
    struct qemu_D3DXMatrixShadow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXSHADOW);
    call.pout = (uint64_t)pout;
    call.plight = (uint64_t)plight;
    call.pplane = (uint64_t)pplane;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixShadow(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixShadow *c = (struct qemu_D3DXMatrixShadow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixShadow(QEMU_G2H(c->pout), QEMU_G2H(c->plight), QEMU_G2H(c->pplane)));
}

#endif

struct qemu_D3DXMatrixTransformation
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pscalingcenter;
    uint64_t pscalingrotation;
    uint64_t pscaling;
    uint64_t protationcenter;
    uint64_t protation;
    uint64_t ptranslation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixTransformation(D3DXMATRIX *pout, const D3DXVECTOR3 *pscalingcenter, const D3DXQUATERNION *pscalingrotation, const D3DXVECTOR3 *pscaling, const D3DXVECTOR3 *protationcenter, const D3DXQUATERNION *protation, const D3DXVECTOR3 *ptranslation)
{
    struct qemu_D3DXMatrixTransformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXTRANSFORMATION);
    call.pout = (uint64_t)pout;
    call.pscalingcenter = (uint64_t)pscalingcenter;
    call.pscalingrotation = (uint64_t)pscalingrotation;
    call.pscaling = (uint64_t)pscaling;
    call.protationcenter = (uint64_t)protationcenter;
    call.protation = (uint64_t)protation;
    call.ptranslation = (uint64_t)ptranslation;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixTransformation(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixTransformation *c = (struct qemu_D3DXMatrixTransformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixTransformation(QEMU_G2H(c->pout), QEMU_G2H(c->pscalingcenter), QEMU_G2H(c->pscalingrotation), QEMU_G2H(c->pscaling), QEMU_G2H(c->protationcenter), QEMU_G2H(c->protation), QEMU_G2H(c->ptranslation)));
}

#endif

struct qemu_D3DXMatrixTransformation2D
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pscalingcenter;
    double scalingrotation;
    uint64_t pscaling;
    uint64_t protationcenter;
    double rotation;
    uint64_t ptranslation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixTransformation2D(D3DXMATRIX *pout, const D3DXVECTOR2 *pscalingcenter, FLOAT scalingrotation, const D3DXVECTOR2 *pscaling, const D3DXVECTOR2 *protationcenter, FLOAT rotation, const D3DXVECTOR2 *ptranslation)
{
    struct qemu_D3DXMatrixTransformation2D call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXTRANSFORMATION2D);
    call.pout = (uint64_t)pout;
    call.pscalingcenter = (uint64_t)pscalingcenter;
    call.scalingrotation = scalingrotation;
    call.pscaling = (uint64_t)pscaling;
    call.protationcenter = (uint64_t)protationcenter;
    call.rotation = rotation;
    call.ptranslation = (uint64_t)ptranslation;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixTransformation2D(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixTransformation2D *c = (struct qemu_D3DXMatrixTransformation2D *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixTransformation2D(QEMU_G2H(c->pout), QEMU_G2H(c->pscalingcenter), c->scalingrotation, QEMU_G2H(c->pscaling), QEMU_G2H(c->protationcenter), c->rotation, QEMU_G2H(c->ptranslation)));
}

#endif

struct qemu_D3DXMatrixTranslation
{
    struct qemu_syscall super;
    uint64_t pout;
    double x;
    double y;
    double z;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixTranslation(D3DXMATRIX *pout, FLOAT x, FLOAT y, FLOAT z)
{
    struct qemu_D3DXMatrixTranslation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXTRANSLATION);
    call.pout = (uint64_t)pout;
    call.x = x;
    call.y = y;
    call.z = z;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixTranslation(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixTranslation *c = (struct qemu_D3DXMatrixTranslation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixTranslation(QEMU_G2H(c->pout), c->x, c->y, c->z));
}

#endif

struct qemu_D3DXMatrixTranspose
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXMATRIX* WINAPI D3DXMatrixTranspose(D3DXMATRIX *pout, const D3DXMATRIX *pm)
{
    struct qemu_D3DXMatrixTranspose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXMATRIXTRANSPOSE);
    call.pout = (uint64_t)pout;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXMATRIX *)call.super.iret;
}

#else

void qemu_D3DXMatrixTranspose(struct qemu_syscall *call)
{
    struct qemu_D3DXMatrixTranspose *c = (struct qemu_D3DXMatrixTranspose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXMatrixTranspose(QEMU_G2H(c->pout), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXCreateMatrixStack
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t stack;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3DXCreateMatrixStack(DWORD flags, ID3DXMatrixStack **stack)
{
    struct qemu_D3DXCreateMatrixStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXCREATEMATRIXSTACK);
    call.flags = (uint64_t)flags;
    call.stack = (uint64_t)stack;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DXCreateMatrixStack(struct qemu_syscall *call)
{
    struct qemu_D3DXCreateMatrixStack *c = (struct qemu_D3DXCreateMatrixStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXCreateMatrixStack(c->flags, QEMU_G2H(c->stack)));
}

#endif

struct qemu_D3DXPlaneFromPointNormal
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pvpoint;
    uint64_t pvnormal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXPLANE* WINAPI D3DXPlaneFromPointNormal(D3DXPLANE *pout, const D3DXVECTOR3 *pvpoint, const D3DXVECTOR3 *pvnormal)
{
    struct qemu_D3DXPlaneFromPointNormal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXPLANEFROMPOINTNORMAL);
    call.pout = (uint64_t)pout;
    call.pvpoint = (uint64_t)pvpoint;
    call.pvnormal = (uint64_t)pvnormal;

    qemu_syscall(&call.super);

    return (D3DXPLANE *)call.super.iret;
}

#else

void qemu_D3DXPlaneFromPointNormal(struct qemu_syscall *call)
{
    struct qemu_D3DXPlaneFromPointNormal *c = (struct qemu_D3DXPlaneFromPointNormal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXPlaneFromPointNormal(QEMU_G2H(c->pout), QEMU_G2H(c->pvpoint), QEMU_G2H(c->pvnormal)));
}

#endif

struct qemu_D3DXPlaneFromPoints
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXPLANE* WINAPI D3DXPlaneFromPoints(D3DXPLANE *pout, const D3DXVECTOR3 *pv1, const D3DXVECTOR3 *pv2, const D3DXVECTOR3 *pv3)
{
    struct qemu_D3DXPlaneFromPoints call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXPLANEFROMPOINTS);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;

    qemu_syscall(&call.super);

    return (D3DXPLANE *)call.super.iret;
}

#else

void qemu_D3DXPlaneFromPoints(struct qemu_syscall *call)
{
    struct qemu_D3DXPlaneFromPoints *c = (struct qemu_D3DXPlaneFromPoints *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXPlaneFromPoints(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3)));
}

#endif

struct qemu_D3DXPlaneIntersectLine
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pp;
    uint64_t pv1;
    uint64_t pv2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXPlaneIntersectLine(D3DXVECTOR3 *pout, const D3DXPLANE *pp, const D3DXVECTOR3 *pv1, const D3DXVECTOR3 *pv2)
{
    struct qemu_D3DXPlaneIntersectLine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXPLANEINTERSECTLINE);
    call.pout = (uint64_t)pout;
    call.pp = (uint64_t)pp;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXPlaneIntersectLine(struct qemu_syscall *call)
{
    struct qemu_D3DXPlaneIntersectLine *c = (struct qemu_D3DXPlaneIntersectLine *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXPlaneIntersectLine(QEMU_G2H(c->pout), QEMU_G2H(c->pp), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2)));
}

#endif

struct qemu_D3DXPlaneNormalize
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXPLANE * WINAPI D3DXPlaneNormalize(D3DXPLANE *out, const D3DXPLANE *p)
{
    struct qemu_D3DXPlaneNormalize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXPLANENORMALIZE);
    call.out = (uint64_t)out;
    call.p = (uint64_t)p;

    qemu_syscall(&call.super);

    return (D3DXPLANE *)call.super.iret;
}

#else

void qemu_D3DXPlaneNormalize(struct qemu_syscall *call)
{
    struct qemu_D3DXPlaneNormalize *c = (struct qemu_D3DXPlaneNormalize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXPlaneNormalize(QEMU_G2H(c->out), QEMU_G2H(c->p)));
}

#endif

struct qemu_D3DXPlaneTransform
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pplane;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXPLANE* WINAPI D3DXPlaneTransform(D3DXPLANE *pout, const D3DXPLANE *pplane, const D3DXMATRIX *pm)
{
    struct qemu_D3DXPlaneTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXPLANETRANSFORM);
    call.pout = (uint64_t)pout;
    call.pplane = (uint64_t)pplane;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXPLANE *)call.super.iret;
}

#else

void qemu_D3DXPlaneTransform(struct qemu_syscall *call)
{
    struct qemu_D3DXPlaneTransform *c = (struct qemu_D3DXPlaneTransform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXPlaneTransform(QEMU_G2H(c->pout), QEMU_G2H(c->pplane), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXPlaneTransformArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXPLANE* WINAPI D3DXPlaneTransformArray(D3DXPLANE* out, UINT outstride, const D3DXPLANE* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXPlaneTransformArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXPLANETRANSFORMARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXPLANE *)call.super.iret;
}

#else

void qemu_D3DXPlaneTransformArray(struct qemu_syscall *call)
{
    struct qemu_D3DXPlaneTransformArray *c = (struct qemu_D3DXPlaneTransformArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXPlaneTransformArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXQuaternionBaryCentric
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pq1;
    uint64_t pq2;
    uint64_t pq3;
    double f;
    double g;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION* WINAPI D3DXQuaternionBaryCentric(D3DXQUATERNION *pout, const D3DXQUATERNION *pq1, const D3DXQUATERNION *pq2, const D3DXQUATERNION *pq3, FLOAT f, FLOAT g)
{
    struct qemu_D3DXQuaternionBaryCentric call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONBARYCENTRIC);
    call.pout = (uint64_t)pout;
    call.pq1 = (uint64_t)pq1;
    call.pq2 = (uint64_t)pq2;
    call.pq3 = (uint64_t)pq3;
    call.f = f;
    call.g = g;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionBaryCentric(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionBaryCentric *c = (struct qemu_D3DXQuaternionBaryCentric *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionBaryCentric(QEMU_G2H(c->pout), QEMU_G2H(c->pq1), QEMU_G2H(c->pq2), QEMU_G2H(c->pq3), c->f, c->g));
}

#endif

struct qemu_D3DXQuaternionExp
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t q;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionExp(D3DXQUATERNION *out, const D3DXQUATERNION *q)
{
    struct qemu_D3DXQuaternionExp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONEXP);
    call.out = (uint64_t)out;
    call.q = (uint64_t)q;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionExp(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionExp *c = (struct qemu_D3DXQuaternionExp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionExp(QEMU_G2H(c->out), QEMU_G2H(c->q)));
}

#endif

struct qemu_D3DXQuaternionInverse
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pq;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION* WINAPI D3DXQuaternionInverse(D3DXQUATERNION *pout, const D3DXQUATERNION *pq)
{
    struct qemu_D3DXQuaternionInverse call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONINVERSE);
    call.pout = (uint64_t)pout;
    call.pq = (uint64_t)pq;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionInverse(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionInverse *c = (struct qemu_D3DXQuaternionInverse *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionInverse(QEMU_G2H(c->pout), QEMU_G2H(c->pq)));
}

#endif

struct qemu_D3DXQuaternionLn
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t q;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionLn(D3DXQUATERNION *out, const D3DXQUATERNION *q)
{
    struct qemu_D3DXQuaternionLn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONLN);
    call.out = (uint64_t)out;
    call.q = (uint64_t)q;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionLn(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionLn *c = (struct qemu_D3DXQuaternionLn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionLn(QEMU_G2H(c->out), QEMU_G2H(c->q)));
}

#endif

struct qemu_D3DXQuaternionMultiply
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pq1;
    uint64_t pq2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION* WINAPI D3DXQuaternionMultiply(D3DXQUATERNION *pout, const D3DXQUATERNION *pq1, const D3DXQUATERNION *pq2)
{
    struct qemu_D3DXQuaternionMultiply call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONMULTIPLY);
    call.pout = (uint64_t)pout;
    call.pq1 = (uint64_t)pq1;
    call.pq2 = (uint64_t)pq2;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionMultiply(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionMultiply *c = (struct qemu_D3DXQuaternionMultiply *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionMultiply(QEMU_G2H(c->pout), QEMU_G2H(c->pq1), QEMU_G2H(c->pq2)));
}

#endif

struct qemu_D3DXQuaternionNormalize
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t q;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionNormalize(D3DXQUATERNION *out, const D3DXQUATERNION *q)
{
    struct qemu_D3DXQuaternionNormalize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONNORMALIZE);
    call.out = (uint64_t)out;
    call.q = (uint64_t)q;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionNormalize(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionNormalize *c = (struct qemu_D3DXQuaternionNormalize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionNormalize(QEMU_G2H(c->out), QEMU_G2H(c->q)));
}

#endif

struct qemu_D3DXQuaternionRotationAxis
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t v;
    double angle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionRotationAxis(D3DXQUATERNION *out, const D3DXVECTOR3 *v, FLOAT angle)
{
    struct qemu_D3DXQuaternionRotationAxis call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONROTATIONAXIS);
    call.out = (uint64_t)out;
    call.v = (uint64_t)v;
    call.angle = angle;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionRotationAxis(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionRotationAxis *c = (struct qemu_D3DXQuaternionRotationAxis *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionRotationAxis(QEMU_G2H(c->out), QEMU_G2H(c->v), c->angle));
}

#endif

struct qemu_D3DXQuaternionRotationMatrix
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t m;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionRotationMatrix(D3DXQUATERNION *out, const D3DXMATRIX *m)
{
    struct qemu_D3DXQuaternionRotationMatrix call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONROTATIONMATRIX);
    call.out = (uint64_t)out;
    call.m = (uint64_t)m;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionRotationMatrix(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionRotationMatrix *c = (struct qemu_D3DXQuaternionRotationMatrix *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionRotationMatrix(QEMU_G2H(c->out), QEMU_G2H(c->m)));
}

#endif

struct qemu_D3DXQuaternionRotationYawPitchRoll
{
    struct qemu_syscall super;
    uint64_t out;
    double yaw;
    double pitch;
    double roll;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionRotationYawPitchRoll(D3DXQUATERNION *out, FLOAT yaw, FLOAT pitch, FLOAT roll)
{
    struct qemu_D3DXQuaternionRotationYawPitchRoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONROTATIONYAWPITCHROLL);
    call.out = (uint64_t)out;
    call.yaw = yaw;
    call.pitch = pitch;
    call.roll = roll;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionRotationYawPitchRoll(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionRotationYawPitchRoll *c = (struct qemu_D3DXQuaternionRotationYawPitchRoll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionRotationYawPitchRoll(QEMU_G2H(c->out), c->yaw, c->pitch, c->roll));
}

#endif

struct qemu_D3DXQuaternionSlerp
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t q1;
    uint64_t q2;
    double t;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION * WINAPI D3DXQuaternionSlerp(D3DXQUATERNION *out, const D3DXQUATERNION *q1, const D3DXQUATERNION *q2, FLOAT t)
{
    struct qemu_D3DXQuaternionSlerp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONSLERP);
    call.out = (uint64_t)out;
    call.q1 = (uint64_t)q1;
    call.q2 = (uint64_t)q2;
    call.t = t;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionSlerp(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionSlerp *c = (struct qemu_D3DXQuaternionSlerp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionSlerp(QEMU_G2H(c->out), QEMU_G2H(c->q1), QEMU_G2H(c->q2), c->t));
}

#endif

struct qemu_D3DXQuaternionSquad
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pq1;
    uint64_t pq2;
    uint64_t pq3;
    uint64_t pq4;
    double t;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXQUATERNION* WINAPI D3DXQuaternionSquad(D3DXQUATERNION *pout, const D3DXQUATERNION *pq1, const D3DXQUATERNION *pq2, const D3DXQUATERNION *pq3, const D3DXQUATERNION *pq4, FLOAT t)
{
    struct qemu_D3DXQuaternionSquad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONSQUAD);
    call.pout = (uint64_t)pout;
    call.pq1 = (uint64_t)pq1;
    call.pq2 = (uint64_t)pq2;
    call.pq3 = (uint64_t)pq3;
    call.pq4 = (uint64_t)pq4;
    call.t = t;

    qemu_syscall(&call.super);

    return (D3DXQUATERNION *)call.super.iret;
}

#else

void qemu_D3DXQuaternionSquad(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionSquad *c = (struct qemu_D3DXQuaternionSquad *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXQuaternionSquad(QEMU_G2H(c->pout), QEMU_G2H(c->pq1), QEMU_G2H(c->pq2), QEMU_G2H(c->pq3), QEMU_G2H(c->pq4), c->t));
}

#endif

struct qemu_D3DXQuaternionSquadSetup
{
    struct qemu_syscall super;
    uint64_t paout;
    uint64_t pbout;
    uint64_t pcout;
    uint64_t pq0;
    uint64_t pq1;
    uint64_t pq2;
    uint64_t pq3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI D3DXQuaternionSquadSetup(D3DXQUATERNION *paout, D3DXQUATERNION *pbout, D3DXQUATERNION *pcout, const D3DXQUATERNION *pq0, const D3DXQUATERNION *pq1, const D3DXQUATERNION *pq2, const D3DXQUATERNION *pq3)
{
    struct qemu_D3DXQuaternionSquadSetup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONSQUADSETUP);
    call.paout = (uint64_t)paout;
    call.pbout = (uint64_t)pbout;
    call.pcout = (uint64_t)pcout;
    call.pq0 = (uint64_t)pq0;
    call.pq1 = (uint64_t)pq1;
    call.pq2 = (uint64_t)pq2;
    call.pq3 = (uint64_t)pq3;

    qemu_syscall(&call.super);
}

#else

void qemu_D3DXQuaternionSquadSetup(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionSquadSetup *c = (struct qemu_D3DXQuaternionSquadSetup *)call;
    WINE_FIXME("Unverified!\n");
    D3DXQuaternionSquadSetup(QEMU_G2H(c->paout), QEMU_G2H(c->pbout), QEMU_G2H(c->pcout), QEMU_G2H(c->pq0), QEMU_G2H(c->pq1), QEMU_G2H(c->pq2), QEMU_G2H(c->pq3));
}

#endif

struct qemu_D3DXQuaternionToAxisAngle
{
    struct qemu_syscall super;
    uint64_t pq;
    uint64_t paxis;
    uint64_t pangle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI D3DXQuaternionToAxisAngle(const D3DXQUATERNION *pq, D3DXVECTOR3 *paxis, FLOAT *pangle)
{
    struct qemu_D3DXQuaternionToAxisAngle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXQUATERNIONTOAXISANGLE);
    call.pq = (uint64_t)pq;
    call.paxis = (uint64_t)paxis;
    call.pangle = (uint64_t)pangle;

    qemu_syscall(&call.super);
}

#else

void qemu_D3DXQuaternionToAxisAngle(struct qemu_syscall *call)
{
    struct qemu_D3DXQuaternionToAxisAngle *c = (struct qemu_D3DXQuaternionToAxisAngle *)call;
    WINE_FIXME("Unverified!\n");
    D3DXQuaternionToAxisAngle(QEMU_G2H(c->pq), QEMU_G2H(c->paxis), QEMU_G2H(c->pangle));
}

#endif

struct qemu_D3DXVec2BaryCentric
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
    double f;
    double g;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2BaryCentric(D3DXVECTOR2 *pout, const D3DXVECTOR2 *pv1, const D3DXVECTOR2 *pv2, const D3DXVECTOR2 *pv3, FLOAT f, FLOAT g)
{
    struct qemu_D3DXVec2BaryCentric call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2BARYCENTRIC);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;
    call.f = f;
    call.g = g;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2BaryCentric(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2BaryCentric *c = (struct qemu_D3DXVec2BaryCentric *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2BaryCentric(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3), c->f, c->g));
}

#endif

struct qemu_D3DXVec2CatmullRom
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv0;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2CatmullRom(D3DXVECTOR2 *pout, const D3DXVECTOR2 *pv0, const D3DXVECTOR2 *pv1, const D3DXVECTOR2 *pv2, const D3DXVECTOR2 *pv3, FLOAT s)
{
    struct qemu_D3DXVec2CatmullRom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2CATMULLROM);
    call.pout = (uint64_t)pout;
    call.pv0 = (uint64_t)pv0;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2CatmullRom(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2CatmullRom *c = (struct qemu_D3DXVec2CatmullRom *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2CatmullRom(QEMU_G2H(c->pout), QEMU_G2H(c->pv0), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3), c->s));
}

#endif

struct qemu_D3DXVec2Hermite
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pt1;
    uint64_t pv2;
    uint64_t pt2;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2Hermite(D3DXVECTOR2 *pout, const D3DXVECTOR2 *pv1, const D3DXVECTOR2 *pt1, const D3DXVECTOR2 *pv2, const D3DXVECTOR2 *pt2, FLOAT s)
{
    struct qemu_D3DXVec2Hermite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2HERMITE);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pt1 = (uint64_t)pt1;
    call.pv2 = (uint64_t)pv2;
    call.pt2 = (uint64_t)pt2;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2Hermite(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2Hermite *c = (struct qemu_D3DXVec2Hermite *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2Hermite(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pt1), QEMU_G2H(c->pv2), QEMU_G2H(c->pt2), c->s));
}

#endif

struct qemu_D3DXVec2Normalize
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2Normalize(D3DXVECTOR2 *pout, const D3DXVECTOR2 *pv)
{
    struct qemu_D3DXVec2Normalize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2NORMALIZE);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2Normalize(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2Normalize *c = (struct qemu_D3DXVec2Normalize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2Normalize(QEMU_G2H(c->pout), QEMU_G2H(c->pv)));
}

#endif

struct qemu_D3DXVec2Transform
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec2Transform(D3DXVECTOR4 *pout, const D3DXVECTOR2 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec2Transform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2TRANSFORM);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec2Transform(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2Transform *c = (struct qemu_D3DXVec2Transform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2Transform(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec2TransformArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec2TransformArray(D3DXVECTOR4* out, UINT outstride, const D3DXVECTOR2* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXVec2TransformArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2TRANSFORMARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec2TransformArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2TransformArray *c = (struct qemu_D3DXVec2TransformArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2TransformArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXVec2TransformCoord
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2TransformCoord(D3DXVECTOR2 *pout, const D3DXVECTOR2 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec2TransformCoord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2TRANSFORMCOORD);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2TransformCoord(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2TransformCoord *c = (struct qemu_D3DXVec2TransformCoord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2TransformCoord(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec2TransformCoordArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2TransformCoordArray(D3DXVECTOR2* out, UINT outstride, const D3DXVECTOR2* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXVec2TransformCoordArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2TRANSFORMCOORDARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2TransformCoordArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2TransformCoordArray *c = (struct qemu_D3DXVec2TransformCoordArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2TransformCoordArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXVec2TransformNormal
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2TransformNormal(D3DXVECTOR2 *pout, const D3DXVECTOR2 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec2TransformNormal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2TRANSFORMNORMAL);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2TransformNormal(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2TransformNormal *c = (struct qemu_D3DXVec2TransformNormal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2TransformNormal(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec2TransformNormalArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR2* WINAPI D3DXVec2TransformNormalArray(D3DXVECTOR2* out, UINT outstride, const D3DXVECTOR2 *in, UINT instride, const D3DXMATRIX *matrix, UINT elements)
{
    struct qemu_D3DXVec2TransformNormalArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC2TRANSFORMNORMALARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR2 *)call.super.iret;
}

#else

void qemu_D3DXVec2TransformNormalArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec2TransformNormalArray *c = (struct qemu_D3DXVec2TransformNormalArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec2TransformNormalArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXVec3BaryCentric
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
    double f;
    double g;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3BaryCentric(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv1, const D3DXVECTOR3 *pv2, const D3DXVECTOR3 *pv3, FLOAT f, FLOAT g)
{
    struct qemu_D3DXVec3BaryCentric call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3BARYCENTRIC);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;
    call.f = f;
    call.g = g;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3BaryCentric(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3BaryCentric *c = (struct qemu_D3DXVec3BaryCentric *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3BaryCentric(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3), c->f, c->g));
}

#endif

struct qemu_D3DXVec3CatmullRom
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv0;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3CatmullRom(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv0, const D3DXVECTOR3 *pv1, const D3DXVECTOR3 *pv2, const D3DXVECTOR3 *pv3, FLOAT s)
{
    struct qemu_D3DXVec3CatmullRom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3CATMULLROM);
    call.pout = (uint64_t)pout;
    call.pv0 = (uint64_t)pv0;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3CatmullRom(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3CatmullRom *c = (struct qemu_D3DXVec3CatmullRom *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3CatmullRom(QEMU_G2H(c->pout), QEMU_G2H(c->pv0), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3), c->s));
}

#endif

struct qemu_D3DXVec3Hermite
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pt1;
    uint64_t pv2;
    uint64_t pt2;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3Hermite(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv1, const D3DXVECTOR3 *pt1, const D3DXVECTOR3 *pv2, const D3DXVECTOR3 *pt2, FLOAT s)
{
    struct qemu_D3DXVec3Hermite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3HERMITE);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pt1 = (uint64_t)pt1;
    call.pv2 = (uint64_t)pv2;
    call.pt2 = (uint64_t)pt2;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3Hermite(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3Hermite *c = (struct qemu_D3DXVec3Hermite *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3Hermite(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pt1), QEMU_G2H(c->pv2), QEMU_G2H(c->pt2), c->s));
}

#endif

struct qemu_D3DXVec3Normalize
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3Normalize(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv)
{
    struct qemu_D3DXVec3Normalize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3NORMALIZE);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3Normalize(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3Normalize *c = (struct qemu_D3DXVec3Normalize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3Normalize(QEMU_G2H(c->pout), QEMU_G2H(c->pv)));
}

#endif

struct qemu_D3DXVec3Project
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pviewport;
    uint64_t pprojection;
    uint64_t pview;
    uint64_t pworld;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3Project(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv, const D3DVIEWPORT9 *pviewport, const D3DXMATRIX *pprojection, const D3DXMATRIX *pview, const D3DXMATRIX *pworld)
{
    struct qemu_D3DXVec3Project call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3PROJECT);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pviewport = (uint64_t)pviewport;
    call.pprojection = (uint64_t)pprojection;
    call.pview = (uint64_t)pview;
    call.pworld = (uint64_t)pworld;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3Project(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3Project *c = (struct qemu_D3DXVec3Project *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3Project(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pviewport), QEMU_G2H(c->pprojection), QEMU_G2H(c->pview), QEMU_G2H(c->pworld)));
}

#endif

struct qemu_D3DXVec3ProjectArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t viewport;
    uint64_t projection;
    uint64_t view;
    uint64_t world;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3ProjectArray(D3DXVECTOR3* out, UINT outstride, const D3DXVECTOR3* in, UINT instride, const D3DVIEWPORT9* viewport, const D3DXMATRIX* projection, const D3DXMATRIX* view, const D3DXMATRIX* world, UINT elements)
{
    struct qemu_D3DXVec3ProjectArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3PROJECTARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.viewport = (uint64_t)viewport;
    call.projection = (uint64_t)projection;
    call.view = (uint64_t)view;
    call.world = (uint64_t)world;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3ProjectArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3ProjectArray *c = (struct qemu_D3DXVec3ProjectArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3ProjectArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->viewport), QEMU_G2H(c->projection), QEMU_G2H(c->view), QEMU_G2H(c->world), c->elements));
}

#endif

struct qemu_D3DXVec3Transform
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec3Transform(D3DXVECTOR4 *pout, const D3DXVECTOR3 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec3Transform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORM);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec3Transform(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3Transform *c = (struct qemu_D3DXVec3Transform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3Transform(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec3TransformArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec3TransformArray(D3DXVECTOR4* out, UINT outstride, const D3DXVECTOR3* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXVec3TransformArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORMARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec3TransformArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3TransformArray *c = (struct qemu_D3DXVec3TransformArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3TransformArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXVec3TransformCoord
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3TransformCoord(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec3TransformCoord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORMCOORD);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3TransformCoord(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3TransformCoord *c = (struct qemu_D3DXVec3TransformCoord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3TransformCoord(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec3TransformCoordArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3TransformCoordArray(D3DXVECTOR3* out, UINT outstride, const D3DXVECTOR3* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXVec3TransformCoordArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORMCOORDARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3TransformCoordArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3TransformCoordArray *c = (struct qemu_D3DXVec3TransformCoordArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3TransformCoordArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXVec3TransformNormal
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3TransformNormal(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec3TransformNormal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORMNORMAL);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3TransformNormal(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3TransformNormal *c = (struct qemu_D3DXVec3TransformNormal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3TransformNormal(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec3TransformNormalArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3TransformNormalArray(D3DXVECTOR3* out, UINT outstride, const D3DXVECTOR3* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXVec3TransformNormalArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORMNORMALARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3TransformNormalArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3TransformNormalArray *c = (struct qemu_D3DXVec3TransformNormalArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3TransformNormalArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXVec3Unproject
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pviewport;
    uint64_t pprojection;
    uint64_t pview;
    uint64_t pworld;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3Unproject(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv, const D3DVIEWPORT9 *pviewport, const D3DXMATRIX *pprojection, const D3DXMATRIX *pview, const D3DXMATRIX *pworld)
{
    struct qemu_D3DXVec3Unproject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3UNPROJECT);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pviewport = (uint64_t)pviewport;
    call.pprojection = (uint64_t)pprojection;
    call.pview = (uint64_t)pview;
    call.pworld = (uint64_t)pworld;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3Unproject(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3Unproject *c = (struct qemu_D3DXVec3Unproject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3Unproject(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pviewport), QEMU_G2H(c->pprojection), QEMU_G2H(c->pview), QEMU_G2H(c->pworld)));
}

#endif

struct qemu_D3DXVec3UnprojectArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t viewport;
    uint64_t projection;
    uint64_t view;
    uint64_t world;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR3* WINAPI D3DXVec3UnprojectArray(D3DXVECTOR3* out, UINT outstride, const D3DXVECTOR3* in, UINT instride, const D3DVIEWPORT9* viewport, const D3DXMATRIX* projection, const D3DXMATRIX* view, const D3DXMATRIX* world, UINT elements)
{
    struct qemu_D3DXVec3UnprojectArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3UNPROJECTARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.viewport = (uint64_t)viewport;
    call.projection = (uint64_t)projection;
    call.view = (uint64_t)view;
    call.world = (uint64_t)world;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3UnprojectArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3UnprojectArray *c = (struct qemu_D3DXVec3UnprojectArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3UnprojectArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->viewport), QEMU_G2H(c->projection), QEMU_G2H(c->view), QEMU_G2H(c->world), c->elements));
}

#endif

struct qemu_D3DXVec4BaryCentric
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
    double f;
    double g;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4BaryCentric(D3DXVECTOR4 *pout, const D3DXVECTOR4 *pv1, const D3DXVECTOR4 *pv2, const D3DXVECTOR4 *pv3, FLOAT f, FLOAT g)
{
    struct qemu_D3DXVec4BaryCentric call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4BARYCENTRIC);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;
    call.f = f;
    call.g = g;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4BaryCentric(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4BaryCentric *c = (struct qemu_D3DXVec4BaryCentric *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4BaryCentric(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3), c->f, c->g));
}

#endif

struct qemu_D3DXVec4CatmullRom
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv0;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4CatmullRom(D3DXVECTOR4 *pout, const D3DXVECTOR4 *pv0, const D3DXVECTOR4 *pv1, const D3DXVECTOR4 *pv2, const D3DXVECTOR4 *pv3, FLOAT s)
{
    struct qemu_D3DXVec4CatmullRom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4CATMULLROM);
    call.pout = (uint64_t)pout;
    call.pv0 = (uint64_t)pv0;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4CatmullRom(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4CatmullRom *c = (struct qemu_D3DXVec4CatmullRom *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4CatmullRom(QEMU_G2H(c->pout), QEMU_G2H(c->pv0), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3), c->s));
}

#endif

struct qemu_D3DXVec4Cross
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pv2;
    uint64_t pv3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4Cross(D3DXVECTOR4 *pout, const D3DXVECTOR4 *pv1, const D3DXVECTOR4 *pv2, const D3DXVECTOR4 *pv3)
{
    struct qemu_D3DXVec4Cross call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4CROSS);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pv2 = (uint64_t)pv2;
    call.pv3 = (uint64_t)pv3;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4Cross(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4Cross *c = (struct qemu_D3DXVec4Cross *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4Cross(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pv2), QEMU_G2H(c->pv3)));
}

#endif

struct qemu_D3DXVec4Hermite
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv1;
    uint64_t pt1;
    uint64_t pv2;
    uint64_t pt2;
    double s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4Hermite(D3DXVECTOR4 *pout, const D3DXVECTOR4 *pv1, const D3DXVECTOR4 *pt1, const D3DXVECTOR4 *pv2, const D3DXVECTOR4 *pt2, FLOAT s)
{
    struct qemu_D3DXVec4Hermite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4HERMITE);
    call.pout = (uint64_t)pout;
    call.pv1 = (uint64_t)pv1;
    call.pt1 = (uint64_t)pt1;
    call.pv2 = (uint64_t)pv2;
    call.pt2 = (uint64_t)pt2;
    call.s = s;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4Hermite(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4Hermite *c = (struct qemu_D3DXVec4Hermite *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4Hermite(QEMU_G2H(c->pout), QEMU_G2H(c->pv1), QEMU_G2H(c->pt1), QEMU_G2H(c->pv2), QEMU_G2H(c->pt2), c->s));
}

#endif

struct qemu_D3DXVec4Normalize
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4Normalize(D3DXVECTOR4 *pout, const D3DXVECTOR4 *pv)
{
    struct qemu_D3DXVec4Normalize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4NORMALIZE);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4Normalize(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4Normalize *c = (struct qemu_D3DXVec4Normalize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4Normalize(QEMU_G2H(c->pout), QEMU_G2H(c->pv)));
}

#endif

struct qemu_D3DXVec4Transform
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4Transform(D3DXVECTOR4 *pout, const D3DXVECTOR4 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec4Transform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4TRANSFORM);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4Transform(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4Transform *c = (struct qemu_D3DXVec4Transform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4Transform(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif

struct qemu_D3DXVec4TransformArray
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t outstride;
    uint64_t in;
    uint64_t instride;
    uint64_t matrix;
    uint64_t elements;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXVECTOR4* WINAPI D3DXVec4TransformArray(D3DXVECTOR4* out, UINT outstride, const D3DXVECTOR4* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
{
    struct qemu_D3DXVec4TransformArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC4TRANSFORMARRAY);
    call.out = (uint64_t)out;
    call.outstride = (uint64_t)outstride;
    call.in = (uint64_t)in;
    call.instride = (uint64_t)instride;
    call.matrix = (uint64_t)matrix;
    call.elements = (uint64_t)elements;

    qemu_syscall(&call.super);

    return (D3DXVECTOR4 *)call.super.iret;
}

#else

void qemu_D3DXVec4TransformArray(struct qemu_syscall *call)
{
    struct qemu_D3DXVec4TransformArray *c = (struct qemu_D3DXVec4TransformArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec4TransformArray(QEMU_G2H(c->out), c->outstride, QEMU_G2H(c->in), c->instride, QEMU_G2H(c->matrix), c->elements));
}

#endif

struct qemu_D3DXFloat32To16Array
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pin;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI D3DXFLOAT16 *WINAPI D3DXFloat32To16Array(D3DXFLOAT16 *pout, const FLOAT *pin, UINT n)
{
    struct qemu_D3DXFloat32To16Array call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXFLOAT32TO16ARRAY);
    call.pout = (uint64_t)pout;
    call.pin = (uint64_t)pin;
    call.n = n;

    qemu_syscall(&call.super);

    return (D3DXFLOAT16 *)call.super.iret;
}

#else

void qemu_D3DXFloat32To16Array(struct qemu_syscall *call)
{
    struct qemu_D3DXFloat32To16Array *c = (struct qemu_D3DXFloat32To16Array *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXFloat32To16Array(QEMU_G2H(c->pout), QEMU_G2H(c->pin), c->n));
}

#endif

struct qemu_D3DXFloat16To32Array
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pin;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT *WINAPI D3DXFloat16To32Array(FLOAT *pout, const D3DXFLOAT16 *pin, UINT n)
{
    struct qemu_D3DXFloat16To32Array call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXFLOAT16TO32ARRAY);
    call.pout = (uint64_t)pout;
    call.pin = (uint64_t)pin;
    call.n = (uint64_t)n;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXFloat16To32Array(struct qemu_syscall *call)
{
    struct qemu_D3DXFloat16To32Array *c = (struct qemu_D3DXFloat16To32Array *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXFloat16To32Array(QEMU_G2H(c->pout), QEMU_G2H(c->pin), c->n));
}

#endif

struct qemu_D3DXSHAdd
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t order;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT* WINAPI D3DXSHAdd(FLOAT *out, UINT order, const FLOAT *a, const FLOAT *b)
{
    struct qemu_D3DXSHAdd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHADD);
    call.out = (uint64_t)out;
    call.order = (uint64_t)order;
    call.a = (uint64_t)a;
    call.b = (uint64_t)b;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHAdd(struct qemu_syscall *call)
{
    struct qemu_D3DXSHAdd *c = (struct qemu_D3DXSHAdd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHAdd(QEMU_G2H(c->out), c->order, QEMU_G2H(c->a), QEMU_G2H(c->b)));
}

#endif

struct qemu_D3DXSHDot
{
    struct qemu_syscall super;
    uint64_t order;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT WINAPI D3DXSHDot(UINT order, const FLOAT *a, const FLOAT *b)
{
    struct qemu_D3DXSHDot call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHDOT);
    call.order = (uint64_t)order;
    call.a = (uint64_t)a;
    call.b = (uint64_t)b;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_D3DXSHDot(struct qemu_syscall *call)
{
    struct qemu_D3DXSHDot *c = (struct qemu_D3DXSHDot *)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = D3DXSHDot(c->order, QEMU_G2H(c->a), QEMU_G2H(c->b));
}

#endif

struct qemu_D3DXSHEvalConeLight
{
    struct qemu_syscall super;
    uint64_t order;
    uint64_t dir;
    double radius;
    double Rintensity;
    double Gintensity;
    double Bintensity;
    uint64_t rout;
    uint64_t gout;
    uint64_t bout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3DXSHEvalConeLight(UINT order, const D3DXVECTOR3 *dir, FLOAT radius, FLOAT Rintensity, FLOAT Gintensity, FLOAT Bintensity, FLOAT *rout, FLOAT *gout, FLOAT *bout)
{
    struct qemu_D3DXSHEvalConeLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHEVALCONELIGHT);
    call.order = (uint64_t)order;
    call.dir = (uint64_t)dir;
    call.radius = radius;
    call.Rintensity = Rintensity;
    call.Gintensity = Gintensity;
    call.Bintensity = Bintensity;
    call.rout = (uint64_t)rout;
    call.gout = (uint64_t)gout;
    call.bout = (uint64_t)bout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DXSHEvalConeLight(struct qemu_syscall *call)
{
    struct qemu_D3DXSHEvalConeLight *c = (struct qemu_D3DXSHEvalConeLight *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHEvalConeLight(c->order, QEMU_G2H(c->dir), c->radius, c->Rintensity, c->Gintensity, c->Bintensity, QEMU_G2H(c->rout), QEMU_G2H(c->gout), QEMU_G2H(c->bout)));
}

#endif

struct qemu_D3DXSHEvalDirection
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t order;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT* WINAPI D3DXSHEvalDirection(FLOAT *out, UINT order, const D3DXVECTOR3 *dir)
{
    struct qemu_D3DXSHEvalDirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHEVALDIRECTION);
    call.out = (uint64_t)out;
    call.order = (uint64_t)order;
    call.dir = (uint64_t)dir;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHEvalDirection(struct qemu_syscall *call)
{
    struct qemu_D3DXSHEvalDirection *c = (struct qemu_D3DXSHEvalDirection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHEvalDirection(QEMU_G2H(c->out), c->order, QEMU_G2H(c->dir)));
}

#endif

struct qemu_D3DXSHEvalDirectionalLight
{
    struct qemu_syscall super;
    uint64_t order;
    uint64_t dir;
    double Rintensity;
    double Gintensity;
    double Bintensity;
    uint64_t Rout;
    uint64_t Gout;
    uint64_t Bout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3DXSHEvalDirectionalLight(UINT order, const D3DXVECTOR3 *dir, FLOAT Rintensity, FLOAT Gintensity, FLOAT Bintensity, FLOAT *Rout, FLOAT *Gout, FLOAT *Bout)
{
    struct qemu_D3DXSHEvalDirectionalLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHEVALDIRECTIONALLIGHT);
    call.order = (uint64_t)order;
    call.dir = (uint64_t)dir;
    call.Rintensity = Rintensity;
    call.Gintensity = Gintensity;
    call.Bintensity = Bintensity;
    call.Rout = (uint64_t)Rout;
    call.Gout = (uint64_t)Gout;
    call.Bout = (uint64_t)Bout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DXSHEvalDirectionalLight(struct qemu_syscall *call)
{
    struct qemu_D3DXSHEvalDirectionalLight *c = (struct qemu_D3DXSHEvalDirectionalLight *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHEvalDirectionalLight(c->order, QEMU_G2H(c->dir), c->Rintensity, c->Gintensity, c->Bintensity, QEMU_G2H(c->Rout), QEMU_G2H(c->Gout), QEMU_G2H(c->Bout)));
}

#endif

struct qemu_D3DXSHEvalHemisphereLight
{
    struct qemu_syscall super;
    uint64_t order;
    uint64_t dir;
    double topr, topg, topb, topa;
    double bottomr, bottomg, bottomb, bottoma;
    uint64_t rout;
    uint64_t gout;
    uint64_t bout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3DXSHEvalHemisphereLight(UINT order, const D3DXVECTOR3 *dir, D3DXCOLOR top, D3DXCOLOR bottom, FLOAT *rout, FLOAT *gout, FLOAT *bout)
{
    struct qemu_D3DXSHEvalHemisphereLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHEVALHEMISPHERELIGHT);
    call.order = (uint64_t)order;
    call.dir = (uint64_t)dir;
    call.topr = top.r;
    call.topg = top.g;
    call.topb = top.b;
    call.topa = top.a;
    call.bottomr = bottom.r;
    call.bottomg = bottom.g;
    call.bottomb = bottom.b;
    call.bottoma = bottom.a;
    call.rout = (uint64_t)rout;
    call.gout = (uint64_t)gout;
    call.bout = (uint64_t)bout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DXSHEvalHemisphereLight(struct qemu_syscall *call)
{
    D3DXCOLOR top, bottom;
    struct qemu_D3DXSHEvalHemisphereLight *c = (struct qemu_D3DXSHEvalHemisphereLight *)call;
    WINE_FIXME("Unverified!\n");

    top.r = c->topr;
    top.g = c->topg;
    top.b = c->topb;
    top.a = c->topa;
    bottom.r = c->bottomr;
    bottom.g = c->bottomg;
    bottom.b = c->bottomb;
    bottom.a = c->bottoma;

    c->super.iret = QEMU_H2G(D3DXSHEvalHemisphereLight(c->order, QEMU_G2H(c->dir), top, bottom, QEMU_G2H(c->rout), QEMU_G2H(c->gout), QEMU_G2H(c->bout)));
}

#endif

struct qemu_D3DXSHEvalSphericalLight
{
    struct qemu_syscall super;
    uint64_t order;
    uint64_t dir;
    double radius;
    double Rintensity;
    double Gintensity;
    double Bintensity;
    uint64_t rout;
    uint64_t gout;
    uint64_t bout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3DXSHEvalSphericalLight(UINT order, const D3DXVECTOR3 *dir, FLOAT radius, FLOAT Rintensity, FLOAT Gintensity, FLOAT Bintensity, FLOAT *rout, FLOAT *gout, FLOAT *bout)
{
    struct qemu_D3DXSHEvalSphericalLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHEVALSPHERICALLIGHT);
    call.order = (uint64_t)order;
    call.dir = (uint64_t)dir;
    call.radius = radius;
    call.Rintensity = Rintensity;
    call.Gintensity = Gintensity;
    call.Bintensity = Bintensity;
    call.rout = (uint64_t)rout;
    call.gout = (uint64_t)gout;
    call.bout = (uint64_t)bout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DXSHEvalSphericalLight(struct qemu_syscall *call)
{
    struct qemu_D3DXSHEvalSphericalLight *c = (struct qemu_D3DXSHEvalSphericalLight *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHEvalSphericalLight(c->order, QEMU_G2H(c->dir), c->radius, c->Rintensity, c->Gintensity, c->Bintensity, QEMU_G2H(c->rout), QEMU_G2H(c->gout), QEMU_G2H(c->bout)));
}

#endif

struct qemu_D3DXSHMultiply2
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT * WINAPI D3DXSHMultiply2(FLOAT *out, const FLOAT *a, const FLOAT *b)
{
    struct qemu_D3DXSHMultiply2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHMULTIPLY2);
    call.out = (uint64_t)out;
    call.a = (uint64_t)a;
    call.b = (uint64_t)b;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHMultiply2(struct qemu_syscall *call)
{
    struct qemu_D3DXSHMultiply2 *c = (struct qemu_D3DXSHMultiply2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHMultiply2(QEMU_G2H(c->out), QEMU_G2H(c->a), QEMU_G2H(c->b)));
}

#endif

struct qemu_D3DXSHMultiply3
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT * WINAPI D3DXSHMultiply3(FLOAT *out, const FLOAT *a, const FLOAT *b)
{
    struct qemu_D3DXSHMultiply3 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHMULTIPLY3);
    call.out = (uint64_t)out;
    call.a = (uint64_t)a;
    call.b = (uint64_t)b;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHMultiply3(struct qemu_syscall *call)
{
    struct qemu_D3DXSHMultiply3 *c = (struct qemu_D3DXSHMultiply3 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHMultiply3(QEMU_G2H(c->out), QEMU_G2H(c->a), QEMU_G2H(c->b)));
}

#endif

struct qemu_D3DXSHMultiply4
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT * WINAPI D3DXSHMultiply4(FLOAT *out, const FLOAT *a, const FLOAT *b)
{
    struct qemu_D3DXSHMultiply4 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHMULTIPLY4);
    call.out = (uint64_t)out;
    call.a = (uint64_t)a;
    call.b = (uint64_t)b;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHMultiply4(struct qemu_syscall *call)
{
    struct qemu_D3DXSHMultiply4 *c = (struct qemu_D3DXSHMultiply4 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHMultiply4(QEMU_G2H(c->out), QEMU_G2H(c->a), QEMU_G2H(c->b)));
}

#endif

struct qemu_D3DXSHRotate
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t order;
    uint64_t matrix;
    uint64_t in;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT* WINAPI D3DXSHRotate(FLOAT *out, UINT order, const D3DXMATRIX *matrix, const FLOAT *in)
{
    struct qemu_D3DXSHRotate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHROTATE);
    call.out = (uint64_t)out;
    call.order = (uint64_t)order;
    call.matrix = (uint64_t)matrix;
    call.in = (uint64_t)in;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHRotate(struct qemu_syscall *call)
{
    struct qemu_D3DXSHRotate *c = (struct qemu_D3DXSHRotate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHRotate(QEMU_G2H(c->out), c->order, QEMU_G2H(c->matrix), QEMU_G2H(c->in)));
}

#endif

struct qemu_D3DXSHRotateZ
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t order;
    double angle;
    uint64_t in;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT * WINAPI D3DXSHRotateZ(FLOAT *out, UINT order, FLOAT angle, const FLOAT *in)
{
    struct qemu_D3DXSHRotateZ call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHROTATEZ);
    call.out = (uint64_t)out;
    call.order = (uint64_t)order;
    call.angle = angle;
    call.in = (uint64_t)in;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHRotateZ(struct qemu_syscall *call)
{
    struct qemu_D3DXSHRotateZ *c = (struct qemu_D3DXSHRotateZ *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHRotateZ(QEMU_G2H(c->out), c->order, c->angle, QEMU_G2H(c->in)));
}

#endif

struct qemu_D3DXSHScale
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t order;
    uint64_t a;
    float scale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FLOAT* WINAPI D3DXSHScale(FLOAT *out, UINT order, const FLOAT *a, const FLOAT scale)
{
    struct qemu_D3DXSHScale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXSHSCALE);
    call.out = (uint64_t)out;
    call.order = (uint64_t)order;
    call.a = (uint64_t)a;
    call.scale = scale;

    qemu_syscall(&call.super);

    return (FLOAT *)call.super.iret;
}

#else

void qemu_D3DXSHScale(struct qemu_syscall *call)
{
    struct qemu_D3DXSHScale *c = (struct qemu_D3DXSHScale *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXSHScale(QEMU_G2H(c->out), c->order, QEMU_G2H(c->a), c->scale));
}

#endif

