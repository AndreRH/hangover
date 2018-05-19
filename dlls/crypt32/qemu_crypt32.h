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

#ifndef QEMU_CRYPT32_H
#define QEMU_CRYPT32_H

enum crypt32_calls
{
    CALL_CRYPTMEMALLOC = 0,
    CALL_CRYPTMEMFREE,
    CALL_CRYPTMEMREALLOC,
    CALL_CRYPTPROTECTMEMORY,
    CALL_CRYPTUNPROTECTMEMORY,
    CALL_I_CRYPTALLOCTLS,
    CALL_I_CRYPTCREATELRUCACHE,
    CALL_I_CRYPTCREATELRUENTRY,
    CALL_I_CRYPTDETACHTLS,
    CALL_I_CRYPTFINDLRUENTRY,
    CALL_I_CRYPTFINDLRUENTRYDATA,
    CALL_I_CRYPTFLUSHLRUCACHE,
    CALL_I_CRYPTFREELRUCACHE,
    CALL_I_CRYPTFREETLS,
    CALL_I_CRYPTGETASN1DECODER,
    CALL_I_CRYPTGETASN1ENCODER,
    CALL_I_CRYPTGETDEFAULTCRYPTPROV,
    CALL_I_CRYPTGETOSSGLOBAL,
    CALL_I_CRYPTGETTLS,
    CALL_I_CRYPTINSTALLASN1MODULE,
    CALL_I_CRYPTINSTALLOSSGLOBAL,
    CALL_I_CRYPTREADTRUSTEDPUBLISHERDWORDVALUEFROMREGISTRY,
    CALL_I_CRYPTSETTLS,
    CALL_I_CRYPTUNINSTALLASN1MODULE,
    CALL_INIT_DLL,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
