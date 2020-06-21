TESTS := $(if $(NOTESTS),--disable-tests,)

WINEDLLS = activeds adsldp adsldpc shcore dbghelp ole32 oleaut32 propsys rpcrt4 urlmon netapi32 dnsapi msimg32 dwmapi uxtheme setupapi wintrust wtsapi32 pdh avrt cryptnet imagehlp cryptui sensapi msvcp80 msvcp100 lz32 msi dplay dplayx dpwsockx dpnet dpnaddr dpnhpast dpnlobby dpvoice mpr oledlg shdocvw msacm32 mlang gdiplus shell32 shlwapi wininet comctl32 comdlg32 d3d10core d3d10 d3d10_1 d3dcompiler_43 msxml msxml2 msxml3 msxml4 msxml6 shfolder d2d1 dwrite sspicli quartz msvfw32 amstream apphelp atl ieframe atl100 atl80 atlthunk scrrun mshtml inetcomm avifil32 browseui combase explorerframe credui d3dx10_43 d3dx9_43 d3dxof d3drm d3dx11_43 ddrawex devenum msdmo avicap32 dinput8 dispex dmband dmcompos dmime dmloader dmusic dmsynth hnetcfg dxdiagn evr faultrep fusion mscoree gameux hid hlink httpapi actxprxy inetmib1 snmpapi itss infosoft jscript jsproxy kernelbase mapi32 mf mfplat msctf mspatcha mswsock odbccp32 msrle32 vbscript mstask taskschd xmllite msvcirt msvcp110 msvcp120 msvcp140 msvcp60 msvcp90 netcfgx netprofm ninput ntdsapi ntprint oleacc packager psapi pstorec qcap qedit qmgr rasapi32 schannel serialui slc spoolss sti sxs twain_32 userenv vcomp version vulkan-1 winevulkan webservices winhttp wer windowscodecsext wlanapi wldap32 wmp wmphoto wmvcore wpc wsdapi wsnmp32 wuapi mssip32 msisip wbemprox powrprof
EXTDLLS  = libcharset-1 libiconv-2 libxml2-2 libxslt-1 libexslt-0
QEMU_DISABLES = --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --disable-tools --disable-linux-user --disable-guest-agent --disable-fdt --disable-capstone --disable-werror --disable-virglrenderer --disable-vte --disable-auth-pam --disable-curses --disable-docs --disable-vde --disable-cap-ng --disable-spice --disable-rbd --disable-xfsctl --disable-smartcard --disable-usb-redir --disable-libiscsi --disable-libnfs --disable-glusterfs --disable-libssh

WINEDLL_TARGET32 = $(patsubst %,build/qemu/x86_64-windows-user/qemu_guest_dll32/%.dll,$(WINEDLLS))
WINEDLL_TARGET64 = $(patsubst %,build/qemu/x86_64-windows-user/qemu_guest_dll64/%.dll,$(WINEDLLS))
EXTDLL_TARGET32  = $(patsubst %,build/qemu/x86_64-windows-user/qemu_guest_dll32/%.dll,$(EXTDLLS))
EXTDLL_TARGET64  = $(patsubst %,build/qemu/x86_64-windows-user/qemu_guest_dll64/%.dll,$(EXTDLLS))

DLLS = $(strip $(subst include,,$(notdir $(shell find dlls/ -maxdepth 1 -type d | grep -v "\.drv"))))
DRVS = $(strip $(subst include,,$(notdir $(shell find dlls/ -maxdepth 1 -type d | grep "\.drv"))))

DLL_GUEST = $(patsubst %,%.dll,$(DLLS))
DLL__HOST = $(patsubst %,qemu_%.dll.so,$(DLLS))
DLL___DIRS32 = $(patsubst %,build/dlls32/%/,$(DLLS))
DLL_TARGET32 = $(join $(DLL___DIRS32), $(DLL_GUEST)) $(join $(DLL___DIRS32), $(DLL__HOST))
DLL___DIRS64 = $(patsubst %,build/dlls64/%/,$(DLLS))
DLL_TARGET64 = $(join $(DLL___DIRS64), $(DLL_GUEST)) $(join $(DLL___DIRS64), $(DLL__HOST))

