SOURCE_DIR=$(CURDIR)
BUILD_DIR=$(CURDIR)/build
TESTS := $(if $(NOTESTS),--disable-tests,)

WINEDLLS = dbghelp ole32 oleaut32 propsys rpcrt4 urlmon windowscodecs netapi32 dnsapi msimg32 crypt32 dwmapi uxtheme setupapi wintrust wtsapi32 pdh avrt cryptnet imagehlp cryptui sensapi msvcp80 msvcp100 lz32 cabinet msi dplay dplayx dpwsockx dpnet dpnaddr dpnhpast dpnlobby dpvoice mpr oledlg shdocvw msacm32 mlang gdiplus shell32 shlwapi wininet comctl32 comdlg32

WINEDLL_TARGET32 = $(patsubst %,$(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/%.dll,$(WINEDLLS))
WINEDLL_TARGET64 = $(patsubst %,$(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/%.dll,$(WINEDLLS))

DLLS = $(strip $(subst include,,$(notdir $(shell find $(SOURCE_DIR)/dlls/ -maxdepth 1 -type d | grep -v "\.drv"))))
DRVS = $(strip $(subst include,,$(notdir $(shell find $(SOURCE_DIR)/dlls/ -maxdepth 1 -type d | grep "\.drv"))))

DLL_GUEST = $(patsubst %,%.dll,$(DLLS))
DLL__HOST = $(patsubst %,qemu_%.dll.so,$(DLLS))
DLL___DIRS32 = $(patsubst %,$(BUILD_DIR)/dlls32/%/,$(DLLS))
DLL_TARGET32 = $(join $(DLL___DIRS32), $(DLL_GUEST)) $(join $(DLL___DIRS32), $(DLL__HOST))
DLL___DIRS64 = $(patsubst %,$(BUILD_DIR)/dlls64/%/,$(DLLS))
DLL_TARGET64 = $(join $(DLL___DIRS64), $(DLL_GUEST)) $(join $(DLL___DIRS64), $(DLL__HOST))

DRV__HOST = $(patsubst %,qemu_%.so,$(DRVS))
DRV___DIRS32 = $(patsubst %,$(BUILD_DIR)/dlls32/%/,$(DRVS))
DRV_TARGET32 = $(join $(DRV___DIRS32), $(DRVS)) $(join $(DRV___DIRS32), $(DRV__HOST))
DRV___DIRS64 = $(patsubst %,$(BUILD_DIR)/dlls64/%/,$(DRVS))
DRV_TARGET64 = $(join $(DRV___DIRS64), $(DRVS)) $(join $(DRV___DIRS64), $(DRV__HOST))

all: $(BUILD_DIR)/wine-host/.built wine-guest wine-guest32 qemu $(DLL_TARGET32) $(DLL_TARGET64) $(DRV_TARGET32) $(DRV_TARGET64) $(WINEDLL_TARGET32) $(WINEDLL_TARGET64) $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/libwine.dll $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/libwine.dll
.PHONY: all

# Build the Host (e.g. arm64) wine
$(BUILD_DIR)/wine-host/Makefile: $(SOURCE_DIR)/wine/configure
	@mkdir -p $(@D)
	cd $(BUILD_DIR)/wine-host ; $(SOURCE_DIR)/wine/configure --prefix=$(BUILD_DIR)/build/install --enable-win64 $(TESTS)

wine-host $(BUILD_DIR)/wine-host/.built: $(BUILD_DIR)/wine-host/Makefile
	+$(MAKE) -C $(BUILD_DIR)/wine-host
	@touch $(BUILD_DIR)/wine-host/.built

# Cross-Compile Wine for the guest platform to copy higher level DLLs from.
$(BUILD_DIR)/wine-guest/Makefile: $(BUILD_DIR)/wine-host/.built $(SOURCE_DIR)/wine/configure
	@mkdir -p $(@D)
	cd $(BUILD_DIR)/wine-guest ; $(SOURCE_DIR)/wine/configure --host=x86_64-w64-mingw32 --with-wine-tools=../wine-host --without-freetype $(TESTS)

wine-guest: $(BUILD_DIR)/wine-guest/Makefile
	+$(MAKE) -C $(BUILD_DIR)/wine-guest

# Cross-Compile Wine for the guest32 platform to copy higher level DLLs from.
$(BUILD_DIR)/wine-guest32/Makefile: $(BUILD_DIR)/wine-host/.built $(SOURCE_DIR)/wine/configure
	@mkdir -p $(@D)
	cd $(BUILD_DIR)/wine-guest32 ; $(SOURCE_DIR)/wine/configure --host=i686-w64-mingw32 --with-wine-tools=../wine-host --without-freetype $(TESTS)

wine-guest32: $(BUILD_DIR)/wine-guest32/Makefile
	+$(MAKE) -C $(BUILD_DIR)/wine-guest32

# Build qemu
$(BUILD_DIR)/qemu/Makefile: $(BUILD_DIR)/wine-host/.built $(SOURCE_DIR)/qemu/configure
	@mkdir -p $(@D)
	cd $(BUILD_DIR)/qemu ; CC="$(BUILD_DIR)/wine-host/tools/winegcc/winegcc -B$(BUILD_DIR)/wine-host/tools/winebuild -I$(BUILD_DIR)/wine-host/include -I$(SOURCE_DIR)/wine/include -lpthread -DWINE_NOWINSOCK" CXX="$(BUILD_DIR)/wine-host/tools/winegcc/wineg++ -B$(BUILD_DIR)/wine-host/tools/winebuild -I$(BUILD_DIR)/wine-host/include -I$(SOURCE_DIR)/wine/include -lpthread -DWINE_NOWINSOCK" $(SOURCE_DIR)/qemu/configure --disable-bzip2 --disable-libusb --disable-sdl --disable-snappy --disable-virtfs --disable-opengl --python=/usr/bin/python2.7 --disable-xen --disable-lzo --disable-qom-cast-debug --disable-vnc --disable-seccomp --disable-strip --disable-hax --disable-gnutls --disable-nettle --disable-replication --disable-tpm --disable-gtk --disable-gcrypt --disable-linux-aio --disable-system --disable-tools --disable-linux-user --disable-guest-agent --enable-windows-user --disable-fdt --disable-capstone

$(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so: $(BUILD_DIR)/qemu/Makefile
	+$(MAKE) -C $(BUILD_DIR)/qemu
	@mkdir -p $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64
	@mkdir -p $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_host_dll64
	@mkdir -p $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32
	@mkdir -p $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_host_dll32

# Build the wrapper DLLs.

# with known dependencies (32-bit):
$(BUILD_DIR)/dlls32/gdi32/gdi32.dll: $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/comctl32/comctl32.dll: $(BUILD_DIR)/dlls32/shlwapi/shlwapi.dll $(BUILD_DIR)/dlls32/user32/user32.dll
$(BUILD_DIR)/dlls32/d3d9/d3d9.dll: $(BUILD_DIR)/dlls32/kernel32/kernel32.dll $(BUILD_DIR)/dlls32/msvcrt/msvcrt.dll
$(BUILD_DIR)/dlls32/ddraw/ddraw.dll: $(BUILD_DIR)/dlls32/msvcrt/msvcrt.dll $(BUILD_DIR)/dlls32/kernel32/kernel32.dll
$(BUILD_DIR)/dlls32/dinput/dinput.dll: $(BUILD_DIR)/dlls32/msvcrt/msvcrt.dll $(BUILD_DIR)/dlls32/kernel32/kernel32.dll
$(BUILD_DIR)/dlls32/dsound/dsound.dll: $(BUILD_DIR)/dlls32/msvcrt/msvcrt.dll
$(BUILD_DIR)/dlls32/gdi32/gdi32.dll: $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/kernel32/kernel32.dll: $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/msvcr100/msvcr100.dll: $(BUILD_DIR)/dlls32/kernel32/kernel32.dll $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/msvcr80/msvcr80.dll: $(BUILD_DIR)/dlls32/kernel32/kernel32.dll $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/msvcrt/msvcrt.dll: $(BUILD_DIR)/dlls32/kernel32/kernel32.dll $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/riched20/riched20.dll: $(BUILD_DIR)/dlls32/user32/user32.dll
$(BUILD_DIR)/dlls32/riched32/riched32.dll: $(BUILD_DIR)/dlls32/riched20/riched20.dll
$(BUILD_DIR)/dlls32/user32/user32.dll: $(BUILD_DIR)/dlls32/ntdll/ntdll.dll
$(BUILD_DIR)/dlls32/winmm/winmm.dll: $(BUILD_DIR)/dlls32/user32/user32.dll

# with known dependencies (64-bit):
$(BUILD_DIR)/dlls64/gdi32/gdi32.dll: $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/comctl32/comctl32.dll: $(BUILD_DIR)/dlls64/shlwapi/shlwapi.dll $(BUILD_DIR)/dlls64/user32/user32.dll
$(BUILD_DIR)/dlls64/d3d9/d3d9.dll: $(BUILD_DIR)/dlls64/kernel32/kernel32.dll $(BUILD_DIR)/dlls64/msvcrt/msvcrt.dll
$(BUILD_DIR)/dlls64/ddraw/ddraw.dll: $(BUILD_DIR)/dlls64/msvcrt/msvcrt.dll $(BUILD_DIR)/dlls64/kernel32/kernel32.dll
$(BUILD_DIR)/dlls64/dinput/dinput.dll: $(BUILD_DIR)/dlls64/msvcrt/msvcrt.dll $(BUILD_DIR)/dlls64/kernel32/kernel32.dll
$(BUILD_DIR)/dlls64/dsound/dsound.dll: $(BUILD_DIR)/dlls64/msvcrt/msvcrt.dll
$(BUILD_DIR)/dlls64/gdi32/gdi32.dll: $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/kernel32/kernel32.dll: $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/msvcr100/msvcr100.dll: $(BUILD_DIR)/dlls64/kernel32/kernel32.dll $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/msvcr80/msvcr80.dll: $(BUILD_DIR)/dlls64/kernel32/kernel32.dll $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/msvcrt/msvcrt.dll: $(BUILD_DIR)/dlls64/kernel32/kernel32.dll $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/riched20/riched20.dll: $(BUILD_DIR)/dlls64/user32/user32.dll
$(BUILD_DIR)/dlls64/riched32/riched32.dll: $(BUILD_DIR)/dlls64/riched20/riched20.dll
$(BUILD_DIR)/dlls64/user32/user32.dll: $(BUILD_DIR)/dlls64/ntdll/ntdll.dll
$(BUILD_DIR)/dlls64/winmm/winmm.dll: $(BUILD_DIR)/dlls64/user32/user32.dll

$(BUILD_DIR)/dlls64/%/Makefile:
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
	echo "include $(SOURCE_DIR)/dlls/$(DLL)/Makefile" >> $@

$(BUILD_DIR)/dlls32/%/Makefile:
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
	echo "include $(SOURCE_DIR)/dlls/$(DLL)/Makefile" >> $@

define DLLS32_RULE_G
$(BUILD_DIR)/dlls32/$(1)/$(1).dll: $(BUILD_DIR)/dlls32/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls32/$(1)/$(1).dll         $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/
	+$(MAKE) -C $(BUILD_DIR)/dlls32/$(1) $(1).dll
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS32_RULE_G,$(mod))))

