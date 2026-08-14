#include <cstring>
#include <cstddef>
#include <cctype>
#include <iostream>

bool is_palindrome(const char s[], std::size_t n)
{
	if (!n) return true;
	std::size_t first = 0;
	std::size_t last = n - 1;
	while (first < last)
	{
		if (s[first] != s[last])
			return false;
		++first;
		--last;
	}
	return true;
}

// Input stream skippers

template <typename UnaryPred>
void skip_by_predicate(std::istream& is, UnaryPred pred)
{
	char c;
	while (is.get(c) && pred(c));
	if (is)
		is.unget();
}

void skip_whitespace(std::istream& is)
{
	skip_by_predicate(is, [](unsigned char c) { return std::isspace(c); });
}

void skip_nonwhitespace(std::istream& is)
{
	skip_by_predicate(is, [](unsigned char c) { return !std::isspace(c); });
}

void skip_to_next_word(std::istream& is)
{
	skip_nonwhitespace(is);
	skip_whitespace(is);
}

// ==== A) Word length checking solution ====

struct word_too_long{};

// Stores the read word into `buffer`
// Assumes buffer can hold at least `max` characters including the null-terminator
// The read word is null-terminated
std::istream& read_word_checked(std::istream& is, char* buffer, std::size_t max)
{
	skip_whitespace(is);
	std::size_t i = 0;
	char c;
	while (i < max && is.get(c) && !std::isspace(c))
	{
		if (i + 1 == max)
		{
			// buffer full, but still read a nonspace char
			// hence, the word is larger than the buffer
			is.unget();
			throw word_too_long{};
		}
		else
		{
			buffer[i] = c;
			++i;
		}
	}
	if (max > 0)
		buffer[i] = '\0';
	return is;
}

void palindrome_checked(char* s, std::size_t max)
{
	if (read_word_checked(std::cin, s, max))
	{
		std::cout << s << " is";
		if (!is_palindrome(s, std::strlen(s)))
			std::cout << " not";
		std::cout << " a palindrome\n";
	}
}

template <std::size_t max>
void test_checked()
{
	std::cout << "Testing strings with the max size of " << max << " (including null-terminator)\n";
	char s[max];
	while (std::cin)
	{
		try
		{
			palindrome_checked(s, max);
		}
		catch (word_too_long)
		{
			std::cout << "[ERROR]: Word too long, skipped...\n";
			skip_to_next_word(std::cin);
		}
	}
}

// ==== B) Arbitrary word size solution ====

void strn_cpy(char* dst, const char* src, std::size_t n)
{
	while (n--)
		*dst++ = *src++;
}

char* reallocate_buffer(char* old_buf, std::size_t old_length, std::size_t new_length)
{
	char* new_buf = new char[new_length];
	strn_cpy(new_buf, old_buf, old_length);
	new_buf[old_length] = '\0';
	delete[] old_buf;
	return new_buf;
}

// Reads a word into an arbitrarily sized buffer
// `buffer` is adjusted to point to the newly allocated word on the free store
// `n` is changed to denote the length (without the null-terminator) of the word
// `buffer` should be `delete[]`-d after you're done using it
std::istream& read_word_arbitrary(std::istream& is, char*& buffer, std::size_t& n)
{
	skip_whitespace(is);
	std::size_t length = 0;
	std::size_t buf_size = 2;
	char* buf = new char[buf_size];
	for (char c; is.get(c) && !std::isspace(c); ++length)
	{
		if (length + 1 >= buf_size)
		{
			buf_size *= 2;
			buf = reallocate_buffer(buf, length, buf_size);
		}
		buf[length] = c;
	}
	buf[length] = '\0';
	if (is)
		is.unget();
	buffer = buf;
	n = length;
	return is;
}

void palindrome_arbitrary()
{
	char* s = nullptr;
	std::size_t len = 0;
	if (read_word_arbitrary(std::cin, s, len))
	{
		std::cout << s << " is";
		if (!is_palindrome(s, len))
			std::cout << " not";
		std::cout << " a palindrome\n";
	}
	delete[] s;
}

void test_arbitrary()
{
	std::cout << "Testing arbitrarily sized strings\n";
	while (std::cin)
	{
		palindrome_arbitrary();
	}
}

int main()
{
	// select one
#if 0
	constexpr std::size_t max = 5;
	test_checked<max>();
#else
	test_arbitrary();
#endif
}
