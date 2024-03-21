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

void print_blist_inorder_recursive(struct blist *head)
{
   struct elem *p;

   if (head == NULL)
       return;

    print_blist_inorder_recursive(head->lnext);

    p = containerofnode(elem, node, head);
    printf("%d\n", p->a);

    print_blist_inorder_recursive(head->rnext);
}

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

struct blist *preorder_inorder_to_tree(int *p, int *in,  int size, int *index, int low, int high)
{
    int local_index = *index;
    struct elem *entry; 
    int x;
    int last;
    int last_elem;
    int i;

    printf("Low %d high %d\n", low, high);
#if 0
    if (*index == size) {
        printf("Index overshooting\n");
        return NULL;
    }
#endif
    if (high < low) {
        printf("Low greater than high\n");
        return NULL;
    
    }
    if (*index == size) {
        printf("Index overshooting\n");
        return NULL;
    }
    x = p[(*index)];
     (*index)++;

     entry = malloc(sizeof(struct elem));
     entry->a = x;
     entry->node.rnext = NULL;
     entry->node.lnext = NULL;
     printf("Node = %d\n", x);

    if (low == high) {
        printf("single node\n");
        return &(entry->node);
    }
    for (i = low; i < high; i++) {
        if (in[i] == x) {
            last = i -1;
            printf("x = %d l = %d\n", x, i);
            break;
        }
    }
    entry->node.lnext = preorder_inorder_to_tree(p, in, size , index, low, last);
    entry->node.rnext = preorder_inorder_to_tree(p, in, size , index, last + 2, high);
    return  &entry->node;
}



int main() 
{
    struct blist *head = NULL;
//    int x[] = {7,5,4,2,1,3,6,9,8,20,15,13,12,11,14,25,23,26,27,28,29,31,30,32};
//    int x[] = {7,5,4,2,1,3,6,9,8,11};
//    int x[] = {7,5,4,2,1,3,6};
//    int x[] = {6,8,9,10,11,12};
      int p[] = {7,4,2,1,3,5,6,9,8,10};
      int i[] = {1,2,3,4,5,6,7,8,9,10};
    int size = sizeof(p)/sizeof(int);
    int index = 0;

    head = preorder_inorder_to_tree(p, i, size, &index, 0 , size -1); 

    print_blist_preorder_recursive(head);
    printf("******************\n"); 
    print_blist_inorder_recursive(head);

}