define DLLS64_RULE_G
$(BUILD_DIR)/dlls64/$(1)/$(1).dll: $(BUILD_DIR)/dlls64/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls64/$(1)/$(1).dll         $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/
	+$(MAKE) -C $(BUILD_DIR)/dlls64/$(1) $(1).dll
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS64_RULE_G,$(mod))))

define DRVS32_RULE_G
$(BUILD_DIR)/dlls32/$(1)/$(1): $(BUILD_DIR)/dlls32/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls32/$(1)/$(1)         $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/
	+$(MAKE) -C $(BUILD_DIR)/dlls32/$(1) $(1)
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS32_RULE_G,$(mod))))

define DRVS64_RULE_G
$(BUILD_DIR)/dlls64/$(1)/$(1): $(BUILD_DIR)/dlls64/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls64/$(1)/$(1)         $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/
	+$(MAKE) -C $(BUILD_DIR)/dlls64/$(1) $(1)
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS64_RULE_G,$(mod))))

define DLLS32_RULE_H
$(BUILD_DIR)/dlls32/$(1)/qemu_$(1).dll.so: $(BUILD_DIR)/dlls32/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls32/$(1)/qemu_$(1).dll.so $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_host_dll32/
	+$(MAKE) -C $(BUILD_DIR)/dlls32/$(1) qemu_$(1).dll.so
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS32_RULE_H,$(mod))))

