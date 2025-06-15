
### How to build
First make sure you have the submodules set up:
```bash
$ git submodule update --init --recursive
```
And note while Box64 is already integrated as DLL, you can build other emulators (currently FEX and QEMU), but you don't need to, one is enough depending on your use-case.
Except for libarm64ecfex.dll, which is necessary for x86_64 emulation.

#### Wine (includes Box64)
To build Hangover Wine you need:

- The dependencies to [build](https://wiki.winehq.org/Building_Wine#Satisfying_Build_Dependencies) a 64 bit Wine
- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 5GB of disk space

If you don't want to run 32-Bit ARM applications, you can drop ",arm" from the configure line.

on ARM64 (from the Hangover repository):
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --disable-tests --with-mingw=clang --enable-archs=arm64ec,aarch64,i386,arm
$ make -j$(nproc)
$ sudo env PATH="$PATH" make install
```

on x86-64 (from the Hangover repository):
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --enable-win64 --disable-tests --with-mingw --enable-archs=x86_64,i386,arm
$ make -j$(nproc)
$ sudo env PATH="$PATH" make install
```

#### FEX for 64-bit
To build wow64fex from FEX you need:

- [bylaws-llvm-mingw](https://github.com/bylaws/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 1.5GB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p fex/build_ec
$ cd fex/build_ec
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=../toolchain_mingw.cmake -DENABLE_LTO=False -DMINGW_TRIPLE=arm64ec-w64-mingw32 -DBUILD_TESTS=False ..


$ make -j$(nproc) arm64ecfex
```

Place resulting library (build_ec/Bin/libarm64ecfex.dll) in your wine prefix under drive_c/windows/system32/.

#### FEX for 32-bit (optional)
To build wow64fex from FEX you need:

- [bylaws-llvm-mingw](https://github.com/bylaws/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 1.5GB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p fex/build_pe
$ cd fex/build_pe
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=../toolchain_mingw.cmake -DENABLE_LTO=False -DMINGW_TRIPLE=aarch64-w64-mingw32 -DBUILD_TESTS=False ..

$ make -j$(nproc) wow64fex
```

Place resulting library (build_pe/Bin/libwow64fex.dll) in your wine prefix under drive_c/windows/system32/.

#### Box64 (upstream) for 32-bit (optional)
To build wowbox64 from Box64 you need:

- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 400MB of disk space

Build it like (from the Hangover repository):
```bash
$ mkdir -p box64/build_pe
$ cd box64/build_pe
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc -DARM_DYNAREC=ON -DWOW64=ON ..

$ make -j$(nproc) wowbox64
```

Place resulting library (build_pe/wowbox64-prefix/src/wowbox64-build/wowbox64.dll) in your wine prefix under drive_c/windows/system32/.

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
