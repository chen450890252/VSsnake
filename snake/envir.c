#include "envir.h"


//初始化首页
void createFirstPage()
{
	system("mode con cols=90 lines=30");
	PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
	COORD tempPos;
	tempPos.X = 18;
	tempPos.Y = 12;
	SetConsoleCursorPosition(handle, tempPos);
	printf("欢迎进入贪吃蛇世界\n");
	Sleep(3000);
}

void enterIntoFirstPage()
{
	system("cls");
	SetConsoleCursorPosition(handle, new_game);
	SetConsoleTextAttribute(handle, 250);
	printf("新 游 戏");
	SetConsoleTextAttribute(handle, 10);
	SetConsoleCursorPosition(handle, saved_mode);
	printf("读 取 存 档");
	SetConsoleCursorPosition(handle, top);
	printf("排 行 榜");
	selectMode();
}

int scoreSort(FILE *file, char *filePath, int array[])
{
	int i = 0;
	int max;
	int count = 0;
	fopen_s(&file, filePath, "r");
	if (file != NULL)
	{

		int result;
		do {
			result = fscanf_s(file, "%d", &array[i]);
			i++;
			count++;
		} while (result > 0);
	}
	fclose(file);
	for (i = 0; i < count; i++)
	{
		max = array[i];
		for (int j = i + 1; j < count; j++)
		{
			if (array[j] > max)
			{
				int temp = max;
				max = array[j];
				array[j] = temp;
			}
		}
		array[i] = max;
	}
	return count;
}

void selectMode()
{
	int i = 0;
	int isChange = 1;
	int isbreak = 0;
	COORD topTitle;
	int score;
	int count = 0;
	while (1)
	{
		if (isbreak)
			break;
		if (_kbhit())
		{
			char hit = _getch();
			switch (hit)
			{
			case ' ':
				isbreak = 1;
				break;
			case 'w':case 'W':
				PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (modeSelect > 1)
				{
					modeSelect--;
					isChange = 1;
				}
				break;
			case 's':case 'S':
				PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (modeSelect < 3)
				{
					modeSelect++;
					isChange = 1;
				}
				break;
			default:
				break;
			}
		}
		if (isChange == 1)
		{
			isChange = 0;
			switch (modeSelect)
			{
			case 1:
				SetConsoleCursorPosition(handle, new_game);
				SetConsoleTextAttribute(handle, 250);
				printf("新 游 戏");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, saved_mode);
				printf("读 取 存 档");
				SetConsoleCursorPosition(handle, top);
				printf("排 行 榜");
				break;
			case 2:
				SetConsoleCursorPosition(handle, new_game);
				SetConsoleTextAttribute(handle, 10);
				printf("新 游 戏");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, saved_mode);
				printf("读 取 存 档");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, top);
				printf("排 行 榜");
				break;
			case 3:
				SetConsoleCursorPosition(handle, new_game);
				SetConsoleTextAttribute(handle, 10);
				printf("新 游 戏");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, saved_mode);
				printf("读 取 存 档");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, top);
				printf("排 行 榜");
				SetConsoleTextAttribute(handle, 10);
				break;
			default:
				break;
			}
		}
	}
	switch (modeSelect)
	{
	case 1:
		system("cls");
		PlaySound(TEXT("entergame.wav"), NULL, SND_FILENAME | SND_ASYNC);
		initScene();
		return;
		break;
	case 3:
		topTitle.X = 30;
		topTitle.Y = 5;
		system("cls");
		SetConsoleCursorPosition(handle, topTitle);
		printf("排 行 榜\n");
		count = scoreSort(file, filePath, topScore);
		if (count > 10)
		{
			for (i = 0; i < 10; i++)
			{
				topTitle.Y++;
				SetConsoleCursorPosition(handle, topTitle);
				printf("%d -> %d", i + 1, topScore[i]);
			}
		}
		else
		{
			for (i = 0; i < count; i++)
			{
				topTitle.Y++;
				SetConsoleCursorPosition(handle, topTitle);
				printf("%d -> %d", i + 1, topScore[i]);
			}
			for (; i < 10; i++)
			{
				topTitle.Y++;
				SetConsoleCursorPosition(handle, topTitle);
				printf("%d -> 0", i + 1);
			}
		}
		while (1)
		{
			if (_kbhit())
			{
				char hit = _getch();
				switch (hit)
				{
				case ' ':
					system("cls");
					//递归完成返回
					selectMode();
					return;
					break;
				default:
					break;
				}
			}
		}
		break;
	}
	
}


