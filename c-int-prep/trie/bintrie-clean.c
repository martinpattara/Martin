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

uint32_t add_bits(struct tnode *node, uint32_t ip, uint32_t pos)
{
    uint32_t mask, x;
    struct tnode  **cnode_ptr;
    mask = get_mask(pos, node->mlen);
    printf("In add bits %d %d\n", node->pos, node->mlen);
    printf("Mask is %x\n", mask);
    x = ((node->prefix & mask) ^ (ip & mask));
    printf("%x %x\n", node->prefix, ip & mask);
    printf("%d %x\n",x, mask); 
    if (!x) {
        printf("All matched\n");
        return pos +  node->mlen;
    } else {
        x = ffs(x);
        cnode_ptr = get_node_ptr(node, ((node->prefix >> (31 - x)) & 0x01));
        *cnode_ptr = create_node(node->prefix, x, node->mlen - (x -  node->pos),  1, node->devname);
        node->mlen = (x -  node->pos);
        return  x;
    } 
}
struct tnode  * route_lookup(struct tnode *trie_head, uint32_t prefix)
{
    uint8_t pos, i = 0;
    uint32_t mask, x;
    struct tnode *prev;
    uint32_t p_prefix;
    struct tnode *cnode, *node, **cnode_ptr;

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
          prev = *cnode_ptr;
     }
     return prev;
}


void insert_node(struct tnode *trie_head, uint32_t prefix, uint32_t mlen, char *name)
{
    uint8_t pos, i = 0;
    char advance;
    uint32_t p_prefix;
    struct tnode *cnode, *node, **cnode_ptr;

    p_prefix = prefix;
    pos  = 0;
    node = trie_head;
    printf("Insert node %x %x\n", prefix, p_prefix & (0x01 << 31));
    

    for (cnode_ptr = get_node_ptr(node, ((p_prefix >> (31 - pos)) & 0x01));
         *cnode_ptr != NULL;
         cnode_ptr = get_node_ptr(*cnode_ptr, ((p_prefix >> (31-pos)) & 0x01))) { 
         pos = add_bits(*cnode_ptr, prefix, pos);
         printf("Pos = %d\n", pos);
         printf("prefix = %x\n", ((p_prefix >> (31 - pos)) & 0x01));
    }
    *cnode_ptr = create_node(prefix, pos, mlen - pos,  1, name);
}

void insert_route(uint32_t ip, uint32_t mlen, char *name)
{
    insert_node(&trie_head, ip, mlen, name);
}

int main()
{
    struct tnode *node;
    insert_route(0x10000000, 8,  "eth1");
    insert_route(0x10000000, 24, "eth2");
    insert_route(0x10000100, 24, "eth3");
    insert_route(0x10000101, 32, "eth4");
    if (node = route_lookup(&trie_head, 0x10000111)) {
        printf("%s", node->devname);
    } else {
        printf("Route not present\n");
    }

}

