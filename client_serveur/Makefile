CC=gcc
CFLAGS=-Wall -g

# Cibles pour construire les programmes serveur et client
all: serveur client

# Compilation du serveur
serveur: serveur.o fonctions.o
	$(CC) $(CFLAGS) -o serveur serveur.o fonctions.o

# Compilation du client
client: client.o fonctions.o
	$(CC) $(CFLAGS) -o client client.o fonctions.o

# Compilation des fichiers objet du serveur
serveur.o: serveur.c common.h fonctions.h
	$(CC) $(CFLAGS) -c serveur.c

# Compilation des fichiers objet du client
client.o: client.c common.h fonctions.h
	$(CC) $(CFLAGS) -c client.c

# Compilation des fonctions partagées
fonctions.o: fonctions.c fonctions.h common.h
	$(CC) $(CFLAGS) -c fonctions.c

# Nettoyage des fichiers compilés
clean:
	rm -f *.o client serveur
