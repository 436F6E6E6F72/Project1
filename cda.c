/*
Circular Dynamic Array Implementation File
This is file contains the implementation for the cda.h header file

File author: Connor Adams
*/

#include "cda.h"

struct cda
{
	void **data;
	int capacity, sizeDA, debugFlag, startIndex;
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
};

// This function is just going to double the size of a dynamic array
void doubleCDAStorage(CDA *items)
{
	void **holder = (void**)malloc(sizeof(void*) * items->capacity);
	for (int i = 0; i < items->sizeDA; i++)// This is going to re-index at 0
		holder[i] = items->data[(i + items->startIndex) % (items->capacity)];
	items->capacity *= 2;
	free(items->data);
	items->data = (void**)malloc(sizeof(void*) * items->capacity);
	for (int i = 0; i < items->sizeDA; i++)
	{
		items->data[i] = holder[i];
	}
	free(holder);
	items->startIndex = 0;
}

// Function made for halving storage size for the remove function
void halfCDAStorage(CDA *items)
{
	void **holder = (void**)malloc(sizeof(void*) * items->capacity);
	for (int i = 0; i < items->sizeDA; i++)
	{ // This is going to re-index at 0
		holder[i] = items->data[(i + items->startIndex) % items->capacity];
	}
	items->capacity /= 2;
	free(items->data);
	items->data = (void**)malloc(sizeof(void*) * items->capacity);
	for (int i = 0; i < items->sizeDA; i++)
	{
		items->data[i] = holder[i];
	}
	items->startIndex = 0;
	free(holder);
}

// Creates a new CDA and returns it
CDA *newCDA(void)
{
	CDA *newCDA;
	newCDA = (CDA *)malloc(sizeof(CDA));
	newCDA->data = (void**)malloc(sizeof(void*));
	newCDA->capacity = 1;
	newCDA->sizeDA = 0;
	newCDA->debugFlag = 0;
	newCDA->startIndex = 0;
	newCDA->freeMethod = NULL;
	newCDA->displayMethod = NULL;
	return newCDA;
}

// Takes in and stores the display method for CDA
void setCDAdisplay(CDA *items, void(*displayInput)(void *, FILE *))
{
	items->displayMethod = displayInput;
}

// Takes in and stores the free method for CDA
void setCDAfree(CDA *items, void(*freeInput)(void *))
{
	items->freeMethod = freeInput;
}

// Returns the value at index, corrected for index start num
void *getCDA(CDA *items, int index)
{
	assert(index >= 0 && index < items->sizeDA);
	return (items->data[(items->startIndex + index) %items->capacity]);
}

// Inserts a value at the index, corrected for index start
void insertCDA(CDA *items, int index, void *value)
{
	assert(index <= items->sizeDA && index > -1);
	if (items->sizeDA == items->capacity)
		doubleCDAStorage(items);
	// Shift into the front
	if (index == 0 && items->sizeDA > 1)
	{
		//printf("*\n");
		if (items->startIndex > 0)
			items->startIndex -= 1;
		else
			items->startIndex = items->capacity - 1;
		items->data[items->startIndex] = value;
		//printf("S: %d\n", items->startIndex);
	}
	// Just put on the end
	else if (index == items->sizeDA)
	{
		//printf("=\n");
		items->data[(items->startIndex + index) % items->capacity] = value;
	}
	else
	{
		void *holder = NULL;
		void *prevValue = value;
		// Between 0 and half so shift to front
		if (index < sizeCDA(items) / 2 && sizeCDA(items) > 1)
		{
			for (int i = index-1; i >= 0; i--)
			{
				holder = items->data[(i + items->startIndex) % items->capacity];
				items->data[(i + items->startIndex) % items->capacity] = prevValue;
				prevValue = holder;
			}
			if (items->startIndex > 0)
				items->startIndex -= 1;
			else
				items->startIndex = items->capacity - 1;
			items->data[items->startIndex] = prevValue;
		}
		// Between half+1 and end so shift to end
		else
		{
			for (int i = index; i <= items->sizeDA; i++)
			{
				holder = items->data[(i + items->startIndex) % items->capacity];
				items->data[(i + items->startIndex) % items->capacity] = prevValue;
				prevValue = holder;
			}
		}
	}
	items->sizeDA++;
}

