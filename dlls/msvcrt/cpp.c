/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

#define TRACE(str, ...)

#include "cppexcept.h"
#include "cxx.h"

typedef void (*vtable_ptr)(void);

typedef exception bad_cast;

extern const vtable_ptr MSVCRT_exception_vtable;
extern const vtable_ptr MSVCRT_type_info_vtable;
extern const vtable_ptr MSVCRT_bad_cast_vtable;

#ifdef _WIN64
void CDECL MSVCRT__CxxThrowException(void *object, const void *type)
#else
void WINAPI MSVCRT__CxxThrowException( void *object, const void *type )
#endif
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__CXXTHROWEXCEPTION);

    qemu_syscall(&call);
}

#else

void qemu__CxxThrowException(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_terminate(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_TERMINATE);

    qemu_syscall(&call);
}

#else

void qemu_terminate(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    p_terminate();
}

#endif

struct qemu_type_info_dtor
{
    struct qemu_syscall super;
    uint64_t this;
};

#ifdef QEMU_DLL_GUEST

void __thiscall __thiscall_MSVCRT_type_info_dtor(void * _this)
{
    struct qemu_type_info_dtor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TYPE_INFO_DTOR);
    call.this = (ULONG_PTR)_this;

    qemu_syscall(&call.super);
}

#else

