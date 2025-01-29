/* CS 261 Recitation 4: Anagram Detector
 */

#include <stdio.h>

/*
  The Function checks two given strings (a, b) and return
  1 if they are anagram, and 0 otherwise
  Assuming:
  1. a and b are of the same length
  2. a and b are made up of symbols from the set of 26 lowercase characters
 */

int check(){
  int x = 'b' ;

  return x;

}

int check_anagram(char *a, char *b)
{
  int count_a = 0;
  int count_b = 0;

  // FIXME:
  for(int i = 0; i < sizeof(a); i++){
     count_a += (int)a[i];
     count_b += (int)b[i];
  }

if(count_a == count_b){
  return 1;
}else{
  return 0  ;
}

}


int main()
{
  int x = check();
  printf("%d \n\n",x);
  printf("Test 1.....\n");
  printf("\"heart\", \"earth\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("heart", "earth"));


  printf("Test 2.....\n");
  printf("\"python\", \"typhon\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("python", "typhon"));

  printf("Test 3.....\n");
  printf("\"race\", \"care\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("race", "care"));

  printf("Test 4.....\n");
  printf("\"listen\", \"silent\"\n");
  printf("Expected: 1 \n");
  printf("Acutal: %d\n\n", check_anagram("listen", "silent"));

  printf("Test 5.....\n");
  printf("\"seal\", \"leaf\"\n");
  printf("Expected: 0 \n");
  printf("Acutal: %d\n\n", check_anagram("seal", "leaf"));

  printf("Test 6.....\n");
  printf("\"asdfghjkl\", \"aasdfghjk\"\n");
  printf("Expected: 0 \n");
  printf("Acutal: %d\n\n", check_anagram("asdfghjkl", "aasdfghjk"));

  printf("Test 7.....\n");
  printf("\"abba\", \"acaa\"\n");
  printf("Expected: 0 \n");
  printf("Acutal: %d\n\n", check_anagram("abba", "acaa"));

  printf("Test 8.....\n");
  printf("\"hqbqo\", \"lsnma\"\n");
  printf("Expected: 0 \n");
  printf("Acutal: %d\n\n", check_anagram("hqbqo", "lsnma"));

  

  return 0;
}

