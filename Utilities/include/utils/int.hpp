#ifndef UTILS_INT_HEADER_INCLUDED
#define UTILS_INT_HEADER_INCLUDED

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>

namespace utils
{
	static std::default_random_engine generator(time(0));

	static int random(int min, int max, int seed) {
		generator.seed(seed);
		std::uniform_int_distribution<int> dist(min, max);
		return dist(generator);
	}
	
	static int random(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(generator);
	}

	static int random(int max) {
		return random(0, max);
	}

	static bool isnumeric(const std::string& s)
	{
		return !s.empty() && std::find_if(s.begin(),
			s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
	}
	
}

#endif