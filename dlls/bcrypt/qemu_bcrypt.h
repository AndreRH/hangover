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

#ifndef QEMU_BCRYPT_H
#define QEMU_BCRYPT_H

enum bcrypt_calls
{
    CALL_BCRYPTADDCONTEXTFUNCTION = 0,
    CALL_BCRYPTADDCONTEXTFUNCTIONPROVIDER,
    CALL_BCRYPTCLOSEALGORITHMPROVIDER,
    CALL_BCRYPTCREATEHASH,
    CALL_BCRYPTDECRYPT,
    CALL_BCRYPTDERIVEKEY,
    CALL_BCRYPTDERIVEKEYCAPI,
    CALL_BCRYPTDERIVEKEYPBKDF2,
    CALL_BCRYPTDESTROYHASH,
    CALL_BCRYPTDESTROYKEY,
    CALL_BCRYPTDESTROYSECRET,
    CALL_BCRYPTDUPLICATEHASH,
    CALL_BCRYPTDUPLICATEKEY,
    CALL_BCRYPTENCRYPT,
    CALL_BCRYPTENUMALGORITHMS,
    CALL_BCRYPTENUMCONTEXTFUNCTIONS,
    CALL_BCRYPTEXPORTKEY,
    CALL_BCRYPTFINALIZEKEYPAIR,
    CALL_BCRYPTFINISHHASH,
    CALL_BCRYPTFREEBUFFER,
    CALL_BCRYPTGENERATEKEYPAIR,
    CALL_BCRYPTGENERATESYMMETRICKEY,
    CALL_BCRYPTGENRANDOM,
    CALL_BCRYPTGETFIPSALGORITHMMODE,
    CALL_BCRYPTGETPROPERTY,
    CALL_BCRYPTHASH,
    CALL_BCRYPTHASHDATA,
    CALL_BCRYPTIMPORTKEY,
    CALL_BCRYPTIMPORTKEYPAIR,
    CALL_BCRYPTOPENALGORITHMPROVIDER,
    CALL_BCRYPTREGISTERPROVIDER,
    CALL_BCRYPTREMOVECONTEXTFUNCTION,
    CALL_BCRYPTREMOVECONTEXTFUNCTIONPROVIDER,
    CALL_BCRYPTSECRETAGREEMENT,
    CALL_BCRYPTSETPROPERTY,
    CALL_BCRYPTSIGNHASH,
    CALL_BCRYPTUNREGISTERPROVIDER,
    CALL_BCRYPTVERIFYSIGNATURE,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
