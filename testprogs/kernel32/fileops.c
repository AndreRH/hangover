/* x86_64-w64-mingw32-gcc fileops.c -o fileops.exe -nostdlib -lkernel32 */

#include <windows.h>

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "Hello contents\n";
    char buffer2[] = "Calling CreateFile to create testfile.txt\n";
    HANDLE file, stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WIN32_FIND_DATAW find_data = {0};
    HANDLE find_handle;
    DWORD high;

    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    HANDLE f = CreateFileW(L"testfile.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(f, buffer, sizeof(buffer), &written, NULL);
    GetFileSize(f, &high);
    CloseHandle(f);

    find_handle = FindFirstFileW(L"*", &find_data);
    FindClose(find_handle);

    ReadFile(NULL, NULL, 0, NULL, NULL);

    ExitProcess(0);
}
