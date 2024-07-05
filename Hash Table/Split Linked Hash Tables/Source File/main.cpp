#include <iostream>
#include "SplitLinkedHashTable.hpp"
#include <memory>

int main()
{
	DSM::HashTblSL hash(10);
	hash.Insert("CLANNAD");
	hash.Insert("Code Geass");
	hash.Insert("AB");
	hash.Insert("LB");
	hash.Insert("AIR");
	hash.Insert("MADO");
	hash.Insert("HOMU");
	hash.Delete("AB");
	auto it = hash.Find("CLANNAD");
	auto it1 = hash.Find("Code Geass");
	std::cout << *it << std::endl;
	std::cout << *it1 << std::endl;
}