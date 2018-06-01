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

#ifndef QEMU_D3D11_H
#define QEMU_D3D11_H

enum d3d11_calls
{
    CALL_D3D10_DEVICE_CHECKCOUNTER = 0,
    CALL_D3D10_DEVICE_CHECKCOUNTERINFO,
    CALL_D3D10_DEVICE_CHECKFORMATSUPPORT,
    CALL_D3D10_DEVICE_CHECKMULTISAMPLEQUALITYLEVELS,
    CALL_D3D10_DEVICE_CLEARDEPTHSTENCILVIEW,
    CALL_D3D10_DEVICE_CLEARRENDERTARGETVIEW,
    CALL_D3D10_DEVICE_CLEARSTATE,
    CALL_D3D10_DEVICE_COPYRESOURCE,
    CALL_D3D10_DEVICE_COPYSUBRESOURCEREGION,
    CALL_D3D10_DEVICE_CREATEBLENDSTATE,
    CALL_D3D10_DEVICE_CREATEBLENDSTATE1,
    CALL_D3D10_DEVICE_CREATEBUFFER,
    CALL_D3D10_DEVICE_CREATECOUNTER,
    CALL_D3D10_DEVICE_CREATEDEPTHSTENCILSTATE,
    CALL_D3D10_DEVICE_CREATEDEPTHSTENCILVIEW,
    CALL_D3D10_DEVICE_CREATEGEOMETRYSHADER,
    CALL_D3D10_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT,
    CALL_D3D10_DEVICE_CREATEINPUTLAYOUT,
    CALL_D3D10_DEVICE_CREATEPIXELSHADER,
    CALL_D3D10_DEVICE_CREATEPREDICATE,
    CALL_D3D10_DEVICE_CREATEQUERY,
    CALL_D3D10_DEVICE_CREATERASTERIZERSTATE,
    CALL_D3D10_DEVICE_CREATERENDERTARGETVIEW,
    CALL_D3D10_DEVICE_CREATESAMPLERSTATE,
    CALL_D3D10_DEVICE_CREATESHADERRESOURCEVIEW,
    CALL_D3D10_DEVICE_CREATESHADERRESOURCEVIEW1,
    CALL_D3D10_DEVICE_CREATETEXTURE3D,
    CALL_D3D10_DEVICE_CREATEVERTEXSHADER,
    CALL_D3D10_DEVICE_DRAW,
    CALL_D3D10_DEVICE_DRAWAUTO,
    CALL_D3D10_DEVICE_DRAWINDEXED,
    CALL_D3D10_DEVICE_DRAWINDEXEDINSTANCED,
    CALL_D3D10_DEVICE_DRAWINSTANCED,
    CALL_D3D10_DEVICE_FLUSH,
    CALL_D3D10_DEVICE_GENERATEMIPS,
    CALL_D3D10_DEVICE_GETCREATIONFLAGS,
    CALL_D3D10_DEVICE_GETDEVICEREMOVEDREASON,
    CALL_D3D10_DEVICE_GETEXCEPTIONMODE,
    CALL_D3D10_DEVICE_GETFEATURELEVEL,
    CALL_D3D10_DEVICE_GETPREDICATION,
    CALL_D3D10_DEVICE_GETPRIVATEDATA,
    CALL_D3D10_DEVICE_GETTEXTFILTERSIZE,
    CALL_D3D10_DEVICE_GSGETCONSTANTBUFFERS,
    CALL_D3D10_DEVICE_GSGETSAMPLERS,
    CALL_D3D10_DEVICE_GSGETSHADER,
    CALL_D3D10_DEVICE_GSGETSHADERRESOURCES,
    CALL_D3D10_DEVICE_GSSETCONSTANTBUFFERS,
    CALL_D3D10_DEVICE_GSSETSAMPLERS,
    CALL_D3D10_DEVICE_GSSETSHADER,
    CALL_D3D10_DEVICE_GSSETSHADERRESOURCES,
    CALL_D3D10_DEVICE_IAGETINDEXBUFFER,
    CALL_D3D10_DEVICE_IAGETINPUTLAYOUT,
    CALL_D3D10_DEVICE_IAGETPRIMITIVETOPOLOGY,
    CALL_D3D10_DEVICE_IAGETVERTEXBUFFERS,
    CALL_D3D10_DEVICE_IASETINDEXBUFFER,
    CALL_D3D10_DEVICE_IASETINPUTLAYOUT,
    CALL_D3D10_DEVICE_IASETPRIMITIVETOPOLOGY,
    CALL_D3D10_DEVICE_IASETVERTEXBUFFERS,
    CALL_D3D10_DEVICE_OMGETBLENDSTATE,
    CALL_D3D10_DEVICE_OMGETDEPTHSTENCILSTATE,
    CALL_D3D10_DEVICE_OMGETRENDERTARGETS,
    CALL_D3D10_DEVICE_OMSETBLENDSTATE,
    CALL_D3D10_DEVICE_OMSETDEPTHSTENCILSTATE,
    CALL_D3D10_DEVICE_OMSETRENDERTARGETS,
    CALL_D3D10_DEVICE_OPENSHAREDRESOURCE,
    CALL_D3D10_DEVICE_PSGETCONSTANTBUFFERS,
    CALL_D3D10_DEVICE_PSGETSAMPLERS,
    CALL_D3D10_DEVICE_PSGETSHADER,
    CALL_D3D10_DEVICE_PSGETSHADERRESOURCES,
    CALL_D3D10_DEVICE_PSSETCONSTANTBUFFERS,
    CALL_D3D10_DEVICE_PSSETSAMPLERS,
    CALL_D3D10_DEVICE_PSSETSHADER,
    CALL_D3D10_DEVICE_PSSETSHADERRESOURCES,
    CALL_D3D10_DEVICE_RESOLVESUBRESOURCE,
    CALL_D3D10_DEVICE_RSGETSCISSORRECTS,
    CALL_D3D10_DEVICE_RSGETSTATE,
    CALL_D3D10_DEVICE_RSGETVIEWPORTS,
    CALL_D3D10_DEVICE_RSSETSCISSORRECTS,
    CALL_D3D10_DEVICE_RSSETSTATE,
    CALL_D3D10_DEVICE_RSSETVIEWPORTS,
    CALL_D3D10_DEVICE_SETEXCEPTIONMODE,
    CALL_D3D10_DEVICE_SETPREDICATION,
    CALL_D3D10_DEVICE_SETPRIVATEDATA,
    CALL_D3D10_DEVICE_SETPRIVATEDATAINTERFACE,
    CALL_D3D10_DEVICE_SETTEXTFILTERSIZE,
    CALL_D3D10_DEVICE_SOGETTARGETS,
    CALL_D3D10_DEVICE_SOSETTARGETS,
    CALL_D3D10_DEVICE_UPDATESUBRESOURCE,
    CALL_D3D10_DEVICE_VSGETCONSTANTBUFFERS,
    CALL_D3D10_DEVICE_VSGETSAMPLERS,
    CALL_D3D10_DEVICE_VSGETSHADER,
    CALL_D3D10_DEVICE_VSGETSHADERRESOURCES,
    CALL_D3D10_DEVICE_VSSETCONSTANTBUFFERS,
    CALL_D3D10_DEVICE_VSSETSAMPLERS,
    CALL_D3D10_DEVICE_VSSETSHADER,
    CALL_D3D10_DEVICE_VSSETSHADERRESOURCES,
    CALL_D3D10_MULTITHREAD_ENTER,
    CALL_D3D10_MULTITHREAD_GETMULTITHREADPROTECTED,
    CALL_D3D10_MULTITHREAD_LEAVE,
    CALL_D3D10_MULTITHREAD_SETMULTITHREADPROTECTED,
    CALL_D3D10_TEXTURE1D_ADDREF,
    CALL_D3D10_TEXTURE1D_GETDESC,
    CALL_D3D10_TEXTURE1D_GETDEVICE,
    CALL_D3D10_TEXTURE1D_GETEVICTIONPRIORITY,
    CALL_D3D10_TEXTURE1D_GETPRIVATEDATA,
    CALL_D3D10_TEXTURE1D_GETTYPE,
    CALL_D3D10_TEXTURE1D_MAP,
    CALL_D3D10_TEXTURE1D_QUERYINTERFACE,
    CALL_D3D10_TEXTURE1D_RELEASE,
    CALL_D3D10_TEXTURE1D_SETEVICTIONPRIORITY,
    CALL_D3D10_TEXTURE1D_SETPRIVATEDATA,
    CALL_D3D10_TEXTURE1D_SETPRIVATEDATAINTERFACE,
    CALL_D3D10_TEXTURE1D_UNMAP,
    CALL_D3D10_TEXTURE2D_ADDREF,
    CALL_D3D10_TEXTURE2D_GETDESC,
    CALL_D3D10_TEXTURE2D_GETDEVICE,
    CALL_D3D10_TEXTURE2D_GETEVICTIONPRIORITY,
    CALL_D3D10_TEXTURE2D_GETPRIVATEDATA,
    CALL_D3D10_TEXTURE2D_GETTYPE,
    CALL_D3D10_TEXTURE2D_MAP,
    CALL_D3D10_TEXTURE2D_QUERYINTERFACE,
    CALL_D3D10_TEXTURE2D_RELEASE,
    CALL_D3D10_TEXTURE2D_SETEVICTIONPRIORITY,
    CALL_D3D10_TEXTURE2D_SETPRIVATEDATA,
    CALL_D3D10_TEXTURE2D_SETPRIVATEDATAINTERFACE,
    CALL_D3D10_TEXTURE2D_UNMAP,
    CALL_D3D10_TEXTURE3D_ADDREF,
    CALL_D3D10_TEXTURE3D_GETDESC,
    CALL_D3D10_TEXTURE3D_GETDEVICE,
    CALL_D3D10_TEXTURE3D_GETEVICTIONPRIORITY,
    CALL_D3D10_TEXTURE3D_GETPRIVATEDATA,
    CALL_D3D10_TEXTURE3D_GETTYPE,
    CALL_D3D10_TEXTURE3D_MAP,
    CALL_D3D10_TEXTURE3D_QUERYINTERFACE,
    CALL_D3D10_TEXTURE3D_RELEASE,
    CALL_D3D10_TEXTURE3D_SETEVICTIONPRIORITY,
    CALL_D3D10_TEXTURE3D_SETPRIVATEDATA,
    CALL_D3D10_TEXTURE3D_SETPRIVATEDATAINTERFACE,
    CALL_D3D10_TEXTURE3D_UNMAP,
    CALL_D3D11_DEVICE_CHECKCOUNTER,
    CALL_D3D11_DEVICE_CHECKCOUNTERINFO,
    CALL_D3D11_DEVICE_CHECKFEATURESUPPORT,
    CALL_D3D11_DEVICE_CHECKFORMATSUPPORT,
    CALL_D3D11_DEVICE_CHECKMULTISAMPLEQUALITYLEVELS,
    CALL_D3D11_DEVICE_CHECKMULTISAMPLEQUALITYLEVELS1,
    CALL_D3D11_DEVICE_CREATEBLENDSTATE,
    CALL_D3D11_DEVICE_CREATEBLENDSTATE1,
    CALL_D3D11_DEVICE_CREATEBUFFER,
    CALL_D3D11_DEVICE_CREATECLASSLINKAGE,
    CALL_D3D11_DEVICE_CREATECOMPUTESHADER,
    CALL_D3D11_DEVICE_CREATECOUNTER,
    CALL_D3D11_DEVICE_CREATEDEFERREDCONTEXT,
    CALL_D3D11_DEVICE_CREATEDEFERREDCONTEXT1,
    CALL_D3D11_DEVICE_CREATEDEFERREDCONTEXT2,
    CALL_D3D11_DEVICE_CREATEDEPTHSTENCILSTATE,
    CALL_D3D11_DEVICE_CREATEDEPTHSTENCILVIEW,
    CALL_D3D11_DEVICE_CREATEDEVICECONTEXTSTATE,
    CALL_D3D11_DEVICE_CREATEDOMAINSHADER,
    CALL_D3D11_DEVICE_CREATEGEOMETRYSHADER,
    CALL_D3D11_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT,
    CALL_D3D11_DEVICE_CREATEHULLSHADER,
    CALL_D3D11_DEVICE_CREATEINPUTLAYOUT,
    CALL_D3D11_DEVICE_CREATEPIXELSHADER,
    CALL_D3D11_DEVICE_CREATEPREDICATE,
    CALL_D3D11_DEVICE_CREATEQUERY,
    CALL_D3D11_DEVICE_CREATERASTERIZERSTATE,
    CALL_D3D11_DEVICE_CREATERASTERIZERSTATE1,
    CALL_D3D11_DEVICE_CREATERENDERTARGETVIEW,
    CALL_D3D11_DEVICE_CREATESAMPLERSTATE,
    CALL_D3D11_DEVICE_CREATESHADERRESOURCEVIEW,
    CALL_D3D11_DEVICE_CREATETEXTURE1D,
    CALL_D3D11_DEVICE_CREATETEXTURE2D,
    CALL_D3D11_DEVICE_CREATETEXTURE3D,
    CALL_D3D11_DEVICE_CREATEUNORDEREDACCESSVIEW,
    CALL_D3D11_DEVICE_CREATEVERTEXSHADER,
    CALL_D3D11_DEVICE_GETCREATIONFLAGS,
    CALL_D3D11_DEVICE_GETDEVICEREMOVEDREASON,
    CALL_D3D11_DEVICE_GETEXCEPTIONMODE,
    CALL_D3D11_DEVICE_GETFEATURELEVEL,
    CALL_D3D11_DEVICE_GETIMMEDIATECONTEXT,
    CALL_D3D11_DEVICE_GETIMMEDIATECONTEXT1,
    CALL_D3D11_DEVICE_GETIMMEDIATECONTEXT2,
    CALL_D3D11_DEVICE_GETPRIVATEDATA,
    CALL_D3D11_DEVICE_GETRESOURCETILING,
    CALL_D3D11_DEVICE_OPENSHAREDRESOURCE,
    CALL_D3D11_DEVICE_OPENSHAREDRESOURCE1,
    CALL_D3D11_DEVICE_OPENSHAREDRESOURCEBYNAME,
    CALL_D3D11_DEVICE_SETEXCEPTIONMODE,
    CALL_D3D11_DEVICE_SETPRIVATEDATA,
    CALL_D3D11_DEVICE_SETPRIVATEDATAINTERFACE,
    CALL_D3D11_IMMEDIATE_CONTEXT_ADDREF,
    CALL_D3D11_IMMEDIATE_CONTEXT_BEGIN,
    CALL_D3D11_IMMEDIATE_CONTEXT_CLEARDEPTHSTENCILVIEW,
    CALL_D3D11_IMMEDIATE_CONTEXT_CLEARRENDERTARGETVIEW,
    CALL_D3D11_IMMEDIATE_CONTEXT_CLEARSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_CLEARUNORDEREDACCESSVIEWFLOAT,
    CALL_D3D11_IMMEDIATE_CONTEXT_CLEARUNORDEREDACCESSVIEWUINT,
    CALL_D3D11_IMMEDIATE_CONTEXT_CLEARVIEW,
    CALL_D3D11_IMMEDIATE_CONTEXT_COPYRESOURCE,
    CALL_D3D11_IMMEDIATE_CONTEXT_COPYSTRUCTURECOUNT,
    CALL_D3D11_IMMEDIATE_CONTEXT_COPYSUBRESOURCEREGION,
    CALL_D3D11_IMMEDIATE_CONTEXT_COPYSUBRESOURCEREGION1,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSGETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSGETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSGETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSGETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSGETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSGETUNORDEREDACCESSVIEWS,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSSETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSSETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSSETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSSETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSSETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_CSSETUNORDEREDACCESSVIEWS,
    CALL_D3D11_IMMEDIATE_CONTEXT_DISCARDRESOURCE,
    CALL_D3D11_IMMEDIATE_CONTEXT_DISCARDVIEW,
    CALL_D3D11_IMMEDIATE_CONTEXT_DISCARDVIEW1,
    CALL_D3D11_IMMEDIATE_CONTEXT_DISPATCH,
    CALL_D3D11_IMMEDIATE_CONTEXT_DISPATCHINDIRECT,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAW,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAWAUTO,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINDEXED,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINDEXEDINSTANCED,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINDEXEDINSTANCEDINDIRECT,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINSTANCED,
    CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINSTANCEDINDIRECT,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSGETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSGETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSGETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSGETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSGETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSSETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSSETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSSETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSSETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_DSSETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_END,
    CALL_D3D11_IMMEDIATE_CONTEXT_EXECUTECOMMANDLIST,
    CALL_D3D11_IMMEDIATE_CONTEXT_FINISHCOMMANDLIST,
    CALL_D3D11_IMMEDIATE_CONTEXT_FLUSH,
    CALL_D3D11_IMMEDIATE_CONTEXT_GENERATEMIPS,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETCONTEXTFLAGS,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETDATA,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETDEVICE,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETPREDICATION,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETPRIVATEDATA,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETRESOURCEMINLOD,
    CALL_D3D11_IMMEDIATE_CONTEXT_GETTYPE,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSGETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSGETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSGETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSGETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSGETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSSETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSSETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSSETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSSETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_GSSETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSGETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSGETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSGETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSGETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSGETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSSETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSSETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSSETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSSETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_HSSETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_IAGETINDEXBUFFER,
    CALL_D3D11_IMMEDIATE_CONTEXT_IAGETINPUTLAYOUT,
    CALL_D3D11_IMMEDIATE_CONTEXT_IAGETPRIMITIVETOPOLOGY,
    CALL_D3D11_IMMEDIATE_CONTEXT_IAGETVERTEXBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_IASETINDEXBUFFER,
    CALL_D3D11_IMMEDIATE_CONTEXT_IASETINPUTLAYOUT,
    CALL_D3D11_IMMEDIATE_CONTEXT_IASETPRIMITIVETOPOLOGY,
    CALL_D3D11_IMMEDIATE_CONTEXT_IASETVERTEXBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_MAP,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMGETBLENDSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMGETDEPTHSTENCILSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMGETRENDERTARGETS,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMGETRENDERTARGETSANDUNORDEREDACCESSVIEWS,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMSETBLENDSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMSETDEPTHSTENCILSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMSETRENDERTARGETS,
    CALL_D3D11_IMMEDIATE_CONTEXT_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSGETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSGETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSGETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSGETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSGETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSSETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSSETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSSETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSSETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_PSSETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_QUERYINTERFACE,
    CALL_D3D11_IMMEDIATE_CONTEXT_RELEASE,
    CALL_D3D11_IMMEDIATE_CONTEXT_RESOLVESUBRESOURCE,
    CALL_D3D11_IMMEDIATE_CONTEXT_RSGETSCISSORRECTS,
    CALL_D3D11_IMMEDIATE_CONTEXT_RSGETSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_RSGETVIEWPORTS,
    CALL_D3D11_IMMEDIATE_CONTEXT_RSSETSCISSORRECTS,
    CALL_D3D11_IMMEDIATE_CONTEXT_RSSETSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_RSSETVIEWPORTS,
    CALL_D3D11_IMMEDIATE_CONTEXT_SETPREDICATION,
    CALL_D3D11_IMMEDIATE_CONTEXT_SETPRIVATEDATA,
    CALL_D3D11_IMMEDIATE_CONTEXT_SETPRIVATEDATAINTERFACE,
    CALL_D3D11_IMMEDIATE_CONTEXT_SETRESOURCEMINLOD,
    CALL_D3D11_IMMEDIATE_CONTEXT_SOGETTARGETS,
    CALL_D3D11_IMMEDIATE_CONTEXT_SOSETTARGETS,
    CALL_D3D11_IMMEDIATE_CONTEXT_SWAPDEVICECONTEXTSTATE,
    CALL_D3D11_IMMEDIATE_CONTEXT_UNMAP,
    CALL_D3D11_IMMEDIATE_CONTEXT_UPDATESUBRESOURCE,
    CALL_D3D11_IMMEDIATE_CONTEXT_UPDATESUBRESOURCE1,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSGETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSGETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSGETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSGETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSGETSHADERRESOURCES,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSSETCONSTANTBUFFERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSSETCONSTANTBUFFERS1,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSSETSAMPLERS,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSSETSHADER,
    CALL_D3D11_IMMEDIATE_CONTEXT_VSSETSHADERRESOURCES,
    CALL_D3D11_TEXTURE1D_ADDREF,
    CALL_D3D11_TEXTURE1D_GETDESC,
    CALL_D3D11_TEXTURE1D_GETDEVICE,
    CALL_D3D11_TEXTURE1D_GETEVICTIONPRIORITY,
    CALL_D3D11_TEXTURE1D_GETPRIVATEDATA,
    CALL_D3D11_TEXTURE1D_GETTYPE,
    CALL_D3D11_TEXTURE1D_QUERYINTERFACE,
    CALL_D3D11_TEXTURE1D_RELEASE,
    CALL_D3D11_TEXTURE1D_SETEVICTIONPRIORITY,
    CALL_D3D11_TEXTURE1D_SETPRIVATEDATA,
    CALL_D3D11_TEXTURE1D_SETPRIVATEDATAINTERFACE,
    CALL_D3D11_TEXTURE2D_ADDREF,
    CALL_D3D11_TEXTURE2D_GETDESC,
    CALL_D3D11_TEXTURE2D_GETDEVICE,
    CALL_D3D11_TEXTURE2D_GETEVICTIONPRIORITY,
    CALL_D3D11_TEXTURE2D_GETPRIVATEDATA,
    CALL_D3D11_TEXTURE2D_GETTYPE,
    CALL_D3D11_TEXTURE2D_QUERYINTERFACE,
    CALL_D3D11_TEXTURE2D_RELEASE,
    CALL_D3D11_TEXTURE2D_SETEVICTIONPRIORITY,
    CALL_D3D11_TEXTURE2D_SETPRIVATEDATA,
    CALL_D3D11_TEXTURE2D_SETPRIVATEDATAINTERFACE,
    CALL_D3D11_TEXTURE3D_ADDREF,
    CALL_D3D11_TEXTURE3D_GETDESC,
    CALL_D3D11_TEXTURE3D_GETDEVICE,
    CALL_D3D11_TEXTURE3D_GETEVICTIONPRIORITY,
    CALL_D3D11_TEXTURE3D_GETPRIVATEDATA,
    CALL_D3D11_TEXTURE3D_GETTYPE,
    CALL_D3D11_TEXTURE3D_QUERYINTERFACE,
    CALL_D3D11_TEXTURE3D_RELEASE,
    CALL_D3D11_TEXTURE3D_SETEVICTIONPRIORITY,
    CALL_D3D11_TEXTURE3D_SETPRIVATEDATA,
    CALL_D3D11_TEXTURE3D_SETPRIVATEDATAINTERFACE,
    CALL_D3D_DEVICE_INNER_ADDREF,
    CALL_D3D_DEVICE_INNER_QUERYINTERFACE,
    CALL_D3D_DEVICE_INNER_RELEASE,
    CALL_INIT_DLL,
    CALL_LAYER_CREATE,
    CALL_LAYER_GET_SIZE,
    CALL_WRAP_IMPLICIT_SURFACE,
};

