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

#ifndef QEMU_DDRAW_H
#define QEMU_DDRAW_H

enum ddraw_calls
{
    CALL_CF_CREATEOBJECT = 0,
    CALL_D3D1_CREATELIGHT,
    CALL_D3D1_CREATEMATERIAL,
    CALL_D3D1_CREATEVIEWPORT,
    CALL_D3D1_ENUMDEVICES,
    CALL_D3D1_FINDDEVICE,
    CALL_D3D1_INITIALIZE,
    CALL_D3D2_CREATEDEVICE,
    CALL_D3D2_CREATELIGHT,
    CALL_D3D2_CREATEMATERIAL,
    CALL_D3D2_CREATEVIEWPORT,
    CALL_D3D2_ENUMDEVICES,
    CALL_D3D2_FINDDEVICE,
    CALL_D3D3_CREATEDEVICE,
    CALL_D3D3_CREATELIGHT,
    CALL_D3D3_CREATEMATERIAL,
    CALL_D3D3_CREATEVERTEXBUFFER,
    CALL_D3D3_CREATEVIEWPORT,
    CALL_D3D3_ENUMDEVICES,
    CALL_D3D3_ENUMZBUFFERFORMATS,
    CALL_D3D3_EVICTMANAGEDTEXTURES,
    CALL_D3D3_FINDDEVICE,
    CALL_D3D7_CREATEDEVICE,
    CALL_D3D7_CREATEVERTEXBUFFER,
    CALL_D3D7_ENUMDEVICES,
    CALL_D3D7_ENUMZBUFFERFORMATS,
    CALL_D3D7_EVICTMANAGEDTEXTURES,
    CALL_D3D_TEXTURE1_GETHANDLE,
    CALL_D3D_TEXTURE1_INITIALIZE,
    CALL_D3D_TEXTURE1_LOAD,
    CALL_D3D_TEXTURE1_PALETTECHANGED,
    CALL_D3D_TEXTURE1_UNLOAD,
    CALL_D3D_TEXTURE2_GETHANDLE,
    CALL_D3D_TEXTURE2_LOAD,
    CALL_D3D_TEXTURE2_PALETTECHANGED,
    CALL_DDRAW1_COMPACT,
    CALL_DDRAW1_CREATEPALETTE,
    CALL_DDRAW1_CREATESURFACE,
    CALL_DDRAW1_DUPLICATESURFACE,
    CALL_DDRAW1_ENUMSURFACES,
    CALL_DDRAW1_FLIPTOGDISURFACE,
    CALL_DDRAW1_GETCAPS,
    CALL_DDRAW1_GETDISPLAYMODE,
    CALL_DDRAW1_GETFOURCCCODES,
    CALL_DDRAW1_GETGDISURFACE,
    CALL_DDRAW1_GETMONITORFREQUENCY,
    CALL_DDRAW1_GETSCANLINE,
    CALL_DDRAW1_GETVERTICALBLANKSTATUS,
    CALL_DDRAW1_INITIALIZE,
    CALL_DDRAW1_QUERYINTERFACE,
    CALL_DDRAW1_RELEASE,
    CALL_DDRAW1_RESTOREDISPLAYMODE,
    CALL_DDRAW1_SETCOOPERATIVELEVEL,
    CALL_DDRAW1_SETDISPLAYMODE,
    CALL_DDRAW1_WAITFORVERTICALBLANK,
    CALL_DDRAW2_COMPACT,
    CALL_DDRAW2_CREATEPALETTE,
    CALL_DDRAW2_CREATESURFACE,
    CALL_DDRAW2_DUPLICATESURFACE,
    CALL_DDRAW2_ENUMDISPLAYMODES,
    CALL_DDRAW2_ENUMSURFACES,
    CALL_DDRAW2_FLIPTOGDISURFACE,
    CALL_DDRAW2_GETAVAILABLEVIDMEM,
    CALL_DDRAW2_GETCAPS,
    CALL_DDRAW2_GETDISPLAYMODE,
    CALL_DDRAW2_GETFOURCCCODES,
    CALL_DDRAW2_GETGDISURFACE,
    CALL_DDRAW2_GETMONITORFREQUENCY,
    CALL_DDRAW2_GETSCANLINE,
    CALL_DDRAW2_GETVERTICALBLANKSTATUS,
    CALL_DDRAW2_INITIALIZE,
    CALL_DDRAW2_RESTOREDISPLAYMODE,
    CALL_DDRAW2_SETCOOPERATIVELEVEL,
    CALL_DDRAW2_SETDISPLAYMODE,
    CALL_DDRAW2_WAITFORVERTICALBLANK,
    CALL_DDRAW4_COMPACT,
    CALL_DDRAW4_CREATEPALETTE,
    CALL_DDRAW4_CREATESURFACE,
    CALL_DDRAW4_DUPLICATESURFACE,
    CALL_DDRAW4_ENUMSURFACES,
    CALL_DDRAW4_FLIPTOGDISURFACE,
    CALL_DDRAW4_GETAVAILABLEVIDMEM,
    CALL_DDRAW4_GETCAPS,
    CALL_DDRAW4_GETDEVICEIDENTIFIER,
    CALL_DDRAW4_GETDISPLAYMODE,
    CALL_DDRAW4_GETFOURCCCODES,
    CALL_DDRAW4_GETGDISURFACE,
    CALL_DDRAW4_GETMONITORFREQUENCY,
    CALL_DDRAW4_GETSCANLINE,
    CALL_DDRAW4_GETSURFACEFROMDC,
    CALL_DDRAW4_GETVERTICALBLANKSTATUS,
    CALL_DDRAW4_INITIALIZE,
    CALL_DDRAW4_RESTOREALLSURFACES,
    CALL_DDRAW4_RESTOREDISPLAYMODE,
    CALL_DDRAW4_SETCOOPERATIVELEVEL,
    CALL_DDRAW4_SETDISPLAYMODE,
    CALL_DDRAW4_TESTCOOPERATIVELEVEL,
    CALL_DDRAW4_WAITFORVERTICALBLANK,
    CALL_DDRAW7_COMPACT,
    CALL_DDRAW7_CREATEPALETTE,
    CALL_DDRAW7_CREATESURFACE,
    CALL_DDRAW7_DUPLICATESURFACE,
    CALL_DDRAW7_ENUMDISPLAYMODES,
    CALL_DDRAW7_ENUMSURFACES,
    CALL_DDRAW7_EVALUATEMODE,
    CALL_DDRAW7_FLIPTOGDISURFACE,
    CALL_DDRAW7_GETAVAILABLEVIDMEM,
    CALL_DDRAW7_GETCAPS,
    CALL_DDRAW7_GETDEVICEIDENTIFIER,
    CALL_DDRAW7_GETDISPLAYMODE,
    CALL_DDRAW7_GETFOURCCCODES,
    CALL_DDRAW7_GETGDISURFACE,
    CALL_DDRAW7_GETMONITORFREQUENCY,
    CALL_DDRAW7_GETSCANLINE,
    CALL_DDRAW7_GETSURFACEFROMDC,
    CALL_DDRAW7_GETVERTICALBLANKSTATUS,
    CALL_DDRAW7_INITIALIZE,
    CALL_DDRAW7_RESTOREALLSURFACES,
    CALL_DDRAW7_RESTOREDISPLAYMODE,
    CALL_DDRAW7_SETCOOPERATIVELEVEL,
    CALL_DDRAW7_SETDISPLAYMODE,
    CALL_DDRAW7_STARTMODETEST,
    CALL_DDRAW7_TESTCOOPERATIVELEVEL,
    CALL_DDRAW7_WAITFORVERTICALBLANK,
    CALL_DDRAW_CLIPPER_GETCLIPLIST,
    CALL_DDRAW_CLIPPER_GETHWND,
    CALL_DDRAW_CLIPPER_INITIALIZE,
    CALL_DDRAW_CLIPPER_ISCLIPLISTCHANGED,
    CALL_DDRAW_CLIPPER_RELEASE,
    CALL_DDRAW_CLIPPER_SETCLIPLIST,
    CALL_DDRAW_CLIPPER_SETHWND,
    CALL_DDRAW_GAMMA_CONTROL_GETGAMMARAMP,
    CALL_DDRAW_GAMMA_CONTROL_SETGAMMARAMP,
    CALL_DDRAW_SURFACE1_ADDATTACHEDSURFACE,
    CALL_DDRAW_SURFACE1_ADDOVERLAYDIRTYRECT,
    CALL_DDRAW_SURFACE1_BLT,
    CALL_DDRAW_SURFACE1_BLTBATCH,
    CALL_DDRAW_SURFACE1_BLTFAST,
    CALL_DDRAW_SURFACE1_DELETEATTACHEDSURFACE,
    CALL_DDRAW_SURFACE1_ENUMATTACHEDSURFACES,
    CALL_DDRAW_SURFACE1_ENUMOVERLAYZORDERS,
    CALL_DDRAW_SURFACE1_FLIP,
    CALL_DDRAW_SURFACE1_GETATTACHEDSURFACE,
    CALL_DDRAW_SURFACE1_GETBLTSTATUS,
    CALL_DDRAW_SURFACE1_GETCAPS,
    CALL_DDRAW_SURFACE1_GETCLIPPER,
    CALL_DDRAW_SURFACE1_GETCOLORKEY,
    CALL_DDRAW_SURFACE1_GETDC,
    CALL_DDRAW_SURFACE1_GETFLIPSTATUS,
    CALL_DDRAW_SURFACE1_GETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE1_GETPALETTE,
    CALL_DDRAW_SURFACE1_GETPIXELFORMAT,
    CALL_DDRAW_SURFACE1_GETSURFACEDESC,
    CALL_DDRAW_SURFACE1_INITIALIZE,
    CALL_DDRAW_SURFACE1_ISLOST,
    CALL_DDRAW_SURFACE1_LOCK,
    CALL_DDRAW_SURFACE1_RELEASE,
    CALL_DDRAW_SURFACE1_RELEASEDC,
    CALL_DDRAW_SURFACE1_RESTORE,
    CALL_DDRAW_SURFACE1_SETCLIPPER,
    CALL_DDRAW_SURFACE1_SETCOLORKEY,
    CALL_DDRAW_SURFACE1_SETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE1_SETPALETTE,
    CALL_DDRAW_SURFACE1_UNLOCK,
    CALL_DDRAW_SURFACE1_UPDATEOVERLAY,
    CALL_DDRAW_SURFACE1_UPDATEOVERLAYDISPLAY,
    CALL_DDRAW_SURFACE1_UPDATEOVERLAYZORDER,
    CALL_DDRAW_SURFACE2_ADDATTACHEDSURFACE,
    CALL_DDRAW_SURFACE2_ADDOVERLAYDIRTYRECT,
    CALL_DDRAW_SURFACE2_BLT,
    CALL_DDRAW_SURFACE2_BLTBATCH,
    CALL_DDRAW_SURFACE2_BLTFAST,
    CALL_DDRAW_SURFACE2_DELETEATTACHEDSURFACE,
    CALL_DDRAW_SURFACE2_ENUMATTACHEDSURFACES,
    CALL_DDRAW_SURFACE2_ENUMOVERLAYZORDERS,
    CALL_DDRAW_SURFACE2_FLIP,
    CALL_DDRAW_SURFACE2_GETATTACHEDSURFACE,
    CALL_DDRAW_SURFACE2_GETBLTSTATUS,
    CALL_DDRAW_SURFACE2_GETCAPS,
    CALL_DDRAW_SURFACE2_GETCLIPPER,
    CALL_DDRAW_SURFACE2_GETCOLORKEY,
    CALL_DDRAW_SURFACE2_GETDC,
    CALL_DDRAW_SURFACE2_GETDDINTERFACE,
    CALL_DDRAW_SURFACE2_GETFLIPSTATUS,
    CALL_DDRAW_SURFACE2_GETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE2_GETPALETTE,
    CALL_DDRAW_SURFACE2_GETPIXELFORMAT,
    CALL_DDRAW_SURFACE2_GETSURFACEDESC,
    CALL_DDRAW_SURFACE2_INITIALIZE,
    CALL_DDRAW_SURFACE2_ISLOST,
    CALL_DDRAW_SURFACE2_LOCK,
    CALL_DDRAW_SURFACE2_PAGELOCK,
    CALL_DDRAW_SURFACE2_PAGEUNLOCK,
    CALL_DDRAW_SURFACE2_RELEASEDC,
    CALL_DDRAW_SURFACE2_RESTORE,
    CALL_DDRAW_SURFACE2_SETCLIPPER,
    CALL_DDRAW_SURFACE2_SETCOLORKEY,
    CALL_DDRAW_SURFACE2_SETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE2_SETPALETTE,
    CALL_DDRAW_SURFACE2_UNLOCK,
    CALL_DDRAW_SURFACE2_UPDATEOVERLAY,
    CALL_DDRAW_SURFACE2_UPDATEOVERLAYDISPLAY,
    CALL_DDRAW_SURFACE2_UPDATEOVERLAYZORDER,
    CALL_DDRAW_SURFACE3_ADDATTACHEDSURFACE,
    CALL_DDRAW_SURFACE3_ADDOVERLAYDIRTYRECT,
    CALL_DDRAW_SURFACE3_BLT,
    CALL_DDRAW_SURFACE3_BLTBATCH,
    CALL_DDRAW_SURFACE3_BLTFAST,
    CALL_DDRAW_SURFACE3_DELETEATTACHEDSURFACE,
    CALL_DDRAW_SURFACE3_ENUMATTACHEDSURFACES,
    CALL_DDRAW_SURFACE3_ENUMOVERLAYZORDERS,
    CALL_DDRAW_SURFACE3_FLIP,
    CALL_DDRAW_SURFACE3_GETATTACHEDSURFACE,
    CALL_DDRAW_SURFACE3_GETBLTSTATUS,
    CALL_DDRAW_SURFACE3_GETCAPS,
    CALL_DDRAW_SURFACE3_GETCLIPPER,
    CALL_DDRAW_SURFACE3_GETCOLORKEY,
    CALL_DDRAW_SURFACE3_GETDC,
    CALL_DDRAW_SURFACE3_GETDDINTERFACE,
    CALL_DDRAW_SURFACE3_GETFLIPSTATUS,
    CALL_DDRAW_SURFACE3_GETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE3_GETPALETTE,
    CALL_DDRAW_SURFACE3_GETPIXELFORMAT,
    CALL_DDRAW_SURFACE3_GETSURFACEDESC,
    CALL_DDRAW_SURFACE3_INITIALIZE,
    CALL_DDRAW_SURFACE3_ISLOST,
    CALL_DDRAW_SURFACE3_LOCK,
    CALL_DDRAW_SURFACE3_PAGELOCK,
    CALL_DDRAW_SURFACE3_PAGEUNLOCK,
    CALL_DDRAW_SURFACE3_RELEASEDC,
    CALL_DDRAW_SURFACE3_RESTORE,
    CALL_DDRAW_SURFACE3_SETCLIPPER,
    CALL_DDRAW_SURFACE3_SETCOLORKEY,
    CALL_DDRAW_SURFACE3_SETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE3_SETPALETTE,
    CALL_DDRAW_SURFACE3_SETSURFACEDESC,
    CALL_DDRAW_SURFACE3_UNLOCK,
    CALL_DDRAW_SURFACE3_UPDATEOVERLAY,
    CALL_DDRAW_SURFACE3_UPDATEOVERLAYDISPLAY,
    CALL_DDRAW_SURFACE3_UPDATEOVERLAYZORDER,
    CALL_DDRAW_SURFACE4_ADDATTACHEDSURFACE,
    CALL_DDRAW_SURFACE4_ADDOVERLAYDIRTYRECT,
    CALL_DDRAW_SURFACE4_BLT,
    CALL_DDRAW_SURFACE4_BLTBATCH,
    CALL_DDRAW_SURFACE4_BLTFAST,
    CALL_DDRAW_SURFACE4_CHANGEUNIQUENESSVALUE,
    CALL_DDRAW_SURFACE4_DELETEATTACHEDSURFACE,
    CALL_DDRAW_SURFACE4_ENUMATTACHEDSURFACES,
    CALL_DDRAW_SURFACE4_ENUMOVERLAYZORDERS,
    CALL_DDRAW_SURFACE4_FLIP,
    CALL_DDRAW_SURFACE4_FREEPRIVATEDATA,
    CALL_DDRAW_SURFACE4_GETATTACHEDSURFACE,
    CALL_DDRAW_SURFACE4_GETBLTSTATUS,
    CALL_DDRAW_SURFACE4_GETCAPS,
    CALL_DDRAW_SURFACE4_GETCLIPPER,
    CALL_DDRAW_SURFACE4_GETCOLORKEY,
    CALL_DDRAW_SURFACE4_GETDC,
    CALL_DDRAW_SURFACE4_GETDDINTERFACE,
    CALL_DDRAW_SURFACE4_GETFLIPSTATUS,
    CALL_DDRAW_SURFACE4_GETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE4_GETPALETTE,
    CALL_DDRAW_SURFACE4_GETPIXELFORMAT,
    CALL_DDRAW_SURFACE4_GETPRIVATEDATA,
    CALL_DDRAW_SURFACE4_GETSURFACEDESC,
    CALL_DDRAW_SURFACE4_GETUNIQUENESSVALUE,
    CALL_DDRAW_SURFACE4_INITIALIZE,
    CALL_DDRAW_SURFACE4_ISLOST,
    CALL_DDRAW_SURFACE4_LOCK,
    CALL_DDRAW_SURFACE4_PAGELOCK,
    CALL_DDRAW_SURFACE4_PAGEUNLOCK,
    CALL_DDRAW_SURFACE4_RELEASEDC,
    CALL_DDRAW_SURFACE4_RESTORE,
    CALL_DDRAW_SURFACE4_SETCLIPPER,
    CALL_DDRAW_SURFACE4_SETCOLORKEY,
    CALL_DDRAW_SURFACE4_SETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE4_SETPALETTE,
    CALL_DDRAW_SURFACE4_SETPRIVATEDATA,
    CALL_DDRAW_SURFACE4_SETSURFACEDESC,
    CALL_DDRAW_SURFACE4_UNLOCK,
    CALL_DDRAW_SURFACE4_UPDATEOVERLAY,
    CALL_DDRAW_SURFACE4_UPDATEOVERLAYDISPLAY,
    CALL_DDRAW_SURFACE4_UPDATEOVERLAYZORDER,
    CALL_DDRAW_SURFACE7_ADDATTACHEDSURFACE,
    CALL_DDRAW_SURFACE7_ADDOVERLAYDIRTYRECT,
    CALL_DDRAW_SURFACE7_BLT,
    CALL_DDRAW_SURFACE7_BLTBATCH,
    CALL_DDRAW_SURFACE7_BLTFAST,
    CALL_DDRAW_SURFACE7_CHANGEUNIQUENESSVALUE,
    CALL_DDRAW_SURFACE7_DELETEATTACHEDSURFACE,
    CALL_DDRAW_SURFACE7_ENUMATTACHEDSURFACES,
    CALL_DDRAW_SURFACE7_ENUMOVERLAYZORDERS,
    CALL_DDRAW_SURFACE7_FLIP,
    CALL_DDRAW_SURFACE7_FREEPRIVATEDATA,
    CALL_DDRAW_SURFACE7_GETATTACHEDSURFACE,
    CALL_DDRAW_SURFACE7_GETBLTSTATUS,
    CALL_DDRAW_SURFACE7_GETCAPS,
    CALL_DDRAW_SURFACE7_GETCLIPPER,
    CALL_DDRAW_SURFACE7_GETCOLORKEY,
    CALL_DDRAW_SURFACE7_GETDC,
    CALL_DDRAW_SURFACE7_GETDDINTERFACE,
    CALL_DDRAW_SURFACE7_GETFLIPSTATUS,
    CALL_DDRAW_SURFACE7_GETLOD,
    CALL_DDRAW_SURFACE7_GETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE7_GETPALETTE,
    CALL_DDRAW_SURFACE7_GETPIXELFORMAT,
    CALL_DDRAW_SURFACE7_GETPRIORITY,
    CALL_DDRAW_SURFACE7_GETPRIVATEDATA,
    CALL_DDRAW_SURFACE7_GETSURFACEDESC,
    CALL_DDRAW_SURFACE7_GETUNIQUENESSVALUE,
    CALL_DDRAW_SURFACE7_INITIALIZE,
    CALL_DDRAW_SURFACE7_ISLOST,
    CALL_DDRAW_SURFACE7_LOCK,
    CALL_DDRAW_SURFACE7_PAGELOCK,
    CALL_DDRAW_SURFACE7_PAGEUNLOCK,
    CALL_DDRAW_SURFACE7_RELEASEDC,
    CALL_DDRAW_SURFACE7_RESTORE,
    CALL_DDRAW_SURFACE7_SETCLIPPER,
    CALL_DDRAW_SURFACE7_SETCOLORKEY,
    CALL_DDRAW_SURFACE7_SETLOD,
    CALL_DDRAW_SURFACE7_SETOVERLAYPOSITION,
    CALL_DDRAW_SURFACE7_SETPALETTE,
    CALL_DDRAW_SURFACE7_SETPRIORITY,
    CALL_DDRAW_SURFACE7_SETPRIVATEDATA,
    CALL_DDRAW_SURFACE7_SETSURFACEDESC,
    CALL_DDRAW_SURFACE7_UNLOCK,
    CALL_DDRAW_SURFACE7_UPDATEOVERLAY,
    CALL_DDRAW_SURFACE7_UPDATEOVERLAYDISPLAY,
    CALL_DDRAW_SURFACE7_UPDATEOVERLAYZORDER,
    CALL_DIRECTDRAWCREATE,
    CALL_DIRECTDRAWCREATECLIPPER,
    CALL_DIRECTDRAWCREATEEX,
    CALL_DIRECTDRAWENUMERATEA,
    CALL_DIRECTDRAWENUMERATEEXA,
    CALL_DIRECTDRAWENUMERATEEXW,
    CALL_DIRECTDRAWENUMERATEW,
    CALL_GETSURFACEFROMDC,
    CALL_INIT_DLL,
};

