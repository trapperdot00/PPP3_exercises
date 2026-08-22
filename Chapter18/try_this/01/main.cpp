#include <iostream>
#include <string>

void suspicious(int s, int err_pos)
{
	int* p = new int[s];

	try {
		if (err_pos == 1) throw 1;
	} catch (...) {
		delete[] p;
		throw;
	}

	int* q = new int[s];

	try {
		if (err_pos == 2) throw 2;
	} catch (...) {
		delete[] p;
		delete[] q;
		throw;
	}

	delete[] p;

	try {
		if (err_pos == 3) throw 3;
	} catch (...) {
		delete[] q;
		throw;
	}

	delete[] q;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << " <err_pos>\n";
		return 1;
	}
	try {
		suspicious(10, std::stoi(argv[1]));
	} catch (int i) {
		std::cout << i << '\n';
	}
}
