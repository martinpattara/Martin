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
    list_delete(&head, &(d->node));
    print_list(head);
}
