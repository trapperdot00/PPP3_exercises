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

#include <string>
#include <print>

std::string format_found(const char* found)
{
	if (!found)
		return "<nullptr>";
	return "\"" + std::string{found} + "\"";
}

void print_result(const char* s, const char* x, const char* found)
{
	std::println(R"(find_x("{}", "{}")  ->  {})", s, x, format_found(found));
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::println("usage: <string> <find_string>");
		return 1;
	}
	char* s = argv[1];
	char* x = argv[2];
	char* found = find_x(s, x);
	print_result(s, x, found);
}
