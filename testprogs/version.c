/* x86_64-w64-mingw32-gcc startupinfo.c -o startupinfo.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void dword_to_char(char *c, DWORD ptr);

void __stdcall WinMainCRTStartup()
{
    char buffer1[32] = "version=0x";
    char buffer2[32] = "major=0x";
    char buffer3[32] = "minor=0x";
    char buffer4[32] = "build=0x";
    OSVERSIONINFOA infoA;
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written, version;

    version = GetVersion();
    dword_to_char(buffer1 + 10, version);
    buffer1[10+8] = '\n';
    WriteFile(stdout, buffer1, sizeof(buffer1), &written, NULL);

    infoA.dwOSVersionInfoSize = sizeof(infoA);
    GetVersionExA(&infoA);
    dword_to_char(buffer2 + 8, infoA.dwMajorVersion);
    buffer2[8+8] = '\n';
    WriteFile(stdout, buffer2, sizeof(buffer2), &written, NULL);

    dword_to_char(buffer3 + 8, infoA.dwMinorVersion);
    buffer3[8+8] = '\n';
    WriteFile(stdout, buffer3, sizeof(buffer3), &written, NULL);

    dword_to_char(buffer4 + 8, infoA.dwBuildNumber);
    buffer4[8+8] = '\n';
    WriteFile(stdout, buffer4, sizeof(buffer4), &written, NULL);

    WriteFile(stdout, infoA.szCSDVersion, sizeof(infoA.szCSDVersion), &written, NULL);
    WriteFile(stdout, "\n", 1, &written, NULL);

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
