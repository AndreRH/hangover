#include <stdio.h>
#include <windows.h>

#include "format_msg.h"

#define COUNTOF(x) (sizeof(x)/sizeof(x)[0])

int main()
{
    CPINFOEXW cpinfo;
    SYSTEMTIME  curtime;
    LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    CHAR bufferA[128], inputA[128];
    WCHAR bufferW[128], inputW[128];
    HMODULE k32;

    GetCPInfoExW(CP_UTF8, 0, &cpinfo);
    printf("%ls\n", cpinfo.CodePageName);

    printf("CommandLineA: %s\n", GetCommandLineA());
    printf("CommandLineW: %ls\n", GetCommandLineW());

    curtime.wYear = 2002;
    curtime.wMonth = 10;
    curtime.wDay = 23;
    curtime.wDayOfWeek = 45612; /* Should be 3 - Wednesday */
    curtime.wHour = 65432; /* Invalid */
    curtime.wMinute = 34512; /* Invalid */
    curtime.wSecond = 65535; /* Invalid */
    curtime.wMilliseconds = 12345;
    strcpy(inputA, "dddd d MMMM yyyy");
    GetDateFormatA(lcid, 0, &curtime, inputA, bufferA, COUNTOF(bufferA));
    printf("GetDateFormatA: %s\n", bufferA);

    wcscpy(inputW, L"dddd d MMMM yyyy");
    GetDateFormatW(lcid, 0, &curtime, inputW, bufferW, COUNTOF(bufferW));
    printf("GetDateFormatW: %ls\n", bufferW);

    GetModuleFileNameA(NULL, bufferA, COUNTOF(bufferA));
    printf("GetModuleFileNameA(NULL): %s\n", bufferA);
    GetModuleFileNameW(NULL, bufferW, COUNTOF(bufferW));
    printf("GetModuleFileNameW(NULL): %ls\n", bufferW);

    k32 = GetModuleHandleA("kernel32.dll");
    GetModuleFileNameW(k32, bufferW, COUNTOF(bufferW));
    printf("GetModuleFileNameW(GetModuleHandleA(\"kernel32\")=%p): %ls\n", k32, bufferW);

    return 0;
}
