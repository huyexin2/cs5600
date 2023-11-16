main: main.c cache.o message.o query.o hashmap.o
	gcc main.c message.o cache.o query.o hashmap.o -o main -lsqlite3 

hashmap.o: hashmap.c hashmap.h
	gcc -Wall -c hashmap.c

message.o: message.c message.h
	gcc -Wall -c message.c

cache.o: cache.c cache.h
	gcc -Wall -c cache.c

query.o: query.c query.h
	gcc -Wall -c query.c

clean:
	rm -f *.o main
