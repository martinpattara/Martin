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

void list_insert(struct list **head, struct list *node)
{
    node->next = *head;
    *head = node;
}

void insert(int x, struct list **head)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = x;
    list_insert(head, &entry->node);
    
}

void delete_duplicate(struct list **head)
{
    struct list *ptr;
    struct elem *p;
    ptr = *head;
    int x;

    while(ptr != NULL) {
        p = containerofnode(elem, node, ptr);
        x = p->a;
        while (ptr->next &&
               ((containerofnode(elem, node, ptr->next))->a == x)) {
        	ptr->next = ptr->next->next;
        }
        ptr = ptr->next;        
   }
}

void delete_duplicate_unique(struct list **head)
{
    struct list **ptr;
    struct elem *p;
    int x;
    int nounique;

    ptr = head;
    while(*ptr != NULL) {
        p = containerofnode(elem, node, *ptr);
        x = p->a;
        nounique = 0;
        while ((*ptr)->next &&
               ((containerofnode(elem, node, (*ptr)->next))->a == x)) {
            *ptr = (*ptr)->next;
            nounique = 1;
        }
        if (nounique) {
            *ptr = (*ptr)->next;
        }
        ptr = &((*ptr)->next);
   }
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
    delete_duplicate_unique(&head);
    print_list(head);
}
