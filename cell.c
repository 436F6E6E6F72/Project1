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
	newCELL->walls = (int*)malloc(sizeof(int*)*2);
	for (int i = 0; i < 2; i++)
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

// Sets the maze walls, mainly for reading in data
void setWallsCELL(CELL *cell, char *wallRaw)
{
	for (int i = 0; i < 2; i++)
	{
		cell->walls[i] = wallRaw[i] - '0';
	}
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

// Externally set a cell's values
void setValueCELL(CELL *cell, int val)
{
	cell->value = val;
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
	if (yDiff != 0)
	{
		if (yDiff == 1) // Left of the first
		{
			secondCELL->walls[0] = 0;
			//printf("Left \n");
		}
		else // Right of the first
		{
			firstCELL->walls[0] = 0;
			//printf("Right \n");
		}
	}
	else
	{
		if (xDiff == 1) // Above the first
		{
			secondCELL->walls[1] = 0;
			//printf("Above \n");
		}
		else // Below the first
		{
			firstCELL->walls[1] = 0;
			//printf("Below \n");
		}
	}
	visitedCELL(firstCELL);
	visitedCELL(secondCELL);
}

// Frees the cell's data
void freeCELL(CELL *cell)
{
	free(cell->walls);
	//free(cell);
}

// Returns the walls as a char* East-South
char* wallsCELL(CELL *cell)
{
	char* walls = (char*)malloc(sizeof(char*)*2);
	for (int i = 0; i < 2; i++)
	{
		if (cell->walls[i] == 1)
			walls[i] = '1';
		else
			walls[i] = '0';
	}
	return walls;
}
