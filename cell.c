/*
Cell Implementation File
This is file contains the implementation for the cell.h header file

File author: Connor Adams
*/

#include "cell.h"

struct cell
{
	int xLoc, yLoc, value, state; // for State 0 == normal, -1 == start, 1 == end
	int *walls; // The walls are stored in an array, North, East, South, West - 1 == exists | 0 == none
};

// Creates a new CELL struct
CELL *newCELL(void)
{
	CELL *newCELL = (CELL*)malloc(sizeof(CELL));
	newCELL->walls = (int*)malloc(sizeof(int*)*4);
	for (int i = 0; i < 4; i++)
		newCELL->walls[i] = 1; 
	newCELL->xLoc = 0;
	newCELL->yLoc = 0;
	newCELL->value = 0;
	return newCELL;
}

// Sets the x, y coords for the given cell
void setCELL(CELL *cell, int x, int y, int value)
{
	cell->xLoc = x;
	cell->yLoc = y;
	cell->value = value;
}
