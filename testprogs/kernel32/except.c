#include <windows.h>
#include <stdio.h>

static int global = 0;
static CONTEXT compare_ctx;

static LONG WINAPI my_filter(PEXCEPTION_POINTERS epointers)
{
    printf("in my filter, %%rcx=%p\n", (void *)epointers->ContextRecord->Rcx);

    if (memcmp(&epointers->ContextRecord->FltSave, &compare_ctx.FltSave, sizeof(compare_ctx.FltSave)))
        printf("Float state differs.\n");
    else
        printf("Float state is equal.\n");


    epointers->ContextRecord->Rcx = (DWORD64)&global;
    return EXCEPTION_CONTINUE_EXECUTION;
}

int main()
{
    int *x = NULL;
    printf("Hello exception test.\n");
    volatile float f = 123.4;
    volatile float g = 456.7;

    printf("Printing a float %f and another %f, multiplied %f to put junk into fpregs.\n",
            f, g, f * g);
    RtlCaptureContext(&compare_ctx);

    SetUnhandledExceptionFilter(my_filter);

    asm volatile( "movq $1, (%%rcx)\n"
            : /* no output */
            : "c"(x)
            : "memory");

    printf("Post exception, global=%d, &global=%p, x=%p.\n", global, &global, x);
    return 0;
}
