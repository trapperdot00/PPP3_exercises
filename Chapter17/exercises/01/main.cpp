#include "Matrix.hpp"

#include <iostream>

void test1()
{
	Matrix m1{4, 4};
	Matrix m2{3, 3};
	try {
		m1 = m2;
	} catch (const std::exception& e) {
		std::cout << "[OK]: " << e.what() << '\n';
		return;
	}
	std::cout << "[FAIL]: matrices of differing sizes can be assigned\n";
}

void test2()
{
	Matrix m1{5, 5};
	Matrix m2{4, 5};
	try
	{
		m1 + m2;
	} catch (const std::exception& e) {
		std::cout << "[OK]: " << e.what() << '\n';
		return;
	}
	std::cout << "[FAIL]: matrices of differing sizes can be added\n";
}

void test3()
{
	Matrix m1{3, 3};
	FOR_EACH_INDEX(m1)
	{
		m1(row, col) = (row * m1.column_count()) + col;
	}
	Matrix m2{m1};
	if (m1 == m2)
		std::cout << "[OK]: matrices equal after copy construction\n";
	else
		std::cout << "[FAIL]: matrices not equal after copy construction\n";
}

void test4()
{
	Matrix m1{3, 3};
	FOR_EACH_INDEX(m1)
	{
		m1(row, col) = (row * m1.column_count()) + col;
	}
	Matrix m2{3, 3};
	m2 = m1;
	if (m1 == m2)
		std::cout << "[OK]: matrices equal after copy assignment\n";
	else
		std::cout << "[FAIL]: matrices not equal after copy assignment\n";
}

void test5()
{
	Matrix m1{3, 3};
	FOR_EACH_INDEX(m1)
	{
		m1(row, col) = (row * m1.column_count()) + col;
	}
	Matrix m2{3, 3};
	FOR_EACH_INDEX(m2)
	{
		m2(row, col) = -1.0 * ((row * m2.column_count()) + col);
	}
	Matrix result = m1 + m2;
	Matrix expected{3, 3}; // full of zeroes
	if (result == expected)
		std::cout << "[OK]: addition of matrices passed\n";
	else
	{
		std::cout << "[FAIL]: addition of matrices failed\n";
	}
}

void test6()
{
	Matrix m{9, 9};
	try {
		m(9, 0);
	} catch (const std::exception& e) {
		std::cout << "[OK]: out of range row indexing throws: " << e.what() << '\n';
		return;
	}
	std::cout << "[FAIL]: out of range row indexing fails\n";
}

void test7()
{
	Matrix m{9, 9};
	try {
		m(0, 9);
	} catch (const std::exception& e) {
		std::cout << "[OK]: out of range column indexing throws: " << e.what() << '\n';
		return;
	}
	std::cout << "[FAIL]: out of range column indexing fails\n";
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
}
