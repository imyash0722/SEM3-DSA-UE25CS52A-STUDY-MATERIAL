#ifndef TRIE_H
#define TRIE_H
#include <stdio.h>
#include "mylist.h"
#define MAXSIZE 26
struct trie_node 
{
	struct trie_node *child_[MAXSIZE];
	int count_;
	mylist_t lines_;
};	
typedef struct trie_node trie_node_t;
struct trie
{
	trie_node_t* root_;
};
typedef struct trie trie_t;
void init_trie(trie_t *ptr_trie);
void deinit_trie(trie_t *ptr_trie);
void insert_word(trie_t *ptr_tree, char* s, int line_no);
void display(trie_t *ptr_trie);
int search(trie_t *ptr_trie, char* s);
void all_prefix(trie_t *ptr_trie, char* s);
#endif 
