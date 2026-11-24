FILE=input1.txt

wordindex : client.o trie.o stack.o
	gcc client.o trie.o stack.o -o wordindex 
client.o : client.c trie.h 
	gcc -Wall -c client.c 
trie.o : trie.c trie.h 
	gcc -Wall -c trie.c 
stack.o : stack.h stack.c 
	gcc -Wall -c stack.c 

run: wordindex
	@./wordindex $(FILE)
clean:
	rm -f client.o trie.o stack.o wordindex
