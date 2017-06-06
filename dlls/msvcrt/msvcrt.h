#ifndef MSVCRT_H
#define MSVCRT_H

enum msvcrt_calls
{
    CALL___IOB_FUNC = 0,
    CALL_CALLOC,
    CALL_EXIT,
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
void CDECL MSVCRT_free(void *ptr);
void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size);
void * CDECL MSVCRT_realloc(void *ptr, size_t size);

#else

extern const struct qemu_ops *qemu_ops;

void qemu___iob_func(struct qemu_syscall *call);
void qemu_calloc(struct qemu_syscall *call);
void qemu_exit(struct qemu_syscall *call);
void qemu_free(struct qemu_syscall *call);
void qemu_fwrite(struct qemu_syscall *call);
void qemu_malloc(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_realloc(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);

/* Be careful not to call the Linux libc! */
FILE *(* CDECL p___iob_func)();
void *(* CDECL p_calloc)(size_t item_count,size_t size);
void (* CDECL p_exit)(int code);
void (* CDECL p_free)(void *ptr);
size_t (* CDECL p_fwrite)(const void *str, size_t size, size_t count, FILE *file);
void *(* CDECL p_malloc)(size_t size);
void *(* CDECL p_memset)(void *dst, int c, size_t n);
void *(* CDECL p_memcpy)(void *dst, const void *src, size_t size);
void *(* CDECL p_realloc)(void *ptr, size_t size);
size_t (* CDECL p_strlen)(const char *str);

#endif

#endif
