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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers.
 *
 * Wrapping msvcrt like this is not my first choice. In theory it only calls Windows
 * API functions and has a lot of small functions, so running it as a Win32/64 DLL
 * would save a lot of work and would most likely be faster and more compatible. Keep
 * in mind that CRT code is embedded into every crt-linked binary. Things will go
 * wrong if the host-side msvcrt.dll tries to access the module image - and it seems
 * the code in dlls/msvcrt/cpp.c is doing just that.
 *
 * Unfortunately Wine's msvcrt is not stand-alone and imports symbols from Linux/OSX
 * libc. So it is disabled in a mingw cross compile build, and if it is forced on it
 * will link against itself...
 */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifdef QEMU_DLL_GUEST

/* INTERNAL: Create a wide string from an ascii string */
static WCHAR *msvcrt_wstrdupa(const char *str)
{
    const unsigned int len = MSVCRT_strlen(str) + 1 ;
    WCHAR *wstr = MSVCRT_malloc(len * sizeof(*wstr));
    if (!wstr)
        return NULL;
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, len, wstr, len);
    return wstr;
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            MSVCRT__acmdln = MSVCRT__strdup(GetCommandLineA());
            MSVCRT__wcmdln = msvcrt_wstrdupa(MSVCRT__acmdln);
            return TRUE;

        default:
            return TRUE;
    }
}

#else