// Removes data at index, corrected for index start
void *removeCDA(CDA *items, int index)
{
	assert(index < items->sizeDA && index > -1);
	void *returnVal = NULL;
	// Just remove and shift
	if (index == 0)
	{
		returnVal = items->data[items->startIndex];
		if (items->startIndex < items->capacity - 1)
			items->startIndex += 1;
		else
			items->startIndex = 0;
	}
	// Take the end off
	else if (index == items->sizeDA)
	{
		returnVal = items->data[(items->startIndex + index) % items->capacity];
	}
	else
	{
		// Between half and front, so just shift forward and correct
		if (index < sizeCDA(items) / 2 && sizeCDA(items) > 1)
		{
			returnVal = items->data[(items->startIndex + index) % items->capacity];
			for (int i = 0; i < index; i++)
			{
				items->data[(items->startIndex + index - i) % items->capacity] = items->data[(items->startIndex + index - i - 1) % items->capacity];
			}
			if (items->startIndex < items->capacity - 1)
				items->startIndex += 1;
			else
			{
				items->startIndex = 0;
			}
		}
		// Between half and the end so just shift
		else
		{
			returnVal = items->data[(items->startIndex + index) % items->capacity];
			for (int i = index; i < items->sizeDA - 1; i++)
			{
				items->data[(items->startIndex + i) % items->capacity] = items->data[(items->startIndex + i + 1) % items->capacity];
			}
		}
	}
	items->sizeDA--;
	while (((float)(items->sizeDA / (float)items->capacity) < 0.25f && items->capacity > 1))
		halfCDAStorage(items);
	return returnVal;
}

// Returns the size of the given CDA
int sizeCDA(CDA *items)
{
	return items->sizeDA;
}

// Combines the donor into the recipient
void unionCDA(CDA *recipient, CDA *donor)
{
	for (int i = 0; i < donor->sizeDA; i++)
	{
		//insertCDA(recipient, sizeCDA(recipient), removeCDAfront(donor));
		insertCDA(recipient, sizeCDA(recipient), getCDA(donor, i));
	}
	donor->data = (void**)malloc(sizeof(void*));
	donor->sizeDA = 0;
	donor->capacity = 1;
	donor->startIndex = 0;
}

// Uses the stored display method to display the data
void displayCDA(CDA *items, FILE *fp)
{
	fprintf(fp, "(");
	for (int i = 0; i < items->sizeDA; i++)
	{
		if (i != 0)
			fprintf(fp, ",");
		if (items->displayMethod == NULL)
			fprintf(fp, "@%p", items->data[(items->startIndex + i) % items->capacity]);
		else
			items->displayMethod(items->data[(items->startIndex + i) % items->capacity], fp);

	}
	if (items->debugFlag > 0)
	{
		if (items->sizeDA > 0)
			fprintf(fp, ",(%d)", items->capacity - sizeCDA(items)); //items->sizeDA);
		else
			fprintf(fp, "(%d)", items->capacity - sizeCDA(items)); //items->sizeDA);
	}
	fprintf(fp, ")");
}

// Outputs the stored values followed by the number of unfilled slots
int debugCDA(CDA *items, int level)
{
	int prevVal = items->debugFlag;
	items->debugFlag = level;
	return prevVal;
}

void freeCDA(CDA *items)
{
	if (items->freeMethod != NULL)
	{
		for (int i = 0; i < items->sizeDA; i++)
		{
			items->freeMethod(items->data[(items->startIndex + i) % items->capacity]);
		}
		free(items->data);
		items->freeMethod(items);
	}
}

// Replaces the value or if == size makes a new one
void *setCDA(CDA *items, int index, void* value)
{
	assert(index >= -1 && index <= items->capacity);
	if (items->sizeDA == index)
	{
		insertCDA(items, index, value);
		return NULL;
	}
	else if (index == -1)
	{
		insertCDAfront(items, value);
		return NULL;
	}
	else if (index > items->sizeDA)
		return NULL;
	else
	{
		void *returnVal = items->data[(items->startIndex + index) % items->capacity];
		items->data[(items->startIndex + index) % items->capacity] = value;
		return returnVal;
	}
}
