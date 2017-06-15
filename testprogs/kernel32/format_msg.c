#include <stdio.h>
#include <windows.h>

#include "format_msg.h"

int main()
{
    WCHAR output[512];
    const WCHAR *inserts[] = {L"insert1", L"insert2", L"insert3"};
    HMODULE kernel32 = GetModuleHandle("kernel32.dll");
    WCHAR *allocbuf;

    /* Strings loaded from message resources have newlines at the end,
     * so don't bother writing another \n. */

    FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_IGNORE_INSERTS,
            L"Dummy input string", 0, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
            output, sizeof(output)/sizeof(*output), NULL);
    fprintf(stderr, "Output 1: \"%ls\" \n", output);

    FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
            L"1: \"%1\", 3: \"%3\". 2: \"%2\", 1: \"%1\".", 0,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), output,
            sizeof(output)/sizeof(*output), (void *)inserts);
    fprintf(stderr, "Output 2: \"%ls\" \n", output);

    FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_IGNORE_INSERTS,
            kernel32, 193 /* ERROR_BAD_EXE_FORMAT */,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
            output, sizeof(output)/sizeof(*output), NULL);
    fprintf(stderr, "Output 3: %ls", output);

    FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_ARGUMENT_ARRAY,
            kernel32, 193 /* ERROR_BAD_EXE_FORMAT */,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
            output, sizeof(output)/sizeof(*output), (void *)inserts);
    fprintf(stderr, "Output 4: %ls", output);

    FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, MYSTRING1,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
            output, sizeof(output)/sizeof(*output), NULL);
    fprintf(stderr, "Output 5: %ls", output);

    inserts[0] = (const wchar_t *)12345;
    FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
            L"Here be integers: %1!d!. And strings: %2", 0,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), output,
            sizeof(output)/sizeof(*output), (void *)inserts);
    fprintf(stderr, "Output 6: %ls\n", output);

    FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS
            | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL, MYSTRING2,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
            (void *)&allocbuf, 0, NULL);
    fprintf(stderr, "Output 7: %ls", allocbuf);
    LocalFree(allocbuf);

    return 0;
}
