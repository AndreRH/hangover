[español](https://github-com.translate.goog/AndreRH/hangover/blob/master/README.md?_x_tr_sl=en&_x_tr_tl=es) | [français](https://github-com.translate.goog/AndreRH/hangover/blob/master/README.md?_x_tr_sl=en&_x_tr_tl=fr) | [português](https://github-com.translate.goog/AndreRH/hangover/blob/master/README.md?_x_tr_sl=en&_x_tr_tl=pt) | [deutsch](https://github-com.translate.goog/AndreRH/hangover/blob/master/README.md?_x_tr_sl=en&_x_tr_tl=de)

---

![stars](https://img.shields.io/github/stars/AndreRH/hangover?style=flat-square)
![forks](https://img.shields.io/github/forks/AndreRH/hangover?style=flat-square)
![Release](https://img.shields.io/github/v/release/AndreRH/hangover?style=flat-square)

Make sure to leave a :star: :)

## Hangover
This is Hangover, a project started by André Zwing and Stefan Dösinger in 2016 that can
run x86_64 and x86_32 Windows applications on aarch64 Wine.

### How it works
Hangover uses emulator DLLs to emulate only the application you want to run, rather than an entire Wine installation. It does not require 32-bit Unix libraries, and you can also run applications natively without emulation (like ARM64 7-Zip on ARM64).

As soon as the application does a Windows/Wine system call, say NtUserCreateWindowEx, it's executed outside the emulator (read non-emulated, fast, native). Even better, everything Unix related is never emulated.

In short, we break out of emulation at the win32 syscall or wine unix call level for performance reasons, which is enabled by the WoW64 support in Wine.

For 64-Bit we're using the ARM64EC ABI combined with an emulator (FEX).

### Benchmarks
For Benchmarks see [here](benchmarks/readme.md). They show that the Hangover approach works as expected, as only emulating the application instead of a complete Wine installation has benefits. It's especially visible with box64cpu vs. Wine running under Box64.

### Interesting Branches

* [RISC-V 64-bit Linux support](https://github.com/AndreRH/hangover/tree/riscv64)
* [Hangover-WOW64](https://github.com/AndreRH/hangover/tree/wow) (Hangover 0.8.1 - 9.19)
* [Hangover-Classic](https://github.com/AndreRH/hangover/tree/hangover-classic) (Hangover 0.4.0 - 0.6.5)

### Status
Current main focus is to run x86_64 and i386 Windows applications on ARM64 Linux, but it's also possible to run ARM32 Windows applications on x86_64 Linux.

PPC64le isn't supported anymore and won't be added back in the near future.
If you need that feature, have a look at older releases before 0.8.x.

Emulator integrations:

- [QEMU](https://gitlab.com/qemu-project/qemu): Has the most issues and is by far the [slowest](https://github.com/AndreRH/hangover/tree/master/benchmarks) option
- [FEX](https://github.com/FEX-Emu/FEX): Upstream PE version plus some conveniences
- [Box64](https://github.com/ptitSeb/box64/): Upstream PE version
- [Blink](https://github.com/jart/blink): started, not part of this repository yet

### Discord
A Discord Server is available for contributors and previous financial supporters (see "Financial Contributiors" below).
It provides advanced user support, development discussions and more.

### Packages
__Debian__ 11 & 12 & 13 (also usable for Raspbian, Armbian, ...) and __Ubuntu__ 20.04 & 22.04 & 24.04 & 25.04 are attached to the Github Release.
Install them with
```bash
$ sudo apt install ./hangover.*deb
```

__Termux__ packages can be found in the [Termux Repository](https://github.com/termux/termux-packages/tree/master/x11-packages/hangover-wine).

### How to build
For build instructions see [here](docs/COMPILE.md).

### Running
You can add the following environment variables:

* HODLL64 to select the 64-bit emulator dll:
    * libarm64ecfex.dll for x86_64 emulation (FEX)
    * xtajit64.dll (Wine stub dll)
* HODLL to select the 32-bit emulator dll:
    * wow64cpu.dll for "native" i386 mode on x86_64
    * wowarmhw.dll for ARM emulation (Qemu)
    * xtajit.dll for i386 emulation (Qemu)
    * libwow64fex.dll for i386 emulation (FEX)
    * wowbox64.dll for i386 emulation (Box64)
* HOLIB to set full path of the library, e.g. HOLIB=/path/to/libqemu-i386.so
* QEMU_LOG to set QEMU log channels, find some options [here.](https://github.com/AndreRH/qemu/blob/v5.2.0/util/log.c#L297)

#### FEX
libarm64ecfex.dll currently is the default for x86_64 emulation, so it's simply:

```bash
$ wine your_x86_64_application.exe
```

libwow64fex.dll is not the default for i386 emulation, so you need:

```bash
$ HODLL=libwow64fex.dll wine your_x86_application.exe
```

#### Box64
wowbox64.dll currently is the default for i386 emulation, so it's simply:

```bash
$ wine your_x86_application.exe
```

If you have issues with the default, please try one of the other emulators below.

#### QEMU
Until the critical section issue is solved it is highly recomended to limit execution to 1 core with
"taskset -c 1" for Qemu emulation:

```bash
$ HODLL=xtajit.dll   taskset -c 1 wine your_x86_application.exe
$ HODLL=wowarmhw.dll taskset -c 1 wine your_arm_application.exe
```

#### Enabling Wayland
Wayland isn't used by default or automatically, but if you want to use it instead of X11 do:

```bash
$ wine reg.exe add HKCU\\Software\\Wine\\Drivers /v Graphics /d wayland,x11
```

#### DXVK
Copy the x32 binaries to $WINEPREFIX/drive_c/windows/syswow64

Copy the arm64ec, aarch64 or x64 binaries to $WINEPREFIX/drive_c/windows/system32, depending on your use case.
For x86_64 applications first try arm64ec, it should perform best. In case it doesn't work, try x64. For aarch64 applications use aarch64.
Then open `winecfg`, switch to the Libraries tab and add `native` DLL overrides for `d3d8`, `d3d9`, `d3d10core`, `d3d11` and `dxgi`.

Note that DXVK requires a Vulkan 1.3 driver with certain features and that might not be the case for a lot of ARM64 hardware.

### Known issues

* QEMU: CriticalSection doesn't work reliably and other instabilities

### Financial Contributors

I have decided to end my activities on Patreon and other platforms.
It won't be the end of the project, my plan is to keep working on it,
delivering new releases and updates. However, I will invest less time,
except for the RISC-V port.
