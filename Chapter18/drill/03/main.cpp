#include <utility>
#include <string>
#include <vector>

template <typename T>
struct S
{
	S(T value) : val{std::move(value)} {}

	T val;
};

int main()
{
	S<int> sa{10};
	S<char> sb{'Y'};
	S<double> sc{3.14};
	S<std::string> sd{"hello"};
	S<std::vector<int>> se{{1,2,3,4}};
}
