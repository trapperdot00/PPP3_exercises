#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iosfwd>

class Matrix
{
public:
	Matrix(unsigned rows, unsigned columns, double value = 0.0);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);

	unsigned row_count() const noexcept { return rows_; }
	unsigned column_count() const noexcept { return cols_; }
	unsigned size() const noexcept { return rows_ * cols_; }

#if __cplusplus > 202002L
	double& operator[](unsigned row, unsigned column);
	const double& operator[](unsigned row, unsigned column) const;
#endif
	double& operator()(unsigned row, unsigned column);
	const double& operator()(unsigned row, unsigned column) const;

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator/=(const Matrix& other);
	Matrix& operator%=(const Matrix& other);

	template <typename Func>
	Matrix& apply(const Matrix& other, Func f)
	{
		throw_if_dimensions_differ(other);
		for (unsigned row = 0; row < row_count(); ++row)
			for (unsigned col = 0; col < column_count(); ++col)
			{
				double& lhs = this->operator()(row, col);
				lhs = f(lhs, other(row, col));
			}
		return *this;
	}
private:
	void throw_if_dimensions_differ(const Matrix&);
	unsigned to_index(unsigned row, unsigned column) const;
private:
	unsigned rows_;
	unsigned cols_;
	std::vector<double> data_;
};

bool dimensions_differ(const Matrix&, const Matrix&);
bool operator==(const Matrix&, const Matrix&);
bool operator!=(const Matrix&, const Matrix&);

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator/(const Matrix&, const Matrix&);
Matrix operator%(const Matrix&, const Matrix&);

std::ostream& operator<<(std::ostream&, const Matrix&);
std::istream& operator>>(std::istream&, Matrix&);

#define FOR_EACH_INDEX(MATRIX) \
	for (decltype(MATRIX.row_count()) row = 0; row < MATRIX.row_count(); ++row) \
		for (decltype(MATRIX.column_count()) col = 0; col < MATRIX.column_count(); ++col)

#endif
