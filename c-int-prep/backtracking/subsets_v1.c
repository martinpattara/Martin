#include <stdio.h>
#include <stdlib.h>

#define N 4

void print_subset(int *arr, int *subarr, int len, int pos, int end)
{
   int i = 0, j;
   int *subset;

   if (end == N) {
       return;
   }

   for (j = end +1 ; j < N; j++) {
       subset = malloc((len +1) * 4);
       for (i = 0; i < len; i++) {
           printf("%d", subarr[i]);
           subset[i] = subarr[i]; 
       }
       printf("%d", arr[j]);
       subset[i] = arr[j];
       printf("\n");

       print_subset(arr, subset, len +1, pos ,j);
       free(subset);
   } 
}

int main()
{
    int i = 0;
    int arr[N] = {1,2,3,4};

    for (i = 0; i < N; i++) {
        printf("%d\n", arr[i]);
        print_subset(arr,&arr[i], 1, i, i);
    }
}
