#include "data.h"

void initHandle(HANDLE *handle)
{
	*handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(*handle, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(*handle, &cci);
}