DRV__HOST = $(patsubst %,qemu_%.so,$(DRVS))
DRV___DIRS32 = $(patsubst %,build/dlls32/%/,$(DRVS))
DRV_TARGET32 = $(join $(DRV___DIRS32), $(DRVS)) $(join $(DRV___DIRS32), $(DRV__HOST))
DRV___DIRS64 = $(patsubst %,build/dlls64/%/,$(DRVS))
DRV_TARGET64 = $(join $(DRV___DIRS64), $(DRVS)) $(join $(DRV___DIRS64), $(DRV__HOST))

WINE_SRC = $(abspath wine)
WINE_HOST = $(abspath build/wine-host)

all: build/wine-host/.built wine-guest wine-guest32 qemu $(DLL_TARGET32) $(DLL_TARGET64) $(DRV_TARGET32) $(DRV_TARGET64) $(WINEDLL_TARGET32) $(WINEDLL_TARGET64) $(EXTDLL_TARGET32) $(EXTDLL_TARGET64)
.PHONY: all

build/libiconv32/Makefile: libiconv/configure
	@mkdir -p $(@D)
	cd $(@D) ; ../../libiconv/configure --host=i686-w64-mingw32 --prefix=$(abspath build/i686-w64-mingw32)

build/libiconv64/Makefile: libiconv/configure
	@mkdir -p $(@D)
	cd $(@D) ; ../../libiconv/configure --host=x86_64-w64-mingw32 --prefix=$(abspath build/x86_64-w64-mingw32)

build/i686-w64-mingw32/bin/libcharset-1.dll: build/libiconv32/Makefile
	@mkdir -p $(@D)
	+$(MAKE) -C build/libiconv32/ install

build/x86_64-w64-mingw32/bin/libcharset-1.dll: build/libiconv64/Makefile
	@mkdir -p $(@D)
	+$(MAKE) -C build/libiconv64/ install

libxml2/configure: libxml2/autogen.sh
	cd $(@D) ; NOCONFIGURE=1 ./autogen.sh

build/libxml2_32/Makefile: libxml2/configure build/i686-w64-mingw32/bin/libcharset-1.dll
	@mkdir -p $(@D)
	cd $(@D) ; ../../libxml2/configure --host=i686-w64-mingw32 --enable-static=no --enable-shared=yes --without-python --without-zlib --without-lzma --with-iconv=$(abspath build/i686-w64-mingw32) --prefix=$(abspath build/i686-w64-mingw32)

build/libxml2_64/Makefile: libxml2/configure build/x86_64-w64-mingw32/bin/libcharset-1.dll
	@mkdir -p $(@D)
	cd $(@D) ; ../../libxml2/configure --host=x86_64-w64-mingw32 --enable-static=no --enable-shared=yes --without-python --without-zlib --without-lzma --with-iconv=$(abspath build/x86_64-w64-mingw32) --prefix=$(abspath build/x86_64-w64-mingw32)

build/i686-w64-mingw32/bin/libxml2-2.dll: build/libxml2_32/Makefile
	@mkdir -p $(@D)
	+$(MAKE) -C build/libxml2_32/ install

build/x86_64-w64-mingw32/bin/libxml2-2.dll: build/libxml2_64/Makefile
	@mkdir -p $(@D)
	+$(MAKE) -C build/libxml2_64/ install

libxslt/configure: libxslt/autogen.sh
	cd $(@D) ; NOCONFIGURE=1 ./autogen.sh

build/libxslt32/Makefile: libxslt/configure build/i686-w64-mingw32/bin/libxml2-2.dll
	@mkdir -p $(@D)
	cd $(@D) ; ../../libxslt/configure --host=i686-w64-mingw32 --enable-static=no --enable-shared=yes --without-python --without-plugins --without-crypto --prefix=$(abspath build/i686-w64-mingw32) PATH=$(abspath build/i686-w64-mingw32/bin):$(PATH) PKG_CONFIG_PATH=$(abspath build/i686-w64-mingw32/lib/pkgconfig) LDFLAGS="-L$(abspath build/i686-w64-mingw32/lib) -lxml2 -liconv"