define DLLS64_RULE_H
$(BUILD_DIR)/dlls64/$(1)/qemu_$(1).dll.so: $(BUILD_DIR)/dlls64/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls64/$(1)/qemu_$(1).dll.so $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_host_dll64/
	+$(MAKE) -C $(BUILD_DIR)/dlls64/$(1) qemu_$(1).dll.so
endef
$(foreach mod,$(DLLS),$(eval $(call DLLS64_RULE_H,$(mod))))

define DRVS32_RULE_H
$(BUILD_DIR)/dlls32/$(1)/qemu_$(1).so: $(BUILD_DIR)/dlls32/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls32/$(1)/qemu_$(1).so $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_host_dll32/
	+$(MAKE) -C $(BUILD_DIR)/dlls32/$(1) qemu_$(1).so
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS32_RULE_H,$(mod))))

define DRVS64_RULE_H
$(BUILD_DIR)/dlls64/$(1)/qemu_$(1).so: $(BUILD_DIR)/dlls64/$(1)/Makefile $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/dlls64/$(1)/qemu_$(1).so $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_host_dll64/
	+$(MAKE) -C $(BUILD_DIR)/dlls64/$(1) qemu_$(1).so
endef
$(foreach mod,$(DRVS),$(eval $(call DRVS64_RULE_H,$(mod))))

# Link Wine libraries.

define WINEDLLS_RULE
$(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/$(1).dll $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/$(1).dll: wine-guest32 wine-guest $(BUILD_DIR)/qemu/x86_64-windows-user/qemu-x86_64.exe.so
	ln -sf $(BUILD_DIR)/wine-guest32/dlls/$(1)/$(1).dll $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/
	ln -sf $(BUILD_DIR)/wine-guest/dlls/$(1)/$(1).dll   $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/
endef
$(foreach mod,$(WINEDLLS),$(eval $(call WINEDLLS_RULE,$(mod))))

# Link libwine
$(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/libwine.dll: wine-guest32
	ln -sf $(BUILD_DIR)/wine-guest32/libs/wine/libwine.dll $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll32/libwine.dll
$(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/libwine.dll: wine-guest
	ln -sf $(BUILD_DIR)/wine-guest/libs/wine/libwine.dll $(BUILD_DIR)/qemu/x86_64-windows-user/qemu_guest_dll64/libwine.dll
