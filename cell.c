/*
Cell Implementation File
This is file contains the implementation for the cell.h header file

File author: Connor Adams
*/

#include "cell.h"

struct cell
{
	int xLoc, yLoc, value, state; // for State 0 == normal, -1 == start, 1 == end
	bool visited;
	int *walls; // The walls are stored in an array, North, East, South, West - 1 == exists | 0 == none
};

// Creates a new CELL struct
CELL *newCELL(int x, int y)
{
	CELL *newCELL = (CELL*)malloc(sizeof(CELL*));
	newCELL->walls = (int*)malloc(sizeof(int*)*4);
	for (int i = 0; i < 4; i++)
		newCELL->walls[i] = 1; 
	newCELL->xLoc = x;
	newCELL->yLoc = y;
	newCELL->value = -1;
	newCELL->visited = false;
	return newCELL;
}

// Sets the x, y coords for the given cell
void setCELL(CELL *cell, int x, int y, int value)
{
	cell->xLoc = x;
	cell->yLoc = y;
	cell->value = value;
}

// Returns the value
int valueCELL(CELL *cell)
{
	return cell->value;
}

// Sets the visit bool to true
void visitedCELL(CELL *cell)
{
	cell->visited = true;
}

// Returns the visit state
bool visitStateCELL(CELL *cell)
{
	return cell->visited;
}

// Returns the x val of the cell
int xCell(CELL *cell)
{
	return cell->xLoc;
}

// Returns the y val of the cell
int yCell(CELL *cell)
{
	return cell->yLoc;
}

// Removes a wall between two cells
void removeWall(CELL *firstCELL, CELL *secondCELL)
{
	int xDiff = firstCELL->xLoc - secondCELL->xLoc, yDiff = firstCELL->yLoc - secondCELL->yLoc;
	printf("Removing at %d %d ", xDiff, yDiff);
	if (xDiff != 0)
	{
		if (xDiff == 1) // Left of the first
		{
			firstCELL->walls[3] = 0;
			secondCELL->walls[1] = 0;
			printf("Left \n");
		}
		else // Right of the first
		{
			firstCELL->walls[1] = 0;
			secondCELL->walls[3] = 0;
			printf("Right \n");
		}
	}
	else
	{
		if (yDiff == 1) // Above the first
		{
			firstCELL->walls[2] = 0;
			secondCELL->walls[0] = 0;

			printf("Above \n");
		}
		else // Below the first
		{
			firstCELL->walls[0] = 0;
			secondCELL->walls[2] = 0;
			printf("Below \n");
		}
	}
}

// Returns the walls as a char* N-E-S-W
char* wallsCELL(CELL *cell)
{
	char* walls = (char*)malloc(sizeof(char*)*4);
	for (int i = 0; i < 4; i++)
	{
		if (cell->walls[i] == 1)
			walls[i] = '1';
		else
			walls[0] = '0';
	}
	return walls;
}
