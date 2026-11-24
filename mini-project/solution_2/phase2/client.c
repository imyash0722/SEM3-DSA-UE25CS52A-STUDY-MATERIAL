#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h" 
#include "process_text.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return 1;
	}

	trie_t t;
	init_trie(&t);

	char filename[1024];
	strcpy(filename, argv[1]);
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		return 1;
	}
	
	process_file(&t, fp);
	fclose(fp);
	display(&t); 
	deinit_trie(&t);
	return 0;
}
