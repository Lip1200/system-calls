CC = gcc
CFLAGS = -Wall -g
LIBS = -lssl -lcrypto

OBJS = main.o option.o hash.o

all: hash

hash: $(OBJS)
	$(CC) $(CFLAGS) -o hash $(OBJS) $(LIBS)

main.o: main.c option.h hash.h
	$(CC) $(CFLAGS) -c main.c

option.o: option.c option.h
	$(CC) $(CFLAGS) -c option.c

hash.o: hash.c hash.h option.h
	$(CC) $(CFLAGS) -c hash.c

clean:
	rm -f *.o hash
