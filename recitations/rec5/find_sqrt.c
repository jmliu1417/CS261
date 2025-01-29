#include <stdio.h>
#include <stdlib.h>

int sqrt_func(int x)
{
    //FIXME:
    if(x == 0 || x == 1){
        return x;
    }

    int temp = 1;
    int r = x;
    int sqrt = 0;

    while(temp <= r){
        int middle = temp + (r-temp)/2;
        if(middle <= x/middle){
            sqrt = middle;
            temp = middle + 1;
        }else{
             r = middle - 1;
        }
    }

    return sqrt;
}

int main()
{
    
    //test cases...
    printf("Square root of 2: \nExpected: 1\tActual: %d\n", sqrt_func(2));
    printf("Square root of 4: \nExpected: 2\tActual: %d\n", sqrt_func(4));
    printf("Square root of 8: \nExpected: 2\tActual: %d\n", sqrt_func(8));
    printf("Square root of 9: \nExpected: 3\tActual: %d\n", sqrt_func(9));
    printf("Square root of 1024: \nExpected: 32\tActual: %d\n", sqrt_func(1024));
    printf("Square root of 555555: \nExpected: 745\tActual: %d\n", sqrt_func(555555));
    printf("Square root of 123456789: \nExpected: 11111\tActual: %d\n", sqrt_func(123456789));
    printf("\nFor the example below, think of integer overflow: \n");
    printf("Square root of 2147395600: \nExpected: 46340\tActual: %d\n", sqrt_func(2147395600));



    return 0;
}
