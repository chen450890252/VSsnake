#include "ui.h"

//各类坐标，如食物，分数，排行榜
COORD foodPos, amaGrassPos, obtPos[50], drugPos[50], bombPos[10];
//毒草的个数
int drugCount, obtCount, bombCount, levels, drugflash, score, topScore[11];
char *filePath;
FILE *file;
extern HANDLE handle;
extern int hasFood, hasAmaGrass;
extern snake *tailPointer, *headPointer;


void initUIData()
{
	filePath = "scores.txt";
	file = NULL;
	drugflash = 0;
	hasFood = 0;
	hasAmaGrass = 0;
	for (int i = 0; i < 50; i++)
	{
		obtPos[i].X = 0;
		obtPos[i].Y = 0;
	}
	for (int i = 0; i < 50; i++)
	{
		drugPos[i].X = 0;
		drugPos[i].Y = 0;
	}
	foodPos.X = 0;
	foodPos.Y = 0;
	amaGrassPos.X = 0;
	amaGrassPos.Y = 0;
	obtCount = 0;
	drugCount = 0;
}

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

int selectMode()
{
	system("cls");
	fflush(stdin);
	levels = 1;
	int i = 0;
	int isChange = 1;
	int isbreak = 0;
	int modeSelect = 1;
	COORD topTitle, new_game, saved_mode, top, exitPos;
	new_game.X = 30;
	new_game.Y = 10;
	saved_mode.X = 30;
	saved_mode.Y = 13;
	top.X = 30;
	top.Y = 16;
	exitPos.X = 30;
	exitPos.Y = 19;
	int count = 0;
	scoreSort(file, filePath, topScore);
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
				if (modeSelect < 4)
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
				SetConsoleCursorPosition(handle, exitPos);
				printf("退 出 游 戏");
				break;
			case 2:
				SetConsoleCursorPosition(handle, new_game);
				SetConsoleTextAttribute(handle, 10);
				printf("新 游 戏");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, saved_mode);
				printf("读 取 存 档");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, top);
				printf("排 行 榜");
				SetConsoleCursorPosition(handle, exitPos);
				printf("退 出 游 戏");
				break;
			case 3:
				SetConsoleCursorPosition(handle, new_game);
				SetConsoleTextAttribute(handle, 10);
				printf("新 游 戏");
				SetConsoleCursorPosition(handle, saved_mode);
				printf("读 取 存 档");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, top);
				printf("排 行 榜");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, exitPos);
				printf("退 出 游 戏");
				break;
			case 4:
				SetConsoleCursorPosition(handle, new_game);
				SetConsoleTextAttribute(handle, 10);
				printf("新 游 戏");
				SetConsoleCursorPosition(handle, saved_mode);
				printf("读 取 存 档");
				SetConsoleCursorPosition(handle, top);
				printf("排 行 榜");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, exitPos);
				printf("退 出 游 戏");
			default:
				break;
			}
		}
	}
	switch (modeSelect)
	{
	case 1:
		PlaySound(TEXT("entergame.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return selectLevels();
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
					return selectMode();
					break;
				default:
					break;
				}
			}
		}
		break;
	case 4:
		exit(1);
		break;
	}
}

int selectLevels()
{
	system("cls");
	fflush(stdin);
	COORD levelPos[4];
	int isbreak = 0;
	int isChange = 0;
	int selectLevel = 1;
	for (int i = 0; i < 4; i++)
	{
		levelPos[i].X = 30;
		levelPos[i].Y = 10 + i * 3;
	}
	SetConsoleCursorPosition(handle, levelPos[0]);
	SetConsoleTextAttribute(handle, 250);
	printf("第 一 关");
	SetConsoleTextAttribute(handle, 10);
	SetConsoleCursorPosition(handle, levelPos[1]);
	printf("第 二 关");
	SetConsoleCursorPosition(handle, levelPos[2]);
	printf("第 三 关");
	SetConsoleCursorPosition(handle, levelPos[3]);
	printf("返回主菜单");
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
				if (selectLevel > 1)
				{
					selectLevel--;
					isChange = 1;
				}
				break;
			case 's':case 'S':
				PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (selectLevel < 4)
				{
					selectLevel++;
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
			switch (selectLevel)
			{
			case 1:
				SetConsoleCursorPosition(handle, levelPos[0]);
				SetConsoleTextAttribute(handle, 250);
				printf("第 一 关");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, levelPos[1]);
				printf("第 二 关");
				SetConsoleCursorPosition(handle, levelPos[2]);
				printf("第 三 关");
				SetConsoleCursorPosition(handle, levelPos[3]);
				printf("返回主菜单");
				break;
			case 2:
				SetConsoleCursorPosition(handle, levelPos[0]);
				SetConsoleTextAttribute(handle, 10);
				printf("第 一 关");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, levelPos[1]);
				printf("第 二 关");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, levelPos[2]);
				printf("第 三 关");
				SetConsoleCursorPosition(handle, levelPos[3]);
				printf("返回主菜单");
				break;
			case 3:
				SetConsoleCursorPosition(handle, levelPos[0]);
				SetConsoleTextAttribute(handle, 10);
				printf("第 一 关");
				SetConsoleCursorPosition(handle, levelPos[1]);
				printf("第 二 关");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, levelPos[2]);
				printf("第 三 关");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, levelPos[3]);
				printf("返回主菜单");
				break;
			case 4:
				SetConsoleCursorPosition(handle, levelPos[0]);
				SetConsoleTextAttribute(handle, 10);
				printf("第 一 关");
				SetConsoleCursorPosition(handle, levelPos[1]);
				printf("第 二 关");
				SetConsoleCursorPosition(handle, levelPos[2]);
				printf("第 三 关");
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, levelPos[3]);
				printf("返回主菜单");
				SetConsoleTextAttribute(handle, 10);
				break;
			default:
				break;
			}
		}
	}
	switch (selectLevel)
	{
	case 1:
		levels = 1;
		return 1;
		break;
	case 2:
		levels = 2;
		return 2;
		break;
	case 3:
		levels = 3;
		return 3;
		break;
	case 4:
		return 0;
		break;
	}
}

