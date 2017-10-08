/*
 * Copyright 2017 Stefan Dösinger
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

#include "windows-user-services.h"
#include "dll_list.h"
#include "ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_LdrFindEntryForAddress
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t mod;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_LdrFindEntryForAddress(const void *addr, LDR_MODULE **mod)
{
    /* FIXME: With proper data in the PEB we should be able to do this on the
     * client side.
     *
     * FIXME 2: HMODULE != LDR_MODULE, but for now it is good enough for our little
     * PE loader. */
    struct qemu_LdrFindEntryForAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRFINDENTRYFORADDRESS);
    call.addr = (ULONG_PTR)addr;
    call.mod = (ULONG_PTR)mod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrFindEntryForAddress(struct qemu_syscall *call)
{
    struct qemu_LdrFindEntryForAddress *c = (struct qemu_LdrFindEntryForAddress *)call;
    HMODULE mod;
    WINE_TRACE("\n");

    if (qemu_ops->qemu_FindEntryForAddress(QEMU_G2H(c->addr), &mod))
        c->super.iret = STATUS_SUCCESS;
    else
        c->super.iret = STATUS_NO_MORE_ENTRIES;

    *(uint64_t *)QEMU_G2H(c->mod) = (ULONG_PTR)mod;
}

#endif

#ifdef QEMU_DLL_GUEST

/* Copypasted from Wine with exception handling removed for now. */
PIMAGE_NT_HEADERS WINAPI ntdll_RtlImageNtHeader(HMODULE hModule)
{
    IMAGE_NT_HEADERS *ret;

    IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)hModule;

    ret = NULL;
    if (dos->e_magic == IMAGE_DOS_SIGNATURE)
    {
        ret = (IMAGE_NT_HEADERS *)((char *)dos + dos->e_lfanew);
        if (ret->Signature != IMAGE_NT_SIGNATURE) ret = NULL;
    }
    return ret;
}

/* Copypasted from Wine. */
PIMAGE_SECTION_HEADER WINAPI ntdll_RtlImageRvaToSection( const IMAGE_NT_HEADERS *nt,
                                                   HMODULE module, DWORD rva )
{
    int i;
    const IMAGE_SECTION_HEADER *sec;

    sec = (const IMAGE_SECTION_HEADER*)((const char*)&nt->OptionalHeader +
                                        nt->FileHeader.SizeOfOptionalHeader);
    for (i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++)
    {
        if ((sec->VirtualAddress <= rva) && (sec->VirtualAddress + sec->SizeOfRawData > rva))
            return (PIMAGE_SECTION_HEADER)sec;
    }
    return NULL;
}

/* Copypasted from Wine. */
PVOID WINAPI ntdll_RtlImageRvaToVa( const IMAGE_NT_HEADERS *nt, HMODULE module,
                              DWORD rva, IMAGE_SECTION_HEADER **section )
{
    IMAGE_SECTION_HEADER *sec;

    if (section && *section)  /* try this section first */
    {
        sec = *section;
        if ((sec->VirtualAddress <= rva) && (sec->VirtualAddress + sec->SizeOfRawData > rva))
            goto found;
    }
    if (!(sec = ntdll_RtlImageRvaToSection( nt, module, rva ))) return NULL;
 found:
    if (section) *section = sec;
    return (char *)module + sec->PointerToRawData + (rva - sec->VirtualAddress);
}

/* Copypasted from Wine. */
PVOID WINAPI ntdll_RtlImageDirectoryEntryToData( HMODULE module, BOOL image, WORD dir, ULONG *size )
{
    const IMAGE_NT_HEADERS *nt;
    DWORD addr;

    if ((ULONG_PTR)module & 1)  /* mapped as data file */
    {
        module = (HMODULE)((ULONG_PTR)module & ~1);
        image = FALSE;
    }
    if (!(nt = ntdll_RtlImageNtHeader( module ))) return NULL;
    if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        const IMAGE_NT_HEADERS64 *nt64 = (const IMAGE_NT_HEADERS64 *)nt;

        if (dir >= nt64->OptionalHeader.NumberOfRvaAndSizes) return NULL;
        if (!(addr = nt64->OptionalHeader.DataDirectory[dir].VirtualAddress)) return NULL;
        *size = nt64->OptionalHeader.DataDirectory[dir].Size;
        if (image || addr < nt64->OptionalHeader.SizeOfHeaders) return (char *)module + addr;
    }
    else if (nt->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
    {
        const IMAGE_NT_HEADERS32 *nt32 = (const IMAGE_NT_HEADERS32 *)nt;

        if (dir >= nt32->OptionalHeader.NumberOfRvaAndSizes) return NULL;
        if (!(addr = nt32->OptionalHeader.DataDirectory[dir].VirtualAddress)) return NULL;
        *size = nt32->OptionalHeader.DataDirectory[dir].Size;
        if (image || addr < nt32->OptionalHeader.SizeOfHeaders) return (char *)module + addr;
    }
    else return NULL;

    /* not mapped as image, need to find the section containing the virtual address */
    return ntdll_RtlImageRvaToVa( nt, module, addr, NULL );
}

#endif

struct qemu_RtlPcToFileHeader
{
    struct qemu_syscall super;
    uint64_t pc;
    uint64_t address;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI RtlPcToFileHeader(void *pc, void **address)
{
    struct qemu_RtlPcToFileHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLPCTOFILEHEADER);
    call.pc = (ULONG_PTR)pc;
    call.address = (ULONG_PTR)address;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlPcToFileHeader(struct qemu_syscall *call)
{
    struct qemu_RtlPcToFileHeader *c = (struct qemu_RtlPcToFileHeader *)call;
    void *ret = NULL;

    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(qemu_ops->qemu_RtlPcToFileHeader(QEMU_G2H(c->pc), c->address ? &ret : NULL));
    if (c->address)
        *(uint64_t *)QEMU_G2H(c->address) = QEMU_H2G(ret);
}

#endif
