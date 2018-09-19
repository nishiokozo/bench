#include <stdio.h>
#include <math.h>
#include <chrono>
using namespace std;
float	cos2( float rad )
{
	float pow1 = rad * rad;
	float pow2 = pow1 * pow1;
	float pow3 = pow2 * pow1;
	float pow4 = pow2 * pow2;
	return 1 
		- (pow1 / 2.0f)
		+ (pow2 / 24.0f)
		- (pow3 / 720.0f)
		+ (pow4 / 40320.0f)
	;
}
float	cos3( float r )
{
	float r2 = pow(r,2);
	float r4 = pow(r,4);
	float r6 = pow(r,6);
	float r8 = pow(r,8);
	return 1 
		- (r2 / (2))
		+ (r4 / (4*3*2))
		- (r6 / (6*5*4*3*2))
		+ (r8 / (8*7*6*5*4*3*2))
	;
}

void run_loop( const char* str, int n, float (*func_cos)(float) )
{
	auto st = chrono::system_clock::now();
	for ( int i = 0 ; i <= n ; i++)
	{
		func_cos( 1.23456789f );
	}
	auto en = chrono::system_clock::now();
	auto time2 = chrono::duration_cast<chrono::microseconds>(en-st).count();
	printf("%s x%d :%.2fsec (%3lldmsec)\n",str, n, time2/1000.0/1000.0,time2/1000 );
}
int main()
{
	printf("deg : cosf()   :cos2()    :cos3()    \n" );
	printf("----+----------+----------+----------\n" );
	for ( int i = 0 ; i <= 90 ; i+=5 )
	{
		float	r = i*3.14f/180.0f;
		float	a = cosf(r);
		float	b = cos2(r);
		float	c = cos3(r);
		printf("%3d : %f : %f : %f \n", i, a,b,c );
	}
	printf("-------------------------------------\n" );


	int	loops = 1000*1000*1;
	run_loop( "cos ",loops, cosf );
	run_loop( "cos2",loops, cos2 );
	run_loop( "cos3",loops, cos3 );

	return 0;
}
