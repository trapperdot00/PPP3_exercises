#include <vector>
#include <cassert>
#include <iostream>

std::vector<int> gv{1,2,4,8,16,32,64,128,256,512};

template <typename T>
void copy_vector(std::vector<T>& dst, const std::vector<T>& src)
{
	assert(dst.size() == src.size());
	for (typename std::vector<T>::size_type i = 0; i < dst.size(); ++i)
	{
		dst[i] = src[i];
	}
}

template <typename T>
void print_vector(const std::vector<T>& v)
{
	std::cout << '{';
	for (typename std::vector<T>::size_type i = 0; i < v.size(); ++i)
	{
		if (i)
		{
			std::cout << ", ";
		}
		std::cout << v[i];
	}
	std::cout << "}\n";
}

void f(std::vector<int> v)
{
	std::vector<int> lv(v.size());
	copy_vector(lv, v);
	print_vector(lv);

	std::vector<int> lv2{v};
	print_vector(lv2);
}

int main()
{
	f(gv);
	std::vector<int> vv{1,2,6,24,120,720,5040,40320,362880,3628800};
	f(vv);
}
