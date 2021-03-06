#include "snake.h"

//蛇的头指针
snake *headPointer;
//蛇的尾指针，主要方便于删除尾部节点
snake *tailPointer;
//用于保存现在的蛇头方向
int currentDirection;
int snakeCount, addRule, subRule, stepCount, path[200], hasFood, hasAmaGrass;
extern HANDLE handle;
extern int score, drugCount, bombCount, obtCount, levels;
extern COORD foodPos, amaGrassPos, obtPos[50], drugPos[50], bombPos[10];

void initSnakeData()
{
	snakeCount = 4;
	currentDirection = up;
	snake *first = (snake*)malloc(sizeof(snake));
	snake *second = (snake*)malloc(sizeof(snake));
	snake *third = (snake*)malloc(sizeof(snake));
	snake *fourth = (snake*)malloc(sizeof(snake));
	first->coord.X = 6;
	first->coord.Y = 6;
	second->coord.X = 6;
	second->coord.Y = 7;
	third->coord.X = 6;
	third->coord.Y = 8;
	fourth->coord.X = 6;
	fourth->coord.Y = 9;
	first->pre = NULL;
	first->next = second;
	second->pre = first;
	second->next = third;
	third->next = fourth;
	third->pre = second;
	fourth->next = NULL;
	fourth->pre = third;
	headPointer = first;
	tailPointer = fourth;
}

//初始化画蛇
void drawSnake(int color)
{
	snake *tempSnake = headPointer;
	while (tempSnake->next != NULL)
	{
		SetConsoleCursorPosition(handle, tempSnake->coord);
		SetConsoleTextAttribute(handle, color);
		printf("●");
		SetConsoleTextAttribute(handle, 7);
		tempSnake = tempSnake->next;
	}
	SetConsoleCursorPosition(handle, tempSnake->coord);
	printf("●");
}