//画出初始化场景，包括地图、初始化蛇、毒草
void initScene()
{
	system("cls");
	for (int i = 0; i < 26; i++)
	{
		if (i == 0 || i == 25)
		{
			for (int j = 0; j < 27; j++)
			{
				SetConsoleTextAttribute(handle, 17);
				printf("■");
				SetConsoleTextAttribute(handle, 7);
				Sleep(20);
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
					Sleep(20);
				}
				else
					printf("  ");
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(handle, 7);
	printData();
}

void printData()
{
	COORD scorePos, rulePos;
	scorePos.X = 68;
	scorePos.Y = 20;
	SetConsoleCursorPosition(handle, scorePos);
	printf("分数: %d", score);
	rulePos.X = scorePos.X - 6;
	rulePos.Y = scorePos.Y - 15;
	SetConsoleCursorPosition(handle, rulePos);
	printf("按↑↓←→控制蛇");
	rulePos.Y++;
	SetConsoleCursorPosition(handle, rulePos);
	printf("按空格暂停游戏");
	rulePos.Y += 2;
	SetConsoleCursorPosition(handle, rulePos);
	SetConsoleTextAttribute(handle, 12);
	printf("★");
	SetConsoleTextAttribute(handle, 15);
	printf("  食物");
	rulePos.Y += 2;
	SetConsoleCursorPosition(handle, rulePos);
	SetConsoleTextAttribute(handle, 13);
	printf("●");
	SetConsoleTextAttribute(handle, 15);
	printf("  毒草");
	rulePos.Y += 2;
	SetConsoleCursorPosition(handle, rulePos);
	if (levels > 1)
	{
		SetConsoleTextAttribute(handle, 14);
		printf("◆");
		SetConsoleTextAttribute(handle, 15);
		printf("  智慧草");
		rulePos.Y += 2;
		SetConsoleCursorPosition(handle, rulePos);
		SetConsoleTextAttribute(handle, 119);
		printf("■");
		SetConsoleTextAttribute(handle, 15);
		printf("  障碍");
	}


}

void createFood()
{
	if (hasFood == no)
	{
		srand(time(NULL));
		foodPos.X = (rand() * 1314 + score) % 24 * 2 + 2;
		foodPos.Y = (rand() * 520) % 22 + 2;
		createNoEquCoordWithOther(&foodPos, tFood);
		SetConsoleCursorPosition(handle, foodPos);
		SetConsoleTextAttribute(handle, 12);
		printf("★");
		SetConsoleTextAttribute(handle, 7);
		hasFood = yes;
	}
}

void createDrug()
{
	srand(time(NULL));
	switch (levels)
	{
	case 1:
		drugCount = 3;
		break;
	case 2:
		drugCount = 5;
		break;
	case 3:
		drugCount = 8;
		break;
	}
	for (int i = 0; i < drugCount; i++)
	{
		drugPos[i].X = (rand() * 1998) % 24 * 2 + 2;
		drugPos[i].Y = (rand() * 1217) % 22 + 2;
		createNoEquCoordWithOther(&drugPos[i], tDrug);
		SetConsoleCursorPosition(handle, drugPos[i]);
		SetConsoleTextAttribute(handle, 13);
		printf("●");
		SetConsoleTextAttribute(handle, 7);
	}
}

void createAmaGrass()
{
	int grassRule = 0;
	grassRule = score % 50;
	srand(time(NULL) + score);
	if (grassRule >= 20 && hasAmaGrass == no && levels > 1)
	{
		grassRule = 0;
		amaGrassPos.X = (rand() * 1998) % 24 * 2 + 2;
		amaGrassPos.Y = (rand() * 1998 + score) % 22 + 2;
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
	if (levels == 2)
	{
		int i = 0;
		for (; i < 8; i++)
		{
			obtPos[i].X = 8;
			obtPos[i].Y = 10 + i;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 8);
			printf("■");
			obtCount++;
		}
		for (; i < 16; i++)
		{
			obtPos[i].X = 42;
			obtPos[i].Y = 2 + i;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 8);
			printf("■");
			obtCount++;
		}
		for (; i < 24; i++)
		{
			obtPos[i].X = -14 + i * 2;
			obtPos[i].Y = 5;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 8);
			printf("■");
			obtCount++;
		}
		for (; i < 32; i++)
		{
			obtPos[i].X = -30 + i * 2;
			obtPos[i].Y = 21;
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 8);
			printf("■");
			obtCount++;
		}
	}
	else if (levels == 3)
	{
		for (int i = 0; i < 30; i++)
		{
			int time = i;
			srand(time += 1251345);
			obtPos[i].X = rand() % 22 * 2 + 4;
			obtPos[i].Y = (rand() * i + i) % 18 + 5;
			snake *temp = headPointer;
			int equal = 0;
			while (temp->next != NULL)
			{
				if (coordEqu(temp->coord, obtPos[i]))
				{
					obtPos[i].X = rand() % 22 * 2 + 4;
					obtPos[i].Y = (rand() * 1314 + i * 65) % 18 + 5;
					equal = 1;
					break;
				}
				temp = temp->next;
			}
			if (coordEqu(temp->coord, obtPos[i]))
			{
				obtPos[i].X = (rand() * 1217 + i * 565) % 22 * 2 + 4;
				obtPos[i].Y = (rand() * 1314 + i * 231) % 18 + 5;
				equal = 1;
			}
			if (equal == 1)
			{
				continue;
			}
			SetConsoleCursorPosition(handle, obtPos[i]);
			SetConsoleTextAttribute(handle, 8);
			printf("■");
			obtCount++;
		}
	}
}

