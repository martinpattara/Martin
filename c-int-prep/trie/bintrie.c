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
   //return m;
   return (m  & (~0 << (op - n)));
}



struct tnode *  create_node(uint32_t ip, int pos, uint32_t  mlen, bool leaf)
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
#if 0
uint32_t get_mask(unsigned int p, int n)
{
   int m = ~0;
   int op = 32 - p;

   for (int i = 0; i < 32 - p; i++) {
      m =  m << 1;
   }
   m = ~m;
   //return m;
   return (m  & (~0 << (op - n)));
}
#endif

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
    //    node->mlen =  (x -  node->pos);
      //  node->pos = x;
        cnode_ptr = get_node_ptr(node, ((node->prefix >> (31 - x)) & 0x01));
        *cnode_ptr = create_node(node->prefix, x, node->mlen - (x -  node->pos),  1);
        node->mlen = (x -  node->pos);
        return  x;
    } 
}

void insert_node(struct tnode *trie_head, uint32_t prefix, uint32_t mlen)
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
      //   p_prefix  = p_prefix << pos;
         printf("prefix = %x\n", ((p_prefix >> (31 - pos)) & 0x01));
    //     if (++i == 5)
      //       break;
        // mlen = mlen - pos;
    }
    *cnode_ptr = create_node(prefix, pos, mlen - pos,  1);
    
/*
      while (p_prefix = p_prefix << pos) {
        cnode_ptr = get_node_ptr(node, p_prefix & (0x01 << 31));
        if (*cnode_ptr == NULL) {
           *cnode_ptr = create_node(str, pos, mask,  1);
           printf("Cnode pointer %x\n", *cnode_ptr);
           advance = (*cnode_ptr)->bits;
        } else {
           advance = add_bits(*cnode_ptr, str, cindex);
        }
        pos = advance + cindex;
        node = *cnode_ptr;
    }
*/

}

void insert_route(uint32_t ip, uint32_t mlen)
{
    insert_node(&trie_head, ip, mlen);
}

int main()
{
    insert_route(0x10000000, 8);
    insert_route(0x10000000, 24);
    insert_route(0x10000100, 24);
    insert_route(0x10000101, 32);

}

