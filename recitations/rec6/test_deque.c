/*
 * This file contains executable code for testing your deque implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "deque.h"
#include "db_list.h"

void print_int (void* a)
{
    int* s = a;
    printf ("%d\t", *s);
}


int main(int argc, char** argv) {
  int simfront, simback, i, n = 16, k_removed = 4, k_insert = 8;
  int* test_data;
  int** simdeque;
  struct deque* dq;

  /*
   * Create array of testing data.
   */
  test_data = malloc(n * sizeof(int));
  for (i = 0; i < n; i++) {
    test_data[i] = i * i * i;
  }

  /*
   * Create deque and insert part of the testing data into the front.  Simulate a deque
   * in the simdeque array (with current front kept track of in simfront).
   */
  dq = deque_create();
  simdeque = malloc(n * sizeof(int*));
  simfront = 0;
  simback = k_insert;
  printf("== Inserting first %d of %d values at the front of the deque.\n", k_insert, n);
  for (i = 0; i < k_insert; i++) {
    deque_add_to_front(dq, &test_data[i]);
    simdeque[--simback] = &test_data[i];
  }
  simback = k_insert;

  printf("\n");
  printf("Display the deque...\n");

  printf("Expected:\n");
  for (i = simfront; i < simback; ++i)
  {
    print_int((void*)simdeque[i]);
  }
  printf("\n");
  
  printf("\n");
  printf("Actual:\n");
  deque_display(dq, &print_int);
  printf("\n");

  /*
   * Remove a few of the values held in the deque from the front and make sure they're the
   * correct values.
   */
  printf("\n== Remove some from the front of the deque: front / removed (expected)\n");
  for (i = 0; i < k_removed; i++) {
    int* expected = simdeque[simfront++];
    int* front = deque_front(dq);
    int* removed = deque_remove_front(dq);
    if (front && removed) {
      printf("  - %4d / %4d (%4d)\n", *front, *removed, *expected);
    } else {
      printf("  - front (%p) or removed (%p) is NULL (expected: %4d)\n", front,
        removed, *expected);
    }
  }

  printf("\n");
  printf("Display the deque...\n");

  printf("Expected:\n");
  for (i = simfront; i < simback; ++i)
  {
    print_int((void*)simdeque[i]);
  }
  printf("\n");
  
  printf("\n");
  printf("Actual:\n");
  deque_display(dq, &print_int);
  printf("\n");

  /*
   * Insert remaining values into the back of the deque (and simulated deque).
   */
  printf("\n== Inserting remaining %d of %d values onto the back of the deque.\n", n - k_insert, n);
  for (i = k_insert; i < n; i++) {
    deque_add_to_back(dq, &test_data[i]);
    simdeque[simback++] = &test_data[i];
  }

  printf("\n");
  printf("Display the deque...\n");

  printf("Expected:\n");
  for (i = simfront; i < simback; ++i)
  {
    print_int((void*)simdeque[i]);
  }
  printf("\n");
  
  printf("\n");
  printf("Actual:\n");
  deque_display(dq, &print_int);
  printf("\n");

  /*
   * Remove the remaining values held in the deque and make sure they're the
   * correct values.
   */
  printf("\n== Removing the rest from the back deque: back / removed (expected)\n");
  while (simback > simfront && !deque_isempty(dq)) {
    int* expected = simdeque[--simback];
    int* back = deque_back(dq);
    int* removed = deque_remove_back(dq);
    if (back && removed) {
      printf("  - %4d / %4d (%4d)\n", *back, *removed, *expected);
    } else {
      printf("  - back (%p) or removed (%p) is NULL (expected: %4d)\n", back,
        removed, *expected);
    }
  }

  /*
   * Make sure the deque is actually empty and also exhausted all actual data.
   */
  printf("\n== Is deque empty (expect 1)? %d\n", deque_isempty(dq));
  printf("== Saw all test data (expect 1)? %d\n", simfront == simback);

  /*
   * add some values to the deque to fully test deque_free() function
   */
  struct db_list** ll = (struct db_list**) dq;
  if (ll){
    for (i = 0; i < k_insert; i++) {
      db_list_insert(*ll, &test_data[i]);
    }
  }
  

  deque_free(dq);
  free(test_data);
  free(simdeque);

  return 0;
}
