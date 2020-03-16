## Hangover
This is Hangover, a project started by Stefan Dösinger and André Hentschel to run
x86_64 Windows applications on aarch64 Windows or Wine.

### 1) Status
Hangover currently runs a small number of 32 bit and 64 bit Windows applications. A list of applications the authors have tested is listed below. Other applications may work, but don't expect too much. Direct3D is working if you have a host OpenGL implementation that supports regular desktop GL. Wine's d3d implementation currently does not support OpenGL:ES well enough to be usable. Once this changes, Hangover will support it without any changes.

Debugger support is nonexistent and exception handling has known bugs. Due to these reasons copy protection and anti-cheat systems are likely to be in worse shape than in reguar Wine.

You can generally expect 64 bit applications to be in better shape than 32 bit applications because no data structure thunking is necessary.

### 2) Host system requirements
Hangover is tested on aarch64 Linux, x86_64 Linux and x86_64 MacOS. No Intel x86 libraries are needed on the host system. No 32 bit multilib is required.

To build this project you need:
- Docker (Android build only)

or
- The dependencies to build a 64 bit Wine (./configure --enable-win64)
- The dependencies to build qemu (in particular glib)
- x86_64-w64-mingw32-gcc (exactly this name)
- i686-w64-mingw32-gcc (exactly this name)
- About 5gb of disk space

### 3) How to build

First make sure you have the submodules set up:

```bash
$ git submodule init
$ git submodule update
```

#### 3.a) Android build:
For Docker (Android build only) you can simply run:

```bash
$ docker build -f Dockerfile.android -t hob ./
```

Alternatively, to build without Docker, run:

```bash
$ make -f Makefile.android
```

The Android Makefile script is poorly tested though.

To then extract the .apk file, run:

```bash
$ docker run --rm hob tar -C /root/hangover/build/wine-host/dlls/wineandroid.drv/ -cf - hangover-debug.apk | tar -xvf -
```

#### 3.b) Linux / MacOS build:
In theory everything should be built by running `make`. In practise you'll probably run into some bugs in our build system. Parallel builds should work, but if they fail try a non-parallel one first.

Some 32 bit programs and DLLs built with mingw depend on `libgcc_s_sjlj-1.dll`. You can symlink the DLL from your mingw installation to `build/qemu/x86_64-windows-user/qemu_guest_dll32`.

### 4) How to run

```bash
/path/to/hangover/build/wine-host/loader/wine64 /path/to/hangover/build/qemu/x86_64-windows-user/qemu-x86_64.exe.so foo.exe
```

Wine's programs can be found in `build/wine-guest/programs/*` and `build/wine-guest32/programs/*`. `build/wine-[guest|guest32]/` also contain PE builds of Wine's tests.

### 5) Performance
Don't expect this to be fast. The main bottleneck at the moment is the speed of the code qemu generates from the input x86 code. To provide a rough comparison, my Nvidia Shield Android TV device (running a regular desktop Linux, not Android) runs games from the late 1990s to early 2000s at playable speed. The DirectX 9 SDK samples run fairly well because they contain little logic of their own and just call out of the VM into d3d, so all the heavy lifting is done natively. Warhammer 40k: Dawn of War starts a fresh game at around 30 fps but slows to a crawl as soon as a few units are built.

### 6) 32 bit guest support
The host Wine is always built as a 64 bit application. Hangover handles 32 bit applications by translating structures passed between the application and Wine. The code doing this is hand written because the thunks have to understand in which situation a pointer is valid and in which situation it could point to a random address and should be ignored, and how to handle writes to resulting structures in case of errors etc. The LLP64 model of Windows keeps most structures compatible between 32 and 64 bit, but translating is still a big effort.

The address space is limited to 4 GB by reserving every address below 4 GB, then calling mmap to reserve remaining space until we run out of free address space and then freeing up the bottom 4 GB again. Most host Wine libraries are loaded earlier above 4 GB to keep the previous space below 4 GB as free as possible. The drawback of this is that starting a new process takes about 2 seconds.

Wine sees every process as a 64 bit process, so its WoW64 layer is not active. This will work OK for pure 32 bit or pure 64 bit applications, but it will cause problems for mixed applications that expect a distinction between e.g. C:\windows\system32 and C:\windows\syswow64.

### 7) 16 bit guest support
Support for Win16 does not yet exist, but should be possible by using Wine's regular Win16->Win32 thunks and taking it from there. Some changes to the way Wine sets up 16 bit protected mode segments will be needed.

For vm86 (DOS) support install `dosbox` on your host. Wine will call it for you.

### 8) 32 bit host support
Support for 32 bit host systems is not implemented. It should not be hard to do, but you will probably have to put some effort into making sure the address space layout works OK and the load address of the main .exe file remains free until qemu loads it.

### 9) Porting to other host architectures
Porting to little endian host architectures should be fairly simple. You will have to replace a few bits of host specific assembler code, the most complicated one is the vararg forward code in `dlls/include/va_helper_impl.h`. The compiler will make you aware of other places through #error statements in ifdef guards.

If you want this to work on big endian platforms forget about it. It would require converting *every* Win32 structure, not just those with pointers or pointer sized integers in it. It will not happen.

### 10) Tested applications

This is a list of applications the authors tested. There is hope that they will work for you as well. If an application is marked as "installer: no" that means that the installer doesn't work for some reason. You'll have to install it elsewhere and copy the directory and registry keys.

- **Notepad++:** Works, Installer untested
- **ANNO 1602:** Runs with good performance, installer does not work. Videos may cause crashes
- **Age of Wonders:** Installer works, but 1.36 update does not install. Game version 1.36 works
- **Warhammer 40k: Dawn of War:** Game works, installer intested. Too slow to be playable
- **The Settlers II 10th Anniversary:** Installer works, updater works, game runs but is too slow to be playable. Needs native d3dx9 and d3dcompiler libs.
- **Prince of Persia 3D:** Installer and update work, game is playable.
- **Worms 2:** Installer fails because it needs Win16, game is playable. Game needs Audio CD support, otherwise it will complain that it doesn't find the CD.
- **Worms Armageddon:** Works with the right Wine settings. Despite having the same graphics as Worms 2 it is noticeably slower but borderline playable.

#### Known not to work:
- **StarCraft:** Breaks because 2GB address space limit is not respected.
- **Age of Empires 2:** Extended exception information missing.

### 11) Running "make test" in Wine
To run Wine's tests inside Hangover you can use scripts/hangover-test.sh as $WINETEST_WRAPPER. You also have to create an empty file server/wineserver (just touch it, it doesn't need anything special) to make Wine's tools/runtest happy. See comments in scripts/hangover-test.sh for more details
