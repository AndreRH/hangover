#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>

enum msvcrt_calls
{
    CALL____MB_CUR_MAX_FUNC = 0,
    CALL____MB_CUR_MAX_L_FUNC,
    CALL___CONTROL87_2,
    CALL___CRT_DEBUGGER_HOOK,
    CALL___CXXFRAMEHANDLER,
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
    CALL___P__MBCTYPE,
    CALL___P__PCTYPE,
    CALL___PCTYPE_FUNC,
    CALL___SET_APP_TYPE,
    CALL___SETUSERMATHERR,
    CALL___TOASCII,
    CALL___WGETMAINARGS,
    CALL__ABS64,
    CALL__AMSG_EXIT,
    CALL__CABS,
    CALL__CEXIT,
    CALL__CHGSIGN,
    CALL__CHGSIGNF,
    CALL__CIACOS,
    CALL__CIASIN,
    CALL__CIATAN,
    CALL__CIATAN2,
    CALL__CICOS,
    CALL__CICOSH,
    CALL__CIEXP,
    CALL__CIFMOD,
    CALL__CILOG,
    CALL__CILOG10,
    CALL__CIPOW,
    CALL__CISIN,
    CALL__CISINH,
    CALL__CISQRT,
    CALL__CITAN,
    CALL__CITANH,
    CALL__CLEARFP,
    CALL__CONFIGTHREADLOCALE,
    CALL__CONTROL87,
    CALL__CONTROLFP,
    CALL__CONTROLFP_S,
    CALL__COPYSIGN,
    CALL__COPYSIGNF,
    CALL__CXXTHROWEXCEPTION,
    CALL__DCLASS,
    CALL__DPCOMP,
    CALL__DSIGN,
    CALL__DTEST,
    CALL__DUPENV_S,
    CALL__ECVT,
    CALL__ECVT_S,
    CALL__ERRNO,
    CALL__EXIT,
    CALL__FCVT,
    CALL__FCVT_S,
    CALL__FDCLASS,
    CALL__FDPCOMP,
    CALL__FDSIGN,
    CALL__FDTEST,
    CALL__FILENO,
    CALL__FINITE,
    CALL__FINITEF,
    CALL__FPCLASS,
    CALL__FPRESET,
    CALL__FTOL,
    CALL__GCVT,
    CALL__GCVT_S,
    CALL__GETMBCP,
    CALL__HYPOT,
    CALL__HYPOTF,
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
    CALL__ISXDIGIT_L,
    CALL__J0,
    CALL__J1,
    CALL__JN,
    CALL__LDCLASS,
    CALL__LDTEST,
    CALL__LOCK,
    CALL__LOGB,
    CALL__LOGBF,
    CALL__LROTL,
    CALL__LROTR,
    CALL__LSEEK,
    CALL__LSEEKI64,
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
    CALL__MBSTOWCS_S,
    CALL__MBSTOWCS_S_L,
    CALL__MBSTRLEN,
    CALL__MBSTRLEN_L,
    CALL__MBSUPR,
    CALL__MBSUPR_S,
    CALL__NEXTAFTER,
    CALL__NEXTAFTERF,
    CALL__ONEXIT,
    CALL__PURECALL,
    CALL__PUTENV,
    CALL__PUTENV_S,
    CALL__ROTL,
    CALL__ROTL64,
    CALL__ROTR,
    CALL__ROTR64,
    CALL__SCALB,
    CALL__SCALBF,
    CALL__SET_CONTROLFP,
    CALL__SET_FMA3_ENABLE,
    CALL__SET_SSE2_ENABLE,
    CALL__SETJMP,
    CALL__SETMBCP,
    CALL__SNWPRINTF,
    CALL__STATUSFP,
    CALL__STATUSFP2,
    CALL__STRDATE,
    CALL__STRDUP,
    CALL__STRICMP,
    CALL__STRNICMP,
    CALL__STRTIME,
    CALL__STRTOUI64,
    CALL__TEMPNAM,
    CALL__TOLOWER,
    CALL__TOLOWER_L,
    CALL__TOUPPER,
    CALL__TOUPPER_L,
    CALL__UNLOCK,
    CALL__VSNPRINTF,
    CALL__VSNWPRINTF,
    CALL__WCSNICMP,
    CALL__WDUPENV_S,
    CALL__WGETENV,
    CALL__WGETENV_S,
    CALL__WPUTENV,
    CALL__WPUTENV_S,
    CALL__WRITE,
    CALL__WTOF,
    CALL__WTOI,
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
    CALL_CALLOC,
    CALL_CBRT,
    CALL_CBRTF,
    CALL_CBRTL,
    CALL_CEIL,
    CALL_CEILF,
    CALL_COS,
    CALL_COSF,
    CALL_COSH,
    CALL_COSHF,
    CALL_DIV,
    CALL_ERF,
    CALL_ERFC,
    CALL_ERFCF,
    CALL_ERFCL,
    CALL_ERFF,
    CALL_ERFL,
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
    CALL_FEGETENV,
    CALL_FEGETROUND,
    CALL_FESETENV,
    CALL_FESETROUND,
    CALL_FFLUSH,
    CALL_FLOOR,
    CALL_FLOORF,
    CALL_FMAX,
    CALL_FMAXF,
    CALL_FMIN,
    CALL_FMINF,
    CALL_FMOD,
    CALL_FMODF,
    CALL_FPRINTF,
    CALL_FREAD,
    CALL_FREE,
    CALL_FREXP,
    CALL_FREXPF,
    CALL_FWPRINTF,
    CALL_FWRITE,
    CALL_GETENV,
    CALL_GETENV_S,
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
    CALL_ISWALPHA,
    CALL_ISWASCII,
    CALL_ISWDIGIT,
    CALL_ISWPUNCT,
    CALL_ISWSPACE,
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
    CALL_MBTOWC,
    CALL_MBTOWC_L,
    CALL_MEMCMP,
    CALL_MEMCPY,
    CALL_MEMMOVE,
    CALL_MEMSET,
    CALL_MODF,
    CALL_MODFF,
    CALL_NAN,
    CALL_NANF,
    CALL_NEARBYINT,
    CALL_NEARBYINTF,
    CALL_OPERATOR_DELETE,
    CALL_OPERATOR_NEW,
    CALL_POW,
    CALL_POWF,
    CALL_PRINTF,
    CALL_PUTS,
    CALL_QSORT,
    CALL_RAISE,
    CALL_RAND,
    CALL_REALLOC,
    CALL_REMAINDER,
    CALL_REMAINDERF,
    CALL_REMAINDERL,
    CALL_RINT,
    CALL_RINTF,
    CALL_RINTL,
    CALL_ROUND,
    CALL_ROUNDF,
    CALL_ROUNDL,
    CALL_SCALBNL,
    CALL_SETLOCALE,
    CALL_SETVBUF,
    CALL_SIGNAL,
    CALL_SIN,
    CALL_SINF,
    CALL_SINH,
    CALL_SINHF,
    CALL_SPRINTF,
    CALL_SQRT,
    CALL_SQRTF,
    CALL_SRAND,
    CALL_STRCAT_S,
    CALL_STRCHR,
    CALL_STRCMP,
    CALL_STRCPY_S,
    CALL_STRLEN,
    CALL_STRNCMP,
    CALL_STRRCHR,
    CALL_STRSTR,
    CALL_STRTOD,
    CALL_SWPRINTF_S,
    CALL_TAN,
    CALL_TANF,
    CALL_TANH,
    CALL_TANHF,
    CALL_TERMINATE,
    CALL_TOLOWER,
    CALL_TOUPPER,
    CALL_TRUNC,
    CALL_TRUNCF,
    CALL_TRUNCL,
    CALL_TYPE_INFO_DTOR,
    CALL_VSSCANF,
    CALL_WCSCAT_S,
    CALL_WCSCPY,
    CALL_WCSCPY_S,
    CALL_WCSNCMP,
    CALL_WCSSTR,
    CALL_WCSTOD,
    CALL_WCSTOMBS,
    CALL_WCTOMB,
    CALL_WPRINTF,
};

