#include <iostream>

#include "Int.hpp"

int main()
{
	Int a{105};
	Int b{20};
	std::cout << "a: " << a << '\n';
	std::cout << "b: " << b << '\n';
	std::cout << '\n';

	std::cout << "a + b: " << a + b << '\n';
	std::cout << "a - b: " << a - b << '\n';
	std::cout << "a * b: " << a * b << '\n';
	std::cout << "a / b: " << a / b << '\n';
	std::cout << "a % b: " << a % b << '\n';
	std::cout << '\n';

	std::cout << "a + 10: " << a + 10 << '\n';
	std::cout << "a - 10: " << a - 10 << '\n';
	std::cout << "a * 10: " << a * 10 << '\n';
	std::cout << "a / 10: " << a / 10 << '\n';
	std::cout << "a % 10: " << a % 10 << '\n';
}
