#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "maze.h"

/* options */
int seed = 1; // The seed the random generator will use

int ProcessOptions(int, char **);
void Fatal(char *, ...);

int main(int argc, char **argv)
{
	int argIndex;

	if (argc == 1) Fatal("%d arguments!\n", argc - 1);

	argIndex = ProcessOptions(argc, argv);

	if (argIndex != argc)
	{
		int i;
		printf("Remaining arguments:\n");
		for (i = argIndex; i < argc; ++i)
			printf("    %s\n", argv[i]);
	}

	return 0;
}

void Fatal(char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "An error occured: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(-1);
}

int ProcessOptions(int argc, char **argv)
{
	int start, argIndex;
	int argsUsed;
	char *arg;

	argIndex = 1;

	while (argIndex < argc && *argv[argIndex] == '-')
	{
		/* check if stdin, represented by "-" is an argument */
		/* if so, the end of options has been reached */
		if (argv[argIndex][1] == '\0') return argIndex;

		argsUsed = 0;
		start = argIndex;


		/* advance argIndex to point to the first argument to the option */
		if (argv[start][2] == '\0')
		{
			arg = argv[start + 1];
			++argIndex;
		}
		else
		{
			/* first arg is connected to option, so don't advance */
			arg = argv[start] + 2;
		}

		switch (argv[start][1])
		{
		/*
		CASES:
		- v	give author's name; the program exits immediately after the name is printed
		- s III OOO	solve the maze in file III placing solution in file OOO
		- c RRR CCC MMM	create a maze with RRR rows and CCC columns, placing the maze in file MMM
		- r NNN	seed a pseudo - random number generator with NNN; if the - r option is not given, use a random seed of 1
		- d III	draw the created maze(-c) or draw the solved maze(-s) found in file III
		*/

		case 's':
			printf("Command to solve detected\n");
			MAZE *maze = readMAZE(argv[argIndex]);
			maze = solveMAZE(maze);
			argsUsed += 2;
			break;
		case 'c':
			printf("Command to create detected\n");
			MAZE* newMA = newMAZE(atoi(argv[argIndex]), atoi(argv[argIndex + 1]), seed);
			saveMAZE(newMA, argv[argIndex+2]);
			displayMAZE(newMA);
			MAZE *solvedMA = solveMAZE(newMA);
			displayMAZE(solvedMA);
			free(newMA);
			argsUsed += 3;
			break;
		case 'r':
			//printf("Command to input seed detected\n");
			seed = atoi(arg);
			//printf("Seed is %d\n", seed);
			argsUsed += 1; // TODO: VERIFY THESE INCREMENTS
			break;
		case 'd':
			printf("Command to draw detected\n");
			MAZE *rMAZE = readMAZE(argv[argIndex]);
			displayMAZE(rMAZE);
			free(rMAZE);
			argsUsed += 1;
			break;
		case 'v':
			printf("Written by Connor Adams\n");
			break;
		default:
			fprintf(stderr, "option %s not understood\n", argv[start]);
			exit(-1);
		}

		argIndex += argsUsed;
	}

	return argIndex;
}
