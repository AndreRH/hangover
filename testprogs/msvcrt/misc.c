/* x86_64-w64-mingw32-gcc library.c -o library.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void ptr_to_char(char *c, const void *ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Going to call exit(123)\n";
    DWORD written;
    void (CDECL *p_exit)(int code);

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE msvcrt = LoadLibraryA("msvcrt.dll");

    p_exit = (void *)GetProcAddress(msvcrt, "exit");

    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);
    p_exit(123);
}
