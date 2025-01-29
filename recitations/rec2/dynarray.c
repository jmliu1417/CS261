/* CS261 - Reciation 2*/
/* Description: create a array of integers and struct student by giving the size of array, 
                and sort them using sort() and function pointers
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

struct student{
	int id;
	int score;
};

//helper function to compare students by their scores
int compare_student (void* x, void* y){
	struct student *s1 = x;
	struct student *s2 = y;
	return s1->score > s2->score ? 1 : 0;
}

//helper function to compare two ints
int compare_int (void* x, void* y){
	int* a = x, *b = y;
	return *a > *b ? 1 : 0;
}

/* sort the arr array by using a function pointer to 
 * compare its elements
 * Param: 
 *		void** arr                 - array of generic type 
 *      int n                      - array size
 *      int(*cmp)(void* a, void* b)- function pointer to compare two elements in the array 
 */
//void sort(void** arr, int n, int(*cmp)(void* a, void* b))
void sort(void** arr, int n, int(*cmp)(void* a, void *b)){
    /*Sort n integers in arr, ascending order*/
	/*
	 * FIX ME:
	 */
    for(int i = 0; i < n -1; i++){
        for(int j = 0; j < n-1; j++){
            if(cmp(arr[j], arr[j+1]) > 0){
                void* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
	 
}


/* free the memeory allocated by arr
 * Param: 
 *      void** arr                 - array of generic type 
 *      int n                      - array size
 */
void free_arr (void** arr, int n){
	/* free the memory allocated by arr*/
	/*
	 * FIX ME:
	 */
    for(int i = 0; i < n; i++){
        free(arr[i]);
    }

    free(arr);
}

int main(){
    srand(time(NULL));

    /*Declare an integer n and assign 10 to it.*/

    int n = 10;

    /***Step 1: sort an integer array ***/
    
    /*Allocate memory for n integers using malloc.*/

    int **rand_array = malloc(n * sizeof(int *));
    
    /*Populate the array by generating random ints (0-100, inclusive) n times, using rand().*/

    for(int i = 0; i<n; i++){
        rand_array[i] = (int*)malloc(sizeof(int));
        *(rand_array[i]) = rand()%101;
    }

    /*Print the contents of the array of n ints.*/
    printf("\nBefore sorting....\n");
    for(int i=0; i<n; i++){
        printf("%d ", *(rand_array[i]));
    }

    /*call sort() function to sort*/
    sort((void**)rand_array, n, compare_int);

    /*Print the contents of the array of n ints.*/
    printf("\nAfter sorting....\n");

    for(int i=0; i<n; i++){
        printf("%d ", *(rand_array[i]));
    }

    /***Step 2: After modifying sort() by using function pointer, 
    modify your sort() function call above. 
    (Note: you may also need to change the way the array is allocated ) ****/




    /***Step 3: sort an array of students ***/

    /*Allocate memory for n students using malloc.*/
    
    /*Generate random IDs and scores for the n students, using rand().*/
    /*note: 
     *    1. no two students should have the same ids 
     *    2. score and id range: 0-100, inclusive
     */
    
    struct student ** student_arr = malloc(sizeof(struct student*) * n);

    for(int i = 0; i < n; i++){
        student_arr[i] = malloc(sizeof(struct student));
        student_arr[i]->id = rand()%101;
        student_arr[i]->score = rand()%101;
    }

    /*Print the contents of the array of n students.*/
    printf("\nBefore sorting....\n");

for(int i = 0; i<n; i++){
    printf("Student ID: %d  Student score: %d \n", student_arr[i]->id, student_arr[i]->score);
}
    

    /*call sort() function to sort*/

    sort((void**)student_arr, n, compare_student);
    
    /*Print the contents of the array of n students.*/
    printf("\nAfter sorting....\n");
    

    for(int i = 0; i<n; i++){
        printf("Student ID: %d  Student score: %d \n", student_arr[i]->id, student_arr[i]->score);
    }

    /***Step 4: free the memory allocated in Step 1-3 by calling free_arr() ***/
    
    free_arr((void**)rand_array, n);
    free_arr((void**)student_arr, n);

    return 0;
}