void createBomb()
{
	if (levels == 3)
	{
		srand(score + 520);
		bombCount = 4;
		for (int i = 0; i < bombCount; i++)
		{
			bombPos[i].X = (rand() * score) % 20 + 4;
			bombPos[i].Y = (rand() + score) % 20 + 4;
			createNoEquCoordWithOther(&bombPos[i], tBomb);
			SetConsoleCursorPosition(handle, bombPos[i]);
			SetConsoleTextAttribute(handle, 8);
			printf("●");
		}
	}
	else
	{
		bombCount = 0;
	}
}

void changeSpeed(int *i)
{
	if (score > 50)
	{
		*i = 150;
	}
	else if (score > 100)
	{
		*i = 100;
	}
}

int isWin()
{
	int rule = 200;
	int isbreak = 0;
	int isChange = 0;
	int select = 1;
	COORD winInfo;
	winInfo.X = 30;
	winInfo.Y = 12;
	COORD selectPos[2];
	for (int i = 0; i < 2; i++)
	{
		selectPos[i].X = 28 + i * 15;
		selectPos[i].Y = 14;
	}
	switch (levels)
	{
	case 1:
		rule = 100;
		break;
	case 2:
		rule = 200;
		break;
	case 3:
		rule = 300;
		break;
	}
	if (levels < 3)
	{
		if (score > rule)
		{
			PlaySound(TEXT("pass.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			SetConsoleCursorPosition(handle, winInfo);
			SetConsoleTextAttribute(handle, 10);
			printf("恭喜你通过第 %d 关", levels);
			SetConsoleCursorPosition(handle, selectPos[0]);
			SetConsoleTextAttribute(handle, 250);
			printf("返回主菜单");
			SetConsoleTextAttribute(handle, 10);
			SetConsoleCursorPosition(handle, selectPos[1]);
			printf("下 一 关");
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
					case 'a':case 'A':
						PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
						if (select > 1)
						{
							select--;
							isChange = 1;
						}
						break;
					case 'd':case 'D':
						PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
						if (select < 2)
						{
							select++;
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
					switch (select)
					{
					case 1:
						SetConsoleCursorPosition(handle, selectPos[0]);
						SetConsoleTextAttribute(handle, 250);
						printf("返回主菜单");
						SetConsoleTextAttribute(handle, 10);
						SetConsoleCursorPosition(handle, selectPos[1]);
						printf("下 一 关");
						break;
					case 2:
						SetConsoleCursorPosition(handle, selectPos[0]);
						SetConsoleTextAttribute(handle, 10);
						printf("返回主菜单");
						SetConsoleTextAttribute(handle, 10);
						SetConsoleTextAttribute(handle, 250);
						SetConsoleCursorPosition(handle, selectPos[1]);
						printf("下 一 关");
						SetConsoleTextAttribute(handle, 10);
						break;
					default:
						break;
					}
				}
			}
			switch (select)
			{
			case 1:
				score = 0;
				return 1;
				break;
			case 2:
				levels++;
				return levels;
				break;
			default:
				return 1;
				break;
			}
		}
		return 0;
	}
	else if (levels == 3)
	{
		if (score > rule)
		{
			PlaySound(TEXT("finishWin.wav"), NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			SetConsoleCursorPosition(handle, winInfo);
			SetConsoleTextAttribute(handle, 10);
			printf("游 戏 胜 利！！！");
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
					case 'a':case 'A':
						PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
						if (select > 1)
						{
							select--;
							isChange = 1;
						}
						break;
					case 'd':case 'D':
						PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
						if (select < 2)
						{
							select++;
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
					switch (select)
					{
					case 1:
						SetConsoleCursorPosition(handle, selectPos[0]);
						SetConsoleTextAttribute(handle, 250);
						printf("返回主菜单");
						SetConsoleTextAttribute(handle, 10);
						SetConsoleCursorPosition(handle, selectPos[1]);
						printf("退出游戏");
						break;
					case 2:
						SetConsoleCursorPosition(handle, selectPos[0]);
						SetConsoleTextAttribute(handle, 10);
						printf("返回主菜单");
						SetConsoleTextAttribute(handle, 10);
						SetConsoleTextAttribute(handle, 250);
						SetConsoleCursorPosition(handle, selectPos[1]);
						printf("退出游戏");
						SetConsoleTextAttribute(handle, 10);
						break;
					default:
						break;
					}
				}
			}
			switch (select)
			{
			case 1:
				return 1;
				break;
			case 2:
				exit(1);
				break;
			default:
				return yes;
				break;
			}
		}
		return 0;
	}
}

void flashDrug() 
{
	if (drugflash % 4 == 2)
	{
		for (int i = 0; i < drugCount && drugPos[i].X != 0 && drugPos[i].Y != 0; i++)
		{
			SetConsoleCursorPosition(handle, drugPos[i]);
			printf("  ");
		}
	}
	else if (drugflash % 4 == 0)
	{
		for (int i = 0; i < drugCount && drugPos[i].X != 0 && drugPos[i].Y != 0; i++)
		{
			SetConsoleCursorPosition(handle, drugPos[i]);
			SetConsoleTextAttribute(handle, 13);
			printf("●");
			SetConsoleTextAttribute(handle, 7);
		}
	}
	drugflash += 2;
}

int gameOver()
{
	int isbreak = 0;
	int select = 1;
	int isChange = 1;
	COORD winInfo;
	winInfo.X = 37;
	winInfo.Y = 12;
	COORD selectPos[2];
	for (int i = 0; i < 2; i++)
	{
		selectPos[i].X = 28 + i * 15;
		selectPos[i].Y = 14;
	}
	score = 0;
	fopen_s(&file, filePath, "a+");
	if (file != NULL && score > topScore[10])
	{
		fprintf(file, "%d\n", score);
	}
	fclose(file);
	system("cls");
	PlaySound(TEXT("over.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SetConsoleCursorPosition(handle, winInfo);
	SetConsoleTextAttribute(handle, 10);
	printf("欧^GG");
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
			case 'a':case 'A':
				PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (select > 1)
				{
					select--;
					isChange = 1;
				}
				break;
			case 'd':case 'D':
				PlaySound(TEXT("choice.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (select < 2)
				{
					select++;
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
			switch (select)
			{
			case 1:
				SetConsoleCursorPosition(handle, selectPos[0]);
				SetConsoleTextAttribute(handle, 250);
				printf("返回主菜单");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleCursorPosition(handle, selectPos[1]);
				printf("退出游戏");
				break;
			case 2:
				SetConsoleCursorPosition(handle, selectPos[0]);
				SetConsoleTextAttribute(handle, 10);
				printf("返回主菜单");
				SetConsoleTextAttribute(handle, 10);
				SetConsoleTextAttribute(handle, 250);
				SetConsoleCursorPosition(handle, selectPos[1]);
				printf("退出游戏");
				SetConsoleTextAttribute(handle, 10);
				break;
			default:
				break;
			}
		}
	}
	switch (select)
	{
	case 1:
		return yes;
		break;
	case 2:
		return no;
		break;
	default:
		return yes;
		break;
	}
}