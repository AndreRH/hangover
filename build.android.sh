#!/bin/bash

set -e

SRCDIR=`pwd`
DESTDIR=`pwd`

# environment needs to be setup before the script can run, e.g.:
#export PATH=/home/$USER/src/ndk/aarch64-linux-android/bin/:$PATH
#export ANDROID_HOME=/home/$USER/src/ANDROID/android-sdk-linux
#export NDK_SYSROOT=/home/$USER/src/ndk/aarch64-linux-android/sysroot

mkdir -p $DESTDIR/build.android
mkdir -p $DESTDIR/build.android/wine-host
mkdir -p $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a
mkdir -p $DESTDIR/build.android/qemu
mkdir -p $DESTDIR/build.android/glib
mkdir -p $DESTDIR/build.android/libs

# Build libs
cd $DESTDIR/build.android/
wget -c ftp://ftp-osl.osuosl.org/pub/libpng/src/libpng15/libpng-1.5.28.tar.gz
tar -xzf libpng-1.5.28.tar.gz
wget -c https://download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz
tar -xzf freetype-2.8.tar.gz
cd $DESTDIR/build.android/libpng-1.5.28
./configure --host=aarch64-linux-android --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a CXX=aarch64-linux-android-clang++ CC=aarch64-linux-android-clang
make -j4 ; make install
cd $DESTDIR/build.android/freetype-2.8
./configure --host=aarch64-linux-android --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a LIBPNG_CFLAGS="-I$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/include/libpng15" LIBPNG_LIBS="-L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib -lpng15" CXX=aarch64-linux-android-clang++ CC=aarch64-linux-android-clang
make -j4 ; make install
cd $DESTDIR/glib
./autogen.sh --help
cd $DESTDIR/build.android/glib
../../glib/configure --with-pcre=internal --host=aarch64-linux-android CXX=aarch64-linux-android-clang++ CC=aarch64-linux-android-clang --disable-libmount --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a
make -j 4 ; make install

# Build the Host (e.g. arm64) wine
cd $DESTDIR/build.android/wine-host
$SRCDIR/wine/configure --host=aarch64-linux-android --with-wine-tools=../../build/wine-host --prefix=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/ --libdir=$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib CXX=aarch64-linux-android-clang++ CC=aarch64-linux-android-clang LIBPNG_CFLAGS="-I$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/include/libpng15" LIBPNG_LIBS="-L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib -lpng15" FREETYPE_CFLAGS="-I$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/include/freetype2" FREETYPE_LIBS="-L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib -lm -lz -lpng15 -lfreetype"
make -j 4 ; make install
ln -sf ../../build/wine-host/tools tools

# Build qemu
cd $DESTDIR/build.android/qemu
CC="$DESTDIR/build.android/wine-host/tools/winegcc/winegcc -D__ANDROID_API__=22 -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib --sysroot=$DESTDIR/build.android/wine-host -b aarch64-linux-android -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include -DWINE_NOWINSOCK" CXX="$DESTDIR/build.android/wine-host/tools/winegcc/wineg++ -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib --sysroot=$DESTDIR/build.android/wine-host -b aarch64-linux-android -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include  -DWINE_NOWINSOCK" $SRCDIR/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --without-pixman --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user
make -j 4
mkdir -p $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_guest_dll64
mkdir -p $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_host_dll64
mkdir -p $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_guest_dll32
mkdir -p $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_host_dll32

# Build the wrapper DLLs.
# TODO: Figure out dependencies between them better.
declare -a dlls=("ntdll" "kernel32" "msvcrt" "advapi32" "comctl32" "comdlg32" "d3d9" "d3dx10_43" "d3dx9_43" "gdi32" "imm32"
        "msvcr100" "shell32" "shlwapi" "user32" "version" "xinput1_3" "winmm" "wsock32" "ws2_32" "iphlpapi"
        "secur32" "wininet" "advpack" "usp10")

for dll in "${dlls[@]}"
do
    mkdir -p $DESTDIR/build/dlls64/$dll
    cd $DESTDIR/build/dlls64/$dll
    echo "GUEST_CC=x86_64-w64-mingw32" > Makefile
    echo "SRCDIR=../../../dlls/$dll" >> Makefile
    echo "DESTDIR?=../../.." >> Makefile
    echo "GUEST_BIT=64" >> Makefile
    echo "HOST_BIT=64" >> Makefile
    echo >> Makefile
    echo "include $SRCDIR/dlls/$dll/Makefile" >> Makefile

    make -j4 WINEGCC="$DESTDIR/build.android/wine-host/tools/winegcc/winegcc -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib --sysroot=$DESTDIR/build.android/wine-host -b aarch64-linux-android -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include"
    ln -sf $PWD/$dll.dll $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_guest_dll64
    ln -sf $PWD/qemu_$dll.dll.so $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_host_dll64

    mkdir -p $DESTDIR/build/dlls32/$dll
    cd $DESTDIR/build/dlls32/$dll
    echo "GUEST_CC=i686-w64-mingw32" > Makefile
    echo "SRCDIR=../../../dlls/$dll" >> Makefile
    echo "DESTDIR?=../../.." >> Makefile
    echo "GUEST_BIT=32" >> Makefile
    echo "HOST_BIT=64" >> Makefile
    echo "CFLAGS=-Wno-pointer-to-int-cast -Wno-int-to-pointer-cast" >> Makefile
    echo >> Makefile
    echo "include $SRCDIR/dlls/$dll/Makefile" >> Makefile

#     make -j4 WINEGCC="$DESTDIR/build.android/wine-host/tools/winegcc/winegcc -I$NDK_SYSROOT/usr/include -L$DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib --sysroot=$DESTDIR/build.android/wine-host -b aarch64-linux-android -B$DESTDIR/build.android/wine-host/tools/winebuild -I$DESTDIR/build.android/wine-host/include -I$DESTDIR/wine/include"
#     ln -sf $PWD/$dll.dll $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_guest_dll32
#     ln -sf $PWD/qemu_$dll.dll.so $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_host_dll32
done

# Link Wine libraries.
declare -a wine_dlls=("dbghelp" "ole32" "oleaut32" "propsys" "rpcrt4" "urlmon" "windowscodecs" "netapi32" "dnsapi"
        "crypt32" "dwmapi" "uxtheme" "setupapi" "wintrust" "wtsapi32" "pdh" "avrt" "cryptnet" "imagehlp" "cryptui"
        "sensapi" "riched20")
ln -sf $DESTDIR/build/wine-guest/libs/wine/libwine.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll

for dll in "${wine_dlls[@]}"
do
    ln -sf $DESTDIR/build/wine-guest/dlls/$dll/$dll.dll $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll
done
ln -sf $DESTDIR/build/wine-guest/dlls/winspool.drv/winspool.drv $DESTDIR/build/qemu/x86_64-windows-user/qemu_guest_dll

set +e

# Resetup the apk with qemu
cp -lf $DESTDIR/build.android/qemu/x86_64-windows-user/qemu-x86_64.exe.so $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/bin/
cp -rf $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_host_dll $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/bin/
cp -rf $DESTDIR/build.android/qemu/x86_64-windows-user/qemu_guest_dll $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/bin/
mkdir -p $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/lib/arm64-v8a
cp -f  $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/lib/* $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/lib/arm64-v8a/
rm -rf $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/arm64-v8a/include
rm -rf $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/assets/include
rm -rf $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/wine-debug.apk
make -C $DESTDIR/build.android/wine-host/dlls/wineandroid.drv/
