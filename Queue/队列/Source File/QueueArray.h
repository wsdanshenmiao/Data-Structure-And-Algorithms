#ifndef __QUEUEARRAY__H__
#define __QUEUEARRAY__H__

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct QueueArray
{
	size_t m_Capacity;	//容量
	size_t m_Size;	//元素个数
	size_t m_Front;	//对头
	size_t m_Rear;	//队尾
	int* m_Array;	//数组
}QueueArray;

inline bool A_IsEmpty(QueueArray* const queue);
inline bool A_IsFull(QueueArray* const queue);
QueueArray* A_CreateQueue(const size_t capacity);
void A_Enqueue(int data, QueueArray* queue);
void A_Dequeue(QueueArray* queue);
int A_Front(QueueArray* queue);
int A_FrontAndDequeue(QueueArray* queue);
void A_MakeEmpty(QueueArray* queue);
QueueArray* A_DisposeQueue(QueueArray* queue);


#endif // !__QUEUEARRAY__H__

