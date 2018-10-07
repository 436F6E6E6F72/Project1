/*
STACK Implementation File
This is file contains the implementation for the stack.h header file

File author: Connor Adams
*/

#include "stack.h"
#include "da.h"

struct stack
{
	DA *dynamicArr;
	void (*displayMethod)(void *,FILE *);
	void (*freeMethod)(void *);
	int debugFlag;
};

// Creates a new STACK struct
STACK *newSTACK(void)
{
	STACK *newST;
	newST = (STACK *) malloc(sizeof(STACK));
	newST->dynamicArr = newDA();
	newST->debugFlag = 0;
	newST->freeMethod = NULL;
	newST->displayMethod = NULL;
	return newST;
}

// Stores the diplay method in the STACK via the DA
void setSTACKdisplay(STACK *items,void (*dpMethod)(void *dpMethod,FILE *))
{
	setDAdisplay(items->dynamicArr, dpMethod);
	items->displayMethod = dpMethod;
}

// Stores the free method in the STACK via the DA
void setSTACKfree(STACK *items,void (*freeMethod)(void *))
{
	setDAfree(items->dynamicArr, freeMethod);
	items->freeMethod = freeMethod;
}

// Adds a value onto the stack
void push(STACK *items, void *value)
{
	insertDAback(items->dynamicArr, value);
}

// Pops the next value from the stack
void *pop(STACK *items)
{
	return removeDAback(items->dynamicArr);
}

// Shows what is next to be popped
void *peekSTACK(STACK *items)
{
	return getDA(items->dynamicArr, sizeDA(items->dynamicArr)-1);
}

// Returns how many items are on the stack
int sizeSTACK(STACK *items)
{
	return sizeDA(items->dynamicArr);
}

// Shows the items in the stack in reverse order they were pushed, so index order
void displaySTACK(STACK *items, FILE *fp)
{
	if (items->debugFlag == 1)
	{
		displayDA(items->dynamicArr, fp);
		return;
	}
	else if (items->debugFlag == 2)
	{
		debugDA(items->dynamicArr, items->debugFlag);
		displayDA(items->dynamicArr, fp);
		return;
	}
	fprintf(fp, "|");
	for (int i = sizeDA(items->dynamicArr) - 1; i > -1; i--)
	{
		if (i < sizeDA(items->dynamicArr) - 1)
			fprintf(fp, ",");
		if (items->displayMethod == NULL)
			fprintf(fp, "@%p", getDA(items->dynamicArr, i));
		else
			items->displayMethod(getDA(items->dynamicArr, i), fp);
	}
	fprintf(fp, "|");
}

// Shows the items in the order the debug mode dictates
int debugSTACK(STACK *items, int level)
{
	int prevDebug = items->debugFlag;
	items->debugFlag = level;
	return prevDebug;
}

// Frees the data with the given method
void freeSTACK(STACK *items)
{
	if (items->freeMethod != NULL)
	{
		freeDA(items->dynamicArr);
		items->freeMethod(items);	
	}
}
