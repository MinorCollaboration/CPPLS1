#ifndef UTILS_INT_HEADER_INCLUDED
#define UTILS_INT_HEADER_INCLUDED

#include <iostream>
#include <random>
#include <ctime>

namespace utils
{
	static int random(int min, int max, int seed) {
		std::default_random_engine generator;
		generator.seed(seed);
		std::uniform_int_distribution<int> dist(min, max);
		return dist(generator);
	}

	static int random(int max) {
		return random(0, max, time(0));
	}

	static int random(int min, int max) {
		return random(min, max, time(0));
	}
}

#endif