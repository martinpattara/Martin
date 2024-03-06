#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

struct stack {
	uint8_t *mem;
    uint8_t head;
    uint8_t tail;	
};

int stack_init(struct stack *st, int sz)
{
    st->mem = malloc(sz * 4);
    st->head = 0;
    st->tail = 0;
    return 0;
}

int stack_push(struct stack *st, int elem)
{
   st->mem[st->head++] = elem;
}

int stack_pop(struct stack *st)
{
   return st->mem[--st->head]; 
}


int main()
{
    struct stack s;
    int i;
  
    stack_init(&s, 10);
    for (i = 0; i < 10; i++) {
        stack_push(&s, i);
    }
    for(i = 0; i < 10; i++) {
        printf("%d\n", stack_pop(&s)); 
    }
}
