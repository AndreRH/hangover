#ifndef SHLWAPI_H
#define SHLWAPI_H

#include <stdlib.h>

enum shlwapi_calls
{
    CALL_ASSOCCREATE = 0,
    CALL_ASSOCGETPERCEIVEDTYPE,
    CALL_ASSOCISDANGEROUS,
    CALL_ASSOCQUERYKEYA,
    CALL_ASSOCQUERYKEYW,
    CALL_ASSOCQUERYSTRINGA,
    CALL_ASSOCQUERYSTRINGBYKEYA,
    CALL_ASSOCQUERYSTRINGBYKEYW,
    CALL_ASSOCQUERYSTRINGW,
    CALL_CHRCMPIA,
    CALL_CHRCMPIW,
    CALL_DOESSTRINGROUNDTRIPA,
    CALL_DOESSTRINGROUNDTRIPW,
    CALL_HASHDATA,
    CALL_ISCHARSPACEA,
    CALL_ISCHARSPACEW,
    CALL_ISINTERNETESCENABLED,
    CALL_ISTREAM_RESET,
    CALL_ISTREAM_SIZE,
    CALL_MLBUILDRESURLA,
    CALL_MLBUILDRESURLW,
    CALL_PARSEURLA,
    CALL_PARSEURLW,
    CALL_PATHADDBACKSLASHA,
    CALL_PATHADDBACKSLASHW,
    CALL_PATHADDEXTENSIONA,
    CALL_PATHADDEXTENSIONW,
    CALL_PATHAPPENDA,
    CALL_PATHAPPENDW,
    CALL_PATHBUILDROOTA,
    CALL_PATHBUILDROOTW,
    CALL_PATHCANONICALIZEA,
    CALL_PATHCANONICALIZEW,
    CALL_PATHCOMBINEA,
    CALL_PATHCOMBINEW,
    CALL_PATHCOMMONPREFIXA,
    CALL_PATHCOMMONPREFIXW,
    CALL_PATHCOMPACTPATHA,
    CALL_PATHCOMPACTPATHEXA,
    CALL_PATHCOMPACTPATHEXW,
    CALL_PATHCOMPACTPATHW,
    CALL_PATHCREATEFROMURLA,
    CALL_PATHCREATEFROMURLALLOC,
    CALL_PATHCREATEFROMURLW,
    CALL_PATHFILEEXISTSA,
    CALL_PATHFILEEXISTSANDATTRIBUTESA,
    CALL_PATHFILEEXISTSANDATTRIBUTESW,
    CALL_PATHFILEEXISTSDEFEXTA,
    CALL_PATHFILEEXISTSDEFEXTW,
    CALL_PATHFILEEXISTSW,
    CALL_PATHFINDEXTENSIONA,
    CALL_PATHFINDEXTENSIONW,
    CALL_PATHFINDFILENAMEA,
    CALL_PATHFINDFILENAMEW,
    CALL_PATHFINDNEXTCOMPONENTA,
    CALL_PATHFINDNEXTCOMPONENTW,
    CALL_PATHFINDONPATHA,
    CALL_PATHFINDONPATHEXA,
    CALL_PATHFINDONPATHEXW,
    CALL_PATHFINDONPATHW,
    CALL_PATHFINDSUFFIXARRAYA,
    CALL_PATHFINDSUFFIXARRAYW,
    CALL_PATHGETARGSA,
    CALL_PATHGETARGSW,
    CALL_PATHGETCHARTYPEA,
    CALL_PATHGETCHARTYPEW,
    CALL_PATHGETDRIVENUMBERA,
    CALL_PATHGETDRIVENUMBERW,
    CALL_PATHISCONTENTTYPEA,
    CALL_PATHISCONTENTTYPEW,
    CALL_PATHISDIRECTORYA,
    CALL_PATHISDIRECTORYEMPTYA,
    CALL_PATHISDIRECTORYEMPTYW,
    CALL_PATHISDIRECTORYW,
    CALL_PATHISFILESPECA,
    CALL_PATHISFILESPECW,
    CALL_PATHISLFNFILESPECA,
    CALL_PATHISLFNFILESPECW,
    CALL_PATHISNETWORKPATHA,
    CALL_PATHISNETWORKPATHW,
    CALL_PATHISPREFIXA,
    CALL_PATHISPREFIXW,
    CALL_PATHISRELATIVEA,
    CALL_PATHISRELATIVEW,
    CALL_PATHISROOTA,
    CALL_PATHISROOTW,
    CALL_PATHISSAMEROOTA,
    CALL_PATHISSAMEROOTW,
    CALL_PATHISSYSTEMFOLDERA,
    CALL_PATHISSYSTEMFOLDERW,
    CALL_PATHISUNCA,
    CALL_PATHISUNCSERVERA,
    CALL_PATHISUNCSERVERSHAREA,
    CALL_PATHISUNCSERVERSHAREW,
    CALL_PATHISUNCSERVERW,
    CALL_PATHISUNCW,
    CALL_PATHISURLA,
    CALL_PATHISURLW,
    CALL_PATHISVALIDCHARA,
    CALL_PATHISVALIDCHARW,
    CALL_PATHMAKEPRETTYA,
    CALL_PATHMAKEPRETTYW,
    CALL_PATHMAKESYSTEMFOLDERA,
    CALL_PATHMAKESYSTEMFOLDERW,
    CALL_PATHMATCHSPECA,
    CALL_PATHMATCHSPECW,
    CALL_PATHPARSEICONLOCATIONA,
    CALL_PATHPARSEICONLOCATIONW,
    CALL_PATHQUOTESPACESA,
    CALL_PATHQUOTESPACESW,
    CALL_PATHRELATIVEPATHTOA,
    CALL_PATHRELATIVEPATHTOW,
    CALL_PATHREMOVEARGSA,
    CALL_PATHREMOVEARGSW,
    CALL_PATHREMOVEBACKSLASHA,
    CALL_PATHREMOVEBACKSLASHW,
    CALL_PATHREMOVEBLANKSA,
    CALL_PATHREMOVEBLANKSW,
    CALL_PATHREMOVEEXTENSIONA,
    CALL_PATHREMOVEEXTENSIONW,
    CALL_PATHREMOVEFILESPECA,
    CALL_PATHREMOVEFILESPECW,
    CALL_PATHRENAMEEXTENSIONA,
    CALL_PATHRENAMEEXTENSIONW,
    CALL_PATHSEARCHANDQUALIFYA,
    CALL_PATHSEARCHANDQUALIFYW,
    CALL_PATHSETDLGITEMPATHA,
    CALL_PATHSETDLGITEMPATHW,
    CALL_PATHSKIPROOTA,
    CALL_PATHSKIPROOTW,
    CALL_PATHSTRIPPATHA,
    CALL_PATHSTRIPPATHW,
    CALL_PATHSTRIPTOROOTA,
    CALL_PATHSTRIPTOROOTW,
    CALL_PATHUNDECORATEA,
    CALL_PATHUNDECORATEW,
    CALL_PATHUNEXPANDENVSTRINGSA,
    CALL_PATHUNEXPANDENVSTRINGSW,
    CALL_PATHUNMAKESYSTEMFOLDERA,
    CALL_PATHUNMAKESYSTEMFOLDERW,
    CALL_PATHUNQUOTESPACESA,
    CALL_PATHUNQUOTESPACESW,
    CALL_SHANSITOANSI,
    CALL_SHANSITOUNICODE,
    CALL_SHANSITOUNICODECP,
    CALL_SHAUTOCOMPLETE,
    CALL_SHCREATESTREAMONFILEA,
    CALL_SHCREATESTREAMONFILEEX,
    CALL_SHCREATESTREAMONFILEW,
    CALL_SHGETWEBFOLDERFILEPATHA,
    CALL_SHGETWEBFOLDERFILEPATHW,
    CALL_SHISEMPTYSTREAM,
    CALL_SHISTREAM_READ,
    CALL_SHISTREAM_WRITE,
    CALL_SHLOADINDIRECTSTRING,
    CALL_SHSTRDUPA,
    CALL_SHSTRDUPW,
    CALL_SHSTRIPMNEUMONICA,
    CALL_SHSTRIPMNEUMONICW,
    CALL_SHTRUNCATESTRING,
    CALL_SHUNICODETOANSI,
    CALL_SHUNICODETOANSICP,
    CALL_SHUNICODETOUNICODE,
    CALL_STRCATBUFFA,
    CALL_STRCATBUFFW,
    CALL_STRCATCHAINW,
    CALL_STRCATW,
    CALL_STRCHRA,
    CALL_STRCHRIA,
    CALL_STRCHRIW,
    CALL_STRCHRNW,
    CALL_STRCHRW,
    CALL_STRCMPIW,
    CALL_STRCMPLOGICALW,
    CALL_STRCMPNA,
    CALL_STRCMPNIA,
    CALL_STRCMPNIW,
    CALL_STRCMPNW,
    CALL_STRCMPW,
    CALL_STRCPYNW,
    CALL_STRCPYNXA,
    CALL_STRCPYNXW,
    CALL_STRCPYW,
    CALL_STRCSPNA,
    CALL_STRCSPNIA,
    CALL_STRCSPNIW,
    CALL_STRCSPNW,
    CALL_STRDUPA,
    CALL_STRDUPW,
    CALL_STRFORMATBYTESIZE64A,
    CALL_STRFORMATBYTESIZEA,
    CALL_STRFORMATBYTESIZEW,
    CALL_STRFORMATKBSIZEA,
    CALL_STRFORMATKBSIZEW,
    CALL_STRFROMTIMEINTERVALA,
    CALL_STRFROMTIMEINTERVALW,
    CALL_STRISINTLEQUALA,
    CALL_STRISINTLEQUALW,
    CALL_STRNCATA,
    CALL_STRNCATW,
    CALL_STRPBRKA,
    CALL_STRPBRKW,
    CALL_STRRCHRA,
    CALL_STRRCHRIA,
    CALL_STRRCHRIW,
    CALL_STRRCHRW,
    CALL_STRRETTOBSTR,
    CALL_STRRETTOBUFA,
    CALL_STRRETTOBUFW,
    CALL_STRRETTOSTRA,
    CALL_STRRETTOSTRW,
    CALL_STRRSTRIA,
    CALL_STRRSTRIW,
    CALL_STRSPNA,
    CALL_STRSPNW,
    CALL_STRSTRA,
    CALL_STRSTRIA,
    CALL_STRSTRIW,
    CALL_STRSTRNIW,
    CALL_STRSTRNW,
    CALL_STRSTRW,
    CALL_STRTOINT64EXA,
    CALL_STRTOINT64EXW,
    CALL_STRTOINTA,
    CALL_STRTOINTEXA,
    CALL_STRTOINTEXW,
    CALL_STRTOINTW,
    CALL_STRTRIMA,
    CALL_STRTRIMW,
    CALL_URLAPPLYSCHEMEA,
    CALL_URLAPPLYSCHEMEW,
    CALL_URLCANONICALIZEA,
    CALL_URLCANONICALIZEW,
    CALL_URLCOMBINEA,
    CALL_URLCOMBINEW,
    CALL_URLCOMPAREA,
    CALL_URLCOMPAREW,
    CALL_URLCREATEFROMPATHA,
    CALL_URLCREATEFROMPATHW,
    CALL_URLESCAPEA,
    CALL_URLESCAPEW,
    CALL_URLFIXUPW,
    CALL_URLGETLOCATIONA,
    CALL_URLGETLOCATIONW,
    CALL_URLGETPARTA,
    CALL_URLGETPARTW,
    CALL_URLHASHA,
    CALL_URLHASHW,
    CALL_URLISA,
    CALL_URLISNOHISTORYA,
    CALL_URLISNOHISTORYW,
    CALL_URLISOPAQUEA,
    CALL_URLISOPAQUEW,
    CALL_URLISW,
    CALL_URLUNESCAPEA,
    CALL_URLUNESCAPEW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_AssocCreate(struct qemu_syscall *call);
void qemu_AssocGetPerceivedType(struct qemu_syscall *call);
void qemu_AssocIsDangerous(struct qemu_syscall *call);
void qemu_AssocQueryKeyA(struct qemu_syscall *call);
void qemu_AssocQueryKeyW(struct qemu_syscall *call);
void qemu_AssocQueryStringA(struct qemu_syscall *call);
void qemu_AssocQueryStringByKeyA(struct qemu_syscall *call);
void qemu_AssocQueryStringByKeyW(struct qemu_syscall *call);
void qemu_AssocQueryStringW(struct qemu_syscall *call);
void qemu_ChrCmpIA(struct qemu_syscall *call);
void qemu_ChrCmpIW(struct qemu_syscall *call);
void qemu_DoesStringRoundTripA(struct qemu_syscall *call);
void qemu_DoesStringRoundTripW(struct qemu_syscall *call);
void qemu_HashData(struct qemu_syscall *call);
void qemu_IsCharSpaceA(struct qemu_syscall *call);
void qemu_IsCharSpaceW(struct qemu_syscall *call);
void qemu_IsInternetESCEnabled(struct qemu_syscall *call);
void qemu_IStream_Reset(struct qemu_syscall *call);
void qemu_IStream_Size(struct qemu_syscall *call);
void qemu_MLBuildResURLA(struct qemu_syscall *call);
void qemu_MLBuildResURLW(struct qemu_syscall *call);
void qemu_ParseURLA(struct qemu_syscall *call);
void qemu_ParseURLW(struct qemu_syscall *call);
void qemu_PathAddBackslashA(struct qemu_syscall *call);
void qemu_PathAddBackslashW(struct qemu_syscall *call);
void qemu_PathAddExtensionA(struct qemu_syscall *call);
void qemu_PathAddExtensionW(struct qemu_syscall *call);
void qemu_PathAppendA(struct qemu_syscall *call);
void qemu_PathAppendW(struct qemu_syscall *call);
void qemu_PathBuildRootA(struct qemu_syscall *call);
void qemu_PathBuildRootW(struct qemu_syscall *call);
void qemu_PathCanonicalizeA(struct qemu_syscall *call);
void qemu_PathCanonicalizeW(struct qemu_syscall *call);
void qemu_PathCombineA(struct qemu_syscall *call);
void qemu_PathCombineW(struct qemu_syscall *call);
void qemu_PathCommonPrefixA(struct qemu_syscall *call);
void qemu_PathCommonPrefixW(struct qemu_syscall *call);
void qemu_PathCompactPathA(struct qemu_syscall *call);
void qemu_PathCompactPathExA(struct qemu_syscall *call);
void qemu_PathCompactPathExW(struct qemu_syscall *call);
void qemu_PathCompactPathW(struct qemu_syscall *call);
void qemu_PathCreateFromUrlA(struct qemu_syscall *call);
void qemu_PathCreateFromUrlAlloc(struct qemu_syscall *call);
void qemu_PathCreateFromUrlW(struct qemu_syscall *call);
void qemu_PathFileExistsA(struct qemu_syscall *call);
void qemu_PathFileExistsAndAttributesA(struct qemu_syscall *call);
void qemu_PathFileExistsAndAttributesW(struct qemu_syscall *call);
void qemu_PathFileExistsDefExtA(struct qemu_syscall *call);
void qemu_PathFileExistsDefExtW(struct qemu_syscall *call);
void qemu_PathFileExistsW(struct qemu_syscall *call);
void qemu_PathFindExtensionA(struct qemu_syscall *call);
void qemu_PathFindExtensionW(struct qemu_syscall *call);
void qemu_PathFindFileNameA(struct qemu_syscall *call);
void qemu_PathFindFileNameW(struct qemu_syscall *call);
void qemu_PathFindNextComponentA(struct qemu_syscall *call);
void qemu_PathFindNextComponentW(struct qemu_syscall *call);
void qemu_PathFindOnPathA(struct qemu_syscall *call);
void qemu_PathFindOnPathExA(struct qemu_syscall *call);
void qemu_PathFindOnPathExW(struct qemu_syscall *call);
void qemu_PathFindOnPathW(struct qemu_syscall *call);
void qemu_PathFindSuffixArrayA(struct qemu_syscall *call);
void qemu_PathFindSuffixArrayW(struct qemu_syscall *call);
void qemu_PathGetArgsA(struct qemu_syscall *call);
void qemu_PathGetArgsW(struct qemu_syscall *call);
void qemu_PathGetCharTypeA(struct qemu_syscall *call);
void qemu_PathGetCharTypeW(struct qemu_syscall *call);
void qemu_PathGetDriveNumberA(struct qemu_syscall *call);
void qemu_PathGetDriveNumberW(struct qemu_syscall *call);
void qemu_PathIsContentTypeA(struct qemu_syscall *call);
void qemu_PathIsContentTypeW(struct qemu_syscall *call);
void qemu_PathIsDirectoryA(struct qemu_syscall *call);
void qemu_PathIsDirectoryEmptyA(struct qemu_syscall *call);
void qemu_PathIsDirectoryEmptyW(struct qemu_syscall *call);
void qemu_PathIsDirectoryW(struct qemu_syscall *call);
void qemu_PathIsFileSpecA(struct qemu_syscall *call);
void qemu_PathIsFileSpecW(struct qemu_syscall *call);
void qemu_PathIsLFNFileSpecA(struct qemu_syscall *call);
void qemu_PathIsLFNFileSpecW(struct qemu_syscall *call);
void qemu_PathIsNetworkPathA(struct qemu_syscall *call);
void qemu_PathIsNetworkPathW(struct qemu_syscall *call);
void qemu_PathIsPrefixA(struct qemu_syscall *call);
void qemu_PathIsPrefixW(struct qemu_syscall *call);
void qemu_PathIsRelativeA(struct qemu_syscall *call);
void qemu_PathIsRelativeW(struct qemu_syscall *call);
void qemu_PathIsRootA(struct qemu_syscall *call);
void qemu_PathIsRootW(struct qemu_syscall *call);
void qemu_PathIsSameRootA(struct qemu_syscall *call);
void qemu_PathIsSameRootW(struct qemu_syscall *call);
void qemu_PathIsSystemFolderA(struct qemu_syscall *call);
void qemu_PathIsSystemFolderW(struct qemu_syscall *call);
void qemu_PathIsUNCA(struct qemu_syscall *call);
void qemu_PathIsUNCServerA(struct qemu_syscall *call);
void qemu_PathIsUNCServerShareA(struct qemu_syscall *call);
void qemu_PathIsUNCServerShareW(struct qemu_syscall *call);
void qemu_PathIsUNCServerW(struct qemu_syscall *call);
void qemu_PathIsUNCW(struct qemu_syscall *call);
void qemu_PathIsURLA(struct qemu_syscall *call);
void qemu_PathIsURLW(struct qemu_syscall *call);
void qemu_PathIsValidCharA(struct qemu_syscall *call);
void qemu_PathIsValidCharW(struct qemu_syscall *call);
void qemu_PathMakePrettyA(struct qemu_syscall *call);
void qemu_PathMakePrettyW(struct qemu_syscall *call);
void qemu_PathMakeSystemFolderA(struct qemu_syscall *call);
void qemu_PathMakeSystemFolderW(struct qemu_syscall *call);
void qemu_PathMatchSpecA(struct qemu_syscall *call);
void qemu_PathMatchSpecW(struct qemu_syscall *call);
void qemu_PathParseIconLocationA(struct qemu_syscall *call);
void qemu_PathParseIconLocationW(struct qemu_syscall *call);
void qemu_PathQuoteSpacesA(struct qemu_syscall *call);
void qemu_PathQuoteSpacesW(struct qemu_syscall *call);
void qemu_PathRelativePathToA(struct qemu_syscall *call);
void qemu_PathRelativePathToW(struct qemu_syscall *call);
void qemu_PathRemoveArgsA(struct qemu_syscall *call);
void qemu_PathRemoveArgsW(struct qemu_syscall *call);
void qemu_PathRemoveBackslashA(struct qemu_syscall *call);
void qemu_PathRemoveBackslashW(struct qemu_syscall *call);
void qemu_PathRemoveBlanksA(struct qemu_syscall *call);
void qemu_PathRemoveBlanksW(struct qemu_syscall *call);
void qemu_PathRemoveExtensionA(struct qemu_syscall *call);
void qemu_PathRemoveExtensionW(struct qemu_syscall *call);
void qemu_PathRemoveFileSpecA(struct qemu_syscall *call);
void qemu_PathRemoveFileSpecW(struct qemu_syscall *call);
void qemu_PathRenameExtensionA(struct qemu_syscall *call);
void qemu_PathRenameExtensionW(struct qemu_syscall *call);
void qemu_PathSearchAndQualifyA(struct qemu_syscall *call);
void qemu_PathSearchAndQualifyW(struct qemu_syscall *call);
void qemu_PathSetDlgItemPathA(struct qemu_syscall *call);
void qemu_PathSetDlgItemPathW(struct qemu_syscall *call);
void qemu_PathSkipRootA(struct qemu_syscall *call);
void qemu_PathSkipRootW(struct qemu_syscall *call);
void qemu_PathStripPathA(struct qemu_syscall *call);
void qemu_PathStripPathW(struct qemu_syscall *call);
void qemu_PathStripToRootA(struct qemu_syscall *call);
void qemu_PathStripToRootW(struct qemu_syscall *call);
void qemu_PathUndecorateA(struct qemu_syscall *call);
void qemu_PathUndecorateW(struct qemu_syscall *call);
void qemu_PathUnExpandEnvStringsA(struct qemu_syscall *call);
void qemu_PathUnExpandEnvStringsW(struct qemu_syscall *call);
void qemu_PathUnmakeSystemFolderA(struct qemu_syscall *call);
void qemu_PathUnmakeSystemFolderW(struct qemu_syscall *call);
void qemu_PathUnquoteSpacesA(struct qemu_syscall *call);
void qemu_PathUnquoteSpacesW(struct qemu_syscall *call);
void qemu_SHAnsiToAnsi(struct qemu_syscall *call);
void qemu_SHAnsiToUnicode(struct qemu_syscall *call);
void qemu_SHAnsiToUnicodeCP(struct qemu_syscall *call);
void qemu_SHAutoComplete(struct qemu_syscall *call);
void qemu_SHCreateStreamOnFileA(struct qemu_syscall *call);
void qemu_SHCreateStreamOnFileEx(struct qemu_syscall *call);
void qemu_SHCreateStreamOnFileW(struct qemu_syscall *call);
void qemu_SHGetWebFolderFilePathA(struct qemu_syscall *call);
void qemu_SHGetWebFolderFilePathW(struct qemu_syscall *call);
void qemu_SHIsEmptyStream(struct qemu_syscall *call);
void qemu_SHIStream_Read(struct qemu_syscall *call);
void qemu_SHIStream_Write(struct qemu_syscall *call);
void qemu_SHLoadIndirectString(struct qemu_syscall *call);
void qemu_SHStrDupA(struct qemu_syscall *call);
void qemu_SHStrDupW(struct qemu_syscall *call);
void qemu_SHStripMneumonicA(struct qemu_syscall *call);
void qemu_SHStripMneumonicW(struct qemu_syscall *call);
void qemu_SHTruncateString(struct qemu_syscall *call);
void qemu_SHUnicodeToAnsi(struct qemu_syscall *call);
void qemu_SHUnicodeToAnsiCP(struct qemu_syscall *call);
void qemu_SHUnicodeToUnicode(struct qemu_syscall *call);
void qemu_StrCatBuffA(struct qemu_syscall *call);
void qemu_StrCatBuffW(struct qemu_syscall *call);
void qemu_StrCatChainW(struct qemu_syscall *call);
void qemu_StrCatW(struct qemu_syscall *call);
void qemu_StrChrA(struct qemu_syscall *call);
void qemu_StrChrIA(struct qemu_syscall *call);
void qemu_StrChrIW(struct qemu_syscall *call);
void qemu_StrChrNW(struct qemu_syscall *call);
void qemu_StrChrW(struct qemu_syscall *call);
void qemu_StrCmpIW(struct qemu_syscall *call);
void qemu_StrCmpLogicalW(struct qemu_syscall *call);
void qemu_StrCmpNA(struct qemu_syscall *call);
void qemu_StrCmpNIA(struct qemu_syscall *call);
void qemu_StrCmpNIW(struct qemu_syscall *call);
void qemu_StrCmpNW(struct qemu_syscall *call);
void qemu_StrCmpW(struct qemu_syscall *call);
void qemu_StrCpyNW(struct qemu_syscall *call);
void qemu_StrCpyNXA(struct qemu_syscall *call);
void qemu_StrCpyNXW(struct qemu_syscall *call);
void qemu_StrCpyW(struct qemu_syscall *call);
void qemu_StrCSpnA(struct qemu_syscall *call);
void qemu_StrCSpnIA(struct qemu_syscall *call);
void qemu_StrCSpnIW(struct qemu_syscall *call);
void qemu_StrCSpnW(struct qemu_syscall *call);
void qemu_StrDupA(struct qemu_syscall *call);
void qemu_StrDupW(struct qemu_syscall *call);
void qemu_StrFormatByteSize64A(struct qemu_syscall *call);
void qemu_StrFormatByteSizeA(struct qemu_syscall *call);
void qemu_StrFormatByteSizeW(struct qemu_syscall *call);
void qemu_StrFormatKBSizeA(struct qemu_syscall *call);
void qemu_StrFormatKBSizeW(struct qemu_syscall *call);
void qemu_StrFromTimeIntervalA(struct qemu_syscall *call);
void qemu_StrFromTimeIntervalW(struct qemu_syscall *call);
void qemu_StrIsIntlEqualA(struct qemu_syscall *call);
void qemu_StrIsIntlEqualW(struct qemu_syscall *call);
void qemu_StrNCatA(struct qemu_syscall *call);
void qemu_StrNCatW(struct qemu_syscall *call);
void qemu_StrPBrkA(struct qemu_syscall *call);
void qemu_StrPBrkW(struct qemu_syscall *call);
void qemu_StrRChrA(struct qemu_syscall *call);
void qemu_StrRChrIA(struct qemu_syscall *call);
void qemu_StrRChrIW(struct qemu_syscall *call);
void qemu_StrRChrW(struct qemu_syscall *call);
void qemu_StrRetToBSTR(struct qemu_syscall *call);
void qemu_StrRetToBufA(struct qemu_syscall *call);
void qemu_StrRetToBufW(struct qemu_syscall *call);
void qemu_StrRetToStrA(struct qemu_syscall *call);
void qemu_StrRetToStrW(struct qemu_syscall *call);
void qemu_StrRStrIA(struct qemu_syscall *call);
void qemu_StrRStrIW(struct qemu_syscall *call);
void qemu_StrSpnA(struct qemu_syscall *call);
void qemu_StrSpnW(struct qemu_syscall *call);
void qemu_StrStrA(struct qemu_syscall *call);
void qemu_StrStrIA(struct qemu_syscall *call);
void qemu_StrStrIW(struct qemu_syscall *call);
void qemu_StrStrNIW(struct qemu_syscall *call);
void qemu_StrStrNW(struct qemu_syscall *call);
void qemu_StrStrW(struct qemu_syscall *call);
void qemu_StrToInt64ExA(struct qemu_syscall *call);
void qemu_StrToInt64ExW(struct qemu_syscall *call);
void qemu_StrToIntA(struct qemu_syscall *call);
void qemu_StrToIntExA(struct qemu_syscall *call);
void qemu_StrToIntExW(struct qemu_syscall *call);
void qemu_StrToIntW(struct qemu_syscall *call);
void qemu_StrTrimA(struct qemu_syscall *call);
void qemu_StrTrimW(struct qemu_syscall *call);
void qemu_UrlApplySchemeA(struct qemu_syscall *call);
void qemu_UrlApplySchemeW(struct qemu_syscall *call);
void qemu_UrlCanonicalizeA(struct qemu_syscall *call);
void qemu_UrlCanonicalizeW(struct qemu_syscall *call);
void qemu_UrlCombineA(struct qemu_syscall *call);
void qemu_UrlCombineW(struct qemu_syscall *call);
void qemu_UrlCompareA(struct qemu_syscall *call);
void qemu_UrlCompareW(struct qemu_syscall *call);
void qemu_UrlCreateFromPathA(struct qemu_syscall *call);
void qemu_UrlCreateFromPathW(struct qemu_syscall *call);
void qemu_UrlEscapeA(struct qemu_syscall *call);
void qemu_UrlEscapeW(struct qemu_syscall *call);
void qemu_UrlFixupW(struct qemu_syscall *call);
void qemu_UrlGetLocationA(struct qemu_syscall *call);
void qemu_UrlGetLocationW(struct qemu_syscall *call);
void qemu_UrlGetPartA(struct qemu_syscall *call);
void qemu_UrlGetPartW(struct qemu_syscall *call);
void qemu_UrlHashA(struct qemu_syscall *call);
void qemu_UrlHashW(struct qemu_syscall *call);
void qemu_UrlIsA(struct qemu_syscall *call);
void qemu_UrlIsNoHistoryA(struct qemu_syscall *call);
void qemu_UrlIsNoHistoryW(struct qemu_syscall *call);
void qemu_UrlIsOpaqueA(struct qemu_syscall *call);
void qemu_UrlIsOpaqueW(struct qemu_syscall *call);
void qemu_UrlIsW(struct qemu_syscall *call);
void qemu_UrlUnescapeA(struct qemu_syscall *call);
void qemu_UrlUnescapeW(struct qemu_syscall *call);

#endif

#endif
