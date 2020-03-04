#include <windows.h>
#include <iostream>
#include <chrono>
using namespace std;

#include "foo.h"
#include "bar.h"

void func_c();

int main()
{
	chrono::system_clock::time_point time_a;
	chrono::system_clock::time_point time_b;
	double f;

	HMODULE hdl = ::LoadLibrary( "foo.dll" );

	typedef Foo* (*DEF)(void);
	DEF  GetInstance = (DEF)::GetProcAddress(hdl, "GetInstance");
	Foo * foo =  GetInstance();

	typedef void (*DEF_B)(void);
	DEF_B  func_b = (DEF_B)::GetProcAddress(hdl, "func_b");


	Bar	bar;

	int64_t loop = 2000000000;	// 20億回	

	{
		time_a= chrono::system_clock::now(); 
		for ( int64_t i=0 ; i < loop ; i++ )	foo->b();
		time_b= chrono::system_clock::now(); 
		f= chrono::duration_cast<chrono::milliseconds>(time_b-time_a).count();
		cout << "foo::b in loaded dll) " << f << " msec" << endl;
	}
	{
		time_a= chrono::system_clock::now(); 
		for ( int64_t i=0 ; i < loop ; i++ )	bar.b();
		time_b= chrono::system_clock::now(); 
		f= chrono::duration_cast<chrono::milliseconds>(time_b-time_a).count();
		cout << "bar::b in linked dll) " << f << " msec" << endl;
	}
	{
		time_a= chrono::system_clock::now(); 
		for ( int64_t i=0 ; i < loop ; i++ )	func_b();
		time_b= chrono::system_clock::now(); 
		f= chrono::duration_cast<chrono::milliseconds>(time_b-time_a).count();
		cout << "func_b in linked dll) " << f << " msec" << endl;
	}
	{
		time_a= chrono::system_clock::now(); 
		for ( int64_t i=0 ; i < loop ; i++ )	func_c();
		time_b= chrono::system_clock::now(); 
		f= chrono::duration_cast<chrono::milliseconds>(time_b-time_a).count();
		cout << "func_c in linked obj) " << f << " msec" << endl;
	}

	foo->Delete();

	FreeLibrary(hdl);

}