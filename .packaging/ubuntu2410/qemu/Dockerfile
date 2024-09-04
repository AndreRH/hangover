FROM foundationubuntu2410

RUN rm -rf /opt/qemu; mkdir -p /opt/qemu/
COPY ./ /opt/qemu/
RUN cd /opt/qemu; mkdir build; cd build; ../configure --disable-werror --target-list=arm-linux-user,i386-linux-user,x86_64-linux-user --cross-prefix=aarch64-linux-gnu- --cpu=aarch64; make -j `nproc`
RUN mkdir -p /opt/deb/hangover-libqemu/DEBIAN /opt/deb/hangover-libqemu/usr/lib/ /opt/deb/hangover-libqemu/usr/share/doc/hangover-libqemu
COPY DEBIAN /opt/deb/hangover-libqemu/DEBIAN/
RUN cp /opt/deb/hangover-libqemu/DEBIAN/copyright /opt/deb/hangover-libqemu/usr/share/doc/hangover-libqemu/; \
    cp /opt/qemu/build/libqemu-*.so /opt/deb/hangover-libqemu/usr/lib/; \
    cd /opt/deb; mv hangover-libqemu hangover-libqemu_HOVERSION~oracular_arm64; \
    dpkg-deb --build --root-owner-group hangover-libqemu_HOVERSION~oracular_arm64
