#include "data.h"

void initData()
{
	currentDirection = up;
	hasFood = no;
	snake *first = (snake*)malloc(sizeof(snake));
	snake *second = (snake*)malloc(sizeof(snake));
	snake *third = (snake*)malloc(sizeof(snake));
	first->coord.X = 6;
	first->coord.Y = 6;
	second->coord.X = 6;
	second->coord.Y = 7;
	third->coord.X = 6;
	third->coord.Y = 8;
	first->pre = NULL;
	first->next = second;
	second->pre = first;
	second->next = third;
	third->next = NULL;
	third->pre = second;
	headPointer = first;
	tailPointer = third;
}

void initHandle()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(handle, &cci);
}