/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  /*
   * FIXME:
   */
  struct bst* new_bst = malloc(sizeof(struct bst));
  new_bst->root = NULL;

  return new_bst;
}


/*
 * function frees an indiv nodes and its children
 * Params:
 *   bst node (the root passed in) 
 */


void free_node(struct bst_node* node){
  
  if(node != NULL){
    free_node(node->left);
    free_node(node->right);

    free(node);
  }
}
/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  /*
   * FIXME:
   */

  //free indiv node
  if(bst != NULL){
    free_node(bst->root);
    free(bst);
  }

  return;
}

/*


/*
 * function recursively finds mnumber of nodes
 * Params:
 *   bst node (the root passed in) 
 */

int count_nodes(struct bst_node* node){
     if(node == NULL){
       return 0;
    }

//traversing through the tree, adding one per transversal
    return 1 + count_nodes(node->right) + count_nodes(node->left);
}
 /* This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  /*
   * FIXME:
   */

  if(bst == NULL){
    return 0;
  }

  return count_nodes(bst->root);
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */


void bst_insert(struct bst* bst, int key, void* value) {
  /*
   * FIXME:
   */

  //setting parent and temp nodes to traverse
  struct bst_node* parent = NULL;
  struct bst_node* temp = bst->root;

//when temp is not at the end of the tree
  while(temp != NULL){
    //move parnt around, move to left if key is less than temps key, right otherwise
    parent = temp;
    if(key < temp->key){
      temp = temp->left;
    }else{
      temp = temp->right;
    }
  }

//new node to be created
  struct bst_node* new_node = (struct bst_node*)malloc(sizeof(struct bst_node));

  new_node->key = key;
  new_node->value = value;
  new_node->right = NULL;
  new_node->left = NULL;

//if the tree is empty
  if(parent == NULL){
    bst->root = new_node;
    //if key is less than parent's key move insert to the left, right otherwise
  }else if(key < parent->key){
    parent->left = new_node;
  }else if(key > parent->key){
    parent->right = new_node;
  }

  return;
}

/*
 * function recursively the node to be removed and removes it. Finds the in-order successor based on 
 the parent and roots values
 * Params:
 *   bst root (the root passed in), key - desired node to be removed
 */

struct bst_node* remove_helper(struct bst_node* root, int key){

  //if root is null
      if (root == NULL) {
        return root;
    }

//if the key's root is greater than desired, move left
    if (root->key > key) {
        root->left = remove_helper(root->left, key);
        return root;
      //otherwise if its less, move right
    } else if (root->key < key) {
        root->right = remove_helper(root->right, key);
        return root;
    }

//if theres only one child  on the right, replace root with its child on the right
    if (root->left == NULL) {
        struct bst_node* temp = root->right;
        free(root);
        return temp;
        //otherwise if no child on the right, move the node up from the left child
    } else if (root->right == NULL) {
        struct bst_node* temp = root->left;
        free(root);
        return temp;
    } else {

      //if root has two children
      //make a node repping parent of successor and the actual successor
        struct bst_node* p_sub_s = root;

        //successor will be on the right, greater than
        struct bst_node* successor = root->right;

//iterate through left node to find order successor, moving parent down until successor left
//is null, finding the in-order
        while (successor->left != NULL) {
            p_sub_s = successor;
            successor = successor->left;
        }

//if the parent of the successor isn't eq to root, left goes to right, else otherwise
        if (p_sub_s != root) {
            p_sub_s->left = successor->right;
        } else {
            p_sub_s->right = successor->right;
        }

//assign root to new successor's values, free successor
        root->key = successor->key;
        root->value = successor->value;
        free(successor);
        return root;
    }
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */

void bst_remove(struct bst* bst, int key) {
  //checking bst null
  if(bst == NULL){
    return;
  }else{
    remove_helper(bst->root, key);
  }

  return;
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {

//creating a root to traverse
  struct bst_node* root = bst->root;

//iterate while root does not hit the end of the tree
  while(root != NULL){
    //once root reaches the end, or the key reaches desired key value
    if(root == NULL || root->key == key){
      return root->value;

//traverses till it reaches one less than the desired key, root will be saved as right and continue right
    }else if(root->key < key){
      root = root->right;

//otherwise would go left if greater
    }else if(root->key > key){
      root = root->left;
    }
  }
  return NULL;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * function recursively finds max height of tree by increasing one each time a level is traversed
 * Params:
 *   bst node (the root passed in) 
 */

int height_helper(struct bst_node* root){
  //if root is null height is -1
if(root == NULL){
        return -1;
    }

    if(root != NULL){
      //iterate through height helper
        int rightTree = height_helper(root->right);
        int leftTree = height_helper(root->left);

//add one every time the left is greater than the right, or anytime a tree is greater than another
//ensures that we go down the greatest path, increase for every one time
        if(leftTree > rightTree){
        return leftTree + 1;
        }else{
            return rightTree + 1;
        }
    }

    //-2 otherwise
    return -2;
}

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
  /*
   * FIXME:
   */
  if(bst == NULL){
    return -1;
  } else {
    return height_helper(bst->root);
  }

 }

/*
 * function recursively finds the sums based by subtracting items from the sum value until it
 traverses the whole tree
 * Params:
 *   bst node (the root passed in) and the desired checked sum
 */

int sum_helper(struct bst_node* node, int sum){
 
 //check if node is null
  if(node == NULL){
    return 0;
  }

//start with sum, decrease as node traverses throughout the tree
  sum -= node->key;

//at the end of the tree, check if sum is at 0 (case where sum exists)
  if(node->left == NULL && node->right == NULL){
    if(sum == 0){
      //proper case
      return 1;
    }else{
      //false if sum is anything other than 0
      return 0;
    }
  }

//traverse the trees with the decreasing sum
  int left_tree = sum_helper(node->left, sum);
  int right_tree = sum_helper(node->right, sum);

//if either the left or right are not null, return true
 if(left_tree || right_tree){
    return 1;
  }else{
    return 0;
  }
  

}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */

int bst_path_sum(struct bst* bst, int sum) {
  /*
   * FIXME:
   */
  //check if bst is null, otherwise continue on
  if(bst == NULL){
    return 0;
  }else{
    return sum_helper(bst->root, sum);
  }
  //return 0;
}


/*
 * This function recursively checks the trees based on the values of the current node
 * Params:
 *   a node (root in this case), and a bound for lower and upper values
 */
int range_helper(struct bst_node* node, int lower, int upper){
  //checking if node is null initially
  if(node == NULL){
    return 0;
  }

//if node's key is lower than the lower bound, continue to right to traverse greater values
  if(node->key < lower){
    return range_helper(node->right, lower, upper);

//above upper, traverse left tree to traverse lower
  }else if(node->key > upper){
    return range_helper(node->left, lower, upper);

  }else{
  //within range, check both paths and traverse otherwise
    int sum_right = range_helper(node->right, lower, upper);
    int sum_left = range_helper(node->left, lower, upper);

  //add the sums of the traversals
    return node->key + sum_right + sum_left;
  }

}
/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  /*
   * FIXME:
   */

//checking if bst is null, otherwise
  if(bst == NULL){
    return 0;
  }else{
    range_helper(bst->root, lower, upper);
  }
  //return 0;
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  /*
   * FIXME:
   */
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  /*
   * FIXME:
   */
  if (value) {
    *value = NULL;
  }
  return 0;
}


