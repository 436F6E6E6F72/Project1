/*
Maze Implementation File
This is file contains the implementation for the maze.h header file

File author: Connor Adams
*/

#include "maze.h"
#include "cell.h"
#include "stack.h"

long int random(void);
void srandom(unsigned int seed);

struct maze
{
	int rows, columns, seed;
	void ***cellHolder;
};

void saveMAZE(MAZE *maze, char *output)
{
	FILE *fptr = fopen( output, "w+");
	printf("Starting save\n");
	fprintf(fptr, "%d %d\n", maze->rows, maze->columns);

	int x = 0, y = 0;
	for (x = 0; x < maze->rows; x++)
	{
		for (y = 0; y < maze->columns; y++)
		{
			char* returnVal = wallsCELL((CELL*)maze->cellHolder[x][y]);
			fprintf(fptr, "%s ", returnVal);
			free(returnVal);
		}
		fprintf(fptr, "\n");

	}
	fclose(fptr);
	printf("Finished saving\n");
}

// Just inserts a cell into the maze
void insertCELL(MAZE *maze, CELL *cell, int x, int y)
{
	maze->cellHolder[x][y] = (void*)cell;
}

// Reads a given made file
MAZE *readMAZE(char *input)
{
	MAZE *rMAZE;
	FILE *fptr = fopen(input, "r");
	printf("Starting read\n");
	int rows = -1, cols = -1, x = 0, y = 0;
	char buf[10];
	if (fptr) {
		printf("Opened\n");
		while (fscanf(fptr, "%s", buf) != EOF)
		{
			if (rows == -1)
			{
				rows = atoi(buf);
			}
			else if (cols == -1)
			{
				cols = atoi(buf);
				rMAZE = newMAZE(rows, cols, 1);
			}
			else
			{
				insertCELL(rMAZE, newCELL(x, y), x, y);
				setWallsCELL(rMAZE->cellHolder[x][y], buf);
				if (y < cols - 1)
					y++;
				else
				{
					y = 0;
					x++;
				}
			}
		}
		fclose(fptr);
	}
	saveMAZE(rMAZE, "test2.data");
	return rMAZE;
}

// Sets the generation seed
void setSeedMAZE(MAZE *maze, int seed)
{
	maze->seed = seed;
}

// Displays the maze
void displayMAZE(MAZE *maze)
{
	int x = 0, y = 0;
	for (x = 0; x < maze->rows; x++)
	{
		// Print top wall
		for (y = 0; y < maze->columns; y++)
		{
			if (x == 0)
				printf("----");
			if (x == 0 && y == maze->columns - 1)
				printf("-");
		}
		printf("\n");
		// Populate each cell and add walls
		for (y = 0; y < maze->columns; y++)
		{
			if (y == 0 && x != 0) // Left bound wall
				printf("|");
			else if (y == 0 && x == 0)
				printf(" ");
			char* walls = wallsCELL(maze->cellHolder[x][y]); // Pull the wall vals
			//printf("'%s'", walls);
			int cellVal = valueCELL(maze->cellHolder[x][y]); // Pull the cell val
			if (cellVal > -1)
				printf(" %d ", cellVal); // Display the val if it exists
			else
				printf("   "); // If not display blank space
			if ((walls[1] == '1' && y != maze->columns - 1) || (y == maze->columns - 1 && x != maze->rows - 1)) // If the right wall exists display it
				printf("|");
			else
				printf(" ");
			free(walls);
		}
		printf("\n");
		for (y = 0; y < maze->columns; y++)
		{
			if (x == maze->rows - 1)
				printf("----");
			else
			{
				printf("-");
				char* walls = wallsCELL(maze->cellHolder[x][y]);
				if (walls[2] == '1')
					printf("---");
				else
					printf("   ");
				free(walls);
			}
			if (y == maze->columns - 1)
				printf("-");
		}
	}
	printf("\n");
}

void gatherCandidates(MAZE *maze, STACK *candidates, int x, int y)
{
	while (sizeSTACK(candidates) > 0)
		pop(candidates);
	if (x > 0 && visitStateCELL(maze->cellHolder[x - 1][y]) == false) // Above
		push(candidates, maze->cellHolder[x - 1][y]);
	if (y > 0 && visitStateCELL(maze->cellHolder[x][y - 1]) == false) // Left
		push(candidates, maze->cellHolder[x][y - 1]);
	if (y < maze->columns - 1 && visitStateCELL(maze->cellHolder[x][y + 1]) == false) // Right
		push(candidates, maze->cellHolder[x][y + 1]);
	if (x < maze->rows - 1 && visitStateCELL(maze->cellHolder[x + 1][y]) == false) // Down
		push(candidates, maze->cellHolder[x + 1][y]);
	//printf("\n%d candidates", sizeSTACK(candidates));
}

// Randomly removes walls to make it into a maze
void generateMAZE(MAZE *maze)
{
	srandom(maze->seed);
	int traversed = 0, i = 0;
	STACK *traversalOrder = newSTACK(), *candidates = newSTACK();
	CELL *currentCELL = maze->cellHolder[0][0], *nexCELL = currentCELL;
	while (traversed < (maze->rows * maze->columns) - 1)
	{
		// Set the curr CELL to the next
		currentCELL = nexCELL;
		visitedCELL(currentCELL);
		// Add the current spot to the stack
		push(traversalOrder, currentCELL);
		// Gather all eligable candiates in order of value
		gatherCandidates(maze, candidates, xCell(currentCELL), yCell(currentCELL));
		int size = sizeSTACK(candidates);
		// If there are no avaliable candidates pop traversed and check it
		while (size == 0)
		{
			if (sizeSTACK(traversalOrder) > 0)
			{
				//printf("POPBACK");
				currentCELL = pop(traversalOrder);
				gatherCandidates(maze, candidates, xCell(currentCELL), yCell(currentCELL));
				size = sizeSTACK(candidates);
			}
			else
			{
				printf("\n\nNo more candidates\n\n");
				break;
			}
		}
		// Generate which one is next randomly
		int nextNum = random() % sizeSTACK(candidates);
		int pops = sizeSTACK(candidates) - nextNum;
		// Pop until the cell is reached
		for (i = 0; i < pops; i++)
		{
			nexCELL = pop(candidates);
		}
		removeWall(currentCELL, nexCELL);

		for (i = 0; i < sizeSTACK(candidates); i++)
		{
			pop(candidates);
		}
		traversed++;
	}
}

// Creates a new MAZE struct
MAZE *newMAZE(int rows, int cols, int seed)
{
	MAZE *newMAZE = (MAZE*)malloc(sizeof(MAZE));
	newMAZE->rows = rows;
	newMAZE->columns = cols;
	printf("Creating a maze of size %d x %d\n", rows, cols);
	// Create a 1-D array of row pointers
	newMAZE->cellHolder = malloc(sizeof(void**) * rows);
	for (int x = 0; x < rows; x++)
	{
		//printf("%d", x);
		// Create each row
		newMAZE->cellHolder[x] = malloc(sizeof(void*) * cols);
		for (int y = 0; y < cols; y++)
		{
			// Populate it
			insertCELL(newMAZE, newCELL(x, y), x, y);
			//printf("%d ", y);
		}
		//printf("\n");
	}
	printf("\nCreated maze\n");
	newMAZE->seed = seed;
	generateMAZE(newMAZE);
	return newMAZE;
}
