DESTDIR?=../..
CURRENT_DLL=DLL_ADVAPI32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: advapi32.dll qemu_advapi32.dll.so

advapi32.dll: advapi32.def main_g.o advapi_g.o registry_g.o
	x86_64-w64-mingw32-ld -shared advapi32.def *_g.o -o advapi32.dll -nostdlib

qemu_advapi32.dll.so: main_h.o qemu_advapi32.spec advapi_h.o registry_h.o
	$(WINEGCC) -shared qemu_advapi32.spec *_h.o -o qemu_advapi32.dll.so

%_g.o: %.c advapi32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c advapi32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
