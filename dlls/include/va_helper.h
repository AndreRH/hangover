#ifndef VA_HELPER_H
#define VA_HELPER_H

struct va_array
{
    uint64_t is_float;
    uint64_t arg;
};

extern uint64_t call_va(uint64_t (*func)(void *ctx, ...), void *ctx, unsigned int icount,
        unsigned int fcount, const struct va_array *array);

#endif
