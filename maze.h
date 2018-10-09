/*
Maze Header File
The purpose of this file is relatively simple, it is a header
File author: Connor Adams
*/

#ifndef __MAZE_INCLUDED__
#define __MAZE_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct maze MAZE;

extern MAZE *newMAZE(int, int, int);
extern void saveMAZE(MAZE*, char*);
extern MAZE *readMAZE(char*);
extern void displayMAZE(MAZE*);
extern void generateMAZE(MAZE*);
extern MAZE *solveMAZE(MAZE*);

#endif
