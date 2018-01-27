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
#include "qemu_msvcrt.h"

struct qemu_init_dll
{
    struct qemu_syscall super;
    uint64_t iob;
    uint64_t FILE_size;
    uint64_t iob_size;
    uint64_t argc, argv;
    double HUGE;
};

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

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_init_dll call;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
#ifndef __x86_64__
            call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
            call.iob = (ULONG_PTR)guest_iob;
            call.FILE_size = sizeof(FILE);
            call.iob_size = GUEST_IOB_SIZE;
            qemu_syscall(&call.super);
            msvcrt_data_init(call.HUGE, call.argc, (char **)(ULONG_PTR)call.argv);
#endif
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

static void qemu_init_dll(struct qemu_syscall *call)
{
    qemu_ptr *argv;
    unsigned int i;

    struct qemu_init_dll *c = (struct qemu_init_dll *)call;
    guest_FILE_size = c->FILE_size;
    guest_iob = c->iob;
    guest_iob_size = c->iob_size;
    c->HUGE = *p__HUGE;
    c->argc = *p___argc;

    argv = HeapAlloc(GetProcessHeap(), 0, sizeof(qemu_ptr) * c->argc);
    for (i = 0; i < c->argc; ++i)
    {
        const char *orig = p___argv[i];
        char *copy = NULL;

        if (orig)
        {
            size_t len = strlen(orig) + 1;
            copy = HeapAlloc(GetProcessHeap(), 0, len);
            memcpy(copy, orig, len);
        }

        argv[i] = QEMU_H2G(copy);
    }

    c->argv = QEMU_H2G(argv);
}

