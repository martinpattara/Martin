#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
struct tnode trie_head;

struct tnode {
    uint32_t prefix;
    uint32_t route;
    uint32_t pos;
    uint32_t mlen;
    uint32_t bitmask;    
    bool route_flag;
    struct tnode *cnode[2];
    struct tnode *parent;
    char devname[24];
};

struct tnode **get_node_ptr(struct tnode *node, char tindex)
{
    return &node->cnode[tindex];
}

uint32_t get_mask(unsigned int p, int n)
{
   int m = ~0;
   int op = 32 - p;

   for (int i = 0; i < 32 - p; i++) {
      m =  m << 1;
   }
   m = ~m;
   return (m  & (~0 << (op - n)));
}

struct tnode *  create_node(uint32_t ip, int pos, uint32_t  mlen, bool leaf, char *name)
{
   struct tnode *node;

   printf("Create node %d %d %x\n", pos, mlen, get_mask(pos, mlen));
   node = malloc(sizeof(struct tnode));
   memset(node ,0x0, sizeof(struct tnode));
   node->prefix = ip;
   node->mlen = mlen;
   node->pos = pos;
   if (leaf) {
       node->route = ip;
       node->route_flag   = true;
       strcpy(node->devname, name); 
   }
   return node;
}
int ffs(int x)
{
   int i = 0;
   while (!(x  & (1 << 31))) {
       x = x << 1;
       i++;
   }
   return i;
}

uint32_t add_bits(struct tnode *node, uint32_t ip, uint32_t pos, uint32_t mlen, char *name)
{
    uint32_t mask, x;
    struct tnode  **cnode_ptr;
    int route_flag = 0;

    mask = get_mask(pos, node->mlen);
    printf("In add bits %d %d %d\n", node->pos, node->mlen, mlen);
    printf("Mask is %x\n", mask);
    x = ((node->prefix & mask) ^ (ip & mask));
    printf("%x %x\n", node->prefix, ip & mask);
    printf("%d %x\n",x, mask); 
    if (!x) {
        if ((node->mlen <= mlen)) {
            printf("All matched\n");
            return  node->mlen;
         } else {
            x = pos + mlen;
            printf("Update node's route\n");
            route_flag = 1;
         }   
    } else  {
        printf("Mismatch\n");
        x = ffs(x);
    }
    cnode_ptr = get_node_ptr(node, ((node->prefix >> (31 - x)) & 0x01));
    *cnode_ptr = create_node(node->prefix, x, node->mlen - (x -  node->pos),  1, node->devname);
    node->mlen = (x -  node->pos);
    node->route_flag = route_flag;
    strcpy(node->devname, name);
    return  node->mlen;;
     
}
struct tnode  * route_lookup(struct tnode *trie_head, uint32_t prefix)
{
    uint8_t pos, i = 0;
    uint32_t mask, x;
    struct tnode *prev;
    uint32_t p_prefix;
    struct tnode *cnode, *node, **cnode_ptr;

    printf("In route lookup\n");

    p_prefix = prefix;
    pos  = 0;
    node = trie_head;

    
    prev = NULL;
    for (cnode_ptr = get_node_ptr(node, ((p_prefix >> (31 - pos)) & 0x01));
          *cnode_ptr != NULL;
          cnode_ptr = get_node_ptr(*cnode_ptr, ((p_prefix >> (31-pos)) & 0x01))) {

          mask = get_mask(pos, (*cnode_ptr)->mlen);
          x = ((((*cnode_ptr)->prefix) & mask) ^ (prefix & mask));
          printf("mask %x\n", mask);
          if (x) {
              printf("Breaking\n");
              break;
          }
          pos =  pos +  (*cnode_ptr)->mlen;
          if ((*cnode_ptr)->route_flag) {
              prev = *cnode_ptr;
          } else {
            printf("Not a route node\n");
          }
     }
     return prev;
}


void insert_node(struct tnode *trie_head, uint32_t prefix, uint32_t mlen, char *name)
{
    uint8_t pos, i = 0;
    char advance = 0;
    uint32_t p_prefix;
    uint32_t len = mlen;
    struct tnode *cnode, *node, **cnode_ptr;

    p_prefix = prefix;
    pos  = 0;
    node = trie_head;
    printf("Insert node %x %x\n", prefix, p_prefix & (0x01 << 31));
    

    for (cnode_ptr = get_node_ptr(node, ((p_prefix >> (31 - pos)) & 0x01));
         ((*cnode_ptr != NULL) && (len > 0));
         cnode_ptr = get_node_ptr(*cnode_ptr, ((p_prefix >> (31-pos)) & 0x01))) { 
         advance = add_bits(*cnode_ptr, prefix, pos, len, name);
         printf("Pos = %d\n", pos);
         printf("prefix = %x\n", ((p_prefix >> (31 - pos)) & 0x01));
         len = len - advance;
         pos = pos + advance;
    }
     if (len) {
        printf("creating node of len %d\n", len);
        *cnode_ptr = create_node(prefix, pos, mlen - pos,  1, name);
     } else {
        printf("Length is 0\n");
     }
}

void insert_route(uint32_t ip, uint32_t mlen, char *name)
{
    insert_node(&trie_head, ip, mlen, name);
}

int main()
{
    struct tnode *node;
    insert_route(0x10000000, 24,  "eth1");
    insert_route(0x10000000, 24,  "eth6");
    insert_route(0x10000000, 8, "eth2");
    insert_route(0x10000100, 32, "eth3");
    insert_route(0x10000101, 32, "eth4");
#if 1
    if (node = route_lookup(&trie_head, 0x10000001)) {
        printf("%s", node->devname);
    } else {
        printf("Route not present\n");
    }
#endif

}

