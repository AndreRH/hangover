FROM foundationubuntu2204

ARG LLVMMINGW_NAME=llvm-mingw-20251202-ucrt-ubuntu-22.04-x86_64
ENV LLVMMINGW_PATH="/opt/$LLVMMINGW_NAME/bin"

RUN rm -rf /opt/box64; mkdir -p /opt/box64/
COPY ./ /opt/box64/
RUN ls -la /opt/box64/
ENV PATH="$LLVMMINGW_PATH:$PATH"
RUN cd /opt/box64; mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc -DARM_DYNAREC=ON -DWOW64=ON ..; make -j `nproc` wowbox64
RUN ls -la /opt/box64/build/wowbox64-prefix/src/wowbox64-build/
RUN aarch64-w64-mingw32-strip --strip-unneeded /opt/box64/build/wowbox64-prefix/src/wowbox64-build/wowbox64.dll
RUN mkdir -p /opt/deb/hangover-wowbox64/DEBIAN /opt/deb/hangover-wowbox64/usr/lib/wine/aarch64-windows /opt/deb/hangover-wowbox64/usr/share/doc/hangover-wowbox64
COPY DEBIAN /opt/deb/hangover-wowbox64/DEBIAN/
RUN cp /opt/deb/hangover-wowbox64/DEBIAN/copyright /opt/deb/hangover-wowbox64/usr/share/doc/hangover-wowbox64/; \
    cp /opt/box64/build/wowbox64-prefix/src/wowbox64-build/wowbox64.dll /opt/deb/hangover-wowbox64/usr/lib/wine/aarch64-windows/; \
    cd /opt/deb; mv hangover-wowbox64 hangover-wowbox64_HOVERSION_arm64; \
    dpkg-deb -Zxz --build --root-owner-group  hangover-wowbox64_HOVERSION_arm64
