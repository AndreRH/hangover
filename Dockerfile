FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
	unzip wget python \
&&	apt clean \
&&	rm -rf /var/lib/apt/lists/*

RUN	apt-get update && apt-get install -y --no-install-recommends \
	ca-certificates \
	python \
	flex bison \
	libfreetype6-dev \
	libglib2.0-dev \
	libltdl-dev \
	libxcb1-dev \
	libx11-dev  \
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

ENV NOTESTS 1

RUN mkdir -p /root/hangover
COPY . /root/hangover/
RUN make -j `nproc` -C /root/hangover -f Makefile
