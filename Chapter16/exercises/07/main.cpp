#include <cstddef>
#include <string>
#include <print>

std::size_t str_len(const char* s)
{
	if (!s) return 0;
	std::size_t n = 0;
	while (*s++)
		++n;
	return n;
}

void strn_cpy(char* dst, const char* src, std::size_t count)
{
	while (count--)
		*dst++ = *src++;
}

std::string cat_dot(const char* s1, const char* s2)
{
	std::size_t n1 = str_len(s1);
	std::size_t n2 = str_len(s2);
	// one for the dot, one for the null-terminator
	std::size_t len = n1 + n2 + 2;

	char* buf = new char[len];
	strn_cpy(buf, s1, n1);
	buf[n1] = '.';
	strn_cpy(buf + n1 + 1, s2, n2);
	buf[len - 1] = '\0';

	std::string s{buf};
	delete[] buf;
	return s;
}

int main()
{
	std::println(R"("{}")", cat_dot("Niels", "Bohr"));
}
