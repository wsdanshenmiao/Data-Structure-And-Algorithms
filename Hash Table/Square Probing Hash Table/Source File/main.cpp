#include <iostream>
#include "Square Probing Hash Table.h"

int main()
{
	DSM::HashTblSP<const char*> hashTable(10);
	hashTable.Insert("Code");
	hashTable.Insert("CL");
	hashTable.Insert("LB");
	hashTable.Insert("AIR");
	hashTable.Insert("JO");
	hashTable.Insert("AB");
	DSM::HashEntry<const char*>& entry = hashTable.Find("CL");
	std::cout << entry.m_Key;
	hashTable.Delete("Code");
	hashTable.Delete("CL");
	hashTable.Delete("LB");
	hashTable.Delete("AIR");
	hashTable.Delete("JO");
	hashTable.Delete("AB");
	entry = hashTable.Find("CL");
	std::cout << entry.m_Key;

}