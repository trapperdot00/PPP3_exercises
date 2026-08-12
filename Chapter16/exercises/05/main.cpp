int str_len(const char* s)
{
	if (!s) return 0;

	int len = 0;
	while (*s++)
		++len;
	return len;
}

void str_cpy(char* dst, const char* src)
{
	if (!dst || !src) return;

	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char* str_dup(const char* s)
{
	if (!s) return nullptr;

	int size = str_len(s) + 1; // space for null
	char* copy = new char[size];
	str_cpy(copy, s);
	return copy;
}

bool starts_with(const char* s, const char* x)
{
	while (*s && *x)
	{
		if (*s++ != *x++)
			return false;
	}
	return *x == '\0';
}

char* find_x(char* s, const char* x)
{
	if (!s || !x) return nullptr;
	if (*x == '\0') return s;
	while (*s)
	{
		if (starts_with(s, x))
			return s;
		++s;
	}
	return nullptr;
}

int str_cmp(const char* s1, const char* s2)
{
	while (*s1 && *s2)
	{
		if (*s1 < *s2) return -1;
		if (*s1 > *s2) return  1;
		++s1;
		++s2;
	}
	if (*s1) return  1;
	if (*s2) return -1;
	return 0;
}

// explicit string-size versions:

void strn_cpy(char* dst, const char* src, unsigned n)
{
	while (n--)
	{
		*dst++ = *src++;
	}
}

char* strn_dup(const char* s, unsigned n)
{
	if (!s) return nullptr;
	char* copy = new char[n];
	strn_cpy(copy, s, n);
	return copy;
}

bool starts_with_n(const char* s, unsigned n1, const char* x, unsigned n2)
{
	if (n1 < n2) return false;
	while (n2--)
	{
		if (*s++ != *x++)
			return false;
	}
	return true;
}

char* findn_x(char* s, unsigned n1, const char* x, unsigned n2)
{
	if (!s || !x) return nullptr;
	if (!n2) return s;
	while (n1 >= n2)
	{
		if (starts_with_n(s, n1, x, n2))
			return s;
		++s;
		--n1;
	}
	return nullptr;
}

int strn_cmp(const char* s1, unsigned n1, const char* s2, unsigned n2)
{
	while (n1 && n2)
	{
		if (*s1 < *s2) return -1;
		if (*s1 > *s2) return  1;
		++s1;
		++s2;
		--n1;
		--n2;
	}
	if (n1) return  1;
	if (n2) return -1;
	return 0;
}

// testing

#include <print>
#include <string_view>

void test_strn_dup(const char* s, unsigned n)
{
	char* cp = strn_dup(s, n);
	std::println(R"([strn_dup] n: {}, original: "{}", copied: "{}")",
			n, std::string_view{s, n},
			std::string_view{cp, n}
	);
	delete[] cp;
}

void test_findn_x(char* s1, unsigned n1, const char* s2, unsigned n2)
{
	char* found = findn_x(s1, n1, s2, n2);
	std::print(R"([findn_x] s1: "{}", n1: {}, s2: "{}", n2: {}, found: )",
		std::string_view{s1, n1}, n1,
		std::string_view{s2, n2}, n2
	);
	if (found)
	{
		auto found_n = n1 - (found - s1);
		std::println(R"("{}")", std::string_view(found, found_n));
	}
	else
	{
		std::println("<nullptr>");
	}
}

void test_strn_cmp(const char* s1, unsigned n1, const char* s2, unsigned n2)
{
	int cmp = strn_cmp(s1, n1, s2, n2);
	std::println(R"([strn_cmp]: s1: "{}", n1: {}, s2: "{}", n2: {}, result: {})",
		std::string_view{s1, n1}, n1,
		std::string_view{s2, n2}, n2,
		cmp
	);
}

void test(char* s1, unsigned n1, char* s2, unsigned n2)
{
	test_strn_dup(s1, n1);
	test_strn_dup(s2, n2);
	test_findn_x(s1, n1, s2, n2);
	test_strn_cmp(s1, n1, s2, n2);
}

int make_non_cstring(char* s)
{
	int len = str_len(s);
	s[len] = '!';
	return len;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::println("usage: <string> <string>");
		return 1;
	}
	char* s1 = argv[1];
	int n1 = make_non_cstring(s1);
	char* s2 = argv[2];
	int n2 = make_non_cstring(s2);

	test(s1, n1, s2, n2);
}
