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

    printf("cheking position row %d pos  %d\n", r, pos);

    for (i = 0; i < r; i++) {
        if (c[i][pos] == 1){
            printf("r %d  pos %d failed in hori\n", i, pos); 
            return -1;
        } 
    } 
    rd  = pos - 1 ;
    fd = pos + 1;
    for (i = r-1; ((i >= 0) && (rd >= 0)); i--,rd--) {
        if (c[i][rd] == 1 ) {
            printf("r %d  pos %d failed in rdia\n", i, rd);
            return -1;
        }
    }
    for (i = r-1; ((i >= 0) && (fd < N)); i--, fd++) {
        if (c[i][fd] == 1 ) {
            printf("r %d  pos %d failed in fdia\n", i, fd);
            return -1;
        }
    }
    return 0;
}

int queue_place(int c[N][N], int r)
{
    int i,j;
    if (r == N) {
        printf("QUEUE position found\n");
#if 0
        for (i = 0; i < N; i++ ) {
            for (j = 0; j < N; j++) {
                printf("%d", c[i][j]);
            }
            printf("\n");    
        }
#endif
        print_matrix(c);
        return 1;
    }

    for (i = 0; i < N; i++) {
       if (!check_pos(c, r, i)) {
           c[r][i] = 1;
           printf("Getting to new row %d with pos %d\n", r+1, i);
           print_matrix(c); 
           queue_place(c, r+1);
           c[r][i] = 0;
       }
    }
}


int noofqueens(int n)
{
   int i = 0;
   int c[N][N];

   memset(c, 0x0, (N*N) * sizeof(int));
   queue_place(c, 0); 
}

int main()
{
    noofqueens(N);

}
