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

#include <iostream>

int main()
{
	char s1[] = "Hello, World!";
	char* s2 = str_dup(s1);
	std::cout
		<< "s1 == '" << s1 << "'\n"
		<< "s2 == '" << s2 << "'\n";
	delete[] s2;
}
