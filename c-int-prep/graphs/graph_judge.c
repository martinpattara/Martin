#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

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
          
  }
}

int find_judge(char g[N][N])
{
  int i , j;
  for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (g[i][j] == 1) {
                break;
            }
        }
        if (j == N) {
            break;
        }
        
   }
   printf("i =%d\n", i);  
   if (i != N) {
       for (j = 0; j < N; j++) {
            if ((i!=j) && !g[j][i]) {
                return -1;
            }
        }
        return i + 1; 
  }
  return -1;
}




int main()
{

   char g[N][N];
   int n;
   char  edges[][2] = {{1,3},{2,3}};

   n = sizeof(edges)/sizeof(edges[0]);

   memset(g, 0x0, N*N);

   create_graph_matrix(edges, n, g);
   print_matrix(g);
   printf("Judge node is %d\n", find_judge(g));
}   

  





