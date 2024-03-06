#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
 
#define N 3
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

void print_list(struct list *head)
{
    struct elem *p;

    while(head != NULL) {
        p = containerofnode(elem, node, head);
        printf("%x", p->a);
        head = head->next;
    }
}

struct list *head[N+1];

void add_edge(int s, int d) 
{
    insert(d, &head[s]);
} 

int main()
{
   int n, i;
   char  edges[][2] = {{1,3},{2,3}};
 
  

   n = sizeof(edges)/sizeof(edges[0]);
   for (i = 0; i < n; i++) {
       add_edge(edges[i][0], edges[i][1]);
   }
   for (i = 0; i < N; i++) {
       print_list(head[i]);     
   }
}
