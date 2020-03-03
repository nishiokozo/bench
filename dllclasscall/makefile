
all: main.exe foo.dll

main.exe:	main.cpp foo.h func_c.o
	g++  -O2 main.cpp func_c.o -o main.exe

foo.dll:	foo.cpp foo.h
	g++  -O0 -shared foo.cpp -o foo.dll

func_c.o:	func_c.cpp
	g++  -O0 -c func_c.cpp -o func_c.o

clean:
	rm -f *.o
	rm -f foo.dll
	rm -f *.exe
