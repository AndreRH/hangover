TESTS := $(if $(NOTESTS),--disable-tests,)

WINEDLLS = dbghelp ole32 oleaut32 propsys rpcrt4 urlmon windowscodecs netapi32 dnsapi msimg32 dwmapi uxtheme setupapi wintrust wtsapi32 pdh avrt cryptnet imagehlp cryptui sensapi msvcp80 msvcp100 lz32 msi dplay dplayx dpwsockx dpnet dpnaddr dpnhpast dpnlobby dpvoice mpr oledlg shdocvw msacm32 mlang gdiplus shell32 shlwapi wininet comctl32 comdlg32 d3d10core d3d10 d3d10_1 d3dcompiler_43 msxml msxml2 msxml3 msxml4 msxml6 shfolder

WINEDLL_TARGET32 = $(patsubst %,build/qemu/x86_64-windows-user/qemu_guest_dll32/%.dll,$(WINEDLLS))
WINEDLL_TARGET64 = $(patsubst %,build/qemu/x86_64-windows-user/qemu_guest_dll64/%.dll,$(WINEDLLS))

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

WINE_SRC = $(realpath wine)
WINE_HOST = $(realpath build/wine-host)

all: build/wine-host/.built wine-guest wine-guest32 qemu $(DLL_TARGET32) $(DLL_TARGET64) $(DRV_TARGET32) $(DRV_TARGET64) $(WINEDLL_TARGET32) $(WINEDLL_TARGET64) build/qemu/x86_64-windows-user/qemu_guest_dll32/libwine.dll build/qemu/x86_64-windows-user/qemu_guest_dll64/libwine.dll
.PHONY: all

# Build the Host (e.g. arm64) wine
build/wine-host/Makefile: wine/configure
	@mkdir -p $(@D)
	cd build/wine-host ; ../../wine/configure --enable-win64 $(TESTS)

wine-host build/wine-host/.built: build/wine-host/Makefile
	+$(MAKE) -C build/wine-host
	@touch build/wine-host/.built

# Cross-Compile Wine for the guest platform to copy higher level DLLs from.
build/wine-guest/Makefile: build/wine-host/.built wine/configure
	@mkdir -p $(@D)
	cd build/wine-guest ; ../../wine/configure --host=x86_64-w64-mingw32 --with-wine-tools=../wine-host --without-freetype $(TESTS)

wine-guest: build/wine-guest/Makefile
	+$(MAKE) -C build/wine-guest $(if $(NOTESTS),$(patsubst %,dlls/%,$(WINEDLLS)),)

# Cross-Compile Wine for the guest32 platform to copy higher level DLLs from.
build/wine-guest32/Makefile: build/wine-host/.built wine/configure
	@mkdir -p $(@D)
	cd build/wine-guest32 ; ../../wine/configure --host=i686-w64-mingw32 --with-wine-tools=../wine-host --without-freetype $(TESTS)

wine-guest32: build/wine-guest32/Makefile
	+$(MAKE) -C build/wine-guest32 $(if $(NOTESTS),$(patsubst %,dlls/%,$(WINEDLLS)),)

# Build qemu
build/qemu/Makefile: build/wine-host/.built qemu/configure
	@mkdir -p $(@D)
	cd build/qemu ; CC="$(WINE_HOST)/tools/winegcc/winegcc -B$(WINE_HOST)/tools/winebuild -I$(WINE_HOST)/include -I$(WINE_SRC)/include -lpthread -DWINE_NOWINSOCK" CXX="$(WINE_HOST)/tools/winegcc/wineg++ -B$(WINE_HOST)/tools/winebuild -I$(WINE_HOST)/include -I$(WINE_SRC)/include -lpthread -DWINE_NOWINSOCK" ../../qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user --disable-fdt --disable-capstone ; cd ../.. ; touch $@

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
build/dlls64/user32/user32.dll: build/dlls64/ntdll/ntdll.dll
build/dlls64/winmm/winmm.dll: build/dlls64/user32/user32.dll

build/dlls64/%/Makefile:
	mkdir -p $(@D)
	$(eval DLL := $(lastword $(subst /, ,$(@D))))
	echo "GUEST_CC=x86_64-w64-mingw32" > $@
	echo "HOST_CC=$(TRIPLE)" >> $@
	echo "SRCDIR=../../../dlls/$(DLL)" >> $@
	echo "DESTDIR?=../../.." >> $@
	echo "GUEST_BIT=64" >> $@
	echo "HOST_BIT=64" >> $@
	echo "WINE_DIR=wine-guest" >> $@
	echo >> $@
	echo "include ../../../dlls/$(DLL)/Makefile" >> $@

build/dlls32/%/Makefile:
	mkdir -p $(@D)
	$(eval DLL := $(lastword $(subst /, ,$(@D))))
	echo "GUEST_CC=i686-w64-mingw32" > $@
	echo "HOST_CC=$(TRIPLE)" >> $@
	echo "SRCDIR=../../../dlls/$(DLL)" >> $@
	echo "DESTDIR?=../../.." >> $@
	echo "GUEST_BIT=32" >> $@
	echo "HOST_BIT=64" >> $@
	echo "WINE_DIR=wine-guest32" >> $@
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

# Link libwine
build/qemu/x86_64-windows-user/qemu_guest_dll32/libwine.dll: wine-guest32
	ln -sf ../../../wine-guest32/libs/wine/libwine.dll build/qemu/x86_64-windows-user/qemu_guest_dll32/libwine.dll
build/qemu/x86_64-windows-user/qemu_guest_dll64/libwine.dll: wine-guest
	ln -sf ../../../wine-guest/libs/wine/libwine.dll build/qemu/x86_64-windows-user/qemu_guest_dll64/libwine.dll
