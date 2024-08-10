#include <iostream>
#include <random>
#include "Heap.hpp"


int main()
{
	std::random_device rd;
	std::mt19937 randEngine;
	randEngine.seed(rd());
	std::uniform_int_distribution<uint32_t> range(0, 10);

	DSM::Heap<size_t> heap(0);
	for (size_t i = 10; i > 0; --i) {
		heap.Insert(range(randEngine));
	}

	DSM::Heap<size_t> heap1(0);
	for (size_t i = 0; i < 10; ++i) {
		heap1.Insert(range(randEngine));
	}

	heap.Merge(heap1);

	for (size_t i = heap.Size(); i > 0; --i) {
		heap.DeleteMin();
	}
}