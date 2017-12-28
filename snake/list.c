#include "list.h"

void addHead(int color)
{
	snake *newHead = (snake*)malloc(sizeof(snake));
	snake *lastHead = headPointer;
	newHead->next = lastHead;
	newHead->pre = NULL;
	lastHead->pre = newHead;
	switch (currentDirection)
	{
	case up:
		newHead->coord.X = lastHead->coord.X;
		newHead->coord.Y = lastHead->coord.Y - 1;
		break;
	case down:
		newHead->coord.X = lastHead->coord.X;
		newHead->coord.Y = lastHead->coord.Y + 1;
		break;
	case left:
		newHead->coord.X = lastHead->coord.X - 2;
		newHead->coord.Y = lastHead->coord.Y;
		break;
	case right:
		newHead->coord.X = lastHead->coord.X + 2;
		newHead->coord.Y = lastHead->coord.Y;
		break;
	default:
		break;
	}
	SetConsoleCursorPosition(handle, newHead->coord);
	SetConsoleTextAttribute(handle, color);
	printf("¡ñ");
	SetConsoleTextAttribute(handle, 7);
	headPointer = newHead;
}

void deleteTail()
{
	SetConsoleCursorPosition(handle, tailPointer->coord);
	printf("  ");
	snake *temp = tailPointer;
	tailPointer = tailPointer->pre;
	tailPointer->next = NULL;
	free(temp);
}
