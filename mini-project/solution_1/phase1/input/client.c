#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trie.h" 

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		return 1;
	}

	trie_t t;
	init_trie(&t);

	char line[1024];
	char delim[] = " \t\r\n`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?0123456789";

	while(fgets(line, sizeof(line), fp) != NULL)
	{
		char *token = strtok(line, delim);
		while(token != NULL)
		{
			for(int i = 0; token[i] != '\0'; ++i)
			{
				token[i] = tolower((unsigned char)token[i]);
			}
			insert_word(&t, token);
			token = strtok(NULL, delim);
		}
	}

	fclose(fp);

	display(&t);

	deinit_trie(&t);
	return 0;
}
