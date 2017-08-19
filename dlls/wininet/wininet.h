#ifndef QEMU_WININET_H
#define QEMU_WININET_H

enum wininet_calls
{
    CALL_COMMITURLCACHEENTRYA = 0,
    CALL_COMMITURLCACHEENTRYW,
    CALL_CREATEMD5SSOHASH,
    CALL_CREATEURLCACHECONTAINERA,
    CALL_CREATEURLCACHECONTAINERW,
    CALL_CREATEURLCACHEENTRYA,
    CALL_CREATEURLCACHEENTRYW,
    CALL_CREATEURLCACHEGROUP,
    CALL_DELETEIE3CACHE,
    CALL_DELETEURLCACHECONTAINERA,
    CALL_DELETEURLCACHECONTAINERW,
    CALL_DELETEURLCACHEENTRYA,
    CALL_DELETEURLCACHEENTRYW,
    CALL_DELETEURLCACHEGROUP,
    CALL_DELETEWPADCACHEFORNETWORKS,
    CALL_DETECTAUTOPROXYURL,
    CALL_FINDCLOSEURLCACHE,
    CALL_FINDFIRSTURLCACHECONTAINERA,
    CALL_FINDFIRSTURLCACHECONTAINERW,
    CALL_FINDFIRSTURLCACHEENTRYA,
    CALL_FINDFIRSTURLCACHEENTRYEXA,
    CALL_FINDFIRSTURLCACHEENTRYEXW,
    CALL_FINDFIRSTURLCACHEENTRYW,
    CALL_FINDFIRSTURLCACHEGROUP,
    CALL_FINDNEXTURLCACHECONTAINERA,
    CALL_FINDNEXTURLCACHECONTAINERW,
    CALL_FINDNEXTURLCACHEENTRYA,
    CALL_FINDNEXTURLCACHEENTRYEXA,
    CALL_FINDNEXTURLCACHEENTRYEXW,
    CALL_FINDNEXTURLCACHEENTRYW,
    CALL_FINDNEXTURLCACHEGROUP,
    CALL_FREEURLCACHESPACEA,
    CALL_FREEURLCACHESPACEW,
    CALL_FTPCOMMANDA,
    CALL_FTPCOMMANDW,
    CALL_FTPCREATEDIRECTORYA,
    CALL_FTPCREATEDIRECTORYW,
    CALL_FTPDELETEFILEA,
    CALL_FTPDELETEFILEW,
    CALL_FTPFINDFIRSTFILEA,
    CALL_FTPFINDFIRSTFILEW,
    CALL_FTPGETCURRENTDIRECTORYA,
    CALL_FTPGETCURRENTDIRECTORYW,
    CALL_FTPGETFILEA,
    CALL_FTPGETFILESIZE,
    CALL_FTPGETFILEW,
    CALL_FTPOPENFILEA,
    CALL_FTPOPENFILEW,
    CALL_FTPPUTFILEA,
    CALL_FTPPUTFILEW,
    CALL_FTPREMOVEDIRECTORYA,
    CALL_FTPREMOVEDIRECTORYW,
    CALL_FTPRENAMEFILEA,
    CALL_FTPRENAMEFILEW,
    CALL_FTPSETCURRENTDIRECTORYA,
    CALL_FTPSETCURRENTDIRECTORYW,
    CALL_GETDISKINFOA,
    CALL_GETURLCACHECONFIGINFOA,
    CALL_GETURLCACHECONFIGINFOW,
    CALL_GETURLCACHEENTRYINFOA,
    CALL_GETURLCACHEENTRYINFOEXA,
    CALL_GETURLCACHEENTRYINFOEXW,
    CALL_GETURLCACHEENTRYINFOW,
    CALL_GETURLCACHEGROUPATTRIBUTEA,
    CALL_GETURLCACHEGROUPATTRIBUTEW,
    CALL_GOPHERCREATELOCATORA,
    CALL_GOPHERCREATELOCATORW,
    CALL_GOPHERFINDFIRSTFILEA,
    CALL_GOPHERFINDFIRSTFILEW,
    CALL_GOPHERGETATTRIBUTEA,
    CALL_GOPHERGETATTRIBUTEW,
    CALL_GOPHERGETLOCATORTYPEA,
    CALL_GOPHERGETLOCATORTYPEW,
    CALL_GOPHEROPENFILEA,
    CALL_GOPHEROPENFILEW,
    CALL_HTTPADDREQUESTHEADERSA,
    CALL_HTTPADDREQUESTHEADERSW,
    CALL_HTTPENDREQUESTA,
    CALL_HTTPENDREQUESTW,
    CALL_HTTPOPENREQUESTA,
    CALL_HTTPOPENREQUESTW,
    CALL_HTTPQUERYINFOA,
    CALL_HTTPQUERYINFOW,
    CALL_HTTPSENDREQUESTA,
    CALL_HTTPSENDREQUESTEXA,
    CALL_HTTPSENDREQUESTEXW,
    CALL_HTTPSENDREQUESTW,
    CALL_INCREMENTURLCACHEHEADERDATA,
    CALL_INTERNETATTEMPTCONNECT,
    CALL_INTERNETAUTODIAL,
    CALL_INTERNETAUTODIALHANGUP,
    CALL_INTERNETCANONICALIZEURLA,
    CALL_INTERNETCANONICALIZEURLW,
    CALL_INTERNETCHECKCONNECTIONA,
    CALL_INTERNETCHECKCONNECTIONW,
    CALL_INTERNETCLEARALLPERSITECOOKIEDECISIONS,
    CALL_INTERNETCLOSEHANDLE,
    CALL_INTERNETCOMBINEURLA,
    CALL_INTERNETCOMBINEURLW,
    CALL_INTERNETCONFIRMZONECROSSINGA,
    CALL_INTERNETCONFIRMZONECROSSINGW,
    CALL_INTERNETCONNECTA,
    CALL_INTERNETCONNECTW,
    CALL_INTERNETCRACKURLA,
    CALL_INTERNETCRACKURLW,
    CALL_INTERNETCREATEURLA,
    CALL_INTERNETCREATEURLW,
    CALL_INTERNETDIALA,
    CALL_INTERNETDIALW,
    CALL_INTERNETENUMPERSITECOOKIEDECISIONA,
    CALL_INTERNETENUMPERSITECOOKIEDECISIONW,
    CALL_INTERNETERRORDLG,
    CALL_INTERNETFINDNEXTFILEA,
    CALL_INTERNETFINDNEXTFILEW,
    CALL_INTERNETGETCONNECTEDSTATE,
    CALL_INTERNETGETCONNECTEDSTATEEXA,
    CALL_INTERNETGETCONNECTEDSTATEEXW,
    CALL_INTERNETGETCOOKIEA,
    CALL_INTERNETGETCOOKIEEXA,
    CALL_INTERNETGETCOOKIEEXW,
    CALL_INTERNETGETCOOKIEW,
    CALL_INTERNETGETLASTRESPONSEINFOA,
    CALL_INTERNETGETLASTRESPONSEINFOW,
    CALL_INTERNETGETPERSITECOOKIEDECISIONA,
    CALL_INTERNETGETPERSITECOOKIEDECISIONW,
    CALL_INTERNETGETSECURITYINFOBYURLA,
    CALL_INTERNETGETSECURITYINFOBYURLW,
    CALL_INTERNETGOONLINEA,
    CALL_INTERNETGOONLINEW,
    CALL_INTERNETHANGUP,
    CALL_INTERNETINITIALIZEAUTOPROXYDLL,
    CALL_INTERNETLOCKREQUESTFILE,
    CALL_INTERNETOPENA,
    CALL_INTERNETOPENURLA,
    CALL_INTERNETOPENURLW,
    CALL_INTERNETOPENW,
    CALL_INTERNETQUERYDATAAVAILABLE,
    CALL_INTERNETQUERYFORTEZZASTATUS,
    CALL_INTERNETQUERYOPTIONA,
    CALL_INTERNETQUERYOPTIONW,
    CALL_INTERNETREADFILE,
    CALL_INTERNETREADFILEEXA,
    CALL_INTERNETREADFILEEXW,
    CALL_INTERNETSETCOOKIEA,
    CALL_INTERNETSETCOOKIEEXA,
    CALL_INTERNETSETCOOKIEEXW,
    CALL_INTERNETSETCOOKIEW,
    CALL_INTERNETSETFILEPOINTER,
    CALL_INTERNETSETOPTIONA,
    CALL_INTERNETSETOPTIONEXA,
    CALL_INTERNETSETOPTIONEXW,
    CALL_INTERNETSETOPTIONW,
    CALL_INTERNETSETPERSITECOOKIEDECISIONA,
    CALL_INTERNETSETPERSITECOOKIEDECISIONW,
    CALL_INTERNETSETSTATUSCALLBACKA,
    CALL_INTERNETSETSTATUSCALLBACKW,
    CALL_INTERNETSHOWSECURITYINFOBYURLA,
    CALL_INTERNETSHOWSECURITYINFOBYURLW,
    CALL_INTERNETTIMEFROMSYSTEMTIMEA,
    CALL_INTERNETTIMEFROMSYSTEMTIMEW,
    CALL_INTERNETTIMETOSYSTEMTIMEA,
    CALL_INTERNETTIMETOSYSTEMTIMEW,
    CALL_INTERNETUNLOCKREQUESTFILE,
    CALL_INTERNETWRITEFILE,
    CALL_ISDOMAINLEGALCOOKIEDOMAINW,
    CALL_ISHOSTINPROXYBYPASSLIST,
    CALL_ISURLCACHEENTRYEXPIREDA,
    CALL_ISURLCACHEENTRYEXPIREDW,
    CALL_LOADURLCACHECONTENT,
    CALL_PRIVACYGETZONEPREFERENCEW,
    CALL_PRIVACYSETZONEPREFERENCEW,
    CALL_READURLCACHEENTRYSTREAM,
    CALL_REGISTERURLCACHENOTIFICATION,
    CALL_RESUMESUSPENDEDDOWNLOAD,
    CALL_RETRIEVEURLCACHEENTRYFILEA,
    CALL_RETRIEVEURLCACHEENTRYFILEW,
    CALL_RETRIEVEURLCACHEENTRYSTREAMA,
    CALL_RETRIEVEURLCACHEENTRYSTREAMW,
    CALL_RUNONCEURLCACHE,
    CALL_SETURLCACHECONFIGINFOA,
    CALL_SETURLCACHECONFIGINFOW,
    CALL_SETURLCACHEENTRYGROUPA,
    CALL_SETURLCACHEENTRYGROUPW,
    CALL_SETURLCACHEENTRYINFOA,
    CALL_SETURLCACHEENTRYINFOW,
    CALL_SETURLCACHEGROUPATTRIBUTEA,
    CALL_SETURLCACHEGROUPATTRIBUTEW,
    CALL_SHOWCLIENTAUTHCERTS,
    CALL_SHOWX509ENCODEDCERTIFICATE,
    CALL_UNLOCKURLCACHEENTRYFILEA,
    CALL_UNLOCKURLCACHEENTRYFILEW,
    CALL_UNLOCKURLCACHEENTRYSTREAM,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_CommitUrlCacheEntryA(struct qemu_syscall *call);
void qemu_CommitUrlCacheEntryW(struct qemu_syscall *call);
void qemu_CreateMD5SSOHash(struct qemu_syscall *call);
void qemu_CreateUrlCacheContainerA(struct qemu_syscall *call);
void qemu_CreateUrlCacheContainerW(struct qemu_syscall *call);
void qemu_CreateUrlCacheEntryA(struct qemu_syscall *call);
void qemu_CreateUrlCacheEntryW(struct qemu_syscall *call);
void qemu_CreateUrlCacheGroup(struct qemu_syscall *call);
void qemu_DeleteIE3Cache(struct qemu_syscall *call);
void qemu_DeleteUrlCacheContainerA(struct qemu_syscall *call);
void qemu_DeleteUrlCacheContainerW(struct qemu_syscall *call);
void qemu_DeleteUrlCacheEntryA(struct qemu_syscall *call);
void qemu_DeleteUrlCacheEntryW(struct qemu_syscall *call);
void qemu_DeleteUrlCacheGroup(struct qemu_syscall *call);
void qemu_DeleteWpadCacheForNetworks(struct qemu_syscall *call);
void qemu_DetectAutoProxyUrl(struct qemu_syscall *call);
void qemu_FindCloseUrlCache(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheContainerA(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheContainerW(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheEntryA(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheEntryExA(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheEntryExW(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheEntryW(struct qemu_syscall *call);
void qemu_FindFirstUrlCacheGroup(struct qemu_syscall *call);
void qemu_FindNextUrlCacheContainerA(struct qemu_syscall *call);
void qemu_FindNextUrlCacheContainerW(struct qemu_syscall *call);
void qemu_FindNextUrlCacheEntryA(struct qemu_syscall *call);
void qemu_FindNextUrlCacheEntryExA(struct qemu_syscall *call);
void qemu_FindNextUrlCacheEntryExW(struct qemu_syscall *call);
void qemu_FindNextUrlCacheEntryW(struct qemu_syscall *call);
void qemu_FindNextUrlCacheGroup(struct qemu_syscall *call);
void qemu_FreeUrlCacheSpaceA(struct qemu_syscall *call);
void qemu_FreeUrlCacheSpaceW(struct qemu_syscall *call);
void qemu_FtpCommandA(struct qemu_syscall *call);
void qemu_FtpCommandW(struct qemu_syscall *call);
void qemu_FtpCreateDirectoryA(struct qemu_syscall *call);
void qemu_FtpCreateDirectoryW(struct qemu_syscall *call);
void qemu_FtpDeleteFileA(struct qemu_syscall *call);
void qemu_FtpDeleteFileW(struct qemu_syscall *call);
void qemu_FtpFindFirstFileA(struct qemu_syscall *call);
void qemu_FtpFindFirstFileW(struct qemu_syscall *call);
void qemu_FtpGetCurrentDirectoryA(struct qemu_syscall *call);
void qemu_FtpGetCurrentDirectoryW(struct qemu_syscall *call);
void qemu_FtpGetFileA(struct qemu_syscall *call);
void qemu_FtpGetFileSize(struct qemu_syscall *call);
void qemu_FtpGetFileW(struct qemu_syscall *call);
void qemu_FtpOpenFileA(struct qemu_syscall *call);
void qemu_FtpOpenFileW(struct qemu_syscall *call);
void qemu_FtpPutFileA(struct qemu_syscall *call);
void qemu_FtpPutFileW(struct qemu_syscall *call);
void qemu_FtpRemoveDirectoryA(struct qemu_syscall *call);
void qemu_FtpRemoveDirectoryW(struct qemu_syscall *call);
void qemu_FtpRenameFileA(struct qemu_syscall *call);
void qemu_FtpRenameFileW(struct qemu_syscall *call);
void qemu_FtpSetCurrentDirectoryA(struct qemu_syscall *call);
void qemu_FtpSetCurrentDirectoryW(struct qemu_syscall *call);
void qemu_GetDiskInfoA(struct qemu_syscall *call);
void qemu_GetUrlCacheConfigInfoA(struct qemu_syscall *call);
void qemu_GetUrlCacheConfigInfoW(struct qemu_syscall *call);
void qemu_GetUrlCacheEntryInfoA(struct qemu_syscall *call);
void qemu_GetUrlCacheEntryInfoExA(struct qemu_syscall *call);
void qemu_GetUrlCacheEntryInfoExW(struct qemu_syscall *call);
void qemu_GetUrlCacheEntryInfoW(struct qemu_syscall *call);
void qemu_GetUrlCacheGroupAttributeA(struct qemu_syscall *call);
void qemu_GetUrlCacheGroupAttributeW(struct qemu_syscall *call);
void qemu_GopherCreateLocatorA(struct qemu_syscall *call);
void qemu_GopherCreateLocatorW(struct qemu_syscall *call);
void qemu_GopherFindFirstFileA(struct qemu_syscall *call);
void qemu_GopherFindFirstFileW(struct qemu_syscall *call);
void qemu_GopherGetAttributeA(struct qemu_syscall *call);
void qemu_GopherGetAttributeW(struct qemu_syscall *call);
void qemu_GopherGetLocatorTypeA(struct qemu_syscall *call);
void qemu_GopherGetLocatorTypeW(struct qemu_syscall *call);
void qemu_GopherOpenFileA(struct qemu_syscall *call);
void qemu_GopherOpenFileW(struct qemu_syscall *call);
void qemu_HttpAddRequestHeadersA(struct qemu_syscall *call);
void qemu_HttpAddRequestHeadersW(struct qemu_syscall *call);
void qemu_HttpEndRequestA(struct qemu_syscall *call);
void qemu_HttpEndRequestW(struct qemu_syscall *call);
void qemu_HttpOpenRequestA(struct qemu_syscall *call);
void qemu_HttpOpenRequestW(struct qemu_syscall *call);
void qemu_HttpQueryInfoA(struct qemu_syscall *call);
void qemu_HttpQueryInfoW(struct qemu_syscall *call);
void qemu_HttpSendRequestA(struct qemu_syscall *call);
void qemu_HttpSendRequestExA(struct qemu_syscall *call);
void qemu_HttpSendRequestExW(struct qemu_syscall *call);
void qemu_HttpSendRequestW(struct qemu_syscall *call);
void qemu_IncrementUrlCacheHeaderData(struct qemu_syscall *call);
void qemu_InternetAttemptConnect(struct qemu_syscall *call);
void qemu_InternetAutodial(struct qemu_syscall *call);
void qemu_InternetAutodialHangup(struct qemu_syscall *call);
void qemu_InternetCanonicalizeUrlA(struct qemu_syscall *call);
void qemu_InternetCanonicalizeUrlW(struct qemu_syscall *call);
void qemu_InternetCheckConnectionA(struct qemu_syscall *call);
void qemu_InternetCheckConnectionW(struct qemu_syscall *call);
void qemu_InternetClearAllPerSiteCookieDecisions(struct qemu_syscall *call);
void qemu_InternetCloseHandle(struct qemu_syscall *call);
void qemu_InternetCombineUrlA(struct qemu_syscall *call);
void qemu_InternetCombineUrlW(struct qemu_syscall *call);
void qemu_InternetConfirmZoneCrossingA(struct qemu_syscall *call);
void qemu_InternetConfirmZoneCrossingW(struct qemu_syscall *call);
void qemu_InternetConnectA(struct qemu_syscall *call);
void qemu_InternetConnectW(struct qemu_syscall *call);
void qemu_InternetCrackUrlA(struct qemu_syscall *call);
void qemu_InternetCrackUrlW(struct qemu_syscall *call);
void qemu_InternetCreateUrlA(struct qemu_syscall *call);
void qemu_InternetCreateUrlW(struct qemu_syscall *call);
void qemu_InternetDialA(struct qemu_syscall *call);
void qemu_InternetDialW(struct qemu_syscall *call);
void qemu_InternetEnumPerSiteCookieDecisionA(struct qemu_syscall *call);
void qemu_InternetEnumPerSiteCookieDecisionW(struct qemu_syscall *call);
void qemu_InternetErrorDlg(struct qemu_syscall *call);
void qemu_InternetFindNextFileA(struct qemu_syscall *call);
void qemu_InternetFindNextFileW(struct qemu_syscall *call);
void qemu_InternetGetConnectedState(struct qemu_syscall *call);
void qemu_InternetGetConnectedStateExA(struct qemu_syscall *call);
void qemu_InternetGetConnectedStateExW(struct qemu_syscall *call);
void qemu_InternetGetCookieA(struct qemu_syscall *call);
void qemu_InternetGetCookieExA(struct qemu_syscall *call);
void qemu_InternetGetCookieExW(struct qemu_syscall *call);
void qemu_InternetGetCookieW(struct qemu_syscall *call);
void qemu_InternetGetLastResponseInfoA(struct qemu_syscall *call);
void qemu_InternetGetLastResponseInfoW(struct qemu_syscall *call);
void qemu_InternetGetPerSiteCookieDecisionA(struct qemu_syscall *call);
void qemu_InternetGetPerSiteCookieDecisionW(struct qemu_syscall *call);
void qemu_InternetGetSecurityInfoByURLA(struct qemu_syscall *call);
void qemu_InternetGetSecurityInfoByURLW(struct qemu_syscall *call);
void qemu_InternetGoOnlineA(struct qemu_syscall *call);
void qemu_InternetGoOnlineW(struct qemu_syscall *call);
void qemu_InternetHangUp(struct qemu_syscall *call);
void qemu_InternetInitializeAutoProxyDll(struct qemu_syscall *call);
void qemu_InternetLockRequestFile(struct qemu_syscall *call);
void qemu_InternetOpenA(struct qemu_syscall *call);
void qemu_InternetOpenUrlA(struct qemu_syscall *call);
void qemu_InternetOpenUrlW(struct qemu_syscall *call);
void qemu_InternetOpenW(struct qemu_syscall *call);
void qemu_InternetQueryDataAvailable(struct qemu_syscall *call);
void qemu_InternetQueryFortezzaStatus(struct qemu_syscall *call);
void qemu_InternetQueryOptionA(struct qemu_syscall *call);
void qemu_InternetQueryOptionW(struct qemu_syscall *call);
void qemu_InternetReadFile(struct qemu_syscall *call);
void qemu_InternetReadFileExA(struct qemu_syscall *call);
void qemu_InternetReadFileExW(struct qemu_syscall *call);
void qemu_InternetSetCookieA(struct qemu_syscall *call);
void qemu_InternetSetCookieExA(struct qemu_syscall *call);
void qemu_InternetSetCookieExW(struct qemu_syscall *call);
void qemu_InternetSetCookieW(struct qemu_syscall *call);
void qemu_InternetSetFilePointer(struct qemu_syscall *call);
void qemu_InternetSetOptionA(struct qemu_syscall *call);
void qemu_InternetSetOptionExA(struct qemu_syscall *call);
void qemu_InternetSetOptionExW(struct qemu_syscall *call);
void qemu_InternetSetOptionW(struct qemu_syscall *call);
void qemu_InternetSetPerSiteCookieDecisionA(struct qemu_syscall *call);
void qemu_InternetSetPerSiteCookieDecisionW(struct qemu_syscall *call);
void qemu_InternetSetStatusCallbackA(struct qemu_syscall *call);
void qemu_InternetSetStatusCallbackW(struct qemu_syscall *call);
void qemu_InternetShowSecurityInfoByURLA(struct qemu_syscall *call);
void qemu_InternetShowSecurityInfoByURLW(struct qemu_syscall *call);
void qemu_InternetTimeFromSystemTimeA(struct qemu_syscall *call);
void qemu_InternetTimeFromSystemTimeW(struct qemu_syscall *call);
void qemu_InternetTimeToSystemTimeA(struct qemu_syscall *call);
void qemu_InternetTimeToSystemTimeW(struct qemu_syscall *call);
void qemu_InternetUnlockRequestFile(struct qemu_syscall *call);
void qemu_InternetWriteFile(struct qemu_syscall *call);
void qemu_IsDomainLegalCookieDomainW(struct qemu_syscall *call);
void qemu_IsHostInProxyBypassList(struct qemu_syscall *call);
void qemu_IsUrlCacheEntryExpiredA(struct qemu_syscall *call);
void qemu_IsUrlCacheEntryExpiredW(struct qemu_syscall *call);
void qemu_LoadUrlCacheContent(struct qemu_syscall *call);
void qemu_PrivacyGetZonePreferenceW(struct qemu_syscall *call);
void qemu_PrivacySetZonePreferenceW(struct qemu_syscall *call);
void qemu_ReadUrlCacheEntryStream(struct qemu_syscall *call);
void qemu_RegisterUrlCacheNotification(struct qemu_syscall *call);
void qemu_ResumeSuspendedDownload(struct qemu_syscall *call);
void qemu_RetrieveUrlCacheEntryFileA(struct qemu_syscall *call);
void qemu_RetrieveUrlCacheEntryFileW(struct qemu_syscall *call);
void qemu_RetrieveUrlCacheEntryStreamA(struct qemu_syscall *call);
void qemu_RetrieveUrlCacheEntryStreamW(struct qemu_syscall *call);
void qemu_RunOnceUrlCache(struct qemu_syscall *call);
void qemu_SetUrlCacheConfigInfoA(struct qemu_syscall *call);
void qemu_SetUrlCacheConfigInfoW(struct qemu_syscall *call);
void qemu_SetUrlCacheEntryGroupA(struct qemu_syscall *call);
void qemu_SetUrlCacheEntryGroupW(struct qemu_syscall *call);
void qemu_SetUrlCacheEntryInfoA(struct qemu_syscall *call);
void qemu_SetUrlCacheEntryInfoW(struct qemu_syscall *call);
void qemu_SetUrlCacheGroupAttributeA(struct qemu_syscall *call);
void qemu_SetUrlCacheGroupAttributeW(struct qemu_syscall *call);
void qemu_ShowClientAuthCerts(struct qemu_syscall *call);
void qemu_ShowX509EncodedCertificate(struct qemu_syscall *call);
void qemu_UnlockUrlCacheEntryFileA(struct qemu_syscall *call);
void qemu_UnlockUrlCacheEntryFileW(struct qemu_syscall *call);
void qemu_UnlockUrlCacheEntryStream(struct qemu_syscall *call);

#endif

#endif
