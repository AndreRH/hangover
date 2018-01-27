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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#else

#define MSVCRT__SW_INEXACT      0x00000001 /* inexact (precision) */
#define MSVCRT__SW_UNDERFLOW    0x00000002 /* underflow */
#define MSVCRT__SW_OVERFLOW     0x00000004 /* overflow */
#define MSVCRT__SW_ZERODIVIDE   0x00000008 /* zero divide */
#define MSVCRT__SW_INVALID      0x00000010 /* invalid */

#define MSVCRT__SW_UNEMULATED     0x00000040  /* unemulated instruction */
#define MSVCRT__SW_SQRTNEG        0x00000080  /* square root of a neg number */
#define MSVCRT__SW_STACKOVERFLOW  0x00000200  /* FP stack overflow */
#define MSVCRT__SW_STACKUNDERFLOW 0x00000400  /* FP stack underflow */

#define MSVCRT__SW_DENORMAL     0x00080000 /* denormal status bit */

/* fpclass constants */
#define MSVCRT__FPCLASS_SNAN 0x0001  /* Signaling "Not a Number" */
#define MSVCRT__FPCLASS_QNAN 0x0002  /* Quiet "Not a Number" */
#define MSVCRT__FPCLASS_NINF 0x0004  /* Negative Infinity */
#define MSVCRT__FPCLASS_NN   0x0008  /* Negative Normal */
#define MSVCRT__FPCLASS_ND   0x0010  /* Negative Denormal */
#define MSVCRT__FPCLASS_NZ   0x0020  /* Negative Zero */
#define MSVCRT__FPCLASS_PZ   0x0040  /* Positive Zero */
#define MSVCRT__FPCLASS_PD   0x0080  /* Positive Denormal */
#define MSVCRT__FPCLASS_PN   0x0100  /* Positive Normal */
#define MSVCRT__FPCLASS_PINF 0x0200  /* Positive Infinity */

#define MSVCRT__MCW_EM        0x0008001f
#define MSVCRT__MCW_IC        0x00040000
#define MSVCRT__MCW_RC        0x00000300
#define MSVCRT__MCW_PC        0x00030000
#define MSVCRT__MCW_DN        0x03000000

#define MSVCRT__EM_INVALID    0x00000010
#define MSVCRT__EM_DENORMAL   0x00080000
#define MSVCRT__EM_ZERODIVIDE 0x00000008
#define MSVCRT__EM_OVERFLOW   0x00000004
#define MSVCRT__EM_UNDERFLOW  0x00000002
#define MSVCRT__EM_INEXACT    0x00000001
#define MSVCRT__IC_AFFINE     0x00040000
#define MSVCRT__IC_PROJECTIVE 0x00000000
#define MSVCRT__RC_CHOP       0x00000300
#define MSVCRT__RC_UP         0x00000200
#define MSVCRT__RC_DOWN       0x00000100
#define MSVCRT__RC_NEAR       0x00000000
#define MSVCRT__PC_24         0x00020000
#define MSVCRT__PC_53         0x00010000
#define MSVCRT__PC_64         0x00000000
#define MSVCRT__DN_SAVE       0x00000000
#define MSVCRT__DN_FLUSH      0x01000000
#define MSVCRT__DN_FLUSH_OPERANDS_SAVE_RESULTS 0x02000000
#define MSVCRT__DN_SAVE_OPERANDS_FLUSH_RESULTS 0x03000000
#define MSVCRT__EM_AMBIGUOUS  0x80000000

/* fpclassify constants */
#define MSVCRT_FP_INFINITE   1
#define MSVCRT_FP_NAN        2
#define MSVCRT_FP_NORMAL    -1
#define MSVCRT_FP_SUBNORMAL -2
#define MSVCRT_FP_ZERO       0

#define MSVCRT_EINVAL  22
// MSVCRT__invalid_parameter(NULL, NULL, NULL, 0, 0)
#define MSVCRT_INVALID_PMT(x,err)   (*MSVCRT__errno() = (err), ExitProcess(0))
#define MSVCRT_CHECK_PMT_ERR(x,err) ((x) || (MSVCRT_INVALID_PMT( 0, (err) ), FALSE))
#define MSVCRT_CHECK_PMT(x)         MSVCRT_CHECK_PMT_ERR((x), MSVCRT_EINVAL)

#endif

struct qemu___setusermatherr
{
    struct qemu_syscall super;
    uint64_t func;
};


#ifdef QEMU_DLL_GUEST

typedef int (CDECL *MSVCRT_matherr_func)(void *);
static MSVCRT_matherr_func MSVCRT_default_matherr_func = NULL;

static int matherr_callback(void *exception)
{
    if (MSVCRT_default_matherr_func)
        return MSVCRT_default_matherr_func(exception);
    return 0;
}

void CDECL MSVCRT___setusermatherr(void *func)
{
    struct qemu___setusermatherr call;
    call.super.id = QEMU_SYSCALL_ID(CALL___SETUSERMATHERR);
    call.func = (ULONG_PTR)matherr_callback;
    MSVCRT_default_matherr_func = func;

    qemu_syscall(&call.super);
}

#else

static void *matherr_guest_func = 0;

static int host_matherr_callback(void *exception)
{
    WINE_TRACE("Calling guest function at %p.\n", matherr_guest_func);
    if (matherr_guest_func)
        return qemu_ops->qemu_execute(matherr_guest_func, QEMU_H2G(exception));

    WINE_ERR("Unhandled math error!\n");
    return 0;
}

