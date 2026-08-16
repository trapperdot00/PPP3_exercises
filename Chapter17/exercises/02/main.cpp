#include "Matrix.hpp"

#include <iostream>
#include <sstream>

int main()
{
	Matrix m1{20, 20};
	FOR_EACH_INDEX(m1)
	{
		double diff = std::min(
			std::min(row, m1.row_count() - row - 1),
			std::min(col, m1.column_count() - col - 1)
		);
		m1(row, col) = diff;
	}
	std::cout << m1 << '\n';

	std::ostringstream oss;
	oss << m1;
	std::istringstream iss{oss.str()};

	Matrix m2{m1.row_count(), m1.column_count()};
	if (iss >> m2)
	{
		std::cout << '\n' << m2 << '\n';
	}

	Matrix m3{5, 5};
	std::cout << "Enter a " << m3.row_count() << 'x' << m3.column_count() << " matrix:\n";
	if (std::cin >> m3)
		std::cout << "Parsed as:\n" << m3 << '\n';
	else
		std::cout << "Failed read\n";
}
