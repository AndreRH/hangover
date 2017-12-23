/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* Include this only in your main file. */

#include "va_helper.h"

#ifdef __aarch64__

#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl " #name suffix "\n\t.type " #name suffix ",@function\n" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc\n\t.previous");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)
extern int CDECL call_va_asm( void *ctx, void *func, int nb_args, int nb_onstack, const void *args );
__ASM_GLOBAL_FUNC( call_va_asm,
                   "stp x29, x30, [SP,#-16]!\n\t"           /* push FP & LR */
                   "stp x19, x20, [SP,#-16]!\n\t"           /* push some regs we'll use */
                   "add x9, x4, x2, lsl #4\n\t"             /* end=args+nb_args*sizeof(args[0]) */
                   "mov x10, x1\n\t"                        /* remember func */
                   "mov x11, x4\n\t"                        /* remember args */
                   "mov x12, #0\n\t"                        /* init arg counter */
                   "mov x13, #0\n\t"                        /* init float arg counter */
                   "mov x19, #0\n\t"                        /* init align */
                   "mov x20, #0\n\t"                        /* init stack arg counter */
                   "cbz x3, 1f\n\t"                         /* if nb_onstack == 0 goto 1 */
                   "lsl x3, x3, #3\n\t"                     /* nb_onstack *= 8 */
                   "add x3, x3, #0x16\n\t"                  /* align helper */
                   "and x3, x3, #0xfffffffffffffff0\n\t"    /* align */
                   "sub SP, SP, x3\n\t"                     /* allocate space on stack for later */
                   "mov x19, x3\n\t"                        /* remember align */
                   "1: cbz x2, 11f\n\t"                     /* if nb_args == 0 goto 4 */
                   /* init  done */
                   "2: ldr x14, [x11]\n\t"                  /* is_float */
                   "cbz x14, 6f\n\t"                        /* if !is_float goto 97 */
                   "cmp x13, #8\n\t"                        /* if floats exceed 8, */
                   "b.eq 5f\n\t"                            /* they need to continue on the stack */
                   /* floats -> regs */
                   "adr x14, 3f\n\t"                        /* different reg per arg nubmer */
                   "add x14, x14, x13, lsl #3\n\t"          /* some kind of switch statement */
                   "br x14\n\t"
                   "3: ldr d0, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d1, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d2, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d3, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d4, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d5, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d6, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d7, [x11,#8]\n\t"
                   "4: add x13, x13, #1\n\t"                /* increment the float arg counter */
                   "b 10f\n\t"                              /* next */
                   /* floats -> stack */
                   "5: add x17, sp, x20, lsl #3\n\t"        /* pos = 8 * stack arg count + SP */
                   "ldr x16, [x11,#8]\n\t"                  /* load the value */
                   "str x16, [x17]\n\t"                     /* store it at the calculated position */
                   "add x20, x20, #1\n\t"                   /* increment the stack arg counter */
                   "b 10f\n\t"                              /* next */
                   "6: cmp x12, #7\n\t"                     /* if args exceed ctx+7, */
                   "b.eq 9f\n\t"                            /* they need to continue on the stack */
                   /* ints -> reg */
                   "adr x14, 7f\n\t"                        /* different reg per arg nubmer */
                   "add x14, x14, x12, lsl #3\n\t"          /* some kind of switch statement */
                   "br x14\n\t"
                   "7: ldr x1, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x2, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x3, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x4, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x5, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x6, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x7, [x11,#8]\n\t"
                   "8: add x12, x12, #1\n\t"                /* increment the arg counter */
                   "b 10f\n\t"                              /* next */
                   /* ints -> stack */
                   "9: add x17, sp, x20, lsl #3\n\t"        /* pos = 8 * stack arg count + SP */
                   "ldr x16, [x11,#8]\n\t"                  /* load the value */
                   "str x16, [x17]\n\t"                     /* store it at the calculated position */
                   "add x20, x20, #1\n\t"                   /* increment the stack arg counter */
                   "10: add x11, x11, #0x10\n\t"            /* next in args */
                   "cmp	x11, x9\n\t"                        /* end? */
                   "b.ne 2b\n\t"                            /* if not, loop */
                   "11: blr x10\n\t"                        /* call func */
                   "add SP, SP, x19\n\t"                    /* restore stack */
                   "ldp x19, x20, [SP], #16\n\t"            /* pop local regs */
                   "ldp x29, x30, [SP], #16\n\t"            /* pop FP & LR */
                   "ret\n\t" )

#else

