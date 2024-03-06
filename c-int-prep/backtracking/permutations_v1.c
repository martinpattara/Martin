/* 
 *                 123
 *           123   213  321  
 *         
 *       123 132  213 231 321 312
 *  
 *  
 *  
 *
 *
 *
 *
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

void swap(char *a, char *b)
{
    char t;

    t = *a;
    *a = *b;
    *b = t;
}

int permutation(char* nums, int pos, int num)
{
    int i = 0;
    char *tmp;

    if ( pos == (N-1)) {
         for (int j = 0; j < N; j++) {
                printf("%d",nums[j]);
            }
            printf("\n");
    }
  

    for (i = pos ; i < N; i++) {

        swap(&nums[i], &nums[pos]);
        permutation(nums, pos + 1, ++num);
        swap(&nums[i], &nums[pos]);
    }
}

int** permute(char* nums, int numsSize, int *rsize) 
{
    int num = 0, i;

    permutation(nums, 0, num); 
    
}

int main()
{
    int rsize;
    char array[N] = {1,2,3};
    permute(array, N, &rsize);
  

}
