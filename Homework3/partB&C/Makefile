CC = gcc
CFLAGS  = -g -Wall

default: loadmem

loadmem: load-mem-lastname.o
	$(CC) $(CFLAGS) -o load-mem load-mem-lastname.o block-impl.o 

load-mem-lastname.o: load-mem-lastname.c block-impl.o 
	$(CC) $(CFLAGS) -c load-mem-lastname.c

block-impl.o: block-structure.h block-impl.h block-impl.c
	$(CC) $(CFLAGS) -c block-impl.c