void qemu___setusermatherr(struct qemu_syscall *call)
{
    struct qemu___setusermatherr *c = (struct qemu___setusermatherr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    if (!matherr_guest_func)
    {
        matherr_guest_func = QEMU_G2H(c->func);
        p___setusermatherr(host_matherr_callback);
    }
}

#endif

struct qemu__matherr
{
    struct qemu_syscall super;
    uint64_t exception;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__matherr(void *exception)
{
    struct qemu__matherr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MATHERR);
    call.exception = (ULONG_PTR)exception;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__matherr(struct qemu_syscall *call)
{
    struct qemu__matherr *c = (struct qemu__matherr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    if (!matherr_guest_func)
        WINE_FIXME("Make sure the exception struct makes sense for the host.\n");
    c->super.iret = p__matherr(QEMU_G2H(c->exception));
}

#endif

struct qemu__set_SSE2_enable
{
    struct qemu_syscall super;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__set_SSE2_enable(int flag)
{
    struct qemu__set_SSE2_enable call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_SSE2_ENABLE);
    call.flag = (ULONG_PTR)flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_SSE2_enable(struct qemu_syscall *call)
{
    struct qemu__set_SSE2_enable *c = (struct qemu__set_SSE2_enable *)(ULONG_PTR)call;
    WINE_TRACE("\n");

    /* As of the writing of this comment Wine ignores the flag. The function just returns FALSE
     * if PF_XMMI64_INSTRUCTIONS_AVAILABLE is not set. */
    c->super.iret = p__set_SSE2_enable(c->flag);

    if (c->flag && !c->super.iret)
        WINE_FIXME("Host msvcrt won't allow enabling SSE2\n");
}

#endif

struct qemu__set_FMA3_enable
{
    struct qemu_syscall super;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__set_FMA3_enable(int flag)
{
    struct qemu__set_FMA3_enable call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_FMA3_ENABLE);
    call.flag = (ULONG_PTR)flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_FMA3_enable(struct qemu_syscall *call)
{
    struct qemu__set_FMA3_enable *c = (struct qemu__set_FMA3_enable *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_FMA3_enable(c->flag);
}

#endif

struct qemu__chgsignf
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__chgsignf(float num)
{
    struct qemu__chgsignf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHGSIGNF);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__chgsignf(struct qemu_syscall *call)
{
    struct qemu__chgsignf *c = (struct qemu__chgsignf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__chgsignf(c->num);
}

#endif

struct qemu__copysignf
{
    struct qemu_syscall super;
    double num;
    double sign;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__copysignf(float num, float sign)
{
    struct qemu__copysignf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__COPYSIGNF);
    call.num = num;
    call.sign = sign;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__copysignf(struct qemu_syscall *call)
{
    struct qemu__copysignf *c = (struct qemu__copysignf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__copysignf(c->num, c->sign);
}

#endif

struct qemu__nextafterf
{
    struct qemu_syscall super;
    double num;
    double next;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__nextafterf(float num, float next)
{
    struct qemu__nextafterf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__NEXTAFTERF);
    call.num = num;
    call.next = next;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__nextafterf(struct qemu_syscall *call)
{
    struct qemu__nextafterf *c = (struct qemu__nextafterf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__nextafterf(c->num, c->next);
}

#endif

struct qemu__finitef
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__finitef(float num)
{
    struct qemu__finitef call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINITEF);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__finitef(struct qemu_syscall *call)
{
    struct qemu__finitef *c = (struct qemu__finitef *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__finitef(c->num);
}

#endif

struct qemu__isnanf
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__isnanf(float num)
{
    struct qemu__isnanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISNANF);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isnanf(struct qemu_syscall *call)
{
    struct qemu__isnanf *c = (struct qemu__isnanf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__isnanf(c->num);
}

#endif

struct qemu__logbf
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__logbf(float num)
{
    struct qemu__logbf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOGBF);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__logbf(struct qemu_syscall *call)
{
    struct qemu__logbf *c = (struct qemu__logbf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__logbf(c->num);
}

#endif

struct qemu_acosf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_acosf(float x)
{
    struct qemu_acosf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACOSF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_acosf(struct qemu_syscall *call)
{
    struct qemu_acosf *c = (struct qemu_acosf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_acosf(c->x);
}

#endif

struct qemu_asinf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_asinf(float x)
{
    struct qemu_asinf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASINF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_asinf(struct qemu_syscall *call)
{
    struct qemu_asinf *c = (struct qemu_asinf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_asinf(c->x);
}

#endif

struct qemu_atanf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_atanf(float x)
{
    struct qemu_atanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATANF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atanf(struct qemu_syscall *call)
{
    struct qemu_atanf *c = (struct qemu_atanf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_atanf(c->x);
}

#endif

struct qemu_atan2f
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_atan2f(float x, float y)
{
    struct qemu_atan2f call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATAN2F);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atan2f(struct qemu_syscall *call)
{
    struct qemu_atan2f *c = (struct qemu_atan2f *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_atan2f(c->x, c->y);
}

#endif

struct qemu_cosf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_cosf(float x)
{
    struct qemu_cosf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cosf(struct qemu_syscall *call)
{
    struct qemu_cosf *c = (struct qemu_cosf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_cosf(c->x);
}

#endif

struct qemu_coshf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_coshf(float x)
{
    struct qemu_coshf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSHF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_coshf(struct qemu_syscall *call)
{
    struct qemu_coshf *c = (struct qemu_coshf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_coshf(c->x);
}

#endif

struct qemu_expf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_expf(float x)
{
    struct qemu_expf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_expf(struct qemu_syscall *call)
{
    struct qemu_expf *c = (struct qemu_expf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_expf(c->x);
}

#endif

struct qemu_fmodf
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_fmodf(float x, float y)
{
    struct qemu_fmodf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FMODF);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fmodf(struct qemu_syscall *call)
{
    struct qemu_fmodf *c = (struct qemu_fmodf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_fmodf(c->x, c->y);
}

#endif

struct qemu_logf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_logf(float x)
{
    struct qemu_logf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOGF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_logf(struct qemu_syscall *call)
{
    struct qemu_logf *c = (struct qemu_logf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_logf(c->x);
}

#endif

struct qemu_log10f
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_log10f(float x)
{
    struct qemu_log10f call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG10F);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log10f(struct qemu_syscall *call)
{
    struct qemu_log10f *c = (struct qemu_log10f *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log10f(c->x);
}

#endif

struct qemu_powf
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_powf(float x, float y)
{
    struct qemu_powf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POWF);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_powf(struct qemu_syscall *call)
{
    struct qemu_powf *c = (struct qemu_powf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_powf(c->x, c->y);
}

#endif

struct qemu_sinf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_sinf(float x)
{
    struct qemu_sinf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SINF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sinf(struct qemu_syscall *call)
{
    struct qemu_sinf *c = (struct qemu_sinf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_sinf(c->x);
}

#endif

struct qemu_sinhf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_sinhf(float x)
{
    struct qemu_sinhf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SINHF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sinhf(struct qemu_syscall *call)
{
    struct qemu_sinhf *c = (struct qemu_sinhf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_sinhf(c->x);
}

#endif

struct qemu_sqrtf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_sqrtf(float x)
{
    struct qemu_sqrtf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SQRTF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sqrtf(struct qemu_syscall *call)
{
    struct qemu_sqrtf *c = (struct qemu_sqrtf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_sqrtf(c->x);
}

#endif

struct qemu_tanf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_tanf(float x)
{
    struct qemu_tanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TANF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_tanf(struct qemu_syscall *call)
{
    struct qemu_tanf *c = (struct qemu_tanf *)(ULONG_PTR)call;
    WINE_TRACE("Unverified!\n");
    c->super.dret = p_tanf(c->x);
}

#endif

struct qemu_tanhf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_tanhf(float x)
{
    struct qemu_tanhf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TANHF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_tanhf(struct qemu_syscall *call)
{
    struct qemu_tanhf *c = (struct qemu_tanhf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_tanhf(c->x);
}

#endif

struct qemu_ceilf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_ceilf(float x)
{
    struct qemu_ceilf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CEILF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_ceilf(struct qemu_syscall *call)
{
    struct qemu_ceilf *c = (struct qemu_ceilf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_ceilf(c->x);
}

#endif

struct qemu_fabsf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_fabsf(float x)
{
    struct qemu_fabsf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FABSF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fabsf(struct qemu_syscall *call)
{
    struct qemu_fabsf *c = (struct qemu_fabsf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_fabsf(c->x);
}

#endif

struct qemu_floorf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_floorf(float x)
{
    struct qemu_floorf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLOORF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_floorf(struct qemu_syscall *call)
{
    struct qemu_floorf *c = (struct qemu_floorf *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_floorf(c->x);
}

#endif

struct qemu_frexpf
{
    struct qemu_syscall super;
    double x;
    uint64_t exp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_frexpf(float x, int *exp)
{
    struct qemu_frexpf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREXPF);
    call.x = x;
    call.exp = (ULONG_PTR)exp;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_frexpf(struct qemu_syscall *call)
{
    struct qemu_frexpf *c = (struct qemu_frexpf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_frexpf(c->x, QEMU_G2H(c->exp));
}

#endif

struct qemu_modff
{
    struct qemu_syscall super;
    double x;
    uint64_t iptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_modff(float x, float *iptr)
{
    struct qemu_modff call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODFF);
    call.x = x;
    call.iptr = (ULONG_PTR)iptr;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_modff(struct qemu_syscall *call)
{
    struct qemu_modff *c = (struct qemu_modff *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_modff(c->x, QEMU_G2H(c->iptr));
}

#endif

struct qemu_acos
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_acos(double x)
{
    struct qemu_acos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACOS);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_acos(struct qemu_syscall *call)
{
    struct qemu_acos *c = (struct qemu_acos *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_acos(c->x);
}

#endif

struct qemu_asin
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_asin(double x)
{
    struct qemu_asin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASIN);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_asin(struct qemu_syscall *call)
{
    struct qemu_asin *c = (struct qemu_asin *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_asin(c->x);
}

#endif

struct qemu_atan
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_atan(double x)
{
    struct qemu_atan call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATAN);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atan(struct qemu_syscall *call)
{
    struct qemu_atan *c = (struct qemu_atan *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_atan(c->x);
}

#endif

struct qemu_atan2
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_atan2(double x, double y)
{
    struct qemu_atan2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATAN2);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atan2(struct qemu_syscall *call)
{
    struct qemu_atan2 *c = (struct qemu_atan2 *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_atan2(c->x, c->y);
}

#endif

struct qemu_cos
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_cos(double x)
{
    struct qemu_cos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COS);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cos(struct qemu_syscall *call)
{
    struct qemu_cos *c = (struct qemu_cos *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_cos(c->x);
}

#endif

struct qemu_cosh
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_cosh(double x)
{
    struct qemu_cosh call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSH);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cosh(struct qemu_syscall *call)
{
    struct qemu_cosh *c = (struct qemu_cosh *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_cosh(c->x);
}

#endif

struct qemu_exp
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_exp(double x)
{
    struct qemu_exp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXP);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_exp(struct qemu_syscall *call)
{
    struct qemu_exp *c = (struct qemu_exp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_exp(c->x);
}

#endif

struct qemu_fmod
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_fmod(double x, double y)
{
    struct qemu_fmod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FMOD);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fmod(struct qemu_syscall *call)
{
    struct qemu_fmod *c = (struct qemu_fmod *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_fmod(c->x, c->y);
}

#endif

struct qemu_log
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_log(double x)
{
    struct qemu_log call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log(struct qemu_syscall *call)
{
    struct qemu_log *c = (struct qemu_log *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_log(c->x);
}

#endif

struct qemu_log10
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_log10(double x)
{
    struct qemu_log10 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG10);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log10(struct qemu_syscall *call)
{
    struct qemu_log10 *c = (struct qemu_log10 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log10(c->x);
}

#endif

struct qemu_pow
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_pow(double x, double y)
{
    struct qemu_pow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POW);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_pow(struct qemu_syscall *call)
{
    struct qemu_pow *c = (struct qemu_pow *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_pow(c->x, c->y);
}

#endif

struct qemu_sin
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_sin(double x)
{
    struct qemu_sin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SIN);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sin(struct qemu_syscall *call)
{
    struct qemu_sin *c = (struct qemu_sin *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_sin(c->x);
}

#endif

struct qemu_sinh
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_sinh(double x)
{
    struct qemu_sinh call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SINH);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sinh(struct qemu_syscall *call)
{
    struct qemu_sinh *c = (struct qemu_sinh *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_sinh(c->x);
}

#endif

struct qemu_sqrt
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_sqrt(double x)
{
    struct qemu_sqrt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SQRT);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sqrt(struct qemu_syscall *call)
{
    struct qemu_sqrt *c = (struct qemu_sqrt *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_sqrt(c->x);
}

#endif

struct qemu_tan
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_tan(double x)
{
    struct qemu_tan call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TAN);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_tan(struct qemu_syscall *call)
{
    struct qemu_tan *c = (struct qemu_tan *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_tan(c->x);
}

#endif

struct qemu_tanh
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_tanh(double x)
{
    struct qemu_tanh call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TANH);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_tanh(struct qemu_syscall *call)
{
    struct qemu_tanh *c = (struct qemu_tanh *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_tanh(c->x);
}

#endif

struct qemu__ftol
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONGLONG CDECL MSVCRT__ftol(void)
{
    struct qemu__ftol call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTOL);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ftol(struct qemu_syscall *call)
{
    struct qemu__ftol *c = (struct qemu__ftol *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ftol();
}

#endif

struct qemu__fpclass
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__fpclass(double num)
{
    struct qemu__fpclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FPCLASS);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fpclass(struct qemu_syscall *call)
{
    struct qemu__fpclass *c = (struct qemu__fpclass *)(ULONG_PTR)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = p__fpclass(c->num);
}

#endif

struct qemu__rotl
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t shift;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL MSVCRT__rotl(unsigned int num, int shift)
{
    struct qemu__rotl call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ROTL);
    call.num = (ULONG_PTR)num;
    call.shift = (ULONG_PTR)shift;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__rotl(struct qemu_syscall *call)
{
    struct qemu__rotl *c = (struct qemu__rotl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__rotl(c->num, c->shift);
}

#endif

struct qemu__lrotl
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t shift;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI uint32_t CDECL MSVCRT__lrotl(uint32_t num, int shift)
{
    struct qemu__lrotl call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LROTL);
    call.num = (ULONG_PTR)num;
    call.shift = (ULONG_PTR)shift;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lrotl(struct qemu_syscall *call)
{
    struct qemu__lrotl *c = (struct qemu__lrotl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__lrotl(c->num, c->shift);
}

#endif

struct qemu__lrotr
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t shift;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI uint32_t CDECL MSVCRT__lrotr(uint32_t num, int shift)
{
    struct qemu__lrotr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LROTR);
    call.num = (ULONG_PTR)num;
    call.shift = (ULONG_PTR)shift;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lrotr(struct qemu_syscall *call)
{
    struct qemu__lrotr *c = (struct qemu__lrotr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__lrotr(c->num, c->shift);
}

#endif

struct qemu__rotr
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t shift;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL MSVCRT__rotr(unsigned int num, int shift)
{
    struct qemu__rotr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ROTR);
    call.num = (ULONG_PTR)num;
    call.shift = (ULONG_PTR)shift;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__rotr(struct qemu_syscall *call)
{
    struct qemu__rotr *c = (struct qemu__rotr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__rotr(c->num, c->shift);
}

#endif

struct qemu__rotl64
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t shift;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned __int64 CDECL _rotl64(unsigned __int64 num, int shift)
{
    struct qemu__rotl64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ROTL64);
    call.num = (ULONG_PTR)num;
    call.shift = (ULONG_PTR)shift;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__rotl64(struct qemu_syscall *call)
{
    struct qemu__rotl64 *c = (struct qemu__rotl64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__rotl64(c->num, c->shift);
}

#endif

struct qemu__rotr64
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t shift;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned __int64 CDECL _rotr64(unsigned __int64 num, int shift)
{
    struct qemu__rotr64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ROTR64);
    call.num = (ULONG_PTR)num;
    call.shift = (ULONG_PTR)shift;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__rotr64(struct qemu_syscall *call)
{
    struct qemu__rotr64 *c = (struct qemu__rotr64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__rotr64(c->num, c->shift);
}

#endif

struct qemu_abs
{
    struct qemu_syscall super;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_abs(int n)
{
    struct qemu_abs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ABS);
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_abs(struct qemu_syscall *call)
{
    struct qemu_abs *c = (struct qemu_abs *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_abs(c->n);
}

#endif

struct qemu_labs
{
    struct qemu_syscall super;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCRT_labs(int32_t n)
{
    struct qemu_labs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LABS);
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_labs(struct qemu_syscall *call)
{
    struct qemu_labs *c = (struct qemu_labs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_labs(c->n);
}

#endif

struct qemu_llabs
{
    struct qemu_syscall super;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCRT_llabs(int64_t n)
{
    struct qemu_llabs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLABS);
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llabs(struct qemu_syscall *call)
{
    struct qemu_llabs *c = (struct qemu_llabs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llabs(c->n);
}

#endif

struct qemu__abs64
{
    struct qemu_syscall super;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI __int64 CDECL _abs64(__int64 n)
{
    struct qemu__abs64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ABS64);
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__abs64(struct qemu_syscall *call)
{
    struct qemu__abs64 *c = (struct qemu__abs64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__abs64(c->n);
}

#endif

struct qemu__logb
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__logb(double num)
{
    struct qemu__logb call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOGB);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__logb(struct qemu_syscall *call)
{
    struct qemu__logb *c = (struct qemu__logb *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__logb(c->num);
}

#endif

struct qemu__hypot
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL _hypot(double x, double y)
{
    struct qemu__hypot call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HYPOT);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__hypot(struct qemu_syscall *call)
{
    struct qemu__hypot *c = (struct qemu__hypot *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__hypot(c->x, c->y);
}

#endif

struct qemu__hypotf
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__hypotf(float x, float y)
{
    struct qemu__hypotf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HYPOTF);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__hypotf(struct qemu_syscall *call)
{
    struct qemu__hypotf *c = (struct qemu__hypotf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__hypotf(c->x, c->y);
}

#endif

struct qemu_ceil
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_ceil(double x)
{
    struct qemu_ceil call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CEIL);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_ceil(struct qemu_syscall *call)
{
    struct qemu_ceil *c = (struct qemu_ceil *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_ceil(c->x);
}

#endif

struct qemu_floor
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_floor(double x)
{
    struct qemu_floor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLOOR);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_floor(struct qemu_syscall *call)
{
    struct qemu_floor *c = (struct qemu_floor *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_floor(c->x);
}

#endif

struct qemu_fabs
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_fabs(double x)
{
    struct qemu_fabs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FABS);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fabs(struct qemu_syscall *call)
{
    struct qemu_fabs *c = (struct qemu_fabs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_fabs(c->x);
}

#endif

struct qemu_frexp
{
    struct qemu_syscall super;
    double x;
    uint64_t exp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_frexp(double x, int *exp)
{
    struct qemu_frexp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREXP);
    call.x = x;
    call.exp = (ULONG_PTR)exp;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_frexp(struct qemu_syscall *call)
{
    struct qemu_frexp *c = (struct qemu_frexp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_frexp(c->x, QEMU_G2H(c->exp));
}

#endif

struct qemu_modf
{
    struct qemu_syscall super;
    double x;
    uint64_t iptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_modf(double x, double *iptr)
{
    struct qemu_modf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODF);
    call.x = x;
    call.iptr = (ULONG_PTR)iptr;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_modf(struct qemu_syscall *call)
{
    struct qemu_modf *c = (struct qemu_modf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_modf(c->x, QEMU_G2H(c->iptr));
}

#endif

struct qemu__statusfp2
{
    struct qemu_syscall super;
    uint64_t x86_sw;
    uint64_t sse2_sw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _statusfp2(unsigned int *x86_sw, unsigned int *sse2_sw)
{
    struct qemu__statusfp2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STATUSFP2);
    call.x86_sw = (ULONG_PTR)x86_sw;
    call.sse2_sw = (ULONG_PTR)sse2_sw;

    qemu_syscall(&call.super);
}

#else

void qemu__statusfp2(struct qemu_syscall *call)
{
    struct qemu__statusfp2 *c = (struct qemu__statusfp2 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__statusfp2(QEMU_G2H(c->x86_sw), QEMU_G2H(c->sse2_sw));
}

#endif

struct qemu__statusfp
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL _statusfp(void)
{
    struct qemu__statusfp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STATUSFP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__statusfp(struct qemu_syscall *call)
{
    struct qemu__statusfp *c = (struct qemu__statusfp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__statusfp();
}

#endif

struct qemu__clearfp
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL _clearfp(void)
{
    unsigned int flags = 0;
    unsigned long fpword;

    __asm__ __volatile__( "fnstsw %0; fnclex" : "=m" (fpword) );
    if (fpword & 0x1)  flags |= MSVCRT__SW_INVALID;
    if (fpword & 0x2)  flags |= MSVCRT__SW_DENORMAL;
    if (fpword & 0x4)  flags |= MSVCRT__SW_ZERODIVIDE;
    if (fpword & 0x8)  flags |= MSVCRT__SW_OVERFLOW;
    if (fpword & 0x10) flags |= MSVCRT__SW_UNDERFLOW;
    if (fpword & 0x20) flags |= MSVCRT__SW_INEXACT;

    __asm__ __volatile__( "stmxcsr %0" : "=m" (fpword) );
    if (fpword & 0x1)  flags |= MSVCRT__SW_INVALID;
    if (fpword & 0x2)  flags |= MSVCRT__SW_DENORMAL;
    if (fpword & 0x4)  flags |= MSVCRT__SW_ZERODIVIDE;
    if (fpword & 0x8)  flags |= MSVCRT__SW_OVERFLOW;
    if (fpword & 0x10) flags |= MSVCRT__SW_UNDERFLOW;
    if (fpword & 0x20) flags |= MSVCRT__SW_INEXACT;
    fpword &= ~0x3f;
    __asm__ __volatile__( "ldmxcsr %0" : : "m" (fpword) );
}

#else

void qemu__clearfp(struct qemu_syscall *call)
{
    struct qemu__clearfp *c = (struct qemu__clearfp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__clearfp();
}

#endif

struct qemu___fpecode
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int * CDECL __fpecode(void)
{
    struct qemu___fpecode call;
    call.super.id = QEMU_SYSCALL_ID(CALL___FPECODE);

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___fpecode(struct qemu_syscall *call)
{
    struct qemu___fpecode *c = (struct qemu___fpecode *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___fpecode());
}

#endif

struct qemu_ldexp
{
    struct qemu_syscall super;
    double num;
    uint64_t exp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_ldexp(double num, int32_t exp)
{
    struct qemu_ldexp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDEXP);
    call.num = num;
    call.exp = (ULONG_PTR)exp;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_ldexp(struct qemu_syscall *call)
{
    struct qemu_ldexp *c = (struct qemu_ldexp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_ldexp(c->num, c->exp);
}

#endif

struct qemu__cabs
{
    struct qemu_syscall super;
    double x, y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__cabs(struct MSVCRT__complex num)
{
    struct qemu__cabs call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CABS);
    call.x = num.x;
    call.y = num.y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__cabs(struct qemu_syscall *call)
{
    struct qemu__cabs *c = (struct qemu__cabs *)(ULONG_PTR)call;
    struct MSVCRT__complex num;
    WINE_FIXME("Unverified!\n");
    num.x = c->x;
    num.y = c->y;
    c->super.dret = p__cabs(num);
}

#endif

struct qemu__chgsign
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__chgsign(double num)
{
    struct qemu__chgsign call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHGSIGN);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__chgsign(struct qemu_syscall *call)
{
    struct qemu__chgsign *c = (struct qemu__chgsign *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__chgsign(c->num);
}

#endif

struct qemu___control87_2
{
    struct qemu_syscall super;
    uint64_t newval;
    uint64_t mask;
    uint64_t x86_cw;
    uint64_t sse2_cw;
};

#ifdef QEMU_DLL_GUEST

int CDECL __control87_2(unsigned int newval, unsigned int mask, unsigned int *x86_cw, unsigned int *sse2_cw)
{
    unsigned long fpword;
    unsigned int flags;

    if (x86_cw)
    {
        __asm__ __volatile__( "fstcw %0" : "=m" (fpword) );

        /* Convert into mask constants */
        flags = 0;
        if (fpword & 0x1)  flags |= MSVCRT__EM_INVALID;
        if (fpword & 0x2)  flags |= MSVCRT__EM_DENORMAL;
        if (fpword & 0x4)  flags |= MSVCRT__EM_ZERODIVIDE;
        if (fpword & 0x8)  flags |= MSVCRT__EM_OVERFLOW;
        if (fpword & 0x10) flags |= MSVCRT__EM_UNDERFLOW;
        if (fpword & 0x20) flags |= MSVCRT__EM_INEXACT;
        switch (fpword & 0xc00)
        {
        case 0xc00: flags |= MSVCRT__RC_UP|MSVCRT__RC_DOWN; break;
        case 0x800: flags |= MSVCRT__RC_UP; break;
        case 0x400: flags |= MSVCRT__RC_DOWN; break;
        }
        switch (fpword & 0x300)
        {
        case 0x0:   flags |= MSVCRT__PC_24; break;
        case 0x200: flags |= MSVCRT__PC_53; break;
        case 0x300: flags |= MSVCRT__PC_64; break;
        }
        if (fpword & 0x1000) flags |= MSVCRT__IC_AFFINE;

        if (mask)
        {
            flags = (flags & ~mask) | (newval & mask);

            /* Convert (masked) value back to fp word */
            fpword = 0;
            if (flags & MSVCRT__EM_INVALID)    fpword |= 0x1;
            if (flags & MSVCRT__EM_DENORMAL)   fpword |= 0x2;
            if (flags & MSVCRT__EM_ZERODIVIDE) fpword |= 0x4;
            if (flags & MSVCRT__EM_OVERFLOW)   fpword |= 0x8;
            if (flags & MSVCRT__EM_UNDERFLOW)  fpword |= 0x10;
            if (flags & MSVCRT__EM_INEXACT)    fpword |= 0x20;
            switch (flags & MSVCRT__MCW_RC)
            {
            case MSVCRT__RC_UP|MSVCRT__RC_DOWN: fpword |= 0xc00; break;
            case MSVCRT__RC_UP:                 fpword |= 0x800; break;
            case MSVCRT__RC_DOWN:               fpword |= 0x400; break;
            }
            switch (flags & MSVCRT__MCW_PC)
            {
            case MSVCRT__PC_64: fpword |= 0x300; break;
            case MSVCRT__PC_53: fpword |= 0x200; break;
            case MSVCRT__PC_24: fpword |= 0x0; break;
            }
            if (flags & MSVCRT__IC_AFFINE) fpword |= 0x1000;

            __asm__ __volatile__( "fldcw %0" : : "m" (fpword) );
        }
        *x86_cw = flags;
    }

    if (!sse2_cw) return 1;

    if (1)
    {
        __asm__ __volatile__( "stmxcsr %0" : "=m" (fpword) );

        /* Convert into mask constants */
        flags = 0;
        if (fpword & 0x80)   flags |= MSVCRT__EM_INVALID;
        if (fpword & 0x100)  flags |= MSVCRT__EM_DENORMAL;
        if (fpword & 0x200)  flags |= MSVCRT__EM_ZERODIVIDE;
        if (fpword & 0x400)  flags |= MSVCRT__EM_OVERFLOW;
        if (fpword & 0x800)  flags |= MSVCRT__EM_UNDERFLOW;
        if (fpword & 0x1000) flags |= MSVCRT__EM_INEXACT;
        switch (fpword & 0x6000)
        {
        case 0x6000: flags |= MSVCRT__RC_UP|MSVCRT__RC_DOWN; break;
        case 0x4000: flags |= MSVCRT__RC_UP; break;
        case 0x2000: flags |= MSVCRT__RC_DOWN; break;
        }
        switch (fpword & 0x8040)
        {
        case 0x0040: flags |= MSVCRT__DN_FLUSH_OPERANDS_SAVE_RESULTS; break;
        case 0x8000: flags |= MSVCRT__DN_SAVE_OPERANDS_FLUSH_RESULTS; break;
        case 0x8040: flags |= MSVCRT__DN_FLUSH; break;
        }

        if (mask)
        {
            flags = (flags & ~mask) | (newval & mask);

            /* Convert (masked) value back to fp word */
            fpword = 0;
            if (flags & MSVCRT__EM_INVALID)    fpword |= 0x80;
            if (flags & MSVCRT__EM_DENORMAL)   fpword |= 0x100;
            if (flags & MSVCRT__EM_ZERODIVIDE) fpword |= 0x200;
            if (flags & MSVCRT__EM_OVERFLOW)   fpword |= 0x400;
            if (flags & MSVCRT__EM_UNDERFLOW)  fpword |= 0x800;
            if (flags & MSVCRT__EM_INEXACT)    fpword |= 0x1000;
            switch (flags & MSVCRT__MCW_RC)
            {
            case MSVCRT__RC_UP|MSVCRT__RC_DOWN: fpword |= 0x6000; break;
            case MSVCRT__RC_UP:                 fpword |= 0x4000; break;
            case MSVCRT__RC_DOWN:               fpword |= 0x2000; break;
            }
            switch (flags & MSVCRT__MCW_DN)
            {
            case MSVCRT__DN_FLUSH_OPERANDS_SAVE_RESULTS: fpword |= 0x0040; break;
            case MSVCRT__DN_SAVE_OPERANDS_FLUSH_RESULTS: fpword |= 0x8000; break;
            case MSVCRT__DN_FLUSH:                       fpword |= 0x8040; break;
            }
            __asm__ __volatile__( "ldmxcsr %0" : : "m" (fpword) );
        }
        *sse2_cw = flags;
    }
    else *sse2_cw = 0;

    return 1;
}

#else

void qemu___control87_2(struct qemu_syscall *call)
{
    struct qemu___control87_2 *c = (struct qemu___control87_2 *)(ULONG_PTR)call;
    WINE_WARN("Stub!\n");
    c->super.iret = 0;
}

#endif

struct qemu__control87
{
    struct qemu_syscall super;
    uint64_t newval;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _control87(unsigned int newval, unsigned int mask)
{
    unsigned int x86_cw, sse2_cw;

    __control87_2( newval, mask, &x86_cw, &sse2_cw );

    if ((x86_cw ^ sse2_cw) & (MSVCRT__MCW_EM | MSVCRT__MCW_RC)) x86_cw |= MSVCRT__EM_AMBIGUOUS;
    return x86_cw;
}

#else

void qemu__control87(struct qemu_syscall *call)
{
    struct qemu__control87 *c = (struct qemu__control87 *)(ULONG_PTR)call;
    WINE_WARN("Stub\n");
    c->super.iret = 0;
}

#endif

struct qemu__controlfp
{
    struct qemu_syscall super;
    uint64_t newval;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _controlfp(unsigned int newval, unsigned int mask)
{
    return _control87( newval, mask & ~MSVCRT__EM_DENORMAL );
}

#else

void qemu__controlfp(struct qemu_syscall *call)
{
    struct qemu__controlfp *c = (struct qemu__controlfp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__controlfp(c->newval, c->mask);
}

#endif

struct qemu__set_controlfp
{
    struct qemu_syscall super;
    uint64_t newval;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _set_controlfp(unsigned int newval, unsigned int mask)
{
    struct qemu__set_controlfp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_CONTROLFP);
    call.newval = (ULONG_PTR)newval;
    call.mask = (ULONG_PTR)mask;

    qemu_syscall(&call.super);
}

#else

void qemu__set_controlfp(struct qemu_syscall *call)
{
    struct qemu__set_controlfp *c = (struct qemu__set_controlfp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__set_controlfp(c->newval, c->mask);
}

#endif

struct qemu__controlfp_s
{
    struct qemu_syscall super;
    uint64_t cur;
    uint64_t newval;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _controlfp_s(unsigned int *cur, unsigned int newval, unsigned int mask)
{
    static const unsigned int all_flags = (MSVCRT__MCW_EM | MSVCRT__MCW_IC | MSVCRT__MCW_RC |
                                           MSVCRT__MCW_PC | MSVCRT__MCW_DN);
    unsigned int val;

    if (!MSVCRT_CHECK_PMT( !(newval & mask & ~all_flags) ))
    {
        if (cur) *cur = _controlfp( 0, 0 );  /* retrieve it anyway */
        return MSVCRT_EINVAL;
    }
    val = _controlfp( newval, mask );
    if (cur) *cur = val;
    return 0;
}

#else

void qemu__controlfp_s(struct qemu_syscall *call)
{
    struct qemu__controlfp_s *c = (struct qemu__controlfp_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__controlfp_s(QEMU_G2H(c->cur), c->newval, c->mask);
}

#endif

struct qemu_fegetenv
{
    struct qemu_syscall super;
    uint64_t env;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_fegetenv(MSVCRT_fenv_t *env)
{
    struct qemu_fegetenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FEGETENV);
    call.env = (ULONG_PTR)env;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fegetenv(struct qemu_syscall *call)
{
    struct qemu_fegetenv *c = (struct qemu_fegetenv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fegetenv(QEMU_G2H(c->env));
}

#endif

struct qemu___fpe_flt_rounds
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __fpe_flt_rounds(void)
{
    struct qemu___fpe_flt_rounds call;
    call.super.id = QEMU_SYSCALL_ID(CALL___FPE_FLT_ROUNDS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___fpe_flt_rounds(struct qemu_syscall *call)
{
    struct qemu___fpe_flt_rounds *c = (struct qemu___fpe_flt_rounds *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___fpe_flt_rounds();
}

#endif

struct qemu_fegetround
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_fegetround(void)
{
    struct qemu_fegetround call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FEGETROUND);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fegetround(struct qemu_syscall *call)
{
    struct qemu_fegetround *c = (struct qemu_fegetround *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fegetround();
}

#endif

struct qemu_fesetround
{
    struct qemu_syscall super;
    uint64_t round_mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_fesetround(int round_mode)
{
    struct qemu_fesetround call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FESETROUND);
    call.round_mode = (ULONG_PTR)round_mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fesetround(struct qemu_syscall *call)
{
    struct qemu_fesetround *c = (struct qemu_fesetround *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fesetround(c->round_mode);
}

#endif

struct qemu__copysign
{
    struct qemu_syscall super;
    double num;
    double sign;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__copysign(double num, double sign)
{
    struct qemu__copysign call;
    call.super.id = QEMU_SYSCALL_ID(CALL__COPYSIGN);
    call.num = num;
    call.sign = sign;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__copysign(struct qemu_syscall *call)
{
    struct qemu__copysign *c = (struct qemu__copysign *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__copysign(c->num, c->sign);
}

#endif

struct qemu__finite
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__finite(double num)
{
    struct qemu__finite call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FINITE);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__finite(struct qemu_syscall *call)
{
    struct qemu__finite *c = (struct qemu__finite *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__finite(c->num);
}

#endif

struct qemu__fpreset
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _fpreset(void)
{
    struct qemu__fpreset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FPRESET);

    qemu_syscall(&call.super);
}

#else

void qemu__fpreset(struct qemu_syscall *call)
{
    struct qemu__fpreset *c = (struct qemu__fpreset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__fpreset();
}

#endif

struct qemu_fesetenv
{
    struct qemu_syscall super;
    uint64_t env;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_fesetenv(const MSVCRT_fenv_t *env)
{
    struct qemu_fesetenv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FESETENV);
    call.env = (ULONG_PTR)env;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fesetenv(struct qemu_syscall *call)
{
    struct qemu_fesetenv *c = (struct qemu_fesetenv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fesetenv(QEMU_G2H(c->env));
}

#endif

struct qemu__isnan
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__isnan(double num)
{
    struct qemu__isnan call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISNAN);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isnan(struct qemu_syscall *call)
{
    struct qemu__isnan *c = (struct qemu__isnan *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__isnan(c->num);
}

#endif

struct qemu__j0
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__j0(double num)
{
    struct qemu__j0 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__J0);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__j0(struct qemu_syscall *call)
{
    struct qemu__j0 *c = (struct qemu__j0 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__j0(c->num);
}

#endif

struct qemu__j1
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__j1(double num)
{
    struct qemu__j1 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__J1);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__j1(struct qemu_syscall *call)
{
    struct qemu__j1 *c = (struct qemu__j1 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__j1(c->num);
}

#endif

struct qemu__jn
{
    struct qemu_syscall super;
    uint64_t n;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__jn(int n, double num)
{
    struct qemu__jn call;
    call.super.id = QEMU_SYSCALL_ID(CALL__JN);
    call.n = (ULONG_PTR)n;
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__jn(struct qemu_syscall *call)
{
    struct qemu__jn *c = (struct qemu__jn *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__jn(c->n, c->num);
}

#endif

struct qemu__y0
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__y0(double num)
{
    struct qemu__y0 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__Y0);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__y0(struct qemu_syscall *call)
{
    struct qemu__y0 *c = (struct qemu__y0 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__y0(c->num);
}

#endif

struct qemu__y1
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__y1(double num)
{
    struct qemu__y1 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__Y1);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__y1(struct qemu_syscall *call)
{
    struct qemu__y1 *c = (struct qemu__y1 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__y1(c->num);
}

#endif

struct qemu__yn
{
    struct qemu_syscall super;
    uint64_t order;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__yn(int order, double num)
{
    struct qemu__yn call;
    call.super.id = QEMU_SYSCALL_ID(CALL__YN);
    call.order = (ULONG_PTR)order;
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__yn(struct qemu_syscall *call)
{
    struct qemu__yn *c = (struct qemu__yn *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__yn(c->order, c->num);
}

#endif

struct qemu_nearbyint
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_nearbyint(double num)
{
    struct qemu_nearbyint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NEARBYINT);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_nearbyint(struct qemu_syscall *call)
{
    struct qemu_nearbyint *c = (struct qemu_nearbyint *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_nearbyint(c->num);
}

#endif

struct qemu_nearbyintf
{
    struct qemu_syscall super;
    double num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_nearbyintf(float num)
{
    struct qemu_nearbyintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NEARBYINTF);
    call.num = num;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_nearbyintf(struct qemu_syscall *call)
{
    struct qemu_nearbyintf *c = (struct qemu_nearbyintf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_nearbyintf(c->num);
}

#endif

struct qemu__nextafter
{
    struct qemu_syscall super;
    double num;
    double next;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__nextafter(double num, double next)
{
    struct qemu__nextafter call;
    call.super.id = QEMU_SYSCALL_ID(CALL__NEXTAFTER);
    call.num = num;
    call.next = next;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__nextafter(struct qemu_syscall *call)
{
    struct qemu__nextafter *c = (struct qemu__nextafter *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__nextafter(c->num, c->next);
}

#endif

struct qemu__ecvt
{
    struct qemu_syscall super;
    double number;
    uint64_t ndigits;
    uint64_t decpt;
    uint64_t sign;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT__ecvt(double number, int ndigits, int *decpt, int *sign)
{
    struct qemu__ecvt call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ECVT);
    call.number = number;
    call.ndigits = (ULONG_PTR)ndigits;
    call.decpt = (ULONG_PTR)decpt;
    call.sign = (ULONG_PTR)sign;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ecvt(struct qemu_syscall *call)
{
    struct qemu__ecvt *c = (struct qemu__ecvt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__ecvt(c->number, c->ndigits, QEMU_G2H(c->decpt), QEMU_G2H(c->sign)));
}

#endif

struct qemu__ecvt_s
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t length;
    double number;
    uint64_t ndigits;
    uint64_t decpt;
    uint64_t sign;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__ecvt_s(char *buffer, size_t length, double number, int ndigits, int *decpt, int *sign)
{
    struct qemu__ecvt_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ECVT_S);
    call.buffer = (ULONG_PTR)buffer;
    call.length = length;
    call.number = number;
    call.ndigits = ndigits;
    call.decpt = (ULONG_PTR)decpt;
    call.sign = (ULONG_PTR)sign;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ecvt_s(struct qemu_syscall *call)
{
    struct qemu__ecvt_s *c = (struct qemu__ecvt_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ecvt_s(QEMU_G2H(c->buffer), c->length, c->number, c->ndigits, QEMU_G2H(c->decpt), QEMU_G2H(c->sign));
}

#endif

struct qemu__fcvt
{
    struct qemu_syscall super;
    double number;
    uint64_t ndigits;
    uint64_t decpt;
    uint64_t sign;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT__fcvt(double number, int ndigits, int *decpt, int *sign)
{
    struct qemu__fcvt call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FCVT);
    call.number = number;
    call.ndigits = ndigits;
    call.decpt = (ULONG_PTR)decpt;
    call.sign = (ULONG_PTR)sign;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__fcvt(struct qemu_syscall *call)
{
    struct qemu__fcvt *c = (struct qemu__fcvt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__fcvt(c->number, c->ndigits, QEMU_G2H(c->decpt), QEMU_G2H(c->sign)));
}

#endif

struct qemu__fcvt_s
{
    struct qemu_syscall super;
    uint64_t outbuffer;
    uint64_t size;
    double number;
    uint64_t ndigits;
    uint64_t decpt;
    uint64_t sign;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__fcvt_s(char* outbuffer, size_t size, double number, int ndigits, int *decpt, int *sign)
{
    struct qemu__fcvt_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FCVT_S);
    call.outbuffer = (ULONG_PTR)outbuffer;
    call.size = size;
    call.number = number;
    call.ndigits = ndigits;
    call.decpt = (ULONG_PTR)decpt;
    call.sign = (ULONG_PTR)sign;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fcvt_s(struct qemu_syscall *call)
{
    struct qemu__fcvt_s *c = (struct qemu__fcvt_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fcvt_s(QEMU_G2H(c->outbuffer), c->size, c->number, c->ndigits, QEMU_G2H(c->decpt), QEMU_G2H(c->sign));
}

#endif

struct qemu__gcvt
{
    struct qemu_syscall super;
    uint64_t number;
    uint64_t ndigit;
    uint64_t buff;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT__gcvt(double number, int ndigit, char *buff)
{
    struct qemu__gcvt call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GCVT);
    call.number = (ULONG_PTR)number;
    call.ndigit = (ULONG_PTR)ndigit;
    call.buff = (ULONG_PTR)buff;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__gcvt(struct qemu_syscall *call)
{
    struct qemu__gcvt *c = (struct qemu__gcvt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__gcvt(c->number, c->ndigit, QEMU_G2H(c->buff)));
}

#endif

struct qemu__gcvt_s
{
    struct qemu_syscall super;
    uint64_t buff;
    uint64_t size;
    uint64_t number;
    uint64_t digits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__gcvt_s(char *buff, size_t size, double number, int digits)
{
    struct qemu__gcvt_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GCVT_S);
    call.buff = (ULONG_PTR)buff;
    call.size = (ULONG_PTR)size;
    call.number = (ULONG_PTR)number;
    call.digits = (ULONG_PTR)digits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__gcvt_s(struct qemu_syscall *call)
{
    struct qemu__gcvt_s *c = (struct qemu__gcvt_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__gcvt_s(QEMU_G2H(c->buff), c->size, c->number, c->digits);
}

#endif

struct qemu_div
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t denom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned __int64 CDECL MSVCRT_div(int num, int denom)
{
    struct qemu_div call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIV);
    call.num = (ULONG_PTR)num;
    call.denom = (ULONG_PTR)denom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_div(struct qemu_syscall *call)
{
    struct qemu_div *c = (struct qemu_div *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_div(c->num, c->denom);
}

#endif

struct qemu_ldiv
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t denom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned __int64 CDECL MSVCRT_ldiv(int32_t num, int32_t denom)
{
    struct qemu_ldiv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDIV);
    call.num = (ULONG_PTR)num;
    call.denom = (ULONG_PTR)denom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ldiv(struct qemu_syscall *call)
{
    struct qemu_ldiv *c = (struct qemu_ldiv *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ldiv(c->num, c->denom);
}

#endif

#ifdef QEMU_DLL_GUEST
int MSVCRT__adjust_fdiv = 0;
#endif

struct qemu___libm_sse2_acos
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_acos(void)
{
    struct qemu___libm_sse2_acos call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ACOS);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_acos(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_acos *c = (struct qemu___libm_sse2_acos *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_acos();
}

#endif

struct qemu___libm_sse2_acosf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_acosf(void)
{
    struct qemu___libm_sse2_acosf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ACOSF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_acosf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_acosf *c = (struct qemu___libm_sse2_acosf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_acosf();
}

#endif

struct qemu___libm_sse2_asin
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_asin(void)
{
    struct qemu___libm_sse2_asin call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ASIN);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_asin(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_asin *c = (struct qemu___libm_sse2_asin *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_asin();
}

#endif

struct qemu___libm_sse2_asinf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_asinf(void)
{
    struct qemu___libm_sse2_asinf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ASINF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_asinf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_asinf *c = (struct qemu___libm_sse2_asinf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_asinf();
}

#endif

struct qemu___libm_sse2_atan
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_atan(void)
{
    struct qemu___libm_sse2_atan call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ATAN);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_atan(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_atan *c = (struct qemu___libm_sse2_atan *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_atan();
}

#endif

struct qemu___libm_sse2_atan2
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_atan2(void)
{
    struct qemu___libm_sse2_atan2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ATAN2);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_atan2(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_atan2 *c = (struct qemu___libm_sse2_atan2 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_atan2();
}

#endif

struct qemu___libm_sse2_atanf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_atanf(void)
{
    struct qemu___libm_sse2_atanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_ATANF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_atanf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_atanf *c = (struct qemu___libm_sse2_atanf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_atanf();
}

#endif

struct qemu___libm_sse2_cos
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_cos(void)
{
    struct qemu___libm_sse2_cos call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_COS);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_cos(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_cos *c = (struct qemu___libm_sse2_cos *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_cos();
}

#endif

struct qemu___libm_sse2_cosf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_cosf(void)
{
    struct qemu___libm_sse2_cosf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_COSF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_cosf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_cosf *c = (struct qemu___libm_sse2_cosf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_cosf();
}

#endif

struct qemu___libm_sse2_exp
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_exp(void)
{
    struct qemu___libm_sse2_exp call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_EXP);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_exp(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_exp *c = (struct qemu___libm_sse2_exp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_exp();
}

#endif

struct qemu___libm_sse2_expf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_expf(void)
{
    struct qemu___libm_sse2_expf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_EXPF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_expf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_expf *c = (struct qemu___libm_sse2_expf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_expf();
}

#endif

struct qemu___libm_sse2_log
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_log(void)
{
    struct qemu___libm_sse2_log call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_LOG);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_log(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_log *c = (struct qemu___libm_sse2_log *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_log();
}

#endif

struct qemu___libm_sse2_log10
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_log10(void)
{
    struct qemu___libm_sse2_log10 call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_LOG10);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_log10(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_log10 *c = (struct qemu___libm_sse2_log10 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_log10();
}

#endif

struct qemu___libm_sse2_log10f
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_log10f(void)
{
    struct qemu___libm_sse2_log10f call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_LOG10F);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_log10f(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_log10f *c = (struct qemu___libm_sse2_log10f *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_log10f();
}

#endif

struct qemu___libm_sse2_logf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_logf(void)
{
    struct qemu___libm_sse2_logf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_LOGF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_logf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_logf *c = (struct qemu___libm_sse2_logf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_logf();
}

#endif

struct qemu___libm_sse2_pow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_pow(void)
{
    struct qemu___libm_sse2_pow call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_POW);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_pow(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_pow *c = (struct qemu___libm_sse2_pow *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_pow();
}

#endif

struct qemu___libm_sse2_powf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_powf(void)
{
    struct qemu___libm_sse2_powf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_POWF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_powf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_powf *c = (struct qemu___libm_sse2_powf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_powf();
}

#endif

struct qemu___libm_sse2_sin
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_sin(void)
{
    struct qemu___libm_sse2_sin call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_SIN);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_sin(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_sin *c = (struct qemu___libm_sse2_sin *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_sin();
}

#endif

struct qemu___libm_sse2_sinf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_sinf(void)
{
    struct qemu___libm_sse2_sinf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_SINF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_sinf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_sinf *c = (struct qemu___libm_sse2_sinf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_sinf();
}

#endif

struct qemu___libm_sse2_tan
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_tan(void)
{
    struct qemu___libm_sse2_tan call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_TAN);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_tan(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_tan *c = (struct qemu___libm_sse2_tan *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_tan();
}

#endif

struct qemu___libm_sse2_tanf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_tanf(void)
{
    struct qemu___libm_sse2_tanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_TANF);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_tanf(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_tanf *c = (struct qemu___libm_sse2_tanf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_tanf();
}

#endif

struct qemu___libm_sse2_sqrt_precise
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT___libm_sse2_sqrt_precise(void)
{
    struct qemu___libm_sse2_sqrt_precise call;
    call.super.id = QEMU_SYSCALL_ID(CALL___LIBM_SSE2_SQRT_PRECISE);

    qemu_syscall(&call.super);
}

#else

void qemu___libm_sse2_sqrt_precise(struct qemu_syscall *call)
{
    struct qemu___libm_sse2_sqrt_precise *c = (struct qemu___libm_sse2_sqrt_precise *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p___libm_sse2_sqrt_precise();
}

#endif

struct qemu_cbrt
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_cbrt(double x)
{
    struct qemu_cbrt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CBRT);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cbrt(struct qemu_syscall *call)
{
    struct qemu_cbrt *c = (struct qemu_cbrt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_cbrt(c->x);
}

#endif

struct qemu_cbrtf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_cbrtf(float x)
{
    struct qemu_cbrtf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CBRTF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cbrtf(struct qemu_syscall *call)
{
    struct qemu_cbrtf *c = (struct qemu_cbrtf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_cbrtf(c->x);
}

#endif

struct qemu_cbrtl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_cbrtl(double x)
{
    struct qemu_cbrtl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CBRTL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cbrtl(struct qemu_syscall *call)
{
    struct qemu_cbrtl *c = (struct qemu_cbrtl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_cbrtl(c->x);
}

#endif

struct qemu_exp2
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_exp2(double x)
{
    struct qemu_exp2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXP2);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_exp2(struct qemu_syscall *call)
{
    struct qemu_exp2 *c = (struct qemu_exp2 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_exp2(c->x);
}

#endif

struct qemu_exp2f
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_exp2f(float x)
{
    struct qemu_exp2f call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXP2F);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_exp2f(struct qemu_syscall *call)
{
    struct qemu_exp2f *c = (struct qemu_exp2f *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_exp2f(c->x);
}

#endif

struct qemu_exp2l
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_exp2l(double x)
{
    struct qemu_exp2l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXP2L);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_exp2l(struct qemu_syscall *call)
{
    struct qemu_exp2l *c = (struct qemu_exp2l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_exp2l(c->x);
}

#endif

struct qemu_expm1
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_expm1(double x)
{
    struct qemu_expm1 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPM1);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_expm1(struct qemu_syscall *call)
{
    struct qemu_expm1 *c = (struct qemu_expm1 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_expm1(c->x);
}

#endif

struct qemu_expm1f
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_expm1f(float x)
{
    struct qemu_expm1f call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPM1F);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_expm1f(struct qemu_syscall *call)
{
    struct qemu_expm1f *c = (struct qemu_expm1f *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_expm1f(c->x);
}

#endif

struct qemu_expm1l
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_expm1l(double x)
{
    struct qemu_expm1l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPM1L);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_expm1l(struct qemu_syscall *call)
{
    struct qemu_expm1l *c = (struct qemu_expm1l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_expm1l(c->x);
}

#endif

struct qemu_log1p
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_log1p(double x)
{
    struct qemu_log1p call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG1P);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log1p(struct qemu_syscall *call)
{
    struct qemu_log1p *c = (struct qemu_log1p *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log1p(c->x);
}

#endif

struct qemu_log1pf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_log1pf(float x)
{
    struct qemu_log1pf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG1PF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log1pf(struct qemu_syscall *call)
{
    struct qemu_log1pf *c = (struct qemu_log1pf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log1pf(c->x);
}

#endif

struct qemu_log1pl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_log1pl(double x)
{
    struct qemu_log1pl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG1PL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log1pl(struct qemu_syscall *call)
{
    struct qemu_log1pl *c = (struct qemu_log1pl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log1pl(c->x);
}

#endif

struct qemu_log2
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_log2(double x)
{
    struct qemu_log2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG2);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log2(struct qemu_syscall *call)
{
    struct qemu_log2 *c = (struct qemu_log2 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log2(c->x);
}

#endif

struct qemu_log2f
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_log2f(float x)
{
    struct qemu_log2f call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG2F);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log2f(struct qemu_syscall *call)
{
    struct qemu_log2f *c = (struct qemu_log2f *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log2f(c->x);
}

#endif

struct qemu_log2l
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_log2l(double x)
{
    struct qemu_log2l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOG2L);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_log2l(struct qemu_syscall *call)
{
    struct qemu_log2l *c = (struct qemu_log2l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_log2l(c->x);
}

#endif

struct qemu_rint
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_rint(double x)
{
    struct qemu_rint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RINT);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_rint(struct qemu_syscall *call)
{
    struct qemu_rint *c = (struct qemu_rint *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_rint(c->x);
}

#endif

struct qemu_rintf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_rintf(float x)
{
    struct qemu_rintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RINTF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_rintf(struct qemu_syscall *call)
{
    struct qemu_rintf *c = (struct qemu_rintf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_rintf(c->x);
}

#endif

struct qemu_rintl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_rintl(double x)
{
    struct qemu_rintl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RINTL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_rintl(struct qemu_syscall *call)
{
    struct qemu_rintl *c = (struct qemu_rintl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_rintl(c->x);
}

#endif

struct qemu_lrint
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCR120_lrint(double x)
{
    struct qemu_lrint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LRINT);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lrint(struct qemu_syscall *call)
{
    struct qemu_lrint *c = (struct qemu_lrint *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_lrint(c->x);
}

#endif

struct qemu_lrintf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCR120_lrintf(float x)
{
    struct qemu_lrintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LRINTF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lrintf(struct qemu_syscall *call)
{
    struct qemu_lrintf *c = (struct qemu_lrintf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_lrintf(c->x);
}

#endif

struct qemu_lrintl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCR120_lrintl(double x)
{
    struct qemu_lrintl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LRINTL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lrintl(struct qemu_syscall *call)
{
    struct qemu_lrintl *c = (struct qemu_lrintl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_lrintl(c->x);
}

#endif

struct qemu_llrint
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCR120_llrint(double x)
{
    struct qemu_llrint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLRINT);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llrint(struct qemu_syscall *call)
{
    struct qemu_llrint *c = (struct qemu_llrint *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llrint(c->x);
}

#endif

struct qemu_llrintf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCR120_llrintf(float x)
{
    struct qemu_llrintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLRINTF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llrintf(struct qemu_syscall *call)
{
    struct qemu_llrintf *c = (struct qemu_llrintf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llrintf(c->x);
}

#endif

struct qemu_llrintl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCR120_llrintl(double x)
{
    struct qemu_llrintl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLRINTL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llrintl(struct qemu_syscall *call)
{
    struct qemu_llrintl *c = (struct qemu_llrintl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llrintl(c->x);
}

#endif

struct qemu_round
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_round(double x)
{
    struct qemu_round call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ROUND);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_round(struct qemu_syscall *call)
{
    struct qemu_round *c = (struct qemu_round *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_round(c->x);
}

#endif

struct qemu_roundf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_roundf(float x)
{
    struct qemu_roundf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ROUNDF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_roundf(struct qemu_syscall *call)
{
    struct qemu_roundf *c = (struct qemu_roundf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_roundf(c->x);
}

#endif

struct qemu_roundl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_roundl(double x)
{
    struct qemu_roundl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ROUNDL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_roundl(struct qemu_syscall *call)
{
    struct qemu_roundl *c = (struct qemu_roundl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_roundl(c->x);
}

#endif

struct qemu_lround
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCR120_lround(double x)
{
    struct qemu_lround call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LROUND);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lround(struct qemu_syscall *call)
{
    struct qemu_lround *c = (struct qemu_lround *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_lround(c->x);
}

#endif

struct qemu_lroundf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCR120_lroundf(float x)
{
    struct qemu_lroundf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LROUNDF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lroundf(struct qemu_syscall *call)
{
    struct qemu_lroundf *c = (struct qemu_lroundf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_lroundf(c->x);
}

#endif

struct qemu_lroundl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int32_t CDECL MSVCR120_lroundl(double x)
{
    struct qemu_lroundl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LROUNDL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lroundl(struct qemu_syscall *call)
{
    struct qemu_lroundl *c = (struct qemu_lroundl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_lroundl(c->x);
}

#endif

struct qemu_llround
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCR120_llround(double x)
{
    struct qemu_llround call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLROUND);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llround(struct qemu_syscall *call)
{
    struct qemu_llround *c = (struct qemu_llround *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llround(c->x);
}

#endif

struct qemu_llroundf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCR120_llroundf(float x)
{
    struct qemu_llroundf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLROUNDF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llroundf(struct qemu_syscall *call)
{
    struct qemu_llroundf *c = (struct qemu_llroundf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llroundf(c->x);
}

#endif

struct qemu_llroundl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int64_t CDECL MSVCR120_llroundl(double x)
{
    struct qemu_llroundl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LLROUNDL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_llroundl(struct qemu_syscall *call)
{
    struct qemu_llroundl *c = (struct qemu_llroundl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_llroundl(c->x);
}

#endif

struct qemu_trunc
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_trunc(double x)
{
    struct qemu_trunc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRUNC);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_trunc(struct qemu_syscall *call)
{
    struct qemu_trunc *c = (struct qemu_trunc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_trunc(c->x);
}

#endif

struct qemu_truncf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_truncf(float x)
{
    struct qemu_truncf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRUNCF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_truncf(struct qemu_syscall *call)
{
    struct qemu_truncf *c = (struct qemu_truncf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_truncf(c->x);
}

#endif

struct qemu_truncl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_truncl(double x)
{
    struct qemu_truncl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRUNCL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_truncl(struct qemu_syscall *call)
{
    struct qemu_truncl *c = (struct qemu_truncl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_truncl(c->x);
}

#endif

struct qemu__dclass
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short CDECL MSVCR120__dclass(double x)
{
    struct qemu__dclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DCLASS);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dclass(struct qemu_syscall *call)
{
    struct qemu__dclass *c = (struct qemu__dclass *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dclass(c->x);
}

#endif

struct qemu__fdclass
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short CDECL MSVCR120__fdclass(float x)
{
    struct qemu__fdclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FDCLASS);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fdclass(struct qemu_syscall *call)
{
    struct qemu__fdclass *c = (struct qemu__fdclass *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fdclass(c->x);
}

#endif

struct qemu__ldclass
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short CDECL MSVCR120__ldclass(double x)
{
    struct qemu__ldclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LDCLASS);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ldclass(struct qemu_syscall *call)
{
    struct qemu__ldclass *c = (struct qemu__ldclass *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ldclass(c->x);
}

#endif

struct qemu__dtest
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short CDECL MSVCR120__dtest(double *x)
{
    struct qemu__dtest call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DTEST);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dtest(struct qemu_syscall *call)
{
    struct qemu__dtest *c = (struct qemu__dtest *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dtest(QEMU_G2H(c->x));
}

#endif

struct qemu__fdtest
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short CDECL MSVCR120__fdtest(float *x)
{
    struct qemu__fdtest call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FDTEST);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fdtest(struct qemu_syscall *call)
{
    struct qemu__fdtest *c = (struct qemu__fdtest *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fdtest(QEMU_G2H(c->x));
}

#endif

struct qemu__ldtest
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short CDECL MSVCR120__ldtest(double *x)
{
    struct qemu__ldtest call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LDTEST);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ldtest(struct qemu_syscall *call)
{
    struct qemu__ldtest *c = (struct qemu__ldtest *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ldtest(QEMU_G2H(c->x));
}

#endif

struct qemu_erf
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_erf(double x)
{
    struct qemu_erf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERF);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_erf(struct qemu_syscall *call)
{
    struct qemu_erf *c = (struct qemu_erf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_erf(c->x);
}

#endif

struct qemu_erff
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_erff(float x)
{
    struct qemu_erff call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERFF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_erff(struct qemu_syscall *call)
{
    struct qemu_erff *c = (struct qemu_erff *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_erff(c->x);
}

#endif

struct qemu_erfl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_erfl(double x)
{
    struct qemu_erfl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERFL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_erfl(struct qemu_syscall *call)
{
    struct qemu_erfl *c = (struct qemu_erfl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_erfl(c->x);
}

#endif

struct qemu_erfc
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_erfc(double x)
{
    struct qemu_erfc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERFC);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_erfc(struct qemu_syscall *call)
{
    struct qemu_erfc *c = (struct qemu_erfc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_erfc(c->x);
}

#endif

struct qemu_erfcf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_erfcf(float x)
{
    struct qemu_erfcf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERFCF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_erfcf(struct qemu_syscall *call)
{
    struct qemu_erfcf *c = (struct qemu_erfcf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_erfcf(c->x);
}

#endif

struct qemu_erfcl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_erfcl(double x)
{
    struct qemu_erfcl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERFCL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_erfcl(struct qemu_syscall *call)
{
    struct qemu_erfcl *c = (struct qemu_erfcl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_erfcl(c->x);
}

#endif

struct qemu_fmaxf
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_fmaxf(float x, float y)
{
    struct qemu_fmaxf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FMAXF);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fmaxf(struct qemu_syscall *call)
{
    struct qemu_fmaxf *c = (struct qemu_fmaxf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_fmaxf(c->x, c->y);
}

#endif

struct qemu_fmax
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_fmax(double x, double y)
{
    struct qemu_fmax call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FMAX);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fmax(struct qemu_syscall *call)
{
    struct qemu_fmax *c = (struct qemu_fmax *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_fmax(c->x, c->y);
}

#endif

struct qemu__fdsign
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCR120__fdsign(float x)
{
    struct qemu__fdsign call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FDSIGN);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fdsign(struct qemu_syscall *call)
{
    struct qemu__fdsign *c = (struct qemu__fdsign *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fdsign(c->x);
}

#endif

struct qemu__dsign
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCR120__dsign(double x)
{
    struct qemu__dsign call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DSIGN);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dsign(struct qemu_syscall *call)
{
    struct qemu__dsign *c = (struct qemu__dsign *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dsign(c->x);
}

#endif

struct qemu__dpcomp
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCR120__dpcomp(double x, double y)
{
    struct qemu__dpcomp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DPCOMP);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dpcomp(struct qemu_syscall *call)
{
    struct qemu__dpcomp *c = (struct qemu__dpcomp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dpcomp(c->x, c->y);
}

#endif

struct qemu__fdpcomp
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCR120__fdpcomp(float x, float y)
{
    struct qemu__fdpcomp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FDPCOMP);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fdpcomp(struct qemu_syscall *call)
{
    struct qemu__fdpcomp *c = (struct qemu__fdpcomp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fdpcomp(c->x, c->y);
}

#endif

struct qemu_fminf
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_fminf(float x, float y)
{
    struct qemu_fminf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FMINF);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fminf(struct qemu_syscall *call)
{
    struct qemu_fminf *c = (struct qemu_fminf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_fminf(c->x, c->y);
}

#endif

struct qemu_fmin
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_fmin(double x, double y)
{
    struct qemu_fmin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FMIN);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_fmin(struct qemu_syscall *call)
{
    struct qemu_fmin *c = (struct qemu_fmin *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_fmin(c->x, c->y);
}

#endif

struct qemu_asinh
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_asinh(double x)
{
    struct qemu_asinh call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASINH);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_asinh(struct qemu_syscall *call)
{
    struct qemu_asinh *c = (struct qemu_asinh *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_asinh(c->x);
}

#endif

struct qemu_asinhf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_asinhf(float x)
{
    struct qemu_asinhf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASINHF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_asinhf(struct qemu_syscall *call)
{
    struct qemu_asinhf *c = (struct qemu_asinhf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_asinhf(c->x);
}

#endif

struct qemu_asinhl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_asinhl(double x)
{
    struct qemu_asinhl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASINHL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_asinhl(struct qemu_syscall *call)
{
    struct qemu_asinhl *c = (struct qemu_asinhl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_asinhl(c->x);
}

#endif

struct qemu_acosh
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_acosh(double x)
{
    struct qemu_acosh call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACOSH);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_acosh(struct qemu_syscall *call)
{
    struct qemu_acosh *c = (struct qemu_acosh *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_acosh(c->x);
}

#endif

struct qemu_acoshf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_acoshf(float x)
{
    struct qemu_acoshf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACOSHF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_acoshf(struct qemu_syscall *call)
{
    struct qemu_acoshf *c = (struct qemu_acoshf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_acoshf(c->x);
}

#endif

struct qemu_acoshl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_acoshl(double x)
{
    struct qemu_acoshl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACOSHL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_acoshl(struct qemu_syscall *call)
{
    struct qemu_acoshl *c = (struct qemu_acoshl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_acoshl(c->x);
}

#endif

struct qemu_atanh
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_atanh(double x)
{
    struct qemu_atanh call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATANH);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atanh(struct qemu_syscall *call)
{
    struct qemu_atanh *c = (struct qemu_atanh *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_atanh(c->x);
}

#endif

struct qemu_atanhf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_atanhf(float x)
{
    struct qemu_atanhf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATANHF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atanhf(struct qemu_syscall *call)
{
    struct qemu_atanhf *c = (struct qemu_atanhf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_atanhf(c->x);
}

#endif

struct qemu_atanhl
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_atanhl(double x)
{
    struct qemu_atanhl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATANHL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atanhl(struct qemu_syscall *call)
{
    struct qemu_atanhl *c = (struct qemu_atanhl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_atanhl(c->x);
}

#endif

struct qemu__scalb
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t power;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__scalb(double num, int32_t power)
{
    struct qemu__scalb call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SCALB);
    call.num = (ULONG_PTR)num;
    call.power = (ULONG_PTR)power;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__scalb(struct qemu_syscall *call)
{
    struct qemu__scalb *c = (struct qemu__scalb *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__scalb(c->num, c->power);
}

#endif

struct qemu__scalbf
{
    struct qemu_syscall super;
    double num;
    uint64_t power;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__scalbf(float num, int32_t power)
{
    struct qemu__scalbf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SCALBF);
    call.num = num;
    call.power = (ULONG_PTR)power;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__scalbf(struct qemu_syscall *call)
{
    struct qemu__scalbf *c = (struct qemu__scalbf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__scalbf(c->num, c->power);
}

#endif

struct qemu_scalbnl
{
    struct qemu_syscall super;
    uint64_t num;
    uint64_t power;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_scalbnl(double num, int32_t power)
{
    struct qemu_scalbnl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCALBNL);
    call.num = (ULONG_PTR)num;
    call.power = (ULONG_PTR)power;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_scalbnl(struct qemu_syscall *call)
{
    struct qemu_scalbnl *c = (struct qemu_scalbnl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_scalbnl(c->num, c->power);
}

#endif

struct qemu_remainder
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_remainder(double x, double y)
{
    struct qemu_remainder call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMAINDER);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_remainder(struct qemu_syscall *call)
{
    struct qemu_remainder *c = (struct qemu_remainder *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_remainder(c->x, c->y);
}

#endif

struct qemu_remainderf
{
    struct qemu_syscall super;
    double x;
    double y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_remainderf(float x, float y)
{
    struct qemu_remainderf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMAINDERF);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_remainderf(struct qemu_syscall *call)
{
    struct qemu_remainderf *c = (struct qemu_remainderf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_remainderf(c->x, c->y);
}

#endif

struct qemu_remainderl
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_remainderl(double x, double y)
{
    struct qemu_remainderl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMAINDERL);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_remainderl(struct qemu_syscall *call)
{
    struct qemu_remainderl *c = (struct qemu_remainderl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_remainderl(c->x, c->y);
}

#endif

struct qemu_lgamma
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_lgamma(double x)
{
    struct qemu_lgamma call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LGAMMA);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_lgamma(struct qemu_syscall *call)
{
    struct qemu_lgamma *c = (struct qemu_lgamma *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_lgamma(c->x);
}

#endif

struct qemu_lgammaf
{
    struct qemu_syscall super;
    double x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_lgammaf(float x)
{
    struct qemu_lgammaf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LGAMMAF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_lgammaf(struct qemu_syscall *call)
{
    struct qemu_lgammaf *c = (struct qemu_lgammaf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_lgammaf(c->x);
}

#endif

struct qemu_lgammal
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_lgammal(double x)
{
    struct qemu_lgammal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LGAMMAL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_lgammal(struct qemu_syscall *call)
{
    struct qemu_lgammal *c = (struct qemu_lgammal *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_lgammal(c->x);
}

#endif

struct qemu_nan
{
    struct qemu_syscall super;
    uint64_t tagp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCR120_nan(const char *tagp)
{
    struct qemu_nan call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NAN);
    call.tagp = (ULONG_PTR)tagp;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_nan(struct qemu_syscall *call)
{
    struct qemu_nan *c = (struct qemu_nan *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_nan(QEMU_G2H(c->tagp));
}

#endif

struct qemu_nanf
{
    struct qemu_syscall super;
    uint64_t tagp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCR120_nanf(const char *tagp)
{
    struct qemu_nanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NANF);
    call.tagp = (ULONG_PTR)tagp;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_nanf(struct qemu_syscall *call)
{
    struct qemu_nanf *c = (struct qemu_nanf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_nanf(QEMU_G2H(c->tagp));
}

#endif

#if defined(QEMU_DLL_GUEST) && defined(__i386__)

#define __ASM_CFI(str) str
#define __ASM_NAME(name) "_" name
#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl _" #name suffix "\n\t.def _" #name suffix "; .scl 2; .type 32; .endef\n_" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)

#define CREATE_FPU_FUNC1(name, call) \
    __ASM_GLOBAL_FUNC(name, \
            "pushl   %ebp\n\t" \
            __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t") \
            __ASM_CFI(".cfi_rel_offset %ebp,0\n\t") \
            "movl    %esp, %ebp\n\t" \
            __ASM_CFI(".cfi_def_cfa_register %ebp\n\t") \
            "subl    $68, %esp\n\t" /* sizeof(double)*8 + sizeof(int) */ \
            "fstpl   (%esp)\n\t"    /* store function argument */ \
            "fwait\n\t" \
            "movl    $1, %ecx\n\t"  /* empty FPU stack */ \
            "1:\n\t" \
            "fxam\n\t" \
            "fstsw   %ax\n\t" \
            "and     $0x4500, %ax\n\t" \
            "cmp     $0x4100, %ax\n\t" \
            "je      2f\n\t" \
            "fstpl    (%esp,%ecx,8)\n\t" \
            "fwait\n\t" \
            "incl    %ecx\n\t" \
            "jmp     1b\n\t" \
            "2:\n\t" \
            "movl    %ecx, -4(%ebp)\n\t" \
            "call    " __ASM_NAME( #call ) "\n\t" \
            "movl    -4(%ebp), %ecx\n\t" \
            "fstpl   (%esp)\n\t"    /* save result */ \
            "3:\n\t"                /* restore FPU stack */ \
            "decl    %ecx\n\t" \
            "fldl    (%esp,%ecx,8)\n\t" \
            "cmpl    $0, %ecx\n\t" \
            "jne     3b\n\t" \
            "leave\n\t" \
            __ASM_CFI(".cfi_def_cfa %esp,4\n\t") \
            __ASM_CFI(".cfi_same_value %ebp\n\t") \
            "ret")

#define CREATE_FPU_FUNC2(name, call) \
    __ASM_GLOBAL_FUNC(name, \
            "pushl   %ebp\n\t" \
            __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t") \
            __ASM_CFI(".cfi_rel_offset %ebp,0\n\t") \
            "movl    %esp, %ebp\n\t" \
            __ASM_CFI(".cfi_def_cfa_register %ebp\n\t") \
            "subl    $68, %esp\n\t" /* sizeof(double)*8 + sizeof(int) */ \
            "fstpl   8(%esp)\n\t"   /* store function argument */ \
            "fwait\n\t" \
            "fstpl   (%esp)\n\t" \
            "fwait\n\t" \
            "movl    $2, %ecx\n\t"  /* empty FPU stack */ \
            "1:\n\t" \
            "fxam\n\t" \
            "fstsw   %ax\n\t" \
            "and     $0x4500, %ax\n\t" \
            "cmp     $0x4100, %ax\n\t" \
            "je      2f\n\t" \
            "fstpl    (%esp,%ecx,8)\n\t" \
            "fwait\n\t" \
            "incl    %ecx\n\t" \
            "jmp     1b\n\t" \
            "2:\n\t" \
            "movl    %ecx, -4(%ebp)\n\t" \
            "call    " __ASM_NAME( #call ) "\n\t" \
            "movl    -4(%ebp), %ecx\n\t" \
            "fstpl   8(%esp)\n\t"   /* save result */ \
            "3:\n\t"                /* restore FPU stack */ \
            "decl    %ecx\n\t" \
            "fldl    (%esp,%ecx,8)\n\t" \
            "cmpl    $1, %ecx\n\t" \
            "jne     3b\n\t" \
            "leave\n\t" \
            __ASM_CFI(".cfi_def_cfa %esp,4\n\t") \
            __ASM_CFI(".cfi_same_value %ebp\n\t") \
            "ret")

CREATE_FPU_FUNC1(_CIacos, MSVCRT_acos)
CREATE_FPU_FUNC1(_CIasin, MSVCRT_asin)
CREATE_FPU_FUNC1(_CIatan, MSVCRT_atan)
CREATE_FPU_FUNC2(_CIatan2, MSVCRT_atan2)
CREATE_FPU_FUNC1(_CIcos, MSVCRT_cos)
CREATE_FPU_FUNC1(_CIcosh, MSVCRT_cosh)
CREATE_FPU_FUNC1(_CIexp, MSVCRT_exp)
CREATE_FPU_FUNC2(_CIfmod, MSVCRT_fmod)
CREATE_FPU_FUNC1(_CIlog, MSVCRT_log)
CREATE_FPU_FUNC1(_CIlog10, MSVCRT_log10)
CREATE_FPU_FUNC2(_CIpow, MSVCRT_pow)
CREATE_FPU_FUNC1(_CIsin, MSVCRT_sin)
CREATE_FPU_FUNC1(_CIsinh, MSVCRT_sinh)
CREATE_FPU_FUNC1(_CIsqrt, MSVCRT_sqrt)
CREATE_FPU_FUNC1(_CItan, MSVCRT_tan)
CREATE_FPU_FUNC1(_CItanh, MSVCRT_tanh)

#endif
