/* x86_64-w64-mingw32-gcc library.c -o library.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void ptr_to_char(char *c, const void *ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer[32] = "kernel32=0x";
    char buffer2[32] = "ExitProcess=0x";
    DWORD written;
    void (* WINAPI pExitProcess)(UINT exitcode);

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE k32 = GetModuleHandle("kernel32.dll");

    ptr_to_char(buffer + 11, k32);
    buffer[11+16] = '\n';
    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);

    pExitProcess = (void *)GetProcAddress(k32, "ExitProcess");
    ptr_to_char(buffer2 + 14, pExitProcess);
    buffer2[14+16] = '\n';
    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    pExitProcess(0);
}

static void ptr_to_char(char *c, const void *ptr)
{
    int i, j = 0;

    for (i = (sizeof(ptr) - 1); i >= 0; --i)
    {
        uint64_t num = (uint64_t)ptr, num2, num3;
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