struct qemu_clipper
{
    /* Guest fields */
    IDirectDrawClipper IDirectDrawClipper_iface;
    LONG ref;

    /* Host fields */
    IDirectDrawClipper *host;
};

struct qemu_ddraw
{
    /* Guest fields */
    IDirectDraw7 IDirectDraw7_iface;
    IDirectDraw4 IDirectDraw4_iface;
    IDirectDraw2 IDirectDraw2_iface;
    IDirectDraw IDirectDraw_iface;
    IDirect3D7 IDirect3D7_iface;
    IDirect3D3 IDirect3D3_iface;
    IDirect3D2 IDirect3D2_iface;
    IDirect3D IDirect3D_iface;

    LONG ref7, ref4, ref2, ref3, ref1, numIfaces;

    /* Host fields */
    IDirect3D7 *host_d3d7;
    IDirect3D3 *host_d3d3;
    IDirect3D2 *host_d3d2;
    IDirect3D *host_d3d1;

    IDirectDraw7 *host_ddraw7;
    IDirectDraw4 *host_ddraw4;
    IDirectDraw2 *host_ddraw2;
    IDirectDraw *host_ddraw1;
};

struct qemu_surface
{
    /* Guest fields */
    IDirectDrawSurface7 IDirectDrawSurface7_iface;
    IDirectDrawSurface4 IDirectDrawSurface4_iface;
    IDirectDrawSurface3 IDirectDrawSurface3_iface;
    IDirectDrawSurface2 IDirectDrawSurface2_iface;
    IDirectDrawSurface IDirectDrawSurface_iface;
    IDirectDrawGammaControl IDirectDrawGammaControl_iface;
    IDirect3DTexture2 IDirect3DTexture2_iface;
    IDirect3DTexture IDirect3DTexture_iface;

