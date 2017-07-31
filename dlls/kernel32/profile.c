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


struct qemu_GetProfileIntA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetProfileIntA(LPCSTR section, LPCSTR entry, INT def_val)
{
    struct qemu_GetProfileIntA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROFILEINTA);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProfileIntA(struct qemu_syscall *call)
{
    struct qemu_GetProfileIntA *c = (struct qemu_GetProfileIntA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProfileIntA(QEMU_G2H(c->section), QEMU_G2H(c->entry), c->def_val);
}

#endif

struct qemu_GetProfileIntW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetProfileIntW(LPCWSTR section, LPCWSTR entry, INT def_val)
{
    struct qemu_GetProfileIntW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROFILEINTW);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProfileIntW(struct qemu_syscall *call)
{
    struct qemu_GetProfileIntW *c = (struct qemu_GetProfileIntW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProfileIntW(QEMU_G2H(c->section), QEMU_G2H(c->entry), c->def_val);
}

#endif

struct qemu_GetPrivateProfileStringW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
    uint64_t buffer;
    uint64_t len;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrivateProfileStringW(LPCWSTR section, LPCWSTR entry, LPCWSTR def_val, LPWSTR buffer, DWORD len, LPCWSTR filename)
{
    struct qemu_GetPrivateProfileStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESTRINGW);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileStringW(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileStringW *c = (struct qemu_GetPrivateProfileStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileStringW(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->def_val), QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileStringA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
    uint64_t buffer;
    uint64_t len;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrivateProfileStringA(LPCSTR section, LPCSTR entry, LPCSTR def_val, LPSTR buffer, DWORD len, LPCSTR filename)
{
    struct qemu_GetPrivateProfileStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESTRINGA);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileStringA(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileStringA *c = (struct qemu_GetPrivateProfileStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileStringA(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->def_val), QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetProfileStringA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProfileStringA(LPCSTR section, LPCSTR entry, LPCSTR def_val, LPSTR buffer, DWORD len)
{
    struct qemu_GetProfileStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROFILESTRINGA);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProfileStringA(struct qemu_syscall *call)
{
    struct qemu_GetProfileStringA *c = (struct qemu_GetProfileStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProfileStringA(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->def_val), QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_GetProfileStringW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProfileStringW(LPCWSTR section, LPCWSTR entry, LPCWSTR def_val, LPWSTR buffer, DWORD len)
{
    struct qemu_GetProfileStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROFILESTRINGW);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProfileStringW(struct qemu_syscall *call)
{
    struct qemu_GetProfileStringW *c = (struct qemu_GetProfileStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProfileStringW(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->def_val), QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_WriteProfileStringA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t string;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteProfileStringA(LPCSTR section, LPCSTR entry, LPCSTR string)
{
    struct qemu_WriteProfileStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPROFILESTRINGA);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.string = (uint64_t)string;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteProfileStringA(struct qemu_syscall *call)
{
    struct qemu_WriteProfileStringA *c = (struct qemu_WriteProfileStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteProfileStringA(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->string));
}

#endif

struct qemu_WriteProfileStringW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t string;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteProfileStringW(LPCWSTR section, LPCWSTR entry, LPCWSTR string)
{
    struct qemu_WriteProfileStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPROFILESTRINGW);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.string = (uint64_t)string;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteProfileStringW(struct qemu_syscall *call)
{
    struct qemu_WriteProfileStringW *c = (struct qemu_WriteProfileStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteProfileStringW(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->string));
}

#endif

struct qemu_GetPrivateProfileIntW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetPrivateProfileIntW(LPCWSTR section, LPCWSTR entry, INT def_val, LPCWSTR filename)
{
    struct qemu_GetPrivateProfileIntW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILEINTW);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileIntW(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileIntW *c = (struct qemu_GetPrivateProfileIntW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileIntW(QEMU_G2H(c->section), QEMU_G2H(c->entry), c->def_val, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileIntA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t def_val;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetPrivateProfileIntA(LPCSTR section, LPCSTR entry, INT def_val, LPCSTR filename)
{
    struct qemu_GetPrivateProfileIntA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILEINTA);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.def_val = (uint64_t)def_val;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileIntA(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileIntA *c = (struct qemu_GetPrivateProfileIntA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileIntA(QEMU_G2H(c->section), QEMU_G2H(c->entry), c->def_val, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileSectionW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t buffer;
    uint64_t len;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrivateProfileSectionW(LPCWSTR section, LPWSTR buffer, DWORD len, LPCWSTR filename)
{
    struct qemu_GetPrivateProfileSectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESECTIONW);
    call.section = (uint64_t)section;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileSectionW(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileSectionW *c = (struct qemu_GetPrivateProfileSectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileSectionW(QEMU_G2H(c->section), QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileSectionA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t buffer;
    uint64_t len;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrivateProfileSectionA(LPCSTR section, LPSTR buffer, DWORD len, LPCSTR filename)
{
    struct qemu_GetPrivateProfileSectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESECTIONA);
    call.section = (uint64_t)section;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileSectionA(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileSectionA *c = (struct qemu_GetPrivateProfileSectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileSectionA(QEMU_G2H(c->section), QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetProfileSectionA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProfileSectionA(LPCSTR section, LPSTR buffer, DWORD len)
{
    struct qemu_GetProfileSectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROFILESECTIONA);
    call.section = (uint64_t)section;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProfileSectionA(struct qemu_syscall *call)
{
    struct qemu_GetProfileSectionA *c = (struct qemu_GetProfileSectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProfileSectionA(QEMU_G2H(c->section), QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_GetProfileSectionW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProfileSectionW(LPCWSTR section, LPWSTR buffer, DWORD len)
{
    struct qemu_GetProfileSectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROFILESECTIONW);
    call.section = (uint64_t)section;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProfileSectionW(struct qemu_syscall *call)
{
    struct qemu_GetProfileSectionW *c = (struct qemu_GetProfileSectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProfileSectionW(QEMU_G2H(c->section), QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_WritePrivateProfileStringW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t string;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrivateProfileStringW(LPCWSTR section, LPCWSTR entry, LPCWSTR string, LPCWSTR filename)
{
    struct qemu_WritePrivateProfileStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRIVATEPROFILESTRINGW);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.string = (uint64_t)string;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrivateProfileStringW(struct qemu_syscall *call)
{
    struct qemu_WritePrivateProfileStringW *c = (struct qemu_WritePrivateProfileStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrivateProfileStringW(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->string), QEMU_G2H(c->filename));
}

#endif

struct qemu_WritePrivateProfileStringA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t entry;
    uint64_t string;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrivateProfileStringA(LPCSTR section, LPCSTR entry, LPCSTR string, LPCSTR filename)
{
    struct qemu_WritePrivateProfileStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRIVATEPROFILESTRINGA);
    call.section = (uint64_t)section;
    call.entry = (uint64_t)entry;
    call.string = (uint64_t)string;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrivateProfileStringA(struct qemu_syscall *call)
{
    struct qemu_WritePrivateProfileStringA *c = (struct qemu_WritePrivateProfileStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrivateProfileStringA(QEMU_G2H(c->section), QEMU_G2H(c->entry), QEMU_G2H(c->string), QEMU_G2H(c->filename));
}

#endif

struct qemu_WritePrivateProfileSectionW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t string;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrivateProfileSectionW(LPCWSTR section, LPCWSTR string, LPCWSTR filename)
{
    struct qemu_WritePrivateProfileSectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRIVATEPROFILESECTIONW);
    call.section = (uint64_t)section;
    call.string = (uint64_t)string;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrivateProfileSectionW(struct qemu_syscall *call)
{
    struct qemu_WritePrivateProfileSectionW *c = (struct qemu_WritePrivateProfileSectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrivateProfileSectionW(QEMU_G2H(c->section), QEMU_G2H(c->string), QEMU_G2H(c->filename));
}

#endif

struct qemu_WritePrivateProfileSectionA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t string;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrivateProfileSectionA(LPCSTR section, LPCSTR string, LPCSTR filename)
{
    struct qemu_WritePrivateProfileSectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRIVATEPROFILESECTIONA);
    call.section = (uint64_t)section;
    call.string = (uint64_t)string;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrivateProfileSectionA(struct qemu_syscall *call)
{
    struct qemu_WritePrivateProfileSectionA *c = (struct qemu_WritePrivateProfileSectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrivateProfileSectionA(QEMU_G2H(c->section), QEMU_G2H(c->string), QEMU_G2H(c->filename));
}

#endif

struct qemu_WriteProfileSectionA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t keys_n_values;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteProfileSectionA(LPCSTR section, LPCSTR keys_n_values)
{
    struct qemu_WriteProfileSectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPROFILESECTIONA);
    call.section = (uint64_t)section;
    call.keys_n_values = (uint64_t)keys_n_values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteProfileSectionA(struct qemu_syscall *call)
{
    struct qemu_WriteProfileSectionA *c = (struct qemu_WriteProfileSectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteProfileSectionA(QEMU_G2H(c->section), QEMU_G2H(c->keys_n_values));
}

#endif

struct qemu_WriteProfileSectionW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t keys_n_values;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteProfileSectionW(LPCWSTR section, LPCWSTR keys_n_values)
{
    struct qemu_WriteProfileSectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPROFILESECTIONW);
    call.section = (uint64_t)section;
    call.keys_n_values = (uint64_t)keys_n_values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteProfileSectionW(struct qemu_syscall *call)
{
    struct qemu_WriteProfileSectionW *c = (struct qemu_WriteProfileSectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteProfileSectionW(QEMU_G2H(c->section), QEMU_G2H(c->keys_n_values));
}

#endif

struct qemu_GetPrivateProfileSectionNamesW
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t size;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrivateProfileSectionNamesW(LPWSTR buffer, DWORD size, LPCWSTR filename)
{
    struct qemu_GetPrivateProfileSectionNamesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESECTIONNAMESW);
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileSectionNamesW(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileSectionNamesW *c = (struct qemu_GetPrivateProfileSectionNamesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileSectionNamesW(QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileSectionNamesA
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t size;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrivateProfileSectionNamesA(LPSTR buffer, DWORD size, LPCSTR filename)
{
    struct qemu_GetPrivateProfileSectionNamesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESECTIONNAMESA);
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileSectionNamesA(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileSectionNamesA *c = (struct qemu_GetPrivateProfileSectionNamesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileSectionNamesA(QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileStructW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t key;
    uint64_t buf;
    uint64_t len;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrivateProfileStructW (LPCWSTR section, LPCWSTR key, LPVOID buf, UINT len, LPCWSTR filename)
{
    struct qemu_GetPrivateProfileStructW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESTRUCTW);
    call.section = (uint64_t)section;
    call.key = (uint64_t)key;
    call.buf = (uint64_t)buf;
    call.len = (uint64_t)len;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileStructW(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileStructW *c = (struct qemu_GetPrivateProfileStructW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileStructW(QEMU_G2H(c->section), QEMU_G2H(c->key), QEMU_G2H(c->buf), c->len, QEMU_G2H(c->filename));
}

#endif

struct qemu_GetPrivateProfileStructA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t key;
    uint64_t buffer;
    uint64_t len;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrivateProfileStructA (LPCSTR section, LPCSTR key, LPVOID buffer, UINT len, LPCSTR filename)
{
    struct qemu_GetPrivateProfileStructA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEPROFILESTRUCTA);
    call.section = (uint64_t)section;
    call.key = (uint64_t)key;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateProfileStructA(struct qemu_syscall *call)
{
    struct qemu_GetPrivateProfileStructA *c = (struct qemu_GetPrivateProfileStructA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateProfileStructA(QEMU_G2H(c->section), QEMU_G2H(c->key), QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->filename));
}

#endif

struct qemu_WritePrivateProfileStructW
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t key;
    uint64_t buf;
    uint64_t bufsize;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrivateProfileStructW (LPCWSTR section, LPCWSTR key, LPVOID buf, UINT bufsize, LPCWSTR filename)
{
    struct qemu_WritePrivateProfileStructW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRIVATEPROFILESTRUCTW);
    call.section = (uint64_t)section;
    call.key = (uint64_t)key;
    call.buf = (uint64_t)buf;
    call.bufsize = (uint64_t)bufsize;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrivateProfileStructW(struct qemu_syscall *call)
{
    struct qemu_WritePrivateProfileStructW *c = (struct qemu_WritePrivateProfileStructW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrivateProfileStructW(QEMU_G2H(c->section), QEMU_G2H(c->key), QEMU_G2H(c->buf), c->bufsize, QEMU_G2H(c->filename));
}

#endif

struct qemu_WritePrivateProfileStructA
{
    struct qemu_syscall super;
    uint64_t section;
    uint64_t key;
    uint64_t buf;
    uint64_t bufsize;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrivateProfileStructA (LPCSTR section, LPCSTR key, LPVOID buf, UINT bufsize, LPCSTR filename)
{
    struct qemu_WritePrivateProfileStructA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRIVATEPROFILESTRUCTA);
    call.section = (uint64_t)section;
    call.key = (uint64_t)key;
    call.buf = (uint64_t)buf;
    call.bufsize = (uint64_t)bufsize;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrivateProfileStructA(struct qemu_syscall *call)
{
    struct qemu_WritePrivateProfileStructA *c = (struct qemu_WritePrivateProfileStructA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrivateProfileStructA(QEMU_G2H(c->section), QEMU_G2H(c->key), QEMU_G2H(c->buf), c->bufsize, QEMU_G2H(c->filename));
}

#endif

struct qemu_OpenProfileUserMapping
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI OpenProfileUserMapping(void)
{
    struct qemu_OpenProfileUserMapping call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENPROFILEUSERMAPPING);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add OpenProfileUserMapping to Wine headers? */
extern BOOL WINAPI OpenProfileUserMapping(void);
void qemu_OpenProfileUserMapping(struct qemu_syscall *call)
{
    struct qemu_OpenProfileUserMapping *c = (struct qemu_OpenProfileUserMapping *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenProfileUserMapping();
}

#endif

struct qemu_CloseProfileUserMapping
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseProfileUserMapping(void)
{
    struct qemu_CloseProfileUserMapping call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEPROFILEUSERMAPPING);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CloseProfileUserMapping to Wine headers? */
extern BOOL WINAPI CloseProfileUserMapping(void);
void qemu_CloseProfileUserMapping(struct qemu_syscall *call)
{
    struct qemu_CloseProfileUserMapping *c = (struct qemu_CloseProfileUserMapping *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseProfileUserMapping();
}

#endif

