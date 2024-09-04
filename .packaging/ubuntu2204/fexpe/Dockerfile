FROM foundationubuntu2204

RUN rm -rf /opt/fex; mkdir -p /opt/fex/
COPY ./ /opt/fex/
RUN ls -la /opt/fex/
ENV PATH="/opt/llvm-mingw-20240518-ucrt-ubuntu-20.04-x86_64/bin:$PATH"
RUN cd /opt/fex; mkdir build; cd build; cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain_mingw.cmake -DENABLE_JEMALLOC=0 -DENABLE_JEMALLOC_GLIBC_ALLOC=0 -DMINGW_TRIPLE=aarch64-w64-mingw32 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTS=False -DENABLE_ASSERTIONS=False ..; make -j `nproc` wow64fex
RUN ls -la /opt/fex/build/Bin
RUN aarch64-w64-mingw32-strip --strip-unneeded /opt/fex/build/Bin/libwow64fex.dll
RUN mkdir -p /opt/deb/hangover-libwow64fex/DEBIAN /opt/deb/hangover-libwow64fex/usr/lib/wine/aarch64-windows /opt/deb/hangover-libwow64fex/usr/share/doc/hangover-libwow64fex
COPY DEBIAN /opt/deb/hangover-libwow64fex/DEBIAN/
RUN cp /opt/deb/hangover-libwow64fex/DEBIAN/copyright /opt/deb/hangover-libwow64fex/usr/share/doc/hangover-libwow64fex/; \
    cp /opt/fex/build/Bin/libwow64fex.dll /opt/deb/hangover-libwow64fex/usr/lib/wine/aarch64-windows/; \
    cd /opt/deb; mv hangover-libwow64fex hangover-libwow64fex_HOVERSION_arm64; \
    dpkg-deb --build --root-owner-group  hangover-libwow64fex_HOVERSION_arm64
