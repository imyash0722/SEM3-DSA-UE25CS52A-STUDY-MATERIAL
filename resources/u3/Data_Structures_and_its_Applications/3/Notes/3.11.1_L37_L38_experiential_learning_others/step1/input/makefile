client.exe : client.o function.o
	gcc client.o function.o -o client.exe
function.o : function.c function.h 
	gcc -Wall -c function.c 
client.o : client.c function.h 
	gcc -Wall -c client.c 
	