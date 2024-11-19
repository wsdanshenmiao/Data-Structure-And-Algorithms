#ifndef __QUEUEARRAY__H__
#define __QUEUEARRAY__H__

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct QueueArray
{
	size_t m_Capacity;	//����
	size_t m_Size;	//Ԫ�ظ���
	size_t m_Front;	//��ͷ
	size_t m_Rear;	//��β
	int* m_Array;	//����
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

