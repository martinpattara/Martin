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
struct list * reverse(struct list *head)
{
     struct list *rst;
     if (head->next == NULL)
         return head;
     
    rst  =  reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return rst;
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

int check_palandrome(struct list **head, struct list *tail)
{
    int result;

    if (tail == NULL)
       return 1;

    result = check_palandrome(head, tail->next);

    if (result == 0) {
        return 0;
    } else {
        struct elem *h, *t;
        h = containerofnode(elem, node, *head);
        t = containerofnode(elem, node, tail);
        printf("%d %d\n", h->a, t->a);
        if (h->a == t->a) {
          *head = ((*head)->next);
          return 1;
        } else 
           return 0;
         
    }
}


int main()
{
    struct list *head = NULL;
    struct list *lhead;
    struct elem *entry, *d;
    int x;
    int result = 0;
    

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
    print_list(head);
    lhead = head;
    result = check_palandrome(&lhead, head);
    printf("result is %d\n", result);
}
