SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_OPENGL32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: opengl32.dll qemu_opengl32.dll.so

opengl32.dll: main_g.o opengl32.def wgl_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/opengl32.def *_g.o -o opengl32.dll -nostdlib -e DllMain

qemu_opengl32.dll.so: main_h.o wgl_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_opengl32.spec *_h.o -o qemu_opengl32.dll.so -lopengl32

%_g.o: %.c qemu_opengl32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_opengl32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
