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
#include "imm32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_imm32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ImmAssociateContext,
    qemu_ImmAssociateContextEx,
    qemu_ImmConfigureIMEA,
    qemu_ImmConfigureIMEW,
    qemu_ImmCreateContext,
    qemu_ImmCreateIMCC,
    qemu_ImmCreateSoftKeyboard,
    qemu_ImmDestroyContext,
    qemu_ImmDestroyIMCC,
    qemu_ImmDestroySoftKeyboard,
    qemu_ImmDisableIME,
    qemu_ImmDisableTextFrameService,
    qemu_ImmEnumInputContext,
    qemu_ImmEnumRegisterWordA,
    qemu_ImmEnumRegisterWordW,
    qemu_ImmEscapeA,
    qemu_ImmEscapeW,
    qemu_ImmGenerateMessage,
    qemu_ImmGetCandidateListA,
    qemu_ImmGetCandidateListCountA,
    qemu_ImmGetCandidateListCountW,
    qemu_ImmGetCandidateListW,
    qemu_ImmGetCandidateWindow,
    qemu_ImmGetCompositionFontA,
    qemu_ImmGetCompositionFontW,
    qemu_ImmGetCompositionStringA,
    qemu_ImmGetCompositionStringW,
    qemu_ImmGetCompositionWindow,
    qemu_ImmGetContext,
    qemu_ImmGetConversionListA,
    qemu_ImmGetConversionListW,
    qemu_ImmGetConversionStatus,
    qemu_ImmGetDefaultIMEWnd,
    qemu_ImmGetDescriptionA,
    qemu_ImmGetDescriptionW,
    qemu_ImmGetGuideLineA,
    qemu_ImmGetGuideLineW,
    qemu_ImmGetHotKey,
    qemu_ImmGetIMCCLockCount,
    qemu_ImmGetIMCCSize,
    qemu_ImmGetIMCLockCount,
    qemu_ImmGetIMEFileNameA,
    qemu_ImmGetIMEFileNameW,
    qemu_ImmGetImeMenuItemsA,
    qemu_ImmGetImeMenuItemsW,
    qemu_ImmGetOpenStatus,
    qemu_ImmGetProperty,
    qemu_ImmGetRegisterWordStyleA,
    qemu_ImmGetRegisterWordStyleW,
    qemu_ImmGetStatusWindowPos,
    qemu_ImmGetVirtualKey,
    qemu_ImmInstallIMEA,
    qemu_ImmInstallIMEW,
    qemu_ImmIsIME,
    qemu_ImmIsUIMessageA,
    qemu_ImmIsUIMessageW,
    qemu_ImmLockIMC,
    qemu_ImmLockIMCC,
    qemu_ImmNotifyIME,
    qemu_ImmProcessKey,
    qemu_ImmRegisterWordA,
    qemu_ImmRegisterWordW,
    qemu_ImmReleaseContext,
    qemu_ImmRequestMessageA,
    qemu_ImmRequestMessageW,
    qemu_ImmReSizeIMCC,
    qemu_ImmSetCandidateWindow,
    qemu_ImmSetCompositionFontA,
    qemu_ImmSetCompositionFontW,
    qemu_ImmSetCompositionStringA,
    qemu_ImmSetCompositionStringW,
    qemu_ImmSetCompositionWindow,
    qemu_ImmSetConversionStatus,
    qemu_ImmSetOpenStatus,
    qemu_ImmSetStatusWindowPos,
    qemu_ImmShowSoftKeyboard,
    qemu_ImmSimulateHotKey,
    qemu_ImmTranslateMessage,
    qemu_ImmUnlockIMC,
    qemu_ImmUnlockIMCC,
    qemu_ImmUnregisterWordA,
    qemu_ImmUnregisterWordW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side imm32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
