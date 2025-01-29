#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};



int maxDepth(struct TreeNode* root)
{
    /*
     * FIXME:
     */

    // struct TreeNode* current = root;

    if(root == NULL){
        return -1;
    }

    if(root != NULL){
        int rightTree = maxDepth(root->right);
        int leftTree = maxDepth(root->left);

        if(leftTree > rightTree){
        return leftTree + 1;
        }else{
            return rightTree + 1;
        }
    }
    return -2;
}

int minDepth(struct TreeNode* root)
{
    if(root == NULL){
        return -1;
    }
    //if child is null, dont visit

    if(root){
        int rightTree = minDepth(root->right);
        int leftTree = minDepth(root->left);

        if(root->right && !root->left){
            return 1 + rightTree;

        }else if(root->left && !root->right){
            return 1 + leftTree;
        }

        if(leftTree > rightTree){
            return rightTree + 1;
        }else{
            return leftTree + 1;
        }
    }

    return -2;
}

struct TreeNode* newNode(int val){
    struct TreeNode *n = malloc(sizeof(struct TreeNode));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int main(void)
{
    
    //test 1: Empty Tree
    printf("\n-----------------------\nTest1: Empty Tree....\n");
    printf("Max Depth:\nExpected: -1\nActual: %d\n\n", maxDepth(NULL));
    printf("Min Depth:\nExpected: -1\nActual: %d\n\n", minDepth(NULL));


    //test 2: Tree with only a root node
    // 20
    struct TreeNode *root = newNode(20);

    printf("\n-----------------------\nTest2....\n");
    printf("Max Depth:\nExpected: 0\nActual: %d\n\n", maxDepth(root)); //20
    printf("Min Depth:\nExpected: 0\nActual: %d\n\n", minDepth(root)); //20
    

    //test 3:
    //            20
    //         18
    //      16
    //   14
    //12
    struct TreeNode *node1 = newNode(18);
    root->left = node1;

    struct TreeNode *node2 = newNode(16);
    node1->left = node2;

    struct TreeNode *node3 = newNode(14);
    node2->left = node3;

    struct TreeNode *node4 = newNode(12);
    node3->left = node4;
    
    printf("\n-----------------------\nTest3....\n");
    printf("Max Depth:\nExpected: 4\nActual: %d\n\n", maxDepth(root)); //20-18-16-14-12
    printf("Min Depth:\nExpected: 4\nActual: %d\n\n", minDepth(root)); //20-18-16-14-12


    //test 4:
    //            20
    //         18    22
    //      16
    //   14
    //12
    struct TreeNode *node5 = newNode(22);
    root->right = node5;
    printf("\n-----------------------\nTest4....\n");
    printf("Max Depth:\nExpected: 4\nActual: %d\n\n", maxDepth(root));	//20-18-16-14-12
    printf("Min Depth:\nExpected: 1\nActual: %d\n\n", minDepth(root));	//20-22


    //test 5:
    //            20
    //         18    22
    //      16    21    26 
    //   14                30
    //12
    struct TreeNode *node6 = newNode(21);
    node5->left = node6;
    struct TreeNode *node7 = newNode(26);
    node5->right = node7;
    struct TreeNode *node8 = newNode(30);
    node7->right = node8;
    printf("\n-----------------------\nTest5....\n");
    printf("Max Depth:\nExpected: 4\nActual: %d\n\n", maxDepth(root));	//20-18-16-14-12
    printf("Min Depth:\nExpected: 2\nActual: %d\n\n", minDepth(root));  //20-22-21


    //test 6: 
    //            20
    //         18    22
    //      	  21    26 
    //		               30
   
    free(node2);		//16
    free(node3);		//14
    free(node4);		//12
    node1->left = NULL;
    
    printf("\n-----------------------\nTest6....\n");
    printf("Max Depth:\nExpected: 3\nActual: %d\n\n", maxDepth(root));	//20-22-26-30
    printf("Min Depth:\nExpected: 1\nActual: %d\n\n", minDepth(root));  //20-18



    //test 7: 
    //            20
    //        		 22
    //      	  21    26 
    //		               30
   
    free(node1);		//18
    root->left = NULL;
    printf("\n-----------------------\nTest7....\n");
    printf("Max Depth:\nExpected: 3\nActual: %d\n\n", maxDepth(root)); //20-22-26-30
    printf("Min Depth:\nExpected: 2\nActual: %d\n\n", minDepth(root)); //20-22-21

    //test 8: 
    //            20
    //        		 22
    //      	        26 
    //		               30
   
    free(node6);		//21
    node5->left = NULL;
    printf("\n-----------------------\nTest8....\n");
    printf("Max Depth:\nExpected: 3\nActual: %d\n\n", maxDepth(root)); //20-22-26-30
    printf("Min Depth:\nExpected: 3\nActual: %d\n\n", minDepth(root)); //20-22-26-30


    free(node8);		//30
    free(node7);		//26
    free(node5);		//22
    free(root);			//20
    root->right = NULL;



    return 0;
}