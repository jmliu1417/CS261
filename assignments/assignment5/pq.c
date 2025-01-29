/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: 
 * Email: 
 */

#include <stdlib.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * Given index i, these macro calculate the index of node i's children and parent.
 */
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
#define PARENT(i) ((i - 1) / 2)


/*
 * structure to represent a single element in a priority queue.
 */
struct pq_elem {
  int priority;
  void* value;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = (struct pq*) malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create();
  return pq;
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
  assert(pq);

  /*
   * Free each struct pq_elem stored in the heap.
   */
  for (int i = 0; i < dynarray_size(pq->heap); i++) {
    struct pq_elem* pq_elem = (struct pq_elem*) dynarray_get(pq->heap, i);
    if (pq_elem) {
      free(pq_elem);
    }
  }

  dynarray_free(pq->heap);
  free(pq);
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
  return dynarray_size(pq->heap) <= 0;
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
  assert(pq);

  /*
   * Create a new pq_elem
   */
  struct pq_elem* elem = (struct pq_elem*) malloc(sizeof(struct pq_elem));
  elem->priority = priority;
  elem->value = value;

  /*
   * Insert the new element at the end of the heap, and then percolate it up
   */
  dynarray_insert(pq->heap, elem);
  int n = dynarray_size(pq->heap) - 1; //node index
  while (n > 0) {
    int p = PARENT(n); //parent index
    struct pq_elem* parent = dynarray_get(pq->heap, p);

    if (elem->priority < parent->priority) { //swap
      dynarray_set(pq->heap, p, elem);
      dynarray_set(pq->heap, n, parent);
      n = p; //update node index to p
    } 
    else {
      break; //break if already restored, i.e., no swap needed
    }
  }
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
  assert(pq && !pq_isempty(pq));
  struct pq_elem* first = (struct pq_elem*) dynarray_get(pq->heap, 0);
  return first->value;
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
  assert(pq && !pq_isempty(pq));
  struct pq_elem* first = (struct pq_elem*) dynarray_get(pq->heap, 0);
  return first->priority;
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
  assert(pq && !pq_isempty(pq));

  struct pq_elem* first = (struct pq_elem*) dynarray_get(pq->heap, 0);
  void* first_value = first->value; //value to return

  free(first); //free the element

  /*
   * Replace the first with the last, and percolate it down
   */
  int k = 0, n = dynarray_size(pq->heap);
  struct pq_elem* replacement = (struct pq_elem*) dynarray_get(pq->heap, n - 1);
  dynarray_set(pq->heap, 0, replacement);
  dynarray_remove(pq->heap, n - 1);

  if (dynarray_size(pq->heap) > 0) {
    int l = LEFT(k), r = RIGHT(k); //indices of left and right child 
    while (l < dynarray_size(pq->heap)) {

      /*
       * If the replacement element has at least one child, check
       * which one has the smaller priority value.
       */
      struct pq_elem* left = (struct pq_elem*) dynarray_get(pq->heap, l), * smaller = left;
      int s = l;

      //if right index is within the size 
      if (r < dynarray_size(pq->heap)) {
        struct pq_elem* right = (struct pq_elem*) dynarray_get(pq->heap, r);
        if (right->priority < left->priority) {
          smaller = right;
          s = r;
        }
      }

      /*
       * If the smaller priority of the replacement element's two children is smaller than 
       * the replacement's priority, then swap the child with the replacement
       */
      if (replacement->priority > smaller->priority) {
        dynarray_set(pq->heap, k, smaller);
        dynarray_set(pq->heap, s, replacement);
        //update indices 
        k = s;
        l = LEFT(k);
        r = RIGHT(k);
      } 
      else {
        break; //break if no swap needed, i.e., the heap is restored
      }
    }
  }

  return first_value;
}
