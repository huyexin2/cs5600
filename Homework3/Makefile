CC = gcc
CFLAGS  = -g -Wall

default: allocmem

allocmem: alloc-mem-lastname.o
	$(CC) $(CFLAGS) -o allocmem alloc-mem-lastname.o alloc-mem.o

alloc-mem-lastname.o: alloc-mem-lastname.c alloc-mem.o
	$(CC) $(CFLAGS) -c alloc-mem-lastname.c

alloc-mem.o: alloc-mem.c alloc-mem.h
	$(CC) $(CFLAGS) -c alloc-mem.c
