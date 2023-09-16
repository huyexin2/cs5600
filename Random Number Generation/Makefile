genRand: genRand-hu.c randomNumber.o
	gcc genRand-hu.c randomNumber.o -o genRand

randomNumber.o: randomNumber.c randomNumber.h
	gcc -c randomNumber.c

clean:
	rm *.o 
