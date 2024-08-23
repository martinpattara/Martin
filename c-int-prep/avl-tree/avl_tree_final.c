#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
#define ELEM(head) (containerofnode(elem, node, (head)))->a


struct blist {
    int h;
    struct blist *rnext;
    struct blist *lnext;
};

struct elem {
    int a;
    struct blist node;
};

struct blist *head = NULL;

struct blist * right_rotate(struct blist* x)
{
   struct blist *y;

    y = x->lnext;
    x->lnext = y->rnext;
    y->rnext = x;    
    return y;
}


struct blist * left_rotate(struct blist* x)
{
   struct blist *y;

    y = x->rnext;
    x->rnext = y->lnext;
    y->lnext = x;
    return y;
}


void blist_insert(struct blist **head, struct blist *node, int x)
{
    struct blist **ptr, **z;
    struct elem *entry;
    int da[16], k = 0;
/***********Insertion**************/
    ptr = head;
    z = head;
    while (*ptr != NULL) {
        entry = containerofnode(elem, node, *ptr);
        if ((*ptr)->h != 0) {
           z = ptr; 
           k  = 0;     
        } 
        if (x > entry->a) {
            ptr = &((*ptr)->rnext);
            printf("Right node\n");
            da[k++] = 1;

        }  else {
            ptr = &((*ptr)->lnext);
            printf("Left node\n");
            da[k++] = 0;
        }
    }
    *ptr = node;
/***********Updating Balance********/
    ptr = z;
    k = 0;
    while (*ptr != node) {
        struct elem *p;
        if (da[k++] == 1) {
            (*ptr)->h++;

             ptr = &((*ptr)->rnext); 
        } else {
           (*ptr)->h--;
            ptr = &((*ptr)->lnext);
        }
    }

/***********Balanceing****************/
   ptr = z;
   k = 0;
   if ((*ptr)->h == -2) {
        struct blist *x, **xp;
        
		x = ((*ptr)->lnext);
        xp = &((*ptr)->lnext);
        if (x->h == -1) {

            printf("right rotate\n");
            *ptr =  right_rotate(*ptr);
            (*ptr)->h = 0;
            (*ptr)->rnext->h = 0;
  
        } else {
            printf("left rotate\n");
            *xp =  left_rotate(x);
            *ptr =  right_rotate(*ptr);
             if ((*ptr)->h == 0) {
                 ((*ptr)->rnext)->h = 0;
                 ((*ptr)->lnext)->h = 0;
             } else if ((*ptr)->h == -1) {
                 ((*ptr)->rnext)->h = 1;
                 ((*ptr)->lnext)->h = 0;
                 (*ptr)->h = 0; 
             } else {
                 ((*ptr)->rnext)->h = 0;
                 ((*ptr)->lnext)->h = -1;
                 (*ptr)->h = 0;
             }
        }
   } else if ((*ptr)->h == 2) {
        struct blist *x, **xp;
       
  
        printf("balance is 2\n");
        x = ((*ptr)->rnext);
        xp = &((*ptr)->rnext);

        if (x->h == 1) {
            printf("left rotate\n");
            *ptr =  left_rotate(*ptr);
            (*ptr)->h = 0;
            (*ptr)->lnext->h = 0;

        } else {
            printf("right rotate\n");
            *xp =  right_rotate(x);
            *ptr = left_rotate(*ptr);
             if ((*ptr)->h == 0) {
                 ((*ptr)->rnext)->h = 0;
                 ((*ptr)->lnext)->h = 0;
             } else if ((*ptr)->h == -1) {
                 ((*ptr)->rnext)->h = 1;
                 ((*ptr)->lnext)->h = 0;
                 (*ptr)->h = 0;
             } else {
                 ((*ptr)->rnext)->h = 0;
                 ((*ptr)->lnext)->h = -1;
                 (*ptr)->h = 0;
             }
        }
 
   } else {

   }
}

void print_blist_preorder_recursive(struct blist *head)
{
   struct elem *p;

   if (head == NULL)
       return;

    p = containerofnode(elem, node, head);
    printf("%d %d\n", p->a, head->h);

    print_blist_preorder_recursive(head->lnext);

    print_blist_preorder_recursive(head->rnext);
}


void insert(int x, struct blist **head)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = x;
    entry->node.h = 0;
    entry->node.rnext = NULL;
    entry->node.lnext = NULL;
    blist_insert(head, &entry->node, x);

}

