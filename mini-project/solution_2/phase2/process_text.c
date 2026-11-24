#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"
#include "process_text.h"

// string tokenizer
void word_to_lower(char s[])
{
	char *p = s;
	while(*p != '\0')
	{
		*p = tolower(*p);
		++p;
	}
}
void process_line(trie_t* tr, char line[], char delim[], int line_no)
{
	char *token = strtok(line, delim); // string to tokenize - the first argument 
	// first time only
    while (token != NULL) {
		word_to_lower(token);
		insert_word(tr, token, line_no);
        token = strtok(NULL, delim); // continue tokenizing the given string
    }
}

void process_file(trie_t* tr, FILE *fp)
{
	char line[1024];
	char delim[] = " \t\r\n`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?0123456789";
	int line_no = 0;

	while(fgets(line, sizeof(line), fp) != NULL)
	{
		++line_no;
		process_line(tr, line, delim, line_no);
	}
}
