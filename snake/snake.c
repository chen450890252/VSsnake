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
	while (1)
	{
		initData();
		createFirstPage();
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
			Sleep(200);
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

