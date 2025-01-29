/*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"


/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
struct ht{
    struct dynarray* dynarray;
    int size;

};

struct ht_node{
    void* value;
    void* key;
};


/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
struct ht* ht_create(){
    /*
     * FIXME: 
     */
    struct ht* new_ht = malloc(sizeof(struct ht));
    new_ht->dynarray = dynarray_create();
    new_ht->size = 0;
    
    //create a new list at every index of dynarray
    for(int i=0; i<get_capacity(new_ht->dynarray); i++){
        struct list* list = list_create();
        dynarray_set(new_ht->dynarray, i , list);
    }
  
    return new_ht;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    /*
     * FIXME: 
     */

    int size = get_capacity(ht->dynarray);

//go through list at each dynarray, free that
    for(int i = 0; i<size; i++){
        struct list* list = dynarray_get(ht->dynarray, i);
        list_free(list);
    }
//free remaining structs
    dynarray_free(ht->dynarray);
    free(ht);
    
    return;
}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
    /*
     * FIXME: 
     */
    //check later?
//just checks size attribute
    if(ht->size!=0){
        return 0;
    }

    return 1;
}


/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 *
 * Params:
 *   ht - the hash table whose size is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return the size of the given hash table.
 */
int ht_size(struct ht* ht){
    /*
     * FIXME: 
     */
    return ht->size;
}

int compare_keys(struct ht_node* key1, struct ht_node* key2){
    if(key1->key == key2->key){
        return 0;
    }else{
        return -1;
    }
}





/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash function is passed in as a function pointer, stored in 'convert'
 * Assuming the passed in hash function is well designed.
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element used to calculate the index
 *   convert - a pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 *
 * Return:
 *   Should return the index value of 'key' in the hash table .
 */

int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */

    int index = 0;
    int hash = convert(key);

//mod for indiv index
    index = hash % get_capacity(ht->dynarray);
    return index;
}

/*
This function rehashes and creates a new dynamic array with the new amount of memory
 *
 * Params:
 *   ht - passed in hash table
 *   key - desired key
 *   conver - func pointer to conver index
 *
 * Return:
 *   returns nothing, just reads the file
 */

void rehash(struct ht* ht, void* key, int (*convert)(void*)){
//new capacity for new dynarray
    int capacity = get_capacity(ht->dynarray)*2;

//passed in new array
    struct dynarray* new_arr = dynarray_create();

    for(int i =0; i<capacity; i++){
        //reinsert lists for each index
        struct list* list = list_create();
        dynarray_insert(new_arr, list);
    }

//for the current capacity:
    for(int i=0; i<get_capacity(ht->dynarray); i++){
        struct list* list = dynarray_get(ht->dynarray, i);

        while(list_isempty(list) == 0){
            //poptop list value off stack
            struct ht_node* current = list_pop(list);
            //create new index for rehashed value
            int new_idx = convert(current->key) % capacity;

            struct list* new_list = dynarray_get(new_arr, new_idx);
            //insert at old value
            list_insert(new_list, current);
        }

        free(list);
    }
    //free values, set to new array after populating values
    dynarray_free(ht->dynarray);
    ht->dynarray = new_arr;
}

/*
 * This function should insert a given element into a hash table with a
 * specified key. Note that you cannot have two same keys in one hash table.
 * If the key already exists, update the value associated with the key.  
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */

void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    /*
     * FIXME: 
     */
//calc load factor
    int load_factor = (ht->size)/get_capacity(ht->dynarray);

    if(load_factor >= 4){
        //rehash in case
        rehash(ht, key, convert);
    }

//value of new index of new value
    int index = ht_hash_func(ht, key, convert);

//new list for specific value
    struct list* list = dynarray_get(ht->dynarray, index);

//in case the key is empty, insert the element to list and return
    if(list_find(list, key, convert) != NULL){
        struct ht_node* elem = list_find(list, key, convert);
        elem->value = value;
        return;
    }

    //otherwise, assign new value and insert
    struct ht_node* new_val = malloc(sizeof(struct ht_node));
    new_val->key = key;
    new_val->value = value;

    list_insert(list, new_val);

    //increase size
    ht->size++;

    return;
}


/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 *
 * Return:
 *   Should return the value of the corresponding 'key' in the hash table .
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */
    //find list at desired key
    int idx = ht_hash_func(ht, key, convert);
    struct list* list = dynarray_get(ht->dynarray, idx);

//traverse that list
    while(list_isempty(list) == 0){
        //find value at that list
        struct ht_node* elem = list_find(list, key, convert);
        if(elem){
            //if exists, return the value
            return elem->value;
        }else{
            return NULL;
        }
    }

    return NULL;
}


/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){
    /*
     * FIXME: 
     */

    //compute index of key
    int idx = ht_hash_func(ht, key, convert);
    struct list* list = dynarray_get(ht->dynarray, idx);

//remove list at that key
    list_remove(list, key, convert);

    ht->size--;
    return;
} 
