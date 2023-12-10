#include "option.h"
#include <stdio.h>
#include <getopt.h>

int parseOptions(int argc, char* argv[], int* isA, int* isF, int* nbOpt){
    int opt; // Variable pour stocker l'option actuellement analysée
    // Boucle pour analyser toutes les options fournies
    while ((opt = getopt(argc, argv, "af")) != -1){
        switch (opt) {
            case 'a':
                *isA = 1;
                *nbOpt +=1;
                break;
            case 'f': // Option pour spécifier que les liens seront copiés en tant que lien
                *isF = 1;
                *nbOpt +=1;
                break;
            default: // Gestion des options non reconnues ou des erreurs
                fprintf(stderr, "Usage: %s [-a] [-f] source(s) destination\n", argv[0]);
                return -1; // Retourne une erreur pour les options non reconnues
        }
    }
    return 0;
}

