client.exe : client.o poly.o term.o 
	gcc client.o poly.o term.o -o client.exe
poly.o : poly.c poly.h 
	gcc -Wall -c poly.c
term.o : term.c term.h 
	gcc -Wall -c term.c 
client.o : client.c poly.h  term.h 
	gcc -Wall -c client.c