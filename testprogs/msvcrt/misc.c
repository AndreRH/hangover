/* x86_64-w64-mingw32-gcc library.c -o library.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void ptr_to_char(char *c, const void *ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Going to call exit(123)\n";
    DWORD written, *ptr;
    void (CDECL *p_exit)(int code);
    void (CDECL *p_free)(void *ptr);
    void *(CDECL *p_malloc)(size_t size);
    void *(CDECL *p_realloc)(void *ptr, size_t size);

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE msvcrt = LoadLibraryA("msvcrt.dll");

    p_exit = (void *)GetProcAddress(msvcrt, "exit");
    p_free = (void *)GetProcAddress(msvcrt, "free");
    p_malloc = (void *)GetProcAddress(msvcrt, "malloc");
    p_realloc = (void *)GetProcAddress(msvcrt, "realloc");

    ptr = p_malloc(sizeof(*ptr));
    ptr[0] = 123;
    ptr = p_realloc(ptr, 2 * sizeof(ptr));
    ptr[1] = 456;
    p_free(ptr);

    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);
    p_exit(123);
}
