/* Automatically generated from http://www.opengl.org/registry files; DO NOT EDIT! */

#ifndef QEMU_DLL_GUEST
#include <windows.h>
#include <stdio.h>
#include <wine/wgl.h>
#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_opengl32.h"
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_opengl32);
const syscall_handler dll_functions[] =
{
    qemu_glAccum,
    qemu_glAlphaFunc,
    qemu_glAreTexturesResident,
    qemu_glArrayElement,
    qemu_glBegin,
    qemu_glBindTexture,
    qemu_glBitmap,
    qemu_glBlendFunc,
    qemu_glCallList,
    qemu_glCallLists,
    qemu_glClear,
    qemu_glClearAccum,
    qemu_glClearColor,
    qemu_glClearDepth,
    qemu_glClearIndex,
    qemu_glClearStencil,
    qemu_glClipPlane,
    qemu_glColor3b,
    qemu_glColor3bv,
    qemu_glColor3d,
    qemu_glColor3dv,
    qemu_glColor3f,
    qemu_glColor3fv,
    qemu_glColor3i,
    qemu_glColor3iv,
    qemu_glColor3s,
    qemu_glColor3sv,
    qemu_glColor3ub,
    qemu_glColor3ubv,
    qemu_glColor3ui,
    qemu_glColor3uiv,
    qemu_glColor3us,
    qemu_glColor3usv,
    qemu_glColor4b,
    qemu_glColor4bv,
    qemu_glColor4d,
    qemu_glColor4dv,
    qemu_glColor4f,
    qemu_glColor4fv,
    qemu_glColor4i,
    qemu_glColor4iv,
    qemu_glColor4s,
    qemu_glColor4sv,
    qemu_glColor4ub,
    qemu_glColor4ubv,
    qemu_glColor4ui,
    qemu_glColor4uiv,
    qemu_glColor4us,
    qemu_glColor4usv,
    qemu_glColorMask,
    qemu_glColorMaterial,
    qemu_glColorPointer,
    qemu_glCopyPixels,
    qemu_glCopyTexImage1D,
    qemu_glCopyTexImage2D,
    qemu_glCopyTexSubImage1D,
    qemu_glCopyTexSubImage2D,
    qemu_glCullFace,
    qemu_glDebugEntry,
    qemu_glDeleteLists,
    qemu_glDeleteTextures,
    qemu_glDepthFunc,
    qemu_glDepthMask,
    qemu_glDepthRange,
    qemu_glDisable,
    qemu_glDisableClientState,
    qemu_glDrawArrays,
    qemu_glDrawBuffer,
    qemu_glDrawElements,
    qemu_glDrawPixels,
    qemu_glEdgeFlag,
    qemu_glEdgeFlagPointer,
    qemu_glEdgeFlagv,
    qemu_glEnable,
    qemu_glEnableClientState,
    qemu_glEnd,
    qemu_glEndList,
    qemu_glEvalCoord1d,
    qemu_glEvalCoord1dv,
    qemu_glEvalCoord1f,
    qemu_glEvalCoord1fv,
    qemu_glEvalCoord2d,
    qemu_glEvalCoord2dv,
    qemu_glEvalCoord2f,
    qemu_glEvalCoord2fv,
    qemu_glEvalMesh1,
    qemu_glEvalMesh2,
    qemu_glEvalPoint1,
    qemu_glEvalPoint2,
    qemu_glFeedbackBuffer,
    qemu_glFinish,
    qemu_glFlush,
    qemu_glFogf,
    qemu_glFogfv,
    qemu_glFogi,
    qemu_glFogiv,
    qemu_glFrontFace,
    qemu_glFrustum,
    qemu_glGenLists,
    qemu_glGenTextures,
    qemu_glGetBooleanv,
    qemu_glGetClipPlane,
    qemu_glGetDoublev,
    qemu_glGetError,
    qemu_glGetFloatv,
    qemu_glGetIntegerv,
    qemu_glGetLightfv,
    qemu_glGetLightiv,
    qemu_glGetMapdv,
    qemu_glGetMapfv,
    qemu_glGetMapiv,
    qemu_glGetMaterialfv,
    qemu_glGetMaterialiv,
    qemu_glGetPixelMapfv,
    qemu_glGetPixelMapuiv,
    qemu_glGetPixelMapusv,
    qemu_glGetPointerv,
    qemu_glGetPolygonStipple,
    qemu_glGetString,
    qemu_glGetTexEnvfv,
    qemu_glGetTexEnviv,
    qemu_glGetTexGendv,
    qemu_glGetTexGenfv,
    qemu_glGetTexGeniv,
    qemu_glGetTexImage,
    qemu_glGetTexLevelParameterfv,
    qemu_glGetTexLevelParameteriv,
    qemu_glGetTexParameterfv,
    qemu_glGetTexParameteriv,
    qemu_glHint,
    qemu_glIndexMask,
    qemu_glIndexPointer,
    qemu_glIndexd,
    qemu_glIndexdv,
    qemu_glIndexf,
    qemu_glIndexfv,
    qemu_glIndexi,
    qemu_glIndexiv,
    qemu_glIndexs,
    qemu_glIndexsv,
    qemu_glIndexub,
    qemu_glIndexubv,
    qemu_glInitNames,
    qemu_glInterleavedArrays,
    qemu_glIsEnabled,
    qemu_glIsList,
    qemu_glIsTexture,
    qemu_glLightModelf,
    qemu_glLightModelfv,
    qemu_glLightModeli,
    qemu_glLightModeliv,
    qemu_glLightf,
    qemu_glLightfv,
    qemu_glLighti,
    qemu_glLightiv,
    qemu_glLineStipple,
    qemu_glLineWidth,
    qemu_glListBase,
    qemu_glLoadIdentity,
    qemu_glLoadMatrixd,
    qemu_glLoadMatrixf,
    qemu_glLoadName,
    qemu_glLogicOp,
    qemu_glMap1d,
    qemu_glMap1f,
    qemu_glMap2d,
    qemu_glMap2f,
    qemu_glMapGrid1d,
    qemu_glMapGrid1f,
    qemu_glMapGrid2d,
    qemu_glMapGrid2f,
    qemu_glMaterialf,
    qemu_glMaterialfv,
    qemu_glMateriali,
    qemu_glMaterialiv,
    qemu_glMatrixMode,
    qemu_glMultMatrixd,
    qemu_glMultMatrixf,
    qemu_glNewList,
    qemu_glNormal3b,
    qemu_glNormal3bv,
    qemu_glNormal3d,
    qemu_glNormal3dv,
    qemu_glNormal3f,
    qemu_glNormal3fv,
    qemu_glNormal3i,
    qemu_glNormal3iv,
    qemu_glNormal3s,
    qemu_glNormal3sv,
    qemu_glNormalPointer,
    qemu_glOrtho,
    qemu_glPassThrough,
    qemu_glPixelMapfv,
    qemu_glPixelMapuiv,
    qemu_glPixelMapusv,
    qemu_glPixelStoref,
    qemu_glPixelStorei,
    qemu_glPixelTransferf,
    qemu_glPixelTransferi,
    qemu_glPixelZoom,
    qemu_glPointSize,
    qemu_glPolygonMode,
    qemu_glPolygonOffset,
    qemu_glPolygonStipple,
    qemu_glPopAttrib,
    qemu_glPopClientAttrib,
    qemu_glPopMatrix,
    qemu_glPopName,
    qemu_glPrioritizeTextures,
    qemu_glPushAttrib,
    qemu_glPushClientAttrib,
    qemu_glPushMatrix,
    qemu_glPushName,
    qemu_glRasterPos2d,
    qemu_glRasterPos2dv,
    qemu_glRasterPos2f,
    qemu_glRasterPos2fv,
    qemu_glRasterPos2i,
    qemu_glRasterPos2iv,
    qemu_glRasterPos2s,
    qemu_glRasterPos2sv,
    qemu_glRasterPos3d,
    qemu_glRasterPos3dv,
    qemu_glRasterPos3f,
    qemu_glRasterPos3fv,
    qemu_glRasterPos3i,
    qemu_glRasterPos3iv,
    qemu_glRasterPos3s,
    qemu_glRasterPos3sv,
    qemu_glRasterPos4d,
    qemu_glRasterPos4dv,
    qemu_glRasterPos4f,
    qemu_glRasterPos4fv,
    qemu_glRasterPos4i,
    qemu_glRasterPos4iv,
    qemu_glRasterPos4s,
    qemu_glRasterPos4sv,
    qemu_glReadBuffer,
    qemu_glReadPixels,
    qemu_glRectd,
    qemu_glRectdv,
    qemu_glRectf,
    qemu_glRectfv,
    qemu_glRecti,
    qemu_glRectiv,
    qemu_glRects,
    qemu_glRectsv,
    qemu_glRenderMode,
    qemu_glRotated,
    qemu_glRotatef,
    qemu_glScaled,
    qemu_glScalef,
    qemu_glScissor,
    qemu_glSelectBuffer,
    qemu_glShadeModel,
    qemu_glStencilFunc,
    qemu_glStencilMask,
    qemu_glStencilOp,
    qemu_glTexCoord1d,
    qemu_glTexCoord1dv,
    qemu_glTexCoord1f,
    qemu_glTexCoord1fv,
    qemu_glTexCoord1i,
    qemu_glTexCoord1iv,
    qemu_glTexCoord1s,
    qemu_glTexCoord1sv,
    qemu_glTexCoord2d,
    qemu_glTexCoord2dv,
    qemu_glTexCoord2f,
    qemu_glTexCoord2fv,
    qemu_glTexCoord2i,
    qemu_glTexCoord2iv,
    qemu_glTexCoord2s,
    qemu_glTexCoord2sv,
    qemu_glTexCoord3d,
    qemu_glTexCoord3dv,
    qemu_glTexCoord3f,
    qemu_glTexCoord3fv,
    qemu_glTexCoord3i,
    qemu_glTexCoord3iv,
    qemu_glTexCoord3s,
    qemu_glTexCoord3sv,
    qemu_glTexCoord4d,
    qemu_glTexCoord4dv,
    qemu_glTexCoord4f,
    qemu_glTexCoord4fv,
    qemu_glTexCoord4i,
    qemu_glTexCoord4iv,
    qemu_glTexCoord4s,
    qemu_glTexCoord4sv,
    qemu_glTexCoordPointer,
    qemu_glTexEnvf,
    qemu_glTexEnvfv,
    qemu_glTexEnvi,
    qemu_glTexEnviv,
    qemu_glTexGend,
    qemu_glTexGendv,
    qemu_glTexGenf,
    qemu_glTexGenfv,
    qemu_glTexGeni,
    qemu_glTexGeniv,
    qemu_glTexImage1D,
    qemu_glTexImage2D,
    qemu_glTexParameterf,
    qemu_glTexParameterfv,
    qemu_glTexParameteri,
    qemu_glTexParameteriv,
    qemu_glTexSubImage1D,
    qemu_glTexSubImage2D,
    qemu_glTranslated,
    qemu_glTranslatef,
    qemu_glVertex2d,
    qemu_glVertex2dv,
    qemu_glVertex2f,
    qemu_glVertex2fv,
    qemu_glVertex2i,
    qemu_glVertex2iv,
    qemu_glVertex2s,
    qemu_glVertex2sv,
    qemu_glVertex3d,
    qemu_glVertex3dv,
    qemu_glVertex3f,
    qemu_glVertex3fv,
    qemu_glVertex3i,
    qemu_glVertex3iv,
    qemu_glVertex3s,
    qemu_glVertex3sv,
    qemu_glVertex4d,
    qemu_glVertex4dv,
    qemu_glVertex4f,
    qemu_glVertex4fv,
    qemu_glVertex4i,
    qemu_glVertex4iv,
    qemu_glVertex4s,
    qemu_glVertex4sv,
    qemu_glVertexPointer,
    qemu_glViewport,
    qemu_glAccumxOES,
    qemu_glAcquireKeyedMutexWin32EXT,
    qemu_glActiveProgramEXT,
    qemu_glActiveShaderProgram,
    qemu_glActiveStencilFaceEXT,
    qemu_glActiveTexture,
    qemu_glActiveTextureARB,
    qemu_glActiveVaryingNV,
    qemu_glAlphaFragmentOp1ATI,
    qemu_glAlphaFragmentOp2ATI,
    qemu_glAlphaFragmentOp3ATI,
    qemu_glAlphaFuncxOES,
    qemu_glAlphaToCoverageDitherControlNV,
    qemu_glApplyFramebufferAttachmentCMAAINTEL,
    qemu_glApplyTextureEXT,
    qemu_glAreProgramsResidentNV,
    qemu_glAreTexturesResidentEXT,
    qemu_glArrayElementEXT,
    qemu_glArrayObjectATI,
    qemu_glAsyncCopyBufferSubDataNVX,
    qemu_glAsyncCopyImageSubDataNVX,
    qemu_glAsyncMarkerSGIX,
    qemu_glAttachObjectARB,
    qemu_glAttachShader,
    qemu_glBeginConditionalRender,
    qemu_glBeginConditionalRenderNV,
    qemu_glBeginConditionalRenderNVX,
    qemu_glBeginFragmentShaderATI,
    qemu_glBeginOcclusionQueryNV,
    qemu_glBeginPerfMonitorAMD,
    qemu_glBeginPerfQueryINTEL,
    qemu_glBeginQuery,
    qemu_glBeginQueryARB,
    qemu_glBeginQueryIndexed,
    qemu_glBeginTransformFeedback,
    qemu_glBeginTransformFeedbackEXT,
    qemu_glBeginTransformFeedbackNV,
    qemu_glBeginVertexShaderEXT,
    qemu_glBeginVideoCaptureNV,
    qemu_glBindAttribLocation,
    qemu_glBindAttribLocationARB,
    qemu_glBindBuffer,
    qemu_glBindBufferARB,
    qemu_glBindBufferBase,
    qemu_glBindBufferBaseEXT,
    qemu_glBindBufferBaseNV,
    qemu_glBindBufferOffsetEXT,
    qemu_glBindBufferOffsetNV,
    qemu_glBindBufferRange,
    qemu_glBindBufferRangeEXT,
    qemu_glBindBufferRangeNV,
    qemu_glBindBuffersBase,
    qemu_glBindBuffersRange,
    qemu_glBindFragDataLocation,
    qemu_glBindFragDataLocationEXT,
    qemu_glBindFragDataLocationIndexed,
    qemu_glBindFragmentShaderATI,
    qemu_glBindFramebuffer,
    qemu_glBindFramebufferEXT,
    qemu_glBindImageTexture,
    qemu_glBindImageTextureEXT,
    qemu_glBindImageTextures,
    qemu_glBindLightParameterEXT,
    qemu_glBindMaterialParameterEXT,
    qemu_glBindMultiTextureEXT,
    qemu_glBindParameterEXT,
    qemu_glBindProgramARB,
    qemu_glBindProgramNV,
    qemu_glBindProgramPipeline,
    qemu_glBindRenderbuffer,
    qemu_glBindRenderbufferEXT,
    qemu_glBindSampler,
    qemu_glBindSamplers,
    qemu_glBindShadingRateImageNV,
    qemu_glBindTexGenParameterEXT,
    qemu_glBindTextureEXT,
    qemu_glBindTextureUnit,
    qemu_glBindTextureUnitParameterEXT,
    qemu_glBindTextures,
    qemu_glBindTransformFeedback,
    qemu_glBindTransformFeedbackNV,
    qemu_glBindVertexArray,
    qemu_glBindVertexArrayAPPLE,
    qemu_glBindVertexBuffer,
    qemu_glBindVertexBuffers,
    qemu_glBindVertexShaderEXT,
    qemu_glBindVideoCaptureStreamBufferNV,
    qemu_glBindVideoCaptureStreamTextureNV,
    qemu_glBinormal3bEXT,
    qemu_glBinormal3bvEXT,
    qemu_glBinormal3dEXT,
    qemu_glBinormal3dvEXT,
    qemu_glBinormal3fEXT,
    qemu_glBinormal3fvEXT,
    qemu_glBinormal3iEXT,
    qemu_glBinormal3ivEXT,
    qemu_glBinormal3sEXT,
    qemu_glBinormal3svEXT,
    qemu_glBinormalPointerEXT,
    qemu_glBitmapxOES,
    qemu_glBlendBarrierKHR,
    qemu_glBlendBarrierNV,
    qemu_glBlendColor,
    qemu_glBlendColorEXT,
    qemu_glBlendColorxOES,
    qemu_glBlendEquation,
    qemu_glBlendEquationEXT,
    qemu_glBlendEquationIndexedAMD,
    qemu_glBlendEquationSeparate,
    qemu_glBlendEquationSeparateEXT,
    qemu_glBlendEquationSeparateIndexedAMD,
    qemu_glBlendEquationSeparatei,
    qemu_glBlendEquationSeparateiARB,
    qemu_glBlendEquationi,
    qemu_glBlendEquationiARB,
    qemu_glBlendFuncIndexedAMD,
    qemu_glBlendFuncSeparate,
    qemu_glBlendFuncSeparateEXT,
    qemu_glBlendFuncSeparateINGR,
    qemu_glBlendFuncSeparateIndexedAMD,
    qemu_glBlendFuncSeparatei,
    qemu_glBlendFuncSeparateiARB,
    qemu_glBlendFunci,
    qemu_glBlendFunciARB,
    qemu_glBlendParameteriNV,
    qemu_glBlitFramebuffer,
    qemu_glBlitFramebufferEXT,
    qemu_glBlitNamedFramebuffer,
    qemu_glBufferAddressRangeNV,
    qemu_glBufferAttachMemoryNV,
    qemu_glBufferData,
    qemu_glBufferDataARB,
    qemu_glBufferPageCommitmentARB,
    qemu_glBufferParameteriAPPLE,
    qemu_glBufferRegionEnabled,
    qemu_glBufferStorage,
    qemu_glBufferStorageExternalEXT,
    qemu_glBufferStorageMemEXT,
    qemu_glBufferSubData,
    qemu_glBufferSubDataARB,
    qemu_glCallCommandListNV,
    qemu_glCheckFramebufferStatus,
    qemu_glCheckFramebufferStatusEXT,
    qemu_glCheckNamedFramebufferStatus,
    qemu_glCheckNamedFramebufferStatusEXT,
    qemu_glClampColor,
    qemu_glClampColorARB,
    qemu_glClearAccumxOES,
    qemu_glClearBufferData,
    qemu_glClearBufferSubData,
    qemu_glClearBufferfi,
    qemu_glClearBufferfv,
    qemu_glClearBufferiv,
    qemu_glClearBufferuiv,
    qemu_glClearColorIiEXT,
    qemu_glClearColorIuiEXT,
    qemu_glClearColorxOES,
    qemu_glClearDepthdNV,
    qemu_glClearDepthf,
    qemu_glClearDepthfOES,
    qemu_glClearDepthxOES,
    qemu_glClearNamedBufferData,
    qemu_glClearNamedBufferDataEXT,
    qemu_glClearNamedBufferSubData,
    qemu_glClearNamedBufferSubDataEXT,
    qemu_glClearNamedFramebufferfi,
    qemu_glClearNamedFramebufferfv,
    qemu_glClearNamedFramebufferiv,
    qemu_glClearNamedFramebufferuiv,
    qemu_glClearTexImage,
    qemu_glClearTexSubImage,
    qemu_glClientActiveTexture,
    qemu_glClientActiveTextureARB,
    qemu_glClientActiveVertexStreamATI,
    qemu_glClientAttribDefaultEXT,
    qemu_glClientWaitSemaphoreui64NVX,
    qemu_glClientWaitSync,
    qemu_glClipControl,
    qemu_glClipPlanefOES,
    qemu_glClipPlanexOES,
    qemu_glColor3fVertex3fSUN,
    qemu_glColor3fVertex3fvSUN,
    qemu_glColor3hNV,
    qemu_glColor3hvNV,
    qemu_glColor3xOES,
    qemu_glColor3xvOES,
    qemu_glColor4fNormal3fVertex3fSUN,
    qemu_glColor4fNormal3fVertex3fvSUN,
    qemu_glColor4hNV,
    qemu_glColor4hvNV,
    qemu_glColor4ubVertex2fSUN,
    qemu_glColor4ubVertex2fvSUN,
    qemu_glColor4ubVertex3fSUN,
    qemu_glColor4ubVertex3fvSUN,
    qemu_glColor4xOES,
    qemu_glColor4xvOES,
    qemu_glColorFormatNV,
    qemu_glColorFragmentOp1ATI,
    qemu_glColorFragmentOp2ATI,
    qemu_glColorFragmentOp3ATI,
    qemu_glColorMaskIndexedEXT,
    qemu_glColorMaski,
    qemu_glColorP3ui,
    qemu_glColorP3uiv,
    qemu_glColorP4ui,
    qemu_glColorP4uiv,
    qemu_glColorPointerEXT,
    qemu_glColorPointerListIBM,
    qemu_glColorPointervINTEL,
    qemu_glColorSubTable,
    qemu_glColorSubTableEXT,
    qemu_glColorTable,
    qemu_glColorTableEXT,
    qemu_glColorTableParameterfv,
    qemu_glColorTableParameterfvSGI,
    qemu_glColorTableParameteriv,
    qemu_glColorTableParameterivSGI,
    qemu_glColorTableSGI,
    qemu_glCombinerInputNV,
    qemu_glCombinerOutputNV,
    qemu_glCombinerParameterfNV,
    qemu_glCombinerParameterfvNV,
    qemu_glCombinerParameteriNV,
    qemu_glCombinerParameterivNV,
    qemu_glCombinerStageParameterfvNV,
    qemu_glCommandListSegmentsNV,
    qemu_glCompileCommandListNV,
    qemu_glCompileShader,
    qemu_glCompileShaderARB,
    qemu_glCompileShaderIncludeARB,
    qemu_glCompressedMultiTexImage1DEXT,
    qemu_glCompressedMultiTexImage2DEXT,
    qemu_glCompressedMultiTexImage3DEXT,
    qemu_glCompressedMultiTexSubImage1DEXT,
    qemu_glCompressedMultiTexSubImage2DEXT,
    qemu_glCompressedMultiTexSubImage3DEXT,
    qemu_glCompressedTexImage1D,
    qemu_glCompressedTexImage1DARB,
    qemu_glCompressedTexImage2D,
    qemu_glCompressedTexImage2DARB,
    qemu_glCompressedTexImage3D,
    qemu_glCompressedTexImage3DARB,
    qemu_glCompressedTexSubImage1D,
    qemu_glCompressedTexSubImage1DARB,
    qemu_glCompressedTexSubImage2D,
    qemu_glCompressedTexSubImage2DARB,
    qemu_glCompressedTexSubImage3D,
    qemu_glCompressedTexSubImage3DARB,
    qemu_glCompressedTextureImage1DEXT,
    qemu_glCompressedTextureImage2DEXT,
    qemu_glCompressedTextureImage3DEXT,
    qemu_glCompressedTextureSubImage1D,
    qemu_glCompressedTextureSubImage1DEXT,
    qemu_glCompressedTextureSubImage2D,
    qemu_glCompressedTextureSubImage2DEXT,
    qemu_glCompressedTextureSubImage3D,
    qemu_glCompressedTextureSubImage3DEXT,
    qemu_glConservativeRasterParameterfNV,
    qemu_glConservativeRasterParameteriNV,
    qemu_glConvolutionFilter1D,
    qemu_glConvolutionFilter1DEXT,
    qemu_glConvolutionFilter2D,
    qemu_glConvolutionFilter2DEXT,
    qemu_glConvolutionParameterf,
    qemu_glConvolutionParameterfEXT,
    qemu_glConvolutionParameterfv,
    qemu_glConvolutionParameterfvEXT,
    qemu_glConvolutionParameteri,
    qemu_glConvolutionParameteriEXT,
    qemu_glConvolutionParameteriv,
    qemu_glConvolutionParameterivEXT,
    qemu_glConvolutionParameterxOES,
    qemu_glConvolutionParameterxvOES,
    qemu_glCopyBufferSubData,
    qemu_glCopyColorSubTable,
    qemu_glCopyColorSubTableEXT,
    qemu_glCopyColorTable,
    qemu_glCopyColorTableSGI,
    qemu_glCopyConvolutionFilter1D,
    qemu_glCopyConvolutionFilter1DEXT,
    qemu_glCopyConvolutionFilter2D,
    qemu_glCopyConvolutionFilter2DEXT,
    qemu_glCopyImageSubData,
    qemu_glCopyImageSubDataNV,
    qemu_glCopyMultiTexImage1DEXT,
    qemu_glCopyMultiTexImage2DEXT,
    qemu_glCopyMultiTexSubImage1DEXT,
    qemu_glCopyMultiTexSubImage2DEXT,
    qemu_glCopyMultiTexSubImage3DEXT,
    qemu_glCopyNamedBufferSubData,
    qemu_glCopyPathNV,
    qemu_glCopyTexImage1DEXT,
    qemu_glCopyTexImage2DEXT,
    qemu_glCopyTexSubImage1DEXT,
    qemu_glCopyTexSubImage2DEXT,
    qemu_glCopyTexSubImage3D,
    qemu_glCopyTexSubImage3DEXT,
    qemu_glCopyTextureImage1DEXT,
    qemu_glCopyTextureImage2DEXT,
    qemu_glCopyTextureSubImage1D,
    qemu_glCopyTextureSubImage1DEXT,
    qemu_glCopyTextureSubImage2D,
    qemu_glCopyTextureSubImage2DEXT,
    qemu_glCopyTextureSubImage3D,
    qemu_glCopyTextureSubImage3DEXT,
    qemu_glCoverFillPathInstancedNV,
    qemu_glCoverFillPathNV,
    qemu_glCoverStrokePathInstancedNV,
    qemu_glCoverStrokePathNV,
    qemu_glCoverageModulationNV,
    qemu_glCoverageModulationTableNV,
    qemu_glCreateBuffers,
    qemu_glCreateCommandListsNV,
    qemu_glCreateFramebuffers,
    qemu_glCreateMemoryObjectsEXT,
    qemu_glCreatePerfQueryINTEL,
    qemu_glCreateProgram,
    qemu_glCreateProgramObjectARB,
    qemu_glCreateProgramPipelines,
    qemu_glCreateProgressFenceNVX,
    qemu_glCreateQueries,
    qemu_glCreateRenderbuffers,
    qemu_glCreateSamplers,
    qemu_glCreateShader,
    qemu_glCreateShaderObjectARB,
    qemu_glCreateShaderProgramEXT,
    qemu_glCreateShaderProgramv,
    qemu_glCreateStatesNV,
    qemu_glCreateSyncFromCLeventARB,
    qemu_glCreateTextures,
    qemu_glCreateTransformFeedbacks,
    qemu_glCreateVertexArrays,
    qemu_glCullParameterdvEXT,
    qemu_glCullParameterfvEXT,
    qemu_glCurrentPaletteMatrixARB,
    qemu_glDebugMessageCallback,
    qemu_glDebugMessageCallbackAMD,
    qemu_glDebugMessageCallbackARB,
    qemu_glDebugMessageControl,
    qemu_glDebugMessageControlARB,
    qemu_glDebugMessageEnableAMD,
    qemu_glDebugMessageInsert,
    qemu_glDebugMessageInsertAMD,
    qemu_glDebugMessageInsertARB,
    qemu_glDeformSGIX,
    qemu_glDeformationMap3dSGIX,
    qemu_glDeformationMap3fSGIX,
    qemu_glDeleteAsyncMarkersSGIX,
    qemu_glDeleteBufferRegion,
    qemu_glDeleteBuffers,
    qemu_glDeleteBuffersARB,
    qemu_glDeleteCommandListsNV,
    qemu_glDeleteFencesAPPLE,
    qemu_glDeleteFencesNV,
    qemu_glDeleteFragmentShaderATI,
    qemu_glDeleteFramebuffers,
    qemu_glDeleteFramebuffersEXT,
    qemu_glDeleteMemoryObjectsEXT,
    qemu_glDeleteNamedStringARB,
    qemu_glDeleteNamesAMD,
    qemu_glDeleteObjectARB,
    qemu_glDeleteObjectBufferATI,
    qemu_glDeleteOcclusionQueriesNV,
    qemu_glDeletePathsNV,
    qemu_glDeletePerfMonitorsAMD,
    qemu_glDeletePerfQueryINTEL,
    qemu_glDeleteProgram,
    qemu_glDeleteProgramPipelines,
    qemu_glDeleteProgramsARB,
    qemu_glDeleteProgramsNV,
    qemu_glDeleteQueries,
    qemu_glDeleteQueriesARB,
    qemu_glDeleteQueryResourceTagNV,
    qemu_glDeleteRenderbuffers,
    qemu_glDeleteRenderbuffersEXT,
    qemu_glDeleteSamplers,
    qemu_glDeleteSemaphoresEXT,
    qemu_glDeleteShader,
    qemu_glDeleteStatesNV,
    qemu_glDeleteSync,
    qemu_glDeleteTexturesEXT,
    qemu_glDeleteTransformFeedbacks,
    qemu_glDeleteTransformFeedbacksNV,
    qemu_glDeleteVertexArrays,
    qemu_glDeleteVertexArraysAPPLE,
    qemu_glDeleteVertexShaderEXT,
    qemu_glDepthBoundsEXT,
    qemu_glDepthBoundsdNV,
    qemu_glDepthRangeArraydvNV,
    qemu_glDepthRangeArrayv,
    qemu_glDepthRangeIndexed,
    qemu_glDepthRangeIndexeddNV,
    qemu_glDepthRangedNV,
    qemu_glDepthRangef,
    qemu_glDepthRangefOES,
    qemu_glDepthRangexOES,
    qemu_glDetachObjectARB,
    qemu_glDetachShader,
    qemu_glDetailTexFuncSGIS,
    qemu_glDisableClientStateIndexedEXT,
    qemu_glDisableClientStateiEXT,
    qemu_glDisableIndexedEXT,
    qemu_glDisableVariantClientStateEXT,
    qemu_glDisableVertexArrayAttrib,
    qemu_glDisableVertexArrayAttribEXT,
    qemu_glDisableVertexArrayEXT,
    qemu_glDisableVertexAttribAPPLE,
    qemu_glDisableVertexAttribArray,
    qemu_glDisableVertexAttribArrayARB,
    qemu_glDisablei,
    qemu_glDispatchCompute,
    qemu_glDispatchComputeGroupSizeARB,
    qemu_glDispatchComputeIndirect,
    qemu_glDrawArraysEXT,
    qemu_glDrawArraysIndirect,
    qemu_glDrawArraysInstanced,
    qemu_glDrawArraysInstancedARB,
    qemu_glDrawArraysInstancedBaseInstance,
    qemu_glDrawArraysInstancedEXT,
    qemu_glDrawBufferRegion,
    qemu_glDrawBuffers,
    qemu_glDrawBuffersARB,
    qemu_glDrawBuffersATI,
    qemu_glDrawCommandsAddressNV,
    qemu_glDrawCommandsNV,
    qemu_glDrawCommandsStatesAddressNV,
    qemu_glDrawCommandsStatesNV,
    qemu_glDrawElementArrayAPPLE,
    qemu_glDrawElementArrayATI,
    qemu_glDrawElementsBaseVertex,
    qemu_glDrawElementsIndirect,
    qemu_glDrawElementsInstanced,
    qemu_glDrawElementsInstancedARB,
    qemu_glDrawElementsInstancedBaseInstance,
    qemu_glDrawElementsInstancedBaseVertex,
    qemu_glDrawElementsInstancedBaseVertexBaseInstance,
    qemu_glDrawElementsInstancedEXT,
    qemu_glDrawMeshArraysSUN,
    qemu_glDrawMeshTasksIndirectNV,
    qemu_glDrawMeshTasksNV,
    qemu_glDrawRangeElementArrayAPPLE,
    qemu_glDrawRangeElementArrayATI,
    qemu_glDrawRangeElements,
    qemu_glDrawRangeElementsBaseVertex,
    qemu_glDrawRangeElementsEXT,
    qemu_glDrawTextureNV,
    qemu_glDrawTransformFeedback,
    qemu_glDrawTransformFeedbackInstanced,
    qemu_glDrawTransformFeedbackNV,
    qemu_glDrawTransformFeedbackStream,
    qemu_glDrawTransformFeedbackStreamInstanced,
    qemu_glDrawVkImageNV,
    qemu_glEGLImageTargetTexStorageEXT,
    qemu_glEGLImageTargetTextureStorageEXT,
    qemu_glEdgeFlagFormatNV,
    qemu_glEdgeFlagPointerEXT,
    qemu_glEdgeFlagPointerListIBM,
    qemu_glElementPointerAPPLE,
    qemu_glElementPointerATI,
    qemu_glEnableClientStateIndexedEXT,
    qemu_glEnableClientStateiEXT,
    qemu_glEnableIndexedEXT,
    qemu_glEnableVariantClientStateEXT,
    qemu_glEnableVertexArrayAttrib,
    qemu_glEnableVertexArrayAttribEXT,
    qemu_glEnableVertexArrayEXT,
    qemu_glEnableVertexAttribAPPLE,
    qemu_glEnableVertexAttribArray,
    qemu_glEnableVertexAttribArrayARB,
    qemu_glEnablei,
    qemu_glEndConditionalRender,
    qemu_glEndConditionalRenderNV,
    qemu_glEndConditionalRenderNVX,
    qemu_glEndFragmentShaderATI,
    qemu_glEndOcclusionQueryNV,
    qemu_glEndPerfMonitorAMD,
    qemu_glEndPerfQueryINTEL,
    qemu_glEndQuery,
    qemu_glEndQueryARB,
    qemu_glEndQueryIndexed,
    qemu_glEndTransformFeedback,
    qemu_glEndTransformFeedbackEXT,
    qemu_glEndTransformFeedbackNV,
    qemu_glEndVertexShaderEXT,
    qemu_glEndVideoCaptureNV,
    qemu_glEvalCoord1xOES,
    qemu_glEvalCoord1xvOES,
    qemu_glEvalCoord2xOES,
    qemu_glEvalCoord2xvOES,
    qemu_glEvalMapsNV,
    qemu_glEvaluateDepthValuesARB,
    qemu_glExecuteProgramNV,
    qemu_glExtractComponentEXT,
    qemu_glFeedbackBufferxOES,
    qemu_glFenceSync,
    qemu_glFinalCombinerInputNV,
    qemu_glFinishAsyncSGIX,
    qemu_glFinishFenceAPPLE,
    qemu_glFinishFenceNV,
    qemu_glFinishObjectAPPLE,
    qemu_glFinishTextureSUNX,
    qemu_glFlushMappedBufferRange,
    qemu_glFlushMappedBufferRangeAPPLE,
    qemu_glFlushMappedNamedBufferRange,
    qemu_glFlushMappedNamedBufferRangeEXT,
    qemu_glFlushPixelDataRangeNV,
    qemu_glFlushRasterSGIX,
    qemu_glFlushStaticDataIBM,
    qemu_glFlushVertexArrayRangeAPPLE,
    qemu_glFlushVertexArrayRangeNV,
    qemu_glFogCoordFormatNV,
    qemu_glFogCoordPointer,
    qemu_glFogCoordPointerEXT,
    qemu_glFogCoordPointerListIBM,
    qemu_glFogCoordd,
    qemu_glFogCoorddEXT,
    qemu_glFogCoorddv,
    qemu_glFogCoorddvEXT,
    qemu_glFogCoordf,
    qemu_glFogCoordfEXT,
    qemu_glFogCoordfv,
    qemu_glFogCoordfvEXT,
    qemu_glFogCoordhNV,
    qemu_glFogCoordhvNV,
    qemu_glFogFuncSGIS,
    qemu_glFogxOES,
    qemu_glFogxvOES,
    qemu_glFragmentColorMaterialSGIX,
    qemu_glFragmentCoverageColorNV,
    qemu_glFragmentLightModelfSGIX,
    qemu_glFragmentLightModelfvSGIX,
    qemu_glFragmentLightModeliSGIX,
    qemu_glFragmentLightModelivSGIX,
    qemu_glFragmentLightfSGIX,
    qemu_glFragmentLightfvSGIX,
    qemu_glFragmentLightiSGIX,
    qemu_glFragmentLightivSGIX,
    qemu_glFragmentMaterialfSGIX,
    qemu_glFragmentMaterialfvSGIX,
    qemu_glFragmentMaterialiSGIX,
    qemu_glFragmentMaterialivSGIX,
    qemu_glFrameTerminatorGREMEDY,
    qemu_glFrameZoomSGIX,
    qemu_glFramebufferDrawBufferEXT,
    qemu_glFramebufferDrawBuffersEXT,
    qemu_glFramebufferFetchBarrierEXT,
    qemu_glFramebufferParameteri,
    qemu_glFramebufferParameteriMESA,
    qemu_glFramebufferReadBufferEXT,
    qemu_glFramebufferRenderbuffer,
    qemu_glFramebufferRenderbufferEXT,
    qemu_glFramebufferSampleLocationsfvARB,
    qemu_glFramebufferSampleLocationsfvNV,
    qemu_glFramebufferSamplePositionsfvAMD,
    qemu_glFramebufferTexture,
    qemu_glFramebufferTexture1D,
    qemu_glFramebufferTexture1DEXT,
    qemu_glFramebufferTexture2D,
    qemu_glFramebufferTexture2DEXT,
    qemu_glFramebufferTexture3D,
    qemu_glFramebufferTexture3DEXT,
    qemu_glFramebufferTextureARB,
    qemu_glFramebufferTextureEXT,
    qemu_glFramebufferTextureFaceARB,
    qemu_glFramebufferTextureFaceEXT,
    qemu_glFramebufferTextureLayer,
    qemu_glFramebufferTextureLayerARB,
    qemu_glFramebufferTextureLayerEXT,
    qemu_glFramebufferTextureMultiviewOVR,
    qemu_glFreeObjectBufferATI,
    qemu_glFrustumfOES,
    qemu_glFrustumxOES,
    qemu_glGenAsyncMarkersSGIX,
    qemu_glGenBuffers,
    qemu_glGenBuffersARB,
    qemu_glGenFencesAPPLE,
    qemu_glGenFencesNV,
    qemu_glGenFragmentShadersATI,
    qemu_glGenFramebuffers,
    qemu_glGenFramebuffersEXT,
    qemu_glGenNamesAMD,
    qemu_glGenOcclusionQueriesNV,
    qemu_glGenPathsNV,
    qemu_glGenPerfMonitorsAMD,
    qemu_glGenProgramPipelines,
    qemu_glGenProgramsARB,
    qemu_glGenProgramsNV,
    qemu_glGenQueries,
    qemu_glGenQueriesARB,
    qemu_glGenQueryResourceTagNV,
    qemu_glGenRenderbuffers,
    qemu_glGenRenderbuffersEXT,
    qemu_glGenSamplers,
    qemu_glGenSemaphoresEXT,
    qemu_glGenSymbolsEXT,
    qemu_glGenTexturesEXT,
    qemu_glGenTransformFeedbacks,
    qemu_glGenTransformFeedbacksNV,
    qemu_glGenVertexArrays,
    qemu_glGenVertexArraysAPPLE,
    qemu_glGenVertexShadersEXT,
    qemu_glGenerateMipmap,
    qemu_glGenerateMipmapEXT,
    qemu_glGenerateMultiTexMipmapEXT,
    qemu_glGenerateTextureMipmap,
    qemu_glGenerateTextureMipmapEXT,
    qemu_glGetActiveAtomicCounterBufferiv,
    qemu_glGetActiveAttrib,
    qemu_glGetActiveAttribARB,
    qemu_glGetActiveSubroutineName,
    qemu_glGetActiveSubroutineUniformName,
    qemu_glGetActiveSubroutineUniformiv,
    qemu_glGetActiveUniform,
    qemu_glGetActiveUniformARB,
    qemu_glGetActiveUniformBlockName,
    qemu_glGetActiveUniformBlockiv,
    qemu_glGetActiveUniformName,
    qemu_glGetActiveUniformsiv,
    qemu_glGetActiveVaryingNV,
    qemu_glGetArrayObjectfvATI,
    qemu_glGetArrayObjectivATI,
    qemu_glGetAttachedObjectsARB,
    qemu_glGetAttachedShaders,
    qemu_glGetAttribLocation,
    qemu_glGetAttribLocationARB,
    qemu_glGetBooleanIndexedvEXT,
    qemu_glGetBooleani_v,
    qemu_glGetBufferParameteri64v,
    qemu_glGetBufferParameteriv,
    qemu_glGetBufferParameterivARB,
    qemu_glGetBufferParameterui64vNV,
    qemu_glGetBufferPointerv,
    qemu_glGetBufferPointervARB,
    qemu_glGetBufferSubData,
    qemu_glGetBufferSubDataARB,
    qemu_glGetClipPlanefOES,
    qemu_glGetClipPlanexOES,
    qemu_glGetColorTable,
    qemu_glGetColorTableEXT,
    qemu_glGetColorTableParameterfv,
    qemu_glGetColorTableParameterfvEXT,
    qemu_glGetColorTableParameterfvSGI,
    qemu_glGetColorTableParameteriv,
    qemu_glGetColorTableParameterivEXT,
    qemu_glGetColorTableParameterivSGI,
    qemu_glGetColorTableSGI,
    qemu_glGetCombinerInputParameterfvNV,
    qemu_glGetCombinerInputParameterivNV,
    qemu_glGetCombinerOutputParameterfvNV,
    qemu_glGetCombinerOutputParameterivNV,
    qemu_glGetCombinerStageParameterfvNV,
    qemu_glGetCommandHeaderNV,
    qemu_glGetCompressedMultiTexImageEXT,
    qemu_glGetCompressedTexImage,
    qemu_glGetCompressedTexImageARB,
    qemu_glGetCompressedTextureImage,
    qemu_glGetCompressedTextureImageEXT,
    qemu_glGetCompressedTextureSubImage,
    qemu_glGetConvolutionFilter,
    qemu_glGetConvolutionFilterEXT,
    qemu_glGetConvolutionParameterfv,
    qemu_glGetConvolutionParameterfvEXT,
    qemu_glGetConvolutionParameteriv,
    qemu_glGetConvolutionParameterivEXT,
    qemu_glGetConvolutionParameterxvOES,
    qemu_glGetCoverageModulationTableNV,
    qemu_glGetDebugMessageLog,
    qemu_glGetDebugMessageLogAMD,
    qemu_glGetDebugMessageLogARB,
    qemu_glGetDetailTexFuncSGIS,
    qemu_glGetDoubleIndexedvEXT,
    qemu_glGetDoublei_v,
    qemu_glGetDoublei_vEXT,
    qemu_glGetFenceivNV,
    qemu_glGetFinalCombinerInputParameterfvNV,
    qemu_glGetFinalCombinerInputParameterivNV,
    qemu_glGetFirstPerfQueryIdINTEL,
    qemu_glGetFixedvOES,
    qemu_glGetFloatIndexedvEXT,
    qemu_glGetFloati_v,
    qemu_glGetFloati_vEXT,
    qemu_glGetFogFuncSGIS,
    qemu_glGetFragDataIndex,
    qemu_glGetFragDataLocation,
    qemu_glGetFragDataLocationEXT,
    qemu_glGetFragmentLightfvSGIX,
    qemu_glGetFragmentLightivSGIX,
    qemu_glGetFragmentMaterialfvSGIX,
    qemu_glGetFragmentMaterialivSGIX,
    qemu_glGetFramebufferAttachmentParameteriv,
    qemu_glGetFramebufferAttachmentParameterivEXT,
    qemu_glGetFramebufferParameterfvAMD,
    qemu_glGetFramebufferParameteriv,
    qemu_glGetFramebufferParameterivEXT,
    qemu_glGetFramebufferParameterivMESA,
    qemu_glGetGraphicsResetStatus,
    qemu_glGetGraphicsResetStatusARB,
    qemu_glGetHandleARB,
    qemu_glGetHistogram,
    qemu_glGetHistogramEXT,
    qemu_glGetHistogramParameterfv,
    qemu_glGetHistogramParameterfvEXT,
    qemu_glGetHistogramParameteriv,
    qemu_glGetHistogramParameterivEXT,
    qemu_glGetHistogramParameterxvOES,
    qemu_glGetImageHandleARB,
    qemu_glGetImageHandleNV,
    qemu_glGetImageTransformParameterfvHP,
    qemu_glGetImageTransformParameterivHP,
    qemu_glGetInfoLogARB,
    qemu_glGetInstrumentsSGIX,
    qemu_glGetInteger64i_v,
    qemu_glGetInteger64v,
    qemu_glGetIntegerIndexedvEXT,
    qemu_glGetIntegeri_v,
    qemu_glGetIntegerui64i_vNV,
    qemu_glGetIntegerui64vNV,
    qemu_glGetInternalformatSampleivNV,
    qemu_glGetInternalformati64v,
    qemu_glGetInternalformativ,
    qemu_glGetInvariantBooleanvEXT,
    qemu_glGetInvariantFloatvEXT,
    qemu_glGetInvariantIntegervEXT,
    qemu_glGetLightxOES,
    qemu_glGetListParameterfvSGIX,
    qemu_glGetListParameterivSGIX,
    qemu_glGetLocalConstantBooleanvEXT,
    qemu_glGetLocalConstantFloatvEXT,
    qemu_glGetLocalConstantIntegervEXT,
    qemu_glGetMapAttribParameterfvNV,
    qemu_glGetMapAttribParameterivNV,
    qemu_glGetMapControlPointsNV,
    qemu_glGetMapParameterfvNV,
    qemu_glGetMapParameterivNV,
    qemu_glGetMapxvOES,
    qemu_glGetMaterialxOES,
    qemu_glGetMemoryObjectDetachedResourcesuivNV,
    qemu_glGetMemoryObjectParameterivEXT,
    qemu_glGetMinmax,
    qemu_glGetMinmaxEXT,
    qemu_glGetMinmaxParameterfv,
    qemu_glGetMinmaxParameterfvEXT,
    qemu_glGetMinmaxParameteriv,
    qemu_glGetMinmaxParameterivEXT,
    qemu_glGetMultiTexEnvfvEXT,
    qemu_glGetMultiTexEnvivEXT,
    qemu_glGetMultiTexGendvEXT,
    qemu_glGetMultiTexGenfvEXT,
    qemu_glGetMultiTexGenivEXT,
    qemu_glGetMultiTexImageEXT,
    qemu_glGetMultiTexLevelParameterfvEXT,
    qemu_glGetMultiTexLevelParameterivEXT,
    qemu_glGetMultiTexParameterIivEXT,
    qemu_glGetMultiTexParameterIuivEXT,
    qemu_glGetMultiTexParameterfvEXT,
    qemu_glGetMultiTexParameterivEXT,
    qemu_glGetMultisamplefv,
    qemu_glGetMultisamplefvNV,
    qemu_glGetNamedBufferParameteri64v,
    qemu_glGetNamedBufferParameteriv,
    qemu_glGetNamedBufferParameterivEXT,
    qemu_glGetNamedBufferParameterui64vNV,
    qemu_glGetNamedBufferPointerv,
    qemu_glGetNamedBufferPointervEXT,
    qemu_glGetNamedBufferSubData,
    qemu_glGetNamedBufferSubDataEXT,
    qemu_glGetNamedFramebufferAttachmentParameteriv,
    qemu_glGetNamedFramebufferAttachmentParameterivEXT,
    qemu_glGetNamedFramebufferParameterfvAMD,
    qemu_glGetNamedFramebufferParameteriv,
    qemu_glGetNamedFramebufferParameterivEXT,
    qemu_glGetNamedProgramLocalParameterIivEXT,
    qemu_glGetNamedProgramLocalParameterIuivEXT,
    qemu_glGetNamedProgramLocalParameterdvEXT,
    qemu_glGetNamedProgramLocalParameterfvEXT,
    qemu_glGetNamedProgramStringEXT,
    qemu_glGetNamedProgramivEXT,
    qemu_glGetNamedRenderbufferParameteriv,
    qemu_glGetNamedRenderbufferParameterivEXT,
    qemu_glGetNamedStringARB,
    qemu_glGetNamedStringivARB,
    qemu_glGetNextPerfQueryIdINTEL,
    qemu_glGetObjectBufferfvATI,
    qemu_glGetObjectBufferivATI,
    qemu_glGetObjectLabel,
    qemu_glGetObjectLabelEXT,
    qemu_glGetObjectParameterfvARB,
    qemu_glGetObjectParameterivAPPLE,
    qemu_glGetObjectParameterivARB,
    qemu_glGetObjectPtrLabel,
    qemu_glGetOcclusionQueryivNV,
    qemu_glGetOcclusionQueryuivNV,
    qemu_glGetPathColorGenfvNV,
    qemu_glGetPathColorGenivNV,
    qemu_glGetPathCommandsNV,
    qemu_glGetPathCoordsNV,
    qemu_glGetPathDashArrayNV,
    qemu_glGetPathLengthNV,
    qemu_glGetPathMetricRangeNV,
    qemu_glGetPathMetricsNV,
    qemu_glGetPathParameterfvNV,
    qemu_glGetPathParameterivNV,
    qemu_glGetPathSpacingNV,
    qemu_glGetPathTexGenfvNV,
    qemu_glGetPathTexGenivNV,
    qemu_glGetPerfCounterInfoINTEL,
    qemu_glGetPerfMonitorCounterDataAMD,
    qemu_glGetPerfMonitorCounterInfoAMD,
    qemu_glGetPerfMonitorCounterStringAMD,
    qemu_glGetPerfMonitorCountersAMD,
    qemu_glGetPerfMonitorGroupStringAMD,
    qemu_glGetPerfMonitorGroupsAMD,
    qemu_glGetPerfQueryDataINTEL,
    qemu_glGetPerfQueryIdByNameINTEL,
    qemu_glGetPerfQueryInfoINTEL,
    qemu_glGetPixelMapxv,
    qemu_glGetPixelTexGenParameterfvSGIS,
    qemu_glGetPixelTexGenParameterivSGIS,
    qemu_glGetPixelTransformParameterfvEXT,
    qemu_glGetPixelTransformParameterivEXT,
    qemu_glGetPointerIndexedvEXT,
    qemu_glGetPointeri_vEXT,
    qemu_glGetPointervEXT,
    qemu_glGetProgramBinary,
    qemu_glGetProgramEnvParameterIivNV,
    qemu_glGetProgramEnvParameterIuivNV,
    qemu_glGetProgramEnvParameterdvARB,
    qemu_glGetProgramEnvParameterfvARB,
    qemu_glGetProgramInfoLog,
    qemu_glGetProgramInterfaceiv,
    qemu_glGetProgramLocalParameterIivNV,
    qemu_glGetProgramLocalParameterIuivNV,
    qemu_glGetProgramLocalParameterdvARB,
    qemu_glGetProgramLocalParameterfvARB,
    qemu_glGetProgramNamedParameterdvNV,
    qemu_glGetProgramNamedParameterfvNV,
    qemu_glGetProgramParameterdvNV,
    qemu_glGetProgramParameterfvNV,
    qemu_glGetProgramPipelineInfoLog,
    qemu_glGetProgramPipelineiv,
    qemu_glGetProgramResourceIndex,
    qemu_glGetProgramResourceLocation,
    qemu_glGetProgramResourceLocationIndex,
    qemu_glGetProgramResourceName,
    qemu_glGetProgramResourcefvNV,
    qemu_glGetProgramResourceiv,
    qemu_glGetProgramStageiv,
    qemu_glGetProgramStringARB,
    qemu_glGetProgramStringNV,
    qemu_glGetProgramSubroutineParameteruivNV,
    qemu_glGetProgramiv,
    qemu_glGetProgramivARB,
    qemu_glGetProgramivNV,
    qemu_glGetQueryBufferObjecti64v,
    qemu_glGetQueryBufferObjectiv,
    qemu_glGetQueryBufferObjectui64v,
    qemu_glGetQueryBufferObjectuiv,
    qemu_glGetQueryIndexediv,
    qemu_glGetQueryObjecti64v,
    qemu_glGetQueryObjecti64vEXT,
    qemu_glGetQueryObjectiv,
    qemu_glGetQueryObjectivARB,
    qemu_glGetQueryObjectui64v,
    qemu_glGetQueryObjectui64vEXT,
    qemu_glGetQueryObjectuiv,
    qemu_glGetQueryObjectuivARB,
    qemu_glGetQueryiv,
    qemu_glGetQueryivARB,
    qemu_glGetRenderbufferParameteriv,
    qemu_glGetRenderbufferParameterivEXT,
    qemu_glGetSamplerParameterIiv,
    qemu_glGetSamplerParameterIuiv,
    qemu_glGetSamplerParameterfv,
    qemu_glGetSamplerParameteriv,
    qemu_glGetSemaphoreParameterui64vEXT,
    qemu_glGetSeparableFilter,
    qemu_glGetSeparableFilterEXT,
    qemu_glGetShaderInfoLog,
    qemu_glGetShaderPrecisionFormat,
    qemu_glGetShaderSource,
    qemu_glGetShaderSourceARB,
    qemu_glGetShaderiv,
    qemu_glGetShadingRateImagePaletteNV,
    qemu_glGetShadingRateSampleLocationivNV,
    qemu_glGetSharpenTexFuncSGIS,
    qemu_glGetStageIndexNV,
    qemu_glGetStringi,
    qemu_glGetSubroutineIndex,
    qemu_glGetSubroutineUniformLocation,
    qemu_glGetSynciv,
    qemu_glGetTexBumpParameterfvATI,
    qemu_glGetTexBumpParameterivATI,
    qemu_glGetTexEnvxvOES,
    qemu_glGetTexFilterFuncSGIS,
    qemu_glGetTexGenxvOES,
    qemu_glGetTexLevelParameterxvOES,
    qemu_glGetTexParameterIiv,
    qemu_glGetTexParameterIivEXT,
    qemu_glGetTexParameterIuiv,
    qemu_glGetTexParameterIuivEXT,
    qemu_glGetTexParameterPointervAPPLE,
    qemu_glGetTexParameterxvOES,
    qemu_glGetTextureHandleARB,
    qemu_glGetTextureHandleNV,
    qemu_glGetTextureImage,
    qemu_glGetTextureImageEXT,
    qemu_glGetTextureLevelParameterfv,
    qemu_glGetTextureLevelParameterfvEXT,
    qemu_glGetTextureLevelParameteriv,
    qemu_glGetTextureLevelParameterivEXT,
    qemu_glGetTextureParameterIiv,
    qemu_glGetTextureParameterIivEXT,
    qemu_glGetTextureParameterIuiv,
    qemu_glGetTextureParameterIuivEXT,
    qemu_glGetTextureParameterfv,
    qemu_glGetTextureParameterfvEXT,
    qemu_glGetTextureParameteriv,
    qemu_glGetTextureParameterivEXT,
    qemu_glGetTextureSamplerHandleARB,
    qemu_glGetTextureSamplerHandleNV,
    qemu_glGetTextureSubImage,
    qemu_glGetTrackMatrixivNV,
    qemu_glGetTransformFeedbackVarying,
    qemu_glGetTransformFeedbackVaryingEXT,
    qemu_glGetTransformFeedbackVaryingNV,
    qemu_glGetTransformFeedbacki64_v,
    qemu_glGetTransformFeedbacki_v,
    qemu_glGetTransformFeedbackiv,
    qemu_glGetUniformBlockIndex,
    qemu_glGetUniformBufferSizeEXT,
    qemu_glGetUniformIndices,
    qemu_glGetUniformLocation,
    qemu_glGetUniformLocationARB,
    qemu_glGetUniformOffsetEXT,
    qemu_glGetUniformSubroutineuiv,
    qemu_glGetUniformdv,
    qemu_glGetUniformfv,
    qemu_glGetUniformfvARB,
    qemu_glGetUniformi64vARB,
    qemu_glGetUniformi64vNV,
    qemu_glGetUniformiv,
    qemu_glGetUniformivARB,
    qemu_glGetUniformui64vARB,
    qemu_glGetUniformui64vNV,
    qemu_glGetUniformuiv,
    qemu_glGetUniformuivEXT,
    qemu_glGetUnsignedBytei_vEXT,
    qemu_glGetUnsignedBytevEXT,
    qemu_glGetVariantArrayObjectfvATI,
    qemu_glGetVariantArrayObjectivATI,
    qemu_glGetVariantBooleanvEXT,
    qemu_glGetVariantFloatvEXT,
    qemu_glGetVariantIntegervEXT,
    qemu_glGetVariantPointervEXT,
    qemu_glGetVaryingLocationNV,
    qemu_glGetVertexArrayIndexed64iv,
    qemu_glGetVertexArrayIndexediv,
    qemu_glGetVertexArrayIntegeri_vEXT,
    qemu_glGetVertexArrayIntegervEXT,
    qemu_glGetVertexArrayPointeri_vEXT,
    qemu_glGetVertexArrayPointervEXT,
    qemu_glGetVertexArrayiv,
    qemu_glGetVertexAttribArrayObjectfvATI,
    qemu_glGetVertexAttribArrayObjectivATI,
    qemu_glGetVertexAttribIiv,
    qemu_glGetVertexAttribIivEXT,
    qemu_glGetVertexAttribIuiv,
    qemu_glGetVertexAttribIuivEXT,
    qemu_glGetVertexAttribLdv,
    qemu_glGetVertexAttribLdvEXT,
    qemu_glGetVertexAttribLi64vNV,
    qemu_glGetVertexAttribLui64vARB,
    qemu_glGetVertexAttribLui64vNV,
    qemu_glGetVertexAttribPointerv,
    qemu_glGetVertexAttribPointervARB,
    qemu_glGetVertexAttribPointervNV,
    qemu_glGetVertexAttribdv,
    qemu_glGetVertexAttribdvARB,
    qemu_glGetVertexAttribdvNV,
    qemu_glGetVertexAttribfv,
    qemu_glGetVertexAttribfvARB,
    qemu_glGetVertexAttribfvNV,
    qemu_glGetVertexAttribiv,
    qemu_glGetVertexAttribivARB,
    qemu_glGetVertexAttribivNV,
    qemu_glGetVideoCaptureStreamdvNV,
    qemu_glGetVideoCaptureStreamfvNV,
    qemu_glGetVideoCaptureStreamivNV,
    qemu_glGetVideoCaptureivNV,
    qemu_glGetVideoi64vNV,
    qemu_glGetVideoivNV,
    qemu_glGetVideoui64vNV,
    qemu_glGetVideouivNV,
    qemu_glGetVkProcAddrNV,
    qemu_glGetnColorTable,
    qemu_glGetnColorTableARB,
    qemu_glGetnCompressedTexImage,
    qemu_glGetnCompressedTexImageARB,
    qemu_glGetnConvolutionFilter,
    qemu_glGetnConvolutionFilterARB,
    qemu_glGetnHistogram,
    qemu_glGetnHistogramARB,
    qemu_glGetnMapdv,
    qemu_glGetnMapdvARB,
    qemu_glGetnMapfv,
    qemu_glGetnMapfvARB,
    qemu_glGetnMapiv,
    qemu_glGetnMapivARB,
    qemu_glGetnMinmax,
    qemu_glGetnMinmaxARB,
    qemu_glGetnPixelMapfv,
    qemu_glGetnPixelMapfvARB,
    qemu_glGetnPixelMapuiv,
    qemu_glGetnPixelMapuivARB,
    qemu_glGetnPixelMapusv,
    qemu_glGetnPixelMapusvARB,
    qemu_glGetnPolygonStipple,
    qemu_glGetnPolygonStippleARB,
    qemu_glGetnSeparableFilter,
    qemu_glGetnSeparableFilterARB,
    qemu_glGetnTexImage,
    qemu_glGetnTexImageARB,
    qemu_glGetnUniformdv,
    qemu_glGetnUniformdvARB,
    qemu_glGetnUniformfv,
    qemu_glGetnUniformfvARB,
    qemu_glGetnUniformi64vARB,
    qemu_glGetnUniformiv,
    qemu_glGetnUniformivARB,
    qemu_glGetnUniformui64vARB,
    qemu_glGetnUniformuiv,
    qemu_glGetnUniformuivARB,
    qemu_glGlobalAlphaFactorbSUN,
    qemu_glGlobalAlphaFactordSUN,
    qemu_glGlobalAlphaFactorfSUN,
    qemu_glGlobalAlphaFactoriSUN,
    qemu_glGlobalAlphaFactorsSUN,
    qemu_glGlobalAlphaFactorubSUN,
    qemu_glGlobalAlphaFactoruiSUN,
    qemu_glGlobalAlphaFactorusSUN,
    qemu_glHintPGI,
    qemu_glHistogram,
    qemu_glHistogramEXT,
    qemu_glIglooInterfaceSGIX,
    qemu_glImageTransformParameterfHP,
    qemu_glImageTransformParameterfvHP,
    qemu_glImageTransformParameteriHP,
    qemu_glImageTransformParameterivHP,
    qemu_glImportMemoryFdEXT,
    qemu_glImportMemoryWin32HandleEXT,
    qemu_glImportMemoryWin32NameEXT,
    qemu_glImportSemaphoreFdEXT,
    qemu_glImportSemaphoreWin32HandleEXT,
    qemu_glImportSemaphoreWin32NameEXT,
    qemu_glImportSyncEXT,
    qemu_glIndexFormatNV,
    qemu_glIndexFuncEXT,
    qemu_glIndexMaterialEXT,
    qemu_glIndexPointerEXT,
    qemu_glIndexPointerListIBM,
    qemu_glIndexxOES,
    qemu_glIndexxvOES,
    qemu_glInsertComponentEXT,
    qemu_glInsertEventMarkerEXT,
    qemu_glInstrumentsBufferSGIX,
    qemu_glInterpolatePathsNV,
    qemu_glInvalidateBufferData,
    qemu_glInvalidateBufferSubData,
    qemu_glInvalidateFramebuffer,
    qemu_glInvalidateNamedFramebufferData,
    qemu_glInvalidateNamedFramebufferSubData,
    qemu_glInvalidateSubFramebuffer,
    qemu_glInvalidateTexImage,
    qemu_glInvalidateTexSubImage,
    qemu_glIsAsyncMarkerSGIX,
    qemu_glIsBuffer,
    qemu_glIsBufferARB,
    qemu_glIsBufferResidentNV,
    qemu_glIsCommandListNV,
    qemu_glIsEnabledIndexedEXT,
    qemu_glIsEnabledi,
    qemu_glIsFenceAPPLE,
    qemu_glIsFenceNV,
    qemu_glIsFramebuffer,
    qemu_glIsFramebufferEXT,
    qemu_glIsImageHandleResidentARB,
    qemu_glIsImageHandleResidentNV,
    qemu_glIsMemoryObjectEXT,
    qemu_glIsNameAMD,
    qemu_glIsNamedBufferResidentNV,
    qemu_glIsNamedStringARB,
    qemu_glIsObjectBufferATI,
    qemu_glIsOcclusionQueryNV,
    qemu_glIsPathNV,
    qemu_glIsPointInFillPathNV,
    qemu_glIsPointInStrokePathNV,
    qemu_glIsProgram,
    qemu_glIsProgramARB,
    qemu_glIsProgramNV,
    qemu_glIsProgramPipeline,
    qemu_glIsQuery,
    qemu_glIsQueryARB,
    qemu_glIsRenderbuffer,
    qemu_glIsRenderbufferEXT,
    qemu_glIsSampler,
    qemu_glIsSemaphoreEXT,
    qemu_glIsShader,
    qemu_glIsStateNV,
    qemu_glIsSync,
    qemu_glIsTextureEXT,
    qemu_glIsTextureHandleResidentARB,
    qemu_glIsTextureHandleResidentNV,
    qemu_glIsTransformFeedback,
    qemu_glIsTransformFeedbackNV,
    qemu_glIsVariantEnabledEXT,
    qemu_glIsVertexArray,
    qemu_glIsVertexArrayAPPLE,
    qemu_glIsVertexAttribEnabledAPPLE,
    qemu_glLGPUCopyImageSubDataNVX,
    qemu_glLGPUInterlockNVX,
    qemu_glLGPUNamedBufferSubDataNVX,
    qemu_glLabelObjectEXT,
    qemu_glLightEnviSGIX,
    qemu_glLightModelxOES,
    qemu_glLightModelxvOES,
    qemu_glLightxOES,
    qemu_glLightxvOES,
    qemu_glLineWidthxOES,
    qemu_glLinkProgram,
    qemu_glLinkProgramARB,
    qemu_glListDrawCommandsStatesClientNV,
    qemu_glListParameterfSGIX,
    qemu_glListParameterfvSGIX,
    qemu_glListParameteriSGIX,
    qemu_glListParameterivSGIX,
    qemu_glLoadIdentityDeformationMapSGIX,
    qemu_glLoadMatrixxOES,
    qemu_glLoadProgramNV,
    qemu_glLoadTransposeMatrixd,
    qemu_glLoadTransposeMatrixdARB,
    qemu_glLoadTransposeMatrixf,
    qemu_glLoadTransposeMatrixfARB,
    qemu_glLoadTransposeMatrixxOES,
    qemu_glLockArraysEXT,
    qemu_glMTexCoord2fSGIS,
    qemu_glMTexCoord2fvSGIS,
    qemu_glMakeBufferNonResidentNV,
    qemu_glMakeBufferResidentNV,
    qemu_glMakeImageHandleNonResidentARB,
    qemu_glMakeImageHandleNonResidentNV,
    qemu_glMakeImageHandleResidentARB,
    qemu_glMakeImageHandleResidentNV,
    qemu_glMakeNamedBufferNonResidentNV,
    qemu_glMakeNamedBufferResidentNV,
    qemu_glMakeTextureHandleNonResidentARB,
    qemu_glMakeTextureHandleNonResidentNV,
    qemu_glMakeTextureHandleResidentARB,
    qemu_glMakeTextureHandleResidentNV,
    qemu_glMap1xOES,
    qemu_glMap2xOES,
    qemu_glMapBuffer,
    qemu_glMapBufferARB,
    qemu_glMapBufferRange,
    qemu_glMapControlPointsNV,
    qemu_glMapGrid1xOES,
    qemu_glMapGrid2xOES,
    qemu_glMapNamedBuffer,
    qemu_glMapNamedBufferEXT,
    qemu_glMapNamedBufferRange,
    qemu_glMapNamedBufferRangeEXT,
    qemu_glMapObjectBufferATI,
    qemu_glMapParameterfvNV,
    qemu_glMapParameterivNV,
    qemu_glMapTexture2DINTEL,
    qemu_glMapVertexAttrib1dAPPLE,
    qemu_glMapVertexAttrib1fAPPLE,
    qemu_glMapVertexAttrib2dAPPLE,
    qemu_glMapVertexAttrib2fAPPLE,
    qemu_glMaterialxOES,
    qemu_glMaterialxvOES,
    qemu_glMatrixFrustumEXT,
    qemu_glMatrixIndexPointerARB,
    qemu_glMatrixIndexubvARB,
    qemu_glMatrixIndexuivARB,
    qemu_glMatrixIndexusvARB,
    qemu_glMatrixLoad3x2fNV,
    qemu_glMatrixLoad3x3fNV,
    qemu_glMatrixLoadIdentityEXT,
    qemu_glMatrixLoadTranspose3x3fNV,
    qemu_glMatrixLoadTransposedEXT,
    qemu_glMatrixLoadTransposefEXT,
    qemu_glMatrixLoaddEXT,
    qemu_glMatrixLoadfEXT,
    qemu_glMatrixMult3x2fNV,
    qemu_glMatrixMult3x3fNV,
    qemu_glMatrixMultTranspose3x3fNV,
    qemu_glMatrixMultTransposedEXT,
    qemu_glMatrixMultTransposefEXT,
    qemu_glMatrixMultdEXT,
    qemu_glMatrixMultfEXT,
    qemu_glMatrixOrthoEXT,
    qemu_glMatrixPopEXT,
    qemu_glMatrixPushEXT,
    qemu_glMatrixRotatedEXT,
    qemu_glMatrixRotatefEXT,
    qemu_glMatrixScaledEXT,
    qemu_glMatrixScalefEXT,
    qemu_glMatrixTranslatedEXT,
    qemu_glMatrixTranslatefEXT,
    qemu_glMaxShaderCompilerThreadsARB,
    qemu_glMaxShaderCompilerThreadsKHR,
    qemu_glMemoryBarrier,
    qemu_glMemoryBarrierByRegion,
    qemu_glMemoryBarrierEXT,
    qemu_glMemoryObjectParameterivEXT,
    qemu_glMinSampleShading,
    qemu_glMinSampleShadingARB,
    qemu_glMinmax,
    qemu_glMinmaxEXT,
    qemu_glMultMatrixxOES,
    qemu_glMultTransposeMatrixd,
    qemu_glMultTransposeMatrixdARB,
    qemu_glMultTransposeMatrixf,
    qemu_glMultTransposeMatrixfARB,
    qemu_glMultTransposeMatrixxOES,
    qemu_glMultiDrawArrays,
    qemu_glMultiDrawArraysEXT,
    qemu_glMultiDrawArraysIndirect,
    qemu_glMultiDrawArraysIndirectAMD,
    qemu_glMultiDrawArraysIndirectBindlessCountNV,
    qemu_glMultiDrawArraysIndirectBindlessNV,
    qemu_glMultiDrawArraysIndirectCount,
    qemu_glMultiDrawArraysIndirectCountARB,
    qemu_glMultiDrawElementArrayAPPLE,
    qemu_glMultiDrawElements,
    qemu_glMultiDrawElementsBaseVertex,
    qemu_glMultiDrawElementsEXT,
    qemu_glMultiDrawElementsIndirect,
    qemu_glMultiDrawElementsIndirectAMD,
    qemu_glMultiDrawElementsIndirectBindlessCountNV,
    qemu_glMultiDrawElementsIndirectBindlessNV,
    qemu_glMultiDrawElementsIndirectCount,
    qemu_glMultiDrawElementsIndirectCountARB,
    qemu_glMultiDrawMeshTasksIndirectCountNV,
    qemu_glMultiDrawMeshTasksIndirectNV,
    qemu_glMultiDrawRangeElementArrayAPPLE,
    qemu_glMultiModeDrawArraysIBM,
    qemu_glMultiModeDrawElementsIBM,
    qemu_glMultiTexBufferEXT,
    qemu_glMultiTexCoord1bOES,
    qemu_glMultiTexCoord1bvOES,
    qemu_glMultiTexCoord1d,
    qemu_glMultiTexCoord1dARB,
    qemu_glMultiTexCoord1dSGIS,
    qemu_glMultiTexCoord1dv,
    qemu_glMultiTexCoord1dvARB,
    qemu_glMultiTexCoord1dvSGIS,
    qemu_glMultiTexCoord1f,
    qemu_glMultiTexCoord1fARB,
    qemu_glMultiTexCoord1fSGIS,
    qemu_glMultiTexCoord1fv,
    qemu_glMultiTexCoord1fvARB,
    qemu_glMultiTexCoord1fvSGIS,
    qemu_glMultiTexCoord1hNV,
    qemu_glMultiTexCoord1hvNV,
    qemu_glMultiTexCoord1i,
    qemu_glMultiTexCoord1iARB,
    qemu_glMultiTexCoord1iSGIS,
    qemu_glMultiTexCoord1iv,
    qemu_glMultiTexCoord1ivARB,
    qemu_glMultiTexCoord1ivSGIS,
    qemu_glMultiTexCoord1s,
    qemu_glMultiTexCoord1sARB,
    qemu_glMultiTexCoord1sSGIS,
    qemu_glMultiTexCoord1sv,
    qemu_glMultiTexCoord1svARB,
    qemu_glMultiTexCoord1svSGIS,
    qemu_glMultiTexCoord1xOES,
    qemu_glMultiTexCoord1xvOES,
    qemu_glMultiTexCoord2bOES,
    qemu_glMultiTexCoord2bvOES,
    qemu_glMultiTexCoord2d,
    qemu_glMultiTexCoord2dARB,
    qemu_glMultiTexCoord2dSGIS,
    qemu_glMultiTexCoord2dv,
    qemu_glMultiTexCoord2dvARB,
    qemu_glMultiTexCoord2dvSGIS,
    qemu_glMultiTexCoord2f,
    qemu_glMultiTexCoord2fARB,
    qemu_glMultiTexCoord2fSGIS,
    qemu_glMultiTexCoord2fv,
    qemu_glMultiTexCoord2fvARB,
    qemu_glMultiTexCoord2fvSGIS,
    qemu_glMultiTexCoord2hNV,
    qemu_glMultiTexCoord2hvNV,
    qemu_glMultiTexCoord2i,
    qemu_glMultiTexCoord2iARB,
    qemu_glMultiTexCoord2iSGIS,
    qemu_glMultiTexCoord2iv,
    qemu_glMultiTexCoord2ivARB,
    qemu_glMultiTexCoord2ivSGIS,
    qemu_glMultiTexCoord2s,
    qemu_glMultiTexCoord2sARB,
    qemu_glMultiTexCoord2sSGIS,
    qemu_glMultiTexCoord2sv,
    qemu_glMultiTexCoord2svARB,
    qemu_glMultiTexCoord2svSGIS,
    qemu_glMultiTexCoord2xOES,
    qemu_glMultiTexCoord2xvOES,
    qemu_glMultiTexCoord3bOES,
    qemu_glMultiTexCoord3bvOES,
    qemu_glMultiTexCoord3d,
    qemu_glMultiTexCoord3dARB,
    qemu_glMultiTexCoord3dSGIS,
    qemu_glMultiTexCoord3dv,
    qemu_glMultiTexCoord3dvARB,
    qemu_glMultiTexCoord3dvSGIS,
    qemu_glMultiTexCoord3f,
    qemu_glMultiTexCoord3fARB,
    qemu_glMultiTexCoord3fSGIS,
    qemu_glMultiTexCoord3fv,
    qemu_glMultiTexCoord3fvARB,
    qemu_glMultiTexCoord3fvSGIS,
    qemu_glMultiTexCoord3hNV,
    qemu_glMultiTexCoord3hvNV,
    qemu_glMultiTexCoord3i,
    qemu_glMultiTexCoord3iARB,
    qemu_glMultiTexCoord3iSGIS,
    qemu_glMultiTexCoord3iv,
    qemu_glMultiTexCoord3ivARB,
    qemu_glMultiTexCoord3ivSGIS,
    qemu_glMultiTexCoord3s,
    qemu_glMultiTexCoord3sARB,
    qemu_glMultiTexCoord3sSGIS,
    qemu_glMultiTexCoord3sv,
    qemu_glMultiTexCoord3svARB,
    qemu_glMultiTexCoord3svSGIS,
    qemu_glMultiTexCoord3xOES,
    qemu_glMultiTexCoord3xvOES,
    qemu_glMultiTexCoord4bOES,
    qemu_glMultiTexCoord4bvOES,
    qemu_glMultiTexCoord4d,
    qemu_glMultiTexCoord4dARB,
    qemu_glMultiTexCoord4dSGIS,
    qemu_glMultiTexCoord4dv,
    qemu_glMultiTexCoord4dvARB,
    qemu_glMultiTexCoord4dvSGIS,
    qemu_glMultiTexCoord4f,
    qemu_glMultiTexCoord4fARB,
    qemu_glMultiTexCoord4fSGIS,
    qemu_glMultiTexCoord4fv,
    qemu_glMultiTexCoord4fvARB,
    qemu_glMultiTexCoord4fvSGIS,
    qemu_glMultiTexCoord4hNV,
    qemu_glMultiTexCoord4hvNV,
    qemu_glMultiTexCoord4i,
    qemu_glMultiTexCoord4iARB,
    qemu_glMultiTexCoord4iSGIS,
    qemu_glMultiTexCoord4iv,
    qemu_glMultiTexCoord4ivARB,
    qemu_glMultiTexCoord4ivSGIS,
    qemu_glMultiTexCoord4s,
    qemu_glMultiTexCoord4sARB,
    qemu_glMultiTexCoord4sSGIS,
    qemu_glMultiTexCoord4sv,
    qemu_glMultiTexCoord4svARB,
    qemu_glMultiTexCoord4svSGIS,
    qemu_glMultiTexCoord4xOES,
    qemu_glMultiTexCoord4xvOES,
    qemu_glMultiTexCoordP1ui,
    qemu_glMultiTexCoordP1uiv,
    qemu_glMultiTexCoordP2ui,
    qemu_glMultiTexCoordP2uiv,
    qemu_glMultiTexCoordP3ui,
    qemu_glMultiTexCoordP3uiv,
    qemu_glMultiTexCoordP4ui,
    qemu_glMultiTexCoordP4uiv,
    qemu_glMultiTexCoordPointerEXT,
    qemu_glMultiTexCoordPointerSGIS,
    qemu_glMultiTexEnvfEXT,
    qemu_glMultiTexEnvfvEXT,
    qemu_glMultiTexEnviEXT,
    qemu_glMultiTexEnvivEXT,
    qemu_glMultiTexGendEXT,
    qemu_glMultiTexGendvEXT,
    qemu_glMultiTexGenfEXT,
    qemu_glMultiTexGenfvEXT,
    qemu_glMultiTexGeniEXT,
    qemu_glMultiTexGenivEXT,
    qemu_glMultiTexImage1DEXT,
    qemu_glMultiTexImage2DEXT,
    qemu_glMultiTexImage3DEXT,
    qemu_glMultiTexParameterIivEXT,
    qemu_glMultiTexParameterIuivEXT,
    qemu_glMultiTexParameterfEXT,
    qemu_glMultiTexParameterfvEXT,
    qemu_glMultiTexParameteriEXT,
    qemu_glMultiTexParameterivEXT,
    qemu_glMultiTexRenderbufferEXT,
    qemu_glMultiTexSubImage1DEXT,
    qemu_glMultiTexSubImage2DEXT,
    qemu_glMultiTexSubImage3DEXT,
    qemu_glMulticastBarrierNV,
    qemu_glMulticastBlitFramebufferNV,
    qemu_glMulticastBufferSubDataNV,
    qemu_glMulticastCopyBufferSubDataNV,
    qemu_glMulticastCopyImageSubDataNV,
    qemu_glMulticastFramebufferSampleLocationsfvNV,
    qemu_glMulticastGetQueryObjecti64vNV,
    qemu_glMulticastGetQueryObjectivNV,
    qemu_glMulticastGetQueryObjectui64vNV,
    qemu_glMulticastGetQueryObjectuivNV,
    qemu_glMulticastScissorArrayvNVX,
    qemu_glMulticastViewportArrayvNVX,
    qemu_glMulticastViewportPositionWScaleNVX,
    qemu_glMulticastWaitSyncNV,
    qemu_glNamedBufferAttachMemoryNV,
    qemu_glNamedBufferData,
    qemu_glNamedBufferDataEXT,
    qemu_glNamedBufferPageCommitmentARB,
    qemu_glNamedBufferPageCommitmentEXT,
    qemu_glNamedBufferStorage,
    qemu_glNamedBufferStorageEXT,
    qemu_glNamedBufferStorageExternalEXT,
    qemu_glNamedBufferStorageMemEXT,
    qemu_glNamedBufferSubData,
    qemu_glNamedBufferSubDataEXT,
    qemu_glNamedCopyBufferSubDataEXT,
    qemu_glNamedFramebufferDrawBuffer,
    qemu_glNamedFramebufferDrawBuffers,
    qemu_glNamedFramebufferParameteri,
    qemu_glNamedFramebufferParameteriEXT,
    qemu_glNamedFramebufferReadBuffer,
    qemu_glNamedFramebufferRenderbuffer,
    qemu_glNamedFramebufferRenderbufferEXT,
    qemu_glNamedFramebufferSampleLocationsfvARB,
    qemu_glNamedFramebufferSampleLocationsfvNV,
    qemu_glNamedFramebufferSamplePositionsfvAMD,
    qemu_glNamedFramebufferTexture,
    qemu_glNamedFramebufferTexture1DEXT,
    qemu_glNamedFramebufferTexture2DEXT,
    qemu_glNamedFramebufferTexture3DEXT,
    qemu_glNamedFramebufferTextureEXT,
    qemu_glNamedFramebufferTextureFaceEXT,
    qemu_glNamedFramebufferTextureLayer,
    qemu_glNamedFramebufferTextureLayerEXT,
    qemu_glNamedProgramLocalParameter4dEXT,
    qemu_glNamedProgramLocalParameter4dvEXT,
    qemu_glNamedProgramLocalParameter4fEXT,
    qemu_glNamedProgramLocalParameter4fvEXT,
    qemu_glNamedProgramLocalParameterI4iEXT,
    qemu_glNamedProgramLocalParameterI4ivEXT,
    qemu_glNamedProgramLocalParameterI4uiEXT,
    qemu_glNamedProgramLocalParameterI4uivEXT,
    qemu_glNamedProgramLocalParameters4fvEXT,
    qemu_glNamedProgramLocalParametersI4ivEXT,
    qemu_glNamedProgramLocalParametersI4uivEXT,
    qemu_glNamedProgramStringEXT,
    qemu_glNamedRenderbufferStorage,
    qemu_glNamedRenderbufferStorageEXT,
    qemu_glNamedRenderbufferStorageMultisample,
    qemu_glNamedRenderbufferStorageMultisampleAdvancedAMD,
    qemu_glNamedRenderbufferStorageMultisampleCoverageEXT,
    qemu_glNamedRenderbufferStorageMultisampleEXT,
    qemu_glNamedStringARB,
    qemu_glNewBufferRegion,
    qemu_glNewObjectBufferATI,
    qemu_glNormal3fVertex3fSUN,
    qemu_glNormal3fVertex3fvSUN,
    qemu_glNormal3hNV,
    qemu_glNormal3hvNV,
    qemu_glNormal3xOES,
    qemu_glNormal3xvOES,
    qemu_glNormalFormatNV,
    qemu_glNormalP3ui,
    qemu_glNormalP3uiv,
    qemu_glNormalPointerEXT,
    qemu_glNormalPointerListIBM,
    qemu_glNormalPointervINTEL,
    qemu_glNormalStream3bATI,
    qemu_glNormalStream3bvATI,
    qemu_glNormalStream3dATI,
    qemu_glNormalStream3dvATI,
    qemu_glNormalStream3fATI,
    qemu_glNormalStream3fvATI,
    qemu_glNormalStream3iATI,
    qemu_glNormalStream3ivATI,
    qemu_glNormalStream3sATI,
    qemu_glNormalStream3svATI,
    qemu_glObjectLabel,
    qemu_glObjectPtrLabel,
    qemu_glObjectPurgeableAPPLE,
    qemu_glObjectUnpurgeableAPPLE,
    qemu_glOrthofOES,
    qemu_glOrthoxOES,
    qemu_glPNTrianglesfATI,
    qemu_glPNTrianglesiATI,
    qemu_glPassTexCoordATI,
    qemu_glPassThroughxOES,
    qemu_glPatchParameterfv,
    qemu_glPatchParameteri,
    qemu_glPathColorGenNV,
    qemu_glPathCommandsNV,
    qemu_glPathCoordsNV,
    qemu_glPathCoverDepthFuncNV,
    qemu_glPathDashArrayNV,
    qemu_glPathFogGenNV,
    qemu_glPathGlyphIndexArrayNV,
    qemu_glPathGlyphIndexRangeNV,
    qemu_glPathGlyphRangeNV,
    qemu_glPathGlyphsNV,
    qemu_glPathMemoryGlyphIndexArrayNV,
    qemu_glPathParameterfNV,
    qemu_glPathParameterfvNV,
    qemu_glPathParameteriNV,
    qemu_glPathParameterivNV,
    qemu_glPathStencilDepthOffsetNV,
    qemu_glPathStencilFuncNV,
    qemu_glPathStringNV,
    qemu_glPathSubCommandsNV,
    qemu_glPathSubCoordsNV,
    qemu_glPathTexGenNV,
    qemu_glPauseTransformFeedback,
    qemu_glPauseTransformFeedbackNV,
    qemu_glPixelDataRangeNV,
    qemu_glPixelMapx,
    qemu_glPixelStorex,
    qemu_glPixelTexGenParameterfSGIS,
    qemu_glPixelTexGenParameterfvSGIS,
    qemu_glPixelTexGenParameteriSGIS,
    qemu_glPixelTexGenParameterivSGIS,
    qemu_glPixelTexGenSGIX,
    qemu_glPixelTransferxOES,
    qemu_glPixelTransformParameterfEXT,
    qemu_glPixelTransformParameterfvEXT,
    qemu_glPixelTransformParameteriEXT,
    qemu_glPixelTransformParameterivEXT,
    qemu_glPixelZoomxOES,
    qemu_glPointAlongPathNV,
    qemu_glPointParameterf,
    qemu_glPointParameterfARB,
    qemu_glPointParameterfEXT,
    qemu_glPointParameterfSGIS,
    qemu_glPointParameterfv,
    qemu_glPointParameterfvARB,
    qemu_glPointParameterfvEXT,
    qemu_glPointParameterfvSGIS,
    qemu_glPointParameteri,
    qemu_glPointParameteriNV,
    qemu_glPointParameteriv,
    qemu_glPointParameterivNV,
    qemu_glPointParameterxvOES,
    qemu_glPointSizexOES,
    qemu_glPollAsyncSGIX,
    qemu_glPollInstrumentsSGIX,
    qemu_glPolygonOffsetClamp,
    qemu_glPolygonOffsetClampEXT,
    qemu_glPolygonOffsetEXT,
    qemu_glPolygonOffsetxOES,
    qemu_glPopDebugGroup,
    qemu_glPopGroupMarkerEXT,
    qemu_glPresentFrameDualFillNV,
    qemu_glPresentFrameKeyedNV,
    qemu_glPrimitiveBoundingBoxARB,
    qemu_glPrimitiveRestartIndex,
    qemu_glPrimitiveRestartIndexNV,
    qemu_glPrimitiveRestartNV,
    qemu_glPrioritizeTexturesEXT,
    qemu_glPrioritizeTexturesxOES,
    qemu_glProgramBinary,
    qemu_glProgramBufferParametersIivNV,
    qemu_glProgramBufferParametersIuivNV,
    qemu_glProgramBufferParametersfvNV,
    qemu_glProgramEnvParameter4dARB,
    qemu_glProgramEnvParameter4dvARB,
    qemu_glProgramEnvParameter4fARB,
    qemu_glProgramEnvParameter4fvARB,
    qemu_glProgramEnvParameterI4iNV,
    qemu_glProgramEnvParameterI4ivNV,
    qemu_glProgramEnvParameterI4uiNV,
    qemu_glProgramEnvParameterI4uivNV,
    qemu_glProgramEnvParameters4fvEXT,
    qemu_glProgramEnvParametersI4ivNV,
    qemu_glProgramEnvParametersI4uivNV,
    qemu_glProgramLocalParameter4dARB,
    qemu_glProgramLocalParameter4dvARB,
    qemu_glProgramLocalParameter4fARB,
    qemu_glProgramLocalParameter4fvARB,
    qemu_glProgramLocalParameterI4iNV,
    qemu_glProgramLocalParameterI4ivNV,
    qemu_glProgramLocalParameterI4uiNV,
    qemu_glProgramLocalParameterI4uivNV,
    qemu_glProgramLocalParameters4fvEXT,
    qemu_glProgramLocalParametersI4ivNV,
    qemu_glProgramLocalParametersI4uivNV,
    qemu_glProgramNamedParameter4dNV,
    qemu_glProgramNamedParameter4dvNV,
    qemu_glProgramNamedParameter4fNV,
    qemu_glProgramNamedParameter4fvNV,
    qemu_glProgramParameter4dNV,
    qemu_glProgramParameter4dvNV,
    qemu_glProgramParameter4fNV,
    qemu_glProgramParameter4fvNV,
    qemu_glProgramParameteri,
    qemu_glProgramParameteriARB,
    qemu_glProgramParameteriEXT,
    qemu_glProgramParameters4dvNV,
    qemu_glProgramParameters4fvNV,
    qemu_glProgramPathFragmentInputGenNV,
    qemu_glProgramStringARB,
    qemu_glProgramSubroutineParametersuivNV,
    qemu_glProgramUniform1d,
    qemu_glProgramUniform1dEXT,
    qemu_glProgramUniform1dv,
    qemu_glProgramUniform1dvEXT,
    qemu_glProgramUniform1f,
    qemu_glProgramUniform1fEXT,
    qemu_glProgramUniform1fv,
    qemu_glProgramUniform1fvEXT,
    qemu_glProgramUniform1i,
    qemu_glProgramUniform1i64ARB,
    qemu_glProgramUniform1i64NV,
    qemu_glProgramUniform1i64vARB,
    qemu_glProgramUniform1i64vNV,
    qemu_glProgramUniform1iEXT,
    qemu_glProgramUniform1iv,
    qemu_glProgramUniform1ivEXT,
    qemu_glProgramUniform1ui,
    qemu_glProgramUniform1ui64ARB,
    qemu_glProgramUniform1ui64NV,
    qemu_glProgramUniform1ui64vARB,
    qemu_glProgramUniform1ui64vNV,
    qemu_glProgramUniform1uiEXT,
    qemu_glProgramUniform1uiv,
    qemu_glProgramUniform1uivEXT,
    qemu_glProgramUniform2d,
    qemu_glProgramUniform2dEXT,
    qemu_glProgramUniform2dv,
    qemu_glProgramUniform2dvEXT,
    qemu_glProgramUniform2f,
    qemu_glProgramUniform2fEXT,
    qemu_glProgramUniform2fv,
    qemu_glProgramUniform2fvEXT,
    qemu_glProgramUniform2i,
    qemu_glProgramUniform2i64ARB,
    qemu_glProgramUniform2i64NV,
    qemu_glProgramUniform2i64vARB,
    qemu_glProgramUniform2i64vNV,
    qemu_glProgramUniform2iEXT,
    qemu_glProgramUniform2iv,
    qemu_glProgramUniform2ivEXT,
    qemu_glProgramUniform2ui,
    qemu_glProgramUniform2ui64ARB,
    qemu_glProgramUniform2ui64NV,
    qemu_glProgramUniform2ui64vARB,
    qemu_glProgramUniform2ui64vNV,
    qemu_glProgramUniform2uiEXT,
    qemu_glProgramUniform2uiv,
    qemu_glProgramUniform2uivEXT,
    qemu_glProgramUniform3d,
    qemu_glProgramUniform3dEXT,
    qemu_glProgramUniform3dv,
    qemu_glProgramUniform3dvEXT,
    qemu_glProgramUniform3f,
    qemu_glProgramUniform3fEXT,
    qemu_glProgramUniform3fv,
    qemu_glProgramUniform3fvEXT,
    qemu_glProgramUniform3i,
    qemu_glProgramUniform3i64ARB,
    qemu_glProgramUniform3i64NV,
    qemu_glProgramUniform3i64vARB,
    qemu_glProgramUniform3i64vNV,
    qemu_glProgramUniform3iEXT,
    qemu_glProgramUniform3iv,
    qemu_glProgramUniform3ivEXT,
    qemu_glProgramUniform3ui,
    qemu_glProgramUniform3ui64ARB,
    qemu_glProgramUniform3ui64NV,
    qemu_glProgramUniform3ui64vARB,
    qemu_glProgramUniform3ui64vNV,
    qemu_glProgramUniform3uiEXT,
    qemu_glProgramUniform3uiv,
    qemu_glProgramUniform3uivEXT,
    qemu_glProgramUniform4d,
    qemu_glProgramUniform4dEXT,
    qemu_glProgramUniform4dv,
    qemu_glProgramUniform4dvEXT,
    qemu_glProgramUniform4f,
    qemu_glProgramUniform4fEXT,
    qemu_glProgramUniform4fv,
    qemu_glProgramUniform4fvEXT,
    qemu_glProgramUniform4i,
    qemu_glProgramUniform4i64ARB,
    qemu_glProgramUniform4i64NV,
    qemu_glProgramUniform4i64vARB,
    qemu_glProgramUniform4i64vNV,
    qemu_glProgramUniform4iEXT,
    qemu_glProgramUniform4iv,
    qemu_glProgramUniform4ivEXT,
    qemu_glProgramUniform4ui,
    qemu_glProgramUniform4ui64ARB,
    qemu_glProgramUniform4ui64NV,
    qemu_glProgramUniform4ui64vARB,
    qemu_glProgramUniform4ui64vNV,
    qemu_glProgramUniform4uiEXT,
    qemu_glProgramUniform4uiv,
    qemu_glProgramUniform4uivEXT,
    qemu_glProgramUniformHandleui64ARB,
    qemu_glProgramUniformHandleui64NV,
    qemu_glProgramUniformHandleui64vARB,
    qemu_glProgramUniformHandleui64vNV,
    qemu_glProgramUniformMatrix2dv,
    qemu_glProgramUniformMatrix2dvEXT,
    qemu_glProgramUniformMatrix2fv,
    qemu_glProgramUniformMatrix2fvEXT,
    qemu_glProgramUniformMatrix2x3dv,
    qemu_glProgramUniformMatrix2x3dvEXT,
    qemu_glProgramUniformMatrix2x3fv,
    qemu_glProgramUniformMatrix2x3fvEXT,
    qemu_glProgramUniformMatrix2x4dv,
    qemu_glProgramUniformMatrix2x4dvEXT,
    qemu_glProgramUniformMatrix2x4fv,
    qemu_glProgramUniformMatrix2x4fvEXT,
    qemu_glProgramUniformMatrix3dv,
    qemu_glProgramUniformMatrix3dvEXT,
    qemu_glProgramUniformMatrix3fv,
    qemu_glProgramUniformMatrix3fvEXT,
    qemu_glProgramUniformMatrix3x2dv,
    qemu_glProgramUniformMatrix3x2dvEXT,
    qemu_glProgramUniformMatrix3x2fv,
    qemu_glProgramUniformMatrix3x2fvEXT,
    qemu_glProgramUniformMatrix3x4dv,
    qemu_glProgramUniformMatrix3x4dvEXT,
    qemu_glProgramUniformMatrix3x4fv,
    qemu_glProgramUniformMatrix3x4fvEXT,
    qemu_glProgramUniformMatrix4dv,
    qemu_glProgramUniformMatrix4dvEXT,
    qemu_glProgramUniformMatrix4fv,
    qemu_glProgramUniformMatrix4fvEXT,
    qemu_glProgramUniformMatrix4x2dv,
    qemu_glProgramUniformMatrix4x2dvEXT,
    qemu_glProgramUniformMatrix4x2fv,
    qemu_glProgramUniformMatrix4x2fvEXT,
    qemu_glProgramUniformMatrix4x3dv,
    qemu_glProgramUniformMatrix4x3dvEXT,
    qemu_glProgramUniformMatrix4x3fv,
    qemu_glProgramUniformMatrix4x3fvEXT,
    qemu_glProgramUniformui64NV,
    qemu_glProgramUniformui64vNV,
    qemu_glProgramVertexLimitNV,
    qemu_glProvokingVertex,
    qemu_glProvokingVertexEXT,
    qemu_glPushClientAttribDefaultEXT,
    qemu_glPushDebugGroup,
    qemu_glPushGroupMarkerEXT,
    qemu_glQueryCounter,
    qemu_glQueryMatrixxOES,
    qemu_glQueryObjectParameteruiAMD,
    qemu_glQueryResourceNV,
    qemu_glQueryResourceTagNV,
    qemu_glRasterPos2xOES,
    qemu_glRasterPos2xvOES,
    qemu_glRasterPos3xOES,
    qemu_glRasterPos3xvOES,
    qemu_glRasterPos4xOES,
    qemu_glRasterPos4xvOES,
    qemu_glRasterSamplesEXT,
    qemu_glReadBufferRegion,
    qemu_glReadInstrumentsSGIX,
    qemu_glReadnPixels,
    qemu_glReadnPixelsARB,
    qemu_glRectxOES,
    qemu_glRectxvOES,
    qemu_glReferencePlaneSGIX,
    qemu_glReleaseKeyedMutexWin32EXT,
    qemu_glReleaseShaderCompiler,
    qemu_glRenderGpuMaskNV,
    qemu_glRenderbufferStorage,
    qemu_glRenderbufferStorageEXT,
    qemu_glRenderbufferStorageMultisample,
    qemu_glRenderbufferStorageMultisampleAdvancedAMD,
    qemu_glRenderbufferStorageMultisampleCoverageNV,
    qemu_glRenderbufferStorageMultisampleEXT,
    qemu_glReplacementCodePointerSUN,
    qemu_glReplacementCodeubSUN,
    qemu_glReplacementCodeubvSUN,
    qemu_glReplacementCodeuiColor3fVertex3fSUN,
    qemu_glReplacementCodeuiColor3fVertex3fvSUN,
    qemu_glReplacementCodeuiColor4fNormal3fVertex3fSUN,
    qemu_glReplacementCodeuiColor4fNormal3fVertex3fvSUN,
    qemu_glReplacementCodeuiColor4ubVertex3fSUN,
    qemu_glReplacementCodeuiColor4ubVertex3fvSUN,
    qemu_glReplacementCodeuiNormal3fVertex3fSUN,
    qemu_glReplacementCodeuiNormal3fVertex3fvSUN,
    qemu_glReplacementCodeuiSUN,
    qemu_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN,
    qemu_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN,
    qemu_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN,
    qemu_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN,
    qemu_glReplacementCodeuiTexCoord2fVertex3fSUN,
    qemu_glReplacementCodeuiTexCoord2fVertex3fvSUN,
    qemu_glReplacementCodeuiVertex3fSUN,
    qemu_glReplacementCodeuiVertex3fvSUN,
    qemu_glReplacementCodeuivSUN,
    qemu_glReplacementCodeusSUN,
    qemu_glReplacementCodeusvSUN,
    qemu_glRequestResidentProgramsNV,
    qemu_glResetHistogram,
    qemu_glResetHistogramEXT,
    qemu_glResetMemoryObjectParameterNV,
    qemu_glResetMinmax,
    qemu_glResetMinmaxEXT,
    qemu_glResizeBuffersMESA,
    qemu_glResolveDepthValuesNV,
    qemu_glResumeTransformFeedback,
    qemu_glResumeTransformFeedbackNV,
    qemu_glRotatexOES,
    qemu_glSampleCoverage,
    qemu_glSampleCoverageARB,
    qemu_glSampleMapATI,
    qemu_glSampleMaskEXT,
    qemu_glSampleMaskIndexedNV,
    qemu_glSampleMaskSGIS,
    qemu_glSampleMaski,
    qemu_glSamplePatternEXT,
    qemu_glSamplePatternSGIS,
    qemu_glSamplerParameterIiv,
    qemu_glSamplerParameterIuiv,
    qemu_glSamplerParameterf,
    qemu_glSamplerParameterfv,
    qemu_glSamplerParameteri,
    qemu_glSamplerParameteriv,
    qemu_glScalexOES,
    qemu_glScissorArrayv,
    qemu_glScissorExclusiveArrayvNV,
    qemu_glScissorExclusiveNV,
    qemu_glScissorIndexed,
    qemu_glScissorIndexedv,
    qemu_glSecondaryColor3b,
    qemu_glSecondaryColor3bEXT,
    qemu_glSecondaryColor3bv,
    qemu_glSecondaryColor3bvEXT,
    qemu_glSecondaryColor3d,
    qemu_glSecondaryColor3dEXT,
    qemu_glSecondaryColor3dv,
    qemu_glSecondaryColor3dvEXT,
    qemu_glSecondaryColor3f,
    qemu_glSecondaryColor3fEXT,
    qemu_glSecondaryColor3fv,
    qemu_glSecondaryColor3fvEXT,
    qemu_glSecondaryColor3hNV,
    qemu_glSecondaryColor3hvNV,
    qemu_glSecondaryColor3i,
    qemu_glSecondaryColor3iEXT,
    qemu_glSecondaryColor3iv,
    qemu_glSecondaryColor3ivEXT,
    qemu_glSecondaryColor3s,
    qemu_glSecondaryColor3sEXT,
    qemu_glSecondaryColor3sv,
    qemu_glSecondaryColor3svEXT,
    qemu_glSecondaryColor3ub,
    qemu_glSecondaryColor3ubEXT,
    qemu_glSecondaryColor3ubv,
    qemu_glSecondaryColor3ubvEXT,
    qemu_glSecondaryColor3ui,
    qemu_glSecondaryColor3uiEXT,
    qemu_glSecondaryColor3uiv,
    qemu_glSecondaryColor3uivEXT,
    qemu_glSecondaryColor3us,
    qemu_glSecondaryColor3usEXT,
    qemu_glSecondaryColor3usv,
    qemu_glSecondaryColor3usvEXT,
    qemu_glSecondaryColorFormatNV,
    qemu_glSecondaryColorP3ui,
    qemu_glSecondaryColorP3uiv,
    qemu_glSecondaryColorPointer,
    qemu_glSecondaryColorPointerEXT,
    qemu_glSecondaryColorPointerListIBM,
    qemu_glSelectPerfMonitorCountersAMD,
    qemu_glSelectTextureCoordSetSGIS,
    qemu_glSelectTextureSGIS,
    qemu_glSemaphoreParameterui64vEXT,
    qemu_glSeparableFilter2D,
    qemu_glSeparableFilter2DEXT,
    qemu_glSetFenceAPPLE,
    qemu_glSetFenceNV,
    qemu_glSetFragmentShaderConstantATI,
    qemu_glSetInvariantEXT,
    qemu_glSetLocalConstantEXT,
    qemu_glSetMultisamplefvAMD,
    qemu_glShaderBinary,
    qemu_glShaderOp1EXT,
    qemu_glShaderOp2EXT,
    qemu_glShaderOp3EXT,
    qemu_glShaderSource,
    qemu_glShaderSourceARB,
    qemu_glShaderStorageBlockBinding,
    qemu_glShadingRateImageBarrierNV,
    qemu_glShadingRateImagePaletteNV,
    qemu_glShadingRateSampleOrderCustomNV,
    qemu_glShadingRateSampleOrderNV,
    qemu_glSharpenTexFuncSGIS,
    qemu_glSignalSemaphoreEXT,
    qemu_glSignalSemaphoreui64NVX,
    qemu_glSignalVkFenceNV,
    qemu_glSignalVkSemaphoreNV,
    qemu_glSpecializeShader,
    qemu_glSpecializeShaderARB,
    qemu_glSpriteParameterfSGIX,
    qemu_glSpriteParameterfvSGIX,
    qemu_glSpriteParameteriSGIX,
    qemu_glSpriteParameterivSGIX,
    qemu_glStartInstrumentsSGIX,
    qemu_glStateCaptureNV,
    qemu_glStencilClearTagEXT,
    qemu_glStencilFillPathInstancedNV,
    qemu_glStencilFillPathNV,
    qemu_glStencilFuncSeparate,
    qemu_glStencilFuncSeparateATI,
    qemu_glStencilMaskSeparate,
    qemu_glStencilOpSeparate,
    qemu_glStencilOpSeparateATI,
    qemu_glStencilOpValueAMD,
    qemu_glStencilStrokePathInstancedNV,
    qemu_glStencilStrokePathNV,
    qemu_glStencilThenCoverFillPathInstancedNV,
    qemu_glStencilThenCoverFillPathNV,
    qemu_glStencilThenCoverStrokePathInstancedNV,
    qemu_glStencilThenCoverStrokePathNV,
    qemu_glStopInstrumentsSGIX,
    qemu_glStringMarkerGREMEDY,
    qemu_glSubpixelPrecisionBiasNV,
    qemu_glSwizzleEXT,
    qemu_glSyncTextureINTEL,
    qemu_glTagSampleBufferSGIX,
    qemu_glTangent3bEXT,
    qemu_glTangent3bvEXT,
    qemu_glTangent3dEXT,
    qemu_glTangent3dvEXT,
    qemu_glTangent3fEXT,
    qemu_glTangent3fvEXT,
    qemu_glTangent3iEXT,
    qemu_glTangent3ivEXT,
    qemu_glTangent3sEXT,
    qemu_glTangent3svEXT,
    qemu_glTangentPointerEXT,
    qemu_glTbufferMask3DFX,
    qemu_glTessellationFactorAMD,
    qemu_glTessellationModeAMD,
    qemu_glTestFenceAPPLE,
    qemu_glTestFenceNV,
    qemu_glTestObjectAPPLE,
    qemu_glTexAttachMemoryNV,
    qemu_glTexBuffer,
    qemu_glTexBufferARB,
    qemu_glTexBufferEXT,
    qemu_glTexBufferRange,
    qemu_glTexBumpParameterfvATI,
    qemu_glTexBumpParameterivATI,
    qemu_glTexCoord1bOES,
    qemu_glTexCoord1bvOES,
    qemu_glTexCoord1hNV,
    qemu_glTexCoord1hvNV,
    qemu_glTexCoord1xOES,
    qemu_glTexCoord1xvOES,
    qemu_glTexCoord2bOES,
    qemu_glTexCoord2bvOES,
    qemu_glTexCoord2fColor3fVertex3fSUN,
    qemu_glTexCoord2fColor3fVertex3fvSUN,
    qemu_glTexCoord2fColor4fNormal3fVertex3fSUN,
    qemu_glTexCoord2fColor4fNormal3fVertex3fvSUN,
    qemu_glTexCoord2fColor4ubVertex3fSUN,
    qemu_glTexCoord2fColor4ubVertex3fvSUN,
    qemu_glTexCoord2fNormal3fVertex3fSUN,
    qemu_glTexCoord2fNormal3fVertex3fvSUN,
    qemu_glTexCoord2fVertex3fSUN,
    qemu_glTexCoord2fVertex3fvSUN,
    qemu_glTexCoord2hNV,
    qemu_glTexCoord2hvNV,
    qemu_glTexCoord2xOES,
    qemu_glTexCoord2xvOES,
    qemu_glTexCoord3bOES,
    qemu_glTexCoord3bvOES,
    qemu_glTexCoord3hNV,
    qemu_glTexCoord3hvNV,
    qemu_glTexCoord3xOES,
    qemu_glTexCoord3xvOES,
    qemu_glTexCoord4bOES,
    qemu_glTexCoord4bvOES,
    qemu_glTexCoord4fColor4fNormal3fVertex4fSUN,
    qemu_glTexCoord4fColor4fNormal3fVertex4fvSUN,
    qemu_glTexCoord4fVertex4fSUN,
    qemu_glTexCoord4fVertex4fvSUN,
    qemu_glTexCoord4hNV,
    qemu_glTexCoord4hvNV,
    qemu_glTexCoord4xOES,
    qemu_glTexCoord4xvOES,
    qemu_glTexCoordFormatNV,
    qemu_glTexCoordP1ui,
    qemu_glTexCoordP1uiv,
    qemu_glTexCoordP2ui,
    qemu_glTexCoordP2uiv,
    qemu_glTexCoordP3ui,
    qemu_glTexCoordP3uiv,
    qemu_glTexCoordP4ui,
    qemu_glTexCoordP4uiv,
    qemu_glTexCoordPointerEXT,
    qemu_glTexCoordPointerListIBM,
    qemu_glTexCoordPointervINTEL,
    qemu_glTexEnvxOES,
    qemu_glTexEnvxvOES,
    qemu_glTexFilterFuncSGIS,
    qemu_glTexGenxOES,
    qemu_glTexGenxvOES,
    qemu_glTexImage2DMultisample,
    qemu_glTexImage2DMultisampleCoverageNV,
    qemu_glTexImage3D,
    qemu_glTexImage3DEXT,
    qemu_glTexImage3DMultisample,
    qemu_glTexImage3DMultisampleCoverageNV,
    qemu_glTexImage4DSGIS,
    qemu_glTexPageCommitmentARB,
    qemu_glTexParameterIiv,
    qemu_glTexParameterIivEXT,
    qemu_glTexParameterIuiv,
    qemu_glTexParameterIuivEXT,
    qemu_glTexParameterxOES,
    qemu_glTexParameterxvOES,
    qemu_glTexRenderbufferNV,
    qemu_glTexStorage1D,
    qemu_glTexStorage2D,
    qemu_glTexStorage2DMultisample,
    qemu_glTexStorage3D,
    qemu_glTexStorage3DMultisample,
    qemu_glTexStorageMem1DEXT,
    qemu_glTexStorageMem2DEXT,
    qemu_glTexStorageMem2DMultisampleEXT,
    qemu_glTexStorageMem3DEXT,
    qemu_glTexStorageMem3DMultisampleEXT,
    qemu_glTexStorageSparseAMD,
    qemu_glTexSubImage1DEXT,
    qemu_glTexSubImage2DEXT,
    qemu_glTexSubImage3D,
    qemu_glTexSubImage3DEXT,
    qemu_glTexSubImage4DSGIS,
    qemu_glTextureAttachMemoryNV,
    qemu_glTextureBarrier,
    qemu_glTextureBarrierNV,
    qemu_glTextureBuffer,
    qemu_glTextureBufferEXT,
    qemu_glTextureBufferRange,
    qemu_glTextureBufferRangeEXT,
    qemu_glTextureColorMaskSGIS,
    qemu_glTextureImage1DEXT,
    qemu_glTextureImage2DEXT,
    qemu_glTextureImage2DMultisampleCoverageNV,
    qemu_glTextureImage2DMultisampleNV,
    qemu_glTextureImage3DEXT,
    qemu_glTextureImage3DMultisampleCoverageNV,
    qemu_glTextureImage3DMultisampleNV,
    qemu_glTextureLightEXT,
    qemu_glTextureMaterialEXT,
    qemu_glTextureNormalEXT,
    qemu_glTexturePageCommitmentEXT,
    qemu_glTextureParameterIiv,
    qemu_glTextureParameterIivEXT,
    qemu_glTextureParameterIuiv,
    qemu_glTextureParameterIuivEXT,
    qemu_glTextureParameterf,
    qemu_glTextureParameterfEXT,
    qemu_glTextureParameterfv,
    qemu_glTextureParameterfvEXT,
    qemu_glTextureParameteri,
    qemu_glTextureParameteriEXT,
    qemu_glTextureParameteriv,
    qemu_glTextureParameterivEXT,
    qemu_glTextureRangeAPPLE,
    qemu_glTextureRenderbufferEXT,
    qemu_glTextureStorage1D,
    qemu_glTextureStorage1DEXT,
    qemu_glTextureStorage2D,
    qemu_glTextureStorage2DEXT,
    qemu_glTextureStorage2DMultisample,
    qemu_glTextureStorage2DMultisampleEXT,
    qemu_glTextureStorage3D,
    qemu_glTextureStorage3DEXT,
    qemu_glTextureStorage3DMultisample,
    qemu_glTextureStorage3DMultisampleEXT,
    qemu_glTextureStorageMem1DEXT,
    qemu_glTextureStorageMem2DEXT,
    qemu_glTextureStorageMem2DMultisampleEXT,
    qemu_glTextureStorageMem3DEXT,
    qemu_glTextureStorageMem3DMultisampleEXT,
    qemu_glTextureStorageSparseAMD,
    qemu_glTextureSubImage1D,
    qemu_glTextureSubImage1DEXT,
    qemu_glTextureSubImage2D,
    qemu_glTextureSubImage2DEXT,
    qemu_glTextureSubImage3D,
    qemu_glTextureSubImage3DEXT,
    qemu_glTextureView,
    qemu_glTrackMatrixNV,
    qemu_glTransformFeedbackAttribsNV,
    qemu_glTransformFeedbackBufferBase,
    qemu_glTransformFeedbackBufferRange,
    qemu_glTransformFeedbackStreamAttribsNV,
    qemu_glTransformFeedbackVaryings,
    qemu_glTransformFeedbackVaryingsEXT,
    qemu_glTransformFeedbackVaryingsNV,
    qemu_glTransformPathNV,
    qemu_glTranslatexOES,
    qemu_glUniform1d,
    qemu_glUniform1dv,
    qemu_glUniform1f,
    qemu_glUniform1fARB,
    qemu_glUniform1fv,
    qemu_glUniform1fvARB,
    qemu_glUniform1i,
    qemu_glUniform1i64ARB,
    qemu_glUniform1i64NV,
    qemu_glUniform1i64vARB,
    qemu_glUniform1i64vNV,
    qemu_glUniform1iARB,
    qemu_glUniform1iv,
    qemu_glUniform1ivARB,
    qemu_glUniform1ui,
    qemu_glUniform1ui64ARB,
    qemu_glUniform1ui64NV,
    qemu_glUniform1ui64vARB,
    qemu_glUniform1ui64vNV,
    qemu_glUniform1uiEXT,
    qemu_glUniform1uiv,
    qemu_glUniform1uivEXT,
    qemu_glUniform2d,
    qemu_glUniform2dv,
    qemu_glUniform2f,
    qemu_glUniform2fARB,
    qemu_glUniform2fv,
    qemu_glUniform2fvARB,
    qemu_glUniform2i,
    qemu_glUniform2i64ARB,
    qemu_glUniform2i64NV,
    qemu_glUniform2i64vARB,
    qemu_glUniform2i64vNV,
    qemu_glUniform2iARB,
    qemu_glUniform2iv,
    qemu_glUniform2ivARB,
    qemu_glUniform2ui,
    qemu_glUniform2ui64ARB,
    qemu_glUniform2ui64NV,
    qemu_glUniform2ui64vARB,
    qemu_glUniform2ui64vNV,
    qemu_glUniform2uiEXT,
    qemu_glUniform2uiv,
    qemu_glUniform2uivEXT,
    qemu_glUniform3d,
    qemu_glUniform3dv,
    qemu_glUniform3f,
    qemu_glUniform3fARB,
    qemu_glUniform3fv,
    qemu_glUniform3fvARB,
    qemu_glUniform3i,
    qemu_glUniform3i64ARB,
    qemu_glUniform3i64NV,
    qemu_glUniform3i64vARB,
    qemu_glUniform3i64vNV,
    qemu_glUniform3iARB,
    qemu_glUniform3iv,
    qemu_glUniform3ivARB,
    qemu_glUniform3ui,
    qemu_glUniform3ui64ARB,
    qemu_glUniform3ui64NV,
    qemu_glUniform3ui64vARB,
    qemu_glUniform3ui64vNV,
    qemu_glUniform3uiEXT,
    qemu_glUniform3uiv,
    qemu_glUniform3uivEXT,
    qemu_glUniform4d,
    qemu_glUniform4dv,
    qemu_glUniform4f,
    qemu_glUniform4fARB,
    qemu_glUniform4fv,
    qemu_glUniform4fvARB,
    qemu_glUniform4i,
    qemu_glUniform4i64ARB,
    qemu_glUniform4i64NV,
    qemu_glUniform4i64vARB,
    qemu_glUniform4i64vNV,
    qemu_glUniform4iARB,
    qemu_glUniform4iv,
    qemu_glUniform4ivARB,
    qemu_glUniform4ui,
    qemu_glUniform4ui64ARB,
    qemu_glUniform4ui64NV,
    qemu_glUniform4ui64vARB,
    qemu_glUniform4ui64vNV,
    qemu_glUniform4uiEXT,
    qemu_glUniform4uiv,
    qemu_glUniform4uivEXT,
    qemu_glUniformBlockBinding,
    qemu_glUniformBufferEXT,
    qemu_glUniformHandleui64ARB,
    qemu_glUniformHandleui64NV,
    qemu_glUniformHandleui64vARB,
    qemu_glUniformHandleui64vNV,
    qemu_glUniformMatrix2dv,
    qemu_glUniformMatrix2fv,
    qemu_glUniformMatrix2fvARB,
    qemu_glUniformMatrix2x3dv,
    qemu_glUniformMatrix2x3fv,
    qemu_glUniformMatrix2x4dv,
    qemu_glUniformMatrix2x4fv,
    qemu_glUniformMatrix3dv,
    qemu_glUniformMatrix3fv,
    qemu_glUniformMatrix3fvARB,
    qemu_glUniformMatrix3x2dv,
    qemu_glUniformMatrix3x2fv,
    qemu_glUniformMatrix3x4dv,
    qemu_glUniformMatrix3x4fv,
    qemu_glUniformMatrix4dv,
    qemu_glUniformMatrix4fv,
    qemu_glUniformMatrix4fvARB,
    qemu_glUniformMatrix4x2dv,
    qemu_glUniformMatrix4x2fv,
    qemu_glUniformMatrix4x3dv,
    qemu_glUniformMatrix4x3fv,
    qemu_glUniformSubroutinesuiv,
    qemu_glUniformui64NV,
    qemu_glUniformui64vNV,
    qemu_glUnlockArraysEXT,
    qemu_glUnmapBuffer,
    qemu_glUnmapBufferARB,
    qemu_glUnmapNamedBuffer,
    qemu_glUnmapNamedBufferEXT,
    qemu_glUnmapObjectBufferATI,
    qemu_glUnmapTexture2DINTEL,
    qemu_glUpdateObjectBufferATI,
    qemu_glUploadGpuMaskNVX,
    qemu_glUseProgram,
    qemu_glUseProgramObjectARB,
    qemu_glUseProgramStages,
    qemu_glUseShaderProgramEXT,
    qemu_glVDPAUFiniNV,
    qemu_glVDPAUGetSurfaceivNV,
    qemu_glVDPAUInitNV,
    qemu_glVDPAUIsSurfaceNV,
    qemu_glVDPAUMapSurfacesNV,
    qemu_glVDPAURegisterOutputSurfaceNV,
    qemu_glVDPAURegisterVideoSurfaceNV,
    qemu_glVDPAURegisterVideoSurfaceWithPictureStructureNV,
    qemu_glVDPAUSurfaceAccessNV,
    qemu_glVDPAUUnmapSurfacesNV,
    qemu_glVDPAUUnregisterSurfaceNV,
    qemu_glValidateProgram,
    qemu_glValidateProgramARB,
    qemu_glValidateProgramPipeline,
    qemu_glVariantArrayObjectATI,
    qemu_glVariantPointerEXT,
    qemu_glVariantbvEXT,
    qemu_glVariantdvEXT,
    qemu_glVariantfvEXT,
    qemu_glVariantivEXT,
    qemu_glVariantsvEXT,
    qemu_glVariantubvEXT,
    qemu_glVariantuivEXT,
    qemu_glVariantusvEXT,
    qemu_glVertex2bOES,
    qemu_glVertex2bvOES,
    qemu_glVertex2hNV,
    qemu_glVertex2hvNV,
    qemu_glVertex2xOES,
    qemu_glVertex2xvOES,
    qemu_glVertex3bOES,
    qemu_glVertex3bvOES,
    qemu_glVertex3hNV,
    qemu_glVertex3hvNV,
    qemu_glVertex3xOES,
    qemu_glVertex3xvOES,
    qemu_glVertex4bOES,
    qemu_glVertex4bvOES,
    qemu_glVertex4hNV,
    qemu_glVertex4hvNV,
    qemu_glVertex4xOES,
    qemu_glVertex4xvOES,
    qemu_glVertexArrayAttribBinding,
    qemu_glVertexArrayAttribFormat,
    qemu_glVertexArrayAttribIFormat,
    qemu_glVertexArrayAttribLFormat,
    qemu_glVertexArrayBindVertexBufferEXT,
    qemu_glVertexArrayBindingDivisor,
    qemu_glVertexArrayColorOffsetEXT,
    qemu_glVertexArrayEdgeFlagOffsetEXT,
    qemu_glVertexArrayElementBuffer,
    qemu_glVertexArrayFogCoordOffsetEXT,
    qemu_glVertexArrayIndexOffsetEXT,
    qemu_glVertexArrayMultiTexCoordOffsetEXT,
    qemu_glVertexArrayNormalOffsetEXT,
    qemu_glVertexArrayParameteriAPPLE,
    qemu_glVertexArrayRangeAPPLE,
    qemu_glVertexArrayRangeNV,
    qemu_glVertexArraySecondaryColorOffsetEXT,
    qemu_glVertexArrayTexCoordOffsetEXT,
    qemu_glVertexArrayVertexAttribBindingEXT,
    qemu_glVertexArrayVertexAttribDivisorEXT,
    qemu_glVertexArrayVertexAttribFormatEXT,
    qemu_glVertexArrayVertexAttribIFormatEXT,
    qemu_glVertexArrayVertexAttribIOffsetEXT,
    qemu_glVertexArrayVertexAttribLFormatEXT,
    qemu_glVertexArrayVertexAttribLOffsetEXT,
    qemu_glVertexArrayVertexAttribOffsetEXT,
    qemu_glVertexArrayVertexBindingDivisorEXT,
    qemu_glVertexArrayVertexBuffer,
    qemu_glVertexArrayVertexBuffers,
    qemu_glVertexArrayVertexOffsetEXT,
    qemu_glVertexAttrib1d,
    qemu_glVertexAttrib1dARB,
    qemu_glVertexAttrib1dNV,
    qemu_glVertexAttrib1dv,
    qemu_glVertexAttrib1dvARB,
    qemu_glVertexAttrib1dvNV,
    qemu_glVertexAttrib1f,
    qemu_glVertexAttrib1fARB,
    qemu_glVertexAttrib1fNV,
    qemu_glVertexAttrib1fv,
    qemu_glVertexAttrib1fvARB,
    qemu_glVertexAttrib1fvNV,
    qemu_glVertexAttrib1hNV,
    qemu_glVertexAttrib1hvNV,
    qemu_glVertexAttrib1s,
    qemu_glVertexAttrib1sARB,
    qemu_glVertexAttrib1sNV,
    qemu_glVertexAttrib1sv,
    qemu_glVertexAttrib1svARB,
    qemu_glVertexAttrib1svNV,
    qemu_glVertexAttrib2d,
    qemu_glVertexAttrib2dARB,
    qemu_glVertexAttrib2dNV,
    qemu_glVertexAttrib2dv,
    qemu_glVertexAttrib2dvARB,
    qemu_glVertexAttrib2dvNV,
    qemu_glVertexAttrib2f,
    qemu_glVertexAttrib2fARB,
    qemu_glVertexAttrib2fNV,
    qemu_glVertexAttrib2fv,
    qemu_glVertexAttrib2fvARB,
    qemu_glVertexAttrib2fvNV,
    qemu_glVertexAttrib2hNV,
    qemu_glVertexAttrib2hvNV,
    qemu_glVertexAttrib2s,
    qemu_glVertexAttrib2sARB,
    qemu_glVertexAttrib2sNV,
    qemu_glVertexAttrib2sv,
    qemu_glVertexAttrib2svARB,
    qemu_glVertexAttrib2svNV,
    qemu_glVertexAttrib3d,
    qemu_glVertexAttrib3dARB,
    qemu_glVertexAttrib3dNV,
    qemu_glVertexAttrib3dv,
    qemu_glVertexAttrib3dvARB,
    qemu_glVertexAttrib3dvNV,
    qemu_glVertexAttrib3f,
    qemu_glVertexAttrib3fARB,
    qemu_glVertexAttrib3fNV,
    qemu_glVertexAttrib3fv,
    qemu_glVertexAttrib3fvARB,
    qemu_glVertexAttrib3fvNV,
    qemu_glVertexAttrib3hNV,
    qemu_glVertexAttrib3hvNV,
    qemu_glVertexAttrib3s,
    qemu_glVertexAttrib3sARB,
    qemu_glVertexAttrib3sNV,
    qemu_glVertexAttrib3sv,
    qemu_glVertexAttrib3svARB,
    qemu_glVertexAttrib3svNV,
    qemu_glVertexAttrib4Nbv,
    qemu_glVertexAttrib4NbvARB,
    qemu_glVertexAttrib4Niv,
    qemu_glVertexAttrib4NivARB,
    qemu_glVertexAttrib4Nsv,
    qemu_glVertexAttrib4NsvARB,
    qemu_glVertexAttrib4Nub,
    qemu_glVertexAttrib4NubARB,
    qemu_glVertexAttrib4Nubv,
    qemu_glVertexAttrib4NubvARB,
    qemu_glVertexAttrib4Nuiv,
    qemu_glVertexAttrib4NuivARB,
    qemu_glVertexAttrib4Nusv,
    qemu_glVertexAttrib4NusvARB,
    qemu_glVertexAttrib4bv,
    qemu_glVertexAttrib4bvARB,
    qemu_glVertexAttrib4d,
    qemu_glVertexAttrib4dARB,
    qemu_glVertexAttrib4dNV,
    qemu_glVertexAttrib4dv,
    qemu_glVertexAttrib4dvARB,
    qemu_glVertexAttrib4dvNV,
    qemu_glVertexAttrib4f,
    qemu_glVertexAttrib4fARB,
    qemu_glVertexAttrib4fNV,
    qemu_glVertexAttrib4fv,
    qemu_glVertexAttrib4fvARB,
    qemu_glVertexAttrib4fvNV,
    qemu_glVertexAttrib4hNV,
    qemu_glVertexAttrib4hvNV,
    qemu_glVertexAttrib4iv,
    qemu_glVertexAttrib4ivARB,
    qemu_glVertexAttrib4s,
    qemu_glVertexAttrib4sARB,
    qemu_glVertexAttrib4sNV,
    qemu_glVertexAttrib4sv,
    qemu_glVertexAttrib4svARB,
    qemu_glVertexAttrib4svNV,
    qemu_glVertexAttrib4ubNV,
    qemu_glVertexAttrib4ubv,
    qemu_glVertexAttrib4ubvARB,
    qemu_glVertexAttrib4ubvNV,
    qemu_glVertexAttrib4uiv,
    qemu_glVertexAttrib4uivARB,
    qemu_glVertexAttrib4usv,
    qemu_glVertexAttrib4usvARB,
    qemu_glVertexAttribArrayObjectATI,
    qemu_glVertexAttribBinding,
    qemu_glVertexAttribDivisor,
    qemu_glVertexAttribDivisorARB,
    qemu_glVertexAttribFormat,
    qemu_glVertexAttribFormatNV,
    qemu_glVertexAttribI1i,
    qemu_glVertexAttribI1iEXT,
    qemu_glVertexAttribI1iv,
    qemu_glVertexAttribI1ivEXT,
    qemu_glVertexAttribI1ui,
    qemu_glVertexAttribI1uiEXT,
    qemu_glVertexAttribI1uiv,
    qemu_glVertexAttribI1uivEXT,
    qemu_glVertexAttribI2i,
    qemu_glVertexAttribI2iEXT,
    qemu_glVertexAttribI2iv,
    qemu_glVertexAttribI2ivEXT,
    qemu_glVertexAttribI2ui,
    qemu_glVertexAttribI2uiEXT,
    qemu_glVertexAttribI2uiv,
    qemu_glVertexAttribI2uivEXT,
    qemu_glVertexAttribI3i,
    qemu_glVertexAttribI3iEXT,
    qemu_glVertexAttribI3iv,
    qemu_glVertexAttribI3ivEXT,
    qemu_glVertexAttribI3ui,
    qemu_glVertexAttribI3uiEXT,
    qemu_glVertexAttribI3uiv,
    qemu_glVertexAttribI3uivEXT,
    qemu_glVertexAttribI4bv,
    qemu_glVertexAttribI4bvEXT,
    qemu_glVertexAttribI4i,
    qemu_glVertexAttribI4iEXT,
    qemu_glVertexAttribI4iv,
    qemu_glVertexAttribI4ivEXT,
    qemu_glVertexAttribI4sv,
    qemu_glVertexAttribI4svEXT,
    qemu_glVertexAttribI4ubv,
    qemu_glVertexAttribI4ubvEXT,
    qemu_glVertexAttribI4ui,
    qemu_glVertexAttribI4uiEXT,
    qemu_glVertexAttribI4uiv,
    qemu_glVertexAttribI4uivEXT,
    qemu_glVertexAttribI4usv,
    qemu_glVertexAttribI4usvEXT,
    qemu_glVertexAttribIFormat,
    qemu_glVertexAttribIFormatNV,
    qemu_glVertexAttribIPointer,
    qemu_glVertexAttribIPointerEXT,
    qemu_glVertexAttribL1d,
    qemu_glVertexAttribL1dEXT,
    qemu_glVertexAttribL1dv,
    qemu_glVertexAttribL1dvEXT,
    qemu_glVertexAttribL1i64NV,
    qemu_glVertexAttribL1i64vNV,
    qemu_glVertexAttribL1ui64ARB,
    qemu_glVertexAttribL1ui64NV,
    qemu_glVertexAttribL1ui64vARB,
    qemu_glVertexAttribL1ui64vNV,
    qemu_glVertexAttribL2d,
    qemu_glVertexAttribL2dEXT,
    qemu_glVertexAttribL2dv,
    qemu_glVertexAttribL2dvEXT,
    qemu_glVertexAttribL2i64NV,
    qemu_glVertexAttribL2i64vNV,
    qemu_glVertexAttribL2ui64NV,
    qemu_glVertexAttribL2ui64vNV,
    qemu_glVertexAttribL3d,
    qemu_glVertexAttribL3dEXT,
    qemu_glVertexAttribL3dv,
    qemu_glVertexAttribL3dvEXT,
    qemu_glVertexAttribL3i64NV,
    qemu_glVertexAttribL3i64vNV,
    qemu_glVertexAttribL3ui64NV,
    qemu_glVertexAttribL3ui64vNV,
    qemu_glVertexAttribL4d,
    qemu_glVertexAttribL4dEXT,
    qemu_glVertexAttribL4dv,
    qemu_glVertexAttribL4dvEXT,
    qemu_glVertexAttribL4i64NV,
    qemu_glVertexAttribL4i64vNV,
    qemu_glVertexAttribL4ui64NV,
    qemu_glVertexAttribL4ui64vNV,
    qemu_glVertexAttribLFormat,
    qemu_glVertexAttribLFormatNV,
    qemu_glVertexAttribLPointer,
    qemu_glVertexAttribLPointerEXT,
    qemu_glVertexAttribP1ui,
    qemu_glVertexAttribP1uiv,
    qemu_glVertexAttribP2ui,
    qemu_glVertexAttribP2uiv,
    qemu_glVertexAttribP3ui,
    qemu_glVertexAttribP3uiv,
    qemu_glVertexAttribP4ui,
    qemu_glVertexAttribP4uiv,
    qemu_glVertexAttribParameteriAMD,
    qemu_glVertexAttribPointer,
    qemu_glVertexAttribPointerARB,
    qemu_glVertexAttribPointerNV,
    qemu_glVertexAttribs1dvNV,
    qemu_glVertexAttribs1fvNV,
    qemu_glVertexAttribs1hvNV,
    qemu_glVertexAttribs1svNV,
    qemu_glVertexAttribs2dvNV,
    qemu_glVertexAttribs2fvNV,
    qemu_glVertexAttribs2hvNV,
    qemu_glVertexAttribs2svNV,
    qemu_glVertexAttribs3dvNV,
    qemu_glVertexAttribs3fvNV,
    qemu_glVertexAttribs3hvNV,
    qemu_glVertexAttribs3svNV,
    qemu_glVertexAttribs4dvNV,
    qemu_glVertexAttribs4fvNV,
    qemu_glVertexAttribs4hvNV,
    qemu_glVertexAttribs4svNV,
    qemu_glVertexAttribs4ubvNV,
    qemu_glVertexBindingDivisor,
    qemu_glVertexBlendARB,
    qemu_glVertexBlendEnvfATI,
    qemu_glVertexBlendEnviATI,
    qemu_glVertexFormatNV,
    qemu_glVertexP2ui,
    qemu_glVertexP2uiv,
    qemu_glVertexP3ui,
    qemu_glVertexP3uiv,
    qemu_glVertexP4ui,
    qemu_glVertexP4uiv,
    qemu_glVertexPointerEXT,
    qemu_glVertexPointerListIBM,
    qemu_glVertexPointervINTEL,
    qemu_glVertexStream1dATI,
    qemu_glVertexStream1dvATI,
    qemu_glVertexStream1fATI,
    qemu_glVertexStream1fvATI,
    qemu_glVertexStream1iATI,
    qemu_glVertexStream1ivATI,
    qemu_glVertexStream1sATI,
    qemu_glVertexStream1svATI,
    qemu_glVertexStream2dATI,
    qemu_glVertexStream2dvATI,
    qemu_glVertexStream2fATI,
    qemu_glVertexStream2fvATI,
    qemu_glVertexStream2iATI,
    qemu_glVertexStream2ivATI,
    qemu_glVertexStream2sATI,
    qemu_glVertexStream2svATI,
    qemu_glVertexStream3dATI,
    qemu_glVertexStream3dvATI,
    qemu_glVertexStream3fATI,
    qemu_glVertexStream3fvATI,
    qemu_glVertexStream3iATI,
    qemu_glVertexStream3ivATI,
    qemu_glVertexStream3sATI,
    qemu_glVertexStream3svATI,
    qemu_glVertexStream4dATI,
    qemu_glVertexStream4dvATI,
    qemu_glVertexStream4fATI,
    qemu_glVertexStream4fvATI,
    qemu_glVertexStream4iATI,
    qemu_glVertexStream4ivATI,
    qemu_glVertexStream4sATI,
    qemu_glVertexStream4svATI,
    qemu_glVertexWeightPointerEXT,
    qemu_glVertexWeightfEXT,
    qemu_glVertexWeightfvEXT,
    qemu_glVertexWeighthNV,
    qemu_glVertexWeighthvNV,
    qemu_glVideoCaptureNV,
    qemu_glVideoCaptureStreamParameterdvNV,
    qemu_glVideoCaptureStreamParameterfvNV,
    qemu_glVideoCaptureStreamParameterivNV,
    qemu_glViewportArrayv,
    qemu_glViewportIndexedf,
    qemu_glViewportIndexedfv,
    qemu_glViewportPositionWScaleNV,
    qemu_glViewportSwizzleNV,
    qemu_glWaitSemaphoreEXT,
    qemu_glWaitSemaphoreui64NVX,
    qemu_glWaitSync,
    qemu_glWaitVkSemaphoreNV,
    qemu_glWeightPathsNV,
    qemu_glWeightPointerARB,
    qemu_glWeightbvARB,
    qemu_glWeightdvARB,
    qemu_glWeightfvARB,
    qemu_glWeightivARB,
    qemu_glWeightsvARB,
    qemu_glWeightubvARB,
    qemu_glWeightuivARB,
    qemu_glWeightusvARB,
    qemu_glWindowPos2d,
    qemu_glWindowPos2dARB,
    qemu_glWindowPos2dMESA,
    qemu_glWindowPos2dv,
    qemu_glWindowPos2dvARB,
    qemu_glWindowPos2dvMESA,
    qemu_glWindowPos2f,
    qemu_glWindowPos2fARB,
    qemu_glWindowPos2fMESA,
    qemu_glWindowPos2fv,
    qemu_glWindowPos2fvARB,
    qemu_glWindowPos2fvMESA,
    qemu_glWindowPos2i,
    qemu_glWindowPos2iARB,
    qemu_glWindowPos2iMESA,
    qemu_glWindowPos2iv,
    qemu_glWindowPos2ivARB,
    qemu_glWindowPos2ivMESA,
    qemu_glWindowPos2s,
    qemu_glWindowPos2sARB,
    qemu_glWindowPos2sMESA,
    qemu_glWindowPos2sv,
    qemu_glWindowPos2svARB,
    qemu_glWindowPos2svMESA,
    qemu_glWindowPos3d,
    qemu_glWindowPos3dARB,
    qemu_glWindowPos3dMESA,
    qemu_glWindowPos3dv,
    qemu_glWindowPos3dvARB,
    qemu_glWindowPos3dvMESA,
    qemu_glWindowPos3f,
    qemu_glWindowPos3fARB,
    qemu_glWindowPos3fMESA,
    qemu_glWindowPos3fv,
    qemu_glWindowPos3fvARB,
    qemu_glWindowPos3fvMESA,
    qemu_glWindowPos3i,
    qemu_glWindowPos3iARB,
    qemu_glWindowPos3iMESA,
    qemu_glWindowPos3iv,
    qemu_glWindowPos3ivARB,
    qemu_glWindowPos3ivMESA,
    qemu_glWindowPos3s,
    qemu_glWindowPos3sARB,
    qemu_glWindowPos3sMESA,
    qemu_glWindowPos3sv,
    qemu_glWindowPos3svARB,
    qemu_glWindowPos3svMESA,
    qemu_glWindowPos4dMESA,
    qemu_glWindowPos4dvMESA,
    qemu_glWindowPos4fMESA,
    qemu_glWindowPos4fvMESA,
    qemu_glWindowPos4iMESA,
    qemu_glWindowPos4ivMESA,
    qemu_glWindowPos4sMESA,
    qemu_glWindowPos4svMESA,
    qemu_glWindowRectanglesEXT,
    qemu_glWriteMaskEXT,
    qemu_wglAllocateMemoryNV,
    qemu_wglBindTexImageARB,
    qemu_wglChoosePixelFormatARB,
    qemu_wglCreateContextAttribsARB,
    qemu_wglCreatePbufferARB,
    qemu_wglDestroyPbufferARB,
    qemu_wglFreeMemoryNV,
    qemu_wglGetCurrentReadDCARB,
    qemu_wglGetExtensionsStringARB,
    qemu_wglGetExtensionsStringEXT,
    qemu_wglGetPbufferDCARB,
    qemu_wglGetPixelFormatAttribfvARB,
    qemu_wglGetPixelFormatAttribivARB,
    qemu_wglGetSwapIntervalEXT,
    qemu_wglMakeContextCurrentARB,
    qemu_wglQueryCurrentRendererIntegerWINE,
    qemu_wglQueryCurrentRendererStringWINE,
    qemu_wglQueryPbufferARB,
    qemu_wglQueryRendererIntegerWINE,
    qemu_wglQueryRendererStringWINE,
    qemu_wglReleasePbufferDCARB,
    qemu_wglReleaseTexImageARB,
    qemu_wglSetPbufferAttribARB,
    qemu_wglSetPixelFormatWINE,
    qemu_wglSwapIntervalEXT,
    qemu_wglCopyContext,
    qemu_wglCreateContext,
    qemu_wglDeleteContext,
    qemu_wglDescribePixelFormat,
    qemu_wglGetPixelFormat,
    qemu_wglGetProcAddress,
    qemu_wglMakeCurrent,
    qemu_wglSetPixelFormat,
    qemu_wglShareLists,
    qemu_wglSwapBuffers,
    qemu_wglChoosePixelFormat,
    qemu_wglCreateLayerContext,
    qemu_wglDescribeLayerPlane,
    qemu_wglGetCurrentContext,
    qemu_wglGetCurrentDC,
    qemu_wglGetDefaultProcAddress,
    qemu_wglGetLayerPaletteEntries,
    qemu_wglRealizeLayerPalette,
    qemu_wglSetLayerPaletteEntries,
    qemu_wglSwapLayerBuffers,
    qemu_wglUseFontBitmapsA,
    qemu_wglUseFontBitmapsW,
    qemu_wglUseFontOutlinesA,
    qemu_wglUseFontOutlinesW,
};

