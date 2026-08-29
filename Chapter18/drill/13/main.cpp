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
	const T& access() const;
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
const T& S<T>::access() const
{
	return val;
}

struct PrintTraits
{
	static constexpr char list_starter   = '{';
	static constexpr char list_stopper   = '}';
	static constexpr char list_delimiter = ',';
};

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec)
{
	if (char ch; !(is >> ch) || ch != PrintTraits::list_starter)
	{
		is.setstate(std::ios_base::failbit);
		return is;
	}
	if (char ch; (is >> ch) && ch == PrintTraits::list_stopper)
	{
		vec = {};
		return is;
	}
	else
	{
		is.unget();
	}
	std::vector<T> tmp;
	for (T value; is; )
	{
		if (!(is >> value))
		{
			is.setstate(std::ios_base::failbit);
			return is;
		}
		tmp.push_back(std::move(value));
		if (char ch; (is >> ch) && ch != PrintTraits::list_delimiter)
		{
			is.unget();
			break;
		}
	}
	if (char ch; !(is >> ch) || ch != PrintTraits::list_stopper)
	{
		is.setstate(std::ios_base::failbit);
		return is;
	}
	vec = std::move(tmp);
	return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << PrintTraits::list_starter;
	for (typename std::vector<T>::size_type i = 0; i < vec.size(); ++i)
	{
		if (i)
			os << PrintTraits::list_delimiter;
		os << ' ' << vec[i];
	}
	if (!vec.empty())
		os << ' ';
	os << PrintTraits::list_stopper;
	return os;
}

template <typename T>
void read_val(T& v)
{
	std::cin >> v;
}

template <typename T>
void read_S(S<T>& s)
{
	read_val(s.access());
}

template <typename T>
void print_S(const S<T>& s)
{
	std::cout << s.access() << '\n';
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
}
