CC=gcc --std=c99 -g

all: avl

avl: avl.o test_avl.c
	$(CC) avl.o test_avl.c -o avl

avl.o: avl.c avl.h
	$(CC) -c avl.c

clean:
	rm -f *.o avl
