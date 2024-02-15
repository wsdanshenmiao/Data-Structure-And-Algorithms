#include "StackWithLinkedList.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))

int main()
{
	Node* stack = CreateStack();
	IsEmpty(stack);
	Push(4, stack);
	Push(5, stack);
	Push(6, stack);
	Push(7, stack);
	IsEmpty(stack);
	Pop(stack);
	Top(stack);
	MakeEmpty(stack);
	Push(4, stack);
	Push(5, stack);
	stack = DisposeStack(stack);

	return 0;
}