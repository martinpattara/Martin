#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t id[3];
int cnt = 0;


void *printNumber(void *p)
{
   int x;
   printf("p = %d\n", *((int *)p));
  
   while (1) { 
       x = cnt%3;
       if (x == *((int *)p)) {
           printf("thread %d %d\n",*(int*)p ,cnt);
           cnt++;
       }
   }
}

int main()
{
    int i = 0, *ptr;
    int arg[3];

    for (i = 0; i < 3; i++) {
        arg[i] = i; 
        pthread_create(&id[i], NULL, printNumber, &arg[i]);
    } 
    for (i = 0; i < 3; i++) {
        pthread_join(id[0], NULL);
    }
}

