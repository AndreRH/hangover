DESTDIR?=../..
CURRENT_DLL=DLL_GDI32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: gdi32.dll qemu_gdi32.dll.so

gdi32.dll: bitblt_g.o bitmap_g.o brush_g.o clipping_g.o dc_g.o dib_g.o driver_g.o enhmetafile_g.o font_g.o gdi32.def gdiobj_g.o main_g.o mapping_g.o metafile_g.o opengl_g.o painting_g.o printdrv_g.o
	x86_64-w64-mingw32-ld -shared gdi32.def *_g.o -o gdi32.dll -nostdlib -e DllMain

qemu_gdi32.dll.so: bitblt_h.o bitmap_h.o brush_h.o clipping_h.o dc_h.o dib_h.o driver_h.o enhmetafile_h.o font_h.o gdiobj_h.o main_h.o mapping_h.o metafile_h.o opengl_h.o painting_h.o printdrv_h.o qemu_gdi32.spec
	$(WINEGCC) -shared qemu_gdi32.spec *_h.o -o qemu_gdi32.dll.so -lgdi32

%_g.o: %.c gdi32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c gdi32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
