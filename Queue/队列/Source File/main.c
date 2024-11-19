#include "QueueLinkedList.h"
#include <stdio.h>
#include "QueueArray.h"

int main()
{
	QueueArray* queue = A_CreateQueue(100);
	printf("%d", A_IsEmpty(queue));
	for (int i = 0; i < 100; i++) {
		A_Enqueue(i, queue);
	}
	printf("%d", A_IsFull(queue));
	printf("%d", A_IsEmpty(queue));
	for (int i = 0; i < 90; i++) {
		A_Dequeue(queue);
	}
	for (int i = 0; i < 60; i++) {
		A_Enqueue(i, queue);
	}
	for (int i = 0; i < 50; i++) {
		A_Dequeue(queue);
	}
	printf("%d", A_Front(queue));
	printf("%d", A_FrontAndDequeue(queue));
	printf("%d", A_Front(queue));
	A_MakeEmpty(queue);
	A_Enqueue(1, queue);
	queue = A_DisposeQueue(queue);

	return 0;
}

//int main()
//{
//	Queue* queue = L_CreateQueue();
//	printf("%d", L_IsEmpty(queue));
//	for (int i = 0; i < 5; i++) {
//		L_Enqueue(i, queue);
//	}
//	L_Dequeue(queue);
//	printf("%d", L_Front(queue));
//	L_MakeEmpty(queue);
//	for (int i = 0; i < 5; i++) {
//		L_Enqueue(i, queue);
//	}
//	queue = L_DisposeQueue(queue);
//
//	return 0;
//}