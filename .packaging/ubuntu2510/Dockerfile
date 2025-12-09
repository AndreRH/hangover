FROM ubuntu:25.10

ARG LLVMMINGW_DATE=20251202
ARG LLVMMINGW_NAME=llvm-mingw-$LLVMMINGW_DATE-ucrt-ubuntu-22.04-aarch64

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils gcc \
    ca-certificates nano python3 python3-setuptools clang screen llvm lld wget curl \
    flex bison nasm \
    libglib2.0-dev \
    libltdl-dev \
    libxcb1-dev \
    libx11-dev  \
    librsvg2-bin \
    git gettext make automake autoconf pkg-config libtool gtk-doc-tools clang \
    dpkg-dev \
    libglib2.0-dev \
    libfreetype-dev \
    libltdl-dev \
    libxcb1-dev \
    libx11-dev \
    build-essential less libc-devtools libidn2-0 \
    libx11-dev libxinerama-dev libfreetype-dev libfontconfig-dev \
    cmake \
    libepoxy-dev \
    libsdl2-dev \
    ninja-build \
    dpkg-dev fakeroot debhelper dh-make \
    libxcursor-dev \
    libxi-dev \
    libxshmfence-dev \
    libxxf86vm-dev \
    libxrandr-dev \
    libxrender-dev \
    libxfixes-dev \
    libxcomposite-dev \
    libdbus-1-dev \
    libsane-dev \
    libusb-1.0-0-dev \
    libv4l-dev \
    libpulse-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libudev-dev \
    libunwind-dev \
    libsdl2-dev \
    libfontconfig1-dev \
    libkrb5-dev \
    libvulkan-dev \
    libgl-dev \
    libgnutls28-dev \
    libcups2-dev \
    libxkbcommon-dev \
    libxkbregistry-dev \
    libwayland-dev

RUN cd /opt; wget https://github.com/mstorsjo/llvm-mingw/releases/download/$LLVMMINGW_DATE/$LLVMMINGW_NAME.tar.xz; tar -xJf $LLVMMINGW_NAME.tar.xz; rm *.tar.xz
