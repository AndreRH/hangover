#ifndef VA_HELPER_H
#define VA_HELPER_H

struct va_array
{
    uint64_t is_float;
    uint64_t arg;
};

extern uint64_t CDECL call_va(uint64_t (* CDECL func)(void *ctx, ...), void *ctx, unsigned int icount,
        unsigned int fcount, struct va_array *array);
extern uint64_t CDECL call_va2(uint64_t (* CDECL func)(void *fixed1, void *fixed2, ...), void *fixed1, void *fixed2,
        unsigned int icount, unsigned int fcount, struct va_array *array);

#endif