build/libxslt64/Makefile: libxslt/configure build/x86_64-w64-mingw32/bin/libxml2-2.dll
	@mkdir -p $(@D)
	cd $(@D) ; ../../libxslt/configure --host=x86_64-w64-mingw32 --enable-static=no --enable-shared=yes --without-python --without-plugins --without-crypto --prefix=$(abspath build/x86_64-w64-mingw32) PATH=$(abspath build/x86_64-w64-mingw32/bin):$(PATH) PKG_CONFIG_PATH=$(abspath build/x86_64-w64-mingw32/lib/pkgconfig) LDFLAGS="-L$(abspath build/x86_64-w64-mingw32/lib) -lxml2 -liconv"

build/i686-w64-mingw32/bin/libxslt-1.dll: build/libxslt32/Makefile
	@mkdir -p $(@D)
	+$(MAKE) -C build/libxslt32/ install

build/x86_64-w64-mingw32/bin/libxslt-1.dll: build/libxslt64/Makefile
	@mkdir -p $(@D)
	+$(MAKE) -C build/libxslt64/ install

# Build the Host (e.g. arm64) wine.
# FIXME: If $HANGOVER_WINE_CC is not set this will define CC to an empty string, which still makes configure
# happy. Is there a nicer way?
build/wine-host/Makefile: wine/configure
	@mkdir -p $(@D)
	cd build/wine-host ; CC=$(HANGOVER_WINE_CC) ../../wine/configure --enable-win64 $(TESTS)

wine-host build/wine-host/.built: build/wine-host/Makefile
	+$(MAKE) -C build/wine-host
	@touch build/wine-host/.built

# Cross-Compile Wine for the guest platform to copy higher level DLLs from.
build/wine-guest/Makefile: build/wine-host/.built wine/configure build/x86_64-w64-mingw32/bin/libxml2-2.dll build/x86_64-w64-mingw32/bin/libxslt-1.dll
	@mkdir -p $(@D)
	cd build/wine-guest ; ../../wine/configure --host=x86_64-w64-mingw32 --without-mingw --with-wine-tools=../wine-host --without-freetype $(TESTS) --with-xml --with-xslt  XML2_CFLAGS="-I$(abspath build/x86_64-w64-mingw32/include/libxml2) -I$(abspath build/x86_64-w64-mingw32/include)" XML2_LIBS="-L$(abspath build/x86_64-w64-mingw32/lib) -lxml2 -liconv"  XSLT_CFLAGS="-I$(abspath build/x86_64-w64-mingw32/include/libxml2) -I$(abspath build/x86_64-w64-mingw32/include)" XSLT_LIBS="-L$(abspath build/x86_64-w64-mingw32/lib) -lxslt -lxml2 -liconv" ac_cv_lib_soname_xslt="libxslt-1.dll"

wine-guest: build/wine-guest/Makefile
	+$(MAKE) -C build/wine-guest/libs/port
	+$(MAKE) -C build/wine-guest $(if $(NOTESTS),$(patsubst %,dlls/%,$(WINEDLLS)),)

# Cross-Compile Wine for the guest32 platform to copy higher level DLLs from.
build/wine-guest32/Makefile: build/wine-host/.built wine/configure build/i686-w64-mingw32/bin/libxml2-2.dll build/i686-w64-mingw32/bin/libxslt-1.dll
	@mkdir -p $(@D)
	cd build/wine-guest32 ; ../../wine/configure --host=i686-w64-mingw32 --without-mingw --with-wine-tools=../wine-host --without-freetype $(TESTS) --with-xml --with-xslt  XML2_CFLAGS="-I$(abspath build/i686-w64-mingw32/include/libxml2) -I$(abspath build/i686-w64-mingw32/include)" XML2_LIBS="-L$(abspath build/i686-w64-mingw32/lib) -lxml2 -liconv"  XSLT_CFLAGS="-I$(abspath build/i686-w64-mingw32/include/libxml2) -I$(abspath build/i686-w64-mingw32/include)" XSLT_LIBS="-L$(abspath build/i686-w64-mingw32/lib) -lxslt -lxml2 -liconv" ac_cv_lib_soname_xslt="libxslt-1.dll"