extern int CDECL call_va_asm( void *ctx, void *func, int nb_args, int nb_onstack, const void *args );
#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl _" #name suffix "\n\t\n_" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc\n\t.previous");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)
__ASM_GLOBAL_FUNC(call_va_asm,
                  "push %rbp\n\t"
                  "push %rbx\n\t"
                  "push %rsi\n\t"
                  /* Stack should be aligned here (8 bytes ret, 40 bytes pushed) */
                  "mov %rsp, %rbp\n\t"

                  /* Load args from stack 0x8*5(push) + 0x8 (ret) + 0x20(space) */
                  "mov 0x40(%rbp), %rsi\n\t"

                  /* Calculate array end */
                  "leaq (%rsi,%r8,8), %r11\n\t"
                  "leaq (%r11,%r8,8), %r11\n\t"

                  /* align stack in case of uneven number of stack params */
                  "mov %r9, %rax\n\t"
                  "and $0x1, %rax\n\t"
                  "add %rax, %r9\n\t"

                  /* Remember func, we’ll probably overwrite it in the input register */
                  "mov %rdx, %rbx\n\t"

                  /* Reserve stack space for stack params */
                  "mov $0x8, %rax\n\t"
                  "mulq %r9\n\t"
                  "sub %rax, %rsp\n\t"

                  /* If parameter X is a float, the corresponding int parameter register
                   * is ignored and vice versa. */
                  "xor %rax, %rax\n\t" /* stored register params */

                  /* From here on RDX, R8 and R9 may no longer contain our params, and instead
                   * the params we pass on to func */

                  "loop:\n\t"
                      "cmpq %rsi, %r11\n\t"
                      "je done\n\t"

                      /* is it a float? */
                      "cmpq $0x0, (%rsi)\n\t"
                      "je int_param\n\t"
                          /* Handle floats here. It seems that float register parameters are also
                           * copied into their int slots, and apparently also read from there.
                           * This behavior isn't explicitly mentioned in the calling convention
                           * description. However, Microsoft's page describing the behavior for
                           * calling unprototyped functions mentions it. */
                          "cmpq $0x0, %rax\n\t"
                          "jne cmp_f1\n\t"
                              "mov 0x8(%rsi), %rdx\n\t"
                              "movsd 0x8(%rsi), %xmm1\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch\n\t"

                          "cmp_f1:\n\t"
                          "cmpq $0x1, %rax\n\t"
                          "jne cmp_f2\n\t"
                              "mov 0x8(%rsi), %r8\n\t"
                              "movsd 0x8(%rsi), %xmm2\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch\n\t"

                          "cmp_f2:\n\t"
                          "cmpq $0x2, %rax\n\t"
                          "jne store_fstack\n\t"
                              "mov 0x8(%rsi), %r9\n\t"
                              "movsd 0x8(%rsi), %xmm3\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch\n\t"

                          "store_fstack:\n\t"
                              "mov 0x8(%rsi), %r10\n\t"
                              "mov %r10, -0x18(%rsp, %rax, 8)\n\t"
                              "inc %rax\n\t"

                          "jmp end_branch\n\t"

                      /* else */
                      "int_param:\n\t"
                          "cmpq $0x0, %rax\n\t"
                          "jne cmp_i1\n\t"
                              "mov 0x8(%rsi), %rdx\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch\n\t"

                          "cmp_i1:\n\t"
                          "cmpq $0x1, %rax\n\t"
                          "jne cmp_i2\n\t"
                              "mov 0x8(%rsi), %r8\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch\n\t"

                          "cmp_i2:\n\t"
                          "cmpq $0x2, %rax\n\t"
                          "jne store_istack\n\t"
                              "mov 0x8(%rsi), %r9\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch\n\t"

                          "store_istack:\n\t"
                              "mov 0x8(%rsi), %r10\n\t"
                              "mov %r10, -0x18(%rsp, %rax, 8)\n\t"
                              "inc %rax\n\t"

                      "end_branch:\n\t"

                      /* Next array entry */
                      "add $0x10, %rsi\n\t"

                      "jmp loop\n\t"

                  "done:\n\t"

                  /* parameter 1 (ctx, in rcx) is already in place */
                  "sub $0x20, %rsp\n\t" /* Shadow register space */
                  "call *%rbx\n\t"

                  "mov %rbp, %rsp\n\t"
                  "pop %rsi\n\t"
                  "pop %rbx\n\t"
                  "pop %rbp\n\t"
                  "ret\n\t" )

#endif

uint64_t CDECL call_va(uint64_t (* CDECL func)(void *ctx, ...), void *ctx, unsigned int icount,
        unsigned int fcount, const struct va_array *array)
{
    int onstack = 0;

    if (icount > 3)
        onstack += icount - 3;

    return call_va_asm(ctx, func, icount, onstack, array);
}

#ifdef __aarch64__

