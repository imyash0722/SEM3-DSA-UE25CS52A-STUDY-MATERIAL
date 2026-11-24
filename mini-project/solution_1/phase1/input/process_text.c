#include <stdio.h>
#include <string.h>
// string tokenizer
int main()
{
	char s[] = "Betty Botter bought some butter";
	char delim[] = " "; // string of delimiters
	char *token = strtok(s, delim); // string to tokenize - the first argument 
	// first time only
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delim); // continue tokenizing the given string
		// use NULL as the first argument
    }
}