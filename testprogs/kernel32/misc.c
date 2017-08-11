#include <stdio.h>
#include <windows.h>
#include <excpt.h>

#include "format_msg.h"

#define COUNTOF(x) (sizeof(x)/sizeof(x)[0])

/* Not quite right, HMODULE != LDR_MODULE */
static NTSTATUS (* WINAPI pLdrFindEntryForAddress)(void *addr, HMODULE *mod);

static long CALLBACK test_handler(EXCEPTION_POINTERS *pointers)
{
    printf("test_handler executed\n");
    switch (pointers->ExceptionRecord->ExceptionCode)
    {
        case EXCEPTION_STACK_OVERFLOW:
            return EXCEPTION_EXECUTE_HANDLER;
        default:
            return EXCEPTION_CONTINUE_SEARCH;
    }
}

int main()
{
    CPINFOEXW cpinfo;
    SYSTEMTIME  curtime;
    LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    CHAR bufferA[128], inputA[128];
    WCHAR bufferW[128], inputW[128];
    HMODULE k32, test_mod, ntdll;
    char *heaptest;
    void *handler;

    ntdll = GetModuleHandleA("ntdll");
    pLdrFindEntryForAddress = (void *)GetProcAddress(ntdll, "LdrFindEntryForAddress");

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

    curtime.wHour = 8;
    curtime.wMinute = 56;
    curtime.wSecond = 13;
    curtime.wMilliseconds = 22;
    strcpy(inputA, "tt HH':'mm'@'ss");
    GetTimeFormatA(lcid, TIME_FORCE24HOURFORMAT, &curtime, inputA, bufferA, COUNTOF(bufferA));
    printf("GetTimeFormatA: %s\n", bufferA);

    wcscpy(inputW, L"tt HH':'mm'@'ss");
    GetTimeFormatW(lcid, TIME_FORCE24HOURFORMAT, &curtime, inputW, bufferW, COUNTOF(bufferW));
    printf("GetTimeFormatW: %ls\n", bufferW);

    GetModuleFileNameA(NULL, bufferA, COUNTOF(bufferA));
    printf("GetModuleFileNameA(NULL): %s\n", bufferA);
    GetModuleFileNameW(NULL, bufferW, COUNTOF(bufferW));
    printf("GetModuleFileNameW(NULL): %ls\n", bufferW);

    k32 = GetModuleHandleA("kernel32.dll");
    GetModuleFileNameW(k32, bufferW, COUNTOF(bufferW));
    printf("GetModuleFileNameW(GetModuleHandleA(\"kernel32\")=%p): %ls\n", k32, bufferW);

    heaptest = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 16);
    memcpy(heaptest, "12345", 5);
    printf("%s\n", heaptest);
    HeapFree(GetProcessHeap(), 0, heaptest);

    MultiByteToWideChar(CP_ACP, 0, "char input", -1, bufferW, COUNTOF(bufferW));
    printf("MultiByteToWideChar: %ls\n", bufferW);

    WideCharToMultiByte(CP_ACP, 0, L"wide char input", -1, bufferA, COUNTOF(bufferA), NULL, NULL);
    printf("WideCharToMultiByte: %s\n", bufferA);

    printf("lstrcmpW(abc123, abc456)=%d\n", lstrcmpW(L"abc123", L"abc456"));
    printf("lstrcmpW(abc123, abc123)=%d\n", lstrcmpW(L"abc123", L"abc123"));
    printf("lstrcmpW(abc456, abc123)=%d\n", lstrcmpW(L"abc456", L"abc123"));

somelabel:
    pLdrFindEntryForAddress(&&somelabel, &test_mod);
    printf("Got module %p for label in my code.\n", test_mod);
    pLdrFindEntryForAddress(HeapAlloc, &test_mod);
    printf("Got module %p for HeapAlloc.\n", test_mod);

    /* Inspired by some stackoverflow discussion. */
    __try1(test_handler)
    {
        RUNTIME_FUNCTION *func;
        CONTEXT context = {0};
        ULONG64 frame;
        void *handler_data;
        long dummy;

        exceptlabel:
        printf("Dummy printf inside a try block\n");

        func = RtlLookupFunctionEntry((DWORD64)&&exceptlabel, (ULONG64 *)&test_mod, NULL);

        printf("Found function table entry %p.\n", func);
        if (func->BeginAddress + (ULONG64)test_mod == (ULONG64)main)
            printf("Begin matches this function. Begin %lx, main %p, base %p\n", func->BeginAddress, main, test_mod);
        else
            printf("Seems like I found an incorrect function entry. Begin %lx, main %p, base %p\n", func->BeginAddress, main, test_mod);

        RtlCaptureContext(&context);
        printf("Got rsp %p, rbp %p.\n", (void *)context.Rsp, (void *)context.Rbp);

        handler = RtlVirtualUnwind(UNW_FLAG_EHANDLER, (DWORD64)test_mod, context.Rip, func, &context, &handler_data, &frame, NULL);
        printf("Got language handler %p\n", handler);

        __asm__ goto ( "jmp %l[stupid_manual_jump]\n" :::: stupid_manual_jump);
    }
    __except1
    {
        printf("Dummy printf inside an except block\n");
    }
stupid_manual_jump:

    return 0;
}
