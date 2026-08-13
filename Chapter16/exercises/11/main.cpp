#include <cstddef>
#include <string>
#include <span>
#include <string_view>
#include <iostream>
#include <print>

std::size_t str_len(const char s[])
{
	if (!s) return 0;
	std::size_t n = 0;
	while (*s++)
		++n;
	return n;
}

std::string reversed_copy(const std::string& s)
{
	std::string reversed;
	for (auto it = s.crbegin(); it != s.crend(); ++it)
		reversed.push_back(*it);
	return reversed;
}

// C-String
char* reversed_copy(const char s[])
{
	if (!s) return nullptr;
	std::size_t len = str_len(s);
	char* reversed = new char[len + 1];
	for (std::size_t i = 0; i < len; ++i)
		reversed[i] = s[len - i - 1];
	reversed[len] = '\0';
	return reversed;
}

char* reversed_copy(const char s[], std::size_t len)
{
	if (!s || len == 0) return nullptr;
	char* reversed = new char[len];
	for (std::size_t i = 0; i < len; ++i)
		reversed[i] = s[len - i - 1];
	return reversed;
}

char* reversed_copy(const char* first, const char* last)
{
	if (!first || !last) return nullptr;
	std::size_t len = last - first + 1;
	char* reversed = new char[len];
	char* dst = reversed;
	while (last >= first)
	{
		*dst++ = *last--;
	}
	return reversed;
}

bool is_palindrome(const std::string& s)
{
	return s == reversed_copy(s);
}

bool is_palindrome(const char s[], int n)
{
	char* rs = reversed_copy(s, n);
	for (int i = 0; i < n; ++i)
	{
		if (s[i] != rs[i])
		{
			delete[] rs;
			return false;
		}
	}
	delete[] rs;
	return true;
}

bool is_palindrome(const char* first, const char* last)
{
	char* rs = reversed_copy(first, last);
	char* p = rs;
	while (first <= last)
	{
		if (*first++ != *p++)
		{
			delete[] rs;
			return false;
		}
	}
	delete[] rs;
	return true;
}

bool is_palindrome(std::span<char> s)
{
	return is_palindrome(s.data(), s.size());
}

std::istream& prompted_getline(std::istream& is, std::string& s)
{
	std::cout << "> ";
	return std::getline(is, s);
}

void test(std::string s)
{
	std::span<char> sp{s.data(), s.size()};
	std::println("is_palindrome(const std::string&)      : {}", is_palindrome(s));
	std::println("is_palindrome(const char[], int)       : {}", is_palindrome(sp.data(), sp.size()));
	std::println("is_palindrome(const char*, const char*): {}", is_palindrome(sp.data(), sp.data() + sp.size() - 1));
	std::println("is_palindrome(std::span<char>)         : {}", is_palindrome(sp));
}

int main()
{
	for (std::string line; prompted_getline(std::cin, line); )
	{
		test(line);
	}
}
