#include "QueueLinkedList.h"
#include <stdio.h>

int main()
{
	Queue* queue = L_CreateQueue();
	printf("%d", L_IsEmpty(queue));
	return 0;
}