/* x86_64-w64-mingw32-gcc startupinfo.c -o startupinfo.exe -nostdlib -lkernel32 */

#include <windows.h>

static int getstrlen(const char *str);

void __stdcall WinMainCRTStartup()
{
    STARTUPINFOA info;
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    /* Not sure if Wine stores sane information in these things. Even writing
     * them in the host Wine code only prints garbage. */
    GetStartupInfoA(&info);
    WriteFile(stdout, info.lpTitle, getstrlen(info.lpTitle), &written, NULL);
    WriteFile(stdout, "\n", 1, &written, NULL);

    ExitProcess(0);
}

static int getstrlen(const char *str)
{
    const char *s = str;
    while (*str) str++;
    return str - s;
}
