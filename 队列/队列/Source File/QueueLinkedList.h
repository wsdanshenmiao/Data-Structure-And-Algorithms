#ifndef __QUEUELINKEDLIST__H__
#define __QUEUELINKEDLIST__H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
	int m_Data;
	struct Node* m_Next;
}Node;
typedef struct Queue
{
	Node* m_Rear;	//队尾
	Node* m_Front;	//队首
	size_t m_Size;
}Queue;

bool L_IsEmpty(const Queue* const queue);	//判断链表是否为空
Queue* L_CreateQueue();	//创建队列
void L_Enqueue(int data, Queue* queue);	//入队


#endif // !__QUEUELINKEDLIST__H__
