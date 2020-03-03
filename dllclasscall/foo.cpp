#include <windows.h>
#include <iostream>
using namespace std;


#include "foo.h"

int Foo::b()
{
	static	int g = 0;
	return g++;
}
void Foo::Delete()
{
	delete this;
}


extern "C" __declspec(dllexport)  Foo* GetInstance()
{
	return new Foo();
}

extern "C" __declspec(dllexport)  int func_b()
{
	static	int g = 0;
	return g++;
}
