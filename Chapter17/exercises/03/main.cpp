#include "Matrix.hpp"

#include <iostream>

int main()
{
	Matrix m1{2, 2, 1.2};
	Matrix m2{2, 2, 2.1};

	std::cout << m1 + m2 << "\n\n";
	std::cout << m1 - m2 << "\n\n";
	std::cout << m1 * m2 << "\n\n";
	std::cout << m1 / m2 << "\n\n";
	std::cout << m1 % m2 << "\n\n";

	Matrix m3{2, 3};
	Matrix m4{3, 2};

	for (unsigned i = 0; i < m3.size(); ++i)
		m3(i / m3.column_count(), i % m3.column_count()) = i + 1;

	for (unsigned i = 0; i < m4.size(); ++i)
		m4(i / m4.column_count(), i % m4.column_count()) = i + m3.size() + 1;

	std::cout << m3 * m4 << "\n\n";

	std::cout << m3 << "\n\n";
	m3 *= m4;
	std::cout << m3 << '\n';
}
