CC = gcc
CFLAGS = -Wall -Wextra -g
COOK = cook
SERVER = server

# Cible par défaut pour construire les programmes
all: $(COOK) $(SERVER)

# Règle pour construire le programme cook
$(COOK): $(COOK).c pizza_rack.h
	$(CC) $(CFLAGS) -o $(COOK) $(COOK).c

# Règle pour construire le programme server
$(SERVER): $(SERVER).c pizza_rack.h
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER).c

# Nettoyage des fichiers exécutables
clean:
	rm -f $(COOK) $(SERVER)

