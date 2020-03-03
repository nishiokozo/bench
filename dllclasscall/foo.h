struct Prim
{
	virtual int b() = 0;
	virtual void Delete() = 0;
};
struct Foo:Prim
{
	void Delete();
	int b();
};
