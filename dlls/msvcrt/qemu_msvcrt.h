#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

enum msvcrt_calls
{
    CALL____LC_CODEPAGE_FUNC = 0,
    CALL____LC_COLLATE_CP_FUNC,
    CALL____LC_HANDLE_FUNC,
    CALL____LC_LOCALE_NAME_FUNC,
    CALL____MB_CUR_MAX_FUNC,
    CALL____MB_CUR_MAX_L_FUNC,
    CALL____SETLC_ACTIVE_FUNC,
    CALL____UNGUARDED_READLC_ACTIVE_ADD_FUNC,
    CALL___ACRT_IOB_FUNC,
    CALL___CLEAN_TYPE_INFO_NAMES_INTERNAL,
    CALL___CONTROL87_2,
    CALL___CRT_DEBUGGER_HOOK,
    CALL___CRTCOMPARESTRINGA,
    CALL___CRTCOMPARESTRINGW,
    CALL___CRTGETLOCALEINFOEX,
    CALL___CRTGETLOCALEINFOW,
    CALL___CRTGETSTRINGTYPEW,
    CALL___CRTLCMAPSTRINGA,
    CALL___CRTLCMAPSTRINGW,
    CALL___CXXFRAMEHANDLER,
    CALL___DOSERRNO,
    CALL___FPE_FLT_ROUNDS,
    CALL___FPECODE,
    CALL___GETMAINARGS,
    CALL___IOB_FUNC,
    CALL___ISASCII,
    CALL___ISCSYM,
    CALL___ISCSYMF,
    CALL___LCONV_INIT,
    CALL___LIBM_SSE2_ACOS,
    CALL___LIBM_SSE2_ACOSF,
    CALL___LIBM_SSE2_ASIN,
    CALL___LIBM_SSE2_ASINF,
    CALL___LIBM_SSE2_ATAN,
    CALL___LIBM_SSE2_ATAN2,
    CALL___LIBM_SSE2_ATANF,
    CALL___LIBM_SSE2_COS,
    CALL___LIBM_SSE2_COSF,
    CALL___LIBM_SSE2_EXP,
    CALL___LIBM_SSE2_EXPF,
    CALL___LIBM_SSE2_LOG,
    CALL___LIBM_SSE2_LOG10,
    CALL___LIBM_SSE2_LOG10F,
    CALL___LIBM_SSE2_LOGF,
    CALL___LIBM_SSE2_POW,
    CALL___LIBM_SSE2_POWF,
    CALL___LIBM_SSE2_SIN,
    CALL___LIBM_SSE2_SINF,
    CALL___LIBM_SSE2_SQRT_PRECISE,
    CALL___LIBM_SSE2_TAN,
    CALL___LIBM_SSE2_TANF,
    CALL___P___MB_CUR_MAX,
    CALL___P__AMBLKSIZ,
    CALL___P__DAYLIGHT,
    CALL___P__DSTBIAS,
    CALL___P__ENVIRON,
    CALL___P__MBCTYPE,
    CALL___P__PCTYPE,
    CALL___P__TIMEZONE,
    CALL___P__TZNAME,
    CALL___P__WENVIRON,
    CALL___PCTYPE_FUNC,
    CALL___SET_APP_TYPE,
    CALL___SETUSERMATHERR,
    CALL___STRINGTOLD,
    CALL___SYS_ERRLIST,
    CALL___SYS_NERR,
    CALL___TOASCII,
    CALL___UNCAUGHT_EXCEPTION,
    CALL___UNDNAME,
    CALL___UNDNAMEEX,
    CALL___WCSERROR,
    CALL___WCSERROR_S,
    CALL___WGETMAINARGS,
    CALL__ABS64,
    CALL__ACCESS,
    CALL__ACCESS_S,
    CALL__ALIGNED_FREE,
    CALL__ALIGNED_MALLOC,
    CALL__ALIGNED_MSIZE,
    CALL__ALIGNED_OFFSET_MALLOC,
    CALL__ALIGNED_OFFSET_REALLOC,
    CALL__ALIGNED_REALLOC,
    CALL__AMSG_EXIT,
    CALL__ASSERT,
    CALL__ATODBL,
    CALL__ATODBL_L,
    CALL__ATOF_L,
    CALL__ATOFLT,
    CALL__ATOFLT_L,
    CALL__ATOLDBL,
    CALL__ATOLL_L,
    CALL__BEGINTHREAD,
    CALL__BEGINTHREADEX,
    CALL__CABS,
    CALL__CALLNEWH,
    CALL__CALLOC_BASE,
    CALL__CEXIT,
    CALL__CGETS,
    CALL__CHDIR,
    CALL__CHDRIVE,
    CALL__CHGSIGN,
    CALL__CHGSIGNF,
    CALL__CHMOD,
    CALL__CHSIZE,
    CALL__CHSIZE_S,
    CALL__CLEARFP,
    CALL__CLOSE,
    CALL__COMMIT,
    CALL__CONFIGTHREADLOCALE,
    CALL__CONFIGURE_NARROW_ARGV,
    CALL__CONFIGURE_WIDE_ARGV,
    CALL__CONTROL87,
    CALL__CONTROLFP,
    CALL__CONTROLFP_S,
    CALL__COPYSIGN,
    CALL__COPYSIGNF,
    CALL__CPUTS,
    CALL__CPUTWS,
    CALL__CREAT,
    CALL__CREATE_LOCALE,
    CALL__CRTTERMINATEPROCESS,
    CALL__CTIME32,
    CALL__CTIME32_S,
    CALL__CTIME64,
    CALL__CTIME64_S,
    CALL__CURRENTSCHEDULER__GET,
    CALL__CURRENTSCHEDULER__GETNUMBEROFVIRTUALPROCESSORS,
    CALL__CURRENTSCHEDULER__ID,
    CALL__CWAIT,
    CALL__CXXTHROWEXCEPTION,
    CALL__DCLASS,
    CALL__DIFFTIME32,
    CALL__DIFFTIME64,
    CALL__DPCOMP,
    CALL__DSIGN,
    CALL__DTEST,
    CALL__DUP,
    CALL__DUP2,
    CALL__DUPENV_S,
    CALL__ECVT,
    CALL__ECVT_S,
    CALL__ENCODED_NULL,
    CALL__ENDTHREAD,
    CALL__ENDTHREADEX,
    CALL__EOF,
    CALL__ERRNO,
    CALL__EXECV,
    CALL__EXECVE,
    CALL__EXECVP,
    CALL__EXECVPE,
    CALL__EXIT,
    CALL__EXPAND,
    CALL__FCLOSE_NOLOCK,
    CALL__FCLOSEALL,
    CALL__FCVT,
    CALL__FCVT_S,
    CALL__FDCLASS,
    CALL__FDOPEN,
    CALL__FDPCOMP,
    CALL__FDSIGN,
    CALL__FDTEST,
    CALL__FFLUSH_NOLOCK,
    CALL__FGETC_NOLOCK,
    CALL__FGETCHAR,
    CALL__FGETWC_NOLOCK,
    CALL__FGETWCHAR,
    CALL__FILBUF,
    CALL__FILELENGTH,
    CALL__FILELENGTHI64,
    CALL__FILENO,
    CALL__FINDCLOSE,
    CALL__FINDFIRST,
    CALL__FINDFIRST32,
    CALL__FINDFIRST64,
    CALL__FINDFIRST64I32,
    CALL__FINDFIRSTI64,
    CALL__FINDNEXT,
    CALL__FINDNEXT32,
    CALL__FINDNEXT64,
    CALL__FINDNEXT64I32,
    CALL__FINDNEXTI64,
    CALL__FINITE,
    CALL__FINITEF,
    CALL__FLSBUF,
    CALL__FLUSHALL,
    CALL__FPCLASS,
    CALL__FPRESET,
    CALL__FPUTC_NOLOCK,
    CALL__FPUTCHAR,
    CALL__FPUTWC_NOLOCK,
    CALL__FPUTWCHAR,
    CALL__FREAD_NOLOCK,
    CALL__FREAD_NOLOCK_S,
    CALL__FREE_BASE,
    CALL__FREE_LOCALE,
    CALL__FSEEK_NOLOCK,
    CALL__FSEEKI64,
    CALL__FSEEKI64_NOLOCK,
    CALL__FSOPEN,
    CALL__FSTAT,
    CALL__FSTAT32,
    CALL__FSTAT32I64,
    CALL__FSTAT64,
    CALL__FSTAT64I32,
    CALL__FSTATI64,
    CALL__FTELL_NOLOCK,
    CALL__FTELLI64,
    CALL__FTELLI64_NOLOCK,
    CALL__FTIME,
    CALL__FTIME32,
    CALL__FTIME32_S,
    CALL__FTIME64,
    CALL__FTIME64_S,
    CALL__FULLPATH,
    CALL__FUTIME,
    CALL__FUTIME32,
    CALL__FUTIME64,
    CALL__FWRITE_NOLOCK,
    CALL__GCVT,
    CALL__GCVT_S,
    CALL__GET_CURRENT_LOCALE,
    CALL__GET_DAYLIGHT,
    CALL__GET_DOSERRNO,
    CALL__GET_DSTBIAS,
    CALL__GET_ERRNO,
    CALL__GET_FMODE,
    CALL__GET_HEAP_HANDLE,
    CALL__GET_INITIAL_NARROW_ENVIRONMENT,
    CALL__GET_INITIAL_WIDE_ENVIRONMENT,
    CALL__GET_INVALID_PARAMETER_HANDLER,
    CALL__GET_NARROW_WINMAIN_COMMAND_LINE,
    CALL__GET_OSFHANDLE,
    CALL__GET_OSPLATFORM,
    CALL__GET_PGMPTR,
    CALL__GET_PRINTF_COUNT_OUTPUT,
    CALL__GET_SBH_THRESHOLD,
    CALL__GET_STREAM_BUFFER_POINTERS,
    CALL__GET_THREAD_LOCAL_INVALID_PARAMETER_HANDLER,
    CALL__GET_TIMEZONE,
    CALL__GET_TZNAME,
    CALL__GET_WIDE_WINMAIN_COMMAND_LINE,
    CALL__GET_WPGMPTR,
    CALL__GETCH,
    CALL__GETCH_NOLOCK,
    CALL__GETCHE,
    CALL__GETCHE_NOLOCK,
    CALL__GETCONCURRENCY,
    CALL__GETCWD,
    CALL__GETDAYS,
    CALL__GETDCWD,
    CALL__GETDISKFREE,
    CALL__GETDLLPROCADDR,
    CALL__GETDRIVE,
    CALL__GETMAXSTDIO,
    CALL__GETMBCP,
    CALL__GETMONTHS,
    CALL__GETPID,
    CALL__GETPTD,
    CALL__GETTNAMES,
    CALL__GETW,
    CALL__GETWCH,
    CALL__GETWCH_NOLOCK,
    CALL__GETWCHE,
    CALL__GETWCHE_NOLOCK,
    CALL__GETWS,
    CALL__GMTIME32,
    CALL__GMTIME32_S,
    CALL__GMTIME64,
    CALL__GMTIME64_S,
    CALL__HEAPADD,
    CALL__HEAPCHK,
    CALL__HEAPMIN,
    CALL__HEAPSET,
    CALL__HEAPWALK,
    CALL__HYPOT,
    CALL__HYPOTF,
    CALL__I64TOA_S,
    CALL__I64TOW_S,
    CALL__INITIALIZE_NARROW_ENVIRONMENT,
    CALL__INITIALIZE_WIDE_ENVIRONMENT,
    CALL__INVALID_PARAMETER_NOINFO,
    CALL__INVALID_PARAMETER_NOINFO_NORETURN,
    CALL__ISALNUM_L,
    CALL__ISALPHA_L,
    CALL__ISATTY,
    CALL__ISBLANK_L,
    CALL__ISCNTRL_L,
    CALL__ISCTYPE,
    CALL__ISCTYPE_L,
    CALL__ISDIGIT_L,
    CALL__ISGRAPH_L,
    CALL__ISLEADBYTE_L,
    CALL__ISLOWER_L,
    CALL__ISMBBKANA,
    CALL__ISMBBLEAD,
    CALL__ISMBBLEAD_L,
    CALL__ISMBBTRAIL,
    CALL__ISMBCALNUM,
    CALL__ISMBCALPHA,
    CALL__ISMBCDIGIT,
    CALL__ISMBCGRAPH,
    CALL__ISMBCHIRA,
    CALL__ISMBCKATA,
    CALL__ISMBCLEGAL,
    CALL__ISMBCLOWER,
    CALL__ISMBCPRINT,
    CALL__ISMBCPUNCT,
    CALL__ISMBCSPACE,
    CALL__ISMBCSYMBOL,
    CALL__ISMBCUPPER,
    CALL__ISMBSLEAD,
    CALL__ISMBSTRAIL,
    CALL__ISNAN,
    CALL__ISNANF,
    CALL__ISPRINT_L,
    CALL__ISSPACE_L,
    CALL__ISUPPER_L,
    CALL__ISWALPHA_L,
    CALL__ISWBLANK_L,
    CALL__ISWCTYPE_L,
    CALL__ISWDIGIT_L,
    CALL__ISWPUNCT_L,
    CALL__ISWSPACE_L,
    CALL__ISXDIGIT_L,
    CALL__ITOA,
    CALL__ITOA_S,
    CALL__ITOW_S,
    CALL__J0,
    CALL__J1,
    CALL__JN,
    CALL__KBHIT,
    CALL__LDCLASS,
    CALL__LDTEST,
    CALL__LOADDLL,
    CALL__LOCALTIME32,
    CALL__LOCALTIME32_S,
    CALL__LOCALTIME64,
    CALL__LOCALTIME64_S,
    CALL__LOCK,
    CALL__LOCK_FILE,
    CALL__LOCK_LOCALES,
    CALL__LOCK_SHARED_PTR_SPIN_LOCK,
    CALL__LOCKING,
    CALL__LOGB,
    CALL__LOGBF,
    CALL__LROTL,
    CALL__LROTR,
    CALL__LSEEK,
    CALL__LSEEKI64,
    CALL__LTOA_S,
    CALL__LTOW_S,
    CALL__MAKEPATH,
    CALL__MAKEPATH_S,
    CALL__MALLOC_BASE,
    CALL__MATHERR,
    CALL__MBBTOMBC,
    CALL__MBBTYPE,
    CALL__MBCCPY,
    CALL__MBCJISTOJMS,
    CALL__MBCJMSTOJIS,
    CALL__MBCLEN,
    CALL__MBCTOHIRA,
    CALL__MBCTOKATA,
    CALL__MBCTOLOWER,
    CALL__MBCTOMBB,
    CALL__MBCTOUPPER,
    CALL__MBSBTYPE,
    CALL__MBSCAT,
    CALL__MBSCAT_S,
    CALL__MBSCAT_S_L,
    CALL__MBSCHR,
    CALL__MBSCMP,
    CALL__MBSCOLL,
    CALL__MBSCOLL_L,
    CALL__MBSCPY,
    CALL__MBSCPY_S,
    CALL__MBSCPY_S_L,
    CALL__MBSCSPN,
    CALL__MBSDEC,
    CALL__MBSICMP,
    CALL__MBSICOLL,
    CALL__MBSICOLL_L,
    CALL__MBSINC,
    CALL__MBSLEN,
    CALL__MBSLWR,
    CALL__MBSLWR_S,
    CALL__MBSNBCAT,
    CALL__MBSNBCAT_S,
    CALL__MBSNBCMP,
    CALL__MBSNBCNT,
    CALL__MBSNBCOLL,
    CALL__MBSNBCOLL_L,
    CALL__MBSNBCPY,
    CALL__MBSNBCPY_S,
    CALL__MBSNBCPY_S_L,
    CALL__MBSNBICMP,
    CALL__MBSNBICOLL,
    CALL__MBSNBICOLL_L,
    CALL__MBSNBSET,
    CALL__MBSNCAT,
    CALL__MBSNCCNT,
    CALL__MBSNCMP,
    CALL__MBSNCPY,
    CALL__MBSNEXTC,
    CALL__MBSNICMP,
    CALL__MBSNINC,
    CALL__MBSNSET,
    CALL__MBSPBRK,
    CALL__MBSRCHR,
    CALL__MBSREV,
    CALL__MBSSET,
    CALL__MBSSPN,
    CALL__MBSSPNP,
    CALL__MBSSTR,
    CALL__MBSTOK,
    CALL__MBSTOK_L,
    CALL__MBSTOK_S,
    CALL__MBSTOK_S_L,
    CALL__MBSTOWCS_L,
    CALL__MBSTOWCS_S_L,
    CALL__MBSTRLEN,
    CALL__MBSTRLEN_L,
    CALL__MBSUPR,
    CALL__MBSUPR_S,
    CALL__MKDIR,
    CALL__MKGMTIME,
    CALL__MKGMTIME32,
    CALL__MKGMTIME64,
    CALL__MKTEMP,
    CALL__MKTEMP_S,
    CALL__MKTIME32,
    CALL__MKTIME64,
    CALL__MSIZE,
    CALL__NEXTAFTER,
    CALL__NEXTAFTERF,
    CALL__ONEXIT,
    CALL__OPEN,
    CALL__OPEN_OSFHANDLE,
    CALL__PCLOSE,
    CALL__PIPE,
    CALL__POPEN,
    CALL__PURECALL,
    CALL__PUTCH,
    CALL__PUTCH_NOLOCK,
    CALL__PUTENV,
    CALL__PUTENV_S,
    CALL__PUTW,
    CALL__PUTWCH,
    CALL__PUTWCH_NOLOCK,
    CALL__PUTWS,
    CALL__QUERY_NEW_HANDLER,
    CALL__QUERY_NEW_MODE,
    CALL__READ,
    CALL__REALLOC_BASE,
    CALL__RECALLOC,
    CALL__RMDIR,
    CALL__RMTMP,
    CALL__ROTL,
    CALL__ROTL64,
    CALL__ROTR,
    CALL__ROTR64,
    CALL__SCALB,
    CALL__SCALBF,
    CALL__SEARCHENV,
    CALL__SEARCHENV_S,
    CALL__SET_CONTROLFP,
    CALL__SET_DOSERRNO,
    CALL__SET_ERRNO,
    CALL__SET_ERROR_MODE,
    CALL__SET_FMA3_ENABLE,
    CALL__SET_FMODE,
    CALL__SET_INVALID_PARAMETER_HANDLER,
    CALL__SET_NEW_HANDLER,
    CALL__SET_NEW_MODE,
    CALL__SET_PRINTF_COUNT_OUTPUT,
    CALL__SET_SBH_THRESHOLD,
    CALL__SET_SSE2_ENABLE,
    CALL__SET_THREAD_LOCAL_INVALID_PARAMETER_HANDLER,
    CALL__SETERRORMODE,
    CALL__SETJMP,
    CALL__SETMAXSTDIO,
    CALL__SETMBCP,
    CALL__SETMODE,
    CALL__SOPEN_DISPATCH,
    CALL__SOPEN_S,
    CALL__SPAWNV,
    CALL__SPAWNVE,
    CALL__SPAWNVP,
    CALL__SPAWNVPE,
    CALL__SPLITPATH,
    CALL__SPLITPATH_S,
    CALL__STAT32,
    CALL__STAT32I64,
    CALL__STAT64,
    CALL__STAT64I32,
    CALL__STATUSFP,
    CALL__STATUSFP2,
    CALL__STRDATE,
    CALL__STRDATE_S,
    CALL__STRDUP,
    CALL__STRERROR,
    CALL__STRFTIME,
    CALL__STRFTIME_L,
    CALL__STRICMP,
    CALL__STRICOLL,
    CALL__STRICOLL_L,
    CALL__STRLWR,
    CALL__STRLWR_L,
    CALL__STRLWR_S,
    CALL__STRLWR_S_L,
    CALL__STRNCOLL,
    CALL__STRNCOLL_L,
    CALL__STRNICMP,
    CALL__STRNICOLL,
    CALL__STRNICOLL_L,
    CALL__STRNSET,
    CALL__STRNSET_S,
    CALL__STRREV,
    CALL__STRSET,
    CALL__STRTIME,
    CALL__STRTIME_S,
    CALL__STRTOF_L,
    CALL__STRTOI64,
    CALL__STRTOI64_L,
    CALL__STRTOL_L,
    CALL__STRTOUI64,
    CALL__STRTOUI64_L,
    CALL__STRUPR,
    CALL__STRUPR_L,
    CALL__STRUPR_S,
    CALL__STRUPR_S_L,
    CALL__STRXFRM_L,
    CALL__SWAB,
    CALL__TELL,
    CALL__TELLI64,
    CALL__TEMPNAM,
    CALL__TIME32,
    CALL__TIME64,
    CALL__TOLOWER,
    CALL__TOLOWER_L,
    CALL__TOUPPER,
    CALL__TOUPPER_L,
    CALL__TOWLOWER_L,
    CALL__TOWUPPER_L,
    CALL__TZSET,
    CALL__UI64TOA_S,
    CALL__UI64TOW_S,
    CALL__ULTOA_S,
    CALL__ULTOW_S,
    CALL__UMASK,
    CALL__UNGETC_NOLOCK,
    CALL__UNGETCH,
    CALL__UNGETCH_NOLOCK,
    CALL__UNGETWC_NOLOCK,
    CALL__UNGETWCH,
    CALL__UNGETWCH_NOLOCK,
    CALL__UNLINK,
    CALL__UNLOADDLL,
    CALL__UNLOCK,
    CALL__UNLOCK_FILE,
    CALL__UNLOCK_LOCALES,
    CALL__UNLOCK_SHARED_PTR_SPIN_LOCK,
    CALL__UTIME,
    CALL__UTIME32,
    CALL__UTIME64,
    CALL__VSNPRINTF,
    CALL__VSNPRINTF_S,
    CALL__VSNWPRINTF,
    CALL__W_GETDAYS,
    CALL__W_GETMONTHS,
    CALL__W_GETTNAMES,
    CALL__WACCESS,
    CALL__WACCESS_S,
    CALL__WASCTIME,
    CALL__WASCTIME_S,
    CALL__WASSERT,
    CALL__WCHDIR,
    CALL__WCHMOD,
    CALL__WCREAT,
    CALL__WCREATE_LOCALE,
    CALL__WCSCOLL_L,
    CALL__WCSDUP,
    CALL__WCSERROR,
    CALL__WCSERROR_S,
    CALL__WCSFTIME,
    CALL__WCSFTIME_L,
    CALL__WCSICMP,
    CALL__WCSICMP_L,
    CALL__WCSICOLL,
    CALL__WCSICOLL_L,
    CALL__WCSLWR,
    CALL__WCSLWR_L,
    CALL__WCSLWR_S,
    CALL__WCSLWR_S_L,
    CALL__WCSNCOLL,
    CALL__WCSNCOLL_L,
    CALL__WCSNICMP,
    CALL__WCSNICMP_L,
    CALL__WCSNICOLL,
    CALL__WCSNICOLL_L,
    CALL__WCSNSET,
    CALL__WCSREV,
    CALL__WCSSET,
    CALL__WCSSET_S,
    CALL__WCSTOD_L,
    CALL__WCSTOF_L,
    CALL__WCSTOI64,
    CALL__WCSTOI64_L,
    CALL__WCSTOL_L,
    CALL__WCSTOMBS_L,
    CALL__WCSTOMBS_S_L,
    CALL__WCSTOUI64,
    CALL__WCSTOUI64_L,
    CALL__WCSTOUL_L,
    CALL__WCSUPR_L,
    CALL__WCSUPR_S,
    CALL__WCSUPR_S_L,
    CALL__WCSXFRM_L,
    CALL__WCTIME,
    CALL__WCTIME32,
    CALL__WCTIME32_S,
    CALL__WCTIME64,
    CALL__WCTIME64_S,
    CALL__WCTOMB_L,
    CALL__WCTOMB_S_L,
    CALL__WDUPENV_S,
    CALL__WEXECV,
    CALL__WEXECVE,
    CALL__WEXECVP,
    CALL__WEXECVPE,
    CALL__WFDOPEN,
    CALL__WFINDFIRST,
    CALL__WFINDFIRST32,
    CALL__WFINDFIRST64,
    CALL__WFINDFIRST64I32,
    CALL__WFINDFIRSTI64,
    CALL__WFINDNEXT,
    CALL__WFINDNEXT32,
    CALL__WFINDNEXT64,
    CALL__WFINDNEXT64I32,
    CALL__WFINDNEXTI64,
    CALL__WFOPEN,
    CALL__WFOPEN_S,
    CALL__WFREOPEN,
    CALL__WFREOPEN_S,
    CALL__WFSOPEN,
    CALL__WFULLPATH,
    CALL__WGETCWD,
    CALL__WGETDCWD,
    CALL__WGETENV,
    CALL__WGETENV_S,
    CALL__WMAKEPATH,
    CALL__WMAKEPATH_S,
    CALL__WMKDIR,
    CALL__WMKTEMP,
    CALL__WMKTEMP_S,
    CALL__WPERROR,
    CALL__WPOPEN,
    CALL__WPUTENV,
    CALL__WPUTENV_S,
    CALL__WREMOVE,
    CALL__WRENAME,
    CALL__WRITE,
    CALL__WRMDIR,
    CALL__WSEARCHENV,
    CALL__WSEARCHENV_S,
    CALL__WSETLOCALE,
    CALL__WSOPEN_DISPATCH,
    CALL__WSOPEN_S,
    CALL__WSPAWNV,
    CALL__WSPAWNVE,
    CALL__WSPAWNVP,
    CALL__WSPAWNVPE,
    CALL__WSPLITPATH,
    CALL__WSPLITPATH_S,
    CALL__WSTAT,
    CALL__WSTAT32,
    CALL__WSTAT32I64,
    CALL__WSTAT64,
    CALL__WSTAT64I32,
    CALL__WSTATI64,
    CALL__WSTRDATE,
    CALL__WSTRDATE_S,
    CALL__WSTRTIME,
    CALL__WSTRTIME_S,
    CALL__WSYSTEM,
    CALL__WTEMPNAM,
    CALL__WTMPNAM,
    CALL__WTMPNAM_S,
    CALL__WTOF,
    CALL__WTOF_L,
    CALL__WTOI,
    CALL__WTOI64,
    CALL__WTOI64_L,
    CALL__WTOI_L,
    CALL__WTOL,
    CALL__WTOL_L,
    CALL__WTOLL,
    CALL__WTOLL_L,
    CALL__WUNLINK,
    CALL__WUTIME,
    CALL__WUTIME32,
    CALL__WUTIME64,
    CALL__XCPTFILTER,
    CALL__Y0,
    CALL__Y1,
    CALL__YN,
    CALL_ABORT,
    CALL_ABS,
    CALL_ACOS,
    CALL_ACOSF,
    CALL_ACOSH,
    CALL_ACOSHF,
    CALL_ACOSHL,
    CALL_ASCTIME,
    CALL_ASCTIME_S,
    CALL_ASIN,
    CALL_ASINF,
    CALL_ASINH,
    CALL_ASINHF,
    CALL_ASINHL,
    CALL_ATAN,
    CALL_ATAN2,
    CALL_ATAN2F,
    CALL_ATANF,
    CALL_ATANH,
    CALL_ATANHF,
    CALL_ATANHL,
    CALL_ATOF,
    CALL_ATOI,
    CALL_ATOLL,
    CALL_BSEARCH,
    CALL_BTOWC,
    CALL_CALLOC,
    CALL_CBRT,
    CALL_CBRTF,
    CALL_CBRTL,
    CALL_CEIL,
    CALL_CEILF,
    CALL_CLEARERR,
    CALL_CLOCK,
    CALL_CONCURRENCY_ALLOC,
    CALL_CONCURRENCY_FREE,
    CALL_CONTEXT__SPINYIELD,
    CALL_CONTEXT_BLOCK,
    CALL_CONTEXT_CURRENTCONTEXT,
    CALL_CONTEXT_ID,
    CALL_CONTEXT_ISCURRENTTASKCOLLECTIONCANCELING,
    CALL_CONTEXT_OVERSUBSCRIBE,
    CALL_CONTEXT_SCHEDULEGROUPID,
    CALL_CONTEXT_VIRTUALPROCESSORID,
    CALL_CONTEXT_YIELD,
    CALL_COS,
    CALL_COSF,
    CALL_COSH,
    CALL_COSHF,
    CALL_CTIME,
    CALL_CURRENTSCHEDULER_CREATE,
    CALL_CURRENTSCHEDULER_CREATESCHEDULEGROUP,
    CALL_CURRENTSCHEDULER_DETACH,
    CALL_CURRENTSCHEDULER_GET,
    CALL_CURRENTSCHEDULER_GETNUMBEROFVIRTUALPROCESSORS,
    CALL_CURRENTSCHEDULER_GETPOLICY,
    CALL_CURRENTSCHEDULER_ID,
    CALL_CURRENTSCHEDULER_ISAVAILABLELOCATION,
    CALL_CURRENTSCHEDULER_REGISTERSHUTDOWNEVENT,
    CALL_DECODE_POINTER,
    CALL_DIFFTIME,
    CALL_DIV,
    CALL_ENCODE_POINTER,
    CALL_ERF,
    CALL_ERFC,
    CALL_ERFCF,
    CALL_ERFCL,
    CALL_ERFF,
    CALL_ERFL,
    CALL_EVENT_WAIT_FOR_MULTIPLE,
    CALL_EXIT,
    CALL_EXP,
    CALL_EXP2,
    CALL_EXP2F,
    CALL_EXP2L,
    CALL_EXPF,
    CALL_EXPM1,
    CALL_EXPM1F,
    CALL_EXPM1L,
    CALL_FABS,
    CALL_FABSF,
    CALL_FCLOSE,
    CALL_FEGETENV,
    CALL_FEGETROUND,
    CALL_FEOF,
    CALL_FERROR,
    CALL_FESETENV,
    CALL_FESETROUND,
    CALL_FFLUSH,
    CALL_FGETC,
    CALL_FGETPOS,
    CALL_FGETS,
    CALL_FGETWC,
    CALL_FGETWS,
    CALL_FLOOR,
    CALL_FLOORF,
    CALL_FMAX,
    CALL_FMAXF,
    CALL_FMIN,
    CALL_FMINF,
    CALL_FMOD,
    CALL_FMODF,
    CALL_FOPEN,
    CALL_FOPEN_S,
    CALL_FPRINTF,
    CALL_FPRINTF_UCRTBASE,
    CALL_FPUTC,
    CALL_FPUTS,
    CALL_FPUTWC,
    CALL_FPUTWS,
    CALL_FREAD,
    CALL_FREAD_S,
    CALL_FREE,
    CALL_FREOPEN,
    CALL_FREOPEN_S,
    CALL_FREXP,
    CALL_FREXPF,
    CALL_FSEEK,
    CALL_FSETPOS,
    CALL_FTELL,
    CALL_FWPRINTF,
    CALL_FWRITE,
    CALL_GENERIC_STUB,
    CALL_GETC,
    CALL_GETCHAR,
    CALL_GETENV,
    CALL_GETENV_S,
    CALL_GETGRGID,
    CALL_GETPWUID,
    CALL_GETS,
    CALL_GETWC,
    CALL_GETWCHAR,
    CALL_GMTIME,
    CALL_I10_OUTPUT,
    CALL_INIT_DLL,
    CALL_ISALNUM,
    CALL_ISALPHA,
    CALL_ISBLANK,
    CALL_ISCNTRL,
    CALL_ISDIGIT,
    CALL_ISGRAPH,
    CALL_ISLEADBYTE,
    CALL_ISLOWER,
    CALL_ISPRINT,
    CALL_ISPUNCT,
    CALL_ISSPACE,
    CALL_ISUPPER,
    CALL_ISWALNUM,
    CALL_ISWALPHA,
    CALL_ISWASCII,
    CALL_ISWBLANK,
    CALL_ISWCNTRL,
    CALL_ISWDIGIT,
    CALL_ISWGRAPH,
    CALL_ISWLOWER,
    CALL_ISWPRINT,
    CALL_ISWPUNCT,
    CALL_ISWSPACE,
    CALL_ISWUPPER,
    CALL_ISWXDIGIT,
    CALL_ISXDIGIT,
    CALL_LABS,
    CALL_LDEXP,
    CALL_LDIV,
    CALL_LGAMMA,
    CALL_LGAMMAF,
    CALL_LGAMMAL,
    CALL_LLABS,
    CALL_LLRINT,
    CALL_LLRINTF,
    CALL_LLRINTL,
    CALL_LLROUND,
    CALL_LLROUNDF,
    CALL_LLROUNDL,
    CALL_LOCALECONV,
    CALL_LOCALTIME,
    CALL_LOG,
    CALL_LOG10,
    CALL_LOG10F,
    CALL_LOG1P,
    CALL_LOG1PF,
    CALL_LOG1PL,
    CALL_LOG2,
    CALL_LOG2F,
    CALL_LOG2L,
    CALL_LOGF,
    CALL_LONGJMP,
    CALL_LRINT,
    CALL_LRINTF,
    CALL_LRINTL,
    CALL_LROUND,
    CALL_LROUNDF,
    CALL_LROUNDL,
    CALL_MALLOC,
    CALL_MBLEN,
    CALL_MBRLEN,
    CALL_MBRTOWC,
    CALL_MBSRTOWCS,
    CALL_MBSRTOWCS_S,
    CALL_MBSTOWCS,
    CALL_MBSTOWCS_S,
    CALL_MBTOWC,
    CALL_MBTOWC_L,
    CALL_MEMCHR,
    CALL_MEMCMP,
    CALL_MEMCPY,
    CALL_MEMCPY_S,
    CALL_MEMMOVE,
    CALL_MEMMOVE_S,
    CALL_MEMSET,
    CALL_MKTIME,
    CALL_MODF,
    CALL_MODFF,
    CALL_NAN,
    CALL_NANF,
    CALL_NEARBYINT,
    CALL_NEARBYINTF,
    CALL_OPERATOR_DELETE,
    CALL_OPERATOR_NEW,
    CALL_OPERATOR_NEW_DBG,
    CALL_PERROR,
    CALL_POW,
    CALL_POWF,
    CALL_PRINTF,
    CALL_PUTC,
    CALL_PUTCHAR,
    CALL_PUTS,
    CALL_QSORT,
    CALL_RAISE,
    CALL_RAND,
    CALL_REALLOC,
    CALL_REALPATH,
    CALL_REMAINDER,
    CALL_REMAINDERF,
    CALL_REMAINDERL,
    CALL_REMOVE,
    CALL_RENAME,
    CALL_REWIND,
    CALL_RINT,
    CALL_RINTF,
    CALL_RINTL,
    CALL_ROUND,
    CALL_ROUNDF,
    CALL_ROUNDL,
    CALL_SCALBNL,
    CALL_SCHEDULER_CREATE,
    CALL_SCHEDULER_RESETDEFAULTSCHEDULERPOLICY,
    CALL_SCHEDULER_SETDEFAULTSCHEDULERPOLICY,
    CALL_SET_NEW_HANDLER,
    CALL_SETBUF,
    CALL_SETLOCALE,
    CALL_SETVBUF,
    CALL_SIGNAL,
    CALL_SIN,
    CALL_SINF,
    CALL_SINH,
    CALL_SINHF,
    CALL_SNWSCANF,
    CALL_SPINCOUNT__VALUE,
    CALL_SPRINTF,
    CALL_SPRINTF_S,
    CALL_SPRINTF_UCRTBASE,
    CALL_SQRT,
    CALL_SQRTF,
    CALL_SRAND,
    CALL_STAT,
    CALL_STATI64,
    CALL_STRCAT_S,
    CALL_STRCHR,
    CALL_STRCMP,
    CALL_STRCOLL,
    CALL_STRCOLL_L,
    CALL_STRCPY,
    CALL_STRCPY_S,
    CALL_STRERROR,
    CALL_STRERROR_S,
    CALL_STRFTIME,
    CALL_STRLEN,
    CALL_STRNCAT,
    CALL_STRNCAT_S,
    CALL_STRNCMP,
    CALL_STRNCPY,
    CALL_STRNCPY_S,
    CALL_STRNLEN,
    CALL_STRRCHR,
    CALL_STRSTR,
    CALL_STRTOD,
    CALL_STRTOD_L,
    CALL_STRTOF,
    CALL_STRTOK,
    CALL_STRTOK_S,
    CALL_STRTOL,
    CALL_STRTOUL,
    CALL_STRTOUL_L,
    CALL_STRXFRM,
    CALL_SWPRINTF_S,
    CALL_SWPRINTF_UCRTBASE,
    CALL_SWSCANF_S,
    CALL_SYSTEM,
    CALL_TAN,
    CALL_TANF,
    CALL_TANH,
    CALL_TANHF,
    CALL_TERMINATE,
    CALL_TIME,
    CALL_TMPFILE,
    CALL_TMPFILE_S,
    CALL_TMPNAM,
    CALL_TMPNAM_S,
    CALL_TOLOWER,
    CALL_TOUPPER,
    CALL_TOWLOWER,
    CALL_TOWUPPER,
    CALL_TRUNC,
    CALL_TRUNCF,
    CALL_TRUNCL,
    CALL_TYPE_INFO_DTOR,
    CALL_UNGETC,
    CALL_UNGETWC,
    CALL_VFSCANF,
    CALL_VSNSCANF,
    CALL_VSSCANF,
    CALL_VSSCANF_S,
    CALL_VSSCANF_UCRTBASE,
    CALL_WCRTOMB,
    CALL_WCSCAT_S,
    CALL_WCSCHR,
    CALL_WCSCOLL,
    CALL_WCSCPY,
    CALL_WCSCPY_S,
    CALL_WCSFTIME,
    CALL_WCSLEN,
    CALL_WCSNCAT_S,
    CALL_WCSNCMP,
    CALL_WCSNCPY,
    CALL_WCSNCPY_S,
    CALL_WCSNLEN,
    CALL_WCSPBRK,
    CALL_WCSRTOMBS,
    CALL_WCSRTOMBS_S,
    CALL_WCSSTR,
    CALL_WCSTOD,
    CALL_WCSTOF,
    CALL_WCSTOK,
    CALL_WCSTOK_S,
    CALL_WCSTOMBS,
    CALL_WCSTOMBS_S,
    CALL_WCSTOUL,
    CALL_WCSXFRM,
    CALL_WCTOB,
    CALL_WCTOMB,
    CALL_WCTOMB_S,
    CALL_WMEMCPY_S,
    CALL_WMEMMOVE_S,
    CALL_WPRINTF,
};

