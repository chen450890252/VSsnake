// snake.cpp: 定义控制台应用程序的入口点。
//

#include "list.h"
#include "envir.h"
#include "snaevent.h"
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")



int main()
{

	initHandle();
	createFirstPage();
	while (1)
	{
		initData();
		initCoord();
		enterIntoFirstPage();
		scoreSort(file, filePath, topScore);
		Sleep(2000);
		while (1)
		{
			if (isSnakeDie() == yes)
			{
				break;
			}
			createFood();
			createAmaGrass();
			changeDirection();
			eat();
			faster();
			Sleep(speed);
		}
		char isAgian = gameOver();
		if (isAgian == yes)
		{
			continue;
		}
		else if (isAgian == no)
		{
			break;
		}
	}
}