//异步检测键盘输入，并以此改变蛇的方向
void changeDirection()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (currentDirection != down)
		{
			currentDirection = up;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (currentDirection != up)
		{
			currentDirection = down;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (currentDirection != right)
		{
			currentDirection = left;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (currentDirection != left)
		{
			currentDirection = right;
		}
	}
}

//判断蛇是否死亡
//包括分数太低，撞自己，撞墙
int isSnakeDie()
{
	if (score < 0)
		return yes;
	else if (snakeCount <= 0)
		return yes;
	else if (isBlockWall(headPointer->coord))
	{
		PlaySound(TEXT("blockWall.wav"), NULL, SND_FILENAME | SND_SYNC);
		return yes;
	}
	else if (isBlockSelf(headPointer->coord))
	{
		PlaySound(TEXT("gg.wav"), NULL, SND_FILENAME | SND_SYNC);
		return yes;
	}
	else
		return no;
}

//判断蛇是否撞到自己
int isBlockSelf(COORD coord)
{
	snake *temp = headPointer;
	if (temp == NULL)
		return yes;
	else if(temp->next != NULL)
		temp = temp->next;
	if (temp->next == NULL)
		return yes;
	do
	{
		if (coordEqu(temp->coord, coord))
			return yes;
		temp = temp->next;
	} while (temp->next != NULL);
	if (coordEqu(temp->coord, coord))
		return yes;
	else
		return no;
}

int isEatDrug(COORD coord)
{
	for (int i = 0; i < drugCount; i++)
	{
		if (coordEqu(coord, drugPos[i]))
		{
			drugPos[i].X = 0;
			drugPos[i].Y = 0;
			return yes;
		}
	}
	return no;
}

int isBlockWall(COORD coord)
{
	for (int i = 0; i < obtCount; i++)
	{
		if (coordEqu(coord, obtPos[i]))
		{
			return yes;
		}
	}
	if (currentDirection == up && coord.Y == 0)
		return yes;
	else if (currentDirection == down && coord.Y == 25)
		return yes;
	else if (currentDirection == left && coord.X == 0)
		return yes;
	else if (currentDirection == right && coord.X == 52)
		return yes;
	else
		return no;
}

//判断蛇是否吃到食物，并进行一系列数据操作
int eatFood()
{
	if (coordEqu(headPointer->coord, foodPos))
	{
		PlaySound(TEXT("eatfood.wav"), NULL, SND_ASYNC | SND_FILENAME);
		addRule++;
		score += addRule;
		printData();
		hasFood = no;
		snakeCount++;
		return yes;
	}
	return no;
}

//判断蛇是否吃到毒草，并进行一系列数据操作
int eatDrug()
{
	for (int i = 0; i < drugCount; i++)
	{
		if (coordEqu(headPointer->coord, drugPos[i]))
		{
			PlaySound(TEXT("drug.wav"), NULL, SND_FILENAME | SND_ASYNC);
			addRule = 1;
			score -= subRule;
			subRule += 10;
			printData();
			drugPos[i].X = 0;
			drugPos[i].Y = 0;
			snakeCount -= 3;
			return yes;
		}
	}
	return no;
}

//执行判断吃到什么东西的函数，并进行打印处理
void eat(int speed)
{
	if (eatFood())
	{
		addHead(10);
	}
	else if (eatDrug())
	{
		Sleep(speed);
		drawSnake(13);
		Sleep(speed);
		drawSnake(15);
		Sleep(speed);
		drawSnake(13);
		Sleep(speed);
		drawSnake(15);
		Sleep(speed);
		drawSnake(13);
		Sleep(speed);
		drawSnake(15);
		Sleep(speed);
		drawSnake(10);
		deleteTail();
	}
	else if (eatAmaGrass())
	{
		for (int i = 0; i < stepCount; i++)
		{
			currentDirection = path[i];
			int color = i % 7 + 9;
			addHead(color);
			deleteTail();
			Sleep(speed);
			if (eatFood())
			{
				addHead(10);
				stepCount = 0;
				return;
			}
			else if (isSnakeDie())
			{
				gameOver();
				return;
			}
		}
	}
	else if (eatBomb())
	{
		for (int i = 0; i < snakeCount; i++)
		{
			deleteTail();
		}
	}
	else
	{
		addHead(10);
		deleteTail();
	}
}

//判断是否吃到智慧草，并进行自动寻路
int eatAmaGrass()
{
	if (coordEqu(headPointer->coord, amaGrassPos))
	{
		PlaySound(TEXT("amagrass.wav"), NULL, SND_FILENAME | SND_ASYNC);
		hasAmaGrass = no;
		node temp1 = (node)malloc(sizeof(struct _node));
		node tempEnd = (node)malloc(sizeof(struct _node));
		temp1->coord.X = headPointer->coord.X;
		temp1->coord.Y = headPointer->coord.Y;
		temp1->dir = currentDirection;
		temp1->next = NULL;
		temp1->pre = NULL;
		tempEnd->coord.X = foodPos.X;
		tempEnd->coord.Y = foodPos.Y;
		if (searchLoad(temp1, tempEnd))
		{
			return yes;
		}
		else
		{
			return no;
		}
	}
	return no;
}

int searchLoad(node start, node end)
{
	node headNode = (node)malloc(sizeof(struct _node));
	headNode = start;
	int nodeCount = 1;
	node temp1, temp2;
	temp1 = (node)malloc(sizeof(struct _node));
	temp2 = (node)malloc(sizeof(struct _node));
	int i;
	int visit[60][30];

	int dir[][2] = { { 0,1 },{ 2,0 },{ 0,-1 },{ -2,0 } };

	visit[start->coord.X][start->coord.Y] = yes;

	while (nodeCount > 0)
	{
		temp1 = front(headNode);
		nodeCount--;
		for (i = 0; i < 4; i++)
		{
			temp2->coord.X = temp1->coord.X + dir[i][0];
			temp2->coord.Y = temp1->coord.Y + dir[i][1];
			switch (i)
			{
			case 0:
				temp2->dir = down;
				break;
			case 1:
				temp2->dir = right;
				break;
			case 2:
				temp2->dir = up;
				break;
			case 3:
				temp2->dir = left;
				break;
			}
			temp2->pre = headNode;
			if (coordEqu(temp2->coord, foodPos))
			{
				node temp = temp2;
				while (temp->pre != NULL)
				{
					temp = temp->pre;
					stepCount++;
				}
				temp = temp2;
				for (int j = stepCount - 1; j >= 0 && temp != NULL; j--)
				{
					path[j] = temp->dir;
					temp = temp->pre;
				}
				return yes;
			}
			if (!isStepBlockWall(temp2->coord) && visit[temp2->coord.X][temp2->coord.Y] != yes && !isBlockSelf(temp2->coord) && !coordEqu(temp2->coord, headPointer->coord))
			{
				node newNode = (node)malloc(sizeof(struct _node));
				newNode->coord.X = temp2->coord.X;
				newNode->coord.Y = temp2->coord.Y;
				newNode->dir = temp2->dir;
				push(headNode, newNode, temp1);
				nodeCount++;
				visit[temp2->coord.X][temp2->coord.Y] = yes;
			}
		}
		pop(&headNode);
	}
	return no;
}

int isStepBlockWall(COORD coord)
{
	for (int i = 0; i < obtCount; i++)
	{
		if (coordEqu(coord, obtPos[i]))
			return yes;
	}
	if (levels == 3)
	{
		for (int i = 0; i < bombCount; i++)
		{
			if (coordEqu(coord, bombPos[i]))
				return yes;
		}
	}
	for (int i = 0; i < drugCount; i++)
	{
		if (coordEqu(coord, drugPos[i]))
			return yes;
	}
	if (coord.Y == 0)
		return yes;
	else if (coord.Y == 25)
		return yes;
	else if (coord.X == 0)
		return yes;
	else if (coord.X == 52)
		return yes;
	else
		return no;
}

int eatBomb()
{
	for (int i = 0; i < bombCount; i++)
	{
		if (coordEqu(headPointer->coord, bombPos[i]))
		{
			PlaySound(TEXT("blockWall.wav"), NULL, SND_FILENAME | SND_ASYNC);
			score /= 2;
			printData();
			bombPos[i].X = 0;
			bombPos[i].Y = 0;
			if (snakeCount > 8)
			{
				snakeCount /= 2;
				return yes;
			}
			else
			{
				snakeCount = 0;
				return yes;
			}
		}
	}
	return no;
}

