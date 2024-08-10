#pragma once
#ifndef __BINOMIALQUEUE__HPP__
#define __BINOMIALQUEUE__HPP__

#include <vector>
#include <cstdlib>

namespace DSM {

// 二项队列的节点
template <typename Type>
struct BinNode
{
	BinNode() : m_LeftChild(nullptr), m_NextSibling(nullptr) {}
	BinNode(const Type& data, BinNode* leftChild = nullptr, BinNode* nextSibling = nullptr)
		:m_Data(data), m_LeftChild(leftChild), m_NextSibling(nextSibling) {}
	BinNode(const BinNode& other) = default;
	BinNode& operator=(const BinNode& other) = default;

	BinNode* m_LeftChild;
	BinNode* m_NextSibling;
	Type m_Data;
};


// 二项队列
template <typename Type>
class BinomialQueue
{
public:
	using BinNode = BinNode<Type>;

	BinomialQueue() = default;
	BinomialQueue(const Type& data);

	static BinNode* CombineTrees(BinNode* const T1, BinNode* const T2);

	bool IsEmpty() const;
	size_t Size() const;
	void Merge(const BinomialQueue& other);
	void Insert(const Type& data);

private:
	size_t m_Size;
	std::vector<BinNode*> m_Trees;
};

template<typename Type>
inline BinomialQueue<Type>::BinomialQueue(const Type& data)
	:m_Size(1) 
{
	BinNode* newNode = new BinNode(data);
	m_Trees.assign({ newNode });
}

template<typename Type>
inline bool BinomialQueue<Type>::IsEmpty() const
{
	return m_Size == 0;
}

template<typename Type>
inline size_t BinomialQueue<Type>::Size() const
{
	return m_Size;
}

/// <summary>
/// 合并两个二项队列
/// 
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <param name="other"></param> 被合并的树，合并后不会被清空
template<typename Type>
inline void BinomialQueue<Type>::Merge(const BinomialQueue& other)
{
	BinNode* T1, * T2, * carry;
	T1 = T2 = carry = nullptr;
	
	m_Size += other.m_Size;
	if (IsEmpty() || other.IsEmpty()) {
		return;
	}
	m_Trees.resize(static_cast<size_t>(log2(m_Size) + 1));

	for (size_t i = 0, j = 1; j < m_Size; ++i, j <<= 1) {
		T1 = m_Trees[i];
		T2 = i < other.m_Trees.size() ? other.m_Trees[i] : nullptr;

		switch (!!T1 + !!T2 * 2 + !!carry * 4) {
		case 0: 	// 都为空
		case 1: {	// T1
			break;
		}
		case 2: {	// T2
			m_Trees[i] = T2;
			break;
		}
		case 3: {	// T1, T2
			carry = CombineTrees(T1, T2);
			m_Trees[i] = nullptr;
			break;
		}
		case 4: {	// carry
			m_Trees[i] = carry;
			carry = nullptr;
			break;
		}
		case 5: {	// carry, T1
			carry = CombineTrees(carry, T1);
			m_Trees[i] = nullptr;
			break;
		}
		case 6: {	// carry,T2
			carry = CombineTrees(carry, T2);
			break;
		}
		case 7: {	// all
			m_Trees[i] = carry;
			carry = CombineTrees(T1, T2);
			break;
		}
		}
	}
}

template<typename Type>
inline void BinomialQueue<Type>::Insert(const Type& data)
{
	BinomialQueue newTree(data);
	Merge(newTree);
}





/// <summary>
/// 合并两个相同高度的树
/// 
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <param name="T1"></param>
/// <param name="T2"></param>
/// <returns></returns>	合并后新树的根节点
template<typename Type>
inline BinNode<Type>* BinomialQueue<Type>::CombineTrees(BinNode* const T1, BinNode* const T2)
{
	// 将根节点小的作为新的根节点
	if (T1->m_Data > T2->m_Data) {
		return CombineTrees(T2, T1);
	}
	T2->m_NextSibling = T1->m_LeftChild;
	T1->m_LeftChild = T2;
	return T1;
}








}
#endif // !__BINOMIALQUEUE__HPP__