    LONG                    ref7, ref4, ref3, ref2, ref1, iface_count, gamma_count;
    IUnknown                *ifaceToRelease;
    IUnknown *texture_outer;
    IUnknown                *attached_iface;

    int                     version;
    struct qemu_ddraw       *ddraw;

    /* FIXME: These fields need thread synchronization! */
    struct qemu_clipper     *clipper;
    /* TODO: Palette */

    /* Host fields */
    IDirectDrawSurface7     *host_surface7;
    IDirectDrawSurface4     *host_surface4;
    IDirectDrawSurface3     *host_surface3;
    IDirectDrawSurface2     *host_surface2;
    IDirectDrawSurface      *host_surface1;
    IDirectDrawGammaControl *host_gamma;
    IDirect3DTexture2       *host_texture2;
    IDirect3DTexture        *host_texture1;

    IUnknown                private_data;
    LONG                    private_data_ref;
};

#ifdef QEMU_DLL_GUEST

extern const GUID IID_D3DDEVICE_WineD3D;

struct qemu_ddraw *unsafe_impl_from_IDirectDraw(IDirectDraw *iface);
void ddraw_guest_init(struct qemu_ddraw *ddraw);

struct qemu_clipper *unsafe_impl_from_IDirectDrawClipper(IDirectDrawClipper *iface);
HRESULT WINAPI qemu_guest_DirectDrawCreateClipper(DWORD flags, IDirectDrawClipper **clipper, IUnknown *outer_unknown);
void ddraw_clipper_guest_init(struct qemu_clipper *clipper);

