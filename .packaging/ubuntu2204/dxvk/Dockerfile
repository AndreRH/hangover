FROM foundationubuntu2204

RUN rm -rf /opt/dxvk; mkdir -p /opt/dxvk/output
COPY ./ /opt/dxvk/
RUN ls -la /opt/dxvk/
ENV PATH="/opt/bylaws-llvm-mingw-20240929-ucrt-ubuntu-20.04-x86_64/bin:$PATH"
RUN cd /opt/dxvk; ./package-release.sh $(git describe --abbrev=0) /opt/dxvk/output
