#pragma once
#include <Windows.h>
#include <conio.h>
#include <rpc.h>
#include <stdio.h>

void initHandle();
void initData();
void initCoord();

//相当于一个bool类型
enum {no, yes};

//用于表示方向
enum {up, down, left, right};

//用于表示种类，比如吃到食物、毒草、没吃到东西
enum {tFood, tDrug, tAmaGrass, tNull, tObt, tBomb};

//蛇的结构体，包含一个坐标，以及两个指针，做双向链表
typedef struct s
{
	COORD coord;
	struct s *next;
	struct s *pre;
}snake;

//蛇的头指针
snake *headPointer;

//蛇的尾指针，主要方便于删除尾部节点
snake *tailPointer;

//用于保存现在的蛇头方向
int currentDirection;

//句柄，给光标函数使用的
HANDLE handle;

//用于判断有没有食物和智慧草存在，如果没有，则生成另一个食物或智慧草
int hasFood, hasAmaGrass;

//各类坐标，如食物，分数，排行榜
COORD foodPos, amaGrassPos;
COORD obtPos[35], drugPos[10];



//毒草的个数、蛇的节数
int drugCount, snakeCount, obtCount;

//分数，以及控制分数加减的辅助数据

int score, addRule, subRule, grassRule;
int topScore[11];

int modeSelect;


typedef struct _node
{
	COORD coord;
	int dir;
	struct _node *pre;
	struct _node *next;
}*node;
int path[100];
int count;

char *filePath;
FILE *file;
//关卡
int level;

int speed, speedControl;


