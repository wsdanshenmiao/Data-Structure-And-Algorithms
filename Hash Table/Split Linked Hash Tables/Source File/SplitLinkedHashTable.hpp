#ifndef __SPLITLINKEDHASHTABLE__HPP__
#define __SPLITLINKEDHASHTABLE__HPP__

#include <list>
#include <vector>
#include "allocator.hpp"
#include "DSMUtility.h"

namespace DSM {


// 分离式链接散列表
class HashTblSL
{
public:
	HashTblSL(const std::size_t& size);

	void DestoryTable();
    std::list<const char*>::iterator Find(const char* key) const;
    std::list<const char*>::iterator Find(const char* key, std::list<const char*>& list) const;
	void Insert(const char* key);
    void Delete(const char* key);

private:
    std::size_t Hash(const char* key) const; // 哈希函数
    std::list<const char*>::iterator _Find(const char* key, std::list<const char*>& list) const;


private:
    std::vector<std::list<const char*>> m_HashTable;
};

std::size_t HashTblSL::Hash(const char* key) const
{
    const char* pos = key;
    size_t hashValue = 0;
    for (; *pos != '\0'; hashValue = (hashValue << 5) + *pos++);
    return hashValue % m_HashTable.size();
}

HashTblSL::HashTblSL(const std::size_t& size)
{
    // 将散列表的大小设置为质数
    m_HashTable.resize(NextPrime(size));
}

std::list<const char*>::iterator HashTblSL::_Find(const char* key, std::list<const char*>& list) const
{
    for (auto it = list.begin(); it != list.end(); it++) {
        if (!std::strcmp(key, *it)) {
            return it;
        }
    }
    return list.end();  // 查找失败返回end()
}
std::list<const char*>::iterator HashTblSL::Find(const char* key) const
{
    auto list = m_HashTable[Hash(key)];
    return _Find(key, list);
}
std::list<const char*>::iterator HashTblSL::Find(const char* key, std::list<const char*>& list) const
{
    return _Find(key, list);
}

void HashTblSL::Insert(const char* key)
{
    auto& list = m_HashTable[Hash(key)];
    auto it = Find(key, list);
    if (it == list.end()) { // 没有重复的元素
        list.push_front(key);
    }
}

void HashTblSL::Delete(const char* key)
{
    auto& list = m_HashTable[Hash(key)];
    auto it = Find(key, list);
    if (it != list.end()) {
        list.erase(it);
    }
}


}


#endif // !__SPLITLINKEDHASHTABLE__HPP__
