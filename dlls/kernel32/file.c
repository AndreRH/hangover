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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <fileapi.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include "callback_helper.h"
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_SetFileApisToOEM
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SetFileApisToOEM(void)
{
    struct qemu_SetFileApisToOEM call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEAPISTOOEM);

    qemu_syscall(&call.super);
}

#else

void qemu_SetFileApisToOEM(struct qemu_syscall *call)
{
    struct qemu_SetFileApisToOEM *c = (struct qemu_SetFileApisToOEM *)call;
    WINE_FIXME("Unverified!\n");
    SetFileApisToOEM();
}

#endif

struct qemu_SetFileApisToANSI
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SetFileApisToANSI(void)
{
    struct qemu_SetFileApisToANSI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEAPISTOANSI);

    qemu_syscall(&call.super);
}

#else

void qemu_SetFileApisToANSI(struct qemu_syscall *call)
{
    struct qemu_SetFileApisToANSI *c = (struct qemu_SetFileApisToANSI *)call;
    WINE_FIXME("Unverified!\n");
    SetFileApisToANSI();
}

#endif

struct qemu_AreFileApisANSI
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AreFileApisANSI(void)
{
    struct qemu_AreFileApisANSI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AREFILEAPISANSI);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AreFileApisANSI(struct qemu_syscall *call)
{
    struct qemu_AreFileApisANSI *c = (struct qemu_AreFileApisANSI *)call;
    WINE_TRACE("\n");
    c->super.iret = AreFileApisANSI();
}

#endif

struct qemu_ReadFileEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t buffer;
    uint64_t bytesToRead;
    uint64_t overlapped;
    uint64_t lpCompletionRoutine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadFileEx(HANDLE hFile, LPVOID buffer, DWORD bytesToRead, LPOVERLAPPED overlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_ReadFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READFILEEX);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.buffer = (ULONG_PTR)buffer;
    call.bytesToRead = bytesToRead;
    call.overlapped = (ULONG_PTR)overlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadFileEx(struct qemu_syscall *call)
{
    struct qemu_ReadFileEx *c = (struct qemu_ReadFileEx *)call;
    uint64_t guest_completion;
    OVERLAPPED *guest_ov;
    struct callback_entry *wrapper = NULL;

    WINE_TRACE("\n");
    guest_completion = c->lpCompletionRoutine;
    guest_ov = QEMU_G2H(c->overlapped);

    if (guest_completion && guest_ov)
    {
        wrapper = callback_get(overlapped_wrappers, guest_completion, NULL);
        if (!wrapper)
            WINE_ERR("Failed to get an overlapped IO callback wrapper.\n");
    }

    c->super.iret = ReadFileEx(QEMU_G2H(c->hFile), QEMU_G2H(c->buffer), c->bytesToRead, guest_ov,
            (LPOVERLAPPED_COMPLETION_ROUTINE)wrapper);
}

#endif

struct qemu_ReadFileScatter
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t segments;
    uint64_t count;
    uint64_t reserved;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadFileScatter(HANDLE file, FILE_SEGMENT_ELEMENT *segments, DWORD count, LPDWORD reserved,
        LPOVERLAPPED overlapped)
{
    struct qemu_ReadFileScatter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READFILESCATTER);
    call.file = guest_HANDLE_g2h(file);
    call.segments = (ULONG_PTR)segments;
    call.count = count;
    call.reserved = (ULONG_PTR)reserved;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadFileScatter(struct qemu_syscall *call)
{
    struct qemu_ReadFileScatter *c = (struct qemu_ReadFileScatter *)call;
    WINE_TRACE("\n");
    c->super.iret = ReadFileScatter(QEMU_G2H(c->file), QEMU_G2H(c->segments), c->count, QEMU_G2H(c->reserved),
            QEMU_G2H(c->overlapped));
}

#endif

