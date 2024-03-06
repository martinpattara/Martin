#include <stdio.h>

int main()
{
 unsigned int x =1, y, z;
 z = 1;
 printf("%d\n", z);
 y = (0x80000000);
//for (int i = 0; i < 32; i++)
 //    y = y << 1;
y = (y << z);
 printf("%x" ,y);

}

