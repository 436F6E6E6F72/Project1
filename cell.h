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

typedef struct cell CELL;

extern CELL *newCELL(void);
extern void setCELL(CELL*, int, int, int);


#endif
