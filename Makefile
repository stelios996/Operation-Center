CC=gcc

CFLAGS= -c -I.

all: werhauz

werhauz: main.o structure.o readfunctions.o hash.o
	$(CC) -o werhauz main.o structure.o readfunctions.o hash.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

structure.o: structure.c
	$(CC) $(CFLAGS) structure.c

readfunctions.o: readfunctions.c
	$(CC) $(CFLAGS) readfunctions.c

hash.o: hash.c
	$(CC) $(CFLAGS) hash.c

clean:
	rm -f *.o werhauz
