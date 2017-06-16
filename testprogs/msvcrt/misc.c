/* x86_64-w64-mingw32-gcc library.c -o library.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <signal.h>

int CDECL matherr_callback(void *exception);

static int (* CDECL p_fprintf)(FILE *file, const char *format, ...);
static int (* CDECL p_fwprintf)(FILE *file, const WCHAR *format, ...);
int (CDECL *p_vfprintf)(FILE *file, const char *format, va_list args);
int (CDECL *p_vfwprintf)(FILE *file, const WCHAR *format, va_list args);
static FILE *iob;

void call_vfprintf(const char *fmt, ...);
void call_vfwprintf(const WCHAR *fmt, ...);

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Going to call exit(123)\n";
    const char *tostdout = "Hello stdout!\n";
    const char *tostderr = "Hello stderr!\n";
    DWORD written, *ptr;
    char *charp;
    int n = 0;
    int argc;
    char **argv, **envp;
    int new_mode;

    FILE *(CDECL *p___iob_func)(void);
    void (CDECL *p___lconv_init)(void);
    void (CDECL *p___set_app_type)(int type);
    void (CDECL *p___setusermatherr)(void *func);
    int (CDECL *p__cexit)(void);
    void (CDECL *p__lock)(int num);
    int (CDECL *p__matherr)(void *exception);
    void (CDECL *p__unlock)(int num);
    void (CDECL *p_abort)(void);
    void *(CDECL *p_calloc)(size_t, size_t);
    void (CDECL *p_exit)(int code);
    void (CDECL *p_free)(void *ptr);
    size_t (* CDECL p_fwrite)(const void *str, size_t size, size_t count, FILE *file);
    void *(CDECL *p_malloc)(size_t size);
    int (* CDECL p_memcmp)(const void *ptr1, const void *ptr2, size_t size);
    void *(CDECL *p_memcpy)(void *dst, const void *src, size_t size);
    void *(CDECL *p_memset)(void *ptr, int val, size_t size);
    int (CDECL *p_puts)(const char *str);
    void *(CDECL *p_realloc)(void *ptr, size_t size);
    __p_sig_fn_t (CDECL *p_signal)(int sig, __p_sig_fn_t func);
    size_t (CDECL *p_strlen)(const char *str);
    void (CDECL *p___getmainargs)(int *argc, char** *argv, char** *envp,
            int expand_wildcards, int *new_mode);
    int (CDECL *p_strncmp)(const char *str1, const char *str2, size_t len);
    int (* CDECL p_wprintf)(const WCHAR *format, ...);

    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE msvcrt = LoadLibraryA("msvcrt.dll");

    p___getmainargs = (void *)GetProcAddress(msvcrt, "__getmainargs");
    p___iob_func = (void *)GetProcAddress(msvcrt, "__iob_func");
    p___lconv_init = (void *)GetProcAddress(msvcrt, "__lconv_init");
    p___set_app_type = (void *)GetProcAddress(msvcrt, "__set_app_type");
    p___setusermatherr = (void *)GetProcAddress(msvcrt, "__setusermatherr");
    p__cexit = (void *)GetProcAddress(msvcrt, "_cexit");
    p__lock = (void *)GetProcAddress(msvcrt, "_lock");
    p__matherr = (void *)GetProcAddress(msvcrt, "_matherr");
    p__unlock = (void *)GetProcAddress(msvcrt, "_unlock");
    p_abort = (void *)GetProcAddress(msvcrt, "abort");
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_fprintf = (void *)GetProcAddress(msvcrt, "fprintf");
    p_fwprintf = (void *)GetProcAddress(msvcrt, "fwprintf");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_memcmp = (void *)GetProcAddress(msvcrt, "memcmp");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_puts = (void *)GetProcAddress(msvcrt, "puts");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");
    p_signal = (void *)GetProcAddress(msvcrt, "signal");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");
    p_strncmp = (void *)GetProcAddress(msvcrt, "strncmp");
    p_vfprintf = (void *)GetProcAddress(msvcrt, "vfprintf");
    p_vfwprintf = (void *)GetProcAddress(msvcrt, "vfwprintf");
    p_wprintf = (void *)GetProcAddress(msvcrt, "wprintf");

    ptr = p_malloc(sizeof(*ptr));
    ptr[0] = 123;
    ptr = p_realloc(ptr, 2 * sizeof(ptr));
    ptr[1] = 456;
    p_free(ptr);

    charp = p_calloc(10, sizeof(*charp));
    p_memset(charp, 'A', 7);
    charp[7] = '\n';
    charp[9] = 'X';
    WriteFile(hstdout, charp, p_strlen(charp), &written, NULL);
    p_memcpy(charp, WinMainCRTStartup, 4);
    p_free(charp);

    iob = p___iob_func();
    p_fwrite(tostdout, p_strlen(tostdout), 1, iob + 1);
    p_fwrite(tostderr, p_strlen(tostderr), 1, iob + 2);

    p_fprintf(iob + 1, "Test \\ int=%05d %% str=\"%s\" %% ptr=%p %% float=%f\n",
            -5, "HelloString", WinMainCRTStartup, 123.5f);

    p_fprintf(iob + 1, "Test \\ hex=%04x %% HEX=%X %% long=%li%n\n",
            0xdead, 0xBEEF, 1073741824, &n);
    p_fprintf(iob + 1, "Test \\ n=%i\n", n);

    p_fprintf(iob + 1, "Test \\ e=%e %% f=%f %% g=%g %% a=%a\n",
            1.23, 2.34, 3.45, 4.56);
    p_fprintf(iob + 1, "Test \\ E=%E %% F=%F %% G=%G %% A=%A\n",
            1.23, 2.34, 3.45, 4.56);

    p_fprintf(iob + 1, "6 ints: %d %d %d %d %d %d\n"
                       "8 floats: %f %f %f %f %f %f %f %f\n"
                       "mix: %x %f %s %f %d\n",
                       1, 2, 3, 4, 5, 6, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8,
                       7, 9.9, "hi", 10.1, 8);
    p_fprintf(iob + 1, "\n");

    p___getmainargs(&argc, &argv, &envp, 0, &new_mode);
    p_fprintf(iob + 1, "%d arguments, argv[0]=%s\n", argc, argv[0]);

    p___lconv_init();
    p___set_app_type(2);

    p___setusermatherr(matherr_callback);
    p_fprintf(iob + 1, "Calling matherr\n");
    n = p__matherr(NULL);
    p_fprintf(iob + 1, "Got %x from matherr\n", n);

    p__lock(0);
    p__unlock(0);

    /*
    p__cexit();
    p_abort();
     */

    p_fprintf(iob + 1, "string compare 9 chars \"%.13s\" and \"%.13s\" = %d\n",
            tostdout, tostderr, p_strncmp(tostdout, tostderr, 9));

    call_vfprintf("Hello vfprintf(i1=%d, f=%f)\n", 1, 123.45);

    p_signal(SIGINT, NULL);

    p_puts("This is from puts()");

    p_fprintf(iob + 1, "memcmp(\"1234\", \"1235\", 4)=%d\n", p_memcmp("1234", "1235", 4));
    p_fprintf(iob + 1, "memcmp(\"1235\", \"1234\", 4)=%d\n", p_memcmp("1235", "1234", 4));

    p_wprintf(L"This is from wprintf: %d\n", 1234);
    p_fwprintf(iob + 1, L"This is from fwprintf: %d\n", 5678);
    call_vfwprintf(L"Hello vfwprintf(i1=%d, f=%f)\n", 1, 123.45);

    WriteFile(hstdout, buffer, sizeof(buffer), &written, NULL);
    p_exit(123);
}

int CDECL matherr_callback(void *exception)
{
    p_fprintf(iob + 1, "math err callback, exception %p\n", exception);
    return 0x1234567;
}

void call_vfprintf(const char *fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    p_vfprintf(iob + 1, fmt, list);
    va_end(list);
}

void call_vfwprintf(const WCHAR *fmt, ...)
{
    va_list list;

    va_start(list, fmt);
    p_vfwprintf(iob + 1, fmt, list);
    va_end(list);
}
