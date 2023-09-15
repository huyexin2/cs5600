CC = gcc
CFLAGS  = -g -Wall

default: allocmem

allocmem: alloc-mem-lastname.o
	$(CC) $(CFLAGS) -o alloc-mem alloc-mem-lastname.o

alloc-mem-lastname.o: alloc-mem-lastname.c 
	$(CC) $(CFLAGS) -c alloc-mem-lastname.c
