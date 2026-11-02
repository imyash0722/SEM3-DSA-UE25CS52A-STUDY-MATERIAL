a.exe : mylist.o client.o
	gcc mylist.o client.o
mylist.o : mylist.c mylist.h
	gcc -Wall -c mylist.c 
client.o : client.c mylist.h
	gcc -Wall -c client.c 
	
