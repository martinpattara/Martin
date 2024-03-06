#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct tnode trie_head;

struct tnode {
	char pre[128];
    struct tnode *tp[26];
    char word[128];
    char cindex;
    char letters;
    bool cword;
};

struct tnode *  create_node(char *str, int cindex, int len, bool leaf)
{
   struct tnode *node;

   printf("Create node %d %d\n", cindex, len);
   node = malloc(sizeof(struct tnode));
   memset(node ,0x0, sizeof(struct tnode));
   memcpy(node->pre, &str[cindex], len);
   node->letters = len;
   if (leaf) {
       strcpy(node->word, str);
       node->cword = true;
   }
   return node;
}

struct tnode **get_node_ptr(struct tnode *node, char tindex)
{
    return &node->tp[tindex];
}

struct tnode *get_node(struct tnode *node, char tindex)
{
    return node->tp[tindex];
}
int populate_str(struct tnode *node, char *str, int cindex)
{
    int i = 0, tindex;
    bool orig_cword;
    struct tnode *ptr;

    printf("populate_str %d\n", cindex);
	for (i = 0; i < node->letters; i++) {
         if (node->pre[i] != str[cindex +i]) {
             printf("%d %d\n", node->pre[i], str[cindex +i]);
             break;
         }
    }

    if (i == node->letters) {
        printf("i = node->letters %d\n", node->letters);
        return node->letters;
    } else {
        orig_cword = node->cword;        
        if (str[cindex + i] == '\0') {
            node->cword = true;

        } else {
            node->cword = false;
            printf("restting cword\n");
		}
        tindex = node->pre[i] - 'a';
        printf("Tindex = %d %c\n", tindex, node->pre[i]);
        ptr =  create_node(node->word, i, node->letters - i,
                                       orig_cword);
        memcpy(ptr->tp, node->tp, 26 *sizeof(struct tnode *));
        printf("Cnode pointer %x\n", ptr);
        node->tp[tindex]  = ptr;
        node->tp[node->letters] = NULL;
        node->letters = i;
        strcpy(node->word, str);
        return node->letters;
    }
}

void insert_node(struct tnode *trie_head, char *str)
{
    char cindex;
    char advance;

    struct tnode *cnode, *node, **cnode_ptr ;
	cindex = 0;
    node = trie_head;
    printf("Insert node %s\n", str);
    while (str[cindex]!='\0') {
		cnode_ptr = get_node_ptr(node, str[cindex] - 'a');
        if (*cnode_ptr == NULL) {
		   *cnode_ptr = create_node(str, cindex, strlen(str) - cindex,  1);
           printf("Cnode pointer %x\n", *cnode_ptr);
           advance = (*cnode_ptr)->letters;
        } else {
           advance = populate_str(*cnode_ptr, str, cindex); 
        }
        cindex = advance + cindex;
        node = *cnode_ptr;
    } 
}

void print_trie(struct tnode *root) 
{
	int i = 0;
    struct tnode *node;

    node = root;
    printf("print_trie %x\n", root);
    if (node->cword) {
        printf("%s\n", node->word);
    }
    for (i = 0; i < node->letters; i++) {
       printf("%c", node->pre[i]);
    }
    printf("\n");
    for (i =0; i < 26; i++) {
    	if (node->tp[i] != NULL) {
            print_trie(node->tp[i]);
        }
    }
}


void insert_word_trie(char *str)
{
	insert_node(&trie_head, str);
}

int match_str(struct tnode *node, char *str, char cindex, char len)
{
    int i = 0; 

    for (i = 0; i < node->letters; i++) {
         if (node->pre[i] != str[cindex +i]) {
             break;
         }
    }
    if (i == node->letters) {
        if (str[cindex + i] == '\0') {
            printf("%d %d\n", cindex, i);
            return 0;
        } else {
            printf("returning %d\n", node->letters);
            return node->letters;
        } 
    } else {
        return -1;
    }
}

bool trie_lookup(struct tnode *root, char *str)
{
    char cindex;
    char advance;

    struct tnode *cnode, *node, **cnode_ptr ;
    cindex = 0;
    node = root;
    while (str[cindex]!='\0') {
        cnode_ptr = get_node_ptr(node, str[cindex] - 'a');
        if (*cnode_ptr == NULL) {
            printf("Word pointer not found %d %c\n", cindex, str[cindex]);
            
            return false;
        } else {
			advance = match_str(*cnode_ptr, str, cindex, strlen(str) - cindex);
            if (!advance) {
                printf("word found\n");
                return true;
            } else if (advance == -1) {
                printf("word not found\n");
                return 0;
            } else {
               cindex = cindex + advance;
            }
            node = *cnode_ptr;
        }
     }
}
	

bool word_lookup(char *str)
{
    trie_lookup(&trie_head, str);
}

int main()
{   
    insert_word_trie("flower");
    insert_word_trie("flow");
    insert_word_trie("flew"); 
  //  insert_word_trie("flow"); 
//	insert_word_trie("flower");
    print_trie(&trie_head);
   // insert_word_trie("flow");
   word_lookup("flew");

}
