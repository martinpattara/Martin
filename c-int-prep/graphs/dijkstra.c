#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

 
#define N 5
struct list {
    struct list *next;
};

struct elem {
	int a;
    int cost;
    struct list node;
};

#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))

struct list * list_pop(struct list **head) 
{
    struct list *tmp = NULL;
    
    if (*head) {
        tmp =  *head;
       *head = (*head)->next;
    } 
    return tmp;
}

void remove_node(struct list **head, struct list *node)
{
    struct list **p;

    p = head;
    while(*p!= NULL) {
        if (*p == node) {
            *p = node->next;
            return;
        }
        p  = &((*p)->next);
    }

} 
void list_insert(struct list **head, struct list *node)
{
    node->next = *head;
    *head = node;
}

void priority_list_insert(struct list **head, struct list *node, int ncost)
{
    struct list **p;
    struct elem *entry;
    
    p = head;

    while(*p!= NULL) {
        entry = containerofnode(elem, node, *p);

        if (entry->cost > ncost) {
            break;
        }        
        p = &((*p)->next);
    }
    node->next = *p;
    *p = node;
}

void insert(int x, struct list **head, int w)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = x;
    entry->cost = w;
    list_insert(head, &entry->node);
}
void priority_insert(struct list **head, int s, int w)
{
    struct elem *entry;
    entry = malloc(sizeof(struct elem));
    entry->a = s;
    entry->cost = w;
    priority_list_insert(head, &entry->node, w);
}


void print_list(struct list *head)
{
    struct elem *p;

    while(head != NULL) {
        p = containerofnode(elem, node, head);
        printf("%x\n", p->a);
        head = head->next;
    }
}

struct list *head[N+1];

void add_edge(int s, int d, int w) 
{
    insert(d, &head[s], w);
}

struct list *qlist = NULL; 

void priority_queue_insert(int s, int w)
{
   priority_insert(&qlist, s, w);

}

struct elem vertices[N+1];
int prev[N+1];


int shortest_path(int s, int d)
{
    int i = 0;
    struct list *qnode;

    printf("In shortest path first\n");
    //  Insert all vertices.
    for (i = 0; i <= N; i++) {
        if (i != s) { 
            vertices[i].a = i;
            vertices[i].cost = 99;        
        } else {
            vertices[i].a = i;
            vertices[i].cost = 0;
        }
        priority_list_insert(&qlist, &vertices[i].node, vertices[i].cost); 
    }

    while (qnode = list_pop(&qlist)) {
       
       struct elem *qelem, *nelem, *vertice;
       struct list *neig_node, *vnode;
       int w;

       printf("Printing qlist\n");      
       print_list(qlist);

       // update neighbor weights       
       qelem = containerofnode(elem, node, qnode);

       if (head[qelem->a]) {
           vnode = head[qelem->a]->next;
       } else {
           vnode = NULL;
       }
       
       while(vnode != NULL) {
           neig_node = vnode;
           nelem = containerofnode(elem, node, neig_node);
           w = qelem->cost + nelem->cost;
           if (w < vertices[nelem->a].cost) {
               vertices[nelem->a].cost = w;
               prev[nelem->a] = qelem->a;        
               remove_node(&qlist, &vertices[nelem->a].node);
               priority_list_insert(&qlist, &vertices[nelem->a].node, w); 
                        
           }
           vnode = vnode->next;
       }
   }
} 

void print_path(int s, int d)
{
   if (s == d) {
       printf("%d->", s);
       return;
    }
    print_path(s, prev[d] );
    printf("%d->", d);
}      

int main()
{
   int n, i;
   char  edges[][3] = {{1,3,1},{1,2,3},{1,4,2},{2,5,3},{2,3,1},{4,5,2},{4,3,1}};
 
 
   n = sizeof(edges)/sizeof(edges[0]);
   for (i = 0; i < n; i++) {
       add_edge(edges[i][0], edges[i][1], edges[i][2]);
   }
   for (i = 0; i < N; i++) {
       print_list(head[i]);     
   }
#if 0
   // testibg priority queue//
   printf("Testing priority queue\n");
   {
       int testv[][2] = {{1,3},{2,3},{3,1},{4,5},{5,6}};
       for (i = 0; i < 5; i++) {
           priority_queue_insert(testv[i][0], testv[i][1]);
       }
   }
#endif
//   print_list(qlist);
   shortest_path(1,5);
   printf("Printing path\n");
   print_path(1,5);
   printf("Printing costs\n");
   for (i = 0; i <= N; i++) {
      printf("%d\n",  vertices[i].cost);
   }

}
