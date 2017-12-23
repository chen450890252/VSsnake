#include "envir.h"
#include <time.h>
void createFirstPage()
{
	printf("\n\n\n\t\t\t欢迎进入贪吃蛇世界\n");
	printf("\t\t      按↑↓←→控制蛇的方向\n");
	printf("\t\t\t 按空格键进入游戏\n\n\n");
	enterIntoGame();
}

void enterIntoGame()
{
	char isEnter;
	while (1)
	{
		isEnter = _getch();
		if (isEnter == ' ')  break;
	}
	system("cls");
}

void createMap()
{
	for (int i = 0; i < 26; i++)
	{
		if (i == 0 || i == 25)
		{
			for (int j = 0; j < 27; j++)
			{
				printf("■");
			}
		}
		else
		{
			for (int j = 0; j < 27; j++)
			{
				if (j == 0 || j == 26)
				{
					printf("■");
				}
				else
					printf("  ");
			}
		}
		printf("\n");
	}
}

void gameOver()
{
	system("cls");
	printf("\n\n\n\t\t\t\tGG\n\n\n\n\n\n\n");
}

void createFood()
{
	if (hasFood == no)
	{
		srand(time(NULL));
		food.X = (rand() * 1998) % 48 + 2;
		food.Y = (rand() * 1998) % 24 + 2;
		SetConsoleCursorPosition(handle, food);
		printf("★");
		hasFood = yes;
	}
}
