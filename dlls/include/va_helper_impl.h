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

#include <ffi.h>
#include "va_helper.h"

#include "config.h"
#undef _WIN32
#include "wine/asm.h"

#ifndef QEMU_DLL_GUEST

#if defined(__x86_64__) || defined(__aarch64__)
const ffi_abi ffiabi = FFI_WIN64;
#else
const ffi_abi ffiabi = FFI_DEFAULT_ABI;
#endif

#ifdef __ANDROID__
#define CNTWARN printf("call_va: Too many arguments, increase the arrays!\n")
#else
#define CNTWARN fprintf(stderr, "call_va: Too many arguments, increase the arrays!\n")
#endif

uint64_t CDECL call_va(uint64_t (* CDECL func)(void *ctx, ...), void *ctx, unsigned int icount, struct va_array *array)
{
    ffi_type *arg_types[64];
    void *values[64];
    uint64_t rc = 0;
    ffi_cif cif;
    int i;

    if (icount >= 64)
        CNTWARN;

    arg_types[0] = &ffi_type_pointer;
    values[0] = &ctx;
    for (i = 0; i < icount; i++)
    {
        arg_types[i + 1] = array[i].is_float ? &ffi_type_double :  &ffi_type_uint64;
        values[i + 1] = &array[i].arg;
    }

    if (ffi_prep_cif_var(&cif, ffiabi, 1, icount + 1, &ffi_type_uint64, arg_types) != FFI_OK)
        return 0;

    ffi_call(&cif, FFI_FN(func), &rc, values);
    return rc;
}

uint64_t CDECL call_va2(uint64_t (* CDECL func)(void *fixed1, void *fixed2, ...), void *fixed1, void *fixed2,
                                  unsigned int icount, struct va_array *array)
{
    ffi_type *arg_types[64];
    void *values[64];
    uint64_t rc = 0;
    ffi_cif cif;
    int i;

    if (icount >= 64)
        CNTWARN;

    arg_types[0] = &ffi_type_pointer;
    values[0] = &fixed1;
    arg_types[1] = &ffi_type_pointer;
    values[1] = &fixed2;
    for (i = 0; i < icount; i++)
    {
        arg_types[i + 2] = array[i].is_float ? &ffi_type_double :  &ffi_type_uint64;
        values[i + 2] = &array[i].arg;
    }

    if (ffi_prep_cif_var(&cif, ffiabi, 2, icount + 2, &ffi_type_uint64, arg_types) != FFI_OK)
        return 0;

    ffi_call(&cif, FFI_FN(func), &rc, values);
    return rc;
}
#endif
