#pragma once
#include "data.h"


int scoreSort(FILE *file, char *filePath, int array[]);
int coordEqu(COORD coord1, COORD coord2);
void createNoEquCoordWithOther(COORD *coord, int type);