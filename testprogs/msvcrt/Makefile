all: misc.exe

%.exe: %.c Makefile
	x86_64-w64-mingw32-gcc $< -o $@ -lkernel32 -nostdlib

clean:
	rm -rf *.exe
