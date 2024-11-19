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
	Node* m_Rear;	//��β
	Node* m_Front;	//����
	size_t m_Size;
}Queue;

inline bool L_IsEmpty(const Queue* const queue);	//�ж������Ƿ�Ϊ��
Queue* L_CreateQueue();	//��������
void L_Enqueue(int data, Queue* queue);	//���
void L_Dequeue(Queue* queue);	//����
int L_Front(Queue* queue);	//���ض�ͷ
void L_MakeEmpty(Queue* queue);	//��ն���
int L_FrontAndDequeue(Queue* queue);	//���ض�ͷ������
Queue* L_DisposeQueue(Queue* queue);	//ɾ������


#endif // !__QUEUELINKEDLIST__H__
