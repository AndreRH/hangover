FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN echo "Types: deb" > /tmp/new.src; echo "URIs: http://archive.ubuntu.com/ubuntu/" >> /tmp/new.src; echo "Suites: noble noble-updates noble-backports" >> /tmp/new.src; echo "Components: main universe restricted multiverse" >> /tmp/new.src; echo "Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg" >> /tmp/new.src; echo "Architectures: amd64" >> /tmp/new.src; \
    echo "" >> /tmp/new.src; \
    echo "Types: deb" >> /tmp/new.src; echo "URIs: http://ports.ubuntu.com/ubuntu-ports/" >> /tmp/new.src; echo "Suites: noble noble-updates noble-backports" >> /tmp/new.src; echo "Components: main universe restricted multiverse" >> /tmp/new.src; echo "Signed-By: /usr/share/keyrings/ubuntu-archive-keyring.gpg" >> /tmp/new.src; echo "Architectures: arm64" >> /tmp/new.src; \
    cp /tmp/new.src /etc/apt/sources.list.d/ubuntu.sources && dpkg --add-architecture arm64
RUN cat /etc/apt/sources.list.d/ubuntu.sources

RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils-aarch64-linux-gnu gcc-aarch64-linux-gnu \
    ca-certificates nano python3 python3-setuptools clang screen llvm lld wget curl \
    flex bison \
    libglib2.0-dev \
    libltdl-dev \
    libxcb1-dev \
    libx11-dev  \
    librsvg2-bin \
    git gettext make automake autoconf pkg-config libtool gtk-doc-tools clang \
    dpkg-dev \
    libglib2.0-dev:arm64 \
    libfreetype-dev:arm64 \
    libltdl-dev:arm64 \
    libxcb1-dev:arm64 \
    libx11-dev:arm64 \
    build-essential libc-dev-arm64-cross less libc-devtools libidn2-0:arm64 \
    libx11-dev libxinerama-dev libfreetype-dev libfontconfig-dev \
    cmake \
    libstdc++6-arm64-cross \
    libstdc++-13-dev-arm64-cross \
    libepoxy-dev:arm64 \
    libsdl2-dev:arm64 \
    ninja-build \
    dpkg-dev fakeroot debhelper dh-make \
    libxcursor-dev:arm64 \
    libxi-dev:arm64 \
    libxshmfence-dev:arm64 \
    libxxf86vm-dev:arm64 \
    libxrandr-dev:arm64 \
    libxrender-dev:arm64 \
    libxfixes-dev:arm64 \
    libxcomposite-dev:arm64 \
    libosmesa-dev:arm64 \
    libdbus-1-dev:arm64 \
    libsane-dev:arm64 \
    libusb-1.0-0-dev:arm64 \
    libv4l-dev:arm64 \
    libpulse-dev:arm64 \
    libgstreamer1.0-dev:arm64 \
    libgstreamer-plugins-base1.0-dev:arm64 \
    libudev-dev:arm64 \
    libunwind-dev:arm64 \
    libsdl2-dev:arm64 \
    libfontconfig1-dev:arm64 \
    libkrb5-dev:arm64 \
    libvulkan-dev:arm64 \
    libgl-dev:arm64 \
    libgnutls28-dev:arm64 \
    libcups2-dev:arm64

RUN cd /opt; wget https://github.com/mstorsjo/llvm-mingw/releases/download/20240518/llvm-mingw-20240518-ucrt-ubuntu-20.04-x86_64.tar.xz; tar -xJf llvm-mingw-20240518-ucrt-ubuntu-20.04-x86_64.tar.xz; rm *.tar.xz
