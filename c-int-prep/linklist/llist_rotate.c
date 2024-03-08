#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
 

struct list {
    struct list *next;
};

struct elem {
	int a;
    struct list node;
};

void list_insert_tail(struct list **head, struct list *node)
{
    struct list **ptr;
 
    ptr = head;
    while (*ptr != NULL) {
        ptr = &((*ptr)->next);
    }
    *ptr = node;
}

void insert(int x, struct list **head)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = x;
    list_insert_tail(head, &entry->node);
    
}

void k_reverse(struct list **head, struct list *p, int k)
{
   struct list  *tmp, *prev, **next_head;
   int i = 0;

   if (p == NULL)
       return;

   prev = NULL;

   next_head = &p->next; 
   for (i = 0; i < k && (p != NULL); i++) {
               tmp = p->next;
               p->next = prev;
               prev = p;
               p = tmp;
   }
   *head = prev;
   k_reverse(next_head, p, k);
}

void rotate_list(struct list **head, struct list *p, int *n)
{
    struct list *temp;

    if (p->next != NULL) {
        rotate_list(head, p->next, n);
    } else {
        return;
    }
    printf(" b %d\n", *n);
    if (*n > 0) {
        printf("%d\n", *n);
        temp = p->next;
        temp->next = *head;
        *head = temp;
        p->next = NULL;
        (*n)--; 
    } 
}
#if 0
/******* with temperory variable***/
struct list * rotate_list_nonreccursive(struct list *head, int n)
{
    struct list *p,*q, *prev, *qprev;
    p = q =  head;
    
    while (p != NULL) {
        prev = p;
        p = p->next;
     
        if (n) { 
            n--;
        } else {
           qprev = q;
           q = q->next;
        }
    }
    prev->next = head;
    qprev->next = NULL;
    return q;
   
}
#endif
#if 1
struct list * rotate_list_nonreccursive(struct list *head, int n)
{
    struct list **p,**q, *prev, *qprev, *new_head;;
    p = q =  &head;

    while (*p!= NULL) {
        p = &((*p)->next);

        if (n) {
            n--;
        } else {
            q = &((*q)->next);
        }
    }
    if (q == &head)  {
        return head;
    } else {
        *p = head;
        new_head = *q;
        *q = NULL;
    
        return new_head;
    }

}
#endif

void swap(struct list **head, struct list *p)
{
  struct list *temp, **next_head;

  if ((p == NULL) || (p->next == NULL)) {
      *head = p;
      return;
  }
  next_head = &p->next;
  temp =  p->next->next;
  p->next->next = p;
  *head = p->next;
  *next_head = NULL;
  swap(next_head, temp);

}
void print_list(struct list *head)
{
    struct elem *p;

    while(head != NULL) {
        p = containerofnode(elem, node, head);
        printf("%x %x\n", p->a, head);
        head = head->next;
    }
}


int main()
{
    struct list *head = NULL;
    int x, n = 3;
    

    while(1) {
        printf("Enter the element\n");
        scanf("%d", &x);
        if (x != 0)
            insert(x, &head);
        else
            break;
    }
    print_list(head);
    head = rotate_list_nonreccursive(head, 3);
    print_list(head);
}
