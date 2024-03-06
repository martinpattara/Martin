#include <stdio.h>
#include <stdlib.h>

void heapify(int *a)
{
    int i, t, p, k, j;
    for (i = 1; i < 10; i++) {
        j = i;
        printf("p = %d\n", p);
        while (j > 0) {
            p = (j-1)/2;
            printf("pi = %d\n", p);
            if (a[j] >  a[p]) { 
                t = a[p];
                a[p] = a[j];
                a[j] = t;
                j = p;
            } else {
                break;
            }
        }
        for (k = 0; k < 10; k++) {
            printf("%d\n", a[k]);
        }
        printf("\n");    
    }
}

void heap_sort(int *a)
{
    int i, j, e, t;
    int largest, n;
    int rch, lch;

    heapify(a);
    n = 10;
    for (i = 0; i < n; i++) {
         e = (n-1) - i;
         t = a[0];
         a[0] = a[e];
         a[e] = t;
         
		 printf("sif down i =  %d e =%d\n", i, e);
         for (int k = 0; k < 10; k++) {
            printf("%d\n", a[k]);
         }       
         for (j =0;j < e; j++) {
             lch = (2*j) + 1;
             rch = (2*j) + 2;
             largest = j;

             printf("lch = %d  rch = %d , largest = %d\n", lch, rch, largest);
             if (lch < e) {
                 if (a[largest] < a[lch]) {
                     largest = lch;
                 }
                 if (rch < e) { 
                     if (a[largest] < a[rch]) {
                         largest = rch;
                     }
                 }
             }
             if (largest != j) {
                 t = a[j];
                 a[j] = a[largest];
                 a[largest] = t;
             } else {
                 break;
             }

         }
          
    }
}

int main()
{
    int i = 0;
    int a[] = {10,5,4,9,1,3,6,2,7,8};
    
    for (i = 0; i < sizeof(a)/sizeof(int); i++) {
        printf("%d\n", a[i]);
    }
    printf("\n");
 
    heap_sort(a);

    for (i = 0; i < sizeof(a)/sizeof(int); i++) {
        printf("%d\n", a[i]);
    }
}

