/* CS 261 Recitation 5: Use stack to validate parentheses */

#include <stdio.h>
#include <stdbool.h> //for bool type

#include "char_stack.h"

/*
  Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
  determine if the input string is valid.

  An input string is valid if:
  1. Open brackets must be closed by the same type of brackets.
  2. Open brackets must be closed in the correct order.
  3. Every close bracket has a corresponding open bracket of the same type.
 */

bool is_valid(char *s)
{
  // FIXME:

  char  char_stack [size];
  init(char_stack);

  for(int i = 0; i<strlen(s); i++){
    //push(char_stack, s[i]);
    
    if(s[i] == '{' || s[i] == '(' || s[i]=='['){
      push(char_stack, s[i]);
    }else{
      if(is_empty(char_stack)){
        return false;
      }

      char top_char = top(char_stack);

      if((s[i] == '}' && top_char != '{') || (s[i] == ')' && top_char != '(') || (s[i] == ']' && top_char != '[')){
        return false;
     }
     pop(char_stack);

    }

  }
  return is_empty (char_stack);
}

/**************************************************
* The following are test cases
* DO NOT MODIFY CODE BEYOND THIS POINT!!!
* *************************************************/

void test_case(int num, char *s, int expected, int* counter){
  printf("\nTest %d.....\n", num);
  printf("%s\n", s);
  printf("Expected: %d \n", expected);
  printf("Acutal: %d  ", is_valid(s));

  if (is_valid(s) == expected){
    printf("OK\n\n");
    (*counter) ++;
  }
  else{
    printf("failed\n\n");
  }
  
  return;
}


int main()
{
  int passed = 0, num = 1;

  test_case(num++, "()", 1, &passed);
  test_case(num++, "[]", 1, &passed);
  test_case(num++, "{}", 1, &passed);
  test_case(num++, "()[]{}", 1, &passed);
  test_case(num++, "(]", 0, &passed);
  test_case(num++, "{()})", 0, &passed);
  test_case(num++, "{(})[]", 0, &passed);
  test_case(num++, "{[]}", 1, &passed);
  test_case(num++, "{[(())]}", 1, &passed);
  test_case(num++, "{]()[}", 0, &passed);
  test_case(num++, "([{()()[]}[]])", 1, &passed);

  if (passed == num)
    printf("\nAll tests passed!!\n\n\n");
  else
    printf("%d out of 11 tests passed, plz check your solution!\n\n\n", passed);

  return 0;
}

