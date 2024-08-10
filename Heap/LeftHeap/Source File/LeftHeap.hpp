#pragma once
#ifndef __LEFTHEAP__HPP__
#define __LEFTHEAP__HPP__

#include "allocator.hpp"

namespace DSM {

// 堆的节点
template <typename Type>
struct HeapNode {
	HeapNode() : m_Left(nullptr), m_Right(nullptr), m_Npl(0) {}
	HeapNode(const Type& data, HeapNode* left = nullptr, HeapNode* right = nullptr)
		:m_Data(data), m_Left(left), m_Right(right) {
		m_Npl = __min(GetNpl(m_Left), GetNpl(m_Right)) + 1;
	}
	HeapNode(const HeapNode& other) = default;

	HeapNode& operator=(const HeapNode& other) = default;

	static int GetNpl(const HeapNode* node) {
		if (node == nullptr) {
			return -1;
		}
		else {
			return node->m_Npl;
		}
	}

	HeapNode* m_Left;
	HeapNode* m_Right;
	int m_Npl;
	Type m_Data;
};


// 左式堆
template <typename Type>
class LeftHeap
{
public:
	using HeapNode = HeapNode<Type>;

	LeftHeap() : m_Head(nullptr) {}
	LeftHeap(const LeftHeap& other) = default;
	~LeftHeap();

	LeftHeap& operator=(const LeftHeap& other) = default;

	static void SwapChild(HeapNode* node);

	bool IsEmpty() const;
	HeapNode* GetRoot() const;
	void Merge(const LeftHeap& other);
	void Insert(const Type& data);
	void DeleteMin();

private:
	HeapNode* _Merge(HeapNode* H1, HeapNode* H2);
	HeapNode* _Insert(const Type& data);

private:
	HeapNode* m_Head;
};

template<typename Type>
bool LeftHeap<Type>::IsEmpty() const
{
	return m_Head == nullptr;
}

template<typename Type>
HeapNode<Type>* LeftHeap<Type>::GetRoot() const
{
	return m_Head;
}

template<typename Type>
void LeftHeap<Type>::Merge(const LeftHeap& other)
{
	if (m_Head == nullptr) {
		m_Head = other.GetRoot();
	}
	if (other.GetRoot() == nullptr) {
		return;
	}

	m_Head = _Merge(m_Head, other.GetRoot());
}

template<typename Type>
void LeftHeap<Type>::Insert(const Type& data)
{
	HeapNode* newNode = new HeapNode(data);
	m_Head = _Merge(m_Head, newNode);
}

template<typename Type>
void LeftHeap<Type>::DeleteMin()
{
	if (IsEmpty()) {
		return;
	}
	DSM::allocator<Type> dAllo;
	DSM::allocator<HeapNode> nAllo;
	HeapNode* left, * right;
	left = m_Head->m_Left;
	right = m_Head->m_Right;
	dAllo.destroy(&m_Head->m_Data);
	nAllo.destroy(m_Head);
	nAllo.deallocate(m_Head, 1);
	m_Head = _Merge(left, right);
}

template<typename Type>
inline LeftHeap<Type>::~LeftHeap()
{
	while (m_Head) {
		DeleteMin();
	}
}

template<typename Type>
void LeftHeap<Type>::SwapChild(HeapNode* node)
{
	HeapNode* tmp = node->m_Left;
	node->m_Left = node->m_Right;
	node->m_Right = tmp;
}





template<typename Type>
HeapNode<Type>* LeftHeap<Type>::_Merge(HeapNode* H1, HeapNode* H2)
{
	if (H1 == nullptr) {
		return H2;
	}
	if (H2 == nullptr) {
		return H1;
	}

	// 确保H1小于H2
	if (H1->m_Data > H2->m_Data) {
		return _Merge(H2, H1);
	}

	if (H1->m_Left == nullptr) {	// 右子树必为空
		H1->m_Left = H2;
	}
	else {
		H1->m_Right = _Merge(H1->m_Right, H2);
		if (H1->m_Left->m_Npl < H1->m_Right->m_Npl) {
			SwapChild(H1);
		}
		H1->m_Npl = H1->m_Right->m_Npl + 1;
	}

	return H1;
}

template<typename Type>
HeapNode<Type>* LeftHeap<Type>::_Insert(const Type& data)
{
	return nullptr;
}


}

#endif // !__LEFTHEAP__HPP__
