/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Jamie Liu
 * Email: liujam@oregonstate.com
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* dynarray;
};

struct node {
	void* value;
	int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	/*
	 * FIXME: 
	 */
	struct pq* new_pq = malloc(sizeof(struct pq));

	new_pq->dynarray = dynarray_create();

	return new_pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	/*
	 * FIXME: 
	 */

	if(pq != NULL){
		dynarray_free(pq->dynarray);

		free(pq);
	}

	return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	/*
	 * FIXME: 
	 */

	if(dynarray_size(pq->dynarray) == 0){
		return 1;
	}
	return 0;
}

/*
 * This function swaps two nodes
 *
 * Params:
 *   pq - the priority queue, and the two indexes being swapes
 *
 * Return:
 *   nothing, just swaps them
 */
void swap(struct pq* pq, int parent_idx, int child_idx){
	//struct node* temp = parent;

	void* parent = dynarray_get(pq->dynarray, parent_idx);
	void* child = dynarray_get(pq->dynarray, child_idx);

	dynarray_set(pq->dynarray, child_idx, parent);
	dynarray_set(pq->dynarray, parent_idx, child);
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	/*
	 * FIXME: 
	 */

	//Note: This function needs to be O(logn)
	struct node* new_val = malloc(sizeof(struct node));
	new_val->value = value;
	new_val->priority = priority;

	dynarray_insert(pq->dynarray, new_val);
	int current_index = dynarray_size(pq->dynarray)-1;

	while(current_index != 0){

		int parent_index = ((current_index - 1)/2);
		struct node* parent = dynarray_get(pq->dynarray, parent_index);
		struct node* child = dynarray_get(pq->dynarray, current_index);

		if(parent->priority > child->priority){
			swap(pq, parent_index, current_index);

			current_index = parent_index;
		}else{
			break;
		}
	}
	
	return;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	//Note: This function needs to be O(1)
	struct node* first = dynarray_get(pq->dynarray, 0);
	return first;

	//return NULL;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	/*
	 * FIXME: 
	 */

	//Note: This function needs to be O(1)
	struct node* priority = dynarray_get(pq->dynarray, 0);
	
	return priority->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	//Note: This function needs to be O(logn)

//creating removed node to place value
	struct node* removed_node = dynarray_get(pq->dynarray, 0);
	void* value = removed_node->value;
	
//swapping
	swap(pq, 0, (dynarray_size(pq->dynarray) - 1));
	dynarray_remove(pq->dynarray, (dynarray_size(pq->dynarray) - 1));
	//free(removed_node);

	//holds current index
	int current = 0;
	int size = dynarray_size(pq->dynarray);
	
	//if pq is empty return imm
	if(pq_isempty(pq)){
		free(removed_node);
		return value;
	}else{
		struct node* current_node = dynarray_get(pq->dynarray, 0);

//while condition holds true
		while(1){
			//int min_idx = current;
			int first_idx = (2 * current + 1);
			int second_idx = 2 * current+2;			
			
			//if both indexes are value
			if((first_idx <= size-1) && (second_idx <= size-1)){

				//repping the childrennnn
				struct node* first_child = dynarray_get(pq->dynarray, first_idx);
				struct node* second_child = dynarray_get(pq->dynarray,second_idx);

				//checking first childs (lefts) priority
				if(first_child->priority > second_child->priority){
					//checking the parent
					if(current_node->priority > second_child->priority){
						//swap if parent is less than child, percing down
						swap(pq, current, second_idx);
						current = second_idx; 
					}else{
						//free otherwise
						free(removed_node);
						return value;
					}
				}else{
					//if the other child holds a smaller priority
					if(current_node->priority > first_child->priority){
						swap(pq, current, first_idx);
						current = first_idx;
					}else{
						free(removed_node);
						return value;
					}
				}
			}else{
				//checking second index (if the other child exists)
				if(second_idx > size - 1){
					if(first_idx > size - 1){
						free(removed_node);
						return value;
					}else{
						//recreating first child
						struct node* first_child = dynarray_get(pq->dynarray, first_idx);
						if(current_node->priority > first_child->priority){
							swap(pq, current, first_idx);
							current = first_idx;
						}else{
							
							free(removed_node);
							return value;
						}
					}
				}
			}
		}
	}
}

