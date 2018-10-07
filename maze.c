/*
Maze Implementation File
This is file contains the implementation for the maze.h header file

File author: Connor Adams
*/

#include "maze.h"
#include "cell.h"
#include "stack.h"

struct maze
{
	int rows, columns;
	void ***cellHolder;
};

// Creates a new MAZE struct
MAZE *newMAZE(void)
{
	MAZE *newMAZE = (MAZE*)malloc(sizeof(MAZE));
	newMAZE->rows = 0;
	newMAZE->columns = 0;
	return newMAZE;
}

// Generates a maze;
void buildMAZE(MAZE *maze, int rowsInput, int colsInput)
{
	maze->rows = rowsInput;
	maze->columns = colsInput;
	maze->cellHolder = (void*)malloc(sizeof(void*) * rowsInput * colsInput);
	int x, y;
	for (y = 0; y < maze->columns; y++)
	{
		for (x = 0; x < maze->rows; x++)
		{
			maze->cellHolder[x][y] = newCELL();
			setCELL(maze->cellHolder[x][y], x, y, 0);

		}
	}
}