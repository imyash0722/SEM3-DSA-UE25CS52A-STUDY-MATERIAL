#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "trie.h"
#include "stack.h"

static trie_node_t* create_node()
{
	trie_node_t* temp = (trie_node_t*)malloc(sizeof(trie_node_t));
	for(int i = 0; i < MAXSIZE; ++i)
	{
		temp->child_[i] = NULL;
	}
	temp->count_ = 0;
	init_list(&temp->lines_);
	return temp;
}

void init_trie(trie_t *ptr_trie)
{
	ptr_trie->root_ = create_node();
}

static void deinit_recursive(trie_node_t *temp)
{
	for(int i = 0; i < MAXSIZE; ++i)
	{
		if(temp->child_[i])
		{
			deinit_recursive(temp->child_[i]);
			free_list(&temp->child_[i]->lines_);
		}
		free(temp->child_[i]);
	}
}
void deinit_trie(trie_t *ptr_trie)
{
	deinit_recursive(ptr_trie->root_);
	free_list(&ptr_trie->root_->lines_);
	free(ptr_trie->root_);
}

// check if the word already exists and  increment the count in such a case
void insert_word(trie_t *ptr_trie, char* s, int line_no)
{
	trie_node_t* pres = ptr_trie->root_;
	int ch;
	while((ch = *s++) != '\0')
	{
		int idx = ch - 'a';
		if(idx < 0 || idx >= MAXSIZE)
			continue;
		if(pres->child_[idx] == NULL)
		{
			pres->child_[idx] = create_node();
		}
		pres = pres->child_[idx];
	}
	++pres->count_;
	node_t* cur = pres->lines_.head_;
	while(cur && cur->next_)
	{
		cur = cur->next_;
	}
	if(cur == NULL || cur->key_ != line_no)
	{
		insert_list(&pres->lines_, line_no);
	}
}

static void display_recursive(trie_node_t *pres, char word[], int* ptr_len)
{
	for(int i = 0; i < MAXSIZE; ++i)
	{
		if(pres->child_[i] != NULL)
		{
			word[(*ptr_len)++] = 'a' + i;
			if(pres->child_[i]->count_)
			{
				word[*ptr_len] = '\0';
				printf("word : %s :", word);
				node_t* cur = pres->child_[i]->lines_.head_;
				while(cur != NULL)
				{
					printf(" %d", cur->key_);
					cur = cur->next_;
				}
				printf("\n");
			}
			display_recursive(pres->child_[i], word, ptr_len);
			--(*ptr_len);  
		}
	}
}

void display(trie_t *ptr_trie)
{
	char word[MAXSIZE * 4] = ""; 
	int len = 0;
	display_recursive(ptr_trie->root_, word, &len);
}

static trie_node_t* prefix(trie_node_t* pres, char* s)
{
	int ch;
	while((ch = *s++) != '\0')
	{
		int idx = ch - 'a';
		if(idx < 0 || idx >= MAXSIZE)
			return NULL;
		if(pres->child_[idx] == NULL)
			return NULL;
		pres = pres->child_[idx];
	}
	return pres;
}

int search(trie_t *ptr_trie, char* s)
{
	trie_node_t* pres = prefix(ptr_trie->root_, s);
	return (pres != NULL) && pres->count_;
}

void all_prefix(trie_t *ptr_trie, char* s)
{
	trie_node_t* pres = prefix(ptr_trie->root_, s);
	if(pres == NULL)
		return;
	if(pres->count_)
		printf("word: %s count %d\n", s, pres->count_);
	char word[MAXSIZE * 4];
	strcpy(word, s);
	int len = strlen(s);
	display_recursive(pres, word, &len);	
}
