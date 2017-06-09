all: misc.exe fullcrt.exe atexit.exe

misc.exe: misc.c Makefile
	x86_64-w64-mingw32-gcc $< -o $@ -lkernel32 -nostdlib

%.o: %.c Makefile
	x86_64-w64-mingw32-gcc -c $< -o $@

%.exe: %.o Makefile
	x86_64-w64-mingw32-ld $< -o $@ -lmsvcrt

clean:
	rm -rf *.exe *.o
