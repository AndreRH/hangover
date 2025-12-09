FROM foundationubuntu2510

ARG LLVMMINGW_NAME=llvm-mingw-20251202-ucrt-ubuntu-22.04-aarch64
ENV LLVMMINGW_PATH="/opt/$LLVMMINGW_NAME/bin"

RUN rm -rf /opt/wine; mkdir -p /opt/wine/
COPY ./ /opt/wine/
RUN ls -la /opt/wine/
ENV PATH="$LLVMMINGW_PATH:$PATH"
RUN cd /opt/wine; dpkg-buildpackage -d -b -a arm64 -us -uc -ui
