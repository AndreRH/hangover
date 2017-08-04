#include <stdio.h>

int main()
{
    int *x = NULL;
    printf("Hello exception test.\n");
    *x = 1;
    printf("Should not get here.\n");
    return 0;
}
