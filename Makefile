OBJS = da.o stack.o maze.o cell.o options.o 
OOPTS = -Wall -Wextra -g -std=c99 -c 
LOPTS = -Wall -Wextra -g 

all : amaze

amaze : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o amaze

da.o : da.h da.c
	gcc $(OOPTS) da.c

stack.o : stack.h stack.c
	gcc $(OOPTS) stack.c

cell.o : cell.h cell.c
	gcc $(OOPTS) cell.c

maze.o : maze.h maze.c
	gcc $(OOPTS) maze.c

options.o : options.c da.h stack.h maze.h cell.h
	gcc $(OOPTS) options.c

test : amaze
	./amaze

valgrind : amaze
	valgrind amaze

clean:
	rm -f $(OBJS) amaze
