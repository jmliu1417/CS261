#include <stdio.h>
#include <stdlib.h>

void swap(int nums[], int i, int j){
    //set init largest to j;
    int largest = j;
    int right_child = 2 * j+2;
    int left_child = 2* j+1;


    if(left_child < i && nums[left_child] > nums[largest]){
        largest = left_child;
    }

    if(right_child < i && nums[right_child] > nums[largest]){
        largest = right_child;
    }

    if(largest != j){
        int temp = nums[j];
        nums[j] = nums[largest];
        
        nums[largest] = temp;
        swap(nums, i, largest);
    }
}

void create_heap(int nums[], int k){
    //start at lowest non-leaf node, traverse down
    for(int i = k/2 - 1; i >= 0; i--){
        swap(nums, k, i);
    }
}

int findKthLargest(int* nums, int numsSize, int k)
{
    /*
     * FIXME:
     */
    create_heap(nums, numsSize);

    for(int i=0; i<k-1; i++){
        nums[0] = nums[numsSize - 1];
        numsSize--;
        swap(nums, numsSize, 0);
    }

    return nums[0];
}


int main(int argc, char **argv)
{
    
    printf("\nTest 1...\n");
    int num1[6] = {3,2,1,5,6,4};
    printf("2nd largest in [3 2 1 5 6 4]\n");
    printf("Expected: 5\n");
    printf("Actual: %d\n", findKthLargest(num1, 6, 2));

    printf("\nTest 2...\n");
    int num2[9] = {3,2,3,1,2,4,5,5,6};
    printf("4th largest in [3 2 3 1 2 4 5 5 6]\n");
    printf("Expected: 4\n");
    printf("Actual: %d\n", findKthLargest(num2, 9, 4));


    printf("\nTest 3...\n");
    int num3[5] = {10,10,10,10,10};
    printf("5th largest in [10 10 10 10 10]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num3, 5, 5));

    printf("\nTest 4...\n");
    int num4[7] = {-10,10,-10,10,-10,10,0};
    printf("4th largest in [-10 10 -10 10 -10 10 0]\n");
    printf("Expected: 0\n");
    printf("Actual: %d\n", findKthLargest(num4, 7, 4));

    printf("\nTest 5...\n");
    int num5[10] = {10,9,8,7,6,5,4,3,2,1};
    printf("1st largest in [10 9 8 7 6 5 4 3 2 1]\n");
    printf("Expected: 10\n");
    printf("Actual: %d\n", findKthLargest(num5, 10, 1));


    return 0;
}
