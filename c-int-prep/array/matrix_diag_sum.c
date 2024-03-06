#include <stdio.h>
#include <stdlib.h>

#define N 3


int matrix_sum(int m[N][N])
{

    int i, j = 0, sum = 0;

    for (i = 0; i < N; i++) {
         sum = sum + m[i][i];
    }
    for (i = N-1; i >=0; i--) {
        if ((N%2) && (i != j)) {
            sum = sum  +  m[i][j];
        }
        j++;
    }
    return sum;

}


int main()
{
    int m[N][N] = {{1,2,3},{4,5,6},{7,8,9}};
    int i , j;
    int sum;

    sum = matrix_sum(m);
    printf("sum is %d\n", sum);
    
}
