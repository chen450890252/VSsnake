#pragma once
#include <Windows.h>
#include <conio.h>
#include <rpc.h>
#include <stdio.h>

void initHandle();
void initData();

//�൱��һ��bool����
enum {no, yes};

//���ڱ�ʾ����
enum {up, down, left, right};

//���ڱ�ʾ���࣬����Ե�ʳ����ݡ�û�Ե�����
enum {tFood, tDrug, tAmaGrass, tNull};

//�ߵĽṹ�壬����һ�����꣬�Լ�����ָ�룬��˫������
typedef struct s
{
	COORD coord;
	struct s *next;
	struct s *pre;
}snake;

//�ߵ�ͷָ��
snake *headPointer;

//�ߵ�βָ�룬��Ҫ������ɾ��β���ڵ�
snake *tailPointer;

//���ڱ������ڵ���ͷ����
int currentDirection;

//���������꺯��ʹ�õ�
HANDLE handle;

//�����ж���û��ʳ����ڣ����û�У���������һ��ʳ��
int hasFood;

//�������꣬��ʳ����������а�
COORD foodPos, scorePos, top;
COORD drugPos[50];

//���ݵĸ������ߵĽ���
int drugCount, snakeCount;

//�������Լ����Ʒ����Ӽ��ĸ�������
int score, addRule, subRule;