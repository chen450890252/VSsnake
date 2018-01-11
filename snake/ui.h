#pragma once
#include "snake.h"
void initUIData();
void createFirstPage();
void initScene();
int gameOver();
void printData();
int selectMode();
void createFood();
void createDrug();
void createAmaGrass();
void createObt();
void createBomb();
int selectLevels();
void changeSpeed(int *i);
int isWin();
void flashDrug();