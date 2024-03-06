#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pattern_replace (char *str, char *pattern, char *replace)
{
   int i,j, p = 0, r = 0;
   int plen = strlen(pattern);
   int rlen = strlen(replace);
   int len = strlen(str);
   char res[1000];
 
   for (i = 0; i < len; i++) {

       printf("i = %d\n", i);      
       for (j = i; i < j + plen; i++) {
           if (str[i] != pattern[p++]) {
               i = j;
               res[i] = str[i];
               p = 0;
               break;
           } else {
               if (p == (plen )) {
                   memcpy(&str[j], replace, rlen);
                   memcpy(&res[j], replace, rlen);
                   printf("mattched\n");
                   if (rlen < plen) {
                       memcpy(&str[j + rlen],&str[j + plen], (len - (j +plen)));
                       str[len - (plen -rlen)] = '\0';
                   }  
                   i = j + 1;
                   p = 0;
                   break;
               }  
           }
        }
	    printf("\n");   
   }
   res[i] = '\0';
   printf("res is %s\n", res);
}

int main()
{
    char str[] = "abcbc";
    char pattern[] = "abc";
    char replace[] = "cba";
    pattern_replace(str, pattern, replace);
    printf("%s\n", str);

}