#include "va_helper_impl.h"
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu____mb_cur_max_func,
    qemu____mb_cur_max_l_func,
    qemu___acrt_iob_func,
    qemu___control87_2,
    qemu___crt_debugger_hook,
    qemu___cxxframehandler,
    qemu___doserrno,
    qemu___fpe_flt_rounds,
    qemu___fpecode,
    qemu___getmainargs,
    qemu___iob_func,
    qemu___isascii,
    qemu___iscsym,
    qemu___iscsymf,
    qemu___lconv_init,
    qemu___libm_sse2_acos,
    qemu___libm_sse2_acosf,
    qemu___libm_sse2_asin,
    qemu___libm_sse2_asinf,
    qemu___libm_sse2_atan,
    qemu___libm_sse2_atan2,
    qemu___libm_sse2_atanf,
    qemu___libm_sse2_cos,
    qemu___libm_sse2_cosf,
    qemu___libm_sse2_exp,
    qemu___libm_sse2_expf,
    qemu___libm_sse2_log,
    qemu___libm_sse2_log10,
    qemu___libm_sse2_log10f,
    qemu___libm_sse2_logf,
    qemu___libm_sse2_pow,
    qemu___libm_sse2_powf,
    qemu___libm_sse2_sin,
    qemu___libm_sse2_sinf,
    qemu___libm_sse2_sqrt_precise,
    qemu___libm_sse2_tan,
    qemu___libm_sse2_tanf,
    qemu___p___mb_cur_max,
    qemu___p__mbctype,
    qemu___p__pctype,
    qemu___pctype_func,
    qemu___set_app_type,
    qemu___setusermatherr,
    qemu___sys_errlist,
    qemu___sys_nerr,
    qemu___toascii,
    qemu___wcserror,
    qemu___wcserror_s,
    qemu___wgetmainargs,
    qemu__abs64,
    qemu__access,
    qemu__access_s,
    qemu__amsg_exit,
    qemu__cabs,
    qemu__cexit,
    qemu__chgsign,
    qemu__chgsignf,
    qemu__chmod,
    qemu__chsize,
    qemu__chsize_s,
    qemu__CIacos,
    qemu__CIasin,
    qemu__CIatan,
    qemu__CIatan2,
    qemu__CIcos,
    qemu__CIcosh,
    qemu__CIexp,
    qemu__CIfmod,
    qemu__CIlog,
    qemu__CIlog10,
    qemu__CIpow,
    qemu__CIsin,
    qemu__CIsinh,
    qemu__CIsqrt,
    qemu__CItan,
    qemu__CItanh,
    qemu__clearfp,
    qemu__close,
    qemu__commit,
    qemu__configthreadlocale,
    qemu__control87,
    qemu__controlfp,
    qemu__controlfp_s,
    qemu__copysign,
    qemu__copysignf,
    qemu__creat,
    qemu__CxxThrowException,
    qemu__dclass,
    qemu__dpcomp,
    qemu__dsign,
    qemu__dtest,
    qemu__dup,
    qemu__dup2,
    qemu__dupenv_s,
    qemu__ecvt,
    qemu__ecvt_s,
    qemu__eof,
    qemu__errno,
    qemu__exit,
    qemu__fclose_nolock,
    qemu__fcloseall,
    qemu__fcvt,
    qemu__fcvt_s,
    qemu__fdclass,
    qemu__fdopen,
    qemu__fdpcomp,
    qemu__fdsign,
    qemu__fdtest,
    qemu__fflush_nolock,
    qemu__fgetc_nolock,
    qemu__fgetchar,
    qemu__fgetwc_nolock,
    qemu__fgetwchar,
    qemu__filbuf,
    qemu__filelength,
    qemu__filelengthi64,
    qemu__fileno,
    qemu__finite,
    qemu__finitef,
    qemu__flsbuf,
    qemu__flushall,
    qemu__fpclass,
    qemu__fpreset,
    qemu__fputc_nolock,
    qemu__fputchar,
    qemu__fputwc_nolock,
    qemu__fputwchar,
    qemu__fread_nolock,
    qemu__fread_nolock_s,
    qemu__fseek_nolock,
    qemu__fseeki64,
    qemu__fseeki64_nolock,
    qemu__fsopen,
    qemu__fstat,
    qemu__fstat32,
    qemu__fstat32i64,
    qemu__fstat64,
    qemu__fstat64i32,
    qemu__fstati64,
    qemu__ftell_nolock,
    qemu__ftelli64,
    qemu__ftelli64_nolock,
    qemu__ftol,
    qemu__futime,
    qemu__futime32,
    qemu__futime64,
    qemu__fwrite_nolock,
    qemu__gcvt,
    qemu__gcvt_s,
    qemu__get_doserrno,
    qemu__get_errno,
    qemu__get_invalid_parameter_handler,
    qemu__get_osfhandle,
    qemu__get_stream_buffer_pointers,
    qemu__get_thread_local_invalid_parameter_handler,
    qemu__getmaxstdio,
    qemu__getmbcp,
    qemu__getw,
    qemu__getws,
    qemu__hypot,
    qemu__hypotf,
    qemu__invalid_parameter_noinfo,
    qemu__invalid_parameter_noinfo_noreturn,
    qemu__isalnum_l,
    qemu__isalpha_l,
    qemu__isatty,
    qemu__isblank_l,
    qemu__iscntrl_l,
    qemu__isctype,
    qemu__isctype_l,
    qemu__isdigit_l,
    qemu__isgraph_l,
    qemu__isleadbyte_l,
    qemu__islower_l,
    qemu__ismbbkana,
    qemu__ismbblead,
    qemu__ismbblead_l,
    qemu__ismbbtrail,
    qemu__ismbcalnum,
    qemu__ismbcalpha,
    qemu__ismbcdigit,
    qemu__ismbcgraph,
    qemu__ismbchira,
    qemu__ismbckata,
    qemu__ismbclegal,
    qemu__ismbclower,
    qemu__ismbcprint,
    qemu__ismbcpunct,
    qemu__ismbcspace,
    qemu__ismbcsymbol,
    qemu__ismbcupper,
    qemu__ismbslead,
    qemu__ismbstrail,
    qemu__isnan,
    qemu__isnanf,
    qemu__isprint_l,
    qemu__isspace_l,
    qemu__isupper_l,
    qemu__isxdigit_l,
    qemu__j0,
    qemu__j1,
    qemu__jn,
    qemu__ldclass,
    qemu__ldtest,
    qemu__lock,
    qemu__lock_file,
    qemu__locking,
    qemu__logb,
    qemu__logbf,
    qemu__lrotl,
    qemu__lrotr,
    qemu__lseek,
    qemu__lseeki64,
    qemu__matherr,
    qemu__mbbtombc,
    qemu__mbbtype,
    qemu__mbccpy,
    qemu__mbcjistojms,
    qemu__mbcjmstojis,
    qemu__mbclen,
    qemu__mbctohira,
    qemu__mbctokata,
    qemu__mbctolower,
    qemu__mbctombb,
    qemu__mbctoupper,
    qemu__mbsbtype,
    qemu__mbscat,
    qemu__mbscat_s,
    qemu__mbscat_s_l,
    qemu__mbschr,
    qemu__mbscmp,
    qemu__mbscoll,
    qemu__mbscoll_l,
    qemu__mbscpy,
    qemu__mbscpy_s,
    qemu__mbscpy_s_l,
    qemu__mbscspn,
    qemu__mbsdec,
    qemu__mbsicmp,
    qemu__mbsicoll,
    qemu__mbsicoll_l,
    qemu__mbsinc,
    qemu__mbslen,
    qemu__mbslwr,
    qemu__mbslwr_s,
    qemu__mbsnbcat,
    qemu__mbsnbcat_s,
    qemu__mbsnbcmp,
    qemu__mbsnbcnt,
    qemu__mbsnbcoll,
    qemu__mbsnbcoll_l,
    qemu__mbsnbcpy,
    qemu__mbsnbcpy_s,
    qemu__mbsnbcpy_s_l,
    qemu__mbsnbicmp,
    qemu__mbsnbicoll,
    qemu__mbsnbicoll_l,
    qemu__mbsnbset,
    qemu__mbsncat,
    qemu__mbsnccnt,
    qemu__mbsncmp,
    qemu__mbsncpy,
    qemu__mbsnextc,
    qemu__mbsnicmp,
    qemu__mbsninc,
    qemu__mbsnset,
    qemu__mbspbrk,
    qemu__mbsrchr,
    qemu__mbsrev,
    qemu__mbsset,
    qemu__mbsspn,
    qemu__mbsspnp,
    qemu__mbsstr,
    qemu__mbstok,
    qemu__mbstok_l,
    qemu__mbstok_s,
    qemu__mbstok_s_l,
    qemu__mbstowcs_l,
    qemu__mbstowcs_s,
    qemu__mbstowcs_s_l,
    qemu__mbstrlen,
    qemu__mbstrlen_l,
    qemu__mbsupr,
    qemu__mbsupr_s,
    qemu__mktemp,
    qemu__mktemp_s,
    qemu__nextafter,
    qemu__nextafterf,
    qemu__onexit,
    qemu__open_osfhandle,
    qemu__pipe,
    qemu__purecall,
    qemu__putenv,
    qemu__putenv_s,
    qemu__putw,
    qemu__putws,
    qemu__read,
    qemu__rmtmp,
    qemu__rotl,
    qemu__rotl64,
    qemu__rotr,
    qemu__rotr64,
    qemu__scalb,
    qemu__scalbf,
    qemu__set_controlfp,
    qemu__set_doserrno,
    qemu__set_errno,
    qemu__set_FMA3_enable,
    qemu__set_invalid_parameter_handler,
    qemu__set_SSE2_enable,
    qemu__set_thread_local_invalid_parameter_handler,
    qemu__seterrormode,
    qemu__setjmp,
    qemu__setmaxstdio,
    qemu__setmbcp,
    qemu__setmode,
    qemu__snwprintf,
    qemu__sopen_dispatch,
    qemu__sopen_s,
    qemu__stat32,
    qemu__stat32i64,
    qemu__stat64,
    qemu__stat64i32,
    qemu__statusfp,
    qemu__statusfp2,
    qemu__strdate,
    qemu__strdup,
    qemu__strerror,
    qemu__stricmp,
    qemu__strnicmp,
    qemu__strtime,
    qemu__strtoui64,
    qemu__tell,
    qemu__telli64,
    qemu__tempnam,
    qemu__time64,
    qemu__tolower,
    qemu__tolower_l,
    qemu__toupper,
    qemu__toupper_l,
    qemu__umask,
    qemu__ungetc_nolock,
    qemu__ungetwc_nolock,
    qemu__unlink,
    qemu__unlock,
    qemu__unlock_file,
    qemu__utime,
    qemu__utime32,
    qemu__utime64,
    qemu_sprintf,
    qemu_sprintf,
    qemu__waccess,
    qemu__waccess_s,
    qemu__wchmod,
    qemu__wcreat,
    qemu__wcserror,
    qemu__wcserror_s,
    qemu__wcsnicmp,
    qemu__wdupenv_s,
    qemu__wfdopen,
    qemu__wfopen,
    qemu__wfopen_s,
    qemu__wfreopen,
    qemu__wfreopen_s,
    qemu__wfsopen,
    qemu__wgetenv,
    qemu__wgetenv_s,
    qemu__wmktemp,
    qemu__wmktemp_s,
    qemu__wperror,
    qemu__wputenv,
    qemu__wputenv_s,
    qemu__wremove,
    qemu__wrename,
    qemu__write,
    qemu__wsopen_dispatch,
    qemu__wsopen_s,
    qemu__wstat,
    qemu__wstat32,
    qemu__wstat32i64,
    qemu__wstat64,
    qemu__wstat64i32,
    qemu__wstati64,
    qemu__wtempnam,
    qemu__wtmpnam,
    qemu__wtmpnam_s,
    qemu__wtof,
    qemu__wtoi,
    qemu__wunlink,
    qemu__wutime,
    qemu__wutime32,
    qemu__wutime64,
    qemu__xcptfilter,
    qemu__y0,
    qemu__y1,
    qemu__yn,
    qemu_abort,
    qemu_abs,
    qemu_acos,
    qemu_acosf,
    qemu_acosh,
    qemu_acoshf,
    qemu_acoshl,
    qemu_asin,
    qemu_asinf,
    qemu_asinh,
    qemu_asinhf,
    qemu_asinhl,
    qemu_atan,
    qemu_atan2,
    qemu_atan2f,
    qemu_atanf,
    qemu_atanh,
    qemu_atanhf,
    qemu_atanhl,
    qemu_atof,
    qemu_bsearch,
    qemu_calloc,
    qemu_cbrt,
    qemu_cbrtf,
    qemu_cbrtl,
    qemu_ceil,
    qemu_ceilf,
    qemu_clearerr,
    qemu_cos,
    qemu_cosf,
    qemu_cosh,
    qemu_coshf,
    qemu_div,
    qemu_erf,
    qemu_erfc,
    qemu_erfcf,
    qemu_erfcl,
    qemu_erff,
    qemu_erfl,
    qemu_exit,
    qemu_exp,
    qemu_exp2,
    qemu_exp2f,
    qemu_exp2l,
    qemu_expf,
    qemu_expm1,
    qemu_expm1f,
    qemu_expm1l,
    qemu_fabs,
    qemu_fabsf,
    qemu_fclose,
    qemu_fegetenv,
    qemu_fegetround,
    qemu_feof,
    qemu_ferror,
    qemu_fesetenv,
    qemu_fesetround,
    qemu_fflush,
    qemu_fgetc,
    qemu_fgetpos,
    qemu_fgets,
    qemu_fgetwc,
    qemu_fgetws,
    qemu_floor,
    qemu_floorf,
    qemu_fmax,
    qemu_fmaxf,
    qemu_fmin,
    qemu_fminf,
    qemu_fmod,
    qemu_fmodf,
    qemu_fopen,
    qemu_fopen_s,
    qemu_fprintf,
    qemu_fputc,
    qemu_fputs,
    qemu_fputwc,
    qemu_fputws,
    qemu_fread,
    qemu_fread_s,
    qemu_free,
    qemu_freopen,
    qemu_freopen_s,
    qemu_frexp,
    qemu_frexpf,
    qemu_fseek,
    qemu_fsetpos,
    qemu_ftell,
    qemu_fprintf,
    qemu_fwrite,
    qemu_getc,
    qemu_getchar,
    qemu_getenv,
    qemu_getenv_s,
    qemu_gets,
    qemu_getwc,
    qemu_getwchar,
    qemu_isalnum,
    qemu_isalpha,
    qemu_isblank,
    qemu_iscntrl,
    qemu_isdigit,
    qemu_isgraph,
    qemu_isleadbyte,
    qemu_islower,
    qemu_isprint,
    qemu_ispunct,
    qemu_isspace,
    qemu_isupper,
    qemu_iswalpha,
    qemu_iswascii,
    qemu_iswdigit,
    qemu_iswpunct,
    qemu_iswspace,
    qemu_isxdigit,
    qemu_labs,
    qemu_ldexp,
    qemu_ldiv,
    qemu_lgamma,
    qemu_lgammaf,
    qemu_lgammal,
    qemu_llabs,
    qemu_llrint,
    qemu_llrintf,
    qemu_llrintl,
    qemu_llround,
    qemu_llroundf,
    qemu_llroundl,
    qemu_log,
    qemu_log10,
    qemu_log10f,
    qemu_log1p,
    qemu_log1pf,
    qemu_log1pl,
    qemu_log2,
    qemu_log2f,
    qemu_log2l,
    qemu_logf,
    qemu_longjmp,
    qemu_lrint,
    qemu_lrintf,
    qemu_lrintl,
    qemu_lround,
    qemu_lroundf,
    qemu_lroundl,
    qemu_malloc,
    qemu_mblen,
    qemu_mbrlen,
    qemu_mbrtowc,
    qemu_mbsrtowcs,
    qemu_mbsrtowcs_s,
    qemu_mbstowcs,
    qemu_mbtowc,
    qemu_mbtowc_l,
    qemu_memcmp,
    qemu_memcpy,
    qemu_memmove,
    qemu_memset,
    qemu_modf,
    qemu_modff,
    qemu_nan,
    qemu_nanf,
    qemu_nearbyint,
    qemu_nearbyintf,
    qemu_operator_delete,
    qemu_operator_new,
    qemu_perror,
    qemu_pow,
    qemu_powf,
    qemu_fprintf,
    qemu_putc,
    qemu_putchar,
    qemu_puts,
    qemu_qsort,
    qemu_raise,
    qemu_rand,
    qemu_realloc,
    qemu_remainder,
    qemu_remainderf,
    qemu_remainderl,
    qemu_remove,
    qemu_rename,
    qemu_rewind,
    qemu_rint,
    qemu_rintf,
    qemu_rintl,
    qemu_round,
    qemu_roundf,
    qemu_roundl,
    qemu_scalbnl,
    qemu_setbuf,
    qemu_setlocale,
    qemu_setvbuf,
    qemu_signal,
    qemu_sin,
    qemu_sinf,
    qemu_sinh,
    qemu_sinhf,
    qemu_sprintf,
    qemu_sprintf,
    qemu_sqrt,
    qemu_sqrtf,
    qemu_srand,
    qemu_stat,
    qemu_stati64,
    qemu_strcat_s,
    qemu_strchr,
    qemu_strcmp,
    qemu_strcpy_s,
    qemu_strerror,
    qemu_strerror_s,
    qemu_strlen,
    qemu_strncmp,
    qemu_strrchr,
    qemu_strstr,
    qemu_strtod,
    qemu_sprintf,
    qemu_swscanf_s,
    qemu_tan,
    qemu_tanf,
    qemu_tanh,
    qemu_tanhf,
    qemu_terminate,
    qemu_tmpfile,
    qemu_tmpfile_s,
    qemu_tmpnam,
    qemu_tmpnam_s,
    qemu_tolower,
    qemu_toupper,
    qemu_trunc,
    qemu_truncf,
    qemu_truncl,
    qemu_type_info_dtor,
    qemu_ungetc,
    qemu_ungetwc,
    qemu_scanf,
    qemu_wcscat_s,
    qemu_wcscpy,
    qemu_wcscpy_s,
    qemu_wcsncmp,
    qemu_wcsstr,
    qemu_wcstod,
    qemu_wcstombs,
    qemu_wctomb,
    qemu_fprintf,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE msvcrt;
    const char *dll_name;
    WINE_TRACE("Loading host-side msvcrt wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    if (QEMU_CURRENT_DLL == DLL_MSVCR100)
        dll_name = "msvcr100.dll";
    else
        dll_name = "msvcrt.dll";

    msvcrt = LoadLibraryA(dll_name);
    if (!msvcrt)
        WINE_ERR("Cannot find %s.\n", dll_name);

    p____mb_cur_max_func = (void *)GetProcAddress(msvcrt, "___mb_cur_max_func");
    p____mb_cur_max_l_func = (void *)GetProcAddress(msvcrt, "___mb_cur_max_l_func");
    p___control87_2 = (void *)GetProcAddress(msvcrt, "__control87_2");
    p___crt_debugger_hook = (void *)GetProcAddress(msvcrt, "__crt_debugger_hook");
    p___doserrno = (void *)GetProcAddress(msvcrt, "__doserrno");
    p___fpe_flt_rounds = (void *)GetProcAddress(msvcrt, "__fpe_flt_rounds");
    p___fpecode = (void *)GetProcAddress(msvcrt, "__fpecode");
    p___getmainargs = (void *)GetProcAddress(msvcrt, "__getmainargs");
    p___iob_func = (void *)GetProcAddress(msvcrt, "__iob_func");
    p___isascii = (void *)GetProcAddress(msvcrt, "__isascii");
    p___iscsym = (void *)GetProcAddress(msvcrt, "__iscsym");
    p___iscsymf = (void *)GetProcAddress(msvcrt, "__iscsymf");
    p___lconv_init = (void *)GetProcAddress(msvcrt, "__lconv_init");
    p___libm_sse2_acos = (void *)GetProcAddress(msvcrt, "__libm_sse2_acos");
    p___libm_sse2_acosf = (void *)GetProcAddress(msvcrt, "__libm_sse2_acosf");
    p___libm_sse2_asin = (void *)GetProcAddress(msvcrt, "__libm_sse2_asin");
    p___libm_sse2_asinf = (void *)GetProcAddress(msvcrt, "__libm_sse2_asinf");
    p___libm_sse2_atan = (void *)GetProcAddress(msvcrt, "__libm_sse2_atan");
    p___libm_sse2_atan2 = (void *)GetProcAddress(msvcrt, "__libm_sse2_atan2");
    p___libm_sse2_atanf = (void *)GetProcAddress(msvcrt, "__libm_sse2_atanf");
    p___libm_sse2_cos = (void *)GetProcAddress(msvcrt, "__libm_sse2_cos");
    p___libm_sse2_cosf = (void *)GetProcAddress(msvcrt, "__libm_sse2_cosf");
    p___libm_sse2_exp = (void *)GetProcAddress(msvcrt, "__libm_sse2_exp");
    p___libm_sse2_expf = (void *)GetProcAddress(msvcrt, "__libm_sse2_expf");
    p___libm_sse2_log = (void *)GetProcAddress(msvcrt, "__libm_sse2_log");
    p___libm_sse2_log10 = (void *)GetProcAddress(msvcrt, "__libm_sse2_log10");
    p___libm_sse2_log10f = (void *)GetProcAddress(msvcrt, "__libm_sse2_log10f");
    p___libm_sse2_logf = (void *)GetProcAddress(msvcrt, "__libm_sse2_logf");
    p___libm_sse2_pow = (void *)GetProcAddress(msvcrt, "__libm_sse2_pow");
    p___libm_sse2_powf = (void *)GetProcAddress(msvcrt, "__libm_sse2_powf");
    p___libm_sse2_sin = (void *)GetProcAddress(msvcrt, "__libm_sse2_sin");
    p___libm_sse2_sinf = (void *)GetProcAddress(msvcrt, "__libm_sse2_sinf");
    p___libm_sse2_sqrt_precise = (void *)GetProcAddress(msvcrt, "__libm_sse2_sqrt_precise");
    p___libm_sse2_tan = (void *)GetProcAddress(msvcrt, "__libm_sse2_tan");
    p___libm_sse2_tanf = (void *)GetProcAddress(msvcrt, "__libm_sse2_tanf");
    p___p___mb_cur_max = (void *)GetProcAddress(msvcrt, "__p___mb_cur_max");
    p___p__mbctype = (void *)GetProcAddress(msvcrt, "__p__mbctype");
    p___p__pctype = (void *)GetProcAddress(msvcrt, "__p__pctype");
    p___pctype_func = (void *)GetProcAddress(msvcrt, "__pctype_func");
    p___set_app_type = (void *)GetProcAddress(msvcrt, "__set_app_type");
    p___setusermatherr = (void *)GetProcAddress(msvcrt, "__setusermatherr");
    p___sys_errlist = (void *)GetProcAddress(msvcrt, "__sys_errlist");
    p___sys_nerr = (void *)GetProcAddress(msvcrt, "__sys_nerr");
    p___toascii = (void *)GetProcAddress(msvcrt, "__toascii");
    p___wcserror = (void *)GetProcAddress(msvcrt, "__wcserror");
    p___wcserror_s = (void *)GetProcAddress(msvcrt, "__wcserror_s");
    p___wgetmainargs = (void *)GetProcAddress(msvcrt, "__wgetmainargs");
    p__abs64 = (void *)GetProcAddress(msvcrt, "_abs64");
    p__amsg_exit = (void *)GetProcAddress(msvcrt, "_amsg_exit");
    p__cabs = (void *)GetProcAddress(msvcrt, "_cabs");
    p__cexit = (void *)GetProcAddress(msvcrt, "_cexit");
    p__chgsign = (void *)GetProcAddress(msvcrt, "_chgsign");
    p__chgsignf = (void *)GetProcAddress(msvcrt, "_chgsignf");
    p__CIacos = (void *)GetProcAddress(msvcrt, "_CIacos");
    p__CIasin = (void *)GetProcAddress(msvcrt, "_CIasin");
    p__CIatan = (void *)GetProcAddress(msvcrt, "_CIatan");
    p__CIatan2 = (void *)GetProcAddress(msvcrt, "_CIatan2");
    p__CIcos = (void *)GetProcAddress(msvcrt, "_CIcos");
    p__CIcosh = (void *)GetProcAddress(msvcrt, "_CIcosh");
    p__CIexp = (void *)GetProcAddress(msvcrt, "_CIexp");
    p__CIfmod = (void *)GetProcAddress(msvcrt, "_CIfmod");
    p__CIlog = (void *)GetProcAddress(msvcrt, "_CIlog");
    p__CIlog10 = (void *)GetProcAddress(msvcrt, "_CIlog10");
    p__CIpow = (void *)GetProcAddress(msvcrt, "_CIpow");
    p__CIsin = (void *)GetProcAddress(msvcrt, "_CIsin");
    p__CIsinh = (void *)GetProcAddress(msvcrt, "_CIsinh");
    p__CIsqrt = (void *)GetProcAddress(msvcrt, "_CIsqrt");
    p__CItan = (void *)GetProcAddress(msvcrt, "_CItan");
    p__CItanh = (void *)GetProcAddress(msvcrt, "_CItanh");
    p__clearfp = (void *)GetProcAddress(msvcrt, "_clearfp");
    p__configthreadlocale = (void *)GetProcAddress(msvcrt, "_configthreadlocale");
    p__control87 = (void *)GetProcAddress(msvcrt, "_control87");
    p__controlfp = (void *)GetProcAddress(msvcrt, "_controlfp");
    p__copysign = (void *)GetProcAddress(msvcrt, "_copysign");
    p__copysignf = (void *)GetProcAddress(msvcrt, "_copysignf");
    p__dclass = (void *)GetProcAddress(msvcrt, "_dclass");
    p__dpcomp = (void *)GetProcAddress(msvcrt, "_dpcomp");
    p__dsign = (void *)GetProcAddress(msvcrt, "_dsign");
    p__dtest = (void *)GetProcAddress(msvcrt, "_dtest");
    p__dup = (void *)GetProcAddress(msvcrt, "_dup");
    p__dup2 = (void *)GetProcAddress(msvcrt, "_dup2");
    p__dupenv_s = (void *)GetProcAddress(msvcrt, "_dupenv_s");
    p__ecvt = (void *)GetProcAddress(msvcrt, "_ecvt");
    p__ecvt_s = (void *)GetProcAddress(msvcrt, "_ecvt_s");
    p__eof = (void *)GetProcAddress(msvcrt, "_eof");
    p__errno = (void *)GetProcAddress(msvcrt, "_errno");
    p__errno = (void *)GetProcAddress(msvcrt, "_errno");
    p__exit = (void *)GetProcAddress(msvcrt, "_exit");
    p__fclose_nolock = (void *)GetProcAddress(msvcrt, "_fclose_nolock");
    p__fcloseall = (void *)GetProcAddress(msvcrt, "_fcloseall");
    p__fcvt = (void *)GetProcAddress(msvcrt, "_fcvt");
    p__fcvt_s = (void *)GetProcAddress(msvcrt, "_fcvt_s");
    p__fdclass = (void *)GetProcAddress(msvcrt, "_fdclass");
    p__fdopen = (void *)GetProcAddress(msvcrt, "_fdopen");
    p__fdpcomp = (void *)GetProcAddress(msvcrt, "_fdpcomp");
    p__fdsign = (void *)GetProcAddress(msvcrt, "_fdsign");
    p__fdtest = (void *)GetProcAddress(msvcrt, "_fdtest");
    p__fflush_nolock = (void *)GetProcAddress(msvcrt, "_fflush_nolock");
    p__fgetc_nolock = (void *)GetProcAddress(msvcrt, "_fgetc_nolock");
    p__fgetchar = (void *)GetProcAddress(msvcrt, "_fgetchar");
    p__fgetwc_nolock = (void *)GetProcAddress(msvcrt, "_fgetwc_nolock");
    p__fgetwchar = (void *)GetProcAddress(msvcrt, "_fgetwchar");
    p__filbuf = (void *)GetProcAddress(msvcrt, "_filbuf");
    p__filelength = (void *)GetProcAddress(msvcrt, "_filelength");
    p__filelengthi64 = (void *)GetProcAddress(msvcrt, "_filelengthi64");
    p__fileno = (void *)GetProcAddress(msvcrt, "_fileno");
    p__finite = (void *)GetProcAddress(msvcrt, "_finite");
    p__finitef = (void *)GetProcAddress(msvcrt, "_finitef");
    p__flsbuf = (void *)GetProcAddress(msvcrt, "_flsbuf");
    p__flushall = (void *)GetProcAddress(msvcrt, "_flushall");
    p__fpclass = (void *)GetProcAddress(msvcrt, "_fpclass");
    p__fpreset = (void *)GetProcAddress(msvcrt, "_fpreset");
    p__fputc_nolock = (void *)GetProcAddress(msvcrt, "_fputc_nolock");
    p__fputchar = (void *)GetProcAddress(msvcrt, "_fputchar");
    p__fputwc_nolock = (void *)GetProcAddress(msvcrt, "_fputwc_nolock");
    p__fputwchar = (void *)GetProcAddress(msvcrt, "_fputwchar");
    p__fread_nolock = (void *)GetProcAddress(msvcrt, "_fread_nolock");
    p__fread_nolock_s = (void *)GetProcAddress(msvcrt, "_fread_nolock_s");
    p__fseek_nolock = (void *)GetProcAddress(msvcrt, "_fseek_nolock");
    p__fseeki64 = (void *)GetProcAddress(msvcrt, "_fseeki64");
    p__fseeki64_nolock = (void *)GetProcAddress(msvcrt, "_fseeki64_nolock");
    p__fsopen = (void *)GetProcAddress(msvcrt, "_fsopen");
    p__fstat = (void *)GetProcAddress(msvcrt, "_fstat");
    p__fstat32 = (void *)GetProcAddress(msvcrt, "_fstat32");
    p__fstat32i64 = (void *)GetProcAddress(msvcrt, "_fstat32i64");
    p__fstat64 = (void *)GetProcAddress(msvcrt, "_fstat64");
    p__fstat64i32 = (void *)GetProcAddress(msvcrt, "_fstat64i32");
    p__fstati64 = (void *)GetProcAddress(msvcrt, "_fstati64");
    p__ftell_nolock = (void *)GetProcAddress(msvcrt, "_ftell_nolock");
    p__ftelli64 = (void *)GetProcAddress(msvcrt, "_ftelli64");
    p__ftelli64_nolock = (void *)GetProcAddress(msvcrt, "_ftelli64_nolock");
    p__ftol = (void *)GetProcAddress(msvcrt, "_ftol");
    p__fwrite_nolock = (void *)GetProcAddress(msvcrt, "_fwrite_nolock");
    p__gcvt = (void *)GetProcAddress(msvcrt, "_gcvt");
    p__gcvt_s = (void *)GetProcAddress(msvcrt, "_gcvt_s");
    p__get_doserrno = (void *)GetProcAddress(msvcrt, "_get_doserrno");
    p__get_errno = (void *)GetProcAddress(msvcrt, "_get_errno");
    p__get_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_get_invalid_parameter_handler");
    p__get_osfhandle = (void *)GetProcAddress(msvcrt, "_get_osfhandle");
    p__get_stream_buffer_pointers = (void *)GetProcAddress(msvcrt, "_get_stream_buffer_pointers");
    p__get_thread_local_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_get_thread_local_invalid_parameter_handler");
    p__getmaxstdio = (void *)GetProcAddress(msvcrt, "_getmaxstdio");
    p__getmbcp = (void *)GetProcAddress(msvcrt, "_getmbcp");
    p__getw = (void *)GetProcAddress(msvcrt, "_getw");
    p__getws = (void *)GetProcAddress(msvcrt, "_getws");
    p__hypot = (void *)GetProcAddress(msvcrt, "_hypot");
    p__hypotf = (void *)GetProcAddress(msvcrt, "_hypotf");
    p__invalid_parameter_noinfo = (void *)GetProcAddress(msvcrt, "_invalid_parameter_noinfo");
    p__invalid_parameter_noinfo_noreturn = (void *)GetProcAddress(msvcrt, "_invalid_parameter_noinfo_noreturn");
    p__isalnum_l = (void *)GetProcAddress(msvcrt, "_isalnum_l");
    p__isalpha_l = (void *)GetProcAddress(msvcrt, "_isalpha_l");
    p__isatty = (void *)GetProcAddress(msvcrt, "_isatty");
    p__isatty = (void *)GetProcAddress(msvcrt, "_isatty");
    p__isblank_l = (void *)GetProcAddress(msvcrt, "_isblank_l");
    p__iscntrl_l = (void *)GetProcAddress(msvcrt, "_iscntrl_l");
    p__isctype = (void *)GetProcAddress(msvcrt, "_isctype");
    p__isctype_l = (void *)GetProcAddress(msvcrt, "_isctype_l");
    p__isdigit_l = (void *)GetProcAddress(msvcrt, "_isdigit_l");
    p__isgraph_l = (void *)GetProcAddress(msvcrt, "_isgraph_l");
    p__isleadbyte_l = (void *)GetProcAddress(msvcrt, "_isleadbyte_l");
    p__islower_l = (void *)GetProcAddress(msvcrt, "_islower_l");
    p__ismbbkana = (void *)GetProcAddress(msvcrt, "_ismbbkana");
    p__ismbblead = (void *)GetProcAddress(msvcrt, "_ismbblead");
    p__ismbblead_l = (void *)GetProcAddress(msvcrt, "_ismbblead_l");
    p__ismbbtrail = (void *)GetProcAddress(msvcrt, "_ismbbtrail");
    p__ismbcalnum = (void *)GetProcAddress(msvcrt, "_ismbcalnum");
    p__ismbcalpha = (void *)GetProcAddress(msvcrt, "_ismbcalpha");
    p__ismbcdigit = (void *)GetProcAddress(msvcrt, "_ismbcdigit");
    p__ismbcgraph = (void *)GetProcAddress(msvcrt, "_ismbcgraph");
    p__ismbchira = (void *)GetProcAddress(msvcrt, "_ismbchira");
    p__ismbckata = (void *)GetProcAddress(msvcrt, "_ismbckata");
    p__ismbclegal = (void *)GetProcAddress(msvcrt, "_ismbclegal");
    p__ismbclower = (void *)GetProcAddress(msvcrt, "_ismbclower");
    p__ismbcprint = (void *)GetProcAddress(msvcrt, "_ismbcprint");
    p__ismbcpunct = (void *)GetProcAddress(msvcrt, "_ismbcpunct");
    p__ismbcspace = (void *)GetProcAddress(msvcrt, "_ismbcspace");
    p__ismbcsymbol = (void *)GetProcAddress(msvcrt, "_ismbcsymbol");
    p__ismbcupper = (void *)GetProcAddress(msvcrt, "_ismbcupper");
    p__ismbslead = (void *)GetProcAddress(msvcrt, "_ismbslead");
    p__ismbstrail = (void *)GetProcAddress(msvcrt, "_ismbstrail");
    p__isnan = (void *)GetProcAddress(msvcrt, "_isnan");
    p__isnanf = (void *)GetProcAddress(msvcrt, "_isnanf");
    p__isprint_l = (void *)GetProcAddress(msvcrt, "_isprint_l");
    p__isspace_l = (void *)GetProcAddress(msvcrt, "_isspace_l");
    p__isupper_l = (void *)GetProcAddress(msvcrt, "_isupper_l");
    p__isxdigit_l = (void *)GetProcAddress(msvcrt, "_isxdigit_l");
    p__j0 = (void *)GetProcAddress(msvcrt, "_j0");
    p__j1 = (void *)GetProcAddress(msvcrt, "_j1");
    p__jn = (void *)GetProcAddress(msvcrt, "_jn");
    p__ldclass = (void *)GetProcAddress(msvcrt, "_ldclass");
    p__ldtest = (void *)GetProcAddress(msvcrt, "_ldtest");
    p__lock = (void *)GetProcAddress(msvcrt, "_lock");
    p__lock_file = (void *)GetProcAddress(msvcrt, "_lock_file");
    p__locking = (void *)GetProcAddress(msvcrt, "_locking");
    p__logb = (void *)GetProcAddress(msvcrt, "_logb");
    p__logbf = (void *)GetProcAddress(msvcrt, "_logbf");
    p__lrotl = (void *)GetProcAddress(msvcrt, "_lrotl");
    p__lrotr = (void *)GetProcAddress(msvcrt, "_lrotr");
    p__lseek = (void *)GetProcAddress(msvcrt, "_lseek");
    p__lseek = (void *)GetProcAddress(msvcrt, "_lseek");
    p__lseeki64 = (void *)GetProcAddress(msvcrt, "_lseeki64");
    p__lseeki64 = (void *)GetProcAddress(msvcrt, "_lseeki64");
    p__matherr = (void *)GetProcAddress(msvcrt, "_matherr");
    p__mbbtombc = (void *)GetProcAddress(msvcrt, "_mbbtombc");
    p__mbbtype = (void *)GetProcAddress(msvcrt, "_mbbtype");
    p__mbccpy = (void *)GetProcAddress(msvcrt, "_mbccpy");
    p__mbcjistojms = (void *)GetProcAddress(msvcrt, "_mbcjistojms");
    p__mbcjmstojis = (void *)GetProcAddress(msvcrt, "_mbcjmstojis");
    p__mbclen = (void *)GetProcAddress(msvcrt, "_mbclen");
    p__mbctohira = (void *)GetProcAddress(msvcrt, "_mbctohira");
    p__mbctokata = (void *)GetProcAddress(msvcrt, "_mbctokata");
    p__mbctolower = (void *)GetProcAddress(msvcrt, "_mbctolower");
    p__mbctombb = (void *)GetProcAddress(msvcrt, "_mbctombb");
    p__mbctoupper = (void *)GetProcAddress(msvcrt, "_mbctoupper");
    p__mbsbtype = (void *)GetProcAddress(msvcrt, "_mbsbtype");
    p__mbscat = (void *)GetProcAddress(msvcrt, "_mbscat");
    p__mbscat_s = (void *)GetProcAddress(msvcrt, "_mbscat_s");
    p__mbscat_s_l = (void *)GetProcAddress(msvcrt, "_mbscat_s_l");
    p__mbschr = (void *)GetProcAddress(msvcrt, "_mbschr");
    p__mbscmp = (void *)GetProcAddress(msvcrt, "_mbscmp");
    p__mbscoll = (void *)GetProcAddress(msvcrt, "_mbscoll");
    p__mbscoll_l = (void *)GetProcAddress(msvcrt, "_mbscoll_l");
    p__mbscpy = (void *)GetProcAddress(msvcrt, "_mbscpy");
    p__mbscpy_s = (void *)GetProcAddress(msvcrt, "_mbscpy_s");
    p__mbscpy_s_l = (void *)GetProcAddress(msvcrt, "_mbscpy_s_l");
    p__mbscspn = (void *)GetProcAddress(msvcrt, "_mbscspn");
    p__mbsdec = (void *)GetProcAddress(msvcrt, "_mbsdec");
    p__mbsicmp = (void *)GetProcAddress(msvcrt, "_mbsicmp");
    p__mbsicoll = (void *)GetProcAddress(msvcrt, "_mbsicoll");
    p__mbsicoll_l = (void *)GetProcAddress(msvcrt, "_mbsicoll_l");
    p__mbsinc = (void *)GetProcAddress(msvcrt, "_mbsinc");
    p__mbslen = (void *)GetProcAddress(msvcrt, "_mbslen");
    p__mbslwr = (void *)GetProcAddress(msvcrt, "_mbslwr");
    p__mbslwr_s = (void *)GetProcAddress(msvcrt, "_mbslwr_s");
    p__mbsnbcat = (void *)GetProcAddress(msvcrt, "_mbsnbcat");
    p__mbsnbcat_s = (void *)GetProcAddress(msvcrt, "_mbsnbcat_s");
    p__mbsnbcmp = (void *)GetProcAddress(msvcrt, "_mbsnbcmp");
    p__mbsnbcnt = (void *)GetProcAddress(msvcrt, "_mbsnbcnt");
    p__mbsnbcoll = (void *)GetProcAddress(msvcrt, "_mbsnbcoll");
    p__mbsnbcoll_l = (void *)GetProcAddress(msvcrt, "_mbsnbcoll_l");
    p__mbsnbcpy = (void *)GetProcAddress(msvcrt, "_mbsnbcpy");
    p__mbsnbcpy_s = (void *)GetProcAddress(msvcrt, "_mbsnbcpy_s");
    p__mbsnbcpy_s_l = (void *)GetProcAddress(msvcrt, "_mbsnbcpy_s_l");
    p__mbsnbicmp = (void *)GetProcAddress(msvcrt, "_mbsnbicmp");
    p__mbsnbicoll = (void *)GetProcAddress(msvcrt, "_mbsnbicoll");
    p__mbsnbicoll_l = (void *)GetProcAddress(msvcrt, "_mbsnbicoll_l");
    p__mbsnbset = (void *)GetProcAddress(msvcrt, "_mbsnbset");
    p__mbsncat = (void *)GetProcAddress(msvcrt, "_mbsncat");
    p__mbsnccnt = (void *)GetProcAddress(msvcrt, "_mbsnccnt");
    p__mbsncmp = (void *)GetProcAddress(msvcrt, "_mbsncmp");
    p__mbsncpy = (void *)GetProcAddress(msvcrt, "_mbsncpy");
    p__mbsnextc = (void *)GetProcAddress(msvcrt, "_mbsnextc");
    p__mbsnicmp = (void *)GetProcAddress(msvcrt, "_mbsnicmp");
    p__mbsninc = (void *)GetProcAddress(msvcrt, "_mbsninc");
    p__mbsnset = (void *)GetProcAddress(msvcrt, "_mbsnset");
    p__mbspbrk = (void *)GetProcAddress(msvcrt, "_mbspbrk");
    p__mbsrchr = (void *)GetProcAddress(msvcrt, "_mbsrchr");
    p__mbsrev = (void *)GetProcAddress(msvcrt, "_mbsrev");
    p__mbsset = (void *)GetProcAddress(msvcrt, "_mbsset");
    p__mbsspn = (void *)GetProcAddress(msvcrt, "_mbsspn");
    p__mbsspnp = (void *)GetProcAddress(msvcrt, "_mbsspnp");
    p__mbsstr = (void *)GetProcAddress(msvcrt, "_mbsstr");
    p__mbstok = (void *)GetProcAddress(msvcrt, "_mbstok");
    p__mbstok_l = (void *)GetProcAddress(msvcrt, "_mbstok_l");
    p__mbstok_s = (void *)GetProcAddress(msvcrt, "_mbstok_s");
    p__mbstok_s_l = (void *)GetProcAddress(msvcrt, "_mbstok_s_l");
    p__mbstowcs_l = (void *)GetProcAddress(msvcrt, "_mbstowcs_l");
    p__mbstowcs_s = (void *)GetProcAddress(msvcrt, "_mbstowcs_s");
    p__mbstowcs_s_l = (void *)GetProcAddress(msvcrt, "_mbstowcs_s_l");
    p__mbstrlen = (void *)GetProcAddress(msvcrt, "_mbstrlen");
    p__mbstrlen_l = (void *)GetProcAddress(msvcrt, "_mbstrlen_l");
    p__mbsupr = (void *)GetProcAddress(msvcrt, "_mbsupr");
    p__mbsupr_s = (void *)GetProcAddress(msvcrt, "_mbsupr_s");
    p__mktemp = (void *)GetProcAddress(msvcrt, "_mktemp");
    p__mktemp_s = (void *)GetProcAddress(msvcrt, "_mktemp_s");
    p__nextafter = (void *)GetProcAddress(msvcrt, "_nextafter");
    p__nextafterf = (void *)GetProcAddress(msvcrt, "_nextafterf");
    p__onexit = (void *)GetProcAddress(msvcrt, "_onexit");
    p__open_osfhandle = (void *)GetProcAddress(msvcrt, "_open_osfhandle");
    p__pipe = (void *)GetProcAddress(msvcrt, "_pipe");
    p__purecall = (void *)GetProcAddress(msvcrt, "_purecall");
    p__putenv = (void *)GetProcAddress(msvcrt, "_putenv");
    p__putenv_s = (void *)GetProcAddress(msvcrt, "_putenv_s");
    p__putw = (void *)GetProcAddress(msvcrt, "_putw");
    p__putws = (void *)GetProcAddress(msvcrt, "_putws");
    p__read = (void *)GetProcAddress(msvcrt, "_read");
    p__rmtmp = (void *)GetProcAddress(msvcrt, "_rmtmp");
    p__rotl = (void *)GetProcAddress(msvcrt, "_rotl");
    p__rotl64 = (void *)GetProcAddress(msvcrt, "_rotl64");
    p__rotr = (void *)GetProcAddress(msvcrt, "_rotr");
    p__rotr64 = (void *)GetProcAddress(msvcrt, "_rotr64");
    p__scalb = (void *)GetProcAddress(msvcrt, "_scalb");
    p__scalbf = (void *)GetProcAddress(msvcrt, "_scalbf");
    p__set_controlfp = (void *)GetProcAddress(msvcrt, "_set_controlfp");
    p__set_doserrno = (void *)GetProcAddress(msvcrt, "_set_doserrno");
    p__set_errno = (void *)GetProcAddress(msvcrt, "_set_errno");
    p__set_FMA3_enable = (void *)GetProcAddress(msvcrt, "_set_FMA3_enable");
    p__set_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_set_invalid_parameter_handler");
    p__set_SSE2_enable = (void *)GetProcAddress(msvcrt, "_set_SSE2_enable");
    p__set_thread_local_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_set_thread_local_invalid_parameter_handler");
    p__seterrormode = (void *)GetProcAddress(msvcrt, "_seterrormode");
    p__setmaxstdio = (void *)GetProcAddress(msvcrt, "_setmaxstdio");
    p__setmbcp = (void *)GetProcAddress(msvcrt, "_setmbcp");
    p__setmode = (void *)GetProcAddress(msvcrt, "_setmode");
    p__sopen_dispatch = (void *)GetProcAddress(msvcrt, "_sopen_dispatch");
    p__sopen_s = (void *)GetProcAddress(msvcrt, "_sopen_s");
    p__stat32 = (void *)GetProcAddress(msvcrt, "_stat32");
    p__stat32i64 = (void *)GetProcAddress(msvcrt, "_stat32i64");
    p__stat64 = (void *)GetProcAddress(msvcrt, "_stat64");
    p__stat64i32 = (void *)GetProcAddress(msvcrt, "_stat64i32");
    p__statusfp = (void *)GetProcAddress(msvcrt, "_statusfp");
    p__statusfp2 = (void *)GetProcAddress(msvcrt, "_statusfp2");
    p__strdate = (void *)GetProcAddress(msvcrt, "_strdate");
    p__strdup = (void *)GetProcAddress(msvcrt, "_strdup");
    p__strerror = (void *)GetProcAddress(msvcrt, "_strerror");
    p__stricmp = (void *)GetProcAddress(msvcrt, "_stricmp");
    p__strnicmp = (void *)GetProcAddress(msvcrt, "_strnicmp");
    p__strtime = (void *)GetProcAddress(msvcrt, "_strtime");
    p__strtoui64 = (void *)GetProcAddress(msvcrt, "_strtoui64");
    p__tell = (void *)GetProcAddress(msvcrt, "_tell");
    p__tempnam = (void *)GetProcAddress(msvcrt, "_tempnam");
    p__tempnam = (void *)GetProcAddress(msvcrt, "_tempnam");
    p__time64 = (void *)GetProcAddress(msvcrt, "_time64");
    p__tolower = (void *)GetProcAddress(msvcrt, "_tolower");
    p__tolower_l = (void *)GetProcAddress(msvcrt, "_tolower_l");
    p__toupper = (void *)GetProcAddress(msvcrt, "_toupper");
    p__toupper_l = (void *)GetProcAddress(msvcrt, "_toupper_l");
    p__umask = (void *)GetProcAddress(msvcrt, "_umask");
    p__ungetc_nolock = (void *)GetProcAddress(msvcrt, "_ungetc_nolock");
    p__ungetwc_nolock = (void *)GetProcAddress(msvcrt, "_ungetwc_nolock");
    p__unlink = (void *)GetProcAddress(msvcrt, "_unlink");
    p__unlock = (void *)GetProcAddress(msvcrt, "_unlock");
    p__unlock_file = (void *)GetProcAddress(msvcrt, "_unlock_file");
    p__vsnprintf = (void *)GetProcAddress(msvcrt, "_vsnprintf");
    p__vsnwprintf = (void *)GetProcAddress(msvcrt, "_vsnwprintf");
    p__waccess = (void *)GetProcAddress(msvcrt, "_waccess");
    p__waccess_s = (void *)GetProcAddress(msvcrt, "_waccess_s");
    p__wchmod = (void *)GetProcAddress(msvcrt, "_wchmod");
    p__wcreat = (void *)GetProcAddress(msvcrt, "_wcreat");
    p__wcserror = (void *)GetProcAddress(msvcrt, "_wcserror");
    p__wcserror_s = (void *)GetProcAddress(msvcrt, "_wcserror_s");
    p__wcsnicmp = (void *)GetProcAddress(msvcrt, "_wcsnicmp");
    p__wdupenv_s = (void *)GetProcAddress(msvcrt, "_wdupenv_s");
    p__wfdopen = (void *)GetProcAddress(msvcrt, "_wfdopen");
    p__wfopen = (void *)GetProcAddress(msvcrt, "_wfopen");
    p__wfopen_s = (void *)GetProcAddress(msvcrt, "_wfopen_s");
    p__wfreopen = (void *)GetProcAddress(msvcrt, "_wfreopen");
    p__wfreopen_s = (void *)GetProcAddress(msvcrt, "_wfreopen_s");
    p__wfsopen = (void *)GetProcAddress(msvcrt, "_wfsopen");
    p__wgetenv = (void *)GetProcAddress(msvcrt, "__wgetenv");
    p__wgetenv_s = (void *)GetProcAddress(msvcrt, "_wgetenv_s");
    p__wmktemp = (void *)GetProcAddress(msvcrt, "_wmktemp");
    p__wmktemp_s = (void *)GetProcAddress(msvcrt, "_wmktemp_s");
    p__wperror = (void *)GetProcAddress(msvcrt, "_wperror");
    p__wputenv = (void *)GetProcAddress(msvcrt, "_wputenv");
    p__wputenv_s = (void *)GetProcAddress(msvcrt, "_wputenv_s");
    p__wremove = (void *)GetProcAddress(msvcrt, "_wremove");
    p__wrename = (void *)GetProcAddress(msvcrt, "_wrename");
    p__write = (void *)GetProcAddress(msvcrt, "_write");
    p__write = (void *)GetProcAddress(msvcrt, "_write");
    p__wsopen_dispatch = (void *)GetProcAddress(msvcrt, "_wsopen_dispatch");
    p__wsopen_s = (void *)GetProcAddress(msvcrt, "_wsopen_s");
    p__wstat = (void *)GetProcAddress(msvcrt, "_wstat");
    p__wstat32 = (void *)GetProcAddress(msvcrt, "_wstat32");
    p__wstat32i64 = (void *)GetProcAddress(msvcrt, "_wstat32i64");
    p__wstat64 = (void *)GetProcAddress(msvcrt, "_wstat64");
    p__wstat64i32 = (void *)GetProcAddress(msvcrt, "_wstat64i32");
    p__wstati64 = (void *)GetProcAddress(msvcrt, "_wstati64");
    p__wtempnam = (void *)GetProcAddress(msvcrt, "_wtempnam");
    p__wtmpnam = (void *)GetProcAddress(msvcrt, "_wtmpnam");
    p__wtmpnam_s = (void *)GetProcAddress(msvcrt, "_wtmpnam_s");
    p__wtof = (void *)GetProcAddress(msvcrt, "_wtof");
    p__wtoi = (void *)GetProcAddress(msvcrt, "_wtoi");
    p__wunlink = (void *)GetProcAddress(msvcrt, "_wunlink");
    p__y0 = (void *)GetProcAddress(msvcrt, "_y0");
    p__y1 = (void *)GetProcAddress(msvcrt, "_y1");
    p__yn = (void *)GetProcAddress(msvcrt, "_yn");
    p_abort = (void *)GetProcAddress(msvcrt, "abort");
    p_abs = (void *)GetProcAddress(msvcrt, "abs");
    p_acos = (void *)GetProcAddress(msvcrt, "acos");
    p_acosf = (void *)GetProcAddress(msvcrt, "acosf");
    p_acosh = (void *)GetProcAddress(msvcrt, "acosh");
    p_acoshf = (void *)GetProcAddress(msvcrt, "acoshf");
    p_acoshl = (void *)GetProcAddress(msvcrt, "acoshl");
    p_asin = (void *)GetProcAddress(msvcrt, "asin");
    p_asinf = (void *)GetProcAddress(msvcrt, "asinf");
    p_asinh = (void *)GetProcAddress(msvcrt, "asinh");
    p_asinhf = (void *)GetProcAddress(msvcrt, "asinhf");
    p_asinhl = (void *)GetProcAddress(msvcrt, "asinhl");
    p_atan = (void *)GetProcAddress(msvcrt, "atan");
    p_atan2 = (void *)GetProcAddress(msvcrt, "atan2");
    p_atan2f = (void *)GetProcAddress(msvcrt, "atan2f");
    p_atanf = (void *)GetProcAddress(msvcrt, "atanf");
    p_atanh = (void *)GetProcAddress(msvcrt, "atanh");
    p_atanhf = (void *)GetProcAddress(msvcrt, "atanhf");
    p_atanhl = (void *)GetProcAddress(msvcrt, "atanhl");
    p_atof = (void *)GetProcAddress(msvcrt, "atof");
    p_bsearch = (void *)GetProcAddress(msvcrt, "bsearch");
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_cbrt = (void *)GetProcAddress(msvcrt, "cbrt");
    p_cbrtf = (void *)GetProcAddress(msvcrt, "cbrtf");
    p_cbrtl = (void *)GetProcAddress(msvcrt, "cbrtl");
    p_ceil = (void *)GetProcAddress(msvcrt, "ceil");
    p_ceilf = (void *)GetProcAddress(msvcrt, "ceilf");
    p_clearerr = (void *)GetProcAddress(msvcrt, "clearerr");
    p_cos = (void *)GetProcAddress(msvcrt, "cos");
    p_cosf = (void *)GetProcAddress(msvcrt, "cosf");
    p_cosh = (void *)GetProcAddress(msvcrt, "cosh");
    p_coshf = (void *)GetProcAddress(msvcrt, "coshf");
    p_div = (void *)GetProcAddress(msvcrt, "div");
    p_erf = (void *)GetProcAddress(msvcrt, "erf");
    p_erfc = (void *)GetProcAddress(msvcrt, "erfc");
    p_erfcf = (void *)GetProcAddress(msvcrt, "erfcf");
    p_erfcl = (void *)GetProcAddress(msvcrt, "erfcl");
    p_erff = (void *)GetProcAddress(msvcrt, "erff");
    p_erfl = (void *)GetProcAddress(msvcrt, "erfl");
    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_exp = (void *)GetProcAddress(msvcrt, "exp");
    p_exp2 = (void *)GetProcAddress(msvcrt, "exp2");
    p_exp2f = (void *)GetProcAddress(msvcrt, "exp2f");
    p_exp2l = (void *)GetProcAddress(msvcrt, "exp2l");
    p_expf = (void *)GetProcAddress(msvcrt, "expf");
    p_expm1 = (void *)GetProcAddress(msvcrt, "expm1");
    p_expm1f = (void *)GetProcAddress(msvcrt, "expm1f");
    p_expm1l = (void *)GetProcAddress(msvcrt, "expm1l");
    p_fabs = (void *)GetProcAddress(msvcrt, "fabs");
    p_fabsf = (void *)GetProcAddress(msvcrt, "fabsf");
    p_fclose = (void *)GetProcAddress(msvcrt, "fclose");
    p_fegetenv = (void *)GetProcAddress(msvcrt, "fegetenv");
    p_fegetround = (void *)GetProcAddress(msvcrt, "fegetround");
    p_feof = (void *)GetProcAddress(msvcrt, "feof");
    p_ferror = (void *)GetProcAddress(msvcrt, "ferror");
    p_fesetenv = (void *)GetProcAddress(msvcrt, "fesetenv");
    p_fesetround = (void *)GetProcAddress(msvcrt, "fesetround");
    p_fflush = (void *)GetProcAddress(msvcrt, "fflush");
    p_fflush = (void *)GetProcAddress(msvcrt, "fflush");
    p_fgetc = (void *)GetProcAddress(msvcrt, "fgetc");
    p_fgetpos = (void *)GetProcAddress(msvcrt, "fgetpos");
    p_fgets = (void *)GetProcAddress(msvcrt, "fgets");
    p_fgetwc = (void *)GetProcAddress(msvcrt, "fgetwc");
    p_fgetws = (void *)GetProcAddress(msvcrt, "fgetws");
    p_floor = (void *)GetProcAddress(msvcrt, "floor");
    p_floorf = (void *)GetProcAddress(msvcrt, "floorf");
    p_fmax = (void *)GetProcAddress(msvcrt, "fmax");
    p_fmaxf = (void *)GetProcAddress(msvcrt, "fmaxf");
    p_fmin = (void *)GetProcAddress(msvcrt, "fmin");
    p_fminf = (void *)GetProcAddress(msvcrt, "fminf");
    p_fmod = (void *)GetProcAddress(msvcrt, "fmod");
    p_fmodf = (void *)GetProcAddress(msvcrt, "fmodf");
    p_fopen = (void *)GetProcAddress(msvcrt, "fopen");
    p_fopen_s = (void *)GetProcAddress(msvcrt, "fopen_s");
    p_fputc = (void *)GetProcAddress(msvcrt, "fputc");
    p_fputs = (void *)GetProcAddress(msvcrt, "fputs");
    p_fputwc = (void *)GetProcAddress(msvcrt, "fputwc");
    p_fputws = (void *)GetProcAddress(msvcrt, "fputws");
    p_fread = (void *)GetProcAddress(msvcrt, "fread");
    p_fread = (void *)GetProcAddress(msvcrt, "fread");
    p_fread_s = (void *)GetProcAddress(msvcrt, "fread_s");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_freopen = (void *)GetProcAddress(msvcrt, "freopen");
    p_freopen_s = (void *)GetProcAddress(msvcrt, "freopen_s");
    p_frexp = (void *)GetProcAddress(msvcrt, "frexp");
    p_frexpf = (void *)GetProcAddress(msvcrt, "frexpf");
    p_fseek = (void *)GetProcAddress(msvcrt, "fseek");
    p_fsetpos = (void *)GetProcAddress(msvcrt, "fsetpos");
    p_ftell = (void *)GetProcAddress(msvcrt, "ftell");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_getc = (void *)GetProcAddress(msvcrt, "getc");
    p_getchar = (void *)GetProcAddress(msvcrt, "getchar");
    p_getenv = (void *)GetProcAddress(msvcrt, "getenv");
    p_getenv_s = (void *)GetProcAddress(msvcrt, "getenv_s");
    p_gets = (void *)GetProcAddress(msvcrt, "gets");
    p_getwc = (void *)GetProcAddress(msvcrt, "getwc");
    p_getwchar = (void *)GetProcAddress(msvcrt, "getwchar");
    p_isalnum = (void *)GetProcAddress(msvcrt, "isalnum");
    p_isalpha = (void *)GetProcAddress(msvcrt, "isalpha");
    p_isblank = (void *)GetProcAddress(msvcrt, "isblank");
    p_iscntrl = (void *)GetProcAddress(msvcrt, "iscntrl");
    p_isdigit = (void *)GetProcAddress(msvcrt, "isdigit");
    p_isgraph = (void *)GetProcAddress(msvcrt, "isgraph");
    p_isleadbyte = (void *)GetProcAddress(msvcrt, "isleadbyte");
    p_islower = (void *)GetProcAddress(msvcrt, "islower");
    p_isprint = (void *)GetProcAddress(msvcrt, "isprint");
    p_ispunct = (void *)GetProcAddress(msvcrt, "ispunct");
    p_isspace = (void *)GetProcAddress(msvcrt, "isspace");
    p_isupper = (void *)GetProcAddress(msvcrt, "isupper");
    p_iswalpha = (void *)GetProcAddress(msvcrt, "iswalpha");
    p_iswascii = (void *)GetProcAddress(msvcrt, "iswascii");
    p_iswdigit = (void *)GetProcAddress(msvcrt, "iswdigit");
    p_iswpunct = (void *)GetProcAddress(msvcrt, "iswpunct");
    p_iswspace = (void *)GetProcAddress(msvcrt, "iswspace");
    p_isxdigit = (void *)GetProcAddress(msvcrt, "isxdigit");
    p_labs = (void *)GetProcAddress(msvcrt, "labs");
    p_ldexp = (void *)GetProcAddress(msvcrt, "ldexp");
    p_ldiv = (void *)GetProcAddress(msvcrt, "ldiv");
    p_lgamma = (void *)GetProcAddress(msvcrt, "lgamma");
    p_lgammaf = (void *)GetProcAddress(msvcrt, "lgammaf");
    p_lgammal = (void *)GetProcAddress(msvcrt, "lgammal");
    p_llabs = (void *)GetProcAddress(msvcrt, "llabs");
    p_llrint = (void *)GetProcAddress(msvcrt, "llrint");
    p_llrintf = (void *)GetProcAddress(msvcrt, "llrintf");
    p_llrintl = (void *)GetProcAddress(msvcrt, "llrintl");
    p_llround = (void *)GetProcAddress(msvcrt, "llround");
    p_llroundf = (void *)GetProcAddress(msvcrt, "llroundf");
    p_llroundl = (void *)GetProcAddress(msvcrt, "llroundl");
    p_log = (void *)GetProcAddress(msvcrt, "log");
    p_log10 = (void *)GetProcAddress(msvcrt, "log10");
    p_log10f = (void *)GetProcAddress(msvcrt, "log10f");
    p_log1p = (void *)GetProcAddress(msvcrt, "log1p");
    p_log1pf = (void *)GetProcAddress(msvcrt, "log1pf");
    p_log1pl = (void *)GetProcAddress(msvcrt, "log1pl");
    p_log2 = (void *)GetProcAddress(msvcrt, "log2");
    p_log2f = (void *)GetProcAddress(msvcrt, "log2f");
    p_log2l = (void *)GetProcAddress(msvcrt, "log2l");
    p_logf = (void *)GetProcAddress(msvcrt, "logf");
    p_lrint = (void *)GetProcAddress(msvcrt, "lrint");
    p_lrintf = (void *)GetProcAddress(msvcrt, "lrintf");
    p_lrintl = (void *)GetProcAddress(msvcrt, "lrintl");
    p_lround = (void *)GetProcAddress(msvcrt, "lround");
    p_lroundf = (void *)GetProcAddress(msvcrt, "lroundf");
    p_lroundl = (void *)GetProcAddress(msvcrt, "lroundl");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_mblen = (void *)GetProcAddress(msvcrt, "mblen");
    p_mbrlen = (void *)GetProcAddress(msvcrt, "mbrlen");
    p_mbrtowc = (void *)GetProcAddress(msvcrt, "mbrtowc");
    p_mbsrtowcs = (void *)GetProcAddress(msvcrt, "mbsrtowcs");
    p_mbsrtowcs_s = (void *)GetProcAddress(msvcrt, "mbsrtowcs_s");
    p_mbstowcs = (void *)GetProcAddress(msvcrt, "mbstowcs");
    p_mbtowc = (void *)GetProcAddress(msvcrt, "mbtowc");
    p_mbtowc_l = (void *)GetProcAddress(msvcrt, "mbtowc_l");
    p_memcmp = (void *)GetProcAddress(msvcrt, "memcmp");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memmove = (void *)GetProcAddress(msvcrt, "memmove");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_modf = (void *)GetProcAddress(msvcrt, "modf");
    p_modff = (void *)GetProcAddress(msvcrt, "modff");
    p_nan = (void *)GetProcAddress(msvcrt, "nan");
    p_nanf = (void *)GetProcAddress(msvcrt, "nanf");
    p_nearbyint = (void *)GetProcAddress(msvcrt, "nearbyint");
    p_nearbyintf = (void *)GetProcAddress(msvcrt, "nearbyintf");
    p_operator_delete = (void *)GetProcAddress(msvcrt, "??3@YAXPEAX@Z");
    p_operator_new = (void *)GetProcAddress(msvcrt, "??2@YAPEAX_K@Z");
    p_perror = (void *)GetProcAddress(msvcrt, "perror");
    p_pow = (void *)GetProcAddress(msvcrt, "pow");
    p_powf = (void *)GetProcAddress(msvcrt, "powf");
    p_putc = (void *)GetProcAddress(msvcrt, "putc");
    p_putchar = (void *)GetProcAddress(msvcrt, "putchar");
    p_puts = (void *)GetProcAddress(msvcrt, "puts");
    p_puts = (void *)GetProcAddress(msvcrt, "puts");
    p_qsort = (void *)GetProcAddress(msvcrt, "qsort");
    p_rand = (void *)GetProcAddress(msvcrt, "rand");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");
    p_remainder = (void *)GetProcAddress(msvcrt, "remainder");
    p_remainderf = (void *)GetProcAddress(msvcrt, "remainderf");
    p_remainderl = (void *)GetProcAddress(msvcrt, "remainderl");
    p_remove = (void *)GetProcAddress(msvcrt, "remove");
    p_rename = (void *)GetProcAddress(msvcrt, "rename");
    p_rewind = (void *)GetProcAddress(msvcrt, "rewind");
    p_rint = (void *)GetProcAddress(msvcrt, "rint");
    p_rintf = (void *)GetProcAddress(msvcrt, "rintf");
    p_rintl = (void *)GetProcAddress(msvcrt, "rintl");
    p_round = (void *)GetProcAddress(msvcrt, "round");
    p_roundf = (void *)GetProcAddress(msvcrt, "roundf");
    p_roundl = (void *)GetProcAddress(msvcrt, "roundl");
    p_scalbnl = (void *)GetProcAddress(msvcrt, "scalbnl");
    p_setbuf = (void *)GetProcAddress(msvcrt, "setbuf");
    p_setlocale = (void *)GetProcAddress(msvcrt, "setlocale");
    p_setvbuf = (void *)GetProcAddress(msvcrt, "setvbuf");
    p_setvbuf = (void *)GetProcAddress(msvcrt, "setvbuf");
    p_sin = (void *)GetProcAddress(msvcrt, "sin");
    p_sinf = (void *)GetProcAddress(msvcrt, "sinf");
    p_sinh = (void *)GetProcAddress(msvcrt, "sinh");
    p_sinhf = (void *)GetProcAddress(msvcrt, "sinhf");
    p_sqrt = (void *)GetProcAddress(msvcrt, "sqrt");
    p_sqrtf = (void *)GetProcAddress(msvcrt, "sqrtf");
    p_srand = (void *)GetProcAddress(msvcrt, "srand");
    p_stat = (void *)GetProcAddress(msvcrt, "stat");
    p_stati64 = (void *)GetProcAddress(msvcrt, "stati64");
    p_strcat_s = (void *)GetProcAddress(msvcrt, "strcat_s");
    p_strchr = (void *)GetProcAddress(msvcrt, "strchr");
    p_strcmp = (void *)GetProcAddress(msvcrt, "strcmp");
    p_strcpy_s = (void *)GetProcAddress(msvcrt, "strcpy_s");
    p_strerror = (void *)GetProcAddress(msvcrt, "strerror");
    p_strerror_s = (void *)GetProcAddress(msvcrt, "strerror_s");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");
    p_strncmp = (void *)GetProcAddress(msvcrt, "strncmp");
    p_strrchr = (void *)GetProcAddress(msvcrt, "strrchr");
    p_strstr = (void *)GetProcAddress(msvcrt, "strstr");
    p_strtod = (void *)GetProcAddress(msvcrt, "strtod");
    p_swscanf_s = (void *)GetProcAddress(msvcrt, "swscanf_s");
    p_tan = (void *)GetProcAddress(msvcrt, "tan");
    p_tanf = (void *)GetProcAddress(msvcrt, "tanf");
    p_tanh = (void *)GetProcAddress(msvcrt, "tanh");
    p_tanhf = (void *)GetProcAddress(msvcrt, "tanhf");
    p_terminate = (void *)GetProcAddress(msvcrt, "?terminate@@YAXXZ");
    p_tmpfile = (void *)GetProcAddress(msvcrt, "tmpfile");
    p_tmpfile_s = (void *)GetProcAddress(msvcrt, "tmpfile_s");
    p_tmpnam = (void *)GetProcAddress(msvcrt, "tmpnam");
    p_tmpnam_s = (void *)GetProcAddress(msvcrt, "tmpnam_s");
    p_tolower = (void *)GetProcAddress(msvcrt, "tolower");
    p_toupper = (void *)GetProcAddress(msvcrt, "toupper");
    p_trunc = (void *)GetProcAddress(msvcrt, "trunc");
    p_truncf = (void *)GetProcAddress(msvcrt, "truncf");
    p_truncl = (void *)GetProcAddress(msvcrt, "truncl");
    p_type_info_dtor = (void *)GetProcAddress(msvcrt, "??1type_info@@UAA@XZ");
    p_ungetc = (void *)GetProcAddress(msvcrt, "ungetc");
    p_ungetwc = (void *)GetProcAddress(msvcrt, "ungetwc");
    p_vfprintf = (void *)GetProcAddress(msvcrt, "vfprintf");
    p_vfwprintf = (void *)GetProcAddress(msvcrt, "vfwprintf");
    p_vsprintf = (void *)GetProcAddress(msvcrt, "vsprintf");
    p_vsprintf_s = (void *)GetProcAddress(msvcrt, "vsprintf_s");
    p_vswprintf_s = (void *)GetProcAddress(msvcrt, "vswprintf_s");
    p_wcscat_s = (void *)GetProcAddress(msvcrt, "wcscat_s");
    p_wcscpy = (void *)GetProcAddress(msvcrt, "wcscpy");
    p_wcscpy_s = (void *)GetProcAddress(msvcrt, "wcscpy_s");
    p_wcsncmp = (void *)GetProcAddress(msvcrt, "wcsncmp");
    p_wcsstr = (void *)GetProcAddress(msvcrt, "wcsstr");
    p_wcstod = (void *)GetProcAddress(msvcrt, "wcstod");
    p_wcstombs = (void *)GetProcAddress(msvcrt, "wcstombs");
    p_wctomb = (void *)GetProcAddress(msvcrt, "wctomb");

    msvcrt_tls = TlsAlloc();
    if (msvcrt_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    return dll_functions;
}

#endif
