#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
 
#define N 6
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

struct stack {
    uint8_t *mem;
    uint8_t head;
    uint8_t tail;
};

int stack_init(struct stack *st, int sz)
{
    st->mem = malloc(sz * 4);
    st->head = 0;
    st->tail = 0;
    return 0;
}

int stack_push(struct stack *st, int elem)
{
   st->mem[st->head++] = elem;
}

int stack_pop(struct stack *st)
{
   if (st->head == 0)
       return 0;

   return st->mem[--st->head];
}

struct list *head[N+1];

void add_edge(int s, int d) 
{
    insert(d, &head[s]);
}

int ftrees[N];
 
int find(int x)
{
   if (ftrees[x] == -1) {
       return x;
   }
   ftrees[x] = find(ftrees[x]);
   return ftrees[x];

}

int check_path_disjoint(char edges[][2], int n_edges,  int s, int d)
{
    int i;
    int x, y;

    for (i = 0; i < N; i++) {
       ftrees[i] = -1;
    }

    for (i = 0; i < n_edges; i++) {
    
       x = edges[i][0];
       y = edges[i][1];
     
       if (find(x) != find(y)) {
           ftrees[y] = x;
       }
    }
    printf("%d %d\n", find(s), find(d));
    return  (find(s) == find(d)); 
     
}

int main()
{
   int n, i;
   char  edges[][2] = {{0,1},{0,2},{1,3},{3,5},{5,4},{4,3}};
 
  

   n = sizeof(edges)/sizeof(edges[0]);
   for (i = 0; i < n; i++) {
       add_edge(edges[i][0], edges[i][1]);
   }
   for (i = 0; i < N+1; i++) {
       print_list(head[i]);
       printf("\n");
   }
   if (check_path_disjoint(edges, n, 1, 4)) {
       printf("\nPath exists\n");
   } else {
       printf("\nPatch doesnot exists\n");
   }
   for (i = 0; i < N; i++) {
       printf("%d\n", ftrees[i]);
   }
}