struct opengl_funcs host_funcs;
void init_norm_funcs(void) {
    HMODULE host = GetModuleHandleA("opengl32.dll");
    host_funcs.gl.p_glAccum = (void *)GetProcAddress(host, "glAccum");
    if (!host_funcs.gl.p_glAccum)
        WINE_ERR("Could not load glAccum\n");

    host_funcs.gl.p_glAlphaFunc = (void *)GetProcAddress(host, "glAlphaFunc");
    if (!host_funcs.gl.p_glAlphaFunc)
        WINE_ERR("Could not load glAlphaFunc\n");

    host_funcs.gl.p_glAreTexturesResident = (void *)GetProcAddress(host, "glAreTexturesResident");
    if (!host_funcs.gl.p_glAreTexturesResident)
        WINE_ERR("Could not load glAreTexturesResident\n");

    host_funcs.gl.p_glArrayElement = (void *)GetProcAddress(host, "glArrayElement");
    if (!host_funcs.gl.p_glArrayElement)
        WINE_ERR("Could not load glArrayElement\n");

    host_funcs.gl.p_glBegin = (void *)GetProcAddress(host, "glBegin");
    if (!host_funcs.gl.p_glBegin)
        WINE_ERR("Could not load glBegin\n");

    host_funcs.gl.p_glBindTexture = (void *)GetProcAddress(host, "glBindTexture");
    if (!host_funcs.gl.p_glBindTexture)
        WINE_ERR("Could not load glBindTexture\n");

    host_funcs.gl.p_glBitmap = (void *)GetProcAddress(host, "glBitmap");
    if (!host_funcs.gl.p_glBitmap)
        WINE_ERR("Could not load glBitmap\n");

    host_funcs.gl.p_glBlendFunc = (void *)GetProcAddress(host, "glBlendFunc");
    if (!host_funcs.gl.p_glBlendFunc)
        WINE_ERR("Could not load glBlendFunc\n");

    host_funcs.gl.p_glCallList = (void *)GetProcAddress(host, "glCallList");
    if (!host_funcs.gl.p_glCallList)
        WINE_ERR("Could not load glCallList\n");

    host_funcs.gl.p_glCallLists = (void *)GetProcAddress(host, "glCallLists");
    if (!host_funcs.gl.p_glCallLists)
        WINE_ERR("Could not load glCallLists\n");

    host_funcs.gl.p_glClear = (void *)GetProcAddress(host, "glClear");
    if (!host_funcs.gl.p_glClear)
        WINE_ERR("Could not load glClear\n");

    host_funcs.gl.p_glClearAccum = (void *)GetProcAddress(host, "glClearAccum");
    if (!host_funcs.gl.p_glClearAccum)
        WINE_ERR("Could not load glClearAccum\n");

    host_funcs.gl.p_glClearColor = (void *)GetProcAddress(host, "glClearColor");
    if (!host_funcs.gl.p_glClearColor)
        WINE_ERR("Could not load glClearColor\n");

    host_funcs.gl.p_glClearDepth = (void *)GetProcAddress(host, "glClearDepth");
    if (!host_funcs.gl.p_glClearDepth)
        WINE_ERR("Could not load glClearDepth\n");

    host_funcs.gl.p_glClearIndex = (void *)GetProcAddress(host, "glClearIndex");
    if (!host_funcs.gl.p_glClearIndex)
        WINE_ERR("Could not load glClearIndex\n");

    host_funcs.gl.p_glClearStencil = (void *)GetProcAddress(host, "glClearStencil");
    if (!host_funcs.gl.p_glClearStencil)
        WINE_ERR("Could not load glClearStencil\n");

    host_funcs.gl.p_glClipPlane = (void *)GetProcAddress(host, "glClipPlane");
    if (!host_funcs.gl.p_glClipPlane)
        WINE_ERR("Could not load glClipPlane\n");

    host_funcs.gl.p_glColor3b = (void *)GetProcAddress(host, "glColor3b");
    if (!host_funcs.gl.p_glColor3b)
        WINE_ERR("Could not load glColor3b\n");

    host_funcs.gl.p_glColor3bv = (void *)GetProcAddress(host, "glColor3bv");
    if (!host_funcs.gl.p_glColor3bv)
        WINE_ERR("Could not load glColor3bv\n");

    host_funcs.gl.p_glColor3d = (void *)GetProcAddress(host, "glColor3d");
    if (!host_funcs.gl.p_glColor3d)
        WINE_ERR("Could not load glColor3d\n");

    host_funcs.gl.p_glColor3dv = (void *)GetProcAddress(host, "glColor3dv");
    if (!host_funcs.gl.p_glColor3dv)
        WINE_ERR("Could not load glColor3dv\n");

    host_funcs.gl.p_glColor3f = (void *)GetProcAddress(host, "glColor3f");
    if (!host_funcs.gl.p_glColor3f)
        WINE_ERR("Could not load glColor3f\n");

    host_funcs.gl.p_glColor3fv = (void *)GetProcAddress(host, "glColor3fv");
    if (!host_funcs.gl.p_glColor3fv)
        WINE_ERR("Could not load glColor3fv\n");

    host_funcs.gl.p_glColor3i = (void *)GetProcAddress(host, "glColor3i");
    if (!host_funcs.gl.p_glColor3i)
        WINE_ERR("Could not load glColor3i\n");

    host_funcs.gl.p_glColor3iv = (void *)GetProcAddress(host, "glColor3iv");
    if (!host_funcs.gl.p_glColor3iv)
        WINE_ERR("Could not load glColor3iv\n");

    host_funcs.gl.p_glColor3s = (void *)GetProcAddress(host, "glColor3s");
    if (!host_funcs.gl.p_glColor3s)
        WINE_ERR("Could not load glColor3s\n");

    host_funcs.gl.p_glColor3sv = (void *)GetProcAddress(host, "glColor3sv");
    if (!host_funcs.gl.p_glColor3sv)
        WINE_ERR("Could not load glColor3sv\n");

    host_funcs.gl.p_glColor3ub = (void *)GetProcAddress(host, "glColor3ub");
    if (!host_funcs.gl.p_glColor3ub)
        WINE_ERR("Could not load glColor3ub\n");

    host_funcs.gl.p_glColor3ubv = (void *)GetProcAddress(host, "glColor3ubv");
    if (!host_funcs.gl.p_glColor3ubv)
        WINE_ERR("Could not load glColor3ubv\n");

    host_funcs.gl.p_glColor3ui = (void *)GetProcAddress(host, "glColor3ui");
    if (!host_funcs.gl.p_glColor3ui)
        WINE_ERR("Could not load glColor3ui\n");

    host_funcs.gl.p_glColor3uiv = (void *)GetProcAddress(host, "glColor3uiv");
    if (!host_funcs.gl.p_glColor3uiv)
        WINE_ERR("Could not load glColor3uiv\n");

    host_funcs.gl.p_glColor3us = (void *)GetProcAddress(host, "glColor3us");
    if (!host_funcs.gl.p_glColor3us)
        WINE_ERR("Could not load glColor3us\n");

    host_funcs.gl.p_glColor3usv = (void *)GetProcAddress(host, "glColor3usv");
    if (!host_funcs.gl.p_glColor3usv)
        WINE_ERR("Could not load glColor3usv\n");

    host_funcs.gl.p_glColor4b = (void *)GetProcAddress(host, "glColor4b");
    if (!host_funcs.gl.p_glColor4b)
        WINE_ERR("Could not load glColor4b\n");

    host_funcs.gl.p_glColor4bv = (void *)GetProcAddress(host, "glColor4bv");
    if (!host_funcs.gl.p_glColor4bv)
        WINE_ERR("Could not load glColor4bv\n");

    host_funcs.gl.p_glColor4d = (void *)GetProcAddress(host, "glColor4d");
    if (!host_funcs.gl.p_glColor4d)
        WINE_ERR("Could not load glColor4d\n");

    host_funcs.gl.p_glColor4dv = (void *)GetProcAddress(host, "glColor4dv");
    if (!host_funcs.gl.p_glColor4dv)
        WINE_ERR("Could not load glColor4dv\n");

    host_funcs.gl.p_glColor4f = (void *)GetProcAddress(host, "glColor4f");
    if (!host_funcs.gl.p_glColor4f)
        WINE_ERR("Could not load glColor4f\n");

    host_funcs.gl.p_glColor4fv = (void *)GetProcAddress(host, "glColor4fv");
    if (!host_funcs.gl.p_glColor4fv)
        WINE_ERR("Could not load glColor4fv\n");

    host_funcs.gl.p_glColor4i = (void *)GetProcAddress(host, "glColor4i");
    if (!host_funcs.gl.p_glColor4i)
        WINE_ERR("Could not load glColor4i\n");

    host_funcs.gl.p_glColor4iv = (void *)GetProcAddress(host, "glColor4iv");
    if (!host_funcs.gl.p_glColor4iv)
        WINE_ERR("Could not load glColor4iv\n");

    host_funcs.gl.p_glColor4s = (void *)GetProcAddress(host, "glColor4s");
    if (!host_funcs.gl.p_glColor4s)
        WINE_ERR("Could not load glColor4s\n");

    host_funcs.gl.p_glColor4sv = (void *)GetProcAddress(host, "glColor4sv");
    if (!host_funcs.gl.p_glColor4sv)
        WINE_ERR("Could not load glColor4sv\n");

    host_funcs.gl.p_glColor4ub = (void *)GetProcAddress(host, "glColor4ub");
    if (!host_funcs.gl.p_glColor4ub)
        WINE_ERR("Could not load glColor4ub\n");

    host_funcs.gl.p_glColor4ubv = (void *)GetProcAddress(host, "glColor4ubv");
    if (!host_funcs.gl.p_glColor4ubv)
        WINE_ERR("Could not load glColor4ubv\n");

    host_funcs.gl.p_glColor4ui = (void *)GetProcAddress(host, "glColor4ui");
    if (!host_funcs.gl.p_glColor4ui)
        WINE_ERR("Could not load glColor4ui\n");

    host_funcs.gl.p_glColor4uiv = (void *)GetProcAddress(host, "glColor4uiv");
    if (!host_funcs.gl.p_glColor4uiv)
        WINE_ERR("Could not load glColor4uiv\n");

    host_funcs.gl.p_glColor4us = (void *)GetProcAddress(host, "glColor4us");
    if (!host_funcs.gl.p_glColor4us)
        WINE_ERR("Could not load glColor4us\n");

    host_funcs.gl.p_glColor4usv = (void *)GetProcAddress(host, "glColor4usv");
    if (!host_funcs.gl.p_glColor4usv)
        WINE_ERR("Could not load glColor4usv\n");

    host_funcs.gl.p_glColorMask = (void *)GetProcAddress(host, "glColorMask");
    if (!host_funcs.gl.p_glColorMask)
        WINE_ERR("Could not load glColorMask\n");

    host_funcs.gl.p_glColorMaterial = (void *)GetProcAddress(host, "glColorMaterial");
    if (!host_funcs.gl.p_glColorMaterial)
        WINE_ERR("Could not load glColorMaterial\n");

    host_funcs.gl.p_glColorPointer = (void *)GetProcAddress(host, "glColorPointer");
    if (!host_funcs.gl.p_glColorPointer)
        WINE_ERR("Could not load glColorPointer\n");

    host_funcs.gl.p_glCopyPixels = (void *)GetProcAddress(host, "glCopyPixels");
    if (!host_funcs.gl.p_glCopyPixels)
        WINE_ERR("Could not load glCopyPixels\n");

    host_funcs.gl.p_glCopyTexImage1D = (void *)GetProcAddress(host, "glCopyTexImage1D");
    if (!host_funcs.gl.p_glCopyTexImage1D)
        WINE_ERR("Could not load glCopyTexImage1D\n");

    host_funcs.gl.p_glCopyTexImage2D = (void *)GetProcAddress(host, "glCopyTexImage2D");
    if (!host_funcs.gl.p_glCopyTexImage2D)
        WINE_ERR("Could not load glCopyTexImage2D\n");

    host_funcs.gl.p_glCopyTexSubImage1D = (void *)GetProcAddress(host, "glCopyTexSubImage1D");
    if (!host_funcs.gl.p_glCopyTexSubImage1D)
        WINE_ERR("Could not load glCopyTexSubImage1D\n");

    host_funcs.gl.p_glCopyTexSubImage2D = (void *)GetProcAddress(host, "glCopyTexSubImage2D");
    if (!host_funcs.gl.p_glCopyTexSubImage2D)
        WINE_ERR("Could not load glCopyTexSubImage2D\n");

    host_funcs.gl.p_glCullFace = (void *)GetProcAddress(host, "glCullFace");
    if (!host_funcs.gl.p_glCullFace)
        WINE_ERR("Could not load glCullFace\n");

    host_funcs.gl.p_glDeleteLists = (void *)GetProcAddress(host, "glDeleteLists");
    if (!host_funcs.gl.p_glDeleteLists)
        WINE_ERR("Could not load glDeleteLists\n");

    host_funcs.gl.p_glDeleteTextures = (void *)GetProcAddress(host, "glDeleteTextures");
    if (!host_funcs.gl.p_glDeleteTextures)
        WINE_ERR("Could not load glDeleteTextures\n");

    host_funcs.gl.p_glDepthFunc = (void *)GetProcAddress(host, "glDepthFunc");
    if (!host_funcs.gl.p_glDepthFunc)
        WINE_ERR("Could not load glDepthFunc\n");

    host_funcs.gl.p_glDepthMask = (void *)GetProcAddress(host, "glDepthMask");
    if (!host_funcs.gl.p_glDepthMask)
        WINE_ERR("Could not load glDepthMask\n");

    host_funcs.gl.p_glDepthRange = (void *)GetProcAddress(host, "glDepthRange");
    if (!host_funcs.gl.p_glDepthRange)
        WINE_ERR("Could not load glDepthRange\n");

    host_funcs.gl.p_glDisable = (void *)GetProcAddress(host, "glDisable");
    if (!host_funcs.gl.p_glDisable)
        WINE_ERR("Could not load glDisable\n");

    host_funcs.gl.p_glDisableClientState = (void *)GetProcAddress(host, "glDisableClientState");
    if (!host_funcs.gl.p_glDisableClientState)
        WINE_ERR("Could not load glDisableClientState\n");

    host_funcs.gl.p_glDrawArrays = (void *)GetProcAddress(host, "glDrawArrays");
    if (!host_funcs.gl.p_glDrawArrays)
        WINE_ERR("Could not load glDrawArrays\n");

    host_funcs.gl.p_glDrawBuffer = (void *)GetProcAddress(host, "glDrawBuffer");
    if (!host_funcs.gl.p_glDrawBuffer)
        WINE_ERR("Could not load glDrawBuffer\n");

    host_funcs.gl.p_glDrawElements = (void *)GetProcAddress(host, "glDrawElements");
    if (!host_funcs.gl.p_glDrawElements)
        WINE_ERR("Could not load glDrawElements\n");

    host_funcs.gl.p_glDrawPixels = (void *)GetProcAddress(host, "glDrawPixels");
    if (!host_funcs.gl.p_glDrawPixels)
        WINE_ERR("Could not load glDrawPixels\n");

    host_funcs.gl.p_glEdgeFlag = (void *)GetProcAddress(host, "glEdgeFlag");
    if (!host_funcs.gl.p_glEdgeFlag)
        WINE_ERR("Could not load glEdgeFlag\n");

    host_funcs.gl.p_glEdgeFlagPointer = (void *)GetProcAddress(host, "glEdgeFlagPointer");
    if (!host_funcs.gl.p_glEdgeFlagPointer)
        WINE_ERR("Could not load glEdgeFlagPointer\n");

    host_funcs.gl.p_glEdgeFlagv = (void *)GetProcAddress(host, "glEdgeFlagv");
    if (!host_funcs.gl.p_glEdgeFlagv)
        WINE_ERR("Could not load glEdgeFlagv\n");

    host_funcs.gl.p_glEnable = (void *)GetProcAddress(host, "glEnable");
    if (!host_funcs.gl.p_glEnable)
        WINE_ERR("Could not load glEnable\n");

    host_funcs.gl.p_glEnableClientState = (void *)GetProcAddress(host, "glEnableClientState");
    if (!host_funcs.gl.p_glEnableClientState)
        WINE_ERR("Could not load glEnableClientState\n");

    host_funcs.gl.p_glEnd = (void *)GetProcAddress(host, "glEnd");
    if (!host_funcs.gl.p_glEnd)
        WINE_ERR("Could not load glEnd\n");

    host_funcs.gl.p_glEndList = (void *)GetProcAddress(host, "glEndList");
    if (!host_funcs.gl.p_glEndList)
        WINE_ERR("Could not load glEndList\n");

    host_funcs.gl.p_glEvalCoord1d = (void *)GetProcAddress(host, "glEvalCoord1d");
    if (!host_funcs.gl.p_glEvalCoord1d)
        WINE_ERR("Could not load glEvalCoord1d\n");

    host_funcs.gl.p_glEvalCoord1dv = (void *)GetProcAddress(host, "glEvalCoord1dv");
    if (!host_funcs.gl.p_glEvalCoord1dv)
        WINE_ERR("Could not load glEvalCoord1dv\n");

    host_funcs.gl.p_glEvalCoord1f = (void *)GetProcAddress(host, "glEvalCoord1f");
    if (!host_funcs.gl.p_glEvalCoord1f)
        WINE_ERR("Could not load glEvalCoord1f\n");

    host_funcs.gl.p_glEvalCoord1fv = (void *)GetProcAddress(host, "glEvalCoord1fv");
    if (!host_funcs.gl.p_glEvalCoord1fv)
        WINE_ERR("Could not load glEvalCoord1fv\n");

    host_funcs.gl.p_glEvalCoord2d = (void *)GetProcAddress(host, "glEvalCoord2d");
    if (!host_funcs.gl.p_glEvalCoord2d)
        WINE_ERR("Could not load glEvalCoord2d\n");

    host_funcs.gl.p_glEvalCoord2dv = (void *)GetProcAddress(host, "glEvalCoord2dv");
    if (!host_funcs.gl.p_glEvalCoord2dv)
        WINE_ERR("Could not load glEvalCoord2dv\n");

    host_funcs.gl.p_glEvalCoord2f = (void *)GetProcAddress(host, "glEvalCoord2f");
    if (!host_funcs.gl.p_glEvalCoord2f)
        WINE_ERR("Could not load glEvalCoord2f\n");

    host_funcs.gl.p_glEvalCoord2fv = (void *)GetProcAddress(host, "glEvalCoord2fv");
    if (!host_funcs.gl.p_glEvalCoord2fv)
        WINE_ERR("Could not load glEvalCoord2fv\n");

    host_funcs.gl.p_glEvalMesh1 = (void *)GetProcAddress(host, "glEvalMesh1");
    if (!host_funcs.gl.p_glEvalMesh1)
        WINE_ERR("Could not load glEvalMesh1\n");

    host_funcs.gl.p_glEvalMesh2 = (void *)GetProcAddress(host, "glEvalMesh2");
    if (!host_funcs.gl.p_glEvalMesh2)
        WINE_ERR("Could not load glEvalMesh2\n");

    host_funcs.gl.p_glEvalPoint1 = (void *)GetProcAddress(host, "glEvalPoint1");
    if (!host_funcs.gl.p_glEvalPoint1)
        WINE_ERR("Could not load glEvalPoint1\n");

    host_funcs.gl.p_glEvalPoint2 = (void *)GetProcAddress(host, "glEvalPoint2");
    if (!host_funcs.gl.p_glEvalPoint2)
        WINE_ERR("Could not load glEvalPoint2\n");

    host_funcs.gl.p_glFeedbackBuffer = (void *)GetProcAddress(host, "glFeedbackBuffer");
    if (!host_funcs.gl.p_glFeedbackBuffer)
        WINE_ERR("Could not load glFeedbackBuffer\n");

    host_funcs.gl.p_glFinish = (void *)GetProcAddress(host, "glFinish");
    if (!host_funcs.gl.p_glFinish)
        WINE_ERR("Could not load glFinish\n");

    host_funcs.gl.p_glFlush = (void *)GetProcAddress(host, "glFlush");
    if (!host_funcs.gl.p_glFlush)
        WINE_ERR("Could not load glFlush\n");

    host_funcs.gl.p_glFogf = (void *)GetProcAddress(host, "glFogf");
    if (!host_funcs.gl.p_glFogf)
        WINE_ERR("Could not load glFogf\n");

    host_funcs.gl.p_glFogfv = (void *)GetProcAddress(host, "glFogfv");
    if (!host_funcs.gl.p_glFogfv)
        WINE_ERR("Could not load glFogfv\n");

    host_funcs.gl.p_glFogi = (void *)GetProcAddress(host, "glFogi");
    if (!host_funcs.gl.p_glFogi)
        WINE_ERR("Could not load glFogi\n");

    host_funcs.gl.p_glFogiv = (void *)GetProcAddress(host, "glFogiv");
    if (!host_funcs.gl.p_glFogiv)
        WINE_ERR("Could not load glFogiv\n");

    host_funcs.gl.p_glFrontFace = (void *)GetProcAddress(host, "glFrontFace");
    if (!host_funcs.gl.p_glFrontFace)
        WINE_ERR("Could not load glFrontFace\n");

    host_funcs.gl.p_glFrustum = (void *)GetProcAddress(host, "glFrustum");
    if (!host_funcs.gl.p_glFrustum)
        WINE_ERR("Could not load glFrustum\n");

    host_funcs.gl.p_glGenLists = (void *)GetProcAddress(host, "glGenLists");
    if (!host_funcs.gl.p_glGenLists)
        WINE_ERR("Could not load glGenLists\n");

    host_funcs.gl.p_glGenTextures = (void *)GetProcAddress(host, "glGenTextures");
    if (!host_funcs.gl.p_glGenTextures)
        WINE_ERR("Could not load glGenTextures\n");

    host_funcs.gl.p_glGetBooleanv = (void *)GetProcAddress(host, "glGetBooleanv");
    if (!host_funcs.gl.p_glGetBooleanv)
        WINE_ERR("Could not load glGetBooleanv\n");

    host_funcs.gl.p_glGetClipPlane = (void *)GetProcAddress(host, "glGetClipPlane");
    if (!host_funcs.gl.p_glGetClipPlane)
        WINE_ERR("Could not load glGetClipPlane\n");

    host_funcs.gl.p_glGetDoublev = (void *)GetProcAddress(host, "glGetDoublev");
    if (!host_funcs.gl.p_glGetDoublev)
        WINE_ERR("Could not load glGetDoublev\n");

    host_funcs.gl.p_glGetError = (void *)GetProcAddress(host, "glGetError");
    if (!host_funcs.gl.p_glGetError)
        WINE_ERR("Could not load glGetError\n");

    host_funcs.gl.p_glGetFloatv = (void *)GetProcAddress(host, "glGetFloatv");
    if (!host_funcs.gl.p_glGetFloatv)
        WINE_ERR("Could not load glGetFloatv\n");

    host_funcs.gl.p_glGetIntegerv = (void *)GetProcAddress(host, "glGetIntegerv");
    if (!host_funcs.gl.p_glGetIntegerv)
        WINE_ERR("Could not load glGetIntegerv\n");

    host_funcs.gl.p_glGetLightfv = (void *)GetProcAddress(host, "glGetLightfv");
    if (!host_funcs.gl.p_glGetLightfv)
        WINE_ERR("Could not load glGetLightfv\n");

    host_funcs.gl.p_glGetLightiv = (void *)GetProcAddress(host, "glGetLightiv");
    if (!host_funcs.gl.p_glGetLightiv)
        WINE_ERR("Could not load glGetLightiv\n");

    host_funcs.gl.p_glGetMapdv = (void *)GetProcAddress(host, "glGetMapdv");
    if (!host_funcs.gl.p_glGetMapdv)
        WINE_ERR("Could not load glGetMapdv\n");

    host_funcs.gl.p_glGetMapfv = (void *)GetProcAddress(host, "glGetMapfv");
    if (!host_funcs.gl.p_glGetMapfv)
        WINE_ERR("Could not load glGetMapfv\n");

    host_funcs.gl.p_glGetMapiv = (void *)GetProcAddress(host, "glGetMapiv");
    if (!host_funcs.gl.p_glGetMapiv)
        WINE_ERR("Could not load glGetMapiv\n");

    host_funcs.gl.p_glGetMaterialfv = (void *)GetProcAddress(host, "glGetMaterialfv");
    if (!host_funcs.gl.p_glGetMaterialfv)
        WINE_ERR("Could not load glGetMaterialfv\n");

    host_funcs.gl.p_glGetMaterialiv = (void *)GetProcAddress(host, "glGetMaterialiv");
    if (!host_funcs.gl.p_glGetMaterialiv)
        WINE_ERR("Could not load glGetMaterialiv\n");

    host_funcs.gl.p_glGetPixelMapfv = (void *)GetProcAddress(host, "glGetPixelMapfv");
    if (!host_funcs.gl.p_glGetPixelMapfv)
        WINE_ERR("Could not load glGetPixelMapfv\n");

    host_funcs.gl.p_glGetPixelMapuiv = (void *)GetProcAddress(host, "glGetPixelMapuiv");
    if (!host_funcs.gl.p_glGetPixelMapuiv)
        WINE_ERR("Could not load glGetPixelMapuiv\n");

    host_funcs.gl.p_glGetPixelMapusv = (void *)GetProcAddress(host, "glGetPixelMapusv");
    if (!host_funcs.gl.p_glGetPixelMapusv)
        WINE_ERR("Could not load glGetPixelMapusv\n");

    host_funcs.gl.p_glGetPointerv = (void *)GetProcAddress(host, "glGetPointerv");
    if (!host_funcs.gl.p_glGetPointerv)
        WINE_ERR("Could not load glGetPointerv\n");

    host_funcs.gl.p_glGetPolygonStipple = (void *)GetProcAddress(host, "glGetPolygonStipple");
    if (!host_funcs.gl.p_glGetPolygonStipple)
        WINE_ERR("Could not load glGetPolygonStipple\n");

    host_funcs.gl.p_glGetString = (void *)GetProcAddress(host, "glGetString");
    if (!host_funcs.gl.p_glGetString)
        WINE_ERR("Could not load glGetString\n");

    host_funcs.gl.p_glGetTexEnvfv = (void *)GetProcAddress(host, "glGetTexEnvfv");
    if (!host_funcs.gl.p_glGetTexEnvfv)
        WINE_ERR("Could not load glGetTexEnvfv\n");

    host_funcs.gl.p_glGetTexEnviv = (void *)GetProcAddress(host, "glGetTexEnviv");
    if (!host_funcs.gl.p_glGetTexEnviv)
        WINE_ERR("Could not load glGetTexEnviv\n");

    host_funcs.gl.p_glGetTexGendv = (void *)GetProcAddress(host, "glGetTexGendv");
    if (!host_funcs.gl.p_glGetTexGendv)
        WINE_ERR("Could not load glGetTexGendv\n");

    host_funcs.gl.p_glGetTexGenfv = (void *)GetProcAddress(host, "glGetTexGenfv");
    if (!host_funcs.gl.p_glGetTexGenfv)
        WINE_ERR("Could not load glGetTexGenfv\n");

    host_funcs.gl.p_glGetTexGeniv = (void *)GetProcAddress(host, "glGetTexGeniv");
    if (!host_funcs.gl.p_glGetTexGeniv)
        WINE_ERR("Could not load glGetTexGeniv\n");

    host_funcs.gl.p_glGetTexImage = (void *)GetProcAddress(host, "glGetTexImage");
    if (!host_funcs.gl.p_glGetTexImage)
        WINE_ERR("Could not load glGetTexImage\n");

    host_funcs.gl.p_glGetTexLevelParameterfv = (void *)GetProcAddress(host, "glGetTexLevelParameterfv");
    if (!host_funcs.gl.p_glGetTexLevelParameterfv)
        WINE_ERR("Could not load glGetTexLevelParameterfv\n");

    host_funcs.gl.p_glGetTexLevelParameteriv = (void *)GetProcAddress(host, "glGetTexLevelParameteriv");
    if (!host_funcs.gl.p_glGetTexLevelParameteriv)
        WINE_ERR("Could not load glGetTexLevelParameteriv\n");

    host_funcs.gl.p_glGetTexParameterfv = (void *)GetProcAddress(host, "glGetTexParameterfv");
    if (!host_funcs.gl.p_glGetTexParameterfv)
        WINE_ERR("Could not load glGetTexParameterfv\n");

    host_funcs.gl.p_glGetTexParameteriv = (void *)GetProcAddress(host, "glGetTexParameteriv");
    if (!host_funcs.gl.p_glGetTexParameteriv)
        WINE_ERR("Could not load glGetTexParameteriv\n");

    host_funcs.gl.p_glHint = (void *)GetProcAddress(host, "glHint");
    if (!host_funcs.gl.p_glHint)
        WINE_ERR("Could not load glHint\n");

    host_funcs.gl.p_glIndexMask = (void *)GetProcAddress(host, "glIndexMask");
    if (!host_funcs.gl.p_glIndexMask)
        WINE_ERR("Could not load glIndexMask\n");

    host_funcs.gl.p_glIndexPointer = (void *)GetProcAddress(host, "glIndexPointer");
    if (!host_funcs.gl.p_glIndexPointer)
        WINE_ERR("Could not load glIndexPointer\n");

    host_funcs.gl.p_glIndexd = (void *)GetProcAddress(host, "glIndexd");
    if (!host_funcs.gl.p_glIndexd)
        WINE_ERR("Could not load glIndexd\n");

    host_funcs.gl.p_glIndexdv = (void *)GetProcAddress(host, "glIndexdv");
    if (!host_funcs.gl.p_glIndexdv)
        WINE_ERR("Could not load glIndexdv\n");

    host_funcs.gl.p_glIndexf = (void *)GetProcAddress(host, "glIndexf");
    if (!host_funcs.gl.p_glIndexf)
        WINE_ERR("Could not load glIndexf\n");

    host_funcs.gl.p_glIndexfv = (void *)GetProcAddress(host, "glIndexfv");
    if (!host_funcs.gl.p_glIndexfv)
        WINE_ERR("Could not load glIndexfv\n");

    host_funcs.gl.p_glIndexi = (void *)GetProcAddress(host, "glIndexi");
    if (!host_funcs.gl.p_glIndexi)
        WINE_ERR("Could not load glIndexi\n");

    host_funcs.gl.p_glIndexiv = (void *)GetProcAddress(host, "glIndexiv");
    if (!host_funcs.gl.p_glIndexiv)
        WINE_ERR("Could not load glIndexiv\n");

    host_funcs.gl.p_glIndexs = (void *)GetProcAddress(host, "glIndexs");
    if (!host_funcs.gl.p_glIndexs)
        WINE_ERR("Could not load glIndexs\n");

    host_funcs.gl.p_glIndexsv = (void *)GetProcAddress(host, "glIndexsv");
    if (!host_funcs.gl.p_glIndexsv)
        WINE_ERR("Could not load glIndexsv\n");

    host_funcs.gl.p_glIndexub = (void *)GetProcAddress(host, "glIndexub");
    if (!host_funcs.gl.p_glIndexub)
        WINE_ERR("Could not load glIndexub\n");

    host_funcs.gl.p_glIndexubv = (void *)GetProcAddress(host, "glIndexubv");
    if (!host_funcs.gl.p_glIndexubv)
        WINE_ERR("Could not load glIndexubv\n");

    host_funcs.gl.p_glInitNames = (void *)GetProcAddress(host, "glInitNames");
    if (!host_funcs.gl.p_glInitNames)
        WINE_ERR("Could not load glInitNames\n");

    host_funcs.gl.p_glInterleavedArrays = (void *)GetProcAddress(host, "glInterleavedArrays");
    if (!host_funcs.gl.p_glInterleavedArrays)
        WINE_ERR("Could not load glInterleavedArrays\n");

    host_funcs.gl.p_glIsEnabled = (void *)GetProcAddress(host, "glIsEnabled");
    if (!host_funcs.gl.p_glIsEnabled)
        WINE_ERR("Could not load glIsEnabled\n");

    host_funcs.gl.p_glIsList = (void *)GetProcAddress(host, "glIsList");
    if (!host_funcs.gl.p_glIsList)
        WINE_ERR("Could not load glIsList\n");

    host_funcs.gl.p_glIsTexture = (void *)GetProcAddress(host, "glIsTexture");
    if (!host_funcs.gl.p_glIsTexture)
        WINE_ERR("Could not load glIsTexture\n");

    host_funcs.gl.p_glLightModelf = (void *)GetProcAddress(host, "glLightModelf");
    if (!host_funcs.gl.p_glLightModelf)
        WINE_ERR("Could not load glLightModelf\n");

    host_funcs.gl.p_glLightModelfv = (void *)GetProcAddress(host, "glLightModelfv");
    if (!host_funcs.gl.p_glLightModelfv)
        WINE_ERR("Could not load glLightModelfv\n");

    host_funcs.gl.p_glLightModeli = (void *)GetProcAddress(host, "glLightModeli");
    if (!host_funcs.gl.p_glLightModeli)
        WINE_ERR("Could not load glLightModeli\n");

    host_funcs.gl.p_glLightModeliv = (void *)GetProcAddress(host, "glLightModeliv");
    if (!host_funcs.gl.p_glLightModeliv)
        WINE_ERR("Could not load glLightModeliv\n");

    host_funcs.gl.p_glLightf = (void *)GetProcAddress(host, "glLightf");
    if (!host_funcs.gl.p_glLightf)
        WINE_ERR("Could not load glLightf\n");

    host_funcs.gl.p_glLightfv = (void *)GetProcAddress(host, "glLightfv");
    if (!host_funcs.gl.p_glLightfv)
        WINE_ERR("Could not load glLightfv\n");

    host_funcs.gl.p_glLighti = (void *)GetProcAddress(host, "glLighti");
    if (!host_funcs.gl.p_glLighti)
        WINE_ERR("Could not load glLighti\n");

    host_funcs.gl.p_glLightiv = (void *)GetProcAddress(host, "glLightiv");
    if (!host_funcs.gl.p_glLightiv)
        WINE_ERR("Could not load glLightiv\n");

    host_funcs.gl.p_glLineStipple = (void *)GetProcAddress(host, "glLineStipple");
    if (!host_funcs.gl.p_glLineStipple)
        WINE_ERR("Could not load glLineStipple\n");

    host_funcs.gl.p_glLineWidth = (void *)GetProcAddress(host, "glLineWidth");
    if (!host_funcs.gl.p_glLineWidth)
        WINE_ERR("Could not load glLineWidth\n");

    host_funcs.gl.p_glListBase = (void *)GetProcAddress(host, "glListBase");
    if (!host_funcs.gl.p_glListBase)
        WINE_ERR("Could not load glListBase\n");

    host_funcs.gl.p_glLoadIdentity = (void *)GetProcAddress(host, "glLoadIdentity");
    if (!host_funcs.gl.p_glLoadIdentity)
        WINE_ERR("Could not load glLoadIdentity\n");

    host_funcs.gl.p_glLoadMatrixd = (void *)GetProcAddress(host, "glLoadMatrixd");
    if (!host_funcs.gl.p_glLoadMatrixd)
        WINE_ERR("Could not load glLoadMatrixd\n");

    host_funcs.gl.p_glLoadMatrixf = (void *)GetProcAddress(host, "glLoadMatrixf");
    if (!host_funcs.gl.p_glLoadMatrixf)
        WINE_ERR("Could not load glLoadMatrixf\n");

    host_funcs.gl.p_glLoadName = (void *)GetProcAddress(host, "glLoadName");
    if (!host_funcs.gl.p_glLoadName)
        WINE_ERR("Could not load glLoadName\n");

    host_funcs.gl.p_glLogicOp = (void *)GetProcAddress(host, "glLogicOp");
    if (!host_funcs.gl.p_glLogicOp)
        WINE_ERR("Could not load glLogicOp\n");

    host_funcs.gl.p_glMap1d = (void *)GetProcAddress(host, "glMap1d");
    if (!host_funcs.gl.p_glMap1d)
        WINE_ERR("Could not load glMap1d\n");

    host_funcs.gl.p_glMap1f = (void *)GetProcAddress(host, "glMap1f");
    if (!host_funcs.gl.p_glMap1f)
        WINE_ERR("Could not load glMap1f\n");

    host_funcs.gl.p_glMap2d = (void *)GetProcAddress(host, "glMap2d");
    if (!host_funcs.gl.p_glMap2d)
        WINE_ERR("Could not load glMap2d\n");

    host_funcs.gl.p_glMap2f = (void *)GetProcAddress(host, "glMap2f");
    if (!host_funcs.gl.p_glMap2f)
        WINE_ERR("Could not load glMap2f\n");

    host_funcs.gl.p_glMapGrid1d = (void *)GetProcAddress(host, "glMapGrid1d");
    if (!host_funcs.gl.p_glMapGrid1d)
        WINE_ERR("Could not load glMapGrid1d\n");

    host_funcs.gl.p_glMapGrid1f = (void *)GetProcAddress(host, "glMapGrid1f");
    if (!host_funcs.gl.p_glMapGrid1f)
        WINE_ERR("Could not load glMapGrid1f\n");

    host_funcs.gl.p_glMapGrid2d = (void *)GetProcAddress(host, "glMapGrid2d");
    if (!host_funcs.gl.p_glMapGrid2d)
        WINE_ERR("Could not load glMapGrid2d\n");

    host_funcs.gl.p_glMapGrid2f = (void *)GetProcAddress(host, "glMapGrid2f");
    if (!host_funcs.gl.p_glMapGrid2f)
        WINE_ERR("Could not load glMapGrid2f\n");

    host_funcs.gl.p_glMaterialf = (void *)GetProcAddress(host, "glMaterialf");
    if (!host_funcs.gl.p_glMaterialf)
        WINE_ERR("Could not load glMaterialf\n");

    host_funcs.gl.p_glMaterialfv = (void *)GetProcAddress(host, "glMaterialfv");
    if (!host_funcs.gl.p_glMaterialfv)
        WINE_ERR("Could not load glMaterialfv\n");

    host_funcs.gl.p_glMateriali = (void *)GetProcAddress(host, "glMateriali");
    if (!host_funcs.gl.p_glMateriali)
        WINE_ERR("Could not load glMateriali\n");

    host_funcs.gl.p_glMaterialiv = (void *)GetProcAddress(host, "glMaterialiv");
    if (!host_funcs.gl.p_glMaterialiv)
        WINE_ERR("Could not load glMaterialiv\n");

    host_funcs.gl.p_glMatrixMode = (void *)GetProcAddress(host, "glMatrixMode");
    if (!host_funcs.gl.p_glMatrixMode)
        WINE_ERR("Could not load glMatrixMode\n");

    host_funcs.gl.p_glMultMatrixd = (void *)GetProcAddress(host, "glMultMatrixd");
    if (!host_funcs.gl.p_glMultMatrixd)
        WINE_ERR("Could not load glMultMatrixd\n");

    host_funcs.gl.p_glMultMatrixf = (void *)GetProcAddress(host, "glMultMatrixf");
    if (!host_funcs.gl.p_glMultMatrixf)
        WINE_ERR("Could not load glMultMatrixf\n");

    host_funcs.gl.p_glNewList = (void *)GetProcAddress(host, "glNewList");
    if (!host_funcs.gl.p_glNewList)
        WINE_ERR("Could not load glNewList\n");

    host_funcs.gl.p_glNormal3b = (void *)GetProcAddress(host, "glNormal3b");
    if (!host_funcs.gl.p_glNormal3b)
        WINE_ERR("Could not load glNormal3b\n");

    host_funcs.gl.p_glNormal3bv = (void *)GetProcAddress(host, "glNormal3bv");
    if (!host_funcs.gl.p_glNormal3bv)
        WINE_ERR("Could not load glNormal3bv\n");

    host_funcs.gl.p_glNormal3d = (void *)GetProcAddress(host, "glNormal3d");
    if (!host_funcs.gl.p_glNormal3d)
        WINE_ERR("Could not load glNormal3d\n");

    host_funcs.gl.p_glNormal3dv = (void *)GetProcAddress(host, "glNormal3dv");
    if (!host_funcs.gl.p_glNormal3dv)
        WINE_ERR("Could not load glNormal3dv\n");

    host_funcs.gl.p_glNormal3f = (void *)GetProcAddress(host, "glNormal3f");
    if (!host_funcs.gl.p_glNormal3f)
        WINE_ERR("Could not load glNormal3f\n");

    host_funcs.gl.p_glNormal3fv = (void *)GetProcAddress(host, "glNormal3fv");
    if (!host_funcs.gl.p_glNormal3fv)
        WINE_ERR("Could not load glNormal3fv\n");

    host_funcs.gl.p_glNormal3i = (void *)GetProcAddress(host, "glNormal3i");
    if (!host_funcs.gl.p_glNormal3i)
        WINE_ERR("Could not load glNormal3i\n");

    host_funcs.gl.p_glNormal3iv = (void *)GetProcAddress(host, "glNormal3iv");
    if (!host_funcs.gl.p_glNormal3iv)
        WINE_ERR("Could not load glNormal3iv\n");

    host_funcs.gl.p_glNormal3s = (void *)GetProcAddress(host, "glNormal3s");
    if (!host_funcs.gl.p_glNormal3s)
        WINE_ERR("Could not load glNormal3s\n");

    host_funcs.gl.p_glNormal3sv = (void *)GetProcAddress(host, "glNormal3sv");
    if (!host_funcs.gl.p_glNormal3sv)
        WINE_ERR("Could not load glNormal3sv\n");

    host_funcs.gl.p_glNormalPointer = (void *)GetProcAddress(host, "glNormalPointer");
    if (!host_funcs.gl.p_glNormalPointer)
        WINE_ERR("Could not load glNormalPointer\n");

    host_funcs.gl.p_glOrtho = (void *)GetProcAddress(host, "glOrtho");
    if (!host_funcs.gl.p_glOrtho)
        WINE_ERR("Could not load glOrtho\n");

    host_funcs.gl.p_glPassThrough = (void *)GetProcAddress(host, "glPassThrough");
    if (!host_funcs.gl.p_glPassThrough)
        WINE_ERR("Could not load glPassThrough\n");

    host_funcs.gl.p_glPixelMapfv = (void *)GetProcAddress(host, "glPixelMapfv");
    if (!host_funcs.gl.p_glPixelMapfv)
        WINE_ERR("Could not load glPixelMapfv\n");

    host_funcs.gl.p_glPixelMapuiv = (void *)GetProcAddress(host, "glPixelMapuiv");
    if (!host_funcs.gl.p_glPixelMapuiv)
        WINE_ERR("Could not load glPixelMapuiv\n");

    host_funcs.gl.p_glPixelMapusv = (void *)GetProcAddress(host, "glPixelMapusv");
    if (!host_funcs.gl.p_glPixelMapusv)
        WINE_ERR("Could not load glPixelMapusv\n");

    host_funcs.gl.p_glPixelStoref = (void *)GetProcAddress(host, "glPixelStoref");
    if (!host_funcs.gl.p_glPixelStoref)
        WINE_ERR("Could not load glPixelStoref\n");

    host_funcs.gl.p_glPixelStorei = (void *)GetProcAddress(host, "glPixelStorei");
    if (!host_funcs.gl.p_glPixelStorei)
        WINE_ERR("Could not load glPixelStorei\n");

    host_funcs.gl.p_glPixelTransferf = (void *)GetProcAddress(host, "glPixelTransferf");
    if (!host_funcs.gl.p_glPixelTransferf)
        WINE_ERR("Could not load glPixelTransferf\n");

    host_funcs.gl.p_glPixelTransferi = (void *)GetProcAddress(host, "glPixelTransferi");
    if (!host_funcs.gl.p_glPixelTransferi)
        WINE_ERR("Could not load glPixelTransferi\n");

    host_funcs.gl.p_glPixelZoom = (void *)GetProcAddress(host, "glPixelZoom");
    if (!host_funcs.gl.p_glPixelZoom)
        WINE_ERR("Could not load glPixelZoom\n");

    host_funcs.gl.p_glPointSize = (void *)GetProcAddress(host, "glPointSize");
    if (!host_funcs.gl.p_glPointSize)
        WINE_ERR("Could not load glPointSize\n");

    host_funcs.gl.p_glPolygonMode = (void *)GetProcAddress(host, "glPolygonMode");
    if (!host_funcs.gl.p_glPolygonMode)
        WINE_ERR("Could not load glPolygonMode\n");

    host_funcs.gl.p_glPolygonOffset = (void *)GetProcAddress(host, "glPolygonOffset");
    if (!host_funcs.gl.p_glPolygonOffset)
        WINE_ERR("Could not load glPolygonOffset\n");

    host_funcs.gl.p_glPolygonStipple = (void *)GetProcAddress(host, "glPolygonStipple");
    if (!host_funcs.gl.p_glPolygonStipple)
        WINE_ERR("Could not load glPolygonStipple\n");

    host_funcs.gl.p_glPopAttrib = (void *)GetProcAddress(host, "glPopAttrib");
    if (!host_funcs.gl.p_glPopAttrib)
        WINE_ERR("Could not load glPopAttrib\n");

    host_funcs.gl.p_glPopClientAttrib = (void *)GetProcAddress(host, "glPopClientAttrib");
    if (!host_funcs.gl.p_glPopClientAttrib)
        WINE_ERR("Could not load glPopClientAttrib\n");

    host_funcs.gl.p_glPopMatrix = (void *)GetProcAddress(host, "glPopMatrix");
    if (!host_funcs.gl.p_glPopMatrix)
        WINE_ERR("Could not load glPopMatrix\n");

    host_funcs.gl.p_glPopName = (void *)GetProcAddress(host, "glPopName");
    if (!host_funcs.gl.p_glPopName)
        WINE_ERR("Could not load glPopName\n");

    host_funcs.gl.p_glPrioritizeTextures = (void *)GetProcAddress(host, "glPrioritizeTextures");
    if (!host_funcs.gl.p_glPrioritizeTextures)
        WINE_ERR("Could not load glPrioritizeTextures\n");

    host_funcs.gl.p_glPushAttrib = (void *)GetProcAddress(host, "glPushAttrib");
    if (!host_funcs.gl.p_glPushAttrib)
        WINE_ERR("Could not load glPushAttrib\n");

    host_funcs.gl.p_glPushClientAttrib = (void *)GetProcAddress(host, "glPushClientAttrib");
    if (!host_funcs.gl.p_glPushClientAttrib)
        WINE_ERR("Could not load glPushClientAttrib\n");

    host_funcs.gl.p_glPushMatrix = (void *)GetProcAddress(host, "glPushMatrix");
    if (!host_funcs.gl.p_glPushMatrix)
        WINE_ERR("Could not load glPushMatrix\n");

    host_funcs.gl.p_glPushName = (void *)GetProcAddress(host, "glPushName");
    if (!host_funcs.gl.p_glPushName)
        WINE_ERR("Could not load glPushName\n");

    host_funcs.gl.p_glRasterPos2d = (void *)GetProcAddress(host, "glRasterPos2d");
    if (!host_funcs.gl.p_glRasterPos2d)
        WINE_ERR("Could not load glRasterPos2d\n");

    host_funcs.gl.p_glRasterPos2dv = (void *)GetProcAddress(host, "glRasterPos2dv");
    if (!host_funcs.gl.p_glRasterPos2dv)
        WINE_ERR("Could not load glRasterPos2dv\n");

    host_funcs.gl.p_glRasterPos2f = (void *)GetProcAddress(host, "glRasterPos2f");
    if (!host_funcs.gl.p_glRasterPos2f)
        WINE_ERR("Could not load glRasterPos2f\n");

    host_funcs.gl.p_glRasterPos2fv = (void *)GetProcAddress(host, "glRasterPos2fv");
    if (!host_funcs.gl.p_glRasterPos2fv)
        WINE_ERR("Could not load glRasterPos2fv\n");

    host_funcs.gl.p_glRasterPos2i = (void *)GetProcAddress(host, "glRasterPos2i");
    if (!host_funcs.gl.p_glRasterPos2i)
        WINE_ERR("Could not load glRasterPos2i\n");

    host_funcs.gl.p_glRasterPos2iv = (void *)GetProcAddress(host, "glRasterPos2iv");
    if (!host_funcs.gl.p_glRasterPos2iv)
        WINE_ERR("Could not load glRasterPos2iv\n");

    host_funcs.gl.p_glRasterPos2s = (void *)GetProcAddress(host, "glRasterPos2s");
    if (!host_funcs.gl.p_glRasterPos2s)
        WINE_ERR("Could not load glRasterPos2s\n");

    host_funcs.gl.p_glRasterPos2sv = (void *)GetProcAddress(host, "glRasterPos2sv");
    if (!host_funcs.gl.p_glRasterPos2sv)
        WINE_ERR("Could not load glRasterPos2sv\n");

    host_funcs.gl.p_glRasterPos3d = (void *)GetProcAddress(host, "glRasterPos3d");
    if (!host_funcs.gl.p_glRasterPos3d)
        WINE_ERR("Could not load glRasterPos3d\n");

    host_funcs.gl.p_glRasterPos3dv = (void *)GetProcAddress(host, "glRasterPos3dv");
    if (!host_funcs.gl.p_glRasterPos3dv)
        WINE_ERR("Could not load glRasterPos3dv\n");

    host_funcs.gl.p_glRasterPos3f = (void *)GetProcAddress(host, "glRasterPos3f");
    if (!host_funcs.gl.p_glRasterPos3f)
        WINE_ERR("Could not load glRasterPos3f\n");

    host_funcs.gl.p_glRasterPos3fv = (void *)GetProcAddress(host, "glRasterPos3fv");
    if (!host_funcs.gl.p_glRasterPos3fv)
        WINE_ERR("Could not load glRasterPos3fv\n");

    host_funcs.gl.p_glRasterPos3i = (void *)GetProcAddress(host, "glRasterPos3i");
    if (!host_funcs.gl.p_glRasterPos3i)
        WINE_ERR("Could not load glRasterPos3i\n");

    host_funcs.gl.p_glRasterPos3iv = (void *)GetProcAddress(host, "glRasterPos3iv");
    if (!host_funcs.gl.p_glRasterPos3iv)
        WINE_ERR("Could not load glRasterPos3iv\n");

    host_funcs.gl.p_glRasterPos3s = (void *)GetProcAddress(host, "glRasterPos3s");
    if (!host_funcs.gl.p_glRasterPos3s)
        WINE_ERR("Could not load glRasterPos3s\n");

    host_funcs.gl.p_glRasterPos3sv = (void *)GetProcAddress(host, "glRasterPos3sv");
    if (!host_funcs.gl.p_glRasterPos3sv)
        WINE_ERR("Could not load glRasterPos3sv\n");

    host_funcs.gl.p_glRasterPos4d = (void *)GetProcAddress(host, "glRasterPos4d");
    if (!host_funcs.gl.p_glRasterPos4d)
        WINE_ERR("Could not load glRasterPos4d\n");

    host_funcs.gl.p_glRasterPos4dv = (void *)GetProcAddress(host, "glRasterPos4dv");
    if (!host_funcs.gl.p_glRasterPos4dv)
        WINE_ERR("Could not load glRasterPos4dv\n");

    host_funcs.gl.p_glRasterPos4f = (void *)GetProcAddress(host, "glRasterPos4f");
    if (!host_funcs.gl.p_glRasterPos4f)
        WINE_ERR("Could not load glRasterPos4f\n");

    host_funcs.gl.p_glRasterPos4fv = (void *)GetProcAddress(host, "glRasterPos4fv");
    if (!host_funcs.gl.p_glRasterPos4fv)
        WINE_ERR("Could not load glRasterPos4fv\n");

    host_funcs.gl.p_glRasterPos4i = (void *)GetProcAddress(host, "glRasterPos4i");
    if (!host_funcs.gl.p_glRasterPos4i)
        WINE_ERR("Could not load glRasterPos4i\n");

    host_funcs.gl.p_glRasterPos4iv = (void *)GetProcAddress(host, "glRasterPos4iv");
    if (!host_funcs.gl.p_glRasterPos4iv)
        WINE_ERR("Could not load glRasterPos4iv\n");

    host_funcs.gl.p_glRasterPos4s = (void *)GetProcAddress(host, "glRasterPos4s");
    if (!host_funcs.gl.p_glRasterPos4s)
        WINE_ERR("Could not load glRasterPos4s\n");

    host_funcs.gl.p_glRasterPos4sv = (void *)GetProcAddress(host, "glRasterPos4sv");
    if (!host_funcs.gl.p_glRasterPos4sv)
        WINE_ERR("Could not load glRasterPos4sv\n");

    host_funcs.gl.p_glReadBuffer = (void *)GetProcAddress(host, "glReadBuffer");
    if (!host_funcs.gl.p_glReadBuffer)
        WINE_ERR("Could not load glReadBuffer\n");

    host_funcs.gl.p_glReadPixels = (void *)GetProcAddress(host, "glReadPixels");
    if (!host_funcs.gl.p_glReadPixels)
        WINE_ERR("Could not load glReadPixels\n");

    host_funcs.gl.p_glRectd = (void *)GetProcAddress(host, "glRectd");
    if (!host_funcs.gl.p_glRectd)
        WINE_ERR("Could not load glRectd\n");

    host_funcs.gl.p_glRectdv = (void *)GetProcAddress(host, "glRectdv");
    if (!host_funcs.gl.p_glRectdv)
        WINE_ERR("Could not load glRectdv\n");

    host_funcs.gl.p_glRectf = (void *)GetProcAddress(host, "glRectf");
    if (!host_funcs.gl.p_glRectf)
        WINE_ERR("Could not load glRectf\n");

    host_funcs.gl.p_glRectfv = (void *)GetProcAddress(host, "glRectfv");
    if (!host_funcs.gl.p_glRectfv)
        WINE_ERR("Could not load glRectfv\n");

    host_funcs.gl.p_glRecti = (void *)GetProcAddress(host, "glRecti");
    if (!host_funcs.gl.p_glRecti)
        WINE_ERR("Could not load glRecti\n");

    host_funcs.gl.p_glRectiv = (void *)GetProcAddress(host, "glRectiv");
    if (!host_funcs.gl.p_glRectiv)
        WINE_ERR("Could not load glRectiv\n");

    host_funcs.gl.p_glRects = (void *)GetProcAddress(host, "glRects");
    if (!host_funcs.gl.p_glRects)
        WINE_ERR("Could not load glRects\n");

    host_funcs.gl.p_glRectsv = (void *)GetProcAddress(host, "glRectsv");
    if (!host_funcs.gl.p_glRectsv)
        WINE_ERR("Could not load glRectsv\n");

    host_funcs.gl.p_glRenderMode = (void *)GetProcAddress(host, "glRenderMode");
    if (!host_funcs.gl.p_glRenderMode)
        WINE_ERR("Could not load glRenderMode\n");

    host_funcs.gl.p_glRotated = (void *)GetProcAddress(host, "glRotated");
    if (!host_funcs.gl.p_glRotated)
        WINE_ERR("Could not load glRotated\n");

    host_funcs.gl.p_glRotatef = (void *)GetProcAddress(host, "glRotatef");
    if (!host_funcs.gl.p_glRotatef)
        WINE_ERR("Could not load glRotatef\n");

    host_funcs.gl.p_glScaled = (void *)GetProcAddress(host, "glScaled");
    if (!host_funcs.gl.p_glScaled)
        WINE_ERR("Could not load glScaled\n");

    host_funcs.gl.p_glScalef = (void *)GetProcAddress(host, "glScalef");
    if (!host_funcs.gl.p_glScalef)
        WINE_ERR("Could not load glScalef\n");

    host_funcs.gl.p_glScissor = (void *)GetProcAddress(host, "glScissor");
    if (!host_funcs.gl.p_glScissor)
        WINE_ERR("Could not load glScissor\n");

    host_funcs.gl.p_glSelectBuffer = (void *)GetProcAddress(host, "glSelectBuffer");
    if (!host_funcs.gl.p_glSelectBuffer)
        WINE_ERR("Could not load glSelectBuffer\n");

    host_funcs.gl.p_glShadeModel = (void *)GetProcAddress(host, "glShadeModel");
    if (!host_funcs.gl.p_glShadeModel)
        WINE_ERR("Could not load glShadeModel\n");

    host_funcs.gl.p_glStencilFunc = (void *)GetProcAddress(host, "glStencilFunc");
    if (!host_funcs.gl.p_glStencilFunc)
        WINE_ERR("Could not load glStencilFunc\n");

    host_funcs.gl.p_glStencilMask = (void *)GetProcAddress(host, "glStencilMask");
    if (!host_funcs.gl.p_glStencilMask)
        WINE_ERR("Could not load glStencilMask\n");

    host_funcs.gl.p_glStencilOp = (void *)GetProcAddress(host, "glStencilOp");
    if (!host_funcs.gl.p_glStencilOp)
        WINE_ERR("Could not load glStencilOp\n");

    host_funcs.gl.p_glTexCoord1d = (void *)GetProcAddress(host, "glTexCoord1d");
    if (!host_funcs.gl.p_glTexCoord1d)
        WINE_ERR("Could not load glTexCoord1d\n");

    host_funcs.gl.p_glTexCoord1dv = (void *)GetProcAddress(host, "glTexCoord1dv");
    if (!host_funcs.gl.p_glTexCoord1dv)
        WINE_ERR("Could not load glTexCoord1dv\n");

    host_funcs.gl.p_glTexCoord1f = (void *)GetProcAddress(host, "glTexCoord1f");
    if (!host_funcs.gl.p_glTexCoord1f)
        WINE_ERR("Could not load glTexCoord1f\n");

    host_funcs.gl.p_glTexCoord1fv = (void *)GetProcAddress(host, "glTexCoord1fv");
    if (!host_funcs.gl.p_glTexCoord1fv)
        WINE_ERR("Could not load glTexCoord1fv\n");

    host_funcs.gl.p_glTexCoord1i = (void *)GetProcAddress(host, "glTexCoord1i");
    if (!host_funcs.gl.p_glTexCoord1i)
        WINE_ERR("Could not load glTexCoord1i\n");

    host_funcs.gl.p_glTexCoord1iv = (void *)GetProcAddress(host, "glTexCoord1iv");
    if (!host_funcs.gl.p_glTexCoord1iv)
        WINE_ERR("Could not load glTexCoord1iv\n");

    host_funcs.gl.p_glTexCoord1s = (void *)GetProcAddress(host, "glTexCoord1s");
    if (!host_funcs.gl.p_glTexCoord1s)
        WINE_ERR("Could not load glTexCoord1s\n");

    host_funcs.gl.p_glTexCoord1sv = (void *)GetProcAddress(host, "glTexCoord1sv");
    if (!host_funcs.gl.p_glTexCoord1sv)
        WINE_ERR("Could not load glTexCoord1sv\n");

    host_funcs.gl.p_glTexCoord2d = (void *)GetProcAddress(host, "glTexCoord2d");
    if (!host_funcs.gl.p_glTexCoord2d)
        WINE_ERR("Could not load glTexCoord2d\n");

    host_funcs.gl.p_glTexCoord2dv = (void *)GetProcAddress(host, "glTexCoord2dv");
    if (!host_funcs.gl.p_glTexCoord2dv)
        WINE_ERR("Could not load glTexCoord2dv\n");

    host_funcs.gl.p_glTexCoord2f = (void *)GetProcAddress(host, "glTexCoord2f");
    if (!host_funcs.gl.p_glTexCoord2f)
        WINE_ERR("Could not load glTexCoord2f\n");

    host_funcs.gl.p_glTexCoord2fv = (void *)GetProcAddress(host, "glTexCoord2fv");
    if (!host_funcs.gl.p_glTexCoord2fv)
        WINE_ERR("Could not load glTexCoord2fv\n");

    host_funcs.gl.p_glTexCoord2i = (void *)GetProcAddress(host, "glTexCoord2i");
    if (!host_funcs.gl.p_glTexCoord2i)
        WINE_ERR("Could not load glTexCoord2i\n");

    host_funcs.gl.p_glTexCoord2iv = (void *)GetProcAddress(host, "glTexCoord2iv");
    if (!host_funcs.gl.p_glTexCoord2iv)
        WINE_ERR("Could not load glTexCoord2iv\n");

    host_funcs.gl.p_glTexCoord2s = (void *)GetProcAddress(host, "glTexCoord2s");
    if (!host_funcs.gl.p_glTexCoord2s)
        WINE_ERR("Could not load glTexCoord2s\n");

    host_funcs.gl.p_glTexCoord2sv = (void *)GetProcAddress(host, "glTexCoord2sv");
    if (!host_funcs.gl.p_glTexCoord2sv)
        WINE_ERR("Could not load glTexCoord2sv\n");

    host_funcs.gl.p_glTexCoord3d = (void *)GetProcAddress(host, "glTexCoord3d");
    if (!host_funcs.gl.p_glTexCoord3d)
        WINE_ERR("Could not load glTexCoord3d\n");

    host_funcs.gl.p_glTexCoord3dv = (void *)GetProcAddress(host, "glTexCoord3dv");
    if (!host_funcs.gl.p_glTexCoord3dv)
        WINE_ERR("Could not load glTexCoord3dv\n");

    host_funcs.gl.p_glTexCoord3f = (void *)GetProcAddress(host, "glTexCoord3f");
    if (!host_funcs.gl.p_glTexCoord3f)
        WINE_ERR("Could not load glTexCoord3f\n");

    host_funcs.gl.p_glTexCoord3fv = (void *)GetProcAddress(host, "glTexCoord3fv");
    if (!host_funcs.gl.p_glTexCoord3fv)
        WINE_ERR("Could not load glTexCoord3fv\n");

    host_funcs.gl.p_glTexCoord3i = (void *)GetProcAddress(host, "glTexCoord3i");
    if (!host_funcs.gl.p_glTexCoord3i)
        WINE_ERR("Could not load glTexCoord3i\n");

    host_funcs.gl.p_glTexCoord3iv = (void *)GetProcAddress(host, "glTexCoord3iv");
    if (!host_funcs.gl.p_glTexCoord3iv)
        WINE_ERR("Could not load glTexCoord3iv\n");

    host_funcs.gl.p_glTexCoord3s = (void *)GetProcAddress(host, "glTexCoord3s");
    if (!host_funcs.gl.p_glTexCoord3s)
        WINE_ERR("Could not load glTexCoord3s\n");

    host_funcs.gl.p_glTexCoord3sv = (void *)GetProcAddress(host, "glTexCoord3sv");
    if (!host_funcs.gl.p_glTexCoord3sv)
        WINE_ERR("Could not load glTexCoord3sv\n");

    host_funcs.gl.p_glTexCoord4d = (void *)GetProcAddress(host, "glTexCoord4d");
    if (!host_funcs.gl.p_glTexCoord4d)
        WINE_ERR("Could not load glTexCoord4d\n");

    host_funcs.gl.p_glTexCoord4dv = (void *)GetProcAddress(host, "glTexCoord4dv");
    if (!host_funcs.gl.p_glTexCoord4dv)
        WINE_ERR("Could not load glTexCoord4dv\n");

    host_funcs.gl.p_glTexCoord4f = (void *)GetProcAddress(host, "glTexCoord4f");
    if (!host_funcs.gl.p_glTexCoord4f)
        WINE_ERR("Could not load glTexCoord4f\n");

    host_funcs.gl.p_glTexCoord4fv = (void *)GetProcAddress(host, "glTexCoord4fv");
    if (!host_funcs.gl.p_glTexCoord4fv)
        WINE_ERR("Could not load glTexCoord4fv\n");

    host_funcs.gl.p_glTexCoord4i = (void *)GetProcAddress(host, "glTexCoord4i");
    if (!host_funcs.gl.p_glTexCoord4i)
        WINE_ERR("Could not load glTexCoord4i\n");

    host_funcs.gl.p_glTexCoord4iv = (void *)GetProcAddress(host, "glTexCoord4iv");
    if (!host_funcs.gl.p_glTexCoord4iv)
        WINE_ERR("Could not load glTexCoord4iv\n");

    host_funcs.gl.p_glTexCoord4s = (void *)GetProcAddress(host, "glTexCoord4s");
    if (!host_funcs.gl.p_glTexCoord4s)
        WINE_ERR("Could not load glTexCoord4s\n");

    host_funcs.gl.p_glTexCoord4sv = (void *)GetProcAddress(host, "glTexCoord4sv");
    if (!host_funcs.gl.p_glTexCoord4sv)
        WINE_ERR("Could not load glTexCoord4sv\n");

    host_funcs.gl.p_glTexCoordPointer = (void *)GetProcAddress(host, "glTexCoordPointer");
    if (!host_funcs.gl.p_glTexCoordPointer)
        WINE_ERR("Could not load glTexCoordPointer\n");

    host_funcs.gl.p_glTexEnvf = (void *)GetProcAddress(host, "glTexEnvf");
    if (!host_funcs.gl.p_glTexEnvf)
        WINE_ERR("Could not load glTexEnvf\n");

    host_funcs.gl.p_glTexEnvfv = (void *)GetProcAddress(host, "glTexEnvfv");
    if (!host_funcs.gl.p_glTexEnvfv)
        WINE_ERR("Could not load glTexEnvfv\n");

    host_funcs.gl.p_glTexEnvi = (void *)GetProcAddress(host, "glTexEnvi");
    if (!host_funcs.gl.p_glTexEnvi)
        WINE_ERR("Could not load glTexEnvi\n");

    host_funcs.gl.p_glTexEnviv = (void *)GetProcAddress(host, "glTexEnviv");
    if (!host_funcs.gl.p_glTexEnviv)
        WINE_ERR("Could not load glTexEnviv\n");

    host_funcs.gl.p_glTexGend = (void *)GetProcAddress(host, "glTexGend");
    if (!host_funcs.gl.p_glTexGend)
        WINE_ERR("Could not load glTexGend\n");

    host_funcs.gl.p_glTexGendv = (void *)GetProcAddress(host, "glTexGendv");
    if (!host_funcs.gl.p_glTexGendv)
        WINE_ERR("Could not load glTexGendv\n");

    host_funcs.gl.p_glTexGenf = (void *)GetProcAddress(host, "glTexGenf");
    if (!host_funcs.gl.p_glTexGenf)
        WINE_ERR("Could not load glTexGenf\n");

    host_funcs.gl.p_glTexGenfv = (void *)GetProcAddress(host, "glTexGenfv");
    if (!host_funcs.gl.p_glTexGenfv)
        WINE_ERR("Could not load glTexGenfv\n");

    host_funcs.gl.p_glTexGeni = (void *)GetProcAddress(host, "glTexGeni");
    if (!host_funcs.gl.p_glTexGeni)
        WINE_ERR("Could not load glTexGeni\n");

    host_funcs.gl.p_glTexGeniv = (void *)GetProcAddress(host, "glTexGeniv");
    if (!host_funcs.gl.p_glTexGeniv)
        WINE_ERR("Could not load glTexGeniv\n");

    host_funcs.gl.p_glTexImage1D = (void *)GetProcAddress(host, "glTexImage1D");
    if (!host_funcs.gl.p_glTexImage1D)
        WINE_ERR("Could not load glTexImage1D\n");

    host_funcs.gl.p_glTexImage2D = (void *)GetProcAddress(host, "glTexImage2D");
    if (!host_funcs.gl.p_glTexImage2D)
        WINE_ERR("Could not load glTexImage2D\n");

    host_funcs.gl.p_glTexParameterf = (void *)GetProcAddress(host, "glTexParameterf");
    if (!host_funcs.gl.p_glTexParameterf)
        WINE_ERR("Could not load glTexParameterf\n");

    host_funcs.gl.p_glTexParameterfv = (void *)GetProcAddress(host, "glTexParameterfv");
    if (!host_funcs.gl.p_glTexParameterfv)
        WINE_ERR("Could not load glTexParameterfv\n");

    host_funcs.gl.p_glTexParameteri = (void *)GetProcAddress(host, "glTexParameteri");
    if (!host_funcs.gl.p_glTexParameteri)
        WINE_ERR("Could not load glTexParameteri\n");

    host_funcs.gl.p_glTexParameteriv = (void *)GetProcAddress(host, "glTexParameteriv");
    if (!host_funcs.gl.p_glTexParameteriv)
        WINE_ERR("Could not load glTexParameteriv\n");

    host_funcs.gl.p_glTexSubImage1D = (void *)GetProcAddress(host, "glTexSubImage1D");
    if (!host_funcs.gl.p_glTexSubImage1D)
        WINE_ERR("Could not load glTexSubImage1D\n");

    host_funcs.gl.p_glTexSubImage2D = (void *)GetProcAddress(host, "glTexSubImage2D");
    if (!host_funcs.gl.p_glTexSubImage2D)
        WINE_ERR("Could not load glTexSubImage2D\n");

    host_funcs.gl.p_glTranslated = (void *)GetProcAddress(host, "glTranslated");
    if (!host_funcs.gl.p_glTranslated)
        WINE_ERR("Could not load glTranslated\n");

    host_funcs.gl.p_glTranslatef = (void *)GetProcAddress(host, "glTranslatef");
    if (!host_funcs.gl.p_glTranslatef)
        WINE_ERR("Could not load glTranslatef\n");

    host_funcs.gl.p_glVertex2d = (void *)GetProcAddress(host, "glVertex2d");
    if (!host_funcs.gl.p_glVertex2d)
        WINE_ERR("Could not load glVertex2d\n");

    host_funcs.gl.p_glVertex2dv = (void *)GetProcAddress(host, "glVertex2dv");
    if (!host_funcs.gl.p_glVertex2dv)
        WINE_ERR("Could not load glVertex2dv\n");

    host_funcs.gl.p_glVertex2f = (void *)GetProcAddress(host, "glVertex2f");
    if (!host_funcs.gl.p_glVertex2f)
        WINE_ERR("Could not load glVertex2f\n");

    host_funcs.gl.p_glVertex2fv = (void *)GetProcAddress(host, "glVertex2fv");
    if (!host_funcs.gl.p_glVertex2fv)
        WINE_ERR("Could not load glVertex2fv\n");

    host_funcs.gl.p_glVertex2i = (void *)GetProcAddress(host, "glVertex2i");
    if (!host_funcs.gl.p_glVertex2i)
        WINE_ERR("Could not load glVertex2i\n");

    host_funcs.gl.p_glVertex2iv = (void *)GetProcAddress(host, "glVertex2iv");
    if (!host_funcs.gl.p_glVertex2iv)
        WINE_ERR("Could not load glVertex2iv\n");

    host_funcs.gl.p_glVertex2s = (void *)GetProcAddress(host, "glVertex2s");
    if (!host_funcs.gl.p_glVertex2s)
        WINE_ERR("Could not load glVertex2s\n");

    host_funcs.gl.p_glVertex2sv = (void *)GetProcAddress(host, "glVertex2sv");
    if (!host_funcs.gl.p_glVertex2sv)
        WINE_ERR("Could not load glVertex2sv\n");

    host_funcs.gl.p_glVertex3d = (void *)GetProcAddress(host, "glVertex3d");
    if (!host_funcs.gl.p_glVertex3d)
        WINE_ERR("Could not load glVertex3d\n");

    host_funcs.gl.p_glVertex3dv = (void *)GetProcAddress(host, "glVertex3dv");
    if (!host_funcs.gl.p_glVertex3dv)
        WINE_ERR("Could not load glVertex3dv\n");

    host_funcs.gl.p_glVertex3f = (void *)GetProcAddress(host, "glVertex3f");
    if (!host_funcs.gl.p_glVertex3f)
        WINE_ERR("Could not load glVertex3f\n");

    host_funcs.gl.p_glVertex3fv = (void *)GetProcAddress(host, "glVertex3fv");
    if (!host_funcs.gl.p_glVertex3fv)
        WINE_ERR("Could not load glVertex3fv\n");

    host_funcs.gl.p_glVertex3i = (void *)GetProcAddress(host, "glVertex3i");
    if (!host_funcs.gl.p_glVertex3i)
        WINE_ERR("Could not load glVertex3i\n");

    host_funcs.gl.p_glVertex3iv = (void *)GetProcAddress(host, "glVertex3iv");
    if (!host_funcs.gl.p_glVertex3iv)
        WINE_ERR("Could not load glVertex3iv\n");

    host_funcs.gl.p_glVertex3s = (void *)GetProcAddress(host, "glVertex3s");
    if (!host_funcs.gl.p_glVertex3s)
        WINE_ERR("Could not load glVertex3s\n");

    host_funcs.gl.p_glVertex3sv = (void *)GetProcAddress(host, "glVertex3sv");
    if (!host_funcs.gl.p_glVertex3sv)
        WINE_ERR("Could not load glVertex3sv\n");

    host_funcs.gl.p_glVertex4d = (void *)GetProcAddress(host, "glVertex4d");
    if (!host_funcs.gl.p_glVertex4d)
        WINE_ERR("Could not load glVertex4d\n");

    host_funcs.gl.p_glVertex4dv = (void *)GetProcAddress(host, "glVertex4dv");
    if (!host_funcs.gl.p_glVertex4dv)
        WINE_ERR("Could not load glVertex4dv\n");

    host_funcs.gl.p_glVertex4f = (void *)GetProcAddress(host, "glVertex4f");
    if (!host_funcs.gl.p_glVertex4f)
        WINE_ERR("Could not load glVertex4f\n");

    host_funcs.gl.p_glVertex4fv = (void *)GetProcAddress(host, "glVertex4fv");
    if (!host_funcs.gl.p_glVertex4fv)
        WINE_ERR("Could not load glVertex4fv\n");

    host_funcs.gl.p_glVertex4i = (void *)GetProcAddress(host, "glVertex4i");
    if (!host_funcs.gl.p_glVertex4i)
        WINE_ERR("Could not load glVertex4i\n");

    host_funcs.gl.p_glVertex4iv = (void *)GetProcAddress(host, "glVertex4iv");
    if (!host_funcs.gl.p_glVertex4iv)
        WINE_ERR("Could not load glVertex4iv\n");

    host_funcs.gl.p_glVertex4s = (void *)GetProcAddress(host, "glVertex4s");
    if (!host_funcs.gl.p_glVertex4s)
        WINE_ERR("Could not load glVertex4s\n");

    host_funcs.gl.p_glVertex4sv = (void *)GetProcAddress(host, "glVertex4sv");
    if (!host_funcs.gl.p_glVertex4sv)
        WINE_ERR("Could not load glVertex4sv\n");

    host_funcs.gl.p_glVertexPointer = (void *)GetProcAddress(host, "glVertexPointer");
    if (!host_funcs.gl.p_glVertexPointer)
        WINE_ERR("Could not load glVertexPointer\n");

    host_funcs.gl.p_glViewport = (void *)GetProcAddress(host, "glViewport");
    if (!host_funcs.gl.p_glViewport)
        WINE_ERR("Could not load glViewport\n");

    host_funcs.wgl.p_wglCopyContext = (void *)GetProcAddress(host, "wglCopyContext");
    if (!host_funcs.wgl.p_wglCopyContext)
        WINE_ERR("Could not load wglCopyContext\n");

    host_funcs.wgl.p_wglCreateContext = (void *)GetProcAddress(host, "wglCreateContext");
    if (!host_funcs.wgl.p_wglCreateContext)
        WINE_ERR("Could not load wglCreateContext\n");

    host_funcs.wgl.p_wglDeleteContext = (void *)GetProcAddress(host, "wglDeleteContext");
    if (!host_funcs.wgl.p_wglDeleteContext)
        WINE_ERR("Could not load wglDeleteContext\n");

    host_funcs.wgl.p_wglDescribePixelFormat = (void *)GetProcAddress(host, "wglDescribePixelFormat");
    if (!host_funcs.wgl.p_wglDescribePixelFormat)
        WINE_ERR("Could not load wglDescribePixelFormat\n");

    host_funcs.wgl.p_wglGetPixelFormat = (void *)GetProcAddress(host, "wglGetPixelFormat");
    if (!host_funcs.wgl.p_wglGetPixelFormat)
        WINE_ERR("Could not load wglGetPixelFormat\n");

    host_funcs.wgl.p_wglGetProcAddress = (void *)GetProcAddress(host, "wglGetProcAddress");
    if (!host_funcs.wgl.p_wglGetProcAddress)
        WINE_ERR("Could not load wglGetProcAddress\n");

    host_funcs.wgl.p_wglMakeCurrent = (void *)GetProcAddress(host, "wglMakeCurrent");
    if (!host_funcs.wgl.p_wglMakeCurrent)
        WINE_ERR("Could not load wglMakeCurrent\n");

    host_funcs.wgl.p_wglSetPixelFormat = (void *)GetProcAddress(host, "wglSetPixelFormat");
    if (!host_funcs.wgl.p_wglSetPixelFormat)
        WINE_ERR("Could not load wglSetPixelFormat\n");

    host_funcs.wgl.p_wglShareLists = (void *)GetProcAddress(host, "wglShareLists");
    if (!host_funcs.wgl.p_wglShareLists)
        WINE_ERR("Could not load wglShareLists\n");

    host_funcs.wgl.p_wglSwapBuffers = (void *)GetProcAddress(host, "wglSwapBuffers");
    if (!host_funcs.wgl.p_wglSwapBuffers)
        WINE_ERR("Could not load wglSwapBuffers\n");

}

#endif
