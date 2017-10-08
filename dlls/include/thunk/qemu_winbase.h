#ifndef HAVE_QEMU_WINBASE_H
#define HAVE_QEMU_WINBASE_H

#include "thunk/qemu_defines.h"

struct qemu_STARTUPINFO
{
        DWORD cb;
        qemu_ptr lpReserved;
        qemu_ptr lpDesktop;
        qemu_ptr lpTitle;
        DWORD dwX;
        DWORD dwY;
        DWORD dwXSize;
        DWORD dwYSize;
        DWORD dwXCountChars;
        DWORD dwYCountChars;
        DWORD dwFillAttribute;
        DWORD dwFlags;
        WORD wShowWindow;
        WORD cbReserved2;
        qemu_ptr lpReserved2;
        qemu_handle hStdInput;
        qemu_handle hStdOutput;
        qemu_handle hStdError;
};

#endif
