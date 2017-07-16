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

/* The basic idea behind declaring these structures outside dlls/d3d9/ is that
 * other DLLs like d3dx9 will need them for functions that take an IDirect3D9*
 * interface somewhere. They'll need to wrap the d3d9 stuff in addition to
 * their own interfaces. */

#ifndef QEMU_D3D9_WRAPPER_H
#define QEMU_D3D9_WRAPPER_H

/* This structure is accessed by both guest and host, including the guest
 * application code. This may need extra care for 32<->64 mapping because
 * we can't just make everything an uint64_t. */
struct qemu_d3d9_impl
{
    IDirect3D9Ex IDirect3D9Ex_iface;
    IDirect3D9Ex *host;
};

struct qemu_d3d9_device_impl
{
    IDirect3DDevice9Ex IDirect3DDevice9Ex_iface;
    IDirect3DDevice9Ex *host;
};

#endif
