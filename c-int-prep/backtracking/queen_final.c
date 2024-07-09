#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

void print_matrix(int c[N][N]) 
{
    int i,j;
    for (i = 0; i < N; i++ ) {
            for (j = 0; j < N; j++) {
                printf("%d", c[i][j]);
            }
            printf("\n");
    }
}

int check_pos(int c[N][N], int r, int pos)
{

    int i, rd, fd;


    for (i = 0; i < r; i++) {
        if (c[i][pos] == 1){
            return -1;
        } 
    } 
    rd  = pos - 1 ;
    fd = pos + 1;
    for (i = r-1; ((i >= 0) && (rd >= 0)); i--,rd--) {
        if (c[i][rd] == 1 ) {
            return -1;
        }
    }
    for (i = r-1; ((i >= 0) && (fd < N)); i--, fd++) {
        if (c[i][fd] == 1 ) {
            return -1;
        }
    }
    return 0;
}

int queue_place(int m[N][N], int r, int c)
{
    int j,i;
    
    if (check_pos(m, r, c)) {
        printf("Positiuin failed %d %d\n", r, c);
        return 0; 
    }
    printf("Positiuin passed %d %d\n", r, c);
    m[r][c] = 1;
    
      
    if (r == (N-1)) {
        printf("QUEUE position found\n");
        print_matrix(m);
        return 1;
    }
    for (i = 0; i < N; i++) {
           queue_place(m, r+1, i);
       
    }
    m[r][c] = 0;
}



int noofqueens(int n)
{
   int i = 0;
   int c[N][N];

   memset(c, 0x0, (N*N) * sizeof(int));
   for (i = 0; i < N; i++ ) {
       queue_place(c, 0, i); 
       c[0][i] = 0;
   }
}

int main()
{
    noofqueens(N);

}
