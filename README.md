## Hangover
This is Hangover, a project started by André Zwing and Stefan Dösinger in 2016 to run
x86_64/x86_32 Windows applications on aarch64/(ppc64le)/x86_64 Wine.

### 1) How it works
In fact it uses the WoW64 support in Wine + an emulator to run e.g. ARM32 on x86_64 or i386 on ARM64.
This is completely different from earlier versions of Hangover.

### 2) Status
Putty runs smoothly, but there seems to be an issue with multithreaded applications, e.g. most.

### 3) How to build
Currently Qemu is built as a library which is used in Wine. This is a huge license conflict,
so there'll be no binaries for download. This will change with other emulators. Instructions on how
to build this will follow. It's by far not as hard as it used to be with classical Hangover.

### 4) Todo

* Get more applications running
* Get all requirements into one place
* Add some kind of a build system or at least build instructions
* Integrate other emulators than Qemu, like Box32, FEX/hex-emu

### 5) Donations

For anyone interested, ways to support André can be found here:

https://www.patreon.com/andre_opensource

https://liberapay.com/andre_opensource

https://flattr.com/@andre_opensource
