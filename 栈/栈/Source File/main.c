#include "StackWithLinkedList.h"
#include "StackWithArray.h"
#include <stdio.h>

#define MALLOC(T) ((T*)malloc(sizeof(T)))

int main()
{
	Array* stack = a_CreateStack(10);
	a_IsEmpty(stack);
	for (int i = 0; i < 10; i++) {
		a_Push(i, stack);
	}
	a_IsFull(stack);
	a_Pop(stack);
	a_Pop(stack);
	printf("%d", a_TopAndPop(stack));
	printf("%d", a_Top(stack));
	a_MakeEmpty(stack);
	stack = a_DisposeStack(stack);
	
	return 0;
}

//int main()
//{
//	Node* stack = l_CreateStack();
//	l_IsEmpty(stack);
//	l_Push(4, stack);
//	l_Push(5, stack);
//	l_Push(6, stack);
//	l_Push(7, stack);
//	l_IsEmpty(stack);
//	l_Pop(stack);
//	l_Top(stack);
//	l_MakeEmpty(stack);
//	l_Push(4, stack);
//	l_Push(5, stack);
//	stack = l_DisposeStack(stack);
//
//	return 0;
//}