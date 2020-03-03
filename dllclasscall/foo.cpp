#include <windows.h>
#include <iostream>
using namespace std;


#include "foo.h"


void Foo::b()
{
}
void Foo::Delete()
{
	delete this;
}


extern "C" __declspec(dllexport)  Foo* GetInstance()
{
	return new Foo();
}

extern "C" __declspec(dllexport)  void func_b()
{
}
