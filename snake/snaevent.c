#include "snaevent.h"

//��ʼ������
void drawSnake(int color)
{
	snake *tempSnake = headPointer;
	while (tempSnake->next != NULL)
	{
		SetConsoleCursorPosition(handle, tempSnake->coord);
		SetConsoleTextAttribute(handle, color);
		printf("��");
		SetConsoleTextAttribute(handle, 7);
		tempSnake = tempSnake->next;
	}
	SetConsoleCursorPosition(handle, tempSnake->coord);
	printf("��");
}

//�첽���������룬���Դ˸ı��ߵķ���
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

//�ж����Ƿ�����
//��������̫�ͣ�ײ�Լ���ײǽ
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

//�ж����Ƿ�ײ���Լ�
int isBlockSelf(COORD coord)
{
	snake *temp = headPointer;
	temp = temp->next;
	do
	{
		if (coordEqu(temp->coord,coord))
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
			return yes;
		}
	}
	return no;
}

int isBlockWall(COORD coord)
{
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

//�ж����Ƿ�Ե�ʳ�������һϵ�����ݲ���
int eatFood()
{
	if (coordEqu(headPointer->coord, foodPos))
	{
		PlaySound(TEXT("eatfood.wav"),NULL,SND_ASYNC|SND_FILENAME);
		addRule++;
		score += addRule;
		printData();
		hasFood = no;
		snakeCount++;
		return yes;
	}
	return no;
}

//�ж����Ƿ�Ե����ݣ�������һϵ�����ݲ���
int eatDrug()
{
	for (int i = 0; i < drugCount; i++)
	{
		if (coordEqu(headPointer->coord, drugPos[i]))
		{
			PlaySound(TEXT("drug.wav"), NULL, SND_FILENAME|SND_ASYNC);
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

//ִ���жϳԵ�ʲô�����ĺ����������д�ӡ����
void eat()
{
	if (eatFood())
	{
		addHead(10);
	}
	else if (eatDrug())
	{
		Sleep(200);
		drawSnake(13);
		Sleep(200);
		drawSnake(15);
		Sleep(200);
		drawSnake(13);
		Sleep(200);
		drawSnake(15);
		Sleep(200);
		drawSnake(13);
		Sleep(200);
		drawSnake(15);
		Sleep(200);
		drawSnake(10);
		deleteTail();
		deleteTail();
		deleteTail();
	}
	else if (eatAmaGrass())
	{
		for (int i = 0; i < count; i++)
		{
			currentDirection = path[i];
			int color = i % 7 + 9;
			addHead(color);
			deleteTail();
			Sleep(200);
			if (eatFood())
			{
				addHead(10);
				deleteTail();
				count = 0;
				return;
			}
			else if (isSnakeDie())
			{
				gameOver();
				return;
			}
		}
	}
	else
	{
		addHead(10);
		deleteTail();
	}
}

//�ж��Ƿ�Ե��ǻ۲ݣ��������Զ�Ѱ·
int eatAmaGrass()
{
	if (coordEqu(headPointer->coord, amaGrassPos))
	{
		PlaySound(TEXT("grass.wav"),NULL, SND_FILENAME|SND_ASYNC);
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
					count++;
				}
				temp = temp2;
				for (int j = count - 1; j >= 0 && temp != NULL; j--)
				{
					path[j] = temp->dir;
					temp = temp->pre;
				}
				return yes;
			}
			if (!isEatDrug(temp2->coord) && !isStepBlockWall(temp2->coord) && visit[temp2->coord.X][temp2->coord.Y] != yes && !isBlockSelf(temp2->coord) && !coordEqu(temp2->coord, headPointer->coord))
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
