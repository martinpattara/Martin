#include <stdio.h>
#include <stdlib.h>

//0xa0a0a0b0  --> 0xa0a0
//0xb0a0a0a0

char  clear_msb_unwanted_bits(char x, int n)
{
   x = x & (~0) << (8 - n);
   return x; 
}

char clear_lsb_unwanted_bits(char x, int n)
{
   x = x & ~((~0) << (n));
   return x;
}

int extract_bits(char x, int p, int n)
{
    x = (x  >> (p - n)) & ~(~0 <<  n);
    return x;

}
int check_nibble_mirror(int x) 
{
    int i, j, s;

    for(i = 0; i < 4; i++) {
         s = 7 - i; 
         if (((x >> i ) & 1) != (x & 1 << s) >> s) {
             printf("Not mirror\n");
             return -1;
         }
    }
    printf("Mirror\n");
    return 0;  
}
int right_shift(int x)
{
    x = (x >> 1) & ~(0x1 << 31);
    return x;
}

int right_shift_n(int x, int n)
{
    x = (x >> n) & ~((~0) << (31 -n));
    return x;
}
int left_shift_n(int x, int n)
{
    x = (x << n);
    return x;
}

int ffs(int x)
{
   int i = 0;
   while (!(x  & (1 << 31))) {
       x = x << 1;
       i++;
   }
   return i;
}
//ff00000
unsigned int get_mask(unsigned int p, int n)
{
   int m = ~0;
   int op = 32 - p;

   for (int i = 0; i < 32 - p; i++) {
      m =  m << 1;
   }
   m = ~m;
   //return m;
   return (m  & (~0 << (op - n)));
}

int main()
{
   unsigned char  r;
   unsigned int  x = 0x3f; 
   r = extract_bits(x, 4, 3);
   printf("%x\n", r);
   x = 0xe7;
   check_nibble_mirror(x);
   x = 0x80000000;
   x = right_shift(x);
   //printf("%x\n", right_shift(x));
   //printf("%x\n", right_shift(x));

   x = 0xffffffff;
   while (x = right_shift_n(x, 3)) {
       printf("%x\n", x);       
   }
   x = 0xffffffff;
   while (x = left_shift_n(x, 3)) {
       printf("%x\n", x);
   }
   x = 0x10000000;
   printf("%d\n", ffs(x));
   printf("mask for pos %x\n", get_mask(8, 16));

}
