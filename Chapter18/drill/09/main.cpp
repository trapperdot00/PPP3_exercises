#include <utility>
#include <string>
#include <vector>
#include <iostream>

template <typename T>
struct S
{
	S(T value) : val{std::move(value)} {}
	S& operator=(const T& value);

	T& access();
private:
	T val;
};

template <typename T>
S<T>& S<T>::operator=(const T& value)
{
	val = value;
	return *this;
}

template <typename T>
T& S<T>::access()
{
	return val;
}

template <typename T>
void read_S(S<T>& s)
{
	std::cin >> s.access();
}

template <typename T>
void read_S(S<std::vector<T>>& s)
{
	s.access().clear();
	for (T value; std::cin >> value; )
		s.access().push_back(std::move(value));
}

template <typename T>
void print_S(S<T>& s)
{
	std::cout << s.access() << '\n';
}

template <typename T>
void print_S(S<std::vector<T>>& s)
{
	for (typename std::vector<T>::size_type i = 0; i < s.access().size(); ++i)
	{
		if (i)
			std::cout << ' ';
		std::cout << s.access()[i];
	}
	std::cout << '\n';
}

int main()
{
	S<int> sa{10};
	S<char> sb{'Y'};
	S<double> sc{3.14};
	S<std::string> sd{"hello"};
	S<std::vector<int>> se{{1,2,3,4}};

	std::cout << "Values:\n";
	print_S(sa);
	print_S(sb);
	print_S(sc);
	print_S(sd);
	print_S(se);

	std::cout << "\nRead:\n";
	read_S(sa);
	read_S(sb);
	read_S(sc);
	read_S(sd);
	read_S(se);

	std::cout << "\nValues:\n";
	print_S(sa);
	print_S(sb);
	print_S(sc);
	print_S(sd);
	print_S(se);

	sa = S<int>{10000};
	print_S(sa);
}
