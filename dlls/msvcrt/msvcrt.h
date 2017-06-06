#ifndef MSVCRT_H
#define MSVCRT_H

enum msvcrt_calls
{
    CALL_EXIT = 0,
    CALL_FREE,
    CALL_MALLOC,
    CALL_REALLOC,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_exit(struct qemu_syscall *call);
void qemu_free(struct qemu_syscall *call);
void qemu_malloc(struct qemu_syscall *call);
void qemu_realloc(struct qemu_syscall *call);

/* Be careful not to call the Linux libc! */
void (* CDECL p_exit)(int code);
void (* CDECL p_free)(void *ptr);
void *(* CDECL p_malloc)(size_t size);
void *(* CDECL p_realloc)(void *ptr, size_t size);

#endif

#endif
