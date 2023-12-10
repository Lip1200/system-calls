CC = gcc
CFLAGS = -Wall -g
LIBS =

OBJS = main.o copy.o option.o func.o

all: ultra-cp

ultra-cp: $(OBJS)
	$(CC) $(CFLAGS) -o ultra-cp $(OBJS) $(LIBS)

main.o: main.c copy.h option.h
	$(CC) $(CFLAGS) -c main.c

copy.o: copy.c copy.h
	$(CC) $(CFLAGS) -c copy.c

option.o: option.c option.h
	$(CC) $(CFLAGS) -c option.c

func.o: func.c func.h
	$(CC) $(CFLAGS) -c func.c

clean:
	rm -f *.o ultra-cp
