#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//537264819
#define containerofnode(elem, member, pointer) (struct elem *)((void *)pointer - (void *) &(((struct elem *)0)->member))
#define ELEM(head) (containerofnode(elem, node, (head)))->a

struct blist **pa = NULL;
int *pac = NULL;
//int k = 0;
//int s = 0;
int k = 0;
#if 0
void push_dir(int n)
{
    static int *pa = NULL;
    static int s = 0;

    if (kc == s) {
       if (s == 0) {
          pa = malloc(10 * sizeof(int));
       } else {
           pa = realloc(pa,(s+10) * sizeof(int));
       }
       if (pa)
           printf("realloced\n");

       s = s + 10;
    }
    pa[kc++] = n;
}
#endif

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

struct lelem {
    int a;
    struct list node;
};


struct qelem {
    struct blist *a;
    struct list node;
};

void push_node(struct blist *n, int d)
{
    static int s = 0;

    if (k == s) {
       if (s == 0) {
          pa = malloc(10 * sizeof(struct blist*));
          pac = malloc(10 * sizeof(int));
       } else {
           pa = realloc(pa,(s+10) * sizeof(struct blist*));
           pac = realloc(pa,(s+10) * sizeof(int));
       }
       if (pa)
           printf("realloced\n");

       s = s + 10;
    }
    pa[k] = n;
    pac[k] = d;
    k++;
}


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
struct blist* rotate_right_tree_iterative(struct blist **root)
{
    struct blist *p, *r, **q;
    
    p = *root;
    q = root;
    while (p != NULL) {
        if (p->lnext) {
            r = p->lnext;
            p->lnext = p->lnext->rnext;
            r->rnext = p;
           *q = r;
           p = r;
        } else {
           q = &((*q)->rnext);
           p = p->rnext;
        }
    }
}

struct blist*  rotate_right_tree(struct blist *root)
{
    struct blist *l, *r;
    struct elem *entry;

    if (root == NULL) {
       return root;
    }
    root->lnext = rotate_right_tree(root->lnext);
    if (root->lnext) {
       entry = containerofnode(elem, node,  root->lnext);
       printf("%d\n", entry->a);
    }
    l = root->lnext;
    r = root;
    if (l == NULL) {
        root = r;
    } else {
        r->lnext = l->rnext;
        l->rnext = r;
        root = l;
    }
    root->rnext  = rotate_right_tree(root->rnext); 
    return root;
}

void rotate_right(struct blist *l, struct blist *r)
{
   r->lnext = l->rnext;
   l->rnext = r;
}
void rotate_left (struct blist *l, struct blist *r)
{
   l->rnext = r->lnext;
   r->lnext = l;
}


#if 0
struct blist* increasingBST(struct blist* root)
{
   if (root == NULL) {
       return root;
   }
   root = increasingBST(root->left);
   root = rotate_right(root->left, root);
   root = increasingBST(root->right);
   return root;
}
#endif

struct blist *root_insert_node(struct blist *head, struct blist *node)
{
    struct blist **ptr;
    struct blist *n;
    struct elem *entry;
    int x;
    
    entry = containerofnode(elem, node, node);
    x = entry->a;
    ptr = &head;
    while (*ptr != NULL) {
        entry = containerofnode(elem, node, *ptr);
        n = *ptr;
        if (x > entry->a) {
            ptr = &((*ptr)->rnext);
            printf("Right node\n");
            push_node(n, 1);

        }  else {
            ptr = &((*ptr)->lnext);
            printf("Left node\n");
            push_node(n, 0);
        }
    }
    *ptr = node;
    for (; k > 0; k--) {
        if (pac[k-1] == 1) {
            pa[k-1]->rnext = node->lnext;
            node->lnext = pa[k-1];
        } else {
            pa[k-1]->lnext = node->rnext;
            node->rnext = pa[k-1]; 
        }
        if (k > 1) {
            struct blist **p;

            if (pac[k-2] == 1) {
                pa[k-2]->rnext = node;
            } else {
                pa[k-2]->lnext = node;
            }
        } else {
            printf("Updating head\n");
            return node;
        } 
    }
}

