#include <stdio.h>
#include <stdlib.h>

#define N 10

void insertion_sort_wiki(int *a)
{
    int i,j,k,t;

    for (i = 0; i < N; i++) {
        for (j = i; j > 0; j--) { 
           if (a[j] > a[j-1]) {
               break; 
           } else {
              t = a[j];
              a[j] = a[j-1];
              a[j-1] = t;
           }
        }
  
    }
}

/* trying to do the shift at one shot when the correct posistion is found  (a[i] > a[j])
 * We need a special case if no correct position is found. Ie even the 0th element of
 * sorted list is also greater than ith element 
 *
 * The approach used in wikipedia is much better. It puts the ith elemt in sorted list 
 * by swapping and proceeding when ever it finds ith element is less than the element (jth)
 *  being checked. It breaks the loop when ith element is greater than jth element */ 

void insertion_sort(int *a)
{
    int i,j,k,t;

    for (i = 0; i < N; i++) {
        for (j = i; j >= 0; j--) {
           if (a[i] > a[j]) {
              t = a[i];
              for (k = i; k > j; k--) {
                  a[k] = a[k-1];
              }
              a[k+1] = t; 
              break;
           }
        }
        if (j < 0) {
            t = a[i];
            for (k = i; k >= 0; k--) {
                  a[k] = a[k-1];
            }
            a[0] = t;
       }
       

    }
}


int main()
{
    int a[10] = {4,2,3,6,5,9,8,1,7,10};
    insertion_sort_wiki(a);

    for (int i = 0; i < N; i++) {
        printf("%d", a[i]);
    }
    printf("\n");
}
