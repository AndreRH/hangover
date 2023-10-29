[![ubuntu-x86_64](https://github.com/AndreRH/hangover/workflows/ubuntu-x86_64/badge.svg)](https://github.com/AndreRH/hangover/actions?query=workflow%3Aubuntu-x86_64)
![stars](https://img.shields.io/github/stars/AndreRH/hangover)
![forks](https://img.shields.io/github/forks/AndreRH/hangover)
![Release](https://img.shields.io/github/v/release/AndreRH/hangover?color=green&include_prereleases)

## Hangover
This is Hangover, a project started by André Zwing and Stefan Dösinger in 2016 that currently can
run x86_32 Windows applications on aarch64 Wine.

### 1) How it works
In fact it now uses the WoW64 support in Wine + an emulator to run e.g. ARM32 on x86_64 or
i386 on ARM64. This is completely different from earlier versions of Hangover, which used QEMU and
broke out of emulation at the win32 API level. Instead we now break out at the win32 syscall level.

### 2) Status
While the overall stability was improved, expect crashes.

PPC64le isn't supported anymore and won't be added back in the near future.
Same for running x86_64 applications, though it might be added back as soon as the ARM64EC support in Wine is ready.
If you need those features, have a look at older releases before 0.8.x.

Emulator integrations:

- [QEMU](https://gitlab.com/qemu-project/qemu): Has the most issues and is by far the [slowest](https://github.com/AndreRH/hangover/tree/master/benchmarks) option
- [FEX](https://github.com/FEX-Emu/FEX): Available as Unix and PE
- [Box64](https://github.com/ptitSeb/box64/): Mostly done, but depends on the early 32-bit emulation of Box64
- [Blink](https://github.com/jart/blink): started, not part of this repository yet
- [Box32](https://news.itsfoss.com/box86-creator-ptitseb/): doesn't exist yet

(Box32 will translate i386 to ARM64. It's what we'll need,
because with WoW64 we only can emulate 32-bit architectures,
but require the emulator in our 64-bit address space.
It also will handle x86 faster than Box64 I assume.)

### 3) Preview
A paid [preview](https://www.patreon.com/posts/previews-82611984) is available with currently the following features coming soon:

- Updated Wine
- Updated FEX
- Updated Box64
- Updated Packages

### 4) Discord
A Discord Server is available for contributors and financial supporters (see point 8 below).
It provides advanced user support, development discussions and more.

### 5) Packages
For now Debian 12 (also for Raspbian) packages are available [here](https://www.patreon.com/andre_opensource/shop) to gain a limited user testing.

### 6) How to build
First make sure you have the submodules set up:
```bash
$ git submodule update --init --recursive
```
And note while Box64 is integrated, you can build other emulators (currently FEX and QEMU), but you don't need to, one is enough depending on your use-case.

#### 6.1) Wine (including Box64)
To build Hangover Wine you need:

- The dependencies to [build](https://wiki.winehq.org/Building_Wine#Satisfying_Build_Dependencies) a 64 bit Wine
- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 5GB of disk space

If you don't want to run 32-Bit ARM applications, you can drop ",arm" from the configure line.

on x86-64 (from the Hangover repository):
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --enable-win64 --disable-tests --with-mingw --enable-archs=i386,x86_64,arm
$ make -j$(nproc)
$ sudo env PATH="$PATH" make install
```

on ARM64 (from the Hangover repository):
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --disable-tests --with-mingw --enable-archs=i386,aarch64,arm
$ make -j$(nproc)
$ sudo env PATH="$PATH" make install
```

#### 6.2) QEMU (optional)
To build QEMU as a library you need:

- The dependencies to build QEMU (in particular glib)
- About 1GB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p qemu/build
$ cd qemu/build
$ ../configure --disable-werror --target-list=arm-linux-user,i386-linux-user
$ make -j$(nproc)
```

In case the compiler complains about something in linux-user/ioctls.h remove the corresponding line and run make again.

Place resulting libraries (build/libqemu-arm.so and/or build/libqemu-i386.so) in your library path (e.g /usr/lib) or set HOLIB to the full path of the resulting library.

Depreciation note: Placing the libraries under /opt will still work, but is deprecated. Until it is removed the load order is HOLIB, library path, /opt.

#### 6.3) FEX, Unix (optional)
To build FEXCore from FEX you need:

- The dependencies to [build](https://wiki.fex-emu.com/index.php/Development:Setting_up_FEX) FEX (in particular clang, libepoxy and libsdl2)
- About 1.4GB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p fex/build_unix
$ cd fex/build_unix
$ CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_LTO=True -DBUILD_TESTS=False -DENABLE_ASSERTIONS=False ..
$ make -j$(nproc) FEXCore_shared
```

Place resulting library (build_unix/FEXCore/Source/libFEXCore.so) in your library path (e.g /usr/lib) or set HOLIB to the full path of the resulting library.

Depreciation note: Placing the libraries under /opt will still work, but is deprecated. Until it is removed the load order is HOLIB, library path, /opt.

#### 6.4) FEX, PE (optional)
To build wow64fex from FEX you need:

- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 1.5GB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p fex/build_pe
$ cd fex/build_pe
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain_mingw.cmake -DENABLE_JEMALLOC=0 -DENABLE_JEMALLOC_GLIBC_ALLOC=0 -DMINGW_TRIPLE=aarch64-w64-mingw32 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTS=False -DENABLE_ASSERTIONS=False ..

$ make -j$(nproc) wow64fex
```

Place resulting library (build_pe/Bin/libwow64fex.dll) in your wine prefix under drive_c/windows/system32/.

### 7) Running
You can add the following environment variables:

* HODLL to select the emulator dll:
    * wow64cpu.dll for "native" i386 mode on x86_64
    * wowarmhw.dll for ARM emulation (Qemu)
    * xtajit.dll for i386 emulation (Qemu)
    * fexcore.dll for i386 emulation (FEX, Unix)
    * libwow64fex.dll for i386 emulation (FEX, PE)
    * box64cpu.dll for i386 emulation (Box64)
* HOLIB to set full path of the library, e.g. HOLIB=/path/to/libqemu-i386.so
* QEMU_LOG to set QEMU log channels, find some options [here.](https://github.com/AndreRH/qemu/blob/v5.2.0/util/log.c#L297)

#### 7.1) Box64
box64cpu.dll currently is the default for i386 emulation, so it's simply:

```bash
$ wine your_x86_application.exe
```

You might have better results with FEX for the moment.

#### 7.2) QEMU
Until the critical section issue is solved it is highly recomended to limit execution to 1 core with
"taskset -c 1" for Qemu emulation:

```bash
$ HODLL=xtajit.dll   taskset -c 1 wine your_x86_application.exe
$ HODLL=wowarmhw.dll taskset -c 1 wine your_arm_application.exe
```

#### 7.3) FEX, Unix
```bash
$ HODLL=fexcore.dll wine your_x86_application.exe
```

#### 7.4) FEX, PE
```bash
$ HODLL=libwow64fex.dll wine your_x86_application.exe
```

### 8) Todo

* Get more applications running
* QEMU: Investigate CriticalSection issues (just timing?)

### 9) Financial Contributors

Become a financial contributor and help me sustain this project:

https://www.patreon.com/andre_opensource

https://liberapay.com/andre_opensource

https://ko-fi.com/andre_opensource

### 10) Hardware Contributors

Become a hardware contributor and help me sustain this project:

https://throne.com/andrerh
