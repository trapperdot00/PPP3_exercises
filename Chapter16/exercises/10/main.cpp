unsigned long long str_len(const char* s)
{
	if (!s) return 0;
	unsigned long long n = 0;
	while (*s++)
		++n;
	return n;
}

void strn_cpy(char* dst, const char* src, unsigned long long count)
{
	while (count--)
		*dst++ = *src++;
}

char* cat_dot(const char* s1, const char* s2)
{
	auto s1_len = str_len(s1);
	auto s2_len = str_len(s2);
	auto len = s1_len + 1 + s2_len + 1;

	char* buf = new char[len];
	strn_cpy(buf, s1, s1_len);
	buf[s1_len] = '.';
	strn_cpy(buf + s1_len + 1, s2, s2_len);
	buf[len - 1] = '\0';

	return buf;
}

char* cat_dot(const char* s1, const char* s2, const char* delim)
{
	auto s1_len = str_len(s1);
	auto s2_len = str_len(s2);
	auto delim_len = str_len(delim);
	auto len = s1_len + delim_len + s2_len + 1;

	char* buf = new char[len];
	strn_cpy(buf, s1, s1_len);
	strn_cpy(buf + s1_len, delim, delim_len);
	strn_cpy(buf + s1_len + delim_len, s2, s2_len);
	buf[len - 1] = '\0';

	return buf;
}

#include <print>

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		char* cat = cat_dot(argv[1], argv[2]);
		std::println(R"("{}")", cat);
		delete[] cat;
	}
	else if (argc == 4)
	{
		char* cat = cat_dot(argv[1], argv[2], argv[3]);
		std::println(R"("{}")", cat);
		delete[] cat;
	}
	else
	{
		std::println("usage: <s1> <s2> [delim]");
		return 1;
	}
}
