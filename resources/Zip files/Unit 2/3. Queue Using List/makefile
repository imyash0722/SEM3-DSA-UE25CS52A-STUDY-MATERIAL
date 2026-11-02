client.exe : client.o queue.o
	gcc client.o queue.o -o client.exe 
client.o : client.c queue.h 
	gcc -Wall -c client.c 
queue.o : queue.c queue.h 
	gcc -Wall -c queue.c 