static const syscall_handler dll_functions[] =
{
    qemu____lc_codepage_func,
    qemu____lc_collate_cp_func,
    qemu____lc_handle_func,
    qemu____lc_locale_name_func,
    qemu____mb_cur_max_func,
    qemu____mb_cur_max_l_func,
    qemu____setlc_active_func,
    qemu____unguarded_readlc_active_add_func,
    qemu___acrt_iob_func,
    qemu___clean_type_info_names_internal,
    qemu___control87_2,
    qemu___crt_debugger_hook,
    qemu___crtCompareStringA,
    qemu___crtCompareStringW,
    qemu___crtGetLocaleInfoEx,
    qemu___crtGetLocaleInfoW,
    qemu___crtGetStringTypeW,
    qemu___crtLCMapStringA,
    qemu___crtLCMapStringW,
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
    qemu___p__amblksiz,
    qemu___p__daylight,
    qemu___p__dstbias,
    qemu___p__environ,
    qemu___p__mbctype,
    qemu___p__pctype,
    qemu___p__timezone,
    qemu___p__tzname,
    qemu___p__wenviron,
    qemu___pctype_func,
    qemu___set_app_type,
    qemu___setusermatherr,
    qemu___STRINGTOLD,
    qemu___sys_errlist,
    qemu___sys_nerr,
    qemu___toascii,
    qemu___uncaught_exception,
    qemu___unDName,
    qemu___unDNameEx,
    qemu___wcserror,
    qemu___wcserror_s,
    qemu___wgetmainargs,
    qemu__abs64,
    qemu__access,
    qemu__access_s,
    qemu__aligned_free,
    qemu__aligned_malloc,
    qemu__aligned_msize,
    qemu__aligned_offset_malloc,
    qemu__aligned_offset_realloc,
    qemu__aligned_realloc,
    qemu__amsg_exit,
    qemu__atodbl,
    qemu__atodbl_l,
    qemu__atof_l,
    qemu__atoflt,
    qemu__atoflt_l,
    qemu__atoldbl,
    qemu__atoll_l,
    qemu__beginthread,
    qemu__beginthreadex,
    qemu__cabs,
    qemu__callnewh,
    qemu__calloc_base,
    qemu__cexit,
    qemu__cgets,
    qemu__chdir,
    qemu__chdrive,
    qemu__chgsign,
    qemu__chgsignf,
    qemu__chmod,
    qemu__chsize,
    qemu__chsize_s,
    qemu__clearfp,
    qemu__close,
    qemu__commit,
    qemu__configthreadlocale,
    qemu__configure_narrow_argv,
    qemu__configure_wide_argv,
    qemu__control87,
    qemu__controlfp,
    qemu__controlfp_s,
    qemu__copysign,
    qemu__copysignf,
    qemu__cputs,
    qemu__cputws,
    qemu__creat,
    qemu__create_locale,
    qemu__crtTerminateProcess,
    qemu__ctime32,
    qemu__ctime32_s,
    qemu__ctime64,
    qemu__ctime64_s,
    qemu__CurrentScheduler__Get,
    qemu__CurrentScheduler__GetNumberOfVirtualProcessors,
    qemu__CurrentScheduler__Id,
    qemu__cwait,
    qemu__CxxThrowException,
    qemu__dclass,
    qemu__difftime32,
    qemu__difftime64,
    qemu__dpcomp,
    qemu__dsign,
    qemu__dtest,
    qemu__dup,
    qemu__dup2,
    qemu__dupenv_s,
    qemu__ecvt,
    qemu__ecvt_s,
    qemu__encoded_null,
    qemu__endthread,
    qemu__endthreadex,
    qemu__eof,
    qemu__errno,
    qemu__execv,
    qemu__execve,
    qemu__execvp,
    qemu__execvpe,
    qemu__exit,
    qemu__expand,
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
    qemu__findclose,
    qemu__findfirst,
    qemu__findfirst32,
    qemu__findfirst64,
    qemu__findfirst64i32,
    qemu__findfirsti64,
    qemu__findnext,
    qemu__findnext32,
    qemu__findnext64,
    qemu__findnext64i32,
    qemu__findnexti64,
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
    qemu__free_base,
    qemu__free_locale,
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
    qemu__ftime,
    qemu__ftime32,
    qemu__ftime32_s,
    qemu__ftime64,
    qemu__ftime64_s,
    qemu__ftol,
    qemu__fullpath,
    qemu__futime,
    qemu__futime32,
    qemu__futime64,
    qemu__fwrite_nolock,
    qemu__gcvt,
    qemu__gcvt_s,
    qemu__get_current_locale,
    qemu__get_daylight,
    qemu__get_doserrno,
    qemu__get_dstbias,
    qemu__get_errno,
    qemu__get_fmode,
    qemu__get_heap_handle,
    qemu__get_initial_narrow_environment,
    qemu__get_initial_wide_environment,
    qemu__get_invalid_parameter_handler,
    qemu__get_narrow_winmain_command_line,
    qemu__get_osfhandle,
    qemu__get_osplatform,
    qemu__get_pgmptr,
    qemu__get_printf_count_output,
    qemu__get_sbh_threshold,
    qemu__get_stream_buffer_pointers,
    qemu__get_thread_local_invalid_parameter_handler,
    qemu__get_timezone,
    qemu__get_tzname,
    qemu__get_wide_winmain_command_line,
    qemu__get_wpgmptr,
    qemu__getch,
    qemu__getch_nolock,
    qemu__getche,
    qemu__getche_nolock,
    qemu__GetConcurrency,
    qemu__getcwd,
    qemu__Getdays,
    qemu__getdcwd,
    qemu__getdiskfree,
    qemu__getdllprocaddr,
    qemu__getdrive,
    qemu__getmaxstdio,
    qemu__getmbcp,
    qemu__Getmonths,
    qemu__getpid,
    qemu__getptd,
    qemu__Gettnames,
    qemu__getw,
    qemu__getwch,
    qemu__getwch_nolock,
    qemu__getwche,
    qemu__getwche_nolock,
    qemu__getws,
    qemu__gmtime32,
    qemu__gmtime32_s,
    qemu__gmtime64,
    qemu__gmtime64_s,
    qemu__heapadd,
    qemu__heapchk,
    qemu__heapmin,
    qemu__heapset,
    qemu__heapwalk,
    qemu__hypot,
    qemu__hypotf,
    qemu__i64toa_s,
    qemu__i64tow_s,
    qemu__initialize_narrow_environment,
    qemu__initialize_wide_environment,
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
    qemu__iswalpha_l,
    qemu__iswblank_l,
    qemu__iswctype_l,
    qemu__iswdigit_l,
    qemu__iswpunct_l,
    qemu__iswspace_l,
    qemu__isxdigit_l,
    qemu__itoa,
    qemu__itoa_s,
    qemu__itow_s,
    qemu__j0,
    qemu__j1,
    qemu__jn,
    qemu__kbhit,
    qemu__ldclass,
    qemu__ldtest,
    qemu__loaddll,
    qemu__localtime32,
    qemu__localtime32_s,
    qemu__localtime64,
    qemu__localtime64_s,
    qemu__lock,
    qemu__lock_file,
    qemu__lock_locales,
    qemu__Lock_shared_ptr_spin_lock,
    qemu__locking,
    qemu__logb,
    qemu__logbf,
    qemu__lrotl,
    qemu__lrotr,
    qemu__lseek,
    qemu__lseeki64,
    qemu__ltoa_s,
    qemu__ltow_s,
    qemu__makepath,
    qemu__makepath_s,
    qemu__malloc_base,
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
    qemu__mkdir,
    qemu__mkgmtime,
    qemu__mkgmtime32,
    qemu__mkgmtime64,
    qemu__mktemp,
    qemu__mktemp_s,
    qemu__mktime32,
    qemu__mktime64,
    qemu__msize,
    qemu__nextafter,
    qemu__nextafterf,
    qemu__onexit,
    qemu__open,
    qemu__open_osfhandle,
    qemu__pclose,
    qemu__pipe,
    qemu__popen,
    qemu__purecall,
    qemu__putch,
    qemu__putch_nolock,
    qemu__putenv,
    qemu__putenv_s,
    qemu__putw,
    qemu__putwch,
    qemu__putwch_nolock,
    qemu__putws,
    qemu__query_new_handler,
    qemu__query_new_mode,
    qemu__read,
    qemu__realloc_base,
    qemu__recalloc,
    qemu__rmdir,
    qemu__rmtmp,
    qemu__rotl,
    qemu__rotl64,
    qemu__rotr,
    qemu__rotr64,
    qemu__scalb,
    qemu__scalbf,
    qemu__searchenv,
    qemu__searchenv_s,
    qemu__set_controlfp,
    qemu__set_doserrno,
    qemu__set_errno,
    qemu__set_FMA3_enable,
    qemu__set_fmode,
    qemu__set_invalid_parameter_handler,
    qemu__set_new_handler,
    qemu__set_new_mode,
    qemu__set_printf_count_output,
    qemu__set_sbh_threshold,
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
    qemu__spawnv,
    qemu__spawnve,
    qemu__spawnvp,
    qemu__spawnvpe,
    qemu__splitpath,
    qemu__splitpath_s,
    qemu__stat32,
    qemu__stat32i64,
    qemu__stat64,
    qemu__stat64i32,
    qemu__statusfp,
    qemu__statusfp2,
    qemu__strdate,
    qemu__strdate_s,
    qemu__strdup,
    qemu__strerror,
    qemu__Strftime,
    qemu__strftime_l,
    qemu__stricmp,
    qemu__stricoll,
    qemu__stricoll_l,
    qemu__strlwr,
    qemu__strlwr_l,
    qemu__strlwr_s,
    qemu__strlwr_s_l,
    qemu__strncoll,
    qemu__strncoll_l,
    qemu__strnicmp,
    qemu__strnicoll,
    qemu__strnicoll_l,
    qemu__strnset,
    qemu__strnset_s,
    qemu__strrev,
    qemu__strset,
    qemu__strtime,
    qemu__strtime_s,
    qemu__strtof_l,
    qemu__strtol_l,
    qemu__strtoui64,
    qemu__strupr,
    qemu__strupr_l,
    qemu__strupr_s,
    qemu__strupr_s_l,
    qemu__strxfrm_l,
    qemu__swab,
    qemu__tell,
    qemu__telli64,
    qemu__tempnam,
    qemu__time32,
    qemu__time64,
    qemu__tolower,
    qemu__tolower_l,
    qemu__toupper,
    qemu__toupper_l,
    qemu__towlower_l,
    qemu__towupper_l,
    qemu__tzset,
    qemu__ui64toa_s,
    qemu__ui64tow_s,
    qemu__ultoa_s,
    qemu__ultow_s,
    qemu__umask,
    qemu__ungetc_nolock,
    qemu__ungetch,
    qemu__ungetch_nolock,
    qemu__ungetwc_nolock,
    qemu__ungetwch,
    qemu__ungetwch_nolock,
    qemu__unlink,
    qemu__unloaddll,
    qemu__unlock,
    qemu__unlock_file,
    qemu__unlock_locales,
    qemu__Unlock_shared_ptr_spin_lock,
    qemu__utime,
    qemu__utime32,
    qemu__utime64,
    qemu_sprintf,
    qemu_sprintf,
    qemu__W_Getdays,
    qemu__W_Getmonths,
    qemu__W_Gettnames,
    qemu__waccess,
    qemu__waccess_s,
    qemu__wasctime,
    qemu__wasctime_s,
    qemu__wchdir,
    qemu__wchmod,
    qemu__wcreat,
    qemu__wcreate_locale,
    qemu__wcscoll_l,
    qemu__wcsdup,
    qemu__wcserror,
    qemu__wcserror_s,
    qemu__Wcsftime,
    qemu__wcsftime_l,
    qemu__wcsicmp,
    qemu__wcsicmp_l,
    qemu__wcsicoll,
    qemu__wcsicoll_l,
    qemu__wcslwr,
    qemu__wcslwr_l,
    qemu__wcslwr_s,
    qemu__wcslwr_s_l,
    qemu__wcsncoll,
    qemu__wcsncoll_l,
    qemu__wcsnicmp,
    qemu__wcsnicmp_l,
    qemu__wcsnicoll,
    qemu__wcsnicoll_l,
    qemu__wcsnset,
    qemu__wcsrev,
    qemu__wcsset,
    qemu__wcsset_s,
    qemu__wcstod_l,
    qemu__wcstof_l,
    qemu__wcstoi64,
    qemu__wcstoi64_l,
    qemu__wcstol_l,
    qemu__wcstombs_l,
    qemu__wcstombs_s_l,
    qemu__wcstoui64,
    qemu__wcstoui64_l,
    qemu__wcstoul_l,
    qemu__wcsupr_l,
    qemu__wcsupr_s,
    qemu__wcsupr_s_l,
    qemu__wcsxfrm_l,
    qemu__wctime,
    qemu__wctime32,
    qemu__wctime32_s,
    qemu__wctime64,
    qemu__wctime64_s,
    qemu__wctomb_l,
    qemu__wctomb_s_l,
    qemu__wdupenv_s,
    qemu__wexecv,
    qemu__wexecve,
    qemu__wexecvp,
    qemu__wexecvpe,
    qemu__wfdopen,
    qemu__wfindfirst,
    qemu__wfindfirst32,
    qemu__wfindfirst64,
    qemu__wfindfirst64i32,
    qemu__wfindfirsti64,
    qemu__wfindnext,
    qemu__wfindnext32,
    qemu__wfindnext64,
    qemu__wfindnext64i32,
    qemu__wfindnexti64,
    qemu__wfopen,
    qemu__wfopen_s,
    qemu__wfreopen,
    qemu__wfreopen_s,
    qemu__wfsopen,
    qemu__wfullpath,
    qemu__wgetcwd,
    qemu__wgetdcwd,
    qemu__wgetenv,
    qemu__wgetenv_s,
    qemu__wmakepath,
    qemu__wmakepath_s,
    qemu__wmkdir,
    qemu__wmktemp,
    qemu__wmktemp_s,
    qemu__wperror,
    qemu__wpopen,
    qemu__wputenv,
    qemu__wputenv_s,
    qemu__wremove,
    qemu__wrename,
    qemu__write,
    qemu__wrmdir,
    qemu__wsearchenv,
    qemu__wsearchenv_s,
    qemu__wsetlocale,
    qemu__wsopen_dispatch,
    qemu__wsopen_s,
    qemu__wspawnv,
    qemu__wspawnve,
    qemu__wspawnvp,
    qemu__wspawnvpe,
    qemu__wsplitpath,
    qemu__wsplitpath_s,
    qemu__wstat,
    qemu__wstat32,
    qemu__wstat32i64,
    qemu__wstat64,
    qemu__wstat64i32,
    qemu__wstati64,
    qemu__wstrdate,
    qemu__wstrdate_s,
    qemu__wstrtime,
    qemu__wstrtime_s,
    qemu__wsystem,
    qemu__wtempnam,
    qemu__wtmpnam,
    qemu__wtmpnam_s,
    qemu__wtof,
    qemu__wtof_l,
    qemu__wtoi,
    qemu__wtoi64,
    qemu__wtoi64_l,
    qemu__wtoi_l,
    qemu__wtol,
    qemu__wtol_l,
    qemu__wtoll,
    qemu__wtoll_l,
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
    qemu_asctime,
    qemu_asctime_s,
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
    qemu_atoi,
    qemu_atoll,
    qemu_bsearch,
    qemu_btowc,
    qemu_calloc,
    qemu_cbrt,
    qemu_cbrtf,
    qemu_cbrtl,
    qemu_ceil,
    qemu_ceilf,
    qemu_clearerr,
    qemu_clock,
    qemu_Concurrency_Alloc,
    qemu_Concurrency_Free,
    qemu_Context__SpinYield,
    qemu_Context_Block,
    qemu_Context_CurrentContext,
    qemu_Context_Id,
    qemu_Context_IsCurrentTaskCollectionCanceling,
    qemu_Context_Oversubscribe,
    qemu_Context_ScheduleGroupId,
    qemu_Context_VirtualProcessorId,
    qemu_Context_Yield,
    qemu_cos,
    qemu_cosf,
    qemu_cosh,
    qemu_coshf,
    qemu_ctime,
    qemu_CurrentScheduler_Create,
    qemu_CurrentScheduler_CreateScheduleGroup,
    qemu_CurrentScheduler_Detach,
    qemu_CurrentScheduler_Get,
    qemu_CurrentScheduler_GetNumberOfVirtualProcessors,
    qemu_CurrentScheduler_GetPolicy,
    qemu_CurrentScheduler_Id,
    qemu_CurrentScheduler_IsAvailableLocation,
    qemu_CurrentScheduler_RegisterShutdownEvent,
    qemu_decode_pointer,
    qemu_difftime,
    qemu_div,
    qemu_encode_pointer,
    qemu_erf,
    qemu_erfc,
    qemu_erfcf,
    qemu_erfcl,
    qemu_erff,
    qemu_erfl,
    qemu_event_wait_for_multiple,
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
    qemu_generic_stub,
    qemu_getc,
    qemu_getchar,
    qemu_getenv,
    qemu_getenv_s,
    qemu_gets,
    qemu_getwc,
    qemu_getwchar,
    qemu_gmtime,
    qemu_I10_OUTPUT,
    qemu_init_dll,
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
    qemu_iswalnum,
    qemu_iswalpha,
    qemu_iswascii,
    qemu_iswblank,
    qemu_iswcntrl,
    qemu_iswdigit,
    qemu_iswgraph,
    qemu_iswlower,
    qemu_iswprint,
    qemu_iswpunct,
    qemu_iswspace,
    qemu_iswupper,
    qemu_iswxdigit,
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
    qemu_localeconv,
    qemu_localtime,
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
    qemu_memchr,
    qemu_memcmp,
    qemu_memcpy,
    qemu_memcpy_s,
    qemu_memmove,
    qemu_memmove_s,
    qemu_memset,
    qemu_mktime,
    qemu_modf,
    qemu_modff,
    qemu_nan,
    qemu_nanf,
    qemu_nearbyint,
    qemu_nearbyintf,
    qemu_operator_delete,
    qemu_operator_new,
    qemu_operator_new_dbg,
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
    qemu_Scheduler_Create,
    qemu_Scheduler_ResetDefaultSchedulerPolicy,
    qemu_Scheduler_SetDefaultSchedulerPolicy,
    qemu_set_new_handler,
    qemu_setbuf,
    qemu_setlocale,
    qemu_setvbuf,
    qemu_signal,
    qemu_sin,
    qemu_sinf,
    qemu_sinh,
    qemu_sinhf,
    qemu_wscanf,
    qemu_SpinCount__Value,
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
    qemu_strcoll,
    qemu_strcoll_l,
    qemu_strcpy,
    qemu_strcpy_s,
    qemu_strerror,
    qemu_strerror_s,
    qemu_strftime,
    qemu_strlen,
    qemu_strncat,
    qemu_strncat_s,
    qemu_strncmp,
    qemu_strncpy,
    qemu_strncpy_s,
    qemu_strnlen,
    qemu_strrchr,
    qemu_strstr,
    qemu_strtod,
    qemu_strtod_l,
    qemu_strtof,
    qemu_strtoi64,
    qemu_strtoi64_l,
    qemu_strtok,
    qemu_strtok_s,
    qemu_strtol,
    qemu_strtoui64,
    qemu_strtoui64_l,
    qemu_strtoul,
    qemu_strtoul_l,
    qemu_strxfrm,
    qemu_sprintf,
    qemu_wscanf,
    qemu_system,
    qemu_tan,
    qemu_tanf,
    qemu_tanh,
    qemu_tanhf,
    qemu_terminate,
    qemu_time,
    qemu_tmpfile,
    qemu_tmpfile_s,
    qemu_tmpnam,
    qemu_tmpnam_s,
    qemu_tolower,
    qemu_toupper,
    qemu_towlower,
    qemu_towupper,
    qemu_trunc,
    qemu_truncf,
    qemu_truncl,
    qemu_type_info_dtor,
    qemu_ungetc,
    qemu_ungetwc,
    qemu_scanf,
    qemu_scanf,
    qemu_scanf,
    qemu_wcrtomb,
    qemu_wcscat_s,
    qemu_wcschr,
    qemu_wcscoll,
    qemu_wcscpy,
    qemu_wcscpy_s,
    qemu_wcsftime,
    qemu_wcslen,
    qemu_wcsncat_s,
    qemu_wcsncmp,
    qemu_wcsncpy,
    qemu_wcsncpy_s,
    qemu_wcsnlen,
    qemu_wcspbrk,
    qemu_wcsrtombs,
    qemu_wcsrtombs_s,
    qemu_wcsstr,
    qemu_wcstod,
    qemu_wcstof,
    qemu_wcstok,
    qemu_wcstok_s,
    qemu_wcstombs,
    qemu_wcstombs_s,
    qemu_wcstoul,
    qemu_wcsxfrm,
    qemu_wctob,
    qemu_wctomb,
    qemu_wctomb_s,
    qemu_wmemcpy_s,
    qemu_wmemmove_s,
    qemu_fprintf,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE msvcrt;
    const char *dll_name;

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    if (QEMU_CURRENT_DLL == DLL_MSVCR100)
        dll_name = "msvcr100.dll";
    else if (QEMU_CURRENT_DLL == DLL_MSVCR80)
        dll_name = "msvcr80.dll";
    else
        dll_name = "msvcrt.dll";

    WINE_TRACE("Loading host-side %s wrapper.\n", dll_name);

    msvcrt = LoadLibraryA(dll_name);
    if (!msvcrt)
        WINE_ERR("Cannot find %s.\n", dll_name);

    p____lc_codepage_func = (void *)GetProcAddress(msvcrt, "___lc_codepage_func");
    p____lc_collate_cp_func = (void *)GetProcAddress(msvcrt, "___lc_collate_cp_func");
    p____lc_handle_func = (void *)GetProcAddress(msvcrt, "___lc_handle_func");
    p____lc_locale_name_func = (void *)GetProcAddress(msvcrt, "___lc_locale_name_func");
    p____mb_cur_max_func = (void *)GetProcAddress(msvcrt, "___mb_cur_max_func");
    p____mb_cur_max_l_func = (void *)GetProcAddress(msvcrt, "___mb_cur_max_l_func");
    p____setlc_active_func = (void *)GetProcAddress(msvcrt, "___setlc_active_func");
    p____unguarded_readlc_active_add_func = (void *)GetProcAddress(msvcrt, "___unguarded_readlc_active_add_func");
    p___argc = (int *)GetProcAddress(msvcrt, "__argc");
    p___argv = (char **)GetProcAddress(msvcrt, "__argv");
    p___clean_type_info_names_internal = (void *)GetProcAddress(msvcrt, "__clean_type_info_names_internal");
    p___control87_2 = (void *)GetProcAddress(msvcrt, "__control87_2");
    p___crt_debugger_hook = (void *)GetProcAddress(msvcrt, "__crt_debugger_hook");
    p___crtCompareStringA = (void *)GetProcAddress(msvcrt, "__crtCompareStringA");
    p___crtCompareStringW = (void *)GetProcAddress(msvcrt, "__crtCompareStringW");
    p___crtGetLocaleInfoEx = (void *)GetProcAddress(msvcrt, "__crtGetLocaleInfoEx");
    p___crtGetLocaleInfoW = (void *)GetProcAddress(msvcrt, "__crtGetLocaleInfoW");
    p___crtGetStringTypeW = (void *)GetProcAddress(msvcrt, "__crtGetStringTypeW");
    p___crtLCMapStringA = (void *)GetProcAddress(msvcrt, "__crtLCMapStringA");
    p___crtLCMapStringW = (void *)GetProcAddress(msvcrt, "__crtLCMapStringW");
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
    p___p__amblksiz = (void *)GetProcAddress(msvcrt, "__p__amblksiz");
    p___p__daylight = (void *)GetProcAddress(msvcrt, "__p__daylight");
    p___p__dstbias = (void *)GetProcAddress(msvcrt, "__p__dstbias");
    p___p__environ = (void *)GetProcAddress(msvcrt, "__p__environ");
    p___p__mbctype = (void *)GetProcAddress(msvcrt, "__p__mbctype");
    p___p__pctype = (void *)GetProcAddress(msvcrt, "__p__pctype");
    p___p__timezone = (void *)GetProcAddress(msvcrt, "__p__timezone");
    p___p__tzname = (void *)GetProcAddress(msvcrt, "__p__tzname");
    p___p__wenviron = (void *)GetProcAddress(msvcrt, "__p__wenviron");
    p___pctype_func = (void *)GetProcAddress(msvcrt, "__pctype_func");
    p___set_app_type = (void *)GetProcAddress(msvcrt, "__set_app_type");
    p___setusermatherr = (void *)GetProcAddress(msvcrt, "__setusermatherr");
    p___STRINGTOLD = (void *)GetProcAddress(msvcrt, "__STRINGTOLD");
    p___sys_errlist = (void *)GetProcAddress(msvcrt, "__sys_errlist");
    p___sys_nerr = (void *)GetProcAddress(msvcrt, "__sys_nerr");
    p___toascii = (void *)GetProcAddress(msvcrt, "__toascii");
    p___uncaught_exception = (void *)GetProcAddress(msvcrt, "__uncaught_exception");
    p___unDName = (void *)GetProcAddress(msvcrt, "__unDName");
    p___unDNameEx = (void *)GetProcAddress(msvcrt, "__unDNameEx");
    p___wcserror = (void *)GetProcAddress(msvcrt, "__wcserror");
    p___wcserror_s = (void *)GetProcAddress(msvcrt, "__wcserror_s");
    p___wgetmainargs = (void *)GetProcAddress(msvcrt, "__wgetmainargs");
    p__abs64 = (void *)GetProcAddress(msvcrt, "_abs64");
    p__access = (void *)GetProcAddress(msvcrt, "_access");
    p__access_s = (void *)GetProcAddress(msvcrt, "_access_s");
    p__aligned_free = (void *)GetProcAddress(msvcrt, "_aligned_free");
    p__aligned_malloc = (void *)GetProcAddress(msvcrt, "_aligned_malloc");
    p__aligned_msize = (void *)GetProcAddress(msvcrt, "_aligned_msize");
    p__aligned_offset_malloc = (void *)GetProcAddress(msvcrt, "_aligned_offset_malloc");
    p__aligned_offset_realloc = (void *)GetProcAddress(msvcrt, "_aligned_offset_realloc");
    p__aligned_realloc = (void *)GetProcAddress(msvcrt, "_aligned_realloc");
    p__amsg_exit = (void *)GetProcAddress(msvcrt, "_amsg_exit");
    p__atodbl = (void *)GetProcAddress(msvcrt, "_atodbl");
    p__atodbl_l = (void *)GetProcAddress(msvcrt, "_atodbl_l");
    p__atof_l = (void *)GetProcAddress(msvcrt, "_atof_l");
    p__atoflt = (void *)GetProcAddress(msvcrt, "_atoflt");
    p__atoflt_l = (void *)GetProcAddress(msvcrt, "_atoflt_l");
    p__atoldbl = (void *)GetProcAddress(msvcrt, "_atoldbl");
    p__atoll_l = (void *)GetProcAddress(msvcrt, "_atoll_l");
    p__beginthread = (void *)GetProcAddress(msvcrt, "_beginthread");
    p__beginthreadex = (void *)GetProcAddress(msvcrt, "_beginthreadex");
    p__cabs = (void *)GetProcAddress(msvcrt, "_cabs");
    p__callnewh = (void *)GetProcAddress(msvcrt, "_callnewh");
    p__calloc_base = (void *)GetProcAddress(msvcrt, "_calloc_base");
    p__cexit = (void *)GetProcAddress(msvcrt, "_cexit");
    p__cgets = (void *)GetProcAddress(msvcrt, "_cgets");
    p__chdir = (void *)GetProcAddress(msvcrt, "_chdir");
    p__chdrive = (void *)GetProcAddress(msvcrt, "_chdrive");
    p__chgsign = (void *)GetProcAddress(msvcrt, "_chgsign");
    p__chgsignf = (void *)GetProcAddress(msvcrt, "_chgsignf");
    p__clearfp = (void *)GetProcAddress(msvcrt, "_clearfp");
    p__configthreadlocale = (void *)GetProcAddress(msvcrt, "_configthreadlocale");
    p__configure_narrow_argv = (void *)GetProcAddress(msvcrt, "_configure_narrow_argv");
    p__configure_wide_argv = (void *)GetProcAddress(msvcrt, "_configure_wide_argv");
    p__control87 = (void *)GetProcAddress(msvcrt, "_control87");
    p__controlfp = (void *)GetProcAddress(msvcrt, "_controlfp");
    p__controlfp_s = (void *)GetProcAddress(msvcrt, "_controlfp_s");
    p__copysign = (void *)GetProcAddress(msvcrt, "_copysign");
    p__copysignf = (void *)GetProcAddress(msvcrt, "_copysignf");
    p__cputs = (void *)GetProcAddress(msvcrt, "_cputs");
    p__cputws = (void *)GetProcAddress(msvcrt, "_cputws");
    p__create_locale = (void *)GetProcAddress(msvcrt, "_create_locale");
    p__crtTerminateProcess = (void *)GetProcAddress(msvcrt, "_crtTerminateProcess");
    p__ctime32 = (void *)GetProcAddress(msvcrt, "_ctime32");
    p__ctime32_s = (void *)GetProcAddress(msvcrt, "_ctime32_s");
    p__ctime64 = (void *)GetProcAddress(msvcrt, "_ctime64");
    p__ctime64_s = (void *)GetProcAddress(msvcrt, "_ctime64_s");
    p__CurrentScheduler__Get = (void *)GetProcAddress(msvcrt, "_CurrentScheduler__Get");
    p__CurrentScheduler__GetNumberOfVirtualProcessors = (void *)GetProcAddress(msvcrt, "_CurrentScheduler__GetNumberOfVirtualProcessors");
    p__CurrentScheduler__Id = (void *)GetProcAddress(msvcrt, "_CurrentScheduler__Id");
    p__cwait = (void *)GetProcAddress(msvcrt, "_cwait");
    p__dclass = (void *)GetProcAddress(msvcrt, "_dclass");
    p__difftime32 = (void *)GetProcAddress(msvcrt, "_difftime32");
    p__difftime64 = (void *)GetProcAddress(msvcrt, "_difftime64");
    p__dpcomp = (void *)GetProcAddress(msvcrt, "_dpcomp");
    p__dsign = (void *)GetProcAddress(msvcrt, "_dsign");
    p__dtest = (void *)GetProcAddress(msvcrt, "_dtest");
    p__dup = (void *)GetProcAddress(msvcrt, "_dup");
    p__dup2 = (void *)GetProcAddress(msvcrt, "_dup2");
    p__dupenv_s = (void *)GetProcAddress(msvcrt, "_dupenv_s");
    p__ecvt = (void *)GetProcAddress(msvcrt, "_ecvt");
    p__ecvt_s = (void *)GetProcAddress(msvcrt, "_ecvt_s");
    p__encoded_null = (void *)GetProcAddress(msvcrt, "_encoded_null");
    p__endthread = (void *)GetProcAddress(msvcrt, "_endthread");
    p__endthreadex = (void *)GetProcAddress(msvcrt, "_endthreadex");
    p__eof = (void *)GetProcAddress(msvcrt, "_eof");
    p__errno = (void *)GetProcAddress(msvcrt, "_errno");
    p__execv = (void *)GetProcAddress(msvcrt, "_execv");
    p__execve = (void *)GetProcAddress(msvcrt, "_execve");
    p__execvp = (void *)GetProcAddress(msvcrt, "_execvp");
    p__execvpe = (void *)GetProcAddress(msvcrt, "_execvpe");
    p__exit = (void *)GetProcAddress(msvcrt, "_exit");
    p__expand = (void *)GetProcAddress(msvcrt, "_expand");
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
    p__findclose = (void *)GetProcAddress(msvcrt, "_findclose");
    p__findfirst = (void *)GetProcAddress(msvcrt, "_findfirst");
    p__findfirst32 = (void *)GetProcAddress(msvcrt, "_findfirst32");
    p__findfirst64 = (void *)GetProcAddress(msvcrt, "_findfirst64");
    p__findfirst64i32 = (void *)GetProcAddress(msvcrt, "_findfirst64i32");
    p__findfirsti64 = (void *)GetProcAddress(msvcrt, "_findfirsti64");
    p__findnext = (void *)GetProcAddress(msvcrt, "_findnext");
    p__findnext32 = (void *)GetProcAddress(msvcrt, "_findnext32");
    p__findnext64 = (void *)GetProcAddress(msvcrt, "_findnext64");
    p__findnext64i32 = (void *)GetProcAddress(msvcrt, "_findnext64i32");
    p__findnexti64 = (void *)GetProcAddress(msvcrt, "_findnexti64");
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
    p__free_base = (void *)GetProcAddress(msvcrt, "_free_base");
    p__free_locale = (void *)GetProcAddress(msvcrt, "MSVCRT__free_locale");
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
    p__ftime = (void *)GetProcAddress(msvcrt, "_ftime");
    p__ftime32 = (void *)GetProcAddress(msvcrt, "_ftime32");
    p__ftime32_s = (void *)GetProcAddress(msvcrt, "_ftime32_s");
    p__ftime64 = (void *)GetProcAddress(msvcrt, "_ftime64");
    p__ftime64_s = (void *)GetProcAddress(msvcrt, "_ftime64_s");
    p__ftol = (void *)GetProcAddress(msvcrt, "_ftol");
    p__fullpath = (void *)GetProcAddress(msvcrt, "_fullpath");
    p__fwrite_nolock = (void *)GetProcAddress(msvcrt, "_fwrite_nolock");
    p__gcvt = (void *)GetProcAddress(msvcrt, "_gcvt");
    p__gcvt_s = (void *)GetProcAddress(msvcrt, "_gcvt_s");
    p__get_current_locale = (void *)GetProcAddress(msvcrt, "MSVCRT__get_current_locale");
    p__get_daylight = (void *)GetProcAddress(msvcrt, "_get_daylight");
    p__get_doserrno = (void *)GetProcAddress(msvcrt, "_get_doserrno");
    p__get_dstbias = (void *)GetProcAddress(msvcrt, "_get_dstbias");
    p__get_errno = (void *)GetProcAddress(msvcrt, "_get_errno");
    p__get_fmode = (void *)GetProcAddress(msvcrt, "_get_fmode");
    p__get_heap_handle = (void *)GetProcAddress(msvcrt, "_get_heap_handle");
    p__get_initial_narrow_environment = (void *)GetProcAddress(msvcrt, "_get_initial_narrow_environment");
    p__get_initial_wide_environment = (void *)GetProcAddress(msvcrt, "_get_initial_wide_environment");
    p__get_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_get_invalid_parameter_handler");
    p__get_narrow_winmain_command_line = (void *)GetProcAddress(msvcrt, "_get_narrow_winmain_command_line");
    p__get_osfhandle = (void *)GetProcAddress(msvcrt, "_get_osfhandle");
    p__get_osplatform = (void *)GetProcAddress(msvcrt, "_get_osplatform");
    p__get_pgmptr = (void *)GetProcAddress(msvcrt, "_get_pgmptr");
    p__get_printf_count_output = (void *)GetProcAddress(msvcrt, "_get_printf_count_output");
    p__get_sbh_threshold = (void *)GetProcAddress(msvcrt, "_get_sbh_threshold");
    p__get_stream_buffer_pointers = (void *)GetProcAddress(msvcrt, "_get_stream_buffer_pointers");
    p__get_thread_local_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_get_thread_local_invalid_parameter_handler");
    p__get_timezone = (void *)GetProcAddress(msvcrt, "_get_timezone");
    p__get_tzname = (void *)GetProcAddress(msvcrt, "_get_tzname");
    p__get_wide_winmain_command_line = (void *)GetProcAddress(msvcrt, "_get_wide_winmain_command_line");
    p__get_wpgmptr = (void *)GetProcAddress(msvcrt, "_get_wpgmptr");
    p__getch = (void *)GetProcAddress(msvcrt, "_getch");
    p__getch_nolock = (void *)GetProcAddress(msvcrt, "_getch_nolock");
    p__getche = (void *)GetProcAddress(msvcrt, "_getche");
    p__getche_nolock = (void *)GetProcAddress(msvcrt, "_getche_nolock");
    p__GetConcurrency = (void *)GetProcAddress(msvcrt, "_GetConcurrency");
    p__getcwd = (void *)GetProcAddress(msvcrt, "_getcwd");
    p__Getdays = (void *)GetProcAddress(msvcrt, "_Getdays");
    p__getdcwd = (void *)GetProcAddress(msvcrt, "_getdcwd");
    p__getdiskfree = (void *)GetProcAddress(msvcrt, "_getdiskfree");
    p__getdllprocaddr = (void *)GetProcAddress(msvcrt, "_getdllprocaddr");
    p__getdrive = (void *)GetProcAddress(msvcrt, "_getdrive");
    p__getmaxstdio = (void *)GetProcAddress(msvcrt, "_getmaxstdio");
    p__getmbcp = (void *)GetProcAddress(msvcrt, "_getmbcp");
    p__Getmonths = (void *)GetProcAddress(msvcrt, "_Getmonths");
    p__getpid = (void *)GetProcAddress(msvcrt, "_getpid");
    p__getptd = (void *)GetProcAddress(msvcrt, "_getptd");
    p__Gettnames = (void *)GetProcAddress(msvcrt, "_Gettnames");
    p__getw = (void *)GetProcAddress(msvcrt, "_getw");
    p__getwch = (void *)GetProcAddress(msvcrt, "_getwch");
    p__getwch_nolock = (void *)GetProcAddress(msvcrt, "_getwch_nolock");
    p__getwche = (void *)GetProcAddress(msvcrt, "_getwche");
    p__getwche_nolock = (void *)GetProcAddress(msvcrt, "_getwche_nolock");
    p__getws = (void *)GetProcAddress(msvcrt, "_getws");
    p__gmtime32 = (void *)GetProcAddress(msvcrt, "_gmtime32");
    p__gmtime32_s = (void *)GetProcAddress(msvcrt, "_gmtime32_s");
    p__gmtime64 = (void *)GetProcAddress(msvcrt, "_gmtime64");
    p__gmtime64_s = (void *)GetProcAddress(msvcrt, "_gmtime64_s");
    p__heapadd = (void *)GetProcAddress(msvcrt, "_heapadd");
    p__heapchk = (void *)GetProcAddress(msvcrt, "_heapchk");
    p__heapmin = (void *)GetProcAddress(msvcrt, "_heapmin");
    p__heapset = (void *)GetProcAddress(msvcrt, "_heapset");
    p__heapwalk = (void *)GetProcAddress(msvcrt, "_heapwalk");
    p__HUGE = (double *)GetProcAddress(msvcrt, "_HUGE");
    p__hypot = (void *)GetProcAddress(msvcrt, "_hypot");
    p__hypotf = (void *)GetProcAddress(msvcrt, "_hypotf");
    p__i64toa_s = (void *)GetProcAddress(msvcrt, "_i64toa_s");
    p__i64tow_s = (void *)GetProcAddress(msvcrt, "_i64tow_s");
    p__initialize_narrow_environment = (void *)GetProcAddress(msvcrt, "_initialize_narrow_environment");
    p__initialize_wide_environment = (void *)GetProcAddress(msvcrt, "_initialize_wide_environment");
    p__invalid_parameter_noinfo = (void *)GetProcAddress(msvcrt, "_invalid_parameter_noinfo");
    p__invalid_parameter_noinfo_noreturn = (void *)GetProcAddress(msvcrt, "_invalid_parameter_noinfo_noreturn");
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
    p__iswalpha_l = (void *)GetProcAddress(msvcrt, "_iswalpha_l");
    p__iswblank_l = (void *)GetProcAddress(msvcrt, "_iswblank_l");
    p__iswctype_l = (void *)GetProcAddress(msvcrt, "_iswctype_l");
    p__iswdigit_l = (void *)GetProcAddress(msvcrt, "_iswdigit_l");
    p__iswpunct_l = (void *)GetProcAddress(msvcrt, "_iswpunct_l");
    p__iswspace_l = (void *)GetProcAddress(msvcrt, "_iswspace_l");
    p__isxdigit_l = (void *)GetProcAddress(msvcrt, "_isxdigit_l");
    p__itoa = (void *)GetProcAddress(msvcrt, "_itoa");
    p__itoa_s = (void *)GetProcAddress(msvcrt, "_itoa_s");
    p__itow_s = (void *)GetProcAddress(msvcrt, "_itow_s");
    p__j0 = (void *)GetProcAddress(msvcrt, "_j0");
    p__j1 = (void *)GetProcAddress(msvcrt, "_j1");
    p__jn = (void *)GetProcAddress(msvcrt, "_jn");
    p__kbhit = (void *)GetProcAddress(msvcrt, "_kbhit");
    p__ldclass = (void *)GetProcAddress(msvcrt, "_ldclass");
    p__ldtest = (void *)GetProcAddress(msvcrt, "_ldtest");
    p__loaddll = (void *)GetProcAddress(msvcrt, "_loaddll");
    p__localtime32 = (void *)GetProcAddress(msvcrt, "_localtime32");
    p__localtime32_s = (void *)GetProcAddress(msvcrt, "_localtime32_s");
    p__localtime64 = (void *)GetProcAddress(msvcrt, "_localtime64");
    p__localtime64_s = (void *)GetProcAddress(msvcrt, "_localtime64_s");
    p__lock = (void *)GetProcAddress(msvcrt, "_lock");
    p__lock_file = (void *)GetProcAddress(msvcrt, "_lock_file");
    p__lock_locales = (void *)GetProcAddress(msvcrt, "_lock_locales");
    p__Lock_shared_ptr_spin_lock = (void *)GetProcAddress(msvcrt, "_Lock_shared_ptr_spin_lock");
    p__locking = (void *)GetProcAddress(msvcrt, "_locking");
    p__logb = (void *)GetProcAddress(msvcrt, "_logb");
    p__logbf = (void *)GetProcAddress(msvcrt, "_logbf");
    p__lrotl = (void *)GetProcAddress(msvcrt, "_lrotl");
    p__lrotr = (void *)GetProcAddress(msvcrt, "_lrotr");
    p__lseek = (void *)GetProcAddress(msvcrt, "_lseek");
    p__lseeki64 = (void *)GetProcAddress(msvcrt, "_lseeki64");
    p__ltoa_s = (void *)GetProcAddress(msvcrt, "_ltoa_s");
    p__ltow_s = (void *)GetProcAddress(msvcrt, "_ltow_s");
    p__makepath = (void *)GetProcAddress(msvcrt, "_makepath");
    p__makepath_s = (void *)GetProcAddress(msvcrt, "_makepath_s");
    p__malloc_base = (void *)GetProcAddress(msvcrt, "_malloc_base");
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
    p__mkdir = (void *)GetProcAddress(msvcrt, "_mkdir");
    p__mkgmtime = (void *)GetProcAddress(msvcrt, "_mkgmtime");
    p__mkgmtime32 = (void *)GetProcAddress(msvcrt, "_mkgmtime32");
    p__mkgmtime64 = (void *)GetProcAddress(msvcrt, "_mkgmtime64");
    p__mktemp = (void *)GetProcAddress(msvcrt, "_mktemp");
    p__mktemp_s = (void *)GetProcAddress(msvcrt, "_mktemp_s");
    p__mktime32 = (void *)GetProcAddress(msvcrt, "_mktime32");
    p__mktime64 = (void *)GetProcAddress(msvcrt, "_mktime64");
    p__msize = (void *)GetProcAddress(msvcrt, "_msize");
    p__nextafter = (void *)GetProcAddress(msvcrt, "_nextafter");
    p__nextafterf = (void *)GetProcAddress(msvcrt, "_nextafterf");
    p__onexit = (void *)GetProcAddress(msvcrt, "_onexit");
    p__open = (void *)GetProcAddress(msvcrt, "_open");
    p__open_osfhandle = (void *)GetProcAddress(msvcrt, "_open_osfhandle");
    p__pclose = (void *)GetProcAddress(msvcrt, "_pclose");
    p__pipe = (void *)GetProcAddress(msvcrt, "_pipe");
    p__popen = (void *)GetProcAddress(msvcrt, "_popen");
    p__purecall = (void *)GetProcAddress(msvcrt, "_purecall");
    p__putch = (void *)GetProcAddress(msvcrt, "_putch");
    p__putch_nolock = (void *)GetProcAddress(msvcrt, "_putch_nolock");
    p__putenv = (void *)GetProcAddress(msvcrt, "_putenv");
    p__putenv_s = (void *)GetProcAddress(msvcrt, "_putenv_s");
    p__putw = (void *)GetProcAddress(msvcrt, "_putw");
    p__putwch = (void *)GetProcAddress(msvcrt, "_putwch");
    p__putwch_nolock = (void *)GetProcAddress(msvcrt, "_putwch_nolock");
    p__putws = (void *)GetProcAddress(msvcrt, "_putws");
    p__query_new_handler = (void *)GetProcAddress(msvcrt, "_query_new_handler");
    p__query_new_mode = (void *)GetProcAddress(msvcrt, "_query_new_mode");
    p__read = (void *)GetProcAddress(msvcrt, "_read");
    p__realloc_base = (void *)GetProcAddress(msvcrt, "_realloc_base");
    p__recalloc = (void *)GetProcAddress(msvcrt, "_recalloc");
    p__rmdir = (void *)GetProcAddress(msvcrt, "_rmdir");
    p__rmtmp = (void *)GetProcAddress(msvcrt, "_rmtmp");
    p__rotl = (void *)GetProcAddress(msvcrt, "_rotl");
    p__rotl64 = (void *)GetProcAddress(msvcrt, "_rotl64");
    p__rotr = (void *)GetProcAddress(msvcrt, "_rotr");
    p__rotr64 = (void *)GetProcAddress(msvcrt, "_rotr64");
    p__scalb = (void *)GetProcAddress(msvcrt, "_scalb");
    p__scalbf = (void *)GetProcAddress(msvcrt, "_scalbf");
    p__searchenv = (void *)GetProcAddress(msvcrt, "_searchenv");
    p__searchenv_s = (void *)GetProcAddress(msvcrt, "_searchenv_s");
    p__set_controlfp = (void *)GetProcAddress(msvcrt, "_set_controlfp");
    p__set_doserrno = (void *)GetProcAddress(msvcrt, "_set_doserrno");
    p__set_errno = (void *)GetProcAddress(msvcrt, "_set_errno");
    p__set_FMA3_enable = (void *)GetProcAddress(msvcrt, "_set_FMA3_enable");
    p__set_fmode = (void *)GetProcAddress(msvcrt, "_set_fmode");
    p__set_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_set_invalid_parameter_handler");
    p__set_new_handler = (void *)GetProcAddress(msvcrt, "_set_new_handler");
    p__set_new_mode = (void *)GetProcAddress(msvcrt, "_set_new_mode");
    p__set_printf_count_output = (void *)GetProcAddress(msvcrt, "_set_printf_count_output");
    p__set_sbh_threshold = (void *)GetProcAddress(msvcrt, "_set_sbh_threshold");
    p__set_SSE2_enable = (void *)GetProcAddress(msvcrt, "_set_SSE2_enable");
    p__set_thread_local_invalid_parameter_handler = (void *)GetProcAddress(msvcrt, "_set_thread_local_invalid_parameter_handler");
    p__seterrormode = (void *)GetProcAddress(msvcrt, "_seterrormode");
    p__setmaxstdio = (void *)GetProcAddress(msvcrt, "_setmaxstdio");
    p__setmbcp = (void *)GetProcAddress(msvcrt, "_setmbcp");
    p__setmode = (void *)GetProcAddress(msvcrt, "_setmode");
    p__sopen_dispatch = (void *)GetProcAddress(msvcrt, "_sopen_dispatch");
    p__sopen_s = (void *)GetProcAddress(msvcrt, "_sopen_s");
    p__spawnv = (void *)GetProcAddress(msvcrt, "_spawnv");
    p__spawnve = (void *)GetProcAddress(msvcrt, "_spawnve");
    p__spawnvp = (void *)GetProcAddress(msvcrt, "_spawnvp");
    p__spawnvpe = (void *)GetProcAddress(msvcrt, "_spawnvpe");
    p__splitpath = (void *)GetProcAddress(msvcrt, "_splitpath");
    p__splitpath_s = (void *)GetProcAddress(msvcrt, "_splitpath_s");
    p__stat32 = (void *)GetProcAddress(msvcrt, "_stat32");
    p__stat32i64 = (void *)GetProcAddress(msvcrt, "_stat32i64");
    p__stat64 = (void *)GetProcAddress(msvcrt, "_stat64");
    p__stat64i32 = (void *)GetProcAddress(msvcrt, "_stat64i32");
    p__statusfp = (void *)GetProcAddress(msvcrt, "_statusfp");
    p__statusfp2 = (void *)GetProcAddress(msvcrt, "_statusfp2");
    p__strdate = (void *)GetProcAddress(msvcrt, "_strdate");
    p__strdate_s = (void *)GetProcAddress(msvcrt, "_strdate_s");
    p__strdup = (void *)GetProcAddress(msvcrt, "_strdup");
    p__strerror = (void *)GetProcAddress(msvcrt, "_strerror");
    p__Strftime = (void *)GetProcAddress(msvcrt, "_Strftime");
    p__strftime_l = (void *)GetProcAddress(msvcrt, "_strftime_l");
    p__stricmp = (void *)GetProcAddress(msvcrt, "_stricmp");
    p__stricoll = (void *)GetProcAddress(msvcrt, "_stricoll");
    p__stricoll_l = (void *)GetProcAddress(msvcrt, "_stricoll_l");
    p__strlwr = (void *)GetProcAddress(msvcrt, "_strlwr");
    p__strlwr_l = (void *)GetProcAddress(msvcrt, "_strlwr_l");
    p__strlwr_s = (void *)GetProcAddress(msvcrt, "_strlwr_s");
    p__strlwr_s_l = (void *)GetProcAddress(msvcrt, "_strlwr_s_l");
    p__strncoll = (void *)GetProcAddress(msvcrt, "_strncoll");
    p__strncoll_l = (void *)GetProcAddress(msvcrt, "_strncoll_l");
    p__strnicmp = (void *)GetProcAddress(msvcrt, "_strnicmp");
    p__strnicoll = (void *)GetProcAddress(msvcrt, "_strnicoll");
    p__strnicoll_l = (void *)GetProcAddress(msvcrt, "_strnicoll_l");
    p__strnset = (void *)GetProcAddress(msvcrt, "_strnset");
    p__strnset_s = (void *)GetProcAddress(msvcrt, "_strnset_s");
    p__strrev = (void *)GetProcAddress(msvcrt, "_strrev");
    p__strset = (void *)GetProcAddress(msvcrt, "_strset");
    p__strtime = (void *)GetProcAddress(msvcrt, "_strtime");
    p__strtime_s = (void *)GetProcAddress(msvcrt, "_strtime_s");
    p__strtof_l = (void *)GetProcAddress(msvcrt, "_strtof_l");
    p__strtol_l = (void *)GetProcAddress(msvcrt, "_strtol_l");
    p__strtoui64 = (void *)GetProcAddress(msvcrt, "_strtoui64");
    p__strupr = (void *)GetProcAddress(msvcrt, "_strupr");
    p__strupr_l = (void *)GetProcAddress(msvcrt, "_strupr_l");
    p__strupr_s = (void *)GetProcAddress(msvcrt, "_strupr_s");
    p__strupr_s_l = (void *)GetProcAddress(msvcrt, "_strupr_s_l");
    p__strxfrm_l = (void *)GetProcAddress(msvcrt, "_strxfrm_l");
    p__swab = (void *)GetProcAddress(msvcrt, "_swab");
    p__tell = (void *)GetProcAddress(msvcrt, "_tell");
    p__tempnam = (void *)GetProcAddress(msvcrt, "_tempnam");
    p__time32 = (void *)GetProcAddress(msvcrt, "_time32");
    p__time64 = (void *)GetProcAddress(msvcrt, "_time64");
    p__tolower = (void *)GetProcAddress(msvcrt, "_tolower");
    p__tolower_l = (void *)GetProcAddress(msvcrt, "_tolower_l");
    p__toupper = (void *)GetProcAddress(msvcrt, "_toupper");
    p__toupper_l = (void *)GetProcAddress(msvcrt, "_toupper_l");
    p__towlower_l = (void *)GetProcAddress(msvcrt, "_towlower_l");
    p__towupper_l = (void *)GetProcAddress(msvcrt, "_towupper_l");
    p__tzset = (void *)GetProcAddress(msvcrt, "_tzset");
    p__ui64toa_s = (void *)GetProcAddress(msvcrt, "_ui64toa_s");
    p__ui64tow_s = (void *)GetProcAddress(msvcrt, "_ui64tow_s");
    p__ultoa_s = (void *)GetProcAddress(msvcrt, "_ultoa_s");
    p__ultow_s = (void *)GetProcAddress(msvcrt, "_ultow_s");
    p__umask = (void *)GetProcAddress(msvcrt, "_umask");
    p__ungetc_nolock = (void *)GetProcAddress(msvcrt, "_ungetc_nolock");
    p__ungetch = (void *)GetProcAddress(msvcrt, "_ungetch");
    p__ungetch_nolock = (void *)GetProcAddress(msvcrt, "_ungetch_nolock");
    p__ungetwc_nolock = (void *)GetProcAddress(msvcrt, "_ungetwc_nolock");
    p__ungetwch = (void *)GetProcAddress(msvcrt, "_ungetwch");
    p__ungetwch_nolock = (void *)GetProcAddress(msvcrt, "_ungetwch_nolock");
    p__unlink = (void *)GetProcAddress(msvcrt, "_unlink");
    p__unloaddll = (void *)GetProcAddress(msvcrt, "_unloaddll");
    p__unlock = (void *)GetProcAddress(msvcrt, "_unlock");
    p__unlock_file = (void *)GetProcAddress(msvcrt, "_unlock_file");
    p__unlock_locales = (void *)GetProcAddress(msvcrt, "_unlock_locales");
    p__Unlock_shared_ptr_spin_lock = (void *)GetProcAddress(msvcrt, "_Unlock_shared_ptr_spin_lock");
    p__vsnprintf = (void *)GetProcAddress(msvcrt, "_vsnprintf");
    p__vsnwprintf = (void *)GetProcAddress(msvcrt, "_vsnwprintf");
    p__W_Getdays = (void *)GetProcAddress(msvcrt, "_W_Getdays");
    p__W_Getmonths = (void *)GetProcAddress(msvcrt, "_W_Getmonths");
    p__W_Gettnames = (void *)GetProcAddress(msvcrt, "_W_Gettnames");
    p__waccess = (void *)GetProcAddress(msvcrt, "_waccess");
    p__waccess_s = (void *)GetProcAddress(msvcrt, "_waccess_s");
    p__wasctime = (void *)GetProcAddress(msvcrt, "_wasctime");
    p__wasctime_s = (void *)GetProcAddress(msvcrt, "_wasctime_s");
    p__wchdir = (void *)GetProcAddress(msvcrt, "_wchdir");
    p__wchmod = (void *)GetProcAddress(msvcrt, "_wchmod");
    p__wcreat = (void *)GetProcAddress(msvcrt, "_wcreat");
    p__wcreate_locale = (void *)GetProcAddress(msvcrt, "_wcreate_locale");
    p__wcscoll_l = (void *)GetProcAddress(msvcrt, "_wcscoll_l");
    p__wcsdup = (void *)GetProcAddress(msvcrt, "_wcsdup");
    p__wcserror = (void *)GetProcAddress(msvcrt, "_wcserror");
    p__wcserror_s = (void *)GetProcAddress(msvcrt, "_wcserror_s");
    p__Wcsftime = (void *)GetProcAddress(msvcrt, "_Wcsftime");
    p__wcsftime_l = (void *)GetProcAddress(msvcrt, "_wcsftime_l");
    p__wcsicmp = (void *)GetProcAddress(msvcrt, "_wcsicmp");
    p__wcsicmp_l = (void *)GetProcAddress(msvcrt, "_wcsicmp_l");
    p__wcsicoll = (void *)GetProcAddress(msvcrt, "_wcsicoll");
    p__wcsicoll_l = (void *)GetProcAddress(msvcrt, "_wcsicoll_l");
    p__wcslwr = (void *)GetProcAddress(msvcrt, "_wcslwr");
    p__wcslwr_l = (void *)GetProcAddress(msvcrt, "_wcslwr_l");
    p__wcslwr_s = (void *)GetProcAddress(msvcrt, "_wcslwr_s");
    p__wcslwr_s_l = (void *)GetProcAddress(msvcrt, "_wcslwr_s_l");
    p__wcsncoll = (void *)GetProcAddress(msvcrt, "_wcsncoll");
    p__wcsncoll_l = (void *)GetProcAddress(msvcrt, "_wcsncoll_l");
    p__wcsnicmp = (void *)GetProcAddress(msvcrt, "_wcsnicmp");
    p__wcsnicmp_l = (void *)GetProcAddress(msvcrt, "_wcsnicmp_l");
    p__wcsnicoll = (void *)GetProcAddress(msvcrt, "_wcsnicoll");
    p__wcsnicoll_l = (void *)GetProcAddress(msvcrt, "_wcsnicoll_l");
    p__wcsnset = (void *)GetProcAddress(msvcrt, "_wcsnset");
    p__wcsrev = (void *)GetProcAddress(msvcrt, "_wcsrev");
    p__wcsset = (void *)GetProcAddress(msvcrt, "_wcsset");
    p__wcsset_s = (void *)GetProcAddress(msvcrt, "_wcsset_s");
    p__wcstod_l = (void *)GetProcAddress(msvcrt, "_wcstod_l");
    p__wcstof_l = (void *)GetProcAddress(msvcrt, "_wcstof_l");
    p__wcstoi64 = (void *)GetProcAddress(msvcrt, "_wcstoi64");
    p__wcstoi64_l = (void *)GetProcAddress(msvcrt, "_wcstoi64_l");
    p__wcstol_l = (void *)GetProcAddress(msvcrt, "_wcstol_l");
    p__wcstombs_l = (void *)GetProcAddress(msvcrt, "_wcstombs_l");
    p__wcstombs_s_l = (void *)GetProcAddress(msvcrt, "_wcstombs_s_l");
    p__wcstoui64 = (void *)GetProcAddress(msvcrt, "_wcstoui64");
    p__wcstoui64_l = (void *)GetProcAddress(msvcrt, "_wcstoui64_l");
    p__wcstoul_l = (void *)GetProcAddress(msvcrt, "_wcstoul_l");
    p__wcsupr_l = (void *)GetProcAddress(msvcrt, "_wcsupr_l");
    p__wcsupr_s = (void *)GetProcAddress(msvcrt, "_wcsupr_s");
    p__wcsupr_s_l = (void *)GetProcAddress(msvcrt, "_wcsupr_s_l");
    p__wcsxfrm_l = (void *)GetProcAddress(msvcrt, "_wcsxfrm_l");
    p__wctime = (void *)GetProcAddress(msvcrt, "_wctime");
    p__wctime32 = (void *)GetProcAddress(msvcrt, "_wctime32");
    p__wctime32_s = (void *)GetProcAddress(msvcrt, "_wctime32_s");
    p__wctime64 = (void *)GetProcAddress(msvcrt, "_wctime64");
    p__wctime64_s = (void *)GetProcAddress(msvcrt, "_wctime64_s");
    p__wctomb_l = (void *)GetProcAddress(msvcrt, "_wctomb_l");
    p__wctomb_s_l = (void *)GetProcAddress(msvcrt, "_wctomb_s_l");
    p__wdupenv_s = (void *)GetProcAddress(msvcrt, "_wdupenv_s");
    p__wexecv = (void *)GetProcAddress(msvcrt, "_wexecv");
    p__wexecve = (void *)GetProcAddress(msvcrt, "_wexecve");
    p__wexecvp = (void *)GetProcAddress(msvcrt, "_wexecvp");
    p__wexecvpe = (void *)GetProcAddress(msvcrt, "_wexecvpe");
    p__wfdopen = (void *)GetProcAddress(msvcrt, "_wfdopen");
    p__wfindfirst = (void *)GetProcAddress(msvcrt, "_wfindfirst");
    p__wfindfirst32 = (void *)GetProcAddress(msvcrt, "_wfindfirst32");
    p__wfindfirst64 = (void *)GetProcAddress(msvcrt, "_wfindfirst64");
    p__wfindfirst64i32 = (void *)GetProcAddress(msvcrt, "_wfindfirst64i32");
    p__wfindfirsti64 = (void *)GetProcAddress(msvcrt, "_wfindfirsti64");
    p__wfindnext = (void *)GetProcAddress(msvcrt, "_wfindnext");
    p__wfindnext32 = (void *)GetProcAddress(msvcrt, "_wfindnext32");
    p__wfindnext64 = (void *)GetProcAddress(msvcrt, "_wfindnext64");
    p__wfindnext64i32 = (void *)GetProcAddress(msvcrt, "_wfindnext64i32");
    p__wfindnexti64 = (void *)GetProcAddress(msvcrt, "_wfindnexti64");
    p__wfopen = (void *)GetProcAddress(msvcrt, "_wfopen");
    p__wfopen_s = (void *)GetProcAddress(msvcrt, "_wfopen_s");
    p__wfreopen = (void *)GetProcAddress(msvcrt, "_wfreopen");
    p__wfreopen_s = (void *)GetProcAddress(msvcrt, "_wfreopen_s");
    p__wfsopen = (void *)GetProcAddress(msvcrt, "_wfsopen");
    p__wfullpath = (void *)GetProcAddress(msvcrt, "_wfullpath");
    p__wgetcwd = (void *)GetProcAddress(msvcrt, "_wgetcwd");
    p__wgetdcwd = (void *)GetProcAddress(msvcrt, "_wgetdcwd");
    p__wgetenv = (void *)GetProcAddress(msvcrt, "__wgetenv");
    p__wgetenv_s = (void *)GetProcAddress(msvcrt, "_wgetenv_s");
    p__wmakepath = (void *)GetProcAddress(msvcrt, "_wmakepath");
    p__wmakepath_s = (void *)GetProcAddress(msvcrt, "_wmakepath_s");
    p__wmkdir = (void *)GetProcAddress(msvcrt, "_wmkdir");
    p__wmktemp = (void *)GetProcAddress(msvcrt, "_wmktemp");
    p__wmktemp_s = (void *)GetProcAddress(msvcrt, "_wmktemp_s");
    p__wperror = (void *)GetProcAddress(msvcrt, "_wperror");
    p__wpopen = (void *)GetProcAddress(msvcrt, "_wpopen");
    p__wputenv = (void *)GetProcAddress(msvcrt, "_wputenv");
    p__wputenv_s = (void *)GetProcAddress(msvcrt, "_wputenv_s");
    p__wremove = (void *)GetProcAddress(msvcrt, "_wremove");
    p__wrename = (void *)GetProcAddress(msvcrt, "_wrename");
    p__write = (void *)GetProcAddress(msvcrt, "_write");
    p__wrmdir = (void *)GetProcAddress(msvcrt, "_wrmdir");
    p__wsearchenv = (void *)GetProcAddress(msvcrt, "_wsearchenv");
    p__wsearchenv_s = (void *)GetProcAddress(msvcrt, "_wsearchenv_s");
    p__wsetlocale = (void *)GetProcAddress(msvcrt, "_wsetlocale");
    p__wsopen_dispatch = (void *)GetProcAddress(msvcrt, "_wsopen_dispatch");
    p__wsopen_s = (void *)GetProcAddress(msvcrt, "_wsopen_s");
    p__wspawnv = (void *)GetProcAddress(msvcrt, "_wspawnv");
    p__wspawnve = (void *)GetProcAddress(msvcrt, "_wspawnve");
    p__wspawnvp = (void *)GetProcAddress(msvcrt, "_wspawnvp");
    p__wspawnvpe = (void *)GetProcAddress(msvcrt, "_wspawnvpe");
    p__wsplitpath = (void *)GetProcAddress(msvcrt, "_wsplitpath");
    p__wsplitpath_s = (void *)GetProcAddress(msvcrt, "_wsplitpath_s");
    p__wstat = (void *)GetProcAddress(msvcrt, "_wstat");
    p__wstat32 = (void *)GetProcAddress(msvcrt, "_wstat32");
    p__wstat32i64 = (void *)GetProcAddress(msvcrt, "_wstat32i64");
    p__wstat64 = (void *)GetProcAddress(msvcrt, "_wstat64");
    p__wstat64i32 = (void *)GetProcAddress(msvcrt, "_wstat64i32");
    p__wstati64 = (void *)GetProcAddress(msvcrt, "_wstati64");
    p__wstrdate = (void *)GetProcAddress(msvcrt, "_wstrdate");
    p__wstrdate_s = (void *)GetProcAddress(msvcrt, "_wstrdate_s");
    p__wstrtime = (void *)GetProcAddress(msvcrt, "_wstrtime");
    p__wstrtime_s = (void *)GetProcAddress(msvcrt, "_wstrtime_s");
    p__wsystem = (void *)GetProcAddress(msvcrt, "_wsystem");
    p__wtempnam = (void *)GetProcAddress(msvcrt, "_wtempnam");
    p__wtmpnam = (void *)GetProcAddress(msvcrt, "_wtmpnam");
    p__wtmpnam_s = (void *)GetProcAddress(msvcrt, "_wtmpnam_s");
    p__wtof = (void *)GetProcAddress(msvcrt, "_wtof");
    p__wtof_l = (void *)GetProcAddress(msvcrt, "_wtof_l");
    p__wtoi = (void *)GetProcAddress(msvcrt, "_wtoi");
    p__wtoi64 = (void *)GetProcAddress(msvcrt, "_wtoi64");
    p__wtoi64_l = (void *)GetProcAddress(msvcrt, "_wtoi64_l");
    p__wtoi_l = (void *)GetProcAddress(msvcrt, "_wtoi_l");
    p__wtol = (void *)GetProcAddress(msvcrt, "_wtol");
    p__wtol_l = (void *)GetProcAddress(msvcrt, "_wtol_l");
    p__wtoll = (void *)GetProcAddress(msvcrt, "_wtoll");
    p__wtoll_l = (void *)GetProcAddress(msvcrt, "_wtoll_l");
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
    p_asctime = (void *)GetProcAddress(msvcrt, "asctime");
    p_asctime_s = (void *)GetProcAddress(msvcrt, "asctime_s");
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
    p_atoi = (void *)GetProcAddress(msvcrt, "atoi");
    p_atoll = (void *)GetProcAddress(msvcrt, "atoll");
    p_bsearch = (void *)GetProcAddress(msvcrt, "bsearch");
    p_btowc = (void *)GetProcAddress(msvcrt, "btowc");
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_cbrt = (void *)GetProcAddress(msvcrt, "cbrt");
    p_cbrtf = (void *)GetProcAddress(msvcrt, "cbrtf");
    p_cbrtl = (void *)GetProcAddress(msvcrt, "cbrtl");
    p_ceil = (void *)GetProcAddress(msvcrt, "ceil");
    p_ceilf = (void *)GetProcAddress(msvcrt, "ceilf");
    p_clearerr = (void *)GetProcAddress(msvcrt, "clearerr");
    p_clock = (void *)GetProcAddress(msvcrt, "clock");
    p_Concurrency_Alloc = (void *)GetProcAddress(msvcrt, "Concurrency_Alloc");
    p_Concurrency_Free = (void *)GetProcAddress(msvcrt, "Concurrency_Free");
    p_Context__SpinYield = (void *)GetProcAddress(msvcrt, "Context__SpinYield");
    p_Context_Block = (void *)GetProcAddress(msvcrt, "Context_Block");
    p_Context_CurrentContext = (void *)GetProcAddress(msvcrt, "Context_CurrentContext");
    p_Context_Id = (void *)GetProcAddress(msvcrt, "Context_Id");
    p_Context_IsCurrentTaskCollectionCanceling = (void *)GetProcAddress(msvcrt, "Context_IsCurrentTaskCollectionCanceling");
    p_Context_Oversubscribe = (void *)GetProcAddress(msvcrt, "Context_Oversubscribe");
    p_Context_ScheduleGroupId = (void *)GetProcAddress(msvcrt, "Context_ScheduleGroupId");
    p_Context_VirtualProcessorId = (void *)GetProcAddress(msvcrt, "Context_VirtualProcessorId");
    p_Context_Yield = (void *)GetProcAddress(msvcrt, "Context_Yield");
    p_cos = (void *)GetProcAddress(msvcrt, "cos");
    p_cosf = (void *)GetProcAddress(msvcrt, "cosf");
    p_cosh = (void *)GetProcAddress(msvcrt, "cosh");
    p_coshf = (void *)GetProcAddress(msvcrt, "coshf");
    p_ctime = (void *)GetProcAddress(msvcrt, "ctime");
    p_CurrentScheduler_Create = (void *)GetProcAddress(msvcrt, "CurrentScheduler_Create");
    p_CurrentScheduler_CreateScheduleGroup = (void *)GetProcAddress(msvcrt, "CurrentScheduler_CreateScheduleGroup");
    p_CurrentScheduler_Detach = (void *)GetProcAddress(msvcrt, "CurrentScheduler_Detach");
    p_CurrentScheduler_Get = (void *)GetProcAddress(msvcrt, "CurrentScheduler_Get");
    p_CurrentScheduler_GetNumberOfVirtualProcessors = (void *)GetProcAddress(msvcrt, "CurrentScheduler_GetNumberOfVirtualProcessors");
    p_CurrentScheduler_GetPolicy = (void *)GetProcAddress(msvcrt, "CurrentScheduler_GetPolicy");
    p_CurrentScheduler_Id = (void *)GetProcAddress(msvcrt, "CurrentScheduler_Id");
    p_CurrentScheduler_IsAvailableLocation = (void *)GetProcAddress(msvcrt, "CurrentScheduler_IsAvailableLocation");
    p_CurrentScheduler_RegisterShutdownEvent = (void *)GetProcAddress(msvcrt, "CurrentScheduler_RegisterShutdownEvent");
    p_decode_pointer = (void *)GetProcAddress(msvcrt, "_decode_pointer");
    p_difftime = (void *)GetProcAddress(msvcrt, "difftime");
    p_div = (void *)GetProcAddress(msvcrt, "div");
    p_encode_pointer = (void *)GetProcAddress(msvcrt, "_encode_pointer");
    p_erf = (void *)GetProcAddress(msvcrt, "erf");
    p_erfc = (void *)GetProcAddress(msvcrt, "erfc");
    p_erfcf = (void *)GetProcAddress(msvcrt, "erfcf");
    p_erfcl = (void *)GetProcAddress(msvcrt, "erfcl");
    p_erff = (void *)GetProcAddress(msvcrt, "erff");
    p_erfl = (void *)GetProcAddress(msvcrt, "erfl");
    p_event_wait_for_multiple = (void *)GetProcAddress(msvcrt, "event_wait_for_multiple");
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
    p_fread_s = (void *)GetProcAddress(msvcrt, "fread_s");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_freopen = (void *)GetProcAddress(msvcrt, "freopen");
    p_freopen_s = (void *)GetProcAddress(msvcrt, "freopen_s");
    p_frexp = (void *)GetProcAddress(msvcrt, "frexp");
    p_frexpf = (void *)GetProcAddress(msvcrt, "frexpf");
    p_fscanf = (void *)GetProcAddress(msvcrt, "fscanf");
    p_fseek = (void *)GetProcAddress(msvcrt, "fseek");
    p_fsetpos = (void *)GetProcAddress(msvcrt, "fsetpos");
    p_ftell = (void *)GetProcAddress(msvcrt, "ftell");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_getc = (void *)GetProcAddress(msvcrt, "getc");
    p_getchar = (void *)GetProcAddress(msvcrt, "getchar");
    p_getenv = (void *)GetProcAddress(msvcrt, "getenv");
    p_getenv_s = (void *)GetProcAddress(msvcrt, "getenv_s");
    p_gets = (void *)GetProcAddress(msvcrt, "gets");
    p_getwc = (void *)GetProcAddress(msvcrt, "getwc");
    p_getwchar = (void *)GetProcAddress(msvcrt, "getwchar");
    p_gmtime = (void *)GetProcAddress(msvcrt, "gmtime");
    p_I10_OUTPUT = (void *)GetProcAddress(msvcrt, "I10_OUTPUT");
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
    p_iswalnum = (void *)GetProcAddress(msvcrt, "iswalnum");
    p_iswalpha = (void *)GetProcAddress(msvcrt, "iswalpha");
    p_iswascii = (void *)GetProcAddress(msvcrt, "iswascii");
    p_iswblank = (void *)GetProcAddress(msvcrt, "iswblank");
    p_iswcntrl = (void *)GetProcAddress(msvcrt, "iswcntrl");
    p_iswdigit = (void *)GetProcAddress(msvcrt, "iswdigit");
    p_iswgraph = (void *)GetProcAddress(msvcrt, "iswgraph");
    p_iswlower = (void *)GetProcAddress(msvcrt, "iswlower");
    p_iswprint = (void *)GetProcAddress(msvcrt, "iswprint");
    p_iswpunct = (void *)GetProcAddress(msvcrt, "iswpunct");
    p_iswspace = (void *)GetProcAddress(msvcrt, "iswspace");
    p_iswupper = (void *)GetProcAddress(msvcrt, "iswupper");
    p_iswxdigit = (void *)GetProcAddress(msvcrt, "iswxdigit");
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
    p_localeconv = (void *)GetProcAddress(msvcrt, "MSVCRT_localeconv");
    p_localtime = (void *)GetProcAddress(msvcrt, "localtime");
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
    p_memchr = (void *)GetProcAddress(msvcrt, "memchr");
    p_memcmp = (void *)GetProcAddress(msvcrt, "memcmp");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memcpy_s = (void *)GetProcAddress(msvcrt, "memcpy_s");
    p_memmove = (void *)GetProcAddress(msvcrt, "memmove");
    p_memmove_s = (void *)GetProcAddress(msvcrt, "memmove_s");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_mktime = (void *)GetProcAddress(msvcrt, "mktime");
    p_modf = (void *)GetProcAddress(msvcrt, "modf");
    p_modff = (void *)GetProcAddress(msvcrt, "modff");
    p_nan = (void *)GetProcAddress(msvcrt, "nan");
    p_nanf = (void *)GetProcAddress(msvcrt, "nanf");
    p_nearbyint = (void *)GetProcAddress(msvcrt, "nearbyint");
    p_nearbyintf = (void *)GetProcAddress(msvcrt, "nearbyintf");
    p_operator_delete = (void *)GetProcAddress(msvcrt, "??3@YAXPEAX@Z");
    p_operator_new = (void *)GetProcAddress(msvcrt, "??2@YAPEAX_K@Z");
    p_operator_new_dbg = (void *)GetProcAddress(msvcrt, "operator_new_dbg");
    p_perror = (void *)GetProcAddress(msvcrt, "perror");
    p_pow = (void *)GetProcAddress(msvcrt, "pow");
    p_powf = (void *)GetProcAddress(msvcrt, "powf");
    p_putc = (void *)GetProcAddress(msvcrt, "putc");
    p_putchar = (void *)GetProcAddress(msvcrt, "putchar");
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
    p_Scheduler_Create = (void *)GetProcAddress(msvcrt, "Scheduler_Create");
    p_Scheduler_ResetDefaultSchedulerPolicy = (void *)GetProcAddress(msvcrt, "Scheduler_ResetDefaultSchedulerPolicy");
    p_Scheduler_SetDefaultSchedulerPolicy = (void *)GetProcAddress(msvcrt, "Scheduler_SetDefaultSchedulerPolicy");
    p_set_new_handler = (void *)GetProcAddress(msvcrt, "set_new_handler");
    p_setbuf = (void *)GetProcAddress(msvcrt, "setbuf");
    p_setlocale = (void *)GetProcAddress(msvcrt, "setlocale");
    p_setvbuf = (void *)GetProcAddress(msvcrt, "setvbuf");
    p_sin = (void *)GetProcAddress(msvcrt, "sin");
    p_sinf = (void *)GetProcAddress(msvcrt, "sinf");
    p_sinh = (void *)GetProcAddress(msvcrt, "sinh");
    p_sinhf = (void *)GetProcAddress(msvcrt, "sinhf");
    p_SpinCount__Value = (void *)GetProcAddress(msvcrt, "SpinCount__Value");
    p_sqrt = (void *)GetProcAddress(msvcrt, "sqrt");
    p_sqrtf = (void *)GetProcAddress(msvcrt, "sqrtf");
    p_srand = (void *)GetProcAddress(msvcrt, "srand");
    p_sscanf = (void *)GetProcAddress(msvcrt, "sscanf");
    p_stat = (void *)GetProcAddress(msvcrt, "stat");
    p_stati64 = (void *)GetProcAddress(msvcrt, "_stati64");
    p_strcat_s = (void *)GetProcAddress(msvcrt, "strcat_s");
    p_strchr = (void *)GetProcAddress(msvcrt, "strchr");
    p_strcmp = (void *)GetProcAddress(msvcrt, "strcmp");
    p_strcoll = (void *)GetProcAddress(msvcrt, "strcoll");
    p_strcoll_l = (void *)GetProcAddress(msvcrt, "strcoll_l");
    p_strcpy = (void *)GetProcAddress(msvcrt, "strcpy");
    p_strcpy_s = (void *)GetProcAddress(msvcrt, "strcpy_s");
    p_strerror = (void *)GetProcAddress(msvcrt, "strerror");
    p_strerror_s = (void *)GetProcAddress(msvcrt, "strerror_s");
    p_strftime = (void *)GetProcAddress(msvcrt, "strftime");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");
    p_strncat = (void *)GetProcAddress(msvcrt, "strncat");
    p_strncat_s = (void *)GetProcAddress(msvcrt, "strncat_s");
    p_strncmp = (void *)GetProcAddress(msvcrt, "strncmp");
    p_strncpy = (void *)GetProcAddress(msvcrt, "strncpy");
    p_strncpy_s = (void *)GetProcAddress(msvcrt, "strncpy_s");
    p_strnlen = (void *)GetProcAddress(msvcrt, "strnlen");
    p_strrchr = (void *)GetProcAddress(msvcrt, "strrchr");
    p_strstr = (void *)GetProcAddress(msvcrt, "strstr");
    p_strtod = (void *)GetProcAddress(msvcrt, "strtod");
    p_strtod_l = (void *)GetProcAddress(msvcrt, "strtod_l");
    p_strtof = (void *)GetProcAddress(msvcrt, "strtof");
    p_strtoi64 = (void *)GetProcAddress(msvcrt, "strtoi64");
    p_strtoi64_l = (void *)GetProcAddress(msvcrt, "strtoi64_l");
    p_strtok = (void *)GetProcAddress(msvcrt, "strtok");
    p_strtok_s = (void *)GetProcAddress(msvcrt, "strtok_s");
    p_strtol = (void *)GetProcAddress(msvcrt, "strtol");
    p_strtoui64 = (void *)GetProcAddress(msvcrt, "strtoui64");
    p_strtoui64_l = (void *)GetProcAddress(msvcrt, "strtoui64_l");
    p_strtoul = (void *)GetProcAddress(msvcrt, "strtoul");
    p_strtoul_l = (void *)GetProcAddress(msvcrt, "strtoul_l");
    p_strxfrm = (void *)GetProcAddress(msvcrt, "strxfrm");
    p_swscanf = (void *)GetProcAddress(msvcrt, "swscanf");
    p_swscanf_s = (void *)GetProcAddress(msvcrt, "swscanf_s");
    p_system = (void *)GetProcAddress(msvcrt, "system");
    p_tan = (void *)GetProcAddress(msvcrt, "tan");
    p_tanf = (void *)GetProcAddress(msvcrt, "tanf");
    p_tanh = (void *)GetProcAddress(msvcrt, "tanh");
    p_tanhf = (void *)GetProcAddress(msvcrt, "tanhf");
    p_terminate = (void *)GetProcAddress(msvcrt, "?terminate@@YAXXZ");
    p_time = (void *)GetProcAddress(msvcrt, "time");
    p_tmpfile = (void *)GetProcAddress(msvcrt, "tmpfile");
    p_tmpfile_s = (void *)GetProcAddress(msvcrt, "tmpfile_s");
    p_tmpnam = (void *)GetProcAddress(msvcrt, "tmpnam");
    p_tmpnam_s = (void *)GetProcAddress(msvcrt, "tmpnam_s");
    p_tolower = (void *)GetProcAddress(msvcrt, "tolower");
    p_toupper = (void *)GetProcAddress(msvcrt, "toupper");
    p_towlower = (void *)GetProcAddress(msvcrt, "towlower");
    p_towupper = (void *)GetProcAddress(msvcrt, "towupper");
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
    p_wcrtomb = (void *)GetProcAddress(msvcrt, "wcrtomb");
    p_wcscat_s = (void *)GetProcAddress(msvcrt, "wcscat_s");
    p_wcschr = (void *)GetProcAddress(msvcrt, "wcschr");
    p_wcscoll = (void *)GetProcAddress(msvcrt, "wcscoll");
    p_wcscpy = (void *)GetProcAddress(msvcrt, "wcscpy");
    p_wcscpy_s = (void *)GetProcAddress(msvcrt, "wcscpy_s");
    p_wcsftime = (void *)GetProcAddress(msvcrt, "wcsftime");
    p_wcslen = (void *)GetProcAddress(msvcrt, "wcslen");
    p_wcsncat_s = (void *)GetProcAddress(msvcrt, "wcsncat_s");
    p_wcsncmp = (void *)GetProcAddress(msvcrt, "wcsncmp");
    p_wcsncpy = (void *)GetProcAddress(msvcrt, "wcsncpy");
    p_wcsncpy_s = (void *)GetProcAddress(msvcrt, "wcsncpy_s");
    p_wcsnlen = (void *)GetProcAddress(msvcrt, "wcsnlen");
    p_wcspbrk = (void *)GetProcAddress(msvcrt, "wcspbrk");
    p_wcsrtombs = (void *)GetProcAddress(msvcrt, "wcsrtombs");
    p_wcsrtombs_s = (void *)GetProcAddress(msvcrt, "wcsrtombs_s");
    p_wcsstr = (void *)GetProcAddress(msvcrt, "wcsstr");
    p_wcstod = (void *)GetProcAddress(msvcrt, "wcstod");
    p_wcstof = (void *)GetProcAddress(msvcrt, "wcstof");
    p_wcstok = (void *)GetProcAddress(msvcrt, "wcstok");
    p_wcstok_s = (void *)GetProcAddress(msvcrt, "wcstok_s");
    p_wcstombs = (void *)GetProcAddress(msvcrt, "wcstombs");
    p_wcstombs_s = (void *)GetProcAddress(msvcrt, "wcstombs_s");
    p_wcstoul = (void *)GetProcAddress(msvcrt, "wcstoul");
    p_wcsxfrm = (void *)GetProcAddress(msvcrt, "wcsxfrm");
    p_wctob = (void *)GetProcAddress(msvcrt, "wctob");
    p_wctomb = (void *)GetProcAddress(msvcrt, "wctomb");
    p_wctomb_s = (void *)GetProcAddress(msvcrt, "wctomb_s");
    p_wmemcpy_s = (void *)GetProcAddress(msvcrt, "wmemcpy_s");
    p_wmemmove_s = (void *)GetProcAddress(msvcrt, "wmemmove_s");

    msvcrt_tls = TlsAlloc();
    if (msvcrt_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    return dll_functions;
}

#endif
