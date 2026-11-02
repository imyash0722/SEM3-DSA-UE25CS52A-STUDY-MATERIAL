a.exe : clist.o client.o
	gcc clist.o client.o -o client.exe
clist.o : clist.c clist.h
	gcc -Wall -c clist.c 
client.o : client.c clist.h
	gcc -Wall -c client.c 
	
