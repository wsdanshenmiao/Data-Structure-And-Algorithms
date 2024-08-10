#pragma once
#ifndef __HEAP__HPP__
#define __HEAP__HPP__

#include <memory>
#include "allocator.hpp"

namespace DSM {

template <typename Type>
class Heap
{
public:
	Heap(const Type& minValue);
	Heap(const Type& minValue, const size_t& capacity);
	Heap(const Heap& other);
	~Heap();

	Heap& operator=(const Heap& other);

	constexpr bool IsEmpty() const;
	constexpr size_t Size() const;
	void Insert(const Type& value);
	void DeleteMin();
	Type& FindMin();
	void MakeEmpty();
	void Destory();
	void Merge(const Heap& other);

private:
	size_t m_Capacity;
	size_t m_Size;
	Type* m_Data;
};


template <typename T>
Heap<T>::Heap(const T& minValue)
{
	DSM::allocator<T> allo;
	m_Capacity = 0;
	m_Size = 0;
	m_Data = allo.allocate(1);
	allo.construct(m_Data, minValue);
}


template <typename T>
Heap<T>::Heap(const T& minValue, const size_t& capacity)
	:m_Capacity(capacity)
{
	DSM::allocator<T> allo;
	m_Size = capacity + 1;
	m_Data = allo.allocate(m_Size < 0 ? 0 : m_Size);
	m_Size = 0;
	allo.construct(m_Data, minValue);
}

template <typename T>
Heap<T>::Heap(const Heap& other)
	:m_Capacity(other.m_Capacity), m_Size(other.m_Size)
{
	DSM::allocator<T> allo;
	m_Data = allo.allocate(other.m_Capacity + 1);
	memcpy_s(m_Data, sizeof(other.m_Data), other.m_Data, sizeof(other.m_Data));
}

template <typename T>
Heap<T>::~Heap()
{
	DSM::allocator<T> allo;
	Destory();
	allo.destroy(m_Data);
	allo.deallocate(m_Data, 1);
	m_Data = nullptr;
}


template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other)
{
	DSM::allocator<T> allo;
	Destory();
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_Data = allo.allocate(other.m_Capacity + 1);
	memcpy_s(m_Data, sizeof(other.m_Data), other.m_Data, sizeof(other.m_Data));
	return *this;
}

template <typename T>
constexpr size_t Heap<T>::Size() const
{
	return m_Size;
}

// 判断堆是否为空
template <typename T>
constexpr bool Heap<T>::IsEmpty() const
{
	return m_Size == 0;
}

// 析构元素清空堆，但不释放内存
template <typename T>
void Heap<T>::MakeEmpty()
{
	DSM::allocator<T> allo;
	if (!IsEmpty()) {
		for (size_t i = 1; i < m_Size; i++) {
			allo.destroy(m_Data + i);
		}
	}
	m_Size = 0;
}

// 清空堆并释放内存，将堆置空,保留占位值
template <typename T>
void Heap<T>::Destory()
{
	DSM::allocator<T> allo;
	MakeEmpty();
	T* tmp = allo.allocate(1);
	allo.construct(tmp, m_Data[0]);
	allo.deallocate(m_Data, m_Capacity + 1);
	m_Capacity = 0;
	m_Data = tmp;
	tmp = nullptr;
}

template<typename T>
inline void Heap<T>::Merge(const Heap& other)
{
	for (size_t i = 1; i <= other.Size(); ++i) {
		Insert(other.m_Data[i]);
	}
}


template <typename T>
void Heap<T>::Insert(const T& value)
{
	// 动态扩展
	size_t i = ++m_Size;
	if (m_Size > m_Capacity) {
		DSM::allocator<T> allo;
		size_t capacity = m_Capacity ? (m_Capacity << 1) : 1;
		T* tmp = allo.allocate(capacity + 1);
		memcpy_s(tmp, sizeof(T) * m_Size, m_Data, sizeof(T) * m_Size);
		MakeEmpty();
		allo.deallocate(m_Data, m_Capacity + 1);
		m_Data = tmp;
		tmp = nullptr;
		m_Size = i;
		m_Capacity = capacity;
	}

	for (; m_Data[i >> 1] > value; i >>= 1) {
		m_Data[i] = m_Data[i >> 1];
	}
	m_Data[i] = value;
}

template <typename T>
T& Heap<T>::FindMin()
{
	if (!IsEmpty()) {
		return m_Data[1];
	}
	else {
		return m_Data[0];
	}
}

template <typename T>
void Heap<T>::DeleteMin()
{
	if (IsEmpty()) {
		return;
	}
	for (size_t i = 1, child; i << 1 <= m_Size; i = child) {
		child = i << 1;
		if (child + 1 < m_Size && m_Data[child] > m_Data[child + 1]) {
			++child;
		}
		m_Data[i] = m_Data[child];
	}
	--m_Size;
}






}


#endif // !__HEAP__HPP__
