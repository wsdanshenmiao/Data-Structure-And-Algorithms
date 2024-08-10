#include <iostream>
#include "BinomialQueue.hpp"
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 randEngine(rd());
	std::uniform_int_distribution<int> range(0, 100000);

	DSM::BinomialQueue<int> binQueue;
	for (size_t i = 0; i < 100000; ++i) {
		binQueue.Insert(range(randEngine));
		std::cout << i << '\n';
	}
}