#include "envir.h"
#include <time.h>
//初始化首页
void createFirstPage()
{
	system("mode con cols=90 lines=30");
	printf("\n\n\n\t\t\t欢迎进入贪吃蛇世界\n");
	printf("\t\t      按↑↓←→控制蛇的方向\n");
	printf("\t\t\t 按空格键进入游戏\n\n\n");
	enterIntoGame();
}

//按空格健进入游戏，清屏
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

//画出初始化场景，包括地图、初始化蛇、毒草
void initScene()
{
	SetConsoleTextAttribute(handle, 1);
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
	SetConsoleTextAttribute(handle, 7);
	printData();
	drawSnake(10);
	createDrug();
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
		SetConsoleTextAttribute(handle, 12);
		printf("★");
		SetConsoleTextAttribute(handle, 7);
		
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
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		drugPos[i].X = (rand() * 1998) % 48 + 2;
		drugPos[i].Y = (rand() * 1998) % 24 + 2;
		drugCount++;
		createNoEquCoordWithOther(&drugPos[i], tDrug);
	}
	for (int i = 0; i < drugCount; i++)
	{
		createNoEquCoordWithOther(&drugPos[i], tDrug);
		SetConsoleCursorPosition(handle, drugPos[i]);
		SetConsoleTextAttribute(handle, 13);
		printf("卍");
		SetConsoleTextAttribute(handle, 7);
		
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
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		otherCoord[i].X = amaGrassPos.X;
		otherCoord[i].Y = amaGrassPos.Y;
		i++;
		break;
	case tDrug:
		for (i = 0; i < drugCount - 1 && coord != &drugPos[i]; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		if (drugCount == 1)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
			break;
		}
		otherCoord[i].X = foodPos.X;
		otherCoord[i].Y = foodPos.Y;
		i++;
		otherCoord[i].X = amaGrassPos.X;
		otherCoord[i].Y = amaGrassPos.Y;
		i++;
		break;
	case tAmaGrass:
		for (i = 0; i < drugCount; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		otherCoord[i].X = foodPos.X;
		otherCoord[i].Y = foodPos.Y;
		i++;
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
		for (int j = 0; j < i && equal == no; j++)
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

void createAmaGrass()
{
	grassRule = score % 150;
	srand(score);
	if (grassRule >= 20 && hasAmaGrass == no)
	{
		grassRule = 0;
		amaGrassPos.X = (rand() * 1998) % 48 + 2;
		amaGrassPos.Y = (rand() * 1998) % 24 + 2;
		createNoEquCoordWithOther(&amaGrassPos, tAmaGrass);
		SetConsoleCursorPosition(handle, amaGrassPos);
		SetConsoleTextAttribute(handle, 14);
		printf("◆");
		SetConsoleTextAttribute(handle, 7);
		hasAmaGrass = yes;
	}
}