CFLAGS= -std=c99 -Wall

all: helloworld.c Makefile
	gcc $(CFLAGS) helloworld.c -o helloworld
	
clean: 
	rm -f *.o helloworld