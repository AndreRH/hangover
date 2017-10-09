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

#ifdef QEMU_DLL_GUEST

#else

#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_usp10.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_usp10);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ScriptApplyDigitSubstitution,
    qemu_ScriptApplyLogicalWidth,
    qemu_ScriptBreak,
    qemu_ScriptCacheGetHeight,
    qemu_ScriptCPtoX,
    qemu_ScriptFreeCache,
    qemu_ScriptGetCMap,
    qemu_ScriptGetFontFeatureTags,
    qemu_ScriptGetFontLanguageTags,
    qemu_ScriptGetFontProperties,
    qemu_ScriptGetFontScriptTags,
    qemu_ScriptGetGlyphABCWidth,
    qemu_ScriptGetLogicalWidths,
    qemu_ScriptGetProperties,
    qemu_ScriptIsComplex,
    qemu_ScriptItemize,
    qemu_ScriptItemizeOpenType,
    qemu_ScriptJustify,
    qemu_ScriptLayout,
    qemu_ScriptPlace,
    qemu_ScriptPlaceOpenType,
    qemu_ScriptRecordDigitSubstitution,
    qemu_ScriptShape,
    qemu_ScriptShapeOpenType,
    qemu_ScriptString_pcOutChars,
    qemu_ScriptString_pLogAttr,
    qemu_ScriptString_pSize,
    qemu_ScriptStringAnalyse,
    qemu_ScriptStringCPtoX,
    qemu_ScriptStringFree,
    qemu_ScriptStringGetLogicalWidths,
    qemu_ScriptStringGetOrder,
    qemu_ScriptStringOut,
    qemu_ScriptStringValidate,
    qemu_ScriptStringXtoCP,
    qemu_ScriptTextOut,
    qemu_ScriptXtoCP,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side usp10 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
