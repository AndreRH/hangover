#include <stdio.h>
#include <wchar.h>

int wcscpy_s(wchar_t *, size_t, const wchar_t *);
int wcscat_s(wchar_t *, size_t, const wchar_t *);
int swprintf_s(wchar_t *str, size_t count, const wchar_t *format, ...);

int WinMain()
{
    char buffer[128];
    wchar_t bufferW[128];
    double db;

    fprintf(stdout, "Hello world!\n");
    sprintf(buffer, "Hello sprintf, main@%p, float=%f", WinMain, 123.456);
    printf("%s\n", buffer);

    printf("wcsstr(\"12345\", \"34\")=%p\n", wcsstr(L"12345", L"34"));

    wcscpy_s(bufferW, 128, L"Test wcscpy");
    wcscat_s(bufferW, 128, L" + wcscat_s !!!");
    printf("%ls\n", bufferW);

    printf("wcsncmp(\"12345\", \"12367\", 3)=%d\n", wcsncmp(L"12345", L"12367", 3));
    printf("wcsncmp(\"12345\", \"12367\", 4)=%d\n", wcsncmp(L"12345", L"12367", 4));
    printf("_wcsnicmp(\"ABCDEF\", \"abcdef\", 7)=%d\n", _wcsnicmp(L"ABCDEF", L"abcdef", 7));
    printf("_wcsnicmp(\"ABCDEF\", \"abXdef\", 7)=%d\n", _wcsnicmp(L"ABCDEF", L"abXdef", 7));

    db = wcstod(L"123.456", NULL);
    printf("wcstod(123.456)=%f\n", db);

    swprintf_s(bufferW, 128, L"This is a %s test", L"sprintf_s");
    printf("Hello swprintf_s %p \"%ls\"\n", bufferW, bufferW);

    printf("_wtoi(L\"-123\")=%d\n", _wtoi(L"-123"));

    return 123;
}
