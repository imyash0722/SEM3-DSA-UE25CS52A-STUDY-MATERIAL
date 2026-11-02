client.exe : client.o tree.o 
	gcc client.o tree.o -o client.exe
tree.o : tree.c tree.h 
	gcc -Wall -c tree.c 
client.o : client.o tree.h 
	gcc -Wall -c client.c 
	