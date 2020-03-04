
all: main.exe foo.dll

main.exe:	main.cpp foo.h func_c.o bar.dll
	g++  -O2 main.cpp func_c.o bar.dll -o main.exe

foo.dll:	foo.cpp foo.h
	g++  -O0 -shared foo.cpp -o foo.dll

bar.dll:	bar.cpp bar.h
	g++  -O0 -shared bar.cpp -o bar.dll

func_c.o:	func_c.cpp
	g++  -O0 -c func_c.cpp -o func_c.o

clean:
	rm -f *.o
	rm -f *.dll
	rm -f *.exe