extern int CDECL call_va_asm2( void *fixed1, void *fixed2, void *func, int nb_args, int nb_onstack, const void *args );
__ASM_GLOBAL_FUNC( call_va_asm2,
                   "stp x29, x30, [SP,#-16]!\n\t"           /* push FP & LR */
                   "stp x19, x20, [SP,#-16]!\n\t"           /* push some regs we'll use */
                   "add x9, x5, x3, lsl #4\n\t"             /* end=args+nb_args*sizeof(args[0]) */
                   "mov x10, x2\n\t"                        /* remember func */
                   "mov x11, x5\n\t"                        /* remember args */
                   "mov x12, #0\n\t"                        /* init arg counter */
                   "mov x13, #0\n\t"                        /* init float arg counter */
                   "mov x19, #0\n\t"                        /* init align */
                   "mov x20, #0\n\t"                        /* init stack arg counter */
                   "cbz x4, 1f\n\t"                         /* if nb_onstack == 0 goto 1 */
                   "lsl x4, x4, #3\n\t"                     /* nb_onstack *= 8 */
                   "add x4, x4, #0x16\n\t"                  /* align helper */
                   "and x4, x4, #0xfffffffffffffff0\n\t"    /* align */
                   "sub SP, SP, x4\n\t"                     /* allocate space on stack for later */
                   "mov x19, x4\n\t"                        /* remember align */
                   "1: cbz x3, 11f\n\t"                     /* if nb_args == 0 goto 4 */
                   /* init  done */
                   "2: ldr x14, [x11]\n\t"                  /* is_float */
                   "cbz x14, 6f\n\t"                        /* if !is_float goto 97 */
                   "cmp x13, #8\n\t"                        /* if floats exceed 8, */
                   "b.eq 5f\n\t"                            /* they need to continue on the stack */
                   /* floats -> regs */
                   "adr x14, 3f\n\t"                        /* different reg per arg nubmer */
                   "add x14, x14, x13, lsl #3\n\t"          /* some kind of switch statement */
                   "br x14\n\t"
                   "3: ldr d0, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d1, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d2, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d3, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d4, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d5, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d6, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d7, [x11,#8]\n\t"
                   "4: add x13, x13, #1\n\t"                /* increment the float arg counter */
                   "b 10f\n\t"                              /* next */
                   /* floats -> stack */
                   "5: add x17, sp, x20, lsl #3\n\t"        /* pos = 8 * stack arg count + SP */
                   "ldr x16, [x11,#8]\n\t"                  /* load the value */
                   "str x16, [x17]\n\t"                     /* store it at the calculated position */
                   "add x20, x20, #1\n\t"                   /* increment the stack arg counter */
                   "b 10f\n\t"                              /* next */
                   "6: cmp x12, #6\n\t"                     /* if args exceed file+fmt+6, */
                   "b.eq 9f\n\t"                            /* they need to continue on the stack */
                   /* ints -> reg */
                   "adr x14, 7f\n\t"                        /* different reg per arg nubmer */
                   "add x14, x14, x12, lsl #3\n\t"          /* some kind of switch statement */
                   "br x14\n\t"
                   "7: ldr x2, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x3, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x4, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x5, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x6, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x7, [x11,#8]\n\t"
                   "8: add x12, x12, #1\n\t"                /* increment the arg counter */
                   "b 10f\n\t"                              /* next */
                   /* ints -> stack */
                   "9: add x17, sp, x20, lsl #3\n\t"        /* pos = 8 * stack arg count + SP */
                   "ldr x16, [x11,#8]\n\t"                  /* load the value */
                   "str x16, [x17]\n\t"                     /* store it at the calculated position */
                   "add x20, x20, #1\n\t"                   /* increment the stack arg counter */
                   "10: add x11, x11, #0x10\n\t"            /* next in args */
                   "cmp	x11, x9\n\t"                        /* end? */
                   "b.ne 2b\n\t"                            /* if not, loop */
                   "11: blr x10\n\t"                        /* call func */
                   "add SP, SP, x19\n\t"                    /* restore stack */
                   "ldp x19, x20, [SP], #16\n\t"            /* pop local regs */
                   "ldp x29, x30, [SP], #16\n\t"            /* pop FP & LR */
                   "ret\n\t" )

uint64_t call_va2(uint64_t (* CDECL func)(void *fixed1, void *fixed2, ...), void *fixed1, void *fixed2,
                  unsigned int icount, unsigned int fcount, const struct va_array *array)
{
    int onstack = 0;

    if (icount - fcount > 6)
        onstack = icount - fcount - 6;
    if (fcount > 8)
        onstack += fcount - 8;

    return call_va_asm2(fixed1, fixed2, func, icount, onstack, array);
}

#else

