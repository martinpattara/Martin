#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reduce_string(char *str)
{
	int i = 0, j, c =0, l =0, o =0;

        i=strlen(str)-1;
        while (i > 0) {  
        j =  i;
        printf("i is %d\n", i);
        while (i > 0 && (str[i] == str[i-1])) {
            printf("matching\n");
            i--;
#if 0
            if (i == 0) {
                memcpy(&str[i], &str[j+1], (strlen(str) + 1 - i));
                return;
            }  
#endif
        }

        if (j != (i)) {
            memcpy(&str[i], &str[j+1], (strlen(str) + 1 - i));
//            if (i != 0) {
//               i = i+1;
//            }
        } else {
          i--;
        }
    }
    printf("string is %s\n", str);
}

int main()
{

    char s[] = "aababbcaa";
    char s1[] = "azxxzy";
    char s2[]= "aabba";
    char s5[]= "aaaa";
    reduce_string(s);
    printf("final string is %s\n", s);
    reduce_string(s1); 
    printf("final string is %s\n", s1);
    reduce_string(s2); 
    printf("final string is %s\n", s2);
    char s3[] = "aaaab";
    reduce_string(s3);
    printf("final string is %s\n", s3);
    char s4[] = "geekforgeeks";
    reduce_string(s4);
    printf("final string is %s\n", s4);
    reduce_string(s5);
    printf("final string is %s\n", s5);
    
 }
