#!/bin/bash

set -e

SRCDIR=`pwd`
DESTDIR=`pwd`

mkdir -p $DESTDIR/build
mkdir -p $DESTDIR/build/wine-host
mkdir -p $DESTDIR/build/wine-guest
mkdir -p $DESTDIR/build/wine-guest32
mkdir -p $DESTDIR/build/qemu

# Build the Host (e.g. arm64) wine
cd $DESTDIR/build/wine-host
$SRCDIR/wine/configure --prefix=$DESTDIR/build/install --enable-win64
make -j 4

# Cross-Compile Wine for the guest platform to copy higher level DLLs from.
cd ../wine-guest
$SRCDIR/wine/configure --host=x86_64-w64-mingw32 --with-wine-tools=../wine-host --without-freetype
make -j 4
cd ../wine-guest32
$SRCDIR/wine/configure --host=i686-w64-mingw32 --with-wine-tools=../wine-host --without-freetype
make -j 4

# Build qemu
cd $DESTDIR/build/qemu
CC="$DESTDIR/build/wine-host/tools/winegcc/winegcc -B$DESTDIR/build/wine-host/tools/winebuild -I$DESTDIR/build/wine-host/include -I$DESTDIR/wine/include -lpthread -DWINE_NOWINSOCK" CXX="$DESTDIR/build/wine-host/tools/winegcc/wineg++ -B$DESTDIR/build/wine-host/tools/winebuild -I$DESTDIR/build/wine-host/include -I$DESTDIR/wine/include -lpthread -DWINE_NOWINSOCK" $SRCDIR/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user --disable-fdt --disable-capstone
make -j 4
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll64
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll64
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll32
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll32

# Build the wrapper DLLs.
# TODO: Figure out dependencies between them better.
declare -a dlls=("ntdll" "kernel32" "msvcrt" "advapi32" "comctl32" "comdlg32" "d3d9" "d3dx10_43" "d3dx9_43" "gdi32" "imm32"
        "msvcr80" "msvcr100" "opengl32" "shell32" "shlwapi" "user32" "version" "xinput1_3" "winmm" "wsock32" "ws2_32"
        "iphlpapi" "secur32" "wininet" "advpack" "usp10" "riched20" "dsound")

mkdir -p $DESTDIR/build/dlls32
mkdir -p $DESTDIR/build/dlls64

for dll in "${dlls[@]}"
do
    mkdir -p $DESTDIR/build/dlls64/$dll
    cd $DESTDIR/build/dlls64/$dll
    echo "GUEST_CC=x86_64-w64-mingw32" > Makefile
    echo "SRCDIR=../../../dlls/$dll" >> Makefile
    echo "DESTDIR?=../../.." >> Makefile
    echo "GUEST_BIT=64" >> Makefile
    echo "HOST_BIT=64" >> Makefile
    echo "WINE_DIR=wine-guest" >> Makefile
    echo >> Makefile
    echo "include $SRCDIR/dlls/$dll/Makefile" >> Makefile

    make -j4
    ln -sf $PWD/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll64
    ln -sf $PWD/qemu_$dll.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll64

    mkdir -p $DESTDIR/build/dlls32/$dll
    cd $DESTDIR/build/dlls32/$dll
    echo "GUEST_CC=i686-w64-mingw32" > Makefile
    echo "SRCDIR=../../../dlls/$dll" >> Makefile
    echo "DESTDIR?=../../.." >> Makefile
    echo "GUEST_BIT=32" >> Makefile
    echo "HOST_BIT=64" >> Makefile
    echo "WINE_DIR=wine-guest32" >> Makefile
    echo >> Makefile
    echo "include $SRCDIR/dlls/$dll/Makefile" >> Makefile

    make -j4 || true
    ln -sf $PWD/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll32
    ln -sf $PWD/qemu_$dll.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll32
done

# Link Wine libraries.
declare -a wine_dlls=("dbghelp" "ole32" "oleaut32" "propsys" "rpcrt4" "urlmon" "windowscodecs" "netapi32" "dnsapi" "msimg32"
        "crypt32" "dwmapi" "uxtheme" "setupapi" "wintrust" "wtsapi32" "pdh" "avrt" "cryptnet" "imagehlp" "cryptui" "sensapi"
        "msvcp80" "msvcp100")
ln -sf $DESTDIR/build/wine-guest/libs/wine/libwine.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll64
ln -sf $DESTDIR/build/wine-guest32/libs/wine/libwine.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll32

for dll in "${wine_dlls[@]}"
do
    ln -sf $DESTDIR/build/wine-guest/dlls/$dll/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll64
    ln -sf $DESTDIR/build/wine-guest32/dlls/$dll/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll32
done
ln -sf $DESTDIR/build/wine-guest/dlls/winspool.drv/winspool.drv $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll64
ln -sf $DESTDIR/build/wine-guest32/dlls/winspool.drv/winspool.drv $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll32

# Build the test progs. FIXME: automate this better.
cd $DESTDIR/testprogs/advapi32
make -j4

cd $DESTDIR/testprogs/kernel32
make -j4

cd $DESTDIR/testprogs/msvcrt
make -j4
