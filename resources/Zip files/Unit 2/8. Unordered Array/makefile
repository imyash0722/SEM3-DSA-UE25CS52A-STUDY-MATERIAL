client.exe : client.o queue.o job.o
	gcc client.o queue.o job.o -o client.exe 
client.o : client.c queue.h job.h
	gcc -Wall -c client.c 
queue.o : queue.c queue.h job.h
	gcc -Wall -c queue.c 
job.o : job.c job.h 
	gcc -Wall -c job.c 
	