#include "data.h"

//��ʼ������
void drawSnake()
{
	snake *tempSnake = headPointer;
	while (tempSnake->next != NULL)
	{
		SetConsoleCursorPosition(handle, tempSnake->coord);
		printf("��");
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

//ִ���жϳԵ�ʲô�����ĺ���������������ظ�main����
int eat()
{
	if (eatFood())
		return tFood;
	else if (eatDrug())
		return tDrug;
	else return tNull;
}