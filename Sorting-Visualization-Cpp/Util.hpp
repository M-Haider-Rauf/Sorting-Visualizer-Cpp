#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <random>

#include "Constants.hpp"

std::vector<unsigned> getRandomArray(size_t n)
{
	std::vector<unsigned> arr(n, 0);

	static std::default_random_engine randEng(std::random_device().operator()());
	std::uniform_int_distribution<unsigned> dist(MIN_DATA_RANGE, MAX_DATA_RANGE);

	for (size_t i = 0; i < n; ++i) {
		arr[i] = dist(randEng);
	}

	return arr;
}

#endif // !UTIL_HPP
