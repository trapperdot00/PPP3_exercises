#include <concepts>
#include <type_traits>
#include <utility>
#include <string>
#include <iostream>

template <typename T>
struct Link
{
	// Cheesing out a constructor that forwards its first
	// argument, to be able to write it only once.
	// You can only `std::forward<T>()` inside template
	// functions' parameters, so I made a template
	// constructor that takes any type `U` that can be used
	// to construct `T`, which I can forward to value:
	//  - moves if I pass an rvalue
	//  - copies if I pass an lvalue
	template <typename U>
		requires std::constructible_from<T, U>
	explicit Link(U&& v, Link* p = nullptr, Link* s = nullptr) :
		value{std::forward<U>(v)}, prev{p}, succ{s}
	{}

	T value;
	Link* prev;
	Link* succ;
};

// Prefer `std::string`s
Link(const char*) -> Link<std::string>;

// Deduce the type implicitly from the constructor's argument
template <typename T>
Link(T) -> Link<T>;

template <typename T>
Link<T>* insert(Link<T>* p, Link<T>* n)
{
	if (!n) return p;
	if (!p) return n;
	n->succ = p;
	if (p->prev)
		p->prev->succ = n;
	n->prev = p->prev;
	p->prev = n;
	return n;
}

int main()
{
	using God = std::string;
	Link<God>* norse_gods = new Link{"Thor"};
	norse_gods = insert(norse_gods, new Link{"Odin"});
	norse_gods = insert(norse_gods, new Link{"Freja"});

	while (norse_gods)
	{
		Link<God>* next = norse_gods->succ;
		delete norse_gods;
		norse_gods = next;
	}
	norse_gods = nullptr;
}
