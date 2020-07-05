FROM ubuntu:20.04

ENV ANDROID_HOME /opt/android-sdk-linux
ENV PATH ${ANDROID_HOME}/tools/bin:${ANDROID_HOME}/platform-tools:${PATH}:${ANDROID_HOME}/tools:${PATH}

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
	unzip wget python \
&&	apt clean \
&&	rm -rf /var/lib/apt/lists/*

RUN	apt-get update && apt-get install -y --no-install-recommends \
	python \
	flex bison \
	libfreetype6-dev \
	libglib2.0-dev \
	libxcb1-dev \
	libx11-dev  \
	gradle \
	librsvg2-bin \
	gcc-mingw-w64-x86-64 gcc-mingw-w64-i686 \
	automake autoconf pkg-config libtool \
	automake1.11 autoconf2.13 autoconf2.64 \
	gtk-doc-tools git gperf groff p7zip-full \
	gettext \
	g++ \
	make \
&&	apt clean \
&&	rm -rf /var/lib/apt/lists/* \
&&	ln -s /usr/bin/autoconf /usr/bin/autoconf-2.69 \
&&	ln -s /usr/bin/autoheader /usr/bin/autoheader-2.69

RUN mkdir -p /root/hangover
COPY . /root/hangover/
RUN make -C /root/hangover -f Makefile
