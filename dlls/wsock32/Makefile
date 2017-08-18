DESTDIR?=../..
CURRENT_DLL=DLL_WSOCK32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: wsock32.dll qemu_wsock32.dll.so

wsock32.dll: main_g.o protocol_g.o service_g.o socket_g.o wsock32.def
	x86_64-w64-mingw32-ld -shared wsock32.def *_g.o -o wsock32.dll -nostdlib -e DllMain

qemu_wsock32.dll.so: main_h.o protocol_h.o service_h.o socket_h.o
	$(WINEGCC) -shared qemu_wsock32.spec *_h.o -o qemu_wsock32.dll.so -lwsock32

%_g.o: %.c wsock32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c wsock32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
