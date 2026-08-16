class Ptr
{
public:
	Ptr() = default;

	explicit Ptr(double value) :
		p{new double{value}}
	{}

	Ptr(const Ptr& other) :
		p{other.p ? new double{*other.p} : nullptr}
	{}

	Ptr(Ptr&& other) :
		p{other.p}
	{
		other.p = nullptr;
	}

	Ptr& operator=(const Ptr& other)
	{
		if (!other.p)
		{
			delete p;
			p = nullptr;
		}
		else
		{
			double* new_p = new double{*other.p};
			delete p;
			p = new_p;
		}
		return *this;
	}

	Ptr& operator=(Ptr&& other) noexcept
	{
		if (this != &other)
		{
			delete p;
			p = other.p;
			other.p = nullptr;
		}
		return *this;
	}

	~Ptr()
	{
		delete p;
	}

	double& operator*() const
	{
		return *p;
	}

	double* operator->() const
	{
		return p;
	}

	explicit operator bool() const
	{
		return p != nullptr;
	}
private:
	double* p = nullptr;
};

#include <iostream>

std::ostream& print_ptr(std::ostream& os, const Ptr& p)
{
	if (p)
	{
		os << *p << '\n';
	}
	else
	{
		os << "<nullptr>\n";
	}
	return os;
}

int main()
{
	Ptr p1;
	Ptr p2{3.14};

	print_ptr(std::cout, p1);
	print_ptr(std::cout, p2) << '\n';

	Ptr p3{p2};
	*p3 = 100;
	print_ptr(std::cout, p1);
	print_ptr(std::cout, p2);
	print_ptr(std::cout, p3) << '\n';

	Ptr p4{std::move(p2)};
	print_ptr(std::cout, p1);
	print_ptr(std::cout, p2);
	print_ptr(std::cout, p3);
	print_ptr(std::cout, p4) << '\n';

	p3 = p4;
	print_ptr(std::cout, p1);
	print_ptr(std::cout, p2);
	print_ptr(std::cout, p3);
	print_ptr(std::cout, p4) << '\n';

	p4 = std::move(p3);
	print_ptr(std::cout, p1);
	print_ptr(std::cout, p2);
	print_ptr(std::cout, p3);
	print_ptr(std::cout, p4) << '\n';
}
