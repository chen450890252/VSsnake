#include "envir.h"

//��ʼ����ҳ
void createFirstPage()
{
	system("mode con cols=90 lines=30");
	PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printf("\n\n\n\n\n\t\t\t��ӭ����̰��������\n");
	printf("\t\t      ���������������ߵķ���\n");
	printf("\t\t\t ���ո��������ҳ\n\n\n");
	enterIntoFirstPage();
}

void enterIntoFirstPage()
{
	char isEnter;
	while (1)
	{
		isEnter = getchar();
		if (isEnter == '\n')
		{
			break;
		}
	}
	system("cls");
	SetConsoleCursorPosition(handle, new_game);
	SetConsoleTextAttribute(handle, 250);
	printf("�� �� Ϸ");
	SetConsoleTextAttribute(handle, 10);
	SetConsoleCursorPosition(handle, saved_mode);
	printf("�� ȡ �� ��");
	selectMode();
}

void selectMode()
{
	while (1)
	{
		if (GetAsyncKeyState(' '))
		{
			break;
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			modeSelect = up;
			SetConsoleCursorPosition(handle, new_game);
			SetConsoleTextAttribute(handle, 250);
			printf("�� �� Ϸ");
			SetConsoleTextAttribute(handle, 10);
			SetConsoleCursorPosition(handle, saved_mode);
			printf("�� ȡ �� ��");
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			modeSelect = down;
			SetConsoleTextAttribute(handle, 250);
			SetConsoleCursorPosition(handle, saved_mode);
			printf("�� ȡ �� ��");
			SetConsoleCursorPosition(handle, new_game);
			SetConsoleTextAttribute(handle, 10);
			printf("�� �� Ϸ");

		}
	}
	if (modeSelect == up)
	{
		PlaySound(TEXT("entergame.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		initScene();
	}
	else if (modeSelect == down)
	{}
}

//���ո񽡽�����Ϸ������
void enterIntoGame()
{
	char isEnter;
	while (1)
	{
		isEnter = _getch();
		if (isEnter == ' ')
		{
			PlaySound(TEXT("entergame.wav"),NULL,SND_FILENAME|SND_ASYNC);
			break;
		}
	}

}

//������ʼ��������������ͼ����ʼ���ߡ�����
void initScene()
{
	SetConsoleTextAttribute(handle, 1);
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
	SetConsoleTextAttribute(handle, 7);
	printData();
	drawSnake(10);
	createDrug();
}

int gameOver()
{
	system("cls");
	PlaySound(TEXT("over.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printf("\n\n\n\t\t\t\tGG\n\n");
	printf("\t\t\t    ��Q�����¿�ʼ��Ϸ\n\t\t\t    ��F������\n\n\n\n\n");
	char isAgain;
	while (1)
	{
		isAgain = _getch();
		if (isAgain == 'F' || isAgain == 'f')
		{
			return no;
		}
		else if (isAgain == 'q' || isAgain == 'Q')
		{
			return yes;
		}
	}
}

void createFood()
{
	if (hasFood == no)
	{
		srand(time(NULL));
		foodPos.X = (rand() * 1998) % 24 * 2 + 2;
		foodPos.Y = (rand() * 1998) % 24 + 2;
		createNoEquCoordWithOther(&foodPos, tFood);
		SetConsoleCursorPosition(handle, foodPos);
		SetConsoleTextAttribute(handle, 12);
		printf("��");
		SetConsoleTextAttribute(handle, 7);
		
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
		drugPos[i].X = (rand() * 1998) % 24 * 2 + 2;
		drugPos[i].Y = (rand() * 1998) % 24 + 2;
		drugCount++;
		createNoEquCoordWithOther(&drugPos[i], tDrug);
	}
	for (int i = 0; i < drugCount; i++)
	{
		createNoEquCoordWithOther(&drugPos[i], tDrug);
		SetConsoleCursorPosition(handle, drugPos[i]);
		SetConsoleTextAttribute(handle, 13);
		printf("�d");
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
	//���ݴ������Ҫ�жϵ����ͣ���ȡ�������͵���������
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
		amaGrassPos.X = (rand() * 1998) % 24 * 2 + 2;
		amaGrassPos.Y = (rand() * 1998) % 24 + 2;
		createNoEquCoordWithOther(&amaGrassPos, tAmaGrass);
		SetConsoleCursorPosition(handle, amaGrassPos);
		SetConsoleTextAttribute(handle, 14);
		printf("��");
		SetConsoleTextAttribute(handle, 7);
		hasAmaGrass = yes;
	}
}