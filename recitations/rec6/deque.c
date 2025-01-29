/*
 * This file is where you should implement your deque.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name: Jamie Liu
 * Email: liujam@oregonstate.edu
 */

#include <stdlib.h>

#include "deque.h"
#include "db_list.h"

/*
 * This is the structure that will be used to represent a deque.  This
 * structure specifically contains a single field representing a doubly linked list
 * that should be used as the underlying data storage for the deque.
 *
 * You should not modify this structure.
 */
struct deque {
  struct db_list* db_list;
};

/*
 * This function should allocate and initialize a new, empty deque and return
 * a pointer to it.
 */
struct deque* deque_create() {
	/*
	 * FIXME:
	 */

	struct deque* new_deque = (struct deque*)malloc(sizeof(struct deque));
	new_deque->db_list = db_list_create();
	
	return new_deque;
}

/*
 * This function should free the memory associated with a deque.  While this
 * function should up all memory used in the deque itself, it should not free
 * any memory allocated to the pointer values stored in the deque.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   deque - the deque to be destroyed.  May not be NULL.
 */
void deque_free(struct deque* deque) {
	/*
	 * FIXME:
	 */
	db_list_free(deque->db_list);
	free(deque);
	
	return;
}

/*
 * This function should indicate whether a given deque is currently empty.
 * Specifically, it should return 1 if the specified deque is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   deque - the deque whose emptiness is being questioned.  May not be NULL.
 */
int deque_isempty(struct deque* deque) {
	/*
	 * FIXME:
	 */

	if(if_empty(deque->db_list) == 1){
		return 1;
	}
	return 0;
}

/*
 * This function should add a new value to the front of a given deque.  The value to be
 * inserted is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   deque - the deque onto which a value is to be inserted.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void deque_add_to_front(struct deque* deque, void* val) {
	/*
	 * FIXME:
	 */
	if(deque == NULL){
		return;
	}

	db_list_insert(deque->db_list, val);
	
	return;
}

/*
 * This function should add a new value to the back of a given deque.  The value to be
 * inserted is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   deque - the deque onto which a value is to be inserted.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void deque_add_to_back(struct deque* deque, void* val) {
	/*
	 * FIXME:
	 */
	db_list_insert_end(deque->db_list, val);
	return;
}

/*
 * This function should return the value stored at the front of a given deque
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   deque - the deque from which to query the front value.  May not be NULL.
 */
void* deque_front(struct deque* deque) {
	/*
	 * FIXME:
	 */
	if(deque == NULL){
		return NULL;
	}
	
	return get_head(deque->db_list);
}

/*
 * This function should return the value stored at the back of a given deque
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   deque - the deque from which to query the back value.  May not be NULL.
 */
void* deque_back(struct deque* deque) {
	/*
	 * FIXME:
	 */
	if(deque == NULL){
		return NULL;
	}
	
	return get_tail(deque->db_list);
}

/*
 * This function should remove a value at the front from a given deque and return the
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   deque - the deque from which a value is to be removed.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was removed.
 */
void* deque_remove_front(struct deque* deque) {
	/*
	 * FIXME:
	 */
	void* node = deque_front(deque);

	db_list_remove_front(deque->db_list);

	return node;
}

/*
 * This function should remove a value at the back from a given deque and return the
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   deque - the deque from which a value is to be removed.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was removed.
 */
void* deque_remove_back(struct deque* deque) {
	/*
	 * FIXME:
	 */
	void* node = deque_back(deque);
	db_list_remove_end(deque->db_list);

	return node;
}

/*
 * This function should display/print all the elements of the given deque 
 * from beginning to the end. 
 *
 * This function will be passed a *function pointer* called `p` that you
 * should use to print each element.
 * 
 * Params:
 * deque - the deque from which to display. May not be NULL.
 * p - pointer to a function that can be passed one void* value from
 *     to print it out, as described above.
 */
void deque_display(struct deque* deque, void (*p)(void* a)){
	/*
	 * FIXME:
	 */
	db_list_display_forward(deque->db_list, p);
	return;
}	
