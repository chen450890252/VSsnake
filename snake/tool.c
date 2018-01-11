#include "tool.h"
extern COORD foodPos, amaGrassPos, obtPos[50], drugPos[50], bombPos[10];
extern int score, drugCount, bombCount, obtCount, levels;
extern snake *headPointer;

int scoreSort(FILE *file, char *filePath, int array[])
{
	int i = 0;
	int max;
	int count = 0;
	fopen_s(&file, filePath, "r");
	if (file != NULL)
	{
		int result;
		do {
			result = fscanf_s(file, "%d", &array[i]);
			i++;
			count++;
		} while (result > 0);
		fclose(file);
	}
	for (i = 0; i < count; i++)
	{
		max = array[i];
		for (int j = i + 1; j < count; j++)
		{
			if (array[j] > max)
			{
				int temp = max;
				max = array[j];
				array[j] = temp;
			}
		}
		array[i] = max;
	}
	return count;
}

int coordEqu(COORD coord1, COORD coord2)
{
	if (coord1.X == coord2.X && coord1.Y == coord2.Y)
		return yes;
	else
		return no;
}

void createNoEquCoordWithOther(COORD *coord, int type)
{
	COORD otherCoord[100];
	int i = 0;
	//根据传入的需要判断的类型，获取其他类型的所有坐标
	switch (type)
	{
	case tFood:
		for (i = 0; i < drugCount; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
		}
		for (int j = 0; j < bombCount; j++, i++)
		{
			otherCoord[i].X = bombPos[j].X;
			otherCoord[i].Y = bombPos[j].Y;
		}
		otherCoord[i].X = amaGrassPos.X;
		otherCoord[i].Y = amaGrassPos.Y;
		i++;
		break;
	case tDrug:
		for (i = 0; i < drugCount && coord != &drugPos[i]; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		if (drugCount == 1)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
		}
		for (int j = 0; j < bombCount; j++, i++)
		{
			otherCoord[i].X = bombPos[j].X;
			otherCoord[i].Y = bombPos[j].Y;
		}
		otherCoord[i].X = foodPos.X;
		otherCoord[i].Y = foodPos.Y;
		i++;
		otherCoord[i].X = amaGrassPos.X;
		otherCoord[i].Y = amaGrassPos.Y;
		i++;
		break;
	case tAmaGrass:
		for (i = 0; i < drugCount; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
		}
		for (int j = 0; j < bombCount; j++, i++)
		{
			otherCoord[i].X = bombPos[j].X;
			otherCoord[i].Y = bombPos[j].Y;
		}
		otherCoord[i].X = foodPos.X;
		otherCoord[i].Y = foodPos.Y;
		i++;
		break;
	case tBomb:
		for (i = 0; i < drugCount; i++)
		{
			otherCoord[i].X = drugPos[i].X;
			otherCoord[i].Y = drugPos[i].Y;
		}
		for (int j = 0; j < obtCount; j++, i++)
		{
			otherCoord[i].X = obtPos[j].X;
			otherCoord[i].Y = obtPos[j].Y;
		}
		for (int j = 0; j < bombCount && coord != &bombPos[i]; j++, i++)
		{
			otherCoord[i].X = bombPos[j].X;
			otherCoord[i].Y = bombPos[j].Y;
		}
		if (bombCount == 1)
		{
			otherCoord[i].X = bombPos[0].X;
			otherCoord[i].Y = bombPos[0].Y;
		}
		otherCoord[i].X = amaGrassPos.X;
		otherCoord[i].Y = amaGrassPos.Y;
		i++;
		otherCoord[i].X = foodPos.X;
		otherCoord[i].Y = foodPos.Y;
		i++;
		break;
	default:
		break;
	}
	while (1)
	{
		snake *temp = headPointer;
		int equal = no;
		while (temp->next != NULL)
		{
			if (coordEqu(temp->coord, *coord))
			{
				equal = yes;
				break;
			}
			temp = temp->next;
		}
		if (equal == no && coordEqu(temp->coord, *coord))
		{
			equal = yes;
		}
		for (int j = 0; j < i && equal == no; j++)
		{
			if (coordEqu(otherCoord[j], *coord))
			{
				equal = yes;
				break;
			}
		}
		if (equal)
		{
			(*coord).X = (rand() * 1998) % 48 + 2;
			(*coord).Y = (rand() * 1998) % 22 + 2;
			continue;
		}
		else
			break;
	}
}
