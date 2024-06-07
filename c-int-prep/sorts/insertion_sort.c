#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;

}

void insertion_sort(int *x, int s)
{
    int i, j, min;

    for (i = 0; i < s; i++) {
        for (j = i; j > 0; j--) {
            if (x[j] < x[j-1]) {
                 swap(&x[j], &x[j-1]);
            }
        }
    }
}

int main()
{

    int x[] = {2,3,4,6,8,9,1,5,7};
   
    insertion_sort(x, 9);
    for (int i = 0; i < 9; i++) {
        printf("%d\n", x[i]); 
    } 
}

