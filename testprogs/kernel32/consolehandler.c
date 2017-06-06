/* x86_64-w64-mingw32-gcc consolehandler.c -o consolehandler.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static BOOL WINAPI handler(DWORD type);
static BOOL quit = FALSE;

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Press Ctrl+C to stop me.\n";
    char buffer2[] = "Alright, you convinced me to stop.\n";
    DWORD written;

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCtrlHandler(handler, TRUE);

    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);
    while(!quit);
    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    ExitProcess(0);
}

static BOOL WINAPI handler(DWORD type)
{
    DWORD written;
    char buffer[] = "\nConsole handler callback!\n";
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);
    quit = TRUE;
    return TRUE;
}
