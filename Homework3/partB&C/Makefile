CC = gcc
CFLAGS  = -g -Wall

default: loadmem

loadmem: load-mem-lastname.o
	$(CC) $(CFLAGS) -o load-mem load-mem-lastname.o

load-mem-lastname.o: load-mem-lastname.c 
	$(CC) $(CFLAGS) -c load-mem-lastname.c
