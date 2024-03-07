![stars](https://img.shields.io/github/stars/AndreRH/hangover?style=flat-square)
![forks](https://img.shields.io/github/forks/AndreRH/hangover?style=flat-square)
![Release](https://img.shields.io/github/v/release/AndreRH/hangover?style=flat-square)

Make sure to leave a :star: :)

## Hangover
This is Hangover, a project started by André Zwing and Stefan Dösinger in 2016 that currently can
run x86_32 Windows applications on aarch64 Wine.

### 1) How it works
Hangover uses various emulators as DLLs (pick one that suits your needs, e.g. works for you) to only emulate the application you want to run instead of emulating a complete Wine installation.

As soon as the application does a Windows/Wine system call, say NtUserCreateWindowEx, it's executed outside the emulator (read non-emulated, fast, native). Even better, everything Unix related is never emulated.

In short, we break out of emulation at the win32 syscall or wine unix call level for performance reasons, which is enabled by the WoW64 support in Wine.

### 2) Status
While the overall stability was improved, expect issues.

For Benchmarks see [here](benchmarks/readme.md). They show that the Hangover approach works as expected, as only emulating the application instead of a complete Wine installation has benefits. It's especially visible with box64cpu vs. Wine running under Box64.

Current main focus is to run i386 Windows applications on ARM64 Linux, but it's also possible to run ARM32 Windows applications on x86_64 Linux. I also started working on RISC-V Linux [support](https://www.patreon.com/posts/risc-v-91365090).

PPC64le isn't supported anymore and won't be added back in the near future.
Same for running x86_64 applications, though it might be added back as soon as the ARM64EC support in Wine is ready.
If you need those features, have a look at older releases before 0.8.x.

Emulator integrations:

- [QEMU](https://gitlab.com/qemu-project/qemu): Has the most issues and is by far the [slowest](https://github.com/AndreRH/hangover/tree/master/benchmarks) option
- [FEX](https://github.com/FEX-Emu/FEX): Upstream PE version plus some conveniences
- [Box64](https://github.com/ptitSeb/box64/): Mostly done, but depends on the early 32-bit emulation of Box64
- [Blink](https://github.com/jart/blink): started, not part of this repository yet

### 3) Preview
A paid [preview](https://www.patreon.com/posts/previews-82611984) is available with currently the following features coming soon:

- Updated Wine
- Updated FEX
- Updated Box64

### 4) Discord
A Discord Server is available for contributors and financial supporters (see point 9 below).
It provides advanced user support, development discussions and more.

### 5) Packages
__Debian__ 11 & 12 (also usable for Raspbian, Armbian, ...) and __Ubuntu__ 22.04 & 23.10 are attached to the Github Release.

__Termux__ packages can be found in the [Termux User Repository](https://github.com/termux-user-repository/tur).

__Alpine__ package can be found in the [Alpine Testing Repository](https://gitlab.alpinelinux.org/alpine/aports/-/tree/master/testing/hangover-wine).
It's only hangover-wine without box64cpu.dll for now, but you can copy over box64cpu.dll and/or libwow64fex.dll from extracted debian packages or compile them yourself.

### 6) How to build
For build instructions see [here](docs/COMPILE.md).

### 7) Running
You can add the following environment variables:

* HODLL to select the emulator dll:
    * wow64cpu.dll for "native" i386 mode on x86_64
    * wowarmhw.dll for ARM emulation (Qemu)
    * xtajit.dll for i386 emulation (Qemu)
    * libwow64fex.dll for i386 emulation (FEX, PE)
    * box64cpu.dll for i386 emulation (Box64)
* HOLIB to set full path of the library, e.g. HOLIB=/path/to/libqemu-i386.so
* QEMU_LOG to set QEMU log channels, find some options [here.](https://github.com/AndreRH/qemu/blob/v5.2.0/util/log.c#L297)

#### 7.1) Box64
box64cpu.dll currently is the default for i386 emulation, so it's simply:

```bash
$ wine your_x86_application.exe
```

If you have issues with the default, please try one of the other emulators below.

#### 7.2) QEMU
Until the critical section issue is solved it is highly recomended to limit execution to 1 core with
"taskset -c 1" for Qemu emulation:

```bash
$ HODLL=xtajit.dll   taskset -c 1 wine your_x86_application.exe
$ HODLL=wowarmhw.dll taskset -c 1 wine your_arm_application.exe
```

#### 7.4) FEX, PE
```bash
$ HODLL=libwow64fex.dll wine your_x86_application.exe
```

### 8) Known issues

* QEMU: CriticalSection doesn't work reliably and other instabilities
* FEX, PE: Doesn't support CLI applications, as it can't handle writing to the console

### 9) Financial Contributors

Become a financial contributor and help me sustain this project:

https://www.patreon.com/andre_opensource

https://liberapay.com/andre_opensource

https://ko-fi.com/andre_opensource

### 10) Hardware Contributors

Become a hardware contributor and help me sustain this project:

https://throne.com/andrerh
