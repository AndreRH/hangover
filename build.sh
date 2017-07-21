#!/bin/sh

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

# Build the wrapper DLLs. FIXME: automate this better.
cd $DESTDIR/dlls/ntdll
make -j4
ln -sf $PWD/ntdll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_ntdll.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/kernel32
make -j4
ln -sf $PWD/kernel32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_kernel32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/msvcrt
make -j4
ln -sf $PWD/msvcrt.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_msvcrt.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/advapi32
make -j4
ln -sf $PWD/advapi32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_advapi32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/comdlg32
make -j4
ln -sf $PWD/comdlg32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_comdlg32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/gdi32
make -j4
ln -sf $PWD/gdi32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_gdi32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/user32
make -j4
ln -sf $PWD/user32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_user32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/shell32
make -j4
ln -sf $PWD/shell32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_shell32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/shlwapi
make -j4
ln -sf $PWD/shlwapi.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_shlwapi.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/msvcr100
make -j4
ln -sf $PWD/msvcr100.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_msvcr100.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/comctl32
make -j4
ln -sf $PWD/comctl32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_comctl32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/d3d9
make -j4
ln -sf $PWD/d3d9.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_d3d9.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/d3dx9_43
make -j4
ln -sf $PWD/d3dx9_43.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_d3dx9_43.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

cd $DESTDIR/dlls/imm32
make -j4
ln -sf $PWD/imm32.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
ln -sf $PWD/qemu_imm32.dll.so $DESTDIR/build/qemu/x86_64-windows-user/qemu_host_dll

# Build the test progs. FIXME: automate this better.
cd $DESTDIR/testprogs/advapi32
make -j4

cd $DESTDIR/testprogs/kernel32
make -j4

cd $DESTDIR/testprogs/msvcrt
make -j4
