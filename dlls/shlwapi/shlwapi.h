#ifndef SHLWAPI_H
#define SHLWAPI_H

#include <stdlib.h>

enum shlwapi_calls
{
    CALL_CHRCMPIA = 0,
    CALL_CHRCMPIW,
    CALL_DOESSTRINGROUNDTRIPA,
    CALL_DOESSTRINGROUNDTRIPW,
    CALL_ISCHARSPACEA,
    CALL_ISCHARSPACEW,
    CALL_SHANSITOANSI,
    CALL_SHANSITOUNICODE,
    CALL_SHANSITOUNICODECP,
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
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_ChrCmpIA(struct qemu_syscall *call);
void qemu_ChrCmpIW(struct qemu_syscall *call);
void qemu_DoesStringRoundTripA(struct qemu_syscall *call);
void qemu_DoesStringRoundTripW(struct qemu_syscall *call);
void qemu_IsCharSpaceA(struct qemu_syscall *call);
void qemu_IsCharSpaceW(struct qemu_syscall *call);
void qemu_SHAnsiToAnsi(struct qemu_syscall *call);
void qemu_SHAnsiToUnicode(struct qemu_syscall *call);
void qemu_SHAnsiToUnicodeCP(struct qemu_syscall *call);
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

#endif

#endif
