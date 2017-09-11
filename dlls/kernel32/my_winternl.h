/*
 * Internal NT APIs and data structures
 *
 * Copyright (C) the Wine project
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

/* Copypasted from Wine because mingw is missing all these things. */

#include <ntdef.h>
#include <winternl.h>

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    PVOID Handle;
} CURDIR, *PCURDIR;

typedef struct RTL_DRIVE_LETTER_CURDIR
{
    USHORT              Flags;
    USHORT              Length;
    ULONG               TimeStamp;
    UNICODE_STRING      DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct tagRTL_BITMAP {
    ULONG  SizeOfBitMap; /* Number of bits in the bitmap */
    PULONG Buffer; /* Bitmap data, assumed sized to a DWORD boundary */
} RTL_BITMAP, *PRTL_BITMAP;

typedef struct my_PEB
{                                                                 /* win32/win64 */
    BOOLEAN                      InheritedAddressSpace;             /* 000/000 */
    BOOLEAN                      ReadImageFileExecOptions;          /* 001/001 */
    BOOLEAN                      BeingDebugged;                     /* 002/002 */
    BOOLEAN                      SpareBool;                         /* 003/003 */
    HANDLE                       Mutant;                            /* 004/008 */
    HMODULE                      ImageBaseAddress;                  /* 008/010 */
    PPEB_LDR_DATA                LdrData;                           /* 00c/018 */
    RTL_USER_PROCESS_PARAMETERS *ProcessParameters;                 /* 010/020 */
    PVOID                        SubSystemData;                     /* 014/028 */
    HANDLE                       ProcessHeap;                       /* 018/030 */
    PRTL_CRITICAL_SECTION        FastPebLock;                       /* 01c/038 */
    PVOID /*PPEBLOCKROUTINE*/    FastPebLockRoutine;                /* 020/040 */
    PVOID /*PPEBLOCKROUTINE*/    FastPebUnlockRoutine;              /* 024/048 */
    ULONG                        EnvironmentUpdateCount;            /* 028/050 */
    PVOID                        KernelCallbackTable;               /* 02c/058 */
    ULONG                        Reserved[2];                       /* 030/060 */
    PVOID /*PPEB_FREE_BLOCK*/    FreeList;                          /* 038/068 */
    ULONG                        TlsExpansionCounter;               /* 03c/070 */
    PRTL_BITMAP                  TlsBitmap;                         /* 040/078 */
    ULONG                        TlsBitmapBits[2];                  /* 044/080 */
    PVOID                        ReadOnlySharedMemoryBase;          /* 04c/088 */
    PVOID                        ReadOnlySharedMemoryHeap;          /* 050/090 */
    PVOID                       *ReadOnlyStaticServerData;          /* 054/098 */
    PVOID                        AnsiCodePageData;                  /* 058/0a0 */
    PVOID                        OemCodePageData;                   /* 05c/0a8 */
    PVOID                        UnicodeCaseTableData;              /* 060/0b0 */
    ULONG                        NumberOfProcessors;                /* 064/0b8 */
    ULONG                        NtGlobalFlag;                      /* 068/0bc */
    LARGE_INTEGER                CriticalSectionTimeout;            /* 070/0c0 */
    SIZE_T                       HeapSegmentReserve;                /* 078/0c8 */
    SIZE_T                       HeapSegmentCommit;                 /* 07c/0d0 */
    SIZE_T                       HeapDeCommitTotalFreeThreshold;    /* 080/0d8 */
    SIZE_T                       HeapDeCommitFreeBlockThreshold;    /* 084/0e0 */
    ULONG                        NumberOfHeaps;                     /* 088/0e8 */
    ULONG                        MaximumNumberOfHeaps;              /* 08c/0ec */
    PVOID                       *ProcessHeaps;                      /* 090/0f0 */
    PVOID                        GdiSharedHandleTable;              /* 094/0f8 */
    PVOID                        ProcessStarterHelper;              /* 098/100 */
    PVOID                        GdiDCAttributeList;                /* 09c/108 */
    PVOID                        LoaderLock;                        /* 0a0/110 */
    ULONG                        OSMajorVersion;                    /* 0a4/118 */
    ULONG                        OSMinorVersion;                    /* 0a8/11c */
    ULONG                        OSBuildNumber;                     /* 0ac/120 */
    ULONG                        OSPlatformId;                      /* 0b0/124 */
    ULONG                        ImageSubSystem;                    /* 0b4/128 */
    ULONG                        ImageSubSystemMajorVersion;        /* 0b8/12c */
    ULONG                        ImageSubSystemMinorVersion;        /* 0bc/130 */
    ULONG                        ImageProcessAffinityMask;          /* 0c0/134 */
    HANDLE                       GdiHandleBuffer[28];               /* 0c4/138 */
    ULONG                        unknown[6];                        /* 134/218 */
    PVOID                        PostProcessInitRoutine;            /* 14c/230 */
    PRTL_BITMAP                  TlsExpansionBitmap;                /* 150/238 */
    ULONG                        TlsExpansionBitmapBits[32];        /* 154/240 */
    ULONG                        SessionId;                         /* 1d4/2c0 */
    ULARGE_INTEGER               AppCompatFlags;                    /* 1d8/2c8 */
    ULARGE_INTEGER               AppCompatFlagsUser;                /* 1e0/2d0 */
    PVOID                        ShimData;                          /* 1e8/2d8 */
    PVOID                        AppCompatInfo;                     /* 1ec/2e0 */
    UNICODE_STRING               CSDVersion;                        /* 1f0/2e8 */
    PVOID                        ActivationContextData;             /* 1f8/2f8 */
    PVOID                        ProcessAssemblyStorageMap;         /* 1fc/300 */
    PVOID                        SystemDefaultActivationData;       /* 200/308 */
    PVOID                        SystemAssemblyStorageMap;          /* 204/310 */
    SIZE_T                       MinimumStackCommit;                /* 208/318 */
    PVOID                       *FlsCallback;                       /* 20c/320 */
    LIST_ENTRY                   FlsListHead;                       /* 210/328 */
    PRTL_BITMAP                  FlsBitmap;                         /* 218/338 */
    ULONG                        FlsBitmapBits[4];                  /* 21c/340 */
} myPEB, *myPPEB;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
    struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *Previous;
    struct _ACTIVATION_CONTEXT                 *ActivationContext;
    ULONG                                       Flags;
} RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

