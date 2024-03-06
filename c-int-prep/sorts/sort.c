#include <stdio.h>
#include <stdlib.h>

int ga[10] = {5,4,3,2,1,8,7,9,10,6};

void print_ga()
{
    int i;

    for (i = 0; i < 10; i++) {
        printf("%d",ga[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int c;
 
    c = *a;
    *a = *b;
    *b = c;
}

int partition(int *a, int l, int h)
{
    int tp = l - 1;
    int pv = h;
    int i;


    for (i = l; i < h;  i++) {
        if (a[i] < a[pv]) {
            tp = tp + 1;
            printf("Incrementing tp %d %d\n", a[i], a[pv]);
            swap(&a[i], &a[tp]);
        }
    }
    tp = tp + 1;
    swap(&a[tp], &a[pv]);
    return tp; 
}

void quick_sort(int *a, int l, int h)
{
    int p;

    if (l >= h) {
        return;
    }
    print_ga();
    printf("After partition\n");
    p  = partition(a, l ,h);
    printf("low %d  high%d p %d\n", l, h, p);
    print_ga();
    quick_sort(a, l, p - 1) ;
    quick_sort(a, p+1, h);
} 

int main()
{
    int i = 0;

    print_ga();
    quick_sort(ga, 0, 9);
    print_ga();
}