struct blist * insert_in_root(struct blist *head, int x)
{
     struct elem *entry;

     entry = malloc(sizeof(struct elem));
     entry->a = x;
     entry->node.rnext = NULL;
     entry->node.lnext = NULL;
     head = root_insert_node(head, &(entry->node));
     return head;

} 

struct blist *root_insert(struct blist *head, int x)
{
    struct blist *root;
    struct elem *entry;
    struct elem *new_entry;

    if (head == NULL) {
        entry = malloc(sizeof(struct elem));
        entry->a = x;
        entry->node.rnext = NULL;
        entry->node.lnext = NULL;
        root = &(entry->node);
        return root;
    }
   
    entry = containerofnode(elem, node, head);
    if (x > entry->a) {
     //  if (head->rnext) {
           root = root_insert(head->rnext, x);
           printf("Rotating left %d\n",  entry->a);
           rotate_left(head, root);
#if 0
       } else {
          new_entry = malloc(sizeof(struct elem));
          entry->a = x;
          entry->node.rnext = NULL;
          entry->node.lnext = NULL;
          root = &(entry->node); 
       }
#endif
    } else {
//       if (head->lnext) {
           root = root_insert(head->lnext, x);
           printf("Rotating right %d\n", entry->a);
           rotate_right(root, head);
#if 0
       } else {
           new_entry = malloc(sizeof(struct elem));
           entry->a = x;
           entry->node.rnext = NULL;
           entry->node.lnext = NULL;
           root = &(entry->node);
       }
#endif
    }
    return root;
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

struct blist* delete(struct blist *head, int x)
{
    struct blist *p, *q, *l, **np;
    struct elem *entry;

    p = head;
    np = &head;
    while (p != NULL) {
        entry = containerofnode(elem, node, p);
        if (x == entry->a) {
            break;
        }
        q = p;
        if (x > entry->a) {
            np = &(p->rnext);
            p = p->rnext;
          
        }  else {
            np = &(p->lnext);
            p = p->lnext;
        }
    }
    if (p->rnext == NULL) {
        *np = p->lnext;
    } else if (p->rnext->lnext == NULL) {
        *np = p->rnext;
        q->lnext->lnext = p->lnext;
    } else {
       l = p->rnext->lnext;
       while (l->lnext!= NULL) {
           l = l->lnext;
       }
       l->lnext = p->lnext;
       *np = p->rnext;
    }
    return head;
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

struct list *iter_qhead = NULL;
struct blist *iter;

void inorder_iter_init(struct blist *ptr)
{
   struct list *qhead = NULL;
   struct list *node;
   struct qelem *q;
   struct elem *p;

   insert_stack(&iter_qhead, ptr);

}

struct blist * next_bst_elem()
{
   struct qelem *q; 
   struct list *node;

