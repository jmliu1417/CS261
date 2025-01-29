#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"


/*
 * Define your call struct here.
 */
//definition of struct
struct caller {
	char* reason;
	char* name;

	int id;
};	
/*
 * This function prints out the options and prompts the user for their display choice
 * Params:
 *   none
 */
int option_menu(){
	int user_option = 0;
	//printed whole statement
	printf("1. Receive a new call \n 2. Answer a call \n 3. Current state of the stack – answered calls \n 4. Current state of the queue – calls to be answered \n 5. Quit");
	scanf("%d", user_option);

	return user_option;
}

/*
 * This function prompts the user for caller details and sets the new caller to the queue
 * Params:
 *   struct queue and calls recieved, calls recieved to be passed in from main
 */
void recieve_caller(struct queue * queue, int* calls_recieved){
	struct caller* new_caller = malloc(sizeof(new_caller));
//checking if new_caller is null
	if(new_caller == NULL){
		return;
	}

//intitializing new caller
	new_caller->id += 1;
	new_caller->name = malloc(sizeof(char) * 1028);
	new_caller->reason = malloc(sizeof(char) * 1028);


	printf("Caller name: \n");
	scanf("%s", new_caller->name);

	printf("Caller reason: \n");
	scanf("%s", new_caller->reason);

//inc caller reason
	(*calls_recieved)++;
	printf("The call has been successfully added to the queue! \n");

	//pop value off queue
	queue_enqueue(queue, new_caller);
	free(new_caller->name);
	free(new_caller->reason);


}

/*
 * This function answers a call from the queue. pops that caller of queue and adds to stack
 *
 * Params:
 *   queue - queue they're making
 * stack - stack to add user
 * calls_ansered - calls that're answered from queue
 */
void answer_caller(struct queue * queue, struct stack * stack, int* calls_answered ){
	//checks if queue is empty
	if(queue_isempty(queue)){
		printf("No calls waiting to be answered, \n");
		return;
	}

	struct caller* pending_caller = queue_front(queue);

//checking if caller is null
	if(pending_caller != NULL){

		printf("The following call has been answered and added to the stack! \n");
		printf("Caller ID %d\n", pending_caller->id);
		printf("Caller name: %s\n", pending_caller->name);
		printf("Caller reason: %s\n", pending_caller->reason);

//pushing stack
		stack_push(stack, pending_caller);
		(*calls_answered++);
	//dequeue value
		queue_dequeue(queue);
	}

}

/*
 * this function displays the details oft the last caller answered
 * Params:
 *   stack - stack of callers answered
 * calls_Answered - num of called answeres, to be dereferenced
 */
void display_stack(struct stack* stack, int* calls_answered){
	//checks top of stack
	if(stack_top(stack) != NULL){
		//setting to the top of the stack
		struct caller* recent = stack_top(stack);

		printf("Calls answered: %d\n\n", *calls_answered);
		printf("Caller details: \n");
		printf("Caller ID %d\n", recent->id);
		printf("Caller name: %s\n", recent->name);
		printf("Caller reason: %s\n\n", recent->reason);
		return;

		
	}else{
		printf("No calls are waiting to be returned. \n");
		return;
	}
}

/*
 * This function displays the callers in the waiting queue
 * Params:
 *   queue - queue to display calls waiting
 * calls_recieved - num of calls recieved, to be drefered
 * calls_Answered - num of calls ansqered to stack , to be derefed
 */
void display_queue(struct queue* queue, int* calls_recieved, int* calls_answered){

//checking if queue is empty
	if(queue_isempty(queue)){
		printf("No calls recieved. \n");
		return;
	}
struct caller* recent = queue_front(queue);
	if(recent!= NULL){
//only if recent isnt null, somehow didnt pass check
		printf("Calls answered: %d\n\n", *calls_recieved - *calls_answered);
		printf("Caller details: \n");
		printf("Caller ID %d\n", recent->id);
		printf("Caller name: %s\n", recent->name);
		printf("Caller reason: %s\n\n", recent->reason);
	}

	
}

/*
 * This function iterates through each of the user options 
 *
 * Params:
 *   all of the stack, queue, and call values to be refered through each of the functions
 */
 void whole_display(int option, struct queue* queue, struct stack*stack, int* calls_answered, int* calls_recieved){
//iterating through each of the options
		if(option == 1){
			recieve_caller(queue, calls_recieved);
			free(new_caller);
		}else if(option == 2){
			answer_caller(queue, stack, calls_answered);
			
		}else if(option == 3){
			display_stack(stack, calls_answered);
			
		}else if(option == 4){
			display_queue(queue, calls_recieved, calls_answered);
		}else{
			printf("BYEEE");
		}
 }


int main(int argc, char const *argv[]) {
	//creating queues and stacks
	struct queue* queue = queue_create();
	struct stack* stack = stack_create();

	int num_answered_calls = 0;
	int num_recieved_calls = 0;

	// struct caller* caller = malloc(sizeof(caller));
	// caller->id = 0;
	// caller->name = NULL;
	// caller->reason = NULL;

	int user_option;

//repeating through options
	do{
		printf("1. Receive a new call \n 2. Answer a call \n 3. Current state of the stack – answered calls \n 4. Current state of the queue – calls to be answered \n 5. Quit\n\n");
		scanf("%d", &user_option);
		whole_display(user_option, queue, stack, &num_answered_calls, &num_recieved_calls);

	}while(user_option!=5);

	//freeing stuff?
	queue_free(queue);
	stack_free(stack);
	free(caller);
	return 0;

	
	
	
}
