CC=gcc --std=c99 -g

all: test_ht dijkstra

test_ht: test_hash_table.c hash_table.o dynarray.o list.o
	$(CC) test_hash_table.c hash_table.o dynarray.o list.o -o test_ht

list.o: list.c list.h
	$(CC) -c list.c

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

hash_table.o: hash_table.c hash_table.h
	$(CC) -c hash_table.c

dijkstra: dijkstra.c pq.o dynarray.o
	$(CC) dijkstra.c pq.o dynarray.o -o dijkstra

pq.o: pq.c pq.h
	$(CC) -c pq.c


clean:
	rm -f *.o test_ht dijkstra
	rm -f *.dSYM/
