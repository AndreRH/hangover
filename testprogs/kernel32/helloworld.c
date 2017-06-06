/* x86_64-w64-mingw32-gcc helloworld.c -o helloworld.exe -nostdlib -lkernel32 */

#include <windows.h>

void __stdcall WinMainCRTStartup()
{
    char buffer[] = "\e[1;31mHello from the x86 world!\e[0m\n";
    DWORD written;
    unsigned int i, j;

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    for (j = '0'; j < '2'; j++)
    {
        buffer[2] = j;
        for (i = '0'; i < '8'; i++)
        {
            buffer[5] = i;
            WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);
        }
    }
    ExitProcess(123);
}
