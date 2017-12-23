#pragma once
#include "snaevent.h"
#include "envir.h"
void drawSnake()
{
	snake *tempSnake = headPointer;
	while (tempSnake->next != NULL)
	{
		SetConsoleCursorPosition(handle, tempSnake->coord);
		printf("¡ñ");
		tempSnake = tempSnake->next;
	}
	SetConsoleCursorPosition(handle, tempSnake->coord);
	printf("¡ñ");
}

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

int isSnakeDie()
{
	if (currentDirection == up && headPointer->coord.Y == 0)
		return yes;
	else if (currentDirection == down && headPointer->coord.Y == 25)
		return yes;
	else if (currentDirection == left && headPointer->coord.X == 0)
		return yes;
	else if (currentDirection == right && headPointer->coord.X == 52)
		return yes;
	//    else if(isBlockSelf(headPointer->coord))
	//        return yes;
	else
		return no;
}

int isBlockSelf(COORD coord)
{
	snake *temp = headPointer;
	temp = temp->next;
	while (temp->next != NULL)
	{
		if (temp->coord.X == coord.X && temp->coord.Y == coord.Y)
			return 1;
	}
	if (temp->coord.X == coord.X && temp->coord.Y == coord.Y)
		return 1;
	else
		return 0;
}

void eatFood()
{
}
