/*
Cell Header File
The purpose of this file is relatively simple, it is a header
File author: Connor Adams
*/

#ifndef __CELL_INCLUDED__
#define __CELL_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct cell CELL;

extern CELL *newCELL(int, int);
extern void setCELL(CELL*, int, int, int);
extern int valueCELL(CELL*);
extern char* wallsCELL(CELL*);
extern bool visitStateCELL(CELL*);
extern void visitedCELL(CELL*);
extern void setWallsCELL(CELL*, char*);
extern int xCell(CELL*);
extern int yCell(CELL*);
extern void removeWall(CELL*, CELL*);
extern void setValueCELL(CELL*, int);
extern void freeCELL(void*);
#endif
