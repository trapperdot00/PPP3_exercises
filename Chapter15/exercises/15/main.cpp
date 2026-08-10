#define private public
#include "Skiplist.hpp"
#undef private

#include <iostream>
#include <string>
#include <cctype>

template <typename Key, typename T>
void print_list(const Skiplist<Key, T>& list)
{
	for (const auto& pair : list)
	{
		std::cout << '[' << pair.first << "]: " << pair.second << '\n';
	}
}

constexpr char  PRINT_OP = 'p';
constexpr char INSERT_OP = 'i';
constexpr char  ERASE_OP = 'e';

using Key   = int;
using Value = int;

int main()
{
	Skiplist<Key, Value> list{1};
	for (char op; std::cin >> op; )
	{
		switch (std::tolower(op))
		{
			case PRINT_OP:
				print_list(list);
				break;
			case INSERT_OP:
			{
				Key key;
				Value value;
				if (std::cin >> key >> value)
				{
					list.insert(key, value);
				}
				break;
			}
			case ERASE_OP:
			{
				Key key;
				if (std::cin >> key)
				{
					list.erase(key);
				}
				break;
			}
			default:
				break;
		}
	}
}
