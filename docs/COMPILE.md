
### How to build
First make sure you have the submodules set up:
```bash
$ git submodule update --init --recursive
```
And note while Box64 is already integrated as DLL, you can build other emulators (currently FEX and QEMU), but you don't need to, one is enough depending on your use-case.

#### Wine (includes Box64)
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

#### QEMU (optional)
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

Place resulting libraries (build/libqemu-arm.so and/or build/libqemu-i386.so) in your library path (e.g /usr/lib) or set HOLIB to the full path of the resulting library. (HOLIB takes precedence)

#### FEX, Unix (optional)
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

Place resulting library (build_unix/FEXCore/Source/libFEXCore.so) in your library path (e.g /usr/lib) or set HOLIB to the full path of the resulting library. (HOLIB takes precedence)

#### FEX, PE (optional)
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

