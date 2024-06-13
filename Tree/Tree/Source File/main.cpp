#include <iostream>
#include "Tree.hpp"
#include <random>

int main()
{
	DSM::TreeNode<int> node(0);
	DSM::Tree<int> tree;
	std::default_random_engine e;
	std::uniform_int_distribution<int> dist(0,100);

	for (int i = 0; i < 100; ++i) {
		tree.Insert(dist(e));
	}
	for (int i = 0; i < 100; ++i) {
		tree.Delete(dist(e));
	}
	//tree.Insert(4);
	//tree.Insert(1);
	//tree.Insert(9);
	//tree.Insert(-1);
	//tree.Insert(3);
	//tree.Insert(7);
	//tree.Insert(11);
	//tree.Insert(6);

	//tree.Delete(-1);
	//tree.Delete(1);
	//tree.Delete(3);
	//tree.Delete(4);
}