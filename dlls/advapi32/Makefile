DESTDIR?=../..
SRCDIR?=build_from_build_dllsXX_YYY
CURRENT_DLL=DLL_ADVAPI32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -D_WIN32_WINNT=0x0600 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: advapi32.dll qemu_advapi32.dll.so

advapi32.dll: advapi32.spec advapi_g.o cred_g.o crypt_arc4_g.o crypt_g.o crypt_lmhash_g.o crypt_md4_g.o crypt_md5_g.o crypt_sha_g.o eventlog_g.o lsa_g.o main_g.o registry_g.o security_g.o service_g.o wmi_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/advapi32.spec *_g.o -o advapi32.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x40000000

qemu_advapi32.dll.so: advapi_h.o cred_h.o crypt_arc4_h.o crypt_h.o crypt_lmhash_h.o crypt_md4_h.o crypt_md5_h.o crypt_sha_h.o eventlog_h.o lsa_h.o main_h.o qemu_advapi32.spec registry_h.o security_h.o service_h.o wmi_h.o
	$(WINEGCC) -shared -b $(HOST_CC) $(SRCDIR)/qemu_advapi32.spec *_h.o -o qemu_advapi32.dll.so -ladvapi32

%_g.o: %.c qemu_advapi32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_advapi32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) -b $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
