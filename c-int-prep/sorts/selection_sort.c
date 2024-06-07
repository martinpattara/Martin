#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int t;

    t = *a;
    *a = *b;
    *b = t;

}

void selection_sort(int *x, int s)
{
    int i, j, min;

    for (i = 0; i < s; i++) {
        min = i;
        for (j = i; j < s; j++) {
            if (x[j] < x[min]) {
                min = j;
            }
        }
        swap(&x[i], &x[min]);
    }


}

int main()
{

    int x[] = {2,3,4,6,8,9,1,5,7};
   
    selection_sort(x, 9);
    for (int i = 0; i < 9; i++) {
        printf("%d\n", x[i]); 
    } 
}

