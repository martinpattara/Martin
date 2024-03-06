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
int check_path(int s, int d)
{
    struct stack vis;
    struct elem *p;
    struct list *ptr;
    char visited[N+1];
    int n;
    
    stack_init(&vis, N);
    memset(visited, 0x0, N);

    stack_push(&vis, s);

    while (n = stack_pop(&vis)) {
        if (n == d) {
            return 1;
        }
        printf("n = %d\n", n);
        if (visited[n] == 0) {
            visited[n] = 1;
            
            ptr = head[n];
            while(ptr != NULL) {
               p = containerofnode(elem, node, ptr);
               printf("p is %d\n", p->a);
               if (visited[p->a] == 0) {
                  printf("Pushing to stack\n");
                  stack_push(&vis, p->a);
               }
               ptr = ptr->next;
            }
        }
    }
    return 0;
}
struct stack vis;
char visited[N+1];

void find_all_path(int s, int d, char *path, int pos)
{
    struct elem *p;
    struct list *ptr;
    int n;
    int i;

    if (s == d) {
        path[pos++] = s;
        for (i = 0; i < pos; i++) {
                printf("%d-->", path[i]);
        }
        printf("\n");
        return;
    } else {
        path[pos++] = s;
        if (visited[s] == 0) {
            visited[s] = 1;

            ptr = head[s];
            while(ptr != NULL) {
               p = containerofnode(elem, node, ptr);
               if (visited[p->a] == 0) {
                   find_all_path(p->a, d, path, pos);
               }
               ptr = ptr->next;
            }
        }
    }
}


int main()
{
   int n, i;
   char path[N+1];
   char  edges[][2] = {{0,1},{1,2},{2,3},{2,4},{3,5}};
   struct stack vis;
   struct elem *p;
   struct list *ptr;
   char visited[N+1];



   n = sizeof(edges)/sizeof(edges[0]);
   for (i = 0; i < n; i++) {
       add_edge(edges[i][0], edges[i][1]);
   }
   for (i = 0; i < N+1; i++) {
       print_list(head[i]);
       printf("\n");
   }
   stack_init(&vis, N);
   memset(visited, 0x0, N);
   
   find_all_path(1, 5 ,path, 0);

}
