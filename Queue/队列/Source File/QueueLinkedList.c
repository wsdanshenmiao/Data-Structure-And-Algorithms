//������ʵ�ֶ���
#include "QueueLinkedList.h"

inline bool L_IsEmpty(const Queue* const queue)	//�ж������Ƿ�Ϊ��
{
	return queue->m_Front->m_Next == NULL;
}

Queue* L_CreateQueue()	//��������
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue) {
		return NULL;
	}
	queue->m_Front = (Node*)malloc(sizeof(Node));
	if (!queue->m_Rear) {
		return NULL;
	}
	queue->m_Front->m_Next = NULL;
	queue->m_Rear = queue->m_Front;
	queue->m_Size = 0;
	return queue;
}

void L_Enqueue(int data, Queue* queue)	//���
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (!tmp) {
		return;
	}
	tmp->m_Data = data;
	tmp->m_Next = queue->m_Rear->m_Next;
	queue->m_Rear->m_Next = tmp;
	queue->m_Rear = tmp;
	queue->m_Size++;
}

void L_Dequeue(Queue* queue)	//����
{
	assert(!L_IsEmpty(queue));
	Node* tmp = queue->m_Front->m_Next;
	queue->m_Front->m_Next = tmp->m_Next;
	free(tmp);
	tmp = NULL;
	queue->m_Size--;
}

int L_Front(Queue* queue)	//���ض�ͷ
{
	assert(!L_IsEmpty(queue));
	return queue->m_Front->m_Next->m_Data;
}

int L_FrontAndDequeue(Queue* queue)	//���ض�ͷ������
{
	assert(!L_IsEmpty(queue));
	Node* tmp = queue->m_Front->m_Next;
	int data = tmp->m_Data;
	queue->m_Front->m_Next = tmp->m_Next;
	free(tmp);
	tmp = NULL;
	queue->m_Size--;
	return data;
}

void L_MakeEmpty(Queue* queue)	//��ն���
{
	Node* position = queue->m_Front->m_Next;
	queue->m_Front->m_Next = NULL;
	while (position) {
		Node* tmp = position->m_Next;
		free(position);
		position = tmp;
	}
	queue->m_Rear = queue->m_Front;
	queue->m_Size = 0;
}

Queue* L_DisposeQueue(Queue* queue)	//ɾ������
{
	Node* position = queue->m_Front;
	queue->m_Rear = NULL;
	while (position) {
		Node* tmp = position->m_Next;
		free(position);
		position = tmp;
	}
	free(queue);
	queue = NULL;
	return queue;
}