#ifndef __QUEUELINKEDLIST__H__
#define __QUEUELINKEDLIST__H__

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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

inline bool L_IsEmpty(const Queue* const queue);	//判断链表是否为空
Queue* L_CreateQueue();	//创建队列
void L_Enqueue(int data, Queue* queue);	//入队
void L_Dequeue(Queue* queue);	//出队
int L_Front(Queue* queue);	//返回队头
void L_MakeEmpty(Queue* queue);	//清空队列
int L_FrontAndDequeue(Queue* queue);	//返回队头并出队
Queue* L_DisposeQueue(Queue* queue);	//删除队列


#endif // !__QUEUELINKEDLIST__H__
