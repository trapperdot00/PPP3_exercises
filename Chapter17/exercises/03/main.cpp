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
}
