#include <chrono>
#include <random>

#include "Random.h"


double GetNextRand()
{
	const double minimum = 0.0, maximum = 1.0;

	// unsigned int seed(std::chrono::system_clock::now().time_since_epoch().count());
	static std::mt19937 rng(std::random_device{}());
	static std::uniform_real_distribution<double> dist(minimum, maximum);
	return dist(rng);
}