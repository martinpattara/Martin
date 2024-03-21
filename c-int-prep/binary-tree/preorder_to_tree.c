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

struct blist *preorder_to_bst(int *a, int *size, int *index)
{
    int local_index = *index;
    struct elem *entry; 
    int x;
    
    if (*size ==0) {
        return NULL;
    }

     x = a[(*index)];
     (*size)--;
     (*index)++;

     entry = malloc(sizeof(struct elem));
     entry->a = x;
     entry->node.rnext = NULL;
     entry->node.lnext = NULL;
 
    
     if(a[*index] < x) {
         entry->node.lnext = preorder_to_bst(a, size, index);
         if (local_index == 0 ) {
             entry->node.rnext = preorder_to_bst(a, size, index);
         } else if (a[local_index] > a[local_index -1]) {
             entry->node.rnext = preorder_to_bst(a, size, index);            
         } else if (a[local_index -1] > a[*index]) {
             entry->node.rnext = preorder_to_bst(a, size, index);
         } else {
             entry->node.rnext = NULL;
         }
         return &(entry->node);
     } else  {
           int i = 0;
      /*
         if (local_index == 0 ) {
             entry->node.rnext =  preorder_to_bst(a, size, index);
         } else if (a[local_index] > a[local_index -1]) {
             entry->node.rnext =  preorder_to_bst(a, size, index);
         } else if (a[local_index -1] > a[*index]) {
            entry->node.rnext = preorder_to_bst(a, size, index);
         }  else {
            entry->node.rnext = NULL;// preorder_to_bst(a, size, index);
         }*/
           for (i = 0; i < *index; i++) {
               if (a[*index] > a[i]) {
                   break;
               }
           }
           if (i != *index) {
               entry->node.rnext = NULL;
           } else {
               entry->node.rnext = preorder_to_bst(a, size, index);
           }
           return &(entry->node);
        
     }
}



int main() 
{
    struct blist *head = NULL;
    int x[] = {7,5,4,2,1,3,6,9,8,20,15,13,12,11,14,25,23,26,27,28,29,31,30,32};
//    int x[] = {7,5,4,2,1,3,6,9,8,11};
    int size = sizeof(x)/sizeof(int);
    int index = 0;

    head = preorder_to_bst(x, &size, &index); 

    print_blist_preorder_recursive(head);
    printf("******************\n"); 
    print_blist_inorder_recursive(head);

}
