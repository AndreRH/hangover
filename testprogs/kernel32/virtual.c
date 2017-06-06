/* x86_64-w64-mingw32-gcc virtual.c -o virtual.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void ptr_to_char(char *c, const void *ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer[32] = "addr=0x";
    char buffer2[32] = "prot=0x";
    char buffer3[32] = "oldp=0x";
    DWORD written;
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    MEMORY_BASIC_INFORMATION info;
    DWORD old_protect;
    
    VirtualQuery(WinMainCRTStartup, &info, sizeof(info));

    ptr_to_char(buffer + 7, info.BaseAddress);
    buffer[7+16] = '\n';
    WriteFile(stdout, buffer, sizeof(buffer), &written, NULL);

    ptr_to_char(buffer2 + 7, (void *)(int64_t)info.Protect);
    buffer2[7+16] = '\n';
    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    VirtualProtect(WinMainCRTStartup, 4096, PAGE_EXECUTE_READWRITE, &old_protect);
    ptr_to_char(buffer3 + 7, (void *)(int64_t)old_protect);
    buffer3[7+16] = '\n';
    WriteFile(stdout, buffer3, sizeof(buffer3), &written, NULL);

    /* See if we can overwrite code now. */
    *(DWORD *)WinMainCRTStartup = 0;

    VirtualProtect(WinMainCRTStartup, 4096, old_protect, &old_protect);
    ptr_to_char(buffer3 + 7, (void *)(int64_t)old_protect);
    buffer3[7+16] = '\n';
    WriteFile(stdout, buffer3, sizeof(buffer3), &written, NULL);
    
    /* This would crash again. */
    /* *(DWORD *)WinMainCRTStartup = 1; */

    ExitProcess(0);
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
