constexpr int ga_size = 10;
int ga[ga_size] = {1,2,4,8,16,32,64,128,256,512};

#include <cassert>
#include <iostream>

template <typename T>
void copy_array(T* dst, const T* src, int size)
{
	while (size--)
	{
		*dst++ = *src++;
	}
}

template <typename T>
void print_array(const T* arr, int size)
{
	std::cout << '{';
	for (int i = 0; i < size; ++i)
	{
		if (i)
		{
			std::cout << ", ";
		}
		std::cout << arr[i];
	}
	std::cout << "}\n";
}

void f(int arr[], int size)
{
	constexpr int la_size = 10;
	int la[la_size];

	assert(la_size == size);
	copy_array(la, arr, la_size);

	print_array(la, la_size);

	int* p = new int[size];
	copy_array(p, arr, size);
	print_array(p, size);

	delete[] p;
}
