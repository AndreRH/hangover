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

#ifndef QEMU_DINPUT_H
#define QEMU_DINPUT_H

enum dinput_calls
{
    CALL_INIT_DLL = 0,
};

struct qemu_dinput
{
    /* Guest fields */
    IDirectInput7A              IDirectInput7A_iface;
    IDirectInput7W              IDirectInput7W_iface;
    IDirectInput8A              IDirectInput8A_iface;
    IDirectInput8W              IDirectInput8W_iface;
    /*IDirectInputJoyConfig8      IDirectInputJoyConfig8_iface;*/

    LONG                        ref;

    /* Host fields */
    IDirectInput7A              *host_7a;
    IDirectInput7W              *host_7w;
    IDirectInput8A              *host_8a;
    IDirectInput8W              *host_8w;
    /*IDirectInputJoyConfig8      *host_joy_config;*/
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
