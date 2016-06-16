CC=gcc -std=c99
CFLAGS=-I.

pollserver: poolserver.o
	$(CC) -o poolserver poolserver.o  $(CFLAGS) 

.PHONY: clean

clean:
		rm -f ./*.o 
