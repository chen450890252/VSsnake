#include "envir.h"
#include <time.h>
//��ʼ����ҳ
void createFirstPage()
{
	system("mode con cols=90 lines=30");
	printf("\n\n\n\t\t\t��ӭ����̰��������\n");
	printf("\t\t      ���������������ߵķ���\n");
	printf("\t\t\t ���ո��������Ϸ\n\n\n");
	enterIntoGame();
}

//���ո񽡽�����Ϸ������
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

//������ʼ����ͼ���Լ�
void initScene()
{
	for (int i = 0; i < 26; i++)
	{
		if (i == 0 || i == 25)
		{
			for (int j = 0; j < 27; j++)
			{
				printf("��");
			}
		}
		else
		{
			for (int j = 0; j < 27; j++)
			{
				if (j == 0 || j == 26)
				{
					printf("��");
				}
				else
					printf("  ");
			}
		}
		printf("\n");
	}
	printData();
	drawSnake();
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
		printf("��");
		hasFood = yes;
	}
}

void printData()
{
	SetConsoleCursorPosition(handle, top);
	printf("���а�");
	SetConsoleCursorPosition(handle, scorePos);
	printf("����: %d", score);
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
		SetConsoleCursorPosition(handle, drugPos[i]);
		printf("�d");
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
	//���ݴ������Ҫ�жϵ����ͣ���ȡ�������͵���������
	switch (type)
	{
	case tFood:
		for (i = 0; i < drugCount; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
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
