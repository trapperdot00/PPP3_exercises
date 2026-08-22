#include <utility>

template <typename T>
struct S
{
	S(T value) : val{std::move(value)} {}

	T val;
};
