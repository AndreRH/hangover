
### How to build
First make sure you have the submodules set up:
```bash
$ git submodule update --init --recursive
```
You can build various emulators (currently Box64 and FEX), but you don't need to, one is enough depending on your use-case.
Except for libarm64ecfex.dll, which is necessary for x86_64 emulation.

#### Wine
To build Hangover Wine you need:

- The dependencies to [build](https://wiki.winehq.org/Building_Wine#Satisfying_Build_Dependencies) a 64 bit Wine
- [llvm-mingw](https://github.com/mstorsjo/llvm-mingw) for PE cross-compilation (downlaod & unpack a release, but don't use the .zip files, they are for Windows)
- About 5GB of disk space

in the Hangover repository do:
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --disable-tests --with-mingw=clang --enable-archs=arm64ec,aarch64,i386
$ make -j$(nproc)
$ sudo env PATH="$PATH" make install
```

For cross-compilation see [here](https://github.com/AndreRH/hangover/blob/master/.packaging/ubuntu2404/wine/Dockerfile).

#### FEX for 64-bit
To build arm64ecfex from FEX you need:

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

Place resulting library (build_ec/Bin/libarm64ecfex.dll) in your wine prefix under drive_c/windows/system32/

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

Place resulting library (build_pe/Bin/libwow64fex.dll) in your wine prefix under drive_c/windows/system32/

#### Box64 for 32-bit
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

Place resulting library (build_pe/wowbox64-prefix/src/wowbox64-build/wowbox64.dll) in your wine prefix under drive_c/windows/system32/
