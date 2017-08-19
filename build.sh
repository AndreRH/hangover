#!/bin/bash

set -e

SRCDIR=`pwd`
DESTDIR=`pwd`

mkdir -p $DESTDIR/build
mkdir -p $DESTDIR/build/wine-host
mkdir -p $DESTDIR/build/wine-guest
mkdir -p $DESTDIR/build/qemu

# Build the Host (e.g. arm64) wine
cd $DESTDIR/build/wine-host
$SRCDIR/wine/configure --prefix=$DESTDIR/build/install
make -j 4

# Cross-Compile Wine for the guest platform to copy higher level DLLs from. Disabled for now.
# Unfortunately this won't work for msvcrt because our msvcrt imports symbols from Linux libc.
cd ../wine-guest
$SRCDIR/wine/configure --host=x86_64-w64-mingw32 --with-wine-tools=../wine-host --without-freetype
make -j 4

# Build qemu
cd $DESTDIR/build/qemu
LIBS=-lpthread_nonshared CC="$DESTDIR/build/wine-host/tools/winegcc/winegcc -B$DESTDIR/build/wine-host/tools/winebuild -I$DESTDIR/build/wine-host/include -I$DESTDIR/wine/include -lpthread -lpthread_nonshared -DWINE_NOWINSOCK" CXX="$DESTDIR/build/wine-host/tools/winegcc/wineg++ -B$DESTDIR/build/wine-host/tools/winebuild -I$DESTDIR/build/wine-host/include -I$DESTDIR/wine/include -lpthread -lpthread_nonshared -DWINE_NOWINSOCK" $SRCDIR/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --without-pixman --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user
make -j 4
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

# Build the wrapper DLLs.
# TODO: Figure out dependencies between them better.
declare -a dlls=("ntdll" "kernel32" "msvcrt" "advapi32" "comctl32" "comdlg32" "d3d9" "d3dx10_43" "d3dx9_43" "gdi32" "imm32"
        "msvcr100" "ole32" "oleaut32" "opengl32" "shell32" "shlwapi" "user32" "version" "xinput1_3" "winmm" "wsock32" "ws2_32"
        "iphlpapi" "secur32" "wininet")

for dll in "${dlls[@]}"
do
    cd $DESTDIR/dlls/$dll
    make -j4
    ln -sf $PWD/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
    ln -sf $PWD/qemu_$dll.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll
done

# Link Wine libraries.
declare -a wine_dlls=("dbghelp" "rpcrt4")
ln -sf $DESTDIR/build/wine-guest/libs/wine/libwine.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll

for dll in "${wine_dlls[@]}"
do
    ln -sf $DESTDIR/build/wine-guest/dlls/$dll/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
done

# Build the test progs. FIXME: automate this better.
cd $DESTDIR/testprogs/advapi32
make -j4

cd $DESTDIR/testprogs/kernel32
make -j4

cd $DESTDIR/testprogs/msvcrt
make -j4
