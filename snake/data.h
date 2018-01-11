#pragma once
#include <Windows.h>
#include <stdio.h>
#include <time.h>

//相当于一个bool类型
enum { no, yes };

//用于表示方向
enum { up, down, left, right };

//用于表示种类，比如吃到食物、毒草、没吃到东西
enum { tFood, tDrug, tAmaGrass, tNull, tObt, tBomb };

//蛇的结构体，包含一个坐标，以及两个指针，做双向链表
typedef struct s
{
	COORD coord;
	struct s *next;
	struct s *pre;
}snake;

typedef struct _node
{
	COORD coord;
	int dir;
	struct _node *pre;
	struct _node *next;
}*node;

void initHandle(HANDLE *handle);