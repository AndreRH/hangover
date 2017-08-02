#ifndef NTDLL_H
#define NTDLL_H

enum ntdll_calls
{
    CALL___C_SPECIFIC_HANDLER = 0,
    CALL___ISASCII,
    CALL___ISCSYM,
    CALL___ISCSYMF,
    CALL___TOASCII,
    CALL__ATOI64,
    CALL__I64TOA,
    CALL__ITOA,
    CALL__LTOA,
    CALL__MEMCCPY,
    CALL__MEMICMP,
    CALL__SPLITPATH,
    CALL__STRICMP,
    CALL__STRLWR,
    CALL__STRNICMP,
    CALL__STRUPR,
    CALL__TOLOWER,
    CALL__TOUPPER,
    CALL__UI64TOA,
    CALL__ULTOA,
    CALL_ATOI,
    CALL_ATOL,
    CALL_ISALNUM,
    CALL_ISALPHA,
    CALL_ISCNTRL,
    CALL_ISDIGIT,
    CALL_ISGRAPH,
    CALL_ISLOWER,
    CALL_ISPRINT,
    CALL_ISPUNCT,
    CALL_ISSPACE,
    CALL_ISUPPER,
    CALL_ISXDIGIT,
    CALL_MEMCHR,
    CALL_MEMCMP,
    CALL_MEMCPY,
    CALL_MEMMOVE,
    CALL_MEMSET,
    CALL_NTCANCELIOFILE,
    CALL_NTCANCELIOFILEEX,
    CALL_NTCREATEFILE,
    CALL_NTCREATEMAILSLOTFILE,
    CALL_NTCREATENAMEDPIPEFILE,
    CALL_NTDELETEFILE,
    CALL_NTDEVICEIOCONTROLFILE,
    CALL_NTFLUSHBUFFERSFILE,
    CALL_NTFSCONTROLFILE,
    CALL_NTLOCKFILE,
    CALL_NTNOTIFYCHANGEDIRECTORYFILE,
    CALL_NTOPENFILE,
    CALL_NTQUERYATTRIBUTESFILE,
    CALL_NTQUERYEAFILE,
    CALL_NTQUERYFULLATTRIBUTESFILE,
    CALL_NTQUERYINFORMATIONFILE,
    CALL_NTQUERYVOLUMEINFORMATIONFILE,
    CALL_NTREADFILE,
    CALL_NTREADFILESCATTER,
    CALL_NTSETEAFILE,
    CALL_NTSETINFORMATIONFILE,
    CALL_NTSETVOLUMEINFORMATIONFILE,
    CALL_NTUNLOCKFILE,
    CALL_NTWRITEFILE,
    CALL_NTWRITEFILEGATHER,
    CALL_RTLACQUIREPEBLOCK,
    CALL_RTLACQUIRERESOURCEEXCLUSIVE,
    CALL_RTLACQUIRERESOURCESHARED,
    CALL_RTLADDFUNCTIONTABLE,
    CALL_RTLAREALLACCESSESGRANTED,
    CALL_RTLAREANYACCESSESGRANTED,
    CALL_RTLASSERT,
    CALL_RTLCAPTURECONTEXT,
    CALL_RTLCOMPAREMEMORY,
    CALL_RTLCOMPAREMEMORYULONG,
    CALL_RTLCOMPRESSBUFFER,
    CALL_RTLCOMPUTECRC32,
    CALL_RTLCOPYLUID,
    CALL_RTLCOPYLUIDANDATTRIBUTESARRAY,
    CALL_RTLCOPYMEMORY,
    CALL_RTLCREATEUSERPROCESS,
    CALL_RTLDECODEPOINTER,
    CALL_RTLDECOMPRESSBUFFER,
    CALL_RTLDECOMPRESSFRAGMENT,
    CALL_RTLDELETECRITICALSECTION,
    CALL_RTLDELETERESOURCE,
    CALL_RTLDELETESECURITYOBJECT,
    CALL_RTLDUMPRESOURCE,
    CALL_RTLENCODEPOINTER,
    CALL_RTLENTERCRITICALSECTION,
    CALL_RTLEQUALLUID,
    CALL_RTLFILLMEMORY,
    CALL_RTLFILLMEMORYULONG,
    CALL_RTLFIRSTENTRYSLIST,
    CALL_RTLGETCOMPRESSIONWORKSPACESIZE,
    CALL_RTLGETCURRENTPROCESSORNUMBEREX,
    CALL_RTLGETCURRENTTRANSACTION,
    CALL_RTLGETTHREADERRORMODE,
    CALL_RTLINITIALIZECRITICALSECTIONEX,
    CALL_RTLINITIALIZEGENERICTABLE,
    CALL_RTLINITIALIZEGENERICTABLEAVL,
    CALL_RTLINITIALIZERESOURCE,
    CALL_RTLINITIALIZESLISTHEAD,
    CALL_RTLINSERTELEMENTGENERICTABLEAVL,
    CALL_RTLINTERLOCKEDFLUSHSLIST,
    CALL_RTLINTERLOCKEDPOPENTRYSLIST,
    CALL_RTLINTERLOCKEDPUSHENTRYSLIST,
    CALL_RTLINTERLOCKEDPUSHLISTSLIST,
    CALL_RTLINTERLOCKEDPUSHLISTSLISTEX,
    CALL_RTLIPV4ADDRESSTOSTRINGA,
    CALL_RTLIPV4ADDRESSTOSTRINGEXA,
    CALL_RTLIPV4ADDRESSTOSTRINGEXW,
    CALL_RTLIPV4ADDRESSTOSTRINGW,
    CALL_RTLIPV4STRINGTOADDRESSEXW,
    CALL_RTLLEAVECRITICALSECTION,
    CALL_RTLLOOKUPFUNCTIONENTRY,
    CALL_RTLMAPGENERICMASK,
    CALL_RTLMOVEMEMORY,
    CALL_RTLNEWSECURITYOBJECT,
    CALL_RTLQUERYDEPTHSLIST,
    CALL_RTLRANDOM,
    CALL_RTLRELEASEPEBLOCK,
    CALL_RTLRELEASERESOURCE,
    CALL_RTLSETCURRENTTRANSACTION,
    CALL_RTLSETTHREADERRORMODE,
    CALL_RTLUNIFORM,
    CALL_RTLVIRTUALUNWIND,
    CALL_RTLZEROMEMORY,
    CALL_STRCAT,
    CALL_STRCHR,
    CALL_STRCMP,
    CALL_STRCPY,
    CALL_STRCSPN,
    CALL_STRLEN,
    CALL_STRNCAT,
    CALL_STRNCMP,
    CALL_STRNCPY,
    CALL_STRPBRK,
    CALL_STRRCHR,
    CALL_STRSPN,
    CALL_STRSTR,
    CALL_STRTOL,
    CALL_STRTOUL,
    CALL_TOLOWER,
    CALL_TOUPPER,
    CALL_WCSRCHR
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu___C_specific_handler(struct qemu_syscall *call);
void qemu___isascii(struct qemu_syscall *call);
void qemu___iscsym(struct qemu_syscall *call);
void qemu___iscsymf(struct qemu_syscall *call);
void qemu___toascii(struct qemu_syscall *call);
void qemu__atoi64(struct qemu_syscall *call);
void qemu__i64toa(struct qemu_syscall *call);
void qemu__itoa(struct qemu_syscall *call);
void qemu__ltoa(struct qemu_syscall *call);
void qemu__memccpy(struct qemu_syscall *call);
void qemu__memicmp(struct qemu_syscall *call);
void qemu__splitpath(struct qemu_syscall *call);
void qemu__stricmp(struct qemu_syscall *call);
void qemu__strlwr(struct qemu_syscall *call);
void qemu__strnicmp(struct qemu_syscall *call);
void qemu__strupr(struct qemu_syscall *call);
void qemu__tolower(struct qemu_syscall *call);
void qemu__toupper(struct qemu_syscall *call);
void qemu__ui64toa(struct qemu_syscall *call);
void qemu__ultoa(struct qemu_syscall *call);
void qemu_atoi(struct qemu_syscall *call);
void qemu_atol(struct qemu_syscall *call);
void qemu_isalnum(struct qemu_syscall *call);
void qemu_isalpha(struct qemu_syscall *call);
void qemu_iscntrl(struct qemu_syscall *call);
void qemu_isdigit(struct qemu_syscall *call);
void qemu_isgraph(struct qemu_syscall *call);
void qemu_islower(struct qemu_syscall *call);
void qemu_isprint(struct qemu_syscall *call);
void qemu_ispunct(struct qemu_syscall *call);
void qemu_isspace(struct qemu_syscall *call);
void qemu_isupper(struct qemu_syscall *call);
void qemu_isxdigit(struct qemu_syscall *call);
void qemu_memchr(struct qemu_syscall *call);
void qemu_memcmp(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memmove(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_NtCancelIoFile(struct qemu_syscall *call);
void qemu_NtCancelIoFileEx(struct qemu_syscall *call);
void qemu_NtCreateFile(struct qemu_syscall *call);
void qemu_NtCreateMailslotFile(struct qemu_syscall *call);
void qemu_NtCreateNamedPipeFile(struct qemu_syscall *call);
void qemu_NtDeleteFile(struct qemu_syscall *call);
void qemu_NtDeviceIoControlFile(struct qemu_syscall *call);
void qemu_NtFlushBuffersFile(struct qemu_syscall *call);
void qemu_NtFsControlFile(struct qemu_syscall *call);
void qemu_NtLockFile(struct qemu_syscall *call);
void qemu_NtNotifyChangeDirectoryFile(struct qemu_syscall *call);
void qemu_NtOpenFile(struct qemu_syscall *call);
void qemu_NtQueryAttributesFile(struct qemu_syscall *call);
void qemu_NtQueryEaFile(struct qemu_syscall *call);
void qemu_NtQueryFullAttributesFile(struct qemu_syscall *call);
void qemu_NtQueryInformationFile(struct qemu_syscall *call);
void qemu_NtQueryVolumeInformationFile(struct qemu_syscall *call);
void qemu_NtReadFile(struct qemu_syscall *call);
void qemu_NtReadFileScatter(struct qemu_syscall *call);
void qemu_NtSetEaFile(struct qemu_syscall *call);
void qemu_NtSetInformationFile(struct qemu_syscall *call);
void qemu_NtSetVolumeInformationFile(struct qemu_syscall *call);
void qemu_NtUnlockFile(struct qemu_syscall *call);
void qemu_NtWriteFile(struct qemu_syscall *call);
void qemu_NtWriteFileGather(struct qemu_syscall *call);
void qemu_RtlAcquirePebLock(struct qemu_syscall *call);
void qemu_RtlAcquireResourceExclusive(struct qemu_syscall *call);
void qemu_RtlAcquireResourceShared(struct qemu_syscall *call);
void qemu_RtlAddFunctionTable(struct qemu_syscall *call);
void qemu_RtlAreAllAccessesGranted(struct qemu_syscall *call);
void qemu_RtlAreAnyAccessesGranted(struct qemu_syscall *call);
void qemu_RtlAssert(struct qemu_syscall *call);
void qemu_RtlCaptureContext(struct qemu_syscall *call);
void qemu_RtlCompareMemory(struct qemu_syscall *call);
void qemu_RtlCompareMemoryUlong(struct qemu_syscall *call);
void qemu_RtlCompressBuffer(struct qemu_syscall *call);
void qemu_RtlComputeCrc32(struct qemu_syscall *call);
void qemu_RtlCopyLuid(struct qemu_syscall *call);
void qemu_RtlCopyLuidAndAttributesArray(struct qemu_syscall *call);
void qemu_RtlCopyMemory(struct qemu_syscall *call);
void qemu_RtlCreateUserProcess(struct qemu_syscall *call);
void qemu_RtlDecodePointer(struct qemu_syscall *call);
void qemu_RtlDecompressBuffer(struct qemu_syscall *call);
void qemu_RtlDecompressFragment(struct qemu_syscall *call);
void qemu_RtlDeleteCriticalSection(struct qemu_syscall *call);
void qemu_RtlDeleteResource(struct qemu_syscall *call);
void qemu_RtlDeleteSecurityObject(struct qemu_syscall *call);
void qemu_RtlDumpResource(struct qemu_syscall *call);
void qemu_RtlEncodePointer(struct qemu_syscall *call);
void qemu_RtlEnterCriticalSection(struct qemu_syscall *call);
void qemu_RtlEqualLuid(struct qemu_syscall *call);
void qemu_RtlFillMemory(struct qemu_syscall *call);
void qemu_RtlFillMemoryUlong(struct qemu_syscall *call);
void qemu_RtlFirstEntrySList(struct qemu_syscall *call);
void qemu_RtlGetCompressionWorkSpaceSize(struct qemu_syscall *call);
void qemu_RtlGetCurrentProcessorNumberEx(struct qemu_syscall *call);
void qemu_RtlGetCurrentTransaction(struct qemu_syscall *call);
void qemu_RtlGetThreadErrorMode(struct qemu_syscall *call);
void qemu_RtlInitializeCriticalSectionEx(struct qemu_syscall *call);
void qemu_RtlInitializeGenericTable(struct qemu_syscall *call);
void qemu_RtlInitializeGenericTableAvl(struct qemu_syscall *call);
void qemu_RtlInitializeResource(struct qemu_syscall *call);
void qemu_RtlInitializeSListHead(struct qemu_syscall *call);
void qemu_RtlInsertElementGenericTableAvl(struct qemu_syscall *call);
void qemu_RtlInterlockedFlushSList(struct qemu_syscall *call);
void qemu_RtlInterlockedPopEntrySList(struct qemu_syscall *call);
void qemu_RtlInterlockedPushEntrySList(struct qemu_syscall *call);
void qemu_RtlInterlockedPushListSList(struct qemu_syscall *call);
void qemu_RtlInterlockedPushListSListEx(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringA(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringExA(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringExW(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringW(struct qemu_syscall *call);
void qemu_RtlIpv4StringToAddressExW(struct qemu_syscall *call);
void qemu_RtlLeaveCriticalSection(struct qemu_syscall *call);
void qemu_RtlLookupFunctionEntry(struct qemu_syscall *call);
void qemu_RtlMapGenericMask(struct qemu_syscall *call);
void qemu_RtlMoveMemory(struct qemu_syscall *call);
void qemu_RtlNewSecurityObject(struct qemu_syscall *call);
void qemu_RtlQueryDepthSList(struct qemu_syscall *call);
void qemu_RtlRandom(struct qemu_syscall *call);
void qemu_RtlReleasePebLock(struct qemu_syscall *call);
void qemu_RtlReleaseResource(struct qemu_syscall *call);
void qemu_RtlSetCurrentTransaction(struct qemu_syscall *call);
void qemu_RtlSetThreadErrorMode(struct qemu_syscall *call);
void qemu_RtlUniform(struct qemu_syscall *call);
void qemu_RtlVirtualUnwind(struct qemu_syscall *call);
void qemu_RtlZeroMemory(struct qemu_syscall *call);
void qemu_strcat(struct qemu_syscall *call);
void qemu_strchr(struct qemu_syscall *call);
void qemu_strcmp(struct qemu_syscall *call);
void qemu_strcpy(struct qemu_syscall *call);
void qemu_strcspn(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);
void qemu_strncat(struct qemu_syscall *call);
void qemu_strncmp(struct qemu_syscall *call);
void qemu_strncpy(struct qemu_syscall *call);
void qemu_strpbrk(struct qemu_syscall *call);
void qemu_strrchr(struct qemu_syscall *call);
void qemu_strspn(struct qemu_syscall *call);
void qemu_strstr(struct qemu_syscall *call);
void qemu_strtol(struct qemu_syscall *call);
void qemu_strtoul(struct qemu_syscall *call);
void qemu_tolower(struct qemu_syscall *call);
void qemu_toupper(struct qemu_syscall *call);
void qemu_wcsrchr(struct qemu_syscall *call);

WCHAR *(* CDECL p_wcsrchr)(WCHAR *str, WCHAR ch);
void * (* CDECL p_memchr)(const void *ptr, int c, size_t n);
int (* CDECL p_memcmp)(const void *ptr1, const void *ptr2, size_t n);
void * (* CDECL p_memcpy)(void *dst, const void *src, size_t n);
void * (* CDECL p_memmove)(void *dst, const void *src, size_t n);
void * (* CDECL p_memset)(void *dst, int c, size_t n);
char * (* CDECL p_strcat)(char *dst, const char *src);
char * (* CDECL p_strchr)(const char *str, int c);
int (* CDECL p_strcmp)(const char *str1, const char *str2);
char * (* CDECL p_strcpy)(char *dst, const char *src);
size_t (* CDECL p_strcspn)(const char *str, const char *reject);
size_t (* CDECL p_strlen)(const char *str);
char * (* CDECL p_strncat)(char *dst, const char *src, size_t len);
int (* CDECL p_strncmp)(const char *str1, const char *str2, size_t len);
char * (* CDECL p_strncpy)(char *dst, const char *src, size_t len);
char * (* CDECL p_strpbrk)(const char *str, const char *accept);
char * (* CDECL p_strrchr)(const char *str, int c);
size_t (* CDECL p_strspn)(const char *str, const char *accept);
char * (* CDECL p_strstr)(const char *haystack, const char *needle);
void * (* CDECL p__memccpy)(void *dst, const void *src, int c, size_t n);
INT (* CDECL p__memicmp)(LPCSTR s1, LPCSTR s2, DWORD len);
int (* CDECL p__stricmp)(LPCSTR str1, LPCSTR str2);
int (* CDECL p__strnicmp)(LPCSTR str1, LPCSTR str2, size_t n);
LPSTR (* CDECL p__strupr)(LPSTR str);
LPSTR (* CDECL p__strlwr)(LPSTR str);
int (* CDECL p_tolower)(int c);
int (* CDECL p_toupper)(int c);
int (* CDECL p_isalnum)(int c);
int (* CDECL p_isalpha)(int c);
int (* CDECL p_iscntrl)(int c);
int (* CDECL p_isdigit)(int c);
int (* CDECL p_isgraph)(int c);
int (* CDECL p_islower)(int c);
int (* CDECL p_isprint)(int c);
int (* CDECL p_ispunct)(int c);
int (* CDECL p_isspace)(int c);
int (* CDECL p_isupper)(int c);
int (* CDECL p_isxdigit)(int c);
int (* CDECL p___isascii)(int c);
int (* CDECL p___toascii)(int c);
int (* CDECL p___iscsym)(int c);
int (* CDECL p___iscsymf)(int c);
int (* CDECL p__toupper)(int c);
int (* CDECL p__tolower)(int c);
LONG (* CDECL p_strtol)(const char *nptr, char **endptr, int base);
ULONG (* CDECL p_strtoul)(const char *nptr, char **endptr, int base);
char * (* CDECL p__ultoa)(ULONG value, char *str, int radix);
char * (* CDECL p__ltoa)(LONG value, char *str, int radix);
char * (* CDECL p__itoa)(int value, char *str, int radix);
char * (* CDECL p__ui64toa)(ULONGLONG value, char *str, int radix);
char * (* CDECL p__i64toa)(LONGLONG value, char *str, int radix);
LONGLONG (* CDECL p__atoi64)(const char *str);
int (* CDECL p_atoi)(const char *nptr);
LONG (* CDECL p_atol)(const char *nptr);
void (* CDECL p__splitpath)(const char* inpath, char * drv, char * dir, char* fname, char * ext);

#endif

#endif
