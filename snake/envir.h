#pragma once
#include "data.h"
#include "snaevent.h"
#include <time.h>
void createFirstPage();
void initScene();
int gameOver();
void enterIntoFirstPage();
void printData();
void selectMode();
void createFood();
void createDrug();
void createAmaGrass();
int scoreSort(FILE *file, char *filePath, int array[]);
int coordEqu(COORD coord1,COORD coord2);
void createNoEquCoordWithOther(COORD *coord, int type);
void selectLevel();
void createObt();