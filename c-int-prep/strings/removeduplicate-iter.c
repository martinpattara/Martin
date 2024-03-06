#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reduce_string(char *str)
{
	int i = 0, j, c =0, l =0, o =0;

    for (i=0; i < strlen(str); i++) {
        j =  i;
        printf("i is %d\n", i);
        while (str[i] == str[i+1]) {
            printf("matching\n");
            i++;
        }
        if (j != (i)) {
            l = c;
            c = str[i];
            memcpy(&str[j], &str[i+1], (strlen(str) + 1 - i));
            i = i -(i -  j);
            printf("after i is %d\n", i);
            i--;
            if ((c == l) || (str[i] == str[i+1])|| (l == str[i+1]))  {
                i--;
            } else {
                printf("%c %c\n", c, l);
            }
        }
    }
    printf("string is %s\n", str);
}

int main()
{
    char s[] = "aababbcaa";
    char s1[] = "azxxzy";
    char s2[]= "aabba";
    char s3[] = "aaaa";
    reduce_string(s);
    reduce_string(s1); 
    reduce_string(s2);
    reduce_string(s3);    
 }
