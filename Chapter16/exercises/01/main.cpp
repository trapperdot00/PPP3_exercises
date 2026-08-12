char lowercase(char c)
{
	// Hardcoded translation table
	// for compatibility with any character-encoding
	switch (c)
	{
		case 'A': return 'a';
		case 'B': return 'b';
		case 'C': return 'c';
		case 'D': return 'd';
		case 'E': return 'e';
		case 'F': return 'f';
		case 'G': return 'g';
		case 'H': return 'h';
		case 'I': return 'i';
		case 'J': return 'j';
		case 'K': return 'k';
		case 'L': return 'l';
		case 'M': return 'm';
		case 'N': return 'n';
		case 'O': return 'o';
		case 'P': return 'p';
		case 'Q': return 'q';
		case 'R': return 'r';
		case 'S': return 's';
		case 'T': return 't';
		case 'U': return 'u';
		case 'V': return 'v';
		case 'W': return 'w';
		case 'X': return 'x';
		case 'Y': return 'y';
		case 'Z': return 'z';
		default:
			return c;
	}
}

void to_lower(char* s)
{
	if (!s)
		return;
	while (*s)
		*s++ = lowercase(*s);
}

#include <iostream>

int main()
{
	char str[] = "Hello, World!\n";
	to_lower(str);
	std::cout << str;
}
