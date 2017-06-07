/* x86_64-w64-mingw32-gcc library.c -o library.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>
#include <stdio.h>

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Going to call exit(123)\n";
    const char *tostdout = "Hello stdout!\n";
    const char *tostderr = "Hello stderr!\n";
    DWORD written, *ptr;
    char *charp;
    FILE *iob;
    int n = 0;

    FILE *(CDECL *p___iob_func)();
    void *(CDECL *p_calloc)(size_t, size_t);
    void (CDECL *p_exit)(int code);
    int (* CDECL p_fprintf)(FILE *file, const char *format, ...);
    void (CDECL *p_free)(void *ptr);
    size_t (* CDECL p_fwrite)(const void *str, size_t size, size_t count, FILE *file);
    void *(CDECL *p_malloc)(size_t size);
    void *(CDECL *p_memcpy)(void *dst, const void *src, size_t size);
    void *(CDECL *p_memset)(void *ptr, int val, size_t size);
    void *(CDECL *p_realloc)(void *ptr, size_t size);
    size_t (CDECL *p_strlen)(const char *str);

    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE msvcrt = LoadLibraryA("msvcrt.dll");

    p___iob_func = (void *)GetProcAddress(msvcrt, "__iob_func");
    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_fprintf = (void *)GetProcAddress(msvcrt, "fprintf");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_fwrite = (void *)GetProcAddress(msvcrt, "fwrite");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");
    p_strlen = (void *)GetProcAddress(msvcrt, "strlen");

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

    WriteFile(hstdout, buffer, sizeof(buffer), &written, NULL);

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

    p_exit(123);
}
