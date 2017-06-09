all: misc.exe

%.exe: %.o Makefile
	x86_64-w64-mingw32-ld $< -o $@ -lmsvcrt -lkernel32 -ladvapi32

%.o: %.c Makefile
	x86_64-w64-mingw32-gcc -c $< -o $@

clean:
	rm -rf *.exe *.o
