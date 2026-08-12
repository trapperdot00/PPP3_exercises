#include <cstddef>
#include <cstring>
#include <string_view>
#include <print>

template <std::size_t N>
std::size_t get_size(char (&)[N])
{
	return N;
}

template <std::size_t N>
void make_non_cstring(char (&arr)[N])
{
	if constexpr (N)
		arr[N - 1] = '!';
}

int main()
{
	char s1[] = "aaa";
	char s2[] = "aaa";
	make_non_cstring(s1);
	make_non_cstring(s2);

	// undefined behaviour
	std::println(R"(std::strcmp("{}", "{}")  ->  {})",
		std::string_view{s1, get_size(s1)},
		std::string_view{s2, get_size(s2)},
		std::strcmp(s1, s2)
	);
}
