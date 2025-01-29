CC=gcc --std=c99 -g

all: test_deque test_list

test_deque: test_deque.c deque.o db_list.o
	$(CC) test_deque.c deque.o db_list.o -o test_deque

deque.o: deque.c deque.h
	$(CC) -c deque.c

db_list.o: db_list.c db_list.h
	$(CC) -c db_list.c

test_list: test_list.c list.o
	$(CC) test_list.c list.o -o test_list

list.o: list.c list.h
	$(CC) -c list.c

clean:
	rm -f *.o test_deque test_list