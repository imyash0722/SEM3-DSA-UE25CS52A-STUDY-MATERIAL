client.exe : client.o dll.o stack.o
	gcc client.o dll.o stack.o -o client.exe 
client.o : client.c dll.h 
	gcc -Wall -c client.c 
dll.o : dll.c dll.h 
	gcc -Wall -c dll.c 
stack.o : stack.c stack.h
	gcc -Wall -c stack.c 
	
	