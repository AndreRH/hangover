#ifndef MSVCRT_H
#define MSVCRT_H

enum msvcrt_calls
{
    CALL___GETMAINARGS = 0,
    CALL___IOB_FUNC,
    CALL___LCONV_INIT,
    CALL___SET_APP_TYPE,
    CALL___SETUSERMATHERR,
    CALL__AMSG_EXIT,
    CALL__CEXIT,
    CALL__MATHERR,
    CALL_CALLOC,
    CALL_EXIT,
    CALL_FPRINTF,
    CALL_FREE,
    CALL_FWRITE,
    CALL_MALLOC,
    CALL_MEMCPY,
    CALL_MEMSET,
    CALL_REALLOC,
    CALL_STRLEN,
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_calloc(size_t item_count,size_t size);
CDECL DECLSPEC_NORETURN void __MINGW_NOTHROW MSVCRT_exit(int code);
void CDECL MSVCRT_free(void *ptr);
void * CDECL MSVCRT_malloc(size_t size);
void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size);
void * CDECL MSVCRT_realloc(void *ptr, size_t size);

#else

extern const struct qemu_ops *qemu_ops;

void qemu___getmainargs(struct qemu_syscall *call);
void qemu___iob_func(struct qemu_syscall *call);
void qemu___lconv_init(struct qemu_syscall *call);
void qemu___set_app_type(struct qemu_syscall *call);
void qemu___setusermatherr(struct qemu_syscall *call);
void qemu__amsg_exit(struct qemu_syscall *call);
void qemu__cexit(struct qemu_syscall *call);
void qemu__matherr(struct qemu_syscall *call);
void qemu_calloc(struct qemu_syscall *call);
void qemu_exit(struct qemu_syscall *call);
void qemu_fprintf(struct qemu_syscall *call);
void qemu_free(struct qemu_syscall *call);
void qemu_fwrite(struct qemu_syscall *call);
void qemu_malloc(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_realloc(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);

/* Be careful not to call the Linux libc! */
void (* CDECL p___getmainargs)(int *argc, char** *argv, char** *envp,
        int expand_wildcards, int *new_mode);
FILE *(* CDECL p___iob_func)();
int (* CDECL p___lconv_init)(void);
void (* CDECL p___set_app_type)(int type);
void (* CDECL p___setusermatherr)(void *func);
void (* CDECL p__amsg_exit)(int errnum);
void (* CDECL p__cexit)(void);
int (* CDECL p__matherr)(void *exception);
void *(* CDECL p_calloc)(size_t item_count,size_t size);
void (* CDECL p_exit)(int code);
int (* CDECL p_fprintf)(FILE *file, const char *format, ...);
void (* CDECL p_free)(void *ptr);
size_t (* CDECL p_fwrite)(const void *str, size_t size, size_t count, FILE *file);
void *(* CDECL p_malloc)(size_t size);
void *(* CDECL p_memset)(void *dst, int c, size_t n);
void *(* CDECL p_memcpy)(void *dst, const void *src, size_t size);
void *(* CDECL p_realloc)(void *ptr, size_t size);
size_t (* CDECL p_strlen)(const char *str);

#endif

#endif
