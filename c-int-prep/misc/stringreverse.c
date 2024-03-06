#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

    int i,j=0,s,e;
    char test_string[] = "This is a test";
    char result[128];
 
    e = strlen(test_string);
    for (i = e-1; i >=0; i--){
        result[j++] = test_string[i];
    }
    result[j] = '\0';
    printf("%s\n", result);
}
