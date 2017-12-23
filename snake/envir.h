#pragma once
#include "data.h"
#include "snaevent.h"
void createFirstPage();
void enterIntoGame();
void initScene();
void gameOver();

void printData();

void createFood();
void createDrug();
void createAmaGrass();

int coordEqu(COORD coord1,COORD coord2);
void createNoEquCoordWithOther(COORD *coord, int type);
