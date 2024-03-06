#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
 

struct list {
    struct list *next;
    struct list *prev;
};

struct elem {
	int a;
    struct list node;
};

void list_insert(struct list **head, struct list *node)
{
    node->next = *head;
    node->prev = NULL;
    if (*head)
    	(*head)->prev = node;
    *head = node;
}

void list_delete(struct list **head, struct list *node)
{
    if (node == *head) {
         *head = node->next;
    } 

    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;  
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


int main()
{
    struct list *head = NULL;
    struct elem *elem, *delem;
    int x;
    

    while(1) {
        printf("Enter the element\n");
        scanf("%d", &x);
        if (x != 0) {
           elem =  insert(x, &head);
           if (x == 3) {
               delem = elem;
           }
         
        } else
            break;
    }
    list_delete(&head, &(delem->node));
    print_list(head);
}
