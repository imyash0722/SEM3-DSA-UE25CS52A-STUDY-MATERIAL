FILE=input1.txt

wordindex : client.o trie.o stack.o process_text.o mylist.o
	gcc client.o trie.o stack.o process_text.o mylist.o -o wordindex 
client.o : client.c trie.h process_text.h
	gcc -Wall -c client.c 
trie.o : trie.c trie.h mylist.h
	gcc -Wall -c trie.c 
stack.o : stack.h stack.c 
	gcc -Wall -c stack.c 
process_text.o : process_text.c process_text.h trie.h
	gcc -Wall -c process_text.c
mylist.o : mylist.c mylist.h
	gcc -Wall -c mylist.c

run: wordindex
	@./wordindex $(FILE)

clean:
	rm -f client.o trie.o stack.o process_text.o mylist.o wordindex