void qemu_type_info_dtor(struct qemu_syscall *call)
{
    struct qemu_type_info_dtor *c = (struct qemu_type_info_dtor *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_type_info_dtor(QEMU_G2H(c->this));
}

#endif

#ifdef QEMU_DLL_GUEST

/* Internal common ctor for exception */
static void EXCEPTION_ctor(exception *_this, const char** name)
{
  _this->vtable = &MSVCRT_exception_vtable;
  if (*name)
  {
    unsigned int name_len = MSVCRT_strlen(*name) + 1;
    _this->name = MSVCRT_malloc(name_len);
    MSVCRT_memcpy(_this->name, *name, name_len);
    _this->do_free = TRUE;
  }
  else
  {
    _this->name = NULL;
    _this->do_free = FALSE;
  }
}

/******************************************************************
 *		??0exception@@QAE@ABQBD@Z (MSVCRT.@)
 */
exception * __thiscall __thiscall_MSVCRT_exception_ctor(exception * _this, const char ** name)
{
  TRACE("(%p,%s)\n", _this, *name);
  EXCEPTION_ctor(_this, name);
  return _this;
}

/******************************************************************
 *		??0exception@@QAE@ABQBDH@Z (MSVCRT.@)
 */
exception * __thiscall __thiscall_MSVCRT_exception_ctor_noalloc(exception * _this, char ** name, int noalloc)
{
  TRACE("(%p,%s)\n", _this, *name);
  _this->vtable = &MSVCRT_exception_vtable;
  _this->name = *name;
  _this->do_free = FALSE;
  return _this;
}

/******************************************************************
 *		??0exception@@QAE@ABV0@@Z (MSVCRT.@)
 */
exception * __thiscall __thiscall_MSVCRT_exception_copy_ctor(exception * _this, const exception * rhs)
{
  TRACE("(%p,%p)\n", _this, rhs);

  if (!rhs->do_free)
  {
    _this->vtable = &MSVCRT_exception_vtable;
    _this->name = rhs->name;
    _this->do_free = FALSE;
  }
  else
    EXCEPTION_ctor(_this, (const char**)&rhs->name);
  TRACE("name = %s\n", _this->name);
  return _this;
}

/******************************************************************
 *		??0exception@@QAE@XZ (MSVCRT.@)
 */
exception * __thiscall __thiscall_MSVCRT_exception_default_ctor(exception * _this)
{
  static const char* empty = NULL;

  TRACE("(%p)\n", _this);
  EXCEPTION_ctor(_this, &empty);
  return _this;
}

/******************************************************************
 *		??1exception@@UAE@XZ (MSVCRT.@)
 */
void __thiscall __thiscall_MSVCRT_exception_dtor(exception * _this)
{
  TRACE("(%p)\n", _this);
  _this->vtable = &MSVCRT_exception_vtable;
  if (_this->do_free) MSVCRT_free(_this->name);
}

/******************************************************************
 *		??4exception@@QAEAAV0@ABV0@@Z (MSVCRT.@)
 */
exception * __thiscall __thiscall_MSVCRT_exception_opequals(exception * _this, const exception * rhs)
{
  TRACE("(%p %p)\n", _this, rhs);
  if (_this != rhs)
  {
      __thiscall_MSVCRT_exception_dtor(_this);
      __thiscall_MSVCRT_exception_copy_ctor(_this, rhs);
  }
  TRACE("name = %s\n", _this->name);
  return _this;
}

/******************************************************************
 *		??_Eexception@@UAEPAXI@Z (MSVCRT.@)
 */
void * __thiscall __thiscall_MSVCRT_exception_vector_dtor(exception * _this, unsigned int flags)
{
    TRACE("(%p %x)\n", _this, flags);
    if (flags & 2)
    {
        /* we have an array, with the number of elements stored before the first object */
        INT_PTR i, *ptr = (INT_PTR *)_this - 1;

        for (i = *ptr - 1; i >= 0; i--) __thiscall_MSVCRT_exception_dtor(_this + i);
        MSVCRT_operator_delete(ptr);
    }
    else
    {
        __thiscall_MSVCRT_exception_dtor(_this);
        if (flags & 1) MSVCRT_operator_delete(_this);
    }
    return _this;
}

/******************************************************************
 *		??_Gexception@@UAEPAXI@Z (MSVCRT.@)
 */
void * __thiscall __thiscall_MSVCRT_exception_scalar_dtor(exception * _this, unsigned int flags)
{
    TRACE("(%p %x)\n", _this, flags);
    __thiscall_MSVCRT_exception_dtor(_this);
    if (flags & 1) MSVCRT_operator_delete(_this);
    return _this;
}

/******************************************************************
 *		?what@exception@@UBEPBDXZ (MSVCRT.@)
 */
const char * __thiscall __thiscall_MSVCRT_what_exception(exception * _this)
{
  TRACE("(%p) returning %s\n", _this, _this->name);
  return _this->name ? _this->name : "Unknown exception";
}

/******************************************************************
 *		??0bad_cast@@AAE@PBQBD@Z (MSVCRT.@)
 *		??0bad_cast@@QAE@ABQBD@Z (MSVCRT.@)
 */
bad_cast * __thiscall __thiscall_MSVCRT_bad_cast_ctor(bad_cast * _this, const char ** name)
{
  TRACE("(%p %s)\n", _this, *name);
  EXCEPTION_ctor(_this, name);
  _this->vtable = &MSVCRT_bad_cast_vtable;
  return _this;
}

/******************************************************************
 *		??0bad_cast@@QAE@ABV0@@Z (MSVCRT.@)
 */
bad_cast * __thiscall __thiscall_MSVCRT_bad_cast_copy_ctor(bad_cast * _this, const bad_cast * rhs)
{
  TRACE("(%p %p)\n", _this, rhs);
  __thiscall_MSVCRT_exception_copy_ctor(_this, rhs);
  _this->vtable = &MSVCRT_bad_cast_vtable;
  return _this;
}

/******************************************************************
 *		??0bad_cast@@QAE@PBD@Z (MSVCRT.@)
 */
bad_cast * __thiscall __thiscall_MSVCRT_bad_cast_ctor_charptr(bad_cast * _this, const char * name)
{
  TRACE("(%p %s)\n", _this, name);
  EXCEPTION_ctor(_this, &name);
  _this->vtable = &MSVCRT_bad_cast_vtable;
  return _this;
}

/******************************************************************
 *		??_Fbad_cast@@QAEXXZ (MSVCRT.@)
 */
bad_cast * __thiscall __thiscall_MSVCRT_bad_cast_default_ctor(bad_cast * _this)
{
  return __thiscall_MSVCRT_bad_cast_ctor_charptr( _this, "bad cast" );
}

/******************************************************************
 *		??1bad_cast@@UAE@XZ (MSVCRT.@)
 */
void __thiscall __thiscall_MSVCRT_bad_cast_dtor(bad_cast * _this)
{
  TRACE("(%p)\n", _this);
  __thiscall_MSVCRT_exception_dtor(_this);
}

/******************************************************************
 *		??4bad_cast@@QAEAAV0@ABV0@@Z (MSVCRT.@)
 */
bad_cast * __thiscall __thiscall_MSVCRT_bad_cast_opequals(bad_cast * _this, const bad_cast * rhs)
{
  TRACE("(%p %p)\n", _this, rhs);
  __thiscall_MSVCRT_exception_opequals(_this, rhs);
  return _this;
}

/******************************************************************
 *              ??_Ebad_cast@@UAEPAXI@Z (MSVCRT.@)
 */
void * __thiscall __thiscall_MSVCRT_bad_cast_vector_dtor(bad_cast * _this, unsigned int flags)
{
    TRACE("(%p %x)\n", _this, flags);
    if (flags & 2)
    {
        /* we have an array, with the number of elements stored before the first object */
        INT_PTR i, *ptr = (INT_PTR *)_this - 1;

        for (i = *ptr - 1; i >= 0; i--) __thiscall_MSVCRT_bad_cast_dtor(_this + i);
        MSVCRT_operator_delete(ptr);
    }
    else
    {
        __thiscall_MSVCRT_bad_cast_dtor(_this);
        if (flags & 1) MSVCRT_operator_delete(_this);
    }
    return _this;
}

/******************************************************************
 *		??_Gbad_cast@@UAEPAXI@Z (MSVCRT.@)
 */
void * __thiscall __thiscall_MSVCRT_bad_cast_scalar_dtor(bad_cast * _this, unsigned int flags)
{
  TRACE("(%p %x)\n", _this, flags);
  __thiscall_MSVCRT_bad_cast_dtor(_this);
  if (flags & 1) MSVCRT_operator_delete(_this);
  return _this;
}

void * __thiscall MSVCRT_type_info_vector_dtor(type_info * _this, unsigned int flags)
{
    TRACE("(%p %x)\n", _this, flags);
    if (flags & 2)
    {
        /* we have an array, with the number of elements stored before the first object */
        INT_PTR i, *ptr = (INT_PTR *)_this - 1;

        for (i = *ptr - 1; i >= 0; i--) __thiscall_MSVCRT_type_info_dtor(_this + i);
        MSVCRT_operator_delete(ptr);
    }
    else
    {
        __thiscall_MSVCRT_type_info_dtor(_this);
        if (flags & 1) MSVCRT_operator_delete(_this);
    }
    return _this;
}

__ASM_VTABLE(type_info,
        VTABLE_ADD_FUNC(MSVCRT_type_info_vector_dtor));
__ASM_VTABLE(exception,
        VTABLE_ADD_FUNC(__thiscall_MSVCRT_exception_vector_dtor)
        VTABLE_ADD_FUNC(__thiscall_MSVCRT_what_exception));
#if _MSVCR_VER >= 80
__ASM_VTABLE(exception_old,
        VTABLE_ADD_FUNC(__thiscall_MSVCRT_exception_vector_dtor)
        VTABLE_ADD_FUNC(__thiscall_MSVCRT_what_exception));
#endif
__ASM_VTABLE(bad_cast,
        VTABLE_ADD_FUNC(__thiscall_MSVCRT_bad_cast_vector_dtor)
        VTABLE_ADD_FUNC(__thiscall_MSVCRT_what_exception));

DEFINE_RTTI_DATA0( type_info, 0, ".?AVtype_info@@" )
#if _MSVCR_VER >= 80
DEFINE_RTTI_DATA0( exception, 0, ".?AVexception@std@@" )
DEFINE_RTTI_DATA0( exception_old, 0, ".?AVexception@@" )
DEFINE_RTTI_DATA1( bad_cast, 0, &exception_rtti_base_descriptor, ".?AVbad_cast@std@@" )
#else
DEFINE_RTTI_DATA0( exception, 0, ".?AVexception@@" )
DEFINE_RTTI_DATA1( bad_cast, 0, &exception_rtti_base_descriptor, ".?AVbad_cast@@" )
#endif

/* FIXME: Call me from DLLMain */
void msvcrt_init_exception(void *base)
{
#ifdef __x86_64__
    init_type_info_rtti(base);
    init_exception_rtti(base);
#if _MSVCR_VER >= 80
    init_exception_old_rtti(base);
//     init_bad_alloc_rtti(base);
#endif
//     init_bad_typeid_rtti(base);
    init_bad_cast_rtti(base);
//     init___non_rtti_object_rtti(base);
#if _MSVCR_VER >= 100
//     init_scheduler_resource_allocation_error_rtti(base);
//     init_improper_lock_rtti(base);
//     init_invalid_scheduler_policy_key_rtti(base);
//     init_invalid_scheduler_policy_value_rtti(base);
//     init_invalid_scheduler_policy_thread_specification_rtti(base);
//     init_improper_scheduler_attach_rtti(base);
//     init_improper_scheduler_detach_rtti(base);
#endif

//     init_exception_cxx(base);
//     init_bad_typeid_cxx(base);
//     init_bad_cast_cxx(base);
//     init___non_rtti_object_cxx(base);
#if _MSVCR_VER >= 80
//     init_bad_alloc_cxx(base);
#endif
#if _MSVCR_VER >= 100
//     init_scheduler_resource_allocation_error_cxx(base);
//     init_improper_lock_cxx(base);
//     init_invalid_scheduler_policy_key_cxx(base);
//     init_invalid_scheduler_policy_value_cxx(base);
//     init_invalid_scheduler_policy_thread_specification_cxx(base);
//     init_improper_scheduler_attach_cxx(base);
//     init_improper_scheduler_detach_cxx(base);
#endif
#endif
}

#endif