wine-guest32: build/wine-guest32/Makefile
	+$(MAKE) -C build/wine-guest32/libs/port
	+$(MAKE) -C build/wine-guest32 $(if $(NOTESTS),$(patsubst %,dlls/%,$(WINEDLLS)),)

# Build qemu
build/qemu/Makefile: build/wine-host/.built qemu/configure
	@mkdir -p $(@D)
	cd build/qemu ; CFLAGS="-fPIC $(CFLAGS)" LIBS="-lwine -lpthread $(LIBS)" CC="$(WINE_HOST)/tools/winegcc/winegcc --winebuild $(WINE_HOST)/tools/winebuild/winebuild -I$(WINE_HOST)/include -I$(WINE_SRC)/include --wine-objdir $(WINE_HOST) -DWINE_NOWINSOCK -U_WIN32 -UWIN64 -UWIN32 -DNOGDI -Wno-pragma-pack" CXX="$(WINE_HOST)/tools/winegcc/wineg++ --winebuild $(WINE_HOST)/tools/winebuild/winebuild -I$(WINE_HOST)/include -I$(WINE_SRC)/include --wine-objdir $(WINE_HOST) -DWINE_NOWINSOCK -U_WIN32 -UWIN64 -UWIN32 -DNOGDI -Wno-pragma-pack" ../../qemu/configure --python=/usr/bin/python3 --enable-windows-user --target-list=x86_64-windows-user $(QEMU_DISABLES); cd ../.. ; touch $@

build/qemu/x86_64-windows-user/qemu-x86_64.exe.so: build/qemu/Makefile
	+$(MAKE) -C build/qemu
	@mkdir -p build/qemu/x86_64-windows-user/qemu_guest_dll64
	@mkdir -p build/qemu/x86_64-windows-user/qemu_host_dll64
	@mkdir -p build/qemu/x86_64-windows-user/qemu_guest_dll32
	@mkdir -p build/qemu/x86_64-windows-user/qemu_host_dll32

# Build the wrapper DLLs.

# with known dependencies (32-bit):
build/dlls32/gdi32/gdi32.dll: build/dlls32/ntdll/ntdll.dll
build/dlls32/comctl32/comctl32.dll: build/dlls32/shlwapi/shlwapi.dll build/dlls32/user32/user32.dll
build/dlls32/d3d9/d3d9.dll: build/dlls32/kernel32/kernel32.dll build/dlls32/msvcrt/msvcrt.dll
build/dlls32/ddraw/ddraw.dll: build/dlls32/msvcrt/msvcrt.dll build/dlls32/kernel32/kernel32.dll
build/dlls32/dinput/dinput.dll: build/dlls32/msvcrt/msvcrt.dll build/dlls32/kernel32/kernel32.dll
build/dlls32/dsound/dsound.dll: build/dlls32/msvcrt/msvcrt.dll
build/dlls32/gdi32/gdi32.dll: build/dlls32/ntdll/ntdll.dll
build/dlls32/kernel32/kernel32.dll: build/dlls32/ntdll/ntdll.dll
build/dlls32/msvcr100/msvcr100.dll: build/dlls32/kernel32/kernel32.dll build/dlls32/ntdll/ntdll.dll
build/dlls32/msvcr80/msvcr80.dll: build/dlls32/kernel32/kernel32.dll build/dlls32/ntdll/ntdll.dll
build/dlls32/msvcrt/msvcrt.dll: build/dlls32/kernel32/kernel32.dll build/dlls32/ntdll/ntdll.dll
build/dlls32/riched20/riched20.dll: build/dlls32/user32/user32.dll
build/dlls32/riched32/riched32.dll: build/dlls32/riched20/riched20.dll
build/dlls32/shcore/shcore.dll: build/dlls32/user32/user32.dll build/dlls32/gdi32/gdi32.dll
build/dlls32/ucrtbase/ucrtbase.dll: build/dlls32/kernel32/kernel32.dll build/dlls32/ntdll/ntdll.dll
build/dlls32/user32/user32.dll: build/dlls32/ntdll/ntdll.dll
build/dlls32/winmm/winmm.dll: build/dlls32/user32/user32.dll

