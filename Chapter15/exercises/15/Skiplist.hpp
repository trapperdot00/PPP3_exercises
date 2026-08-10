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
#include <optional>
#include <cassert>

template <typename Key, typename T>
struct Node
{
	using value_type = std::pair<const Key, T>;

	Node(std::size_t level) : forward(level, nullptr) {}
	Node(std::size_t level, Key k, T v) :
		forward(level, nullptr),
		opt{std::in_place, std::move(k), std::move(v)}
	{}

	bool is_nil() const { return !static_cast<bool>(opt); }

	value_type& pair() { return *opt; }
	const value_type& pair() const { return *opt; }
	const Key& key() const { return opt->first; }
	T& value() { return opt->second; }
	const T& value() const { return opt->second; }

	std::vector<Node*> forward;
	std::optional<value_type> opt;
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

	friend void swap(Skiplist& lhs, Skiplist& rhs) noexcept
	{
		using std::swap;
		swap(lhs.level, rhs.level);
		swap(lhs.max_level, rhs.max_level);
		swap(lhs.header, rhs.header);
	}

	Skiplist(const Skiplist& other) : max_level{other.max_level}
	{
		for (const auto& pair : other)
		{
			insert(pair.first, pair.second);
		}
	}

	Skiplist& operator=(Skiplist other)
	{
		swap(*this, other);
		return *this;
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

	bool contains(const Key& search_key) const
	{
		return search(search_key) != nullptr;
	}

	Node<Key, T>* search(const Key& search_key)
	{
		Node<Key, T>* x = header;
		for (std::size_t i = level; i >= 1; --i)
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
	const Node<Key, T>* search(const Key& search_key) const
	{
		return const_cast<Skiplist*>(this)->search(search_key);
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
			for (std::size_t i = 1; i < new_level + 1; ++i)
			{
				x->forward[i - 1] = update[i - 1]->forward[i - 1];
				update[i - 1]->forward[i - 1] = x;
			}
		}
	}

	bool erase(const Key& search_key)
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
			for (std::size_t i = 0; i < level; ++i)
			{
				if (update[i]->forward[i] != x)
				{
					break;
				}
				update[i]->forward[i] = x->forward[i];
			}
			delete x;
			while (level > 1 && header->forward[level - 1] == nullptr)
			{
				--level;
			}
			return true;
		}
		return false;
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
	typename Node<Key, T>::value_type* operator->() const
	{
		return &this->operator*();
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
	const typename Node<Key, T>::value_type* operator->() const
	{
		return &this->operator*();
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