struct qemu_ReadFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t buffer;
    uint64_t bytesToRead;
    uint64_t bytesRead;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadFile(HANDLE hFile, LPVOID buffer, DWORD bytesToRead, LPDWORD bytesRead, LPOVERLAPPED overlapped)
{
    struct qemu_ReadFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READFILE);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.buffer = (ULONG_PTR)buffer;
    call.bytesToRead = bytesToRead;
    call.bytesRead = (ULONG_PTR)bytesRead;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadFile(struct qemu_syscall *call)
{
    struct qemu_ReadFile *c = (struct qemu_ReadFile *)call;
    WINE_TRACE("\n");
    c->super.iret = ReadFile(QEMU_G2H(c->hFile), QEMU_G2H(c->buffer), c->bytesToRead, QEMU_G2H(c->bytesRead), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_WriteFileEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t buffer;
    uint64_t bytesToWrite;
    uint64_t overlapped;
    uint64_t lpCompletionRoutine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteFileEx(HANDLE hFile, LPCVOID buffer, DWORD bytesToWrite, LPOVERLAPPED overlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WriteFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEFILEEX);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.buffer = (ULONG_PTR)buffer;
    call.bytesToWrite = bytesToWrite;
    call.overlapped = (ULONG_PTR)overlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteFileEx(struct qemu_syscall *call)
{
    struct qemu_WriteFileEx *c = (struct qemu_WriteFileEx *)call;
    uint64_t guest_completion;
    OVERLAPPED *guest_ov;
    struct callback_entry *wrapper = NULL;

    WINE_TRACE("\n");
    guest_completion = c->lpCompletionRoutine;
    guest_ov = QEMU_G2H(c->overlapped);

    if (guest_completion && guest_ov)
    {
        wrapper = callback_get(overlapped_wrappers, guest_completion, NULL);
        if (!wrapper)
            WINE_ERR("Failed to get an overlapped IO callback wrapper.\n");
    }

    c->super.iret = WriteFileEx(QEMU_G2H(c->hFile), QEMU_G2H(c->buffer), c->bytesToWrite, guest_ov,
            (LPOVERLAPPED_COMPLETION_ROUTINE)wrapper);
}

#endif

struct qemu_WriteFileGather
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t segments;
    uint64_t count;
    uint64_t reserved;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteFileGather(HANDLE file, FILE_SEGMENT_ELEMENT *segments, DWORD count, LPDWORD reserved,
        LPOVERLAPPED overlapped)
{
    struct qemu_WriteFileGather call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEFILEGATHER);
    call.file = guest_HANDLE_g2h(file);
    call.segments = (ULONG_PTR)segments;
    call.count = count;
    call.reserved = (ULONG_PTR)reserved;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteFileGather(struct qemu_syscall *call)
{
    struct qemu_WriteFileGather *c = (struct qemu_WriteFileGather *)call;
    WINE_TRACE("\n");
    c->super.iret = WriteFileGather(QEMU_G2H(c->file), QEMU_G2H(c->segments), c->count, QEMU_G2H(c->reserved),
            QEMU_G2H(c->overlapped));
}

#endif

struct qemu_WriteFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t buffer;
    uint64_t bytesToWrite;
    uint64_t bytesWritten;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteFile(HANDLE hFile, LPCVOID buffer, DWORD bytesToWrite, LPDWORD bytesWritten, LPOVERLAPPED overlapped)
{
    struct qemu_WriteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEFILE);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.buffer = (ULONG_PTR)buffer;
    call.bytesToWrite = bytesToWrite;
    call.bytesWritten = (ULONG_PTR)bytesWritten;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteFile(struct qemu_syscall *call)
{
    struct qemu_WriteFile *c = (struct qemu_WriteFile *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->overlapped)
        WINE_FIXME("Overlapped structure not handled in 32 on 64 case.\n");
#endif
    c->super.iret = WriteFile(QEMU_G2H(c->hFile), QEMU_G2H(c->buffer), c->bytesToWrite, QEMU_G2H(c->bytesWritten), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_GetOverlappedResult
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpOverlapped;
    uint64_t lpTransferred;
    uint64_t bWait;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetOverlappedResult(HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpTransferred, BOOL bWait)
{
    struct qemu_GetOverlappedResult call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOVERLAPPEDRESULT);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpTransferred = (ULONG_PTR)lpTransferred;
    call.bWait = bWait;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOverlappedResult(struct qemu_syscall *call)
{
    struct qemu_GetOverlappedResult *c = (struct qemu_GetOverlappedResult *)call;
    struct qemu_OVERLAPPED *ov32;
    NTSTATUS status;
    HANDLE file, event;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    c->super.iret = GetOverlappedResult(QEMU_G2H(c->hFile), QEMU_G2H(c->lpOverlapped), QEMU_G2H(c->lpTransferred), c->bWait);
    return;
#endif

    /* Taken from Wine. We have to make due with the data in the 32 bit struct, as the 64 bit copy is freed
     * when the event is notified. Also we don't want to search for the 64 bit copy... */
    ov32 = QEMU_G2H(c->lpOverlapped);
    file = QEMU_G2H(c->hFile);
    WINE_TRACE( "(%p %p 0x%lx %lx)\n", file, ov32, c->lpTransferred, c->bWait );

    status = ov32->Internal;
    if (status == STATUS_PENDING)
    {
        if (!c->bWait)
        {
            SetLastError( ERROR_IO_INCOMPLETE );
            c->super.iret = FALSE;
            return;
        }

        event = HANDLE_g2h(ov32->hEvent);
        if (WaitForSingleObject(event ? event : file, INFINITE) == WAIT_FAILED)
        {
            c->super.iret = FALSE;
            return;
        }

        status = ov32->Internal;
        if (status == STATUS_PENDING) status = STATUS_SUCCESS;
    }

    *(DWORD *)QEMU_G2H(c->lpTransferred) = ov32->InternalHigh;

    if (status) SetLastError( RtlNtStatusToDosError(status) );
    c->super.iret = !status;
}

#endif

struct qemu_CancelIoEx
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t lpOverlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CancelIoEx(HANDLE handle, LPOVERLAPPED lpOverlapped)
{
    struct qemu_CancelIoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELIOEX);
    call.handle = guest_HANDLE_g2h(handle);
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelIoEx(struct qemu_syscall *call)
{
    struct qemu_CancelIoEx *c = (struct qemu_CancelIoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelIoEx(QEMU_G2H(c->handle), QEMU_G2H(c->lpOverlapped));
}

#endif

struct qemu_CancelIo
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CancelIo(HANDLE handle)
{
    struct qemu_CancelIo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELIO);
    call.handle = guest_HANDLE_g2h(handle);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelIo(struct qemu_syscall *call)
{
    struct qemu_CancelIo *c = (struct qemu_CancelIo *)call;
    WINE_TRACE("\n");
    c->super.iret = CancelIo(QEMU_G2H(c->handle));
}

#endif

struct qemu_CancelSynchronousIo
{
    struct qemu_syscall super;
    uint64_t thread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CancelSynchronousIo(HANDLE thread)
{
    struct qemu_CancelSynchronousIo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELSYNCHRONOUSIO);
    call.thread = guest_HANDLE_g2h(thread);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelSynchronousIo(struct qemu_syscall *call)
{
    struct qemu_CancelSynchronousIo *c = (struct qemu_CancelSynchronousIo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelSynchronousIo(QEMU_G2H(c->thread));
}

#endif

struct qemu__hread
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI _hread(HFILE hFile, LPVOID buffer, LONG count)
{
    struct qemu__hread call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HREAD);
    call.hFile = hFile;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__hread(struct qemu_syscall *call)
{
    struct qemu__hread *c = (struct qemu__hread *)call;
    WINE_TRACE("\n");
    c->super.iret = _hread(c->hFile, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu__hwrite
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI _hwrite(HFILE handle, LPCSTR buffer, LONG count)
{
    struct qemu__hwrite call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HWRITE);
    call.handle = handle;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__hwrite(struct qemu_syscall *call)
{
    struct qemu__hwrite *c = (struct qemu__hwrite *)call;
    WINE_TRACE("\n");
    c->super.iret = _hwrite(c->handle, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu__lclose
{
    struct qemu_syscall super;
    uint64_t hFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI _lclose(HFILE hFile)
{
    struct qemu__lclose call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LCLOSE);
    call.hFile = hFile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lclose(struct qemu_syscall *call)
{
    struct qemu__lclose *c = (struct qemu__lclose *)call;
    WINE_TRACE("\n");
    c->super.iret = _lclose(c->hFile);
}

#endif

struct qemu__lcreat
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI _lcreat(LPCSTR path, INT attr)
{
    struct qemu__lcreat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LCREAT);
    call.path = (ULONG_PTR)path;
    call.attr = attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lcreat(struct qemu_syscall *call)
{
    struct qemu__lcreat *c = (struct qemu__lcreat *)call;
    WINE_TRACE("\n");
    c->super.iret = _lcreat(QEMU_G2H(c->path), c->attr);
}

#endif

struct qemu__lopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI _lopen(LPCSTR path, INT mode)
{
    struct qemu__lopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lopen(struct qemu_syscall *call)
{
    struct qemu__lopen *c = (struct qemu__lopen *)call;
    WINE_TRACE("\n");
    c->super.iret = _lopen(QEMU_G2H(c->path), c->mode);
}

#endif

struct qemu__lread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI _lread(HFILE handle, LPVOID buffer, UINT count)
{
    struct qemu__lread call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LREAD);
    call.handle = handle;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lread(struct qemu_syscall *call)
{
    struct qemu__lread *c = (struct qemu__lread *)call;
    WINE_TRACE("\n");
    c->super.iret = _lread(c->handle, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu__llseek
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lOffset;
    uint64_t nOrigin;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI _llseek(HFILE hFile, LONG lOffset, INT nOrigin)
{
    struct qemu__llseek call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LLSEEK);
    call.hFile = hFile;
    call.lOffset = lOffset;
    call.nOrigin = nOrigin;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__llseek(struct qemu_syscall *call)
{
    struct qemu__llseek *c = (struct qemu__llseek *)call;
    WINE_TRACE("\n");
    c->super.iret = _llseek(c->hFile, c->lOffset, c->nOrigin);
}

#endif

struct qemu__lwrite
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI _lwrite(HFILE hFile, LPCSTR buffer, UINT count)
{
    struct qemu__lwrite call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LWRITE);
    call.hFile = hFile;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lwrite(struct qemu_syscall *call)
{
    struct qemu__lwrite *c = (struct qemu__lwrite *)call;
    WINE_TRACE("\n");
    c->super.iret = _lwrite(c->hFile, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_FlushFileBuffers
{
    struct qemu_syscall super;
    uint64_t hFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlushFileBuffers(HANDLE hFile)
{
    struct qemu_FlushFileBuffers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHFILEBUFFERS);
    call.hFile = guest_HANDLE_g2h(hFile);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushFileBuffers(struct qemu_syscall *call)
{
    struct qemu_FlushFileBuffers *c = (struct qemu_FlushFileBuffers *)call;
    WINE_TRACE("\n");
    c->super.iret = FlushFileBuffers(QEMU_G2H(c->hFile));
}

#endif

struct qemu_GetFileType
{
    struct qemu_syscall super;
    uint64_t hFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileType(HANDLE hFile)
{
    struct qemu_GetFileType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILETYPE);
    call.hFile = guest_HANDLE_g2h(hFile);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileType(struct qemu_syscall *call)
{
    struct qemu_GetFileType *c = (struct qemu_GetFileType *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileType(QEMU_G2H(c->hFile));
}

#endif

struct qemu_GetFileInformationByHandle
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileInformationByHandle(HANDLE hFile, BY_HANDLE_FILE_INFORMATION *info)
{
    struct qemu_GetFileInformationByHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEINFORMATIONBYHANDLE);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileInformationByHandle(struct qemu_syscall *call)
{
    struct qemu_GetFileInformationByHandle *c = (struct qemu_GetFileInformationByHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileInformationByHandle(QEMU_G2H(c->hFile), QEMU_G2H(c->info));
}

#endif

struct qemu_GetFileInformationByHandleEx
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileInformationByHandleEx(HANDLE handle, FILE_INFO_BY_HANDLE_CLASS class, LPVOID info, DWORD size)
{
    struct qemu_GetFileInformationByHandleEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEINFORMATIONBYHANDLEEX);
    call.handle = guest_HANDLE_g2h(handle);
    call.class = class;
    call.info = (ULONG_PTR)info;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileInformationByHandleEx(struct qemu_syscall *call)
{
    struct qemu_GetFileInformationByHandleEx *c = (struct qemu_GetFileInformationByHandleEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileInformationByHandleEx(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->info), c->size);
}

#endif

struct qemu_GetFileSize
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t filesizehigh;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD filesizehigh)
{
    struct qemu_GetFileSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILESIZE);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.filesizehigh = (ULONG_PTR)filesizehigh;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileSize(struct qemu_syscall *call)
{
    struct qemu_GetFileSize *c = (struct qemu_GetFileSize *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileSize(QEMU_G2H(c->hFile), QEMU_G2H(c->filesizehigh));
}

#endif

struct qemu_GetFileSizeEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpFileSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize)
{
    struct qemu_GetFileSizeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILESIZEEX);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.lpFileSize = (ULONG_PTR)lpFileSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileSizeEx(struct qemu_syscall *call)
{
    struct qemu_GetFileSizeEx *c = (struct qemu_GetFileSizeEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileSizeEx(QEMU_G2H(c->hFile), QEMU_G2H(c->lpFileSize));
}

#endif

struct qemu_SetEndOfFile
{
    struct qemu_syscall super;
    uint64_t hFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetEndOfFile(HANDLE hFile)
{
    struct qemu_SetEndOfFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENDOFFILE);
    call.hFile = guest_HANDLE_g2h(hFile);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEndOfFile(struct qemu_syscall *call)
{
    struct qemu_SetEndOfFile *c = (struct qemu_SetEndOfFile *)call;
    WINE_TRACE("\n");
    c->super.iret = SetEndOfFile(QEMU_G2H(c->hFile));
}

#endif

struct qemu_SetFileCompletionNotificationModes
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileCompletionNotificationModes(HANDLE handle, UCHAR flags)
{
    struct qemu_SetFileCompletionNotificationModes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILECOMPLETIONNOTIFICATIONMODES);
    call.handle = guest_HANDLE_g2h(handle);
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileCompletionNotificationModes(struct qemu_syscall *call)
{
    struct qemu_SetFileCompletionNotificationModes *c = (struct qemu_SetFileCompletionNotificationModes *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetFileCompletionNotificationModes(QEMU_G2H(c->handle), c->flags);
}

#endif

struct qemu_SetFileInformationByHandle
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t class;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileInformationByHandle(HANDLE file, FILE_INFO_BY_HANDLE_CLASS class, VOID *info, DWORD size)
{
    struct qemu_SetFileInformationByHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEINFORMATIONBYHANDLE);
    call.file = guest_HANDLE_g2h(file);
    call.class = class;
    call.info = (ULONG_PTR)info;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileInformationByHandle(struct qemu_syscall *call)
{
    struct qemu_SetFileInformationByHandle *c = (struct qemu_SetFileInformationByHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFileInformationByHandle(QEMU_G2H(c->file), c->class, QEMU_G2H(c->info), c->size);
}

#endif

struct qemu_SetFilePointer
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t distance;
    uint64_t highword;
    uint64_t method;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetFilePointer(HANDLE hFile, LONG distance, LONG *highword, DWORD method)
{
    struct qemu_SetFilePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEPOINTER);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.distance = distance;
    call.highword = (ULONG_PTR)highword;
    call.method = method;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFilePointer(struct qemu_syscall *call)
{
    struct qemu_SetFilePointer *c = (struct qemu_SetFilePointer *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFilePointer(QEMU_G2H(c->hFile), c->distance, QEMU_G2H(c->highword), c->method);
}

#endif

struct qemu_SetFilePointerEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t distance_high;
    uint64_t distance_low;
    uint64_t newpos;
    uint64_t method;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFilePointerEx(HANDLE hFile, LARGE_INTEGER distance, LARGE_INTEGER *newpos, DWORD method)
{
    struct qemu_SetFilePointerEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEPOINTEREX);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.distance_high = distance.HighPart;
    call.distance_low = distance.LowPart;
    call.newpos = (ULONG_PTR)newpos;
    call.method = method;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFilePointerEx(struct qemu_syscall *call)
{
    struct qemu_SetFilePointerEx *c = (struct qemu_SetFilePointerEx *)call;
    LARGE_INTEGER distance;
    WINE_TRACE("\n");
    distance.HighPart = c->distance_high;
    distance.LowPart = c->distance_low;
    c->super.iret = SetFilePointerEx(QEMU_G2H(c->hFile), distance, QEMU_G2H(c->newpos), c->method);
}

#endif

struct qemu_SetFileValidData
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t ValidDataLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileValidData(HANDLE hFile, LONGLONG ValidDataLength)
{
    struct qemu_SetFileValidData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEVALIDDATA);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.ValidDataLength = ValidDataLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileValidData(struct qemu_syscall *call)
{
    struct qemu_SetFileValidData *c = (struct qemu_SetFileValidData *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFileValidData(QEMU_G2H(c->hFile), c->ValidDataLength);
}

#endif

struct qemu_GetFileTime
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpCreationTime;
    uint64_t lpLastAccessTime;
    uint64_t lpLastWriteTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileTime(HANDLE hFile, FILETIME *lpCreationTime, FILETIME *lpLastAccessTime,
        FILETIME *lpLastWriteTime)
{
    struct qemu_GetFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILETIME);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.lpCreationTime = (ULONG_PTR)lpCreationTime;
    call.lpLastAccessTime = (ULONG_PTR)lpLastAccessTime;
    call.lpLastWriteTime = (ULONG_PTR)lpLastWriteTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileTime(struct qemu_syscall *call)
{
    struct qemu_GetFileTime *c = (struct qemu_GetFileTime *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileTime(QEMU_G2H(c->hFile), QEMU_G2H(c->lpCreationTime), QEMU_G2H(c->lpLastAccessTime),
            QEMU_G2H(c->lpLastWriteTime));
}

#endif

struct qemu_SetFileTime
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t ctime;
    uint64_t atime;
    uint64_t mtime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileTime(HANDLE hFile, const FILETIME *ctime, const FILETIME *atime, const FILETIME *mtime)
{
    struct qemu_SetFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILETIME);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.ctime = (ULONG_PTR)ctime;
    call.atime = (ULONG_PTR)atime;
    call.mtime = (ULONG_PTR)mtime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileTime(struct qemu_syscall *call)
{
    struct qemu_SetFileTime *c = (struct qemu_SetFileTime *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFileTime((HANDLE)c->hFile, QEMU_G2H(c->ctime), QEMU_G2H(c->atime), QEMU_G2H(c->mtime));
}

#endif

struct qemu_LockFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t offset_low;
    uint64_t offset_high;
    uint64_t count_low;
    uint64_t count_high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LockFile(HANDLE hFile, DWORD offset_low, DWORD offset_high, DWORD count_low, DWORD count_high)
{
    struct qemu_LockFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCKFILE);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.offset_low = offset_low;
    call.offset_high = offset_high;
    call.count_low = count_low;
    call.count_high = count_high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LockFile(struct qemu_syscall *call)
{
    struct qemu_LockFile *c = (struct qemu_LockFile *)call;
    WINE_TRACE("\n");
    c->super.iret = LockFile(QEMU_G2H(c->hFile), c->offset_low, c->offset_high, c->count_low, c->count_high);
}

#endif

struct qemu_LockFileEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t flags;
    uint64_t reserved;
    uint64_t count_low;
    uint64_t count_high;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LockFileEx(HANDLE hFile, DWORD flags, DWORD reserved, DWORD count_low, DWORD count_high, LPOVERLAPPED overlapped)
{
    struct qemu_LockFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCKFILEEX);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.flags = flags;
    call.reserved = reserved;
    call.count_low = count_low;
    call.count_high = count_high;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LockFileEx(struct qemu_syscall *call)
{
    struct qemu_LockFileEx *c = (struct qemu_LockFileEx *)call;
    WINE_TRACE("\n");
    c->super.iret = LockFileEx((HANDLE)c->hFile, c->flags, c->reserved, c->count_low, c->count_high,
            QEMU_G2H(c->overlapped));
}

#endif

struct qemu_UnlockFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t offset_low;
    uint64_t offset_high;
    uint64_t count_low;
    uint64_t count_high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnlockFile(HANDLE hFile, DWORD offset_low, DWORD offset_high, DWORD count_low, DWORD count_high)
{
    struct qemu_UnlockFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOCKFILE);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.offset_low = offset_low;
    call.offset_high = offset_high;
    call.count_low = count_low;
    call.count_high = count_high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnlockFile(struct qemu_syscall *call)
{
    struct qemu_UnlockFile *c = (struct qemu_UnlockFile *)call;
    WINE_TRACE("\n");
    c->super.iret = UnlockFile(QEMU_G2H(c->hFile), c->offset_low, c->offset_high, c->count_low, c->count_high);
}

#endif

struct qemu_UnlockFileEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t reserved;
    uint64_t count_low;
    uint64_t count_high;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnlockFileEx(HANDLE hFile, DWORD reserved, DWORD count_low, DWORD count_high, LPOVERLAPPED overlapped)
{
    struct qemu_UnlockFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOCKFILEEX);
    call.hFile = guest_HANDLE_g2h(hFile);
    call.reserved = reserved;
    call.count_low = count_low;
    call.count_high = count_high;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnlockFileEx(struct qemu_syscall *call)
{
    struct qemu_UnlockFileEx *c = (struct qemu_UnlockFileEx *)call;
    struct qemu_OVERLAPPED *ov32;
    OVERLAPPED stack, *ov = &stack;
    HANDLE guest_event;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    ov = QEMU_G2H(c->overlapped);
#else

    /* Wine doesn't implement async operations here. Don't bother to do anything fancy. */
    ov32 = QEMU_G2H(c->overlapped);
    if (ov32)
        OVERLAPPED_g2h(ov, ov32);
    else
        ov = NULL;
#endif

    c->super.iret = UnlockFileEx(QEMU_G2H(c->hFile), c->reserved, c->count_low, c->count_high, ov);

#if GUEST_BIT != HOST_BIT
    if (ov32);
        OVERLAPPED_h2g(ov32, ov);
#endif
}

#endif

struct qemu_SetHandleCount
{
    struct qemu_syscall super;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SetHandleCount(UINT count)
{
    struct qemu_SetHandleCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETHANDLECOUNT);
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetHandleCount(struct qemu_syscall *call)
{
    struct qemu_SetHandleCount *c = (struct qemu_SetHandleCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetHandleCount(c->count);
}

#endif

struct qemu_CreateFileW
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t access;
    uint64_t sharing;
    uint64_t sa;
    uint64_t creation;
    uint64_t attributes;
    uint64_t template;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFileW(LPCWSTR filename, DWORD access, DWORD sharing, LPSECURITY_ATTRIBUTES sa, DWORD creation, DWORD attributes, HANDLE template)
{
    struct qemu_CreateFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILEW);
    call.filename = (ULONG_PTR)filename;
    call.access = access;
    call.sharing = sharing;
    call.sa = (ULONG_PTR)sa;
    call.creation = creation;
    call.attributes = attributes;
    call.template = guest_HANDLE_g2h(template);

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFileW(struct qemu_syscall *call)
{
    struct qemu_CreateFileW *c = (struct qemu_CreateFileW *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = QEMU_H2G(CreateFileW(QEMU_G2H(c->filename), c->access, c->sharing, sa, c->creation, c->attributes, QEMU_G2H(c->template)));
}

#endif

struct qemu_CreateFileA
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t access;
    uint64_t sharing;
    uint64_t sa;
    uint64_t creation;
    uint64_t attributes;
    uint64_t template;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFileA(LPCSTR filename, DWORD access, DWORD sharing, LPSECURITY_ATTRIBUTES sa, DWORD creation, DWORD attributes, HANDLE template)
{
    struct qemu_CreateFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILEA);
    call.filename = (ULONG_PTR)filename;
    call.access = access;
    call.sharing = sharing;
    call.sa = (ULONG_PTR)sa;
    call.creation = creation;
    call.attributes = attributes;
    call.template = guest_HANDLE_g2h(template);

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFileA(struct qemu_syscall *call)
{
    struct qemu_CreateFileA *c = (struct qemu_CreateFileA *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sa);
#else
    if (c->sa)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sa));
    else
        sa = NULL;
#endif

    c->super.iret = QEMU_H2G(CreateFileA(QEMU_G2H(c->filename), c->access, c->sharing, sa, c->creation, c->attributes, QEMU_G2H(c->template)));
}

#endif

struct qemu_CreateFile2
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t access;
    uint64_t sharing;
    uint64_t creation;
    uint64_t exparams;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFile2(LPCWSTR filename, DWORD access, DWORD sharing, DWORD creation, CREATEFILE2_EXTENDED_PARAMETERS *exparams)
{
    struct qemu_CreateFile2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILE2);
    call.filename = (ULONG_PTR)filename;
    call.access = access;
    call.sharing = sharing;
    call.creation = creation;
    call.exparams = (ULONG_PTR)exparams;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFile2(struct qemu_syscall *call)
{
    struct qemu_CreateFile2 *c = (struct qemu_CreateFile2 *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(CreateFile2(QEMU_G2H(c->filename), c->access, c->sharing, c->creation, QEMU_G2H(c->exparams)));
}

#endif

struct qemu_DeleteFileW
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteFileW(LPCWSTR path)
{
    struct qemu_DeleteFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEFILEW);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteFileW(struct qemu_syscall *call)
{
    struct qemu_DeleteFileW *c = (struct qemu_DeleteFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = DeleteFileW(QEMU_G2H(c->path));
}

#endif

struct qemu_DeleteFileA
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteFileA(LPCSTR path)
{
    struct qemu_DeleteFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEFILEA);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteFileA(struct qemu_syscall *call)
{
    struct qemu_DeleteFileA *c = (struct qemu_DeleteFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = DeleteFileA(QEMU_G2H(c->path));
}

#endif

struct qemu_ReplaceFileW
{
    struct qemu_syscall super;
    uint64_t lpReplacedFileName;
    uint64_t lpReplacementFileName;
    uint64_t lpBackupFileName;
    uint64_t dwReplaceFlags;
    uint64_t lpExclude;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReplaceFileW(LPCWSTR lpReplacedFileName, LPCWSTR lpReplacementFileName, LPCWSTR lpBackupFileName, DWORD dwReplaceFlags, LPVOID lpExclude, LPVOID lpReserved)
{
    struct qemu_ReplaceFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPLACEFILEW);
    call.lpReplacedFileName = (ULONG_PTR)lpReplacedFileName;
    call.lpReplacementFileName = (ULONG_PTR)lpReplacementFileName;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;
    call.dwReplaceFlags = dwReplaceFlags;
    call.lpExclude = (ULONG_PTR)lpExclude;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReplaceFileW(struct qemu_syscall *call)
{
    struct qemu_ReplaceFileW *c = (struct qemu_ReplaceFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = ReplaceFileW(QEMU_G2H(c->lpReplacedFileName), QEMU_G2H(c->lpReplacementFileName),
            QEMU_G2H(c->lpBackupFileName), c->dwReplaceFlags, QEMU_G2H(c->lpExclude), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_ReplaceFileA
{
    struct qemu_syscall super;
    uint64_t lpReplacedFileName;
    uint64_t lpReplacementFileName;
    uint64_t lpBackupFileName;
    uint64_t dwReplaceFlags;
    uint64_t lpExclude;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReplaceFileA(LPCSTR lpReplacedFileName,LPCSTR lpReplacementFileName, LPCSTR lpBackupFileName,
        DWORD dwReplaceFlags, LPVOID lpExclude, LPVOID lpReserved)
{
    struct qemu_ReplaceFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPLACEFILEA);
    call.lpReplacedFileName = (ULONG_PTR)lpReplacedFileName;
    call.lpReplacementFileName = (ULONG_PTR)lpReplacementFileName;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;
    call.dwReplaceFlags = dwReplaceFlags;
    call.lpExclude = (ULONG_PTR)lpExclude;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReplaceFileA(struct qemu_syscall *call)
{
    struct qemu_ReplaceFileA *c = (struct qemu_ReplaceFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = ReplaceFileA(QEMU_G2H(c->lpReplacedFileName), QEMU_G2H(c->lpReplacementFileName),
            QEMU_G2H(c->lpBackupFileName), c->dwReplaceFlags, QEMU_G2H(c->lpExclude), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_FindFirstFileExW
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t level;
    uint64_t data;
    uint64_t search_op;
    uint64_t filter;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstFileExW(LPCWSTR filename, FINDEX_INFO_LEVELS level, LPVOID data, FINDEX_SEARCH_OPS search_op, LPVOID filter, DWORD flags)
{
    struct qemu_FindFirstFileExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTFILEEXW);
    call.filename = (ULONG_PTR)filename;
    call.level = (ULONG_PTR)level;
    call.data = (ULONG_PTR)data;
    call.search_op = (ULONG_PTR)search_op;
    call.filter = (ULONG_PTR)filter;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstFileExW(struct qemu_syscall *call)
{
    struct qemu_FindFirstFileExW *c = (struct qemu_FindFirstFileExW *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(FindFirstFileExW(QEMU_G2H(c->filename), c->level, QEMU_G2H(c->data), c->search_op, QEMU_G2H(c->filter), c->flags));
}

#endif

struct qemu_FindNextFileW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextFileW(HANDLE handle, WIN32_FIND_DATAW *data)
{
    struct qemu_FindNextFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTFILEW);
    call.handle = guest_HANDLE_g2h(handle);
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextFileW(struct qemu_syscall *call)
{
    struct qemu_FindNextFileW *c = (struct qemu_FindNextFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = FindNextFileW(QEMU_G2H(c->handle), QEMU_G2H(c->data));
}

#endif

struct qemu_FindClose
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindClose(HANDLE handle)
{
    struct qemu_FindClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDCLOSE);
    call.handle = guest_HANDLE_g2h(handle);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindClose(struct qemu_syscall *call)
{
    struct qemu_FindClose *c = (struct qemu_FindClose *)call;
    WINE_TRACE("\n");
    c->super.iret = FindClose(QEMU_G2H(c->handle));
}

#endif

struct qemu_FindFirstFileA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t lpFindData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, WIN32_FIND_DATAA *lpFindData)
{
    struct qemu_FindFirstFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTFILEA);
    call.lpFileName = (ULONG_PTR)lpFileName;
    call.lpFindData = (ULONG_PTR)lpFindData;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstFileA(struct qemu_syscall *call)
{
    struct qemu_FindFirstFileA *c = (struct qemu_FindFirstFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(FindFirstFileA(QEMU_G2H(c->lpFileName), QEMU_G2H(c->lpFindData)));
}

#endif

struct qemu_FindFirstFileExA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t fInfoLevelId;
    uint64_t lpFindFileData;
    uint64_t fSearchOp;
    uint64_t lpSearchFilter;
    uint64_t dwAdditionalFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstFileExA(LPCSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData, FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags)
{
    struct qemu_FindFirstFileExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTFILEEXA);
    call.lpFileName = (ULONG_PTR)lpFileName;
    call.fInfoLevelId = fInfoLevelId;
    call.lpFindFileData = (ULONG_PTR)lpFindFileData;
    call.fSearchOp = fSearchOp;
    call.lpSearchFilter = (ULONG_PTR)lpSearchFilter;
    call.dwAdditionalFlags = dwAdditionalFlags;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstFileExA(struct qemu_syscall *call)
{
    struct qemu_FindFirstFileExA *c = (struct qemu_FindFirstFileExA *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(FindFirstFileExA(QEMU_G2H(c->lpFileName), c->fInfoLevelId, QEMU_G2H(c->lpFindFileData), c->fSearchOp, QEMU_G2H(c->lpSearchFilter), c->dwAdditionalFlags));
}

#endif

struct qemu_FindFirstFileW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t lpFindData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, WIN32_FIND_DATAW *lpFindData)
{
    struct qemu_FindFirstFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTFILEW);
    call.lpFileName = (ULONG_PTR)lpFileName;
    call.lpFindData = (ULONG_PTR)lpFindData;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstFileW(struct qemu_syscall *call)
{
    struct qemu_FindFirstFileW *c = (struct qemu_FindFirstFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(FindFirstFileW(QEMU_G2H(c->lpFileName), QEMU_G2H(c->lpFindData)));
}

#endif

struct qemu_FindNextFileA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextFileA(HANDLE handle, WIN32_FIND_DATAA *data)
{
    struct qemu_FindNextFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTFILEA);
    call.handle = guest_HANDLE_g2h(handle);
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextFileA(struct qemu_syscall *call)
{
    struct qemu_FindNextFileA *c = (struct qemu_FindNextFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = FindNextFileA(QEMU_G2H(c->handle), QEMU_G2H(c->data));
}

#endif

struct qemu_GetFileAttributesW
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileAttributesW(LPCWSTR name)
{
    struct qemu_GetFileAttributesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEATTRIBUTESW);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileAttributesW(struct qemu_syscall *call)
{
    struct qemu_GetFileAttributesW *c = (struct qemu_GetFileAttributesW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileAttributesW(QEMU_G2H(c->name));
}

#endif

struct qemu_GetFileAttributesA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileAttributesA(LPCSTR name)
{
    struct qemu_GetFileAttributesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEATTRIBUTESA);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileAttributesA(struct qemu_syscall *call)
{
    struct qemu_GetFileAttributesA *c = (struct qemu_GetFileAttributesA *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = GetFileAttributesA(QEMU_G2H(c->name));
}

#endif

struct qemu_SetFileAttributesW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t attributes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileAttributesW(LPCWSTR name, DWORD attributes)
{
    struct qemu_SetFileAttributesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEATTRIBUTESW);
    call.name = (ULONG_PTR)name;
    call.attributes = attributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileAttributesW(struct qemu_syscall *call)
{
    struct qemu_SetFileAttributesW *c = (struct qemu_SetFileAttributesW *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFileAttributesW(QEMU_G2H(c->name), c->attributes);
}

#endif

struct qemu_SetFileAttributesA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t attributes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileAttributesA(LPCSTR name, DWORD attributes)
{
    struct qemu_SetFileAttributesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILEATTRIBUTESA);
    call.name = (ULONG_PTR)name;
    call.attributes = attributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileAttributesA(struct qemu_syscall *call)
{
    struct qemu_SetFileAttributesA *c = (struct qemu_SetFileAttributesA *)call;
    WINE_TRACE("\n");
    c->super.iret = SetFileAttributesA(QEMU_G2H(c->name), c->attributes);
}

#endif

struct qemu_GetFileAttributesExW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t level;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileAttributesExW(LPCWSTR name, GET_FILEEX_INFO_LEVELS level, LPVOID ptr)
{
    struct qemu_GetFileAttributesExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEATTRIBUTESEXW);
    call.name = (ULONG_PTR)name;
    call.level = level;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileAttributesExW(struct qemu_syscall *call)
{
    struct qemu_GetFileAttributesExW *c = (struct qemu_GetFileAttributesExW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileAttributesExW(QEMU_G2H(c->name), c->level, QEMU_G2H(c->ptr));
}

#endif

struct qemu_GetFileAttributesExA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t level;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileAttributesExA(LPCSTR name, GET_FILEEX_INFO_LEVELS level, LPVOID ptr)
{
    struct qemu_GetFileAttributesExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEATTRIBUTESEXA);
    call.name = (ULONG_PTR)name;
    call.level = (ULONG_PTR)level;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileAttributesExA(struct qemu_syscall *call)
{
    struct qemu_GetFileAttributesExA *c = (struct qemu_GetFileAttributesExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileAttributesExA(QEMU_G2H(c->name), c->level, QEMU_G2H(c->ptr));
}

#endif

struct qemu_GetCompressedFileSizeW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t size_high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCompressedFileSizeW(LPCWSTR name, LPDWORD size_high)
{
    struct qemu_GetCompressedFileSizeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPRESSEDFILESIZEW);
    call.name = (ULONG_PTR)name;
    call.size_high = (ULONG_PTR)size_high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCompressedFileSizeW(struct qemu_syscall *call)
{
    struct qemu_GetCompressedFileSizeW *c = (struct qemu_GetCompressedFileSizeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCompressedFileSizeW(QEMU_G2H(c->name), QEMU_G2H(c->size_high));
}

#endif

struct qemu_GetCompressedFileSizeA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t size_high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCompressedFileSizeA(LPCSTR name, LPDWORD size_high)
{
    struct qemu_GetCompressedFileSizeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPRESSEDFILESIZEA);
    call.name = (ULONG_PTR)name;
    call.size_high = (ULONG_PTR)size_high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCompressedFileSizeA(struct qemu_syscall *call)
{
    struct qemu_GetCompressedFileSizeA *c = (struct qemu_GetCompressedFileSizeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCompressedFileSizeA(QEMU_G2H(c->name), QEMU_G2H(c->size_high));
}

#endif

struct qemu_OpenVxDHandle
{
    struct qemu_syscall super;
    uint64_t hHandleRing3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenVxDHandle(HANDLE hHandleRing3)
{
    struct qemu_OpenVxDHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENVXDHANDLE);
    call.hHandleRing3 = guest_HANDLE_g2h(hHandleRing3);

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenVxDHandle(struct qemu_syscall *call)
{
    struct qemu_OpenVxDHandle *c = (struct qemu_OpenVxDHandle *)call;
    WINE_FIXME("What is this?\n");
    c->super.iret = 0;
}

#endif

struct qemu_DeviceIoControl
{
    struct qemu_syscall super;
    uint64_t hDevice;
    uint64_t dwIoControlCode;
    uint64_t lpvInBuffer;
    uint64_t cbInBuffer;
    uint64_t lpvOutBuffer;
    uint64_t cbOutBuffer;
    uint64_t lpcbBytesReturned;
    uint64_t lpOverlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPOVERLAPPED lpOverlapped)
{
    struct qemu_DeviceIoControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEVICEIOCONTROL);
    call.hDevice = guest_HANDLE_g2h(hDevice);
    call.dwIoControlCode = dwIoControlCode;
    call.lpvInBuffer = (ULONG_PTR)lpvInBuffer;
    call.cbInBuffer = cbInBuffer;
    call.lpvOutBuffer = (ULONG_PTR)lpvOutBuffer;
    call.cbOutBuffer = cbOutBuffer;
    call.lpcbBytesReturned = (ULONG_PTR)lpcbBytesReturned;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeviceIoControl(struct qemu_syscall *call)
{
    struct qemu_DeviceIoControl *c = (struct qemu_DeviceIoControl *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = DeviceIoControl((HANDLE)c->hDevice, c->dwIoControlCode, QEMU_G2H(c->lpvInBuffer),
            c->cbInBuffer, QEMU_G2H(c->lpvOutBuffer), c->cbOutBuffer, QEMU_G2H(c->lpcbBytesReturned),
            QEMU_G2H(c->lpOverlapped));
}

#endif

struct qemu_OpenFile
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t ofs;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI OpenFile(LPCSTR name, OFSTRUCT *ofs, UINT mode)
{
    struct qemu_OpenFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENFILE);
    call.name = (ULONG_PTR)name;
    call.ofs = (ULONG_PTR)ofs;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenFile(struct qemu_syscall *call)
{
    struct qemu_OpenFile *c = (struct qemu_OpenFile *)call;
    WINE_TRACE("\n");
    c->super.iret = OpenFile(QEMU_G2H(c->name), QEMU_G2H(c->ofs), c->mode);
}

#endif

struct qemu_OpenFileById
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t id;
    uint64_t access;
    uint64_t share;
    uint64_t sec_attr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenFileById(HANDLE handle, LPFILE_ID_DESCRIPTOR id, DWORD access, DWORD share,
        LPSECURITY_ATTRIBUTES sec_attr, DWORD flags)
{
    struct qemu_OpenFileById call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENFILEBYID);
    call.handle = guest_HANDLE_g2h(handle);
    call.id = (ULONG_PTR)id;
    call.access = access;
    call.share = share;
    call.sec_attr = (ULONG_PTR)sec_attr;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add OpenFileById to Wine headers? */
extern HANDLE WINAPI OpenFileById(HANDLE handle, LPFILE_ID_DESCRIPTOR id, DWORD access, DWORD share,
        LPSECURITY_ATTRIBUTES sec_attr, DWORD flags);
void qemu_OpenFileById(struct qemu_syscall *call)
{
    struct qemu_OpenFileById *c = (struct qemu_OpenFileById *)call;
    struct SA_conv_struct conv;
    SECURITY_ATTRIBUTES *sa = &conv.sa;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sa = QEMU_G2H(c->sec_attr);
#else
    if (c->sec_attr)
        SECURITY_ATTRIBUTES_g2h(&conv, QEMU_G2H(c->sec_attr));
    else
        sa = NULL;
#endif

    c->super.iret = QEMU_H2G(OpenFileById(QEMU_G2H(c->handle), QEMU_G2H(c->id), c->access, c->share,
            sa, c->flags));
}

#endif

struct qemu_K32EnumDeviceDrivers
{
    struct qemu_syscall super;
    uint64_t image_base;
    uint64_t cb;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EnumDeviceDrivers(void **image_base, DWORD cb, DWORD *needed)
{
    struct qemu_K32EnumDeviceDrivers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32ENUMDEVICEDRIVERS);
    call.image_base = (ULONG_PTR)image_base;
    call.cb = (ULONG_PTR)cb;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32EnumDeviceDrivers to Wine headers? */
extern BOOL WINAPI K32EnumDeviceDrivers(void **image_base, DWORD cb, DWORD *needed);
void qemu_K32EnumDeviceDrivers(struct qemu_syscall *call)
{
    struct qemu_K32EnumDeviceDrivers *c = (struct qemu_K32EnumDeviceDrivers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EnumDeviceDrivers(QEMU_G2H(c->image_base), c->cb, QEMU_G2H(c->needed));
}

#endif

struct qemu_K32GetDeviceDriverBaseNameA
{
    struct qemu_syscall super;
    uint64_t image_base;
    uint64_t base_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetDeviceDriverBaseNameA(void *image_base, LPSTR base_name, DWORD size)
{
    struct qemu_K32GetDeviceDriverBaseNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETDEVICEDRIVERBASENAMEA);
    call.image_base = (ULONG_PTR)image_base;
    call.base_name = (ULONG_PTR)base_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetDeviceDriverBaseNameA to Wine headers? */
extern DWORD WINAPI K32GetDeviceDriverBaseNameA(void *image_base, LPSTR base_name, DWORD size);
void qemu_K32GetDeviceDriverBaseNameA(struct qemu_syscall *call)
{
    struct qemu_K32GetDeviceDriverBaseNameA *c = (struct qemu_K32GetDeviceDriverBaseNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetDeviceDriverBaseNameA(QEMU_G2H(c->image_base), QEMU_G2H(c->base_name), c->size);
}

#endif

struct qemu_K32GetDeviceDriverBaseNameW
{
    struct qemu_syscall super;
    uint64_t image_base;
    uint64_t base_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetDeviceDriverBaseNameW(void *image_base, LPWSTR base_name, DWORD size)
{
    struct qemu_K32GetDeviceDriverBaseNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETDEVICEDRIVERBASENAMEW);
    call.image_base = (ULONG_PTR)image_base;
    call.base_name = (ULONG_PTR)base_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetDeviceDriverBaseNameW to Wine headers? */
extern DWORD WINAPI K32GetDeviceDriverBaseNameW(void *image_base, LPWSTR base_name, DWORD size);
void qemu_K32GetDeviceDriverBaseNameW(struct qemu_syscall *call)
{
    struct qemu_K32GetDeviceDriverBaseNameW *c = (struct qemu_K32GetDeviceDriverBaseNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetDeviceDriverBaseNameW(QEMU_G2H(c->image_base), QEMU_G2H(c->base_name), c->size);
}

#endif

struct qemu_K32GetDeviceDriverFileNameA
{
    struct qemu_syscall super;
    uint64_t image_base;
    uint64_t file_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetDeviceDriverFileNameA(void *image_base, LPSTR file_name, DWORD size)
{
    struct qemu_K32GetDeviceDriverFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETDEVICEDRIVERFILENAMEA);
    call.image_base = (ULONG_PTR)image_base;
    call.file_name = (ULONG_PTR)file_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetDeviceDriverFileNameA to Wine headers? */
extern DWORD WINAPI K32GetDeviceDriverFileNameA(void *image_base, LPSTR file_name, DWORD size);
void qemu_K32GetDeviceDriverFileNameA(struct qemu_syscall *call)
{
    struct qemu_K32GetDeviceDriverFileNameA *c = (struct qemu_K32GetDeviceDriverFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetDeviceDriverFileNameA(QEMU_G2H(c->image_base), QEMU_G2H(c->file_name), c->size);
}

#endif

struct qemu_K32GetDeviceDriverFileNameW
{
    struct qemu_syscall super;
    uint64_t image_base;
    uint64_t file_name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetDeviceDriverFileNameW(void *image_base, LPWSTR file_name, DWORD size)
{
    struct qemu_K32GetDeviceDriverFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETDEVICEDRIVERFILENAMEW);
    call.image_base = (ULONG_PTR)image_base;
    call.file_name = (ULONG_PTR)file_name;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add K32GetDeviceDriverFileNameW to Wine headers? */
extern DWORD WINAPI K32GetDeviceDriverFileNameW(void *image_base, LPWSTR file_name, DWORD size);
void qemu_K32GetDeviceDriverFileNameW(struct qemu_syscall *call)
{
    struct qemu_K32GetDeviceDriverFileNameW *c = (struct qemu_K32GetDeviceDriverFileNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetDeviceDriverFileNameW(QEMU_G2H(c->image_base), QEMU_G2H(c->file_name), c->size);
}

#endif

struct qemu_GetFinalPathNameByHandleW
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t path;
    uint64_t charcount;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFinalPathNameByHandleW(HANDLE file, LPWSTR path, DWORD charcount, DWORD flags)
{
    struct qemu_GetFinalPathNameByHandleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFINALPATHNAMEBYHANDLEW);
    call.file = guest_HANDLE_g2h(file);
    call.path = (ULONG_PTR)path;
    call.charcount = charcount;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFinalPathNameByHandleW to Wine headers? */
extern DWORD WINAPI GetFinalPathNameByHandleW(HANDLE file, LPWSTR path, DWORD charcount, DWORD flags);
void qemu_GetFinalPathNameByHandleW(struct qemu_syscall *call)
{
    struct qemu_GetFinalPathNameByHandleW *c = (struct qemu_GetFinalPathNameByHandleW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFinalPathNameByHandleW(QEMU_G2H(c->file), QEMU_G2H(c->path), c->charcount, c->flags);
}

#endif

struct qemu_GetFinalPathNameByHandleA
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t path;
    uint64_t charcount;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFinalPathNameByHandleA(HANDLE file, LPSTR path, DWORD charcount, DWORD flags)
{
    struct qemu_GetFinalPathNameByHandleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFINALPATHNAMEBYHANDLEA);
    call.file = guest_HANDLE_g2h(file);
    call.path = (ULONG_PTR)path;
    call.charcount = charcount;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFinalPathNameByHandleA to Wine headers? */
extern DWORD WINAPI GetFinalPathNameByHandleA(HANDLE file, LPSTR path, DWORD charcount, DWORD flags);
void qemu_GetFinalPathNameByHandleA(struct qemu_syscall *call)
{
    struct qemu_GetFinalPathNameByHandleA *c = (struct qemu_GetFinalPathNameByHandleA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFinalPathNameByHandleA((HANDLE)c->file, QEMU_G2H(c->path), c->charcount, c->flags);
}

#endif

