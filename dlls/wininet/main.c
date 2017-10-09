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
#include "qemu_wininet.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wininet);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CommitUrlCacheEntryA,
    qemu_CommitUrlCacheEntryW,
    qemu_CreateMD5SSOHash,
    qemu_CreateUrlCacheContainerA,
    qemu_CreateUrlCacheContainerW,
    qemu_CreateUrlCacheEntryA,
    qemu_CreateUrlCacheEntryW,
    qemu_CreateUrlCacheGroup,
    qemu_DeleteIE3Cache,
    qemu_DeleteUrlCacheContainerA,
    qemu_DeleteUrlCacheContainerW,
    qemu_DeleteUrlCacheEntryA,
    qemu_DeleteUrlCacheEntryW,
    qemu_DeleteUrlCacheGroup,
    qemu_DeleteWpadCacheForNetworks,
    qemu_DetectAutoProxyUrl,
    qemu_FindCloseUrlCache,
    qemu_FindFirstUrlCacheContainerA,
    qemu_FindFirstUrlCacheContainerW,
    qemu_FindFirstUrlCacheEntryA,
    qemu_FindFirstUrlCacheEntryExA,
    qemu_FindFirstUrlCacheEntryExW,
    qemu_FindFirstUrlCacheEntryW,
    qemu_FindFirstUrlCacheGroup,
    qemu_FindNextUrlCacheContainerA,
    qemu_FindNextUrlCacheContainerW,
    qemu_FindNextUrlCacheEntryA,
    qemu_FindNextUrlCacheEntryExA,
    qemu_FindNextUrlCacheEntryExW,
    qemu_FindNextUrlCacheEntryW,
    qemu_FindNextUrlCacheGroup,
    qemu_FreeUrlCacheSpaceA,
    qemu_FreeUrlCacheSpaceW,
    qemu_FtpCommandA,
    qemu_FtpCommandW,
    qemu_FtpCreateDirectoryA,
    qemu_FtpCreateDirectoryW,
    qemu_FtpDeleteFileA,
    qemu_FtpDeleteFileW,
    qemu_FtpFindFirstFileA,
    qemu_FtpFindFirstFileW,
    qemu_FtpGetCurrentDirectoryA,
    qemu_FtpGetCurrentDirectoryW,
    qemu_FtpGetFileA,
    qemu_FtpGetFileSize,
    qemu_FtpGetFileW,
    qemu_FtpOpenFileA,
    qemu_FtpOpenFileW,
    qemu_FtpPutFileA,
    qemu_FtpPutFileW,
    qemu_FtpRemoveDirectoryA,
    qemu_FtpRemoveDirectoryW,
    qemu_FtpRenameFileA,
    qemu_FtpRenameFileW,
    qemu_FtpSetCurrentDirectoryA,
    qemu_FtpSetCurrentDirectoryW,
    qemu_GetDiskInfoA,
    qemu_GetUrlCacheConfigInfoA,
    qemu_GetUrlCacheConfigInfoW,
    qemu_GetUrlCacheEntryInfoA,
    qemu_GetUrlCacheEntryInfoExA,
    qemu_GetUrlCacheEntryInfoExW,
    qemu_GetUrlCacheEntryInfoW,
    qemu_GetUrlCacheGroupAttributeA,
    qemu_GetUrlCacheGroupAttributeW,
    qemu_GopherCreateLocatorA,
    qemu_GopherCreateLocatorW,
    qemu_GopherFindFirstFileA,
    qemu_GopherFindFirstFileW,
    qemu_GopherGetAttributeA,
    qemu_GopherGetAttributeW,
    qemu_GopherGetLocatorTypeA,
    qemu_GopherGetLocatorTypeW,
    qemu_GopherOpenFileA,
    qemu_GopherOpenFileW,
    qemu_HttpAddRequestHeadersA,
    qemu_HttpAddRequestHeadersW,
    qemu_HttpEndRequestA,
    qemu_HttpEndRequestW,
    qemu_HttpOpenRequestA,
    qemu_HttpOpenRequestW,
    qemu_HttpQueryInfoA,
    qemu_HttpQueryInfoW,
    qemu_HttpSendRequestA,
    qemu_HttpSendRequestExA,
    qemu_HttpSendRequestExW,
    qemu_HttpSendRequestW,
    qemu_IncrementUrlCacheHeaderData,
    qemu_InternetAttemptConnect,
    qemu_InternetAutodial,
    qemu_InternetAutodialHangup,
    qemu_InternetCanonicalizeUrlA,
    qemu_InternetCanonicalizeUrlW,
    qemu_InternetCheckConnectionA,
    qemu_InternetCheckConnectionW,
    qemu_InternetClearAllPerSiteCookieDecisions,
    qemu_InternetCloseHandle,
    qemu_InternetCombineUrlA,
    qemu_InternetCombineUrlW,
    qemu_InternetConfirmZoneCrossingA,
    qemu_InternetConfirmZoneCrossingW,
    qemu_InternetConnectA,
    qemu_InternetConnectW,
    qemu_InternetCrackUrlA,
    qemu_InternetCrackUrlW,
    qemu_InternetCreateUrlA,
    qemu_InternetCreateUrlW,
    qemu_InternetDialA,
    qemu_InternetDialW,
    qemu_InternetEnumPerSiteCookieDecisionA,
    qemu_InternetEnumPerSiteCookieDecisionW,
    qemu_InternetErrorDlg,
    qemu_InternetFindNextFileA,
    qemu_InternetFindNextFileW,
    qemu_InternetGetConnectedState,
    qemu_InternetGetConnectedStateExA,
    qemu_InternetGetConnectedStateExW,
    qemu_InternetGetCookieA,
    qemu_InternetGetCookieExA,
    qemu_InternetGetCookieExW,
    qemu_InternetGetCookieW,
    qemu_InternetGetLastResponseInfoA,
    qemu_InternetGetLastResponseInfoW,
    qemu_InternetGetPerSiteCookieDecisionA,
    qemu_InternetGetPerSiteCookieDecisionW,
    qemu_InternetGetSecurityInfoByURLA,
    qemu_InternetGetSecurityInfoByURLW,
    qemu_InternetGoOnlineA,
    qemu_InternetGoOnlineW,
    qemu_InternetHangUp,
    qemu_InternetInitializeAutoProxyDll,
    qemu_InternetLockRequestFile,
    qemu_InternetOpenA,
    qemu_InternetOpenUrlA,
    qemu_InternetOpenUrlW,
    qemu_InternetOpenW,
    qemu_InternetQueryDataAvailable,
    qemu_InternetQueryFortezzaStatus,
    qemu_InternetQueryOptionA,
    qemu_InternetQueryOptionW,
    qemu_InternetReadFile,
    qemu_InternetReadFileExA,
    qemu_InternetReadFileExW,
    qemu_InternetSetCookieA,
    qemu_InternetSetCookieExA,
    qemu_InternetSetCookieExW,
    qemu_InternetSetCookieW,
    qemu_InternetSetFilePointer,
    qemu_InternetSetOptionA,
    qemu_InternetSetOptionExA,
    qemu_InternetSetOptionExW,
    qemu_InternetSetOptionW,
    qemu_InternetSetPerSiteCookieDecisionA,
    qemu_InternetSetPerSiteCookieDecisionW,
    qemu_InternetSetStatusCallbackA,
    qemu_InternetSetStatusCallbackW,
    qemu_InternetShowSecurityInfoByURLA,
    qemu_InternetShowSecurityInfoByURLW,
    qemu_InternetTimeFromSystemTimeA,
    qemu_InternetTimeFromSystemTimeW,
    qemu_InternetTimeToSystemTimeA,
    qemu_InternetTimeToSystemTimeW,
    qemu_InternetUnlockRequestFile,
    qemu_InternetWriteFile,
    qemu_IsDomainLegalCookieDomainW,
    qemu_IsHostInProxyBypassList,
    qemu_IsUrlCacheEntryExpiredA,
    qemu_IsUrlCacheEntryExpiredW,
    qemu_LoadUrlCacheContent,
    qemu_PrivacyGetZonePreferenceW,
    qemu_PrivacySetZonePreferenceW,
    qemu_ReadUrlCacheEntryStream,
    qemu_RegisterUrlCacheNotification,
    qemu_ResumeSuspendedDownload,
    qemu_RetrieveUrlCacheEntryFileA,
    qemu_RetrieveUrlCacheEntryFileW,
    qemu_RetrieveUrlCacheEntryStreamA,
    qemu_RetrieveUrlCacheEntryStreamW,
    qemu_RunOnceUrlCache,
    qemu_SetUrlCacheConfigInfoA,
    qemu_SetUrlCacheConfigInfoW,
    qemu_SetUrlCacheEntryGroupA,
    qemu_SetUrlCacheEntryGroupW,
    qemu_SetUrlCacheEntryInfoA,
    qemu_SetUrlCacheEntryInfoW,
    qemu_SetUrlCacheGroupAttributeA,
    qemu_SetUrlCacheGroupAttributeW,
    qemu_ShowClientAuthCerts,
    qemu_ShowX509EncodedCertificate,
    qemu_UnlockUrlCacheEntryFileA,
    qemu_UnlockUrlCacheEntryFileW,
    qemu_UnlockUrlCacheEntryStream,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side wininet wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
