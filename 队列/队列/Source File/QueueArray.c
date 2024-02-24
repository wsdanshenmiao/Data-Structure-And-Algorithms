//用循环数组实现队列
#include "QueueArray.h"

//队尾和队头循环
inline size_t A_Circulation(size_t position, QueueArray* queue)
{
	if (++position == queue->m_Capacity) {
		position = 0;
	}
	return position;
}

//判断队列是否为空
inline bool A_IsEmpty(QueueArray* const queue)
{
	return queue->m_Size == 0;
}

//判断队列是否为满
inline bool A_IsFull(QueueArray* const queue)
{
	return queue->m_Size == queue->m_Capacity;
}

//创建一个队列
QueueArray* A_CreateQueue(const size_t capacity)
{
	QueueArray* queue = (QueueArray*)malloc(sizeof(QueueArray));
	if (!queue) {
		return NULL;
	}
	queue->m_Array = (int*)malloc(sizeof(int) * capacity);
	if (!queue) {
		return NULL;
	}
	queue->m_Capacity = capacity;
	queue->m_Size = 0;
	queue->m_Front = 1;
	queue->m_Rear = 0;
	return queue;
}

//入队
void A_Enqueue(int data, QueueArray* queue)
{
	assert(!A_IsFull(queue));
	queue->m_Rear = A_Circulation(queue->m_Rear, queue);
	queue->m_Array[queue->m_Rear] = data;
	queue->m_Size++;
}

//出队
void A_Dequeue(QueueArray* queue)
{
	assert(!A_IsEmpty(queue));
	queue->m_Front = A_Circulation(queue->m_Front, queue);
	queue->m_Size--;
}

//返回队头
int A_Front(QueueArray* queue)
{
	assert(!A_IsEmpty(queue));
	return queue->m_Array[queue->m_Front];
}

//返回对头并出队
int A_FrontAndDequeue(QueueArray* queue)
{
	assert(!A_IsEmpty(queue));
	int data = queue->m_Array[queue->m_Front];
	queue->m_Front = A_Circulation(queue->m_Front, queue);
	queue->m_Size--;
	return data;
}

//清空队列
void A_MakeEmpty(QueueArray* queue)
{
	queue->m_Front = 1;
	queue->m_Rear = 0;
	queue->m_Size = 0;
}

//删除队列
QueueArray* A_DisposeQueue(QueueArray* queue)
{
	free(queue->m_Array);
	free(queue);
	queue = NULL;
	return queue;
}