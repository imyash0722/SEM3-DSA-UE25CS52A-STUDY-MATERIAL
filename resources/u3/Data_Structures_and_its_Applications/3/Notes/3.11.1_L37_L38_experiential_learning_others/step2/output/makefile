client.exe : client.o heap.o 
	gcc client.o heap.o -o client.exe
heap.o : heap.c heap.h 
	gcc -Wall -c heap.c 
client.o : client.c heap.h 
	gcc -Wall -c client.c 
	