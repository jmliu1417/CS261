#include <stdlib.h>

#include "ll.h"

// FYI: 
// struct node
// {
// 	int val;
// 	struct node *next;
// };


struct node* add_two_num (struct node* l1, struct node* l2)
{
	/*
	 * FIX ME:
	 */

	struct node* current;
	struct node temp;

	current = &temp;
	int num = 0;

	while(l1 || l2 || num){
		int sum = num;
		//sum += l1->val;

		if(l1){
			sum += l1->val;
			l1 = l1->next;
		}

		if(l2){
			sum += l2->val;
			l2 = l2->next;
		}

		num = sum / 10;

		current -> next = malloc(sizeof(struct node));
		current = current->next;
		current->val = sum%10;
		current->next = NULL;
	}


	

	return temp.next;
}


