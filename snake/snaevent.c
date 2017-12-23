#include "snaevent.h"

//��ʼ������
void drawSnake(int x)
{
	snake *tempSnake = headPointer;
	while (tempSnake->next != NULL)
	{
		SetConsoleCursorPosition(handle, tempSnake->coord);
		SetConsoleTextAttribute(handle, x);
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
	else if (currentDirection == up && headPointer->coord.Y == 0)
		return yes;
	else if (currentDirection == down && headPointer->coord.Y == 25)
		return yes;
	else if (currentDirection == left && headPointer->coord.X == 0)
		return yes;
	else if (currentDirection == right && headPointer->coord.X == 52)
		return yes;
	else if (isBlockSelf(headPointer->coord))
		return yes;
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

//�ж����Ƿ�Ե�ʳ�������һϵ�����ݲ���
int eatFood()
{
	if (coordEqu(headPointer->coord, foodPos))
	{
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

//�ж��Ƿ�Ե��ǻ۲ݣ��������Զ�Ѱ·
int eatAmaGrass()
{
	if (searchPath(headPointer->coord))
	{
		return yes;
	}
	else
	{
		return no;
	}
}

int searchPath(COORD coord)
{
	if (!haveFound && coordEqu(coord, foodPos))
	{
		haveFound = yes;
		return yes;
	}
	else if (currentDirection != down && !haveFound && !compareWithOba(coord, 'y', -1))
	{
		currentDirection = up;
		path[stepCount] = up;
		stepCount++;
		coord.Y--;
		if (!searchPath(coord))
		{
			stepCount--;
		}
	}
	else if(currentDirection != left && !haveFound && !compareWithOba(coord, 'x', 2))
	{
		currentDirection = right;
		path[stepCount] = right;
		stepCount++;
		coord.X += 2;
		if (!searchPath(coord))
		{
			stepCount--;
		}
	}
	else if(currentDirection != up && !haveFound && !compareWithOba(coord, 'y', 1))
	{
		currentDirection = down;
		path[stepCount] = down;
		stepCount++;
		coord.Y++;
		if (!searchPath(coord))
		{
			stepCount--;
		}
	}
	else if (currentDirection != right && !haveFound && !compareWithOba(coord, 'x', -2))
	{
		currentDirection = left;
		path[stepCount] = left;
		stepCount++;
		coord.X -= 2;
		if (!searchPath(coord))
		{
			stepCount--;
		}
	}
	else if(!haveFound)
	{
		return no;
	}
	else
	{
		return yes;
	}
}
//ִ���жϳԵ�ʲô�����ĺ����������д�ӡ����
void eat()
{
	if (eatFood())
	{
		addHead();
	}
	else if (eatDrug())
	{
		deleteTail();
		deleteTail();
		deleteTail();
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
	}
	else if(eatAmaGrass())
	{ 
		for (int i = 0; i < stepCount; i++)
		{
			currentDirection = path[i];
			addHead();
			deleteTail();
			Sleep(200);
		}
	}
	else 
	{
		addHead();
		deleteTail();
	}
}

int compareWithOba(COORD coord, char type, int change)
{
	switch (type)
	{
	case 'x':
		coord.X += change;
		break;
	case 'y':
		coord.Y += change;
		break;
	default:
		break;
	}
	for (int i = 0; i < drugCount; i++)
	{
		if (coordEqu(coord, drugPos[i]))
			return yes;
	}
	if (coord.X == 2 || coord.X == 54 || coord.Y == 0 || coord.Y == 25)
		return yes;
	else	
		return no;
}

