#include <windows.h>
#include <iostream>
#include <cstdint>
#include <thread>
#include <vector>
#include <chrono>
#include <stdio.h>
using namespace std;
#define	LOOP 100LL* 1000LL* 1000LL
uint64_t *to = new uint64_t[ 8* LOOP ];
uint64_t *fm = new uint64_t[ 8* LOOP ];
int tmax = 1;
vector<thread*> list;
inline void func( int id, uint64_t* to, uint64_t* fm, int loop )
{
	for ( int i=0; i < loop ; i++ )
	{
		memcpy( to+=8, fm+=8, 64 );
	}
}
int main( int argc, char* argv[] )
{
	if ( argc > 1 ) tmax = atoi(argv[1]);
	int size = LOOP / tmax;
	printf("size %dx%d(thread)\n",size,tmax );

	auto st2 = chrono::system_clock::now();  
  	for ( int i=0 ; i <tmax ; i++ )
	{
		list.push_back( new thread(func, i, &to[size*i], &fm[size*i], size) );
	}
	for ( const auto& t : list )
	{
		t->join();
		delete t;
	}
	auto en2 = chrono::system_clock::now();  

	auto time2 = chrono::duration_cast<chrono::microseconds>(en2-st2).count();

	printf("time:%.2fsec (%dmsec)\n",time2/1000.0/1000.0,time2/1000 );
	return 0;
}