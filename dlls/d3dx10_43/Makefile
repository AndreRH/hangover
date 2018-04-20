SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_D3DX10_43
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: d3dx10_43.dll qemu_d3dx10_43.dll.so

d3dx10_43.dll: d3dx10_43.def main_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/d3dx10_43.def *_g.o -o d3dx10_43.dll -nostdlib -e DllMain

qemu_d3dx10_43.dll.so: main_h.o
	$(WINEGCC) -shared -b $(HOST_CC) $(SRCDIR)/qemu_d3dx10_43.spec *_h.o -o qemu_d3dx10_43.dll.so -ld3dx10

%_g.o: %.c qemu_d3dx10_43.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_d3dx10_43.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) -b $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
