CC = gcc
CFLAGS = -Wall -g
LIBS =

TARGET = locker
OBJS = main.o func.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c func.h
	$(CC) $(CFLAGS) -c main.c

func.o: func.c func.h
	$(CC) $(CFLAGS) -c func.c

clean:
	rm -f *.o $(TARGET)
