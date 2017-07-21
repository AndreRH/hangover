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
    qemu___control87_2,
    qemu___crt_debugger_hook,
    qemu___cxxframehandler,
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
    qemu___p__pctype,
    qemu___pctype_func,
    qemu___set_app_type,
    qemu___setusermatherr,
    qemu___toascii,
    qemu___wgetmainargs,
    qemu__abs64,
    qemu__amsg_exit,
    qemu__cabs,
    qemu__cexit,
    qemu__chgsign,
    qemu__chgsignf,
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
    qemu__configthreadlocale,
    qemu__control87,
    qemu__controlfp,
    qemu__controlfp_s,
    qemu__copysign,
    qemu__copysignf,
    qemu__dclass,
    qemu__dpcomp,
    qemu__dsign,
    qemu__dtest,
    qemu__ecvt,
    qemu__ecvt_s,
    qemu__exit,
    qemu__fcvt,
    qemu__fcvt_s,
    qemu__fdclass,
    qemu__fdpcomp,
    qemu__fdsign,
    qemu__fdtest,
    qemu__fileno,
    qemu__finite,
    qemu__finitef,
    qemu__fpclass,
    qemu__fpreset,
    qemu__ftol,
    qemu__gcvt,
    qemu__gcvt_s,
    qemu__hypot,
    qemu__hypotf,
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
    qemu__logb,
    qemu__logbf,
    qemu__lrotl,
    qemu__lrotr,
    qemu__matherr,
    qemu__nextafter,
    qemu__nextafterf,
    qemu__onexit,
    qemu__purecall,
    qemu__rotl,
    qemu__rotl64,
    qemu__rotr,
    qemu__rotr64,
    qemu__scalb,
    qemu__scalbf,
    qemu__set_controlfp,
    qemu__set_FMA3_enable,
    qemu__set_SSE2_enable,
    qemu__snwprintf,
    qemu__statusfp,
    qemu__statusfp2,
    qemu__strdup,
    qemu__stricmp,
    qemu__tolower,
    qemu__tolower_l,
    qemu__toupper,
    qemu__toupper_l,
    qemu__unlock,
    qemu_sprintf,
    qemu_sprintf,
    qemu__wcsnicmp,
    qemu__write,
    qemu__wtoi,
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
    qemu_calloc,
    qemu_cbrt,
    qemu_cbrtf,
    qemu_cbrtl,
    qemu_ceil,
    qemu_ceilf,
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
    qemu_fegetenv,
    qemu_fegetround,
    qemu_fesetenv,
    qemu_fesetround,
    qemu_floor,
    qemu_floorf,
    qemu_fmax,
    qemu_fmaxf,
    qemu_fmin,
    qemu_fminf,
    qemu_fmod,
    qemu_fmodf,
    qemu_fprintf,
    qemu_free,
    qemu_frexp,
    qemu_frexpf,
    qemu_fprintf,
    qemu_fwrite,
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
    qemu_lrint,
    qemu_lrintf,
    qemu_lrintl,
    qemu_lround,
    qemu_lroundf,
    qemu_lroundl,
    qemu_malloc,
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
    qemu_pow,
    qemu_powf,
    qemu_fprintf,
    qemu_puts,
    qemu_qsort,
    qemu_raise,
    qemu_realloc,
    qemu_remainder,
    qemu_remainderf,
    qemu_remainderl,
    qemu_rint,
    qemu_rintf,
    qemu_rintl,
    qemu_round,
    qemu_roundf,
    qemu_roundl,
    qemu_scalbnl,
    qemu_setlocale,
    qemu_signal,
    qemu_sin,
    qemu_sinf,
    qemu_sinh,
    qemu_sinhf,
    qemu_sprintf,
    qemu_sqrt,
    qemu_sqrtf,
    qemu_strcat_s,
    qemu_strcpy_s,
    qemu_strlen,
    qemu_strncmp,
    qemu_sprintf,
    qemu_tan,
    qemu_tanf,
    qemu_tanh,
    qemu_tanhf,
    qemu_terminate,
    qemu_tolower,
    qemu_toupper,
    qemu_trunc,
    qemu_truncf,
    qemu_truncl,
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

    p___control87_2 = (void *)GetProcAddress(msvcrt, "__control87_2");
    p___crt_debugger_hook = (void *)GetProcAddress(msvcrt, "__crt_debugger_hook");
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
    p___p__pctype = (void *)GetProcAddress(msvcrt, "__p__pctype");
    p___pctype_func = (void *)GetProcAddress(msvcrt, "__pctype_func");
    p___set_app_type = (void *)GetProcAddress(msvcrt, "__set_app_type");
    p___setusermatherr = (void *)GetProcAddress(msvcrt, "__setusermatherr");
    p___toascii = (void *)GetProcAddress(msvcrt, "__toascii");
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
    p__ecvt = (void *)GetProcAddress(msvcrt, "_ecvt");
    p__ecvt_s = (void *)GetProcAddress(msvcrt, "_ecvt_s");
    p__exit = (void *)GetProcAddress(msvcrt, "_exit");
    p__fcvt = (void *)GetProcAddress(msvcrt, "_fcvt");
    p__fcvt_s = (void *)GetProcAddress(msvcrt, "_fcvt_s");
    p__fdclass = (void *)GetProcAddress(msvcrt, "_fdclass");
    p__fdpcomp = (void *)GetProcAddress(msvcrt, "_fdpcomp");
    p__fdsign = (void *)GetProcAddress(msvcrt, "_fdsign");
    p__fdtest = (void *)GetProcAddress(msvcrt, "_fdtest");
    p__finite = (void *)GetProcAddress(msvcrt, "_finite");
    p__finitef = (void *)GetProcAddress(msvcrt, "_finitef");
    p__fpclass = (void *)GetProcAddress(msvcrt, "_fpclass");
    p__fpreset = (void *)GetProcAddress(msvcrt, "_fpreset");
    p__ftol = (void *)GetProcAddress(msvcrt, "_ftol");
    p__gcvt = (void *)GetProcAddress(msvcrt, "_gcvt");
    p__gcvt_s = (void *)GetProcAddress(msvcrt, "_gcvt_s");
    p__hypot = (void *)GetProcAddress(msvcrt, "_hypot");
    p__hypotf = (void *)GetProcAddress(msvcrt, "_hypotf");
    p__isalnum_l = (void *)GetProcAddress(msvcrt, "_isalnum_l");
    p__isalpha_l = (void *)GetProcAddress(msvcrt, "_isalpha_l");
    p__isatty = (void *)GetProcAddress(msvcrt, "_isatty");
    p__isblank_l = (void *)GetProcAddress(msvcrt, "_isblank_l");
    p__iscntrl_l = (void *)GetProcAddress(msvcrt, "_iscntrl_l");
    p__isctype = (void *)GetProcAddress(msvcrt, "_isctype");
    p__isctype_l = (void *)GetProcAddress(msvcrt, "_isctype_l");
    p__isdigit_l = (void *)GetProcAddress(msvcrt, "_isdigit_l");
    p__isgraph_l = (void *)GetProcAddress(msvcrt, "_isgraph_l");
    p__isleadbyte_l = (void *)GetProcAddress(msvcrt, "_isleadbyte_l");
    p__islower_l = (void *)GetProcAddress(msvcrt, "_islower_l");
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
    p__logb = (void *)GetProcAddress(msvcrt, "_logb");
    p__logbf = (void *)GetProcAddress(msvcrt, "_logbf");
    p__lrotl = (void *)GetProcAddress(msvcrt, "_lrotl");
    p__lrotr = (void *)GetProcAddress(msvcrt, "_lrotr");
    p__matherr = (void *)GetProcAddress(msvcrt, "_matherr");
    p__nextafter = (void *)GetProcAddress(msvcrt, "_nextafter");
    p__nextafterf = (void *)GetProcAddress(msvcrt, "_nextafterf");
    p__onexit = (void *)GetProcAddress(msvcrt, "_onexit");
    p__purecall = (void *)GetProcAddress(msvcrt, "_purecall");
    p__rotl = (void *)GetProcAddress(msvcrt, "_rotl");
    p__rotl64 = (void *)GetProcAddress(msvcrt, "_rotl64");
    p__rotr = (void *)GetProcAddress(msvcrt, "_rotr");
    p__rotr64 = (void *)GetProcAddress(msvcrt, "_rotr64");
    p__scalb = (void *)GetProcAddress(msvcrt, "_scalb");
    p__scalbf = (void *)GetProcAddress(msvcrt, "_scalbf");
    p__set_controlfp = (void *)GetProcAddress(msvcrt, "_set_controlfp");
    p__set_FMA3_enable = (void *)GetProcAddress(msvcrt, "_set_FMA3_enable");
    p__set_SSE2_enable = (void *)GetProcAddress(msvcrt, "_set_SSE2_enable");
    p__statusfp = (void *)GetProcAddress(msvcrt, "_statusfp");
    p__statusfp2 = (void *)GetProcAddress(msvcrt, "_statusfp2");
    p__strdup = (void *)GetProcAddress(msvcrt, "_strdup");
    p__stricmp = (void *)GetProcAddress(msvcrt, "_stricmp");
    p__tolower = (void *)GetProcAddress(msvcrt, "_tolower");
    p__tolower_l = (void *)GetProcAddress(msvcrt, "_tolower_l");
    p__toupper = (void *)GetProcAddress(msvcrt, "_toupper");
    p__toupper_l = (void *)GetProcAddress(msvcrt, "_toupper_l");
    p__unlock = (void *)GetProcAddress(msvcrt, "_unlock");
    p__vsnprintf = (void *)GetProcAddress(msvcrt, "_vsnprintf");
    p__vsnwprintf = (void *)GetProcAddress(msvcrt, "_vsnwprintf");
    p__wcsnicmp = (void *)GetProcAddress(msvcrt, "_wcsnicmp");
    p__write = (void *)GetProcAddress(msvcrt, "_write");
    p__wtoi = (void *)GetProcAddress(msvcrt, "_wtoi");
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
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_cbrt = (void *)GetProcAddress(msvcrt, "cbrt");
    p_cbrtf = (void *)GetProcAddress(msvcrt, "cbrtf");
    p_cbrtl = (void *)GetProcAddress(msvcrt, "cbrtl");
    p_ceil = (void *)GetProcAddress(msvcrt, "ceil");
    p_ceilf = (void *)GetProcAddress(msvcrt, "ceilf");
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
    p_fegetenv = (void *)GetProcAddress(msvcrt, "fegetenv");
    p_fegetround = (void *)GetProcAddress(msvcrt, "fegetround");
    p_fesetenv = (void *)GetProcAddress(msvcrt, "fesetenv");
    p_fesetround = (void *)GetProcAddress(msvcrt, "fesetround");
    p_floor = (void *)GetProcAddress(msvcrt, "floor");
    p_floorf = (void *)GetProcAddress(msvcrt, "floorf");
    p_fmax = (void *)GetProcAddress(msvcrt, "fmax");
    p_fmaxf = (void *)GetProcAddress(msvcrt, "fmaxf");
    p_fmin = (void *)GetProcAddress(msvcrt, "fmin");
    p_fminf = (void *)GetProcAddress(msvcrt, "fminf");
    p_fmod = (void *)GetProcAddress(msvcrt, "fmod");
    p_fmodf = (void *)GetProcAddress(msvcrt, "fmodf");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_frexp = (void *)GetProcAddress(msvcrt, "frexp");
    p_frexpf = (void *)GetProcAddress(msvcrt, "frexpf");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
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
    p_pow = (void *)GetProcAddress(msvcrt, "pow");
    p_powf = (void *)GetProcAddress(msvcrt, "powf");
    p_puts = (void *)GetProcAddress(msvcrt, "puts");
    p_qsort = (void *)GetProcAddress(msvcrt, "qsort");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");
    p_remainder = (void *)GetProcAddress(msvcrt, "remainder");
    p_remainderf = (void *)GetProcAddress(msvcrt, "remainderf");
    p_remainderl = (void *)GetProcAddress(msvcrt, "remainderl");
    p_rint = (void *)GetProcAddress(msvcrt, "rint");
    p_rintf = (void *)GetProcAddress(msvcrt, "rintf");
    p_rintl = (void *)GetProcAddress(msvcrt, "rintl");
    p_round = (void *)GetProcAddress(msvcrt, "round");
    p_roundf = (void *)GetProcAddress(msvcrt, "roundf");
    p_roundl = (void *)GetProcAddress(msvcrt, "roundl");
    p_scalbnl = (void *)GetProcAddress(msvcrt, "scalbnl");
    p_setlocale = (void *)GetProcAddress(msvcrt, "setlocale");
    p_sin = (void *)GetProcAddress(msvcrt, "sin");
    p_sinf = (void *)GetProcAddress(msvcrt, "sinf");
    p_sinh = (void *)GetProcAddress(msvcrt, "sinh");
    p_sinhf = (void *)GetProcAddress(msvcrt, "sinhf");
    p_sqrt = (void *)GetProcAddress(msvcrt, "sqrt");
    p_sqrtf = (void *)GetProcAddress(msvcrt, "sqrtf");
    p_strcat_s = (void *)GetProcAddress(msvcrt, "strcat_s");
    p_strcpy_s = (void *)GetProcAddress(msvcrt, "strcpy_s");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");
    p_strncmp = (void *)GetProcAddress(msvcrt, "strncmp");
    p_tan = (void *)GetProcAddress(msvcrt, "tan");
    p_tanf = (void *)GetProcAddress(msvcrt, "tanf");
    p_tanh = (void *)GetProcAddress(msvcrt, "tanh");
    p_tanhf = (void *)GetProcAddress(msvcrt, "tanhf");
    p_terminate = (void *)GetProcAddress(msvcrt, "?terminate@@YAXXZ");
    p_tolower = (void *)GetProcAddress(msvcrt, "tolower");
    p_toupper = (void *)GetProcAddress(msvcrt, "toupper");
    p_trunc = (void *)GetProcAddress(msvcrt, "trunc");
    p_truncf = (void *)GetProcAddress(msvcrt, "truncf");
    p_truncl = (void *)GetProcAddress(msvcrt, "truncl");
    p_vfprintf = (void *)GetProcAddress(msvcrt, "vfprintf");
    p_vfwprintf = (void *)GetProcAddress(msvcrt, "vfwprintf");
    p_vsprintf = (void *)GetProcAddress(msvcrt, "vsprintf");
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
