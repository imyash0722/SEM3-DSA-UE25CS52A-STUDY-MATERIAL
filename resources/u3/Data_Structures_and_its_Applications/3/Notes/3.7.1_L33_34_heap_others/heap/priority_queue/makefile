client.exe : client.o heap.o queue.o
	gcc client.o heap.o queue.o -o client.exe
heap.o : heap.c heap.h 
	gcc -Wall -c heap.c 
client.o : client.c heap.h 
	gcc -Wall -c client.c 
queue.o : queue.h queue.c
	gcc -Wall -c queue.c 
	
	