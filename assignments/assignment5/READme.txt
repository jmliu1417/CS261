Jamie Liu - liujam - 924463192

2. hash_table.c implements the functions necessary for hash table functions.
This includes:
    ht_create - creates and allocates an empty hash table
    ht_free - frees the memory of the hash table
    ht_isempty - returns 1 if hash table is empty, 0 otherwise
    ht_size - returns ht_size
    ht_hash_func - calculates index of the specific element to insert (its unique index)
    rehash - creates and allocates a new dynarray in case items need to be rehashed
    ht_insert - inserts a new element into the hash table
    ht_lookkup - searches for an element w specificed key
    ht_removes - removes element

dijkstra.c includes the reading the file of paths and finding the shortest path through
the dijkstra depth-first algorithm. This implementation uses an adjacency matrix.
    readGraph - reads the graph information into the the adjacency matrix

no limitations, all functions should run normally without memory leaks or errors.

3. Instructions: 
    In the terminal, type "make"
    then to run the hash table testing, type  
        "test_ht"

    to run dijkstra's, type
    "./dijkstra"

type "valgrind " before either to ensure there's no memory leaks or errors.