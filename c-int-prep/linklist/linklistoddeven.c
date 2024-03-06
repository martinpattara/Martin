#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define containerofnode(elem, member, pointer) (struct elem *)((uint8_t *)pointer - (uint8_t *)&(((struct elem *)0)->member))
 


struct list {
    struct list *next;
};

struct elem {
	int a;
    struct list node;
};

void list_insert(struct list **head, struct list *node)
{
    node->next = *head;
    *head = node;
}

void list_delete(struct list **head, struct list *node)
{
    struct list **ptr = head;
    while (*ptr != node) {
       ptr =&((*ptr)->next);
    }
    *ptr = node->next;
}

struct elem * insert(int x, struct list **head)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = x;
    list_insert(head, &entry->node);
    return entry;
    
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

void oddeven_list(struct list **head)
{
   struct list **p1, **p2, *odd, *even;
   p1 = &((*head)->next);
   p2 = &((*head)->next->next);
   struct elem *p;
  
   if (!*head || !*p1)
       return;

   while (*p2 != NULL) {
      odd = *p2;
      // p = containerofnode(elem, node, p1);
     // printf("%x\n", p->a);
         
      *p2 = (*p2)->next;
      // p = containerofnode(elem, node, *p2);
      // printf("%x %x\n", p->a, p);
       even =  *p1;
      // p = containerofnode(elem, node, even);
      //printf(" even %x\n", p->a); 
     (*p1)  = odd;
      if (odd)
         odd->next  = even;

       if (*p2)
           p2 = &((*p2)->next);
    //   p = containerofnode(elem, node, *p2);
     //  printf("%x %x\n", p->a, p);
       p1 = &((*p1)->next);
     //  break;
   }     
}


int main()
{
    struct list *head = NULL;
    struct elem *entry, *d;
    int x;
    

    while(1) {
        printf("Enter the element\n");
        scanf("%d", &x);
        if (x != 0) {
            entry  = insert(x, &head);
            if (x == 3) {
              d = entry;
            }
        }
        else
            break;
    }
//    list_delete(&head, &(d->node));
    oddeven_list(&head);
    print_list(head);
}
