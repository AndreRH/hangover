FROM foundationubuntu2204

RUN rm -rf /opt/fex; mkdir -p /opt/fex/
COPY ./ /opt/fex/
RUN ls -la /opt/fex/
ENV PATH="/opt/bylaws-llvm-mingw-20240929-ucrt-ubuntu-20.04-x86_64/bin:$PATH"
RUN cd /opt/fex; mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_JEMALLOC_GLIBC_ALLOC=False -DENABLE_ASSERTIONS=False -DCMAKE_TOOLCHAIN_FILE=../toolchain_mingw.cmake -DENABLE_LTO=False -DMINGW_TRIPLE=arm64ec-w64-mingw32 -DBUILD_TESTS=False ..; make -j `nproc` arm64ecfex
RUN ls -la /opt/fex/build/Bin
RUN arm64ec-w64-mingw32-strip --strip-unneeded /opt/fex/build/Bin/libarm64ecfex.dll
RUN mkdir -p /opt/deb/hangover-libarm64ecfex/DEBIAN /opt/deb/hangover-libarm64ecfex/usr/lib/wine/aarch64-windows /opt/deb/hangover-libarm64ecfex/usr/share/doc/hangover-libarm64ecfex
COPY DEBIAN /opt/deb/hangover-libarm64ecfex/DEBIAN/
RUN cp /opt/deb/hangover-libarm64ecfex/DEBIAN/copyright /opt/deb/hangover-libarm64ecfex/usr/share/doc/hangover-libarm64ecfex/; \
    cp /opt/fex/build/Bin/libarm64ecfex.dll /opt/deb/hangover-libarm64ecfex/usr/lib/wine/aarch64-windows/; \
    cd /opt/deb; mv hangover-libarm64ecfex hangover-libarm64ecfex_HOVERSION_arm64; \
    dpkg-deb -Zxz --build --root-owner-group  hangover-libarm64ecfex_HOVERSION_arm64
