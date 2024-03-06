#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int print_matrix(char m[N][N])
{
  int i , j;
  for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%x",m[i][j]);
        }
        printf("\n");
    }
}

void create_graph_matrix(char e[][2], int n, char g[N][N])
{
  int i, r, c;


  for (i=0; i < n; i++) {
      r = e[i][0];
      c = e[i][1];
      g[r-1][c-1] = 1;
      g[c-1][r-1] = 1;
          
  }
}

int find_center(char g[N][N])
{
  int i , j;
  for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if ((i !=j) && !g[i][j]) {
                break;
            }
        }
        if (j == (N)) {
            return i+1;
        } else {
           printf("%d\n", j);
        }
  }
  return -1;
}




int main()
{

   char g[N][N];
   int n;
   char  edges[][2] = {{1,2},{5,1},{1,3},{1,4}};

   n = sizeof(edges)/sizeof(edges[0]);

   memset(g, 0x0, N*N);

   create_graph_matrix(edges, n, g);
   print_matrix(g);
   printf("center node is %d\n", find_center(g));
}   

  