void blist_delete(struct blist **head, int x)
{
    struct blist **ptr, **z, **pa[20];
    struct elem *entry;
    struct blist *item;
    struct blist *r, *s;

    int da[16], k = 0;
/***********search**************/
    ptr = head;
    z = head;
    while (*ptr != NULL) {
        entry = containerofnode(elem, node, *ptr);
        pa[k] = ptr;
        if (x > entry->a) {
            ptr = &((*ptr)->rnext);
            printf("Right node\n");
            da[k++] = 1;
        } else if (x < entry->a) {
            ptr = &((*ptr)->lnext);
            printf("Left node\n");
            da[k++] = 0;
        } else {
            item = *ptr;
            break;
        }
    }
  /**************delete*************/
   r = (*ptr)->rnext;
   if ((*ptr)->rnext == NULL ) {
       *ptr = (*ptr)->lnext;
   } else if (((*ptr)->rnext->lnext) == NULL) {
		(*ptr)->rnext->lnext =  (*ptr)->lnext;
        *ptr = (*ptr)->rnext;
   } else {
        int j  = 0;
        struct blist **qtr;
        struct blist *l , *r;
        printf("3rd case\n");

        qtr = &((*ptr)->rnext);
        l  = (*ptr)->lnext;
        r =  (*ptr)->rnext;
    
        da[k++]  = 1;
        pa[k] = qtr;
        while (((*qtr)->lnext) != NULL) {
            entry = containerofnode(elem, node, *qtr);
            printf("%x\n", entry->a);
            da[k++]  = 0;  
            pa[k] = qtr;

            qtr = &((*qtr)->lnext);
            
        }
        *ptr = *qtr;
        *qtr  = (*qtr)->rnext;
        (*ptr)->lnext = l;
        (*ptr)->rnext = r; 
   }
/**********Update height and rebalance*************/
   while (--k >= 0) {
       struct blist **y;
       struct blist *x, **xp;

       y = pa[k];
       if (da[k] == 0) {
           (*y)->h++;
           if ((*y)->h == 1) {
               break;
           } else if  ((*y)->h == 2) {
              x = (*y)->rnext;
              xp = &((*y)->rnext);
              if (x->h == -1) {
                 *xp = right_rotate(x);
                 *y = left_rotate(*y);
                 if ((*y)->h == 0) {
                       ((*y)->rnext)->h = 0;
                       ((*y)->lnext)->h = 0;
                   } else if ((*y)->h == -1) {
                       ((*y)->rnext)->h = 1;
                       ((*y)->lnext)->h = 0;
                       (*y)->h = 0;
                   } else {
                       ((*y)->rnext)->h = 0;
                       ((*y)->lnext)->h = -1;
                       (*y)->h = 0;
                   }
           
              } else {
                 printf("left rotaing\n");
                 *y = left_rotate(*y);
                 if (x->h == 0) {
                     x->h = -1;
                     (*y)->h = 1;
                     break;
                 } else {
                     (*y)->h = 0;
                     (*y)->lnext->h = 0;
                 }
              }
           }
            
       } else {
           (*y)->h--; 
           if ((*y)->h == -1) {
               break;
           } else if  ((*y)->h == -2) {
               x = (*y)->lnext;
               xp = &((*y)->lnext);
               if (x->h == 1) {
                   *xp = left_rotate(x);
                   *y = right_rotate(*y);
             	   if ((*y)->h == 0) {
                       ((*y)->rnext)->h = 0;
                       ((*y)->lnext)->h = 0;
                   } else if ((*y)->h == -1) {
                       ((*y)->rnext)->h = 1;
                       ((*y)->lnext)->h = 0;
                       (*y)->h = 0;
                   } else {
                       ((*y)->rnext)->h = 0;
                       ((*y)->lnext)->h = -1;
                       (*y)->h = 0;
                   }
               } else {
                   *y = right_rotate(*y);
                   if (x->h == 0) {
                       x->h = 1;
                       (*y)->h = -1;
                       break;
                   } else {
                       x->h = (*y)->h = 0;
                   }
               }
           }
       }
   }
}
void delete_node(struct blist **head, int x)
{
	blist_delete(head, x);
}

#define N 3

int main()
{
	int i = 0;
    int a[N] = {5,3,8};
//    int a[N] = {10,5,15,3,7,20,6,8};  //delete test case  
//    int a[N] = {5,3,15,2,4,10,20,9,17,25,1,23,30};
	for (i = 0; i < N; i++) {
         insert(a[i], &head);
    }
    print_blist_preorder_recursive(head);
#if 1
    printf("Deleting Node\n");
    delete_node(&head, 5);
    print_blist_preorder_recursive(head);
#endif
}


