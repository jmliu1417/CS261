//char_stack.h
#include <string.h>
#include <stdbool.h> //for bool type

#define size 0x100000

void init(char* stack);
void push (char* stack, char c);
void pop (char* stack);
char top (char* stack);
bool is_empty(char* stack);
