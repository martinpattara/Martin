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

struct list*  k_r_reverse(struct list *p, int k)
{
   struct list  *tmp, *prev, *nhead;
   int i = 0;

   if (p == NULL)
       return NULL;

   printf("In k_r_reverse\n");
   prev = NULL;
   nhead = p;

   for (i = 0; i < k && (p != NULL); i++) {
               tmp = p->next;
               p->next = prev;
               prev = p;
               p = tmp;
   }
   nhead->next = k_r_reverse(p, k);
   printf("Nhead = %x\n", nhead->next);
   return prev;
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
    int x;
    

    while(1) {
        printf("Enter the element\n");
        scanf("%d", &x);
        if (x != 0)
            insert(x, &head);
        else
            break;
    }
    print_list(head);
    head = k_r_reverse(head, 2);
    print_list(head);
}
