//char_stack.c
#include "char_stack.h"

//initialize the stack
void init(char* stack){
    for(int i = 0; i < size; ++i)
        stack[i] = '\0';
    return;
}

//push an element to the stack
void push (char* stack, char c){
    stack[strlen(stack)] = c;
    return;
}

//remove the top element 
void pop (char* stack) {
    if (strlen(stack) == 0)
        return;
    stack[strlen(stack)-1] = '\0';
}

//returns the top char in the stack
char top (char* stack) {
    if (strlen(stack) == 0)
        return '\0';
    return stack[strlen(stack)-1];
}

//if stack is empty, return true, otherwise, return false
bool is_empty(char* stack){
    return (!strlen(stack));
}