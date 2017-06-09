/* x86_64-w64-mingw32-gcc fileops.c -o fileops.exe -nostdlib -lkernel32 */

#include <windows.h>

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Hello contents\n";
    char buffer2[] = "Calling CreateFile to create testfile.txt\n";
    HANDLE file, stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    HANDLE f = CreateFileW(L"testfile.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(f, buffer, sizeof(buffer), &written, NULL);
    CloseHandle(f);

    ExitProcess(0);
}
