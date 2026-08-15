#include <string>
#include <iostream>
#include <vector>

struct X
{
	int val;

	void out(const std::string& s, int nv)
	{
		std::cout << this << "->" << s << ": " << val << " (" << nv << ")\n";
	}

	X()
	{
		out("X()", 0);
		val = 0;
	}

	X(int x)
	{
		out("X(int)", x);
		val = x;
	}

	X(const X& x)
	{
		out("X(const X&)", x.val);
		val = x.val;
	}

	X& operator=(const X& x)
	{
		out("X copy assignment", x.val);
		val = x.val;
		return *this;
	}

#ifndef NOMOVE
	X(X&& x)
	{
		out("X(X&&)", x.val);
		val = x.val;
		x.val = 0;
	}

	X& operator=(X&& x)
	{
		out("X move assignment", x.val);
		val = x.val;
		x.val = 0;
		return *this;
	}
#endif

	~X()
	{
		out("~X()", 0);
	}
};

X glob{2};

X copy(X a)
{
	std::cout << "copy()\n";
	return a;
}

X copy2(X a)
{
	std::cout << "copy2()\n";
	X aa = a;
	return aa;
}

X& ref_to(X& a)
{
	std::cout << "ref_to()\n";
	return a;
}

X* make(int i)
{
	std::cout << "make()\n";
	X a(i);
	return new X{a};
}

struct XX
{
	X a;
	X b;
};

int main()
{
	X loc{4};
	X loc2{loc};
	loc = X{5};
	loc2 = copy(loc);
	loc2 = copy2(loc);
	X loc3{6};
	X& r = ref_to(loc);
	delete make(7);
	delete make(8);
	std::vector<X> v(4);
	XX loc4;
	X* p = new X{9};
	delete p;
	X* pp = new X[5];
	delete[] pp;
}
