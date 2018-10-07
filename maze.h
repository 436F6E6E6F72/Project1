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

extern MAZE *newMAZE();
extern void buildMAZE(MAZE*, int, int);


#endif
