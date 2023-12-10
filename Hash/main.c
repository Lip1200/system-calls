#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/evp.h>
#include "hash.h"
#include "option.h"
#include <string.h>


int main(int argc, char *argv[])
{
    int isFile = 0;     // Indique si l'option -f est spécifiée
    int indFile = -1;   // Stocke l'indice du premier argument de fichier
    int isT = 0;        // Indique si l'option -t est spécifiée
    int indT = -1;      // Stocke l'indice de l'algorithme de hachage
    int start;          // détermine à partir de quel indice de argv commence le traitement de la
                        // chaîne de caractères en entrée lorsque l'option -f n'est pas spécifiée

    // Vérification des options de ligne de commande
    if(parseOptions(argc, argv, &isFile, &indFile, &isT, &indT) == -1){
        fprintf(stderr, "Usage: %s [-t type] [-f file] name\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    // Si l'option -t n'est pas sélectionnée, SHA-1 par défaut
    const EVP_MD* md;
    if (indT == -1)
        md = EVP_get_digestbyname("sha1");
    else
        md = EVP_get_digestbyname(argv[indT]);
    
    if (isFile)  //si -f est séléctionné on passe à la fonction de hachage tous les fichiers donnés en arguments
    {
        // hash la liste des fichiers passés en arguments
        for (int i = indFile+1; i < argc; i++){
            printf("File %s\n", argv[i]);
            FileHash(argv[i], md); 
        }
    }
    else
    {
        if(isT) // Vérifie si l'option -t est sélectionnée et définit le type de hachage en conséquence
            start = indT+1;
        else
            start = 1;

        // Calcul la taille de l'entrée à hacher
        int size_input = strlen(argv[start]);
        StringHash(argv[start], md, size_input);
    }

    exit(EXIT_SUCCESS);
}