DESTDIR?=../..
CURRENT_DLL=DLL_SHELL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DNTDDI_VERSION=0x06020000
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: shell32.dll qemu_shell32.dll.so

shell32.dll: appbar_g.o main_g.o pidl_g.o shell32.def shell32_main_g.o shellitem_g.o shellole_g.o shellord_g.o shellpath_g.o shfolder_g.o shlexec_g.o
	x86_64-w64-mingw32-ld -shared shell32.def *_g.o -o shell32.dll -nostdlib -e DllMain

qemu_shell32.dll.so: appbar_h.o main_h.o pidl_h.o shell32_main_h.o shellitem_h.o shellole_h.o shellord_h.o shellpath_h.o shfolder_h.o shlexec_h.o
	$(WINEGCC) -shared qemu_shell32.spec *_h.o -o qemu_shell32.dll.so -lshell32

%_g.o: %.c shell32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c shell32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