typedef struct _GDI_TEB_BATCH
{
    ULONG  Offset;
    HANDLE HDC;
    ULONG  Buffer[0x136];
} GDI_TEB_BATCH;

typedef struct _ACTIVATION_CONTEXT_STACK
{
    ULONG                               Flags;
    ULONG                               NextCookieSequenceNumber;
    RTL_ACTIVATION_CONTEXT_STACK_FRAME *ActiveFrame;
    LIST_ENTRY                          FrameListCache;
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

typedef struct my_TEB
{                                                                 /* win32/win64 */
    NT_TIB                       Tib;                               /* 000/0000 */
    PVOID                        EnvironmentPointer;                /* 01c/0038 */
    CLIENT_ID                    ClientId;                          /* 020/0040 */
    PVOID                        ActiveRpcHandle;                   /* 028/0050 */
    PVOID                        ThreadLocalStoragePointer;         /* 02c/0058 */
    myPPEB                       Peb;                               /* 030/0060 */
    ULONG                        LastErrorValue;                    /* 034/0068 */
    ULONG                        CountOfOwnedCriticalSections;      /* 038/006c */
    PVOID                        CsrClientThread;                   /* 03c/0070 */
    PVOID                        Win32ThreadInfo;                   /* 040/0078 */
    ULONG                        Win32ClientInfo[31];               /* 044/0080 used for user32 private data in Wine */
    PVOID                        WOW32Reserved;                     /* 0c0/0100 */
    ULONG                        CurrentLocale;                     /* 0c4/0108 */
    ULONG                        FpSoftwareStatusRegister;          /* 0c8/010c */
    PVOID                        SystemReserved1[54];               /* 0cc/0110 used for kernel32 private data in Wine */
    LONG                         ExceptionCode;                     /* 1a4/02c0 */
    ACTIVATION_CONTEXT_STACK     ActivationContextStack;            /* 1a8/02c8 */
    BYTE                         SpareBytes1[24];                   /* 1bc/02e8 */
    PVOID                        SystemReserved2[10];               /* 1d4/0300 used for ntdll platform-specific private data in Wine */
    GDI_TEB_BATCH                GdiTebBatch;                       /* 1fc/0350 used for ntdll private data in Wine */
    HANDLE                       gdiRgn;                            /* 6dc/0838 */
    HANDLE                       gdiPen;                            /* 6e0/0840 */
    HANDLE                       gdiBrush;                          /* 6e4/0848 */
    CLIENT_ID                    RealClientId;                      /* 6e8/0850 */
    HANDLE                       GdiCachedProcessHandle;            /* 6f0/0860 */
    ULONG                        GdiClientPID;                      /* 6f4/0868 */
    ULONG                        GdiClientTID;                      /* 6f8/086c */
    PVOID                        GdiThreadLocaleInfo;               /* 6fc/0870 */
    ULONG                        UserReserved[5];                   /* 700/0878 */
    PVOID                        glDispatchTable[280];              /* 714/0890 */
    PVOID                        glReserved1[26];                   /* b74/1150 */
    PVOID                        glReserved2;                       /* bdc/1220 */
    PVOID                        glSectionInfo;                     /* be0/1228 */
    PVOID                        glSection;                         /* be4/1230 */
    PVOID                        glTable;                           /* be8/1238 */
    PVOID                        glCurrentRC;                       /* bec/1240 */
    PVOID                        glContext;                         /* bf0/1248 */
    ULONG                        LastStatusValue;                   /* bf4/1250 */
    UNICODE_STRING               StaticUnicodeString;               /* bf8/1258 used by advapi32 */
    WCHAR                        StaticUnicodeBuffer[261];          /* c00/1268 used by advapi32 */
    PVOID                        DeallocationStack;                 /* e0c/1478 */
    PVOID                        TlsSlots[64];                      /* e10/1480 */
    LIST_ENTRY                   TlsLinks;                          /* f10/1680 */
    PVOID                        Vdm;                               /* f18/1690 */
    PVOID                        ReservedForNtRpc;                  /* f1c/1698 */
    PVOID                        DbgSsReserved[2];                  /* f20/16a0 */
    ULONG                        HardErrorDisabled;                 /* f28/16b0 */
    PVOID                        Instrumentation[16];               /* f2c/16b8 */
    PVOID                        WinSockData;                       /* f6c/1738 */
    ULONG                        GdiBatchCount;                     /* f70/1740 */
    ULONG                        Spare2;                            /* f74/1744 */
    PVOID                        Spare3;                            /* f78/1748 */
    PVOID                        Spare4;                            /* f7c/1750 */
    PVOID                        ReservedForOle;                    /* f80/1758 */
    ULONG                        WaitingOnLoaderLock;               /* f84/1760 */
    PVOID                        Reserved5[3];                      /* f88/1768 */
    PVOID                       *TlsExpansionSlots;                 /* f94/1780 */
    ULONG                        ImpersonationLocale;               /* f98/1788 */
    ULONG                        IsImpersonating;                   /* f9c/178c */
    PVOID                        NlsCache;                          /* fa0/1790 */
    PVOID                        ShimData;                          /* fa4/1798 */
    ULONG                        HeapVirtualAffinity;               /* fa8/17a0 */
    PVOID                        CurrentTransactionHandle;          /* fac/17a8 */
    PVOID                        ActiveFrame;                       /* fb0/17b0 */
#ifdef _WIN64
    PVOID                        unknown[2];                        /*     17b8 */
#endif
    PVOID                       *FlsSlots;                          /* fb4/17c8 */
} myTEB, *myPTEB;