void qemu_surface_guest_init(struct qemu_surface *surface, struct qemu_ddraw *ddraw, unsigned int version);

void __fastcall ddraw_surface_destroy_cb(struct qemu_surface *surface);

#else

void qemu_DirectDrawCreateClipper(struct qemu_syscall *call);
void qemu_d3d1_CreateLight(struct qemu_syscall *call);
void qemu_d3d1_CreateMaterial(struct qemu_syscall *call);
void qemu_d3d1_CreateViewport(struct qemu_syscall *call);
void qemu_d3d1_EnumDevices(struct qemu_syscall *call);
void qemu_d3d1_FindDevice(struct qemu_syscall *call);
void qemu_d3d1_Initialize(struct qemu_syscall *call);
void qemu_d3d2_CreateDevice(struct qemu_syscall *call);
void qemu_d3d2_CreateLight(struct qemu_syscall *call);
void qemu_d3d2_CreateMaterial(struct qemu_syscall *call);
void qemu_d3d2_CreateViewport(struct qemu_syscall *call);
void qemu_d3d2_EnumDevices(struct qemu_syscall *call);
void qemu_d3d2_FindDevice(struct qemu_syscall *call);
void qemu_d3d3_CreateDevice(struct qemu_syscall *call);
void qemu_d3d3_CreateLight(struct qemu_syscall *call);
void qemu_d3d3_CreateMaterial(struct qemu_syscall *call);
void qemu_d3d3_CreateVertexBuffer(struct qemu_syscall *call);
void qemu_d3d3_CreateViewport(struct qemu_syscall *call);
void qemu_d3d3_EnumDevices(struct qemu_syscall *call);
void qemu_d3d3_EvictManagedTextures(struct qemu_syscall *call);
void qemu_d3d3_FindDevice(struct qemu_syscall *call);
void qemu_d3d7_CreateDevice(struct qemu_syscall *call);
void qemu_d3d7_CreateVertexBuffer(struct qemu_syscall *call);
void qemu_d3d7_EnumDevices(struct qemu_syscall *call);
void qemu_d3d_EnumZBufferFormats(struct qemu_syscall *call);
void qemu_d3d7_EvictManagedTextures(struct qemu_syscall *call);
void qemu_d3d_texture1_GetHandle(struct qemu_syscall *call);
void qemu_d3d_texture1_Initialize(struct qemu_syscall *call);
void qemu_d3d_texture1_Load(struct qemu_syscall *call);
void qemu_d3d_texture1_PaletteChanged(struct qemu_syscall *call);
void qemu_d3d_texture1_Unload(struct qemu_syscall *call);
void qemu_d3d_texture2_GetHandle(struct qemu_syscall *call);
void qemu_d3d_texture2_Load(struct qemu_syscall *call);
void qemu_d3d_texture2_PaletteChanged(struct qemu_syscall *call);
void qemu_ddraw1_Compact(struct qemu_syscall *call);
void qemu_ddraw1_CreatePalette(struct qemu_syscall *call);
void qemu_ddraw1_CreateSurface(struct qemu_syscall *call);
void qemu_ddraw1_DuplicateSurface(struct qemu_syscall *call);
void qemu_ddraw1_EnumSurfaces(struct qemu_syscall *call);
void qemu_ddraw1_FlipToGDISurface(struct qemu_syscall *call);
void qemu_ddraw1_GetCaps(struct qemu_syscall *call);
void qemu_ddraw1_GetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw1_GetFourCCCodes(struct qemu_syscall *call);
void qemu_ddraw1_GetGDISurface(struct qemu_syscall *call);
void qemu_ddraw1_GetMonitorFrequency(struct qemu_syscall *call);
void qemu_ddraw1_GetScanLine(struct qemu_syscall *call);
void qemu_ddraw1_GetVerticalBlankStatus(struct qemu_syscall *call);
void qemu_ddraw1_Initialize(struct qemu_syscall *call);
void qemu_ddraw1_QueryInterface(struct qemu_syscall *call);
void qemu_ddraw1_Release(struct qemu_syscall *call);
void qemu_ddraw1_RestoreDisplayMode(struct qemu_syscall *call);
void qemu_ddraw1_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw1_SetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw1_WaitForVerticalBlank(struct qemu_syscall *call);
void qemu_ddraw2_Compact(struct qemu_syscall *call);
void qemu_ddraw2_CreatePalette(struct qemu_syscall *call);
void qemu_ddraw2_CreateSurface(struct qemu_syscall *call);
void qemu_ddraw2_DuplicateSurface(struct qemu_syscall *call);
void qemu_ddraw2_EnumDisplayModes(struct qemu_syscall *call);
void qemu_ddraw2_EnumSurfaces(struct qemu_syscall *call);
void qemu_ddraw2_FlipToGDISurface(struct qemu_syscall *call);
void qemu_ddraw2_GetAvailableVidMem(struct qemu_syscall *call);
void qemu_ddraw2_GetCaps(struct qemu_syscall *call);
void qemu_ddraw2_GetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw2_GetFourCCCodes(struct qemu_syscall *call);
void qemu_ddraw2_GetGDISurface(struct qemu_syscall *call);
void qemu_ddraw2_GetMonitorFrequency(struct qemu_syscall *call);
void qemu_ddraw2_GetScanLine(struct qemu_syscall *call);
void qemu_ddraw2_GetVerticalBlankStatus(struct qemu_syscall *call);
void qemu_ddraw2_Initialize(struct qemu_syscall *call);
void qemu_ddraw2_RestoreDisplayMode(struct qemu_syscall *call);
void qemu_ddraw2_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw2_SetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw2_WaitForVerticalBlank(struct qemu_syscall *call);
void qemu_ddraw4_Compact(struct qemu_syscall *call);
void qemu_ddraw4_CreatePalette(struct qemu_syscall *call);
void qemu_ddraw4_CreateSurface(struct qemu_syscall *call);
void qemu_ddraw4_DuplicateSurface(struct qemu_syscall *call);
void qemu_ddraw4_EnumSurfaces(struct qemu_syscall *call);
void qemu_ddraw4_FlipToGDISurface(struct qemu_syscall *call);
void qemu_ddraw4_GetAvailableVidMem(struct qemu_syscall *call);
void qemu_ddraw4_GetCaps(struct qemu_syscall *call);
void qemu_ddraw4_GetDeviceIdentifier(struct qemu_syscall *call);
void qemu_ddraw4_GetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw4_GetFourCCCodes(struct qemu_syscall *call);
void qemu_ddraw4_GetGDISurface(struct qemu_syscall *call);
void qemu_ddraw4_GetMonitorFrequency(struct qemu_syscall *call);
void qemu_ddraw4_GetScanLine(struct qemu_syscall *call);
void qemu_ddraw4_GetSurfaceFromDC(struct qemu_syscall *call);
void qemu_ddraw4_GetVerticalBlankStatus(struct qemu_syscall *call);
void qemu_ddraw4_Initialize(struct qemu_syscall *call);
void qemu_ddraw4_RestoreAllSurfaces(struct qemu_syscall *call);
void qemu_ddraw4_RestoreDisplayMode(struct qemu_syscall *call);
void qemu_ddraw4_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw4_SetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw4_TestCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw4_WaitForVerticalBlank(struct qemu_syscall *call);
void qemu_ddraw7_Compact(struct qemu_syscall *call);
void qemu_ddraw7_CreatePalette(struct qemu_syscall *call);
void qemu_ddraw7_CreateSurface(struct qemu_syscall *call);
void qemu_ddraw7_DuplicateSurface(struct qemu_syscall *call);
void qemu_ddraw7_EnumDisplayModes(struct qemu_syscall *call);
void qemu_ddraw7_EnumSurfaces(struct qemu_syscall *call);
void qemu_ddraw7_EvaluateMode(struct qemu_syscall *call);
void qemu_ddraw7_FlipToGDISurface(struct qemu_syscall *call);
void qemu_ddraw7_GetAvailableVidMem(struct qemu_syscall *call);
void qemu_ddraw7_GetCaps(struct qemu_syscall *call);
void qemu_ddraw7_GetDeviceIdentifier(struct qemu_syscall *call);
void qemu_ddraw7_GetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw7_GetFourCCCodes(struct qemu_syscall *call);
void qemu_ddraw7_GetGDISurface(struct qemu_syscall *call);
void qemu_ddraw7_GetMonitorFrequency(struct qemu_syscall *call);
void qemu_ddraw7_GetScanLine(struct qemu_syscall *call);
void qemu_ddraw7_GetSurfaceFromDC(struct qemu_syscall *call);
void qemu_ddraw7_GetVerticalBlankStatus(struct qemu_syscall *call);
void qemu_ddraw7_Initialize(struct qemu_syscall *call);
void qemu_ddraw7_RestoreAllSurfaces(struct qemu_syscall *call);
void qemu_ddraw7_RestoreDisplayMode(struct qemu_syscall *call);
void qemu_ddraw7_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw7_SetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw7_StartModeTest(struct qemu_syscall *call);
void qemu_ddraw7_TestCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw7_WaitForVerticalBlank(struct qemu_syscall *call);
void qemu_ddraw_clipper_GetClipList(struct qemu_syscall *call);
void qemu_ddraw_clipper_GetHWnd(struct qemu_syscall *call);
void qemu_ddraw_clipper_Initialize(struct qemu_syscall *call);
void qemu_ddraw_clipper_IsClipListChanged(struct qemu_syscall *call);
void qemu_ddraw_clipper_Release(struct qemu_syscall *call);
void qemu_ddraw_clipper_SetClipList(struct qemu_syscall *call);
void qemu_ddraw_clipper_SetHWnd(struct qemu_syscall *call);
void qemu_ddraw_gamma_control_GetGammaRamp(struct qemu_syscall *call);
void qemu_ddraw_gamma_control_SetGammaRamp(struct qemu_syscall *call);
void qemu_ddraw_surface1_AddAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface1_AddOverlayDirtyRect(struct qemu_syscall *call);
void qemu_ddraw_surface1_Blt(struct qemu_syscall *call);
void qemu_ddraw_surface1_BltBatch(struct qemu_syscall *call);
void qemu_ddraw_surface1_BltFast(struct qemu_syscall *call);
void qemu_ddraw_surface1_DeleteAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface1_EnumAttachedSurfaces(struct qemu_syscall *call);
void qemu_ddraw_surface1_EnumOverlayZOrders(struct qemu_syscall *call);
void qemu_ddraw_surface1_Flip(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetBltStatus(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetCaps(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetDC(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetFlipStatus(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetPixelFormat(struct qemu_syscall *call);
void qemu_ddraw_surface1_GetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface1_Initialize(struct qemu_syscall *call);
void qemu_ddraw_surface1_IsLost(struct qemu_syscall *call);
void qemu_ddraw_surface1_Release(struct qemu_syscall *call);
void qemu_ddraw_surface1_ReleaseDC(struct qemu_syscall *call);
void qemu_ddraw_surface1_Restore(struct qemu_syscall *call);
void qemu_ddraw_surface1_SetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface1_SetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface1_SetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface1_Unlock(struct qemu_syscall *call);
void qemu_ddraw_surface1_UpdateOverlay(struct qemu_syscall *call);
void qemu_ddraw_surface1_UpdateOverlayDisplay(struct qemu_syscall *call);
void qemu_ddraw_surface1_UpdateOverlayZOrder(struct qemu_syscall *call);
void qemu_ddraw_surface2_AddAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface2_AddOverlayDirtyRect(struct qemu_syscall *call);
void qemu_ddraw_surface2_Blt(struct qemu_syscall *call);
void qemu_ddraw_surface2_BltBatch(struct qemu_syscall *call);
void qemu_ddraw_surface2_BltFast(struct qemu_syscall *call);
void qemu_ddraw_surface2_DeleteAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface2_EnumAttachedSurfaces(struct qemu_syscall *call);
void qemu_ddraw_surface2_EnumOverlayZOrders(struct qemu_syscall *call);
void qemu_ddraw_surface2_Flip(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetBltStatus(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetCaps(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetDC(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetDDInterface(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetFlipStatus(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetPixelFormat(struct qemu_syscall *call);
void qemu_ddraw_surface2_GetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface2_Initialize(struct qemu_syscall *call);
void qemu_ddraw_surface2_IsLost(struct qemu_syscall *call);
void qemu_ddraw_surface2_PageLock(struct qemu_syscall *call);
void qemu_ddraw_surface2_PageUnlock(struct qemu_syscall *call);
void qemu_ddraw_surface2_ReleaseDC(struct qemu_syscall *call);
void qemu_ddraw_surface2_Restore(struct qemu_syscall *call);
void qemu_ddraw_surface2_SetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface2_SetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface2_SetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface2_SetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface2_Unlock(struct qemu_syscall *call);
void qemu_ddraw_surface2_UpdateOverlay(struct qemu_syscall *call);
void qemu_ddraw_surface2_UpdateOverlayDisplay(struct qemu_syscall *call);
void qemu_ddraw_surface2_UpdateOverlayZOrder(struct qemu_syscall *call);
void qemu_ddraw_surface3_AddAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface3_AddOverlayDirtyRect(struct qemu_syscall *call);
void qemu_ddraw_surface3_Blt(struct qemu_syscall *call);
void qemu_ddraw_surface3_BltBatch(struct qemu_syscall *call);
void qemu_ddraw_surface3_BltFast(struct qemu_syscall *call);
void qemu_ddraw_surface3_DeleteAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface3_EnumAttachedSurfaces(struct qemu_syscall *call);
void qemu_ddraw_surface3_EnumOverlayZOrders(struct qemu_syscall *call);
void qemu_ddraw_surface3_Flip(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetBltStatus(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetCaps(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetDC(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetDDInterface(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetFlipStatus(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetPixelFormat(struct qemu_syscall *call);
void qemu_ddraw_surface3_GetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface3_Initialize(struct qemu_syscall *call);
void qemu_ddraw_surface3_IsLost(struct qemu_syscall *call);
void qemu_ddraw_surface3_PageLock(struct qemu_syscall *call);
void qemu_ddraw_surface3_PageUnlock(struct qemu_syscall *call);
void qemu_ddraw_surface3_ReleaseDC(struct qemu_syscall *call);
void qemu_ddraw_surface3_Restore(struct qemu_syscall *call);
void qemu_ddraw_surface3_SetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface3_SetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface3_SetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface3_SetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface3_SetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface3_Unlock(struct qemu_syscall *call);
void qemu_ddraw_surface3_UpdateOverlay(struct qemu_syscall *call);
void qemu_ddraw_surface3_UpdateOverlayDisplay(struct qemu_syscall *call);
void qemu_ddraw_surface3_UpdateOverlayZOrder(struct qemu_syscall *call);
void qemu_ddraw_surface4_AddAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface4_AddOverlayDirtyRect(struct qemu_syscall *call);
void qemu_ddraw_surface4_Blt(struct qemu_syscall *call);
void qemu_ddraw_surface4_BltBatch(struct qemu_syscall *call);
void qemu_ddraw_surface4_BltFast(struct qemu_syscall *call);
void qemu_ddraw_surface4_ChangeUniquenessValue(struct qemu_syscall *call);
void qemu_ddraw_surface4_DeleteAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface4_EnumAttachedSurfaces(struct qemu_syscall *call);
void qemu_ddraw_surface4_EnumOverlayZOrders(struct qemu_syscall *call);
void qemu_ddraw_surface4_Flip(struct qemu_syscall *call);
void qemu_ddraw_surface4_FreePrivateData(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetBltStatus(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetCaps(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetDC(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetDDInterface(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetFlipStatus(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetPixelFormat(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetPrivateData(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface4_GetUniquenessValue(struct qemu_syscall *call);
void qemu_ddraw_surface4_Initialize(struct qemu_syscall *call);
void qemu_ddraw_surface4_IsLost(struct qemu_syscall *call);
void qemu_ddraw_surface4_PageLock(struct qemu_syscall *call);
void qemu_ddraw_surface4_PageUnlock(struct qemu_syscall *call);
void qemu_ddraw_surface4_ReleaseDC(struct qemu_syscall *call);
void qemu_ddraw_surface4_Restore(struct qemu_syscall *call);
void qemu_ddraw_surface4_SetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface4_SetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface4_SetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface4_SetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface4_SetPrivateData(struct qemu_syscall *call);
void qemu_ddraw_surface4_SetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface4_Unlock(struct qemu_syscall *call);
void qemu_ddraw_surface4_UpdateOverlay(struct qemu_syscall *call);
void qemu_ddraw_surface4_UpdateOverlayDisplay(struct qemu_syscall *call);
void qemu_ddraw_surface4_UpdateOverlayZOrder(struct qemu_syscall *call);
void qemu_ddraw_surface7_AddAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface7_AddOverlayDirtyRect(struct qemu_syscall *call);
void qemu_ddraw_surface7_Blt(struct qemu_syscall *call);
void qemu_ddraw_surface7_BltBatch(struct qemu_syscall *call);
void qemu_ddraw_surface7_BltFast(struct qemu_syscall *call);
void qemu_ddraw_surface7_ChangeUniquenessValue(struct qemu_syscall *call);
void qemu_ddraw_surface7_DeleteAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface7_EnumAttachedSurfaces(struct qemu_syscall *call);
void qemu_ddraw_surface7_EnumOverlayZOrders(struct qemu_syscall *call);
void qemu_ddraw_surface7_Flip(struct qemu_syscall *call);
void qemu_ddraw_surface7_FreePrivateData(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetAttachedSurface(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetBltStatus(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetCaps(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetDC(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetDDInterface(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetFlipStatus(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetLOD(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetPixelFormat(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetPriority(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetPrivateData(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface7_GetUniquenessValue(struct qemu_syscall *call);
void qemu_ddraw_surface7_Initialize(struct qemu_syscall *call);
void qemu_ddraw_surface7_IsLost(struct qemu_syscall *call);
void qemu_ddraw_surface7_PageLock(struct qemu_syscall *call);
void qemu_ddraw_surface7_PageUnlock(struct qemu_syscall *call);
void qemu_ddraw_surface7_ReleaseDC(struct qemu_syscall *call);
void qemu_ddraw_surface7_Restore(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetClipper(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetColorKey(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetLOD(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetOverlayPosition(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetPalette(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetPriority(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetPrivateData(struct qemu_syscall *call);
void qemu_ddraw_surface7_SetSurfaceDesc(struct qemu_syscall *call);
void qemu_ddraw_surface7_Unlock(struct qemu_syscall *call);
void qemu_ddraw_surface7_UpdateOverlay(struct qemu_syscall *call);
void qemu_ddraw_surface7_UpdateOverlayDisplay(struct qemu_syscall *call);
void qemu_ddraw_surface7_UpdateOverlayZOrder(struct qemu_syscall *call);
void qemu_ddraw_surface_Lock(struct qemu_syscall *call);
void qemu_ddraw_surface_SetClipper(struct qemu_syscall *call);

extern uint64_t ddraw_surface_destroy_cb;

const struct IUnknownVtbl surface_priv_vtbl;
const GUID surface_priv_uuid;

static inline struct qemu_surface *surface_impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, private_data);
}

extern const struct qemu_ops *qemu_ops;

#endif

#endif
