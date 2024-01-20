#pragma once
#include <random>

using randomGenerator = std::mt19937;
using intDistribution = std::uniform_int_distribution<>;
using realDistribution = std::uniform_real_distribution<>;
std::random_device randomDevice;
randomGenerator generator(randomDevice());

namespace bx {

	int getRandomNumber(int start, int end) {
		intDistribution distribution(start, end);
		return distribution(generator);
	}

	double getRandomNumber(double start, double end) {
		realDistribution distribution(start, end);
		return distribution(generator);
	}
}