#ifdef QEMU_DLL_GUEST

typedef ID3D11Device ID3D11Device2;
typedef ID3D11DeviceContext ID3D11DeviceContext1;
typedef ID3D11BlendState ID3D11BlendState1;
typedef ID3D11RasterizerState ID3D11RasterizerState1;
typedef ID3D11DeviceContext1 ID3D11DeviceContext2;
typedef void ID3DDeviceContextState;
typedef void D3D11_BLEND_DESC1, D3D11_RASTERIZER_DESC1;
typedef void D3D11_PACKED_MIP_DESC, D3D11_TILE_SHAPE, D3D11_SUBRESOURCE_TILING;

#endif

struct qemu_d3d11_device_context
{
    /* Guest fields */
    ID3D11DeviceContext1 ID3D11DeviceContext1_iface;

    /* Host fields */
    ID3D11DeviceContext1 *host;
};

struct qemu_d3d11_device
{
    /* Guest fields */
    IUnknown IUnknown_inner;
    ID3D11Device2 ID3D11Device2_iface;
    ID3D10Device1 ID3D10Device1_iface;
    ID3D10Multithread ID3D10Multithread_iface;
    IQemuD3D11Device IQemuD3D11Device_iface;
    IUnknown *outer_unk;

    /* Host fields */
    ID3D11Device2 *host_d3d11;
    ID3D10Device1 *host_d3d10;
    ID3D10Multithread *host_mt;
    struct qemu_d3d11_device_context immediate_context;
};

