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
    CALL_D3D11COREREGISTERLAYERS = 0,
    CALL_D3D11CREATEDEVICE,
    CALL_D3D11CREATEDEVICEANDSWAPCHAIN,
    CALL_INIT_DLL,
};

#ifdef QEMU_DLL_GUEST

extern HRESULT (* WINAPI p_DXGID3D10CreateDevice)(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device);

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
