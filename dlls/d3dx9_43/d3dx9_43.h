#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

#include "d3d9_wrapper.h"

enum d3dx9_43_calls
{
    CALL_D3DXCOLORADJUSTCONTRAST = 0,
    CALL_D3DXCOLORADJUSTSATURATION,
    CALL_D3DXCREATEMATRIXSTACK,
    CALL_D3DXFLOAT16TO32ARRAY,
    CALL_D3DXFLOAT32TO16ARRAY,
    CALL_D3DXFRESNELTERM,
    CALL_D3DXMATRIXAFFINETRANSFORMATION,
    CALL_D3DXMATRIXAFFINETRANSFORMATION2D,
    CALL_D3DXMATRIXDECOMPOSE,
    CALL_D3DXMATRIXDETERMINANT,
    CALL_D3DXMATRIXINVERSE,
    CALL_D3DXMATRIXLOOKATLH,
    CALL_D3DXMATRIXLOOKATRH,
    CALL_D3DXMATRIXMULTIPLY,
    CALL_D3DXMATRIXMULTIPLYTRANSPOSE,
    CALL_D3DXMATRIXORTHOLH,
    CALL_D3DXMATRIXORTHOOFFCENTERLH,
    CALL_D3DXMATRIXORTHOOFFCENTERRH,
    CALL_D3DXMATRIXORTHORH,
    CALL_D3DXMATRIXPERSPECTIVEFOVLH,
    CALL_D3DXMATRIXPERSPECTIVEFOVRH,
    CALL_D3DXMATRIXPERSPECTIVELH,
    CALL_D3DXMATRIXPERSPECTIVEOFFCENTERLH,
    CALL_D3DXMATRIXPERSPECTIVEOFFCENTERRH,
    CALL_D3DXMATRIXPERSPECTIVERH,
    CALL_D3DXMATRIXREFLECT,
    CALL_D3DXMATRIXROTATIONAXIS,
    CALL_D3DXMATRIXROTATIONQUATERNION,
    CALL_D3DXMATRIXROTATIONX,
    CALL_D3DXMATRIXROTATIONY,
    CALL_D3DXMATRIXROTATIONYAWPITCHROLL,
    CALL_D3DXMATRIXROTATIONZ,
    CALL_D3DXMATRIXSCALING,
    CALL_D3DXMATRIXSHADOW,
    CALL_D3DXMATRIXTRANSFORMATION,
    CALL_D3DXMATRIXTRANSFORMATION2D,
    CALL_D3DXMATRIXTRANSLATION,
    CALL_D3DXMATRIXTRANSPOSE,
    CALL_D3DXPLANEFROMPOINTNORMAL,
    CALL_D3DXPLANEFROMPOINTS,
    CALL_D3DXPLANEINTERSECTLINE,
    CALL_D3DXPLANENORMALIZE,
    CALL_D3DXPLANETRANSFORM,
    CALL_D3DXPLANETRANSFORMARRAY,
    CALL_D3DXQUATERNIONBARYCENTRIC,
    CALL_D3DXQUATERNIONEXP,
    CALL_D3DXQUATERNIONINVERSE,
    CALL_D3DXQUATERNIONLN,
    CALL_D3DXQUATERNIONMULTIPLY,
    CALL_D3DXQUATERNIONNORMALIZE,
    CALL_D3DXQUATERNIONROTATIONAXIS,
    CALL_D3DXQUATERNIONROTATIONMATRIX,
    CALL_D3DXQUATERNIONROTATIONYAWPITCHROLL,
    CALL_D3DXQUATERNIONSLERP,
    CALL_D3DXQUATERNIONSQUAD,
    CALL_D3DXQUATERNIONSQUADSETUP,
    CALL_D3DXQUATERNIONTOAXISANGLE,
    CALL_D3DXSHADD,
    CALL_D3DXSHDOT,
    CALL_D3DXSHEVALCONELIGHT,
    CALL_D3DXSHEVALDIRECTION,
    CALL_D3DXSHEVALDIRECTIONALLIGHT,
    CALL_D3DXSHEVALHEMISPHERELIGHT,
    CALL_D3DXSHEVALSPHERICALLIGHT,
    CALL_D3DXSHMULTIPLY2,
    CALL_D3DXSHMULTIPLY3,
    CALL_D3DXSHMULTIPLY4,
    CALL_D3DXSHROTATE,
    CALL_D3DXSHROTATEZ,
    CALL_D3DXSHSCALE,
    CALL_D3DXVEC2BARYCENTRIC,
    CALL_D3DXVEC2CATMULLROM,
    CALL_D3DXVEC2HERMITE,
    CALL_D3DXVEC2NORMALIZE,
    CALL_D3DXVEC2TRANSFORM,
    CALL_D3DXVEC2TRANSFORMARRAY,
    CALL_D3DXVEC2TRANSFORMCOORD,
    CALL_D3DXVEC2TRANSFORMCOORDARRAY,
    CALL_D3DXVEC2TRANSFORMNORMAL,
    CALL_D3DXVEC2TRANSFORMNORMALARRAY,
    CALL_D3DXVEC3BARYCENTRIC,
    CALL_D3DXVEC3CATMULLROM,
    CALL_D3DXVEC3HERMITE,
    CALL_D3DXVEC3NORMALIZE,
    CALL_D3DXVEC3PROJECT,
    CALL_D3DXVEC3PROJECTARRAY,
    CALL_D3DXVEC3TRANSFORM,
    CALL_D3DXVEC3TRANSFORMARRAY,
    CALL_D3DXVEC3TRANSFORMCOORD,
    CALL_D3DXVEC3TRANSFORMCOORDARRAY,
    CALL_D3DXVEC3TRANSFORMNORMAL,
    CALL_D3DXVEC3TRANSFORMNORMALARRAY,
    CALL_D3DXVEC3UNPROJECT,
    CALL_D3DXVEC3UNPROJECTARRAY,
    CALL_D3DXVEC4BARYCENTRIC,
    CALL_D3DXVEC4CATMULLROM,
    CALL_D3DXVEC4CROSS,
    CALL_D3DXVEC4HERMITE,
    CALL_D3DXVEC4NORMALIZE,
    CALL_D3DXVEC4TRANSFORM,
    CALL_D3DXVEC4TRANSFORMARRAY,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_D3DXColorAdjustContrast(struct qemu_syscall *call);
void qemu_D3DXColorAdjustSaturation(struct qemu_syscall *call);
void qemu_D3DXCreateMatrixStack(struct qemu_syscall *call);
void qemu_D3DXFloat16To32Array(struct qemu_syscall *call);
void qemu_D3DXFloat32To16Array(struct qemu_syscall *call);
void qemu_D3DXFresnelTerm(struct qemu_syscall *call);
void qemu_D3DXMatrixAffineTransformation(struct qemu_syscall *call);
void qemu_D3DXMatrixAffineTransformation2D(struct qemu_syscall *call);
void qemu_D3DXMatrixDecompose(struct qemu_syscall *call);
void qemu_D3DXMatrixDeterminant(struct qemu_syscall *call);
void qemu_D3DXMatrixInverse(struct qemu_syscall *call);
void qemu_D3DXMatrixLookAtLH(struct qemu_syscall *call);
void qemu_D3DXMatrixLookAtRH(struct qemu_syscall *call);
void qemu_D3DXMatrixMultiply(struct qemu_syscall *call);
void qemu_D3DXMatrixMultiplyTranspose(struct qemu_syscall *call);
void qemu_D3DXMatrixOrthoLH(struct qemu_syscall *call);
void qemu_D3DXMatrixOrthoOffCenterLH(struct qemu_syscall *call);
void qemu_D3DXMatrixOrthoOffCenterRH(struct qemu_syscall *call);
void qemu_D3DXMatrixOrthoRH(struct qemu_syscall *call);
void qemu_D3DXMatrixPerspectiveFovLH(struct qemu_syscall *call);
void qemu_D3DXMatrixPerspectiveFovRH(struct qemu_syscall *call);
void qemu_D3DXMatrixPerspectiveLH(struct qemu_syscall *call);
void qemu_D3DXMatrixPerspectiveOffCenterLH(struct qemu_syscall *call);
void qemu_D3DXMatrixPerspectiveOffCenterRH(struct qemu_syscall *call);
void qemu_D3DXMatrixPerspectiveRH(struct qemu_syscall *call);
void qemu_D3DXMatrixReflect(struct qemu_syscall *call);
void qemu_D3DXMatrixRotationAxis(struct qemu_syscall *call);
void qemu_D3DXMatrixRotationQuaternion(struct qemu_syscall *call);
void qemu_D3DXMatrixRotationX(struct qemu_syscall *call);
void qemu_D3DXMatrixRotationY(struct qemu_syscall *call);
void qemu_D3DXMatrixRotationYawPitchRoll(struct qemu_syscall *call);
void qemu_D3DXMatrixRotationZ(struct qemu_syscall *call);
void qemu_D3DXMatrixScaling(struct qemu_syscall *call);
void qemu_D3DXMatrixShadow(struct qemu_syscall *call);
void qemu_D3DXMatrixTransformation(struct qemu_syscall *call);
void qemu_D3DXMatrixTransformation2D(struct qemu_syscall *call);
void qemu_D3DXMatrixTranslation(struct qemu_syscall *call);
void qemu_D3DXMatrixTranspose(struct qemu_syscall *call);
void qemu_D3DXPlaneFromPointNormal(struct qemu_syscall *call);
void qemu_D3DXPlaneFromPoints(struct qemu_syscall *call);
void qemu_D3DXPlaneIntersectLine(struct qemu_syscall *call);
void qemu_D3DXPlaneNormalize(struct qemu_syscall *call);
void qemu_D3DXPlaneTransform(struct qemu_syscall *call);
void qemu_D3DXPlaneTransformArray(struct qemu_syscall *call);
void qemu_D3DXQuaternionBaryCentric(struct qemu_syscall *call);
void qemu_D3DXQuaternionExp(struct qemu_syscall *call);
void qemu_D3DXQuaternionInverse(struct qemu_syscall *call);
void qemu_D3DXQuaternionLn(struct qemu_syscall *call);
void qemu_D3DXQuaternionMultiply(struct qemu_syscall *call);
void qemu_D3DXQuaternionNormalize(struct qemu_syscall *call);
void qemu_D3DXQuaternionRotationAxis(struct qemu_syscall *call);
void qemu_D3DXQuaternionRotationMatrix(struct qemu_syscall *call);
void qemu_D3DXQuaternionRotationYawPitchRoll(struct qemu_syscall *call);
void qemu_D3DXQuaternionSlerp(struct qemu_syscall *call);
void qemu_D3DXQuaternionSquad(struct qemu_syscall *call);
void qemu_D3DXQuaternionSquadSetup(struct qemu_syscall *call);
void qemu_D3DXQuaternionToAxisAngle(struct qemu_syscall *call);
void qemu_D3DXSHAdd(struct qemu_syscall *call);
void qemu_D3DXSHDot(struct qemu_syscall *call);
void qemu_D3DXSHEvalConeLight(struct qemu_syscall *call);
void qemu_D3DXSHEvalDirection(struct qemu_syscall *call);
void qemu_D3DXSHEvalDirectionalLight(struct qemu_syscall *call);
void qemu_D3DXSHEvalHemisphereLight(struct qemu_syscall *call);
void qemu_D3DXSHEvalSphericalLight(struct qemu_syscall *call);
void qemu_D3DXSHMultiply2(struct qemu_syscall *call);
void qemu_D3DXSHMultiply3(struct qemu_syscall *call);
void qemu_D3DXSHMultiply4(struct qemu_syscall *call);
void qemu_D3DXSHRotate(struct qemu_syscall *call);
void qemu_D3DXSHRotateZ(struct qemu_syscall *call);
void qemu_D3DXSHScale(struct qemu_syscall *call);
void qemu_D3DXVec2BaryCentric(struct qemu_syscall *call);
void qemu_D3DXVec2CatmullRom(struct qemu_syscall *call);
void qemu_D3DXVec2Hermite(struct qemu_syscall *call);
void qemu_D3DXVec2Normalize(struct qemu_syscall *call);
void qemu_D3DXVec2Transform(struct qemu_syscall *call);
void qemu_D3DXVec2TransformArray(struct qemu_syscall *call);
void qemu_D3DXVec2TransformCoord(struct qemu_syscall *call);
void qemu_D3DXVec2TransformCoordArray(struct qemu_syscall *call);
void qemu_D3DXVec2TransformNormal(struct qemu_syscall *call);
void qemu_D3DXVec2TransformNormalArray(struct qemu_syscall *call);
void qemu_D3DXVec3BaryCentric(struct qemu_syscall *call);
void qemu_D3DXVec3CatmullRom(struct qemu_syscall *call);
void qemu_D3DXVec3Hermite(struct qemu_syscall *call);
void qemu_D3DXVec3Normalize(struct qemu_syscall *call);
void qemu_D3DXVec3Project(struct qemu_syscall *call);
void qemu_D3DXVec3ProjectArray(struct qemu_syscall *call);
void qemu_D3DXVec3Transform(struct qemu_syscall *call);
void qemu_D3DXVec3TransformArray(struct qemu_syscall *call);
void qemu_D3DXVec3TransformCoord(struct qemu_syscall *call);
void qemu_D3DXVec3TransformCoordArray(struct qemu_syscall *call);
void qemu_D3DXVec3TransformNormal(struct qemu_syscall *call);
void qemu_D3DXVec3TransformNormalArray(struct qemu_syscall *call);
void qemu_D3DXVec3Unproject(struct qemu_syscall *call);
void qemu_D3DXVec3UnprojectArray(struct qemu_syscall *call);
void qemu_D3DXVec4BaryCentric(struct qemu_syscall *call);
void qemu_D3DXVec4CatmullRom(struct qemu_syscall *call);
void qemu_D3DXVec4Cross(struct qemu_syscall *call);
void qemu_D3DXVec4Hermite(struct qemu_syscall *call);
void qemu_D3DXVec4Normalize(struct qemu_syscall *call);
void qemu_D3DXVec4Transform(struct qemu_syscall *call);
void qemu_D3DXVec4TransformArray(struct qemu_syscall *call);

#endif

#endif
