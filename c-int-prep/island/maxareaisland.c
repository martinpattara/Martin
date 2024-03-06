#include <stdio.h>
#include <stdlib.h>

#define N 8
#define M 13

void getmaxarea(int g[N][M], int r, int c,  int *area)
{
    int i , j;

    if ((r >=  N)|| (c >= M)) {
        return;
    } 
    for (i = c; i < N; i++) {  
        if (g[r][i] == 0) {
            printf("returning %d %d\n", r, c);
            return;
        } else {
            *area = *area + 1;     
            printf("area %d r %d c %d\n", *area, r, i); 
            getmaxarea(g, r + 1, i, area);
        }
    }
}


int maxareaisland(int g[N][M])
{
    int i, j;
    int area = 0, max_area = 0;
 
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            area = 0;
            getmaxarea(g, i, j, &area);
            if (area > max_area) {
                max_area = area;
            } 
        }
    }
    return max_area;
}


int main()
{

   int grid[][13] = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}};

   printf("max area is %d", maxareaisland(grid));

}