//画出初始化场景，包括地图、初始化蛇、毒草
void initScene()
{
	for (int i = 0; i < 26; i++)
	{
		if (i == 0 || i == 25)
		{
			for (int j = 0; j < 27; j++)
			{
				SetConsoleTextAttribute(handle, 17);
				printf("■");
				SetConsoleTextAttribute(handle, 7);
			}
		}
		else
		{
			for (int j = 0; j < 27; j++)
			{
				if (j == 0 || j == 26)
				{
					SetConsoleTextAttribute(handle, 17);
					printf("■");
					SetConsoleTextAttribute(handle, 7);
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
	createObt();
	createDrug();
}

int gameOver()
{
	char *filePath = "scores.txt";
	FILE *file = NULL;
	fopen_s(&file, filePath, "a+");
	if (file != NULL && score > topScore[10])
	{
		fprintf(file, "%d\n", score);
	}
	fclose(file);
	system("cls");
	PlaySound(TEXT("over.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printf("\n\n\n\t\t\t\tGG\n\n");
	printf("\t\t\t    按Q键重新开始游戏\n\t\t\t    按F键结束\n\n\n\n\n");
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
		printf("★");
		SetConsoleTextAttribute(handle, 7);
		
		hasFood = yes;
	}
}

void printData()
{
	SetConsoleCursorPosition(handle, scorePos);
	printf("分数: %d", score);
	COORD rulePos;
	rulePos.X = scorePos.X - 6;
	rulePos.Y = scorePos.Y - 15;
	SetConsoleCursorPosition(handle, rulePos);
	printf("按↑↓←→控制蛇");
	rulePos.Y++;
	SetConsoleCursorPosition(handle, rulePos);
	printf("按空格暂停游戏");
	rulePos.Y+=2;
	SetConsoleCursorPosition(handle, rulePos);
	SetConsoleTextAttribute(handle, 12);
	printf("★");
	SetConsoleTextAttribute(handle, 15);
	printf("  食物");
	rulePos.Y+=2;
	SetConsoleCursorPosition(handle, rulePos);
	SetConsoleTextAttribute(handle, 13);
	printf("●");
	SetConsoleTextAttribute(handle, 15);
	printf("  毒草");
	rulePos.Y++;
	SetConsoleCursorPosition(handle, rulePos);
	if (level > 1)
	{
		SetConsoleTextAttribute(handle, 14);
		printf("◆");
		SetConsoleTextAttribute(handle, 15);
		printf("  智慧草");
	}
	

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
		printf("●");
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
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
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
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
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
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
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
	srand(time(NULL) + score);
	if (grassRule >= 100 && hasAmaGrass == no)
	{
		grassRule = 0;
		amaGrassPos.X = (rand() * 1998) % 24 * 2 + 2;
		amaGrassPos.Y = (rand() * 1998) % 24 + 2;
		createNoEquCoordWithOther(&amaGrassPos, tAmaGrass);
		SetConsoleCursorPosition(handle, amaGrassPos);
		SetConsoleTextAttribute(handle, 14);
		printf("◆");
		SetConsoleTextAttribute(handle, 7);
		hasAmaGrass = yes;
	}
}

void createObt()
{
	if (level == 2)
	{
		int i = 0;
		for (; i < 8; i++)
		{
			obtPos[i].X = 8;
			obtPos[i].Y = 10 + i;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 119);
			printf("■");
			obtCount++;
		}
		for (; i < 16; i++)
		{
			obtPos[i].X = 42;
			obtPos[i].Y = 2 + i;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 119);
			printf("■");
			obtCount++;
		}
		for (; i < 24; i++)
		{
			obtPos[i].X = -14 + i * 2;
			obtPos[i].Y = 5;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 119);
			printf("■");
			obtCount++;
		}
		for (; i < 32; i++)
		{
			obtPos[i].X = -30 + i * 2;
			obtPos[i].Y = 21;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 119);
			printf("■");
			obtCount++;
		}
	}
	else if (level == 3)
	{
		for (int i = 0; i < 30; i++)
		{
			int time = i;
			srand(time += 1251345);
			obtPos[i].X = (rand() * 1217) % 22 * 2 + 4;
			obtPos[i].Y = (rand() * 1314) % 18 + 5;
			snake *temp = headPointer;
			int equal = 0;
			while (temp->next != NULL)
			{
				if (coordEqu(temp->coord, obtPos[i]))
				{
					obtPos[i].X = (rand() * 1217) % 22 * 2 + 4;
					obtPos[i].Y = (rand() * 1314) % 18 + 5;
					equal = 1;
					break;
				}
				temp = temp->next;
			}
			if (coordEqu(temp->coord, obtPos[i]))
			{
				obtPos[i].X = (rand() * 1217) % 22 * 2 + 4;
				obtPos[i].Y = (rand() * 1314) % 18 + 5;
				equal = 1;
			}
			if (equal == 1)
			{
				continue;
			}
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 119);
			printf("■");
			obtCount++;
		}
	}
}