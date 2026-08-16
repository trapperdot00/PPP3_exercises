#include "Matrix.hpp"

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

template <typename T>
void print_vector(const std::vector<T>& vec)
{
	for (typename std::vector<T>::size_type i = 0; i < vec.size(); ++i)
	{
		if (i)
			std::cout << ' ';
		std::cout << vec[i];
	}
	std::cout << '\n';
}

int main()
{
	Matrix m1{5, 5};
	FOR_EACH_INDEX(m1)
	{
		m1(row, col) = 100 + (row * m1.column_count()) + col;
	}

	std::cout << m1 << '\n';

	while (std::cin)
	{
		std::cout << "> ";
		if (char cmd; std::cin >> cmd)
		{
			std::vector<double>(Matrix::*member)(unsigned) const = nullptr;
			switch (cmd)
			{
				case 'c': case 'C':
					member = &Matrix::column;
					break;
				case 'r': case 'R':
					member = &Matrix::row;
					break;
				default:
					std::cout << "usage: [c|r] <number>\n\n";
					break;
			}
			if (!member)
				continue;
			unsigned i;
			if (!(std::cin >> i))
			{
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.clear();
				continue;
			}
			try
			{
				print_vector((m1.*member)(i));
			}
			catch (const std::exception& e)
			{
				std::cout << "Error: " << e.what() << '\n';
			}
		}
	}
}
