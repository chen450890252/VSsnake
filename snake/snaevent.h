#pragma once
#include "envir.h"
#include "list.h"
#include "queue.h"
void drawSnake(int x);
void changeDirection();
int isSnakeDie();
int eatFood();
int eatDrug();
int eatAmaGrass();
void eat();
int searchLoad(node start, node end);