   if (iter == NULL) {
       node = list_pop(&iter_qhead);
       q = containerofnode(qelem, node, node);
       iter = q->a;
       return iter;
   } else {
       printf("Iter not null\n");
       if (iter->rnext) {
           insert_stack(&iter_qhead, iter->rnext);
       } 
       node = list_pop(&iter_qhead);
       q = containerofnode(qelem, node, node);
       iter = q->a;
       return iter;
   }
}


int minimum(int a , int b)
{
   if (a < b)
       return a;
   else 
       return b;
}

int minDiffInBST(struct blist* root)
{
    struct list *qhead = NULL;
    struct list *node;
    struct qelem *q;
    struct elem *p, *r = NULL;
    int min = 0xfffffff;

    insert_stack(&qhead, root);
    while(node = list_pop(&qhead)) {
        q = containerofnode(qelem, node, node);
        p = containerofnode(elem, node, (q->a));
        printf("%d\n", p->a);
        if (r){
          min = minimum(min, p->a - r->a);
        } else { 
          min = minimum(min, p->a);
        }
        r = p;
        insert_stack(&qhead, q->a->rnext);
    }
    return min;
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
struct blist* sortedArrayToBST(int* nums, int numsSize)
{
   int mid;
   struct elem *entry;

   if (numsSize == 0) 
       return NULL;
   
   mid = numsSize/2;
   printf("Mid value of array in sortedArrayToBST is %d %d\n", nums[mid], numsSize);
   entry = malloc(sizeof(struct elem));
   entry->a = nums[mid];
   entry->node.lnext = sortedArrayToBST(nums, mid );
   entry->node.rnext = sortedArrayToBST(&nums[mid +1], (numsSize-mid) -1 );
   return  &(entry->node);
  

}
struct list *get_middle_node(struct list *head)
{
    struct list *slow, *fast, *prevslow;
    slow = fast = head;
    while (fast!= NULL && fast->next != NULL) {
       prevslow = slow; 
       slow = slow->next;
       fast = fast->next->next;
    }
    prevslow->next = NULL;
    
    return slow;
}

struct blist * sortedlistToBST(struct list *head)
{
    struct list *mid;
    struct lelem *p;
    struct elem *entry;

    if (head == NULL)
        return NULL;


    if (head->next == NULL) {
        p = containerofnode(lelem, node, head);
        entry = malloc(sizeof(struct elem));
        entry->a = p->a;
        return &(entry->node);
    }
    
    mid = get_middle_node(head);
    p = containerofnode(lelem, node, mid);
    entry = malloc(sizeof(struct elem));
    entry->a = p->a;
    printf("P->a = %d\n", p->a);
    entry->node.lnext = sortedlistToBST(head);
    entry->node.rnext = sortedlistToBST(mid->next);
    return &(entry->node);
}
struct blist *create_tree_preorder(int *a, int size, int *index)
{
    struct elem *entry;
    int lsize, rsize, rsize_e, i;

    printf("size %d , index %d\n", size, *index);
    if (size <= 0) {
        return NULL;
    }

    entry = malloc(sizeof(struct elem));
    entry->a = a[*index];
    printf("P->a = %d\n", entry->a);
    entry->node.lnext  = NULL;
    entry->node.rnext = NULL;
    (*index)++;
    if (size == 1) {
        return &(entry->node);
    }
  
    for (i = *index; i < (*index+ size - 1); i++) {
        if (a[i] > entry->a) {
            printf("i = %d\n", i);
            break;
        }
    }
    lsize = (i  - *index);
    entry->node.lnext = create_tree_preorder(a, lsize, index);
    rsize = size - lsize - 1;
    rsize_e = *index + size - 1 - i;
    printf("*index  size i rsize risize_e %d %d  %d %d %d\n",*index, size, i, rsize, rsize_e);
    printf("Calling right index %d i %d size %d\n", *index, i, size);
    entry->node.rnext = create_tree_preorder(a, rsize, index);
    return &(entry->node);
}
struct blist *preordertotree(int *a, int size)
{
    int index = 0;
    struct blist *root;

    root = create_tree_preorder(a, size, &index);
    return root;
}


struct list * arraytolist(int* nums, int numsSize)
{
    int i;
    struct list *head = NULL;
    for(i = 0; i < numsSize; i++) {
       struct lelem *p;

       p = malloc(sizeof(*p));
       p->a = nums[i];
       p->node.next = NULL;
       list_insert_tail(&head, &p->node);
    }
    return head; 
}
#define MAX_H(a, b)  a > b ? a : b

int maxheight_tree(struct blist *head)
{
    int height_left, height_right;

    if (head == NULL) {
        return 0;
    }
    height_left = maxheight_tree(head->lnext);
    height_right = maxheight_tree(head->rnext);
    return MAX_H(height_left, height_right) + 1;
}

#define MIN_H(a, b)  a < b ? a : b

int minheight_tree(struct blist *head)
{
    int height_left, height_right;

    if (head == NULL) {
        return 0;
    }
    height_left = minheight_tree(head->lnext);
    height_right = minheight_tree(head->rnext);
    return MIN_H(height_left, height_right) + 1;
}

int isbst(struct blist *head) 
{
    struct elem *p, *q;
    int res = 0;

    if (head->lnext) {
        p = containerofnode(elem, node, (head));
        q = containerofnode(elem, node, (head->lnext)); 
        if (p->a < q->a) {
            return -1;
        } 
        res = isbst(head->lnext);
    }
    if (!res) {
       if (head->rnext) {
           p = containerofnode(elem, node, (head));
           q = containerofnode(elem, node, (head->rnext));
           if (p->a > q->a){
             return -1;
           }
           
res =  isbst(head->rnext);
       }
    }
    return res;
}

void flatten_tree(struct blist *head)
{
    struct blist *ptr, *tmp;
    
    if (head == NULL) {
        return;
    }
    flatten_tree(head->lnext);
    tmp = head->rnext;
    head->rnext = head->lnext;
    head->lnext = NULL;
    ptr = head;
    while(ptr->rnext != NULL) {
        ptr = ptr->rnext;
    }
    ptr->rnext = tmp;
    flatten_tree(head->rnext); 
    return;
}

int get_kth_element(struct blist *head, int k)
{

    struct blist *cur, *lnode, *rnode, *prev;
    struct elem *p;

	if (head == NULL)
        return 0;
    
    cur = head;

    while (cur != NULL) {
        prev = cur;
        if (cur->lnext == NULL) {
            k--;
            cur = cur->rnext;
        } else {
            lnode = cur->lnext;
            while (lnode->rnext != NULL && lnode->rnext != cur) {
                lnode = lnode->rnext;
            }
            if (lnode->rnext == NULL) {
                lnode->rnext = cur;
                cur = cur->lnext;
            }
            if (lnode->rnext == cur) {
               k--;
               cur = cur->rnext;
            }
        }
        if (k == 0) {
            p = containerofnode(elem, node, prev);
            return p->a;
        }
           
    }
}
int is_symmetric_tree_martin(struct blist *lhead, struct blist *rhead)
{
    if ((lhead->lnext == NULL) && (rhead->rnext == NULL) &&
        (lhead->rnext == NULL) && (rhead->lnext == NULL)) {
        return 1;
    }
    if (lhead->lnext && rhead->rnext) {
        if (ELEM(lhead->lnext) != ELEM(rhead->rnext)) {
            printf("%d %d\n", ELEM(lhead->lnext), ELEM(rhead->rnext));
            return 0;
        }       
    } else {
        return 0;
    } 
    
    if (lhead->rnext && rhead->lnext) {
        if (ELEM(lhead->rnext) != ELEM(rhead->lnext)) {
            return 0;
        }
    }
    else {
         return 0;
    }
    return (is_symmetric_tree_martin(lhead->lnext, rhead->rnext) &&
            is_symmetric_tree_martin(lhead->rnext, rhead->lnext));
}

int is_symmetric_tree(struct blist *lhead, struct blist *rhead)
{
    if ((lhead == NULL) && (rhead == NULL))
        return 1;

    if (lhead && rhead) {
        if (ELEM(lhead) == ELEM(rhead)) {
             return (is_symmetric_tree(lhead->lnext, rhead->rnext) &&
                     is_symmetric_tree(lhead->rnext, rhead->lnext));

        } 
    }
    return 0;
}

int is_symmetric(struct blist *head)
{
    return is_symmetric_tree(head, head); 
}

void print_list(struct list *head)
{
    struct lelem *p;

    while(head != NULL) {
        p = containerofnode(lelem, node, head);
        printf("%d %x\n", p->a, head);
        head = head->next;
    }
}

struct blist *join_bst(struct blist *a, struct blist *b)
{
    struct blist *bl, *br;

    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }
    printf("Printing input trees\n");
    printf("Printing a\n"); 
    print_blist_preorder(a);
    printf("printing b\n");
    print_blist_preorder(b);
    
    bl = b->lnext;
    br = b->rnext;

    b->lnext = b->rnext = NULL;
    k = 0;
    a = root_insert_node(a, b);
    printf("joined\n");
    print_blist_preorder(a);
    a->lnext = join_bst(a->lnext, bl);
    a->rnext = join_bst(a->rnext, br); 
    return a;
   
}
void join_bst_testcase()
{
    int e[] = {2,4,6,8,10,12,14,16,18};
    int o[] = {1,3,5,7,9,11,13,15,17,19};
    struct blist *ohead, *ehead, *jhead;

    ohead = sortedArrayToBST(o, sizeof(o)/sizeof(int));
    ehead = sortedArrayToBST(e, sizeof(e)/sizeof(int));

    jhead = join_bst(ehead, ohead);
    printf("Joined tree\n");
    print_blist_preorder(jhead);

}

int main()
{
    struct blist *head = NULL;
    struct list *lhead = NULL;
    struct list *thead = NULL;
    int x[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    int u[] = {18,19,6,5,4,3,2,1,7,8,9,10,11,12,13,14,15,16,17};
    int s[] = {2,1,3,0,3,1,2}; 
    int p[] = {5,3,2,1,4,8,7,6,10};
    int mid;
    
    mid = sizeof(x)/sizeof(int)/2;
    printf("Mid value of array is %d\n", x[mid]);
    head  = sortedArrayToBST(x, sizeof(x)/sizeof(int));
   
    
    
//    print_blist_preorder(head);
    print_blist_inorder(head);
//      print_blist_postorder(head);
    lhead = arraytolist(x, sizeof(x)/sizeof(int));
    print_list(lhead);
    head = sortedlistToBST(lhead);
    print_blist_inorder(head);
    printf("Max height of tree %d\n", maxheight_tree(head));
    printf("Min height of tree %d\n", maxheight_tree(head));
    //flatten_tree(head);
    print_blist_inorder(head);
//    printf("Kth element is %d\n", get_kth_element(head, 5));
//    head  = sortedArrayToBST(s, sizeof(s)/sizeof(int));
//    head  = sortedArrayToBST(u, sizeof(u)/sizeof(int));
//    printf("is bst %d\n", isbst(head));
   
//    thead = get_middle_mode(lhead);
//    printf("Printing from middle\n");
//    print_list(thead);
//    printf("Printing from start after making it half\n");
//    print_list(lhead);
// print_blist_inorder(head);
//     printf("tree is asymetric %d\n", is_symmetric(head));
//    head = root_insert(head, 21);
//    head = root_insert(head, 20);
//    head = root_insert(head, 22);
    printf("Printing in preorder\n");
    print_blist_preorder(head);
    print_blist_inorder(head);
    printf("Preorder to tree\n");
    head = preordertotree(p, sizeof(p)/sizeof(int));
    print_blist_preorder(head);
    print_blist_inorder(head);

    printf("Min diff is %d\n", minDiffInBST(head)); 
//    head = rotate_right_tree(head);
//    rotate_right_tree_iterative(&head);
    print_blist_preorder(head);
//    printf("Inserting in root\n");
//    head = insert_in_root(head, 20);
    print_blist_preorder(head);
    printf("Iterative printing\n");
    inorder_iter_init(head);
    for (int q =0; q < 5; q++ ) {
        struct blist *q;
        struct elem *p;

        q = next_bst_elem();
        p = containerofnode(elem, node, q);
        printf("%d\n", p->a);
    }

//    join_bst_testcase();

}
