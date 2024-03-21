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
void  delete(struct blist **head, int x)
{
    struct blist  *l, **np;
    struct elem *entry, *p;

    np = head;
    while (*np != NULL) {
        entry = containerofnode(elem, node, *np);
        if (x == entry->a) {
            break;
        }
        if (x > entry->a) {
            np = &(*np)->rnext;
        }  else {
            np = &(*np)->lnext;
        }
    }

    if ((*np)->rnext == NULL) {
        *np = (*np)->lnext;
    } else if ((*np)->rnext->lnext == NULL) {
        l = (*np)->lnext;
        *np = (*np)->rnext;
        (*np)->lnext = l;
    } else {
       struct blist **lp;
       struct blist *r;

 
       l = (*np)->lnext;
       r = (*np)->rnext;
       lp = &((*np)->rnext->lnext);
       while ((*lp)->lnext != NULL) {
           lp = &(*lp)->lnext;
       }

       *np =  *lp;
       *lp = (*lp)->rnext; 
       (*np)->lnext = l;
       (*np)->rnext = r; 
    }
}



int main() 
{
    struct blist *head = NULL;
    int x[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

    head  = sortedArrayToBST(x, sizeof(x)/sizeof(int));
    
    delete(&head, 7);   
    printf("delete done\n"); 
    print_blist_inorder_recursive(head); 

}
