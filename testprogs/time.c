/* x86_64-w64-mingw32-gcc time.c -o time.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void dword_to_char(char *c, DWORD ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer[32] = "timehigh=0x";
    char buffer2[32] = "timelow=0x";
    DWORD written;
    FILETIME time;

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    GetSystemTimeAsFileTime(&time);
    dword_to_char(buffer2 + 10, time.dwHighDateTime);
    buffer2[10+8] = '\n';
    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);
    dword_to_char(buffer + 11, time.dwLowDateTime);
    buffer[11+8] = '\n';
    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);

    ExitProcess(0);
}

static void dword_to_char(char *c, DWORD dw)
{
    int i, j = 0;

    for (i = (sizeof(dw) - 1); i >= 0; --i)
    {
        uint64_t num = (uint64_t)dw, num2, num3;
        num >>= i * 8;

        num2 = num & 0xf0;
        num2 >>= 4;
        if (num2 > 9)
            c[j] = num2 + 'a' - 0xa;
        else
            c[j] = num2 + '0';
        j++;

        num3 = num & 0xf;
        if (num3 > 9)
            c[j] = num3 + 'a' - 0xa;
        else
            c[j] = num3 + '0';
        j++;
    }
}
