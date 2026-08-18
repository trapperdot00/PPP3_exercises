#include "Matrix.hpp"

#include <stdexcept>
#include <utility>
#include <functional>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Matrix::Matrix(unsigned rows, unsigned columns, double value) :
	rows_{rows},
	cols_{columns},
	data_(rows_ * columns, value)
{}

Matrix::Matrix(const Matrix& other) :
	rows_{other.rows_},
	cols_{other.cols_},
	data_{other.data_}
{}

Matrix::Matrix(Matrix&& other) :
	rows_{other.rows_},
	cols_{other.cols_},
	data_{std::move(other.data_)}
{}

Matrix& Matrix::operator=(const Matrix& other)
{
	throw_if_dimensions_differ(other);
	data_ = other.data_;
	return *this;
}

Matrix& Matrix::operator=(Matrix&& other)
{
	throw_if_dimensions_differ(other);
	data_ = std::move(other.data_);
	return *this;
}

#if __cplusplus > 202002L
double& Matrix::operator[](unsigned row, unsigned column)
{
	return this->operator()(row, column);
}

const double& Matrix::operator[](unsigned row, unsigned column) const
{
	return this->operator()(row, column);
}
#endif

double& Matrix::operator()(unsigned row, unsigned column)
{
	return data_[to_index(row, column)];
}

const double& Matrix::operator()(unsigned row, unsigned column) const
{
	return data_[to_index(row, column)];
}

std::vector<double> Matrix::row(unsigned i) const
{
	if (i >= row_count())
		throw std::out_of_range{"row out of range"};
	std::vector<double> result;
	for (unsigned col = 0; col < column_count(); ++col)
		result.push_back(this->operator()(i, col));
	return result;
}

std::vector<double> Matrix::column(unsigned i) const
{
	if (i >= column_count())
		throw std::out_of_range{"column out of range"};
	std::vector<double> result;
	for (unsigned row = 0; row < row_count(); ++row)
		result.push_back(this->operator()(row, i));
	return result;
}

unsigned Matrix::to_index(unsigned row, unsigned column) const
{
	if (row >= rows_ || column >= cols_)
		throw std::out_of_range{"index out of range"};
	return (row * cols_) + column;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	return apply_elementwise(other, std::plus<double>{});
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	return apply_elementwise(other, std::minus<double>{});
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	Matrix tmp = *this * other;
	rows_ = tmp.rows_;
	cols_ = tmp.cols_;
	data_ = std::move(tmp.data_);
	return *this;
}

Matrix& Matrix::operator/=(const Matrix& other)
{
	return apply_elementwise(other, std::divides<double>{});
}

Matrix& Matrix::operator%=(const Matrix& other)
{
	return apply_elementwise(other, [](double a, double b) { return std::fmod(a, b); });
}

bool dimensions_differ(const Matrix& a, const Matrix& b)
{
	return a.row_count() != b.row_count() || a.column_count() != b.column_count();
}

void Matrix::throw_if_dimensions_differ(const Matrix& other)
{
	if (dimensions_differ(*this, other))
		throw std::invalid_argument{"Matrix dimensions differ"};
}

bool operator==(const Matrix& a, const Matrix& b)
{
	if (dimensions_differ(a, b))
		return false;
	FOR_EACH_INDEX(a)
	{
		if (a(row, col) != b(row, col))
			return false;
	}
	return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
	return !(a == b);
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix result{a};
	result += b;
	return result;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix result{a};
	result -= b;
	return result;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a.column_count() != b.row_count())
		throw std::invalid_argument{"Matrix with invalid dimensions for multiplication"};
	Matrix result{a.row_count(), b.column_count()};
	for (unsigned row = 0; row < result.row_count(); ++row)
	{
		for (unsigned col = 0; col < result.column_count(); ++col)
		{
			double acc = 0;
			for (unsigned k = 0; k < a.column_count(); ++k)
				acc += a(row, k) * b(k, col);
			result(row, col) = acc;
		}
	}
	return result;
}

Matrix operator/(const Matrix& a, const Matrix& b)
{
	Matrix result{a};
	result /= b;
	return result;
}

Matrix operator%(const Matrix& a, const Matrix& b)
{
	Matrix result{a};
	result %= b;
	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	for (unsigned row = 0; row < m.row_count(); ++row)
	{
		if (row)
			os << '\n';
		for (unsigned col = 0; col < m.column_count(); ++col)
		{
			if (col)
				os << ' ';
			os << m(row, col);
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
	unsigned row = 0;
	for (std::string line; row < m.row_count() && std::getline(is, line); ++row)
	{
		std::vector<double> values;
		std::istringstream line_stream{line};
		for (double value; line_stream >> value; )
			values.push_back(value);
		if (values.size() != m.column_count())
			is.clear(std::ios_base::failbit);
		else
			for (unsigned col = 0; col < values.size(); ++col)
				m(row, col) = values[col];
	}
	if (row != m.row_count())
		is.clear(std::ios_base::failbit);
	return is;
}
