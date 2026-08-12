int str_len(const char* s)
{
	if (!s) return 0;

	int len = 0;
	while (*s++)
		++len;
	return len;
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

#include <string>
#include <print>

std::string format_string(const char* s)
{
	if (!s)
		return "<nullptr>";
	return "\"" + std::string{s} + "\"";
}

void print_result(const char* s1, const char* s2, int result)
{
	std::string sf1 = format_string(s1);
	std::string sf2 = format_string(s2);
	std::println(R"(str_cmp({}, {})  ->  {})", sf1, sf2, result);
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::println("usage: <string> <string>");
		return 1;
	}
	char* s1 = argv[1];
	char* s2 = argv[2];
	int cmp  = str_cmp(s1, s2);
	print_result(s1, s2, cmp);
}
