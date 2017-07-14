#include <stdio.h>

int WinMain()
{
    char buffer[128];
    fprintf(stdout, "Hello world!\n");
    sprintf(buffer, "Hello sprintf, main@%p, float=%f", WinMain, 123.456);
    printf("%s\n", buffer);
    return 123;
}