# with known dependencies (64-bit):
build/dlls64/gdi32/gdi32.dll: build/dlls64/ntdll/ntdll.dll
build/dlls64/comctl32/comctl32.dll: build/dlls64/shlwapi/shlwapi.dll build/dlls64/user32/user32.dll
build/dlls64/d3d9/d3d9.dll: build/dlls64/kernel32/kernel32.dll build/dlls64/msvcrt/msvcrt.dll
build/dlls64/ddraw/ddraw.dll: build/dlls64/msvcrt/msvcrt.dll build/dlls64/kernel32/kernel32.dll
build/dlls64/dinput/dinput.dll: build/dlls64/msvcrt/msvcrt.dll build/dlls64/kernel32/kernel32.dll
build/dlls64/dsound/dsound.dll: build/dlls64/msvcrt/msvcrt.dll
build/dlls64/gdi32/gdi32.dll: build/dlls64/ntdll/ntdll.dll
build/dlls64/kernel32/kernel32.dll: build/dlls64/ntdll/ntdll.dll
build/dlls64/msvcr100/msvcr100.dll: build/dlls64/kernel32/kernel32.dll build/dlls64/ntdll/ntdll.dll
build/dlls64/msvcr80/msvcr80.dll: build/dlls64/kernel32/kernel32.dll build/dlls64/ntdll/ntdll.dll
build/dlls64/msvcrt/msvcrt.dll: build/dlls64/kernel32/kernel32.dll build/dlls64/ntdll/ntdll.dll
build/dlls64/riched20/riched20.dll: build/dlls64/user32/user32.dll
build/dlls64/riched32/riched32.dll: build/dlls64/riched20/riched20.dll
build/dlls64/shcore/shcore.dll: build/dlls64/user32/user32.dll build/dlls64/gdi32/gdi32.dll
build/dlls64/ucrtbase/ucrtbase.dll: build/dlls64/kernel32/kernel32.dll build/dlls64/ntdll/ntdll.dll
build/dlls64/user32/user32.dll: build/dlls64/ntdll/ntdll.dll
build/dlls64/winmm/winmm.dll: build/dlls64/user32/user32.dll

build/dlls64/%/Makefile:
	mkdir -p $(@D)
	$(eval DLL := $(lastword $(subst /, ,$(@D))))
	echo "GUEST_CC=x86_64-w64-mingw32" > $@
	echo "HOST_CC=-Wno-pragma-pack $(TRIPLE)" >> $@
	echo "SRCDIR=../../../dlls/$(DLL)" >> $@
	echo "DESTDIR?=../../.." >> $@
	echo "GUEST_BIT=64" >> $@
	echo "HOST_BIT=64" >> $@
	echo "WINE_DIR=wine-guest" >> $@
	echo "EXTRALIBS=-lpthread" >> $@
	echo >> $@
	echo "include ../../../dlls/$(DLL)/Makefile" >> $@

build/dlls32/%/Makefile:
	mkdir -p $(@D)
	$(eval DLL := $(lastword $(subst /, ,$(@D))))
	echo "GUEST_CC=i686-w64-mingw32" > $@
	echo "HOST_CC=-Wno-pragma-pack $(TRIPLE)" >> $@
	echo "SRCDIR=../../../dlls/$(DLL)" >> $@
	echo "DESTDIR?=../../.." >> $@
	echo "GUEST_BIT=32" >> $@
	echo "HOST_BIT=64" >> $@
	echo "WINE_DIR=wine-guest32" >> $@
	echo "EXTRALIBS=-lpthread" >> $@
	echo >> $@
	echo "include ../../../dlls/$(DLL)/Makefile" >> $@