typedef int (__cdecl *MSVCRT__onexit_t)(void);
typedef void (__cdecl *MSVCRT__se_translator_function)(unsigned int code, struct _EXCEPTION_POINTERS *info);

struct MSVCRT__complex
{
    double x;      /* Real part */
    double y;      /* Imaginary part */
};

typedef struct
{
    unsigned int control;
    unsigned int status;
} MSVCRT_fenv_t;

struct MSVCRT__iobuf {
  char* _ptr;
  int   _cnt;
  char* _base;
  int   _flag;
  int   _file;
  int   _charbuf;
  int   _bufsiz;
  char* _tmpfname;
};

typedef struct MSVCRT__iobuf MSVCRT_FILE;

typedef void *MSVCRT__locale_t;
struct MSVCRT__stat64i32;
struct MSVCRT__stat64;
struct MSVCRT__stat32;
struct MSVCRT__stat32i64;
struct MSVCRT__stat;
struct MSVCRT__stati64;
struct MSVCRT__utimbuf64;
struct MSVCRT__utimbuf32;
struct MSVCRT__finddata_t;
struct MSVCRT__finddata32_t;
struct MSVCRT__wfinddata_t;
struct MSVCRT__wfinddata32_t;
struct MSVCRT__finddatai64_t;
struct MSVCRT___finddata64_t;
struct MSVCRT__wfinddata64_t;
struct MSVCRT__finddata64i32_t;
struct MSVCRT__wfinddata64i32_t;
struct MSVCRT__wfinddatai64_t;
struct MSVCRT__diskfree_t;
typedef unsigned short MSVCRT_wint_t;
typedef void *MSVCRT_invalid_parameter_handler;
typedef void *MSVCRT__beginthread_start_routine_t;
typedef void *MSVCRT__beginthreadex_start_routine_t;
typedef void Context;
typedef void Scheduler, _Scheduler;
typedef void SchedulerPolicy;
typedef void *malloc_func_t, *free_func_t;
typedef void MSVCRT_mbstate_t;
typedef unsigned short MSVCRT_wctype_t;
struct MSVCRT_tm;
typedef void MSVCRT___lc_time_data;
typedef int MSVCRT___time32_t;
typedef __int64 DECLSPEC_ALIGN(8) MSVCRT___time64_t;
typedef int MSVCRT_clock_t;
struct MSVCRT___timeb64;
struct MSVCRT___timeb32;
typedef void *MSVCRT_new_handler_func;
struct MSVCRT__heapinfo;
struct _I10_OUTPUT_DATA;

typedef struct _frame_info
{
    void *object;
    struct _frame_info *next;
} frame_info;

typedef struct
{
    frame_info frame_info;
    EXCEPTION_RECORD *rec;
    void *unk;
} cxx_frame_info;

/* TODO: Keep in sync with wine/dlls/msvcrt up to thread_errno.
 *
 * TODO 2: One day we will run into a 32 bit application that accesses
 * members directly. At that point we don't be able to just pass the host's
 * version of the structure through and will have to create a proper copy
 * and update members. There's hope though that this won't happen until
 * we can make a proper PE build of Wine's msvcrt and ditch this wrapper. */
struct __thread_data
{
    DWORD                           tid;
    HANDLE                          handle;
    int                             thread_errno;
    MSVCRT__se_translator_function  se_translator;
    EXCEPTION_RECORD               *exc_record;
    frame_info                     *frame_info_head;
};

typedef struct __thread_data thread_data_t;
extern thread_data_t *msvcrt_get_thread_data(void);

#ifdef QEMU_DLL_GUEST

extern char *MSVCRT__acmdln;
extern WCHAR *MSVCRT__wcmdln;
extern char **MSVCRT__environ;
extern int MSVCRT___mb_cur_max;
void msvcrt_data_init(double huge, int argc, char **argv, wchar_t **wargv);

CDECL void _amsg_exit(int errnum);
char * CDECL MSVCRT__strdup(const char *str);
void * CDECL MSVCRT_calloc(size_t item_count,size_t size);
int * CDECL MSVCRT__errno(void);
CDECL DECLSPEC_NORETURN void __MINGW_NOTHROW MSVCRT_exit(int code);
void CDECL MSVCRT_free(void *ptr);
void * CDECL MSVCRT_malloc(size_t size);
void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size);
void * CDECL MSVCRT_realloc(void *ptr, size_t size);
char * CDECL MSVCRT_strcmp(const char *str1, const char *str2);
size_t CDECL MSVCRT_strlen(const char *str);
void CDECL MSVCRT_terminate(void);
void CDECL MSVCRT_operator_delete(void *mem);
int WINAPIV MSVCRT_sprintf(char *str, const char *format, ...);

unsigned int count_printf_argsA(const char *format, char *fmts);
unsigned int count_printf_argsW(const WCHAR *format, WCHAR *fmts);

#define GUEST_IOB_SIZE 20
extern FILE guest_iob[GUEST_IOB_SIZE];

#ifdef _WIN64

#define __ASM_NAME(name) name
#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl " #name suffix "\n\t.def " #name suffix "; .scl 2; .type 32; .endef\n" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)
#define __ASM_CFI(str) str

#else

#define __ASM_NAME(name) "_" name
#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl _" #name suffix "\n\t.def _" #name suffix "; .scl 2; .type 32; .endef\n_" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)
#define __ASM_CFI(str) str

#endif

#else

extern const struct qemu_ops *qemu_ops;

