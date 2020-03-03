#include <windows.h>
#include <iostream>
#include <chrono>
using namespace std;

#include "foo.h"

int main()
{
	chrono::system_clock::time_point time_a;
	chrono::system_clock::time_point time_b;
	double f;

	HMODULE hdl = ::LoadLibrary( "foo.dll" );

	typedef Foo* (*DEF)(void);
	DEF  GetInstance = (DEF)::GetProcAddress(hdl, "GetInstance");
	Foo * foo =  GetInstance();

	typedef int (*DEF_B)(void);
	DEF_B  func_b = (DEF_B)::GetProcAddress(hdl, "func_b");

	int64_t loop = 2000000000;	// 20億回	

	{
		time_a= chrono::system_clock::now(); 
		for ( int64_t i=0 ; i < loop ; i++ )	foo->b();
		time_b= chrono::system_clock::now(); 
		f= chrono::duration_cast<chrono::milliseconds>(time_b-time_a).count();
		cout << "class) " << f << " msec" << endl;
	}
	{
		time_a= chrono::system_clock::now(); 
		for ( int64_t i=0 ; i < loop ; i++ )	func_b();
		time_b= chrono::system_clock::now(); 
		f= chrono::duration_cast<chrono::milliseconds>(time_b-time_a).count();
		cout << "func ) " << f << " msec" << endl;
	}

	foo->Delete();

	FreeLibrary(hdl);

}