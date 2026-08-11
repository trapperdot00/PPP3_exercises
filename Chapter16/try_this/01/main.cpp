#include <cstring>
#include <cstddef>
#include <iostream>

int main()
{
	char* p = nullptr;

	// Crashes because of null-pointer dereferencing
	std::size_t x = std::strlen(p);

	std::cout << "strlen(nullptr) == " << x << '\n';
}
