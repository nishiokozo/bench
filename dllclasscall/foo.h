struct Prim
{
	virtual void b() = 0;
	virtual void Delete() = 0;
};
struct Foo:Prim
{
	void Delete();
	void b();
};
