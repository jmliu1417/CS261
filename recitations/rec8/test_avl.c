#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

 
/* main() to test above function*/
int main(){
  
    /* Test case 1:*/
    struct avl_tree *avl1 = avl_create();

    avl_insert(avl1, 10);
    avl_insert(avl1, 20);
    avl_insert(avl1, 30);
    avl_insert(avl1, 40);
    avl_insert(avl1, 50);
    avl_insert(avl1, 25);


  
    /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
    */

    printf("Test case 1: \n"); 
    printf("Preorder traversal: \n");
    printf("Expected: 30 20 10 25 40 50\n");
    printf("Actual:   ");
    preOrder(avl1);
    printf("\n\n");


    /* Test case 2:*/
    struct avl_tree *avl2 = avl_create();

    avl_insert(avl2, 64);
    avl_insert(avl2, 96);
    avl_insert(avl2, 32);
    avl_insert(avl2, 16);
    avl_insert(avl2, 80);
    avl_insert(avl2, 24);
    avl_insert(avl2, 48);
    avl_insert(avl2, 8);
    avl_insert(avl2, 40);
    avl_insert(avl2, 88);
  
    /* The constructed AVL Tree would be
             64
           /    \
         24       88
        /  \     /  \
       16  40   80  96
       /   / \
      8  32  48 
    */
    printf("Test case 2: \n"); 
    printf("Preorder traversal: \n");
    printf("Expected: 64 24 16 8 40 32 48 88 80 96\n");
    printf("Actual:   ");
    preOrder(avl2);
    printf("\n\n");


    /* Test case 3:*/
    struct avl_tree *avl3 = avl_create();

    avl_insert(avl3, 8);
    avl_insert(avl3, 16);
    avl_insert(avl3, 24);
    avl_insert(avl3, 32);
    avl_insert(avl3, 40);
    avl_insert(avl3, 48);
    avl_insert(avl3, 64);
    avl_insert(avl3, 80);
    avl_insert(avl3, 88);
    avl_insert(avl3, 96);

    /* The constructed AVL Tree would be
             32
           /    \
         16       80
        /  \     /  \
       8   24   48  88
               /  \   \
              40  64  96 
    */

    printf("Test case 3: \n"); 
    printf("Preorder traversal: \n");
    printf("Expected:32 16 8 24 80 48 40 64 88 96\n");
    printf("Actual:  ");
    preOrder(avl3);
    printf("\n\n");


    avl_free(avl1);
    avl_free(avl2);
    avl_free(avl3);

    return 0;
}
