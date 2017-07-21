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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "oleaut32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_oleaut32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_DosDateTimeToVariantTime,
    qemu_GetActiveObject,
    qemu_GetAltMonthNames,
    qemu_OaBuildVersion,
    qemu_OleIconToCursor,
    qemu_OleTranslateColor,
    qemu_RegisterActiveObject,
    qemu_RevokeActiveObject,
    qemu_SetOaNoCache,
    qemu_SysAllocString,
    qemu_SysAllocStringByteLen,
    qemu_SysAllocStringLen,
    qemu_SysFreeString,
    qemu_SysReAllocString,
    qemu_SysReAllocStringLen,
    qemu_SysStringByteLen,
    qemu_SysStringLen,
    qemu_SystemTimeToVariantTime,
    qemu_VarAbs,
    qemu_VarAdd,
    qemu_VarAnd,
    qemu_VarCat,
    qemu_VarCmp,
    qemu_VarDateFromUdate,
    qemu_VarDateFromUdateEx,
    qemu_VarDiv,
    qemu_VarEqv,
    qemu_VarFix,
    qemu_VariantChangeType,
    qemu_VariantChangeTypeEx,
    qemu_VariantClear,
    qemu_VariantCopy,
    qemu_VariantCopyInd,
    qemu_VariantInit,
    qemu_VariantTimeToDosDateTime,
    qemu_VariantTimeToSystemTime,
    qemu_VarIdiv,
    qemu_VarImp,
    qemu_VarInt,
    qemu_VarMod,
    qemu_VarMul,
    qemu_VarNeg,
    qemu_VarNot,
    qemu_VarNumFromParseNum,
    qemu_VarOr,
    qemu_VarParseNumFromStr,
    qemu_VarPow,
    qemu_VarRound,
    qemu_VarSub,
    qemu_VarUdateFromDate,
    qemu_VarXor,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side oleaut32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
