/*
 * Skiplist implementation based on the paper
 * 'A Skip List Cookbook' written by William Pugh
 * found at 'https://api.drum.lib.umd.edu/server/api/core/bitstreams/17176ef8-8330-4a6c-8b75-4cd18c570bec/content'
 *
 */
#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include "Random.hpp"

#include <cstddef>
#include <vector>
#include <utility>
#include <memory>
#include <cassert>

template <typename Key, typename T>
struct Node
{
	using value_type = std::pair<const Key, T>;

	Node(std::size_t level) : forward(level, nullptr) {}
	Node(std::size_t level, const Key& k, const T& v) :
		forward(level, nullptr),
		pointer{std::make_shared<value_type>(k, v)}
	{}

	bool nil() const { return pointer.get() == nullptr; }

	value_type& pair() { return *pointer; }
	const value_type& pair() const { return *pointer; }

	const Key& key() const { return pair().first; }
	T& value() { return pair().second; }
	const T& value() const { return pair().second; }

	std::vector<Node*> forward;
	std::shared_ptr<value_type> pointer;
};

template <typename Key, typename T>
class SkiplistIterator;

template <typename Key, typename T>
class SkiplistConstIterator;

template <typename Key, typename T>
class Skiplist
{
	friend class SkiplistIterator<Key, T>;
	friend class SkiplistConstIterator<Key, T>;
public:
	Skiplist(std::size_t max_lvl = 16) : max_level{max_lvl}
	{
		assert(max_lvl > 0);
	}
	~Skiplist()
	{
		while (header)
		{
			Node<Key, T>* next = header->forward[0];
			delete header;
			header = next;
		}
	}

	SkiplistIterator<Key, T> begin()
	{
		return SkiplistIterator<Key, T>{header->forward[0]};
	}
	SkiplistConstIterator<Key, T> begin() const
	{
		return SkiplistConstIterator<Key, T>{header->forward[0]};
	}
	SkiplistConstIterator<Key, T> cbegin() const
	{
		return SkiplistConstIterator<Key, T>{header->forward[0]};
	}
	SkiplistIterator<Key, T> end()
	{
		return SkiplistIterator<Key, T>{nullptr};
	}
	SkiplistConstIterator<Key, T> end() const
	{
		return SkiplistConstIterator<Key, T>{nullptr};
	}
	SkiplistConstIterator<Key, T> cend() const
	{
		return SkiplistConstIterator<Key, T>{nullptr};
	}

	Node<Key, T>* search(const Key& search_key)
	{
		Node<Key, T>* x = header;
		for (std::size_t i = level; i > 1; --i)
		{
			while (x->forward[i - 1] && x->forward[i - 1]->key() < search_key)
			{
				x = x->forward[i - 1];
			}
		}
		x = x->forward[0];
		if (x && x->key() == search_key)
		{
			return x;
		}
		return nullptr;
	}

	void insert(const Key& search_key, const T& new_value)
	{
		std::vector<Node<Key, T>*> update(max_level, nullptr);
		Node<Key, T>* x = header;
		for (std::size_t i = level; i >= 1; --i)
		{
			while (x->forward[i - 1] && x->forward[i - 1]->key() < search_key)
			{
				x = x->forward[i - 1];
			}
			update[i - 1] = x;
		}
		x = x->forward[0];
		if (x && x->key() == search_key)
		{
			x->value() = new_value;
		}
		else
		{
			std::size_t new_level = random_level();
			if (new_level > level)
			{
				for (std::size_t i = level + 1; i <= new_level; ++i)
				{
					update[i - 1] = header;
				}
				level = new_level;
			}
			x = new Node<Key, T>{new_level, search_key, new_value};
			for (std::size_t i = 1; i <= new_level; ++i)
			{
				x->forward[i - 1] = update[i - 1]->forward[i - 1];
				update[i - 1]->forward[i - 1] = x;
			}
		}
	}

	void erase(const Key& search_key)
	{
		std::vector<Node<Key, T>*> update(max_level, nullptr);
		Node<Key, T>* x = header;
		for (std::size_t i = level; i >= 1; --i)
		{
			while (x->forward[i - 1] && x->forward[i - 1]->key() < search_key)
			{
				x = x->forward[i - 1];
			}
			update[i - 1] = x;
		}
		x = x->forward[0];
		if (x && x->key() == search_key)
		{
			for (std::size_t i = 1; i <= level; ++i)
			{
				if (update[i - 1]->forward[i - 1] != x)
				{
					break;
				}
				update[i - 1]->forward[i - 1] = x->forward[i - 1];
			}
			delete x;
			while (level > 1 && header->forward[level] == nullptr)
			{
				--level;
			}
		}
	}
private:
	std::size_t random_level()
	{
		std::size_t lvl = 1;
		while (random_bool() && lvl < max_level)
			++lvl;
		return lvl;
	}
private:
	std::size_t level = 1;
	std::size_t max_level;
	Node<Key, T>* header = new Node<Key, T>{max_level};
};

template <typename Key, typename T>
class SkiplistIterator
{
	friend class Skiplist<Key, T>;
public:
	SkiplistIterator& operator++()
	{
		curr = curr->forward[0];
		return *this;
	}
	SkiplistIterator operator++(int)
	{
		SkiplistIterator old = *this;
		++*this;
		return old;
	}
	typename Node<Key, T>::value_type& operator*() const
	{
		return curr->pair();
	}
	friend bool operator==(const SkiplistIterator& lhs, const SkiplistIterator& rhs)
	{
		return lhs.curr == rhs.curr;
	}
	friend bool operator!=(const SkiplistIterator& lhs, const SkiplistIterator& rhs)
	{
		return !(lhs == rhs);
	}
private:
	SkiplistIterator(Node<Key, T>* p) : curr{p} {}
private:
	Node<Key, T>* curr;
};

template <typename Key, typename T>
class SkiplistConstIterator
{
	friend class Skiplist<Key, T>;
public:
	SkiplistConstIterator& operator++()
	{
		curr = curr->forward[0];
		return *this;
	}
	SkiplistConstIterator operator++(int)
	{
		SkiplistConstIterator old = *this;
		++*this;
		return old;
	}
	const typename Node<Key, T>::value_type& operator*() const
	{
		return curr->pair();
	}
	friend bool operator==(const SkiplistConstIterator& lhs, const SkiplistConstIterator& rhs)
	{
		return lhs.curr == rhs.curr;
	}
	friend bool operator!=(const SkiplistConstIterator& lhs, const SkiplistConstIterator& rhs)
	{
		return !(lhs == rhs);
	}
private:
	SkiplistConstIterator(Node<Key, T>* p) : curr{p} {}
private:
	Node<Key, T>* curr;
};

#endif
