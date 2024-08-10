#include <iostream>
#include "LeftHeap.hpp"
#include <random>
#include <queue>

// 层次打印一棵树
template <typename T>
void PrintHeap(DSM::HeapNode<T>* node)
{
	int num = 1; // 每一层的个数
	int nextNum = 2; // 下一层的个数
	int trans = 1; // 记录何时换行
	std::queue<DSM::HeapNode<T>*> queue;
	queue.push(node);
	for (; !queue.empty();) {
		DSM::HeapNode<T>* tmp = queue.front();
		std::cout << tmp->m_Data << " ";
		queue.pop();
		if (tmp->m_Left) {
			queue.push(tmp->m_Left);
		}
		else {
			nextNum--;
		}
		if (tmp->m_Right) {
			queue.push(tmp->m_Right);
		}
		else {
			nextNum--;
		}
		trans--;
		if (trans == 0) {
			num = nextNum;
			trans = nextNum;
			nextNum <<= 1;
			std::cout << std::endl;
		}
	}
}

int main()
{
	std::random_device rd;
	std::mt19937 randEngine(rd());
	std::uniform_int_distribution<int> range(0, 1000);

	DSM::LeftHeap<int> heap;
	for (size_t i = 0; i < 20; ++i) {
		heap.Insert(range(rd));
	}
	PrintHeap(heap.GetRoot());
	DSM::LeftHeap<int> heap1;
	for (size_t i = 0; i < 20; ++i) {
		heap1.Insert(range(rd));
	}
	PrintHeap(heap1.GetRoot());
	heap.Merge(heap1);
	PrintHeap(heap.GetRoot());
	for (size_t i = 0; i < 10; ++i) {
		heap.DeleteMin();
	}
	PrintHeap(heap.GetRoot());
	for (; heap.GetRoot();) {
		heap.DeleteMin();
	}
}