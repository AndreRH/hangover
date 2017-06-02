/* x86_64-w64-mingw32-gcc startupinfo.c -o startupinfo.exe -nostdlib -lkernel32 */

#include <windows.h>

void __stdcall WinMainCRTStartup()
{
    STARTUPINFOA info;
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    /* Not sure if Wine stores sane information in these things. Even writing
     * them in the host Wine code only prints garbage. */
    GetStartupInfoA(&info);
    //WriteFile(stdout, info.lpDesktop, 16, &written, NULL);

    ExitProcess(0);
}
