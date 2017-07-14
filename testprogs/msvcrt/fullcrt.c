#include <stdio.h>
#include <wchar.h>

int WinMain()
{
    char buffer[128];
    fprintf(stdout, "Hello world!\n");
    sprintf(buffer, "Hello sprintf, main@%p, float=%f", WinMain, 123.456);
    printf("%s\n", buffer);

    printf("wcsstr(\"12345\", \"34\")=%p\n", wcsstr(L"12345", L"34"));
    return 123;
}
