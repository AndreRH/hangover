DESTDIR?=../..
SRCDIR?=build_from_build_dllsXX_YYY
CURRENT_DLL=DLL_NTDLL
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: ntdll.dll qemu_ntdll.dll.so

ntdll.dll: actctx_g.o critsection_g.o error_g.o exception_g.o file_g.o heap_g.o loader_g.o main_g.o misc_g.o nt_g.o ntdll.def om_g.o path_g.o process_g.o reg_g.o rtl_g.o rtlstr_g.o signal_g.o string_g.o sync_g.o thread_g.o version_g.o wcstring_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/ntdll.def *_g.o -o ntdll.dll -nostdlib -e DllMain

qemu_ntdll.dll.so: actctx_h.o critsection_h.o error_h.o exception_h.o file_h.o heap_h.o loader_h.o main_h.o misc_h.o nt_h.o om_h.o path_h.o process_h.o qemu_ntdll.spec reg_h.o rtl_h.o rtlstr_h.o signal_h.o string_h.o sync_h.o thread_h.o version_h.o wcstring_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_ntdll.spec *_h.o -o qemu_ntdll.dll.so

%_g.o: %.c ntdll.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c ntdll.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