define DLLS32_RULE_G
build/dlls32/$(1)/$(1).dll: build/dlls32/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls32/$(1)/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll32/
	+$(MAKE) -C build/dlls32/$(1) $(1).dll
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS32_RULE_G,$(mod))))

define DLLS64_RULE_G
build/dlls64/$(1)/$(1).dll: build/dlls64/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls64/$(1)/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll64/
	+$(MAKE) -C build/dlls64/$(1) $(1).dll
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS64_RULE_G,$(mod))))

define DRVS32_RULE_G
build/dlls32/$(1)/$(1): build/dlls32/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls32/$(1)/$(1) build/qemu/x86_64-windows-user/qemu_guest_dll32/
	+$(MAKE) -C build/dlls32/$(1) $(1)
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS32_RULE_G,$(mod))))

define DRVS64_RULE_G
build/dlls64/$(1)/$(1): build/dlls64/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls64/$(1)/$(1) build/qemu/x86_64-windows-user/qemu_guest_dll64/
	+$(MAKE) -C build/dlls64/$(1) $(1)
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS64_RULE_G,$(mod))))

define DLLS32_RULE_H
build/dlls32/$(1)/qemu_$(1).dll.so: build/dlls32/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls32/$(1)/qemu_$(1).dll.so build/qemu/x86_64-windows-user/qemu_host_dll32/
	+$(MAKE) -C build/dlls32/$(1) qemu_$(1).dll.so
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS32_RULE_H,$(mod))))

define DLLS64_RULE_H
build/dlls64/$(1)/qemu_$(1).dll.so: build/dlls64/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls64/$(1)/qemu_$(1).dll.so build/qemu/x86_64-windows-user/qemu_host_dll64/
	+$(MAKE) -C build/dlls64/$(1) qemu_$(1).dll.so
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS64_RULE_H,$(mod))))

define DRVS32_RULE_H
build/dlls32/$(1)/qemu_$(1).so: build/dlls32/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls32/$(1)/qemu_$(1).so build/qemu/x86_64-windows-user/qemu_host_dll32/
	+$(MAKE) -C build/dlls32/$(1) qemu_$(1).so
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS32_RULE_H,$(mod))))

define DRVS64_RULE_H
build/dlls64/$(1)/qemu_$(1).so: build/dlls64/$(1)/Makefile build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../dlls64/$(1)/qemu_$(1).so build/qemu/x86_64-windows-user/qemu_host_dll64/
	+$(MAKE) -C build/dlls64/$(1) qemu_$(1).so
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS64_RULE_H,$(mod))))

# Link Wine libraries.

define WINEDLLS_RULE
build/qemu/x86_64-windows-user/qemu_guest_dll32/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll64/$(1).dll: wine-guest32 wine-guest build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../wine-guest32/dlls/$(1)/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll32/
	ln -sf ../../../wine-guest/dlls/$(1)/$(1).dll   build/qemu/x86_64-windows-user/qemu_guest_dll64/
endef
$(foreach mod,$(WINEDLLS),$(eval $(call WINEDLLS_RULE,$(mod))))

# Link external libs

define EXTDLLS_RULE
build/qemu/x86_64-windows-user/qemu_guest_dll32/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll64/$(1).dll: wine-guest32 wine-guest build/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf ../../../i686-w64-mingw32/bin/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll32/
	ln -sf ../../../x86_64-w64-mingw32/bin/$(1).dll build/qemu/x86_64-windows-user/qemu_guest_dll64/
endef
$(foreach mod,$(EXTDLLS),$(eval $(call EXTDLLS_RULE,$(mod))))
