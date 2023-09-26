qtest: queuetest.c queue.o
	gcc queuetest.c queue.o -o qtest

queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm *.o 