struct qemu_d3d11_texture1d
{
    /* Guest fields */
    ID3D11Texture1D ID3D11Texture1D_iface;
    ID3D10Texture1D ID3D10Texture1D_iface;
    IUnknown *dxgi_surface;

    /* Host fields */
    ID3D11Texture1D *host11;
    ID3D10Texture1D *host10;
    IUnknown priv_data_iface;
    ULONG refcount;
};

struct qemu_d3d11_texture2d
{
    /* Guest fields */
    ID3D11Texture2D ID3D11Texture2D_iface;
    ID3D10Texture2D ID3D10Texture2D_iface;
    IUnknown *dxgi_surface;

    /* Host fields */
    ID3D11Texture2D *host11;
    ID3D10Texture2D *host10;
    IUnknown priv_data_iface;
    ULONG refcount;
};

struct qemu_d3d11_texture3d
{
    /* Guest fields */
    ID3D11Texture3D ID3D11Texture3D_iface;
    ID3D10Texture3D ID3D10Texture3D_iface;
    IUnknown *dxgi_surface;

    /* Host fields */
    ID3D11Texture3D *host11;
    ID3D10Texture3D *host10;
};

#ifdef QEMU_DLL_GUEST

enum D3D11_USAGE d3d11_usage_from_d3d10_usage(enum D3D10_USAGE usage);
UINT d3d11_bind_flags_from_d3d10_bind_flags(UINT bind_flags);
UINT d3d11_cpu_access_flags_from_d3d10_cpu_access_flags(UINT cpu_access_flags);
UINT d3d11_resource_misc_flags_from_d3d10_resource_misc_flags(UINT resource_misc_flags);

