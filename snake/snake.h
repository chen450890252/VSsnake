#pragma once
#include "interface.h"
void initSnakeData();
void drawSnake(int x);
void changeDirection();
int isSnakeDie();
int eatFood();
int eatDrug();
int eatAmaGrass();
int eatBomb();
void eat(int speed);
int searchLoad(node start, node end);
