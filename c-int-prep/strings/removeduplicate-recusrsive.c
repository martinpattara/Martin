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
            if (str[i] == str[i + 1]) {
                i++;
            }
            break;
        }
    }
    if (i != index) {
        memcpy(&str[index], &str[i+1],  strlen(str) - i);
        return;
    }
}

int main()
{
    char s[] = "aabba";
    reduce_string(s, 0);
    printf("final string is %s\n", s);
}
