#include <stdio.h>
#include <stdlib.h>

int *pa;
int k = 0;
int s = 10;

void push(int a)
{
    if (k == s) {
       pa = realloc(pa,(s+10) * sizeof(int));
       if (pa)
           printf("realloced\n");
       s = s +10;
    }
    pa[k++] = a; 
}

int  main()
{
    int i;

    pa = malloc(s * sizeof(int));
    for (i = 0; i < 100; i++) {
        push(i);
    }
    for (i = 0; i < 100; i++) {
        printf("%d\n", pa[i]);
    }
}
