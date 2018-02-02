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
    CALL_D3D1_CREATELIGHT = 0,
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
    CALL_DDRAW1_COMPACT,
    CALL_DDRAW1_CREATECLIPPER,
    CALL_DDRAW1_CREATEPALETTE,
    CALL_DDRAW1_CREATESURFACE,
    CALL_DDRAW1_DUPLICATESURFACE,
    CALL_DDRAW1_ENUMDISPLAYMODES,
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
    CALL_DDRAW1_RELEASE,
    CALL_DDRAW1_RESTOREDISPLAYMODE,
    CALL_DDRAW1_SETCOOPERATIVELEVEL,
    CALL_DDRAW1_SETDISPLAYMODE,
    CALL_DDRAW1_WAITFORVERTICALBLANK,
    CALL_DDRAW2_COMPACT,
    CALL_DDRAW2_CREATECLIPPER,
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
    CALL_DDRAW4_CREATECLIPPER,
    CALL_DDRAW4_CREATEPALETTE,
    CALL_DDRAW4_CREATESURFACE,
    CALL_DDRAW4_DUPLICATESURFACE,
    CALL_DDRAW4_ENUMDISPLAYMODES,
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
    CALL_DDRAW7_CREATECLIPPER,
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
    CALL_DIRECTDRAWCREATE,
    CALL_DIRECTDRAWCREATECLIPPER,
    CALL_DIRECTDRAWCREATEEX,
    CALL_DIRECTDRAWENUMERATEA,
    CALL_DIRECTDRAWENUMERATEEXA,
    CALL_DIRECTDRAWENUMERATEEXW,
    CALL_DIRECTDRAWENUMERATEW,
    CALL_GETSURFACEFROMDC,
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

#ifdef QEMU_DLL_GUEST

HRESULT ddraw_clipper_guest_init(struct qemu_clipper *clipper);
struct qemu_clipper *unsafe_impl_from_IDirectDrawClipper(IDirectDrawClipper *iface);

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
void qemu_d3d3_EnumZBufferFormats(struct qemu_syscall *call);
void qemu_d3d3_EvictManagedTextures(struct qemu_syscall *call);
void qemu_d3d3_FindDevice(struct qemu_syscall *call);
void qemu_d3d7_CreateDevice(struct qemu_syscall *call);
void qemu_d3d7_CreateVertexBuffer(struct qemu_syscall *call);
void qemu_d3d7_EnumDevices(struct qemu_syscall *call);
void qemu_d3d7_EnumZBufferFormats(struct qemu_syscall *call);
void qemu_d3d7_EvictManagedTextures(struct qemu_syscall *call);
void qemu_ddraw1_Compact(struct qemu_syscall *call);
void qemu_ddraw1_CreateClipper(struct qemu_syscall *call);
void qemu_ddraw1_CreatePalette(struct qemu_syscall *call);
void qemu_ddraw1_CreateSurface(struct qemu_syscall *call);
void qemu_ddraw1_DuplicateSurface(struct qemu_syscall *call);
void qemu_ddraw1_EnumDisplayModes(struct qemu_syscall *call);
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
void qemu_ddraw1_RestoreDisplayMode(struct qemu_syscall *call);
void qemu_ddraw1_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_ddraw1_SetDisplayMode(struct qemu_syscall *call);
void qemu_ddraw1_WaitForVerticalBlank(struct qemu_syscall *call);
void qemu_ddraw2_Compact(struct qemu_syscall *call);
void qemu_ddraw2_CreateClipper(struct qemu_syscall *call);
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
void qemu_ddraw4_CreateClipper(struct qemu_syscall *call);
void qemu_ddraw4_CreatePalette(struct qemu_syscall *call);
void qemu_ddraw4_CreateSurface(struct qemu_syscall *call);
void qemu_ddraw4_DuplicateSurface(struct qemu_syscall *call);
void qemu_ddraw4_EnumDisplayModes(struct qemu_syscall *call);
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
void qemu_ddraw7_CreateClipper(struct qemu_syscall *call);
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
void qemu_ddraw_Release(struct qemu_syscall *call);
void qemu_ddraw_clipper_GetClipList(struct qemu_syscall *call);
void qemu_ddraw_clipper_GetHWnd(struct qemu_syscall *call);
void qemu_ddraw_clipper_Initialize(struct qemu_syscall *call);
void qemu_ddraw_clipper_IsClipListChanged(struct qemu_syscall *call);
void qemu_ddraw_clipper_Release(struct qemu_syscall *call);
void qemu_ddraw_clipper_SetClipList(struct qemu_syscall *call);
void qemu_ddraw_clipper_SetHWnd(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

#endif

#endif
