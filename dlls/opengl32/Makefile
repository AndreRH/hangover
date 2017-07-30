DESTDIR?=../..
CURRENT_DLL=DLL_OPENGL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: opengl32.dll qemu_opengl32.dll.so

opengl32.dll: main_g.o opengl32.def wgl_g.o
	x86_64-w64-mingw32-ld -shared opengl32.def *_g.o -o opengl32.dll -nostdlib -e DllMain

qemu_opengl32.dll.so: main_h.o wgl_h.o
	$(WINEGCC) -shared qemu_opengl32.spec *_h.o -o qemu_opengl32.dll.so -lopengl32

%_g.o: %.c opengl32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c opengl32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
