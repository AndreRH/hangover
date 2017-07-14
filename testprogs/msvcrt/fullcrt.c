#include <stdio.h>
#include <wchar.h>

int wcscpy_s(wchar_t *, size_t, const wchar_t *);

int WinMain()
{
    char buffer[128];
    wchar_t bufferW[128];
    fprintf(stdout, "Hello world!\n");
    sprintf(buffer, "Hello sprintf, main@%p, float=%f", WinMain, 123.456);
    printf("%s\n", buffer);

    printf("wcsstr(\"12345\", \"34\")=%p\n", wcsstr(L"12345", L"34"));

    wcscpy_s(bufferW, 128, L"Test wcscpy !!!");
    printf("%ls\n", bufferW);

    return 123;
}
