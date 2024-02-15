#ifndef __STRACKWITHLINKEDLIST__H__
#define __STRACKWITHLINKEDLIST__H__

#include <stdbool.h>

typedef struct Node
{
	int m_Data;
	struct Node* m_Next;
}Node;
bool IsEmpty(Node* stack);	//判断栈是否为空
Node* CreateStack();	//创建一个栈
void Push(int data, Node* stack);
void Pop(Node* stack);
void MakeEmpty(Node* stack);
int Top(Node* stack);
Node* DisposeStack(Node* stack);

#endif // !__STRACKWITHLINKEDLIST__H__

