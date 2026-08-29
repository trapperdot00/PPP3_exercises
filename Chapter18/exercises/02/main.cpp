#include <type_traits>
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T, typename U>
std::common_type_t<T, U> dot_product(const std::vector<T>& vt, const std::vector<U>& vu)
{
	if (vt.size() != vu.size())
		throw std::invalid_argument{"vt.size() != vu.size()"};
	std::common_type_t<T, U> result{};
	for (typename std::vector<T>::size_type i = 0; i < vt.size(); ++i)
		result += vt[i] * vu[i];
	return result;
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
	std::vector<int> v1{1, 2, 3, 4, 5};
	std::vector<double> v2{1.1, 2.2, 3.3, 4.4, 5.5};

	std::cout << "v1: " << v1 << '\n';
	std::cout << "v2: " << v2 << '\n';

	std::cout << "dot_product(v1, v2): " << dot_product(v1, v2) << '\n';
}
