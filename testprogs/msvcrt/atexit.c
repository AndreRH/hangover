#include <stdio.h>
#include <stdlib.h>

static void exitfunc(void)
{
    printf("Exit function!\n");
}

int main(int argc, char *argv[])
{
    printf("Registering exit callback!\n");
    atexit(exitfunc);
    return 123;
}
