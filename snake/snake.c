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
	initScene();
	while (1)
	{
		if (isSnakeDie() == yes)
		{
			break;
		}
		createFood();
		createAmaGrass();
		changeDirection();
		switch (eat())
		{
		case tFood:
			addHead();
			break;
		case tDrug:
			deleteTail();
			deleteTail();
			deleteTail();
		case tNull:default:
			addHead();
			deleteTail();
			break;
		}
		Sleep(200);
	}
	gameOver();
	system("pause");
}

