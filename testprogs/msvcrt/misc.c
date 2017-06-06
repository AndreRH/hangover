/* x86_64-w64-mingw32-gcc library.c -o library.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static int getstrlen(const char *str);

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Going to call exit(123)\n";
    DWORD written, *ptr;
    char *charp;
    void *(CDECL *p_calloc)(size_t, size_t);
    void (CDECL *p_exit)(int code);
    void (CDECL *p_free)(void *ptr);
    void *(CDECL *p_malloc)(size_t size);
    void *(CDECL *p_memcpy)(void *dst, const void *src, size_t size);
    void *(CDECL *p_memset)(void *ptr, int val, size_t size);
    void *(CDECL *p_realloc)(void *ptr, size_t size);

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE msvcrt = LoadLibraryA("msvcrt.dll");

    p_calloc = (void *)GetProcAddress(msvcrt, "calloc");
    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_memcpy = (void *)GetProcAddress(msvcrt, "memcpy");
    p_memset = (void *)GetProcAddress(msvcrt, "memset");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");

    ptr = p_malloc(sizeof(*ptr));
    ptr[0] = 123;
    ptr = p_realloc(ptr, 2 * sizeof(ptr));
    ptr[1] = 456;
    p_free(ptr);

    charp = p_calloc(10, sizeof(*charp));
    p_memset(charp, 'A', 7);
    charp[7] = '\n';
    charp[9] = 'X';
    WriteFile(stdout, charp, getstrlen(charp), &written, NULL);
    p_memcpy(charp, WinMainCRTStartup, 4);
    p_free(charp);

    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);
    p_exit(123);
}

static int getstrlen(const char *str)
{
    const char *s = str;
    while (*str) str++;
    return str - s;
}
