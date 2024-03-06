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

struct blist {
    struct blist *rnext;
    struct blist *lnext;
};

struct belem {
    int a;
    struct blist node;
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

struct list * get_middle_node(struct list *head, struct list *end)
{
    struct list *fast, *slow;
    int i = 0;
    
    fast = head;
    slow = head;
    while (fast != end) {
        fast = fast->next;
        i++;
        if ((i%2) == 0) {
            slow = slow->next;
        }
    }
    return slow;
}
struct blist* list_btree(struct list *head, struct list *end) 
{
    struct list *mid;
    struct belem *root;
    struct elem *p;
    
    if (head == NULL) {
        return NULL;
    }
    if (end == head)
        return NULL;
      
     
    mid = get_middle_node(head, end);

/*     
    if (mid == head) {
         p = containerofnode(elem, node, mid);  
         root = malloc(sizeof(struct belem));
         root->a = p->a;
         printf("Mis head %d\n", p->a);
         return &(root->node);
    }
 */
    p = containerofnode(elem, node, mid);
    root = malloc(sizeof(struct belem));
    root->a = p->a;
    printf("Mis id %d\n", p->a);
    root->node.lnext = list_btree(head, mid);
    root->node.rnext = list_btree(mid->next, end);
    return &(root->node);
}
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


int main()
{
    struct list *head = NULL;
    struct list *mid;
    struct blist *bnode;
    struct elem *entry, *d, *p;
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
    print_list(head);
    bnode = list_btree(head, NULL);
    print_blist_inorder_recursive(bnode); 
}
