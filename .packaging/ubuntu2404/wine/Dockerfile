FROM foundationubuntu2404

ARG LLVMMINGW_NAME=llvm-mingw-20250528-ucrt-ubuntu-22.04-x86_64
ENV LLVMMINGW_PATH="/opt/$LLVMMINGW_NAME/bin"

RUN rm -rf /opt/wine; mkdir -p /opt/wine/
COPY ./ /opt/wine/
RUN ls -la /opt/wine/
RUN cp -ra /opt/wine /opt/wine64
ENV PATH="$LLVMMINGW_PATH:$PATH"
RUN cd /opt/wine64; mkdir amd64; cd amd64; ../configure --enable-win64; make __tooldeps__ -j `nproc`; make -C nls
RUN cd /opt/wine; dpkg-buildpackage -d -b -a arm64 -us -uc -ui
