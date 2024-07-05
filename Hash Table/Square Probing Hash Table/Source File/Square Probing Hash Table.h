#include "DSMUtility.h"
#include <vector>
#include <string>
#include <string.h>

#pragma once
#ifndef __SQUAREPROBINGHUSHTABLE__HPP__
#define __SQUAREPROBINGHUSHTABLE__HPP__

namespace DSM {


template <typename Type>
struct Hash
{
	size_t operator()(const Type& key) { return 0; }
};

template <>
struct Hash<const char*>
{
	size_t operator()(const char* const& key, const size_t& size) const
	{
		const char* pos = key;
		size_t hashValue;
		for (hashValue = 0; *pos != '\0'; hashValue = (hashValue << 5) + *pos++);
		return hashValue % size;
	}
};

template <>
struct Hash<std::string>
{
	size_t operator()(const std::string & key, const size_t& size) const
	{
		std::string str = key;
		size_t hashValue = 0;
		for (auto& c: str) {
			hashValue = (hashValue << 5) + c;
		}
		return hashValue % size;
	}
};



template <typename Type>
struct HashEntry
{
	enum KindOfEntry {
		Legitimate, Empty, Delete
	};

	HashEntry() = default;
	HashEntry(const Type& key, const KindOfEntry& info);

	Type m_Key;
	KindOfEntry m_Info = KindOfEntry::Empty;
};

template <typename T>
HashEntry<T>::HashEntry(const T& key, const KindOfEntry& info)
	:m_Key(key), m_Info(info) {}


template <typename Type>
class HashTblSP
{
public:
	using HashEntry = HashEntry<Type>;
	HashTblSP(const size_t& capacity);
	HashEntry& Find(const Type& key);
	void Insert(const Type& key);
	bool Delete(const Type& key);

private:
	std::vector<HashEntry> m_HashTable;
};

template <typename T>
HashTblSP<T>::HashTblSP(const size_t& capacity)
{
	m_HashTable.resize(NextPrime(capacity));
}

template <typename T>
HashEntry<T>& HashTblSP<T>::Find(const T& key)
{
	Hash<T> Hash;
	size_t pos = Hash(key,m_HashTable.size());
	size_t collisionNum = 1;
	// 因为插入元素起冲突时会绕过某些单元，若是该单元被真正删除，而不是懒惰删除，查找该元素时会返回该单元，使得本应该成功的查找失败
	for (; m_HashTable[pos].m_Info != HashEntry::KindOfEntry::Empty &&
		m_HashTable[pos].m_Key != key; ++collisionNum) {
		pos += (collisionNum << 1) - 1;
		if (pos >= m_HashTable.size()) {
			pos -= m_HashTable.size();
		}
	}

	return m_HashTable[pos];
}


template <typename T>
void HashTblSP<T>::Insert(const T& key)
{
	HashEntry& data = Find(key);
	if (data.m_Info != HashEntry::KindOfEntry::Legitimate) {
		data.m_Key = key;
		data.m_Info = HashEntry::KindOfEntry::Legitimate;
	}
}


template <typename T>
bool HashTblSP<T>::Delete(const T& key)
{
	HashEntry& data = Find(key);
	if (data.m_Info == HashEntry::KindOfEntry::Legitimate) {
		data.m_Info = HashEntry::KindOfEntry::Delete;
		return true;
	}
	return false;
}



}

#endif // !__SQUAREPROBINGHUSHTABLE__HPP__
