#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <openssl/evp.h>

// Fonction pour parser les options de ligne de commande
int parseOptions(int argc, char* argv[], int* isFile, int* indFile, int* isT, int* indT)
{
    int opt;

    // Utilisation de getopt pour traiter les options de ligne de commande
    while ((opt = getopt(argc, argv, "t:f")) != -1)
    {
        switch (opt)
        {
        case 'f':
            // L'option -f est spécifiée, indiquant que le programme doit traiter un fichier
            *isFile = 1;
            // Stocke l'indice du premier argument de fichier
            *indFile = optind-1;
            break;
        case 't':
            // L'option -t est spécifiée, indiquant l'algorithme de hachage
            *isT = 1;
            // Stocke l'indice de l'algorithme de hachage
            *indT = optind-1;
            // Vérifie si un argument est spécifié avec l'option -t
            if (optarg == NULL)
            {
                printf("Unknown message digest %s\n", optarg);
                return -1;
            }
            break;
        default: /* '?' */
            // Une option non reconnue est spécifiée
            fprintf(stderr, "Usage: %s [-t type] [-f file] name\n",
                    argv[0]);
            return -1;
        }
    }

    return 0;
}
