#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t id[3];
int i = 0;


void *printNumber(void *p)
{
   int x;
   
   x = i%3;
   if (x == *p ) {
       printf("thread %d %d",*p ,i);
   }
}

int main()
{
    int i = 0, *ptr;
    for (i = 0; i < 3; i++) {
        pthread_create(&id[0], NULL, printNumber, &i);
    } 
     for (i = 0; i < 3; i++) {
        pthread_join(id[0], &ptr);
    }


}

