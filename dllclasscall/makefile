
all: main.exe foo.dll

main.exe:	main.cpp foo.h c.o
	g++  -O2 main.cpp c.o -o main.exe

foo.dll:	foo.cpp foo.h
	g++  -O0 -shared foo.cpp -o foo.dll

c.o:	c.cpp
	g++  -O0 -c c.cpp -o c.o

clean:
	rm -f *.o
	rm -f foo.dll
	rm -f *.exe
