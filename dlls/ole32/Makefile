DESTDIR?=../..
CURRENT_DLL=DLL_OLE32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: ole32.dll qemu_ole32.dll.so

ole32.dll: compobj_g.o main_g.o ole32.def
	x86_64-w64-mingw32-ld -shared ole32.def *_g.o -o ole32.dll -nostdlib -e DllMain

qemu_ole32.dll.so: compobj_h.o main_h.o
	$(WINEGCC) -shared qemu_ole32.spec *_h.o -o qemu_ole32.dll.so -lole32

%_g.o: %.c ole32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c ole32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
