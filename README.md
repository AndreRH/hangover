[![ubuntu-x86_64](https://github.com/AndreRH/hangover/workflows/ubuntu-x86_64/badge.svg)](https://github.com/AndreRH/hangover/actions?query=workflow%3Aubuntu-x86_64)
![stars](https://img.shields.io/github/stars/AndreRH/hangover)
![forks](https://img.shields.io/github/forks/AndreRH/hangover)
![Release](https://img.shields.io/github/v/release/AndreRH/hangover?color=green&include_prereleases)

## Hangover
This is Hangover, a project started by André Zwing and Stefan Dösinger in 2016 to run
(x86_64)/x86_32 Windows applications on aarch64/(ppc64le)/x86_64 Wine. (Architectures in brackets
are currently not supported)

### 1) How it works
In fact it now uses the WoW64 support in Wine + an emulator to run e.g. ARM32 on x86_64 or
i386 on ARM64. This is completely different from earlier versions of Hangover, which used QEMU and
broke out of emulation at the win32 API level.

### 2) Status
While the overall stability was improved, expect crashes.

Emulator integrations:

- [QEMU](https://gitlab.com/qemu-project/qemu): Mostly done, though needs fixes for stability and CriticalSection
- [FEX](https://github.com/FEX-Emu/FEX): Mostly done, though needs fixes for invalidation and exceptions
- [Blink](https://github.com/jart/blink): started, not part of this repository yet
- [hex-emu](https://gitlab.com/hex-emu/hex-emu): not started yet
- [Box32](https://news.itsfoss.com/box86-creator-ptitseb/): doesn't exist yet

(Box32 will translate i386 to ARM64. It's what we'll need, because with WoW64 we only can emulate 32-bit architectures, but require the emulator in our 64-bit address space)

### 3) Preview
A paid [preview](https://www.patreon.com/posts/previews-82611984) is available with currently the following features:

- Wine 8.12 based
- Updated FEX

### 4) Discord
A Discord Server is available for contributors and financial supporters (see point 8 below).
It provides advanced user support, development discussions and more.

### 5) How to build
First make sure you have the submodules set up:
```bash
$ git submodule update --init --recursive
```
And note that you can build all emulators (currently QEMU and FEX), but you don't need to, one is enough depending on your use-case.

#### 5.1) QEMU
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

Place resulting libraries (build/libqemu-arm.so and/or build/libqemu-i386.so) in /opt (default) or set HOLIB to the full path of the resulting library.

#### 5.2) FEX
To build FEXCore from FEX you need:

- The dependencies to [build](https://wiki.fex-emu.com/index.php/Development:Setting_up_FEX) FEX
- About 1.5GB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p fex/build
$ cd fex/build
$ CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_LTO=True -DENABLE_LLD=True -DBUILD_TESTS=False -DENABLE_ASSERTIONS=False ..
$ make -j$(nproc) FEXCore_shared
```

On x86-64 you might need to add "-DENABLE_X86_HOST_DEBUG=True" to the cmake call.

Place resulting library (Build/External/FEXCore/Source/libFEXCore.so) in /opt (default) or set HOLIB to the full path of the resulting library.

#### 5.3) Wine
To build Hangover Wine you need:

- The dependencies to [build](https://wiki.winehq.org/Building_Wine#Satisfying_Build_Dependencies) a 64 bit Wine
- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 5GB of disk space

on x86-64 (from the Hangover repository):
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --enable-win64 --disable-tests --with-mingw --enable-archs=i386,x86_64,arm
$ make -j$(nproc)
$ sudo make install
```

on ARM64 (from the Hangover repository):
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --disable-tests --with-mingw --enable-archs=i386,aarch64,arm
$ make -j$(nproc)
$ sudo make install
```

### 6) Running
You can add the following environment variables:

* HODLL to select the emulator dll:
    * wow64cpu.dll for "native" i386 mode on x86_64
    * wowarmhw.dll for ARM emulation (Qemu)
    * xtajit.dll for i386 emulation (Qemu)
    * fexcore.dll for i386 emulation (FEX)
* HOLIB to set full path of the library, e.g. HOLIB=/path/to/libqemu-i386.so
* QEMU_LOG to set QEMU log channels, find some options [here.](https://github.com/AndreRH/qemu/blob/v5.2.0/util/log.c#L297)

#### 6.1) QEMU
Until the critical section issue is solved it is highly recomended to limit execution to 1 core with
"taskset -c 1" for Qemu emulation:

```bash
$ HODLL=xtajit.dll   taskset -c 1 wine your_x86_application.exe
$ HODLL=wowarmhw.dll taskset -c 1 wine your_arm_application.exe
```

#### 6.2) FEX
fexcore.dll currently is the default for i386 emulation, so it's simply:

```bash
$ wine your_x86_application.exe
```

### 7) Todo

* Get more applications running
* QMEU: Investigate CriticalSection issues (just timing?)
* FEX: Fix invalidation and exceptions (maybe as PE module)

### 8) Financial Contributors

Become a financial contributor and help me sustain this project:

https://www.patreon.com/andre_opensource

https://liberapay.com/andre_opensource

https://ko-fi.com/andre_opensource
