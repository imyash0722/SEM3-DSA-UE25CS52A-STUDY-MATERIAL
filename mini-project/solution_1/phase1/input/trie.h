#ifndef TRIE_H
#define TRIE_H
#define MAXSIZE 26
struct node 
{
	struct node *child[MAXSIZE];
	int is_word_end;
	int count;
};	
typedef struct node node_t;
struct trie
{
	node_t* root_;
};
typedef struct trie trie_t;
void init_trie(trie_t *ptr_trie);
void deinit_trie(trie_t *ptr_trie);
void insert_word(trie_t *ptr_tree, char* s);
void delete_word(trie_t *ptr_tree, char* s);
void display(trie_t *ptr_trie);
int search(trie_t *ptr_trie, char* s);
void all_prefix(trie_t *ptr_trie, char* s);
#endif 
