#include <stdio.h>

int function(int num, int ctr) {
  int i;
  for(i = 2;i <= num/2; i++){
    if(num % i==0){
      ctr++;
      break;
    }
  }
  if(ctr == 0 && num != 1)
    return 1;
  
  else
    return 0;
}

int main(){

  int num, ctr = 0, r = -1;
  printf("Input a number: ");
  scanf("%d",&num);
  
  r = function(num, ctr);
  printf("%d\n", r);

  return 0;
}