dSRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_GDI32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-tools/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-tools/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: gdi32.dll qemu_gdi32.dll.so

gdi32.dll: bitblt_g.o bitmap_g.o brush_g.o clipping_g.o dc_g.o dib_g.o driver_g.o enhmetafile_g.o enhmfdrv_g.o font_g.o freetype_g.o gdi32.spec gdiobj_g.o icm_g.o main_g.o mapping_g.o metafile_g.o mfdrv_g.o opengl_g.o painting_g.o palette_g.o path_g.o pen_g.o printdrv_g.o region_g.o usp10_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/gdi32.spec *_g.o -lwinecrt0 -o gdi32.dll -nodefaultlibs -L../ntdll -lntdll -lkernel32 -nostdlib -Wl,--image-base,0x60000000

qemu_gdi32.dll.so: bitblt_h.o bitmap_h.o brush_h.o clipping_h.o dc_h.o dib_h.o driver_h.o enhmetafile_h.o enhmfdrv_h.o font_h.o freetype_h.o gdiobj_h.o icm_h.o main_h.o mapping_h.o metafile_h.o mfdrv_h.o opengl_h.o painting_h.o palette_h.o path_h.o pen_h.o printdrv_h.o qemu_gdi32.spec region_h.o usp10_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_gdi32.spec *_h.o -o qemu_gdi32.dll.so -lgdi32

%_g.o: %.c qemu_gdi32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_gdi32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
