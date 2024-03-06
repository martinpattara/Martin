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
            if (a[j] <  a[p]) { 
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

int main()
{
    int i = 0;
    int a[] = {10,5,4,9,1,3,6,2,7,8};
    
    for (i = 0; i < sizeof(a)/sizeof(int); i++) {
        printf("%d\n", a[i]);
    }
    printf("\n");
 
    heapify(a);

    for (i = 0; i < sizeof(a)/sizeof(int); i++) {
        printf("%d\n", a[i]);
    }
}