static inline struct qemu_d3d11_device *impl_from_ID3D11Device2(ID3D11Device2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device, ID3D11Device2_iface);
}

static inline struct qemu_d3d11_device *impl_from_ID3D10Device(ID3D10Device1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device, ID3D10Device1_iface);
}

extern HRESULT (* WINAPI p_DXGID3D10CreateDevice)(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device);

void qemu_d3d11_device_guest_init(struct qemu_d3d11_device *device, void *outer_unknown);
void qemu_d3d11_context_guest_init(struct qemu_d3d11_device_context *context);
void qemu_d3d11_texture1d_guest_init(struct qemu_d3d11_texture1d *texture, struct qemu_d3d11_device *device,
        uint64_t dxgi_surface);
void qemu_d3d11_texture2d_guest_init(struct qemu_d3d11_texture2d *texture, struct qemu_d3d11_device *device,
        uint64_t dxgi_surface);
void qemu_d3d11_texture3d_guest_init(struct qemu_d3d11_texture3d *texture, struct qemu_d3d11_device *device,
        uint64_t dxgi_surface);

#else

extern const struct qemu_ops *qemu_ops;

void qemu_d3d10_device_CheckCounter(struct qemu_syscall *call);
void qemu_d3d10_device_CheckCounterInfo(struct qemu_syscall *call);
void qemu_d3d10_device_CheckFormatSupport(struct qemu_syscall *call);
void qemu_d3d10_device_CheckMultisampleQualityLevels(struct qemu_syscall *call);
void qemu_d3d10_device_ClearDepthStencilView(struct qemu_syscall *call);
void qemu_d3d10_device_ClearRenderTargetView(struct qemu_syscall *call);
void qemu_d3d10_device_ClearState(struct qemu_syscall *call);
void qemu_d3d10_device_CopyResource(struct qemu_syscall *call);
void qemu_d3d10_device_CopySubresourceRegion(struct qemu_syscall *call);
void qemu_d3d10_device_CreateBlendState(struct qemu_syscall *call);
void qemu_d3d10_device_CreateBlendState1(struct qemu_syscall *call);
void qemu_d3d10_device_CreateBuffer(struct qemu_syscall *call);
void qemu_d3d10_device_CreateCounter(struct qemu_syscall *call);
void qemu_d3d10_device_CreateDepthStencilState(struct qemu_syscall *call);
void qemu_d3d10_device_CreateDepthStencilView(struct qemu_syscall *call);
void qemu_d3d10_device_CreateGeometryShader(struct qemu_syscall *call);
void qemu_d3d10_device_CreateGeometryShaderWithStreamOutput(struct qemu_syscall *call);
void qemu_d3d10_device_CreateInputLayout(struct qemu_syscall *call);
void qemu_d3d10_device_CreatePixelShader(struct qemu_syscall *call);
void qemu_d3d10_device_CreatePredicate(struct qemu_syscall *call);
void qemu_d3d10_device_CreateQuery(struct qemu_syscall *call);
void qemu_d3d10_device_CreateRasterizerState(struct qemu_syscall *call);
void qemu_d3d10_device_CreateRenderTargetView(struct qemu_syscall *call);
void qemu_d3d10_device_CreateSamplerState(struct qemu_syscall *call);
void qemu_d3d10_device_CreateShaderResourceView(struct qemu_syscall *call);
void qemu_d3d10_device_CreateShaderResourceView1(struct qemu_syscall *call);
void qemu_d3d10_device_CreateTexture3D(struct qemu_syscall *call);
void qemu_d3d10_device_CreateVertexShader(struct qemu_syscall *call);
void qemu_d3d10_device_Draw(struct qemu_syscall *call);
void qemu_d3d10_device_DrawAuto(struct qemu_syscall *call);
void qemu_d3d10_device_DrawIndexed(struct qemu_syscall *call);
void qemu_d3d10_device_DrawIndexedInstanced(struct qemu_syscall *call);
void qemu_d3d10_device_DrawInstanced(struct qemu_syscall *call);
void qemu_d3d10_device_Flush(struct qemu_syscall *call);
void qemu_d3d10_device_GSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_GSGetSamplers(struct qemu_syscall *call);
void qemu_d3d10_device_GSGetShader(struct qemu_syscall *call);
void qemu_d3d10_device_GSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d10_device_GSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_GSSetSamplers(struct qemu_syscall *call);
void qemu_d3d10_device_GSSetShader(struct qemu_syscall *call);
void qemu_d3d10_device_GSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d10_device_GenerateMips(struct qemu_syscall *call);
void qemu_d3d10_device_GetCreationFlags(struct qemu_syscall *call);
void qemu_d3d10_device_GetDeviceRemovedReason(struct qemu_syscall *call);
void qemu_d3d10_device_GetExceptionMode(struct qemu_syscall *call);
void qemu_d3d10_device_GetFeatureLevel(struct qemu_syscall *call);
void qemu_d3d11_device_GetImmediateContext(struct qemu_syscall *call);
void qemu_d3d11_device_GetImmediateContext1(struct qemu_syscall *call);
void qemu_d3d11_device_GetImmediateContext2(struct qemu_syscall *call);
void qemu_d3d10_device_GetPredication(struct qemu_syscall *call);
void qemu_d3d10_device_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_device_GetTextFilterSize(struct qemu_syscall *call);
void qemu_d3d10_device_IAGetIndexBuffer(struct qemu_syscall *call);
void qemu_d3d10_device_IAGetInputLayout(struct qemu_syscall *call);
void qemu_d3d10_device_IAGetPrimitiveTopology(struct qemu_syscall *call);
void qemu_d3d10_device_IAGetVertexBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_IASetIndexBuffer(struct qemu_syscall *call);
void qemu_d3d10_device_IASetInputLayout(struct qemu_syscall *call);
void qemu_d3d10_device_IASetPrimitiveTopology(struct qemu_syscall *call);
void qemu_d3d10_device_IASetVertexBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_OMGetBlendState(struct qemu_syscall *call);
void qemu_d3d10_device_OMGetDepthStencilState(struct qemu_syscall *call);
void qemu_d3d10_device_OMGetRenderTargets(struct qemu_syscall *call);
void qemu_d3d10_device_OMSetBlendState(struct qemu_syscall *call);
void qemu_d3d10_device_OMSetDepthStencilState(struct qemu_syscall *call);
void qemu_d3d10_device_OMSetRenderTargets(struct qemu_syscall *call);
void qemu_d3d10_device_OpenSharedResource(struct qemu_syscall *call);
void qemu_d3d10_device_PSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_PSGetSamplers(struct qemu_syscall *call);
void qemu_d3d10_device_PSGetShader(struct qemu_syscall *call);
void qemu_d3d10_device_PSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d10_device_PSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_PSSetSamplers(struct qemu_syscall *call);
void qemu_d3d10_device_PSSetShader(struct qemu_syscall *call);
void qemu_d3d10_device_PSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d10_device_RSGetScissorRects(struct qemu_syscall *call);
void qemu_d3d10_device_RSGetState(struct qemu_syscall *call);
void qemu_d3d10_device_RSGetViewports(struct qemu_syscall *call);
void qemu_d3d10_device_RSSetScissorRects(struct qemu_syscall *call);
void qemu_d3d10_device_RSSetState(struct qemu_syscall *call);
void qemu_d3d10_device_RSSetViewports(struct qemu_syscall *call);
void qemu_d3d10_device_ResolveSubresource(struct qemu_syscall *call);
void qemu_d3d10_device_SOGetTargets(struct qemu_syscall *call);
void qemu_d3d10_device_SOSetTargets(struct qemu_syscall *call);
void qemu_d3d10_device_SetExceptionMode(struct qemu_syscall *call);
void qemu_d3d10_device_SetPredication(struct qemu_syscall *call);
void qemu_d3d10_device_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_device_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d10_device_SetTextFilterSize(struct qemu_syscall *call);
void qemu_d3d10_device_UpdateSubresource(struct qemu_syscall *call);
void qemu_d3d10_device_VSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_VSGetSamplers(struct qemu_syscall *call);
void qemu_d3d10_device_VSGetShader(struct qemu_syscall *call);
void qemu_d3d10_device_VSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d10_device_VSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d10_device_VSSetSamplers(struct qemu_syscall *call);
void qemu_d3d10_device_VSSetShader(struct qemu_syscall *call);
void qemu_d3d10_device_VSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d10_multithread_Enter(struct qemu_syscall *call);
void qemu_d3d10_multithread_GetMultithreadProtected(struct qemu_syscall *call);
void qemu_d3d10_multithread_Leave(struct qemu_syscall *call);
void qemu_d3d10_multithread_SetMultithreadProtected(struct qemu_syscall *call);
void qemu_d3d10_texture1d_AddRef(struct qemu_syscall *call);
void qemu_d3d10_texture1d_GetDesc(struct qemu_syscall *call);
void qemu_d3d10_texture1d_GetDevice(struct qemu_syscall *call);
void qemu_d3d10_texture1d_GetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d10_texture1d_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_texture1d_GetType(struct qemu_syscall *call);
void qemu_d3d10_texture1d_Map(struct qemu_syscall *call);
void qemu_d3d10_texture1d_QueryInterface(struct qemu_syscall *call);
void qemu_d3d10_texture1d_Release(struct qemu_syscall *call);
void qemu_d3d10_texture1d_SetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d10_texture1d_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_texture1d_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d10_texture1d_Unmap(struct qemu_syscall *call);
void qemu_d3d10_texture2d_AddRef(struct qemu_syscall *call);
void qemu_d3d10_texture2d_GetDesc(struct qemu_syscall *call);
void qemu_d3d10_texture2d_GetDevice(struct qemu_syscall *call);
void qemu_d3d10_texture2d_GetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d10_texture2d_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_texture2d_GetType(struct qemu_syscall *call);
void qemu_d3d10_texture2d_Map(struct qemu_syscall *call);
void qemu_d3d10_texture2d_QueryInterface(struct qemu_syscall *call);
void qemu_d3d10_texture2d_Release(struct qemu_syscall *call);
void qemu_d3d10_texture2d_SetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d10_texture2d_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_texture2d_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d10_texture2d_Unmap(struct qemu_syscall *call);
void qemu_d3d10_texture3d_AddRef(struct qemu_syscall *call);
void qemu_d3d10_texture3d_GetDesc(struct qemu_syscall *call);
void qemu_d3d10_texture3d_GetDevice(struct qemu_syscall *call);
void qemu_d3d10_texture3d_GetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d10_texture3d_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_texture3d_GetType(struct qemu_syscall *call);
void qemu_d3d10_texture3d_Map(struct qemu_syscall *call);
void qemu_d3d10_texture3d_QueryInterface(struct qemu_syscall *call);
void qemu_d3d10_texture3d_Release(struct qemu_syscall *call);
void qemu_d3d10_texture3d_SetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d10_texture3d_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d10_texture3d_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d10_texture3d_Unmap(struct qemu_syscall *call);
void qemu_d3d11_device_CheckCounter(struct qemu_syscall *call);
void qemu_d3d11_device_CheckCounterInfo(struct qemu_syscall *call);
void qemu_d3d11_device_CheckFeatureSupport(struct qemu_syscall *call);
void qemu_d3d11_device_CheckFormatSupport(struct qemu_syscall *call);
void qemu_d3d11_device_CheckMultisampleQualityLevels(struct qemu_syscall *call);
void qemu_d3d11_device_CheckMultisampleQualityLevels1(struct qemu_syscall *call);
void qemu_d3d11_device_CreateBlendState(struct qemu_syscall *call);
void qemu_d3d11_device_CreateBlendState1(struct qemu_syscall *call);
void qemu_d3d11_device_CreateBuffer(struct qemu_syscall *call);
void qemu_d3d11_device_CreateClassLinkage(struct qemu_syscall *call);
void qemu_d3d11_device_CreateComputeShader(struct qemu_syscall *call);
void qemu_d3d11_device_CreateCounter(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDeferredContext(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDeferredContext1(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDeferredContext2(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDepthStencilState(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDepthStencilView(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDeviceContextState(struct qemu_syscall *call);
void qemu_d3d11_device_CreateDomainShader(struct qemu_syscall *call);
void qemu_d3d11_device_CreateGeometryShader(struct qemu_syscall *call);
void qemu_d3d11_device_CreateGeometryShaderWithStreamOutput(struct qemu_syscall *call);
void qemu_d3d11_device_CreateHullShader(struct qemu_syscall *call);
void qemu_d3d11_device_CreateInputLayout(struct qemu_syscall *call);
void qemu_d3d11_device_CreatePixelShader(struct qemu_syscall *call);
void qemu_d3d11_device_CreatePredicate(struct qemu_syscall *call);
void qemu_d3d11_device_CreateQuery(struct qemu_syscall *call);
void qemu_d3d11_device_CreateRasterizerState(struct qemu_syscall *call);
void qemu_d3d11_device_CreateRasterizerState1(struct qemu_syscall *call);
void qemu_d3d11_device_CreateRenderTargetView(struct qemu_syscall *call);
void qemu_d3d11_device_CreateSamplerState(struct qemu_syscall *call);
void qemu_d3d11_device_CreateShaderResourceView(struct qemu_syscall *call);
void qemu_d3d11_device_CreateTexture1D(struct qemu_syscall *call);
void qemu_d3d11_device_CreateTexture2D(struct qemu_syscall *call);
void qemu_d3d11_device_CreateTexture3D(struct qemu_syscall *call);
void qemu_d3d11_device_CreateUnorderedAccessView(struct qemu_syscall *call);
void qemu_d3d11_device_CreateVertexShader(struct qemu_syscall *call);
void qemu_d3d11_device_GetCreationFlags(struct qemu_syscall *call);
void qemu_d3d11_device_GetDeviceRemovedReason(struct qemu_syscall *call);
void qemu_d3d11_device_GetExceptionMode(struct qemu_syscall *call);
void qemu_d3d11_device_GetFeatureLevel(struct qemu_syscall *call);
void qemu_d3d11_device_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_device_GetResourceTiling(struct qemu_syscall *call);
void qemu_d3d11_device_OpenSharedResource(struct qemu_syscall *call);
void qemu_d3d11_device_OpenSharedResource1(struct qemu_syscall *call);
void qemu_d3d11_device_OpenSharedResourceByName(struct qemu_syscall *call);
void qemu_d3d11_device_SetExceptionMode(struct qemu_syscall *call);
void qemu_d3d11_device_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_device_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_AddRef(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Begin(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSGetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSGetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSGetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSGetUnorderedAccessViews(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSSetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSSetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSSetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CSSetUnorderedAccessViews(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ClearDepthStencilView(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ClearRenderTargetView(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ClearState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ClearView(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CopyResource(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CopyStructureCount(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CopySubresourceRegion(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_CopySubresourceRegion1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSGetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSGetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSGetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSSetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSSetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSSetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DiscardResource(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DiscardView(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DiscardView1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Dispatch(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DispatchIndirect(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Draw(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DrawAuto(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DrawIndexed(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DrawIndexedInstanced(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DrawInstanced(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_DrawInstancedIndirect(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_End(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ExecuteCommandList(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_FinishCommandList(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Flush(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSGetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSGetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSGetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSSetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSSetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSSetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GenerateMips(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetContextFlags(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetData(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetDevice(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetPredication(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetResourceMinLOD(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_GetType(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSGetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSGetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSGetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSSetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSSetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSSetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_HSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IAGetIndexBuffer(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IAGetInputLayout(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IAGetPrimitiveTopology(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IAGetVertexBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IASetIndexBuffer(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IASetInputLayout(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IASetPrimitiveTopology(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_IASetVertexBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Map(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMGetBlendState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMGetDepthStencilState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMGetRenderTargets(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMSetBlendState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMSetDepthStencilState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMSetRenderTargets(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSGetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSGetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSGetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSSetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSSetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSSetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_PSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_QueryInterface(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_RSGetScissorRects(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_RSGetState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_RSGetViewports(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_RSSetScissorRects(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_RSSetState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_RSSetViewports(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Release(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_ResolveSubresource(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SOGetTargets(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SOSetTargets(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SetPredication(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SetResourceMinLOD(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_SwapDeviceContextState(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_Unmap(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_UpdateSubresource(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_UpdateSubresource1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSGetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSGetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSGetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSGetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSGetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSSetConstantBuffers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSSetConstantBuffers1(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSSetSamplers(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSSetShader(struct qemu_syscall *call);
void qemu_d3d11_immediate_context_VSSetShaderResources(struct qemu_syscall *call);
void qemu_d3d11_texture1d_AddRef(struct qemu_syscall *call);
void qemu_d3d11_texture1d_GetDesc(struct qemu_syscall *call);
void qemu_d3d11_texture1d_GetDevice(struct qemu_syscall *call);
void qemu_d3d11_texture1d_GetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d11_texture1d_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_texture1d_GetType(struct qemu_syscall *call);
void qemu_d3d11_texture1d_QueryInterface(struct qemu_syscall *call);
void qemu_d3d11_texture1d_Release(struct qemu_syscall *call);
void qemu_d3d11_texture1d_SetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d11_texture1d_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_texture1d_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d11_texture2d_AddRef(struct qemu_syscall *call);
void qemu_d3d11_texture2d_GetDesc(struct qemu_syscall *call);
void qemu_d3d11_texture2d_GetDevice(struct qemu_syscall *call);
void qemu_d3d11_texture2d_GetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d11_texture2d_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_texture2d_GetType(struct qemu_syscall *call);
void qemu_d3d11_texture2d_QueryInterface(struct qemu_syscall *call);
void qemu_d3d11_texture2d_Release(struct qemu_syscall *call);
void qemu_d3d11_texture2d_SetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d11_texture2d_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_texture2d_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d11_texture3d_AddRef(struct qemu_syscall *call);
void qemu_d3d11_texture3d_GetDesc(struct qemu_syscall *call);
void qemu_d3d11_texture3d_GetDevice(struct qemu_syscall *call);
void qemu_d3d11_texture3d_GetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d11_texture3d_GetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_texture3d_GetType(struct qemu_syscall *call);
void qemu_d3d11_texture3d_QueryInterface(struct qemu_syscall *call);
void qemu_d3d11_texture3d_Release(struct qemu_syscall *call);
void qemu_d3d11_texture3d_SetEvictionPriority(struct qemu_syscall *call);
void qemu_d3d11_texture3d_SetPrivateData(struct qemu_syscall *call);
void qemu_d3d11_texture3d_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_d3d_device_inner_AddRef(struct qemu_syscall *call);
void qemu_d3d_device_inner_QueryInterface(struct qemu_syscall *call);
void qemu_d3d_device_inner_Release(struct qemu_syscall *call);
void qemu_wrap_implicit_surface(struct qemu_syscall *call);

HRESULT qemu_d3d11_texture1d_create(ID3D11Texture1D *host, struct qemu_d3d11_device *device,
        uint64_t *dxgi_surface, struct qemu_d3d11_texture1d **texture);
HRESULT qemu_d3d11_texture2d_create(ID3D11Texture2D *host, struct qemu_d3d11_device *device,
        uint64_t *dxgi_surface, struct qemu_d3d11_texture2d **texture);

#endif

#endif
