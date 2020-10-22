/*
 * Copyright 2017 André Hentschel
 * Copyright 2019 Stefan Dösinger for CodeWeavers
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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "thunk/qemu_winternl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST
typedef struct _LDR_RESOURCE_INFO LDR_RESOURCE_INFO;
#else
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_NtQuerySystemEnvironmentValue
{
    struct qemu_syscall super;
    uint64_t VariableName;
    uint64_t Value;
    uint64_t ValueBufferLength;
    uint64_t RequiredLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSYSAPI NTSTATUS WINAPI NtQuerySystemEnvironmentValue(PUNICODE_STRING VariableName, PWCHAR Value,
        ULONG ValueBufferLength, PULONG RequiredLength)
{
    struct qemu_NtQuerySystemEnvironmentValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSYSTEMENVIRONMENTVALUE);
    call.VariableName = (ULONG_PTR)VariableName;
    call.Value = (ULONG_PTR)Value;
    call.ValueBufferLength = ValueBufferLength;
    call.RequiredLength = (ULONG_PTR)RequiredLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySystemEnvironmentValue(struct qemu_syscall *call)
{
    struct qemu_NtQuerySystemEnvironmentValue *c = (struct qemu_NtQuerySystemEnvironmentValue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySystemEnvironmentValue(QEMU_G2H(c->VariableName), QEMU_G2H(c->Value), c->ValueBufferLength, QEMU_G2H(c->RequiredLength));
}

#endif

struct qemu_NtQuerySystemEnvironmentValueEx
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t vendor;
    uint64_t value;
    uint64_t retlength;
    uint64_t attrib;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSYSAPI NTSTATUS WINAPI NtQuerySystemEnvironmentValueEx(PUNICODE_STRING name, LPGUID vendor, PVOID value, PULONG retlength, PULONG attrib)
{
    struct qemu_NtQuerySystemEnvironmentValueEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSYSTEMENVIRONMENTVALUEEX);
    call.name = (ULONG_PTR)name;
    call.vendor = (ULONG_PTR)vendor;
    call.value = (ULONG_PTR)value;
    call.retlength = (ULONG_PTR)retlength;
    call.attrib = (ULONG_PTR)attrib;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI NTSYSAPI NTSTATUS WINAPI NtQuerySystemEnvironmentValueEx(PUNICODE_STRING name, LPGUID vendor,
        PVOID value, PULONG retlength, PULONG attrib);
void qemu_NtQuerySystemEnvironmentValueEx(struct qemu_syscall *call)
{
    struct qemu_NtQuerySystemEnvironmentValueEx *c = (struct qemu_NtQuerySystemEnvironmentValueEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySystemEnvironmentValueEx(QEMU_G2H(c->name), QEMU_G2H(c->vendor), QEMU_G2H(c->value), QEMU_G2H(c->retlength), QEMU_G2H(c->attrib));
}

#endif

struct qemu_RtlCreateEnvironment
{
    struct qemu_syscall super;
    uint64_t inherit;
    uint64_t env;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateEnvironment(BOOLEAN inherit, PWSTR* env)
{
    struct qemu_RtlCreateEnvironment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEENVIRONMENT);
    call.inherit = inherit;
    call.env = (ULONG_PTR)env;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateEnvironment(struct qemu_syscall *call)
{
    struct qemu_RtlCreateEnvironment *c = (struct qemu_RtlCreateEnvironment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateEnvironment(c->inherit, QEMU_G2H(c->env));
}

#endif

struct qemu_RtlDestroyEnvironment
{
    struct qemu_syscall super;
    uint64_t env;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDestroyEnvironment(PWSTR env)
{
    struct qemu_RtlDestroyEnvironment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDESTROYENVIRONMENT);
    call.env = (ULONG_PTR)env;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDestroyEnvironment(struct qemu_syscall *call)
{
    struct qemu_RtlDestroyEnvironment *c = (struct qemu_RtlDestroyEnvironment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDestroyEnvironment(QEMU_G2H(c->env));
}

#endif

struct qemu_RtlQueryEnvironmentVariable_U
{
    struct qemu_syscall super;
    uint64_t env;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueryEnvironmentVariable_U(PWSTR env, PUNICODE_STRING name, PUNICODE_STRING value)
{
    struct qemu_RtlQueryEnvironmentVariable_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYENVIRONMENTVARIABLE_U);
    call.env = (ULONG_PTR)env;
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryEnvironmentVariable_U(struct qemu_syscall *call)
{
    struct qemu_RtlQueryEnvironmentVariable_U *c = (struct qemu_RtlQueryEnvironmentVariable_U *)call;
    UNICODE_STRING name_stack, *name = &name_stack;
    UNICODE_STRING value_stack, *value = &value_stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    name = QEMU_G2H(c->name);
    value = QEMU_G2H(c->value);
#else
    UNICODE_STRING_g2h(name, QEMU_G2H(c->name));
    UNICODE_STRING_g2h(value, QEMU_G2H(c->value));
#endif

    c->super.iret = RtlQueryEnvironmentVariable_U(QEMU_G2H(c->env), name, value);
}

#endif

struct qemu_RtlSetCurrentEnvironment
{
    struct qemu_syscall super;
    uint64_t new_env;
    uint64_t old_env;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlSetCurrentEnvironment(PWSTR new_env, PWSTR* old_env)
{
    struct qemu_RtlSetCurrentEnvironment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETCURRENTENVIRONMENT);
    call.new_env = (ULONG_PTR)new_env;
    call.old_env = (ULONG_PTR)old_env;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSetCurrentEnvironment(struct qemu_syscall *call)
{
    struct qemu_RtlSetCurrentEnvironment *c = (struct qemu_RtlSetCurrentEnvironment *)call;
    WINE_FIXME("Unverified!\n");
    RtlSetCurrentEnvironment(QEMU_G2H(c->new_env), QEMU_G2H(c->old_env));
}

#endif

struct qemu_RtlSetEnvironmentVariable
{
    struct qemu_syscall super;
    uint64_t penv;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetEnvironmentVariable(PWSTR* penv, PUNICODE_STRING name, PUNICODE_STRING value)
{
    struct qemu_RtlSetEnvironmentVariable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETENVIRONMENTVARIABLE);
    call.penv = (ULONG_PTR)penv;
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetEnvironmentVariable(struct qemu_syscall *call)
{
    struct qemu_RtlSetEnvironmentVariable *c = (struct qemu_RtlSetEnvironmentVariable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetEnvironmentVariable(QEMU_G2H(c->penv), QEMU_G2H(c->name), QEMU_G2H(c->value));
}

#endif

struct qemu_RtlExpandEnvironmentStrings
{
    struct qemu_syscall super;
    uint64_t renv;
    uint64_t src;
    uint64_t src_len;
    uint64_t dst;
    uint64_t count;
    uint64_t plen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlExpandEnvironmentStrings(const WCHAR *renv, WCHAR *src, SIZE_T src_len, WCHAR *dst, SIZE_T count, SIZE_T *plen)
{
    struct qemu_RtlExpandEnvironmentStrings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEXPANDENVIRONMENTSTRINGS);
    call.renv = (ULONG_PTR)renv;
    call.src = (ULONG_PTR)src;
    call.src_len = src_len;
    call.dst = (ULONG_PTR)dst;
    call.count = count;
    call.plen = (ULONG_PTR)plen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlExpandEnvironmentStrings(struct qemu_syscall *call)
{
    struct qemu_RtlExpandEnvironmentStrings *c = (struct qemu_RtlExpandEnvironmentStrings *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlExpandEnvironmentStrings(QEMU_G2H(c->renv), QEMU_G2H(c->src), c->src_len, QEMU_G2H(c->dst), c->count, QEMU_G2H(c->plen));
}

#endif

struct qemu_RtlExpandEnvironmentStrings_U
{
    struct qemu_syscall super;
    uint64_t env;
    uint64_t src;
    uint64_t dst;
    uint64_t plen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlExpandEnvironmentStrings_U(const WCHAR *env, const UNICODE_STRING *src,
        UNICODE_STRING *dst, ULONG *plen)
{
    struct qemu_RtlExpandEnvironmentStrings_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEXPANDENVIRONMENTSTRINGS_U);
    call.env = (ULONG_PTR)env;
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;
    call.plen = (ULONG_PTR)plen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlExpandEnvironmentStrings_U(struct qemu_syscall *call)
{
    struct qemu_RtlExpandEnvironmentStrings_U *c = (struct qemu_RtlExpandEnvironmentStrings_U *)call;
    UNICODE_STRING src_stack, *src = &src_stack;
    UNICODE_STRING dst_stack, *dst = &dst_stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    src = QEMU_G2H(c->src);
    dst = QEMU_G2H(c->dst);
#else
    UNICODE_STRING_g2h(src, QEMU_G2H(c->src));
    UNICODE_STRING_g2h(dst, QEMU_G2H(c->dst));
#endif

    c->super.iret = RtlExpandEnvironmentStrings_U(QEMU_G2H(c->env), src, dst, QEMU_G2H(c->plen));
}

#endif

struct qemu_RtlNormalizeProcessParams
{
    struct qemu_syscall super;
    uint64_t params;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PRTL_USER_PROCESS_PARAMETERS WINAPI RtlNormalizeProcessParams(RTL_USER_PROCESS_PARAMETERS *params)
{
    struct qemu_RtlNormalizeProcessParams call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNORMALIZEPROCESSPARAMS);
    call.params = (ULONG_PTR)params;

    qemu_syscall(&call.super);

    return (RTL_USER_PROCESS_PARAMETERS *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlNormalizeProcessParams(struct qemu_syscall *call)
{
    struct qemu_RtlNormalizeProcessParams *c = (struct qemu_RtlNormalizeProcessParams *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(RtlNormalizeProcessParams(QEMU_G2H(c->params)));
}

#endif

struct qemu_RtlDeNormalizeProcessParams
{
    struct qemu_syscall super;
    uint64_t params;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PRTL_USER_PROCESS_PARAMETERS WINAPI RtlDeNormalizeProcessParams(RTL_USER_PROCESS_PARAMETERS *params)
{
    struct qemu_RtlDeNormalizeProcessParams call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDENORMALIZEPROCESSPARAMS);
    call.params = (ULONG_PTR)params;

    qemu_syscall(&call.super);

    return (RTL_USER_PROCESS_PARAMETERS *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlDeNormalizeProcessParams(struct qemu_syscall *call)
{
    struct qemu_RtlDeNormalizeProcessParams *c = (struct qemu_RtlDeNormalizeProcessParams *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(RtlDeNormalizeProcessParams(QEMU_G2H(c->params)));
}

#endif

struct qemu_RtlCreateProcessParametersEx
{
    struct qemu_syscall super;
    uint64_t result;
    uint64_t ImagePathName;
    uint64_t DllPath;
    uint64_t CurrentDirectoryName;
    uint64_t CommandLine;
    uint64_t Environment;
    uint64_t WindowTitle;
    uint64_t Desktop;
    uint64_t ShellInfo;
    uint64_t RuntimeInfo;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateProcessParametersEx(RTL_USER_PROCESS_PARAMETERS **result, const UNICODE_STRING *ImagePathName, const UNICODE_STRING *DllPath, const UNICODE_STRING *CurrentDirectoryName, const UNICODE_STRING *CommandLine, PWSTR Environment, const UNICODE_STRING *WindowTitle, const UNICODE_STRING *Desktop, const UNICODE_STRING *ShellInfo, const UNICODE_STRING *RuntimeInfo, ULONG flags)
{
    struct qemu_RtlCreateProcessParametersEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEPROCESSPARAMETERSEX);
    call.result = (ULONG_PTR)result;
    call.ImagePathName = (ULONG_PTR)ImagePathName;
    call.DllPath = (ULONG_PTR)DllPath;
    call.CurrentDirectoryName = (ULONG_PTR)CurrentDirectoryName;
    call.CommandLine = (ULONG_PTR)CommandLine;
    call.Environment = (ULONG_PTR)Environment;
    call.WindowTitle = (ULONG_PTR)WindowTitle;
    call.Desktop = (ULONG_PTR)Desktop;
    call.ShellInfo = (ULONG_PTR)ShellInfo;
    call.RuntimeInfo = (ULONG_PTR)RuntimeInfo;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateProcessParametersEx(struct qemu_syscall *call)
{
    struct qemu_RtlCreateProcessParametersEx *c = (struct qemu_RtlCreateProcessParametersEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateProcessParametersEx(QEMU_G2H(c->result), QEMU_G2H(c->ImagePathName), QEMU_G2H(c->DllPath), QEMU_G2H(c->CurrentDirectoryName), QEMU_G2H(c->CommandLine), QEMU_G2H(c->Environment), QEMU_G2H(c->WindowTitle), QEMU_G2H(c->Desktop), QEMU_G2H(c->ShellInfo), QEMU_G2H(c->RuntimeInfo), c->flags);
}

#endif

struct qemu_RtlCreateProcessParameters
{
    struct qemu_syscall super;
    uint64_t result;
    uint64_t image;
    uint64_t dllpath;
    uint64_t curdir;
    uint64_t cmdline;
    uint64_t env;
    uint64_t title;
    uint64_t desktop;
    uint64_t shellinfo;
    uint64_t runtime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateProcessParameters(RTL_USER_PROCESS_PARAMETERS **result, const UNICODE_STRING *image, const UNICODE_STRING *dllpath, const UNICODE_STRING *curdir, const UNICODE_STRING *cmdline, PWSTR env, const UNICODE_STRING *title, const UNICODE_STRING *desktop, const UNICODE_STRING *shellinfo, const UNICODE_STRING *runtime)
{
    struct qemu_RtlCreateProcessParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEPROCESSPARAMETERS);
    call.result = (ULONG_PTR)result;
    call.image = (ULONG_PTR)image;
    call.dllpath = (ULONG_PTR)dllpath;
    call.curdir = (ULONG_PTR)curdir;
    call.cmdline = (ULONG_PTR)cmdline;
    call.env = (ULONG_PTR)env;
    call.title = (ULONG_PTR)title;
    call.desktop = (ULONG_PTR)desktop;
    call.shellinfo = (ULONG_PTR)shellinfo;
    call.runtime = (ULONG_PTR)runtime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateProcessParameters(struct qemu_syscall *call)
{
    struct qemu_RtlCreateProcessParameters *c = (struct qemu_RtlCreateProcessParameters *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateProcessParameters(QEMU_G2H(c->result), QEMU_G2H(c->image), QEMU_G2H(c->dllpath), QEMU_G2H(c->curdir), QEMU_G2H(c->cmdline), QEMU_G2H(c->env), QEMU_G2H(c->title), QEMU_G2H(c->desktop), QEMU_G2H(c->shellinfo), QEMU_G2H(c->runtime));
}

#endif

struct qemu_RtlDestroyProcessParameters
{
    struct qemu_syscall super;
    uint64_t params;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlDestroyProcessParameters(RTL_USER_PROCESS_PARAMETERS *params)
{
    struct qemu_RtlDestroyProcessParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDESTROYPROCESSPARAMETERS);
    call.params = (ULONG_PTR)params;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlDestroyProcessParameters(struct qemu_syscall *call)
{
    struct qemu_RtlDestroyProcessParameters *c = (struct qemu_RtlDestroyProcessParameters *)call;
    WINE_FIXME("Unverified!\n");
    RtlDestroyProcessParameters(QEMU_G2H(c->params));
}

#endif

