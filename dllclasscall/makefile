
all: main.exe foo.dll

main.exe:	main.cpp foo.h
	g++  -O2 main.cpp -o main.exe

foo.dll:	foo.cpp foo.h
	g++  -O0 -shared foo.cpp -o foo.dll

clean:
	rm -f *.o
	rm -f foo.dll
	rm -f *.exe
