#pragma once
#include "data.h"
#include "snaevent.h"
void createFirstPage();
void enterIntoGame();
void gameOver();
void createFood();
void printData();
void createDrug();
int coordEqu(COORD coord1,COORD coord2);
void createNoEquCoordWithOther(COORD *coord, int type);
void initScene();