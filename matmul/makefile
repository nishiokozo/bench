FLAGS=-g -m64 -std=c++11

main.exe	: main.cpp
	clang++ -O2 $(FLAGS) main.cpp -o main.exe

main_win32	: main_win32
	clang++ -O2 $(FLAGS) main_win32.cpp -o main_win32.exe

clean:
	rm main.exe -f
