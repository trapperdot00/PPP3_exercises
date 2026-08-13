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

std::string cat_dot(const char* s1, const char* s2, const char* delim)
{
	std::size_t s1_len    = str_len(s1);
	std::size_t s2_len    = str_len(s2);
	std::size_t delim_len = str_len(delim);
	std::size_t len = s1_len + s2_len + delim_len + 1;

	char* buf = new char[len];
	strn_cpy(buf, s1, s1_len);
	strn_cpy(buf + s1_len, delim, delim_len);
	strn_cpy(buf + s1_len + delim_len, s2, s2_len);
	buf[len - 1] = '\0';

	std::string s{buf};
	delete[] buf;
	return s;
}

std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& delim)
{
	return s1 + delim + s2;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::println("usage: <string> <string> <delim>");
		return 1;
	}
	std::println(R"("{}")", cat_dot(
		argv[1], argv[2], argv[3]
	));
	std::println(R"("{}")", cat_dot(
		std::string{argv[1]}, std::string{argv[2]}, std::string{argv[3]}
	));
}
