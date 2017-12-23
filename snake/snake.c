// snake.cpp: 定义控制台应用程序的入口点。
//

#include "list.h"
#include "envir.h"
#include "snaevent.h"



int main()
{
	initHandle();
	initData();
	createFirstPage();
	createMap();
	drawSnake();
	createDrug();
	while (1)
	{
		createFood();
		changeDirection();
		switch (eatFood())
		{
		case yes:
			addHead();
			break;
		default:
			addHead();
			deleteTail();
			break;
		}
		if (isSnakeDie() == yes)
		{
			break;
		}
		Sleep(200);
	}
	gameOver();
	system("pause");
}

