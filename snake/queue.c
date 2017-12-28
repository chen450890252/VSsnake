#include"queue.h"

node front(node headNode)
{
	return headNode;
}
void pop(node *headNode)
{
	if (headNode == NULL)
	{
		return;
	}
	else if (*headNode == NULL)
	{
		return;
	}
	else if ((*headNode)->next != NULL)
	{
		*headNode = (*headNode)->next;
	}
	else
	{
		*headNode = NULL;
	}
}
void push(node headNode, node newNode, node parent)
{
	if (headNode == NULL)
	{
		headNode = newNode;
		return;
	}
	node temp = headNode;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->pre = parent;
	newNode->next = NULL;
}