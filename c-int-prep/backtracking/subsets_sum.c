#include <stdio.h>
#include <stdlib.h>

#define N 6

int sum = 0;
int result = 9;

void check_subset_sum(int *arr, int pos,  int *bitmap)
{
   int i = 0, j;

    
   if (sum > result) {
       return;
   }
   if (sum == result) {
      for (i = 0; i < N; i++) {
          if (bitmap[i]) {
              printf("%d - ",arr[i]);
          } 
      }
      printf("\n");
   } 
   for (i = pos;  i < N; i++) { 
       bitmap[i] = 1;
       sum = sum + arr[i];
       check_subset_sum(arr, i + 1, bitmap);
       bitmap[i] = 0;
       sum = sum - arr[i];
   } 
}

int main()
{
    int arr[N] = {3,34,4,12,5,2};
    int bitmap[N] = {0, 0, 0, 0, 0, 0};
    
    check_subset_sum(arr, 0, bitmap);
}
