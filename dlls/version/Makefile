DESTDIR?=../..
CURRENT_DLL=DLL_VERSION
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: version.dll qemu_version.dll.so

version.dll: main_g.o version.def version_g.o
	x86_64-w64-mingw32-ld -shared version.def *_g.o -o version.dll -nostdlib -e DllMain

qemu_version.dll.so: main_h.o version_h.o
	$(WINEGCC) -shared qemu_version.spec *_h.o -o qemu_version.dll.so -lversion

%_g.o: %.c version.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c version.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
