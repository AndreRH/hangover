![stars](https://img.shields.io/github/stars/AndreRH/hangover?style=flat-square)
![forks](https://img.shields.io/github/forks/AndreRH/hangover?style=flat-square)

Make sure to leave a :star: :)

## Hangover (riscv64)
This is the RISC-V 64-bit branch of Hangover.
For more information see the master branch.

### 1) How it works
Wine is compiled for riscv64 and uses i386 PE files for wow64. For more information see the master branch.

### 2) Status
The riscv64 port is in a very early state, expect issues.

Emulator integrations:

Currently only Box64 and QEMU can run on riscv64.

### 3) Preview
The riscv64 port won't be part of any Preview for now.

### 4) Discord
A Discord Server is available for contributors and financial supporters (see point 9 below).
It provides advanced user support, development discussions and more.

### 5) Packages
Coming soon for riscv64.

### 6) How to build
For build instructions see [here](docs/COMPILE.md).

### 7) Running
You can add the following environment variables:

* HODLL to select the emulator dll:
    * xtajit.dll for i386 emulation (Qemu)
    * box64cpu.dll for i386 emulation (Box64)
    * (wowarmhw.dll for ARM emulation (Qemu), not working yet)
* HOLIB to set full path of the library, e.g. HOLIB=/path/to/libqemu-i386.so
* QEMU_LOG to set QEMU log channels, find some options [here.](https://github.com/AndreRH/qemu/blob/v5.2.0/util/log.c#L297)

#### 7.1) Box64
box64cpu.dll currently is the default for i386 emulation, so it's simply:

```bash
$ wine your_x86_application.exe
```

If you have issues with the default, please try the other emulator below.

#### 7.2) QEMU
Until the critical section issue is solved it is highly recomended to limit execution to 1 core with
"taskset -c 1" for Qemu emulation:

```bash
$ HODLL=xtajit.dll   taskset -c 1 wine your_x86_application.exe
$ HODLL=wowarmhw.dll taskset -c 1 wine your_arm_application.exe
```

### 8) Known issues

* Multithreaded programs in general
* High CPU load on some internal applications
* RPC is buggy
* QEMU: CriticalSection doesn't work reliably and other instabilities

### 9) Financial Contributors

Become a financial contributor and help me sustain this project:

https://www.patreon.com/andre_opensource

https://liberapay.com/andre_opensource

https://ko-fi.com/andre_opensource

### 10) Hardware Contributors

Become a hardware contributor and help me sustain this project:

https://throne.com/andrerh
