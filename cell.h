/*
Cell Header File 
The purpose of this file is relatively simple, it is a header
File author: Connor Adams
*/

#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct cell CELL;

extern CELL *newCELL(void);
extern void setPos(CELL, int, int);
extern void setVal(CELL, int);



#endif
