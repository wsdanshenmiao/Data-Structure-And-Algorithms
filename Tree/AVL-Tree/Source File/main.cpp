#include <iostream>
#include <limits>
#include <random>
#include "AVLTree.hpp"

int main()
{
	DSM::AVLTree<size_t> tree;
	std::default_random_engine e;
	std::uniform_int_distribution<size_t> dist(0, 1000000);

	for (size_t i = 0; i < 1000000; ++i) {
		tree.Insert(dist(e));
	}
	
	//tree.Insert(8);
	//tree.Insert(6);
	//tree.Insert(3);
	//tree.Insert(7);
	//tree.Insert(1);
	//tree.Insert(0);
	//tree.Insert(4);
}