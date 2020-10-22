+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_CRYPT32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -DCERT_CHAIN_PARA_HAS_EXTRA_FIELDS -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-tools/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-tools/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: crypt32.dll qemu_crypt32.dll.so

crypt32.dll: base64_g.o cert_g.o chain_g.o collectionstore_g.o crl_g.o crypt32.spec ctl_g.o decode_g.o encode_g.o main_g.o message_g.o msg_g.o object_g.o oid_g.o protectdata_g.o serialize_g.o sip_g.o store_g.o str_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/crypt32.spec *_g.o -o crypt32.dll

qemu_crypt32.dll.so: base64_h.o cert_h.o chain_h.o collectionstore_h.o crl_h.o ctl_h.o decode_h.o encode_h.o main_h.o message_h.o msg_h.o object_h.o oid_h.o protectdata_h.o qemu_crypt32.spec serialize_h.o sip_h.o store_h.o str_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_crypt32.spec *_h.o -o qemu_crypt32.dll.so -lcrypt32

%_g.o: %.c qemu_crypt32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_crypt32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
