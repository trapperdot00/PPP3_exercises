#include "Int.hpp"

#include <iostream>

Int& Int::operator=(int i)
{
	value_ = i;
	return *this;
}

Int& Int::operator++()
{
	++value_;
	return *this;
}

Int& Int::operator--()
{
	--value_;
	return *this;
}

Int& Int::operator+=(const Int& rhs)
{
	value_ += rhs.value_;
	return *this;
}

Int& Int::operator-=(const Int& rhs)
{
	value_ -= rhs.value_;
	return *this;
}

Int& Int::operator*=(const Int& rhs)
{
	value_ *= rhs.value_;
	return *this;
}

Int& Int::operator/=(const Int& rhs)
{
	value_ /= rhs.value_;
	return *this;
}

Int& Int::operator%=(const Int& rhs)
{
	value_ %= rhs.value_;
	return *this;
}

Int& Int::operator<<=(const Int& rhs)
{
	value_ <<= rhs.value_;
	return *this;
}

Int& Int::operator>>=(const Int& rhs)
{
	value_ >>= rhs.value_;
	return *this;
}

Int& Int::operator&=(const Int& rhs)
{
	value_ &= rhs.value_;
	return *this;
}

Int& Int::operator|=(const Int& rhs)
{
	value_ |= rhs.value_;
	return *this;
}

Int& Int::operator^=(const Int& rhs)
{
	value_ ^= rhs.value_;
	return *this;
}

Int operator+(Int i)
{
	return Int{+i.value()};
}

Int operator-(Int i)
{
	return Int{-i.value()};
}

Int operator++(Int& i, int)
{
	Int old{i};
	++i;
	return old;
}

Int operator--(Int& i, int)
{
	Int old{i};
	--i;
	return old;
}

Int operator+(Int lhs, const Int& rhs)
{
	return lhs += rhs;
}

Int operator-(Int lhs, const Int& rhs)
{
	return lhs -= rhs;
}

Int operator*(Int lhs, const Int& rhs)
{
	return lhs *= rhs;
}

Int operator/(Int lhs, const Int& rhs)
{
	return lhs /= rhs;
}

Int operator%(Int lhs, const Int& rhs)
{
	return lhs %= rhs;
}

Int operator<<(Int lhs, const Int& rhs)
{
	return lhs <<= rhs;
}

Int operator>>(Int lhs, const Int& rhs)
{
	return lhs >>= rhs;
}

Int operator&(Int lhs, const Int& rhs)
{
	return lhs &= rhs;
}

Int operator|(Int lhs, const Int& rhs)
{
	return lhs |= rhs;
}

Int operator^(Int lhs, const Int& rhs)
{
	return lhs ^= rhs;
}

Int operator~(Int i)
{
	return Int{~i.value()};
}

bool operator==(const Int& lhs, const Int& rhs)
{
	return lhs.value() == rhs.value();
}

bool operator!=(const Int& lhs, const Int& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Int& lhs, const Int& rhs)
{
	return lhs.value() < rhs.value();
}

bool operator>(const Int& lhs, const Int& rhs)
{
	return rhs < lhs;
}

bool operator<=(const Int& lhs, const Int& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const Int& lhs, const Int& rhs)
{
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Int& i)
{
	return os << i.value();
}

std::istream& operator>>(std::istream& is, Int& i)
{
	if (int j; is >> j)
		i = j;
	return is;
}
