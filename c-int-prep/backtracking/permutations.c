/* 1234
 *  1234
 *   1243
 *  1324
 *   1342
 *  1432
 *   1423
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

#define N 4

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

    for (i = pos ; i < N; i++) {

        tmp = malloc( N);
        memcpy(tmp, nums, N);
        swap(&tmp[i], &tmp[pos]);
        if (i != pos) { 
            for (int j = 0; j < N; j++) {
                printf("%d",tmp[j]);
            }
            printf("\n");
        }
        permutation(tmp, pos + 1, ++num);
    }
}

int** permute(char* nums, int numsSize, int *rsize) 
{
    int num = 0, i;
    char **permus = malloc(6); 

        for (int j = 0; j < N; j++) {
            printf("%d", nums[j]);
        }
        printf("\n");
        permutation(nums, 0, num); 
    
}

int main()
{
    int rsize;
    char array[N] = {1,2,3,4};
    permute(array, N, &rsize);
  

}
