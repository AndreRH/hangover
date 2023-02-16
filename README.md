## Hangover
This is Hangover, a project started by André Zwing and Stefan Dösinger in 2016 to run
x86_64/x86_32 Windows applications on aarch64/(ppc64le)/x86_64 Wine.

### 1) How it works
In fact it uses the WoW64 support in Wine + an emulator to run e.g. ARM32 on x86_64 or i386 on ARM64.
This is completely different from earlier versions of Hangover.

### 2) Status
Putty runs smoothly, most applications run worse on ARM64 than on x86-64 with Hangover.

### 3) How to build
Currently Qemu is built as a library which is used in Wine. This is a license conflict, so there'll be no binaries for download. This will change with other emulators.

#### 3.1) Qemu
To build Qemu as a library you need:

- The dependencies to build qemu (in particular glib)
- About 1GB of disk space

Download and extract version 5.2.0 from [here.](https://download.qemu.org/)

Apply the patch provided in this repo under qemu/ with:
```bash
$ patch -p1 < /path/to/your/patch
```

Build it like:
```bash
$ mkdir build
$ cd build
$ ../configure --target-list=arm-linux-user,i386-linux-user
$ make
```

In case the compiler complains about something in linux-user/ioctls.h remove the corresponding line and run make again.

Place resulting libraries in /opt (currently hardcoded in xtajit.dll)

#### 3.2) Wine
To build Hangover Wine you need:

- The dependencies to build a 64 bit Wine
- clang/llvm-dlltool/lld or llvm-mingw for PE cross-compilation
- About 3GB of disk space

Also make sure you have the submodule set up:
```bash
$ git submodule update --init
```

on x86-64:
```bash
$ mkdir -p wine/build
$ cd wine/build
$ ../configure --enable-win64 --disable-tests --with-mingw --enable-archs=i386,x86_64
$ make
$ ./wine64 notepad++.exe
```

on ARM64:
```bash
$ mkdir -p wine/build
$ cd wine/build
$ ../configure --disable-tests --with-mingw --enable-archs=i386,aarch64
$ make
$ ./wine notepad++.exe
```

### 4) Environment variables

* HODLL to run applications with other dlls than xtajit. e.g. HODLL=wow64cpu.dll to run it without emulation on x86-64
* QEMU_LOG to set Qemu log channels, find some options [here.](https://github.com/AndreRH/qemu/blob/hangover/util/log.c#L297)

### 5) Todo

* Get more applications running
* Investigate CriticalSection issues (just timing?)
* Integrate other emulators than Qemu, like Box32, FEX/hex-emu

### 6) Donations

For anyone interested, ways to support André can be found here:

https://www.patreon.com/andre_opensource

https://liberapay.com/andre_opensource

https://flattr.com/@andre_opensource