typedef int (__cdecl *MSVCRT__onexit_t)(void);

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

typedef void *MSVCRT__locale_t;

#ifdef QEMU_DLL_GUEST

extern char *MSVCRT__acmdln;
extern WCHAR *MSVCRT__wcmdln;
char * CDECL MSVCRT__strdup(const char *str);
void * CDECL MSVCRT_calloc(size_t item_count,size_t size);
CDECL DECLSPEC_NORETURN void __MINGW_NOTHROW MSVCRT_exit(int code);
void CDECL MSVCRT_free(void *ptr);
void * CDECL MSVCRT_malloc(size_t size);
void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size);
void * CDECL MSVCRT_realloc(void *ptr, size_t size);
size_t CDECL MSVCRT_strlen(const char *str);

unsigned int count_printf_argsA(const char *format, char *fmts);

#else

extern const struct qemu_ops *qemu_ops;

void qemu____mb_cur_max_func(struct qemu_syscall *call);
void qemu____mb_cur_max_l_func(struct qemu_syscall *call);
void qemu___control87_2(struct qemu_syscall *call);
void qemu___crt_debugger_hook(struct qemu_syscall *call);
void qemu___cxxframehandler(struct qemu_syscall *call);
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
void qemu___p__mbctype(struct qemu_syscall *call);
void qemu___p__pctype(struct qemu_syscall *call);
void qemu___pctype_func(struct qemu_syscall *call);
void qemu___set_app_type(struct qemu_syscall *call);
void qemu___setusermatherr(struct qemu_syscall *call);
void qemu___toascii(struct qemu_syscall *call);
void qemu___wgetmainargs(struct qemu_syscall *call);
void qemu__abs64(struct qemu_syscall *call);
void qemu__amsg_exit(struct qemu_syscall *call);
void qemu__cabs(struct qemu_syscall *call);
void qemu__cexit(struct qemu_syscall *call);
void qemu__chgsign(struct qemu_syscall *call);
void qemu__chgsignf(struct qemu_syscall *call);
void qemu__CIacos(struct qemu_syscall *call);
void qemu__CIasin(struct qemu_syscall *call);
void qemu__CIatan(struct qemu_syscall *call);
void qemu__CIatan2(struct qemu_syscall *call);
void qemu__CIcos(struct qemu_syscall *call);
void qemu__CIcosh(struct qemu_syscall *call);
void qemu__CIexp(struct qemu_syscall *call);
void qemu__CIfmod(struct qemu_syscall *call);
void qemu__CIlog(struct qemu_syscall *call);
void qemu__CIlog10(struct qemu_syscall *call);
void qemu__CIpow(struct qemu_syscall *call);
void qemu__CIsin(struct qemu_syscall *call);
void qemu__CIsinh(struct qemu_syscall *call);
void qemu__CIsqrt(struct qemu_syscall *call);
void qemu__CItan(struct qemu_syscall *call);
void qemu__CItanh(struct qemu_syscall *call);
void qemu__clearfp(struct qemu_syscall *call);
void qemu__configthreadlocale(struct qemu_syscall *call);
void qemu__control87(struct qemu_syscall *call);
void qemu__controlfp(struct qemu_syscall *call);
void qemu__controlfp_s(struct qemu_syscall *call);
void qemu__copysign(struct qemu_syscall *call);
void qemu__copysignf(struct qemu_syscall *call);
void qemu__CxxThrowException(struct qemu_syscall *c);
void qemu__dclass(struct qemu_syscall *call);
void qemu__dpcomp(struct qemu_syscall *call);
void qemu__dsign(struct qemu_syscall *call);
void qemu__dtest(struct qemu_syscall *call);
void qemu__dupenv_s(struct qemu_syscall *call);
void qemu__ecvt(struct qemu_syscall *call);
void qemu__ecvt_s(struct qemu_syscall *call);
void qemu__errno(struct qemu_syscall *call);
void qemu__exit(struct qemu_syscall *call);
void qemu__fcvt(struct qemu_syscall *call);
void qemu__fcvt_s(struct qemu_syscall *call);
void qemu__fdclass(struct qemu_syscall *call);
void qemu__fdpcomp(struct qemu_syscall *call);
void qemu__fdsign(struct qemu_syscall *call);
void qemu__fdtest(struct qemu_syscall *call);
void qemu__fileno(struct qemu_syscall *call);
void qemu__finite(struct qemu_syscall *call);
void qemu__finitef(struct qemu_syscall *call);
void qemu__fpclass(struct qemu_syscall *call);
void qemu__fpreset(struct qemu_syscall *call);
void qemu__ftol(struct qemu_syscall *call);
void qemu__gcvt(struct qemu_syscall *call);
void qemu__gcvt_s(struct qemu_syscall *call);
void qemu__getmbcp(struct qemu_syscall *call);
void qemu__hypot(struct qemu_syscall *call);
void qemu__hypotf(struct qemu_syscall *call);
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
void qemu__isxdigit_l(struct qemu_syscall *call);
void qemu__j0(struct qemu_syscall *call);
void qemu__j1(struct qemu_syscall *call);
void qemu__jn(struct qemu_syscall *call);
void qemu__ldclass(struct qemu_syscall *call);
void qemu__ldtest(struct qemu_syscall *call);
void qemu__lock(struct qemu_syscall *call);
void qemu__logb(struct qemu_syscall *call);
void qemu__logbf(struct qemu_syscall *call);
void qemu__lrotl(struct qemu_syscall *call);
void qemu__lrotr(struct qemu_syscall *call);
void qemu__lseek(struct qemu_syscall *call);
void qemu__lseeki64(struct qemu_syscall *call);
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
void qemu__mbstowcs_s(struct qemu_syscall *call);
void qemu__mbstowcs_s_l(struct qemu_syscall *call);
void qemu__mbstrlen(struct qemu_syscall *call);
void qemu__mbstrlen_l(struct qemu_syscall *call);
void qemu__mbsupr(struct qemu_syscall *call);
void qemu__mbsupr_s(struct qemu_syscall *call);
void qemu__nextafter(struct qemu_syscall *call);
void qemu__nextafterf(struct qemu_syscall *call);
void qemu__onexit(struct qemu_syscall *call);
void qemu__purecall(struct qemu_syscall *call);
void qemu__putenv(struct qemu_syscall *call);
void qemu__putenv_s(struct qemu_syscall *call);
void qemu__rotl(struct qemu_syscall *call);
void qemu__rotl64(struct qemu_syscall *call);
void qemu__rotr(struct qemu_syscall *call);
void qemu__rotr64(struct qemu_syscall *call);
void qemu__scalb(struct qemu_syscall *call);
void qemu__scalbf(struct qemu_syscall *call);
void qemu__set_controlfp(struct qemu_syscall *call);
void qemu__set_FMA3_enable(struct qemu_syscall *call);
void qemu__set_SSE2_enable(struct qemu_syscall *call);
void qemu__setjmp(struct qemu_syscall *call);
void qemu__setmbcp(struct qemu_syscall *call);
void qemu__snwprintf(struct qemu_syscall *call);
void qemu__statusfp(struct qemu_syscall *call);
void qemu__statusfp2(struct qemu_syscall *call);
void qemu__strdate(struct qemu_syscall *call);
void qemu__strdup(struct qemu_syscall *call);
void qemu__stricmp(struct qemu_syscall *call);
void qemu__strnicmp(struct qemu_syscall *call);
void qemu__strtime(struct qemu_syscall *call);
void qemu__strtoui64(struct qemu_syscall *call);
void qemu__tempnam(struct qemu_syscall *call);
void qemu__tolower(struct qemu_syscall *call);
void qemu__tolower_l(struct qemu_syscall *call);
void qemu__toupper(struct qemu_syscall *call);
void qemu__toupper_l(struct qemu_syscall *call);
void qemu__unlock(struct qemu_syscall *call);
void qemu__wcsnicmp(struct qemu_syscall *call);
void qemu__wdupenv_s(struct qemu_syscall *call);
void qemu__wgetenv(struct qemu_syscall *call);
void qemu__wgetenv_s(struct qemu_syscall *call);
void qemu__wputenv(struct qemu_syscall *call);
void qemu__wputenv_s(struct qemu_syscall *call);
void qemu__write(struct qemu_syscall *call);
void qemu__wtof(struct qemu_syscall *call);
void qemu__wtoi(struct qemu_syscall *call);
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
void qemu_asin(struct qemu_syscall *call);
void qemu_asinf(struct qemu_syscall *call);
void qemu_asinh(struct qemu_syscall *call);
void qemu_asinhf(struct qemu_syscall *call);
void qemu_asinhl(struct qemu_syscall *call);
void qemu_atan(struct qemu_syscall *call);
void qemu_atan2(struct qemu_syscall *call);
void qemu_atan2f(struct qemu_syscall *call);
void qemu_atan2f(struct qemu_syscall *call);
void qemu_atanf(struct qemu_syscall *call);
void qemu_atanh(struct qemu_syscall *call);
void qemu_atanhf(struct qemu_syscall *call);
void qemu_atanhl(struct qemu_syscall *call);
void qemu_atof(struct qemu_syscall *call);
void qemu_calloc(struct qemu_syscall *call);
void qemu_cbrt(struct qemu_syscall *call);
void qemu_cbrtf(struct qemu_syscall *call);
void qemu_cbrtl(struct qemu_syscall *call);
void qemu_ceil(struct qemu_syscall *call);
void qemu_ceilf(struct qemu_syscall *call);
void qemu_cos(struct qemu_syscall *call);
void qemu_cosf(struct qemu_syscall *call);
void qemu_cosf(struct qemu_syscall *call);
void qemu_cosh(struct qemu_syscall *call);
void qemu_coshf(struct qemu_syscall *call);
void qemu_div(struct qemu_syscall *call);
void qemu_erf(struct qemu_syscall *call);
void qemu_erfc(struct qemu_syscall *call);
void qemu_erfcf(struct qemu_syscall *call);
void qemu_erfcl(struct qemu_syscall *call);
void qemu_erff(struct qemu_syscall *call);
void qemu_erfl(struct qemu_syscall *call);
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
void qemu_fegetenv(struct qemu_syscall *call);
void qemu_fegetround(struct qemu_syscall *call);
void qemu_fesetenv(struct qemu_syscall *call);
void qemu_fesetround(struct qemu_syscall *call);
void qemu_fflush(struct qemu_syscall *call);
void qemu_floor(struct qemu_syscall *call);
void qemu_floorf(struct qemu_syscall *call);
void qemu_fmax(struct qemu_syscall *call);
void qemu_fmaxf(struct qemu_syscall *call);
void qemu_fmin(struct qemu_syscall *call);
void qemu_fminf(struct qemu_syscall *call);
void qemu_fmod(struct qemu_syscall *call);
void qemu_fmodf(struct qemu_syscall *call);
void qemu_fprintf(struct qemu_syscall *call);
void qemu_fread(struct qemu_syscall *call);
void qemu_free(struct qemu_syscall *call);
void qemu_frexp(struct qemu_syscall *call);
void qemu_frexpf(struct qemu_syscall *call);
void qemu_fwrite(struct qemu_syscall *call);
void qemu_getenv(struct qemu_syscall *call);
void qemu_getenv_s(struct qemu_syscall *call);
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
void qemu_iswalpha(struct qemu_syscall *call);
void qemu_iswascii(struct qemu_syscall *call);
void qemu_iswdigit(struct qemu_syscall *call);
void qemu_iswpunct(struct qemu_syscall *call);
void qemu_iswspace(struct qemu_syscall *call);
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
void qemu_mbtowc(struct qemu_syscall *call);
void qemu_mbtowc_l(struct qemu_syscall *call);
void qemu_memcmp(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memmove(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_modf(struct qemu_syscall *call);
void qemu_modff(struct qemu_syscall *call);
void qemu_nan(struct qemu_syscall *call);
void qemu_nanf(struct qemu_syscall *call);
void qemu_nearbyint(struct qemu_syscall *call);
void qemu_nearbyintf(struct qemu_syscall *call);
void qemu_operator_delete(struct qemu_syscall *call);
void qemu_operator_new(struct qemu_syscall *call);
void qemu_pow(struct qemu_syscall *call);
void qemu_powf(struct qemu_syscall *call);
void qemu_powf(struct qemu_syscall *call);
void qemu_puts(struct qemu_syscall *call);
void qemu_qsort(struct qemu_syscall *call);
void qemu_raise(struct qemu_syscall *call);
void qemu_rand(struct qemu_syscall *call);
void qemu_realloc(struct qemu_syscall *call);
void qemu_remainder(struct qemu_syscall *call);
void qemu_remainderf(struct qemu_syscall *call);
void qemu_remainderl(struct qemu_syscall *call);
void qemu_rint(struct qemu_syscall *call);
void qemu_rintf(struct qemu_syscall *call);
void qemu_rintl(struct qemu_syscall *call);
void qemu_round(struct qemu_syscall *call);
void qemu_roundf(struct qemu_syscall *call);
void qemu_roundl(struct qemu_syscall *call);
void qemu_scalbnl(struct qemu_syscall *call);
void qemu_scanf(struct qemu_syscall *call);
void qemu_setlocale(struct qemu_syscall *call);
void qemu_setvbuf(struct qemu_syscall *call);
void qemu_signal(struct qemu_syscall *call);
void qemu_sin(struct qemu_syscall *call);
void qemu_sinf(struct qemu_syscall *call);
void qemu_sinf(struct qemu_syscall *call);
void qemu_sinh(struct qemu_syscall *call);
void qemu_sinhf(struct qemu_syscall *call);
void qemu_sprintf(struct qemu_syscall *call);
void qemu_sqrt(struct qemu_syscall *call);
void qemu_sqrtf(struct qemu_syscall *call);
void qemu_srand(struct qemu_syscall *call);
void qemu_strcat_s(struct qemu_syscall *call);
void qemu_strchr(struct qemu_syscall *call);
void qemu_strcmp(struct qemu_syscall *call);
void qemu_strcpy_s(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);
void qemu_strncmp(struct qemu_syscall *call);
void qemu_strrchr(struct qemu_syscall *call);
void qemu_strstr(struct qemu_syscall *call);
void qemu_strtod(struct qemu_syscall *call);
void qemu_tan(struct qemu_syscall *call);
void qemu_tanf(struct qemu_syscall *call);
void qemu_tanh(struct qemu_syscall *call);
void qemu_tanhf(struct qemu_syscall *call);
void qemu_terminate(struct qemu_syscall *c);
void qemu_tolower(struct qemu_syscall *call);
void qemu_toupper(struct qemu_syscall *call);
void qemu_trunc(struct qemu_syscall *call);
void qemu_truncf(struct qemu_syscall *call);
void qemu_truncl(struct qemu_syscall *call);
void qemu_type_info_dtor(struct qemu_syscall *call);
void qemu_wcscat_s(struct qemu_syscall *call);
void qemu_wcscpy(struct qemu_syscall *call);
void qemu_wcscpy_s(struct qemu_syscall *call);
void qemu_wcsncmp(struct qemu_syscall *call);
void qemu_wcsstr(struct qemu_syscall *call);
void qemu_wcstod(struct qemu_syscall *call);
void qemu_wcstombs(struct qemu_syscall *call);
void qemu_wctomb(struct qemu_syscall *call);

/* Be careful not to call the Linux libc! */
void (* CDECL p___crt_debugger_hook)(int reserved);
void (* CDECL p___getmainargs)(int *argc, char** *argv, char** *envp,
        int expand_wildcards, int *new_mode);
FILE *(* CDECL p___iob_func)();
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
size_t (* CDECL p_fwrite)(const void *str, size_t size, size_t count, FILE *file);
void *(* CDECL p_malloc)(size_t size);
void *(* CDECL p_memset)(void *dst, int c, size_t n);
void (* CDECL p_operator_delete)(void *mem);
void *(* CDECL p_operator_new)(size_t size);
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
int (* CDECL p_strrchr)(const char *str, int c);
void (* CDECL p_terminate)(void);
int (* CDECL p_vfprintf)(FILE *file,const char *format, va_list args);
int (* CDECL p_vfwprintf)(FILE *file, const WCHAR *format, va_list args);
int (* CDECL p_vsprintf)(char *str, const char *format, va_list args);
int (* CDECL p_vswprintf_s)(WCHAR *dst, size_t charcount,
        const WCHAR *fmt, va_list args);
int (* CDECL p_wcscat_s)(WCHAR *dst, size_t count, const WCHAR *src);
WCHAR (* CDECL p_wcscpy)(WCHAR *dst, const WCHAR *src);
int (* CDECL p_wcscpy_s)(WCHAR *dst, size_t size, const WCHAR *src);
int (* CDECL p_wcsncmp)(const WCHAR *str1, const WCHAR *str2, size_t count);
const WCHAR (* CDECL p_wcsstr)(const WCHAR *str, const WCHAR *sub);
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
double (* CDECL p__CIacos)(void);
double (* CDECL p__CIasin)(void);
double (* CDECL p__CIatan)(void);
double (* CDECL p__CIatan2)(void);
double (* CDECL p__CIcos)(void);
double (* CDECL p__CIcosh)(void);
double (* CDECL p__CIexp)(void);
double (* CDECL p__CIfmod)(void);
double (* CDECL p__CIlog)(void);
double (* CDECL p__CIlog10)(void);
double (* CDECL p__CIpow)(void);
double (* CDECL p__CIsin)(void);
double (* CDECL p__CIsinh)(void);
double (* CDECL p__CIsqrt)(void);
double (* CDECL p__CItan)(void);
double (* CDECL p__CItanh)(void);
LONGLONG (* CDECL p__ftol)(void);
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
int (* CDECL p__vsnprintf)(char *str, size_t len, const char *format, va_list valist);
int (* CDECL p__vsnwprintf)(WCHAR *str, size_t len, const WCHAR *format, va_list valist);
int (* CDECL p__fileno)(FILE *f);
int (* CDECL p__write)(int fd, const void *buf, unsigned int count);
double (* CDECL p_atof)(const char *str);
size_t (* CDECL p_fread)(void *ptr, size_t size, size_t nmemb, FILE *file);
int (*CDECL p_rand)(void);
int (*CDECL p_srand)(int seed);
int (* CDECL p_fflush)(FILE *file);
LONG (* CDECL p__lseek)(int fd, LONG offset, int whence);
__int64 (* CDECL p__lseeki64)(int fd, __int64 offset, int whence);
char * (* CDECL p__tempnam)(const char *dir, const char *prefix);
int (* CDECL p_strstr)(const char *haystack, char *needle);
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
int (* CDECL p__mbstowcs_s)(size_t *ret, WCHAR *wcstr, size_t size, const char *mbstr, size_t count);
size_t (* CDECL p_mbsrtowcs)(WCHAR *wcstr, const char **pmbstr, size_t count, void *state);
int (* CDECL p_mbsrtowcs_s)(size_t *ret, WCHAR *wcstr, size_t len, const char **mbstr, size_t count, void *state);
unsigned int (* CDECL p__mbctohira)(unsigned int c);
unsigned int (* CDECL p__mbctokata)(unsigned int c);
void (* CDECL p_type_info_dtor)(void *_this); /* __thiscall */
int (* CDECL p__strtoui64)(const char *nptr, char **endptr, int base);

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
int (* CDECL p_setvbuf)(FILE *file, char *buf, int mode, size_t size);

DWORD msvcrt_tls;

#endif

#endif
