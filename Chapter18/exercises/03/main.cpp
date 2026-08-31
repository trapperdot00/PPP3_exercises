#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T, typename U>
struct Pair
{
	T first;
	U second;
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

class Symbol_table
{
public:
	double get(const std::string& name) const;
	bool is_declared(const std::string& name) const;
	double declare(const std::string& name, double value, bool constant);
	void set(const std::string& name, double value);
private:
	// { name { value, constant } }
	using Variable = std::pair<std::string, std::pair<double, bool>>;
	std::vector<Variable> variables;
};

double Symbol_table::get(const std::string& name) const
{
	for (const Variable& variable : variables)
		if (variable.first == name)
			return variable.second.first;
	throw std::runtime_error{name + " not declared"};
}

bool Symbol_table::is_declared(const std::string& name) const
{
	for (const Variable& variable : variables)
		if (variable.first == name)
			return true;
	return false;
}

double Symbol_table::declare(const std::string& name, double value, bool constant)
{
	if (is_declared(name))
		throw std::runtime_error{name + " already declared"};
	variables.push_back({name, {value, constant}});
	return value;
}

void Symbol_table::set(const std::string& name, double value)
{
	for (Variable& variable : variables)
	{
		if (variable.first == name)
		{
			if (variable.second.second)
				throw std::runtime_error{"cannot set constant"};
			variable.second.first = value;
			return;
		}
	}
	throw std::runtime_error{name + " is not declared"};
}

int main()
{
	Symbol_table symtbl;

	symtbl.declare("X", 15.15, false);
	std::cout << symtbl.is_declared("X") << '\n';
	std::cout << symtbl.get("X") << '\n';

	symtbl.set("X", 3.1415);
	std::cout << symtbl.is_declared("X") << '\n';
	std::cout << symtbl.get("X") << '\n';
}
