#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
void add(std::vector<T>& v1, const std::vector<T>& v2)
{
	if (v1.size() > v2.size())
		throw std::invalid_argument{"v1.size() > v2.size()"};
	for (typename std::vector<T>::size_type i = 0; i < v1.size(); ++i)
		v1[i] += v2[i];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << '{';
	for (typename std::vector<T>::size_type i = 0; i < vec.size(); ++i)
	{
		if (i)
			os << ", ";
		os << vec[i];
	}
	os << '}';
	return os;
}

int main()
{
	std::vector<int> v1{1,2,3,4,5};
	std::vector<int> v2{2,4,6,8,10,12};
	std::cout << "v1: " << v1 << '\n';
	std::cout << "v2: " << v2 << '\n';

	std::vector<int> v3 = v1;
	add(v3, v2);
	std::cout << "v3: " << v3 << '\n';
}
