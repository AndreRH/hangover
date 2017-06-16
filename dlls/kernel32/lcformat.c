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

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_GetDateFormat
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t flags;
    uint64_t date;
    uint64_t format;
    uint64_t datestr;
    uint64_t cchDate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetDateFormatA(LCID locale, DWORD flags, CONST SYSTEMTIME *date, const CHAR *format, CHAR *datestr, int cchDate)
{
    struct qemu_GetDateFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDATEFORMATA);
    call.locale = locale;
    call.flags = flags;
    call.date = (uint64_t)date;
    call.format = (uint64_t)format;
    call.datestr = (uint64_t)datestr;
    call.cchDate = cchDate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI int WINAPI GetDateFormatW(LCID locale, DWORD flags, CONST SYSTEMTIME *date, const WCHAR *format, WCHAR *datestr, int cchDate)
{
    struct qemu_GetDateFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDATEFORMATW);
    call.locale = locale;
    call.flags = flags;
    call.date = (uint64_t)date;
    call.format = (uint64_t)format;
    call.datestr = (uint64_t)datestr;
    call.cchDate = cchDate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDateFormatA(struct qemu_syscall *call)
{
    struct qemu_GetDateFormat *c = (struct qemu_GetDateFormat *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetDateFormatA(c->locale, c->flags, QEMU_G2H(c->date),
            QEMU_G2H(c->format), QEMU_G2H(c->datestr), c->cchDate);
}

void qemu_GetDateFormatW(struct qemu_syscall *call)
{
    struct qemu_GetDateFormat *c = (struct qemu_GetDateFormat *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetDateFormatW(c->locale, c->flags, QEMU_G2H(c->date),
            QEMU_G2H(c->format), QEMU_G2H(c->datestr), c->cchDate);
}

#endif
