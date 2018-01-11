#pragma once
#include <Windows.h>
#include <stdio.h>
#include <time.h>

//�൱��һ��bool����
enum { no, yes };

//���ڱ�ʾ����
enum { up, down, left, right };

//���ڱ�ʾ���࣬����Ե�ʳ����ݡ�û�Ե�����
enum { tFood, tDrug, tAmaGrass, tNull, tObt, tBomb };

//�ߵĽṹ�壬����һ�����꣬�Լ�����ָ�룬��˫������
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