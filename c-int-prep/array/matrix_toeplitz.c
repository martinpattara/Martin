#include <stdio.h>
#include <stdlib.h>

#define N 3

int print_matrix(int m[N][N])
{
  int i , j;
  for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%x",m[i][j]);
        }
        printf("\n");
    }
}
int toeplitz_matrix(int m[N][N])
{
  int i, j = 0, k = 0;
  for (i = N-1; i >=0; i--) {
      k = 0;
      for (j = i; j < N; j++) {
          printf("%d\n", m[j][k++]);
      }
  }
  for (i = 1; i < N; i++) {
      k  = 0;
      for (j = i; j < N; j++) {
          printf("%d\n", m[k++][j]);
      }  
  }
  
}


int main()
{
    int m[N][N] = {{1,2,3},{4,5,6},{7,8,9}};
    int i , j;
    int sum;

    print_matrix(m);
    printf("After flip\n");
    toeplitz_matrix(m);
}

