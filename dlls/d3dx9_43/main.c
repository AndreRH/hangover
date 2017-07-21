/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3dx9);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_D3DXColorAdjustContrast,
    qemu_D3DXColorAdjustSaturation,
    qemu_D3DXCreateMatrixStack,
    qemu_D3DXFloat16To32Array,
    qemu_D3DXFloat32To16Array,
    qemu_D3DXFresnelTerm,
    qemu_D3DXMatrixAffineTransformation,
    qemu_D3DXMatrixAffineTransformation2D,
    qemu_D3DXMatrixDecompose,
    qemu_D3DXMatrixDeterminant,
    qemu_D3DXMatrixInverse,
    qemu_D3DXMatrixLookAtLH,
    qemu_D3DXMatrixLookAtRH,
    qemu_D3DXMatrixMultiply,
    qemu_D3DXMatrixMultiplyTranspose,
    qemu_D3DXMatrixOrthoLH,
    qemu_D3DXMatrixOrthoOffCenterLH,
    qemu_D3DXMatrixOrthoOffCenterRH,
    qemu_D3DXMatrixOrthoRH,
    qemu_D3DXMatrixPerspectiveFovLH,
    qemu_D3DXMatrixPerspectiveFovRH,
    qemu_D3DXMatrixPerspectiveLH,
    qemu_D3DXMatrixPerspectiveOffCenterLH,
    qemu_D3DXMatrixPerspectiveOffCenterRH,
    qemu_D3DXMatrixPerspectiveRH,
    qemu_D3DXMatrixReflect,
    qemu_D3DXMatrixRotationAxis,
    qemu_D3DXMatrixRotationQuaternion,
    qemu_D3DXMatrixRotationX,
    qemu_D3DXMatrixRotationY,
    qemu_D3DXMatrixRotationYawPitchRoll,
    qemu_D3DXMatrixRotationZ,
    qemu_D3DXMatrixScaling,
    qemu_D3DXMatrixShadow,
    qemu_D3DXMatrixTransformation,
    qemu_D3DXMatrixTransformation2D,
    qemu_D3DXMatrixTranslation,
    qemu_D3DXMatrixTranspose,
    qemu_D3DXPlaneFromPointNormal,
    qemu_D3DXPlaneFromPoints,
    qemu_D3DXPlaneIntersectLine,
    qemu_D3DXPlaneNormalize,
    qemu_D3DXPlaneTransform,
    qemu_D3DXPlaneTransformArray,
    qemu_D3DXQuaternionBaryCentric,
    qemu_D3DXQuaternionExp,
    qemu_D3DXQuaternionInverse,
    qemu_D3DXQuaternionLn,
    qemu_D3DXQuaternionMultiply,
    qemu_D3DXQuaternionNormalize,
    qemu_D3DXQuaternionRotationAxis,
    qemu_D3DXQuaternionRotationMatrix,
    qemu_D3DXQuaternionRotationYawPitchRoll,
    qemu_D3DXQuaternionSlerp,
    qemu_D3DXQuaternionSquad,
    qemu_D3DXQuaternionSquadSetup,
    qemu_D3DXQuaternionToAxisAngle,
    qemu_D3DXSHAdd,
    qemu_D3DXSHDot,
    qemu_D3DXSHEvalConeLight,
    qemu_D3DXSHEvalDirection,
    qemu_D3DXSHEvalDirectionalLight,
    qemu_D3DXSHEvalHemisphereLight,
    qemu_D3DXSHEvalSphericalLight,
    qemu_D3DXSHMultiply2,
    qemu_D3DXSHMultiply3,
    qemu_D3DXSHMultiply4,
    qemu_D3DXSHRotate,
    qemu_D3DXSHRotateZ,
    qemu_D3DXSHScale,
    qemu_D3DXVec2BaryCentric,
    qemu_D3DXVec2CatmullRom,
    qemu_D3DXVec2Hermite,
    qemu_D3DXVec2Normalize,
    qemu_D3DXVec2Transform,
    qemu_D3DXVec2TransformArray,
    qemu_D3DXVec2TransformCoord,
    qemu_D3DXVec2TransformCoordArray,
    qemu_D3DXVec2TransformNormal,
    qemu_D3DXVec2TransformNormalArray,
    qemu_D3DXVec3BaryCentric,
    qemu_D3DXVec3CatmullRom,
    qemu_D3DXVec3Hermite,
    qemu_D3DXVec3Normalize,
    qemu_D3DXVec3Project,
    qemu_D3DXVec3ProjectArray,
    qemu_D3DXVec3Transform,
    qemu_D3DXVec3TransformArray,
    qemu_D3DXVec3TransformCoord,
    qemu_D3DXVec3TransformCoordArray,
    qemu_D3DXVec3TransformNormal,
    qemu_D3DXVec3TransformNormalArray,
    qemu_D3DXVec3Unproject,
    qemu_D3DXVec3UnprojectArray,
    qemu_D3DXVec4BaryCentric,
    qemu_D3DXVec4CatmullRom,
    qemu_D3DXVec4Cross,
    qemu_D3DXVec4Hermite,
    qemu_D3DXVec4Normalize,
    qemu_D3DXVec4Transform,
    qemu_D3DXVec4TransformArray,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side d3dx9 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
