arger-hu: HuYCommandLine.c compareArgument.o letterConversion.o
	gcc HuYCommandLine.c compareArgument.o letterConversion.o -o arger-hu

compareArgument.o: compareArgument.c compareArgument.h
	gcc -c compareArgument.c
		
letterConversion.o: letterConversion.c letterConversion.h
	gcc -c letterConversion.c

clean:
	rm *.o 
