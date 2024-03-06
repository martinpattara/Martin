#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//537264819
#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
 
struct blist {
    struct blist *rnext;
    struct blist *lnext;
};

struct elem {
	int a;
    struct blist node;
};

struct list {
    struct list *next;
};

struct qelem {
    struct blist *a;
    struct list node;
};

void list_insert_head(struct list **head, struct list *node)
{
    node->next = *head;
    *head = node;
}

struct list *list_pop(struct list **head)
{
   struct list *node;
   node = *head;
   if (*head == NULL)
        return NULL;
   *head  = (*head)->next;
   return node;
}

void list_insert_tail(struct list **head, struct list *node)
{
    struct list **ptr;

    ptr = head;
    while (*ptr != NULL) {
        ptr = &((*ptr)->next);
    }
    *ptr = node;
}

void insert_tail(struct list **head, struct blist *x)
{
    struct qelem *p;

    p = malloc(sizeof(*p));
    p->a = x;
    p->node.next = NULL;
    list_insert_tail(head, &p->node);
}

void insert_head(struct list **head, struct blist *x)
{
    struct qelem *p;

    p = malloc(sizeof(*p));
    p->a = x;
    p->node.next = NULL;
    list_insert_head(head, &p->node);
}

void blist_insert(struct blist **head, struct blist *node, int x)
{
    struct blist **ptr;
    struct elem *entry;
 
    ptr = head;
    while (*ptr != NULL) {
        entry = containerofnode(elem, node, *ptr);
        if (x > entry->a) {
            ptr = &((*ptr)->rnext);
            printf("Right node\n");
           
        }  else { 
            ptr = &((*ptr)->lnext);
            printf("Left node\n");
        }
    }
    *ptr = node;
}

void insert(int x, struct blist **head)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = x;
    entry->node.rnext = NULL;
    entry->node.lnext = NULL;
    blist_insert(head, &entry->node, x);
    
}
#if 0
void print_list(struct list *head)
{
    struct elem *p;

    while(head != NULL) {
        p = containerofnode(elem, node, head);
        printf("%x %x\n", p->a, head);
        head = head->next;
    }
}
#endif

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

void insert_stack(struct list **qhead, struct blist *ptr)
{

    while (ptr != NULL) {
        insert_head(qhead, ptr);
        ptr = ptr->lnext;
    }
}

void print_blist_inorder(struct blist *ptr)
{
   struct list *qhead = NULL;
   struct list *node;
   struct qelem *q;
   struct elem *p; 
  
    insert_stack(&qhead, ptr); 
    while(node = list_pop(&qhead)) {
        q = containerofnode(qelem, node, node);
        p = containerofnode(elem, node, (q->a));
        printf("%d\n", p->a);
        insert_stack(&qhead, q->a->rnext);
    } 
}


void print_blist_preorder(struct blist *head)
{
   struct list *qhead = NULL;
   struct list *node;
   struct qelem *q;
   struct elem *p; 
   
   insert_tail(&qhead, head);
   while(node = list_pop(&qhead)) {
      q = containerofnode(qelem, node, node);
      p = containerofnode(elem, node, (q->a));
      printf("%d\n", p->a);
      if (q->a->rnext) {
    //       p = containerofnode(elem, node, (q->a->lnext));
     //     printf(" queueing  %d\n", p->a);
           insert_head(&qhead, q->a->rnext);
      }
      if (q->a->lnext) {
       //   p = containerofnode(elem, node, (q->a->rnext));
       //   printf("queueing %d\n", p->a); 
          insert_head(&qhead, q->a->lnext);
      }
   }
}




void print_blist_bfs(struct blist *head)
{
   struct list *qhead = NULL;
   struct list *node;
   struct qelem *q;
   struct elem *p; 
   
   insert_tail(&qhead, head);
   while(node = list_pop(&qhead)) {
      q = containerofnode(qelem, node, node);
      p = containerofnode(elem, node, (q->a));
      printf("%d\n", p->a);
      if (q->a->lnext) {
    //       p = containerofnode(elem, node, (q->a->lnext));
     //     printf(" queueing  %d\n", p->a);
           insert_tail(&qhead, q->a->lnext);
      }
      if (q->a->rnext) {
       //   p = containerofnode(elem, node, (q->a->rnext));
       //   printf("queueing %d\n", p->a); 
          insert_tail(&qhead, q->a->rnext);
      }
   }
}

int main()
{
    struct blist *head = NULL;
    int x;
    

    while(1) {
        printf("Enter the element\n");
        scanf("%d", &x);
        if (x != 0)
            insert(x, &head);
        else
            break;
    }
//    print_blist_preorder(head);
//    print_blist_inorder(head);
      print_blist_postorder(head);
}
