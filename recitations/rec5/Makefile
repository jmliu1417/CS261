CC=gcc --std=c99 -g

all: parentheses find_sqrt

parentheses: parentheses.c char_stack.c
	$(CC) parentheses.c char_stack.c -o parentheses

find_sqrt: find_sqrt.c
	$(CC) find_sqrt.c -o find_sqrt

clean:
	rm -f *.o parentheses find_sqrt 
