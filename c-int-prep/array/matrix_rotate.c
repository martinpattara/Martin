#include <stdio.h>
#include <stdlib.h>

#define N 4

int print_array(int *a)
{
    int i = 0;

    for (i = 0; i < 10; i++) {
        printf("%d", a[i]);
    }
}


int rotate_array(int a[10])
{
   int temp, i;

   temp = a[9];
   for (i = 9; i > 0; i--) {
     a[i] = a[i -1];
   }
   a[0] = temp;
}

int rotate_matrix_2 (int m[2][2])
{
   int temp;
   int i, j;

   temp = m[1][0];
  
   for (i = 0 +1; i < 2 - 1; i++) {
       m[i][0] = m[i+1][0];
   } 
   for (i = 0; i < 2 -1; i++) {
      m[2-1][i] = m[2-1][i+1];
   }
   for (i =1 ; i > 0; i--) {
     m[i][1] = m[i-1][1];
   }
   for (i = 1; i >0; i--) {
      m[0][i] = m[0][i-1]; 
   }
   m[0][0] = temp; 
}
int print_matrix(int m[N][N]) 
{
  int i , j;
  for (i = 0; i < 4; i++) {
        for (j = 0; j < N; j++) {
            printf("%x",m[i][j]);
        }
        printf("\n");
    }
}
#if 0
int rotate_matrix_3 (int m[3][3])
{
   int temp;
   int i, j, n;

   for (n = 0; n < 3 - 1; n++) {
       temp = m[1][0];

       for (i = 0 + 1; i < 3 - 1; i++) {
           m[i][0] = m[i+1][0];
       }  
       for (i = 0; i < 3 -1; i++) {
          m[3-1][i] = m[3-1][i+1];
       }
       for (i = 2 ; i > 0; i--) {
         m[i][3-1] = m[i-1][3-1];
       }
       for (i = 2; i >0; i--) {
          m[0][i] = m[0][i-1];
       }
       m[0][0] = temp;
  
      printf("After %d rotate\n", n);
      print_matrix(m);
   }
}
#endif

#if 0
int rotate_matrix_3(int m[3][3])
{
   int temp;
   int i, j, n;

   for (n = 0; n < 3 - 1; n++) {
       temp = m[1][0];

       for (i = 0 + 1; i < 3 - 1; i++) {
           m[i][0] = m[i+1][0];
       }
       for (i = 0; i < 3 -1; i++) {
          m[3-1][i] = m[3-1][i+1];
       }
       for (i = 2 ; i > 0; i--) {
         m[i][3-1] = m[i-1][3-1];
       }
       for (i = 2; i >0; i--) {
          m[0][i] = m[0][i-1];
       }
       m[0][0] = temp;

      printf("After %d rotate\n", n);
      print_matrix(m);
   }
}
#endif

int rotate_matrix(int m[N][N])
{

    int temp;
    int n, i, s, k;
   
    for (k = 0; k < N/2; k++) {
    
       for (n = 0; n < (N - (k*2))  - 1; n++) {
           temp = m[k+1][k];
           s = N - k;

           for (i = k + 1; i < s - 1; i++) {
               m[i][k] = m[i+1][k];
           }
           for (i = k; i < s -1; i++) {
              m[s-1][i] = m[s-1][i+1];
           }
           for (i = s-1 ; i > k; i--) {
             m[i][s-1] = m[i-1][s-1];
           }
           for (i = s-1; i > k; i--) {
              m[k][i] = m[k][i-1];
           }
           m[k][k] = temp;
       
           //printf("After %d rotate\n", n);
           //print_matrix(m);
       }
       printf("After %d round\n", k);
       print_matrix(m); 
   }

}


int main()
{
    int x[10] = {0,1,2,3,4,5,6,7,8,9};
   // int m[2][2] = {{0,1},{2,3}};
//   int m[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
     int m[4][4] = {{0x0,0x1,0x2,0x3},{0x4,0x5,0x6,0x7},{0x8,0x9,0xa,0xb}, {0xc,0xd,0xe,0xf}};
    int i , j;
	//rotate_array(x);
   // print_array(x);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%x",m[i][j]);
        }
        printf("\n");
    }
    rotate_matrix(m);
    printf("After rotate\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%x",m[i][j]);
        }
        printf("\n");
    }
}
