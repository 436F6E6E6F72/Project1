/*
Queue Header File - Based on Circular Dynamic Array base
The purpose of this file is relatively simple, it is a header
Foundation for the file is provided at:
http://beastie.cs.ua.edu/cs201/assign-queue.html
File author: Connor Adams
*/

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct queue QUEUE;

extern QUEUE *newQUEUE(void);
extern void  setQUEUEdisplay(QUEUE *,void (*)(void *,FILE *));
extern void  setQUEUEfree(QUEUE *,void (*)(void *));
extern void  enqueue(QUEUE *items,void *value);
extern void *dequeue(QUEUE *items);
extern void *peekQUEUE(QUEUE *items);
extern void  displayQUEUE(QUEUE *items,FILE *fp);
extern int   debugQUEUE(QUEUE *items,int level);
extern void  freeQUEUE(QUEUE *items);
extern int   sizeQUEUE(QUEUE *items);

#endif
