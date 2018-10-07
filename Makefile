OBJS = da.o stack.o testFile.o maze.o cell.o
OOPTS = -Wall -Wextra -g -std=c99 -c 
LOPTS = -Wall -Wextra -g 

all : project0

project0 : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o project0

da.o : da.h da.c
	gcc $(OOPTS) da.c

stack.o : stack.h stack.c
	gcc $(OOPTS) stack.c

cell.o : cell.h cell.c
	gcc $(OOPTS) cell.c

maze.o : maze.h maze.c
	gcc $(OOPTS) maze.c

testFile.o : testFile.c da.h stack.h
	gcc $(OOPTS) testFile.c

test : project0
	./project0

valgrind : project0
	valgrind project0

clean:
	rm -f $(OBJS) project0
