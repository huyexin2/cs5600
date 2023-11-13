main: main.c cache.o message.o 
	gcc main.c message.o cache.o -o main -lsqlite3 

message.o: message.c message.h
	gcc -Wall -c message.c

cache.o: cache.c cache.h
	gcc -Wall -c cache.c

clean:
	rm -f *.o main
