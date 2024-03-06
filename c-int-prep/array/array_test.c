#include <stdio.h>
#include <stdlib.h>

void change(int a[10])
{
  a[0] = -1;
}

int main()
{
    int a[10] = {0,0,0,0,0,0,0,0,0,0};
    change(a);
    printf("%d", a[0]);
}
