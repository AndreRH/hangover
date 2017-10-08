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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetUserDefaultLangID
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI GetUserDefaultLangID(void)
{
    struct qemu_GetUserDefaultLangID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERDEFAULTLANGID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserDefaultLangID(struct qemu_syscall *call)
{
    struct qemu_GetUserDefaultLangID *c = (struct qemu_GetUserDefaultLangID *)call;
    WINE_TRACE("\n");
    c->super.iret = GetUserDefaultLangID();
}

#endif

struct qemu_GetSystemDefaultLangID
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI GetSystemDefaultLangID(void)
{
    struct qemu_GetSystemDefaultLangID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDEFAULTLANGID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemDefaultLangID(struct qemu_syscall *call)
{
    struct qemu_GetSystemDefaultLangID *c = (struct qemu_GetSystemDefaultLangID *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemDefaultLangID();
}

#endif

struct qemu_GetUserDefaultLCID
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LCID WINAPI GetUserDefaultLCID(void)
{
    struct qemu_GetUserDefaultLCID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERDEFAULTLCID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserDefaultLCID(struct qemu_syscall *call)
{
    struct qemu_GetUserDefaultLCID *c = (struct qemu_GetUserDefaultLCID *)call;
    WINE_TRACE("\n");
    c->super.iret = GetUserDefaultLCID();
}

#endif

struct qemu_GetSystemDefaultLCID
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LCID WINAPI GetSystemDefaultLCID(void)
{
    struct qemu_GetSystemDefaultLCID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDEFAULTLCID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemDefaultLCID(struct qemu_syscall *call)
{
    struct qemu_GetSystemDefaultLCID *c = (struct qemu_GetSystemDefaultLCID *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemDefaultLCID();
}

#endif

struct qemu_GetSystemDefaultLocaleName
{
    struct qemu_syscall super;
    uint64_t localename;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetSystemDefaultLocaleName(LPWSTR localename, INT len)
{
    struct qemu_GetSystemDefaultLocaleName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDEFAULTLOCALENAME);
    call.localename = (ULONG_PTR)localename;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemDefaultLocaleName(struct qemu_syscall *call)
{
    struct qemu_GetSystemDefaultLocaleName *c = (struct qemu_GetSystemDefaultLocaleName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemDefaultLocaleName(QEMU_G2H(c->localename), c->len);
}

#endif

struct qemu_GetSystemPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t count;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSystemPreferredUILanguages(DWORD flags, ULONG* count, WCHAR* buffer, ULONG* size)
{
    struct qemu_GetSystemPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMPREFERREDUILANGUAGES);
    call.flags = flags;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_GetSystemPreferredUILanguages *c = (struct qemu_GetSystemPreferredUILanguages *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemPreferredUILanguages(c->flags, QEMU_G2H(c->count), QEMU_G2H(c->buffer), QEMU_G2H(c->size));
}

#endif

struct qemu_SetThreadPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadPreferredUILanguages(DWORD flags, PCZZWSTR buffer, PULONG count)
{
    struct qemu_SetThreadPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADPREFERREDUILANGUAGES);
    call.flags = flags;
    call.buffer = (ULONG_PTR)buffer;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetThreadPreferredUILanguages to Wine headers? */
extern BOOL WINAPI SetThreadPreferredUILanguages(DWORD flags, PCZZWSTR buffer, PULONG count);
void qemu_SetThreadPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_SetThreadPreferredUILanguages *c = (struct qemu_SetThreadPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadPreferredUILanguages(c->flags, QEMU_G2H(c->buffer), QEMU_G2H(c->count));
}

#endif

struct qemu_GetThreadPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t count;
    uint64_t buf;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadPreferredUILanguages(DWORD flags, ULONG *count, WCHAR *buf, ULONG *size)
{
    struct qemu_GetThreadPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADPREFERREDUILANGUAGES);
    call.flags = flags;
    call.count = (ULONG_PTR)count;
    call.buf = (ULONG_PTR)buf;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_GetThreadPreferredUILanguages *c = (struct qemu_GetThreadPreferredUILanguages *)call;
    WINE_TRACE("\n");
    c->super.iret = GetThreadPreferredUILanguages(c->flags, QEMU_G2H(c->count), QEMU_G2H(c->buf), QEMU_G2H(c->size));
}

#endif

struct qemu_GetUserPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t count;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUserPreferredUILanguages(DWORD flags, ULONG *count, WCHAR *buffer, ULONG *size)
{
    struct qemu_GetUserPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERPREFERREDUILANGUAGES);
    call.flags = flags;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetUserPreferredUILanguages to Wine headers? */
extern BOOL WINAPI GetUserPreferredUILanguages(DWORD flags, ULONG *count, WCHAR *buffer, ULONG *size);
void qemu_GetUserPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_GetUserPreferredUILanguages *c = (struct qemu_GetUserPreferredUILanguages *)call;
    WINE_TRACE("\n");
    c->super.iret = GetUserPreferredUILanguages(c->flags, QEMU_G2H(c->count), QEMU_G2H(c->buffer), QEMU_G2H(c->size));
}

#endif

struct qemu_GetUserDefaultUILanguage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI GetUserDefaultUILanguage(void)
{
    struct qemu_GetUserDefaultUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERDEFAULTUILANGUAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserDefaultUILanguage(struct qemu_syscall *call)
{
    struct qemu_GetUserDefaultUILanguage *c = (struct qemu_GetUserDefaultUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserDefaultUILanguage();
}

#endif

struct qemu_GetSystemDefaultUILanguage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI GetSystemDefaultUILanguage(void)
{
    struct qemu_GetSystemDefaultUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDEFAULTUILANGUAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemDefaultUILanguage(struct qemu_syscall *call)
{
    struct qemu_GetSystemDefaultUILanguage *c = (struct qemu_GetSystemDefaultUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemDefaultUILanguage();
}

#endif

struct qemu_LocaleNameToLCID
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LCID WINAPI LocaleNameToLCID(LPCWSTR name, DWORD flags)
{
    struct qemu_LocaleNameToLCID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALENAMETOLCID);
    call.name = (ULONG_PTR)name;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocaleNameToLCID(struct qemu_syscall *call)
{
    struct qemu_LocaleNameToLCID *c = (struct qemu_LocaleNameToLCID *)call;
    WINE_TRACE("\n");
    c->super.iret = LocaleNameToLCID(QEMU_G2H(c->name), c->flags);
}

#endif

struct qemu_LCIDToLocaleName
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t name;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LCIDToLocaleName(LCID lcid, LPWSTR name, INT count, DWORD flags)
{
    struct qemu_LCIDToLocaleName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LCIDTOLOCALENAME);
    call.lcid = lcid;
    call.name = (ULONG_PTR)name;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LCIDToLocaleName(struct qemu_syscall *call)
{
    struct qemu_LCIDToLocaleName *c = (struct qemu_LCIDToLocaleName *)call;
    WINE_TRACE("\n");
    c->super.iret = LCIDToLocaleName(c->lcid, QEMU_G2H(c->name), c->count, c->flags);
}

#endif

struct qemu_GetLocaleInfoA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t lctype;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetLocaleInfoA(LCID lcid, LCTYPE lctype, LPSTR buffer, INT len)
{
    struct qemu_GetLocaleInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOCALEINFOA);
    call.lcid = lcid;
    call.lctype = lctype;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLocaleInfoA(struct qemu_syscall *call)
{
    struct qemu_GetLocaleInfoA *c = (struct qemu_GetLocaleInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLocaleInfoA(c->lcid, c->lctype, QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_GetLocaleInfoW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t lctype;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetLocaleInfoW(LCID lcid, LCTYPE lctype, LPWSTR buffer, INT len)
{
    struct qemu_GetLocaleInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOCALEINFOW);
    call.lcid = lcid;
    call.lctype = lctype;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLocaleInfoW(struct qemu_syscall *call)
{
    struct qemu_GetLocaleInfoW *c = (struct qemu_GetLocaleInfoW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLocaleInfoW(c->lcid, c->lctype, QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_GetLocaleInfoEx
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t info;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetLocaleInfoEx(LPCWSTR locale, LCTYPE info, LPWSTR buffer, INT len)
{
    struct qemu_GetLocaleInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOCALEINFOEX);
    call.locale = (ULONG_PTR)locale;
    call.info = info;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLocaleInfoEx(struct qemu_syscall *call)
{
    struct qemu_GetLocaleInfoEx *c = (struct qemu_GetLocaleInfoEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLocaleInfoEx(QEMU_G2H(c->locale), c->info, QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_SetLocaleInfoA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t lctype;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetLocaleInfoA(LCID lcid, LCTYPE lctype, LPCSTR data)
{
    struct qemu_SetLocaleInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLOCALEINFOA);
    call.lcid = lcid;
    call.lctype = lctype;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetLocaleInfoA(struct qemu_syscall *call)
{
    struct qemu_SetLocaleInfoA *c = (struct qemu_SetLocaleInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = SetLocaleInfoA(c->lcid, c->lctype, QEMU_G2H(c->data));
}

#endif

struct qemu_SetLocaleInfoW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t lctype;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetLocaleInfoW(LCID lcid, LCTYPE lctype, LPCWSTR data)
{
    struct qemu_SetLocaleInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLOCALEINFOW);
    call.lcid = lcid;
    call.lctype = lctype;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetLocaleInfoW(struct qemu_syscall *call)
{
    struct qemu_SetLocaleInfoW *c = (struct qemu_SetLocaleInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetLocaleInfoW(c->lcid, c->lctype, QEMU_G2H(c->data));
}

#endif

struct qemu_GetACP
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetACP(void)
{
    struct qemu_GetACP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetACP(struct qemu_syscall *call)
{
    struct qemu_GetACP *c = (struct qemu_GetACP *)call;
    WINE_TRACE("\n");
    c->super.iret = GetACP();
}

#endif

struct qemu_SetCPGlobal
{
    struct qemu_syscall super;
    uint64_t acp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SetCPGlobal(UINT acp)
{
    struct qemu_SetCPGlobal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCPGLOBAL);
    call.acp = acp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetCPGlobal to Wine headers? */
extern UINT WINAPI SetCPGlobal(UINT acp);
void qemu_SetCPGlobal(struct qemu_syscall *call)
{
    struct qemu_SetCPGlobal *c = (struct qemu_SetCPGlobal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCPGlobal(c->acp);
}

#endif

struct qemu_GetOEMCP
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetOEMCP(void)
{
    struct qemu_GetOEMCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOEMCP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOEMCP(struct qemu_syscall *call)
{
    struct qemu_GetOEMCP *c = (struct qemu_GetOEMCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetOEMCP();
}

#endif

struct qemu_IsValidCodePage
{
    struct qemu_syscall super;
    uint64_t codepage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidCodePage(UINT codepage)
{
    struct qemu_IsValidCodePage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDCODEPAGE);
    call.codepage = codepage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidCodePage(struct qemu_syscall *call)
{
    struct qemu_IsValidCodePage *c = (struct qemu_IsValidCodePage *)call;
    WINE_TRACE("\n");
    c->super.iret = IsValidCodePage(c->codepage);
}

#endif

struct qemu_IsDBCSLeadByteEx
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t testchar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsDBCSLeadByteEx(UINT codepage, BYTE testchar)
{
    struct qemu_IsDBCSLeadByteEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDBCSLEADBYTEEX);
    call.codepage = codepage;
    call.testchar = testchar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsDBCSLeadByteEx(struct qemu_syscall *call)
{
    struct qemu_IsDBCSLeadByteEx *c = (struct qemu_IsDBCSLeadByteEx *)call;
    WINE_TRACE("\n");
    c->super.iret = IsDBCSLeadByteEx(c->codepage, c->testchar);
}

#endif

struct qemu_IsDBCSLeadByte
{
    struct qemu_syscall super;
    uint64_t testchar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsDBCSLeadByte(BYTE testchar)
{
    struct qemu_IsDBCSLeadByte call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDBCSLEADBYTE);
    call.testchar = testchar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsDBCSLeadByte(struct qemu_syscall *call)
{
    struct qemu_IsDBCSLeadByte *c = (struct qemu_IsDBCSLeadByte *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsDBCSLeadByte(c->testchar);
}

#endif

struct qemu_GetCPInfo
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t cpinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCPInfo(UINT codepage, LPCPINFO cpinfo)
{
    struct qemu_GetCPInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCPINFO);
    call.codepage = codepage;
    call.cpinfo = (ULONG_PTR)cpinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCPInfo(struct qemu_syscall *call)
{
    struct qemu_GetCPInfo *c = (struct qemu_GetCPInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCPInfo(c->codepage, QEMU_G2H(c->cpinfo));
}

#endif

struct qemu_GetCPInfoExA
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t dwFlags;
    uint64_t cpinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCPInfoExA(UINT codepage, DWORD dwFlags, LPCPINFOEXA cpinfo)
{
    struct qemu_GetCPInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCPINFOEXA);
    call.codepage = codepage;
    call.dwFlags = dwFlags;
    call.cpinfo = (ULONG_PTR)cpinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCPInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetCPInfoExA *c = (struct qemu_GetCPInfoExA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCPInfoExA(c->codepage, c->dwFlags, QEMU_G2H(c->cpinfo));
}

#endif

struct qemu_GetCPInfoExW
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t dwFlags;
    uint64_t cpinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCPInfoExW(UINT codepage, DWORD dwFlags, LPCPINFOEXW cpinfo)
{
    struct qemu_GetCPInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCPINFOEXW);
    call.codepage = codepage;
    call.dwFlags = dwFlags;
    call.cpinfo = (ULONG_PTR)cpinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCPInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetCPInfoExW *c = (struct qemu_GetCPInfoExW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCPInfoExW(c->codepage, c->dwFlags, QEMU_G2H(c->cpinfo));
}

#endif

struct qemu_EnumSystemCodePagesA
{
    struct qemu_syscall super;
    uint64_t lpfnCodePageEnum;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumSystemCodePagesA(CODEPAGE_ENUMPROCA lpfnCodePageEnum, DWORD flags)
{
    struct qemu_EnumSystemCodePagesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMCODEPAGESA);
    call.lpfnCodePageEnum = (ULONG_PTR)lpfnCodePageEnum;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumSystemCodePagesA(struct qemu_syscall *call)
{
    struct qemu_EnumSystemCodePagesA *c = (struct qemu_EnumSystemCodePagesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumSystemCodePagesA(QEMU_G2H(c->lpfnCodePageEnum), c->flags);
}

#endif

struct qemu_EnumSystemCodePagesW
{
    struct qemu_syscall super;
    uint64_t lpfnCodePageEnum;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumSystemCodePagesW(CODEPAGE_ENUMPROCW lpfnCodePageEnum, DWORD flags)
{
    struct qemu_EnumSystemCodePagesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMCODEPAGESW);
    call.lpfnCodePageEnum = (ULONG_PTR)lpfnCodePageEnum;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumSystemCodePagesW(struct qemu_syscall *call)
{
    struct qemu_EnumSystemCodePagesW *c = (struct qemu_EnumSystemCodePagesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumSystemCodePagesW(QEMU_G2H(c->lpfnCodePageEnum), c->flags);
}

#endif

struct qemu_MultiByteToWideChar
{
    struct qemu_syscall super;
    uint64_t page;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI MultiByteToWideChar(UINT page, DWORD flags, LPCSTR src, INT srclen, LPWSTR dst, INT dstlen)
{
    struct qemu_MultiByteToWideChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MULTIBYTETOWIDECHAR);
    call.page = page;
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MultiByteToWideChar(struct qemu_syscall *call)
{
    struct qemu_MultiByteToWideChar *c = (struct qemu_MultiByteToWideChar *)call;
    WINE_TRACE("\n");
    c->super.iret = MultiByteToWideChar(c->page, c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen);
}

#endif

struct qemu_WideCharToMultiByte
{
    struct qemu_syscall super;
    uint64_t page;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t defchar;
    uint64_t used;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WideCharToMultiByte(UINT page, DWORD flags, LPCWSTR src, INT srclen, LPSTR dst, INT dstlen, LPCSTR defchar, BOOL *used)
{
    struct qemu_WideCharToMultiByte call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WIDECHARTOMULTIBYTE);
    call.page = page;
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.defchar = (ULONG_PTR)defchar;
    call.used = (ULONG_PTR)used;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WideCharToMultiByte(struct qemu_syscall *call)
{
    struct qemu_WideCharToMultiByte *c = (struct qemu_WideCharToMultiByte *)call;
    WINE_TRACE("\n");
    c->super.iret = WideCharToMultiByte(c->page, c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->defchar), QEMU_G2H(c->used));
}

#endif

struct qemu_GetThreadLocale
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LCID WINAPI GetThreadLocale(void)
{
    struct qemu_GetThreadLocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADLOCALE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadLocale(struct qemu_syscall *call)
{
    struct qemu_GetThreadLocale *c = (struct qemu_GetThreadLocale *)call;
    WINE_TRACE("\n");
    c->super.iret = GetThreadLocale();
}

#endif

struct qemu_SetThreadLocale
{
    struct qemu_syscall super;
    uint64_t lcid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadLocale(LCID lcid)
{
    struct qemu_SetThreadLocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADLOCALE);
    call.lcid = lcid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadLocale(struct qemu_syscall *call)
{
    struct qemu_SetThreadLocale *c = (struct qemu_SetThreadLocale *)call;
    WINE_TRACE("\n");
    c->super.iret = SetThreadLocale(c->lcid);
}

#endif

struct qemu_SetThreadUILanguage
{
    struct qemu_syscall super;
    uint64_t langid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI SetThreadUILanguage(LANGID langid)
{
    struct qemu_SetThreadUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADUILANGUAGE);
    call.langid = langid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadUILanguage(struct qemu_syscall *call)
{
    struct qemu_SetThreadUILanguage *c = (struct qemu_SetThreadUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadUILanguage(c->langid);
}

#endif

struct qemu_ConvertDefaultLocale
{
    struct qemu_syscall super;
    uint64_t lcid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LCID WINAPI ConvertDefaultLocale(LCID lcid)
{
    struct qemu_ConvertDefaultLocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTDEFAULTLOCALE);
    call.lcid = lcid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertDefaultLocale(struct qemu_syscall *call)
{
    struct qemu_ConvertDefaultLocale *c = (struct qemu_ConvertDefaultLocale *)call;
    WINE_TRACE("\n");
    c->super.iret = ConvertDefaultLocale(c->lcid);
}

#endif

struct qemu_IsValidLocale
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidLocale(LCID lcid, DWORD flags)
{
    struct qemu_IsValidLocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDLOCALE);
    call.lcid = lcid;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidLocale(struct qemu_syscall *call)
{
    struct qemu_IsValidLocale *c = (struct qemu_IsValidLocale *)call;
    WINE_TRACE("\n");
    c->super.iret = IsValidLocale(c->lcid, c->flags);
}

#endif

struct qemu_IsValidLocaleName
{
    struct qemu_syscall super;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidLocaleName(LPCWSTR locale)
{
    struct qemu_IsValidLocaleName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDLOCALENAME);
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidLocaleName(struct qemu_syscall *call)
{
    struct qemu_IsValidLocaleName *c = (struct qemu_IsValidLocaleName *)call;
    WINE_TRACE("\n");
    c->super.iret = IsValidLocaleName(QEMU_G2H(c->locale));
}

#endif

struct qemu_EnumSystemLocalesA
{
    struct qemu_syscall super;
    uint64_t lpfnLocaleEnum;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumSystemLocalesA(LOCALE_ENUMPROCA lpfnLocaleEnum, DWORD dwFlags)
{
    struct qemu_EnumSystemLocalesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMLOCALESA);
    call.lpfnLocaleEnum = (ULONG_PTR)lpfnLocaleEnum;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumSystemLocalesA(struct qemu_syscall *call)
{
    struct qemu_EnumSystemLocalesA *c = (struct qemu_EnumSystemLocalesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumSystemLocalesA(QEMU_G2H(c->lpfnLocaleEnum), c->dwFlags);
}

#endif

struct qemu_EnumSystemLocalesW
{
    struct qemu_syscall super;
    uint64_t lpfnLocaleEnum;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumSystemLocalesW(LOCALE_ENUMPROCW lpfnLocaleEnum, DWORD dwFlags)
{
    struct qemu_EnumSystemLocalesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMLOCALESW);
    call.lpfnLocaleEnum = (ULONG_PTR)lpfnLocaleEnum;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumSystemLocalesW(struct qemu_syscall *call)
{
    struct qemu_EnumSystemLocalesW *c = (struct qemu_EnumSystemLocalesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumSystemLocalesW(QEMU_G2H(c->lpfnLocaleEnum), c->dwFlags);
}

#endif

struct qemu_EnumSystemLocalesEx
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t flags;
    uint64_t lparam;
    uint64_t reserved;
    uint64_t wrapper;
};

struct qemu_EnumSystemLocalesEx_cb_data
{
    uint64_t proc;
    uint64_t name;
    uint64_t flags;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t CALLBACK qemu_EnumSystemLocalesEx_cb(struct qemu_EnumSystemLocalesEx_cb_data *data)
{
    LOCALE_ENUMPROCEX proc = (LOCALE_ENUMPROCEX)(ULONG_PTR)data->proc;

    return proc((WCHAR *)(ULONG_PTR)data->name, data->flags, data->param);
}

WINBASEAPI BOOL WINAPI EnumSystemLocalesEx(LOCALE_ENUMPROCEX proc, DWORD flags, LPARAM lparam, LPVOID reserved)
{
    struct qemu_EnumSystemLocalesEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMLOCALESEX);
    call.proc = (ULONG_PTR)proc;
    call.flags = flags;
    call.lparam = lparam;
    call.reserved = (ULONG_PTR)reserved;
    call.wrapper = (ULONG_PTR)qemu_EnumSystemLocalesEx_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct param_wrapper
{
    uint64_t wrapper;
    uint64_t guest_cb;
    uint64_t guest_param;
};

static BOOL CALLBACK qemu_EnumSystemLocalesEx_host_cb(WCHAR *name, DWORD flags, LPARAM param)
{
    struct param_wrapper *data = (struct param_wrapper *)param;
    struct qemu_EnumSystemLocalesEx_cb_data guest_data = {data->guest_cb, QEMU_H2G(name), flags, data->guest_param};
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(%s, 0x%08x, 0x%lx).\n", data->guest_cb,
            wine_dbgstr_w(name), flags, data->guest_param);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&guest_data));
    WINE_TRACE("Guest proc returned %u.\n", ret);
    return ret;
}

void qemu_EnumSystemLocalesEx(struct qemu_syscall *call)
{
    struct qemu_EnumSystemLocalesEx *c = (struct qemu_EnumSystemLocalesEx *)call;
    struct param_wrapper data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_cb = c->proc;
    data.guest_param = c->lparam;

    c->super.iret = EnumSystemLocalesEx(c->proc ? qemu_EnumSystemLocalesEx_host_cb : NULL,
            c->flags, (LPARAM)&data, QEMU_G2H(c->reserved));
}

#endif

struct qemu_VerLanguageNameA
{
    struct qemu_syscall super;
    uint64_t wLang;
    uint64_t szLang;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI VerLanguageNameA(DWORD wLang, LPSTR szLang, DWORD nSize)
{
    struct qemu_VerLanguageNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERLANGUAGENAMEA);
    call.wLang = wLang;
    call.szLang = (ULONG_PTR)szLang;
    call.nSize = nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerLanguageNameA(struct qemu_syscall *call)
{
    struct qemu_VerLanguageNameA *c = (struct qemu_VerLanguageNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerLanguageNameA(c->wLang, QEMU_G2H(c->szLang), c->nSize);
}

#endif

struct qemu_VerLanguageNameW
{
    struct qemu_syscall super;
    uint64_t wLang;
    uint64_t szLang;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI VerLanguageNameW(DWORD wLang, LPWSTR szLang, DWORD nSize)
{
    struct qemu_VerLanguageNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERLANGUAGENAMEW);
    call.wLang = wLang;
    call.szLang = (ULONG_PTR)szLang;
    call.nSize = nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerLanguageNameW(struct qemu_syscall *call)
{
    struct qemu_VerLanguageNameW *c = (struct qemu_VerLanguageNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerLanguageNameW(c->wLang, QEMU_G2H(c->szLang), c->nSize);
}

#endif

struct qemu_GetStringTypeW
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t src;
    uint64_t count;
    uint64_t chartype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetStringTypeW(DWORD type, LPCWSTR src, INT count, LPWORD chartype)
{
    struct qemu_GetStringTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTRINGTYPEW);
    call.type = type;
    call.src = (ULONG_PTR)src;
    call.count = count;
    call.chartype = (ULONG_PTR)chartype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetStringTypeW(struct qemu_syscall *call)
{
    struct qemu_GetStringTypeW *c = (struct qemu_GetStringTypeW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetStringTypeW(c->type, QEMU_G2H(c->src), c->count, QEMU_G2H(c->chartype));
}

#endif

struct qemu_GetStringTypeExW
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t type;
    uint64_t src;
    uint64_t count;
    uint64_t chartype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetStringTypeExW(LCID locale, DWORD type, LPCWSTR src, INT count, LPWORD chartype)
{
    struct qemu_GetStringTypeExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTRINGTYPEEXW);
    call.locale = locale;
    call.type = type;
    call.src = (ULONG_PTR)src;
    call.count = count;
    call.chartype = (ULONG_PTR)chartype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetStringTypeExW(struct qemu_syscall *call)
{
    struct qemu_GetStringTypeExW *c = (struct qemu_GetStringTypeExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetStringTypeExW(c->locale, c->type, QEMU_G2H(c->src), c->count, QEMU_G2H(c->chartype));
}

#endif

struct qemu_GetStringTypeA
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t type;
    uint64_t src;
    uint64_t count;
    uint64_t chartype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetStringTypeA(LCID locale, DWORD type, LPCSTR src, INT count, LPWORD chartype)
{
    struct qemu_GetStringTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTRINGTYPEA);
    call.locale = locale;
    call.type = type;
    call.src = (ULONG_PTR)src;
    call.count = count;
    call.chartype = (ULONG_PTR)chartype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetStringTypeA(struct qemu_syscall *call)
{
    struct qemu_GetStringTypeA *c = (struct qemu_GetStringTypeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetStringTypeA(c->locale, c->type, QEMU_G2H(c->src), c->count, QEMU_G2H(c->chartype));
}

#endif

struct qemu_GetStringTypeExA
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t type;
    uint64_t src;
    uint64_t count;
    uint64_t chartype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetStringTypeExA(LCID locale, DWORD type, LPCSTR src, INT count, LPWORD chartype)
{
    struct qemu_GetStringTypeExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTRINGTYPEEXA);
    call.locale = locale;
    call.type = type;
    call.src = (ULONG_PTR)src;
    call.count = count;
    call.chartype = (ULONG_PTR)chartype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetStringTypeExA(struct qemu_syscall *call)
{
    struct qemu_GetStringTypeExA *c = (struct qemu_GetStringTypeExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetStringTypeExA(c->locale, c->type, QEMU_G2H(c->src), c->count, QEMU_G2H(c->chartype));
}

#endif

struct qemu_LCMapStringEx
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t version;
    uint64_t reserved;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LCMapStringEx(LPCWSTR name, DWORD flags, LPCWSTR src, INT srclen, LPWSTR dst, INT dstlen, LPNLSVERSIONINFO version, LPVOID reserved, LPARAM lparam)
{
    struct qemu_LCMapStringEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LCMAPSTRINGEX);
    call.name = (ULONG_PTR)name;
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.version = (ULONG_PTR)version;
    call.reserved = (ULONG_PTR)reserved;
    call.lparam = lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LCMapStringEx(struct qemu_syscall *call)
{
    struct qemu_LCMapStringEx *c = (struct qemu_LCMapStringEx *)call;
    WINE_TRACE("\n");
    c->super.iret = LCMapStringEx(QEMU_G2H(c->name), c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->version), QEMU_G2H(c->reserved), c->lparam);
}

#endif

struct qemu_LCMapStringW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LCMapStringW(LCID lcid, DWORD flags, LPCWSTR src, INT srclen, LPWSTR dst, INT dstlen)
{
    struct qemu_LCMapStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LCMAPSTRINGW);
    call.lcid = lcid;
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LCMapStringW(struct qemu_syscall *call)
{
    struct qemu_LCMapStringW *c = (struct qemu_LCMapStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = LCMapStringW(c->lcid, c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen);
}

#endif

struct qemu_LCMapStringA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LCMapStringA(LCID lcid, DWORD flags, LPCSTR src, INT srclen, LPSTR dst, INT dstlen)
{
    struct qemu_LCMapStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LCMAPSTRINGA);
    call.lcid = lcid;
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LCMapStringA(struct qemu_syscall *call)
{
    struct qemu_LCMapStringA *c = (struct qemu_LCMapStringA *)call;
    WINE_TRACE("\n");
    c->super.iret = LCMapStringA(c->lcid, c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen);
}

#endif

struct qemu_FoldStringA
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FoldStringA(DWORD dwFlags, LPCSTR src, INT srclen, LPSTR dst, INT dstlen)
{
    struct qemu_FoldStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDSTRINGA);
    call.dwFlags = dwFlags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FoldStringA(struct qemu_syscall *call)
{
    struct qemu_FoldStringA *c = (struct qemu_FoldStringA *)call;
    WINE_TRACE("\n");
    c->super.iret = FoldStringA(c->dwFlags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen);
}

#endif

struct qemu_FoldStringW
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FoldStringW(DWORD dwFlags, LPCWSTR src, INT srclen, LPWSTR dst, INT dstlen)
{
    struct qemu_FoldStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDSTRINGW);
    call.dwFlags = dwFlags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FoldStringW(struct qemu_syscall *call)
{
    struct qemu_FoldStringW *c = (struct qemu_FoldStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = FoldStringW(c->dwFlags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen);
}

#endif

struct qemu_CompareStringW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t str1;
    uint64_t len1;
    uint64_t str2;
    uint64_t len2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CompareStringW(LCID lcid, DWORD flags, LPCWSTR str1, INT len1, LPCWSTR str2, INT len2)
{
    struct qemu_CompareStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPARESTRINGW);
    call.lcid = lcid;
    call.flags = flags;
    call.str1 = (ULONG_PTR)str1;
    call.len1 = len1;
    call.str2 = (ULONG_PTR)str2;
    call.len2 = len2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareStringW(struct qemu_syscall *call)
{
    struct qemu_CompareStringW *c = (struct qemu_CompareStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = CompareStringW(c->lcid, c->flags, QEMU_G2H(c->str1), c->len1, QEMU_G2H(c->str2), c->len2);
}

#endif

struct qemu_CompareStringEx
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t flags;
    uint64_t str1;
    uint64_t len1;
    uint64_t str2;
    uint64_t len2;
    uint64_t version;
    uint64_t reserved;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CompareStringEx(LPCWSTR locale, DWORD flags, LPCWSTR str1, INT len1, LPCWSTR str2, INT len2, LPNLSVERSIONINFO version, LPVOID reserved, LPARAM lParam)
{
    struct qemu_CompareStringEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPARESTRINGEX);
    call.locale = (ULONG_PTR)locale;
    call.flags = flags;
    call.str1 = (ULONG_PTR)str1;
    call.len1 = len1;
    call.str2 = (ULONG_PTR)str2;
    call.len2 = len2;
    call.version = (ULONG_PTR)version;
    call.reserved = (ULONG_PTR)reserved;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareStringEx(struct qemu_syscall *call)
{
    struct qemu_CompareStringEx *c = (struct qemu_CompareStringEx *)call;
    WINE_TRACE("\n");
    c->super.iret = CompareStringEx(QEMU_G2H(c->locale), c->flags, QEMU_G2H(c->str1), c->len1, QEMU_G2H(c->str2), c->len2, QEMU_G2H(c->version), QEMU_G2H(c->reserved), c->lParam);
}

#endif

struct qemu_CompareStringA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t str1;
    uint64_t len1;
    uint64_t str2;
    uint64_t len2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CompareStringA(LCID lcid, DWORD flags, LPCSTR str1, INT len1, LPCSTR str2, INT len2)
{
    struct qemu_CompareStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPARESTRINGA);
    call.lcid = lcid;
    call.flags = flags;
    call.str1 = (ULONG_PTR)str1;
    call.len1 = len1;
    call.str2 = (ULONG_PTR)str2;
    call.len2 = len2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareStringA(struct qemu_syscall *call)
{
    struct qemu_CompareStringA *c = (struct qemu_CompareStringA *)call;
    WINE_TRACE("\n");
    c->super.iret = CompareStringA(c->lcid, c->flags, QEMU_G2H(c->str1), c->len1, QEMU_G2H(c->str2), c->len2);
}

#endif

struct qemu_CompareStringOrdinal
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t len1;
    uint64_t str2;
    uint64_t len2;
    uint64_t ignore_case;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CompareStringOrdinal(const WCHAR *str1, INT len1, const WCHAR *str2, INT len2, BOOL ignore_case)
{
    struct qemu_CompareStringOrdinal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPARESTRINGORDINAL);
    call.str1 = (ULONG_PTR)str1;
    call.len1 = len1;
    call.str2 = (ULONG_PTR)str2;
    call.len2 = len2;
    call.ignore_case = ignore_case;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareStringOrdinal(struct qemu_syscall *call)
{
    struct qemu_CompareStringOrdinal *c = (struct qemu_CompareStringOrdinal *)call;
    WINE_TRACE("\n");
    c->super.iret = CompareStringOrdinal(QEMU_G2H(c->str1), c->len1, QEMU_G2H(c->str2), c->len2, c->ignore_case);
}

#endif

struct qemu_lstrcmpA
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI lstrcmpA(LPCSTR str1, LPCSTR str2)
{
    struct qemu_lstrcmpA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCMPA);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrcmpA(struct qemu_syscall *call)
{
    struct qemu_lstrcmpA *c = (struct qemu_lstrcmpA *)call;
    WINE_TRACE("\n");
    c->super.iret = lstrcmpA(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_lstrcmpiA
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI lstrcmpiA(LPCSTR str1, LPCSTR str2)
{
    struct qemu_lstrcmpiA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCMPIA);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrcmpiA(struct qemu_syscall *call)
{
    struct qemu_lstrcmpiA *c = (struct qemu_lstrcmpiA *)call;
    WINE_TRACE("\n");
    c->super.iret = lstrcmpiA(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_lstrcmpW
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI lstrcmpW(LPCWSTR str1, LPCWSTR str2)
{
    struct qemu_lstrcmpW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCMPW);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrcmpW(struct qemu_syscall *call)
{
    struct qemu_lstrcmpW *c = (struct qemu_lstrcmpW *)call;
    WINE_TRACE("\n");
    c->super.iret = lstrcmpW(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_lstrcmpiW
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI lstrcmpiW(LPCWSTR str1, LPCWSTR str2)
{
    struct qemu_lstrcmpiW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCMPIW);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrcmpiW(struct qemu_syscall *call)
{
    struct qemu_lstrcmpiW *c = (struct qemu_lstrcmpiW *)call;
    WINE_TRACE("\n");
    c->super.iret = lstrcmpiW(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_EnumSystemLanguageGroupsA
{
    struct qemu_syscall super;
    uint64_t pLangGrpEnumProc;
    uint64_t dwFlags;
    uint64_t lParam;
    uint64_t wrapper;
};

struct qemu_EnumSystemLanguageGroups_cb_data
{
    uint64_t grpid;
    uint64_t num;
    uint64_t name;
    uint64_t flags;
    uint64_t param;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

static uint64_t WINAPI qemu_EnumSystemLanguageGroupsA_wrapper(struct qemu_EnumSystemLanguageGroups_cb_data *data)
{
    LANGUAGEGROUP_ENUMPROCA proc = (LANGUAGEGROUP_ENUMPROCA)(ULONG_PTR)data->proc;

    return proc(data->grpid, (char *)(ULONG_PTR)data->num, (char *)(ULONG_PTR)data->name, data->flags, data->param);
}

WINBASEAPI BOOL WINAPI EnumSystemLanguageGroupsA(LANGUAGEGROUP_ENUMPROCA pLangGrpEnumProc, DWORD dwFlags, LONG_PTR lParam)
{
    struct qemu_EnumSystemLanguageGroupsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMLANGUAGEGROUPSA);
    call.pLangGrpEnumProc = (ULONG_PTR)pLangGrpEnumProc;
    call.dwFlags = dwFlags;
    call.lParam = lParam;
    call.wrapper = (ULONG_PTR)qemu_EnumSystemLanguageGroupsA_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK qemu_EnumSystemLanguageGroupsA_cb(LGRPID lgrpid, char *num, char *name,
        DWORD flags, LONG_PTR param)
{
    struct param_wrapper *data = (struct param_wrapper *)param;
    struct qemu_EnumSystemLanguageGroups_cb_data guest_data = {lgrpid, QEMU_H2G(num), QEMU_H2G(name),
            flags, data->guest_param, data->guest_cb};
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(0x%08x, %s, %s, %08x, 0x%lx).\n", data->guest_cb,
            lgrpid, num, name, flags, data->guest_param);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&guest_data));
    WINE_TRACE("Guest proc returned %u.\n", ret);
    return ret;
}

void qemu_EnumSystemLanguageGroupsA(struct qemu_syscall *call)
{
    struct qemu_EnumSystemLanguageGroupsA *c = (struct qemu_EnumSystemLanguageGroupsA *)call;
    struct param_wrapper data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_cb = c->pLangGrpEnumProc;
    data.guest_param = c->lParam;

    c->super.iret = EnumSystemLanguageGroupsA(c->pLangGrpEnumProc ? qemu_EnumSystemLanguageGroupsA_cb : NULL,
            c->dwFlags, (LONG_PTR)&data);
}

#endif

struct qemu_EnumSystemLanguageGroupsW
{
    struct qemu_syscall super;
    uint64_t pLangGrpEnumProc;
    uint64_t dwFlags;
    uint64_t lParam;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

static uint64_t WINAPI qemu_EnumSystemLanguageGroupsW_wrapper(struct qemu_EnumSystemLanguageGroups_cb_data *data)
{
    LANGUAGEGROUP_ENUMPROCW proc = (LANGUAGEGROUP_ENUMPROCW)(ULONG_PTR)data->proc;

    return proc(data->grpid, (WCHAR *)(ULONG_PTR)data->num, (WCHAR *)(ULONG_PTR)data->name, data->flags, data->param);
}

WINBASEAPI BOOL WINAPI EnumSystemLanguageGroupsW(LANGUAGEGROUP_ENUMPROCW pLangGrpEnumProc, DWORD dwFlags, LONG_PTR lParam)
{
    struct qemu_EnumSystemLanguageGroupsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMLANGUAGEGROUPSW);
    call.pLangGrpEnumProc = (ULONG_PTR)pLangGrpEnumProc;
    call.dwFlags = dwFlags;
    call.lParam = lParam;
    call.wrapper = (ULONG_PTR)qemu_EnumSystemLanguageGroupsW_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK qemu_EnumSystemLanguageGroupsW_cb(LGRPID lgrpid, WCHAR *num, WCHAR *name,
        DWORD flags, LONG_PTR param)
{
    struct param_wrapper *data = (struct param_wrapper *)param;
    struct qemu_EnumSystemLanguageGroups_cb_data guest_data = {lgrpid, QEMU_H2G(num), QEMU_H2G(name),
            flags, data->guest_param, data->guest_cb};
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(0x%08x, %s, %s, %08x, 0x%lx).\n", data->guest_cb,
            lgrpid, wine_dbgstr_w(num), wine_dbgstr_w(name), flags, data->guest_param);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&guest_data));
    WINE_TRACE("Guest proc returned %u.\n", ret);
    return ret;
}

void qemu_EnumSystemLanguageGroupsW(struct qemu_syscall *call)
{
    struct qemu_EnumSystemLanguageGroupsW *c = (struct qemu_EnumSystemLanguageGroupsW *)call;
    struct param_wrapper data;

    /* Wrote this based on A, but the tests don't call W, so this is untested. */
    WINE_FIXME("Unverified!\n");
    data.wrapper = c->wrapper;
    data.guest_cb = c->pLangGrpEnumProc;
    data.guest_param = c->lParam;

    c->super.iret = EnumSystemLanguageGroupsW(c->pLangGrpEnumProc ? qemu_EnumSystemLanguageGroupsW_cb : NULL,
            c->dwFlags, (LONG_PTR)&data);
}

#endif

struct qemu_IsValidLanguageGroup
{
    struct qemu_syscall super;
    uint64_t lgrpid;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidLanguageGroup(LGRPID lgrpid, DWORD dwFlags)
{
    struct qemu_IsValidLanguageGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDLANGUAGEGROUP);
    call.lgrpid = lgrpid;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidLanguageGroup(struct qemu_syscall *call)
{
    struct qemu_IsValidLanguageGroup *c = (struct qemu_IsValidLanguageGroup *)call;
    WINE_TRACE("\n");
    c->super.iret = IsValidLanguageGroup(c->lgrpid, c->dwFlags);
}

#endif

struct qemu_EnumLanguageGroupLocalesA
{
    struct qemu_syscall super;
    uint64_t pLangGrpLcEnumProc;
    uint64_t lgrpid;
    uint64_t dwFlags;
    uint64_t lParam;
    uint64_t wrapper;
};

struct qemu_EnumLanguageGroupLocalesA_cb_data
{
    uint64_t proc;
    uint64_t lgrpid;
    uint64_t lcid;
    uint64_t num;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t WINAPI qemu_EnumLanguageGroupLocalesA_host_cb(struct qemu_EnumLanguageGroupLocalesA_cb_data *data)
{
    LANGGROUPLOCALE_ENUMPROCA proc = (LANGGROUPLOCALE_ENUMPROCA)(ULONG_PTR)data->proc;

    return proc(data->lgrpid, data->lcid, (char *)(ULONG_PTR)data->num, data->param);
}

WINBASEAPI BOOL WINAPI EnumLanguageGroupLocalesA(LANGGROUPLOCALE_ENUMPROCA pLangGrpLcEnumProc, LGRPID lgrpid, DWORD dwFlags, LONG_PTR lParam)
{
    struct qemu_EnumLanguageGroupLocalesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMLANGUAGEGROUPLOCALESA);
    call.pLangGrpLcEnumProc = (ULONG_PTR)pLangGrpLcEnumProc;
    call.lgrpid = lgrpid;
    call.dwFlags = dwFlags;
    call.lParam = lParam;
    call.wrapper = (ULONG_PTR)qemu_EnumLanguageGroupLocalesA_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK qemu_EnumLanguageGroupLocalesA_host_cb(LGRPID lgrpid, LCID lcid, char *num,
        LONG_PTR param)
{
    struct param_wrapper *data = (struct param_wrapper *)param;
    struct qemu_EnumLanguageGroupLocalesA_cb_data guest_data = {data->guest_cb, lgrpid, lcid, QEMU_H2G(num),
            data->guest_param};
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(0x%x, 0x%x, %s, 0x%lx).\n", data->guest_cb,
            lgrpid, lcid, num, data->guest_param);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&guest_data));
    WINE_TRACE("Guest proc returned %u.\n", ret);
    return ret;
}

void qemu_EnumLanguageGroupLocalesA(struct qemu_syscall *call)
{
    struct qemu_EnumLanguageGroupLocalesA *c = (struct qemu_EnumLanguageGroupLocalesA *)call;
    struct param_wrapper data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_cb = c->pLangGrpLcEnumProc;
    data.guest_param = c->lParam;

    c->super.iret = EnumLanguageGroupLocalesA(c->pLangGrpLcEnumProc ? qemu_EnumLanguageGroupLocalesA_host_cb : NULL,
            c->lgrpid, c->dwFlags, (LONG_PTR)&data);
}

#endif

struct qemu_EnumLanguageGroupLocalesW
{
    struct qemu_syscall super;
    uint64_t pLangGrpLcEnumProc;
    uint64_t lgrpid;
    uint64_t dwFlags;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumLanguageGroupLocalesW(LANGGROUPLOCALE_ENUMPROCW pLangGrpLcEnumProc, LGRPID lgrpid, DWORD dwFlags, LONG_PTR lParam)
{
    struct qemu_EnumLanguageGroupLocalesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMLANGUAGEGROUPLOCALESW);
    call.pLangGrpLcEnumProc = (ULONG_PTR)pLangGrpLcEnumProc;
    call.lgrpid = lgrpid;
    call.dwFlags = dwFlags;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumLanguageGroupLocalesW(struct qemu_syscall *call)
{
    struct qemu_EnumLanguageGroupLocalesW *c = (struct qemu_EnumLanguageGroupLocalesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumLanguageGroupLocalesW(QEMU_G2H(c->pLangGrpLcEnumProc), c->lgrpid, c->dwFlags, c->lParam);
}

#endif

struct qemu_InvalidateNLSCache
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InvalidateNLSCache(void)
{
    struct qemu_InvalidateNLSCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INVALIDATENLSCACHE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InvalidateNLSCache to Wine headers? */
extern BOOL WINAPI InvalidateNLSCache(void);
void qemu_InvalidateNLSCache(struct qemu_syscall *call)
{
    struct qemu_InvalidateNLSCache *c = (struct qemu_InvalidateNLSCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InvalidateNLSCache();
}

#endif

struct qemu_GetUserGeoID
{
    struct qemu_syscall super;
    uint64_t GeoClass;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI GEOID WINAPI GetUserGeoID(GEOCLASS GeoClass)
{
    struct qemu_GetUserGeoID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERGEOID);
    call.GeoClass = GeoClass;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserGeoID(struct qemu_syscall *call)
{
    struct qemu_GetUserGeoID *c = (struct qemu_GetUserGeoID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserGeoID(c->GeoClass);
}

#endif

struct qemu_SetUserGeoID
{
    struct qemu_syscall super;
    uint64_t GeoID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUserGeoID(GEOID GeoID)
{
    struct qemu_SetUserGeoID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETUSERGEOID);
    call.GeoID = GeoID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUserGeoID(struct qemu_syscall *call)
{
    struct qemu_SetUserGeoID *c = (struct qemu_SetUserGeoID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUserGeoID(c->GeoID);
}

#endif

struct qemu_EnumUILanguagesA
{
    struct qemu_syscall super;
    uint64_t pUILangEnumProc;
    uint64_t dwFlags;
    uint64_t lParam;
    uint64_t wrapper;
};

struct qemu_EnumUILanguagesA_cb
{
    uint64_t proc;
    uint64_t value;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t WINAPI qemu_EnumUILanguagesA_cb(struct qemu_EnumUILanguagesA_cb *data)
{
    UILANGUAGE_ENUMPROCA proc = (UILANGUAGE_ENUMPROCA)(ULONG_PTR)data->proc;

    return proc((char *)(ULONG_PTR)data->value, data->param);
}

WINBASEAPI BOOL WINAPI EnumUILanguagesA(UILANGUAGE_ENUMPROCA pUILangEnumProc, DWORD dwFlags, LONG_PTR lParam)
{
    struct qemu_EnumUILanguagesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUILANGUAGESA);
    call.pUILangEnumProc = (ULONG_PTR)pUILangEnumProc;
    call.dwFlags = dwFlags;
    call.lParam = lParam;
    call.wrapper = (ULONG_PTR)qemu_EnumUILanguagesA_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK qemu_EnumUILanguagesA_host_cb(char *value, LONG_PTR param)
{
    struct param_wrapper *data = (struct param_wrapper *)param;
    struct qemu_EnumUILanguagesA_cb guest_data = {data->guest_cb, QEMU_H2G(value), data->guest_param};
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(%s, 0x%lx).\n", data->guest_cb,
            value, data->guest_param);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&guest_data));
    WINE_TRACE("Guest proc returned %u.\n", ret);
    return ret;
}

void qemu_EnumUILanguagesA(struct qemu_syscall *call)
{
    struct qemu_EnumUILanguagesA *c = (struct qemu_EnumUILanguagesA *)call;
    struct param_wrapper data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_cb = c->pUILangEnumProc;
    data.guest_param = c->lParam;

    c->super.iret = EnumUILanguagesA(c->pUILangEnumProc ? qemu_EnumUILanguagesA_host_cb : NULL, c->dwFlags,
            (LONG_PTR)&data);
}

#endif

struct qemu_EnumUILanguagesW
{
    struct qemu_syscall super;
    uint64_t pUILangEnumProc;
    uint64_t dwFlags;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumUILanguagesW(UILANGUAGE_ENUMPROCW pUILangEnumProc, DWORD dwFlags, LONG_PTR lParam)
{
    struct qemu_EnumUILanguagesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUILANGUAGESW);
    call.pUILangEnumProc = (ULONG_PTR)pUILangEnumProc;
    call.dwFlags = dwFlags;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUILanguagesW(struct qemu_syscall *call)
{
    struct qemu_EnumUILanguagesW *c = (struct qemu_EnumUILanguagesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumUILanguagesW(QEMU_G2H(c->pUILangEnumProc), c->dwFlags, c->lParam);
}

#endif

struct qemu_GetGeoInfoW
{
    struct qemu_syscall super;
    uint64_t geoid;
    uint64_t geotype;
    uint64_t data;
    uint64_t data_len;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetGeoInfoW(GEOID geoid, GEOTYPE geotype, LPWSTR data, int data_len, LANGID lang)
{
    struct qemu_GetGeoInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGEOINFOW);
    call.geoid = geoid;
    call.geotype = geotype;
    call.data = (ULONG_PTR)data;
    call.data_len = data_len;
    call.lang = lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGeoInfoW(struct qemu_syscall *call)
{
    struct qemu_GetGeoInfoW *c = (struct qemu_GetGeoInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetGeoInfoW(c->geoid, c->geotype, QEMU_G2H(c->data), c->data_len, c->lang);
}

#endif

struct qemu_GetGeoInfoA
{
    struct qemu_syscall super;
    uint64_t geoid;
    uint64_t geotype;
    uint64_t data;
    uint64_t data_len;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetGeoInfoA(GEOID geoid, GEOTYPE geotype, LPSTR data, int data_len, LANGID lang)
{
    struct qemu_GetGeoInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGEOINFOA);
    call.geoid = geoid;
    call.geotype = geotype;
    call.data = (ULONG_PTR)data;
    call.data_len = data_len;
    call.lang = lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGeoInfoA(struct qemu_syscall *call)
{
    struct qemu_GetGeoInfoA *c = (struct qemu_GetGeoInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetGeoInfoA(c->geoid, c->geotype, QEMU_G2H(c->data), c->data_len, c->lang);
}

#endif

struct qemu_EnumSystemGeoID
{
    struct qemu_syscall super;
    uint64_t geoclass;
    uint64_t parent;
    uint64_t enumproc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumSystemGeoID(GEOCLASS geoclass, GEOID parent, GEO_ENUMPROC enumproc)
{
    struct qemu_EnumSystemGeoID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSYSTEMGEOID);
    call.geoclass = geoclass;
    call.parent = parent;
    call.enumproc = (ULONG_PTR)enumproc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK qemu_EnumSystemGeoID_host_cb(GEOID id)
{
    uint64_t *guest_proc = TlsGetValue(kernel32_tls);
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(%x).\n", *guest_proc, id);
    ret = qemu_ops->qemu_execute(QEMU_G2H(*guest_proc), id);
    WINE_TRACE("Guest proc returned %u\n", ret);
    return ret;
};

void qemu_EnumSystemGeoID(struct qemu_syscall *call)
{
    struct qemu_EnumSystemGeoID *c = (struct qemu_EnumSystemGeoID *)call;
    uint64_t *old_tls;

    WINE_TRACE("\n");
    old_tls = TlsGetValue(kernel32_tls);
    TlsSetValue(kernel32_tls, &c->enumproc);

    c->super.iret = EnumSystemGeoID(c->geoclass, c->parent,
            c->enumproc ? qemu_EnumSystemGeoID_host_cb : NULL);

    TlsSetValue(kernel32_tls, old_tls);
}

#endif

struct qemu_GetUserDefaultLocaleName
{
    struct qemu_syscall super;
    uint64_t localename;
    uint64_t buffersize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetUserDefaultLocaleName(LPWSTR localename, int buffersize)
{
    struct qemu_GetUserDefaultLocaleName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERDEFAULTLOCALENAME);
    call.localename = (ULONG_PTR)localename;
    call.buffersize = buffersize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserDefaultLocaleName(struct qemu_syscall *call)
{
    struct qemu_GetUserDefaultLocaleName *c = (struct qemu_GetUserDefaultLocaleName *)call;
    WINE_TRACE("\n");
    c->super.iret = GetUserDefaultLocaleName(QEMU_G2H(c->localename), c->buffersize);
}

#endif

struct qemu_NormalizeString
{
    struct qemu_syscall super;
    uint64_t NormForm;
    uint64_t lpSrcString;
    uint64_t cwSrcLength;
    uint64_t lpDstString;
    uint64_t cwDstLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI NormalizeString(NORM_FORM NormForm, LPCWSTR lpSrcString, INT cwSrcLength, LPWSTR lpDstString, INT cwDstLength)
{
    struct qemu_NormalizeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NORMALIZESTRING);
    call.NormForm = NormForm;
    call.lpSrcString = (ULONG_PTR)lpSrcString;
    call.cwSrcLength = cwSrcLength;
    call.lpDstString = (ULONG_PTR)lpDstString;
    call.cwDstLength = cwDstLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NormalizeString(struct qemu_syscall *call)
{
    struct qemu_NormalizeString *c = (struct qemu_NormalizeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NormalizeString(c->NormForm, QEMU_G2H(c->lpSrcString), c->cwSrcLength, QEMU_G2H(c->lpDstString), c->cwDstLength);
}

#endif

struct qemu_IsNormalizedString
{
    struct qemu_syscall super;
    uint64_t NormForm;
    uint64_t lpString;
    uint64_t cwLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsNormalizedString(NORM_FORM NormForm, LPCWSTR lpString, INT cwLength)
{
    struct qemu_IsNormalizedString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISNORMALIZEDSTRING);
    call.NormForm = NormForm;
    call.lpString = (ULONG_PTR)lpString;
    call.cwLength = cwLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsNormalizedString(struct qemu_syscall *call)
{
    struct qemu_IsNormalizedString *c = (struct qemu_IsNormalizedString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsNormalizedString(c->NormForm, QEMU_G2H(c->lpString), c->cwLength);
}

#endif

struct qemu_IdnToAscii
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpUnicodeCharStr;
    uint64_t cchUnicodeChar;
    uint64_t lpASCIICharStr;
    uint64_t cchASCIIChar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI IdnToAscii(DWORD dwFlags, LPCWSTR lpUnicodeCharStr, INT cchUnicodeChar, LPWSTR lpASCIICharStr, INT cchASCIIChar)
{
    struct qemu_IdnToAscii call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDNTOASCII);
    call.dwFlags = dwFlags;
    call.lpUnicodeCharStr = (ULONG_PTR)lpUnicodeCharStr;
    call.cchUnicodeChar = cchUnicodeChar;
    call.lpASCIICharStr = (ULONG_PTR)lpASCIICharStr;
    call.cchASCIIChar = cchASCIIChar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IdnToAscii(struct qemu_syscall *call)
{
    struct qemu_IdnToAscii *c = (struct qemu_IdnToAscii *)call;
    WINE_TRACE("\n");
    c->super.iret = IdnToAscii(c->dwFlags, QEMU_G2H(c->lpUnicodeCharStr), c->cchUnicodeChar, QEMU_G2H(c->lpASCIICharStr), c->cchASCIIChar);
}

#endif

struct qemu_IdnToNameprepUnicode
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpUnicodeCharStr;
    uint64_t cchUnicodeChar;
    uint64_t lpNameprepCharStr;
    uint64_t cchNameprepChar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI IdnToNameprepUnicode(DWORD dwFlags, LPCWSTR lpUnicodeCharStr, INT cchUnicodeChar, LPWSTR lpNameprepCharStr, INT cchNameprepChar)
{
    struct qemu_IdnToNameprepUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDNTONAMEPREPUNICODE);
    call.dwFlags = dwFlags;
    call.lpUnicodeCharStr = (ULONG_PTR)lpUnicodeCharStr;
    call.cchUnicodeChar = cchUnicodeChar;
    call.lpNameprepCharStr = (ULONG_PTR)lpNameprepCharStr;
    call.cchNameprepChar = cchNameprepChar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IdnToNameprepUnicode(struct qemu_syscall *call)
{
    struct qemu_IdnToNameprepUnicode *c = (struct qemu_IdnToNameprepUnicode *)call;
    WINE_TRACE("\n");
    c->super.iret = IdnToNameprepUnicode(c->dwFlags, QEMU_G2H(c->lpUnicodeCharStr), c->cchUnicodeChar, QEMU_G2H(c->lpNameprepCharStr), c->cchNameprepChar);
}

#endif

struct qemu_IdnToUnicode
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpASCIICharStr;
    uint64_t cchASCIIChar;
    uint64_t lpUnicodeCharStr;
    uint64_t cchUnicodeChar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI IdnToUnicode(DWORD dwFlags, LPCWSTR lpASCIICharStr, INT cchASCIIChar, LPWSTR lpUnicodeCharStr, INT cchUnicodeChar)
{
    struct qemu_IdnToUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDNTOUNICODE);
    call.dwFlags = dwFlags;
    call.lpASCIICharStr = (ULONG_PTR)lpASCIICharStr;
    call.cchASCIIChar = cchASCIIChar;
    call.lpUnicodeCharStr = (ULONG_PTR)lpUnicodeCharStr;
    call.cchUnicodeChar = cchUnicodeChar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IdnToUnicode(struct qemu_syscall *call)
{
    struct qemu_IdnToUnicode *c = (struct qemu_IdnToUnicode *)call;
    WINE_TRACE("\n");
    c->super.iret = IdnToUnicode(c->dwFlags, QEMU_G2H(c->lpASCIICharStr), c->cchASCIIChar, QEMU_G2H(c->lpUnicodeCharStr), c->cchUnicodeChar);
}

#endif

struct qemu_GetFileMUIPath
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t filepath;
    uint64_t language;
    uint64_t languagelen;
    uint64_t muipath;
    uint64_t muipathlen;
    uint64_t enumerator;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileMUIPath(DWORD flags, PCWSTR filepath, PWSTR language, PULONG languagelen, PWSTR muipath, PULONG muipathlen, PULONGLONG enumerator)
{
    struct qemu_GetFileMUIPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEMUIPATH);
    call.flags = flags;
    call.filepath = (ULONG_PTR)filepath;
    call.language = (ULONG_PTR)language;
    call.languagelen = (ULONG_PTR)languagelen;
    call.muipath = (ULONG_PTR)muipath;
    call.muipathlen = (ULONG_PTR)muipathlen;
    call.enumerator = (ULONG_PTR)enumerator;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileMUIPath(struct qemu_syscall *call)
{
    struct qemu_GetFileMUIPath *c = (struct qemu_GetFileMUIPath *)call;
    WINE_FIXME("Unverified!\n");
c->super.iret = GetFileMUIPath(c->flags, QEMU_G2H(c->filepath), QEMU_G2H(c->language), QEMU_G2H(c->languagelen), QEMU_G2H(c->muipath), QEMU_G2H(c->muipathlen), QEMU_G2H(c->enumerator));
}

#endif

struct qemu_GetFileMUIInfo
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t path;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileMUIInfo(DWORD flags, PCWSTR path, FILEMUIINFO *info, DWORD *size)
{
    struct qemu_GetFileMUIInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEMUIINFO);
    call.flags = flags;
    call.path = (ULONG_PTR)path;
    call.info = (ULONG_PTR)info;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileMUIInfo(struct qemu_syscall *call)
{
    struct qemu_GetFileMUIInfo *c = (struct qemu_GetFileMUIInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileMUIInfo(c->flags, QEMU_G2H(c->path), QEMU_G2H(c->info), QEMU_G2H(c->size));
}

#endif

struct qemu_ResolveLocaleName
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t localename;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ResolveLocaleName(LPCWSTR name, LPWSTR localename, INT len)
{
    struct qemu_ResolveLocaleName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESOLVELOCALENAME);
    call.name = (ULONG_PTR)name;
    call.localename = (ULONG_PTR)localename;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResolveLocaleName(struct qemu_syscall *call)
{
    struct qemu_ResolveLocaleName *c = (struct qemu_ResolveLocaleName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ResolveLocaleName(QEMU_G2H(c->name), QEMU_G2H(c->localename), c->len);
}

#endif

