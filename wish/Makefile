CC = gcc
CFLAGS = -Wall -g

# Vérifie si libreadline est disponible en utilisant ldconfig
READLINE_AVAILABLE := $(shell ldconfig -p | grep readline | wc -l)

# Ajuste les drapeaux en fonction de la disponibilité de readline
ifeq ($(READLINE_AVAILABLE),0)
  LIBS =
else
  CFLAGS += -DUSE_READLINE=1
  LIBS = -lreadline
endif

wish: main.o func.o
	$(CC) $(CFLAGS) -o wish main.o func.o $(LIBS)

main.o: main.c func.h
	$(CC) $(CFLAGS) -c main.c

func.o: func.c func.h
	$(CC) $(CFLAGS) -c func.c

clean:
	rm -f wish main.o func.o

.PHONY: clean
