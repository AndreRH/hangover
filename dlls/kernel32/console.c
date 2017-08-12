/*
 * Copyright 2017 André Hentschel
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
#include <wincon.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetConsoleWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI GetConsoleWindow(VOID)
{
    struct qemu_GetConsoleWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetConsoleWindow(struct qemu_syscall *call)
{
    struct qemu_GetConsoleWindow *c = (struct qemu_GetConsoleWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetConsoleWindow();
}

#endif

struct qemu_GetConsoleCP
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetConsoleCP(VOID)
{
    struct qemu_GetConsoleCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLECP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleCP(struct qemu_syscall *call)
{
    struct qemu_GetConsoleCP *c = (struct qemu_GetConsoleCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleCP();
}

#endif

struct qemu_SetConsoleCP
{
    struct qemu_syscall super;
    uint64_t cp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleCP(UINT cp)
{
    struct qemu_SetConsoleCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLECP);
    call.cp = (uint64_t)cp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleCP(struct qemu_syscall *call)
{
    struct qemu_SetConsoleCP *c = (struct qemu_SetConsoleCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleCP(c->cp);
}

#endif

struct qemu_GetConsoleOutputCP
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetConsoleOutputCP(VOID)
{
    struct qemu_GetConsoleOutputCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEOUTPUTCP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleOutputCP(struct qemu_syscall *call)
{
    struct qemu_GetConsoleOutputCP *c = (struct qemu_GetConsoleOutputCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleOutputCP();
}

#endif

struct qemu_SetConsoleOutputCP
{
    struct qemu_syscall super;
    uint64_t cp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleOutputCP(UINT cp)
{
    struct qemu_SetConsoleOutputCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEOUTPUTCP);
    call.cp = (uint64_t)cp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleOutputCP(struct qemu_syscall *call)
{
    struct qemu_SetConsoleOutputCP *c = (struct qemu_SetConsoleOutputCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleOutputCP(c->cp);
}

#endif

struct qemu_Beep
{
    struct qemu_syscall super;
    uint64_t dwFreq;
    uint64_t dwDur;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Beep(DWORD dwFreq, DWORD dwDur)
{
    struct qemu_Beep call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BEEP);
    call.dwFreq = (uint64_t)dwFreq;
    call.dwDur = (uint64_t)dwDur;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Beep(struct qemu_syscall *call)
{
    struct qemu_Beep *c = (struct qemu_Beep *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Beep(c->dwFreq, c->dwDur);
}

#endif

struct qemu_OpenConsoleW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t access;
    uint64_t inherit;
    uint64_t creation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenConsoleW(LPCWSTR name, DWORD access, BOOL inherit, DWORD creation)
{
    struct qemu_OpenConsoleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENCONSOLEW);
    call.name = (uint64_t)name;
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.creation = (uint64_t)creation;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

/* TODO: Add OpenConsoleW to Wine headers? */
extern HANDLE WINAPI OpenConsoleW(LPCWSTR name, DWORD access, BOOL inherit, DWORD creation);
void qemu_OpenConsoleW(struct qemu_syscall *call)
{
    struct qemu_OpenConsoleW *c = (struct qemu_OpenConsoleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenConsoleW(QEMU_G2H(c->name), c->access, c->inherit, c->creation);
}

#endif

struct qemu_VerifyConsoleIoHandle
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerifyConsoleIoHandle(HANDLE handle)
{
    struct qemu_VerifyConsoleIoHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERIFYCONSOLEIOHANDLE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add VerifyConsoleIoHandle to Wine headers? */
extern BOOL WINAPI VerifyConsoleIoHandle(HANDLE handle);
void qemu_VerifyConsoleIoHandle(struct qemu_syscall *call)
{
    struct qemu_VerifyConsoleIoHandle *c = (struct qemu_VerifyConsoleIoHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerifyConsoleIoHandle(QEMU_G2H(c->handle));
}

#endif

struct qemu_DuplicateConsoleHandle
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t inherit;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI DuplicateConsoleHandle(HANDLE handle, DWORD access, BOOL inherit, DWORD options)
{
    struct qemu_DuplicateConsoleHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DUPLICATECONSOLEHANDLE);
    call.handle = (uint64_t)handle;
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.options = (uint64_t)options;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

/* TODO: Add DuplicateConsoleHandle to Wine headers? */
extern HANDLE WINAPI DuplicateConsoleHandle(HANDLE handle, DWORD access, BOOL inherit, DWORD options);
void qemu_DuplicateConsoleHandle(struct qemu_syscall *call)
{
    struct qemu_DuplicateConsoleHandle *c = (struct qemu_DuplicateConsoleHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)DuplicateConsoleHandle(QEMU_G2H(c->handle), c->access, c->inherit, c->options);
}

#endif

struct qemu_CloseConsoleHandle
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseConsoleHandle(HANDLE handle)
{
    struct qemu_CloseConsoleHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSECONSOLEHANDLE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CloseConsoleHandle to Wine headers? */
extern BOOL WINAPI CloseConsoleHandle(HANDLE handle);
void qemu_CloseConsoleHandle(struct qemu_syscall *call)
{
    struct qemu_CloseConsoleHandle *c = (struct qemu_CloseConsoleHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseConsoleHandle(QEMU_G2H(c->handle));
}

#endif

struct qemu_GetConsoleInputWaitHandle
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetConsoleInputWaitHandle(void)
{
    struct qemu_GetConsoleInputWaitHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEINPUTWAITHANDLE);

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

/* TODO: Add GetConsoleInputWaitHandle to Wine headers? */
extern HANDLE WINAPI GetConsoleInputWaitHandle(void);
void qemu_GetConsoleInputWaitHandle(struct qemu_syscall *call)
{
    struct qemu_GetConsoleInputWaitHandle *c = (struct qemu_GetConsoleInputWaitHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetConsoleInputWaitHandle();
}

#endif

struct qemu_WriteConsoleInputA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
    uint64_t written;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleInputA(HANDLE handle, const INPUT_RECORD *buffer, DWORD count, LPDWORD written)
{
    struct qemu_WriteConsoleInputA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEINPUTA);
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;
    call.written = (uint64_t)written;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleInputA(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleInputA *c = (struct qemu_WriteConsoleInputA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteConsoleInputA(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->count, QEMU_G2H(c->written));
}

#endif

struct qemu_WriteConsoleInputW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
    uint64_t written;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleInputW(HANDLE handle, const INPUT_RECORD *buffer, DWORD count, LPDWORD written)
{
    struct qemu_WriteConsoleInputW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEINPUTW);
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;
    call.written = (uint64_t)written;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleInputW(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleInputW *c = (struct qemu_WriteConsoleInputW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteConsoleInputW(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->count, QEMU_G2H(c->written));
}

#endif

struct qemu_WriteConsoleOutputA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpBuffer;
    uint64_t sizeX;
    uint64_t sizeY;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t region;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleOutputA(HANDLE hConsoleOutput, const CHAR_INFO *lpBuffer, COORD size, COORD coord, SMALL_RECT *region)
{
    struct qemu_WriteConsoleOutputA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEOUTPUTA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.sizeX = size.X;
    call.sizeY = size.Y;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.region = (uint64_t)region;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleOutputA(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleOutputA *c = (struct qemu_WriteConsoleOutputA *)call;
    COORD size, coord;
    WINE_FIXME("Unverified!\n");
    size.Y = c->sizeX;
    size.Y = c->sizeY;
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = WriteConsoleOutputA(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpBuffer), size, coord, QEMU_G2H(c->region));
}

#endif

struct qemu_WriteConsoleOutputW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpBuffer;
    uint64_t sizeX;
    uint64_t sizeY;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t region;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleOutputW(HANDLE hConsoleOutput, const CHAR_INFO *lpBuffer, COORD size, COORD coord, SMALL_RECT *region)
{
    struct qemu_WriteConsoleOutputW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEOUTPUTW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.sizeX = size.X;
    call.sizeY = size.Y;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.region = (uint64_t)region;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleOutputW(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleOutputW *c = (struct qemu_WriteConsoleOutputW *)call;
    COORD size, coord;
    WINE_FIXME("Unverified!\n");
    size.Y = c->sizeX;
    size.Y = c->sizeY;
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = WriteConsoleOutputW(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpBuffer), size, coord, QEMU_G2H(c->region));
}

#endif

struct qemu_WriteConsoleOutputCharacterA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t str;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t lpNumCharsWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleOutputCharacterA(HANDLE hConsoleOutput, LPCSTR str, DWORD length, COORD coord, LPDWORD lpNumCharsWritten)
{
    struct qemu_WriteConsoleOutputCharacterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEOUTPUTCHARACTERA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.str = (uint64_t)str;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.lpNumCharsWritten = (uint64_t)lpNumCharsWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleOutputCharacterA(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleOutputCharacterA *c = (struct qemu_WriteConsoleOutputCharacterA *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = WriteConsoleOutputCharacterA(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->str), c->length, coord, QEMU_G2H(c->lpNumCharsWritten));
}

#endif

struct qemu_WriteConsoleOutputAttribute
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t attr;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t lpNumAttrsWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleOutputAttribute(HANDLE hConsoleOutput, const WORD *attr, DWORD length, COORD coord, LPDWORD lpNumAttrsWritten)
{
    struct qemu_WriteConsoleOutputAttribute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEOUTPUTATTRIBUTE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.attr = (uint64_t)attr;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.lpNumAttrsWritten = (uint64_t)lpNumAttrsWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleOutputAttribute(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleOutputAttribute *c = (struct qemu_WriteConsoleOutputAttribute *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = WriteConsoleOutputAttribute(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->attr), c->length, coord, QEMU_G2H(c->lpNumAttrsWritten));
}

#endif

struct qemu_FillConsoleOutputCharacterA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t ch;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t lpNumCharsWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FillConsoleOutputCharacterA(HANDLE hConsoleOutput, CHAR ch, DWORD length, COORD coord, LPDWORD lpNumCharsWritten)
{
    struct qemu_FillConsoleOutputCharacterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILLCONSOLEOUTPUTCHARACTERA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.ch = (uint64_t)ch;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.lpNumCharsWritten = (uint64_t)lpNumCharsWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FillConsoleOutputCharacterA(struct qemu_syscall *call)
{
    struct qemu_FillConsoleOutputCharacterA *c = (struct qemu_FillConsoleOutputCharacterA *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = FillConsoleOutputCharacterA(QEMU_G2H(c->hConsoleOutput), c->ch, c->length, coord, QEMU_G2H(c->lpNumCharsWritten));
}

#endif

struct qemu_FillConsoleOutputCharacterW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t ch;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t lpNumCharsWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FillConsoleOutputCharacterW(HANDLE hConsoleOutput, WCHAR ch, DWORD length, COORD coord, LPDWORD lpNumCharsWritten)
{
    struct qemu_FillConsoleOutputCharacterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILLCONSOLEOUTPUTCHARACTERW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.ch = (uint64_t)ch;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.lpNumCharsWritten = (uint64_t)lpNumCharsWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FillConsoleOutputCharacterW(struct qemu_syscall *call)
{
    struct qemu_FillConsoleOutputCharacterW *c = (struct qemu_FillConsoleOutputCharacterW *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = FillConsoleOutputCharacterW(QEMU_G2H(c->hConsoleOutput), c->ch, c->length, coord, QEMU_G2H(c->lpNumCharsWritten));
}

#endif

struct qemu_FillConsoleOutputAttribute
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t attr;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t lpNumAttrsWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FillConsoleOutputAttribute(HANDLE hConsoleOutput, WORD attr, DWORD length, COORD coord, LPDWORD lpNumAttrsWritten)
{
    struct qemu_FillConsoleOutputAttribute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILLCONSOLEOUTPUTATTRIBUTE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.attr = (uint64_t)attr;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.lpNumAttrsWritten = (uint64_t)lpNumAttrsWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FillConsoleOutputAttribute(struct qemu_syscall *call)
{
    struct qemu_FillConsoleOutputAttribute *c = (struct qemu_FillConsoleOutputAttribute *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = FillConsoleOutputAttribute(QEMU_G2H(c->hConsoleOutput), c->attr, c->length, coord, QEMU_G2H(c->lpNumAttrsWritten));
}

#endif

struct qemu_ReadConsoleOutputCharacterA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpstr;
    uint64_t count;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t read_count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleOutputCharacterA(HANDLE hConsoleOutput, LPSTR lpstr, DWORD count, COORD coord, LPDWORD read_count)
{
    struct qemu_ReadConsoleOutputCharacterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEOUTPUTCHARACTERA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpstr = (uint64_t)lpstr;
    call.count = (uint64_t)count;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.read_count = (uint64_t)read_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleOutputCharacterA(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleOutputCharacterA *c = (struct qemu_ReadConsoleOutputCharacterA *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = ReadConsoleOutputCharacterA(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpstr), c->count, coord, QEMU_G2H(c->read_count));
}

#endif

struct qemu_ReadConsoleOutputCharacterW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t buffer;
    uint64_t count;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t read_count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleOutputCharacterW(HANDLE hConsoleOutput, LPWSTR buffer, DWORD count, COORD coord, LPDWORD read_count)
{
    struct qemu_ReadConsoleOutputCharacterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEOUTPUTCHARACTERW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.read_count = (uint64_t)read_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleOutputCharacterW(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleOutputCharacterW *c = (struct qemu_ReadConsoleOutputCharacterW *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = ReadConsoleOutputCharacterW(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->buffer), c->count, coord, QEMU_G2H(c->read_count));
}

#endif

struct qemu_ReadConsoleOutputAttribute
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpAttribute;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t read_count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleOutputAttribute(HANDLE hConsoleOutput, LPWORD lpAttribute, DWORD length, COORD coord, LPDWORD read_count)
{
    struct qemu_ReadConsoleOutputAttribute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEOUTPUTATTRIBUTE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpAttribute = (uint64_t)lpAttribute;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.read_count = (uint64_t)read_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleOutputAttribute(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleOutputAttribute *c = (struct qemu_ReadConsoleOutputAttribute *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = ReadConsoleOutputAttribute(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpAttribute), c->length, coord, QEMU_G2H(c->read_count));
}

#endif

struct qemu_ReadConsoleOutputA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpBuffer;
    uint64_t sizeX;
    uint64_t sizeY;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t region;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleOutputA(HANDLE hConsoleOutput, CHAR_INFO *lpBuffer, COORD size, COORD coord, SMALL_RECT *region)
{
    struct qemu_ReadConsoleOutputA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEOUTPUTA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.sizeX = size.X;
    call.sizeY = size.Y;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.region = (uint64_t)region;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleOutputA(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleOutputA *c = (struct qemu_ReadConsoleOutputA *)call;
    COORD coord, size;
    WINE_FIXME("Unverified!\n");
    size.X = c->sizeX;
    size.Y = c->sizeY;
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = ReadConsoleOutputA(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpBuffer), size, coord, QEMU_G2H(c->region));
}

#endif

struct qemu_ReadConsoleOutputW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpBuffer;
    uint64_t sizeX;
    uint64_t sizeY;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t region;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleOutputW(HANDLE hConsoleOutput, CHAR_INFO *lpBuffer, COORD size, COORD coord, SMALL_RECT *region)
{
    struct qemu_ReadConsoleOutputW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEOUTPUTW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.sizeX = size.X;
    call.sizeY = size.Y;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.region = (uint64_t)region;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleOutputW(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleOutputW *c = (struct qemu_ReadConsoleOutputW *)call;
    COORD size, coord;
    WINE_FIXME("Unverified!\n");
    size.X = c->sizeX;
    size.Y = c->sizeY;
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = ReadConsoleOutputW(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpBuffer), size, coord, QEMU_G2H(c->region));
}

#endif

struct qemu_ReadConsoleInputA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
    uint64_t pRead;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleInputA(HANDLE handle, PINPUT_RECORD buffer, DWORD count, LPDWORD pRead)
{
    struct qemu_ReadConsoleInputA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEINPUTA);
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;
    call.pRead = (uint64_t)pRead;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleInputA(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleInputA *c = (struct qemu_ReadConsoleInputA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadConsoleInputA(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->count, QEMU_G2H(c->pRead));
}

#endif

struct qemu_PeekConsoleInputA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
    uint64_t pRead;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PeekConsoleInputA(HANDLE handle, PINPUT_RECORD buffer, DWORD count, LPDWORD pRead)
{
    struct qemu_PeekConsoleInputA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PEEKCONSOLEINPUTA);
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;
    call.pRead = (uint64_t)pRead;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekConsoleInputA(struct qemu_syscall *call)
{
    struct qemu_PeekConsoleInputA *c = (struct qemu_PeekConsoleInputA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PeekConsoleInputA(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->count, QEMU_G2H(c->pRead));
}

#endif

struct qemu_PeekConsoleInputW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
    uint64_t read;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PeekConsoleInputW(HANDLE handle, PINPUT_RECORD buffer, DWORD count, LPDWORD read)
{
    struct qemu_PeekConsoleInputW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PEEKCONSOLEINPUTW);
    call.handle = (uint64_t)handle;
    call.buffer = (uint64_t)buffer;
    call.count = (uint64_t)count;
    call.read = (uint64_t)read;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PeekConsoleInputW(struct qemu_syscall *call)
{
    struct qemu_PeekConsoleInputW *c = (struct qemu_PeekConsoleInputW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PeekConsoleInputW(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->count, QEMU_G2H(c->read));
}

#endif

struct qemu_GetNumberOfConsoleInputEvents
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t nrofevents;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumberOfConsoleInputEvents(HANDLE handle, LPDWORD nrofevents)
{
    struct qemu_GetNumberOfConsoleInputEvents call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBEROFCONSOLEINPUTEVENTS);
    call.handle = (uint64_t)handle;
    call.nrofevents = (uint64_t)nrofevents;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberOfConsoleInputEvents(struct qemu_syscall *call)
{
    struct qemu_GetNumberOfConsoleInputEvents *c = (struct qemu_GetNumberOfConsoleInputEvents *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberOfConsoleInputEvents(QEMU_G2H(c->handle), QEMU_G2H(c->nrofevents));
}

#endif

struct qemu_FlushConsoleInputBuffer
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlushConsoleInputBuffer(HANDLE handle)
{
    struct qemu_FlushConsoleInputBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHCONSOLEINPUTBUFFER);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushConsoleInputBuffer(struct qemu_syscall *call)
{
    struct qemu_FlushConsoleInputBuffer *c = (struct qemu_FlushConsoleInputBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FlushConsoleInputBuffer(QEMU_G2H(c->handle));
}

#endif

struct qemu_SetConsoleTitleA
{
    struct qemu_syscall super;
    uint64_t title;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleTitleA(LPCSTR title)
{
    struct qemu_SetConsoleTitleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLETITLEA);
    call.title = (uint64_t)title;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleTitleA(struct qemu_syscall *call)
{
    struct qemu_SetConsoleTitleA *c = (struct qemu_SetConsoleTitleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleTitleA(QEMU_G2H(c->title));
}

#endif

struct qemu_GetConsoleKeyboardLayoutNameA
{
    struct qemu_syscall super;
    uint64_t layoutName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleKeyboardLayoutNameA(LPSTR layoutName)
{
    struct qemu_GetConsoleKeyboardLayoutNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEKEYBOARDLAYOUTNAMEA);
    call.layoutName = (uint64_t)layoutName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleKeyboardLayoutNameA to Wine headers? */
extern BOOL WINAPI GetConsoleKeyboardLayoutNameA(LPSTR layoutName);
void qemu_GetConsoleKeyboardLayoutNameA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleKeyboardLayoutNameA *c = (struct qemu_GetConsoleKeyboardLayoutNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleKeyboardLayoutNameA(QEMU_G2H(c->layoutName));
}

#endif

struct qemu_GetConsoleKeyboardLayoutNameW
{
    struct qemu_syscall super;
    uint64_t layoutName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleKeyboardLayoutNameW(LPWSTR layoutName)
{
    struct qemu_GetConsoleKeyboardLayoutNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEKEYBOARDLAYOUTNAMEW);
    call.layoutName = (uint64_t)layoutName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleKeyboardLayoutNameW to Wine headers? */
extern BOOL WINAPI GetConsoleKeyboardLayoutNameW(LPWSTR layoutName);
void qemu_GetConsoleKeyboardLayoutNameW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleKeyboardLayoutNameW *c = (struct qemu_GetConsoleKeyboardLayoutNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleKeyboardLayoutNameW(QEMU_G2H(c->layoutName));
}

#endif

struct qemu_GetConsoleInputExeNameW
{
    struct qemu_syscall super;
    uint64_t buflen;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleInputExeNameW(DWORD buflen, LPWSTR buffer)
{
    struct qemu_GetConsoleInputExeNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEINPUTEXENAMEW);
    call.buflen = (uint64_t)buflen;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleInputExeNameW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleInputExeNameW *c = (struct qemu_GetConsoleInputExeNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleInputExeNameW(c->buflen, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetConsoleInputExeNameA
{
    struct qemu_syscall super;
    uint64_t buflen;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleInputExeNameA(DWORD buflen, LPSTR buffer)
{
    struct qemu_GetConsoleInputExeNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEINPUTEXENAMEA);
    call.buflen = (uint64_t)buflen;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleInputExeNameA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleInputExeNameA *c = (struct qemu_GetConsoleInputExeNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleInputExeNameA(c->buflen, QEMU_G2H(c->buffer));
}

#endif

struct qemu_GetConsoleTitleA
{
    struct qemu_syscall super;
    uint64_t title;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleTitleA(LPSTR title, DWORD size)
{
    struct qemu_GetConsoleTitleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLETITLEA);
    call.title = (uint64_t)title;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleTitleA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleTitleA *c = (struct qemu_GetConsoleTitleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleTitleA(QEMU_G2H(c->title), c->size);
}

#endif

struct qemu_GetConsoleTitleW
{
    struct qemu_syscall super;
    uint64_t title;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleTitleW(LPWSTR title, DWORD size)
{
    struct qemu_GetConsoleTitleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLETITLEW);
    call.title = (uint64_t)title;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleTitleW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleTitleW *c = (struct qemu_GetConsoleTitleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleTitleW(QEMU_G2H(c->title), c->size);
}

#endif

struct qemu_GetLargestConsoleWindowSize
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI COORD WINAPI GetLargestConsoleWindowSize(HANDLE hConsoleOutput)
{
    COORD ret;
    struct qemu_GetLargestConsoleWindowSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLARGESTCONSOLEWINDOWSIZE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;

    qemu_syscall(&call.super);

    ret.X = 0;
    ret.Y = 0;
    return ret;
}

#else

void qemu_GetLargestConsoleWindowSize(struct qemu_syscall *call)
{
    struct qemu_GetLargestConsoleWindowSize *c = (struct qemu_GetLargestConsoleWindowSize *)call;
    WINE_FIXME("Unverified!\n");
    GetLargestConsoleWindowSize(QEMU_G2H(c->hConsoleOutput));
}

#endif

struct qemu_FreeConsole
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeConsole(VOID)
{
    struct qemu_FreeConsole call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREECONSOLE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeConsole(struct qemu_syscall *call)
{
    struct qemu_FreeConsole *c = (struct qemu_FreeConsole *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeConsole();
}

#endif

struct qemu_AllocConsole
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AllocConsole(void)
{
    struct qemu_AllocConsole call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCCONSOLE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AllocConsole(struct qemu_syscall *call)
{
    struct qemu_AllocConsole *c = (struct qemu_AllocConsole *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocConsole();
}

#endif

struct qemu_ReadConsoleA
{
    struct qemu_syscall super;
    uint64_t hConsoleInput;
    uint64_t lpBuffer;
    uint64_t nNumberOfCharsToRead;
    uint64_t lpNumberOfCharsRead;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleA(HANDLE hConsoleInput, LPVOID lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead, LPVOID lpReserved)
{
    struct qemu_ReadConsoleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEA);
    call.hConsoleInput = (uint64_t)hConsoleInput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nNumberOfCharsToRead = (uint64_t)nNumberOfCharsToRead;
    call.lpNumberOfCharsRead = (uint64_t)lpNumberOfCharsRead;
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleA(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleA *c = (struct qemu_ReadConsoleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadConsoleA(QEMU_G2H(c->hConsoleInput), QEMU_G2H(c->lpBuffer), c->nNumberOfCharsToRead, QEMU_G2H(c->lpNumberOfCharsRead), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_ReadConsoleW
{
    struct qemu_syscall super;
    uint64_t hConsoleInput;
    uint64_t lpBuffer;
    uint64_t nNumberOfCharsToRead;
    uint64_t lpNumberOfCharsRead;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleW(HANDLE hConsoleInput, LPVOID lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead, LPVOID lpReserved)
{
    struct qemu_ReadConsoleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEW);
    call.hConsoleInput = (uint64_t)hConsoleInput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nNumberOfCharsToRead = (uint64_t)nNumberOfCharsToRead;
    call.lpNumberOfCharsRead = (uint64_t)lpNumberOfCharsRead;
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleW(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleW *c = (struct qemu_ReadConsoleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadConsoleW(QEMU_G2H(c->hConsoleInput), QEMU_G2H(c->lpBuffer), c->nNumberOfCharsToRead, QEMU_G2H(c->lpNumberOfCharsRead), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_ReadConsoleInputW
{
    struct qemu_syscall super;
    uint64_t hConsoleInput;
    uint64_t lpBuffer;
    uint64_t nLength;
    uint64_t lpNumberOfEventsRead;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadConsoleInputW(HANDLE hConsoleInput, PINPUT_RECORD lpBuffer, DWORD nLength, LPDWORD lpNumberOfEventsRead)
{
    struct qemu_ReadConsoleInputW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READCONSOLEINPUTW);
    call.hConsoleInput = (uint64_t)hConsoleInput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nLength = (uint64_t)nLength;
    call.lpNumberOfEventsRead = (uint64_t)lpNumberOfEventsRead;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadConsoleInputW(struct qemu_syscall *call)
{
    struct qemu_ReadConsoleInputW *c = (struct qemu_ReadConsoleInputW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadConsoleInputW(QEMU_G2H(c->hConsoleInput), QEMU_G2H(c->lpBuffer), c->nLength, QEMU_G2H(c->lpNumberOfEventsRead));
}

#endif

struct qemu_WriteConsoleOutputCharacterW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t str;
    uint64_t length;
    uint64_t coordX;
    uint64_t coordY;
    uint64_t lpNumCharsWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleOutputCharacterW(HANDLE hConsoleOutput, LPCWSTR str, DWORD length, COORD coord, LPDWORD lpNumCharsWritten)
{
    struct qemu_WriteConsoleOutputCharacterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEOUTPUTCHARACTERW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.str = (uint64_t)str;
    call.length = (uint64_t)length;
    call.coordX = coord.X;
    call.coordY = coord.Y;
    call.lpNumCharsWritten = (uint64_t)lpNumCharsWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleOutputCharacterW(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleOutputCharacterW *c = (struct qemu_WriteConsoleOutputCharacterW *)call;
    COORD coord;
    WINE_FIXME("Unverified!\n");
    coord.X = c->coordX;
    coord.Y = c->coordY;
    c->super.iret = WriteConsoleOutputCharacterW(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->str), c->length, coord, QEMU_G2H(c->lpNumCharsWritten));
}

#endif

struct qemu_SetConsoleTitleW
{
    struct qemu_syscall super;
    uint64_t title;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleTitleW(LPCWSTR title)
{
    struct qemu_SetConsoleTitleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLETITLEW);
    call.title = (uint64_t)title;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleTitleW(struct qemu_syscall *call)
{
    struct qemu_SetConsoleTitleW *c = (struct qemu_SetConsoleTitleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleTitleW(QEMU_G2H(c->title));
}

#endif

struct qemu_GetNumberOfConsoleMouseButtons
{
    struct qemu_syscall super;
    uint64_t nrofbuttons;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumberOfConsoleMouseButtons(LPDWORD nrofbuttons)
{
    struct qemu_GetNumberOfConsoleMouseButtons call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBEROFCONSOLEMOUSEBUTTONS);
    call.nrofbuttons = (uint64_t)nrofbuttons;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberOfConsoleMouseButtons(struct qemu_syscall *call)
{
    struct qemu_GetNumberOfConsoleMouseButtons *c = (struct qemu_GetNumberOfConsoleMouseButtons *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberOfConsoleMouseButtons(QEMU_G2H(c->nrofbuttons));
}

#endif

struct qemu_SetConsoleInputExeNameW
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleInputExeNameW(LPCWSTR name)
{
    struct qemu_SetConsoleInputExeNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEINPUTEXENAMEW);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetConsoleInputExeNameW to Wine headers? */
extern BOOL WINAPI SetConsoleInputExeNameW(LPCWSTR name);
void qemu_SetConsoleInputExeNameW(struct qemu_syscall *call)
{
    struct qemu_SetConsoleInputExeNameW *c = (struct qemu_SetConsoleInputExeNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleInputExeNameW(QEMU_G2H(c->name));
}

#endif

struct qemu_SetConsoleInputExeNameA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleInputExeNameA(LPCSTR name)
{
    struct qemu_SetConsoleInputExeNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEINPUTEXENAMEA);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetConsoleInputExeNameA to Wine headers? */
extern BOOL WINAPI SetConsoleInputExeNameA(LPCSTR name);
void qemu_SetConsoleInputExeNameA(struct qemu_syscall *call)
{
    struct qemu_SetConsoleInputExeNameA *c = (struct qemu_SetConsoleInputExeNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleInputExeNameA(QEMU_G2H(c->name));
}

#endif

struct qemu_SetConsoleCtrlHandler
{
    struct qemu_syscall super;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

/* FIXME: Read this from the TEB. */
static PHANDLER_ROUTINE guest_handler;

static uint64_t WINAPI call_ctrl_handler(uint64_t type)
{
    uint64_t ret = FALSE;
    if (guest_handler)
        ret = guest_handler(type);

    return ret;
}

WINBASEAPI BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE routine, BOOL Add)
{
    struct qemu_SetConsoleCtrlHandler call;

    guest_handler = routine;

    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLECTRLHANDLER);
    call.wrapper = (uint64_t)call_ctrl_handler;
    qemu_syscall(&call.super);
}

#else

static void *console_handler_wrapper;

BOOL WINAPI qemu_console_handler(DWORD type)
{
    BOOL ret = FALSE;
    WINE_TRACE("(%x) calling %p.\n", type, console_handler_wrapper);

    ret = qemu_ops->qemu_execute(console_handler_wrapper, type);
    WINE_TRACE("Got return value %u from guest.\n", ret);

    return TRUE;
}

void qemu_SetConsoleCtrlHandler(struct qemu_syscall *call)
{
    struct qemu_SetConsoleCtrlHandler *c = (struct qemu_SetConsoleCtrlHandler *)call;
    WINE_FIXME("Only partial support.\n");

    if (!console_handler_wrapper)
    {
        SetConsoleCtrlHandler(qemu_console_handler, TRUE);
        console_handler_wrapper = QEMU_G2H(c->wrapper);
    }
    else if (console_handler_wrapper != QEMU_G2H(c->wrapper))
    {
        WINE_ERR("Got different console handler wrappers.\n");
    }
}

#endif

struct qemu_GenerateConsoleCtrlEvent
{
    struct qemu_syscall super;
    uint64_t dwCtrlEvent;
    uint64_t dwProcessGroupID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GenerateConsoleCtrlEvent(DWORD dwCtrlEvent, DWORD dwProcessGroupID)
{
    struct qemu_GenerateConsoleCtrlEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GENERATECONSOLECTRLEVENT);
    call.dwCtrlEvent = (uint64_t)dwCtrlEvent;
    call.dwProcessGroupID = (uint64_t)dwProcessGroupID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GenerateConsoleCtrlEvent(struct qemu_syscall *call)
{
    struct qemu_GenerateConsoleCtrlEvent *c = (struct qemu_GenerateConsoleCtrlEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GenerateConsoleCtrlEvent(c->dwCtrlEvent, c->dwProcessGroupID);
}

#endif

struct qemu_CreateConsoleScreenBuffer
{
    struct qemu_syscall super;
    uint64_t dwDesiredAccess;
    uint64_t dwShareMode;
    uint64_t sa;
    uint64_t dwFlags;
    uint64_t lpScreenBufferData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateConsoleScreenBuffer(DWORD dwDesiredAccess, DWORD dwShareMode, const SECURITY_ATTRIBUTES *sa, DWORD dwFlags, LPVOID lpScreenBufferData)
{
    struct qemu_CreateConsoleScreenBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATECONSOLESCREENBUFFER);
    call.dwDesiredAccess = (uint64_t)dwDesiredAccess;
    call.dwShareMode = (uint64_t)dwShareMode;
    call.sa = (uint64_t)sa;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpScreenBufferData = (uint64_t)lpScreenBufferData;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateConsoleScreenBuffer(struct qemu_syscall *call)
{
    struct qemu_CreateConsoleScreenBuffer *c = (struct qemu_CreateConsoleScreenBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateConsoleScreenBuffer(c->dwDesiredAccess, c->dwShareMode, QEMU_G2H(c->sa), c->dwFlags, QEMU_G2H(c->lpScreenBufferData));
}

#endif

struct qemu_GetConsoleScreenBufferInfo
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t csbi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleScreenBufferInfo(HANDLE hConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO *csbi)
{
    struct qemu_GetConsoleScreenBufferInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLESCREENBUFFERINFO);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.csbi = (uint64_t)csbi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleScreenBufferInfo(struct qemu_syscall *call)
{
    struct qemu_GetConsoleScreenBufferInfo *c = (struct qemu_GetConsoleScreenBufferInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleScreenBufferInfo(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->csbi));
}

#endif

struct qemu_SetConsoleActiveScreenBuffer
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleActiveScreenBuffer(HANDLE hConsoleOutput)
{
    struct qemu_SetConsoleActiveScreenBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEACTIVESCREENBUFFER);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleActiveScreenBuffer(struct qemu_syscall *call)
{
    struct qemu_SetConsoleActiveScreenBuffer *c = (struct qemu_SetConsoleActiveScreenBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleActiveScreenBuffer(QEMU_G2H(c->hConsoleOutput));
}

#endif

struct qemu_GetConsoleMode
{
    struct qemu_syscall super;
    uint64_t hcon;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleMode(HANDLE hcon, LPDWORD mode)
{
    struct qemu_GetConsoleMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEMODE);
    call.hcon = (uint64_t)hcon;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleMode(struct qemu_syscall *call)
{
    struct qemu_GetConsoleMode *c = (struct qemu_GetConsoleMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleMode(QEMU_G2H(c->hcon), QEMU_G2H(c->mode));
}

#endif

struct qemu_SetConsoleMode
{
    struct qemu_syscall super;
    uint64_t hcon;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleMode(HANDLE hcon, DWORD mode)
{
    struct qemu_SetConsoleMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEMODE);
    call.hcon = (uint64_t)hcon;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleMode(struct qemu_syscall *call)
{
    struct qemu_SetConsoleMode *c = (struct qemu_SetConsoleMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleMode(QEMU_G2H(c->hcon), c->mode);
}

#endif

struct qemu_WriteConsoleW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpBuffer;
    uint64_t nNumberOfCharsToWrite;
    uint64_t lpNumberOfCharsWritten;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleW(HANDLE hConsoleOutput, LPCVOID lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)
{
    struct qemu_WriteConsoleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nNumberOfCharsToWrite = (uint64_t)nNumberOfCharsToWrite;
    call.lpNumberOfCharsWritten = (uint64_t)lpNumberOfCharsWritten;
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleW(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleW *c = (struct qemu_WriteConsoleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteConsoleW(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpBuffer), c->nNumberOfCharsToWrite, QEMU_G2H(c->lpNumberOfCharsWritten), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_WriteConsoleA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpBuffer;
    uint64_t nNumberOfCharsToWrite;
    uint64_t lpNumberOfCharsWritten;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteConsoleA(HANDLE hConsoleOutput, LPCVOID lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)
{
    struct qemu_WriteConsoleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITECONSOLEA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.nNumberOfCharsToWrite = (uint64_t)nNumberOfCharsToWrite;
    call.lpNumberOfCharsWritten = (uint64_t)lpNumberOfCharsWritten;
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteConsoleA(struct qemu_syscall *call)
{
    struct qemu_WriteConsoleA *c = (struct qemu_WriteConsoleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteConsoleA(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpBuffer), c->nNumberOfCharsToWrite, QEMU_G2H(c->lpNumberOfCharsWritten), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SetConsoleCursorPosition
{
    struct qemu_syscall super;
    uint64_t hcon;
    uint64_t posX;
    uint64_t posY;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleCursorPosition(HANDLE hcon, COORD pos)
{
    struct qemu_SetConsoleCursorPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLECURSORPOSITION);
    call.hcon = (uint64_t)hcon;
    call.posX = pos.X;
    call.posY = pos.Y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleCursorPosition(struct qemu_syscall *call)
{
    struct qemu_SetConsoleCursorPosition *c = (struct qemu_SetConsoleCursorPosition *)call;
    COORD pos;
    WINE_FIXME("Unverified!\n");
    pos.X = c->posX;
    pos.Y = c->posY;
    c->super.iret = SetConsoleCursorPosition(QEMU_G2H(c->hcon), pos);
}

#endif

struct qemu_GetConsoleCursorInfo
{
    struct qemu_syscall super;
    uint64_t hCon;
    uint64_t cinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleCursorInfo(HANDLE hCon, CONSOLE_CURSOR_INFO *cinfo)
{
    struct qemu_GetConsoleCursorInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLECURSORINFO);
    call.hCon = (uint64_t)hCon;
    call.cinfo = (uint64_t)cinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleCursorInfo(struct qemu_syscall *call)
{
    struct qemu_GetConsoleCursorInfo *c = (struct qemu_GetConsoleCursorInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleCursorInfo(QEMU_G2H(c->hCon), QEMU_G2H(c->cinfo));
}

#endif

struct qemu_SetConsoleCursorInfo
{
    struct qemu_syscall super;
    uint64_t hCon;
    uint64_t cinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleCursorInfo(HANDLE hCon, const CONSOLE_CURSOR_INFO *cinfo)
{
    struct qemu_SetConsoleCursorInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLECURSORINFO);
    call.hCon = (uint64_t)hCon;
    call.cinfo = (uint64_t)cinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleCursorInfo(struct qemu_syscall *call)
{
    struct qemu_SetConsoleCursorInfo *c = (struct qemu_SetConsoleCursorInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleCursorInfo(QEMU_G2H(c->hCon), QEMU_G2H(c->cinfo));
}

#endif

struct qemu_SetConsoleWindowInfo
{
    struct qemu_syscall super;
    uint64_t hCon;
    uint64_t bAbsolute;
    uint64_t window;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleWindowInfo(HANDLE hCon, BOOL bAbsolute, const SMALL_RECT *window)
{
    struct qemu_SetConsoleWindowInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEWINDOWINFO);
    call.hCon = (uint64_t)hCon;
    call.bAbsolute = (uint64_t)bAbsolute;
    call.window = (uint64_t)window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleWindowInfo(struct qemu_syscall *call)
{
    struct qemu_SetConsoleWindowInfo *c = (struct qemu_SetConsoleWindowInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleWindowInfo(QEMU_G2H(c->hCon), c->bAbsolute, QEMU_G2H(c->window));
}

#endif

struct qemu_SetConsoleTextAttribute
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t wAttr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttr)
{
    struct qemu_SetConsoleTextAttribute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLETEXTATTRIBUTE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.wAttr = (uint64_t)wAttr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleTextAttribute(struct qemu_syscall *call)
{
    struct qemu_SetConsoleTextAttribute *c = (struct qemu_SetConsoleTextAttribute *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleTextAttribute(QEMU_G2H(c->hConsoleOutput), c->wAttr);
}

#endif

struct qemu_SetConsoleScreenBufferSize
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t dwSizeX;
    uint64_t dwSizeY;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleScreenBufferSize(HANDLE hConsoleOutput, COORD dwSize)
{
    struct qemu_SetConsoleScreenBufferSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLESCREENBUFFERSIZE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.dwSizeX = dwSize.X;
    call.dwSizeY = dwSize.Y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleScreenBufferSize(struct qemu_syscall *call)
{
    struct qemu_SetConsoleScreenBufferSize *c = (struct qemu_SetConsoleScreenBufferSize *)call;
    COORD size;
    WINE_FIXME("Unverified!\n");
    size.X = c->dwSizeX;
    size.Y = c->dwSizeY;
    c->super.iret = SetConsoleScreenBufferSize(QEMU_G2H(c->hConsoleOutput), size);
}

#endif

struct qemu_ScrollConsoleScreenBufferA
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpScrollRect;
    uint64_t lpClipRect;
    uint64_t dwDestOriginX;
    uint64_t dwDestOriginY;
    uint64_t lpFill;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ScrollConsoleScreenBufferA(HANDLE hConsoleOutput, const SMALL_RECT *lpScrollRect, const SMALL_RECT *lpClipRect, COORD dwDestOrigin, const CHAR_INFO *lpFill)
{
    struct qemu_ScrollConsoleScreenBufferA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCROLLCONSOLESCREENBUFFERA);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpScrollRect = (uint64_t)lpScrollRect;
    call.lpClipRect = (uint64_t)lpClipRect;
    call.dwDestOriginX = dwDestOrigin.X;
    call.dwDestOriginY = dwDestOrigin.Y;
    call.lpFill = (uint64_t)lpFill;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScrollConsoleScreenBufferA(struct qemu_syscall *call)
{
    struct qemu_ScrollConsoleScreenBufferA *c = (struct qemu_ScrollConsoleScreenBufferA *)call;
    COORD dwDestOrigin;
    WINE_FIXME("Unverified!\n");
    dwDestOrigin.X = c->dwDestOriginX;
    dwDestOrigin.Y = c->dwDestOriginY;
    c->super.iret = ScrollConsoleScreenBufferA(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpScrollRect), QEMU_G2H(c->lpClipRect), dwDestOrigin, QEMU_G2H(c->lpFill));
}

#endif

struct qemu_ScrollConsoleScreenBufferW
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t lpScrollRect;
    uint64_t lpClipRect;
    uint64_t dwDestOriginX;
    uint64_t dwDestOriginY;
    uint64_t lpFill;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ScrollConsoleScreenBufferW(HANDLE hConsoleOutput, const SMALL_RECT *lpScrollRect, const SMALL_RECT *lpClipRect, COORD dwDestOrigin, const CHAR_INFO *lpFill)
{
    struct qemu_ScrollConsoleScreenBufferW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCROLLCONSOLESCREENBUFFERW);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.lpScrollRect = (uint64_t)lpScrollRect;
    call.lpClipRect = (uint64_t)lpClipRect;
    call.dwDestOriginX = dwDestOrigin.X;
    call.dwDestOriginY = dwDestOrigin.Y;
    call.lpFill = (uint64_t)lpFill;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScrollConsoleScreenBufferW(struct qemu_syscall *call)
{
    struct qemu_ScrollConsoleScreenBufferW *c = (struct qemu_ScrollConsoleScreenBufferW *)call;
    COORD dwDestOrigin;
    WINE_FIXME("Unverified!\n");
    dwDestOrigin.X = c->dwDestOriginX;
    dwDestOrigin.Y = c->dwDestOriginY;
    c->super.iret = ScrollConsoleScreenBufferW(QEMU_G2H(c->hConsoleOutput), QEMU_G2H(c->lpScrollRect), QEMU_G2H(c->lpClipRect), dwDestOrigin, QEMU_G2H(c->lpFill));
}

#endif

struct qemu_AttachConsole
{
    struct qemu_syscall super;
    uint64_t dwProcessId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AttachConsole(DWORD dwProcessId)
{
    struct qemu_AttachConsole call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATTACHCONSOLE);
    call.dwProcessId = (uint64_t)dwProcessId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AttachConsole(struct qemu_syscall *call)
{
    struct qemu_AttachConsole *c = (struct qemu_AttachConsole *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AttachConsole(c->dwProcessId);
}

#endif

struct qemu_GetConsoleDisplayMode
{
    struct qemu_syscall super;
    uint64_t lpModeFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleDisplayMode(LPDWORD lpModeFlags)
{
    struct qemu_GetConsoleDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEDISPLAYMODE);
    call.lpModeFlags = (uint64_t)lpModeFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleDisplayMode(struct qemu_syscall *call)
{
    struct qemu_GetConsoleDisplayMode *c = (struct qemu_GetConsoleDisplayMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleDisplayMode(QEMU_G2H(c->lpModeFlags));
}

#endif

struct qemu_SetConsoleDisplayMode
{
    struct qemu_syscall super;
    uint64_t hConsoleOutput;
    uint64_t dwFlags;
    uint64_t lpNewScreenBufferDimensions;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleDisplayMode(HANDLE hConsoleOutput, DWORD dwFlags, COORD *lpNewScreenBufferDimensions)
{
    struct qemu_SetConsoleDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEDISPLAYMODE);
    call.hConsoleOutput = (uint64_t)hConsoleOutput;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpNewScreenBufferDimensions = (uint64_t)lpNewScreenBufferDimensions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleDisplayMode(struct qemu_syscall *call)
{
    struct qemu_SetConsoleDisplayMode *c = (struct qemu_SetConsoleDisplayMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleDisplayMode(QEMU_G2H(c->hConsoleOutput), c->dwFlags, QEMU_G2H(c->lpNewScreenBufferDimensions));
}

#endif

struct qemu_GetConsoleAliasW
{
    struct qemu_syscall super;
    uint64_t lpSource;
    uint64_t lpTargetBuffer;
    uint64_t TargetBufferLength;
    uint64_t lpExename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleAliasW(LPWSTR lpSource, LPWSTR lpTargetBuffer, DWORD TargetBufferLength, LPWSTR lpExename)
{
    struct qemu_GetConsoleAliasW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEALIASW);
    call.lpSource = (uint64_t)lpSource;
    call.lpTargetBuffer = (uint64_t)lpTargetBuffer;
    call.TargetBufferLength = (uint64_t)TargetBufferLength;
    call.lpExename = (uint64_t)lpExename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleAliasW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleAliasW *c = (struct qemu_GetConsoleAliasW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleAliasW(QEMU_G2H(c->lpSource), QEMU_G2H(c->lpTargetBuffer), c->TargetBufferLength, QEMU_G2H(c->lpExename));
}

#endif

struct qemu_GetConsoleProcessList
{
    struct qemu_syscall super;
    uint64_t processlist;
    uint64_t processcount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleProcessList(LPDWORD processlist, DWORD processcount)
{
    struct qemu_GetConsoleProcessList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEPROCESSLIST);
    call.processlist = (uint64_t)processlist;
    call.processcount = (uint64_t)processcount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleProcessList(struct qemu_syscall *call)
{
    struct qemu_GetConsoleProcessList *c = (struct qemu_GetConsoleProcessList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleProcessList(QEMU_G2H(c->processlist), c->processcount);
}

#endif

struct qemu_GetConsoleCommandHistoryA
{
    struct qemu_syscall super;
    uint64_t unknown1;
    uint64_t unknown2;
    uint64_t unknown3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleCommandHistoryA(DWORD unknown1, DWORD unknown2, DWORD unknown3)
{
    struct qemu_GetConsoleCommandHistoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLECOMMANDHISTORYA);
    call.unknown1 = (uint64_t)unknown1;
    call.unknown2 = (uint64_t)unknown2;
    call.unknown3 = (uint64_t)unknown3;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleCommandHistoryA to Wine headers? */
extern DWORD WINAPI GetConsoleCommandHistoryA(DWORD unknown1, DWORD unknown2, DWORD unknown3);
void qemu_GetConsoleCommandHistoryA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleCommandHistoryA *c = (struct qemu_GetConsoleCommandHistoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleCommandHistoryA(c->unknown1, c->unknown2, c->unknown3);
}

#endif

struct qemu_GetConsoleCommandHistoryW
{
    struct qemu_syscall super;
    uint64_t unknown1;
    uint64_t unknown2;
    uint64_t unknown3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleCommandHistoryW(DWORD unknown1, DWORD unknown2, DWORD unknown3)
{
    struct qemu_GetConsoleCommandHistoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLECOMMANDHISTORYW);
    call.unknown1 = (uint64_t)unknown1;
    call.unknown2 = (uint64_t)unknown2;
    call.unknown3 = (uint64_t)unknown3;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleCommandHistoryW to Wine headers? */
extern DWORD WINAPI GetConsoleCommandHistoryW(DWORD unknown1, DWORD unknown2, DWORD unknown3);
void qemu_GetConsoleCommandHistoryW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleCommandHistoryW *c = (struct qemu_GetConsoleCommandHistoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleCommandHistoryW(c->unknown1, c->unknown2, c->unknown3);
}

#endif

struct qemu_GetConsoleCommandHistoryLengthA
{
    struct qemu_syscall super;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleCommandHistoryLengthA(LPCSTR unknown)
{
    struct qemu_GetConsoleCommandHistoryLengthA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLECOMMANDHISTORYLENGTHA);
    call.unknown = (uint64_t)unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleCommandHistoryLengthA to Wine headers? */
extern DWORD WINAPI GetConsoleCommandHistoryLengthA(LPCSTR unknown);
void qemu_GetConsoleCommandHistoryLengthA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleCommandHistoryLengthA *c = (struct qemu_GetConsoleCommandHistoryLengthA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleCommandHistoryLengthA(QEMU_G2H(c->unknown));
}

#endif

struct qemu_GetConsoleCommandHistoryLengthW
{
    struct qemu_syscall super;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleCommandHistoryLengthW(LPCWSTR unknown)
{
    struct qemu_GetConsoleCommandHistoryLengthW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLECOMMANDHISTORYLENGTHW);
    call.unknown = (uint64_t)unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleCommandHistoryLengthW to Wine headers? */
extern DWORD WINAPI GetConsoleCommandHistoryLengthW(LPCWSTR unknown);
void qemu_GetConsoleCommandHistoryLengthW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleCommandHistoryLengthW *c = (struct qemu_GetConsoleCommandHistoryLengthW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleCommandHistoryLengthW(QEMU_G2H(c->unknown));
}

#endif

struct qemu_GetConsoleAliasesLengthA
{
    struct qemu_syscall super;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleAliasesLengthA(LPSTR unknown)
{
    struct qemu_GetConsoleAliasesLengthA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEALIASESLENGTHA);
    call.unknown = (uint64_t)unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleAliasesLengthA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleAliasesLengthA *c = (struct qemu_GetConsoleAliasesLengthA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleAliasesLengthA(QEMU_G2H(c->unknown));
}

#endif

struct qemu_GetConsoleAliasesLengthW
{
    struct qemu_syscall super;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleAliasesLengthW(LPWSTR unknown)
{
    struct qemu_GetConsoleAliasesLengthW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEALIASESLENGTHW);
    call.unknown = (uint64_t)unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleAliasesLengthW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleAliasesLengthW *c = (struct qemu_GetConsoleAliasesLengthW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleAliasesLengthW(QEMU_G2H(c->unknown));
}

#endif

struct qemu_GetConsoleAliasExesLengthA
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleAliasExesLengthA(void)
{
    struct qemu_GetConsoleAliasExesLengthA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEALIASEXESLENGTHA);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleAliasExesLengthA(struct qemu_syscall *call)
{
    struct qemu_GetConsoleAliasExesLengthA *c = (struct qemu_GetConsoleAliasExesLengthA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleAliasExesLengthA();
}

#endif

struct qemu_GetConsoleAliasExesLengthW
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetConsoleAliasExesLengthW(void)
{
    struct qemu_GetConsoleAliasExesLengthW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEALIASEXESLENGTHW);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleAliasExesLengthW(struct qemu_syscall *call)
{
    struct qemu_GetConsoleAliasExesLengthW *c = (struct qemu_GetConsoleAliasExesLengthW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleAliasExesLengthW();
}

#endif

struct qemu_ExpungeConsoleCommandHistoryA
{
    struct qemu_syscall super;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI ExpungeConsoleCommandHistoryA(LPCSTR unknown)
{
    struct qemu_ExpungeConsoleCommandHistoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPUNGECONSOLECOMMANDHISTORYA);
    call.unknown = (uint64_t)unknown;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add ExpungeConsoleCommandHistoryA to Wine headers? */
extern VOID WINAPI ExpungeConsoleCommandHistoryA(LPCSTR unknown);
void qemu_ExpungeConsoleCommandHistoryA(struct qemu_syscall *call)
{
    struct qemu_ExpungeConsoleCommandHistoryA *c = (struct qemu_ExpungeConsoleCommandHistoryA *)call;
    WINE_FIXME("Unverified!\n");
    ExpungeConsoleCommandHistoryA(QEMU_G2H(c->unknown));
}

#endif

struct qemu_ExpungeConsoleCommandHistoryW
{
    struct qemu_syscall super;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI ExpungeConsoleCommandHistoryW(LPCWSTR unknown)
{
    struct qemu_ExpungeConsoleCommandHistoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPUNGECONSOLECOMMANDHISTORYW);
    call.unknown = (uint64_t)unknown;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add ExpungeConsoleCommandHistoryW to Wine headers? */
extern VOID WINAPI ExpungeConsoleCommandHistoryW(LPCWSTR unknown);
void qemu_ExpungeConsoleCommandHistoryW(struct qemu_syscall *call)
{
    struct qemu_ExpungeConsoleCommandHistoryW *c = (struct qemu_ExpungeConsoleCommandHistoryW *)call;
    WINE_FIXME("Unverified!\n");
    ExpungeConsoleCommandHistoryW(QEMU_G2H(c->unknown));
}

#endif

struct qemu_AddConsoleAliasA
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t target;
    uint64_t exename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddConsoleAliasA(LPSTR source, LPSTR target, LPSTR exename)
{
    struct qemu_AddConsoleAliasA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDCONSOLEALIASA);
    call.source = (uint64_t)source;
    call.target = (uint64_t)target;
    call.exename = (uint64_t)exename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddConsoleAliasA(struct qemu_syscall *call)
{
    struct qemu_AddConsoleAliasA *c = (struct qemu_AddConsoleAliasA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddConsoleAliasA(QEMU_G2H(c->source), QEMU_G2H(c->target), QEMU_G2H(c->exename));
}

#endif

struct qemu_AddConsoleAliasW
{
    struct qemu_syscall super;
    uint64_t source;
    uint64_t target;
    uint64_t exename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddConsoleAliasW(LPWSTR source, LPWSTR target, LPWSTR exename)
{
    struct qemu_AddConsoleAliasW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDCONSOLEALIASW);
    call.source = (uint64_t)source;
    call.target = (uint64_t)target;
    call.exename = (uint64_t)exename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddConsoleAliasW(struct qemu_syscall *call)
{
    struct qemu_AddConsoleAliasW *c = (struct qemu_AddConsoleAliasW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddConsoleAliasW(QEMU_G2H(c->source), QEMU_G2H(c->target), QEMU_G2H(c->exename));
}

#endif

struct qemu_SetConsoleIcon
{
    struct qemu_syscall super;
    uint64_t icon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleIcon(HICON icon)
{
    struct qemu_SetConsoleIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEICON);
    call.icon = (uint64_t)icon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetConsoleIcon to Wine headers? */
extern BOOL WINAPI SetConsoleIcon(HICON icon);
void qemu_SetConsoleIcon(struct qemu_syscall *call)
{
    struct qemu_SetConsoleIcon *c = (struct qemu_SetConsoleIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleIcon(QEMU_G2H(c->icon));
}

#endif

struct qemu_GetNumberOfConsoleFonts
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNumberOfConsoleFonts(void)
{
    struct qemu_GetNumberOfConsoleFonts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBEROFCONSOLEFONTS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNumberOfConsoleFonts to Wine headers? */
extern DWORD WINAPI GetNumberOfConsoleFonts(void);
void qemu_GetNumberOfConsoleFonts(struct qemu_syscall *call)
{
    struct qemu_GetNumberOfConsoleFonts *c = (struct qemu_GetNumberOfConsoleFonts *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberOfConsoleFonts();
}

#endif

struct qemu_SetConsoleFont
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleFont(HANDLE hConsole, DWORD index)
{
    struct qemu_SetConsoleFont call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEFONT);
    call.hConsole = (uint64_t)hConsole;
    call.index = (uint64_t)index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetConsoleFont to Wine headers? */
extern BOOL WINAPI SetConsoleFont(HANDLE hConsole, DWORD index);
void qemu_SetConsoleFont(struct qemu_syscall *call)
{
    struct qemu_SetConsoleFont *c = (struct qemu_SetConsoleFont *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleFont(QEMU_G2H(c->hConsole), c->index);
}

#endif

struct qemu_SetConsoleKeyShortcuts
{
    struct qemu_syscall super;
    uint64_t set;
    uint64_t keys;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleKeyShortcuts(BOOL set, BYTE keys, VOID *a, DWORD b)
{
    struct qemu_SetConsoleKeyShortcuts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLEKEYSHORTCUTS);
    call.set = (uint64_t)set;
    call.keys = (uint64_t)keys;
    call.a = (uint64_t)a;
    call.b = (uint64_t)b;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetConsoleKeyShortcuts to Wine headers? */
extern BOOL WINAPI SetConsoleKeyShortcuts(BOOL set, BYTE keys, VOID *a, DWORD b);
void qemu_SetConsoleKeyShortcuts(struct qemu_syscall *call)
{
    struct qemu_SetConsoleKeyShortcuts *c = (struct qemu_SetConsoleKeyShortcuts *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleKeyShortcuts(c->set, c->keys, QEMU_G2H(c->a), c->b);
}

#endif

struct qemu_GetCurrentConsoleFont
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t maxwindow;
    uint64_t fontinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCurrentConsoleFont(HANDLE hConsole, BOOL maxwindow, CONSOLE_FONT_INFO *fontinfo)
{
    struct qemu_GetCurrentConsoleFont call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTCONSOLEFONT);
    call.hConsole = (uint64_t)hConsole;
    call.maxwindow = (uint64_t)maxwindow;
    call.fontinfo = (uint64_t)fontinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentConsoleFont(struct qemu_syscall *call)
{
    struct qemu_GetCurrentConsoleFont *c = (struct qemu_GetCurrentConsoleFont *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentConsoleFont(QEMU_G2H(c->hConsole), c->maxwindow, QEMU_G2H(c->fontinfo));
}

#endif

struct qemu_GetConsoleFontSize
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t index;
    uint64_t retY;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI COORD WINAPI GetConsoleFontSize(HANDLE hConsole, DWORD index)
{
    COORD ret;
    struct qemu_GetConsoleFontSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEFONTSIZE);
    call.hConsole = (uint64_t)hConsole;
    call.index = (uint64_t)index;

    qemu_syscall(&call.super);

    ret.X = call.super.iret;
    ret.Y = call.retY;
    return ret;
}

#else

void qemu_GetConsoleFontSize(struct qemu_syscall *call)
{
    struct qemu_GetConsoleFontSize *c = (struct qemu_GetConsoleFontSize *)call;
    COORD ret;

    WINE_TRACE("\n");

    ret = GetConsoleFontSize(QEMU_G2H(c->hConsole), c->index);
    c->super.iret = ret.X;
    c->retY = ret.Y;
}

#endif

struct qemu_GetConsoleFontInfo
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t maximize;
    uint64_t numfonts;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleFontInfo(HANDLE hConsole, BOOL maximize, DWORD numfonts, CONSOLE_FONT_INFO *info)
{
    struct qemu_GetConsoleFontInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLEFONTINFO);
    call.hConsole = (uint64_t)hConsole;
    call.maximize = (uint64_t)maximize;
    call.numfonts = (uint64_t)numfonts;
    call.info = (uint64_t)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetConsoleFontInfo to Wine headers? */
extern BOOL WINAPI GetConsoleFontInfo(HANDLE hConsole, BOOL maximize, DWORD numfonts, CONSOLE_FONT_INFO *info);
void qemu_GetConsoleFontInfo(struct qemu_syscall *call)
{
    struct qemu_GetConsoleFontInfo *c = (struct qemu_GetConsoleFontInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleFontInfo(QEMU_G2H(c->hConsole), c->maximize, c->numfonts, QEMU_G2H(c->info));
}

#endif

struct qemu_GetConsoleScreenBufferInfoEx
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t csbix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetConsoleScreenBufferInfoEx(HANDLE hConsole, CONSOLE_SCREEN_BUFFER_INFOEX *csbix)
{
    struct qemu_GetConsoleScreenBufferInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCONSOLESCREENBUFFERINFOEX);
    call.hConsole = (uint64_t)hConsole;
    call.csbix = (uint64_t)csbix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetConsoleScreenBufferInfoEx(struct qemu_syscall *call)
{
    struct qemu_GetConsoleScreenBufferInfoEx *c = (struct qemu_GetConsoleScreenBufferInfoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetConsoleScreenBufferInfoEx(QEMU_G2H(c->hConsole), QEMU_G2H(c->csbix));
}

#endif

struct qemu_SetConsoleScreenBufferInfoEx
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t csbix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetConsoleScreenBufferInfoEx(HANDLE hConsole, CONSOLE_SCREEN_BUFFER_INFOEX *csbix)
{
    struct qemu_SetConsoleScreenBufferInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLESCREENBUFFERINFOEX);
    call.hConsole = (uint64_t)hConsole;
    call.csbix = (uint64_t)csbix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetConsoleScreenBufferInfoEx(struct qemu_syscall *call)
{
    struct qemu_SetConsoleScreenBufferInfoEx *c = (struct qemu_SetConsoleScreenBufferInfoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetConsoleScreenBufferInfoEx(QEMU_G2H(c->hConsole), QEMU_G2H(c->csbix));
}

#endif

struct qemu_SetCurrentConsoleFontEx
{
    struct qemu_syscall super;
    uint64_t hConsole;
    uint64_t maxwindow;
    uint64_t cfix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsole, BOOL maxwindow, CONSOLE_FONT_INFOEX *cfix)
{
    struct qemu_SetCurrentConsoleFontEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCURRENTCONSOLEFONTEX);
    call.hConsole = (uint64_t)hConsole;
    call.maxwindow = (uint64_t)maxwindow;
    call.cfix = (uint64_t)cfix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCurrentConsoleFontEx(struct qemu_syscall *call)
{
    struct qemu_SetCurrentConsoleFontEx *c = (struct qemu_SetCurrentConsoleFontEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCurrentConsoleFontEx(QEMU_G2H(c->hConsole), c->maxwindow, QEMU_G2H(c->cfix));
}

#endif

