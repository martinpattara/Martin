#include <stdio.h>
#include <stdlib.h>

#define N 4

void print_subset(int *arr, int pos, int end)
{
   int i = 0, j;

   if (end == N) {
       return;
   }

   for (j = end +1 ; j < N; j++) {
       for (i = pos; i <= end; i++) {
           printf("%d", arr[i]);
       }
       printf("%d", arr[j]);
       printf("\n");
       print_subset(arr, pos ,j);
   } 
}

int main()
{
    int i = 0;
    int arr[N] = {1,2,3,4};

    for (i = 0; i < N; i++) {
        printf("%d\n", arr[i]);
        print_subset(arr,i, i);
    }
}
