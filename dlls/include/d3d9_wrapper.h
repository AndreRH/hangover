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

#endif
