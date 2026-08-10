#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <chrono>

inline std::default_random_engine& get_random_engine()
{
	static std::default_random_engine engine(
		std::chrono::steady_clock::now().time_since_epoch().count()
	);
	return engine;
}

inline bool random_bool()
{
	return std::bernoulli_distribution{}(get_random_engine());
}

template <typename T>
inline T random_integer(T min, T max)
{
	return std::uniform_int_distribution<T>{min, max}(get_random_engine());
}

#endif
