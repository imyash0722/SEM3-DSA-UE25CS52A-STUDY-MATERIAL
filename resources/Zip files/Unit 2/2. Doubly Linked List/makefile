client.exe : client.o dll.o
	gcc client.o dll.o -o client.exe 
client.o : client.c dll.h 
	gcc -Wall -c client.c 
dll.o : dll.c dll.h 
	gcc -Wall -c dll.c 
	