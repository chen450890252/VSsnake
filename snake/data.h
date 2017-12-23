#pragma once
#include <Windows.h>
#include <conio.h>
#include <rpc.h>
#include <stdio.h>

void initHandle();
void initData();
enum {no, yes};
enum {up, down, left, right};
enum {tFood, tDrug, tAmaGrass};
typedef struct s
{
	COORD coord;
	struct s *next;
	struct s *pre;
}snake;
snake *headPointer;
snake *tailPointer;
int currentDirection;
HANDLE handle;
int hasFood;
COORD foodPos, scorePos, top;
COORD drugPos[50];
int drugCount;
int score, scoreRule;