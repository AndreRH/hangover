/* x86_64-w64-mingw32-gcc lasterror.c -o lasterror.exe -nostdlib -lkernel32 */

#include <windows.h>

void __stdcall WinMainCRTStartup()
{
    char ok[] = "Last error OK!\n";
    char bad[] = "Last error WRONG!\n";
    DWORD error;

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetLastError(0xcafebabe);
    error = GetLastError();
    if (error == 0xcafebabe)
        WriteFile(stdout, ok, sizeof(ok), &error, NULL);
    else
        WriteFile(stdout, bad, sizeof(bad), &error, NULL);
    GetStdHandle(12345);

    error = GetLastError();
    if (error == ERROR_INVALID_HANDLE)
        WriteFile(stdout, ok, sizeof(ok), &error, NULL);
    else
        WriteFile(stdout, bad, sizeof(bad), &error, NULL);

    ExitProcess(0);
}
