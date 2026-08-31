#ifndef INT_HPP
#define INT_HPP

#include <iosfwd>

class Int
{
public:
	Int() : Int{0} {}
	Int(int i) : value_{i} {}
	Int& operator=(int i);

	int value() const { return value_; }

	Int& operator++();
	Int& operator--();

	Int& operator+=(const Int&);
	Int& operator-=(const Int&);
	Int& operator*=(const Int&);
	Int& operator/=(const Int&);
	Int& operator%=(const Int&);

	Int& operator<<=(const Int&);
	Int& operator>>=(const Int&);

	Int& operator&=(const Int&);
	Int& operator|=(const Int&);
	Int& operator^=(const Int&);
private:
	int value_;
};

Int operator+(Int);
Int operator-(Int);

Int operator++(Int&, int);
Int operator--(Int&, int);

Int operator+(Int, const Int&);
Int operator-(Int, const Int&);
Int operator*(Int, const Int&);
Int operator/(Int, const Int&);
Int operator%(Int, const Int&);

Int operator<<(Int, const Int&);
Int operator<<(Int, const Int&);

Int operator&(Int, const Int&);
Int operator|(Int, const Int&);
Int operator^(Int, const Int&);
Int operator~(Int);

bool operator==(const Int&, const Int&);
bool operator!=(const Int&, const Int&);
bool operator<(const Int&, const Int&);
bool operator>(const Int&, const Int&);
bool operator<=(const Int&, const Int&);
bool operator>=(const Int&, const Int&);

std::ostream& operator<<(std::ostream&, const Int&);
std::istream& operator>>(std::istream&, Int&);

#endif
