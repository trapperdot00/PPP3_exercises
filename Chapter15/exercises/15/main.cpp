#include "Skiplist.hpp"

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

constexpr char    PRINT_OP = 'p';
constexpr char   INSERT_OP = 'i';
constexpr char   SEARCH_OP = 's';
constexpr char CONTAINS_OP = 'c';
constexpr char    ERASE_OP = 'e';
constexpr char     HELP_OP = 'h';

void print_help()
{
	std::cout << "Usage:\n"
		<< "\t'" << PRINT_OP << "'              : print elements\n"
		<< "\t'" << INSERT_OP << "' <key> <value>: insert key-value pair\n"
		<< "\t'" << SEARCH_OP << "' <key>        : search for key\n"
		<< "\t'" << CONTAINS_OP << "' <key>        : check if key exists\n"
		<< "\t'" << ERASE_OP << "' <key>        : erase pair with key\n"
		<< "\t'" << HELP_OP << "'              : print help\n";
}

using Key   = std::string;
using Value = std::string;

int main()
{
	Skiplist<Key, Value> list{1};
	std::cout << "> ";
	for (char op; std::cin >> op; std::cout << "> ")
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
			case SEARCH_OP:
			{
				Key key;
				if (std::cin >> key)
				{
					Node<Key, Value>* found = list.search(key);
					if (found)
					{
						std::cout << '[' << found->key() << "]: " << found->value() << '\n';
					}
					else
					{
						std::cout << "not found\n";
					}
				}
				break;
			}
			case CONTAINS_OP:
			{
				Key key;
				if (std::cin >> key)
				{
					bool found = list.contains(key);
					std::cout << (found ? "found" : "not found") << '\n';
				}
				break;
			}
			case ERASE_OP:
			{
				Key key;
				if (std::cin >> key)
				{
					bool erased = list.erase(key);
					std::cout << (erased ? "found & erased" : "not found") << '\n';
				}
				break;
			}
			case HELP_OP:
				[[fallthrough]];
			default:
				print_help();
				break;
		}
	}
}
