all: misc.exe

%.exe: %.o Makefile
	x86_64-w64-mingw32-ld $< -o $@ -lkernel32 -ladvapi32 -lmingw32 -lmsvcrt

%.o: %.c Makefile
	x86_64-w64-mingw32-gcc -c $<

clean:
	rm -rf *.exe *.o
