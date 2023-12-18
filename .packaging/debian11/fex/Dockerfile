FROM foundationdeb11

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get install -y --no-install-recommends libstdc++6:arm64 libstdc++-10-dev:arm64 clang-13 llvm-13 llvm-13-tools llvm-13-linker-tools lld-13

RUN rm -rf /opt/fex; mkdir -p /opt/fex/
COPY ./ /opt/fex/
COPY toolchain_cross.cmake /opt/fex/
RUN ls -la /opt/fex/
RUN cd /opt/fex; mkdir build; cd build; cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain_cross.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTS=False -DENABLE_ASSERTIONS=False ..; make -j `nproc` FEXCore_shared
RUN ls -la /opt/fex/build/FEXCore/Source
RUN mkdir -p /opt/deb/hangover-libfexcore/DEBIAN /opt/deb/hangover-libfexcore/usr/lib/ /opt/deb/hangover-libfexcore/usr/share/doc/hangover-libfexcore
COPY DEBIAN /opt/deb/hangover-libfexcore/DEBIAN/
RUN cp /opt/deb/hangover-libfexcore/DEBIAN/copyright /opt/deb/hangover-libfexcore/usr/share/doc/hangover-libfexcore/; \
    cp /opt/fex/build/FEXCore/Source/libFEXCore.so /opt/deb/hangover-libfexcore/usr/lib/; \
    cd /opt/deb; mv hangover-libfexcore hangover-libfexcore_HOVERSION~bullseye_arm64; \
    dpkg-deb --build --root-owner-group hangover-libfexcore_HOVERSION~bullseye_arm64
