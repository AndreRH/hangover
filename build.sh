#!/bin/sh

set -e

SRCDIR=`pwd`
DESTDIR=`pwd`

mkdir -p build
mkdir -p build/wine-host
mkdir -p build/wine-guest
mkdir -p build/qemu

# Build the Host (e.g. arm64) wine
cd build/wine-host
$SRCDIR/wine/configure --prefix=$DESTDIR/build/install
make -j 4
make install

# Cross-Compile Wine for the guest platform to copy higher level DLLs from. Disabled for now.
# Unfortunately this won't work for msvcrt because our msvcrt imports symbols from Linux libc.
#cd ../wine-guest
#$SRCDIR/wine/configure --host=x86_64-w64-mingw32 --with-wine-tools=../wine-host --without-freetype --enable-msvcrt
#make -j 4

# Bleh. WINEBUILD=XXX means that you can't simply run "make" inside qemu's output dir.
# You need to set WINEBUILD in the same way first.

# Build qemu
cd ../qemu
LIBS=-lpthread_nonshared WINEBUILD=$DESTDIR/build/install/bin/winebuild CC="$DESTDIR/build/install/bin/winegcc -lpthread -lpthread_nonshared -DWINE_NOWINSOCK" CXX="$DESTDIR/build/install/bin/wineg++ -lpthread -lpthread_nonshared -DWINE_NOWINSOCK" $SRCDIR/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --without-pixman --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user
WINEBUILD=$DESTDIR/build/install/bin/winebuild make
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
mkdir -p $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

# Build the wrapper DLLs. FIXME: automate this better.
cd ../../dlls/ntdll
PATH=$PATH:$DESTDIR/build/install/bin make
ln -sf $PWD/ntdll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_ntdll.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd ../../dlls/kernel32
PATH=$PATH:$DESTDIR/build/install/bin make
ln -sf $PWD/kernel32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_kernel32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

#cd $DESTDIR/build
#ln -s wine-host/dlls/msvcrt/msvcrt.dll qemu/x86_64-windows-user/qemu_guest_dll