void qemu____lc_codepage_func(struct qemu_syscall *call);
void qemu____lc_collate_cp_func(struct qemu_syscall *call);
void qemu____lc_handle_func(struct qemu_syscall *call);
void qemu____lc_locale_name_func(struct qemu_syscall *call);
void qemu____mb_cur_max_func(struct qemu_syscall *call);
void qemu____mb_cur_max_l_func(struct qemu_syscall *call);
void qemu____setlc_active_func(struct qemu_syscall *call);
void qemu____unguarded_readlc_active_add_func(struct qemu_syscall *call);
void qemu___acrt_iob_func(struct qemu_syscall *c);
void qemu___clean_type_info_names_internal(struct qemu_syscall *call);
void qemu___control87_2(struct qemu_syscall *call);
void qemu___crt_debugger_hook(struct qemu_syscall *call);
void qemu___crtCompareStringA(struct qemu_syscall *call);
void qemu___crtCompareStringW(struct qemu_syscall *call);
void qemu___crtGetLocaleInfoEx(struct qemu_syscall *call);
void qemu___crtGetLocaleInfoW(struct qemu_syscall *call);
void qemu___crtGetStringTypeW(struct qemu_syscall *call);
void qemu___crtLCMapStringA(struct qemu_syscall *call);
void qemu___crtLCMapStringW(struct qemu_syscall *call);
void qemu___cxxframehandler(struct qemu_syscall *call);
void qemu___doserrno(struct qemu_syscall *call);
void qemu___fpe_flt_rounds(struct qemu_syscall *call);
void qemu___fpecode(struct qemu_syscall *call);
void qemu___getmainargs(struct qemu_syscall *call);
void qemu___iob_func(struct qemu_syscall *call);
void qemu___isascii(struct qemu_syscall *call);
void qemu___iscsym(struct qemu_syscall *call);
void qemu___iscsymf(struct qemu_syscall *call);
void qemu___lconv_init(struct qemu_syscall *call);
void qemu___libm_sse2_acos(struct qemu_syscall *call);
void qemu___libm_sse2_acosf(struct qemu_syscall *call);
void qemu___libm_sse2_asin(struct qemu_syscall *call);
void qemu___libm_sse2_asinf(struct qemu_syscall *call);
void qemu___libm_sse2_atan(struct qemu_syscall *call);
void qemu___libm_sse2_atan2(struct qemu_syscall *call);
void qemu___libm_sse2_atanf(struct qemu_syscall *call);
void qemu___libm_sse2_cos(struct qemu_syscall *call);
void qemu___libm_sse2_cosf(struct qemu_syscall *call);
void qemu___libm_sse2_exp(struct qemu_syscall *call);
void qemu___libm_sse2_expf(struct qemu_syscall *call);
void qemu___libm_sse2_log(struct qemu_syscall *call);
void qemu___libm_sse2_log10(struct qemu_syscall *call);
void qemu___libm_sse2_log10f(struct qemu_syscall *call);
void qemu___libm_sse2_logf(struct qemu_syscall *call);
void qemu___libm_sse2_pow(struct qemu_syscall *call);
void qemu___libm_sse2_powf(struct qemu_syscall *call);
void qemu___libm_sse2_sin(struct qemu_syscall *call);
void qemu___libm_sse2_sinf(struct qemu_syscall *call);
void qemu___libm_sse2_sqrt_precise(struct qemu_syscall *call);
void qemu___libm_sse2_tan(struct qemu_syscall *call);
void qemu___libm_sse2_tanf(struct qemu_syscall *call);
void qemu___p___mb_cur_max(struct qemu_syscall *call);
void qemu___p__amblksiz(struct qemu_syscall *call);
void qemu___p__daylight(struct qemu_syscall *call);
void qemu___p__dstbias(struct qemu_syscall *call);
void qemu___p__environ(struct qemu_syscall *call);
void qemu___p__mbctype(struct qemu_syscall *call);
void qemu___p__pctype(struct qemu_syscall *call);
void qemu___p__timezone(struct qemu_syscall *call);
void qemu___p__tzname(struct qemu_syscall *call);
void qemu___p__wenviron(struct qemu_syscall *call);
void qemu___pctype_func(struct qemu_syscall *call);
void qemu___set_app_type(struct qemu_syscall *call);
void qemu___setusermatherr(struct qemu_syscall *call);
void qemu___STRINGTOLD(struct qemu_syscall *call);
void qemu___sys_errlist(struct qemu_syscall *call);
void qemu___sys_nerr(struct qemu_syscall *call);
void qemu___toascii(struct qemu_syscall *call);
void qemu___uncaught_exception(struct qemu_syscall *call);
void qemu___unDName(struct qemu_syscall *call);
void qemu___unDNameEx(struct qemu_syscall *call);
void qemu___wcserror(struct qemu_syscall *call);
void qemu___wcserror_s(struct qemu_syscall *call);
void qemu___wgetmainargs(struct qemu_syscall *call);
void qemu__abs64(struct qemu_syscall *call);
void qemu__access(struct qemu_syscall *c);
void qemu__access_s(struct qemu_syscall *c);
void qemu__aligned_free(struct qemu_syscall *call);
void qemu__aligned_malloc(struct qemu_syscall *call);
void qemu__aligned_msize(struct qemu_syscall *call);
void qemu__aligned_offset_malloc(struct qemu_syscall *call);
void qemu__aligned_offset_realloc(struct qemu_syscall *call);
void qemu__aligned_realloc(struct qemu_syscall *call);
void qemu__amsg_exit(struct qemu_syscall *call);
void qemu__assert(struct qemu_syscall *call);
void qemu__atodbl(struct qemu_syscall *call);
void qemu__atodbl_l(struct qemu_syscall *call);
void qemu__atof_l(struct qemu_syscall *call);
void qemu__atoflt(struct qemu_syscall *call);
void qemu__atoflt_l(struct qemu_syscall *call);
void qemu__atoldbl(struct qemu_syscall *call);
void qemu__atoll_l(struct qemu_syscall *call);
void qemu__beginthread(struct qemu_syscall *call);
void qemu__beginthreadex(struct qemu_syscall *call);
void qemu__cabs(struct qemu_syscall *call);
void qemu__callnewh(struct qemu_syscall *call);
void qemu__calloc_base(struct qemu_syscall *call);
void qemu__cexit(struct qemu_syscall *call);
void qemu__cgets(struct qemu_syscall *call);
void qemu__chdir(struct qemu_syscall *call);
void qemu__chdrive(struct qemu_syscall *call);
void qemu__chgsign(struct qemu_syscall *call);
void qemu__chgsignf(struct qemu_syscall *call);
void qemu__chmod(struct qemu_syscall *c);
void qemu__chsize(struct qemu_syscall *c);
void qemu__chsize_s(struct qemu_syscall *c);
void qemu__clearfp(struct qemu_syscall *call);
void qemu__close(struct qemu_syscall *c);
void qemu__commit(struct qemu_syscall *c);
void qemu__configthreadlocale(struct qemu_syscall *call);
void qemu__configure_narrow_argv(struct qemu_syscall *call);
void qemu__configure_wide_argv(struct qemu_syscall *call);
void qemu__control87(struct qemu_syscall *call);
void qemu__controlfp(struct qemu_syscall *call);
void qemu__controlfp_s(struct qemu_syscall *call);
void qemu__copysign(struct qemu_syscall *call);
void qemu__copysignf(struct qemu_syscall *call);
void qemu__cputs(struct qemu_syscall *call);
void qemu__cputws(struct qemu_syscall *call);
void qemu__creat(struct qemu_syscall *c);
void qemu__create_locale(struct qemu_syscall *call);
void qemu__crtTerminateProcess(struct qemu_syscall *call);
void qemu__ctime32(struct qemu_syscall *call);
void qemu__ctime32_s(struct qemu_syscall *call);
void qemu__ctime64(struct qemu_syscall *call);
void qemu__ctime64_s(struct qemu_syscall *call);
void qemu__CurrentScheduler__Get(struct qemu_syscall *call);
void qemu__CurrentScheduler__GetNumberOfVirtualProcessors(struct qemu_syscall *call);
void qemu__CurrentScheduler__Id(struct qemu_syscall *call);
void qemu__cwait(struct qemu_syscall *call);
void qemu__CxxThrowException(struct qemu_syscall *c);
void qemu__dclass(struct qemu_syscall *call);
void qemu__difftime32(struct qemu_syscall *call);
void qemu__difftime64(struct qemu_syscall *call);
void qemu__dpcomp(struct qemu_syscall *call);
void qemu__dsign(struct qemu_syscall *call);
void qemu__dtest(struct qemu_syscall *call);
void qemu__dup(struct qemu_syscall *c);
void qemu__dup2(struct qemu_syscall *c);
void qemu__dupenv_s(struct qemu_syscall *call);
void qemu__ecvt(struct qemu_syscall *call);
void qemu__ecvt_s(struct qemu_syscall *call);
void qemu__encoded_null(struct qemu_syscall *call);
void qemu__endthread(struct qemu_syscall *call);
void qemu__endthreadex(struct qemu_syscall *call);
void qemu__eof(struct qemu_syscall *c);
void qemu__errno(struct qemu_syscall *call);
void qemu__execv(struct qemu_syscall *call);
void qemu__execve(struct qemu_syscall *call);
void qemu__execvp(struct qemu_syscall *call);
void qemu__execvpe(struct qemu_syscall *call);
void qemu__exit(struct qemu_syscall *call);
void qemu__expand(struct qemu_syscall *call);
void qemu__fclose_nolock(struct qemu_syscall *c);
void qemu__fcloseall(struct qemu_syscall *c);
void qemu__fcvt(struct qemu_syscall *call);
void qemu__fcvt_s(struct qemu_syscall *call);
void qemu__fdclass(struct qemu_syscall *call);
void qemu__fdopen(struct qemu_syscall *c);
void qemu__fdpcomp(struct qemu_syscall *call);
void qemu__fdsign(struct qemu_syscall *call);
void qemu__fdtest(struct qemu_syscall *call);
void qemu__fflush_nolock(struct qemu_syscall *c);
void qemu__fgetc_nolock(struct qemu_syscall *c);
void qemu__fgetchar(struct qemu_syscall *c);
void qemu__fgetwc_nolock(struct qemu_syscall *c);
void qemu__fgetwchar(struct qemu_syscall *c);
void qemu__filbuf(struct qemu_syscall *c);
void qemu__filelength(struct qemu_syscall *c);
void qemu__filelengthi64(struct qemu_syscall *c);
void qemu__fileno(struct qemu_syscall *call);
void qemu__findclose(struct qemu_syscall *call);
void qemu__findfirst(struct qemu_syscall *call);
void qemu__findfirst32(struct qemu_syscall *call);
void qemu__findfirst64(struct qemu_syscall *call);
void qemu__findfirst64i32(struct qemu_syscall *call);
void qemu__findfirsti64(struct qemu_syscall *call);
void qemu__findnext(struct qemu_syscall *call);
void qemu__findnext32(struct qemu_syscall *call);
void qemu__findnext64(struct qemu_syscall *call);
void qemu__findnext64i32(struct qemu_syscall *call);
void qemu__findnexti64(struct qemu_syscall *call);
void qemu__finite(struct qemu_syscall *call);
void qemu__finitef(struct qemu_syscall *call);
void qemu__flsbuf(struct qemu_syscall *c);
void qemu__flushall(struct qemu_syscall *c);
void qemu__fpclass(struct qemu_syscall *call);
void qemu__fpreset(struct qemu_syscall *call);
void qemu__fputc_nolock(struct qemu_syscall *c);
void qemu__fputchar(struct qemu_syscall *c);
void qemu__fputwc_nolock(struct qemu_syscall *c);
void qemu__fputwchar(struct qemu_syscall *c);
void qemu__fread_nolock(struct qemu_syscall *c);
void qemu__fread_nolock_s(struct qemu_syscall *c);
void qemu__free_base(struct qemu_syscall *call);
void qemu__free_locale(struct qemu_syscall *call);
void qemu__fseek_nolock(struct qemu_syscall *c);
void qemu__fseeki64(struct qemu_syscall *c);
void qemu__fseeki64_nolock(struct qemu_syscall *c);
void qemu__fsopen(struct qemu_syscall *c);
void qemu__fstat(struct qemu_syscall *c);
void qemu__fstat32(struct qemu_syscall *c);
void qemu__fstat32i64(struct qemu_syscall *c);
void qemu__fstat64(struct qemu_syscall *c);
void qemu__fstat64i32(struct qemu_syscall *c);
void qemu__fstati64(struct qemu_syscall *c);
void qemu__ftell_nolock(struct qemu_syscall *c);
void qemu__ftelli64(struct qemu_syscall *c);
void qemu__ftelli64_nolock(struct qemu_syscall *c);
void qemu__ftime(struct qemu_syscall *call);
void qemu__ftime(struct qemu_syscall *call);
void qemu__ftime32(struct qemu_syscall *call);
void qemu__ftime32_s(struct qemu_syscall *call);
void qemu__ftime64(struct qemu_syscall *call);
void qemu__ftime64_s(struct qemu_syscall *call);
void qemu__fullpath(struct qemu_syscall *call);
void qemu__futime(struct qemu_syscall *c);
void qemu__futime32(struct qemu_syscall *c);
void qemu__futime64(struct qemu_syscall *c);
void qemu__fwrite_nolock(struct qemu_syscall *c);
void qemu__gcvt(struct qemu_syscall *call);
void qemu__gcvt_s(struct qemu_syscall *call);
void qemu__get_current_locale(struct qemu_syscall *call);
void qemu__get_daylight(struct qemu_syscall *call);
void qemu__get_doserrno(struct qemu_syscall *call);
void qemu__get_dstbias(struct qemu_syscall *call);
void qemu__get_errno(struct qemu_syscall *call);
void qemu__get_fmode(struct qemu_syscall *call);
void qemu__get_heap_handle(struct qemu_syscall *call);
void qemu__get_initial_narrow_environment(struct qemu_syscall *call);
void qemu__get_initial_wide_environment(struct qemu_syscall *call);
void qemu__get_invalid_parameter_handler(struct qemu_syscall *call);
void qemu__get_narrow_winmain_command_line(struct qemu_syscall *call);
void qemu__get_osfhandle(struct qemu_syscall *c);
void qemu__get_osplatform(struct qemu_syscall *call);
void qemu__get_pgmptr(struct qemu_syscall *call);
void qemu__get_printf_count_output(struct qemu_syscall *call);
void qemu__get_sbh_threshold(struct qemu_syscall *call);
void qemu__get_stream_buffer_pointers(struct qemu_syscall *c);
void qemu__get_thread_local_invalid_parameter_handler(struct qemu_syscall *call);
void qemu__get_timezone(struct qemu_syscall *call);
void qemu__get_tzname(struct qemu_syscall *call);
void qemu__get_wide_winmain_command_line(struct qemu_syscall *call);
void qemu__get_wpgmptr(struct qemu_syscall *call);
void qemu__getch(struct qemu_syscall *call);
void qemu__getch_nolock(struct qemu_syscall *call);
void qemu__getche(struct qemu_syscall *call);
void qemu__getche_nolock(struct qemu_syscall *call);
void qemu__GetConcurrency(struct qemu_syscall *call);
void qemu__getcwd(struct qemu_syscall *call);
void qemu__Getdays(struct qemu_syscall *call);
void qemu__getdcwd(struct qemu_syscall *call);
void qemu__getdiskfree(struct qemu_syscall *call);
void qemu__getdllprocaddr(struct qemu_syscall *call);
void qemu__getdrive(struct qemu_syscall *call);
void qemu__getmaxstdio(struct qemu_syscall *c);
void qemu__getmbcp(struct qemu_syscall *call);
void qemu__Getmonths(struct qemu_syscall *call);
void qemu__getpid(struct qemu_syscall *call);
void qemu__getptd(struct qemu_syscall *call);
void qemu__Gettnames(struct qemu_syscall *call);
void qemu__getw(struct qemu_syscall *c);
void qemu__getwch(struct qemu_syscall *call);
void qemu__getwch_nolock(struct qemu_syscall *call);
void qemu__getwche(struct qemu_syscall *call);
void qemu__getwche_nolock(struct qemu_syscall *call);
void qemu__getws(struct qemu_syscall *c);
void qemu__gmtime32(struct qemu_syscall *call);
void qemu__gmtime32_s(struct qemu_syscall *call);
void qemu__gmtime64(struct qemu_syscall *call);
void qemu__gmtime64_s(struct qemu_syscall *call);
void qemu__heapadd(struct qemu_syscall *call);
void qemu__heapchk(struct qemu_syscall *call);
void qemu__heapmin(struct qemu_syscall *call);
void qemu__heapset(struct qemu_syscall *call);
void qemu__heapwalk(struct qemu_syscall *call);
void qemu__hypot(struct qemu_syscall *call);
void qemu__hypotf(struct qemu_syscall *call);
void qemu__i64toa_s(struct qemu_syscall *call);
void qemu__i64tow_s(struct qemu_syscall *call);
void qemu__initialize_narrow_environment(struct qemu_syscall *call);
void qemu__initialize_wide_environment(struct qemu_syscall *call);
void qemu__invalid_parameter_noinfo(struct qemu_syscall *call);
void qemu__invalid_parameter_noinfo_noreturn(struct qemu_syscall *call);
void qemu__isalnum_l(struct qemu_syscall *call);
void qemu__isalpha_l(struct qemu_syscall *call);
void qemu__isatty(struct qemu_syscall *call);
void qemu__isblank_l(struct qemu_syscall *call);
void qemu__iscntrl_l(struct qemu_syscall *call);
void qemu__isctype(struct qemu_syscall *call);
void qemu__isctype_l(struct qemu_syscall *call);
void qemu__isdigit_l(struct qemu_syscall *call);
void qemu__isgraph_l(struct qemu_syscall *call);
void qemu__isleadbyte_l(struct qemu_syscall *call);
void qemu__islower_l(struct qemu_syscall *call);
void qemu__ismbbkana(struct qemu_syscall *call);
void qemu__ismbblead(struct qemu_syscall *call);
void qemu__ismbblead_l(struct qemu_syscall *call);
void qemu__ismbbtrail(struct qemu_syscall *call);
void qemu__ismbcalnum(struct qemu_syscall *call);
void qemu__ismbcalpha(struct qemu_syscall *call);
void qemu__ismbcdigit(struct qemu_syscall *call);
void qemu__ismbcgraph(struct qemu_syscall *call);
void qemu__ismbchira(struct qemu_syscall *call);
void qemu__ismbckata(struct qemu_syscall *call);
void qemu__ismbclegal(struct qemu_syscall *call);
void qemu__ismbclower(struct qemu_syscall *call);
void qemu__ismbcprint(struct qemu_syscall *call);
void qemu__ismbcpunct(struct qemu_syscall *call);
void qemu__ismbcspace(struct qemu_syscall *call);
void qemu__ismbcsymbol(struct qemu_syscall *call);
void qemu__ismbcupper(struct qemu_syscall *call);
void qemu__ismbslead(struct qemu_syscall *call);
void qemu__ismbstrail(struct qemu_syscall *call);
void qemu__isnan(struct qemu_syscall *call);
void qemu__isnanf(struct qemu_syscall *call);
void qemu__isprint_l(struct qemu_syscall *call);
void qemu__isspace_l(struct qemu_syscall *call);
void qemu__isupper_l(struct qemu_syscall *call);
void qemu__iswalpha_l(struct qemu_syscall *call);
void qemu__iswblank_l(struct qemu_syscall *call);
void qemu__iswctype_l(struct qemu_syscall *call);
void qemu__iswdigit_l(struct qemu_syscall *call);
void qemu__iswpunct_l(struct qemu_syscall *call);
void qemu__iswspace_l(struct qemu_syscall *call);
void qemu__isxdigit_l(struct qemu_syscall *call);
void qemu__itoa(struct qemu_syscall *call);
void qemu__itoa_s(struct qemu_syscall *call);
void qemu__itow_s(struct qemu_syscall *call);
void qemu__j0(struct qemu_syscall *call);
void qemu__j1(struct qemu_syscall *call);
void qemu__jn(struct qemu_syscall *call);
void qemu__kbhit(struct qemu_syscall *call);
void qemu__ldclass(struct qemu_syscall *call);
void qemu__ldtest(struct qemu_syscall *call);
void qemu__loaddll(struct qemu_syscall *call);
void qemu__localtime32(struct qemu_syscall *call);
void qemu__localtime32_s(struct qemu_syscall *call);
void qemu__localtime64(struct qemu_syscall *call);
void qemu__localtime64_s(struct qemu_syscall *call);
void qemu__lock(struct qemu_syscall *call);
void qemu__lock_file(struct qemu_syscall *c);
void qemu__lock_locales(struct qemu_syscall *call);
void qemu__Lock_shared_ptr_spin_lock(struct qemu_syscall *call);
void qemu__locking(struct qemu_syscall *c);
void qemu__logb(struct qemu_syscall *call);
void qemu__logbf(struct qemu_syscall *call);
void qemu__lrotl(struct qemu_syscall *call);
void qemu__lrotr(struct qemu_syscall *call);
void qemu__lseek(struct qemu_syscall *call);
void qemu__lseeki64(struct qemu_syscall *call);
void qemu__ltoa_s(struct qemu_syscall *call);
void qemu__ltow_s(struct qemu_syscall *call);
void qemu__makepath(struct qemu_syscall *call);
void qemu__makepath_s(struct qemu_syscall *call);
void qemu__malloc_base(struct qemu_syscall *call);
void qemu__matherr(struct qemu_syscall *call);
void qemu__mbbtombc(struct qemu_syscall *call);
void qemu__mbbtype(struct qemu_syscall *call);
void qemu__mbccpy(struct qemu_syscall *call);
void qemu__mbcjistojms(struct qemu_syscall *call);
void qemu__mbcjmstojis(struct qemu_syscall *call);
void qemu__mbclen(struct qemu_syscall *call);
void qemu__mbctohira(struct qemu_syscall *call);
void qemu__mbctokata(struct qemu_syscall *call);
void qemu__mbctolower(struct qemu_syscall *call);
void qemu__mbctombb(struct qemu_syscall *call);
void qemu__mbctoupper(struct qemu_syscall *call);
void qemu__mbsbtype(struct qemu_syscall *call);
void qemu__mbscat(struct qemu_syscall *call);
void qemu__mbscat_s(struct qemu_syscall *call);
void qemu__mbscat_s_l(struct qemu_syscall *call);
void qemu__mbschr(struct qemu_syscall *call);
void qemu__mbscmp(struct qemu_syscall *call);
void qemu__mbscoll(struct qemu_syscall *call);
void qemu__mbscoll_l(struct qemu_syscall *call);
void qemu__mbscpy(struct qemu_syscall *call);
void qemu__mbscpy_s(struct qemu_syscall *call);
void qemu__mbscpy_s_l(struct qemu_syscall *call);
void qemu__mbscspn(struct qemu_syscall *call);
void qemu__mbsdec(struct qemu_syscall *call);
void qemu__mbsicmp(struct qemu_syscall *call);
void qemu__mbsicoll(struct qemu_syscall *call);
void qemu__mbsicoll_l(struct qemu_syscall *call);
void qemu__mbsinc(struct qemu_syscall *call);
void qemu__mbslen(struct qemu_syscall *call);
void qemu__mbslwr(struct qemu_syscall *call);
void qemu__mbslwr_s(struct qemu_syscall *call);
void qemu__mbsnbcat(struct qemu_syscall *call);
void qemu__mbsnbcat_s(struct qemu_syscall *call);
void qemu__mbsnbcmp(struct qemu_syscall *call);
void qemu__mbsnbcnt(struct qemu_syscall *call);
void qemu__mbsnbcoll(struct qemu_syscall *call);
void qemu__mbsnbcoll_l(struct qemu_syscall *call);
void qemu__mbsnbcpy(struct qemu_syscall *call);
void qemu__mbsnbcpy_s(struct qemu_syscall *call);
void qemu__mbsnbcpy_s_l(struct qemu_syscall *call);
void qemu__mbsnbicmp(struct qemu_syscall *call);
void qemu__mbsnbicoll(struct qemu_syscall *call);
void qemu__mbsnbicoll_l(struct qemu_syscall *call);
void qemu__mbsnbset(struct qemu_syscall *call);
void qemu__mbsncat(struct qemu_syscall *call);
void qemu__mbsnccnt(struct qemu_syscall *call);
void qemu__mbsncmp(struct qemu_syscall *call);
void qemu__mbsncpy(struct qemu_syscall *call);
void qemu__mbsnextc(struct qemu_syscall *call);
void qemu__mbsnicmp(struct qemu_syscall *call);
void qemu__mbsninc(struct qemu_syscall *call);
void qemu__mbsnset(struct qemu_syscall *call);
void qemu__mbspbrk(struct qemu_syscall *call);
void qemu__mbsrchr(struct qemu_syscall *call);
void qemu__mbsrev(struct qemu_syscall *call);
void qemu__mbsset(struct qemu_syscall *call);
void qemu__mbsspn(struct qemu_syscall *call);
void qemu__mbsspnp(struct qemu_syscall *call);
void qemu__mbsstr(struct qemu_syscall *call);
void qemu__mbstok(struct qemu_syscall *call);
void qemu__mbstok_l(struct qemu_syscall *call);
void qemu__mbstok_s(struct qemu_syscall *call);
void qemu__mbstok_s_l(struct qemu_syscall *call);
void qemu__mbstowcs_l(struct qemu_syscall *call);
void qemu__mbstowcs_s_l(struct qemu_syscall *call);
void qemu__mbstrlen(struct qemu_syscall *call);
void qemu__mbstrlen_l(struct qemu_syscall *call);
void qemu__mbsupr(struct qemu_syscall *call);
void qemu__mbsupr_s(struct qemu_syscall *call);
void qemu__mkdir(struct qemu_syscall *call);
void qemu__mkgmtime(struct qemu_syscall *call);
void qemu__mkgmtime(struct qemu_syscall *call);
void qemu__mkgmtime32(struct qemu_syscall *call);
void qemu__mkgmtime64(struct qemu_syscall *call);
void qemu__mktemp(struct qemu_syscall *c);
void qemu__mktemp_s(struct qemu_syscall *c);
void qemu__mktime32(struct qemu_syscall *call);
void qemu__mktime64(struct qemu_syscall *call);
void qemu__msize(struct qemu_syscall *call);
void qemu__nextafter(struct qemu_syscall *call);
void qemu__nextafterf(struct qemu_syscall *call);
void qemu__onexit(struct qemu_syscall *call);
void qemu__open(struct qemu_syscall *call);
void qemu__open_osfhandle(struct qemu_syscall *c);
void qemu__pclose(struct qemu_syscall *call);
void qemu__pipe(struct qemu_syscall *c);
void qemu__popen(struct qemu_syscall *call);
void qemu__purecall(struct qemu_syscall *call);
void qemu__putch(struct qemu_syscall *call);
void qemu__putch_nolock(struct qemu_syscall *call);
void qemu__putenv(struct qemu_syscall *call);
void qemu__putenv_s(struct qemu_syscall *call);
void qemu__putw(struct qemu_syscall *c);
void qemu__putwch(struct qemu_syscall *call);
void qemu__putwch_nolock(struct qemu_syscall *call);
void qemu__putws(struct qemu_syscall *c);
void qemu__query_new_handler(struct qemu_syscall *call);
void qemu__query_new_mode(struct qemu_syscall *call);
void qemu__read(struct qemu_syscall *c);
void qemu__realloc_base(struct qemu_syscall *call);
void qemu__recalloc(struct qemu_syscall *call);
void qemu__rmdir(struct qemu_syscall *call);
void qemu__rmtmp(struct qemu_syscall *c);
void qemu__rotl(struct qemu_syscall *call);
void qemu__rotl64(struct qemu_syscall *call);
void qemu__rotr(struct qemu_syscall *call);
void qemu__rotr64(struct qemu_syscall *call);
void qemu__scalb(struct qemu_syscall *call);
void qemu__scalbf(struct qemu_syscall *call);
void qemu__searchenv(struct qemu_syscall *call);
void qemu__searchenv_s(struct qemu_syscall *call);
void qemu__set_controlfp(struct qemu_syscall *call);
void qemu__set_doserrno(struct qemu_syscall *call);
void qemu__set_errno(struct qemu_syscall *call);
void qemu__set_error_mode(struct qemu_syscall *call);
void qemu__set_FMA3_enable(struct qemu_syscall *call);
void qemu__set_fmode(struct qemu_syscall *call);
void qemu__set_invalid_parameter_handler(struct qemu_syscall *call);
void qemu__set_new_handler(struct qemu_syscall *call);
void qemu__set_new_mode(struct qemu_syscall *call);
void qemu__set_printf_count_output(struct qemu_syscall *call);
void qemu__set_sbh_threshold(struct qemu_syscall *call);
void qemu__set_SSE2_enable(struct qemu_syscall *call);
void qemu__set_thread_local_invalid_parameter_handler(struct qemu_syscall *call);
void qemu__seterrormode(struct qemu_syscall *call);
void qemu__setjmp(struct qemu_syscall *call);
void qemu__setmaxstdio(struct qemu_syscall *c);
void qemu__setmbcp(struct qemu_syscall *call);
void qemu__setmode(struct qemu_syscall *c);
void qemu__sopen_dispatch(struct qemu_syscall *c);
void qemu__sopen_s(struct qemu_syscall *c);
void qemu__spawnv(struct qemu_syscall *call);
void qemu__spawnve(struct qemu_syscall *call);
void qemu__spawnvp(struct qemu_syscall *call);
void qemu__spawnvpe(struct qemu_syscall *call);
void qemu__splitpath(struct qemu_syscall *call);
void qemu__splitpath_s(struct qemu_syscall *call);
void qemu__stat32(struct qemu_syscall *c);
void qemu__stat32i64(struct qemu_syscall *c);
void qemu__stat64(struct qemu_syscall *c);
void qemu__stat64i32(struct qemu_syscall *c);
void qemu__statusfp(struct qemu_syscall *call);
void qemu__statusfp2(struct qemu_syscall *call);
void qemu__strdate(struct qemu_syscall *call);
void qemu__strdate_s(struct qemu_syscall *call);
void qemu__strdup(struct qemu_syscall *call);
void qemu__strerror(struct qemu_syscall *call);
void qemu__Strftime(struct qemu_syscall *call);
void qemu__strftime_l(struct qemu_syscall *call);
void qemu__stricmp(struct qemu_syscall *call);
void qemu__stricoll(struct qemu_syscall *call);
void qemu__stricoll_l(struct qemu_syscall *call);
void qemu__strlwr(struct qemu_syscall *call);
void qemu__strlwr_l(struct qemu_syscall *call);
void qemu__strlwr_s(struct qemu_syscall *call);
void qemu__strlwr_s_l(struct qemu_syscall *call);
void qemu__strncoll(struct qemu_syscall *call);
void qemu__strncoll_l(struct qemu_syscall *call);
void qemu__strnicmp(struct qemu_syscall *call);
void qemu__strnicoll(struct qemu_syscall *call);
void qemu__strnicoll_l(struct qemu_syscall *call);
void qemu__strnset(struct qemu_syscall *call);
void qemu__strnset_s(struct qemu_syscall *call);
void qemu__strrev(struct qemu_syscall *call);
void qemu__strset(struct qemu_syscall *call);
void qemu__strtime(struct qemu_syscall *call);
void qemu__strtime_s(struct qemu_syscall *call);
void qemu__strtof_l(struct qemu_syscall *call);
void qemu__strtoi64(struct qemu_syscall *call);
void qemu__strtoi64_l(struct qemu_syscall *call);
void qemu__strtol_l(struct qemu_syscall *call);
void qemu__strtoui64(struct qemu_syscall *call);
void qemu__strtoui64_l(struct qemu_syscall *call);
void qemu__strupr(struct qemu_syscall *call);
void qemu__strupr_l(struct qemu_syscall *call);
void qemu__strupr_s(struct qemu_syscall *call);
void qemu__strupr_s_l(struct qemu_syscall *call);
void qemu__strxfrm_l(struct qemu_syscall *call);
void qemu__swab(struct qemu_syscall *call);
void qemu__tell(struct qemu_syscall *c);
void qemu__telli64(struct qemu_syscall *c);
void qemu__tempnam(struct qemu_syscall *call);
void qemu__time32(struct qemu_syscall *call);
void qemu__time64(struct qemu_syscall *call);
void qemu__tolower(struct qemu_syscall *call);
void qemu__tolower_l(struct qemu_syscall *call);
void qemu__toupper(struct qemu_syscall *call);
void qemu__toupper_l(struct qemu_syscall *call);
void qemu__towlower_l(struct qemu_syscall *call);
void qemu__towupper_l(struct qemu_syscall *call);
void qemu__tzset(struct qemu_syscall *call);
void qemu__ui64toa_s(struct qemu_syscall *call);
void qemu__ui64tow_s(struct qemu_syscall *call);
void qemu__ultoa_s(struct qemu_syscall *call);
void qemu__ultow_s(struct qemu_syscall *call);
void qemu__umask(struct qemu_syscall *c);
void qemu__ungetc_nolock(struct qemu_syscall *c);
void qemu__ungetch(struct qemu_syscall *call);
void qemu__ungetch_nolock(struct qemu_syscall *call);
void qemu__ungetwc_nolock(struct qemu_syscall *c);
void qemu__ungetwch(struct qemu_syscall *call);
void qemu__ungetwch_nolock(struct qemu_syscall *call);
void qemu__unlink(struct qemu_syscall *c);
void qemu__unloaddll(struct qemu_syscall *call);
void qemu__unlock(struct qemu_syscall *call);
void qemu__unlock_file(struct qemu_syscall *c);
void qemu__unlock_locales(struct qemu_syscall *call);
void qemu__Unlock_shared_ptr_spin_lock(struct qemu_syscall *call);
void qemu__utime(struct qemu_syscall *c);
void qemu__utime32(struct qemu_syscall *c);
void qemu__utime64(struct qemu_syscall *c);
void qemu__W_Getdays(struct qemu_syscall *call);
void qemu__W_Getmonths(struct qemu_syscall *call);
void qemu__W_Gettnames(struct qemu_syscall *call);
void qemu__waccess(struct qemu_syscall *c);
void qemu__waccess_s(struct qemu_syscall *c);
void qemu__wasctime(struct qemu_syscall *call);
void qemu__wasctime_s(struct qemu_syscall *call);
void qemu__wassert(struct qemu_syscall *call);
void qemu__wchdir(struct qemu_syscall *call);
void qemu__wchmod(struct qemu_syscall *c);
void qemu__wcreat(struct qemu_syscall *c);
void qemu__wcreate_locale(struct qemu_syscall *call);
void qemu__wcscoll_l(struct qemu_syscall *call);
void qemu__wcsdup(struct qemu_syscall *call);
void qemu__wcserror(struct qemu_syscall *call);
void qemu__wcserror_s(struct qemu_syscall *call);
void qemu__Wcsftime(struct qemu_syscall *call);
void qemu__wcsftime_l(struct qemu_syscall *call);
void qemu__wcsicmp(struct qemu_syscall *call);
void qemu__wcsicmp_l(struct qemu_syscall *call);
void qemu__wcsicoll(struct qemu_syscall *call);
void qemu__wcsicoll_l(struct qemu_syscall *call);
void qemu__wcslwr(struct qemu_syscall *call);
void qemu__wcslwr_l(struct qemu_syscall *call);
void qemu__wcslwr_s(struct qemu_syscall *call);
void qemu__wcslwr_s_l(struct qemu_syscall *call);
void qemu__wcsncoll(struct qemu_syscall *call);
void qemu__wcsncoll_l(struct qemu_syscall *call);
void qemu__wcsnicmp(struct qemu_syscall *call);
void qemu__wcsnicmp_l(struct qemu_syscall *call);
void qemu__wcsnicoll(struct qemu_syscall *call);
void qemu__wcsnicoll_l(struct qemu_syscall *call);
void qemu__wcsnset(struct qemu_syscall *call);
void qemu__wcsrev(struct qemu_syscall *call);
void qemu__wcsset(struct qemu_syscall *call);
void qemu__wcsset_s(struct qemu_syscall *call);
void qemu__wcstod_l(struct qemu_syscall *call);
void qemu__wcstof_l(struct qemu_syscall *call);
void qemu__wcstoi64(struct qemu_syscall *call);
void qemu__wcstoi64_l(struct qemu_syscall *call);
void qemu__wcstol_l(struct qemu_syscall *call);
void qemu__wcstombs_l(struct qemu_syscall *call);
void qemu__wcstombs_s_l(struct qemu_syscall *call);
void qemu__wcstoui64(struct qemu_syscall *call);
void qemu__wcstoui64_l(struct qemu_syscall *call);
void qemu__wcstoul_l(struct qemu_syscall *call);
void qemu__wcsupr_l(struct qemu_syscall *call);
void qemu__wcsupr_s(struct qemu_syscall *call);
void qemu__wcsupr_s_l(struct qemu_syscall *call);
void qemu__wcsxfrm_l(struct qemu_syscall *call);
void qemu__wctime(struct qemu_syscall *call);
void qemu__wctime(struct qemu_syscall *call);
void qemu__wctime32(struct qemu_syscall *call);
void qemu__wctime32_s(struct qemu_syscall *call);
void qemu__wctime64(struct qemu_syscall *call);
void qemu__wctime64_s(struct qemu_syscall *call);
void qemu__wctomb_l(struct qemu_syscall *call);
void qemu__wctomb_s_l(struct qemu_syscall *call);
void qemu__wdupenv_s(struct qemu_syscall *call);
void qemu__wexecv(struct qemu_syscall *call);
void qemu__wexecve(struct qemu_syscall *call);
void qemu__wexecvp(struct qemu_syscall *call);
void qemu__wexecvpe(struct qemu_syscall *call);
void qemu__wfdopen(struct qemu_syscall *c);
void qemu__wfindfirst(struct qemu_syscall *call);
void qemu__wfindfirst32(struct qemu_syscall *call);
void qemu__wfindfirst64(struct qemu_syscall *call);
void qemu__wfindfirst64i32(struct qemu_syscall *call);
void qemu__wfindfirsti64(struct qemu_syscall *call);
void qemu__wfindnext(struct qemu_syscall *call);
void qemu__wfindnext32(struct qemu_syscall *call);
void qemu__wfindnext64(struct qemu_syscall *call);
void qemu__wfindnext64i32(struct qemu_syscall *call);
void qemu__wfindnexti64(struct qemu_syscall *call);
void qemu__wfopen(struct qemu_syscall *c);
void qemu__wfopen_s(struct qemu_syscall *c);
void qemu__wfreopen(struct qemu_syscall *c);
void qemu__wfreopen_s(struct qemu_syscall *c);
void qemu__wfsopen(struct qemu_syscall *c);
void qemu__wfullpath(struct qemu_syscall *call);
void qemu__wgetcwd(struct qemu_syscall *call);
void qemu__wgetdcwd(struct qemu_syscall *call);
void qemu__wgetenv(struct qemu_syscall *call);
void qemu__wgetenv_s(struct qemu_syscall *call);
void qemu__wmakepath(struct qemu_syscall *call);
void qemu__wmakepath_s(struct qemu_syscall *call);
void qemu__wmkdir(struct qemu_syscall *call);
void qemu__wmktemp(struct qemu_syscall *c);
void qemu__wmktemp_s(struct qemu_syscall *c);
void qemu__wperror(struct qemu_syscall *call);
void qemu__wpopen(struct qemu_syscall *call);
void qemu__wputenv(struct qemu_syscall *call);
void qemu__wputenv_s(struct qemu_syscall *call);
void qemu__wremove(struct qemu_syscall *c);
void qemu__wrename(struct qemu_syscall *c);
void qemu__write(struct qemu_syscall *call);
void qemu__wrmdir(struct qemu_syscall *call);
void qemu__wsearchenv(struct qemu_syscall *call);
void qemu__wsearchenv_s(struct qemu_syscall *call);
void qemu__wsetlocale(struct qemu_syscall *call);
void qemu__wsopen_dispatch(struct qemu_syscall *c);
void qemu__wsopen_s(struct qemu_syscall *c);
void qemu__wspawnv(struct qemu_syscall *call);
void qemu__wspawnve(struct qemu_syscall *call);
void qemu__wspawnvp(struct qemu_syscall *call);
void qemu__wspawnvpe(struct qemu_syscall *call);
void qemu__wsplitpath(struct qemu_syscall *call);
void qemu__wsplitpath_s(struct qemu_syscall *call);
void qemu__wstat(struct qemu_syscall *c);
void qemu__wstat32(struct qemu_syscall *c);
void qemu__wstat32i64(struct qemu_syscall *c);
void qemu__wstat64(struct qemu_syscall *c);
void qemu__wstat64i32(struct qemu_syscall *c);
void qemu__wstati64(struct qemu_syscall *c);
void qemu__wstrdate(struct qemu_syscall *call);
void qemu__wstrdate_s(struct qemu_syscall *call);
void qemu__wstrtime(struct qemu_syscall *call);
void qemu__wstrtime_s(struct qemu_syscall *call);
void qemu__wsystem(struct qemu_syscall *call);
void qemu__wtempnam(struct qemu_syscall *c);
void qemu__wtmpnam(struct qemu_syscall *c);
void qemu__wtmpnam_s(struct qemu_syscall *c);
void qemu__wtof(struct qemu_syscall *call);
void qemu__wtof_l(struct qemu_syscall *call);
void qemu__wtoi(struct qemu_syscall *call);
void qemu__wtoi64(struct qemu_syscall *call);
void qemu__wtoi64_l(struct qemu_syscall *call);
void qemu__wtoi_l(struct qemu_syscall *call);
void qemu__wtol(struct qemu_syscall *call);
void qemu__wtol_l(struct qemu_syscall *call);
void qemu__wtoll(struct qemu_syscall *call);
void qemu__wtoll_l(struct qemu_syscall *call);
void qemu__wunlink(struct qemu_syscall *c);
void qemu__wutime(struct qemu_syscall *c);
void qemu__wutime32(struct qemu_syscall *c);
void qemu__wutime64(struct qemu_syscall *c);
void qemu__xcptfilter(struct qemu_syscall *c);
void qemu__y0(struct qemu_syscall *call);
void qemu__y1(struct qemu_syscall *call);
void qemu__yn(struct qemu_syscall *call);
void qemu_abort(struct qemu_syscall *call);
void qemu_abs(struct qemu_syscall *call);
void qemu_acos(struct qemu_syscall *call);
void qemu_acosf(struct qemu_syscall *call);
void qemu_acosh(struct qemu_syscall *call);
void qemu_acoshf(struct qemu_syscall *call);
void qemu_acoshl(struct qemu_syscall *call);
void qemu_asctime(struct qemu_syscall *call);
void qemu_asctime_s(struct qemu_syscall *call);
void qemu_asin(struct qemu_syscall *call);
void qemu_asinf(struct qemu_syscall *call);
void qemu_asinh(struct qemu_syscall *call);
void qemu_asinhf(struct qemu_syscall *call);
void qemu_asinhl(struct qemu_syscall *call);
void qemu_atan(struct qemu_syscall *call);
void qemu_atan2(struct qemu_syscall *call);
void qemu_atan2f(struct qemu_syscall *call);
void qemu_atanf(struct qemu_syscall *call);
void qemu_atanh(struct qemu_syscall *call);
void qemu_atanhf(struct qemu_syscall *call);
void qemu_atanhl(struct qemu_syscall *call);
void qemu_atof(struct qemu_syscall *call);
void qemu_atoi(struct qemu_syscall *call);
void qemu_atoll(struct qemu_syscall *call);
void qemu_bsearch(struct qemu_syscall *call);
void qemu_btowc(struct qemu_syscall *call);
void qemu_calloc(struct qemu_syscall *call);
void qemu_cbrt(struct qemu_syscall *call);
void qemu_cbrtf(struct qemu_syscall *call);
void qemu_cbrtl(struct qemu_syscall *call);
void qemu_ceil(struct qemu_syscall *call);
void qemu_ceilf(struct qemu_syscall *call);
void qemu_clearerr(struct qemu_syscall *c);
void qemu_clock(struct qemu_syscall *call);
void qemu_Concurrency_Alloc(struct qemu_syscall *call);
void qemu_Concurrency_Free(struct qemu_syscall *call);
void qemu_Context__SpinYield(struct qemu_syscall *call);
void qemu_Context_Block(struct qemu_syscall *call);
void qemu_Context_CurrentContext(struct qemu_syscall *call);
void qemu_Context_Id(struct qemu_syscall *call);
void qemu_Context_IsCurrentTaskCollectionCanceling(struct qemu_syscall *call);
void qemu_Context_Oversubscribe(struct qemu_syscall *call);
void qemu_Context_ScheduleGroupId(struct qemu_syscall *call);
void qemu_Context_VirtualProcessorId(struct qemu_syscall *call);
void qemu_Context_Yield(struct qemu_syscall *call);
void qemu_cos(struct qemu_syscall *call);
void qemu_cosf(struct qemu_syscall *call);
void qemu_cosh(struct qemu_syscall *call);
void qemu_coshf(struct qemu_syscall *call);
void qemu_ctime(struct qemu_syscall *call);
void qemu_ctime(struct qemu_syscall *call);
void qemu_CurrentScheduler_Create(struct qemu_syscall *call);
void qemu_CurrentScheduler_CreateScheduleGroup(struct qemu_syscall *call);
void qemu_CurrentScheduler_Detach(struct qemu_syscall *call);
void qemu_CurrentScheduler_Get(struct qemu_syscall *call);
void qemu_CurrentScheduler_GetNumberOfVirtualProcessors(struct qemu_syscall *call);
void qemu_CurrentScheduler_GetPolicy(struct qemu_syscall *call);
void qemu_CurrentScheduler_Id(struct qemu_syscall *call);
void qemu_CurrentScheduler_IsAvailableLocation(struct qemu_syscall *call);
void qemu_CurrentScheduler_RegisterShutdownEvent(struct qemu_syscall *call);
void qemu_decode_pointer(struct qemu_syscall *call);
void qemu_difftime(struct qemu_syscall *call);
void qemu_difftime(struct qemu_syscall *call);
void qemu_div(struct qemu_syscall *call);
void qemu_encode_pointer(struct qemu_syscall *call);
void qemu_erf(struct qemu_syscall *call);
void qemu_erfc(struct qemu_syscall *call);
void qemu_erfcf(struct qemu_syscall *call);
void qemu_erfcl(struct qemu_syscall *call);
void qemu_erff(struct qemu_syscall *call);
void qemu_erfl(struct qemu_syscall *call);
void qemu_event_wait_for_multiple(struct qemu_syscall *call);
void qemu_exit(struct qemu_syscall *call);
void qemu_exp(struct qemu_syscall *call);
void qemu_exp2(struct qemu_syscall *call);
void qemu_exp2f(struct qemu_syscall *call);
void qemu_exp2l(struct qemu_syscall *call);
void qemu_expf(struct qemu_syscall *call);
void qemu_expm1(struct qemu_syscall *call);
void qemu_expm1f(struct qemu_syscall *call);
void qemu_expm1l(struct qemu_syscall *call);
void qemu_fabs(struct qemu_syscall *call);
void qemu_fabsf(struct qemu_syscall *call);
void qemu_fclose(struct qemu_syscall *c);
void qemu_fegetenv(struct qemu_syscall *call);
void qemu_fegetround(struct qemu_syscall *call);
void qemu_feof(struct qemu_syscall *c);
void qemu_ferror(struct qemu_syscall *c);
void qemu_fesetenv(struct qemu_syscall *call);
void qemu_fesetround(struct qemu_syscall *call);
void qemu_fflush(struct qemu_syscall *call);
void qemu_fgetc(struct qemu_syscall *c);
void qemu_fgetpos(struct qemu_syscall *c);
void qemu_fgets(struct qemu_syscall *c);
void qemu_fgetwc(struct qemu_syscall *c);
void qemu_fgetws(struct qemu_syscall *c);
void qemu_floor(struct qemu_syscall *call);
void qemu_floorf(struct qemu_syscall *call);
void qemu_fmax(struct qemu_syscall *call);
void qemu_fmaxf(struct qemu_syscall *call);
void qemu_fmin(struct qemu_syscall *call);
void qemu_fminf(struct qemu_syscall *call);
void qemu_fmod(struct qemu_syscall *call);
void qemu_fmodf(struct qemu_syscall *call);
void qemu_fopen(struct qemu_syscall *c);
void qemu_fopen_s(struct qemu_syscall *c);
void qemu_fprintf(struct qemu_syscall *call);
void qemu_fputc(struct qemu_syscall *c);
void qemu_fputs(struct qemu_syscall *c);
void qemu_fputwc(struct qemu_syscall *c);
void qemu_fputws(struct qemu_syscall *c);
void qemu_fread(struct qemu_syscall *call);
void qemu_fread_s(struct qemu_syscall *c);
void qemu_free(struct qemu_syscall *call);
void qemu_freopen(struct qemu_syscall *c);
void qemu_freopen_s(struct qemu_syscall *c);
void qemu_frexp(struct qemu_syscall *call);
void qemu_frexpf(struct qemu_syscall *call);
void qemu_fseek(struct qemu_syscall *c);
void qemu_fsetpos(struct qemu_syscall *c);
void qemu_ftell(struct qemu_syscall *c);
void qemu_fwrite(struct qemu_syscall *call);
void qemu_generic_stub(struct qemu_syscall *call);
void qemu_getc(struct qemu_syscall *c);
void qemu_getchar(struct qemu_syscall *c);
void qemu_getenv(struct qemu_syscall *call);
void qemu_getenv_s(struct qemu_syscall *call);
void qemu_getgrgid(struct qemu_syscall *call);
void qemu_getpwuid(struct qemu_syscall *call);
void qemu_gets(struct qemu_syscall *c);
void qemu_getwc(struct qemu_syscall *c);
void qemu_getwchar(struct qemu_syscall *c);
void qemu_gmtime(struct qemu_syscall *call);
void qemu_gmtime(struct qemu_syscall *call);
void qemu_I10_OUTPUT(struct qemu_syscall *call);
void qemu_isalnum(struct qemu_syscall *call);
void qemu_isalpha(struct qemu_syscall *call);
void qemu_isblank(struct qemu_syscall *call);
void qemu_iscntrl(struct qemu_syscall *call);
void qemu_isdigit(struct qemu_syscall *call);
void qemu_isgraph(struct qemu_syscall *call);
void qemu_isleadbyte(struct qemu_syscall *call);
void qemu_islower(struct qemu_syscall *call);
void qemu_isprint(struct qemu_syscall *call);
void qemu_ispunct(struct qemu_syscall *call);
void qemu_isspace(struct qemu_syscall *call);
void qemu_isupper(struct qemu_syscall *call);
void qemu_iswalnum(struct qemu_syscall *call);
void qemu_iswalpha(struct qemu_syscall *call);
void qemu_iswascii(struct qemu_syscall *call);
void qemu_iswblank(struct qemu_syscall *call);
void qemu_iswcntrl(struct qemu_syscall *call);
void qemu_iswdigit(struct qemu_syscall *call);
void qemu_iswgraph(struct qemu_syscall *call);
void qemu_iswlower(struct qemu_syscall *call);
void qemu_iswprint(struct qemu_syscall *call);
void qemu_iswpunct(struct qemu_syscall *call);
void qemu_iswspace(struct qemu_syscall *call);
void qemu_iswupper(struct qemu_syscall *call);
void qemu_iswxdigit(struct qemu_syscall *call);
void qemu_isxdigit(struct qemu_syscall *call);
void qemu_labs(struct qemu_syscall *call);
void qemu_ldexp(struct qemu_syscall *call);
void qemu_ldiv(struct qemu_syscall *call);
void qemu_lgamma(struct qemu_syscall *call);
void qemu_lgammaf(struct qemu_syscall *call);
void qemu_lgammal(struct qemu_syscall *call);
void qemu_llabs(struct qemu_syscall *call);
void qemu_llrint(struct qemu_syscall *call);
void qemu_llrintf(struct qemu_syscall *call);
void qemu_llrintl(struct qemu_syscall *call);
void qemu_llround(struct qemu_syscall *call);
void qemu_llroundf(struct qemu_syscall *call);
void qemu_llroundl(struct qemu_syscall *call);
void qemu_localeconv(struct qemu_syscall *call);
void qemu_localtime(struct qemu_syscall *call);
void qemu_localtime(struct qemu_syscall *call);
void qemu_log(struct qemu_syscall *call);
void qemu_log10(struct qemu_syscall *call);
void qemu_log10f(struct qemu_syscall *call);
void qemu_log1p(struct qemu_syscall *call);
void qemu_log1pf(struct qemu_syscall *call);
void qemu_log1pl(struct qemu_syscall *call);
void qemu_log2(struct qemu_syscall *call);
void qemu_log2f(struct qemu_syscall *call);
void qemu_log2l(struct qemu_syscall *call);
void qemu_logf(struct qemu_syscall *call);
void qemu_longjmp(struct qemu_syscall *call);
void qemu_lrint(struct qemu_syscall *call);
void qemu_lrintf(struct qemu_syscall *call);
void qemu_lrintl(struct qemu_syscall *call);
void qemu_lround(struct qemu_syscall *call);
void qemu_lroundf(struct qemu_syscall *call);
void qemu_lroundl(struct qemu_syscall *call);
void qemu_malloc(struct qemu_syscall *call);
void qemu_mblen(struct qemu_syscall *call);
void qemu_mbrlen(struct qemu_syscall *call);
void qemu_mbrtowc(struct qemu_syscall *call);
void qemu_mbsrtowcs(struct qemu_syscall *call);
void qemu_mbsrtowcs_s(struct qemu_syscall *call);
void qemu_mbstowcs(struct qemu_syscall *call);
void qemu_mbstowcs_s(struct qemu_syscall *call);
void qemu_mbtowc(struct qemu_syscall *call);
void qemu_mbtowc_l(struct qemu_syscall *call);
void qemu_memchr(struct qemu_syscall *call);
void qemu_memcmp(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memcpy_s(struct qemu_syscall *call);
void qemu_memmove(struct qemu_syscall *call);
void qemu_memmove_s(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_mktime(struct qemu_syscall *call);
void qemu_mktime(struct qemu_syscall *call);
void qemu_modf(struct qemu_syscall *call);
void qemu_modff(struct qemu_syscall *call);
void qemu_nan(struct qemu_syscall *call);
void qemu_nanf(struct qemu_syscall *call);
void qemu_nearbyint(struct qemu_syscall *call);
void qemu_nearbyintf(struct qemu_syscall *call);
void qemu_operator_delete(struct qemu_syscall *call);
void qemu_operator_new(struct qemu_syscall *call);
void qemu_operator_new_dbg(struct qemu_syscall *call);
void qemu_perror(struct qemu_syscall *call);
void qemu_pow(struct qemu_syscall *call);
void qemu_powf(struct qemu_syscall *call);
void qemu_putc(struct qemu_syscall *c);
void qemu_putchar(struct qemu_syscall *c);
void qemu_puts(struct qemu_syscall *call);
void qemu_qsort(struct qemu_syscall *call);
void qemu_raise(struct qemu_syscall *call);
void qemu_rand(struct qemu_syscall *call);
void qemu_realloc(struct qemu_syscall *call);
void qemu_realpath(struct qemu_syscall *call);
void qemu_remainder(struct qemu_syscall *call);
void qemu_remainderf(struct qemu_syscall *call);
void qemu_remainderl(struct qemu_syscall *call);
void qemu_remove(struct qemu_syscall *c);
void qemu_rename(struct qemu_syscall *c);
void qemu_rewind(struct qemu_syscall *c);
void qemu_rint(struct qemu_syscall *call);
void qemu_rintf(struct qemu_syscall *call);
void qemu_rintl(struct qemu_syscall *call);
void qemu_round(struct qemu_syscall *call);
void qemu_roundf(struct qemu_syscall *call);
void qemu_roundl(struct qemu_syscall *call);
void qemu_scalbnl(struct qemu_syscall *call);
void qemu_scanf(struct qemu_syscall *call);
void qemu_Scheduler_Create(struct qemu_syscall *call);
void qemu_Scheduler_ResetDefaultSchedulerPolicy(struct qemu_syscall *call);
void qemu_Scheduler_SetDefaultSchedulerPolicy(struct qemu_syscall *call);
void qemu_set_new_handler(struct qemu_syscall *call);
void qemu_setbuf(struct qemu_syscall *c);
void qemu_setlocale(struct qemu_syscall *call);
void qemu_setvbuf(struct qemu_syscall *call);
void qemu_signal(struct qemu_syscall *call);
void qemu_sin(struct qemu_syscall *call);
void qemu_sinf(struct qemu_syscall *call);
void qemu_sinh(struct qemu_syscall *call);
void qemu_sinhf(struct qemu_syscall *call);
void qemu_SpinCount__Value(struct qemu_syscall *call);
void qemu_sprintf(struct qemu_syscall *call);
void qemu_sqrt(struct qemu_syscall *call);
void qemu_sqrtf(struct qemu_syscall *call);
void qemu_srand(struct qemu_syscall *call);
void qemu_stat(struct qemu_syscall *c);
void qemu_stati64(struct qemu_syscall *c);
void qemu_strcat_s(struct qemu_syscall *call);
void qemu_strchr(struct qemu_syscall *call);
void qemu_strcmp(struct qemu_syscall *call);
void qemu_strcoll(struct qemu_syscall *call);
void qemu_strcoll_l(struct qemu_syscall *call);
void qemu_strcpy(struct qemu_syscall *call);
void qemu_strcpy_s(struct qemu_syscall *call);
void qemu_strerror(struct qemu_syscall *call);
void qemu_strerror_s(struct qemu_syscall *call);
void qemu_strftime(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);
void qemu_strncat(struct qemu_syscall *call);
void qemu_strncat_s(struct qemu_syscall *call);
void qemu_strncmp(struct qemu_syscall *call);
void qemu_strncpy(struct qemu_syscall *call);
void qemu_strncpy_s(struct qemu_syscall *call);
void qemu_strnlen(struct qemu_syscall *call);
void qemu_strrchr(struct qemu_syscall *call);
void qemu_strstr(struct qemu_syscall *call);
void qemu_strtod(struct qemu_syscall *call);
void qemu_strtod_l(struct qemu_syscall *call);
void qemu_strtof(struct qemu_syscall *call);
void qemu_strtok(struct qemu_syscall *call);
void qemu_strtok_s(struct qemu_syscall *call);
void qemu_strtol(struct qemu_syscall *call);
void qemu_strtoul(struct qemu_syscall *call);
void qemu_strtoul_l(struct qemu_syscall *call);
void qemu_strxfrm(struct qemu_syscall *call);
void qemu_system(struct qemu_syscall *call);
void qemu_tan(struct qemu_syscall *call);
void qemu_tanf(struct qemu_syscall *call);
void qemu_tanh(struct qemu_syscall *call);
void qemu_tanhf(struct qemu_syscall *call);
void qemu_terminate(struct qemu_syscall *c);
void qemu_time(struct qemu_syscall *call);
void qemu_time(struct qemu_syscall *call);
void qemu_tmpfile(struct qemu_syscall *c);
void qemu_tmpfile_s(struct qemu_syscall *c);
void qemu_tmpnam(struct qemu_syscall *c);
void qemu_tmpnam_s(struct qemu_syscall *c);
void qemu_tolower(struct qemu_syscall *call);
void qemu_toupper(struct qemu_syscall *call);
void qemu_towlower(struct qemu_syscall *call);
void qemu_towupper(struct qemu_syscall *call);
void qemu_trunc(struct qemu_syscall *call);
void qemu_truncf(struct qemu_syscall *call);
void qemu_truncl(struct qemu_syscall *call);
void qemu_type_info_dtor(struct qemu_syscall *call);
void qemu_ungetc(struct qemu_syscall *c);
void qemu_ungetwc(struct qemu_syscall *c);
void qemu_wcrtomb(struct qemu_syscall *call);
void qemu_wcscat_s(struct qemu_syscall *call);
void qemu_wcschr(struct qemu_syscall *call);
void qemu_wcscoll(struct qemu_syscall *call);
void qemu_wcscpy(struct qemu_syscall *call);
void qemu_wcscpy_s(struct qemu_syscall *call);
void qemu_wcsftime(struct qemu_syscall *call);
void qemu_wcslen(struct qemu_syscall *call);
void qemu_wcsncat_s(struct qemu_syscall *call);
void qemu_wcsncmp(struct qemu_syscall *call);
void qemu_wcsncpy(struct qemu_syscall *call);
void qemu_wcsncpy_s(struct qemu_syscall *call);
void qemu_wcsnlen(struct qemu_syscall *call);
void qemu_wcspbrk(struct qemu_syscall *call);
void qemu_wcsrtombs(struct qemu_syscall *call);
void qemu_wcsrtombs_s(struct qemu_syscall *call);
void qemu_wcsstr(struct qemu_syscall *call);
void qemu_wcstod(struct qemu_syscall *call);
void qemu_wcstof(struct qemu_syscall *call);
void qemu_wcstok(struct qemu_syscall *call);
void qemu_wcstok_s(struct qemu_syscall *call);
void qemu_wcstombs(struct qemu_syscall *call);
void qemu_wcstombs_s(struct qemu_syscall *call);
void qemu_wcstoul(struct qemu_syscall *call);
void qemu_wcsxfrm(struct qemu_syscall *call);
void qemu_wctob(struct qemu_syscall *call);
void qemu_wctomb(struct qemu_syscall *call);
void qemu_wctomb_s(struct qemu_syscall *call);
void qemu_wmemcpy_s(struct qemu_syscall *call);
void qemu_wmemmove_s(struct qemu_syscall *call);
void qemu_wscanf(struct qemu_syscall *call);

/* Be careful not to call the Linux libc! */
void (* CDECL p___crt_debugger_hook)(int reserved);
void (* CDECL p___getmainargs)(int *argc, char** *argv, char** *envp,
        int expand_wildcards, int *new_mode);
MSVCRT_FILE *(* CDECL p___iob_func)();
int (* CDECL p___lconv_init)(void);
void (* CDECL p___set_app_type)(int type);
void (* CDECL p___setusermatherr)(void *func);
void (* CDECL p___wgetmainargs)(int *argc, WCHAR** *wargv, WCHAR** *wenvp,
        int expand_wildcards, int *new_mode);
void (* CDECL p__amsg_exit)(int errnum);
void (* CDECL p__cexit)(void);
int (* CDECL p__configthreadlocale)(int type);
int * (* CDECL p__errno)(void);
void (* CDECL p__exit)(int code);
void (* CDECL p__lock)(int locknum);
int (* CDECL p__matherr)(void *exception);
MSVCRT__onexit_t (* CDECL p__onexit)(MSVCRT__onexit_t func);
void (* CDECL p__purecall)(void);
char * (* CDECL p__strdup)(const char* str);
int (* CDECL p__stricmp)(const char *s1, const char *s2);
int (* CDECL p__strnicmp)(const char *s1, const char *s2, size_t count);
void (* CDECL p__unlock)(int locknum);
int (* CDECL p__wcsnicmp)(const WCHAR *str1, const WCHAR *str2, int count);
double (* CDECL p__wtof)(const WCHAR *str1);
int (* CDECL p__wtoi)(const WCHAR *str1);
void (* CDECL p_abort)(void);
float (* CDECL p_atan2f)(float x, float y);
void *(* CDECL p_calloc)(size_t item_count,size_t size);
float (* CDECL p_cosf)(float x);
void (* CDECL p_exit)(int code);
void (* CDECL p_free)(void *ptr);
size_t (* CDECL p_fwrite)(const void *str, size_t size, size_t count, MSVCRT_FILE *file);
void *(* CDECL p_malloc)(size_t size);
void *(* CDECL p_memset)(void *dst, int c, size_t n);
void (* CDECL p_operator_delete)(void *mem);
void *(* CDECL p_operator_new)(size_t size);
void *(* CDECL p_memchr)(const void *ptr, int c, size_t n);
int (* CDECL p_memcmp)(const void *ptr1, const void *ptr2, size_t size);
void *(* CDECL p_memcpy)(void *dst, const void *src, size_t size);
void *(* CDECL p_memmove)(void *dst, const void *src, size_t size);
float (* CDECL p_powf)(float base, float exp);
int (* CDECL p_puts)(const char *str);
void (* CDECL p_qsort)(void *base, size_t nmemb, size_t size,
        int (CDECL *compar)(const void*, const void*));
void *(* CDECL p_realloc)(void *ptr, size_t size);
float (* CDECL p_sinf)(float x);
float (* CDECL p_sqrtf)(float x);
int (* CDECL p_strcpy_s)(char *dst, size_t elem, const char *src);
int (* CDECL p_strcat_s)(char *dst, size_t elem, const char *src);
char * (* CDECL p_strchr)(const char *str, int c);
char * (* CDECL p_strcmp)(const char *str1, const char *str2);
size_t (* CDECL p_strlen)(const char *str);
int (* CDECL p_strncmp)(const char *str1, const char *str2, size_t len);
char *(* CDECL p_strncpy)(char *dst, const char *src, size_t len);
char * (* CDECL p_strrchr)(const char *str, int c);
void (* CDECL p_terminate)(void);
int (* CDECL p_vfprintf)(FILE *file,const char *format, __ms_va_list args);
int (* CDECL p_vfwprintf)(FILE *file, const WCHAR *format, __ms_va_list args);
int (* CDECL p_vsprintf)(char *str, const char *format, __ms_va_list args);
int (* CDECL p_vsprintf_s)(char *str, size_t num, const char *format, __ms_va_list args);
int (* CDECL p_vswprintf_s)(WCHAR *dst, size_t charcount,
        const WCHAR *fmt, __ms_va_list args);
int (* CDECL p_wcscat_s)(WCHAR *dst, size_t count, const WCHAR *src);
WCHAR (* CDECL p_wcscpy)(WCHAR *dst, const WCHAR *src);
int (* CDECL p_wcscpy_s)(WCHAR *dst, size_t size, const WCHAR *src);
int (* CDECL p_wcsncmp)(const WCHAR *str1, const WCHAR *str2, size_t count);
const WCHAR * (* CDECL p_wcsstr)(const WCHAR *str, const WCHAR *sub);
double (* CDECL p_wcstod)(const WCHAR *str, WCHAR **end);

int (* CDECL p__set_SSE2_enable)(int flag);
int (* CDECL p__set_FMA3_enable)(int flag);
float (* CDECL p__chgsignf)(float num);
float (* CDECL p__copysignf)(float num, float sign);
float (* CDECL p__nextafterf)(float num, float next);
int (* CDECL p__finitef)(float num);
INT (* CDECL p__isnanf)(float num);
float (* CDECL p__logbf)(float num);
float (* CDECL p_acosf)(float x);
float (* CDECL p_asinf)(float x);
float (* CDECL p_atanf)(float x);
float (* CDECL p_atan2f)(float x, float y);
float (* CDECL p_cosf)(float x);
float (* CDECL p_coshf)(float x);
float (* CDECL p_expf)(float x);
float (* CDECL p_fmodf)(float x, float y);
float (* CDECL p_logf)(float x);
float (* CDECL p_log10f)(float x);
float (* CDECL p_powf)(float x, float y);
float (* CDECL p_sinf)(float x);
float (* CDECL p_sinhf)(float x);
float (* CDECL p_sqrtf)(float x);
float (* CDECL p_tanf)(float x);
float (* CDECL p_tanhf)(float x);
float (* CDECL p_ceilf)(float x);
float (* CDECL p_fabsf)(float x);
float (* CDECL p_floorf)(float x);
float (* CDECL p_frexpf)(float x, int *exp);
float (* CDECL p_modff)(float x, float *iptr);
double (* CDECL p_acos)(double x);
double (* CDECL p_asin)(double x);
double (* CDECL p_atan)(double x);
double (* CDECL p_atan2)(double x, double y);
double (* CDECL p_cos)(double x);
double (* CDECL p_cosh)(double x);
double (* CDECL p_exp)(double x);
double (* CDECL p_fmod)(double x, double y);
double (* CDECL p_log)(double x);
double (* CDECL p_log10)(double x);
double (* CDECL p_pow)(double x, double y);
double (* CDECL p_sin)(double x);
double (* CDECL p_sinh)(double x);
double (* CDECL p_sqrt)(double x);
double (* CDECL p_tan)(double x);
double (* CDECL p_tanh)(double x);
int (* CDECL p__fpclass)(double num);
unsigned int (* CDECL p__rotl)(unsigned int num, int shift);
uint32_t (* CDECL p__lrotl)(uint32_t num, int shift);
uint32_t (* CDECL p__lrotr)(uint32_t num, int shift);
unsigned int (* CDECL p__rotr)(unsigned int num, int shift);
unsigned __int64 (* CDECL p__rotl64)(unsigned __int64 num, int shift);
unsigned __int64 (* CDECL p__rotr64)(unsigned __int64 num, int shift);
int (* CDECL p_abs)(int n);
int32_t (* CDECL p_labs)(int32_t n);
int64_t (* CDECL p_llabs)(int64_t n);
__int64 (* CDECL p__abs64)(__int64 n);
double (* CDECL p__logb)(double num);
double (* CDECL p__hypot)(double x, double y);
float (* CDECL p__hypotf)(float x, float y);
double (* CDECL p_ceil)(double x);
double (* CDECL p_floor)(double x);
double (* CDECL p_fabs)(double x);
double (* CDECL p_frexp)(double x, int *exp);
double (* CDECL p_modf)(double x, double *iptr);
void (* CDECL p__statusfp2)(unsigned int *x86_sw, unsigned int *sse2_sw);
unsigned int (* CDECL p__statusfp)(void);
unsigned int (* CDECL p__clearfp)(void);
int * (* CDECL p___fpecode)(void);
double (* CDECL p_ldexp)(double num, int32_t exp);
double (* CDECL p__cabs)(struct MSVCRT__complex num);
double (* CDECL p__chgsign)(double num);
void (* CDECL p___clean_type_info_names_internal)(void *p);
int (* CDECL p___control87_2)(unsigned int newval, unsigned int mask, unsigned int *x86_cw, unsigned int *sse2_cw);
unsigned int (* CDECL p__control87)(unsigned int newval, unsigned int mask);
unsigned int (* CDECL p__controlfp)(unsigned int newval, unsigned int mask);
void (* CDECL p__set_controlfp)(unsigned int newval, unsigned int mask);
int (* CDECL p__controlfp_s)(unsigned int *cur, unsigned int newval, unsigned int mask);
int (* CDECL p_fegetenv)(MSVCRT_fenv_t *env);
int (* CDECL p___fpe_flt_rounds)(void);
int (* CDECL p_fegetround)(void);
int (* CDECL p_fesetround)(int round_mode);
double (* CDECL p__copysign)(double num, double sign);
int (* CDECL p__finite)(double num);
void (* CDECL p__fpreset)(void);
int (* CDECL p_fesetenv)(const MSVCRT_fenv_t *env);
INT (* CDECL p__isnan)(double num);
double (* CDECL p__j0)(double num);
double (* CDECL p__j1)(double num);
double (* CDECL p__jn)(int n, double num);
double (* CDECL p__y0)(double num);
double (* CDECL p__y1)(double num);
double (* CDECL p__yn)(int order, double num);
double (* CDECL p_nearbyint)(double num);
float (* CDECL p_nearbyintf)(float num);
double (* CDECL p__nextafter)(double num, double next);
char * (* CDECL p__ecvt)(double number, int ndigits, int *decpt, int *sign);
int (* CDECL p__ecvt_s)(char *buffer, size_t length, double number, int ndigits, int *decpt, int *sign);
char * (* CDECL p__fcvt)(double number, int ndigits, int *decpt, int *sign);
int (* CDECL p__fcvt_s)(char* outbuffer, size_t size, double number, int ndigits, int *decpt, int *sign);
char * (* CDECL p__gcvt)(double number, int ndigit, char *buff);
int (* CDECL p__gcvt_s)(char *buff, size_t size, double number, int digits);
unsigned __int64 (* CDECL p_div)(int num, int denom);
unsigned __int64 (* CDECL p_ldiv)(int32_t num, int32_t denom);
void (* CDECL p___libm_sse2_acos)(void);
void (* CDECL p___libm_sse2_acosf)(void);
void (* CDECL p___libm_sse2_asin)(void);
void (* CDECL p___libm_sse2_asinf)(void);
void (* CDECL p___libm_sse2_atan)(void);
void (* CDECL p___libm_sse2_atan2)(void);
void (* CDECL p___libm_sse2_atanf)(void);
void (* CDECL p___libm_sse2_cos)(void);
void (* CDECL p___libm_sse2_cosf)(void);
void (* CDECL p___libm_sse2_exp)(void);
void (* CDECL p___libm_sse2_expf)(void);
void (* CDECL p___libm_sse2_log)(void);
void (* CDECL p___libm_sse2_log10)(void);
void (* CDECL p___libm_sse2_log10f)(void);
void (* CDECL p___libm_sse2_logf)(void);
void (* CDECL p___libm_sse2_pow)(void);
void (* CDECL p___libm_sse2_powf)(void);
void (* CDECL p___libm_sse2_sin)(void);
void (* CDECL p___libm_sse2_sinf)(void);
void (* CDECL p___libm_sse2_tan)(void);
void (* CDECL p___libm_sse2_tanf)(void);
void (* CDECL p___libm_sse2_sqrt_precise)(void);
double (* CDECL p_cbrt)(double x);
float (* CDECL p_cbrtf)(float x);
double (* CDECL p_cbrtl)(double x);
double (* CDECL p_exp2)(double x);
float (* CDECL p_exp2f)(float x);
double (* CDECL p_exp2l)(double x);
double (* CDECL p_expm1)(double x);
float (* CDECL p_expm1f)(float x);
double (* CDECL p_expm1l)(double x);
double (* CDECL p_log1p)(double x);
float (* CDECL p_log1pf)(float x);
double (* CDECL p_log1pl)(double x);
double (* CDECL p_log2)(double x);
float (* CDECL p_log2f)(float x);
double (* CDECL p_log2l)(double x);
double (* CDECL p_rint)(double x);
float (* CDECL p_rintf)(float x);
double (* CDECL p_rintl)(double x);
int32_t (* CDECL p_lrint)(double x);
int32_t (* CDECL p_lrintf)(float x);
int32_t (* CDECL p_lrintl)(double x);
int64_t (* CDECL p_llrint)(double x);
int64_t (* CDECL p_llrintf)(float x);
int64_t (* CDECL p_llrintl)(double x);
double (* CDECL p_round)(double x);
float (* CDECL p_roundf)(float x);
double (* CDECL p_roundl)(double x);
int32_t (* CDECL p_lround)(double x);
int32_t (* CDECL p_lroundf)(float x);
int32_t (* CDECL p_lroundl)(double x);
int64_t (* CDECL p_llround)(double x);
int64_t (* CDECL p_llroundf)(float x);
int64_t (* CDECL p_llroundl)(double x);
double (* CDECL p_trunc)(double x);
float (* CDECL p_truncf)(float x);
double (* CDECL p_truncl)(double x);
short (* CDECL p__dclass)(double x);
short (* CDECL p__fdclass)(float x);
short (* CDECL p__ldclass)(double x);
short (* CDECL p__dtest)(double *x);
short (* CDECL p__fdtest)(float *x);
short (* CDECL p__ldtest)(double *x);
double (* CDECL p_erf)(double x);
float (* CDECL p_erff)(float x);
double (* CDECL p_erfl)(double x);
double (* CDECL p_erfc)(double x);
float (* CDECL p_erfcf)(float x);
double (* CDECL p_erfcl)(double x);
float (* CDECL p_fmaxf)(float x, float y);
double (* CDECL p_fmax)(double x, double y);
int (* CDECL p__fdsign)(float x);
int (* CDECL p__dsign)(double x);
int (* CDECL p__dpcomp)(double x, double y);
int (* CDECL p__fdpcomp)(float x, float y);
float (* CDECL p_fminf)(float x, float y);
double (* CDECL p_fmin)(double x, double y);
double (* CDECL p_asinh)(double x);
float (* CDECL p_asinhf)(float x);
double (* CDECL p_asinhl)(double x);
double (* CDECL p_acosh)(double x);
float (* CDECL p_acoshf)(float x);
double (* CDECL p_acoshl)(double x);
double (* CDECL p_atanh)(double x);
float (* CDECL p_atanhf)(float x);
double (* CDECL p_atanhl)(double x);
double (* CDECL p__scalb)(double num, int32_t power);
float (* CDECL p__scalbf)(float num, int32_t power);
double (* CDECL p_scalbnl)(double num, int32_t power);
double (* CDECL p_remainder)(double x, double y);
float (* CDECL p_remainderf)(float x, float y);
double (* CDECL p_remainderl)(double x, double y);
double (* CDECL p_lgamma)(double x);
float (* CDECL p_lgammaf)(float x);
double (* CDECL p_lgammal)(double x);
double (* CDECL p_nan)(const char *tagp);
float (* CDECL p_nanf)(const char *tagp);

unsigned short** (* CDECL p___p__pctype)(void);
const unsigned short* (* CDECL p___pctype_func)(void);
int (* CDECL p__isctype_l)(int c, int type, MSVCRT__locale_t locale);
int (* CDECL p__isctype)(int c, int type);
int (* CDECL p__isalnum_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isalpha_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__iscntrl_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isdigit_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isgraph_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isleadbyte_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p_isleadbyte)(int c);
int (* CDECL p__islower_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isprint_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isspace_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isupper_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isxdigit_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__isblank_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p_iswascii)(wchar_t c);
int (* CDECL p___iscsym)(int c);
int (* CDECL p___iscsymf)(int c);
int (* CDECL p__toupper_l)(int c, MSVCRT__locale_t locale);
int (* CDECL p__tolower_l)(int c, MSVCRT__locale_t locale);
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
int (* CDECL p_isblank)(int c);
int (* CDECL p___isascii)(int c);
int (* CDECL p___toascii)(int c);
int (* CDECL p_toupper)(int c);
int (* CDECL p__toupper)(int c);
int (* CDECL p_tolower)(int c);
int (* CDECL p__tolower)(int c);

INT (* CDECL p_iswpunct)(WCHAR wc);
INT (* CDECL p_iswdigit)(WCHAR wc);
INT (* CDECL p_iswalpha)(WCHAR wc);
INT (* CDECL p_iswspace)(WCHAR wc);
INT (* CDECL p_wctomb)(char *dst, WCHAR ch);
size_t (* CDECL p_wcstombs)(char *mbstr, const WCHAR *wcstr, size_t count);

char * (* CDECL p_setlocale)(int category, const char *locale);
int (* CDECL p__isatty)(int fd);
int (* CDECL p__vsnprintf)(char *str, size_t len, const char *format, __ms_va_list valist);
int (* CDECL p__vsnprintf_s)(char *str, unsigned int len, unsigned int count, const char *format, __ms_va_list valist);
int (* CDECL p__vsnwprintf)(WCHAR *str, size_t len, const WCHAR *format, __ms_va_list valist);
int (* CDECL p__fileno)(MSVCRT_FILE *f);
int (* CDECL p__write)(int fd, const void *buf, unsigned int count);
double (* CDECL p_atof)(const char *str);
size_t (* CDECL p_fread)(void *ptr, size_t size, size_t nmemb, MSVCRT_FILE *file);
int (*CDECL p_rand)(void);
int (*CDECL p_srand)(int seed);
int (* CDECL p_fflush)(MSVCRT_FILE *file);
LONG (* CDECL p__lseek)(int fd, LONG offset, int whence);
__int64 (* CDECL p__lseeki64)(int fd, __int64 offset, int whence);
char * (* CDECL p__tempnam)(const char *dir, const char *prefix);
char * (* CDECL p_strstr)(const char *haystack, char *needle);
double (* CDECL p_strtod)(const char *str, char **end);
char * (* CDECL p__strtime)(char *time);
char * (* CDECL p__strdate)(char *date);

unsigned char* (* CDECL p___p__mbctype)(void);
int* (* CDECL p___p___mb_cur_max)(void);
int (* CDECL p____mb_cur_max_func)(void);
int* (* CDECL p____mb_cur_max_l_func)(MSVCRT__locale_t locale);
int (* CDECL p__setmbcp)(int cp);
int (* CDECL p__getmbcp)(void);
unsigned int (* CDECL p__mbsnextc)(const unsigned char* str);
unsigned int (* CDECL p__mbctolower)(unsigned int c);
unsigned int (* CDECL p__mbctoupper)(unsigned int c);
unsigned int (* CDECL p__mbctombb)(unsigned int c);
unsigned int (* CDECL p__mbcjistojms)(unsigned int c);
unsigned int (* CDECL p__mbcjmstojis)(unsigned int c);
unsigned char* (* CDECL p__mbsdec)(const unsigned char* start, const unsigned char* cur);
unsigned int (* CDECL p__mbclen)(const unsigned char* str);
unsigned char* (* CDECL p__mbsinc)(const unsigned char* str);
unsigned char* (* CDECL p__mbsninc)(const unsigned char* str, size_t num);
size_t (* CDECL p__mbslen)(const unsigned char* str);
void (* CDECL p__mbccpy)(unsigned char* dest, const unsigned char* src);
unsigned char* (* CDECL p__mbsncpy)(unsigned char* dst, const unsigned char* src, size_t n);
int (* CDECL p__mbsnbcpy_s_l)(unsigned char* dst, size_t size, const unsigned char* src, size_t n, MSVCRT__locale_t locale);
int (* CDECL p__mbsnbcpy_s)(unsigned char* dst, size_t size, const unsigned char* src, size_t n);
int (* CDECL p__mbscpy_s_l)(unsigned char *dst, size_t size, const unsigned char *src, MSVCRT__locale_t locale);
int (* CDECL p__mbscpy_s)(unsigned char *dst, size_t size, const unsigned char *src);
unsigned char* (* CDECL p__mbsnbcpy)(unsigned char* dst, const unsigned char* src, size_t n);
int (* CDECL p__mbscmp)(const unsigned char* str, const unsigned char* cmp);
int (* CDECL p__mbsnbicoll_l)(const unsigned char *str1, const unsigned char *str2, size_t len, MSVCRT__locale_t locale);
int (* CDECL p__mbsicoll_l)(const unsigned char *str1, const unsigned char *str2, MSVCRT__locale_t locale);
int (* CDECL p__mbsnbicoll)(const unsigned char *str1, const unsigned char *str2, size_t len);
int (* CDECL p__mbsicoll)(const unsigned char* str, const unsigned char* cmp);
int (* CDECL p__mbsnbcoll_l)(const unsigned char *str1, const unsigned char *str2, size_t len, MSVCRT__locale_t locale);
int (* CDECL p__mbscoll_l)(const unsigned char *str1, const unsigned char *str2, MSVCRT__locale_t locale);
int (* CDECL p__mbsnbcoll)(const unsigned char *str1, const unsigned char *str2, size_t len);
int (* CDECL p__mbscoll)(const unsigned char* str, const unsigned char* cmp);
int (* CDECL p__mbsicmp)(const unsigned char* str, const unsigned char* cmp);
int (* CDECL p__mbsncmp)(const unsigned char* str, const unsigned char* cmp, size_t len);
int (* CDECL p__mbsnbcmp)(const unsigned char* str, const unsigned char* cmp, size_t len);
int (* CDECL p__mbsnicmp)(const unsigned char* str, const unsigned char* cmp, size_t len);
int (* CDECL p__mbsnbicmp)(const unsigned char* str, const unsigned char* cmp, size_t len);
unsigned char * (* CDECL p__mbscat)(unsigned char *dst, const unsigned char *src);
int (* CDECL p__mbscat_s_l)(unsigned char *dst, size_t size, const unsigned char *src, MSVCRT__locale_t locale);
int (* CDECL p__mbscat_s)(unsigned char *dst, size_t size, const unsigned char *src);
unsigned char* (* CDECL p__mbscpy)(unsigned char *dst, const unsigned char *src);
unsigned char * (* CDECL p__mbsstr)(const unsigned char *haystack, const unsigned char *needle);
unsigned char* (* CDECL p__mbschr)(const unsigned char* s, unsigned int x);
unsigned char* (* CDECL p__mbsrchr)(const unsigned char* s, unsigned int x);
unsigned char* (* CDECL p__mbstok_s_l)(unsigned char *str, const unsigned char *delim, unsigned char **ctx, MSVCRT__locale_t locale);
unsigned char* (* CDECL p__mbstok_s)(unsigned char *str, const unsigned char *delim, unsigned char **ctx);
unsigned char* (* CDECL p__mbstok_l)(unsigned char *str, const unsigned char *delim, MSVCRT__locale_t locale);
unsigned char* (* CDECL p__mbstok)(unsigned char *str, const unsigned char *delim);
unsigned int (* CDECL p__mbbtombc)(unsigned int c);
int (* CDECL p__mbbtype)(unsigned char c, int type);
int (* CDECL p__ismbbkana)(unsigned int c);
int (* CDECL p__ismbcdigit)(unsigned int ch);
int (* CDECL p__ismbcgraph)(unsigned int ch);
int (* CDECL p__ismbcalpha)(unsigned int ch);
int (* CDECL p__ismbclower)(unsigned int ch);
int (* CDECL p__ismbcupper)(unsigned int ch);
int (* CDECL p__ismbcsymbol)(unsigned int ch);
int (* CDECL p__ismbcalnum)(unsigned int ch);
int (* CDECL p__ismbcspace)(unsigned int ch);
int (* CDECL p__ismbcprint)(unsigned int ch);
int (* CDECL p__ismbcpunct)(unsigned int ch);
int (* CDECL p__ismbchira)(unsigned int c);
int (* CDECL p__ismbckata)(unsigned int c);
int (* CDECL p__ismbblead_l)(unsigned int c, MSVCRT__locale_t locale);
int (* CDECL p__ismbblead)(unsigned int c);
int (* CDECL p__ismbbtrail)(unsigned int c);
int (* CDECL p__ismbclegal)(unsigned int c);
int (* CDECL p__ismbslead)(const unsigned char* start, const unsigned char* str);
int (* CDECL p__ismbstrail)(const unsigned char* start, const unsigned char* str);
int (* CDECL p__mbsbtype)(const unsigned char *str, size_t count);
unsigned char* (* CDECL p__mbsset)(unsigned char* str, unsigned int c);
unsigned char* (* CDECL p__mbsnbset)(unsigned char *str, unsigned int c, size_t len);
unsigned char* (* CDECL p__mbsnset)(unsigned char* str, unsigned int c, size_t len);
size_t (* CDECL p__mbsnccnt)(const unsigned char* str, size_t len);
size_t (* CDECL p__mbsnbcnt)(const unsigned char* str, size_t len);
unsigned char* (* CDECL p__mbsnbcat)(unsigned char* dst, const unsigned char* src, size_t len);
int (* CDECL p__mbsnbcat_s)(unsigned char *dst, size_t size, const unsigned char *src, size_t len);
unsigned char* (* CDECL p__mbsncat)(unsigned char* dst, const unsigned char* src, size_t len);
unsigned char* (* CDECL p__mbslwr)(unsigned char* s);
int (* CDECL p__mbslwr_s)(unsigned char* s, size_t len);
unsigned char* (* CDECL p__mbsupr)(unsigned char* s);
int (* CDECL p__mbsupr_s)(unsigned char* s, size_t len);
size_t (* CDECL p__mbsspn)(const unsigned char* string, const unsigned char* set);
unsigned char* (* CDECL p__mbsspnp)(const unsigned char* string, const unsigned char* set);
size_t (* CDECL p__mbscspn)(const unsigned char* str, const unsigned char* cmp);
unsigned char* (* CDECL p__mbsrev)(unsigned char* str);
unsigned char* (* CDECL p__mbspbrk)(const unsigned char* str, const unsigned char* accept);
int (* CDECL p_mblen)(const char* str, size_t size);
size_t (* CDECL p_mbrlen)(const char *str, size_t len, void *state);
size_t (* CDECL p__mbstrlen_l)(const char* str, MSVCRT__locale_t locale);
size_t (* CDECL p__mbstrlen)(const char* str);
int (* CDECL p_mbtowc_l)(WCHAR *dst, const char* str, size_t n, MSVCRT__locale_t locale);
int (* CDECL p_mbtowc)(WCHAR *dst, const char* str, size_t n);
size_t (* CDECL p_mbrtowc)(WCHAR *dst, const char *str, size_t n, void *state);
size_t (* CDECL p__mbstowcs_l)(WCHAR *wcstr, const char *mbstr, size_t count, MSVCRT__locale_t locale);
size_t (* CDECL p_mbstowcs)(WCHAR *wcstr, const char *mbstr, size_t count);
int (* CDECL p__mbstowcs_s_l)(size_t *ret, WCHAR *wcstr, size_t size, const char *mbstr, size_t count, MSVCRT__locale_t locale);
int (* CDECL p_mbstowcs_s)(size_t *ret, WCHAR *wcstr, size_t size, const char *mbstr, size_t count);
size_t (* CDECL p_mbsrtowcs)(WCHAR *wcstr, const char **pmbstr, size_t count, void *state);
int (* CDECL p_mbsrtowcs_s)(size_t *ret, WCHAR *wcstr, size_t len, const char **mbstr, size_t count, void *state);
unsigned int (* CDECL p__mbctohira)(unsigned int c);
unsigned int (* CDECL p__mbctokata)(unsigned int c);
void (* CDECL p_type_info_dtor)(void *_this); /* __thiscall */
unsigned __int64 (* CDECL p__strtoui64)(const char *nptr, char **endptr, int base);
unsigned __int64 (* CDECL p__strtoui64_l)(const char *nptr, char **endptr, int base, MSVCRT__locale_t locale);

char * (* CDECL p_getenv)(const char *name);
WCHAR * (* CDECL p__wgetenv)(const WCHAR *name);
int (* CDECL p__putenv)(const char *str);
int (* CDECL p__wputenv)(const WCHAR *str);
int (* CDECL p__putenv_s)(const char *name, const char *value);
int (* CDECL p__wputenv_s)(const WCHAR *name, const WCHAR *value);
int (* CDECL p__dupenv_s)(char **buffer, size_t *numberOfElements, const char *varname);
int (* CDECL p__wdupenv_s)(WCHAR **buffer, size_t *numberOfElements, const WCHAR *varname);
int (* CDECL p_getenv_s)(size_t *pReturnValue, char* buffer, size_t numberOfElements, const char *varname);
int (* CDECL p__wgetenv_s)(size_t *pReturnValue, WCHAR *buffer, size_t numberOfElements, const WCHAR *varname);
int (* CDECL p_setvbuf)(MSVCRT_FILE *file, char *buf, int mode, size_t size);
/* FIXME: Should use __time64_t, but somehow it isn't defined. */
__int64 (* CDECL p__time64)(__int64 *buf);
int (* WINAPIV p_swscanf_s)(const WCHAR *str, const WCHAR *format, ...);
int (* WINAPIV p_swscanf)(wchar_t *str, const wchar_t *fmt, ...);
int (* WINAPIV p_fscanf)(MSVCRT_FILE *file, const char *format, ...);
int (* WINAPIV p_sscanf)(const char *str, const char *format, ...);
int (* WINAPIV p_sscanf_s)(const char *str, const char *format, ...);
MSVCRT_FILE * (* CDECL p___acrt_iob_func)(unsigned idx);
int (* CDECL p__access)(const char *filename, int mode);
int (* CDECL p__access_s)(const char *filename, int mode);
int (* CDECL p__waccess)(const WCHAR *filename, int mode);
int (* CDECL p__waccess_s)(const WCHAR *filename, int mode);
int (* CDECL p__chmod)(const char *path, int flags);
int (* CDECL p__wchmod)(const WCHAR *path, int flags);
int (* CDECL p__unlink)(const char *path);
int (* CDECL p__wunlink)(const WCHAR *path);
int (* CDECL p__commit)(int fd);
int (* CDECL p__flushall)(void);
int (* CDECL p__fflush_nolock)(MSVCRT_FILE* file);
int (* CDECL p__close)(int fd);
int (* CDECL p__dup2)(int od, int nd);
int (* CDECL p__dup)(int od);
int (* CDECL p__eof)(int fd);
int (* CDECL p__fcloseall)(void);
void (* CDECL p__lock_file)(MSVCRT_FILE *file);
void (* CDECL p__unlock_file)(MSVCRT_FILE *file);
int (* CDECL p__locking)(int fd, int mode, LONG nbytes);
int (* CDECL p__fseeki64)(MSVCRT_FILE* file, __int64 offset, int whence);
int (* CDECL p__fseeki64_nolock)(MSVCRT_FILE* file, __int64 offset, int whence);
int (* CDECL p_fseek)(MSVCRT_FILE* file, LONG offset, int whence);
int (* CDECL p__fseek_nolock)(MSVCRT_FILE* file, LONG offset, int whence);
int (* CDECL p__chsize_s)(int fd, __int64 size);
int (* CDECL p__chsize)(int fd, LONG size);
void (* CDECL p_clearerr)(MSVCRT_FILE* file);
void (* CDECL p_rewind)(MSVCRT_FILE* file);
MSVCRT_FILE * (* CDECL p__fdopen)(int fd, const char *mode);
MSVCRT_FILE * (* CDECL p__wfdopen)(int fd, const WCHAR *mode);
LONG (* CDECL p__filelength)(int fd);
__int64 (* CDECL p__filelengthi64)(int fd);
int (* CDECL p__fstat64)(int fd, struct MSVCRT__stat64* buf);
int (* CDECL p__fstati64)(int fd, struct MSVCRT__stati64* buf);
int (* CDECL p__fstat)(int fd, struct MSVCRT__stat* buf);
int (* CDECL p__fstat32)(int fd, struct MSVCRT__stat32* buf);
int (* CDECL p__fstat32i64)(int fd, struct MSVCRT__stat32i64* buf);
int (* CDECL p__fstat64i32)(int fd, struct MSVCRT__stat64i32* buf);
int (* CDECL p__futime64)(int fd, struct MSVCRT__utimbuf64 *t);
int (* CDECL p__futime32)(int fd, struct MSVCRT__utimbuf32 *t);
int (* CDECL p__futime)(int fd, struct MSVCRT__utimbuf64 *t);
intptr_t (* CDECL p__get_osfhandle)(int fd);
int (* CDECL p__mktemp_s)(char *pattern, size_t size);
char * (* CDECL p__mktemp)(char *pattern);
int (* CDECL p__wmktemp_s)(WCHAR *pattern, size_t size);
WCHAR * (* CDECL p__wmktemp)(WCHAR *pattern);
int (* CDECL p__pipe)(int *pfds, unsigned int psize, int textmode);
int (* CDECL p__wsopen_dispatch)(const WCHAR* path, int oflags, int shflags, int pmode, int *fd, int secure);
int (* CDECL p__wsopen_s)(int *fd, const WCHAR* path, int oflags, int shflags, int pmode);
int (* CDECL p__sopen_dispatch)(const char *path, int oflags, int shflags, int pmode, int *fd, int secure);
int (* CDECL p__sopen_s)(int *fd, const char *path, int oflags, int shflags, int pmode);
int (* CDECL p__creat)(const char *path, int pmode);
int (* CDECL p__wcreat)(const WCHAR *path, int pmode);
int (* CDECL p__open_osfhandle)(intptr_t handle, int oflags);
int (* CDECL p__rmtmp)(void);
int (* CDECL p__read)(int fd, void *buf, unsigned int count);
int (* CDECL p__setmode)(int fd,int mode);
int (* CDECL p__stat64)(const char* path, struct MSVCRT__stat64 * buf);
int (* CDECL p_stati64)(const char* path, struct MSVCRT__stati64 * buf);
int (* CDECL p_stat)(const char* path, struct MSVCRT__stat * buf);
int (* CDECL p__stat32)(const char *path, struct MSVCRT__stat32 *buf);
int (* CDECL p__stat32i64)(const char *path, struct MSVCRT__stat32i64 *buf);
int (* CDECL p__stat64i32)(const char* path, struct MSVCRT__stat64i32 *buf);
int (* CDECL p__wstat64)(const WCHAR* path, struct MSVCRT__stat64 * buf);
int (* CDECL p__wstati64)(const WCHAR* path, struct MSVCRT__stati64 * buf);
int (* CDECL p__wstat)(const WCHAR* path, struct MSVCRT__stat * buf);
int (* CDECL p__wstat32)(const WCHAR *path, struct MSVCRT__stat32 *buf);
int (* CDECL p__wstat32i64)(const WCHAR *path, struct MSVCRT__stat32i64 *buf);
int (* CDECL p__wstat64i32)(const WCHAR *path, struct MSVCRT__stat64i32 *buf);
LONG (* CDECL p__tell)(int fd);
__int64 (* CDECL p__telli64)(int fd);
WCHAR * (* CDECL p__wtempnam)(const WCHAR *dir, const WCHAR *prefix);
int (* CDECL p__umask)(int umask);
int (* CDECL p__utime64)(const char* path, struct MSVCRT__utimbuf64 *t);
int (* CDECL p__utime32)(const char* path, struct MSVCRT__utimbuf32 *t);
int (* CDECL p__utime)(const char* path, struct MSVCRT__utimbuf64 *t);
int (* CDECL p__wutime64)(const WCHAR* path, struct MSVCRT__utimbuf64 *t);
int (* CDECL p__wutime32)(const WCHAR* path, struct MSVCRT__utimbuf32 *t);
int (* CDECL p__wutime)(const WCHAR* path, struct MSVCRT__utimbuf64 *t);
int (* CDECL p__putw)(int val, MSVCRT_FILE* file);
int (* CDECL p_fclose)(MSVCRT_FILE* file);
int (* CDECL p__fclose_nolock)(MSVCRT_FILE* file);
int (* CDECL p_feof)(MSVCRT_FILE* file);
int (* CDECL p_ferror)(MSVCRT_FILE* file);
int (* CDECL p__filbuf)(MSVCRT_FILE* file);
int (* CDECL p_fgetc)(MSVCRT_FILE* file);
int (* CDECL p__fgetc_nolock)(MSVCRT_FILE* file);
int (* CDECL p__fgetchar)(void);
char * (* CDECL p_fgets)(char *s, int size, MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p_fgetwc)(MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p__fgetwc_nolock)(MSVCRT_FILE* file);
int (* CDECL p__getw)(MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p_getwc)(MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p__fgetwchar)(void);
MSVCRT_wint_t (* CDECL p_getwchar)(void);
WCHAR * (* CDECL p_fgetws)(WCHAR *s, int size, MSVCRT_FILE* file);
int (* CDECL p__flsbuf)(int c, MSVCRT_FILE* file);
size_t (* CDECL p__fwrite_nolock)(const void *ptr, size_t size, size_t nmemb, MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p_fputwc)(MSVCRT_wint_t wc, MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p__fputwc_nolock)(MSVCRT_wint_t wc, MSVCRT_FILE* file);
MSVCRT_wint_t (* CDECL p__fputwchar)(MSVCRT_wint_t wc);
MSVCRT_FILE * (* CDECL p__wfsopen)(const WCHAR *path, const WCHAR *mode, int share);
MSVCRT_FILE * (* CDECL p__fsopen)(const char *path, const char *mode, int share);
MSVCRT_FILE * (* CDECL p_fopen)(const char *path, const char *mode);
int (* CDECL p_fopen_s)(FILE** pFile, const char *filename, const char *mode);
MSVCRT_FILE * (* CDECL p__wfopen)(const WCHAR *path, const WCHAR *mode);
int (* CDECL p__wfopen_s)(MSVCRT_FILE** pFile, const WCHAR *filename, const WCHAR *mode);
int (* CDECL p_fputc)(int c, MSVCRT_FILE* file);
int (* CDECL p__fputc_nolock)(int c, MSVCRT_FILE* file);
int (* CDECL p__fputchar)(int c);
size_t (* CDECL p__fread_nolock)(void *ptr, size_t size, size_t nmemb, MSVCRT_FILE* file);
size_t (* CDECL p_fread_s)(void *buf, size_t buf_size, size_t elem_size, size_t count, MSVCRT_FILE *stream);
size_t (* CDECL p__fread_nolock_s)(void *buf, size_t buf_size, size_t elem_size, size_t count, MSVCRT_FILE *stream);
MSVCRT_FILE * (* CDECL p__wfreopen)(const WCHAR *path, const WCHAR *mode, MSVCRT_FILE* file);
int (* CDECL p__wfreopen_s)(MSVCRT_FILE** pFile, const WCHAR *path, const WCHAR *mode, MSVCRT_FILE* file);
MSVCRT_FILE * (* CDECL p_freopen)(const char *path, const char *mode, MSVCRT_FILE* file);
int (* CDECL p_freopen_s)(MSVCRT_FILE** pFile, const char *path, const char *mode, MSVCRT_FILE* file);
int (* CDECL p_fsetpos)(MSVCRT_FILE* file, fpos_t *pos);
__int64 (* CDECL p__ftelli64)(MSVCRT_FILE* file);
__int64 (* CDECL p__ftelli64_nolock)(MSVCRT_FILE* file);
LONG (* CDECL p_ftell)(MSVCRT_FILE* file);
LONG (* CDECL p__ftell_nolock)(MSVCRT_FILE* file);
int (* CDECL p_fgetpos)(MSVCRT_FILE* file, fpos_t *pos);
int (* CDECL p_fputs)(const char *s, MSVCRT_FILE* file);
int (* CDECL p_fputws)(const WCHAR *s, MSVCRT_FILE* file);
int (* CDECL p_getchar)(void);
int (* CDECL p_getc)(MSVCRT_FILE* file);
char * (* CDECL p_gets)(char *buf);
WCHAR* (* CDECL p__getws)(WCHAR* buf);
int (* CDECL p_putc)(int c, MSVCRT_FILE* file);
int (* CDECL p_putchar)(int c);
int (* CDECL p__putws)(const WCHAR *s);
int (* CDECL p_remove)(const char *path);
int (* CDECL p__wremove)(const WCHAR *path);
int (* CDECL p_rename)(const char *oldpath,const char *newpath);
int (* CDECL p__wrename)(const WCHAR *oldpath,const WCHAR *newpath);
void (* CDECL p_setbuf)(MSVCRT_FILE* file, char *buf);
int (* CDECL p_tmpnam_s)(char *s, size_t size);
char * (* CDECL p_tmpnam)(char *s);
int (* CDECL p__wtmpnam_s)(WCHAR *s, size_t size);
WCHAR * (* CDECL p__wtmpnam)(WCHAR *s);
MSVCRT_FILE * (* CDECL p_tmpfile)(void);
int (* CDECL p_tmpfile_s)(MSVCRT_FILE** file);
int (* CDECL p_ungetc)(int c, MSVCRT_FILE * file);
int (* CDECL p__ungetc_nolock)(int c, MSVCRT_FILE * file);
MSVCRT_wint_t (* CDECL p_ungetwc)(MSVCRT_wint_t wc, MSVCRT_FILE * file);
MSVCRT_wint_t (* CDECL p__ungetwc_nolock)(MSVCRT_wint_t wc, MSVCRT_FILE * file);
int (* CDECL p__getmaxstdio)(void);
int (* CDECL p__setmaxstdio)(int newmax);
int (* CDECL p__get_stream_buffer_pointers)(MSVCRT_FILE *file, char*** base, char*** ptr, int** count);
int* (* CDECL p___sys_nerr)(void);
char** (* CDECL p___sys_errlist)(void);
int* (* CDECL p__errno)(void);
ULONG* (* CDECL p___doserrno)(void);
int (* CDECL p__get_errno)(int *pValue);
int (* CDECL p__get_doserrno)(int *pValue);
int (* CDECL p__set_errno)(int value);
int (* CDECL p__set_error_mode)(int mode);
int (* CDECL p__set_doserrno)(int value);
char* (* CDECL p_strerror)(int err);
int (* CDECL p_strerror_s)(char *buffer, size_t numberOfElements, int errnum);
char* (* CDECL p__strerror)(const char* str);
void (* CDECL p_perror)(const char* str);
void (* CDECL p__wperror)(const WCHAR* str);
int (* CDECL p__wcserror_s)(WCHAR* buffer, size_t nc, int err);
WCHAR* (* CDECL p__wcserror)(int err);
int (* CDECL p___wcserror_s)(WCHAR* buffer, size_t nc, const WCHAR* str);
WCHAR* (* CDECL p___wcserror)(const WCHAR* str);
void (* CDECL p__seterrormode)(int mode);
void (* CDECL p__invalid_parameter_noinfo)(void);
void (* CDECL p__invalid_parameter_noinfo_noreturn)(void);
MSVCRT_invalid_parameter_handler (* CDECL p__get_invalid_parameter_handler)(void);
MSVCRT_invalid_parameter_handler (* CDECL p__set_invalid_parameter_handler)(MSVCRT_invalid_parameter_handler handler);
MSVCRT_invalid_parameter_handler (* CDECL p__get_thread_local_invalid_parameter_handler)(void);
MSVCRT_invalid_parameter_handler (* CDECL p__set_thread_local_invalid_parameter_handler)(MSVCRT_invalid_parameter_handler handler);
void *(* CDECL p_bsearch)(const void *key, const void *base, size_t nmemb,
        size_t size, int (CDECL *compare)(const void *, const void *));
int (* CDECL p__chdir)(const char * newdir);
int (* CDECL p__wchdir)(const WCHAR * newdir);
int (* CDECL p__chdrive)(int newdrive);
int (* CDECL p__findclose)(intptr_t hand);
intptr_t (* CDECL p__findfirst)(const char * fspec, struct MSVCRT__finddata_t* ft);
intptr_t (* CDECL p__findfirst32)(const char * fspec, struct MSVCRT__finddata32_t* ft);
intptr_t (* CDECL p__wfindfirst)(const WCHAR * fspec, struct MSVCRT__wfinddata_t* ft);
intptr_t (* CDECL p__wfindfirst32)(const WCHAR * fspec, struct MSVCRT__wfinddata32_t* ft);
intptr_t (* CDECL p__findfirsti64)(const char * fspec, struct MSVCRT__finddatai64_t* ft);
intptr_t (* CDECL p__findfirst64)(const char * fspec, struct MSVCRT___finddata64_t* ft);
intptr_t (* CDECL p__wfindfirst64)(const WCHAR * fspec, struct MSVCRT__wfinddata64_t* ft);
intptr_t (* CDECL p__findfirst64i32)(const char * fspec, struct MSVCRT__finddata64i32_t* ft);
intptr_t (* CDECL p__wfindfirst64i32)(const WCHAR * fspec, struct MSVCRT__wfinddata64i32_t* ft);
intptr_t (* CDECL p__wfindfirsti64)(const WCHAR * fspec, struct MSVCRT__wfinddatai64_t* ft);
int (* CDECL p__findnext)(intptr_t hand, struct MSVCRT__finddata_t * ft);
int (* CDECL p__findnext32)(intptr_t hand, struct MSVCRT__finddata32_t * ft);
int (* CDECL p__wfindnext32)(intptr_t hand, struct MSVCRT__wfinddata32_t * ft);
int (* CDECL p__wfindnext)(intptr_t hand, struct MSVCRT__wfinddata_t * ft);
int (* CDECL p__findnexti64)(intptr_t hand, struct MSVCRT__finddatai64_t * ft);
int (* CDECL p__findnext64)(intptr_t hand, struct MSVCRT___finddata64_t * ft);
int (* CDECL p__wfindnext64)(intptr_t hand, struct MSVCRT__wfinddata64_t * ft);
int (* CDECL p__findnext64i32)(intptr_t hand, struct MSVCRT__finddata64i32_t * ft);
int (* CDECL p__wfindnexti64)(intptr_t hand, struct MSVCRT__wfinddatai64_t * ft);
int (* CDECL p__wfindnext64i32)(intptr_t hand, struct MSVCRT__wfinddata64i32_t * ft);
char* (* CDECL p__getcwd)(char * buf, int size);
WCHAR* (* CDECL p__wgetcwd)(WCHAR * buf, int size);
int (* CDECL p__getdrive)(void);
char* (* CDECL p__getdcwd)(int drive, char * buf, int size);
WCHAR* (* CDECL p__wgetdcwd)(int drive, WCHAR * buf, int size);
unsigned int (* CDECL p__getdiskfree)(unsigned int disk, struct MSVCRT__diskfree_t * d);
int (* CDECL p__mkdir)(const char * newdir);
int (* CDECL p__wmkdir)(const WCHAR* newdir);
int (* CDECL p__rmdir)(const char * dir);
int (* CDECL p__wrmdir)(const WCHAR * dir);
int (* CDECL p__splitpath_s)(const char* inpath, char* drive, size_t sz_drive, char* dir, size_t sz_dir, char* fname, size_t sz_fname, char* ext, size_t sz_ext);
void (* CDECL p__splitpath)(const char *inpath, char *drv, char *dir, char *fname, char *ext);
int (* CDECL p__wsplitpath_s)(const WCHAR* inpath, WCHAR* drive, size_t sz_drive, WCHAR* dir, size_t sz_dir, WCHAR* fname, size_t sz_fname, WCHAR* ext, size_t sz_ext);
void (* CDECL p__wsplitpath)(const WCHAR *inpath, WCHAR *drv, WCHAR *dir, WCHAR *fname, WCHAR *ext);
WCHAR * (* CDECL p__wfullpath)(WCHAR * absPath, const WCHAR* relPath, size_t size);
char * (* CDECL p__fullpath)(char * absPath, const char* relPath, unsigned int size);
VOID (* CDECL p__makepath)(char * path, const char * drive, const char *directory, const char * filename, const char * extension);
VOID (* CDECL p__wmakepath)(WCHAR *path, const WCHAR *drive, const WCHAR *directory, const WCHAR *filename, const WCHAR *extension);
int (* CDECL p__makepath_s)(char *path, size_t size, const char *drive, const char *directory, const char *filename, const char *extension);
int (* CDECL p__wmakepath_s)(WCHAR *path, size_t size, const WCHAR *drive, const WCHAR *directory, const WCHAR *filename, const WCHAR *extension);
void (* CDECL p__searchenv)(const char* file, const char* env, char *buf);
int (* CDECL p__searchenv_s)(const char* file, const char* env, char *buf, size_t count);
void (* CDECL p__wsearchenv)(const WCHAR* file, const WCHAR* env, WCHAR *buf);
int (* CDECL p__wsearchenv_s)(const WCHAR* file, const WCHAR* env, WCHAR *buf, size_t count);
intptr_t (* CDECL p__cwait)(int *status, intptr_t pid, int action);
intptr_t (* CDECL p__wexecv)(const WCHAR* name, const WCHAR* const* argv);
intptr_t (* CDECL p__execv)(const char* name, const char* const* argv);
intptr_t (* CDECL p__wexecve)(const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv);
intptr_t (* CDECL p__execve)(const char* name, const char* const* argv, const char* const* envv);
intptr_t (* CDECL p__wexecvpe)(const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv);
intptr_t (* CDECL p__execvpe)(const char* name, const char* const* argv, const char* const* envv);
intptr_t (* CDECL p__wexecvp)(const WCHAR* name, const WCHAR* const* argv);
intptr_t (* CDECL p__execvp)(const char* name, const char* const* argv);
intptr_t (* CDECL p__spawnve)(int flags, const char* name, const char* const* argv, const char* const* envv);
intptr_t (* CDECL p__wspawnve)(int flags, const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv);
intptr_t (* CDECL p__spawnv)(int flags, const char* name, const char* const* argv);
intptr_t (* CDECL p__wspawnv)(int flags, const WCHAR* name, const WCHAR* const* argv);
intptr_t (* CDECL p__spawnvpe)(int flags, const char* name, const char* const* argv, const char* const* envv);
intptr_t (* CDECL p__wspawnvpe)(int flags, const WCHAR* name, const WCHAR* const* argv, const WCHAR* const* envv);
intptr_t (* CDECL p__spawnvp)(int flags, const char* name, const char* const* argv);
intptr_t (* CDECL p__wspawnvp)(int flags, const WCHAR* name, const WCHAR* const* argv);
MSVCRT_FILE* (* CDECL p__wpopen)(const WCHAR* command, const WCHAR* mode);
MSVCRT_FILE* (* CDECL p__popen)(const char* command, const char* mode);
int (* CDECL p__pclose)(MSVCRT_FILE* file);
int (* CDECL p__wsystem)(const WCHAR* cmd);
int (* CDECL p_system)(const char* cmd);
intptr_t (* CDECL p__loaddll)(const char* dllname);
int (* CDECL p__unloaddll)(intptr_t dll);
void * (* CDECL p__getdllprocaddr)(intptr_t dll, const char *name, int ordinal);
int (* CDECL p__getpid)(void);
int (* CDECL p__crtTerminateProcess)(UINT exit_code);
int (* WINAPIV p__open)(const char *path, int flags, ...);

thread_data_t* (* CDECL p__getptd)(void);
void (* CDECL p__endthread)(void);
void (* CDECL p__endthreadex)(unsigned int retval);
uintptr_t (* CDECL p__beginthread)(MSVCRT__beginthread_start_routine_t start_address, void *arglist);
uintptr_t (* CDECL p__beginthreadex)(void *security, unsigned int stack_size, MSVCRT__beginthreadex_start_routine_t start_address, void *arglist, unsigned int initflag, unsigned int *thrdaddr);

int (* CDECL p__cputs)(const char* str);
int (* CDECL p__cputws)(const WCHAR* str);
int (* CDECL p__getch_nolock)(void);
int (* CDECL p__getch)(void);
WCHAR (* CDECL p__getwch_nolock)(void);
WCHAR (* CDECL p__getwch)(void);
int (* CDECL p__putch_nolock)(int c);
int (* CDECL p__putch)(int c);
WCHAR (* CDECL p__putwch_nolock)(WCHAR c);
WCHAR (* CDECL p__putwch)(WCHAR c);
int (* CDECL p__getche_nolock)(void);
int (* CDECL p__getche)(void);
WCHAR (* CDECL p__getwche_nolock)(void);
WCHAR (* CDECL p__getwche)(void);
char* (* CDECL p__cgets)(char* str);
int (* CDECL p__ungetch_nolock)(int c);
int (* CDECL p__ungetch)(int c);
WCHAR (* CDECL p__ungetwch_nolock)(WCHAR c);
WCHAR (* CDECL p__ungetwch)(WCHAR c);
int (* CDECL p__kbhit)(void);

Context* (* CDECL p_Context_CurrentContext)(void);
unsigned int (* CDECL p_Context_Id)(void);
void (* CDECL p_Context_Block)(void);
void (* CDECL p_Context_Yield)(void);
void (* CDECL p_Context__SpinYield)(void);
BOOL (* CDECL p_Context_IsCurrentTaskCollectionCanceling)(void);
void (* CDECL p_Context_Oversubscribe)(BOOL begin);
unsigned int (* CDECL p_Context_ScheduleGroupId)(void);
unsigned int (* CDECL p_Context_VirtualProcessorId)(void);
void * (* CDECL p_Concurrency_Alloc)(size_t size);
void (* CDECL p_Concurrency_Free)(void* mem);
Scheduler* (* CDECL p_Scheduler_Create)(const SchedulerPolicy *policy);
void (* CDECL p_Scheduler_ResetDefaultSchedulerPolicy)(void);
void (* CDECL p_Scheduler_SetDefaultSchedulerPolicy)(const SchedulerPolicy *policy);
void (* CDECL p_CurrentScheduler_Create)(const SchedulerPolicy *policy);
void (* CDECL p_CurrentScheduler_Detach)(void);
Scheduler* (* CDECL p_CurrentScheduler_Get)(void);
void* (* CDECL p_CurrentScheduler_CreateScheduleGroup)(void);
unsigned int (* CDECL p_CurrentScheduler_GetNumberOfVirtualProcessors)(void);
SchedulerPolicy* (* CDECL p_CurrentScheduler_GetPolicy)(SchedulerPolicy *policy);
unsigned int (* CDECL p_CurrentScheduler_Id)(void);
BOOL (* CDECL p_CurrentScheduler_IsAvailableLocation)(const void *placement);
void (* CDECL p_CurrentScheduler_RegisterShutdownEvent)(HANDLE event);
_Scheduler* (* CDECL p__CurrentScheduler__Get)(_Scheduler *ret);
unsigned int (* CDECL p__CurrentScheduler__GetNumberOfVirtualProcessors)(void);
unsigned int (* CDECL p__CurrentScheduler__Id)(void);
char* (* CDECL p___unDNameEx)(char* buffer, const char* mangled, int buflen, malloc_func_t memget, free_func_t memfree, void* unknown, unsigned short int flags);
char* (* CDECL p___unDName)(char* buffer, const char* mangled, int buflen, malloc_func_t memget, free_func_t memfree, unsigned short int flags);

int (* CDECL p__get_printf_count_output)(void);
int (* CDECL p__set_printf_count_output)(int enable);
WCHAR* (* CDECL p__wcsdup)(const WCHAR* str);
INT (* CDECL p__wcsicmp_l)(const WCHAR *str1, const WCHAR *str2, MSVCRT__locale_t locale);
INT (* CDECL p__wcsicmp)(const WCHAR* str1, const WCHAR* str2);
INT (* CDECL p__wcsnicmp_l)(const WCHAR *str1, const WCHAR *str2, INT n, MSVCRT__locale_t locale);
int (* CDECL p__wcsicoll_l)(const WCHAR* str1, const WCHAR* str2, MSVCRT__locale_t locale);
INT (* CDECL p__wcsicoll)(const WCHAR* str1, const WCHAR* str2);
int (* CDECL p__wcsnicoll_l)(const WCHAR* str1, const WCHAR* str2, size_t count, MSVCRT__locale_t locale);
INT (* CDECL p__wcsnicoll)(const WCHAR* str1, const WCHAR* str2, size_t count);
WCHAR* (* CDECL p__wcsnset)(WCHAR* str, WCHAR c, size_t n);
WCHAR* (* CDECL p__wcsrev)(WCHAR* str);
int (* CDECL p__wcsset_s)(WCHAR *str, size_t n, WCHAR c);
WCHAR* (* CDECL p__wcsset)(WCHAR* str, WCHAR c);
int (* CDECL p__wcsupr_s_l)(WCHAR* str, size_t n, MSVCRT__locale_t locale);
INT (* CDECL p__wcsupr_s)(WCHAR* str, size_t n);
WCHAR* (* CDECL p__wcsupr_l)(WCHAR *str, MSVCRT__locale_t locale);
int (* CDECL p__wcslwr_s_l)(WCHAR* str, size_t n, MSVCRT__locale_t locale);
int (* CDECL p__wcslwr_s)(WCHAR* str, size_t n);
WCHAR* (* CDECL p__wcslwr_l)(WCHAR* str, MSVCRT__locale_t locale);
WCHAR* (* CDECL p__wcslwr)(WCHAR* str);
int (* CDECL p__wcsncoll_l)(const WCHAR* str1, const WCHAR* str2, size_t count, MSVCRT__locale_t locale);
int (* CDECL p__wcsncoll)(const WCHAR* str1, const WCHAR* str2, size_t count);
double (* CDECL p__wcstod_l)(const WCHAR* str, WCHAR** end, MSVCRT__locale_t locale);
size_t (* CDECL p__wcstombs_l)(char *mbstr, const WCHAR *wcstr, size_t count, MSVCRT__locale_t locale);
size_t (* CDECL p_wcstombs)(char *mbstr, const WCHAR *wcstr, size_t count);
size_t (* CDECL p_wcsrtombs)(char *mbstr, const WCHAR **wcstr, size_t count, MSVCRT_mbstate_t *mbstate);
int (* CDECL p__wcstombs_s_l)(size_t *ret, char *mbstr, size_t size, const WCHAR *wcstr, size_t count, MSVCRT__locale_t locale);
int (* CDECL p_wcstombs_s)(size_t *ret, char *mbstr, size_t size, const WCHAR *wcstr, size_t count);
int (* CDECL p_wcsrtombs_s)(size_t *ret, char *mbstr, size_t size, const WCHAR **wcstr, size_t count, MSVCRT_mbstate_t *mbstate);
double (* CDECL p__wtof_l)(const WCHAR *str, MSVCRT__locale_t locale);
float (* CDECL p__wcstof_l)(const WCHAR *str, WCHAR **end, MSVCRT__locale_t locale);
float (* CDECL p_wcstof)(const WCHAR *str, WCHAR **end);
int (* CDECL p__wcscoll_l)(const WCHAR* str1, const WCHAR* str2, MSVCRT__locale_t locale);
int (* CDECL p_wcscoll)(const WCHAR* str1, const WCHAR* str2);
WCHAR* (* CDECL p_wcspbrk)(const WCHAR* str, const WCHAR* accept);
WCHAR * (* CDECL p_wcstok_s)(WCHAR *str, const WCHAR *delim, WCHAR **next_token);
WCHAR * (* CDECL p_wcstok)(WCHAR *str, const WCHAR *delim);
int (* CDECL p__wctomb_s_l)(int *len, char *mbchar, size_t size, WCHAR wch, MSVCRT__locale_t locale);
int (* CDECL p_wctomb_s)(int *len, char *mbchar, size_t size, WCHAR wch);
int (* CDECL p__wctomb_l)(char *dst, WCHAR ch, MSVCRT__locale_t locale);
INT (* CDECL p_wctomb)(char *dst, WCHAR ch);
INT (* CDECL p_wctob)(MSVCRT_wint_t wchar);
size_t (* CDECL p_wcrtomb)(char *dst, WCHAR ch, MSVCRT_mbstate_t *s);
INT (* CDECL p_iswalnum)(WCHAR wc);
INT (* CDECL p_iswalpha)(WCHAR wc);
INT (* CDECL p__iswalpha_l)(WCHAR wc, MSVCRT__locale_t locale);
INT (* CDECL p_iswcntrl)(WCHAR wc);
INT (* CDECL p_iswdigit)(WCHAR wc);
INT (* CDECL p__iswdigit_l)(WCHAR wc, MSVCRT__locale_t locale);
INT (* CDECL p_iswgraph)(WCHAR wc);
INT (* CDECL p_iswlower)(WCHAR wc);
INT (* CDECL p_iswprint)(WCHAR wc);
INT (* CDECL p__iswpunct_l)(WCHAR wc, MSVCRT__locale_t locale);
INT (* CDECL p_iswpunct)(WCHAR wc);
INT (* CDECL p__iswspace_l)(WCHAR wc, MSVCRT__locale_t locale);
INT (* CDECL p_iswspace)(WCHAR wc);
INT (* CDECL p_iswupper)(WCHAR wc);
INT (* CDECL p_iswxdigit)(WCHAR wc);
INT (* CDECL p__iswctype_l)(WCHAR wc, MSVCRT_wctype_t type, MSVCRT__locale_t locale);
INT (* CDECL p__iswblank_l)(WCHAR wc, MSVCRT__locale_t locale);
INT (* CDECL p_iswblank)(WCHAR wc);
INT (* CDECL p_wcsncpy_s)(WCHAR* wcDest, size_t numElement, const WCHAR *wcSrc, size_t count);
INT (* CDECL p_wcsncat_s)(WCHAR *dst, size_t elem, const WCHAR *src, size_t count);
__int64 (* CDECL p__wcstoi64_l)(const WCHAR *nptr, WCHAR **endptr, int base, MSVCRT__locale_t locale);
__int64 (* CDECL p__wcstoi64)(const WCHAR *nptr, WCHAR **endptr, int base);
LONG (* CDECL p__wcstol_l)(const WCHAR *s, WCHAR **end, int base, MSVCRT__locale_t locale);
unsigned __int64 (* CDECL p__wcstoui64_l)(const WCHAR *nptr, WCHAR **endptr, int base, MSVCRT__locale_t locale);
unsigned __int64 (* CDECL p__wcstoui64)(const WCHAR *nptr, WCHAR **endptr, int base);
size_t (* CDECL p_wcsnlen)(const WCHAR *s, size_t maxlen);
int (* CDECL p__towupper_l)(MSVCRT_wint_t c, MSVCRT__locale_t locale);
int (* CDECL p_towupper)(MSVCRT_wint_t c);
int (* CDECL p__towlower_l)(MSVCRT_wint_t c, MSVCRT__locale_t locale);
int (* CDECL p_towlower)(MSVCRT_wint_t c);
WCHAR* (* CDECL p_wcschr)(const WCHAR *str, WCHAR ch);
int (* CDECL p_wcslen)(const WCHAR *str);
__int64 (* CDECL p__wtoi64_l)(const WCHAR *str, MSVCRT__locale_t locale);
__int64 (* CDECL p__wtoi64)(const WCHAR *str);
size_t (* CDECL p__wcsxfrm_l)(WCHAR *dest, const WCHAR *src, size_t len, MSVCRT__locale_t locale);
size_t (* CDECL p_wcsxfrm)(WCHAR *dest, const WCHAR *src, size_t len);
WCHAR* (* CDECL p_wcsncpy)(WCHAR* s1, const WCHAR *s2, size_t n);
int (* CDECL p__wtoi_l)(const WCHAR *str, MSVCRT__locale_t locale);
LONG (* CDECL p__wtol_l)(const WCHAR *str, MSVCRT__locale_t locale);
LONG (* CDECL p__wtol)(const WCHAR *str);
LONGLONG (* CDECL p__wtoll_l)(const WCHAR *str, MSVCRT__locale_t locale);
LONGLONG (* CDECL p__wtoll)(const WCHAR *str);
ULONG (* CDECL p__wcstoul_l)(const WCHAR *s, WCHAR **end, int base, MSVCRT__locale_t locale);
ULONG (* CDECL p_wcstoul)(const WCHAR *s, WCHAR **end, int base);

void (* CDECL p__tzset)(void);
MSVCRT___time64_t (* CDECL p__mktime64)(struct MSVCRT_tm *mstm);
MSVCRT___time32_t (* CDECL p__mktime32)(struct MSVCRT_tm *mstm);
MSVCRT___time64_t (* CDECL p_mktime)(struct MSVCRT_tm *mstm);
MSVCRT___time64_t (* CDECL p__mkgmtime64)(struct MSVCRT_tm *time);
MSVCRT___time32_t (* CDECL p__mkgmtime32)(struct MSVCRT_tm *time);
MSVCRT___time32_t (* CDECL p__mkgmtime)(struct MSVCRT_tm *time);
int (* CDECL p__localtime64_s)(struct MSVCRT_tm *res, const MSVCRT___time64_t *secs);
struct MSVCRT_tm* (* CDECL p__localtime64)(const MSVCRT___time64_t* secs);
struct MSVCRT_tm* (* CDECL p__localtime32)(const MSVCRT___time32_t* secs);
int (* CDECL p__localtime32_s)(struct MSVCRT_tm *time, const MSVCRT___time32_t *secs);
struct MSVCRT_tm* (* CDECL p_localtime)(const MSVCRT___time64_t* secs);
int (* CDECL p__gmtime64_s)(struct MSVCRT_tm *res, const MSVCRT___time64_t *secs);
struct MSVCRT_tm* (* CDECL p__gmtime64)(const MSVCRT___time64_t *secs);
int (* CDECL p__gmtime32_s)(struct MSVCRT_tm *res, const MSVCRT___time32_t *secs);
struct MSVCRT_tm* (* CDECL p__gmtime32)(const MSVCRT___time32_t* secs);
struct MSVCRT_tm* (* CDECL p_gmtime)(const MSVCRT___time64_t* secs);
char* (* CDECL p__strdate)(char* date);
int (* CDECL p__strdate_s)(char* date, size_t size);
WCHAR* (* CDECL p__wstrdate)(WCHAR* date);
int (* CDECL p__wstrdate_s)(WCHAR* date, size_t size);
char* (* CDECL p__strtime)(char* time);
int (* CDECL p__strtime_s)(char* time, size_t size);
WCHAR* (* CDECL p__wstrtime)(WCHAR* time);
int (* CDECL p__wstrtime_s)(WCHAR* time, size_t size);
MSVCRT_clock_t (* CDECL p_clock)(void);
double (* CDECL p__difftime64)(MSVCRT___time64_t time1, MSVCRT___time64_t time2);
double (* CDECL p__difftime32)(MSVCRT___time32_t time1, MSVCRT___time32_t time2);
double (* CDECL p_difftime)(MSVCRT___time64_t time1, MSVCRT___time64_t time2);
void (* CDECL p__ftime64)(struct MSVCRT___timeb64 *buf);
int (* CDECL p__ftime64_s)(struct MSVCRT___timeb64 *buf);
void (* CDECL p__ftime32)(struct MSVCRT___timeb32 *buf);
int (* CDECL p__ftime32_s)(struct MSVCRT___timeb32 *buf);
void (* CDECL p__ftime)(struct MSVCRT___timeb64 *buf);
MSVCRT___time64_t (* CDECL p__time64)(MSVCRT___time64_t *buf);
MSVCRT___time32_t (* CDECL p__time32)(MSVCRT___time32_t *buf);
MSVCRT___time64_t (* CDECL p_time)(MSVCRT___time64_t* buf);
int * (* CDECL p___p__daylight)(void);
int * (* CDECL p___p__dstbias)(void);
int (* CDECL p__get_dstbias)(int *seconds);
LONG * (* CDECL p___p__timezone)(void);
int (* CDECL p__get_tzname)(size_t *ret, char *buf, size_t bufsize, int index);
char ** (* CDECL p___p__tzname)(void);
size_t (* CDECL p__strftime_l)(char *str, size_t max, const char *format, const struct MSVCRT_tm *mstm, MSVCRT__locale_t loc);
size_t (* CDECL p__Strftime)(char *str, size_t max, const char *format, const struct MSVCRT_tm *mstm, MSVCRT___lc_time_data *time_data);
size_t (* CDECL p_strftime)(char *str, size_t max, const char *format, const struct MSVCRT_tm *mstm);
size_t (* CDECL p__wcsftime_l)(WCHAR *str, size_t max, const WCHAR *format, const struct MSVCRT_tm *mstm, MSVCRT__locale_t loc);
size_t (* CDECL p_wcsftime)(WCHAR *str, size_t max, const WCHAR *format, const struct MSVCRT_tm *mstm);
size_t (* CDECL p__Wcsftime)(WCHAR *str, size_t max, const WCHAR *format, const struct MSVCRT_tm *mstm, MSVCRT___lc_time_data *time_data);
char * (* CDECL p_asctime)(const struct MSVCRT_tm *mstm);
int (* CDECL p_asctime_s)(char* time, size_t size, const struct MSVCRT_tm *mstm);
WCHAR * (* CDECL p__wasctime)(const struct MSVCRT_tm *mstm);
int (* CDECL p__wasctime_s)(WCHAR* time, size_t size, const struct MSVCRT_tm *mstm);
char * (* CDECL p__ctime64)(const MSVCRT___time64_t *time);
int (* CDECL p__ctime64_s)(char *res, size_t len, const MSVCRT___time64_t *time);
char * (* CDECL p__ctime32)(const MSVCRT___time32_t *time);
int (* CDECL p__ctime32_s)(char *res, size_t len, const MSVCRT___time32_t *time);
char * (* CDECL p_ctime)(const MSVCRT___time64_t *time);
WCHAR * (* CDECL p__wctime64)(const MSVCRT___time64_t *time);
WCHAR * (* CDECL p__wctime32)(const MSVCRT___time32_t *time);
WCHAR * (* CDECL p__wctime)(const MSVCRT___time64_t *time);
int (* CDECL p__wctime64_s)(WCHAR *buf, size_t size, const MSVCRT___time64_t *time);
int (* CDECL p__wctime32_s)(WCHAR *buf, size_t size, const MSVCRT___time32_t *time);
int (* CDECL p__get_timezone)(LONG *timezone);
int (* CDECL p__get_daylight)(int *hours);
void* (* CDECL p_operator_new)(size_t size);
void* (* CDECL p_operator_new_dbg)(size_t size, int type, const char *file, int line);
void (* CDECL p_operator_delete)(void *mem);
MSVCRT_new_handler_func (* CDECL p__query_new_handler)(void);
int (* CDECL p__query_new_mode)(void);
MSVCRT_new_handler_func (* CDECL p__set_new_handler)(MSVCRT_new_handler_func func);
MSVCRT_new_handler_func (* CDECL p_set_new_handler)(void *func);
int (* CDECL p__set_new_mode)(int mode);
int (* CDECL p__callnewh)(size_t size);
void* (* CDECL p__expand)(void* mem, size_t size);
int (* CDECL p__heapchk)(void);
int (* CDECL p__heapmin)(void);
int (* CDECL p__heapwalk)(struct MSVCRT__heapinfo* next);
int (* CDECL p__heapset)(unsigned int value);
int (* CDECL p__heapadd)(void* mem, size_t size);
intptr_t (* CDECL p__get_heap_handle)(void);
size_t (* CDECL p__msize)(void* mem);
size_t (* CDECL p__aligned_msize)(void *p, size_t alignment, size_t offset);
void* (* CDECL p_calloc)(size_t count, size_t size);
void* (* CDECL p__calloc_base)(size_t count, size_t size);
void (* CDECL p_free)(void* ptr);
void (* CDECL p__free_base)(void* ptr);
void* (* CDECL p_malloc)(size_t size);
void* (* CDECL p__malloc_base)(size_t size);
void* (* CDECL p_realloc)(void* ptr, size_t size);
void* (* CDECL p__realloc_base)(void* ptr, size_t size);
void* (* CDECL p__recalloc)(void *mem, size_t num, size_t size);
unsigned int* (* CDECL p___p__amblksiz)(void);
size_t (* CDECL p__get_sbh_threshold)(void);
int (* CDECL p__set_sbh_threshold)(size_t threshold);
void (* CDECL p__aligned_free)(void *memblock);
void * (* CDECL p__aligned_offset_malloc)(size_t size, size_t alignment, size_t offset);
void * (* CDECL p__aligned_malloc)(size_t size, size_t alignment);
void * (* CDECL p__aligned_offset_realloc)(void *memblock, size_t size, size_t alignment, size_t offset);
void * (* CDECL p__aligned_realloc)(void *memblock, size_t size, size_t alignment);
int (* CDECL p_memmove_s)(void *dest, size_t numberOfElements, const void *src, size_t count);
int (* CDECL p_wmemmove_s)(WCHAR *dest, size_t numberOfElements, const WCHAR *src, size_t count);
int (* CDECL p_memcpy_s)(void *dest, size_t numberOfElements, const void *src, size_t count);
int (* CDECL p_wmemcpy_s)(WCHAR *dest, size_t numberOfElements, const WCHAR *src, size_t count);
int (* CDECL p_strncpy_s)(char *dest, size_t numberOfElements, const char *src, size_t count);

unsigned int (* CDECL p_SpinCount__Value)(void);
unsigned int (* CDECL p__GetConcurrency)(void);
int (* CDECL p_event_wait_for_multiple)(void **events, size_t count, BOOL wait_all, unsigned int timeout);
void (* CDECL p__Lock_shared_ptr_spin_lock)(void);
void (* CDECL p__Unlock_shared_ptr_spin_lock)(void);

int (* CDECL p__strlwr_s_l)(char *str, size_t len, MSVCRT__locale_t locale);
int (* CDECL p__strlwr_s)(char *str, size_t len);
char* CDECL (* CDECL p__strlwr_l)(char *str, MSVCRT__locale_t locale);
char* (* CDECL p__strlwr)(char *str);
int (* CDECL p__strupr_s_l)(char *str, size_t len, MSVCRT__locale_t locale);
int (* CDECL p__strupr_s)(char *str, size_t len);
char* (* CDECL p__strupr_l)(char *str, MSVCRT__locale_t locale);
char* (* CDECL p__strupr)(char *str);
int (* CDECL p__strnset_s)(char *str, size_t size, int c, size_t count);
char* (* CDECL p__strnset)(char* str, int value, size_t len);
char* (* CDECL p__strrev)(char* str);
char* CDECL (* CDECL p__strset)(char* str, int value);
char * (* CDECL p_strtok)(char *str, const char *delim);
char * (* CDECL p_strtok_s)(char *str, const char *delim, char **ctx);
void (* CDECL p__swab)(char* src, char* dst, int len);
double (* CDECL p_strtod_l)(const char *str, char **end, MSVCRT__locale_t locale);
float (* CDECL p__strtof_l)(const char *str, char **end, MSVCRT__locale_t locale);
float (* CDECL p_strtof)(const char *str, char **end);
void (* CDECL p__assert)(const char* str, const char* file, unsigned int line);
void (* CDECL p__wassert)(const wchar_t* str, const wchar_t* file, unsigned int line);
double (* CDECL p__atof_l)(const char *str, MSVCRT__locale_t locale);
int (* CDECL p__atoflt_l)(FLOAT *value, char *str, MSVCRT__locale_t locale);
int (* CDECL p__atoflt)(FLOAT *value, char *str);
int (* CDECL p__atodbl_l)(DOUBLE *value, char *str, MSVCRT__locale_t locale);
int (* CDECL p__atodbl)(DOUBLE *value, char *str);
int (* CDECL p_strcoll_l)(const char* str1, const char* str2, MSVCRT__locale_t locale);
int (* CDECL p_strcoll)(const char* str1, const char* str2);
int (* CDECL p__stricoll_l)(const char* str1, const char* str2, MSVCRT__locale_t locale);
int (* CDECL p__stricoll)(const char* str1, const char* str2);
int (* CDECL p__strncoll_l)(const char* str1, const char* str2, size_t count, MSVCRT__locale_t locale);
int (* CDECL p__strncoll)(const char* str1, const char* str2, size_t count);
int (* CDECL p__strnicoll_l)(const char* str1, const char* str2, size_t count, MSVCRT__locale_t locale);
int (* CDECL p__strnicoll)(const char* str1, const char* str2, size_t count);
char* (* CDECL p_strcpy)(char *dst, const char *src);
char * (* CDECL p_strncat)(char *dst, const char *src, size_t len);
int (* CDECL p_strncat_s)(char* dst, size_t elem, const char* src, size_t count);
size_t (* CDECL p__strxfrm_l)(char *dest, const char *src, size_t len, MSVCRT__locale_t locale);
size_t (* CDECL p_strxfrm)(char *dest, const char *src, size_t len);
int (* CDECL p__atoldbl)(long double *value, const char *str);
int CDECL (* CDECL p___STRINGTOLD)(long double *value, char **endptr, const char *str, int flags);
size_t (* CDECL p_strnlen)(const char *s, size_t maxlen);
__int64 (* CDECL p__strtoi64_l)(const char *nptr, char **endptr, int base, MSVCRT__locale_t locale);
__int64 (* CDECL p__strtoi64)(const char *nptr, char **endptr, int base);
int (* CDECL p_atoi)(const char *str);
LONGLONG (* CDECL p__atoll_l)(const char* str, MSVCRT__locale_t locale);
LONGLONG (* CDECL p_atoll)(const char* str);
LONG (* CDECL p__strtol_l)(const char* nptr, char** end, int base, MSVCRT__locale_t locale);
LONG (* CDECL p_strtol)(const char* nptr, char** end, int base);
ULONG (* CDECL p_strtoul_l)(const char* nptr, char** end, int base, MSVCRT__locale_t locale);
ULONG (* CDECL p_strtoul)(const char* nptr, char** end, int base);
int (* CDECL p__ltoa_s)(LONG value, char *str, size_t size, int radix);
int (* CDECL p__ltow_s)(LONG value, WCHAR *str, size_t size, int radix);
int (* CDECL p__itoa_s)(int value, char *str, size_t size, int radix);
char* (* CDECL p__itoa)(int value, char *str, int radix);
int (* CDECL p__itow_s)(int value, WCHAR *str, size_t size, int radix);
int (* CDECL p__ui64toa_s)(unsigned __int64 value, char *str, size_t size, int radix);
int (* CDECL p__ui64tow_s)(unsigned __int64 value, WCHAR *str, size_t size, int radix);
int (* CDECL p__ultoa_s)(ULONG value, char *str, size_t size, int radix);
int (* CDECL p__ultow_s)(ULONG value, WCHAR *str, size_t size, int radix);
int (* CDECL p__i64toa_s)(__int64 value, char *str, size_t size, int radix);
int (* CDECL p__i64tow_s)(__int64 value, WCHAR *str, size_t size, int radix);
int (* CDECL p_I10_OUTPUT)(long double ld80, int prec, int flag, struct _I10_OUTPUT_DATA *data);

int (* CDECL p__get_pgmptr)(char** p);
int (* CDECL p__get_wpgmptr)(WCHAR** p);
int (* CDECL p__set_fmode)(int mode);
int (* CDECL p__get_fmode)(int *mode);
char*** (* CDECL p___p__environ)(void);
char ***p__environ;
WCHAR*** (* CDECL p___p__wenviron)(void);
int (* CDECL p__get_osplatform)(int *pValue);
unsigned int * (* CDECL p____unguarded_readlc_active_add_func)(void);
unsigned int (* CDECL p____setlc_active_func)(void);
char** (* CDECL p__get_initial_narrow_environment)(void);
int (* CDECL p__configure_narrow_argv)(int mode);
int (* CDECL p__initialize_narrow_environment)(void);
WCHAR** (* CDECL p__get_initial_wide_environment)(void);
int (* CDECL p__configure_wide_argv)(int mode);
int (* CDECL p__initialize_wide_environment)(void);
char* (* CDECL p__get_narrow_winmain_command_line)(void);
WCHAR* (* CDECL p__get_wide_winmain_command_line)(void);

char* (* CDECL p__Getdays)(void);
wchar_t* (* CDECL p__W_Getdays)(void);
char* (* CDECL p__Getmonths)(void);
wchar_t* (* CDECL p__W_Getmonths)(void);
void* (* CDECL p__Gettnames)(void);
void* (* CDECL p__W_Gettnames)(void);
int (* CDECL p___crtLCMapStringA)(LCID lcid, DWORD mapflags, const char* src, int srclen, char* dst, int dstlen, unsigned int codepage, int xflag);
int (* CDECL p___crtLCMapStringW)(LCID lcid, DWORD mapflags, const wchar_t *src, int srclen, wchar_t *dst, int dstlen, unsigned int codepage, int xflag);
int (* CDECL p___crtCompareStringA)(LCID lcid, DWORD flags, const char *src1, int len1, const char *src2, int len2);
int (* CDECL p___crtCompareStringW)(LCID lcid, DWORD flags, const wchar_t *src1, int len1, const wchar_t *src2, int len2);
int (* CDECL p___crtGetLocaleInfoW)(LCID lcid, LCTYPE type, wchar_t *buffer, int len);
int (* CDECL p___crtGetLocaleInfoEx)(const WCHAR *locale, LCTYPE type, wchar_t *buffer, int len);
MSVCRT_wint_t (* CDECL p_btowc)(int c);
BOOL (* CDECL p___crtGetStringTypeW)(DWORD unk, DWORD type, wchar_t *buffer, int len, WORD *out);
struct MSVCRT_lconv * (* CDECL p_localeconv)(void);
LCID* (* CDECL p____lc_handle_func)(void);
wchar_t** (* CDECL p____lc_locale_name_func)(void);
unsigned int (* CDECL p____lc_codepage_func)(void);
int (* CDECL p____lc_collate_cp_func)(void);
MSVCRT__locale_t (* CDECL p__get_current_locale)(void);
void (* CDECL p__free_locale)(MSVCRT__locale_t locale);
void (* CDECL p__lock_locales)(void);
void (* CDECL p__unlock_locales)(void);
MSVCRT__locale_t (* CDECL p__create_locale)(int category, const char *locale);
MSVCRT__locale_t (* CDECL p__wcreate_locale)(int category, const wchar_t *locale);
wchar_t* (* CDECL p__wsetlocale)(int category, const wchar_t* wlocale);
void * (* CDECL p_decode_pointer)(void * ptr);
void * (* CDECL p_encode_pointer)(void * ptr);
void * (* CDECL p__encoded_null)(void);
BOOL (* CDECL p___uncaught_exception)(void);
double *p__HUGE;
int *p___argc;
char ***p___argv;
wchar_t ***p___wargv;
int (* CDECL p___stdio_common_vsprintf)( unsigned __int64 options, char *str, size_t len, const char *format,
    MSVCRT__locale_t locale, __ms_va_list valist);
int (* CDECL p___stdio_common_vswprintf)( unsigned __int64 options, wchar_t *str, size_t len, const wchar_t *format,
    MSVCRT__locale_t locale, __ms_va_list valist);
int *p___mb_cur_max;
int (* CDECL p___stdio_common_vfprintf)(unsigned __int64 options, MSVCRT_FILE *file, const char *format,
    MSVCRT__locale_t locale, __ms_va_list valist);
int (* CDECL p___stdio_common_vsscanf)(unsigned __int64 options,
        const char *input, size_t length, const char *format,
        MSVCRT__locale_t locale, __ms_va_list valist);


DWORD msvcrt_tls;
size_t guest_FILE_size;
uint64_t guest_iob;
unsigned int guest_iob_size;

static inline MSVCRT_FILE *FILE_g2h(uint64_t guest)
{
#if GUEST_BIT == HOST_BIT
    return QEMU_G2H(guest);
#else
    if (guest >= guest_iob)
    {
        size_t offset;
        offset = (guest - guest_iob) / guest_FILE_size;
        if (offset <= guest_iob_size)
            return p___iob_func() + offset;
    }
    return QEMU_G2H(guest);
#endif
}

static inline uint64_t FILE_h2g(MSVCRT_FILE *host)
{
#if GUEST_BIT == HOST_BIT
    return QEMU_H2G(host);
#else
    MSVCRT_FILE *host_iob = p___iob_func();
    if ((ULONG_PTR)host >= (ULONG_PTR)host_iob)
    {
        size_t offset;
        offset = (host - host_iob);
        if (offset <= guest_iob_size)
            return QEMU_H2G(guest_iob + offset * guest_FILE_size);
    }
    return QEMU_H2G(host);
#endif
}
#endif

#endif
