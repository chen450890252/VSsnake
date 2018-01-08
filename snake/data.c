#include "data.h"

void initData()
{
	filePath = "scores.txt";
	file = NULL;
	currentDirection = up;
	hasFood = no;
	hasAmaGrass = no;
	score = 0;
	addRule = 1;
	subRule = 10;
	scorePos.X = 68;
	scorePos.Y = 20;
	drugCount = 0;
	snakeCount = 4;
	grassRule = 0;
	amaGrassPos.X = 0;
	amaGrassPos.Y = 0;
	count = 0;
	modeSelect = 1;
	new_game.X = 30;
	new_game.Y = 10;
	saved_mode.X = 30;
	saved_mode.Y = 13;
	top.X = 30;
	top.Y = 16;
	level = 3;
	obtCount = 0;
	for (int i = 0; i < 11; i++)
	{
		topScore[i] = 0;
	}
	for (int i = 0; i < 50; i++)
	{
		obtPos[i].X = 100;
		obtPos[i].Y = 100;
	}
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
