// snake.cpp: 定义控制台应用程序的入口点。
//

#include "list.h"
#include "envir.h"
#include "snaevent.h"



int main()
{
	initHandle();
	createFirstPage();
	createMap();
	initData();
	drawSnake();
	while (1)
	{
		createFood();
		changeDirection();
		addHead();
		deleteTail();
		if (isSnakeDie() == yes)
		{
			break;
		}
		Sleep(300);
	}
	gameOver();
	system("pause");
}

