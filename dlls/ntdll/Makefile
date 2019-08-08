DESTDIR?=../..
SRCDIR?=build_from_build_dllsXX_YYY
CURRENT_DLL=DLL_NTDLL
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -DNTDDI_VERSION=0x06020000
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: ntdll.dll qemu_ntdll.dll.so

ntdll.dll: actctx_g.o critsection_g.o debugtools_g.o env_g.o error_g.o exception_g.o file_g.o heap_g.o loader_g.o main_g.o misc_g.o nt_g.o ntdll.spec om_g.o path_g.o printf_g.o process_g.o reg_g.o resource_g.o rtl_g.o rtlstr_g.o sec_g.o signal_g.o string_g.o sync_g.o thread_g.o threadpool_g.o time_g.o version_g.o wcstring_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/ntdll.spec *_g.o -o ntdll.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x9000000

qemu_ntdll.dll.so: actctx_h.o critsection_h.o debugtools_h.o env_h.o error_h.o exception_h.o file_h.o heap_h.o loader_h.o main_h.o misc_h.o nt_h.o om_h.o path_h.o printf_h.o process_h.o qemu_ntdll.spec reg_h.o resource_h.o rtl_h.o rtlstr_h.o sec_h.o signal_h.o string_h.o sync_h.o thread_h.o threadpool_h.o time_h.o version_h.o wcstring_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_ntdll.spec *_h.o -o qemu_ntdll.dll.so

%_g.o: %.c qemu_ntdll.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_ntdll.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
