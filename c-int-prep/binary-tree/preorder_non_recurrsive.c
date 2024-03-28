#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))


struct blist {
    struct blist *rnext;
    struct blist *lnext;
};

struct elem {
    int a;
    struct blist node;
};


struct stack {
    struct blist **mem;
    uint8_t head;
    uint8_t tail;
};

int stack_init(struct stack *st, int sz)
{
    st->mem =  (struct blist **)malloc(sz * sizeof(struct blist *));
    st->head = 0;
    st->tail = 0;
    return 0;
}

int stack_push(struct stack *st, struct blist *elem)
{
   st->mem[st->head++] = elem;
}

struct blist * stack_pop(struct stack *st)
{
   return st->mem[--st->head];
}
void insert_stack_left(struct stack *st, struct blist *node)
{
    if (node == NULL) {
        return;
    }
    while (node != NULL) {
        stack_push(st, node);
        node = node->lnext;
    }
}

void print_blist_preorder(struct blist *head)
{
    struct blist *node;
    struct elem *p;
    struct stack s;
    int i;

    stack_init(&s, 100);


    stack_push(&s, head);
    while (node = stack_pop(&s)) {
         p = containerofnode(elem, node, node);
         printf("%d\n", p->a);
         if (node->rnext) {
             stack_push(&s, node->rnext);
         }
         if (node->lnext) {
            stack_push(&s, node->lnext);
         }
    }
}

struct blist* sortedArrayToBST(int* nums, int numsSize)
{
   int mid;
   struct elem *entry;

   if (numsSize == 0)
       return NULL;

   mid = numsSize/2;
   printf("Mid value of array in sortedArrayToBST is %d %d\n", nums[mid], numsSize);
   entry = malloc(sizeof(struct elem));
   entry->a = nums[mid];
   entry->node.lnext = sortedArrayToBST(nums, mid );
   entry->node.rnext = sortedArrayToBST(&nums[mid +1], (numsSize-mid) -1 );
   return  &(entry->node);

}


int main()
{
    struct blist *head = NULL;
    int x[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    head  = sortedArrayToBST(x, sizeof(x)/sizeof(int));

    print_blist_preorder(head);

}
