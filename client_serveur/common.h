#ifndef COMMON_H
#define COMMON_H

// Inclusions standard pour les opérations d'entrée/sortie, la gestion de la mémoire, etc.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Inclusions pour les opérations de réseau et de sockets
#include <sys/socket.h>
#include <arpa/inet.h>

// Inclusions pour diverses opérations système
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Définition de la borne supérieure pour le jeu de devinettes
#define MAX_GUESS 20

// Nombre maximum de tentatives autorisées pour le jeu de devinettes
#define MAX_TENTATIVES 4

// Codes pour indiquer l'état de la proposition du joueur
#define TOO_LOW -1
#define WIN 0
#define TOO_HIGH 1
#define LOSE 2

// Taille du buffer pour les opérations de lecture/écriture dans les sockets
#define BUFFER_SIZE 256

#endif // COMMON_H
