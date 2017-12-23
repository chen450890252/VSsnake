#include "envir.h"
#include <time.h>

void createFirstPage()
{
	system("mode con cols=90 lines=30");
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
	printData();
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
		foodPos.X = (rand() * 1998) % 48 + 2;
		foodPos.Y = (rand() * 1998) % 24 + 2;
		createNoEquCoordWithOther(&foodPos, tFood);
		SetConsoleCursorPosition(handle, foodPos);
		printf("★");
		hasFood = yes;
	}
}

void printData()
{
	SetConsoleCursorPosition(handle, top);
	printf("排行版");
	SetConsoleCursorPosition(handle, scorePos);
	printf("分数: %d", score);
}

void createDrug()
{
	for (int i = 0; i < 3; i++)
	{
		drugPos[i].X = (rand() * 1998) % 48 + 2;
		drugPos[i].Y = (rand() * 1998) % 24 + 2;
		drugCount++;
		createNoEquCoordWithOther(&drugPos[i], tDrug);
	}
	for (int i = 0; i < drugCount; i++)
	{
		SetConsoleCursorPosition(handle, drugPos[i]);
		printf("卍");
	}

}

int coordEqu(COORD coord1, COORD coord2)
{
	if (coord1.X == coord2.X && coord1.Y == coord2.Y)
		return yes;
	else
		return no;
}

void createNoEquCoordWithOther(COORD *coord, int type)
{
	COORD otherCoord[100];
	int i = 0;
	//根据传入的需要判断的类型，获取其他类型的所有坐标
	switch (type)
	{
	case tFood:
		for (i = 0; i < drugCount; i++)
		{
			otherCoord[i] = drugPos[i];
		}
		break;
	case tDrug:
		for (i = 0; i < drugCount - 1, coord != &drugPos[i]; i++)
		{
			otherCoord[i] = drugPos[i];
		}
		if (drugCount = 1)
			break;
		otherCoord[i] = foodPos;
		i++;
		break;
	case tAmaGrass:
		break;
	default:
		break;
	}
	while (1)
	{
		snake *temp = headPointer;
		int equal = no;
		while (temp->next != NULL)
		{
			if (coordEqu(temp->coord, *coord))
			{
				equal = yes;
				break;
			}
			temp = temp->next;
		}
		if (equal == no && coordEqu(temp->coord, *coord))
		{
			equal = yes;
		}
		for (int j = 0; j < i, equal == no; j++)
		{
			if (coordEqu(otherCoord[j], *coord))
			{
				equal = yes;
				break;
			}
		}
		if (equal)
		{
			(*coord).X = (rand() * 1998) % 48 + 2;
			(*coord).Y = (rand() * 1998) % 24 + 2;
			continue;
		}
		else
			break;
	}
}
