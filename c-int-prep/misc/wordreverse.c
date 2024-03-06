#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

    int i,j,s,e;
    char test_string[] = "This is a test";
    char result[128];
 
    e = strlen(test_string);
    result[e--] ='\0';
    for (i = 0; i <= strlen(test_string); i++){
        printf("%c\n", test_string[i]);
        if ((test_string[i] == ' ') || (test_string[i] == '\0')) {
            for (j = i - 1; j >=s; j--) {
               result[e] = test_string[j];
                printf("%c\n", result[e]);
                e--;
            }
            s = i+1;
            if (test_string[i] == ' ') 
            result[e--] = ' ';
        }
    }
    printf("%s\n", result);
}
