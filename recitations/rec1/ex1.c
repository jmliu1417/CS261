#include <stdio.h>
 
void function (int *x, int n) {
    int i, temp, j = n, swapped = 1;
    while (swapped) {
        swapped = 0;
        for (i = 1; i < j; i++) {
            if (x[i] < x[i-1]) {
                
                temp = x[i];
                x[i] = x[i-1];
                x[i-1] = temp;
                
                swapped = 1;
            }
        }
        j--;
    }
}
 
int main () {
    int x[] = {15, 56, 12, -21, 1, 659, 3, 83, 51, 3, 135, 0};
    int size = sizeof(x) / sizeof(x[0]);
    int i;
    for (i = 0; i < size; i++)
        printf("%d%s", x[i], i == size-1 ? "\n" : " ");
    
    function(x, size);
    
    for (i = 0; i < size; i++)
        printf("%d%s", x[i], i == size-1 ? "\n" : " ");
    
    return 0;
}