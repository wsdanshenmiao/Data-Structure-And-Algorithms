#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* p_Next;
}Node, * p_Node;
p_Node Creat_Node(p_Node p_Head);
void Traverse_Node(p_Node p_Head);

p_Node Creat_Node(p_Node p_Head)
{
	p_Node pre = NULL;
	p_Node new = (p_Node)malloc(sizeof(Node));	//创建一个节点
	if (NULL == new) {
		return NULL;
	}
	new->data = 1;
	for (; p_Head; pre = p_Head, p_Head = p_Head->p_Next);
	pre->p_Next = new;
	new->p_Next = NULL;
	return new;
}

void Traverse_Node(p_Node p_Head)
{
	for (p_Head = p_Head->p_Next; p_Head; p_Head = p_Head->p_Next) {
		printf("%d ", p_Head->data);
	}
	return;
}

int main()
{
	p_Node p_Head = (p_Node)malloc(sizeof(Node));	//头指针指向头节点
	if (NULL == p_Head) {
		return 0;
	}
	p_Head->p_Next = NULL;
	for (int i = 0; i < 9; i++) {
		Creat_Node(p_Head);
	}
	Traverse_Node(p_Head);
	return 0;
}