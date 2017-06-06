/* x86_64-w64-mingw32-gcc process.c -o process.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void ptr_to_char(char *c, const void *ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer1[64] = "GetCurrentProcess   = 0x";
    char buffer2[64] = "GetCurrentProcessId = 0x";
    char buffer3[64] = "GetCurrentThreadId  = 0x";
    DWORD written;
    HANDLE current;

    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    current = GetCurrentProcess();
    ptr_to_char(buffer1 + 24, (void *)current);
    buffer1[24+16] = '\n';
    WriteFile(stdout, buffer1, sizeof(buffer1), &written, NULL);

    ptr_to_char(buffer2 + 24, (void *)(uint64_t)GetCurrentProcessId());
    buffer2[24+16] = '\n';
    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    ptr_to_char(buffer3 + 24, (void *)(uint64_t)GetCurrentThreadId());
    buffer3[24+16] = '\n';
    WriteFile(stdout, buffer3, sizeof(buffer3), &written, NULL);

    TerminateProcess(current, 123);
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
