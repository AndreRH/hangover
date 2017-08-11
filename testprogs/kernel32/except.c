#include <windows.h>
#include <stdio.h>

static int global = 0;

static LONG WINAPI my_filter(PEXCEPTION_POINTERS epointers)
{
    printf("in my filter, %%rcx=%p\n", (void *)epointers->ContextRecord->Rcx);
    epointers->ContextRecord->Rcx = (DWORD64)&global;
    return EXCEPTION_CONTINUE_EXECUTION;
}

int main()
{
    int *x = NULL;
    printf("Hello exception test.\n");

    SetUnhandledExceptionFilter(my_filter);

    asm volatile( "movq $1, (%%rcx)\n"
            : /* no output */
            : "c"(x)
            : "memory");

    printf("Post exception, global=%d, &global=%p, x=%p.\n", global, &global, x);
    return 0;
}
