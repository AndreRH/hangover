FROM foundationubuntu2204

RUN rm -rf /opt/wine; mkdir -p /opt/wine/
COPY ./ /opt/wine/
RUN ls -la /opt/wine/
RUN cp -ra /opt/wine /opt/wine64
ENV PATH="/opt/llvm-mingw-20241001-ucrt-ubuntu-20.04-x86_64/bin:$PATH"
RUN cd /opt/wine64; mkdir amd64; cd amd64; ../configure --enable-win64; make __tooldeps__ -j `nproc`; make -C nls
RUN cd /opt/wine; mkdir boxpe; cd boxpe; ../configure --with-mingw --enable-archs=i386,aarch64 --disable-tests --host=aarch64-linux-gnu host_alias=aarch64-linux-gnu build_alias=x86_64-linux-gnu --with-wine-tools=/opt/wine64/amd64 CC=aarch64-linux-gnu-gcc; make -C dlls/box64cpu -j `nproc`
RUN ls -la /opt/wine/boxpe/dlls/box64cpu/aarch64-windows/
RUN mkdir -p /opt/deb/hangover-box64cpu/DEBIAN /opt/deb/hangover-box64cpu/usr/lib/wine/aarch64-windows /opt/deb/hangover-box64cpu/usr/share/doc/hangover-box64cpu
COPY DEBIAN /opt/deb/hangover-box64cpu/DEBIAN/
RUN cp /opt/deb/hangover-box64cpu/DEBIAN/copyright /opt/deb/hangover-box64cpu/usr/share/doc/hangover-box64cpu/; \
    cp /opt/wine/boxpe/dlls/box64cpu/aarch64-windows/box64cpu.dll /opt/deb/hangover-box64cpu/usr/lib/wine/aarch64-windows/; \
    cd /opt/deb; mv hangover-box64cpu hangover-box64cpu_HOVERSION_arm64; \
    dpkg-deb --build --root-owner-group hangover-box64cpu_HOVERSION_arm64
