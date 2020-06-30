SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_OPENGL32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603 -fcommon
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-host/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: opengl32.dll qemu_opengl32.dll.so

opengl32.dll: opengl32.spec main_g.o opengl_ext_g.o  opengl_norm_g.o wgl_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/opengl32.spec *_g.o -o opengl32.dll

qemu_opengl32.dll.so: main_h.o opengl_calls_h.o opengl_ext_h.o opengl_norm_h.o wgl_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_opengl32.spec *_h.o -o qemu_opengl32.dll.so -lopengl32 -fcommon

%_g.o: %.c qemu_opengl32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../wine-guest32/include -I../../../wine/include

%_h.o: %.c qemu_opengl32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
