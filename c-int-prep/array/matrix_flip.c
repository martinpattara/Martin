#include <stdio.h>
#include <stdlib.h>

#define N 4

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



int matrix_flip(int m[N][N])
{

    int i, j = 0, temp = 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N/2; j++) {
            temp  = m[i][j];
            m[i][j] = m[i][N - 1 - j];
            m[i][N - 1 - j] = temp;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            m[i][j] = m[i][j] ^ 1;
        }
    }
 
}


int main()
{
    int m[N][N] = {{1,1,0,0},{1,0,0,1},{0,1,1,1},{1,0,1,0}};
    int i , j;
    int sum;

    print_matrix(m);
    matrix_flip(m);
    printf("After flip\n");
    print_matrix(m);
    
}
