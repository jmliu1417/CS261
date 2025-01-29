#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sum_swares(int i){
	int sum = 0;

	while(i > 0){
		int current_digit = i % 10;
		sum += current_digit*current_digit;

		i /= 10;
	}
	return sum;
}


/*
 * return true (1) if n is happy, false (0) otherwise
 */
bool isHappy (int n){
	/*
	 * FIXME:
	 */
	int arr[10000] = {0};

	while(n!=1 && arr[n] == 0){
		arr[n] = 1;
		n = sum_swares(n);
	}

	if(n==1){
		return true;
	}else{
		return false;
	}
}


/*
 * Below are testing functions... DO NOT MODIFY!!!
 */

void show_result(int e, int r){
	printf("Expected: %d\nActual: %d...", e, r);
	if (r != e) 
        printf("FAIL\n\n\n");
    else 
        printf("OK\n\n\n");
}



int main()
{
	printf("\nTEST 1...19\n");
	show_result(1, isHappy(19));

	printf("\nTEST 2...2\n");
	show_result(0, isHappy(2));

	printf("\nTEST 3...7\n");
	show_result(1, isHappy(7));

	printf("\nTEST 4...176\n");
	show_result(1, isHappy(176));

	printf("\nTEST 5...36\n");
	show_result(0, isHappy(36));

	

	return 0;
}
