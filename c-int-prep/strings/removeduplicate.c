#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reduce_string(char *str, int index)
{
	int i = 0, j, c, t;

    printf("Reduce string %s\n", &str[index]); 
    for (i = index; i < strlen(str); i++ ) {
        if (str[i] != str[i + 1]) {
            reduce_string(str , i + 1);
            break;
        }
    }
    j = i; 
    if (str[i+1] == str[i]) {
        t = i+1;
    } else {
        t = i;
    }
 
    while (str[j] == str[j-1]) {
        printf("same %c\n", str[j]);
        j--;       
    }
    printf("string before = %s\n", &str[i]);
    c = (strlen(str)+1  - t + 1); 
    printf("Count = %d i = %d, j = %d\n", c, i , j);
    if ((i != j) ||(t != i)) {
        memcpy(&str[j],&str[t+1], c);
    } 
    printf("string = %s\n", &str[index]);
    return;
}

int main()
{
    char s[] = "aababbcaa";
    char s1[] = "azxxzy";
    reduce_string(s, 0);
    reduce_string(s1, 0); 
    
}
