#include "ui.h"
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
HANDLE handle;

int main()
{
	//0是从主菜单开始，大于0是进入下一关
	int back_next = 1;
	int isAgain = 1;
	int speed = 200;
	initHandle(&handle);
	createFirstPage();
	while (isAgain)
	{
		speed = 200;
		initUIData();
		int back = 0;
		while (!back)
		{
			if (back_next == 1)
				back = selectMode();
			else
				back = 1;
		}
		initScene();
		initSnakeData();
		drawSnake(10);
		createObt();
		createDrug();
		createBomb();
		Sleep(2000);
		while (!isSnakeDie())
		{
			createFood();
			createAmaGrass();
			changeDirection();
			eat(speed);
			flashDrug();
			back_next = isWin();
			if (back_next != 0)
				break;
			changeSpeed(&speed);
			Sleep(speed);
		}
		if (back_next == 0)
		{
			back_next = 1;
			isAgain = gameOver();
		}
	}
}