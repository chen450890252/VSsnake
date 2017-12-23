#include "data.h"

void initData()
{
	currentDirection = up;
	hasFood = no;
	hasAmaGrass = no;
	score = 0;
	addRule = 1;
	subRule = 10;
	scorePos.X = 68;
	scorePos.Y = 20;
	top.X = 69;
	top.Y = 2;
	drugCount = 0;
	snakeCount = 4;
	grassRule = 0;
	amaGrassPos.X = 0;
	amaGrassPos.Y = 0;
	snake *first = (snake*)malloc(sizeof(snake));
	snake *second = (snake*)malloc(sizeof(snake));
	snake *third = (snake*)malloc(sizeof(snake));
	snake *fourth = (snake*)malloc(sizeof(snake));
	first->coord.X = 6;
	first->coord.Y = 6;
	second->coord.X = 6;
	second->coord.Y = 7;
	third->coord.X = 6;
	third->coord.Y = 8;
	fourth->coord.X = 6;
	fourth->coord.Y = 9;
	first->pre = NULL;
	first->next = second;
	second->pre = first;
	second->next = third;
	third->next = fourth;
	third->pre = second;
	fourth->next = NULL;
	fourth->pre = third;
	headPointer = first;
	tailPointer = fourth;
}

void initHandle()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(handle, &cci);
}