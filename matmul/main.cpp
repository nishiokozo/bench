#include <windows.h>
#include <iostream>
//#include <stdint.h>
#include <cstdint>
#include <thread>
#include <vector>
#include <chrono>
#include <stdio.h>
using namespace std;
#define	LOOP 100LL* 1000LL* 1000LL
uint64_t *mr = new uint64_t[ 8* LOOP ];
uint64_t *ma = new uint64_t[ 8* LOOP ];
uint64_t *mb = new uint64_t[ 8* LOOP ];
int tmax = 1;
vector<thread*> list;
inline void	matmul( float* m, float* a, float* b, int loop  )
{

	for ( int i = 0 ; i < loop ; i++ )
	{
		m[ 0] = a[ 0]*b[ 0] + a[ 1]*b[ 4] + a[ 2]*b[ 8] + a[ 3]*b[12];
		m[ 1] = a[ 0]*b[ 1] + a[ 1]*b[ 5] + a[ 2]*b[ 9] + a[ 3]*b[13];
		m[ 2] = a[ 0]*b[ 2] + a[ 1]*b[ 6] + a[ 2]*b[10] + a[ 3]*b[14];
		m[ 3] = a[ 0]*b[ 3] + a[ 1]*b[ 7] + a[ 2]*b[11] + a[ 3]*b[15];
		m[ 4] = a[ 4]*b[ 0] + a[ 5]*b[ 4] + a[ 6]*b[ 8] + a[ 7]*b[12];
		m[ 5] = a[ 4]*b[ 1] + a[ 5]*b[ 5] + a[ 6]*b[ 9] + a[ 7]*b[13];
		m[ 6] = a[ 4]*b[ 2] + a[ 5]*b[ 6] + a[ 6]*b[10] + a[ 7]*b[14];
		m[ 7] = a[ 4]*b[ 3] + a[ 5]*b[ 7] + a[ 6]*b[11] + a[ 7]*b[15];
		m[ 8] = a[ 8]*b[ 0] + a[ 9]*b[ 4] + a[10]*b[ 8] + a[11]*b[12];
		m[ 9] = a[ 8]*b[ 1] + a[ 9]*b[ 5] + a[10]*b[ 9] + a[11]*b[13];
		m[10] = a[ 8]*b[ 2] + a[ 9]*b[ 6] + a[10]*b[10] + a[11]*b[14];
		m[11] = a[ 8]*b[ 3] + a[ 9]*b[ 7] + a[10]*b[11] + a[11]*b[15];
		m[12] = a[12]*b[ 0] + a[13]*b[ 4] + a[14]*b[ 8] + a[15]*b[12];
		m[13] = a[12]*b[ 1] + a[13]*b[ 5] + a[14]*b[ 9] + a[15]*b[13];
		m[14] = a[12]*b[ 2] + a[13]*b[ 6] + a[14]*b[10] + a[15]*b[14];
		m[15] = a[12]*b[ 3] + a[13]*b[ 7] + a[14]*b[11] + a[15]*b[15];
		m+=16;a+=16;b+=16;
	}
}
inline void	matmul_d( double* m, double* a, double* b, int loop  )
{

	for ( int i = 0 ; i < loop ; i++ )
	{
		m[ 0] = a[ 0]*b[ 0] + a[ 1]*b[ 4] + a[ 2]*b[ 8] + a[ 3]*b[12];
		m[ 1] = a[ 0]*b[ 1] + a[ 1]*b[ 5] + a[ 2]*b[ 9] + a[ 3]*b[13];
		m[ 2] = a[ 0]*b[ 2] + a[ 1]*b[ 6] + a[ 2]*b[10] + a[ 3]*b[14];
		m[ 3] = a[ 0]*b[ 3] + a[ 1]*b[ 7] + a[ 2]*b[11] + a[ 3]*b[15];
		m[ 4] = a[ 4]*b[ 0] + a[ 5]*b[ 4] + a[ 6]*b[ 8] + a[ 7]*b[12];
		m[ 5] = a[ 4]*b[ 1] + a[ 5]*b[ 5] + a[ 6]*b[ 9] + a[ 7]*b[13];
		m[ 6] = a[ 4]*b[ 2] + a[ 5]*b[ 6] + a[ 6]*b[10] + a[ 7]*b[14];
		m[ 7] = a[ 4]*b[ 3] + a[ 5]*b[ 7] + a[ 6]*b[11] + a[ 7]*b[15];
		m[ 8] = a[ 8]*b[ 0] + a[ 9]*b[ 4] + a[10]*b[ 8] + a[11]*b[12];
		m[ 9] = a[ 8]*b[ 1] + a[ 9]*b[ 5] + a[10]*b[ 9] + a[11]*b[13];
		m[10] = a[ 8]*b[ 2] + a[ 9]*b[ 6] + a[10]*b[10] + a[11]*b[14];
		m[11] = a[ 8]*b[ 3] + a[ 9]*b[ 7] + a[10]*b[11] + a[11]*b[15];
		m[12] = a[12]*b[ 0] + a[13]*b[ 4] + a[14]*b[ 8] + a[15]*b[12];
		m[13] = a[12]*b[ 1] + a[13]*b[ 5] + a[14]*b[ 9] + a[15]*b[13];
		m[14] = a[12]*b[ 2] + a[13]*b[ 6] + a[14]*b[10] + a[15]*b[14];
		m[15] = a[12]*b[ 3] + a[13]*b[ 7] + a[14]*b[11] + a[15]*b[15];
		m+=16;a+=16;b+=16;
	}
}

int main( int argc, char* argv[] )
{
	if ( argc > 1 ) tmax = atoi(argv[1]);
	int size = LOOP / tmax;
	printf("size %dx%d(thread)\n",size,tmax );

	auto st = chrono::system_clock::now();  
  	for ( int i=0 ; i <tmax ; i++ )
	{
		list.push_back( new thread(matmul,  (float*)&mr[size*i],  (float*)&ma[size*i], (float*)&mb[size*i], size  ) );
//		list.push_back( new thread(matmul_d,  (double*)&mr[size*i],  (double*)&ma[size*i], (double*)&mb[size*i], size  ) );
	}
	for ( const auto& t : list )
	{
		t->join();
		delete t;
	}
	auto en = chrono::system_clock::now();  

	auto time2 = chrono::duration_cast<chrono::microseconds>(en-st).count();

	printf("time:%.2fsec (%dmsec)\n",time2/1000.0/1000.0,time2/1000 );
}