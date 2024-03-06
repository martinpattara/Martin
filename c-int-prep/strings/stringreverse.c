#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[] = "hello world";
    int i = 0, j = 0;

    char *res;
    res = malloc(sizeof(str));
   
    j = strlen(str) - 1;

    while (j >= 0) {
        res[i++] = str[j--];
    }
    res[i] = '\0';
    printf("Reversed string is %s\n", res);
}
