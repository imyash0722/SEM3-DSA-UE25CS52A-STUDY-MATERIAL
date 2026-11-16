client.exe : client.o heap.o median.o
	gcc client.o heap.o median.o -o client.exe
heap.o : heap.c heap.h 
	gcc -Wall -c heap.c 
client.o : client.c heap.h 
	gcc -Wall -c client.c 
median.o : median.c median.h 
	gcc -Wall -c median.c 