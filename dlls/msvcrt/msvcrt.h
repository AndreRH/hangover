#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>

enum msvcrt_calls
{
    CALL___GETMAINARGS = 0,
    CALL___CRT_DEBUGGER_HOOK,
    CALL___CXXFRAMEHANDLER,
    CALL___IOB_FUNC,
    CALL___LCONV_INIT,
    CALL___SET_APP_TYPE,
    CALL___SETUSERMATHERR,
    CALL___WGETMAINARGS,
    CALL__AMSG_EXIT,
    CALL__CEXIT,
    CALL__CONFIGTHREADLOCALE,
    CALL__EXIT,
    CALL__LOCK,
    CALL__MATHERR,
    CALL__ONEXIT,
    CALL__SNWPRINTF,
    CALL__STRDUP,
    CALL__STRICMP,
    CALL__UNLOCK,
    CALL__WCSNICMP,
    CALL__WTOI,
    CALL__XCPTFILTER,
    CALL_ABORT,
    CALL_CALLOC,
    CALL_COSF,
    CALL_EXIT,
    CALL_FPRINTF,
    CALL_FWPRINTF,
    CALL_FREE,
    CALL_FWRITE,
    CALL_MALLOC,
    CALL_MEMCMP,
    CALL_MEMCPY,
    CALL_MEMSET,
    CALL_OPERATOR_DELETE,
    CALL_OPERATOR_NEW,
    CALL_PRINTF,
    CALL_PUTS,
    CALL_QSORT,
    CALL_RAISE,
    CALL_REALLOC,
    CALL_SIGNAL,
    CALL_SINF,
    CALL_SPRINTF,
    CALL_SQRTF,
    CALL_STRLEN,
    CALL_STRNCMP,
    CALL_SWPRINTF_S,
    CALL_TERMINATE,
    CALL_WCSCAT_S,
    CALL_WCSCPY,
    CALL_WCSCPY_S,
    CALL_WCSNCMP,
    CALL_WCSSTR,
    CALL_WCSTOD,
    CALL_WPRINTF,
};

typedef int (__cdecl *MSVCRT__onexit_t)(void);

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

#else

extern const struct qemu_ops *qemu_ops;

void qemu___getmainargs(struct qemu_syscall *call);
void qemu___crt_debugger_hook(struct qemu_syscall *call);
void qemu___cxxframehandler(struct qemu_syscall *call);
void qemu___iob_func(struct qemu_syscall *call);
void qemu___lconv_init(struct qemu_syscall *call);
void qemu___set_app_type(struct qemu_syscall *call);
void qemu___setusermatherr(struct qemu_syscall *call);
void qemu___wgetmainargs(struct qemu_syscall *call);
void qemu__amsg_exit(struct qemu_syscall *call);
void qemu__cexit(struct qemu_syscall *call);
void qemu__configthreadlocale(struct qemu_syscall *call);
void qemu__exit(struct qemu_syscall *call);
void qemu__lock(struct qemu_syscall *call);
void qemu__matherr(struct qemu_syscall *call);
void qemu__onexit(struct qemu_syscall *call);
void qemu__snwprintf(struct qemu_syscall *call);
void qemu__strdup(struct qemu_syscall *call);
void qemu__stricmp(struct qemu_syscall *call);
void qemu__unlock(struct qemu_syscall *call);
void qemu__wcsnicmp(struct qemu_syscall *call);
void qemu__wtoi(struct qemu_syscall *call);
void qemu__xcptfilter(struct qemu_syscall *c);
void qemu_abort(struct qemu_syscall *call);
void qemu_calloc(struct qemu_syscall *call);
void qemu_cosf(struct qemu_syscall *call);
void qemu_exit(struct qemu_syscall *call);
void qemu_fprintf(struct qemu_syscall *call);
void qemu_free(struct qemu_syscall *call);
void qemu_fwrite(struct qemu_syscall *call);
void qemu_malloc(struct qemu_syscall *call);
void qemu_memcmp(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_operator_delete(struct qemu_syscall *call);
void qemu_operator_new(struct qemu_syscall *call);
void qemu_puts(struct qemu_syscall *call);
void qemu_qsort(struct qemu_syscall *call);
void qemu_raise(struct qemu_syscall *call);
void qemu_realloc(struct qemu_syscall *call);
void qemu_signal(struct qemu_syscall *call);
void qemu_sinf(struct qemu_syscall *call);
void qemu_sprintf(struct qemu_syscall *call);
void qemu_sqrtf(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);
void qemu_strncmp(struct qemu_syscall *call);
void qemu_terminate(struct qemu_syscall *c);
void qemu_wcscat_s(struct qemu_syscall *call);
void qemu_wcscpy(struct qemu_syscall *call);
void qemu_wcscpy_s(struct qemu_syscall *call);
void qemu_wcsncmp(struct qemu_syscall *call);
void qemu_wcsstr(struct qemu_syscall *call);
void qemu_wcstod(struct qemu_syscall *call);

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
void (* CDECL p__exit)(int code);
void (* CDECL p__lock)(int locknum);
int (* CDECL p__matherr)(void *exception);
MSVCRT__onexit_t (* CDECL p__onexit)(MSVCRT__onexit_t func);
char * (* CDECL p__strdup)(const char* str);
int (* CDECL p__stricmp)(const char *s1, const char *s2);
void (* CDECL p__unlock)(int locknum);
int (* CDECL p__wcsnicmp)(const WCHAR *str1, const WCHAR *str2, int count);
int (* CDECL p__wtoi)(const WCHAR *str1);
void (* CDECL p_abort)(void);
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
int (* CDECL p_puts)(const char *str);
void (* CDECL p_qsort)(void *base, size_t nmemb, size_t size,
        int (CDECL *compar)(const void*, const void*));
void *(* CDECL p_realloc)(void *ptr, size_t size);
float (* CDECL p_sinf)(float x);
float (* CDECL p_sqrtf)(float x);
size_t (* CDECL p_strlen)(const char *str);
int (* CDECL p_strncmp)(const char *str1, const char *str2, size_t len);
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

DWORD msvcrt_tls;

#endif

#endif
