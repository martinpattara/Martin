#include <stdio.h>
#include <stdlib.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))

struct blist {
    struct blist *rnext;
    struct blist *lnext;
};

struct elem {
    int a;
    struct blist node;
};

void print_blist_preorder_recursive(struct blist *head)
{
   struct elem *p;

   if (head == NULL)
       return;

    p = containerofnode(elem, node, head);
    printf("%d\n", p->a);

    print_blist_preorder_recursive(head->lnext);


    print_blist_preorder_recursive(head->rnext);
}

struct blist* tree_to_vine_iteratinve(struct blist **root)
{
    struct blist *p, *r, **q;

    p = *root;
    q = root;
    while (p != NULL) {
        if (p->lnext) {
            r = p->lnext;
            p->lnext = p->lnext->rnext;
            r->rnext = p;
           *q = r;
           p = r;
        } else {
           q = &((*q)->rnext);
           p = p->rnext;
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
    int x[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

    head  = sortedArrayToBST(x, sizeof(x)/sizeof(int));
    
    print_blist_preorder_recursive(head);
    tree_to_vine_iteratinve(&head);
    print_blist_preorder_recursive(head);

}
