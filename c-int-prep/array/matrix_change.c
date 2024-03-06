#include <stdio.h>
#include <stdlib.h>

#define N 3

int print_matrix(int **m)
{
  int i , j;
  for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%x",m[i][j]);
        }
        printf("\n");
    }
}

int **change_matrix(int *a)
{
  int **dp;
  int i , j;
  
  dp = malloc(sizeof(int*) * N);
  for (i = 0; i < N; i++) {
      dp[i] = (int*) malloc(sizeof(int) * N);
  }
  for (i = 0; i < N; i++) {
      for (j = 0; j <N; j++) {
          dp[i][j] = *(a);
          a++;
      }
  } 
  return dp;
}


int main()
{
    int a[9] = {1,2,3,4,5,6,7,8,9};
    int i , j;
    int sum;
    int **m;

    printf("After flip\n");
    m = change_matrix(a);
    print_matrix(m);
}

