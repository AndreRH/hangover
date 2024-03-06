
### How to build
First make sure you have the submodules set up:
```bash
$ git submodule update --init --recursive
```
And note while Box64 is already integrated as DLL, you can build other emulators (currently only QEMU), but you don't need to, one is enough depending on your use-case.

#### Wine (includes Box64)
To build Hangover Wine you need:

- The dependencies to [build](https://wiki.winehq.org/Building_Wine#Satisfying_Build_Dependencies) a 64 bit Wine
- About 4GB of disk space

from the Hangover repository:
```bash
$ mkdir -p wine/build
$ cd wine/build
$ export PATH=/path/to/llvm-mingw/bin:$PATH
$ ../configure --disable-tests --disable-winedbg
$ make -j$(nproc)
$ sudo env PATH="$PATH" make install
```

Now copy the i386-windows directory to /usr/local/lib/wine/. You can extract it from one of the Hangover 9.0 release packages.

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
