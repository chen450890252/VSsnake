#pragma once
#include <Windows.h>
#include <conio.h>
#include <rpc.h>
#include <stdio.h>

void initHandle();
void initData();
enum {yes, no};
enum {up, down, left, right};
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
COORD food;