extern int CDECL call_va_asm2( void *fixed1, void *fixed2, void *func, int nb_args, int nb_onstack, const void *args );
__ASM_GLOBAL_FUNC(call_va_asm2,
                  "push %rbp\n\t"
                  "push %rbx\n\t"
                  "push %rsi\n\t"
                  /* Stack should be aligned here (8 bytes ret, 40 bytes pushed) */
                  "mov %rsp, %rbp\n\t"

                  /* Load args from stack 0x8*5(push) + 0x8 (ret) + 0x20(space) */
                  "mov 0x48(%rbp), %rsi\n\t"

                  /* Calculate array end */
                  "leaq (%rsi,%r9,8), %r11\n\t"
                  "leaq (%r11,%r9,8), %r11\n\t"

                  /* align stack in case of uneven number of stack params */
                  "mov 0x40(%rbp), %r10\n\t"
                  "mov %r10, %rax\n\t"
                  "and $0x1, %rax\n\t"
                  "add %rax, %r10\n\t"

                  /* Remember fixed2, we’ll overwrite it in the mul */
                  "mov %rdx, %rbx\n\t"

                  /* Reserve stack space for stack params */
                  "mov $0x8, %rax\n\t"
                  "mulq %r10\n\t"
                  "sub %rax, %rsp\n\t"

                  /* If parameter X is a float, the corresponding int parameter register
                   * is ignored and vice versa. */
                  "xor %rax, %rax\n\t" /* stored register params */

                  /* Restore fixed2 back into where we want it */
                  "mov %rbx, %rdx\n\t"

                  /* Remember func before we overwrite the register for param 3. */
                  "mov %r8, %rbx\n\t"

                  /* From here on RDX, R8 and R9 may no longer contain our params, and instead
                   * the params we pass on to func */
                  "loop2:\n\t"
                      "cmpq %rsi, %r11\n\t"
                      "je done2\n\t"

                      /* is it a float? */
                      "cmpq $0x0, (%rsi)\n\t"
                      "je int_param2\n\t"
                          /* Handle floats here. It seems that float register parameters are also
                           * copied into their int slots, and apparently also read from there.
                           * This behavior isn't explicitly mentioned in the calling convention
                           * description. However, Microsoft's page describing the behavior for
                           * calling unprototyped functions mentions it. */
                          "cmpq $0x0, %rax\n\t"
                          "jne cmp_f12\n\t"
                              "mov 0x8(%rsi), %r8\n\t"
                              "movsd 0x8(%rsi), %xmm2\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch2\n\t"

                          "cmp_f12:\n\t"
                          "cmpq $0x1, %rax\n\t"
                          "jne store_fstack2\n\t"
                              "mov 0x8(%rsi), %r9\n\t"
                              "movsd 0x8(%rsi), %xmm3\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch2\n\t"

                          "store_fstack2:\n\t"
                              "mov 0x8(%rsi), %r10\n\t"
                              "mov %r10, -0x10(%rsp, %rax, 8)\n\t"
                              "inc %rax\n\t"

                          "jmp end_branch2\n\t"

                      /* else */
                      "int_param2:\n\t"
                          "cmpq $0x0, %rax\n\t"
                          "jne cmp_i12\n\t"
                              "mov 0x8(%rsi), %r8\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch2\n\t"

                          "cmp_i12:\n\t"
                          "cmpq $0x1, %rax\n\t"
                          "jne store_istack2\n\t"
                              "mov 0x8(%rsi), %r9\n\t"
                              "inc %rax\n\t"
                              "jmp end_branch2\n\t"

                          "store_istack2:\n\t"
                              "mov 0x8(%rsi), %r10\n\t"
                              "mov %r10, -0x10(%rsp, %rax, 8)\n\t"
                              "inc %rax\n\t"

                      "end_branch2:\n\t"

                      /* Next array entry */
                      "add $0x10, %rsi\n\t"

                      "jmp loop2\n\t"
                  "done2:\n\t"

                  /* parameter 1 (fixed1, in rcx) is already in place */
                  /* parameter 2 (fixed2, in rdx) is already in place */
                  "sub $0x20, %rsp\n\t" /* Shadow register space */
                  "call *%rbx\n\t"

                  "mov %rbp, %rsp\n\t"
                  "pop %rsi\n\t"
                  "pop %rbx\n\t"
                  "pop %rbp\n\t"

                  "ret\n\t" )

uint64_t call_va2(uint64_t (* CDECL func)(void *fixed1, void *fixed2, ...), void *fixed1, void *fixed2,
                  unsigned int icount, unsigned int fcount, const struct va_array *array)
{
    int onstack = 0;

    if (icount > 2)
        onstack += icount - 2;

    return call_va_asm2(fixed1, fixed2, func, icount, onstack, array);
}

#endif
