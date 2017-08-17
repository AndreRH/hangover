DESTDIR?=../..
CURRENT_DLL=DLL_ADVAPI32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: advapi32.dll qemu_advapi32.dll.so

advapi32.dll: advapi32.def advapi_g.o crypt_g.o main_g.o registry_g.o security_g.o
	x86_64-w64-mingw32-ld -shared advapi32.def *_g.o -o advapi32.dll -nostdlib -e DllMain

qemu_advapi32.dll.so: advapi_h.o crypt_h.o main_h.o qemu_advapi32.spec registry_h.o security_h.o
	$(WINEGCC) -shared qemu_advapi32.spec *_h.o -o qemu_advapi32.dll.so -ladvapi32

%_g.o: %.c advapi32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c advapi32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
